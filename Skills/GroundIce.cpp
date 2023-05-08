#include "GroundIce.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystem.h"
#include "Weapon/UCWeaponStructure.h"
#include "Utillities/TaskHelper.h"

AGroundIce::AGroundIce()
{
	Capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	Particle = CreateDefaultSubobject<UFXSystemAsset>("Particle");
	SetRootComponent(Capsule);
}

void AGroundIce::BeginPlay()
{
	Super::BeginPlay();
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &AGroundIce::ComponentBeginOverlap);

	if(Cast<UParticleSystem>(Particle) != nullptr)
	{
		auto particlesystem = TaskHelper::PlayParticleSystem(GetWorld(), Particle, GetActorLocation());
		particlesystem->OnSystemFinished.AddDynamic(this, &AGroundIce::OnParticleFinish);
	}
	else if(Cast<UNiagaraSystem>(Particle) != nullptr)
	{
		auto particlesystem = TaskHelper::PlayNiagaraSystem(GetWorld(), Particle, GetActorLocation());
		particlesystem->OnSystemFinished.AddDynamic(this, &AGroundIce::OnNiagaraFinish);
	}
}

void AGroundIce::SetDamageData(FDamageData _DamageData)
{
	DamageData_ = _DamageData;
}

void AGroundIce::ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->GetClass() == GetOwner()->GetClass())
		return;

	if(OtherActor == GetOwner())
		return;

	if(Cast<ACharacter>(OtherActor) == nullptr)
		return;

	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(Character == nullptr)
		return;

	for(const auto& HittedCharacter : HittedCharacters)
	{
		if(HittedCharacter == OtherCharacter)
			return;
	}

	HittedCharacters.Add(OtherCharacter);

	OtherCharacter->TakeDamage(DamageData_.Damage, DamageData_, Character->GetController(), this);
}

void AGroundIce::OnNiagaraFinish(UNiagaraComponent* niagara)
{
	Destroy();
}

void AGroundIce::OnParticleFinish(UParticleSystemComponent* PSystem)
{
	Destroy();
}



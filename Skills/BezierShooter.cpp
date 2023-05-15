#include "Skills/BezierShooter.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components//BezierComponent.h"
#include "Enemy/CEnemy.h"
#include "Utillities/TaskHelper.h"
#include "Utillities/CLog.h"
#include "Net/UnrealNetwork.h"

ABezierShooter::ABezierShooter()
{
	Bezier = CreateDefaultSubobject<UBezierComponent>("Bezier");
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");

	SetRootComponent(Root);
	Sphere->SetupAttachment(Root);
	Sphere->SetHiddenInGame(false);
}

void ABezierShooter::SetParticle(UFXSystemAsset* particle)
{
	Particle = particle;
}

void ABezierShooter::SetDamageData(const FDamageData& _DamageData)
{
	DamageData_ = _DamageData;
}

void ABezierShooter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABezierShooter, Particle);
}

void ABezierShooter::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ABezierShooter::OnComponentBeginOverlap);
	Bezier->OnArrivePosition.AddUObject(this, &ABezierShooter::ArrivePostion);
}

void ABezierShooter::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACCharacter* OwnerCharacter = Cast<ACCharacter>(GetOwner());

	if (OwnerCharacter == OtherActor)
	{
		return;
	}
	if (OwnerCharacter->GetClass() == OtherActor->GetClass())
	{
		return;
	}

	if(this->GetClass() == OtherActor->GetClass())
	{
		return;
	}

	auto childrens = Root->GetAttachChildren();
	for(auto const & children : childrens)
	{
		if(Cast<UFXSystemComponent>(children))
		{
			Cast<UFXSystemComponent>(children)->SetHiddenInGame(true);
		}
	}

	PlayParticle();
}

void ABezierShooter::PlayParticle()
{
	if (Cast<UParticleSystem>(Particle) != nullptr)
	{
		UParticleSystemComponent* effect = TaskHelper::PlayParticleSystem(this->GetWorld(), Particle, GetActorLocation());
		effect->OnSystemFinished.AddDynamic(this, &ABezierShooter::OnParticleFinish);
	}
	else if (Cast<UNiagaraSystem>(Particle) != nullptr)
	{
		UNiagaraComponent* effect = TaskHelper::PlayNiagaraSystem(this->GetWorld(), Particle, GetActorLocation());
		effect->OnSystemFinished.AddDynamic(this, &ABezierShooter::OnNiagaraFinish);
	}
}

void ABezierShooter::ArrivePostion()
{
	PlayParticle();
}

void ABezierShooter::BezierShoot(FVector DirLocation, FVector PlayerLocation)
{
	Bezier->ShootBezierCurve(DirLocation,PlayerLocation);
}

void ABezierShooter::OnNiagaraFinish(UNiagaraComponent* niagara)
{
	Destroy();
}

void ABezierShooter::OnParticleFinish(UParticleSystemComponent* PSystem)
{
	Destroy();
}

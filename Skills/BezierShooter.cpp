#include "Skills/BezierShooter.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components//BezierComponent.h"
#include "Enemy/CEnemy.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
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

void ABezierShooter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABezierShooter, Particle);
}

void ABezierShooter::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ABezierShooter::OnComponentBeginOverlap);
}

void ABezierShooter::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACCharacter* OwnerCharacter = Cast<ACCharacter>(GetOwner());

	if (OwnerCharacter == OtherActor) return;
	if (OwnerCharacter->GetClass() == OtherActor->GetClass()) return;

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

void ABezierShooter::PlayParticle_Implementation()
{
	if (Cast<UParticleSystem>(Particle) != nullptr)
	{
		UParticleSystemComponent* effect = UGameplayStatics::SpawnEmitterAtLocation
		(
			GetWorld(),
			Cast<UParticleSystem>(Particle),
			GetActorLocation()
		);
		effect->OnSystemFinished.AddDynamic(this, &ABezierShooter::OnParticleFinish);
	}
	else if (Cast<UNiagaraSystem>(Particle) != nullptr)
	{
		UNiagaraComponent* effect = UNiagaraFunctionLibrary::SpawnSystemAtLocation
		(
			GetWorld(),
			Cast<UNiagaraSystem>(Particle),
			GetActorLocation()
		);
		effect->OnSystemFinished.AddDynamic(this, &ABezierShooter::OnNiagaraFinish);
	}
}

void ABezierShooter::BezierShoot(FVector Enemy, FVector PlayerLocation)
{
	Bezier->ShootBezierCurve(Enemy,PlayerLocation);
}

void ABezierShooter::OnNiagaraFinish(UNiagaraComponent* niagara)
{
	Destroy();
}

void ABezierShooter::OnParticleFinish(UParticleSystemComponent* PSystem)
{
	Destroy();
}

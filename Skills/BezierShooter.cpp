#include "Skills/BezierShooter.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components//BezierComponent.h"
#include "Enemy/CEnemy.h"
#include "Particles/ParticleSystem.h"
#include "NiagaraSystem.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "Utillities/CLog.h"
#include "NiagaraComponent.h"
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
	SetLifeSpan(5);

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ABezierShooter::OnComponentBeginOverlap);

	CLog::Print(GetOwner()->GetName());
}

void ABezierShooter::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACEnemy* enemy = Cast<ACEnemy>(OtherActor);
	if(enemy == nullptr)
		return;

	ServerPlayParticle();
}

void ABezierShooter::PlayParticle_Implementation()
{
	if (Cast<UParticleSystem>(Particle) != nullptr)
	{
		auto effect = UGameplayStatics::SpawnEmitterAtLocation
		(
			GetWorld(),
			Cast<UParticleSystem>(Particle),
			GetActorLocation()
		);
		effect->SetActive(true);
		effect->SetIsReplicated(true);
	}
	else if (Cast<UNiagaraSystem>(Particle) != nullptr)
	{
		auto effect = UNiagaraFunctionLibrary::SpawnSystemAtLocation
		(
			GetWorld(),
			Cast<UNiagaraSystem>(Particle),
			GetActorLocation()
		);

		effect->Activate(true);
		effect->SetIsReplicated(true);
	}
}

void ABezierShooter::ServerPlayParticle_Implementation()
{
	PlayParticle();
}

void ABezierShooter::BezierShoot(FVector Enemy, FVector PlayerLocation)
{
	Bezier->ShootBezierCurve(Enemy,PlayerLocation);
}

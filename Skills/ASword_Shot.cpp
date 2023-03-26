#include "ASword_Shot.h"
#include "Utillities/CLog.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"


AASword_Shot::AASword_Shot()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(Root);

	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile");
}

void AASword_Shot::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(2.0f);
	//CLog::Log("Shot Spawn");
	//CLog::Log(GetActorLocation());
}

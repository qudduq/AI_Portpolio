#include "Skills/BezierShooter.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components//BezierComponent.h"

ABezierShooter::ABezierShooter()
{
	Bezier = CreateDefaultSubobject<UBezierComponent>("Bezier");
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");

	SetRootComponent(Root);
	Sphere->SetupAttachment(Root);
	Sphere->SetHiddenInGame(false);
}

void ABezierShooter::BeginPlay()
{
	Super::BeginPlay();

	
}

void ABezierShooter::BezierShoot(FVector Enemy, FVector PlayerLocation)
{
	Bezier->ShootBezierCurve(Enemy,PlayerLocation);
}

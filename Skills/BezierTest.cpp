#include "Skills/BezierTest.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components//BezierComponent.h"

ABezierTest::ABezierTest()
{
	Bezier = CreateDefaultSubobject<UBezierComponent>("Bezier");
	
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	OBj = CreateDefaultSubobject<UBoxComponent>("OBj");

	OBj->SetupAttachment(Root);
	OBj->SetHiddenInGame(false);
}

void ABezierTest::BeginPlay()
{
	Super::BeginPlay();

	
}

void ABezierTest::BezierShoot(FVector Enemy, FVector PlayerLocation)
{
	Bezier->ShootBezierCurve(Enemy,PlayerLocation);
}

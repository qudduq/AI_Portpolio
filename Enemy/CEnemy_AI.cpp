#include "CEnemy_AI.h"
#include "Components/CBehaviorComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Utillities/CLog.h"

ACEnemy_AI::ACEnemy_AI()
{
	Behavior = CreateDefaultSubobject<UCBehaviorComponent>("Behavior");
}

void ACEnemy_AI::BeginPlay()
{
	Super::BeginPlay();

	Behavior->SetWaitMode();
}

void ACEnemy_AI::Hitted_Implementation()
{
	Super::Hitted();

	Behavior->SetHitMode();
}

void ACEnemy_AI::End_Hitted_Implementation()
{
	Super::End_Hitted();

	Behavior->SetWaitMode();
}


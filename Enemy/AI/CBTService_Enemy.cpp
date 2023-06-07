#include "CBTService_Enemy.h"
#include "Utillities/CLog.h"
#include "Player/CPlayer.h"
#include "Enemy/CEnemy_AI.h"
#include "Enemy/CAIController.h"
#include "Components/CStateComponent.h"
#include "Components/CBehaviorComponent.h"
#include "BehaviorTree/BehaviorTree.h"

UCBTService_Enemy::UCBTService_Enemy()
{
	NodeName = "Enemy_Service";

	Interval = 0.1f;
	RandomDeviation = 0.0f;
}

void UCBTService_Enemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	if (IsValid(controller) == false) return;

	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());
	if (IsValid(ai) == false) return;

	UCStateComponent* state = Cast<UCStateComponent>(ai->GetComponentByClass(UCStateComponent::StaticClass()));
	if (IsValid(state) == false) return;

	UCBehaviorComponent* behavior = Cast<UCBehaviorComponent>(ai->GetComponentByClass(UCBehaviorComponent::StaticClass()));
	if (IsValid(behavior) == false) return;

	ACPlayer* player = behavior->GetTargetPlayer();
	if (IsValid(player) == false)
	{
		CLog::Log("Not Search Player");
		return;
	}

	if(state->IsHittedMode())
		return;

	if(behavior->IsHittedMode())
		return;

	int access = FMath::RandRange(0, 1);
	float distance = ai->GetDistanceTo(player);
	if (distance < controller->GetCloseActionRange())
	{
		CLog::Log("Close Action");
		behavior->SetcloseActionMode();
	}
	else if (distance < controller->GetMiddleActionRange())
	{
		if(access)
		{
			behavior->SetAccessMode();
		}
		else
		{
			behavior->SetmiddleActionMode();
		}
	}
	else if (distance < controller->GetFarActionRange())
	{
		if(access)
		{
			behavior->SetAccessMode();
		}
		else
		{
			//TODO : 장거리 스킬 구현후 교체
			
		}
	}
}




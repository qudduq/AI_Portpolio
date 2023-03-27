#include "CBTTaskNode_Access.h"

#include "Enemy/CAIController.h"
#include "Enemy/CEnemy_AI.h"
#include "Components/CBehaviorComponent.h"
#include "Utillities/CLog.h"

UCBTTaskNode_Access::UCBTTaskNode_Access()
{
	NodeName = "Access";
	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Access::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	Time = 0;

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Access::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	Time += DeltaSeconds;
	if(Time >= AccessTime)
	{
		ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
		if(controller==nullptr)
		{
			return;
		}

		ACEnemy_AI* owner = Cast<ACEnemy_AI>(controller->GetPawn());
		if(owner == nullptr)
		{
			return;
		}

		UCBehaviorComponent* behaviorComponent = Cast<UCBehaviorComponent>(owner->GetComponentByClass(UCBehaviorComponent::StaticClass()));
		if(behaviorComponent == nullptr)
		{
			return;
		}

		behaviorComponent->SetWaitMode();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

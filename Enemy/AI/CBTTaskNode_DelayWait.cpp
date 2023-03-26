#include "CBTTaskNode_DelayWait.h"

#include "Enemy/CAIController.h"
#include "Enemy/CEnemy_AI.h"
#include "Components/CBehaviorComponent.h"
#include "Utillities/CLog.h"

UCBTTaskNode_DelayWait::UCBTTaskNode_DelayWait()
{
	NodeName = "DelayWait";
	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_DelayWait::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* owner = Cast<ACEnemy_AI>(controller->GetPawn());

	UCBehaviorComponent* behaviorComponent = Cast<UCBehaviorComponent>(owner->GetComponentByClass(UCBehaviorComponent::StaticClass()));


	return EBTNodeResult::InProgress;
}

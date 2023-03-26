#include "CBTService_Enemy.h"
#include "Utillities/CLog.h"
#include "Player/CPlayer.h"
#include "Enemy/CEnemy_AI.h"
#include "Enemy/CAIController.h"
#include "Components/CStateComponent.h"
#include "Components/CBehaviorComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

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
	if (controller == nullptr) return;

	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());
	if (ai == nullptr) return;

	UCStateComponent* state = Cast<UCStateComponent>(ai->GetComponentByClass(UCStateComponent::StaticClass()));
	if (state == nullptr) return;

	UCBehaviorComponent* behavior = Cast<UCBehaviorComponent>(ai->GetComponentByClass(UCBehaviorComponent::StaticClass()));
	if (behavior == nullptr) return;


	if(behavior->IsWaitMode() == false)
		return;


	ACPlayer* player = behavior->GetTargetPlayer();
	if(player == nullptr)
		return;

	float distance = ai->GetDistanceTo(player);
	if (distance < controller->GetCloseActionRange())
	{
		behavior->SetcloseActionMode();
	}
	else if (distance < controller->GetMiddleActionRange())
	{

	}
	else if (distance < controller->GetFarActionRange())
	{

	}


}




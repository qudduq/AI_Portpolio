#include "Enemy/AI/CBTTaskNode_LookPlayer.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/CAIController.h"
#include "Enemy/CEnemy_AI.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/CPlayer.h"
#include "Utillities/CLog.h"

UCBTTaskNode_LookPlayer::UCBTTaskNode_LookPlayer()
{
	NodeName = "LookingPlayer";
}

EBTNodeResult::Type UCBTTaskNode_LookPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	if (controller == nullptr)
	{
		return Result;
	}

	ACEnemy_AI* owner = Cast<ACEnemy_AI>(controller->GetPawn());
	if (owner == nullptr)
	{
		return Result;
	}

	ACPlayer* player = Cast<ACPlayer>(controller->GetBlackboardComponent()->GetValueAsObject("Player"));
	if(player == nullptr)
	{
		return Result;
	}

	//CLog::Log("Look Player");
	FRotator rotation = UKismetMathLibrary::FindLookAtRotation(owner->GetActorLocation(), player->GetActorLocation());
	owner->SetActorRotation(rotation);

	return EBTNodeResult::Succeeded;
}

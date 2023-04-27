#include "CBTDecorator_CustomLoop.h"

#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Character/CCharacter.h"
#include "Utillities/TaskHelper.h"
#include "Components/CBehaviorComponent.h"

UCBTDecorator_CustomLoop::UCBTDecorator_CustomLoop()
{
	NodeName = "Access Loop";
}

void UCBTDecorator_CustomLoop::OnNodeActivation(FBehaviorTreeSearchData& SearchData)
{
	Super::OnNodeActivation(SearchData);
	AAIController* OwnerController = SearchData.OwnerComp.GetAIOwner();
	if(OwnerController == nullptr)
	{
		return;
	}
	ACCharacter* OwnerCharacter = Cast<ACCharacter>(OwnerController->GetPawn());
	if(OwnerCharacter == nullptr)
	{
		return;
	}

	UCBehaviorComponent* Behavior = TaskHelper::GetComponet<UCBehaviorComponent>(OwnerCharacter);
	if(Behavior == nullptr)
	{
		return;
	}

	handle = Behavior->OnActionDelegate.AddUObject
	(
			this,
			&UCBTDecorator_CustomLoop::OffInfinityLoop
	);
}

void UCBTDecorator_CustomLoop::OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult)
{
	Super::OnNodeDeactivation(SearchData, NodeResult);
	AAIController* OwnerController = SearchData.OwnerComp.GetAIOwner();
	if (OwnerController == nullptr)
	{
		return;
	}
	ACCharacter* OwnerCharacter = Cast<ACCharacter>(OwnerController->GetPawn());
	if (OwnerCharacter == nullptr)
	{
		return;
	}

	UCBehaviorComponent* Behavior = TaskHelper::GetComponet<UCBehaviorComponent>(OwnerCharacter);
	if (Behavior == nullptr)
	{
		return;
	}

	Behavior->OnActionDelegate.Remove(handle);
}

void UCBTDecorator_CustomLoop::OffInfinityLoop()
{
	bInfiniteLoop = false;
}

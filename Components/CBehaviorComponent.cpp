#include "CBehaviorComponent.h"
#include "Player/CPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Net/UnrealNetwork.h"

void UCBehaviorComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCBehaviorComponent, type);
}

UCBehaviorComponent::UCBehaviorComponent()
{

}

void UCBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();

	SetWaitMode();
}

void UCBehaviorComponent::OffLoopDecorator()
{
	if(OnActionDelegate.IsBound())
	{
		OnActionDelegate.Broadcast();
	}
}

void UCBehaviorComponent::SetActionMode()
{
	ChangeType(EBehaviorType::Action);
	OffLoopDecorator();
}

void UCBehaviorComponent::SetcloseActionMode()
{
	ChangeType(EBehaviorType::closeAction);
	OffLoopDecorator();
}

void UCBehaviorComponent::SetmiddleActionMode()
{
	ChangeType(EBehaviorType::middleAction);
	OffLoopDecorator();
}

void UCBehaviorComponent::SetfarActionMode()
{
	ChangeType(EBehaviorType::farAction);
	OffLoopDecorator();
}

void UCBehaviorComponent::SetWaitMode()
{
	ChangeType(EBehaviorType::Wait);
}

void UCBehaviorComponent::SetPatrolMode()
{
	ChangeType(EBehaviorType::Patrol);
}

void UCBehaviorComponent::SetAccessMode()
{
	ChangeType(EBehaviorType::Access);
}

void UCBehaviorComponent::SetDefendMode()
{
	ChangeType(EBehaviorType::Defend);
}

void UCBehaviorComponent::SetHitMode()
{
	ChangeType(EBehaviorType::Hit);
}

void UCBehaviorComponent::SetAvoidMode()
{
	ChangeType(EBehaviorType::Avoid);
}

ACPlayer* UCBehaviorComponent::GetTargetPlayer()
{
	return Cast<ACPlayer>(Blackboard->GetValueAsObject(PlayerKey));
}

void UCBehaviorComponent::ChangeType_Implementation(EBehaviorType InType)
{
	type = InType;
	Blackboard->SetValueAsEnum(BehaviorKey, (uint8)InType);
}
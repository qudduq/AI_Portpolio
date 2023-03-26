#include "CBehaviorComponent.h"
#include "Player/CPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"

UCBehaviorComponent::UCBehaviorComponent()
{

}

void UCBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();

	SetWaitMode();
}

void UCBehaviorComponent::SetActionMode()
{
	ChangeType(EBehaviorType::Action);
}

void UCBehaviorComponent::SetcloseActionMode()
{
	ChangeType(EBehaviorType::closeAction);
}

void UCBehaviorComponent::SetmiddleActionMode()
{
	ChangeType(EBehaviorType::middleAction);
}

void UCBehaviorComponent::SetfarActionMode()
{
	ChangeType(EBehaviorType::farAction);
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

void UCBehaviorComponent::ChangeType(EBehaviorType InType)
{
	type = InType;
	Blackboard->SetValueAsEnum(BehaviorKey, (uint8)InType);

	if (OnBehaviorTypeChanged.IsBound())
		OnBehaviorTypeChanged.Broadcast(type, InType);
}
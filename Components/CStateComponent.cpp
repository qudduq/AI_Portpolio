#include "Components/CStateComponent.h"

#include "Utillities/CLog.h"

UCStateComponent::UCStateComponent()
{
}


void UCStateComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCStateComponent::SetIdleMode()
{
	ChangeType(EStateType::Idle);
}

void UCStateComponent::SetActionMode()
{
	ChangeType(EStateType::Action);
}

void UCStateComponent::SetHittedMode()
{
	ChangeType(EStateType::Hitted);
}

void UCStateComponent::SetDeadMode()
{
	ChangeType(EStateType::Dead);
}

void UCStateComponent::ChangeType(EStateType InType)
{
	Type = InType;

	if (OnStateTypeChanged.IsBound())
		OnStateTypeChanged.Broadcast(Type);
}

void UCStateComponent::RegisterDelegate(const FStateTypeChanged::FDelegate& ObserverDelegate)
{
	OnStateTypeChanged.Add(ObserverDelegate);
}

void UCStateComponent::UnregisterDelegate(const FDelegateHandle& handle)
{
	OnStateTypeChanged.Remove(handle);
}

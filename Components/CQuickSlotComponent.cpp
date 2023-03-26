#include "Components/CQuickSlotComponent.h"
#include "GameFramework/Character.h"
#include "Widget/QuickSlotInterface.h"

UCQuickSlotComponent::UCQuickSlotComponent()
{
	
}


void UCQuickSlotComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void UCQuickSlotComponent::SetQuickSlot(FKey slotIndex, class IQuickSlotInterface* slot)
{
	if (QuickSlotData.Find(slotIndex) == nullptr)
		QuickSlotData.Add(slotIndex, slot);
	else
		QuickSlotData[slotIndex] = slot;
}

void UCQuickSlotComponent::QuickSlotCall(FKey slotIndex)
{
	if (QuickSlotData.Find(slotIndex) == nullptr)
		return;

	QuickSlotData[slotIndex]->QuickSlotCall(OwnerCharacter);
}
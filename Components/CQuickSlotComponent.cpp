#include "Components/CQuickSlotComponent.h"
#include "GameFramework/Character.h"
#include "Widget/QuickSlotInterface.h"
#include "Net/UnrealNetwork.h"
#include "Utillities/CLog.h"
#include "Components/CSkillComponent.h"

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

	if(OwnerCharacter->HasAuthority())
	{
		CLog::Print("Controller Set QuickSLot");
	}
	else
	{
		CLog::Print("Copy Character Set QuickSlot");
	}
}

void UCQuickSlotComponent::QuickSlotCall(FKey slotIndex)
{
	if (QuickSlotData.Find(slotIndex) == nullptr)
		return;

	UCSkillComponent* skillComponent = Cast<UCSkillComponent>(OwnerCharacter->GetComponentByClass(UCSkillComponent::StaticClass()));
	if(skillComponent == nullptr)
		return;

	skillComponent->ExcuteSkill(QuickSlotData[slotIndex]->GetID());
}

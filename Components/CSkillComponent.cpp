#include "Components/CSkillComponent.h"
#include "GameFramework/Character.h"
#include "Skills/CSkillData.h"
#include "Skills/CSkill.h"
#include "Animation/AnimMontage.h"
#include "CStateComponent.h"
#include "Character/CCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Skills/UCSkillStructure.h"
#include "Utillities/CLog.h"
#include "Components/CWeaponComponent.h"



UCSkillComponent::UCSkillComponent()
{
	
}

void UCSkillComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCSkillComponent, SkillDataAssets);
}

void UCSkillComponent::BeginPlay()
{
	Super::BeginPlay();

	ACCharacter* OwnerCharacter = Cast<ACCharacter>(GetOwner());

	for (int32 i = 0; i < (int32)EWeaponType::Max; i++)
	{
		if (SkillDataAssets[i] == nullptr)
		{
			FString outStr = OwnerCharacter->GetName();
			outStr += " ";
			outStr += UEnum::GetValueAsString((EWeaponType)i);
			outStr += " Not Setting SkillDatas";
			CLog::Log(outStr);
		}
		else
			SkillDataAssets[i]->BeginPlay();
	}

	CLog::Log("");
}

UCSkill* UCSkillComponent::GetSkillData(EWeaponType WeaponType, FName ID)
{
	for(const auto & skill : GetSkillArrayData(WeaponType))
	{
		if(skill->GetID() == ID)
		{
			return skill;
		}
	}

	return nullptr;
}

const TArray<UCSkill*>& UCSkillComponent::GetSkillArrayData(EWeaponType WeaponType) const
{
	return SkillDataAssets[static_cast<int32>(WeaponType)]->GetSkillArrayDatas();
}

void UCSkillComponent::BeginSkill()
{
	if(OnBeginSkill.IsBound())
	{
		OnBeginSkill.Broadcast();
	}
}

void UCSkillComponent::EndSkill()
{
	if(OnEndSkill.IsBound())
	{
		OnEndSkill.Broadcast();
	}
}

bool UCSkillComponent::ExcuteSkill_Validate(FName SkillID)
{
	return true;
}

void UCSkillComponent::ExcuteSkill_Implementation(FName SkillID)
{
	ACCharacter* OwnerCharacter = Cast<ACCharacter>(GetOwner());
	if (OwnerCharacter == nullptr)
	{
		return;
	}

	UCWeaponComponent* weaponComponent = Cast<UCWeaponComponent>(OwnerCharacter->GetComponentByClass(UCWeaponComponent::StaticClass()));
	if (weaponComponent == nullptr)
	{
		return;
	}

	UCSkill* skill = GetSkillData(weaponComponent->GetWeaponType(), SkillID);
	if (skill == nullptr)
	{
		return;
	}

	skill->ExcuteSkill(OwnerCharacter);
}







#include "Components/CSkillComponent.h"
#include "GameFramework/Character.h"
#include "Skills/CSkillData.h"
#include "Skills/CSkill.h"
#include "CStateComponent.h"
#include "Character/CCharacter.h"
#include "Skills/UCSkillStructure.h"
#include "Utillities/CLog.h"
#include "Utillities/TaskHelper.h"
#include "Components/CWeaponComponent.h"



UCSkillComponent::UCSkillComponent()
{
	
}

void UCSkillComponent::BeginPlay()
{
	Super::BeginPlay();

	ACCharacter* OwnerCharacter = Cast<ACCharacter>(GetOwner());

	// 데이터에셋에 등록된 UCSkill들을 객체화 시켜줍니다.
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
}

UCSkill* UCSkillComponent::GetSkillData(EWeaponType WeaponType, FName ID)
{
	// 해당 아이디에 맞는 스킬을 찾습니다.
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

void UCSkillComponent::ActiveSkill()
{
	if(OnActiveSkill.IsBound())
	{
		OnActiveSkill.Broadcast();
	}
}

void UCSkillComponent::EndSkill()
{
	if(OnEndSkill.IsBound())
	{
		OnEndSkill.Broadcast(false);
	}
}

bool UCSkillComponent::ExcuteSkill_Validate(FName SkillID)
{
	//검증 부분입니다. 현재는 정확히 어떤검증을 해야할지 정하지못해 true만 적어놓았습니다.
	return true;
}

void UCSkillComponent::ExcuteSkill_Implementation(FName SkillID)
{
	ACCharacter* OwnerCharacter = Cast<ACCharacter>(GetOwner());
	if (OwnerCharacter == nullptr)
	{
		return;
	}

	UCWeaponComponent* weaponComponent = TaskHelper::GetComponet<UCWeaponComponent>(OwnerCharacter);
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







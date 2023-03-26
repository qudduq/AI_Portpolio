#include "Components/CSkillComponent.h"
#include "GameFramework/Character.h"
#include "Skills/CSkillData.h"
#include "Skills/CSkill.h"
#include "Animation/AnimMontage.h"
#include "CStateComponent.h"
#include "Skills/UCSkillStructure.h"
#include "Utillities/CLog.h"



UCSkillComponent::UCSkillComponent()
{
	
}


void UCSkillComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	Weapon = Cast<UCWeaponComponent>(OwnerCharacter->GetComponentByClass(UCWeaponComponent::StaticClass()));

	Weapon->OnWeaponTypeChanged.Add(FWeaponTypeChanged::FDelegate::CreateUObject(this,&UCSkillComponent::OnWeaponTypeChanged));

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

const TArray<UCSkill*>& UCSkillComponent::GetSkillData()
{
	return Data->GetSkillDatas();
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

void UCSkillComponent::OnWeaponTypeChanged(EWeaponType InNewType)
{
	WeaponType = InNewType;
	Data = (SkillDataAssets[(int32)WeaponType]);
}







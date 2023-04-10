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

const  TMap<FName, UCSkill*>& UCSkillComponent::GetSkillMapData(EWeaponType WeaponType)
{
	return SkillDataAssets[static_cast<int32>(WeaponType)]->GetSkillMapDatas();
}

const TArray<UCSkill*>& UCSkillComponent::GetSkillArrayData(EWeaponType WeaponType)
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

void UCSkillComponent::ExcuteSkill(FName SkillID)
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


	UCSkill* const* skill = GetSkillMapData(weaponComponent->GetWeaponType()).Find(SkillID);
	if (skill == nullptr)
	{
		return;
	}

	(*skill)->ExcuteSkill(OwnerCharacter);
}







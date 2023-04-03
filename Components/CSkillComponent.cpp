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

const TArray<UCSkill*>& UCSkillComponent::GetSkillData(EWeaponType WeaponType)
{
	return SkillDataAssets[static_cast<int32>(WeaponType)]->GetSkillDatas();
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







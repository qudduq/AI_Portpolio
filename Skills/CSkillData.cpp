#include "CSkillData.h"
#include "Utillities/CLog.h"
#include "GameFramework/Character.h"

UCSkillData::UCSkillData()
{

}

void UCSkillData::BeginPlay()
{
	Skills.Reset();
	for (const auto& skill : SkillDatas)
	{
		Skills.Add(NewObject<UCSkill>(this, skill));
	}
}

const TArray<UCSkill*>& UCSkillData::GetSkillDatas()
{
	return Skills;
}



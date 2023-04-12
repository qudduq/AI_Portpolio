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
		UCSkill* createSkill = NewObject<UCSkill>(this,skill);
		Skills.Add(createSkill);
	}

	CLog::Log("Create SkillDataAsset");
}

const TArray<UCSkill*>& UCSkillData::GetSkillArrayDatas()
{
	return Skills;
}



#include "CSkillData.h"
#include "Utillities/CLog.h"
#include "GameFramework/Character.h"

UCSkillData::UCSkillData()
{

}

void UCSkillData::BeginPlay()
{
	SkillsArray.Reset();
	SkillsMap.Reset();

	for (const auto& skill : SkillDatas)
	{
		UCSkill* createSkill = NewObject<UCSkill>(this,skill);
		if(SkillsMap.Find(createSkill->GetID()) == nullptr)
		{
			SkillsMap.Add(createSkill->GetID(), createSkill);
			SkillsArray.Add(createSkill);
		}
	}

	CLog::Log("Create SkillDataAsset");
}

const TArray<UCSkill*>& UCSkillData::GetSkillArrayDatas()
{
	return SkillsArray;
}

const TMap<FName, UCSkill*>& UCSkillData::GetSkillMapDatas()
{
	return SkillsMap;
}



#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Skills/CSkill.h"
#include "CSkillData.generated.h"

//TODO : SkillComponent에서 불러지는 비긴플레이로 세팅이 아닌 게임이 시작할떄 콜하는것으로 변경할것

UCLASS()
class AI_PORTPOLIO_API UCSkillData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
		TArray<TSubclassOf<UCSkill>> SkillDatas;

public:
	UCSkillData();

	void BeginPlay();

	const TArray<UCSkill*>& GetSkillDatas();

private:
	TArray<UCSkill*> Skills;
	bool bCreate = false;
};

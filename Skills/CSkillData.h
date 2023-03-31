#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Skills/CSkill.h"
#include "CSkillData.generated.h"

//TODO : SkillComponent���� �ҷ����� ����÷��̷� ������ �ƴ� ������ �����ҋ� ���ϴ°����� �����Ұ�

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

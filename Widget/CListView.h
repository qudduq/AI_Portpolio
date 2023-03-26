#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Skills/CSkill.h"
#include "CListView.generated.h"

/*
		AddItem�� listview�� UObject��ӹ��� list�� �־��ش�
		listView�� �迭�� list���� �� �ִ�
		setListView �� ����ϸ� �迭�� �ʱ�ȭ�� ����

		SKillData���� ��ų�� UObject���Ŭ������� �ٲ��ֱ�

		listview doublclick
		���Լ��� ����Ͽ� listview ������ ����Ŭ�� ����
		virtual void OnItemDoubleClickedInternal(UObject* Item) override;
*/

UCLASS()
class AI_PORTPOLIO_API UCListView : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
		class UListView* SkillList;

public:
	void SetSKills(const TArray<UCSkill*>& SkillDatas);
	void COpenSkills();
	void CCloseSkills();


};

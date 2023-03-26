#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Skills/CSkill.h"
#include "CListView.generated.h"

/*
		AddItem은 listview에 UObject상속받은 list를 넣어준다
		listView는 배열로 list들이 들어가 있다
		setListView 를 사용하면 배열로 초기화가 가능

		SKillData내의 스킬들 UObject상속클래스들로 바꿔주기

		listview doublclick
		이함수를 사용하여 listview 내에서 더블클릭 구현
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

#include "CListView.h"
#include "Components/CSkillComponent.h"
#include "GameFramework/Character.h"
#include "Skills/CSkillData.h"
#include "Utillities/CLog.h"
#include "Components/ListView.h"
#include "CDragWidget.h"
#include "CWidgetDrag.h"

void UCListView::SetSKills(const TArray<UCSkill*>& SkillDatas)
{
	SkillList->SetListItems(SkillDatas);
}

void UCListView::COpenSkills()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UCListView::CCloseSkills()
{
	SetVisibility(ESlateVisibility::Hidden);
}






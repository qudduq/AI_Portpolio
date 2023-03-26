#include "CDragWidget.h"
#include "Utillities/CLog.h"
#include "CListSkill.h"


void UCDragWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UCListSkill* listSkill = Cast<UCListSkill>(WidgetRefernce);
	if (listSkill == NULL) return;
	FVector2D size = listSkill->GetImageSize();

	WidgetSize->SetBrushFromTexture(listSkill->GetImage());
	WidgetSize->SetBrushSize(listSkill->GetImage()->GetImportedSize()/4);
}



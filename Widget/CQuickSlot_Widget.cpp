#include "CQuickSlot_Widget.h"
#include "Utillities/CLog.h"
#include "CWidgetDrag.h"
#include "Skills/CSkill.h"
#include "Components/Image.h"
#include "Components/CQuickSlotComponent.h"
#include "Components/CSkillComponent.h"
#include "GameFramework/Character.h"
#include "Widget/QuickSlotInterface.h"

bool UCQuickSlot_Widget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	//드레드되어온 데이터를 확인해줍니다.
	UCWidgetDrag* dragwidget = Cast<UCWidgetDrag>(InOperation);
	if (dragwidget == nullptr) return false;

	//해당데이터가 퀵슬롯 인터페이스를 상속받고있는지 확인합니다.
	IQuickSlotInterface* slotdata = Cast<IQuickSlotInterface>(dragwidget->Payload);
	if (slotdata == nullptr) return false;

	ACharacter* ownercharacter = GetOwningPlayerPawn<ACharacter>();
	if (ownercharacter == nullptr) return false;

	//해당 퀵슬롯에 등록해 줍니다.
	UCQuickSlotComponent* QuickSlotComponent = Cast<UCQuickSlotComponent>(ownercharacter->GetComponentByClass(UCQuickSlotComponent::StaticClass()));
	if (QuickSlotComponent == nullptr) return false;

	QuickSlotComponent->SetQuickSlot(SlotName, slotdata);

	//마지막으로 보여질 텍스쳐까지 세팅해줍니다.
	SetSkill->SetBrushFromTexture(slotdata->GetSlotTexture());

	return false;
}


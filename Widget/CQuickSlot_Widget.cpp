#include "CQuickSlot_Widget.h"
#include "Utillities/CLog.h"
#include "CWidgetDrag.h"
#include "Components/Image.h"
#include "Components/CQuickSlotComponent.h"
#include "GameFramework/Character.h"
#include "Widget/QuickSlotInterface.h"

bool UCQuickSlot_Widget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	//드레드되어온 데이터를 확인해줍니다.
	UCWidgetDrag* dragwidget = Cast<UCWidgetDrag>(InOperation);
	if (dragwidget == nullptr)
	{
		CLog::Log("Not Have Drag Data");
		return false;
	}

	//해당데이터가 퀵슬롯 인터페이스를 상속받고있는지 확인합니다.
	IQuickSlotInterface* slotdata = Cast<IQuickSlotInterface>(dragwidget->Payload);
	if (slotdata == nullptr)
	{
		CLog::Log("Does Not Inherit QuickSlotInterface Object");
		return false;
	}

	//플레이어를 얻어옵니다.
	ACharacter* ownercharacter = GetOwningPlayerPawn<ACharacter>();
	if (ownercharacter == nullptr)
	{
		CLog::Log("Have Not Player");
		return false;
	}

	
	UCQuickSlotComponent* QuickSlotComponent = Cast<UCQuickSlotComponent>(ownercharacter->GetComponentByClass(UCQuickSlotComponent::StaticClass()));
	if (QuickSlotComponent == nullptr)
	{
		CLog::Log("Have Not QuickSlotComponent");
		return false;
	}
	//해당 퀵슬롯에 등록해 줍니다.
	//해당 퀵슬롯 데이터는 IQuickSlotInterface* 의형태로 캐스팅되어 저장됩니다.
	QuickSlotComponent->SetQuickSlot(SlotName, slotdata);

	//마지막으로 보여질 텍스쳐까지 세팅해줍니다.
	UTexture2D* Texture = slotdata->GetSlotTexture();
	if(Texture == nullptr)
	{
		CLog::Log("Skill Have Not Texture");
		return false;
	}

	SetSkill->SetBrushFromTexture(Texture);

	return false;
}


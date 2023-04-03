#include "CQuickSlot_Widget.h"
#include "Utillities/CLog.h"
#include "CWidgetDrag.h"
#include "Components/Image.h"
#include "Components/CQuickSlotComponent.h"
#include "GameFramework/Character.h"
#include "Widget/QuickSlotInterface.h"

bool UCQuickSlot_Widget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	//�巹��Ǿ�� �����͸� Ȯ�����ݴϴ�.
	UCWidgetDrag* dragwidget = Cast<UCWidgetDrag>(InOperation);
	if (dragwidget == nullptr) return false;

	//�ش絥���Ͱ� ������ �������̽��� ��ӹް��ִ��� Ȯ���մϴ�.
	IQuickSlotInterface* slotdata = Cast<IQuickSlotInterface>(dragwidget->Payload);
	if (slotdata == nullptr) return false;

	ACharacter* ownercharacter = GetOwningPlayerPawn<ACharacter>();
	if (ownercharacter == nullptr) return false;

	//�ش� �����Կ� ����� �ݴϴ�.
	UCQuickSlotComponent* QuickSlotComponent = Cast<UCQuickSlotComponent>(ownercharacter->GetComponentByClass(UCQuickSlotComponent::StaticClass()));
	if (QuickSlotComponent == nullptr) return false;

	QuickSlotComponent->SetQuickSlot(SlotName, slotdata);

	//���������� ������ �ؽ��ı��� �������ݴϴ�.
	UTexture2D* Texture = slotdata->GetSlotTexture();
	if(Texture == nullptr)
	{
		CLog::Log("Skill Have Not Texture");
		return false;
	}

	SetSkill->SetBrushFromTexture(Texture);

	return false;
}


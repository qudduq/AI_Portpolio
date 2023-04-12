#include "CListSkill.h"
#include "Utillities/CLog.h"
#include "Skills/CSkill.h"
#include "Layout/Geometry.h"
#include "Input/Events.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "CDragWidget.h"
#include "CWidgetDrag.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CSkillComponent.h"
#include "GameFramework/Character.h"


void UCListSkill::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	skill = Cast<UCSkill>(ListItemObject);
	if (skill == nullptr)
		return;

	texture = skill->GetSlotTexture();
	SkillImage->SetBrushFromTexture(texture);
}

FReply UCListSkill::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply returnParent = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	/*���� Ŭ�� Ȯ��
	 *Ÿ�̸� �ڵ鷯�� Ȱ���ð��� �����Ͽ� Ȱ��ȭ�Ǿ������� ����Ŭ�� �ƴϸ� �Ϲ�Ŭ������ �Ǵ��մϴ�.
	 */
	if (GetWorld()->GetTimerManager().IsTimerActive(handle))
	{
		if (skill == nullptr) return returnParent;

		ACharacter* owner = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
		if(owner == nullptr) return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

		UCSkillComponent* skillComponent = Cast<UCSkillComponent>(owner->GetComponentByClass(UCSkillComponent::StaticClass()));
		if (skillComponent == nullptr)
			return returnParent;

		skillComponent->ExcuteSkill(skill->GetID());

		GetWorld()->GetTimerManager().ClearTimer(handle);
		return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	}

	GetWorld()->GetTimerManager().SetTimer(handle, 0.5f, false);

	Position = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent,this, EKeys::LeftMouseButton).NativeReply;
	
}

void UCListSkill::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	// ������ ������ ������ݴϴ�.
	UCDragWidget* dragwidget = CreateWidget<UCDragWidget>(GetWorld(), DragWidget);
	if (dragwidget == NULL) return;

	dragwidget->WidgetRefernce = this;

	//�巹�׵� �ش� ������ �����͸� �Ѱ��ݴϴ�.
	//�巡�� �ɶ��� ���¶��� ������ �� �ֽ��ϴ�.
	UCWidgetDrag* dragdrop = Cast<UCWidgetDrag>(UWidgetBlueprintLibrary::CreateDragDropOperation(UCWidgetDrag::StaticClass()));
	dragdrop->DefaultDragVisual = dragwidget;
	dragdrop->WidgetReference = this;
	dragdrop->DragOffset = texture->GetImportedSize()/4;
	dragdrop->Pivot = EDragPivot::CenterCenter;
	dragdrop->Payload = skill; // ���� �ֿ��� �ش� ��ų�����͸� �Ѱ��ݴϴ�.

	OutOperation = dragdrop;
}


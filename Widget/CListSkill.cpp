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
#include "Net/UnrealNetwork.h"


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
	/*더블 클릭 확인
	 *타이머 핸들러의 활성시간을 세팅하여 활성화되어있으면 더블클릭 아니면 일반클릭으로 판단합니다.
	 */
	if (GetWorld()->GetTimerManager().IsTimerActive(handle))
	{
		if (skill == NULL) return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

		ACharacter* owner = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
		if(owner == nullptr) return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

		skill->ExcuteSkill(owner);

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

	// 보여질 위젯을 만들어줍니다.
	UCDragWidget* dragwidget = CreateWidget<UCDragWidget>(GetWorld(), DragWidget);
	if (dragwidget == NULL) return;

	dragwidget->WidgetRefernce = this;

	//드레그된 해당 위젯의 데이터를 넘겨줍니다.
	//드래그 될때의 상태또한 정해줄 수 있습니다.
	UCWidgetDrag* dragdrop = Cast<UCWidgetDrag>(UWidgetBlueprintLibrary::CreateDragDropOperation(UCWidgetDrag::StaticClass()));
	dragdrop->DefaultDragVisual = dragwidget;
	dragdrop->WidgetReference = this;
	dragdrop->DragOffset = texture->GetImportedSize()/4;
	dragdrop->Pivot = EDragPivot::CenterCenter;
	dragdrop->Payload = skill; // 가장 주요한 해당 스킬데이터를 넘겨줍니다.

	OutOperation = dragdrop;
}

void UCListSkill::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCListSkill, skill);
	DOREPLIFETIME(UCListSkill, texture);
}



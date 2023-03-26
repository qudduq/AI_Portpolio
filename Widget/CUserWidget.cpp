#include "CUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Utillities/CLog.h"

void UCUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
	ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("Item2")));
}

void UCUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bPush)
	{
		//CLog::Log(InDeltaTime);
		float x, y;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(x, y);

		FVector2D size = ItemImage->GetCachedGeometry().GetDrawSize();

		//CLog::Log(size);
		
		x -= size.X/2;
		y -= size.Y/2;

		FVector2D pos(x,y);

		SetPositionInViewport(pos);
	}
}

FReply UCUserWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply fr = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	bPush = true;

	//UGameViewportClient* Viewport = GEngine->GameViewport;
	//Viewport->SetCaptureMouseOnClick(EMouseCaptureMode::NoCapture);

	return fr;
}


FReply UCUserWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply fr = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
	bPush = false;

	//UGameViewportClient* Viewport = GEngine->GameViewport;
	//Viewport->SetCaptureMouseOnClick(EMouseCaptureMode::CapturePermanently);


	return fr;
}


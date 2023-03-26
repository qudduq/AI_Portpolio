#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget.generated.h"

UCLASS()
class AI_PORTPOLIO_API UCUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly)
		class UImage* ItemImage;

	 
public:
	UFUNCTION(BlueprintNativeEvent)
		void OnItem();

	virtual void OnItem_Implementation() {};

	UFUNCTION(BlueprintNativeEvent)
		void OffItem();

	virtual void OffItem_Implementation() {};

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;


private:
	bool bPush = false;
};

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "CDragWidget.generated.h"

UCLASS()
class AI_PORTPOLIO_API UCDragWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
		class UImage* WidgetSize;

protected:
	virtual void NativeConstruct() override;

public:
	UUserWidget* WidgetRefernce;
};

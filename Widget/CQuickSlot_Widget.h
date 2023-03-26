#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CQuickSlot_Widget.generated.h"

UCLASS()
class AI_PORTPOLIO_API UCQuickSlot_Widget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
		class UImage* SetSkill;

	UPROPERTY(EditAnywhere)
		FKey SlotName;

private:
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;


};

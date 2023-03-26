#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "CWidgetDrag.generated.h"

UCLASS()
class AI_PORTPOLIO_API UCWidgetDrag : public UDragDropOperation
{
	GENERATED_BODY()
	
public:
	class UUserWidget* WidgetReference;
	FVector2D DragOffset;
};

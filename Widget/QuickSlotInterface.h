#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuickSlotInterface.generated.h"

UINTERFACE(MinimalAPI)
class UQuickSlotInterface : public UInterface
{
	GENERATED_BODY()
};

class AI_PORTPOLIO_API IQuickSlotInterface
{
	GENERATED_BODY()

public:
	UFUNCTION()
		virtual void QuickSlotCall(class ACharacter* InOwner) = 0;

	UFUNCTION()
		virtual UTexture2D* GetSlotTexture() = 0;
};

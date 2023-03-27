#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CQuickSlotComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AI_PORTPOLIO_API UCQuickSlotComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCQuickSlotComponent();

protected:
	virtual void BeginPlay() override;

public:
	void SetQuickSlot(FKey slotIndex, class IQuickSlotInterface* slot);
	void QuickSlotCall(FKey slotIndex);

private:
	UPROPERTY()
		class ACharacter* OwnerCharacter;
	TMap<FKey, class IQuickSlotInterface*> QuickSlotData;
};

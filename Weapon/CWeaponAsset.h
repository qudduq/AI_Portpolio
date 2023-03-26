#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UCWeaponStructure.h"
#include "CWeaponAsset.generated.h"

UCLASS()
class AI_PORTPOLIO_API UCWeaponAsset : public UDataAsset
{
	GENERATED_BODY()	

private:
	UPROPERTY(EditAnywhere)
		TArray<FDoActionData> ActionDatas;

public:
	UCWeaponAsset();

	FORCEINLINE const TArray<FDoActionData> GetActionDatas() { return ActionDatas; }
};

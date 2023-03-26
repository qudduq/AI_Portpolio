#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Weapon/UCWeaponStructure.h"
#include "HitDataAsset.generated.h"

UCLASS()
class AI_PORTPOLIO_API UHitDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UHitDataAsset();

private:
	UPROPERTY(EditAnywhere)
		TMap<EDamageType, FHitData> HitDataMap;

public:
	FHitData GetHitData(EDamageType Type);
	
};

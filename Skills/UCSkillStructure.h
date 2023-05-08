#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Weapon/UCWeaponStructure.h"
#include "UCSkillStructure.generated.h"

UENUM(BlueprintType)
enum class EDistanceSkill : uint8
{
	Close, Middle, Far
};


USTRUCT(BlueprintType)
struct FDoSkillData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
		FDamageData DamageData;

	UPROPERTY(EditAnywhere)
		EDistanceSkill Distance;

	UPROPERTY(EditAnywhere)
		float PlayRatio = 1;

	UPROPERTY(EditAnywhere)
		bool bCanMove = true;

	UPROPERTY(EditAnywhere)
		bool bFixedCamera = false;

	UPROPERTY(EditAnywhere)
		class UFXSystemAsset* Effect;
};

UCLASS()
class AI_PORTPOLIO_API UUCSkillStructure : public UObject
{
	GENERATED_BODY()
	
};

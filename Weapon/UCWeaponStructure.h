#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UCWeaponStructure.generated.h"

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	Normal, Normal_Left, Normal_Right, FlyAway, Stun,
};

USTRUCT(BlueprintType)
struct FDamageData : public FDamageEvent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		EDamageType Type = EDamageType::Normal;

	UPROPERTY(EditAnywhere)
		float Damage = 10.0f;

	UPROPERTY(EditAnywhere)
		float StopTime = 0;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMatineeCameraShake> CameraShake;
};

////////////////////////////////////////////////////////////////
USTRUCT(BlueprintType)
struct FDoActionData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		FDamageData DamageData;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
		float PlayRatio = 1;

	UPROPERTY(EditAnywhere)
		bool bCanMove = false;

	UPROPERTY(EditAnywhere)
		bool bFixedCamera = false;

	UPROPERTY(EditAnywhere)
		class UFXSystemAsset* Effect;

	UPROPERTY(EditAnywhere)
		FVector EffectLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
		FVector EffectScale = FVector::OneVector;

public:
	void DoAction(class ACharacter* InOwner);

	void PlayEffect(class ACharacter* InOwner);
	void PlayEffect(class USkeletalMeshComponent* InMesh, FName InSocketName = NAME_None);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////


USTRUCT(BlueprintType)
struct FHitData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
		class UFXSystemAsset* Effect;

	UPROPERTY(EditAnywhere)
		FVector EffectLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
		FVector EffectScale = FVector::OneVector;

	UPROPERTY(EditAnywhere)
		class USoundCue* SoundCue;

};

UCLASS()
class AI_PORTPOLIO_API UUCWeaponStructure : public UObject
{
	GENERATED_BODY()
	//FObjectInitialize
	
};

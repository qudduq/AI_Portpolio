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
		EDamageType Type;

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

	//UPROPERTY(EditAnywhere)
	//	FVector EffectLocation = FVector::ZeroVector;
	//
	//UPROPERTY(EditAnywhere)
	//	FVector EffectScale = FVector::OneVector;

public:
	void DoAction(class ACharacter* InOwner);
	void End_DoAction(class ACharacter* InOwner);

	void PlayEffect(class ACharacter* InOwner);
	void PlayEffect(class USkeletalMeshComponent* InMesh, FName InSocketName = NAME_None);

};

UCLASS()
class AI_PORTPOLIO_API UUCSkillStructure : public UObject
{
	GENERATED_BODY()
	
};

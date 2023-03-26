#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Engine/DataAsset.h"
#include "CEnemy.h"
#include "EnemyRaceData.generated.h"

USTRUCT(BlueprintType)
struct FEnemyRace
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class USkeletalMesh* RaceMesh;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<UAnimInstance> AnimInstance;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UBehaviorTree* BehaviorTree;
		
};

UCLASS()
class AI_PORTPOLIO_API UEnemyRaceData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
		FEnemyRace RaceData[(int32)ERaceType::Max];
};

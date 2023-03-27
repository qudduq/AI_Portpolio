#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class AI_PORTPOLIO_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ACEnemy> Enemy;

public:	
	AEnemySpawner();

	void EnemySpanwn();

protected:
	virtual void BeginPlay() override;

private:
	FTimerHandle Handle;
	int32 EnemyCount;
};



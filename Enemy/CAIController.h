#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"


struct FEnvQueryResult;
UCLASS()
class AI_PORTPOLIO_API ACAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UAIPerceptionComponent* Perception;

	UPROPERTY(EditDefaultsOnly)
		uint8 TeamID = 2;

	UPROPERTY(EditDefaultsOnly)
		float CloseActionRange = 150;

	UPROPERTY(EditDefaultsOnly)
		float MiddleActionRange = 600;

	UPROPERTY(EditDefaultsOnly)
		float FarActionRange = 1000;

public:
	ACAIController();

	FORCEINLINE void SetTeamID(uint8 teamId) { TeamID = teamId; }
	FORCEINLINE uint8 GetTeamID() { return TeamID; }
	FORCEINLINE float GetCloseActionRange() { return CloseActionRange; }
	FORCEINLINE float GetMiddleActionRange() { return MiddleActionRange; }
	FORCEINLINE float GetFarActionRange() { return FarActionRange; }

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	UFUNCTION()
		void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

private:
	UPROPERTY()
		class ACEnemy_AI* Enemy;

	UPROPERTY()
		class UAISenseConfig_Sight* Sight;

	UPROPERTY()
		class UCBehaviorComponent* Behavior;

};

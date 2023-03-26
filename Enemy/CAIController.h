#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"


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

	FORCEINLINE void SetTeamID(uint8 teamId) { TeamID = teamId; return; }
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
	class ACEnemy_AI* Enemy;
	class UAISenseConfig_Sight* Sight;
	class UCBehaviorComponent* Behavior;

};

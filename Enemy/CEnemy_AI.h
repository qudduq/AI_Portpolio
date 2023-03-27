#pragma once

#include "CoreMinimal.h"
#include "Enemy/CEnemy.h"
#include "CEnemy_AI.generated.h"

UCLASS()
class AI_PORTPOLIO_API ACEnemy_AI : public ACEnemy
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleDefaultsOnly, Category = "AI")
		class UCBehaviorComponent* Behavior;

public:
	ACEnemy_AI();

protected:
	virtual void BeginPlay() override;

protected:
	virtual void Hitted() override;
	virtual void End_Hitted() override;


public:
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }

	FTimerHandle TimerHandle;
	FVector currentSpeed;
};

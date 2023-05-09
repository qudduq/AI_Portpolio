#pragma once

#include "CoreMinimal.h"
#include "Skills/CSkill.h"
#include "CSkill_GroundCircle_Many.generated.h"

class AGroundIce;

UCLASS()
class AI_PORTPOLIO_API UCSkill_GroundCircle_Many : public UCSkill
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<AGroundIce> IceClass;

	UPROPERTY(EditAnywhere)
		float MaxDistance = 1000.0f;

	UPROPERTY(EditAnywhere)
		float MinDistance = 500.0f;

	UPROPERTY(EditAnywhere)
		int32 CircleCount = 20;

public:
	UCSkill_GroundCircle_Many();
	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;
public:
	virtual void BeginSkill() override;
	virtual void ActiveSkill() override;

private:
	TArray<FVector> Locations;
	FTimerHandle TimerHandle;
	int count = 0;

	UPROPERTY(Replicated)
		TArray<AGroundIce*> Ices;
};

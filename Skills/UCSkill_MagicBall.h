#pragma once

#include "CoreMinimal.h"
#include "Skills/CSkill.h"
#include "UCSkill_MagicBall.generated.h"

UCLASS()
class AI_PORTPOLIO_API UUCSkill_MagicBall : public UCSkill
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABezierShooter> ShooterClass;

	UPROPERTY(EditAnywhere)
		FName SocketName;

	UPROPERTY(EditAnywhere)
		float Radius = 10.0f;


public:
	virtual void ExcuteSkill(class ACharacter* InOwner) override;
	virtual void BeginSkill() override;

private:
	FVector GetEnemyLocation(class ACharacter* InOwner) const;

private:
	class ABezierShooter* Shooter;
};

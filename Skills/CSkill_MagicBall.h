#pragma once

#include "CoreMinimal.h"
#include "Skills/CSkill.h"
#include "CSkill_MagicBall.generated.h"

class ABezierShooter;

UCLASS()
class AI_PORTPOLIO_API UCSkill_MagicBall : public UCSkill
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<ABezierShooter> ShooterClass;

	UPROPERTY(EditAnywhere)
		FName SocketName;

	UPROPERTY(EditAnywhere)
		float Radius = 10.0f;

	UPROPERTY(EditAnywhere)
		float Horizontal = 0.0f;

	UPROPERTY(EditAnywhere)
		float Vertical = 0.0f;

public:
	virtual void ExcuteSkill(class ACharacter* InOwner) override;
	virtual void BeginSkill() override;
	
private:
	ABezierShooter* Shooter;
};

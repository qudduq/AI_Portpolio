// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skills/CSkill.h"
#include "CSkill_MagicBall_Many.generated.h"

class ABezierShooter;
UCLASS()
class AI_PORTPOLIO_API UCSkill_MagicBall_Many : public UCSkill
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<ABezierShooter> ShooterClass;

	UPROPERTY(EditAnywhere)
		float Radius = 1500.0f;

	UPROPERTY(EditAnywhere)
		int MaxShooterCount = 20;

	UPROPERTY(EditAnywhere)
		float HorizontalMax = 200.0f;

	UPROPERTY(EditAnywhere)
		float HorizontamMin = 0.0f;

	UPROPERTY(EditAnywhere)
		float VerticalMax = 200.0f;

	UPROPERTY(EditAnywhere)
		float VerticlaMin = 0.0f;

	UPROPERTY(EditAnywhere)
		float SpawnInterval = 0.1f;

	UPROPERTY(EditAnywhere)
		float ShootInterval = 0.01f;

public:
	virtual void ExcuteSkill(ACharacter* InOwner) override;
	virtual void BeginSkill() override;
	virtual void ActiveSkill() override;
	virtual void EndSkill(bool bHit) override;
	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;

private:
	void SpawnShootActor();

private:
	UPROPERTY(Replicated)
	TArray<ABezierShooter*> Shooters;

	FTimerHandle TimerHandle;
	int ShooterCount = 0;
};


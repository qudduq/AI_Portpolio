// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skills/CSkill.h"
#include "CSkill_GroundCircle_One.generated.h"

UCLASS()
class AI_PORTPOLIO_API UCSkill_GroundCircle_One : public UCSkill
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float Radius = 1000.0f;

public:
	virtual void BeginSkill() override;
	virtual void EndSkill() override;
};

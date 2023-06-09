// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skills/CSkill.h"
#include "CSkill_Teleport.generated.h"

/**
 * 
 */
UCLASS()
class AI_PORTPOLIO_API UCSkill_Teleport : public UCSkill
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		float TPDistance = 1000.0f;

public:
	virtual void BeginSkill() override;
	virtual void EndSkill(bool bHit) override;

private:
	virtual FVector GetTeleportLocation() { return OwnerCharacter->GetActorLocation(); }
	void SetHiddenWeapon(bool bHidden);
};

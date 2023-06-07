// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skills/CSkill_Teleport.h"
#include "CSkill_Teleport_Player.generated.h"

/**
 * 
 */
UCLASS()
class AI_PORTPOLIO_API UCSkill_Teleport_Player : public UCSkill_Teleport
{
	GENERATED_BODY()

public:
	virtual void BeginSkill() override;

private:
	virtual FVector GetTeleportLocation() override;
};

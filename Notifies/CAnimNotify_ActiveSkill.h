// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_ActiveSkill.generated.h"

/**
 * 
 */
UCLASS()
class AI_PORTPOLIO_API UCAnimNotify_ActiveSkill : public UAnimNotify
{
	GENERATED_BODY()

private:
	virtual FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};

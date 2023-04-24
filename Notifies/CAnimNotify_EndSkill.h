#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_EndSkill.generated.h"

UCLASS()
class AI_PORTPOLIO_API UCAnimNotify_EndSkill : public UAnimNotify
{
	GENERATED_BODY()

private:
	virtual FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};

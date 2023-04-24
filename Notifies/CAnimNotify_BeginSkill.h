#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_BeginSkill.generated.h"


UCLASS()
class AI_PORTPOLIO_API UCAnimNotify_BeginSkill : public UAnimNotify
{
	GENERATED_BODY()

private:
	virtual FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};

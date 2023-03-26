#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Skills/ASword_Shot.h"
#include "CAnimNotify_Sword_Shot.generated.h"

/*
	현재 UPROPERTY가 노티파이 에디터창에 안나옴 해결요망
*/
UCLASS()
class AI_PORTPOLIO_API UCAnimNotify_Sword_Shot : public UAnimNotify
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		FTransform Transform;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AASword_Shot> Sword_Object;

private:
	FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};

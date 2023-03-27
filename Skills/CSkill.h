#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UCSkillStructure.h"
#include "Widget/QuickSlotInterface.h"
#include "CSkill.generated.h"

UCLASS(Blueprintable, BlueprintType)
class AI_PORTPOLIO_API UCSkill :
	public UObject,
	public IQuickSlotInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
		FDoSkillData SkillData;

	UPROPERTY(EditAnywhere)
		UTexture2D* Texture;

public:
	virtual void ExcuteSkill(class ACharacter* InOwner);
	virtual void BeginSkill() {}
	virtual void EndSkill();

	FORCEINLINE EDistanceSkill GetSkillDistance() { return SkillData.Distance; }

public:
	virtual void QuickSlotCall(class ACharacter* InOwner) override;
	virtual UTexture2D* GetSlotTexture() override;

private:
	void HitCancle();

protected:
	UPROPERTY()
		class UCStateComponent* State;

	UPROPERTY()
		class ACCharacter* OwnerCharacter;

private:
	FDelegateHandle HitCancleHandle;
	FDelegateHandle BeginHandle;
	FDelegateHandle EndHandle;
};

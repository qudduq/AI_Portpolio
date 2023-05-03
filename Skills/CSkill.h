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

	UPROPERTY(EditAnywhere)
		FName SkillID;

public:
	virtual void ExcuteSkill(class ACharacter* InOwner);
	virtual void BeginSkill() {}
	virtual void EndSkill();

	FORCEINLINE EDistanceSkill GetSkillDistance() { return SkillData.Distance; }

protected:
	void PlaySkillEffect(FVector Loaction);

public:
	virtual void QuickSlotCall(class ACharacter* InOwner) override;
	virtual UTexture2D* GetSlotTexture() override;
	virtual FName GetID() override;

private:
	void HitCancle();

protected:
	class UCStateComponent* State;
	class ACCharacter* OwnerCharacter;
	class UFXSystemComponent* FXComponent;

private:
	FDelegateHandle HitCancleHandle;
	FDelegateHandle BeginHandle;
	FDelegateHandle EndHandle;
	
};

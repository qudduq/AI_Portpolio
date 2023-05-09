#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UCSkillStructure.h"
#include "Widget/QuickSlotInterface.h"
#include "Functions/RPCUObject.h"
#include "CSkill.generated.h"

class UCStateComponent;
class UFXSystemComponent;

UCLASS(Blueprintable, BlueprintType)
class AI_PORTPOLIO_API UCSkill :
	public URPCUObject,
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
	virtual void ActiveSkill() {}
	virtual void EndSkill();

	FORCEINLINE EDistanceSkill GetSkillDistance() { return SkillData.Distance; }
protected:
	UFUNCTION(NetMulticast,Reliable)
	void PlaySkillEffect(UObject* WorldContext, FVector Loaction);

	UFUNCTION(NetMulticast, Reliable)
	void OffSkillEffect();

public:
	virtual void QuickSlotCall(class ACharacter* InOwner) override;
	virtual UTexture2D* GetSlotTexture() override;
	virtual FName GetID() override;

private:
	void HitCancle();

protected:
	 UCStateComponent* State;
	 TArray<UFXSystemComponent*> FXComponents;

private:
	FDelegateHandle HitCancleHandle;
	FDelegateHandle BeginHandle;
	FDelegateHandle ActiveHandle;
	FDelegateHandle EndHandle;
	
};

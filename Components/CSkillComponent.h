#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Skills/CSkill.h"
#include "CWeaponComponent.h"
#include "CSkillComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnBeginSkill);
DECLARE_MULTICAST_DELEGATE(FOnEndSkill);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AI_PORTPOLIO_API UCSkillComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Replicated)
		class UCSkillData* SkillDataAssets[(int32)EWeaponType::Max];

public:	
	UCSkillComponent();

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty > & OutLifetimeProps) const override;
protected:
	virtual void BeginPlay() override;

public:	
	UCSkill* GetSkillData(EWeaponType WeaponType, FName ID);
	const TArray<UCSkill*>& GetSkillArrayData(EWeaponType WeaponType) const;
	void BeginSkill();
	void EndSkill();

public:
	UFUNCTION(Reliable, Server, WithValidation)
		void ExcuteSkill(FName SkillID);

public:
	FOnBeginSkill OnBeginSkill;
	FOnEndSkill OnEndSkill;

};

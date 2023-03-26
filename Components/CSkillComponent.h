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
	UPROPERTY(EditDefaultsOnly)
		class UCSkillData* SkillDataAssets[(int32)EWeaponType::Max];

public:	
	UCSkillComponent();

protected:
	virtual void BeginPlay() override;

public:	
	const TArray<UCSkill*>& GetSkillData();
	void BeginSkill();
	void EndSkill();

private:
	UFUNCTION()
		void OnWeaponTypeChanged(EWeaponType InNewType);

public:
	FOnBeginSkill OnBeginSkill;
	FOnEndSkill OnEndSkill;

private:
	class ACharacter* OwnerCharacter;
	class UCSkillData* Data;
	UCWeaponComponent* Weapon;
	EWeaponType WeaponType = EWeaponType::Unarmed;

};

#pragma once

#include "CoreMinimal.h"
#include "HitDataAsset.h"
#include "Components/CStateComponent.h"
#include "Weapon/UCWeaponStructure.h"
#include "GameFramework/Character.h"
#include "CCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnCharacterHit);

UCLASS()
class AI_PORTPOLIO_API ACCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;

	UPROPERTY(EditDefaultsOnly)
		class UCWeaponComponent* Weapon;

	UPROPERTY(EditDefaultsOnly)
		class UCSkillComponent* Skill;

protected:
	UPROPERTY(EditDefaultsOnly)
		class UHitDataAsset* HitData;

	UFUNCTION(BlueprintCallable)
		UCWeaponComponent* GetWeaponComponent() { return Weapon; }

public:
	ACCharacter();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	

protected:
	virtual void BeginPlay() override;

	virtual void Hitted();
	virtual void Dead() {}

	virtual void HitStop(AController* AttackerController);
	virtual void CameraShaking();

public:	
	virtual void End_Hitted();
	virtual void End_Dead() {}

protected:
	//Hit Type별 별개 동작
	virtual void Normal_Hit(EDamageType Type);
	virtual void Fly_Hit(EDamageType Type);

public:
	FOnCharacterHit OnCharacterHit;

private:
	virtual void OnStateTypeChanged(EStateType Type);

private:
	struct FDamageData* DamageData;
	FTimerHandle TimerHandle;
};


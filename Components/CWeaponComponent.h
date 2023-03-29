#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/UCWeaponStructure.h"
#include "CWeaponComponent.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Unarmed, OneHand, Bow, Max,
};

DECLARE_MULTICAST_DELEGATE_OneParam(FWeaponTypeChanged, EWeaponType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AI_PORTPOLIO_API UCWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		class UCWeaponAsset* DataAsset[(int32)EWeaponType::Max];

private:
	UPROPERTY(EditDefaultsOnly)
		TArray<TSubclassOf<class ACAttachment>> AttachmentClasses;

public:
	UFUNCTION(BlueprintCallable)
		void SetUnarmedMode();

	UFUNCTION(BlueprintCallable)
		void SetOneHandMode();

	UFUNCTION(BlueprintCallable)
		void SetBowMode();

public:
	FORCEINLINE bool GetbNextAction() { return bNextAction; }
	FORCEINLINE ACAttachment* GetAttachment() { return Weapons[Type]; }

public:	
	UCWeaponComponent();

	void DoAction();

	void BeginDoAction();
	void EndDoAction();

	void EnableNext();
	void DisableNext();

	void OffNextAction();

	void SpawnWeapon(EWeaponType weapon);
	FDamageData GetDamageData();

public:
	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty > & OutLifetimeProps) const override;

private:
	void HitCancle();

	UFUNCTION(NetMulticast, Reliable)
		void PlayMontage(UAnimMontage* montage);


protected:	
	virtual void BeginPlay() override;

private:
	UFUNCTION(NetMulticast, Reliable)
		void ChangeType(EWeaponType InType);

public:
	FWeaponTypeChanged OnWeaponTypeChanged;

private:
	class ACCharacter* OwnerCharacter;
	class UCStateComponent* State;
	class UCStatusComponent* Status;

	TMap<EWeaponType, class ACAttachment*> Weapons;

	UPROPERTY(Replicated)
		EWeaponType Type = EWeaponType::Max;

	int Combo_index = 0;
	bool bNextAction = false;
	bool bAbleNext = false;
};

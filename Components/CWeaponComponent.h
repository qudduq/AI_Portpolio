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
	ACAttachment* GetAttachment();

public:	
	UCWeaponComponent();

	UFUNCTION(Reliable, Server)
		void DoAction();

	UFUNCTION(Reliable, Server)
		void BeginDoAction();

	UFUNCTION(Reliable, Server)
		void EndDoAction();

	void EnableNext();
	void DisableNext();

	void OffNextAction();

	void SpawnWeapon(EWeaponType weapon);
	const FDamageData GetDamageData();
	FORCEINLINE EWeaponType GetWeaponType() { return Type; }

public:
	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty > & OutLifetimeProps) const override;

private:
	void HitCancle();

protected:	
	virtual void BeginPlay() override;

private:
	UFUNCTION(NetMulticast, Reliable)
		void ChangeType(EWeaponType InType);

	UFUNCTION(Reliable, Server)
		void ServerChangeType(EWeaponType InType);

	UFUNCTION(NetMulticast, Reliable)
		void ChangeComboIndex(int comboIndex);

	UFUNCTION(Reliable, Server)
		void ServerChangeComboIndex(int comboIndex);

public:
	FWeaponTypeChanged OnWeaponTypeChanged;

private:
	class ACCharacter* OwnerCharacter;
	class UCStateComponent* State;
	class UCStatusComponent* Status;

	TMap<EWeaponType, ACAttachment*> Weapons;

	UPROPERTY(Replicated)
		EWeaponType Type = EWeaponType::Unarmed;

	UPROPERTY(Replicated)
		int Combo_index = 0;

	bool bNextAction = false;
	bool bAbleNext = false;
};

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Components/CWeaponComponent.h"
#include "CAnimInstance.generated.h"

UCLASS()
class AI_PORTPOLIO_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CharacterMovement")
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CharacterMovement")
		float Direction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CharacterMovement")
		float Pitch;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Replicated, Category = "CharacterMovement")
		EWeaponType WeaponType = EWeaponType::Unarmed;


public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty > & OutLifetimeProps) const override;

private:
	void OnWeaponTypeChanged(EWeaponType InNewType);

private:
	class ACharacter* OwnerCharacter;
	class UCWeaponComponent* Weapon;
};

#pragma once

#include "CoreMinimal.h"
#include "Character/CCharacter.h"
#include "Components/CWeaponComponent.h"
#include "CEnemy.generated.h"

UENUM(BlueprintType)
enum class ERaceType : uint8
{
	Red, Black, White, Blue, Max,
};

UCLASS()
class AI_PORTPOLIO_API ACEnemy : public ACCharacter
{
	GENERATED_BODY()
	friend class Enemy_Factory;

private:
	UPROPERTY(EditDefaultsOnly)
		class UEnemyRaceData* RaceData;

public:
	ACEnemy();

	void Attach_Weapon(EWeaponType weapon);
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};

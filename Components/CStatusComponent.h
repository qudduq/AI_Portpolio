#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"

UENUM(BlueprintType)
enum class ESpeedType : uint8
{
	Walk = 0, Run, Sprint, Max,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AI_PORTPOLIO_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Speed")
		float Speed[(int32)ESpeedType::Max] = { 200, 400, 600 };

	UPROPERTY(EditAnywhere, Category = "Health")
		float MaxHealth = 100;

	UPROPERTY(EditAnywhere, Category = "Energy")
		float MaxEnergy = 100;

public:
	FORCEINLINE float GetWalkSpeed() { return Speed[(int32)ESpeedType::Walk]; }
	FORCEINLINE float GetRunSpeed() { return Speed[(int32)ESpeedType::Run]; }
	FORCEINLINE float GetSprintSpeed() { return Speed[(int32)ESpeedType::Sprint]; }

	FORCEINLINE bool IsMove() { return bCanMove; }

	FORCEINLINE void Move() { bCanMove = true; }
	FORCEINLINE void Stop() { bCanMove = false; }

	FORCEINLINE float GetHealth() { return Health; }
	FORCEINLINE float GetMaxHealth() { return MaxHealth; }


public:	
	UCStatusComponent();

	void Hit(float InAmount);
	void Energing(float InAmount);

protected:
	virtual void BeginPlay() override;

private:
	class ACharacter* OwnerCharacter;
	
	bool bCanMove = true;
	float Health;
	float Energy;
};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundIce.generated.h"

struct FDamageData;
UCLASS()
class AI_PORTPOLIO_API AGroundIce : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		class UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere)
		class UFXSystemAsset* Particle;

public:	
	AGroundIce();

protected:
	virtual void BeginPlay() override;

public:
	void SetDamageData(FDamageData _DamageData);

private:
	UFUNCTION()
	void ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnNiagaraFinish(class UNiagaraComponent* niagara);

	UFUNCTION()
		void OnParticleFinish(class UParticleSystemComponent* PSystem);

private:
	TArray<ACharacter*> HittedCharacters;
	FDamageData DamageData_;
};



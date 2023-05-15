#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon/UCWeaponStructure.h"
#include "BezierShooter.generated.h"

class UFXSystemAsset;

UCLASS()
class AI_PORTPOLIO_API ABezierShooter : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		USceneComponent* Root;

	UPROPERTY(EditAnywhere)
		class USphereComponent* Sphere;

private:
	UPROPERTY(EditAnywhere)
		class UBezierComponent* Bezier;

public:	
	ABezierShooter();
	void SetParticle(UFXSystemAsset* particle);
	void SetDamageData(const FDamageData& _DamageData);
	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty > & OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	void PlayParticle();
	void ArrivePostion();
	
public:
	void BezierShoot(FVector DirLocation, FVector PlayerLocation);

private:
	UFUNCTION()
		void OnNiagaraFinish(class UNiagaraComponent* niagara);

	UFUNCTION()
		void OnParticleFinish(class UParticleSystemComponent* PSystem);

private:
	UPROPERTY(Replicated)
		UFXSystemAsset* Particle;

	FDamageData DamageData_;
};

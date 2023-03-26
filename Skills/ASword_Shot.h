#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ASword_Shot.generated.h"

/*
    충돌판전에 충돌한다고는 뜨는데 눈에는 안보임
*/
UCLASS()
class AI_PORTPOLIO_API AASword_Shot : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		float LifeTime;

private:
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly)
		class USphereComponent* Sphere;

private:
	UPROPERTY(EditDefaultsOnly)
		class UProjectileMovementComponent* Projectile;
	
public:	
	AASword_Shot();

protected:
	virtual void BeginPlay() override;

};

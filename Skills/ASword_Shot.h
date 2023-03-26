#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ASword_Shot.generated.h"

/*
    �浹������ �浹�Ѵٰ�� �ߴµ� ������ �Ⱥ���
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

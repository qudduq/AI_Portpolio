#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BezierShooter.generated.h"

UCLASS()
class AI_PORTPOLIO_API ABezierShooter : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		class USceneComponent* Root;

	UPROPERTY(EditAnywhere)
		class USphereComponent* Sphere;

private:
	UPROPERTY(EditAnywhere)
		class UBezierComponent* Bezier;
	
public:	
	ABezierShooter();

protected:
	virtual void BeginPlay() override;

public:
	void BezierShoot(FVector Enemy, FVector PlayerLocation);


};

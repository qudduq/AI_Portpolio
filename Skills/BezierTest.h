#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BezierTest.generated.h"

DECLARE_DELEGATE_TwoParams(FBezierShoot, FVector, FVector);

UCLASS()
class AI_PORTPOLIO_API ABezierTest : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		class USceneComponent* Root;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* OBj;

private:
	UPROPERTY(EditAnywhere)
		class UBezierComponent* Bezier;
	
public:	
	ABezierTest();

protected:
	virtual void BeginPlay() override;

public:
	void BezierShoot(FVector Enemy, FVector PlayerLocation);

private:
	FBezierShoot OnBezierShoot;

};

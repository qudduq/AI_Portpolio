#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BezierComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnArrivePosition);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AI_PORTPOLIO_API UBezierComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float SpaceHorizontal = 300.0f;

	UPROPERTY(EditAnywhere)
		float SpaceVertical = 200.0f;

	UPROPERTY(EditAnywhere)
		float Speed = 1.0f;

public:	
	UBezierComponent();

public:
	UFUNCTION(BlueprintCallable)
		void ShootBezierCurve(const FVector EndPostion,const FVector OwnerPostion);

	FOnArrivePosition OnArrivePosition;
private:
	const FVector GetLocationBezier(const FVector start,const FVector end,const FVector adj,const float rate);
	const FVector SetControlPosition(const FVector Start, const FVector End, const FVector OwerPostion);

private:
	float Rate = 0;
	FTimerHandle handle;
};

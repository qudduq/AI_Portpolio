#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundCircle.generated.h"

UCLASS()
class AI_PORTPOLIO_API AGroundCircle : public AActor
{
	GENERATED_BODY()
	
public:	
	AGroundCircle();

protected:
	virtual void BeginPlay() override;


};

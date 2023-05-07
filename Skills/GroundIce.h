#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundIce.generated.h"

UCLASS()
class AI_PORTPOLIO_API AGroundIce : public AActor
{
	GENERATED_BODY()
	
public:	
	AGroundIce();

protected:
	virtual void BeginPlay() override;


};

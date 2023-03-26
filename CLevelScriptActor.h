#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "CLevelScriptActor.generated.h"

UCLASS()
class AI_PORTPOLIO_API ACLevelScriptActor 
	: public ALevelScriptActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		class ALandscapeProxy* landscape;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UCUserWidget> Widget;
	
protected:
	virtual void BeginPlay() override;

private:
	FTimerHandle Tm;

};

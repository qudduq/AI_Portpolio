// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CEQSComponent.generated.h"

DECLARE_DELEGATE_RetVal(FVector, FOnEQSPosition);

struct FEnvQueryResult;
class UEnvQuery;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AI_PORTPOLIO_API UCEQSComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "EQS")
		UEnvQuery* EQSOptionData;

public:	
	UCEQSComponent();
	FVector GetEQSPostion();

private:
	FVector FindEQSSpot();
	void EQSResult(TSharedPtr<FEnvQueryResult> result);

	FOnEQSPosition OnEQSPosition;

protected:
	virtual void BeginPlay() override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RPCUObject.generated.h"

UCLASS()
class AI_PORTPOLIO_API URPCUObject : public UObject
{
	GENERATED_BODY()

public:
	FORCEINLINE virtual bool IsSupportedForNetworking() const override
	{
		return true;
	}
	FORCEINLINE virtual bool ReplicateSubObjects(class AActorChannel* Channel, class FOutBunch* Bunch, struct FReplicationFlags* RepFlags)
	{
		return false;
	}

	int32 GetFunctionCallspace(UFunction* Function, FFrame* Stack) override;
	bool CallRemoteFunction(UFunction* Function, void* Parms, FOutParmRec* OutParms, FFrame* Stack) override;
protected:
	class ACCharacter* OwnerCharacter;
};

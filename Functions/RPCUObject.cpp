// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/RPCUObject.h"
#include "Kismet/GameplayStatics.h"
#include "Character/CCharacter.h"
#include "Net/UnrealNetwork.h"

int32 URPCUObject::GetFunctionCallspace(UFunction* Function, FFrame* Stack)
{
	AActor* Owner = Cast<AActor>(OwnerCharacter);
	return Owner ? Owner->GetFunctionCallspace(Function, Stack) : FunctionCallspace::Local;
}

bool URPCUObject::CallRemoteFunction(UFunction* Function, void* Parms, FOutParmRec* OutParms, FFrame* Stack)
{
	if(AActor* MyOwner = Cast<AActor>(OwnerCharacter))
	{
		if(UNetDriver* NetDriver = MyOwner->GetNetDriver())
		{
			NetDriver->ProcessRemoteFunction(MyOwner, Function, Parms, OutParms, Stack, this);
			return true;
		}
	}
	return false;
}

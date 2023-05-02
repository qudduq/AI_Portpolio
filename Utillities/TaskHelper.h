#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Utillities/CLog.h"

class AI_PORTPOLIO_API TaskHelper
{
public:
	template<typename T>
	static T* GetComponet(ACharacter* OwnerCharacter)
	{
		T* OutComponent = Cast<T>(OwnerCharacter->GetComponentByClass(T::StaticClass()));
		if (OutComponent == nullptr)
		{
			FString str = OwnerCharacter->GetName();
			str += " Have Not ";
			str += typeid(T).name();
			CLog::Log(str);
			return nullptr;
		}

		return OutComponent;
	}

	static UParticleSystemComponent* PlayParticleSystem(UObject* WorldContext, UFXSystemAsset* Particle, FVector Location)
	{
		return UGameplayStatics::SpawnEmitterAtLocation
		(
			WorldContext,
			Cast<UParticleSystem>(Particle),
			Location
		);
	}

	static UNiagaraComponent* PlayNiagaraSystem(UObject* WorldContext, UFXSystemAsset* Niagara, FVector Location)
	{
		return UNiagaraFunctionLibrary::SpawnSystemAtLocation
		(
			WorldContext,
			Cast<UNiagaraSystem>(Niagara),
			Location
		);
	}
};

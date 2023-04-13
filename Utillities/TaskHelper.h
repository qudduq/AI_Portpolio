#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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
};

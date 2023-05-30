#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CustomProjectSetting.generated.h"

UCLASS(Config=Game,DefaultConfig)
class AI_PORTPOLIO_API UCustomProjectSetting : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere)
		int MagicNumber;
};

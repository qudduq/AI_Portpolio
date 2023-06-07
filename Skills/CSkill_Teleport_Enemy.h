#pragma once

#include "CoreMinimal.h"
#include "Skills/CSkill_Teleport.h"
#include "CSkill_Teleport_Enemy.generated.h"

struct FEnvQueryResult;
class UEnvQuery;
UCLASS()
class AI_PORTPOLIO_API UCSkill_Teleport_Enemy : public UCSkill_Teleport
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "EQS")
		UEnvQuery* EQSOptionData;

public:
	virtual void BeginSkill() override;

private:
	void EQSTeleport(TSharedPtr<FEnvQueryResult> result);
};


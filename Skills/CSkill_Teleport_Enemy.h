#pragma once

#include "CoreMinimal.h"
#include "Skills/CSkill_Teleport.h"
#include "CSkill_Teleport_Enemy.generated.h"

UCLASS()
class AI_PORTPOLIO_API UCSkill_Teleport_Enemy : public UCSkill_Teleport
{
	GENERATED_BODY()

private:
	virtual FVector GetTeleportLocation() override;
};


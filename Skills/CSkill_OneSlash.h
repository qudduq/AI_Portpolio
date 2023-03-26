#pragma once

#include "CoreMinimal.h"
#include "Skills/CSkill.h"
#include "CSkill_OneSlash.generated.h"

UCLASS()
class AI_PORTPOLIO_API UCSkill_OneSlash : public UCSkill
{
	GENERATED_BODY()

public:
	virtual void BeginSkill() override;
	virtual void EndSkill() override;
};

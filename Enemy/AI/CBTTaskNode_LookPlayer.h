#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_LookPlayer.generated.h"

UCLASS()
class AI_PORTPOLIO_API UCBTTaskNode_LookPlayer : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCBTTaskNode_LookPlayer();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

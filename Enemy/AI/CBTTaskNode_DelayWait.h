#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_DelayWait.generated.h"

UCLASS()
class AI_PORTPOLIO_API UCBTTaskNode_DelayWait : public UBTTaskNode
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float DelayTime = 1.0f;

public:
	UCBTTaskNode_DelayWait();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


private:
	FTimerHandle TimerHandle;
};

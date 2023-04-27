#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_Loop.h"
#include "CBTDecorator_CustomLoop.generated.h"

UCLASS()
class AI_PORTPOLIO_API UCBTDecorator_CustomLoop : public UBTDecorator_Loop
{
	GENERATED_BODY()

public:
	UCBTDecorator_CustomLoop();

protected:
	virtual void OnNodeActivation(FBehaviorTreeSearchData& SearchData);
	virtual void OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult);
private:
	void OffInfinityLoop();

private:
	FDelegateHandle handle;
};

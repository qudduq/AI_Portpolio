#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "Components/CStateComponent.h"
#include "CBTDecorator_Test.generated.h"

UCLASS()
class AI_PORTPOLIO_API UCBTDecorator_Test : public UBTDecorator
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = Blackboard)
		EStateType Type;
	
public:
	UCBTDecorator_Test(const FObjectInitializer& ObjectInitializer);

	virtual uint16 GetInstanceMemorySize() const override;

protected:
	/** called when auxiliary node becomes active
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	/** called when auxiliary node becomes inactive
	 * this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

private:
	void OnStateTypeChanged(EStateType InNewType, AAIController* controller);

};

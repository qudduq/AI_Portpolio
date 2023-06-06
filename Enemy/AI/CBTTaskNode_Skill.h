#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Skills/UCSkillStructure.h"
#include "CBTTaskNode_Skill.generated.h"

UCLASS()
class AI_PORTPOLIO_API UCBTTaskNode_Skill : public UBTTaskNode
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		EDistanceSkill SkillDistance;

public:
	UCBTTaskNode_Skill();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	void ChoiceAndExcuteSkill(class ACCharacter* OwnerCharacter);

};

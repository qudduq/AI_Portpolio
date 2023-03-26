#include "CBTTaskNode_Skill.h"

#include "Components/CStateComponent.h"
#include "Components/CSkillComponent.h"
#include "Components/CBehaviorComponent.h"
#include "Enemy/CAIController.h"
#include "Enemy/CEnemy_AI.h"
#include "Skills/CSkill.h"
#include "Utillities/CLog.h"

UCBTTaskNode_Skill::UCBTTaskNode_Skill()
{
	NodeName = "Skill";
	bNotifyTick = false;
}

EBTNodeResult::Type UCBTTaskNode_Skill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* owner = Cast<ACEnemy_AI>(controller->GetPawn());

	UCStateComponent* stateComponent = Cast<UCStateComponent>(owner->GetComponentByClass(UCStateComponent::StaticClass()));
	if (stateComponent == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	stateComponent->OnIdleMode.BindUObject(this, &UCBTTaskNode_Skill::EndAction);
	UCSkill* skill = ChoiceSkill(owner);
	if (skill == nullptr)
	{
		FString str = "";
		str += UEnum::GetValueAsString(SkillDistance);
		str += " have Not Skill";
		CLog::Log(str);
		return EBTNodeResult::Failed;
	}
	skill->ExcuteSkill(owner);

	return EBTNodeResult::InProgress;
}

UCSkill* UCBTTaskNode_Skill::ChoiceSkill(ACCharacter* OwnerCharacter)
{
	UCSkillComponent* skillComponent = Cast<UCSkillComponent>(OwnerCharacter->GetComponentByClass(UCSkillComponent::StaticClass()));
	if (skillComponent == nullptr)
	{
		CLog::Log("Enemy Not SkillComponent");
		return nullptr;
	}

	TArray<UCSkill*> skills;
	for (auto & skill : skillComponent->GetSkillData())
	{
		if (skill->GetSkillDistance() == SkillDistance)
		{
			skills.Add(skill);
		}
	}

	int maxSkillNum = skills.Num() - 1;
	if (maxSkillNum < 0)
	{
		return nullptr;
	}

	int RandomSkill = FMath::RandRange(0, maxSkillNum);

	return skills[RandomSkill];
}


void UCBTTaskNode_Skill::EndAction(AAIController* controller)
{
	if (controller == nullptr)
		return;

	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(controller->GetBrainComponent());
	if (BehaviorTreeComponent == nullptr)
		return;

	ACCharacter* owner = Cast<ACCharacter>(controller->GetPawn());
	if (owner == nullptr)
		return;

	UCStateComponent* stateComponent = Cast<UCStateComponent>(owner->GetComponentByClass(UCStateComponent::StaticClass()));
	if (stateComponent == nullptr)
		return;

	UCBehaviorComponent* behaviorComponent = Cast<UCBehaviorComponent>(owner->GetComponentByClass(UCBehaviorComponent::StaticClass()));
	if (behaviorComponent == nullptr)
		return;

	CLog::Log("TaskEndAction");
	stateComponent->OnIdleMode.Unbind();
	behaviorComponent->SetWaitMode();

	FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::Succeeded);
}

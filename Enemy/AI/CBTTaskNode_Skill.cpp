#include "CBTTaskNode_Skill.h"

#include "Components/CStateComponent.h"
#include "Components/CSkillComponent.h"
#include "Components/CBehaviorComponent.h"
#include "Enemy/CAIController.h"
#include "Enemy/CEnemy_AI.h"
#include "Skills/CSkill.h"
#include "Utillities/CLog.h"
#include "Utillities/TaskHelper.h"

UCBTTaskNode_Skill::UCBTTaskNode_Skill()
{
	NodeName = "Skill";
	bNotifyTick = false;
}

EBTNodeResult::Type UCBTTaskNode_Skill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	if(IsValid(controller) == false)
	{
		return Result;
	}

	ACEnemy_AI* owner = Cast<ACEnemy_AI>(controller->GetPawn());
	if(IsValid(owner) == false)
	{
		return Result;
	}

	UCStateComponent* stateComponent = Cast<UCStateComponent>(owner->GetComponentByClass(UCStateComponent::StaticClass()));
	if (IsValid(stateComponent) == false)
	{
		return Result;
	}

	if(stateComponent->IsActionMode())
	{
		return Result;
	}
	ChoiceAndExcuteSkill(owner);

	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UCBTTaskNode_Skill::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::AbortTask(OwnerComp, NodeMemory);

	FString str = "";
	str += UEnum::GetValueAsString(SkillDistance);
	str += " Abort";
	CLog::Log(str);

	return Result;
}

void UCBTTaskNode_Skill::ChoiceAndExcuteSkill(ACCharacter* OwnerCharacter)
{
	UCSkillComponent* skillComponent = TaskHelper::GetComponet<UCSkillComponent>(OwnerCharacter);
	if(IsValid(skillComponent) == false)
		return;

	UCWeaponComponent* WeaponComponent = TaskHelper::GetComponet<UCWeaponComponent>(OwnerCharacter);
	if(IsValid(WeaponComponent) == false)
		return;

	TArray<UCSkill*> skills;
	for (const auto & skill : skillComponent->GetSkillArrayData(WeaponComponent->GetWeaponType()))
	{
		if (skill->GetSkillDistance() == SkillDistance)
		{
			skills.Emplace(skill);
		}
	}

	int maxSkillNum = skills.Num() - 1;
	if (maxSkillNum < 0)
	{
		return;
	}

	int RandomSkill = FMath::RandRange(0, maxSkillNum);
	skills[RandomSkill]->ExcuteSkill(OwnerCharacter);
}

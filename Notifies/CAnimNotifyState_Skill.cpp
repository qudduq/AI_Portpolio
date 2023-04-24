#include "Notifies/CAnimNotifyState_Skill.h"
#include "Components/CSkillComponent.h"
#include "GameFramework/Character.h"
#include "Utillities/CLog.h"


FString UCAnimNotifyState_Skill::GetNotifyName_Implementation() const
{
	return "Skill";
}

void UCAnimNotifyState_Skill::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;

	ACharacter* character = Cast<ACharacter>(MeshComp->GetOwner());
	if(character == nullptr)
	{
		return;
	}

	UCSkillComponent* SkillComponent = Cast<UCSkillComponent>(character->GetComponentByClass(UCSkillComponent::StaticClass()));
	if(SkillComponent == nullptr)
	{
		return;
	}

	SkillComponent->BeginSkill();
}

void UCAnimNotifyState_Skill::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;

	ACharacter* character = Cast<ACharacter>(MeshComp->GetOwner());
	if (character == nullptr)
	{
		return;
	}

	UCSkillComponent* SkillComponent = Cast<UCSkillComponent>(character->GetComponentByClass(UCSkillComponent::StaticClass()));
	if (SkillComponent == nullptr)
	{
		return;
	}

	CLog::Log("EndNotify_end");
	SkillComponent->EndSkill();
}

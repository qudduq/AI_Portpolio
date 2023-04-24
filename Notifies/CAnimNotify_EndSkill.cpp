#include "Notifies/CAnimNotify_EndSkill.h"
#include "Components/CSkillComponent.h"
#include "GameFramework/Character.h"

FString UCAnimNotify_EndSkill::GetNotifyName_Implementation() const
{
	return "End Skill";
}

void UCAnimNotify_EndSkill::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

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

	SkillComponent->EndSkill();
}

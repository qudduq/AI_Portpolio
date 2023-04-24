#include "Notifies/CAnimNotify_BeginSkill.h"
#include "Components/CSkillComponent.h"
#include "GameFramework/Character.h"

FString UCAnimNotify_BeginSkill::GetNotifyName_Implementation() const
{
	return "Begin_Skill";
}

void UCAnimNotify_BeginSkill::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
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

	SkillComponent->BeginSkill();
}

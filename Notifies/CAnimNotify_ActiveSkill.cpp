// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifies/CAnimNotify_ActiveSkill.h"

#include "GameFramework/Character.h"
#include "Components/CSkillComponent.h"

FString UCAnimNotify_ActiveSkill::GetNotifyName_Implementation() const
{
	return "Active Skill";
}

void UCAnimNotify_ActiveSkill::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
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

	SkillComponent->ActiveSkill();
}

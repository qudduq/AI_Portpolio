#include "UCSkillStructure.h"
#include "GameFramework/Character.h"
#include "Components/CStatusComponent.h"
#include "Components/CStateComponent.h"
#include "Animation/AnimMontage.h"
#include "Sound/SoundCue.h"

void FDoSkillData::DoAction(ACharacter* InOwner)
{
	UCStatusComponent* status = Cast<UCStatusComponent>(InOwner->GetComponentByClass(UCStatusComponent::StaticClass()));
	if (!!status)
	{

	}

	if (!!Montage)
		InOwner->PlayAnimMontage(Montage, PlayRatio);

}

void FDoSkillData::End_DoAction(ACharacter* InOwner)
{
	UCStateComponent* state = Cast<UCStateComponent>(InOwner->GetComponentByClass(UCStateComponent::StaticClass()));
	if (!!state)
		state->SetIdleMode();
}

void FDoSkillData::PlayEffect(ACharacter* InOwner)
{

}

void FDoSkillData::PlayEffect(USkeletalMeshComponent* InMesh, FName InSocketName)
{
}

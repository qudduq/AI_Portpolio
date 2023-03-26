#include "UCWeaponStructure.h"
#include "GameFramework/Character.h"
#include "Components/CStatusComponent.h"
#include "Components/CStateComponent.h"
#include "Animation/AnimMontage.h"


 ////////////////////////////////////////////////////////


void FDoActionData::DoAction(ACharacter* InOwner)
{
	if (!!Montage)
		InOwner->PlayAnimMontage(Montage, PlayRatio);
}

void FDoActionData::End_DoAction(ACharacter* InOwner)
{
	UCStateComponent* state = Cast<UCStateComponent>(InOwner->GetComponentByClass(UCStateComponent::StaticClass()));
	if (!!state)
		state->SetIdleMode();
}

void FDoActionData::PlayEffect(ACharacter* InOwner)
{

}

void FDoActionData::PlayEffect(USkeletalMeshComponent* InMesh, FName InSocketName)
{

}

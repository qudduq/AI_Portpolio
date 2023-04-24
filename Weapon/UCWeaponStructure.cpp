#include "UCWeaponStructure.h"
#include "GameFramework/Character.h"
#include "Components/CStatusComponent.h"
#include "Components/CStateComponent.h"
#include "Animation/AnimMontage.h"
#include "Utillities/CLog.h"


////////////////////////////////////////////////////////


void FDoActionData::DoAction(ACharacter* InOwner)
{
	if (!!Montage)
		InOwner->PlayAnimMontage(Montage, PlayRatio);
}

void FDoActionData::PlayEffect(ACharacter* InOwner)
{

}

void FDoActionData::PlayEffect(USkeletalMeshComponent* InMesh, FName InSocketName)
{

}

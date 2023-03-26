#include "CAnimNotifyState_BeginDoAction.h"
#include "GameFramework/Character.h"
#include "Components/CWeaponComponent.h"
#include "Utillities/CLog.h"


FString UCAnimNotifyState_BeginDoAction::GetNotifyName_Implementation() const
{
	return "BeginDoAction";
}

void UCAnimNotifyState_BeginDoAction::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp == NULL) return;
	if (MeshComp->GetOwner() == NULL) return;

	UCWeaponComponent* weapon = Cast<UCWeaponComponent>(MeshComp->GetOwner()->GetComponentByClass(UCWeaponComponent::StaticClass()));
	if (weapon == NULL) return;

	weapon->EnableNext();
}

void UCAnimNotifyState_BeginDoAction::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (MeshComp == NULL) return;
	if (MeshComp->GetOwner() == NULL) return;

	UCWeaponComponent* weapon = Cast<UCWeaponComponent>(MeshComp->GetOwner()->GetComponentByClass(UCWeaponComponent::StaticClass()));
	if (weapon == NULL) return;

	if (weapon->GetbNextAction())
	{
		weapon->BeginDoAction();
	}
	
	weapon->DisableNext();
	weapon->OffNextAction();
}

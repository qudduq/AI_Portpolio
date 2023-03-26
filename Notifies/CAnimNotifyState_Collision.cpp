#include "CAnimNotifyState_Collision.h"
#include "Weapon/CAttachment.h"
#include "Components/CWeaponComponent.h"


FString UCAnimNotifyState_Collision::GetNotifyName_Implementation() const
{
	return "Collision";
}

void UCAnimNotifyState_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp,Animation,TotalDuration);

	if (MeshComp == NULL) return;
	if (MeshComp->GetOwner() == NULL) return;

	UCWeaponComponent* weapon = Cast<UCWeaponComponent>(MeshComp->GetOwner()->GetComponentByClass(UCWeaponComponent::StaticClass()));
	if (weapon == NULL) return;

	ACAttachment* attach = weapon->GetAttachment();
	if (attach == NULL) return;

	attach->OnCollision();
}

void UCAnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (MeshComp == NULL) return;
	if (MeshComp->GetOwner() == NULL) return;

	UCWeaponComponent* weapon = Cast<UCWeaponComponent>(MeshComp->GetOwner()->GetComponentByClass(UCWeaponComponent::StaticClass()));
	if (weapon == NULL) return;

	ACAttachment* attach = weapon->GetAttachment();
	if (attach == NULL) return;

	attach->OffCollision();
}

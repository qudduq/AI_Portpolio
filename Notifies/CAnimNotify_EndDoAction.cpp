#include "CAnimNotify_EndDoAction.h"
#include "GameFramework/Character.h"
#include "Components/CWeaponComponent.h"

FString UCAnimNotify_EndDoAction::GetNotifyName_Implementation() const
{
	return "EndDoAction";
}

void UCAnimNotify_EndDoAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp == NULL) return;
	if (MeshComp->GetOwner() == NULL) return;

	UCWeaponComponent* weapon = Cast<UCWeaponComponent>(MeshComp->GetOwner()->GetComponentByClass(UCWeaponComponent::StaticClass()));
	if (weapon == NULL) return;

	weapon->EndDoAction(false);
}
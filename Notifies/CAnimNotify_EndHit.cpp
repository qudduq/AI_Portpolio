#include "CAnimNotify_EndHit.h"
#include "GameFramework/Character.h"
#include "Character/CCharacter.h"
#include "Components/CStateComponent.h"

FString UCAnimNotify_EndHit::GetNotifyName_Implementation() const
{
	return "EndHit";
}

void UCAnimNotify_EndHit::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;

	ACCharacter* owner = Cast<ACCharacter>(MeshComp->GetOwner());
	if (owner == nullptr) return;

	owner->End_Hitted();
}

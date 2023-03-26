#include "CAnimNotify_EndDead.h"
#include "GameFramework/Character.h"
#include "Character/CCharacter.h"
#include "Components/CStateComponent.h"

FString UCAnimNotify_EndDead::GetNotifyName_Implementation() const
{
	return "EndDead";
}

void UCAnimNotify_EndDead::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;

	ACCharacter* owner = Cast<ACCharacter>(MeshComp->GetOwner());
	if (owner == nullptr)
	{
		return;
	}

	owner->End_Dead();
}

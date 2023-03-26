#include "CAnimNotify_Sword_Shot.h"
#include "Utillities/CLog.h"
#include "GameFramework/Character.h"

FString UCAnimNotify_Sword_Shot::GetNotifyName_Implementation() const
{
	return "Sword_Shot";
}

void UCAnimNotify_Sword_Shot::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp == NULL) return;
	if (MeshComp->GetOwner() == NULL) return;
	ACharacter* OwnerCharacter = Cast<ACharacter>(MeshComp->GetOwner());
	if (OwnerCharacter == NULL) return;

	FActorSpawnParameters params;
	params.Owner = OwnerCharacter;

	FTransform transform;
	transform.SetLocation(OwnerCharacter->GetActorLocation());

	//CLog::Log("PlayerLocation");
	//CLog::Log(OwnerCharacter->GetActorLocation());
	MeshComp->GetOwner()->GetWorld()->SpawnActor<AASword_Shot>(Sword_Object,transform, params);
}



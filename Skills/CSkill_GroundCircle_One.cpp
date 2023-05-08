#include "Skills/CSkill_GroundCircle_One.h"

#include "GroundIce.h"
#include "Character/CCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "Particles/ParticleSystemComponent.h"
#include "Utillities/TaskHelper.h"


void UCSkill_GroundCircle_One::BeginSkill()
{
	Super::BeginSkill();

	Location = TaskHelper::GetCircleSearchCharacter(OwnerCharacter, Radius, EDrawDebugTrace::ForDuration);
	Location.Z -= 80.0f;
	PlaySkillEffect(OwnerCharacter->GetWorld(),Location);
}

void UCSkill_GroundCircle_One::ActiveSkill()
{
	Super::ActiveSkill();
	OffSkillEffect();
	if (IceClass != nullptr)
	{
		FTransform Transform;
		Transform.SetLocation(Location);
		Ice = OwnerCharacter->GetWorld()->SpawnActorDeferred<AGroundIce>(IceClass, Transform, OwnerCharacter);
		Ice->SetDamageData(SkillData.DamageData);
		Ice->SetReplicates(true);
		Ice->FinishSpawning(Transform);
	}
}

void UCSkill_GroundCircle_One::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UCSkill_GroundCircle_One, Ice);
}

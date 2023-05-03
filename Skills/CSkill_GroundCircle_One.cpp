#include "Skills/CSkill_GroundCircle_One.h"

#include "Character/CCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystemComponent.h"
#include "Utillities/TaskHelper.h"


void UCSkill_GroundCircle_One::BeginSkill()
{
	Super::BeginSkill();

	FVector Location = TaskHelper::GetCircleSearchCharacter(OwnerCharacter, Radius, EDrawDebugTrace::ForDuration);
	Location.Z -= 80.0f;
	PlaySkillEffect(Location);
	
}

void UCSkill_GroundCircle_One::EndSkill()
{
	FXComponent->DestroyComponent();
	Super::EndSkill();
}

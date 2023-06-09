#include "Skills/CSkill_OneSlash.h"

#include "GameFramework/Character.h"
#include "Utillities/CLog.h"
#include "Components/CapsuleComponent.h"
#include "Character/CCharacter.h"

void UCSkill_OneSlash::BeginSkill()
{
	Super::BeginSkill();

	OwnerCharacter->GetCapsuleComponent()->SetCollisionProfileName(L"SkillOverlap");
}

void UCSkill_OneSlash::EndSkill(bool bHit)
{
	CLog::Log("EndSkill");
	OwnerCharacter->GetCapsuleComponent()->SetCollisionProfileName(L"Pawn");

	Super::EndSkill(bHit);
}
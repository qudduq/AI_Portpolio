#include "Skills/CSkill_OneSlash.h"

#include "GameFramework/Character.h"
#include "Utillities/CLog.h"
#include "Components/CapsuleComponent.h"

void UCSkill_OneSlash::BeginSkill()
{
	Super::BeginSkill();

	CLog::Log("BeginSkill");
	OwnerCharacter->GetCapsuleComponent()->SetCollisionProfileName(L"SkillOverlap");
}

void UCSkill_OneSlash::EndSkill()
{
	CLog::Log("EndSkill");
	OwnerCharacter->GetCapsuleComponent()->SetCollisionProfileName(L"Pawn");

	Super::EndSkill();
}
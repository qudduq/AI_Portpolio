#include "Skills/CSkill_Teleport_Player.h"

#include "Character/CCharacter.h"
#include "Utillities/TaskHelper.h"

FVector UCSkill_Teleport_Player::GetTeleportLocation()
{
	FVector forward = OwnerCharacter->GetActorForwardVector();
	forward.Z = 0.0f;
	FVector Des = OwnerCharacter->GetActorLocation() + forward * TPDistance;
	return Des;
}

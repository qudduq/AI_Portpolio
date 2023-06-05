#include "Skills/CSkill_Teleport.h"

#include "Camera/CameraComponent.h"
#include "Character/CCharacter.h"
#include "Enemy/CEnemy.h"
#include "Player/CPlayer.h"
#include "Utillities/TaskHelper.h"
#include "Components/CWeaponComponent.h"
#include "Weapon/CAttachment.h"

void UCSkill_Teleport::BeginSkill()
{
	Super::BeginSkill();
	OwnerCharacter->SetHidden(true);
	SetHiddenWeapon(true);

	PlaySkillEffect(OwnerCharacter->GetWorld(),OwnerCharacter->GetActorLocation());

	OwnerCharacter->TeleportTo(GetTeleportLocation(), OwnerCharacter->GetActorRotation());
}

void UCSkill_Teleport::EndSkill(bool bHit)
{
	PlaySkillEffect(OwnerCharacter->GetWorld(),OwnerCharacter->GetActorLocation());
	OwnerCharacter->SetHidden(false);
	SetHiddenWeapon(false);

	Super::EndSkill(bHit);
}

void UCSkill_Teleport::SetHiddenWeapon(bool bHidden)
{
	UCWeaponComponent* WeaponComponent = TaskHelper::GetComponet<UCWeaponComponent>(OwnerCharacter);
	ACAttachment* Weapon = WeaponComponent->GetAttachment();
	if (Weapon != nullptr)
	{
		Weapon->SetHidden(bHidden);
	}
}

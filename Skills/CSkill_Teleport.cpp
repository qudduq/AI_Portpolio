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
	UCWeaponComponent* WeaponComponent = TaskHelper::GetComponet<UCWeaponComponent>(OwnerCharacter);
	ACAttachment* Weapon = WeaponComponent->GetAttachment();
	if(Weapon != nullptr)
	{
		Weapon->SetHidden(true);
	}

	PlaySkillEffect(OwnerCharacter->GetWorld(),OwnerCharacter->GetActorLocation());

	Teleport();
}

void UCSkill_Teleport::EndSkill(bool bHit)
{
	PlaySkillEffect(OwnerCharacter->GetWorld(),OwnerCharacter->GetActorLocation());
	OwnerCharacter->SetHidden(false);
	UCWeaponComponent* WeaponComponent = TaskHelper::GetComponet<UCWeaponComponent>(OwnerCharacter);
	ACAttachment* Weapon = WeaponComponent->GetAttachment();
	if (Weapon != nullptr)
	{
		Weapon->SetHidden(false);
	}

	Super::EndSkill(bHit);
}

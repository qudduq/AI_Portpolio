// Fill out your copyright notice in the Description page of Project Settings.


#include "Skills/CSkill_Teleport_Player.h"

#include "Camera/CameraComponent.h"
#include "Utillities/TaskHelper.h"

void UCSkill_Teleport_Player::Teleport()
{
	UCameraComponent* camera = TaskHelper::GetComponet<UCameraComponent>(OwnerCharacter);
	if (camera == nullptr)
	{
		return;
	}

	FVector forward = camera->GetForwardVector();
	forward.Z = 0.0f;
	FVector Des = OwnerCharacter->GetActorLocation() + forward * TPDistance;
	OwnerCharacter->TeleportTo(Des, OwnerCharacter->GetActorRotation());
}

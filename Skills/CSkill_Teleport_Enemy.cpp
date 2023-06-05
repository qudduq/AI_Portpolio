// Fill out your copyright notice in the Description page of Project Settings.


#include "Skills/CSkill_Teleport_Enemy.h"
#include "Enemy/CAIController.h"
#include "Utillities/CLog.h"

FVector UCSkill_Teleport_Enemy::GetTeleportLocation()
{
	ACAIController* AIController = Cast<ACAIController>(OwnerCharacter->GetController());
	if(IsValid(AIController) == false)
	{
		CLog::Log("Enemy Teleport False");
		return OwnerCharacter->GetActorLocation();
	}

	return AIController->GetEQSPostion();
}

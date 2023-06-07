// Fill out your copyright notice in the Description page of Project Settings.


#include "Skills/CSkill_Teleport_Enemy.h"
#include "Enemy/CAIController.h"
#include "Enemy/CEnemy_AI.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "Utillities/CLog.h"

void UCSkill_Teleport_Enemy::BeginSkill()
{
	Super::BeginSkill();
	CLog::Log("Find Position EQS");
	if(ACEnemy_AI* enemy = Cast<ACEnemy_AI>(OwnerCharacter))
	{
		CLog::Log("Owner is Not Enemy_AI");
		return;
	}

	FEnvQueryRequest HidingSpotQueryRequest = FEnvQueryRequest(EQSOptionData, OwnerCharacter);
	HidingSpotQueryRequest.Execute(EEnvQueryRunMode::SingleResult, this, &UCSkill_Teleport_Enemy::EQSTeleport);
}

void UCSkill_Teleport_Enemy::EQSTeleport(TSharedPtr<FEnvQueryResult> result)
{
	if (result->IsSuccsessful())
	{
		auto pos = result->GetItemAsLocation(0);
		CLog::Log(pos);
		OwnerCharacter->TeleportTo(pos, OwnerCharacter->GetActorRotation());
	}
	else
	{
		CLog::Log("EQS Find False");
	}
}

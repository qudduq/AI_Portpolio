#include "Skills/CSkill_Teleport.h"

#include "Camera/CameraComponent.h"
#include "Character/CCharacter.h"
#include "Enemy/CEnemy.h"
#include "Player/CPlayer.h"
#include "Utillities/TaskHelper.h"

void UCSkill_Teleport::BeginSkill()
{
	Super::BeginSkill();

	//TODO : AI�� EQS�� Ȱ���Ͽ� �̵��Ҽ��ֵ��� ���ֱ�

	if(Cast<ACPlayer>(OwnerCharacter))
	{
		PlayerTeleport();
	}
	else if(Cast<ACEnemy>(OwnerCharacter))
	{
		AITeleport();
	}
}

void UCSkill_Teleport::PlayerTeleport()
{
	UCameraComponent* camera = TaskHelper::GetComponet<UCameraComponent>(OwnerCharacter);
	if(camera == nullptr)
	{
		return;
	}

	FVector forward = camera->GetForwardVector();
	FVector Des = OwnerCharacter->GetActorLocation() + forward * TPDistance;
	OwnerCharacter->TeleportTo(Des, OwnerCharacter->GetActorRotation());
}

void UCSkill_Teleport::AITeleport()
{
	// EQS ������
}

#include "CSkill_MagicBall.h"

#include "BezierShooter.h"
#include "Character/CCharacter.h"
#include "GameFramework/Character.h"
#include "Utillities/CLog.h"
#include "Utillities/TaskHelper.h"

void UCSkill_MagicBall::ExcuteSkill(ACharacter* InOwner)
{
	Super::ExcuteSkill(InOwner);

	// Object »õ¼º

	FVector Location = OwnerCharacter->GetMesh()->GetSocketLocation(SocketName);
	FTransform transform;
	transform.SetLocation(Location);
	Shooter = OwnerCharacter->GetWorld()->SpawnActorDeferred<ABezierShooter>(ShooterClass, transform, InOwner);
	Shooter->SetParticle(SkillData.Effect);
	Shooter->FinishSpawning(transform);
}

void UCSkill_MagicBall::BeginSkill()
{
	Super::BeginSkill();
	const FVector EnemyLocation = TaskHelper::GetCircleSearchCharacter(OwnerCharacter, Radius, EDrawDebugTrace::None);
	Shooter->BezierShoot(EnemyLocation,OwnerCharacter->GetActorLocation());
}


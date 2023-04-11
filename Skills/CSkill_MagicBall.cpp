#include "CSkill_MagicBall.h"

#include "BezierShooter.h"
#include "Character/CCharacter.h"
#include "Enemy/CEnemy.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Utillities/CLog.h"
#include "Particles/ParticleSystemComponent.h"

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
	const FVector EnemyLocation = GetEnemyLocation(OwnerCharacter);
	Shooter->BezierShoot(EnemyLocation,OwnerCharacter->GetActorLocation());
}

FVector UCSkill_MagicBall::GetEnemyLocation(ACharacter* InOwner) const
{
	FVector EnemyLocation;

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(InOwner);

	TArray<FHitResult> hitResults;
	
	UKismetSystemLibrary::SphereTraceMultiByProfile
	(
		InOwner->GetWorld(),
		InOwner->GetActorLocation(),
		InOwner->GetActorLocation(),
		Radius,
		"Enemy",
		false,
		ignoreActors,
		EDrawDebugTrace::None,
		hitResults,
		true
	);

	float CloseEnemyDistance = 1e9;
	for (const auto & hitresult : hitResults)
	{
		ACEnemy* enemy = Cast<ACEnemy>(hitresult.Actor);
		if (enemy != nullptr)
		{

			float distance = FVector::Distance(OwnerCharacter->GetActorLocation(), hitresult.ImpactPoint);
			if (CloseEnemyDistance > distance)
			{
				CloseEnemyDistance = distance;
				EnemyLocation = hitresult.ImpactPoint;
			}
		}
	}

	return EnemyLocation;
}


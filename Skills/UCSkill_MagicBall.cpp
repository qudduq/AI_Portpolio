#include "UCSkill_MagicBall.h"

#include "BezierShooter.h"
#include "Character/CCharacter.h"
#include "Enemy/CEnemy.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Utillities/CLog.h"

void UUCSkill_MagicBall::ExcuteSkill(ACharacter* InOwner)
{
	Super::ExcuteSkill(InOwner);

	// Object »õ¼º
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector Location = OwnerCharacter->GetMesh()->GetSocketLocation(SocketName);
	Shooter = OwnerCharacter->GetWorld()->SpawnActor<ABezierShooter>(ShooterClass, Location, FRotator::ZeroRotator, params);
}

void UUCSkill_MagicBall::BeginSkill()
{
	Super::BeginSkill();
	const FVector EnemyLocation = GetEnemyLocation(OwnerCharacter);
	Shooter->BezierShoot(EnemyLocation,OwnerCharacter->GetActorLocation());
}

FVector UUCSkill_MagicBall::GetEnemyLocation(ACharacter* InOwner) const
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

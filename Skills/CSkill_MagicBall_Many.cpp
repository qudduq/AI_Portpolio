#include "Skills/CSkill_MagicBall_Many.h"

#include "BezierShooter.h"
#include "Net/UnrealNetwork.h"
#include "Character/CCharacter.h"
#include "Utillities/TaskHelper.h"

void UCSkill_MagicBall_Many::ExcuteSkill(ACharacter* InOwner)
{
	if(Shooters.Num() > 0)
	{
		return;
	}

	Super::ExcuteSkill(InOwner);
}

void UCSkill_MagicBall_Many::BeginSkill()
{
	Super::BeginSkill();

	OwnerCharacter->GetWorld()->GetTimerManager().SetTimer
	(
		TimerHandle,
		FTimerDelegate::CreateLambda
		(
			[&]()
			{
				if(MaxShooterCount <= ShooterCount)
				{
					ShooterCount = 0;
					OwnerCharacter->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
				}

				SpawnShootActor();
				ShooterCount++;
			}
		), SpawnInterval, true
	);
}

void UCSkill_MagicBall_Many::ActiveSkill()
{
	Super::ActiveSkill();

	OwnerCharacter->GetWorld()->GetTimerManager().SetTimer
	(
		TimerHandle,
		FTimerDelegate::CreateLambda
		(
			[&]()
			{
				if(MaxShooterCount <= ShooterCount)
				{
					ShooterCount = 0;
					Shooters.Empty();
					OwnerCharacter->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
				}

				if(Shooters.Num() > 0)
				{
					FVector Dir = TaskHelper::GetCircleSearchCharacter(OwnerCharacter, Radius, EDrawDebugTrace::None);
					Shooters[ShooterCount]->BezierShoot(Dir, OwnerCharacter->GetActorLocation());
					ShooterCount++;
				}
			}
		), ShootInterval, true
	);
}

void UCSkill_MagicBall_Many::EndSkill(bool bHit)
{
	if(bHit)
	{
		for(auto & shoot : Shooters)
		{
			shoot->Destroy();
		}

		Shooters.Empty();
	}

	Super::EndSkill(bHit);
}

void UCSkill_MagicBall_Many::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UCSkill_MagicBall_Many, Shooters);
}

void UCSkill_MagicBall_Many::SpawnShootActor()
{
	FVector Location;

	Location = OwnerCharacter->GetActorLocation();
	Location -= OwnerCharacter->GetActorForwardVector() * 100;
	Location += OwnerCharacter->GetActorUpVector() * FMath::RandRange(VerticlaMin, VerticalMax);
	Location += OwnerCharacter->GetActorRightVector()* FMath::RandRange(HorizontamMin, HorizontalMax);

	FTransform transform;
	transform.SetLocation(Location);
	ABezierShooter* Shooter = OwnerCharacter->GetWorld()->SpawnActorDeferred<ABezierShooter>(ShooterClass, transform, OwnerCharacter);
	Shooter->SetParticle(SkillData.Effect);
	Shooter->FinishSpawning(transform);
	Shooters.Add(Shooter);
}


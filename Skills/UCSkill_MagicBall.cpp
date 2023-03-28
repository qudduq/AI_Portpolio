#include "UCSkill_MagicBall.h"

#include "BezierShooter.h"
#include "GameFramework/Character.h"

void UUCSkill_MagicBall::ExcuteSkill(ACharacter* InOwner)
{
	Super::ExcuteSkill(InOwner);

	//Shooter = InOwner->GetWorld()->SpawnActor(ShooterClass);
}

void UUCSkill_MagicBall::BeginSkill()
{
	Super::BeginSkill();
	//Shooter->BezierShoot()
}

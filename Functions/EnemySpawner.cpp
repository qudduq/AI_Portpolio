#include "EnemySpawner.h"
#include "Enemy/Enemy_Factory.h"

AEnemySpawner::AEnemySpawner()
{

}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &AEnemySpawner::EnemySpanwn, 2, true);
}

void AEnemySpawner::EnemySpanwn()
{
	if (EnemyCount >= 10)
		return;

	FVector location = GetActorLocation();
	location.X += FMath::RandRange(-500, 500);
	location.Y += FMath::RandRange(-500, 500);

	ACEnemy* enemy = nullptr;

	int setnum = FMath::RandRange(0, 3);

	switch (setnum)
	{
	case 0: enemy = Enemy_Factory::White (Enemy,GetWorld(),location); break;
	case 1: enemy = Enemy_Factory::Red   (Enemy,GetWorld(),location); break;
	case 2: enemy = Enemy_Factory::Blue  (Enemy,GetWorld(),location); break;
	case 3: enemy = Enemy_Factory::Black (Enemy,GetWorld(),location); break;
	}

	enemy->SpawnDefaultController();
	
	EnemyCount++;
	CLog::Log(EnemyCount);
}



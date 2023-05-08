#include "CEnemy.h"
#include "Utillities/CLog.h"
#include "Components/CWeaponComponent.h"
#include "Kismet/KismetMathLibrary.h"


ACEnemy::ACEnemy()
{

}

void ACEnemy::Attach_Weapon(EWeaponType weapon)
{
	Weapon->SpawnWeapon(weapon);
}

float ACEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float rtDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (EventInstigator != nullptr)
	{
		ACCharacter* Opponent = Cast<ACCharacter>(EventInstigator->GetPawn());
		FRotator lookRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Opponent->GetActorLocation());
		SetActorRotation(lookRotation);
	}
	return rtDamage;
}






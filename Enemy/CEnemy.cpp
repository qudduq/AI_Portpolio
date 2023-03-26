#include "CEnemy.h"
#include "Utillities/CLog.h"
#include "Components/CWeaponComponent.h"


ACEnemy::ACEnemy()
{

}

void ACEnemy::Attach_Weapon(EWeaponType weapon)
{
	Weapon->SpawnWeapon(weapon);
}






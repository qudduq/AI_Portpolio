#pragma once

#include "CoreMinimal.h"
#include "CEnemy.h"
#include "EnemyRaceData.h"
#include "Components/CWeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Utillities/CLog.h"

//TODO : 에너미 팩토리 조절하기
// 무기타입에따라서 알맞은 무기소환해주기 굳이 클래스를또 뺄필요가 없어보임 수정요망
class EnemyClass_Factory
{
public:
	static void Normal(ACEnemy* enemy)
	{

		return;
	}

	static void Sword(ACEnemy* enemy)
	{
		enemy->Attach_Weapon(EWeaponType::OneHand);
		
		//(*enemy)->Weapon->SetOneHandMode();

		return;
	}

	static void Bow(ACEnemy* enemy)
	{
		enemy->Attach_Weapon(EWeaponType::Bow);
		//enemy->Controller = aicontroller;
		//(*enemy)->Weapon->SetBowMode();

		return;
	}

};

class AI_PORTPOLIO_API Enemy_Factory
{
public:
	static ACEnemy* White(UClass* Class, UWorld* world, FVector location, EWeaponType Type = EWeaponType::Max)
	{
		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

		ACEnemy* Enemy = world->SpawnActor<ACEnemy>(Class, location, FRotator::ZeroRotator, params);
		if (Enemy == nullptr) 
			return nullptr;

		FEnemyRace racedata = Enemy->RaceData->RaceData[(int32)ERaceType::White];
		Enemy->GetMesh()->SetSkeletalMesh(racedata.RaceMesh);
		Enemy->GetMesh()->SetAnimInstanceClass(racedata.AnimInstance);

		
		Type = EWeaponType::Max == Type ? static_cast<EWeaponType>(FMath::RandRange(0, 2)) : Type;

		switch (Type)
		{
		case EWeaponType::Unarmed: EnemyClass_Factory::Normal(Enemy); break;
		case EWeaponType::OneHand: EnemyClass_Factory::Sword(Enemy); break;
		case EWeaponType::Bow : EnemyClass_Factory::Bow(Enemy); break;
		}
		

		return Enemy;
	}

	static ACEnemy* Red(UClass* Class, UWorld* world, FVector location, EWeaponType Type = EWeaponType::Max)
	{
		FActorSpawnParameters params;

		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
		ACEnemy* Enemy = world->SpawnActor<ACEnemy>(Class, location, FRotator::ZeroRotator, params);

		if (Enemy == nullptr) return nullptr;

		FEnemyRace racedata = Enemy->RaceData->RaceData[(int32)ERaceType::White];
		(Enemy)->GetMesh()->SetSkeletalMesh(racedata.RaceMesh);
		(Enemy)->GetMesh()->SetAnimInstanceClass(racedata.AnimInstance);

		if (Type == EWeaponType::Max)
		{
			int setnum = FMath::RandRange(0, 2);

			switch (setnum)
			{
			case 0: EnemyClass_Factory::Normal(Enemy); break;
			case 1: EnemyClass_Factory::Sword(Enemy); break;
			case 2: EnemyClass_Factory::Bow(Enemy); break;
			}
		}

		return Enemy;
	}

	static ACEnemy* Blue(UClass* Class, UWorld* world, FVector location, EWeaponType Type = EWeaponType::Max)
	{
		FActorSpawnParameters params;

		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
		ACEnemy* Enemy = world->SpawnActor<ACEnemy>(Class, location, FRotator::ZeroRotator, params);

		if (Enemy == nullptr) return nullptr;

		FEnemyRace racedata = Enemy->RaceData->RaceData[(int32)ERaceType::White];
		(Enemy)->GetMesh()->SetSkeletalMesh(racedata.RaceMesh);
		(Enemy)->GetMesh()->SetAnimInstanceClass(racedata.AnimInstance);

		if (Type == EWeaponType::Max)
		{
			int setnum = FMath::RandRange(0, 2);

			switch (setnum)
			{
			case 0: EnemyClass_Factory::Normal(Enemy); break;
			case 1: EnemyClass_Factory::Sword(Enemy); break;
			case 2: EnemyClass_Factory::Bow(Enemy); break;
			}
		}

		return Enemy;
	}

	static ACEnemy* Black(UClass* Class, UWorld* world, FVector location, EWeaponType Type = EWeaponType::Max)
	{
		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

		ACEnemy* Enemy = world->SpawnActor<ACEnemy>(Class, location, FRotator::ZeroRotator, params);

		if (Enemy == nullptr) return nullptr;

		FEnemyRace racedata = Enemy->RaceData->RaceData[(int32)ERaceType::White];
		(Enemy)->GetMesh()->SetSkeletalMesh(racedata.RaceMesh);
		(Enemy)->GetMesh()->SetAnimInstanceClass(racedata.AnimInstance);

		if (Type == EWeaponType::Max)
		{
			int setnum = FMath::RandRange(0, 2);

			switch (setnum)
			{
			case 0: EnemyClass_Factory::Normal(Enemy); break;
			case 1: EnemyClass_Factory::Sword(Enemy); break;
			case 2: EnemyClass_Factory::Bow(Enemy); break;
			}
		}

		return Enemy;
	}

};




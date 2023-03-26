#include "CCharacter.h"

#include "Camera/CameraComponent.h"
#include "Camera/CameraModifier_CameraShake.h"
#include "Components/SkeletalMeshComponent.h"
#include "Weapon/UCWeaponStructure.h"
#include "Components/CStatusComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CWeaponComponent.h"
#include "Components/CSkillComponent.h"
#include "Camera/CameraShake.h"
#include "Manager/CameraShakeManager.h"
#include "Utillities/CLog.h"

ACCharacter::ACCharacter()
{
	State = CreateDefaultSubobject<UCStateComponent>("State");
	Status = CreateDefaultSubobject<UCStatusComponent>("Status");
	Weapon = CreateDefaultSubobject<UCWeaponComponent>("Weapon");
	Skill = CreateDefaultSubobject<UCSkillComponent>("Skill");

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FQuat(FRotator(0, -90, 0)));
}

float ACCharacter::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	DamageData = (FDamageData*)&DamageEvent;


	//대미지가 들어온경우
	State->SetHittedMode();
	CameraShaking();
	HitStop(EventInstigator);

	return Damage;
}

void ACCharacter::BeginPlay()
{
	Super::BeginPlay();

	State->RegisterDelegate(FStateTypeChanged::FDelegate::CreateUObject(this, &ACCharacter::OnStateTypeChanged));

	if(HitData == nullptr)
	{
		FString outStr = GetName();
		outStr += " Not Setting HitDataAsset";
		CLog::Log(outStr);
	}
}

void ACCharacter::OnStateTypeChanged(EStateType Type)
{
	switch (Type)
	{
	case EStateType::Hitted: Hitted(); break;
	case EStateType::Dead: Dead(); break;
	}
}

void ACCharacter::Hitted()
{
	Status->Hit(DamageData->Damage);

	if (Status->GetHealth() == 0)
	{
		State->SetDeadMode();
		return;
	}

	if(OnCharacterHit.IsBound())
	{
		OnCharacterHit.Broadcast();
	}

	EDamageType type = DamageData->Type;
	switch (type)
	{
	case EDamageType::Normal: Normal_Hit(type); break;
	case EDamageType::FlyAway: Fly_Hit(type); break;
	case EDamageType::Stun:; break;
	}

}

void ACCharacter::HitStop(AController* AttackerController)
{
	if (DamageData->StopTime == 0)
		return;

	AttackerController->GetCharacter()->CustomTimeDilation = 0.01f;
	CustomTimeDilation = 0.01f;

	GetWorld()->GetTimerManager().SetTimer
	(TimerHandle,
		FTimerDelegate::CreateLambda
		(
			[=]()
			{
				AttackerController->GetCharacter()->CustomTimeDilation = 1.0f;
				CustomTimeDilation = 1.0f;
				GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
			}
		), DamageData->StopTime, false
	);
}

void ACCharacter::CameraShaking()
{
	if (DamageData->CameraShake == nullptr)
		return;

	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	controller->PlayerCameraManager->PlayCameraShake(DamageData->CameraShake);
}

void ACCharacter::End_Hitted()
{
	State->SetIdleMode();
}

void ACCharacter::Normal_Hit(EDamageType Type)
{
	UAnimMontage* montage = HitData->GetHitData(Type).Montage;
	if (montage == nullptr) return;

	PlayAnimMontage(montage);
}

void ACCharacter::Fly_Hit(EDamageType Type)
{
	UAnimMontage* montage = HitData->GetHitData(Type).Montage;
	if (montage == nullptr) return;

	PlayAnimMontage(montage);
}



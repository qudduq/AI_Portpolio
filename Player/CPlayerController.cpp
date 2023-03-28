#include "Player/CPlayerController.h"

#include "CPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CQuickSlotComponent.h"
#include "Components/CSkillComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/CWeaponComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Utillities/CLog.h"
#include "Widget/CListView.h"

ACPlayerController::ACPlayerController()
{
}

void ACPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("Forward", this, &ACPlayerController::MoveForward);
	InputComponent->BindAxis("Right", this, &ACPlayerController::MoveRight);
	InputComponent->BindAxis("CameraRight", this, &ACPlayerController::CameraYaw);

	InputComponent->BindAction("ChangeWeapon", IE_Pressed, this, &ACPlayerController::ChangeWeapon);
	InputComponent->BindAction("ChangeView",IE_Pressed, this, &ACPlayerController::ChangeView);
	InputComponent->BindAction("Action", IE_Pressed, this, &ACPlayerController::DoAction);
	InputComponent->BindAction("SkillList", IE_Pressed, this, &ACPlayerController::CLickSkillList);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACPlayerController::Jump);

	//Key값이 추가로 입력되고있음
	InputComponent->BindAction("QuickSlot", IE_Pressed, this, &ACPlayerController::QuickSlot);
}

void ACPlayerController::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<ACPlayer>(GetPawn());
}

void ACPlayerController::MoveForward(float Axis)
{
	UCStatusComponent* Status = Cast<UCStatusComponent>(Player->GetComponentByClass(UCStatusComponent::StaticClass()));
	if(Status == nullptr)
		return;

	if (Status->IsMove() == false)
		return;

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Dir = FQuat(rotator).GetForwardVector();

	GetPawn()->AddMovementInput(Dir, Axis);
}

void ACPlayerController::MoveRight(float Axis)
{
	UCStatusComponent* Status = Cast<UCStatusComponent>(Player->GetComponentByClass(UCStatusComponent::StaticClass()));
	if (Status == nullptr)
		return;

	if (Status->IsMove() == false)
		return;

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Dir = FQuat(rotator).GetRightVector();

	GetPawn()->AddMovementInput(Dir, Axis);
}

void ACPlayerController::CameraYaw(float Axis)
{
	if (bQuterView == false || bMouse == true)
		return;

	if (Axis != 0.f && IsLocalPlayerController())
	{
		AddYawInput(Axis);
	}
}

void ACPlayerController::ChangeView()
{
	bQuterView = !bQuterView;

	USpringArmComponent* SpringArmComponent = Cast<USpringArmComponent>(Player->GetComponentByClass(USpringArmComponent::StaticClass()));
	if(SpringArmComponent == nullptr)
	{
		return;
	}

	if (bQuterView)
		SpringArmComponent->TargetArmLength = 800.0f;
	else
		SpringArmComponent->TargetArmLength = 600.0f;

	camera_count = 13;

	GetWorldTimerManager().SetTimer
	(
		handle, this, 
		&ACPlayerController::MoveCamera, 
		GetWorld()->GetDeltaSeconds(), 
		true
	);
}

void ACPlayerController::MoveCamera()
{
	if (--camera_count <= 0)
	{
		GetWorldTimerManager().ClearTimer(handle);
	}

	float axis = 0;

	bQuterView ? axis = 1.0f : axis = -1.0f;

	AddPitchInput(axis);
}

void ACPlayerController::ChangeWeapon()
{
	if (isChanging || bMouse)
		return;

	isChanging = true;

	weaponnum++;
	weaponnum >= (int)EWeaponType::Max ? weaponnum = 0 : weaponnum;
	CLog::Log(weaponnum);
	UCWeaponComponent* Weapon = Cast<UCWeaponComponent>(Player->GetComponentByClass(UCWeaponComponent::StaticClass()));
	if(Weapon == nullptr)
	{
		return;
	}

	switch (weaponnum)
	{
	case 0: Weapon->SetUnarmedMode();
		break;
	case 1: Weapon->SetOneHandMode();
		break;
	case 2: Weapon->SetBowMode();
		break;
	}

	UCSkillComponent* Skill = Cast<UCSkillComponent>(Player->GetComponentByClass(UCSkillComponent::StaticClass()));
	if(Skill == nullptr)
	{
		return;
	}
	Player->GetSkillList()->SetSKills(Skill->GetSkillData());
	isChanging = false;
}

void ACPlayerController::MouseView()
{
	bMouse = !bMouse;
	SetShowMouseCursor(bMouse);
}

void ACPlayerController::DoAction()
{
	if (bMouse)
	{
		return;
	}

	UCWeaponComponent* Weapon = Cast<UCWeaponComponent>(Player->GetComponentByClass(UCWeaponComponent::StaticClass()));
	if(Weapon == nullptr)
	{
		return;
	}
	Weapon->DoAction();
}

void ACPlayerController::QuickSlot(const FKey SetNum)
{
	if (bMouse)
	{
		return;
	}

	UCQuickSlotComponent* QuickSlot = Cast<UCQuickSlotComponent>(Player->GetComponentByClass(UCQuickSlotComponent::StaticClass()));
	if(QuickSlot == nullptr)
	{
		return;
	}
	QuickSlot->QuickSlotCall(SetNum);
}

void ACPlayerController::CLickSkillList()
{
	bSkillList = !bSkillList;

	if (bSkillList)
		Player->GetSkillList()->COpenSkills();
	else
		Player->GetSkillList()->CCloseSkills();

	MouseView();
}

void ACPlayerController::Jump()
{
	Player->Jump();
}

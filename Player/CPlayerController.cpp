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
#include "Utillities/TaskHelper.h"
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

	//매개변수로 해당 Key값이 입력되고있습니다.
	InputComponent->BindAction("QuickSlot", IE_Pressed, this, &ACPlayerController::QuickSlotCall);
}

ACPlayer* ACPlayerController::CheckPlayer()
{
	ACPlayer* CPlayer = Cast<ACPlayer>(GetPawn());
	if (CPlayer == nullptr)
	{
		FString str = "";
		str += GetName();
		str += " Not possessed by a player";
		CLog::Log(str);
		return nullptr;
	}

	return CPlayer;
}

void ACPlayerController::MoveForward(float Axis)
{
	ACPlayer* CPlayer = CheckPlayer();
	if (CPlayer == nullptr)
	{
		return;
	}

	UCStatusComponent* Status = TaskHelper::GetComponet<UCStatusComponent>(CPlayer);
	if (Status == nullptr)
	{
		return;
	}

	if (Status->IsMove() == false)
	{
		CLog::Log("Current is Don't Move");
		return;
	}

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Dir = FQuat(rotator).GetForwardVector();

	GetPawn()->AddMovementInput(Dir, Axis);
}

void ACPlayerController::MoveRight(float Axis)
{
	ACPlayer* CPlayer = CheckPlayer();
	if (CPlayer == nullptr)
	{
		return;
	}

	UCStatusComponent* Status = TaskHelper::GetComponet<UCStatusComponent>(CPlayer);
	if (Status == nullptr)
	{
		return;
	}

	if (Status->IsMove() == false)
	{
		CLog::Log("Current is Don't Move");
		return;
	}

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Dir = FQuat(rotator).GetRightVector();

	GetPawn()->AddMovementInput(Dir, Axis);
}

void ACPlayerController::CameraYaw(float Axis)
{
	ACPlayer* CPlayer = CheckPlayer();
	if (CPlayer == nullptr)
	{
		return;
	}

	if (bQuterView == false || bMouse == true)
		return;

	if (Axis != 0.f && IsLocalPlayerController())
	{
		AddYawInput(Axis);
	}
}

void ACPlayerController::ChangeView()
{
	ACPlayer* CPlayer = CheckPlayer();
	if (CPlayer == nullptr)
	{
		return;
	}

	bQuterView = !bQuterView;

	USpringArmComponent* SpringArmComponent = TaskHelper::GetComponet<USpringArmComponent>(CPlayer);
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
	ACPlayer* CPlayer = CheckPlayer();
	if (CPlayer == nullptr)
	{
		return;
	}

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
	ACPlayer* CPlayer = CheckPlayer();
	if (CPlayer == nullptr)
	{
		return;
	}

	if (isChanging || bMouse)
		return;

	isChanging = true;

	weaponnum++;
	weaponnum >= (int)EWeaponType::Max ? weaponnum = 0 : weaponnum;
	CLog::Log(weaponnum);

	UCWeaponComponent* Weapon = TaskHelper::GetComponet<UCWeaponComponent>(CPlayer);
	if(Weapon == nullptr)
	{
		return;
	}
	UCSkillComponent* Skill = TaskHelper::GetComponet<UCSkillComponent>(CPlayer);
	if (Skill == nullptr)
	{
		return;
	}

	//무기의 상태 변경과 현재 스킬목록을 리스트뷰에 넘기기 위해서 스킬을 무기에 맞게 세팅해주었습니다.
	switch (weaponnum)
	{
	case 0: 
		Weapon->SetUnarmedMode();
		break;
	case 1: 
		Weapon->SetOneHandMode();
		break;
	case 2: 
		Weapon->SetBowMode();
		break;
	case 3:
		Weapon->SetMageMode();
		break;
	}

	CPlayer->GetSkillList()->SetSKills(Skill->GetSkillArrayData(static_cast<EWeaponType>(weaponnum)));
	isChanging = false;
}

void ACPlayerController::MouseView()
{
	ACPlayer* CPlayer = CheckPlayer();
	if (CPlayer == nullptr)
	{
		return;
	}

	bMouse = !bMouse;
	SetShowMouseCursor(bMouse);
}

void ACPlayerController::DoAction()
{
	ACPlayer* CPlayer = CheckPlayer();
	if (CPlayer == nullptr)
	{
		return;
	}

	if (bMouse)
	{
		return;
	}

	UCWeaponComponent* Weapon = TaskHelper::GetComponet<UCWeaponComponent>(CPlayer);
	if(Weapon == nullptr)
	{
		return;
	}
	Weapon->DoAction();
}

void ACPlayerController::ServerQuickSlotCall(const FKey SetNum)
{
	ACPlayer* CPlayer = CheckPlayer();
	if (CPlayer == nullptr)
	{
		return;
	}

	if (bMouse)
	{
		return;
	}

	auto testid = typeid(UCQuickSlotComponent).name();

	UCQuickSlotComponent* QuickSlot = TaskHelper::GetComponet<UCQuickSlotComponent>(CPlayer);
	if(QuickSlot == nullptr)
	{
		return;
	}

	QuickSlot->QuickSlotCall(SetNum);
}

void ACPlayerController::QuickSlotCall(const FKey SetKey)
{
	ServerQuickSlotCall(SetKey);
}

void ACPlayerController::CLickSkillList()
{
	ACPlayer* CPlayer = CheckPlayer();
	if (CPlayer == nullptr)
	{
		return;
	}

	bSkillList = !bSkillList;

	if (bSkillList)
		CPlayer->GetSkillList()->COpenSkills();
	else
		CPlayer->GetSkillList()->CCloseSkills();

	MouseView();
}

void ACPlayerController::Jump()
{
	ACPlayer* CPlayer = CheckPlayer();
	if (CPlayer == nullptr)
	{
		return;
	}

	CPlayer->Jump();
}

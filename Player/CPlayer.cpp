#include "CPlayer.h"
#include "Utillities/CLog.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CWeaponComponent.h"
#include "Components/CSkillComponent.h"
#include "Widget/CListView.h"
#include "Widget/CQuickSlotBar_Widget.h"
#include "Engine/StreamableManager.h"
#include "Skills/BezierTest.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CQuickSlotComponent.h"


ACPlayer::ACPlayer()
{
	QuickSlot = CreateDefaultSubobject<UCQuickSlotComponent>("QuickSlot");

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeLocation(FVector(0,30,13));
	SpringArm->SetRelativeRotation(FQuat(FRotator(0, 0, 0)));
	SpringArm->TargetArmLength = 400.0f;

	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->SetRelativeRotation(FQuat(FRotator(0,0,0)));

	GetCharacterMovement()->bOrientRotationToMovement = true;

	SkillListWidget = UCListView::StaticClass();
	QuickSlotBarWidget = UCQuickSlotBar_Widget::StaticClass();
	Bezier = ABezierTest::StaticClass();
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	SkillList = Cast<UCListView>(CreateWidget(GetWorld(), SkillListWidget));
	QuickSlotBar = Cast<UCQuickSlotBar_Widget>(CreateWidget(GetWorld(), QuickSlotBarWidget));

	if (SkillList != nullptr)
		SkillList->AddToViewport();

	if (QuickSlotBar != nullptr)
		QuickSlotBar->AddToViewport();

	SkillList->CCloseSkills();
	Weapon->SetUnarmedMode();

	if(Bezier != nullptr)
	{
		FActorSpawnParameters param;
		BezierObj = Cast<ABezierTest>(GetWorld()->SpawnActor(Bezier));
		BezierObj->AttachToActor(this,FAttachmentTransformRules::KeepRelativeTransform);
		BezierObj->SetActorLocation(GetActorLocation() + FVector(0, 100, 0));
	}

	
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//플레이어컨트롤러로 이동시키기(pawn 확인해주기)
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump",IE_Pressed ,this, &ACPlayer::OnJump);
	PlayerInputComponent->BindAction("ChangeView", IE_Pressed, this, &ACPlayer::ChangeView);
	PlayerInputComponent->BindAction("ChangeWeapon", IE_Pressed, this, &ACPlayer::ChangeWeapon);
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &ACPlayer::DoAction);
	//FKey를 이용하여 하나로 퉁칠수있음
	PlayerInputComponent->BindAction("OnQuickSlot", IE_Pressed, this, &ACPlayer::OnQuickSlot);

	PlayerInputComponent->BindAction("ClickSkill", IE_Pressed, this, &ACPlayer::CLickSkillList);

	{
		PlayerInputComponent->BindAction("Test", IE_Pressed, this, &ACPlayer::SetTest1);
		PlayerInputComponent->BindAction("Test", IE_Released, this, &ACPlayer::SetTest2);
	}

	PlayerInputComponent->BindAxis("Forward", this, &ACPlayer::Forward);
	PlayerInputComponent->BindAxis("Right", this, &ACPlayer::Right);

	PlayerInputComponent->BindAxis("CameraRight", this, &ACPlayer::CameraYaw);
}

void ACPlayer::Forward(float Axis)
{
	FRotator rotator = FRotator(0, Controller->GetControlRotation().Yaw, 0);
	FVector Dir = FQuat(rotator).GetForwardVector();

	AddMovementInput(Dir, Axis);
}

void ACPlayer::Right(float Axis)
{
	FRotator rotator = FRotator(0, Controller->GetControlRotation().Yaw, 0);
	FVector Dir = FQuat(rotator).GetRightVector();

	AddMovementInput(Dir, Axis);
}

void ACPlayer::CameraPitch(float Axis)
{
	if (bQuterView == false)
		return;

	if (Axis != 0.f && Controller && Controller->IsLocalPlayerController())
	{
		APlayerController* const PC = CastChecked<APlayerController>(Controller);
		PC->AddPitchInput(Axis);
	}
}

void ACPlayer::CameraYaw(float Axis)
{
	if (bQuterView == false)
		return;

	if (Axis != 0.f && Controller && Controller->IsLocalPlayerController())
	{
		APlayerController* const PC = CastChecked<APlayerController>(Controller);
		PC->AddYawInput(Axis);
	}
}

void ACPlayer::OnJump()
{
	Jump();
}

void ACPlayer::ChangeView()
{
	bQuterView = !bQuterView;

	if (bQuterView)
		SpringArm->TargetArmLength = 800.0f;
	else
		SpringArm->TargetArmLength = 600.0f;

	//CLog::Print(SpringArm->TargetArmLength, 1);
	camera_count = 13;
	GetWorldTimerManager().SetTimer(handle, this, &ACPlayer::MoveCamera, GetWorld()->GetDeltaSeconds(), true);
}

void ACPlayer::MoveCamera()
{
	if (--camera_count <= 0)
		GetWorldTimerManager().ClearTimer(handle);

	float axis = 0;

	bQuterView ? axis = 1 : axis = -1 ;

	APlayerController* const PC = CastChecked<APlayerController>(Controller);
	PC->AddPitchInput(axis);
}

void ACPlayer::MouseView()
{
	bMouse = !bMouse;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(bMouse);
	
}

void ACPlayer::ChangeWeapon()
{
	if (isChanging || bMouse)
		return;

	isChanging = true;

	weaponnum++;
	weaponnum >= (int)EWeaponType::Max ? weaponnum = 0 : weaponnum;
	CLog::Log(weaponnum);

	switch (weaponnum)
	{
	case 0: Weapon->SetUnarmedMode();
		break;
	case 1: Weapon->SetOneHandMode();
		break;
	case 2: Weapon->SetBowMode();
		break;
	}

	SkillList->SetSKills(Skill->GetSkillData());
	isChanging = false;

}

void ACPlayer::DoAction()
{
	if (bMouse) return;

	Weapon->DoAction();
}

void ACPlayer::OnQuickSlot(const FKey SetNum)
{
	if (bMouse) return;
	
	QuickSlot->QuickSlotCall(SetNum);
}

void ACPlayer::SetTest1()
{
	FHitResult HitResult;
	TArray<AActor*> ignores;
	ignores.Add(this);

	FVector Start = GetActorLocation() + (GetActorForwardVector() * 100);
	FVector End = GetActorLocation() + (GetActorForwardVector() * 1000);

	UKismetSystemLibrary::BoxTraceSingle
	(
		GetWorld(),
		Start,
		End,
		FVector(10, 10, 10),
		FRotator(),
		ETraceTypeQuery::TraceTypeQuery7,
		false,
		ignores,
		EDrawDebugTrace::ForDuration,
		HitResult,
		true
	);

	if (Cast<ACCharacter>(HitResult.Actor) != nullptr)
	{
		Enemylocation = HitResult.Location;
		bHit = true;
	}

}

void ACPlayer::SetTest2()
{
	if(bHit == false)
		return;

	BezierObj->DetachRootComponentFromParent();
	BezierObj->BezierShoot(Enemylocation, GetActorLocation());
}

void ACPlayer::CLickSkillList()
{
	bSkillList = !bSkillList;

	if (bSkillList)
		SkillList->COpenSkills();
	else
		SkillList->CCloseSkills();

	MouseView();
}







#include "CPlayer.h"

#include "CPlayerController.h"
#include "Utillities/CLog.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CWeaponComponent.h"
#include "Widget/CListView.h"
#include "Widget/CQuickSlotBar_Widget.h"
#include "Engine/StreamableManager.h"
#include "Components/CQuickSlotComponent.h"
#include "Components/CSkillComponent.h"


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
}

void ACPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
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
	SkillList->SetSKills(Skill->GetSkillData(EWeaponType::Unarmed));
}










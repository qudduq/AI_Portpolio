#include "CAnimInstance.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "Utillities/CLog.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	if (OwnerCharacter == nullptr)
		return;

	Weapon = Cast<UCWeaponComponent>(OwnerCharacter->GetComponentByClass(UCWeaponComponent::StaticClass()));

	if (Weapon != nullptr)
		Weapon->OnWeaponTypeChanged.Add(FWeaponTypeChanged::FDelegate::CreateUObject(this,&UCAnimInstance::OnWeaponTypeChanged));

}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);	
	if (OwnerCharacter == nullptr)
		return;

	Speed = OwnerCharacter->GetVelocity().Size2D();
	Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation());
	Pitch = OwnerCharacter->GetBaseAimRotation().Pitch;
}

void UCAnimInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UCAnimInstance, WeaponType);
}

void UCAnimInstance::OnWeaponTypeChanged(EWeaponType InNewType)
{
	WeaponType = InNewType;
}


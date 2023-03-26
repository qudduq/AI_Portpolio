#include "CAnimInstance.h"
#include "GameFramework/Character.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	if (OwnerCharacter == NULL)
		return;

	Weapon = Cast<UCWeaponComponent>(OwnerCharacter->GetComponentByClass(UCWeaponComponent::StaticClass()));

	if (!!Weapon)
		Weapon->OnWeaponTypeChanged.Add(FWeaponTypeChanged::FDelegate::CreateUObject(this,&UCAnimInstance::OnWeaponTypeChanged));

}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (OwnerCharacter == NULL)
		return;

	Speed = OwnerCharacter->GetVelocity().Size2D();
	Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation());
	Pitch = OwnerCharacter->GetBaseAimRotation().Pitch;

}

void UCAnimInstance::OnWeaponTypeChanged(EWeaponType InNewType)
{
	WeaponType = InNewType;
}


#include "Components/CStatusComponent.h"
#include "GameFramework/Character.h"

UCStatusComponent::UCStatusComponent()
{
}


void UCStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	Energy = MaxEnergy;

	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void UCStatusComponent::Hit(float InAmount)
{
	Health -= InAmount;
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);
}

void UCStatusComponent::Energing(float InAmount)
{
	Energy -= InAmount;
	Energy = FMath::Clamp(Health, 0.0f, MaxEnergy);
}


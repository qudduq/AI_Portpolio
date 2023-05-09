#include "CSkill_GroundCircle_Many.h"

#include "GroundIce.h"
#include "Character/CCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Skills/GroundIce.h"

UCSkill_GroundCircle_Many::UCSkill_GroundCircle_Many()
{
}

void UCSkill_GroundCircle_Many::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UCSkill_GroundCircle_Many, Ices);
}

void UCSkill_GroundCircle_Many::BeginSkill()
{
	Super::BeginSkill();
	count = 0;
	Locations.Empty();
	Ices.Empty();

	OwnerCharacter->GetWorld()->GetTimerManager().SetTimer
	(
		TimerHandle,
		FTimerDelegate::CreateLambda
		(
			[&]()
			{
				count++;
				if(count > CircleCount)
				{
					OwnerCharacter->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
				}

				FVector Location;

				int random = FMath::RandRange(0, 360);
				int ranDir = FMath::RandRange(MinDistance, MaxDistance);
				Location.Z = OwnerCharacter->GetActorLocation().Z - 30;
				Location.X = OwnerCharacter->GetActorLocation().X + ranDir * FMath::Cos(random);
				Location.Y = OwnerCharacter->GetActorLocation().Y + ranDir * FMath::Sin(random);
				Locations.Add(Location);
				PlaySkillEffect(OwnerCharacter->GetWorld(), Location);
			}
		), 0.05, true
	);

}

void UCSkill_GroundCircle_Many::ActiveSkill()
{
	Super::ActiveSkill();
	OffSkillEffect();

	for(const auto& Location: Locations)
	{
		if (IceClass != nullptr)
		{
			FTransform Transform;
			Transform.SetLocation(Location);
			AGroundIce* Ice = OwnerCharacter->GetWorld()->SpawnActorDeferred<AGroundIce>(IceClass, Transform, OwnerCharacter);
			Ice->SetDamageData(SkillData.DamageData);
			Ice->SetReplicates(true);
			Ice->FinishSpawning(Transform);
			Ices.Add(Ice);
		}
	}

}
	



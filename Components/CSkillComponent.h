#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Skills/CSkill.h"
#include "CWeaponComponent.h"
#include "CSkillComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnBeginSkill);
DECLARE_MULTICAST_DELEGATE(FOnEndSkill);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AI_PORTPOLIO_API UCSkillComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Replicated)
		class UCSkillData* SkillDataAssets[(int32)EWeaponType::Max];

public:	
	UCSkillComponent();

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty > & OutLifetimeProps) const override;
protected:
	virtual void BeginPlay() override;

public:	
	const  TMap<FName, UCSkill*>& GetSkillMapData(EWeaponType WeaponType);
	const TArray<UCSkill*>& GetSkillArrayData(EWeaponType WeaponType);
	void BeginSkill();
	void EndSkill();

public:
	void ExcuteSkill(FName SkillID);

public:
	FOnBeginSkill OnBeginSkill;
	FOnEndSkill OnEndSkill;

};

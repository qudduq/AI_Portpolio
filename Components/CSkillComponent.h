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
	UPROPERTY(EditDefaultsOnly)
		class UCSkillData* SkillDataAssets[(int32)EWeaponType::Max];

public:	
	UCSkillComponent();

protected:
	virtual void BeginPlay() override;

public:
	//퀵스킬로 스킬발동시 서버간에 퀵슬롯데이터를 중복하지않고 해당 id를 얻어서 알맞는 스킬을 선택하게해줍니다.
	UCSkill* GetSkillData(EWeaponType WeaponType, FName ID);

	//데이터에셋으로부터 알맞는 스킬데이터를 얻어옵니다.
	const TArray<UCSkill*>& GetSkillArrayData(EWeaponType WeaponType) const;

	//스킬발동시 FOnBeginSkill델리게이트에 등록된 함수를 콜합니다.
	//몽타쥬에서 특정 시간에 콜할수 있습니다.
	void BeginSkill();

	//스킬이 끝나갈때 FOnEndSkill델리게이트에 등록된 함수를 콜합니다.
	void EndSkill();

public:
	// 스킬발동은 서버에서만 이루어질수있도록 설정하였습니다.
	// 검증을 추가하였습니다.
	UFUNCTION(Reliable, Server, WithValidation)
		void ExcuteSkill(FName SkillID);

public:
	FOnBeginSkill OnBeginSkill;
	FOnEndSkill OnEndSkill;

};

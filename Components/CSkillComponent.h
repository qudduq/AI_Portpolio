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
	//����ų�� ��ų�ߵ��� �������� �����Ե����͸� �ߺ������ʰ� �ش� id�� �� �˸´� ��ų�� �����ϰ����ݴϴ�.
	UCSkill* GetSkillData(EWeaponType WeaponType, FName ID);

	//�����Ϳ������κ��� �˸´� ��ų�����͸� ���ɴϴ�.
	const TArray<UCSkill*>& GetSkillArrayData(EWeaponType WeaponType) const;

	//��ų�ߵ��� FOnBeginSkill��������Ʈ�� ��ϵ� �Լ��� ���մϴ�.
	//��Ÿ�꿡�� Ư�� �ð��� ���Ҽ� �ֽ��ϴ�.
	void BeginSkill();

	//��ų�� �������� FOnEndSkill��������Ʈ�� ��ϵ� �Լ��� ���մϴ�.
	void EndSkill();

public:
	// ��ų�ߵ��� ���������� �̷�������ֵ��� �����Ͽ����ϴ�.
	// ������ �߰��Ͽ����ϴ�.
	UFUNCTION(Reliable, Server, WithValidation)
		void ExcuteSkill(FName SkillID);

public:
	FOnBeginSkill OnBeginSkill;
	FOnEndSkill OnEndSkill;

};

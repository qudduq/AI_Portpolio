#include "Components/CWeaponComponent.h"

#include "Character/CCharacter.h"
#include "Utillities/CLog.h"
#include "GameFramework/Character.h"
#include "CStateComponent.h"
#include "CStatusComponent.h"
#include "Weapon/CAttachment.h"
#include "Weapon/CWeaponAsset.h"

UCWeaponComponent::UCWeaponComponent()
{
}

void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACCharacter>(GetOwner());
	State = Cast<UCStateComponent>(OwnerCharacter->GetComponentByClass(UCStateComponent::StaticClass()));

	OwnerCharacter->OnCharacterHit.Add(FOnCharacterHit::FDelegate::CreateUObject(this, &UCWeaponComponent::HitCancle));
	for (int32 i = 0; i < (int32)EWeaponType::Max; i++)
	{
		FActorSpawnParameters params;
		params.Owner = OwnerCharacter;

		//�������ִ°Ͱ� �����ϰ��ִ� ���� �ٸ���.
		if (AttachmentClasses[i] != nullptr)
		{
			Weapons.Add((EWeaponType)i, OwnerCharacter->GetWorld()->SpawnActor<ACAttachment>(AttachmentClasses[i], params));
		}
		else
		{
			FString outStr = OwnerCharacter->GetName();
			outStr += " ";
			outStr += UEnum::GetValueAsString((EWeaponType)i);
			outStr += "Not Setting Weapon Attachment";
			CLog::Log(outStr);
		}

		if (DataAsset[i] == nullptr)
		{
			FString outStr = OwnerCharacter->GetName();
			outStr += " ";
			outStr += UEnum::GetValueAsString((EWeaponType)i);
			outStr += " Not Setting ActionDataAsset";
			CLog::Log(outStr);
		}
	}
}

void UCWeaponComponent::SetUnarmedMode() 
{
	ChangeType(EWeaponType::Unarmed);
}

void UCWeaponComponent::SetOneHandMode()
{
	ChangeType(EWeaponType::OneHand);
}
	
void UCWeaponComponent::SetBowMode()
{
	ChangeType(EWeaponType::Bow);
}

void UCWeaponComponent::DoAction()
{
	if (Type == EWeaponType::Unarmed)
		return;

	//�ش� DataAsset�� �����Ͱ��ִ��� �Ǻ��ϴ°��̱� ������ NULL���
	if (DataAsset[(int32)Type] == NULL)
	{
		FString str = "";
		str += UEnum::GetValueAsString(Type);
		str += " Have Not DataAsset";
		return;
	}

	if (bAbleNext)
		bNextAction = true;

	if (State->IsIdleMode() == false)
		return;

	State->SetActionMode();

	OwnerCharacter->PlayAnimMontage(DataAsset[(int32)Type]->GetActionDatas()[Combo_index].Montage);
}

void UCWeaponComponent::BeginDoAction()
{
	Combo_index++;
	UAnimMontage* montage = DataAsset[(int32)Type]->GetActionDatas()[Combo_index].Montage;

	if (montage == nullptr)
	{
		FString str;
		str += UEnum::GetValueAsString(Type);
		str += FString::FromInt(Combo_index);
		str += "Have Not Combo Montage";
		return;
	}

	OwnerCharacter->PlayAnimMontage(montage);
}

void UCWeaponComponent::EndDoAction()
{
	State->SetIdleMode();
	DisableNext();
	OffNextAction();
	Combo_index = 0;
}

void UCWeaponComponent::ChangeType(EWeaponType InType)
{
	Type = InType;

	if (OnWeaponTypeChanged.IsBound())
		OnWeaponTypeChanged.Broadcast(InType);
}

void UCWeaponComponent::EnableNext()
{
	bAbleNext = true;
}

void UCWeaponComponent::DisableNext()
{
	bAbleNext = false;
}

void UCWeaponComponent::OffNextAction()
{
	bNextAction = false;
}

void UCWeaponComponent::SpawnWeapon(EWeaponType weapon)
{
	FActorSpawnParameters params;
	params.Owner = OwnerCharacter;
	Weapons.Add(weapon, OwnerCharacter->GetWorld()->SpawnActor<ACAttachment>(AttachmentClasses[(int32)weapon], params));
}

FDamageData UCWeaponComponent::GetDamageData()
{
	FDamageData rtv_DamageData = DataAsset[(int32)Type]->GetActionDatas()[Combo_index].DamageData;

	UCStatusComponent* status = Cast<UCStatusComponent>(OwnerCharacter->GetComponentByClass(UCStatusComponent::StaticClass()));
	if (status == nullptr) 
	{
		CLog::Log("Character is have Not StatusComponent");
		return FDamageData();
	}

	return rtv_DamageData;
}

void UCWeaponComponent::HitCancle()
{
	EndDoAction();
}




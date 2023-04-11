#include "Components/CWeaponComponent.h"

#include "Character/CCharacter.h"
#include "Utillities/CLog.h"
#include "GameFramework/Character.h"
#include "CStateComponent.h"
#include "CStatusComponent.h"
#include "Net/UnrealNetwork.h"
#include "Weapon/CAttachment.h"
#include "Weapon/CWeaponAsset.h"

UCWeaponComponent::UCWeaponComponent()
{
	
}

void UCWeaponComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UCWeaponComponent, Type);
	DOREPLIFETIME(UCWeaponComponent, Combo_index);
}

void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACCharacter>(GetOwner());
	State = Cast<UCStateComponent>(OwnerCharacter->GetComponentByClass(UCStateComponent::StaticClass()));
	Status = Cast<UCStatusComponent>(OwnerCharacter->GetComponentByClass(UCStatusComponent::StaticClass()));

	OwnerCharacter->OnCharacterHit.Add(FOnCharacterHit::FDelegate::CreateUObject(this, &UCWeaponComponent::HitCancle));
	for (int32 i = 0; i < (int32)EWeaponType::Max; i++)
	{
		FActorSpawnParameters params;
		params.Owner = OwnerCharacter;

		//세팅해주는것과 소유하고있는 것은 다르다.
		if (AttachmentClasses[i] != nullptr)
		{
			SpawnWeapon(EWeaponType(i));
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

void UCWeaponComponent::ChangeComboIndex_Implementation(int comboIndex)
{
	Combo_index = comboIndex;
}

void UCWeaponComponent::ServerChangeComboIndex_Implementation(int comboIndex)
{
	ChangeComboIndex(comboIndex);
}

void UCWeaponComponent::ServerChangeType_Implementation(EWeaponType InType)
{
	ChangeType(InType);
}


void UCWeaponComponent::SetUnarmedMode() 
{
	//if(OwnerCharacter->HasAuthority())
		ServerChangeType(EWeaponType::Unarmed);
}

void UCWeaponComponent::SetOneHandMode()
{
	//if (OwnerCharacter->HasAuthority())
		ServerChangeType(EWeaponType::OneHand);
}
	
void UCWeaponComponent::SetBowMode()
{
	//if (OwnerCharacter->HasAuthority())
		ServerChangeType(EWeaponType::Bow);
}

void UCWeaponComponent::DoAction_Implementation()
{
	if (Type == EWeaponType::Unarmed)
		return;

	//해당 DataAsset에 데이터가있는지 판별하는것이기 떄문에 NULL사용
	if (DataAsset[(int32)Type] == NULL)
	{
		FString str = "";
		str += UEnum::GetValueAsString(Type);
		str += " Have Not DataAsset";
		ensureMsgf(false, TEXT("'%s'"),*str);
	}

	if (bAbleNext)
		bNextAction = true;

	if (State->IsIdleMode() == false)
		return;

	State->SetActionMode();
	Status->Stop();
	UAnimMontage* montage = DataAsset[(int32)Type]->GetActionDatas()[Combo_index].Montage;

	OwnerCharacter->MultiCastPlayMontage(montage);
}


void UCWeaponComponent::BeginDoAction_Implementation()
{
	ServerChangeComboIndex(++Combo_index);
	UAnimMontage* montage = DataAsset[(int32)Type]->GetActionDatas()[Combo_index].Montage;

	if (montage == nullptr)
	{
		FString str;
		str += UEnum::GetValueAsString(Type);
		str += FString::FromInt(Combo_index);
		str += "Have Not Combo Montage";
		return;
	}

	OwnerCharacter->MultiCastPlayMontage(montage);
}

void UCWeaponComponent::EndDoAction_Implementation()
{
	State->SetIdleMode();
	Status->Move();
	DisableNext();
	OffNextAction();
	ServerChangeComboIndex(0);
}

void UCWeaponComponent::ChangeType_Implementation(EWeaponType InType)
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

const FDamageData UCWeaponComponent::GetDamageData()
{
	if(DataAsset[(int32)Type]->GetActionDatas().Num() <= Combo_index)
	{
		FString str = "";
		str += Cast<ACCharacter>(GetOwner())->GetName();
		str += " ";
		str += UEnum::GetValueAsString(Type);
		str += " ";
		str += FString::FromInt(Combo_index);
		str += " Have Not DamageData";

		ensureMsgf(false,TEXT("(%s)"),*str);
	}


	return DataAsset[(int32)Type]->GetActionDatas()[Combo_index].DamageData;
}

void UCWeaponComponent::HitCancle()
{
	EndDoAction();
}




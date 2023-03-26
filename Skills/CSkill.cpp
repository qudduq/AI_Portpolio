#include "CSkill.h"
#include "Utillities/CLog.h"
#include "Components/CStateComponent.h"
#include "Components/CSkillComponent.h"
#include "GameFramework/Character.h"
#include "Character/CCharacter.h"

void UCSkill::ExcuteSkill(ACharacter* InOwner)
{
	OwnerCharacter = Cast<ACCharacter>(InOwner);
	State = Cast<UCStateComponent>(InOwner->GetComponentByClass(UCStateComponent::StaticClass()));

	if(State->IsActionMode())
		return;

	HitCancleHandle = OwnerCharacter->OnCharacterHit.Add(FOnCharacterHit::FDelegate::CreateUObject(this, &UCSkill::HitCancle));
	UCSkillComponent* SkillComponent = Cast<UCSkillComponent>(OwnerCharacter->GetComponentByClass(UCSkillComponent::StaticClass()));

	BeginHandle = SkillComponent->OnBeginSkill.Add(FOnBeginSkill::FDelegate::CreateUObject(this, &UCSkill::BeginSkill));
	EndHandle = SkillComponent->OnEndSkill.Add(FOnEndSkill::FDelegate::CreateUObject(this, &UCSkill::EndSkill));

	State->SetActionMode();
	InOwner->PlayAnimMontage(SkillData.Montage, SkillData.PlayRatio);
}

void UCSkill::EndSkill()
{
	State->SetIdleMode();
	UCSkillComponent* SkillComponent = Cast<UCSkillComponent>(OwnerCharacter->GetComponentByClass(UCSkillComponent::StaticClass()));
	SkillComponent->OnBeginSkill.Remove(BeginHandle);
	SkillComponent->OnEndSkill.Remove(EndHandle);
	OwnerCharacter->OnCharacterHit.Remove(HitCancleHandle);
}

void UCSkill::QuickSlotCall(ACharacter* InOwner)
{
	ExcuteSkill(InOwner);
}

UTexture2D* UCSkill::GetSlotTexture()
{
	if(Texture == nullptr)
	{
		FString str = "";
		this->GetName(str);
		str += " have not Texture";
		CLog::Log(str);
	}

	return Texture;
}

void UCSkill::HitCancle()
{
	CLog::Log("HitCancle");
	EndSkill();
}

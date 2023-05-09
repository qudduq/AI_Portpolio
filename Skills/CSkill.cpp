#include "CSkill.h"
#include "Utillities/CLog.h"
#include "Components/CStateComponent.h"
#include "Components/CSkillComponent.h"
#include "GameFramework/Character.h"
#include "Character/CCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Particles/ParticleSystem.h"
#include "Utillities/TaskHelper.h"

void UCSkill::ExcuteSkill(ACharacter* InOwner)
{
	OwnerCharacter = Cast<ACCharacter>(InOwner);
	State = Cast<UCStateComponent>(InOwner->GetComponentByClass(UCStateComponent::StaticClass()));

	if(State->IsActionMode())
		return;

	HitCancleHandle = OwnerCharacter->OnCharacterHit.Add(FOnCharacterHit::FDelegate::CreateUObject(this, &UCSkill::HitCancle));
	UCSkillComponent* SkillComponent = Cast<UCSkillComponent>(OwnerCharacter->GetComponentByClass(UCSkillComponent::StaticClass()));

	BeginHandle = SkillComponent->OnBeginSkill.Add(FOnBeginSkill::FDelegate::CreateUObject(this, &UCSkill::BeginSkill));
	ActiveHandle = SkillComponent->OnActiveSkill.Add(FOnActiveSkill::FDelegate::CreateUObject(this, &UCSkill::ActiveSkill));
	EndHandle = SkillComponent->OnEndSkill.Add(FOnEndSkill::FDelegate::CreateUObject(this, &UCSkill::EndSkill));

	State->SetActionMode();
	OwnerCharacter->MultiCastPlayMontage(SkillData.Montage);
}

void UCSkill::EndSkill()
{
	FXComponents.Empty();
	UCSkillComponent* SkillComponent = Cast<UCSkillComponent>(OwnerCharacter->GetComponentByClass(UCSkillComponent::StaticClass()));
	SkillComponent->OnBeginSkill.Remove(BeginHandle);
	SkillComponent->OnActiveSkill.Remove(ActiveHandle);
	SkillComponent->OnEndSkill.Remove(EndHandle);
	OwnerCharacter->OnCharacterHit.Remove(HitCancleHandle);
	State->SetIdleMode();
}

void UCSkill::PlaySkillEffect_Implementation(UObject* WorldContext, FVector Location)
{
	UFXSystemComponent* FX;
	if (Cast<UParticleSystem>(SkillData.Effect) != nullptr)
	{
		FX = TaskHelper::PlayParticleSystem(WorldContext, SkillData.Effect, Location);
	}
	else if (Cast<UNiagaraSystem>(SkillData.Effect) != nullptr)
	{
		FX = TaskHelper::PlayNiagaraSystem(WorldContext, SkillData.Effect, Location);
	}

	FXComponents.Add(FX);
}

void UCSkill::OffSkillEffect_Implementation()
{
	for(const auto& FX : FXComponents)
	{
		FX->DestroyComponent();
	}
}

void UCSkill::QuickSlotCall(ACharacter* InOwner)
{
	ExcuteSkill(InOwner);
}

UTexture2D* UCSkill::GetSlotTexture()
{
	if (Texture == nullptr)
	{
		FString str = "";
		this->GetName(str);
		str += " have not Texture";
		CLog::Log(str);
	}

	return Texture;
}

FName UCSkill::GetID()
{
	return SkillID;
}

void UCSkill::HitCancle()
{
	CLog::Log("HitCancle");
	EndSkill();
}

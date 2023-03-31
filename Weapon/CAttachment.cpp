#include "CAttachment.h"
#include "Character/CCharacter.h"
#include "Components/CWeaponComponent.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Utillities/CLog.h"


ACAttachment::ACAttachment()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	Collisions = CreateDefaultSubobject<UCapsuleComponent>("Collisions");
	Collisions->SetupAttachment(Root);
}
	
void ACAttachment::BeginPlay()
{
	OwnerCharacter = Cast<ACCharacter>(GetOwner());

	Collisions->OnComponentBeginOverlap.AddDynamic(this, &ACAttachment::OnComponentBeginOverlap);
	Collisions->OnComponentEndOverlap.AddDynamic(this, &ACAttachment::OnComponentEndOverlap);

	Super::BeginPlay();
	
	OffCollision();
}

void ACAttachment::AttachTo(FName InSocketName)
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}

void ACAttachment::OnCollision()
{
	Collisions->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ACAttachment::OffCollision()
{
	Collisions->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACAttachment::OnComponentBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OwnerCharacter == OtherActor) return;
	if(OwnerCharacter->GetClass() == OtherActor->GetClass()) return;

	UCWeaponComponent* weapon = Cast<UCWeaponComponent>(OwnerCharacter->GetComponentByClass(UCWeaponComponent::StaticClass()));
	if (weapon == nullptr) return;

	if(OwnerCharacter->GetController() == nullptr)
	{
		FString str = "";
		str += OwnerCharacter->GetName();
		str += " Have Not Controller";
		CLog::Log(str);
	}

	OtherActor->TakeDamage(0, weapon->GetDamageData(), OwnerCharacter->GetController(), this);
}

void ACAttachment::OnComponentEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OwnerCharacter == OtherActor) return;
	if (OwnerCharacter->GetClass() == OtherActor->GetClass()) return;

	
}



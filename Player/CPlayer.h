#pragma once

#include "CoreMinimal.h"
#include "Character/CCharacter.h"
#include "GenericTeamAgentInterface.h"
#include "CPlayer.generated.h"

UCLASS()
class AI_PORTPOLIO_API ACPlayer 
	: public ACCharacter
	, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly ,Category = "Team")
		FGenericTeamId TeamId;
private:
	UPROPERTY(EditDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly)
		class UCameraComponent* Camera;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCQuickSlotComponent* QuickSlot;

private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UCListView> SkillListWidget;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UCQuickSlotBar_Widget> QuickSlotBarWidget;
		

public:
	ACPlayer();
	virtual void PossessedBy(AController* NewController) override;

	FORCEINLINE UCListView* GetSkillList() const { return SkillList; }
	FORCEINLINE UCQuickSlotBar_Widget* GetQuickSlotBar() const { return QuickSlotBar; }

	UFUNCTION(Client, Reliable)
		void GetCharacterName();

protected:
	virtual void BeginPlay() override;	

private:
	class UCListView* SkillList;
	class UCQuickSlotBar_Widget* QuickSlotBar;

};

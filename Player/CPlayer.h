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

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UCListView> SkillListWidget;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UCQuickSlotBar_Widget> QuickSlotBarWidget;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ABezierTest> Bezier;
		

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;



private:
	void Forward(float Axis);
	void Right(float Axis);

	void CameraPitch(float Axis);
	void CameraYaw(float Axis);

	void OnJump();

	void ChangeView();
	void MoveCamera();
	void MouseView();

	void ChangeWeapon();

	void DoAction();

	void CLickSkillList();

	//콜백함수는 on붙여라
	void OnQuickSlot(const FKey SetNum);


private:
	void SetTest1();
	void SetTest2();

	FVector Enemylocation;

private:
	UPROPERTY()
		class UCListView* SkillList;
	UPROPERTY()
		class UCQuickSlotBar_Widget* QuickSlotBar;
	//TSharedPtr<class CameraShakeManager> CameraShake;
	FTimerHandle handle;

	bool bQuterView = false;
	bool bMouse = false;
	int camera_count;
	bool isChanging = false;
	bool bSkillList = false;

	int weaponnum = 0;


	class ABezierTest* BezierObj;
	bool bHit = false;
};

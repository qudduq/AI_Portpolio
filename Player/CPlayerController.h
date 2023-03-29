// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AI_PORTPOLIO_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACPlayerController();

protected:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* aPawn) override;

private:
	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void Jump();

	void CameraYaw(float Axis);
	void ChangeView();
	void MoveCamera();

	void ChangeWeapon();
	void MouseView();
	void DoAction();
	void QuickSlot(const FKey SetNum);
	void CLickSkillList();

private:
	FTimerHandle handle;
	int weaponnum = 0;
	int camera_count;
	bool bQuterView = false;
	bool isChanging = false;
	bool bMouse = false;
	bool bSkillList = false;
};

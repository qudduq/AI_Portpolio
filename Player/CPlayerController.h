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

private:
	// ���� �÷��̾ ���� �Ͽ����� �Ǵ����ִ� �Լ��Դϴ�.
	class ACPlayer* CheckPlayer();
	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void CameraYaw(float Axis);
	void Jump();

	// Z���� ������ 2Dȭ��� ���ͺ� �������� ���� �����Ҽ��ִ� ȭ���Դϴ�.
	void ChangeView();

	// SetTimer�� ���� ī�޶� �ε巴�� �����ϼ��ְ� �������־����ϴ�.
	void MoveCamera();
	void ChangeWeapon();

	// ����â�� ������ ��� �������ʴ� ���콺 Ŀ���� ��������ݴϴ�.
	void MouseView();
	void DoAction();

	// Ŭ�󿡼� �������� �����ÿ� ������ �ش� ��ü�� ����ǵ��� �����Ͽ����ϴ�.
	//UFUNCTION(Reliable, Server)
	void ServerQuickSlotCall(const FKey SetNum);
	void QuickSlotCall(const FKey SetKey);

	// ListView �� �̿��Ͽ� �ش� ���⿡�´� ��ų���� ����Ʈ�������� ���̵��� �Ͽ����ϴ�.
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

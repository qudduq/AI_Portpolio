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
	// 현재 플레이어에 빙의 하였는지 판단해주는 함수입니다.
	class ACPlayer* CheckPlayer();
	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void CameraYaw(float Axis);
	void Jump();

	// Z축이 고정된 2D화면과 쿼터뷰 형식으로 서로 변경할수있는 화면입니다.
	void ChangeView();

	// SetTimer에 의해 카메라가 부드럽게 움직일수있게 세팅해주었습니다.
	void MoveCamera();
	void ChangeWeapon();

	// 위젯창이 열리는 경우 보이지않던 마우스 커서를 등장시켜줍니다.
	void MouseView();
	void DoAction();

	// 클라에서 퀵슬롯을 누를시에 서버의 해당 객체가 실행되도록 구현하였습니다.
	//UFUNCTION(Reliable, Server)
	void ServerQuickSlotCall(const FKey SetNum);
	void QuickSlotCall(const FKey SetKey);

	// ListView 를 이용하여 해당 무기에맞는 스킬들이 리스트형식으로 보이도록 하였습니다.
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

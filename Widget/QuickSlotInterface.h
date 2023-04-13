#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuickSlotInterface.generated.h"

/*
 * 퀵슬롯에 등록되는 객체는 해당 인터페이스를 상속받아 구현해야합니다.
 */

UINTERFACE(MinimalAPI)
class UQuickSlotInterface : public UInterface
{
	GENERATED_BODY()
};

class AI_PORTPOLIO_API IQuickSlotInterface
{
	GENERATED_BODY()

public:
	// 퀵슬롯에 저장되어있는 객체가 실행되었을때 불려집니다.
	virtual void QuickSlotCall(class ACharacter* InOwner) = 0;

	//퀵슬롯에 등록시에 이미지를 붙여주는데 사용합니다.
	//따라서 퀵슬롯에 등록될 객체는 텍스쳐를 가지고있어야합니다.
	virtual UTexture2D* GetSlotTexture() = 0;

	//퀵슬록에 등록되어있는 객체의 아이디 정보를 얻어옵니다.
	//해당 아이디는 클라이언트에불려진 객체를 서버에서 정확히 찾기위해 사용됩니다.
	virtual FName GetID() = 0;
};

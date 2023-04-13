#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuickSlotInterface.generated.h"

/*
 * �����Կ� ��ϵǴ� ��ü�� �ش� �������̽��� ��ӹ޾� �����ؾ��մϴ�.
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
	// �����Կ� ����Ǿ��ִ� ��ü�� ����Ǿ����� �ҷ����ϴ�.
	virtual void QuickSlotCall(class ACharacter* InOwner) = 0;

	//�����Կ� ��Ͻÿ� �̹����� �ٿ��ִµ� ����մϴ�.
	//���� �����Կ� ��ϵ� ��ü�� �ؽ��ĸ� �������־���մϴ�.
	virtual UTexture2D* GetSlotTexture() = 0;

	//�����Ͽ� ��ϵǾ��ִ� ��ü�� ���̵� ������ ���ɴϴ�.
	//�ش� ���̵�� Ŭ���̾�Ʈ���ҷ��� ��ü�� �������� ��Ȯ�� ã������ ���˴ϴ�.
	virtual FName GetID() = 0;
};

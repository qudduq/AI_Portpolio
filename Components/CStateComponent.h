#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle, Action, Hitted, Dead, Max
};
DECLARE_MULTICAST_DELEGATE_OneParam(FStateTypeChanged, EStateType);
DECLARE_DELEGATE_OneParam(FOnIdleMode, AAIController*);
// ������ �����ϴ°��� �ƴ϶�� ���� ���̳�������������
// ���� : �̸����������Ͽ��� ã���������� ,�Ϲݵ�������Ʈ���� �� ����

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AI_PORTPOLIO_API UCStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE bool IsIdleMode() { return Type == EStateType::Idle; }
	FORCEINLINE bool IsActionMode() { return Type == EStateType::Action; }
	FORCEINLINE bool IsHittedMode() { return Type == EStateType::Hitted; }
	FORCEINLINE bool IsDeadMode() { return Type == EStateType::Dead; }

public:	
	UCStateComponent();

public:
	void SetIdleMode();
	void SetActionMode();
	void SetHittedMode();
	void SetDeadMode();

protected:
	virtual void BeginPlay() override;

private:
	void ChangeType(EStateType InType);

public:
	void RegisterDelegate(const FStateTypeChanged::FDelegate& ObserverDelegate);
	void UnregisterDelegate(const FDelegateHandle& handle);

private:
	EStateType Type;
	FStateTypeChanged OnStateTypeChanged;

};

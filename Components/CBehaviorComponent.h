#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/ActorComponent.h"
#include "CBehaviorComponent.generated.h"

UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	Wait, Action, closeAction, middleAction, farAction, Patrol, Access, Defend, Hit, Avoid, Max,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBehaviorTypeChanged, EBehaviorType, InPrevType, EBehaviorType, InNewType);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AI_PORTPOLIO_API UCBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		FName BehaviorKey = "Behavior";

	UPROPERTY(EditDefaultsOnly)
		FName PlayerKey = "Player";

public:
	FORCEINLINE bool IsActionMode() { return type == EBehaviorType::Action; }
	FORCEINLINE bool IscloseActionMode() { return type == EBehaviorType::closeAction; }
	FORCEINLINE bool IsmiddleActionMode() { return type == EBehaviorType::middleAction; }
	FORCEINLINE bool IsfarActionMode() { return type == EBehaviorType::farAction; }
	FORCEINLINE bool IsWaitMode() { return type == EBehaviorType::Wait; }
	FORCEINLINE bool IsPatrolMode() { return type == EBehaviorType::Patrol; }
	FORCEINLINE bool IsAccessMode() { return type == EBehaviorType::Access; }
	FORCEINLINE bool IsDefendMode() { return type == EBehaviorType::Defend; }
	FORCEINLINE bool IsHittedMode() { return type == EBehaviorType::Hit; }
	FORCEINLINE bool IsAvoidMode() { return type == EBehaviorType::Avoid; }

public:
	FORCEINLINE void SetBlackboard(class UBlackboardComponent* InBlackboard) { Blackboard = InBlackboard; }

public:	
	UCBehaviorComponent();

	void SetActionMode();
	void SetcloseActionMode();
	void SetmiddleActionMode();
	void SetfarActionMode();
	void SetWaitMode();
	void SetPatrolMode();
	void SetAccessMode();
	void SetDefendMode();
	void SetHitMode();
	void SetAvoidMode();

	class ACPlayer* GetTargetPlayer();

protected:
	virtual void BeginPlay() override;

private:
	void ChangeType(EBehaviorType InType);

public:
	FBehaviorTypeChanged OnBehaviorTypeChanged;

private:
	UPROPERTY()
		class UBlackboardComponent* Blackboard;
	EBehaviorType type = EBehaviorType::Wait;
};

#include "CBTDecorator_Test.h"
#include "Utillities/CLog.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CStateComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"



UCBTDecorator_Test::UCBTDecorator_Test(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CLog::Log("DecortorTest Start");
}

uint16 UCBTDecorator_Test::GetInstanceMemorySize() const
{
	return sizeof(FDelegateHandle);
}

void UCBTDecorator_Test::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	FDelegateHandle* handle = CastInstanceNodeMemory<FDelegateHandle>(NodeMemory);
	
	UCStateComponent* state = Cast<UCStateComponent>(OwnerComp.GetOwner()->GetComponentByClass(UCStateComponent::StaticClass()));
	if (state == nullptr) return;

	*handle = FStateTypeChanged::FDelegate::CreateUObject(this, &UCBTDecorator_Test::OnStateTypeChanged, OwnerComp.GetAIOwner()).GetHandle();
	// payload 사용법 변수가안맞는 델리게이트에 변수를 추가해주는 기능 
	// 주의사항 : 델리게이트의 인자가 우선이며 뒤에 페이로드인자를 받아준다
	
}

void UCBTDecorator_Test::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);

	UCStateComponent* state = Cast<UCStateComponent>(OwnerComp.GetOwner()->GetComponentByClass(UCStateComponent::StaticClass()));
	if (state == nullptr) return;
	FDelegateHandle* handle = CastInstanceNodeMemory<FDelegateHandle>(NodeMemory);

	state->UnregisterDelegate(*handle);
}

void UCBTDecorator_Test::OnStateTypeChanged(EStateType InNewType, AAIController* controller)
{
	UBehaviorTreeComponent* behaviorComp = (UBehaviorTreeComponent*)controller->GetBrainComponent();
	if (behaviorComp == nullptr)
		return;

	if (Type == InNewType)
	{
		behaviorComp->RequestExecution(this);
	}
	
}

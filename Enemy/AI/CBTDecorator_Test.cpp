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
	// payload ���� �������ȸ´� ��������Ʈ�� ������ �߰����ִ� ��� 
	// ���ǻ��� : ��������Ʈ�� ���ڰ� �켱�̸� �ڿ� ���̷ε����ڸ� �޾��ش�
	
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

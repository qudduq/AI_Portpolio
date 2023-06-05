#include "Components/CEQSComponent.h"

#include "Enemy/CAIController.h"
#include "Enemy/CEnemy_AI.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "Utillities/CLog.h"

UCEQSComponent::UCEQSComponent()
{

}


FVector UCEQSComponent::FindEQSSpot()
{
	CLog::Log("Find Position EQS");
	FEnvQueryRequest HidingSpotQueryRequest = FEnvQueryRequest(EQSOptionData, GetOwner());
	HidingSpotQueryRequest.Execute(EEnvQueryRunMode::SingleResult, this, &UCEQSComponent::EQSResult);

	if (OnEQSPosition.IsBound())
	{
		return OnEQSPosition.Execute();
	}

	return GetOwner()->GetActorLocation();
}

void UCEQSComponent::EQSResult(TSharedPtr<FEnvQueryResult> result)
{
	if (result->IsSuccsessful())
	{
		auto pos = result->GetItemAsLocation(0);
		auto pa = GetOwner()->GetActorLocation();
		pa -= FVector(-1, -1, -1);
	}
}

FVector UCEQSComponent::GetEQSPostion()
{
	if (ACEnemy_AI* Enemy_AI = Cast<ACEnemy_AI>(GetOwner()))
	{
		CLog::Log("Owner is Not Enemy_AI");
		return GetOwner()->GetActorLocation();
	}


	return FindEQSSpot();
}

void UCEQSComponent::BeginPlay()
{
	Super::BeginPlay();
	if(ACEnemy_AI* Enemy_AI = Cast<ACEnemy_AI>(GetOwner()))
	{
		CLog::Log("Owner is Not Enemy_AI");
		return;
	}

}
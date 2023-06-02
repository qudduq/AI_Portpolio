#include "CAIController.h"
#include "Enemy/CEnemy_AI.h"
#include "Player/CPlayer.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/CBehaviorComponent.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Utillities/CLog.h"

ACAIController::ACAIController()
{
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("Blackboard");

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	Sight->SightRadius = 1000;
	Sight->LoseSightRadius = 1200;
	Sight->PeripheralVisionAngleDegrees = 60;
	Sight->SetMaxAge(2);

	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;

	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(*Sight->GetSenseImplementation());

}

void ACAIController::FindHidingSpot()
{
	CLog::Log("EQS management");
	FEnvQueryRequest HidingSpotQueryRequest = FEnvQueryRequest(FindHidingSpotEQS, GetPawn());
	HidingSpotQueryRequest.Execute(EEnvQueryRunMode::SingleResult, this, &ACAIController::MovetoQueryResult);
}

void ACAIController::MovetoQueryResult(TSharedPtr<FEnvQueryResult> result)
{
	if(result->IsSuccsessful())
	{
		auto pos = result->GetItemAsLocation(0);
		auto pa = GetPawn()->GetActorLocation();
		//UKismetSystemLibrary::DrawDebugCircle(GetWorld(), result->GetItemAsLocation(0), 100.0f,12,FLinearColor::Red,10.0f,100);
		//MoveToLocation(result->GetItemAsLocation(0));
	}
}

void ACAIController::BeginPlay()
{
	Super::BeginPlay();

	Perception->OnPerceptionUpdated.AddDynamic(this, &ACAIController::OnPerceptionUpdated);
}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Enemy = Cast<ACEnemy_AI>(InPawn);
	if (Enemy == nullptr) return;

	SetGenericTeamId(TeamID);
	UseBlackboard(Enemy->GetBehaviorTree()->BlackboardAsset, Blackboard);

	Behavior = Cast<UCBehaviorComponent>(Enemy->GetComponentByClass(UCBehaviorComponent::StaticClass()));
	Behavior->SetBlackboard(Blackboard);

	RunBehaviorTree(Enemy->GetBehaviorTree());
}

void ACAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*> actors;
	Perception->GetCurrentlyPerceivedActors(nullptr, actors);


	ACPlayer* player = nullptr;
	for (AActor* actor : actors)
	{
		player = Cast<ACPlayer>(actor);
		FindHidingSpot();

		if (!!player)
		{
			break;
		}
	}

	Blackboard->SetValueAsObject("Player", player);
}

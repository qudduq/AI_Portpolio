#include "CLevelScriptActor.h"
#include "Kismet/GameplayStatics.h"
#include "Utillities/CLog.h"
#include "LandscapeProxy.h"
#include "TimerManager.h"
#include "Widget/CUserWidget.h"


void ACLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<FVector> gt;
	landscape->UpdateGrass(gt, false);

	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(1, 1, 0.001, FLinearColor::Black, false, true);
	
	GetWorld()->GetTimerManager().SetTimer
	(
		Tm, 
		FTimerDelegate::CreateLambda
		(
			[=]() 
			{
				if (landscape->AsyncFoliageTasks.Num() == 0)
				{
					UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(1, 0, 1, FLinearColor::Black, false, true);
					GetWorld()->GetTimerManager().ClearTimer(Tm);
					
				}
			}
		),
		0.05f,
		true
	);
	


}

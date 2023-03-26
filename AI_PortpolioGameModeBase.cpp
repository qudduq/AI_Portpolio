#include "AI_PortpolioGameModeBase.h"

AAI_PortpolioGameModeBase::AAI_PortpolioGameModeBase()
{
	FString str = "Blueprint'/Game/CharacterFolder/Player/BP_CPlayer.BP_CPlayer_C'";
	ConstructorHelpers::FClassFinder<APawn> asset(*str);
	DefaultPawnClass = asset.Class;
}
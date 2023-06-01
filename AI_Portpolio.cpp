#include "AI_Portpolio.h"
#include "Modules/ModuleManager.h"

#include "Functions/CustomProjectSetting.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ISettingsContainer.h"

#define LOCTEXT_NAMESPACE "AI_Portpolio"

class FCustomSettingsModule : public FDefaultGameModuleImpl
{
	virtual void StartupModule() override
	{
		RegisterSettings();
	}

	virtual void ShutdownModule() override
	{
		if (UObjectInitialized())
		{
			UnregisterSettings();
		}
	}
private:
	void RegisterSettings()
	{
		// Registering some settings is just a matter of exposijg the default UObject of
		// your desired class, feel free to add here all those settings you want to expose
		// to your LDs or artists.

		if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
		{
			// Register the settings
			ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", FApp::GetProjectName(), "General",
				LOCTEXT("RuntimeGeneralSettingsName", "General"),
				LOCTEXT("RuntimeGeneralSettingsDescription", "Base configuration for our game module"),
				GetMutableDefault<UCustomProjectSetting>()
			);

			ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Project");

			//프로젝트 네임은 우선순위가 -1이고 Default로 설정되어있는 카테고리들은 0, 고급설정과 같이 사용자가 추가하는 카테고리는 1로
			//기본 우선순위가 정해집니다.
			auto str = FApp::GetProjectName();
			SettingsContainer->DescribeCategory(FApp::GetProjectName(),
				LOCTEXT("RuntimeWDCategoryName", "Custorm Settings"),
				LOCTEXT("RuntimeWDCategoryDescription", "Game configuration for the CustomSettings game module"));
		}
	}

	void UnregisterSettings()
	{
		// Ensure to unregister all of your registered settings here, hot-reload would
		// otherwise yield unexpected results.

		if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
		{
			SettingsModule->UnregisterSettings("Project", "CustomProjectSetting", "General");
		}
	}
};

IMPLEMENT_PRIMARY_GAME_MODULE(FCustomSettingsModule, AI_Portpolio, "AI_Portpolio" );

#undef LOCTEXT_NAMESPACE
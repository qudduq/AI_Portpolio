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

	virtual bool SupportsDynamicReloading() override
	{
		return true;
	}

private:

	// Callback for when the settings were saved.
	bool HandleSettingsSaved()
	{
		UCustomProjectSetting* Settings = GetMutableDefault<UCustomProjectSetting>();
		bool ResaveSettings = false;

		// You can put any validation code in here and resave the settings in case an invalid
		// value has been entered

		if (ResaveSettings)
		{
			Settings->SaveConfig();
		}

		return true;
	}

	void RegisterSettings()
	{
		// Registering some settings is just a matter of exposijg the default UObject of
		// your desired class, feel free to add here all those settings you want to expose
		// to your LDs or artists.

		if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
		{
			// Register the settings
			ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "CustomProjectSetting", "General",
				LOCTEXT("RuntimeGeneralSettingsName", "General"),
				LOCTEXT("RuntimeGeneralSettingsDescription", "Base configuration for our game module"),
				GetMutableDefault<UCustomProjectSetting>()
			);

			// Register the save handler to your settings, you might want to use it to
			// validate those or just act to settings changes.
			if (SettingsSection.IsValid())
			{
				SettingsSection->OnModified().BindRaw(this, &FCustomSettingsModule::HandleSettingsSaved);
			}
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
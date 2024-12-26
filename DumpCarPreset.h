#pragma once
#include "SaveCarPreset.h"
#include "FEStateManager.h"

void FECustomizeStateManager_HandlePadButton3()
{
	__asm pushad;

	char FilePath[MAX_PATH];
	
	PresetCar presetCar;
	memset(&presetCar, (BYTE)0, sizeof(presetCar)); // fill with 0s, C++ inits with 0xCC by default
	auto carRecord = FECarRecord::Instance();
	auto userProfile = FEManager::Instance()->GetUserProfile(0);

	if (carRecord)
	{
		FillCarPreset(&presetCar, carRecord);
		sprintf(FilePath, "%s_%s_%d.bin", userProfile + 0x10, presetCar.Model, carRecord->Customization);
		sprintf(presetCar.CollectionName, "CUSTOMIZATION_RECORD_%02d", carRecord->Customization); // Preset Name

		FILE* PresetFile = fopen(FilePath, "wb");
		if (PresetFile)
		{
			fwrite(&presetCar, sizeof(PresetCar), 1, PresetFile);
			fclose(PresetFile);
			FEDialogScreen::ShowOk(GetLocalizedString(bStringHash((char*)"PRESITTER_DUMP_SUCCESS")));
		}
		else
		{
			FEDialogScreen::ShowOk(GetLocalizedString(bStringHash((char*)"PRESITTER_DUMP_FAIL")));
		}
	}

	__asm popad;
}

int __fastcall FECustomizeStateManager_HandleButtonPressed(FECustomizeStateManager* stateManager, int, int a)
{
	int result = stateManager->HandleButtonPressed(a);

	if (stateManager->LastButton == 9)
	{
		stateManager->Pop(0x93E8A57C);
	}

	return result;
}
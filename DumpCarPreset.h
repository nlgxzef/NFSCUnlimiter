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

			if (PresitterAutosculpt) // Save AutoSculpt as floating point values
			{
				// Create file handle
				sprintf(FilePath, "%s_%s_%d_AS.bin", userProfile + 0x10, presetCar.Model, carRecord->Customization);
				FILE* PresetASFile = fopen(FilePath, "wb");

				if (PresetASFile)
				{
					PresetCarAutosculptFloat presetAS;
					memset(&presetAS, (BYTE)0, sizeof(presetAS)); // fill with 0s
					FillCarPresetASFloat(&presetAS, carRecord);
					DWORD Header = bStringHash((char*)"BCHUNK_UNLIMITER_PRESITTERAUTOSCULPT");
					fwrite(&Header, sizeof(DWORD), 1, PresetASFile);
					DWORD Size = sizeof(presetAS);
					fwrite(&Size, sizeof(DWORD), 1, PresetASFile);
					fwrite(&presetAS, sizeof(presetAS), 1, PresetASFile);

					// Close the file
					fclose(PresetASFile);
				}
			}

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
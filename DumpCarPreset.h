#pragma once
#include "SaveCarPreset.h"
#include "FEStateManager.h"

void FECustomizeStateManager_HandlePadButton3()
{
	__asm pushad;

	PresetCar presetCar;
	auto carRecord = FECarRecord::Instance();
	if (carRecord)
	{
		FillCarPreset(&presetCar, carRecord);

		FILE* PresetFile = fopen("CAR_PRESET.bin", "wb");
		if (PresetFile)
		{
			fwrite(&presetCar, sizeof(PresetCar), 1, PresetFile);
			fclose(PresetFile);
			FEDialogScreen::ShowOk("Successfully dumped car preset");
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
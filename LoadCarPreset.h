#pragma once
#include <string>
#include "PresetCar.h"
#include "FECustomizationRecord.h"
#include "CarPartDatabase.h"
#include "FECarRecord.h"
#include "FEManager.h"
#include "MemCard.h"
#include "Slots.h"

void UpdateVinylColor(PresetCarVinylColor* vinylColor, int num, int col, FECustomizationRecord* record, int carType)
{
	if (vinylColor->Swatch)
	{
		auto part = CarPartDatabase::Instance()->GetByPartName(Slot::VINYL_COLOUR, carType, vinylColor->Swatch);
		if (part)
		{
			RecordColorData color;
			color.Brightness = vinylColor->Brightness;
			color.Saturation = vinylColor->Saturation;
			record->SetVinylColor(num, col, color, part);
		}
	}
}

void UpdateVinyl(PresetCarVinyl* carVinyl, int num, FECustomizationRecord* record, CarType carType)
{
	if (carVinyl->VectorVinyl)
	{
		auto part = CarPartDatabase::Instance()->GetByPartName(Slot::VECTORVINYL, carType, carVinyl->VectorVinyl);
		if (part)
		{
			record->SetInstalledVinyl(num, part);

			UpdateVinylColor(&carVinyl->Fill, num, 0, record, carType);
			UpdateVinylColor(&carVinyl->Stroke, num, 1, record, carType);
			UpdateVinylColor(&carVinyl->InnerShadow, num, 2, record, carType);
			UpdateVinylColor(&carVinyl->InnerGlow, num, 3, record, carType);
		}
	}
}

void UpdateCustomizationRecord(PresetCar* preset, FECustomizationRecord* record, FECarRecord* carRecord)
{
	auto carType = carRecord->GetType();

	for (int i = 0; i < (int)Slot::COUNT; i++)
	{
		if (preset->Parts[i])
		{
			auto part = CarPartDatabase::Instance()->GetByPartName((Slot)i, carType, preset->Parts[i]);
			if (part)
			{
				record->SetInstalledPart((Slot)i, part, carType, true);
			}
		}
	}

	if (preset->PaintGroup && preset->PaintSwatch)
	{
		RecordColorData colorData;
		auto paintGroup = CarPartDatabase::Instance()->GetByPartName(Slot::BODY_PAINT_GROUP, carType, preset->PaintGroup);
		auto paintSwatch = CarPartDatabase::Instance()->GetByPartName(Slot::BODY_PAINT_SWATCH, carType, preset->PaintSwatch);
		colorData.Brightness = preset->Brightness;
		colorData.Saturation = preset->Saturation;
		if (paintGroup && paintSwatch)
		{
			record->WriteColor(0, colorData, paintSwatch, paintGroup);
		}
	}

	for (int i = 0; i < NumVinylLayers; i++)
	{
		UpdateVinyl(preset->Vinyls + i, i, record, carType);
	}
}

void LoadPresets(char* PresetPath)
{
	char FilePath[MAX_PATH];
	int WrongCarCount = 0;

	auto carDB = FEManager::Instance()->GetPlayerCarDB();

	sprintf(FilePath, "%s\\SkipLoad", PresetPath);
	FILE* SkipFile = fopen(FilePath, "rb");

	if (!SkipFile && carDB)
	{

		for (int i = 0; i < NumFECarRecords; i++)
		{
			auto carRecord = carDB->GetCarByIndex(i);
			if (carRecord->Handle != 0xFFFFFFFF)
			{
				auto record = carDB->GetCustomizationRecordByHandle(carRecord->Customization);
				if (record)
				{
					// Create file handle
					sprintf(FilePath, "%s\\%02d.bin", PresetPath, carRecord->Customization);
					FILE* PresetFile = fopen(FilePath, "rb");

					if (PresetFile)
					{
						PresetCar presetCar;
						fread(&presetCar, sizeof(PresetCar), 1, PresetFile);

						char* CarNameFromFEREC = GetCarTypeName(carRecord->GetType());
						char* CarNameFromPRESET = presetCar.Model;

						if (!strcmp(CarNameFromFEREC, CarNameFromPRESET)) // Check if it's the same car
						{
							auto record = carDB->GetCustomizationRecordByHandle(carRecord->Customization);
							if (record)
							{
								UpdateCustomizationRecord(&presetCar, record, carRecord);
							}
						}
						else WrongCarCount++;

						// Close the file
						fclose(PresetFile);
					}
				}
			}
		}

#ifdef _DEBUG
		if (WrongCarCount) bReleasePrintf("Presitter: Loaded preset data over the customization records with %d errors.\n", WrongCarCount);
		else bReleasePrintf("Presitter: Loaded preset data over the customization records.\n");
#endif
	}
	else fclose(SkipFile);
}

int __fastcall LoadProfile(MemCard* memcard)
{
	FUNC(0x00595F90, int, __thiscall, _LoadProfile, void*);
	int result = _LoadProfile(memcard);

	LoadPresets(memcard->GetPresetPath());

	return result;
}

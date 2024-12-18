#pragma once
#include "FECustomizationRecord.h"
#include "PresetCar.h"
#include "DBCarPart.h"
#include "FECarRecord.h"
#include "FEManager.h"
#include "MemCard.h"
#include "InGameFunctions.h"

void FillAutosculptZone(BYTE* zones, int zone, FECustomizationRecord* record)
{
	for (int i = 0; i < 11; i++)
	{
		zones[i] = record->GetSculptZoneAmount(zone, i) * 255.0f;
	}
}

void FillVinylColor(PresetCarVinylColor* vinylColor, int num, int col, FECustomizationRecord* record)
{
	RecordVinylColor colorData;
	record->GetVinylColor(num, col, &colorData);

	vinylColor->Swatch = colorData.Hue ? colorData.Hue->GetPartNameHash() : 0;
	vinylColor->Brightness = colorData.Brightness;
	vinylColor->Saturation = colorData.Saturation;
}

void FillVinyl(PresetCarVinyl* carVinyl, int num, FECustomizationRecord* record)
{
	auto vinylPart = record->GetInstalledVinyl(num);
	carVinyl->VectorVinyl = vinylPart ? vinylPart->GetPartNameHash() : 0;

	auto packed = record->GetInstalledVinylPacked(num);
	carVinyl->PositionX = packed ? packed->TranslationX : 0;
	carVinyl->PositionY = packed ? packed->TranslationY : 0;
	carVinyl->ScaleX = packed ? packed->ScaleX : 0;
	carVinyl->ScaleY = packed ? packed->ScaleY : 0;
	carVinyl->Skew = packed ? packed->Shear : 0;
	carVinyl->Rotation = packed ? packed->Rotation : 0;

	FillVinylColor(&carVinyl->Fill, num, 0, record);
	FillVinylColor(&carVinyl->Stroke, num, 1, record);
	FillVinylColor(&carVinyl->InnerShadow, num, 2, record);
	FillVinylColor(&carVinyl->InnerGlow, num, 3, record);
}

void FillCarPreset(PresetCar* preset, FECustomizationRecord* record, FECarRecord* carRecord)
{
	auto carType = carRecord->GetType();
	char* carTypeName = GetCarTypeName(carType);

	strcpy(preset->Model, carTypeName);
	sprintf(preset->CollectionName, "%u", carRecord->Handle);

	preset->VaultHash = carRecord->FEKey;
	preset->PVehicle = carRecord->VehicleKey;
	//preset->PresetKey = carRecord->Handle;

	for (int i = 0; i < (int)Slot::COUNT; i++)
	{
		auto part = record->GetInstalledPart(carType, (Slot)i);
		preset->Parts[i] = part ? part->GetPartNameHash() : 0;
	}

	ColorData colorData;
	record->GetColor(0, &colorData);

	preset->PaintSwatch = colorData.Part1 ? colorData.Part1->GetPartNameHash() : 0;
	preset->PaintGroup = colorData.Part2 ? colorData.Part2->GetPartNameHash() : 0;
	preset->Saturation = colorData.Saturation;
	preset->Brightness = colorData.Brightness;

	FillAutosculptZone(preset->Autosculpt.FrontBumper, ZoneFrontBumper, record);
	FillAutosculptZone(preset->Autosculpt.RearBumper, ZoneRearBumper, record);
	FillAutosculptZone(preset->Autosculpt.Skirt, ZoneSkirt, record);
	FillAutosculptZone(preset->Autosculpt.Spoiler, ZoneSpoiler, record);
	FillAutosculptZone(preset->Autosculpt.Wheels, ZoneFrontWheel, record);
	FillAutosculptZone(preset->Autosculpt.Hood, ZoneHood, record);
	FillAutosculptZone(preset->Autosculpt.RoofScoop, ZoneRoofScoop, record);
	FillAutosculptZone(preset->Autosculpt.Exhaust, ZoneExhaust, record);
	FillAutosculptZone(preset->Autosculpt.ChopTop, ZoneRoof, record);

	for (int i = 0; i < 20; i++)
	{
		FillVinyl(preset->Vinyls + i, i, record);
	}
}

void FillCarPreset(PresetCar* preset, FECarRecord* carRecord)
{
	auto carDB = FEManager::Instance()->GetPlayerCarDB();
	auto record = carDB->GetCustomizationRecordByHandle(carRecord->Customization);
	FillCarPreset(preset, record, carRecord);
}

void SavePresets(char* presetPath)
{
	auto carDB = FEManager::Instance()->GetPlayerCarDB();

	FILE* PresetFile = fopen(presetPath, "wb");
	if (PresetFile)
	{
		int count = 0;
		fwrite(&count, 4, 1, PresetFile);
		for (int i = 0; i < 200; i++)
		{
			auto carRecord = carDB->GetCarByIndex(i);
			if (carRecord->Handle != 0xFFFFFFFF)
			{
				auto record = carDB->GetCustomizationRecordByHandle(carRecord->Customization);
				if (record)
				{
					PresetCar presetCar;
					FillCarPreset(&presetCar, record, carRecord);
					fwrite(&presetCar, sizeof(PresetCar), 1, PresetFile);
					count++;
				}
			}
		}

		// write actual count
		fseek(PresetFile, 0, SEEK_SET);
		fwrite(&count, 4, 1, PresetFile);

		fclose(PresetFile);
	}
}

int __fastcall SaveProfile(MemCard* memcard, int, int a2)
{
	FUNC(0x0058E120, int, __thiscall, _SaveProfile, void*, int);
	int result = _SaveProfile(memcard, a2);

	SavePresets(memcard->GetPresetPath());

	return result;
}
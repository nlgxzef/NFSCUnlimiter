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
	for (int i = 0; i < NumAutosculptMorphTargets; i++)
	{
		zones[i] = record->GetSculptZoneAmount(zone, i) * 100.0f;
	}
}

void FillAutosculptZoneFloat(float* zones, int zone, FECustomizationRecord* record)
{
	for (int i = 0; i < NumAutosculptMorphTargets; i++)
	{
		zones[i] = record->GetSculptZoneAmount(zone, i);
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

	for (int i = 0; i < NumVinylLayers; i++)
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

void FillCarPresetASFloat(PresetCarAutosculptFloat* presetAS, FECustomizationRecord* record, FECarRecord* carRecord)
{
	FillAutosculptZoneFloat(presetAS->FrontBumper, ZoneFrontBumper, record);
	FillAutosculptZoneFloat(presetAS->RearBumper, ZoneRearBumper, record);
	FillAutosculptZoneFloat(presetAS->Skirt, ZoneSkirt, record);
	FillAutosculptZoneFloat(presetAS->Spoiler, ZoneSpoiler, record);
	FillAutosculptZoneFloat(presetAS->Wheels, ZoneFrontWheel, record);
	FillAutosculptZoneFloat(presetAS->Hood, ZoneHood, record);
	FillAutosculptZoneFloat(presetAS->RoofScoop, ZoneRoofScoop, record);
	FillAutosculptZoneFloat(presetAS->Exhaust, ZoneExhaust, record);
	FillAutosculptZoneFloat(presetAS->ChopTop, ZoneRoof, record);
}

void FillCarPresetASFloat(PresetCarAutosculptFloat* presetAS, FECarRecord* carRecord)
{
	auto carDB = FEManager::Instance()->GetPlayerCarDB();
	auto record = carDB->GetCustomizationRecordByHandle(carRecord->Customization);
	FillCarPresetASFloat(presetAS, record, carRecord);
}

void SavePresets(char* PresetPath)
{
	char FilePath[MAX_PATH];

	auto carDB = FEManager::Instance()->GetPlayerCarDB();

	CreateDirectoryA(PresetPath, 0);

	sprintf(FilePath, "%s\\SkipSave", PresetPath);
	FILE* SkipFile = fopen(FilePath, "rb");

	if (!SkipFile && carDB)
	{
		// Delete all files first
		for (int i = 0; i < NumFECustomizationRecords; i++)
		{
			// Create file handle
			sprintf(FilePath, "%s\\%02d.bin", PresetPath, i);
			FILE* PresetFile = fopen(FilePath, "rb");

			if (PresetFile)
			{
				fclose(PresetFile); // Close the file
				remove(FilePath); // Delete the file we just opened
			}
		}

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
					FILE* PresetFile = fopen(FilePath, "wb");

					if (PresetFile)
					{

						PresetCar presetCar;
						memset(&presetCar, (BYTE)0, sizeof(presetCar)); // fill with 0s, C++ inits with 0xCC by default
						FillCarPreset(&presetCar, record, carRecord);
						sprintf(presetCar.CollectionName, "CUSTOMIZATION_RECORD_%02d", carRecord->Customization); // Preset Name
						fwrite(&presetCar, sizeof(PresetCar), 1, PresetFile);

						// Close the file
						fclose(PresetFile);
					}

					if (PresitterAutosculpt) // Save AutoSculpt as floating point values
					{
						// Create file handle
						sprintf(FilePath, "%s\\%02d_AS.bin", PresetPath, carRecord->Customization);
						FILE* PresetASFile = fopen(FilePath, "wb");

						if (PresetASFile)
						{
							PresetCarAutosculptFloat presetAS;
							memset(&presetAS, (BYTE)0, sizeof(presetAS)); // fill with 0s
							FillCarPresetASFloat(&presetAS, record, carRecord);
							DWORD Header = bStringHash((char*)"BCHUNK_UNLIMITER_PRESITTERAUTOSCULPT");
							fwrite(&Header, sizeof(DWORD), 1, PresetASFile);
							DWORD Size = sizeof(presetAS);
							fwrite(&Size, sizeof(DWORD), 1, PresetASFile);
							fwrite(&presetAS, sizeof(presetAS), 1, PresetASFile);

							// Close the file
							fclose(PresetASFile);
						}
					}
				}
			}
		}
#ifdef _DEBUG
	bReleasePrintf("Presitter: Saved customization records as preset data.\n");
#endif
	}
	else fclose(SkipFile);
}

int __fastcall SaveProfile(MemCard* memcard, int, int a2)
{
	FUNC(0x0058E120, int, __thiscall, _SaveProfile, void*, int); // MemcardManager::Save(MemcardManager, MemcardManager::eSaveType)
	int result = _SaveProfile(memcard, a2);

	SavePresets(memcard->GetPresetPath());

	return result;
}
#include "stdafx.h"
#include "stdio.h"
#include <string>
#include <windows.h>
#include "includes\injector\injector.hpp"
#include "includes\IniReader.h"

int CarArraySize, CarCount, ReplacementCar, TrafficCarCount;
bool DisappearingWheelsFix, SecondaryLogoFix, ExpandMemoryPools, MissingPartsFix, VinylsFix, AddOnCopsDamageFix, SuperChargerFix, ForceStockPartsOnAddOnOpponents, UnlimitedPresetCars, FNGFix, NoPartsCrashFix, RimPaintFix, CopDestroyedStringHook;

#include "InGameFunctions.h"
#include "FEPackage.h"
#include "DALFeVehicle.h"
#include "PursuitInformation.h"
#include "GRacerInfo.h"
#include "Helpers.h"
#include "CodeCaves.h"

int Init()
{
	CIniReader Settings("NFSCUnlimiterSettings.ini");

	// Main
	//CarCount = Settings.ReadInteger("Main", "CarModelIDLimit", 127);
	ReplacementCar = Settings.ReadInteger("Main", "ReplacementModel", 1);
	TrafficCarCount = Settings.ReadInteger("Main", "TrafficCarCount", 10);
	UnlimitedPresetCars = Settings.ReadInteger("Fixes", "UnlimitedPresetCars", 0) != 0;
	CopDestroyedStringHook = Settings.ReadInteger("Main", "EnableCopDestroyedStringHook", 1) != 0;
	// Fixes
	DisappearingWheelsFix = Settings.ReadInteger("Fixes", "DisappearingWheelsFix", 1) != 0;
	MissingPartsFix = Settings.ReadInteger("Fixes", "MissingPartsFix", 1) != 0;
	RimPaintFix = Settings.ReadInteger("Fixes", "RimPaintFix", 0) != 0;
	VinylsFix = Settings.ReadInteger("Fixes", "VinylsFix", 1) != 0;
	SecondaryLogoFix = Settings.ReadInteger("Fixes", "SecondaryLogoFix", 1) != 0;
	AddOnCopsDamageFix = Settings.ReadInteger("Fixes", "AddOnCopsDamageFix", 1) != 0;
	SuperChargerFix = Settings.ReadInteger("Fixes", "SuperChargerFix", 1) != 0;
	FNGFix = Settings.ReadInteger("Fixes", "FNGFix", 1) != 0;
	NoPartsCrashFix = Settings.ReadInteger("Fixes", "NoPartsCrashFix", 1) != 0;
	// Misc
	ExpandMemoryPools = Settings.ReadInteger("Misc", "ExpandMemoryPools", 0) != 0;
	ForceStockPartsOnAddOnOpponents = Settings.ReadInteger("Misc", "ForceStockPartsOnAddOnOpponents", 0) != 0;

	if (MissingPartsFix)
	{
		// Fix Mising Parts (RideInfo::SetStockParts)
		injector::MakeRangedNOP(0x7DA7AD, 0x7DA7B3, true);
		injector::WriteMemory<WORD>(0x7DA7AD, 0xC030, true); // xor al,al
	}

	// Count Cars Automatically
	injector::MakeJMP(0x7CD306, DoUnlimiterStuffCodeCave, true); // LoaderCarInfo

	// Car Type Unlimiter
	injector::MakeJMP(0x7D67DB, CarCountCodeCave_RideInfo_SetPart, true);
	injector::MakeJMP(0x7D703B, CarCountCodeCave_RideInfo_FillWithPreset, true);
	injector::MakeJMP(0x7DA86B, CarCountCodeCave_RideInfo_SetStockParts, true);
	injector::MakeJMP(0x7DA8DB, CarCountCodeCave_RideInfo_SetStockParts_2, true);
	injector::MakeJMP(0x7DABCF, CarCountCodeCave_RideInfo_SetRandomPart, true);
	injector::MakeJMP(0x7DAC5B, CarCountCodeCave_RideInfo_SetRandomPart_2, true);
	injector::MakeJMP(0x7DAD1B, CarCountCodeCave_RideInfo_SetRandomPaint, true);
	injector::MakeJMP(0x7DADB2, CarCountCodeCave_RideInfo_FillWithPreset_PresetCar, true);
	injector::MakeJMP(0x7E6FF4, CarCountCodeCave_CarRenderConn_Construct, true);
	injector::MakeJMP(0x7E7084, CarCountCodeCave_HeliRenderConn_Construct, true);
	injector::MakeJMP(0x7B02CB, CarCountCodeCave_GetCarTypeInfoFromHash, true);
	injector::MakeJMP(0x7B0216, CarCountCodeCave_GetCarTypeNameHash, true);
	injector::MakeJMP(0x7D0D91, CarCountCodeCave_RasterizationManager_Initialize, true);
	injector::MakeJMP(0x6C092B, CarCountCodeCave_PVehicle_Resource_Resource, true);
	injector::MakeJMP(0x4BAC61, CarCountCodeCave_FECustomizationRecord_SetInstalledPart, true);
	injector::MakeJMP(0x4C4829, CarCountCodeCave_FECustomizationRecord_WriteRideIntoRecord, true);

	// Replacement model if model is not found in the array
	injector::WriteMemory<int>(0x7B0279, ReplacementCar, true); // CarPartDatabase::GetCarType

	// Fix crash if the model doesn't exist (Model will be invisible)
	injector::MakeJMP(0x7E4AE2, ReplacementCarCodeCave_CarLoader_Load, true); // CarLoader::Load

	// Can apply vinyls to new cars
	if (VinylsFix)
	{
		injector::WriteMemory<unsigned char>(0x7C68F2, 0xEB, true); // VinylSystem::CarAlignmentDB::GetTransform
	}

	// Traffic Pattern Unlimiter
	injector::WriteMemory<BYTE>(0x412ADE, TrafficCarCount, true); // AITrafficManager::TrafficPatternTimersClear (SpawnTraffic)
	injector::WriteMemory<int>(0x412AE4, TrafficCarCount, true); // AITrafficManager::TrafficPatternTimersClear (SpawnTraffic)
	injector::WriteMemory<BYTE>(0x422834, TrafficCarCount, true); // AITrafficManager::NextSpawn
	injector::WriteMemory<int>(0x422839, TrafficCarCount, true); // AITrafficManager::NextSpawn
	injector::WriteMemory<BYTE>(0x412B75, TrafficCarCount, true); // AITrafficManager::TrafficPatternTimersInit
	injector::WriteMemory<int>(0x412B7B, TrafficCarCount, true); // AITrafficManager::TrafficPatternTimersInit
	injector::WriteMemory<BYTE>(0x412C6A, TrafficCarCount, true); // AITrafficManager::TrafficPatternTimersUpdate
	injector::WriteMemory<int>(0x412C70, TrafficCarCount, true); // AITrafficManager::TrafficPatternTimersUpdate

	// Check the ini file for destroyed cops messages
	if (CopDestroyedStringHook)
	{
		injector::MakeCALL(0x5DB4DC, PursuitInformation_ShowFlashers, true); // PursuitInformation::Update
	}

	// Fix Invisible Wheels
	if (DisappearingWheelsFix)
	{
		injector::WriteMemory<unsigned char>(0x7BDDBC, 0x01, true); // CarPartCuller::CullParts
	}

	// 2nd logo fix
	if (SecondaryLogoFix)
	{
		injector::MakeRangedNOP(0x4BAB4A, 0x4BAB50, true); // FECarRecord::GetLogoHash(unsigned long)
	}

	// Expand Memory Pools (ty Berkay and Aero_)
	bool ExpandMemoryASIExists = DoesFileExist("ExpandMemoryPools.asi") || DoesFileExist("scripts\\ExpandMemoryPools.asi");
	if (ExpandMemoryPools && !ExpandMemoryASIExists)
	{
		injector::WriteMemory<int>(0x61D553, 0x2C8000, true); // GManager::GetVaultAllocator (0x2C8000)
		injector::WriteMemory<int>(0x61D573, 0x2C8000, true);

		injector::WriteMemory<int>(0x6B7659, 0x8000, true); // InitializeEverything (0x8000)

		injector::WriteMemory<DWORD>(0xA60DA0, 0x0BE6E0, true); // FEngMemoryPoolSize (InitFEngMemoryPool)
		injector::WriteMemory<DWORD>(0xA62C48, 0x01CC00, true); // CarLoaderPoolSizes

		// ePolySlotPool
		injector::WriteMemory<DWORD>(0x55B503, 0x7D000, true); // eInitEngine
	}

	// Damage Parts Fix for Add-On Cop Cars
	if (AddOnCopsDamageFix)
	{
		injector::MakeRangedNOP(0x7E627E, 0x7E62AB, true); // CarRenderInfo::CarRenderInfo
		injector::MakeJMP(0x7E627E, AddOnCopsDamageFixCodeCave, true);
	}

	// Fix Turbo/Supercharger
	if (SuperChargerFix)
	{
		injector::MakeCALL(0x4D4A4E, DALFeVehicle_GetCarUsesSupercharger, true); // DALFeVehicle::GetInt
	}

	// Force Stock Parts for Add-On Cars to fix Missing Parts on Opponents' Cars
	if (ForceStockPartsOnAddOnOpponents)
	{
		injector::MakeRangedNOP(0x7E19D3, 0x7E19DD, true); // RideInfo::SetRandomParts
		injector::MakeJMP(0x7E19D3, ForceStockPartsOnAddOnsCodeCave, true);
	}

	// Fix Rim Paint crash
	if (RimPaintFix)
	{
		injector::WriteMemory<BYTE>(0x861C45, 0xEB, true); // FeVisualPaint::FeVisualPaint
		/*
		injector::WriteMemory<DWORD>(0x7DFBF6, 0xD20EBC2F, true); // CarRenderInfo::Render
		injector::WriteMemory<DWORD>(0x7DFC3E, 0xD20EBC2F, true); // CarRenderInfo::Render
		injector::WriteMemory<DWORD>(0x7E5EF7, 0xD20EBC2F, true); // CarRenderInfo::CarRenderInfo
		*/
	}

	// Remove GlobalB.bun/lzc, BCHUNK_FEPRESETCARS count limiter
	if (UnlimitedPresetCars)
	{
		injector::WriteMemory<BYTE>(0x4D1723, 0xEB, true); // FEPlayerCarDB::CreateNewPresetCar
	}

	// Racer names count
	injector::MakeCALL(0x6B783F, InitSpaceNodesHook, true); // Count racers after InitSpaceNodes

	// Clone objects in FNG where needed
	if (FNGFix)
	{
		injector::MakeCALL(0x600564, CloneObjectstoShowMoreItemsInMenu, true); // FEPackageReader::Load
		//injector::MakeJMP(0x85FBE6, AddOnPartsFixCodeCave, true);
	}

	if (NoPartsCrashFix)
	{
		injector::MakeJMP(0x8401F9, NoPartsFixCodeCave, true); // FeCustomizeParts::ShowProperHelpBar
	}

	return 0;
}
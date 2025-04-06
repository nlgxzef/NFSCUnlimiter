#include "stdafx.h"
#include "stdio.h"
#include <string>
#include <windows.h>
#include "includes\injector\injector.hpp"
#include "includes\ini.h"

int CarArraySize, CarCount, ReplacementCar, TrafficCarCount;
bool DisappearingWheelsFix, SecondaryLogoFix, ExpandMemoryPools, MissingPartsFix, VinylsFix, AddOnCopsDamageFix, SuperChargerFix, ForceStockPartsOnAddOnOpponents, UnlimitedPresetCars, EnableFNGFixes, NoPartsCrashFix, RimPaintFix, CopDestroyedStringHook, Presitter, RideHeightFix, LightMaterialCrashFix, ChallengeSeriesOpponentNameFix, PresitterAutosculpt;

#include "InGameFunctions.h"
#include "GlobalVariables.h"
#include "DALFeVehicle.h"
#include "PursuitInformation.h"
#include "GRacerInfo.h"
#include "FEPackage.h"
#include "CarMemoryInfo.h"
#include "eModel.h"
#include "UnlimiterData.h"
#include "CodeCaves.h"
#include "Presitter.h"
#include "MemcardManager.h"

int Init()
{
	CurrentWorkingDirectory = std::filesystem::current_path();

	auto UnlimiterSettings = CurrentWorkingDirectory / "NFSCUnlimiterSettings.ini";
	mINI::INIFile NFSCUnlimiterSettingsINIFile(UnlimiterSettings.string());
	mINI::INIStructure Settings;
	NFSCUnlimiterSettingsINIFile.read(Settings);

	// Main
	ReplacementCar = mINI_ReadInteger(Settings, "Main", "ReplacementModel", 1);
	//TrafficCarCount = mINI_ReadInteger(Settings, "Main", "TrafficCarCount", 10);
	UnlimitedPresetCars = mINI_ReadInteger(Settings, "Fixes", "UnlimitedPresetCars", 0) != 0;
	CopDestroyedStringHook = mINI_ReadInteger(Settings, "Main", "EnableCopDestroyedStringHook", 1) != 0;
	Presitter = mINI_ReadInteger(Settings, "Main", "EnablePresitter", 1) != 0;

	// Fixes
	DisappearingWheelsFix = mINI_ReadInteger(Settings, "Fixes", "DisappearingWheelsFix", 1) != 0;
	MissingPartsFix = mINI_ReadInteger(Settings, "Fixes", "MissingPartsFix", 1) != 0;
	RimPaintFix = mINI_ReadInteger(Settings, "Fixes", "RimPaintFix", 0) != 0;
	VinylsFix = mINI_ReadInteger(Settings, "Fixes", "VinylsFix", 1) != 0;
	SecondaryLogoFix = mINI_ReadInteger(Settings, "Fixes", "SecondaryLogoFix", 1) != 0;
	AddOnCopsDamageFix = mINI_ReadInteger(Settings, "Fixes", "AddOnCopsDamageFix", 1) != 0;
	ChallengeSeriesOpponentNameFix = mINI_ReadInteger(Settings, "Fixes", "ChallengeSeriesOpponentNameFix", 1) != 0;
	LightMaterialCrashFix = mINI_ReadInteger(Settings, "Fixes", "LightMaterialCrashFix", 0) != 0;
	RideHeightFix = mINI_ReadInteger(Settings, "Fixes", "RideHeightFix", 1) != 0;
	SuperChargerFix = mINI_ReadInteger(Settings, "Fixes", "SuperChargerFix", 1) != 0;
	EnableFNGFixes = mINI_ReadInteger(Settings, "Fixes", "FNGFix", 1) != 0;
	NoPartsCrashFix = mINI_ReadInteger(Settings, "Fixes", "NoPartsCrashFix", 1) != 0;

	// Presitter
	PresitterAutosculpt = mINI_ReadInteger(Settings, "Presitter", "SaveAutosculptAsFloats", 1) != 0;

	// Misc
	ExpandMemoryPools = mINI_ReadInteger(Settings, "Misc", "ExpandMemoryPools", 0) != 0;
	ForceStockPartsOnAddOnOpponents = mINI_ReadInteger(Settings, "Misc", "ForceStockPartsOnAddOnOpponents", 0) != 0;

	// Check compatibility
	EMPCompatibility = GetModuleHandleA("ExpandMemoryPools.asi") ? 1 : 0;
	LimitAdjusterCompatibility = GetModuleHandleA("NFSCLimitAdjuster.asi") ? 1 : 0;

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
	injector::MakeCALL(0x6B77BD, CarInfo_InitResourceCost, true); // InitializeEverything

	// Replacement model if model is not found in the array
	injector::WriteMemory<int>(0x7B0279, ReplacementCar, true); // CarPartDatabase::GetCarType

	// Fix crash if the model doesn't exist (Model will be invisible)
	injector::MakeJMP(0x7E4AE2, ReplacementCarCodeCave_CarLoader_Load, true); // CarLoader::Load

	// Can apply vinyls to new cars
	if (VinylsFix)
	{
		injector::WriteMemory<unsigned char>(0x7C68F2, 0xEB, true); // VinylSystem::CarAlignmentDB::GetTransform
	}

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
	if (ExpandMemoryPools && !EMPCompatibility)
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

	// Always add both ride height values, not just when it's close enough (from chassis and ecar) (ty rx)
	if (RideHeightFix)
	{
		injector::MakeRangedNOP(0x7C1B6C, 0x7C1B72, true); // CarRenderConn::UpdateRenderMatrix
	}

	// (Attempt to) fix a crash with replacing light materials
	if (LightMaterialCrashFix)
	{
		injector::MakeJMP(0x55C0B0, eModel_ReplaceLightMaterial, true); // eModel::ReplaceLightMaterial (22 references)
	}

	// Fix challenge series character names
	if (ChallengeSeriesOpponentNameFix)
	{
		injector::MakeRangedNOP(0x62DA40, 0x62DA4D, true); // GRaceStatus::AddRacer
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
	if (EnableFNGFixes)
	{
		injector::MakeCALL(0x600564, CloneObjectstoShowMoreItemsInMenu, true); // FEPackageReader::Load
		//injector::MakeJMP(0x85FBE6, AddOnPartsFixCodeCave, true);
	}

	if (NoPartsCrashFix)
	{
		injector::MakeJMP(0x8401F9, NoPartsFixCodeCave, true); // FeCustomizeParts::ShowProperHelpBar
	}

	// Presitter: Dump/load presets when the profile is saved/loaded to work issues around with DBCarPart changes.
	if (Presitter)
	{
		// Saving
		//injector::WriteMemory(0x009D43A4, SaveProfile);
		//injector::WriteMemory(0x009E8D54, SaveProfile);
		hb_MemcardManager_SaveDone.fun = reinterpret_cast<int(__fastcall*)(MemCard*, void*, char const*)>(*(DWORD*)0x9D4308);
		injector::WriteMemory(0x9D4308, &MemcardManager_SaveDone, true); // MemcardManager::vtable
		injector::WriteMemory(0x9E8CB8, &MemcardManager_SaveDone, true); // PCMemcardManager::vtable??

		// Loading
		//injector::WriteMemory(0x009D441C, LoadProfile);
		//injector::WriteMemory(0x009E8DCC, LoadProfile);
		hb_MemcardManager_LoadDone.fun = reinterpret_cast<int(__fastcall*)(MemCard*, void*, char const*)>(*(DWORD*)0x9D4314);
		injector::WriteMemory(0x9D4314, &MemcardManager_LoadDone, true); // MemcardManager::vtable
		injector::WriteMemory(0x9E8CC4, &MemcardManager_LoadDone, true); // PCMemcardManager::vtable??

		// Dump Single Preset
		injector::MakeJMP(0x008462A0, FECustomizeStateManager_HandlePadButton3);
		injector::WriteMemory(0x009FAD80, FECustomizeStateManager_HandleButtonPressed);

		// Deleting
		hb_rmdir.fun = injector::MakeCALL(0x895AE2, Presitter_Delete, true).get(); // RealmcIface::MemcardInterfaceImpl::ProcessDelete
	}

#ifdef _DEBUG
	injector::WriteMemory(0x00A85340, 1, true); // bReleasePrintf
#endif

	return 0;
}
#include "stdafx.h"
#include "stdio.h"
#include <string>
#include <windows.h>
#include "includes\injector\injector.hpp"
#include "includes\IniReader.h"

int CarCount, ReplacementCar, TrafficCarCount;
bool DisappearingWheelsFix, SecondaryLogoFix, ExpandMemoryPools, OnlineLoginCrashFix, MissingPartsFix, VinylsFix;

void __declspec(naked) CarCountCodeCave_RideInfo_SetPart()
{
	__asm
	{
		cmp eax, CarCount
		jl loc_7D67D0

		caveexit :
			push 0x7D67E0
			retn

		loc_7D67D0 :
			push 0x7D67D0
			retn
	}
}

void __declspec(naked) CarCountCodeCave_RideInfo_FillWithPreset()
{
	__asm
	{
		cmp ecx, CarCount
		jl loc_7D7030

		caveexit :
			push 0x7D7040
			retn

		loc_7D7030 :
			push 0x7D7030
			retn
	}
}

void __declspec(naked) CarCountCodeCave_RideInfo_SetStockParts()
{
	__asm
	{
		cmp ecx, CarCount
		jl loc_7DA860

		caveexit :
			push 0x7DA870
			retn

		loc_7DA860 :
			push 0x7DA860
			retn
	}
}

void __declspec(naked) CarCountCodeCave_RideInfo_SetStockParts_2()
{
	__asm
	{
		cmp ecx, CarCount
		jl loc_7DA8D0

		caveexit :
			push 0x7DA8E0
			retn

		loc_7DA8D0 :
			push 0x7DA8D0
			retn
	}
}

void __declspec(naked) CarCountCodeCave_RideInfo_SetRandomPart()
{
	__asm
	{
		cmp ecx, CarCount
		jl loc_7DABC4

		caveexit :
			push 0x7DABD4
			retn

		loc_7DABC4 :
			push 0x7DABC4
			retn
	}
}

void __declspec(naked) CarCountCodeCave_RideInfo_SetRandomPart_2()
{
	__asm
	{
		cmp ecx, CarCount
		jl loc_7DAC50

		caveexit :
			push 0x7DAC60
			retn

		loc_7DAC50 :
			push 0x7DAC50
			retn
	}
}

void __declspec(naked) CarCountCodeCave_RideInfo_SetRandomPaint()
{
	__asm
	{
		cmp eax, CarCount
		jl loc_7DAD10

		caveexit :
			push 0x7DAD20
			retn

		loc_7DAD10 :
			push 0x7DAD10
			retn
	}
}

void __declspec(naked) CarCountCodeCave_RideInfo_FillWithPreset_PresetCar()
{
	__asm
	{
		cmp ecx, CarCount
		jl loc_7DADA7

		caveexit :
			push 0x7DADB7
			retn

		loc_7DADA7 :
			push 0x7DADA7
			retn
	}
}

void __declspec(naked) CarCountCodeCave_CarRenderConn_Construct()
{
	__asm
	{
		cmp esi, CarCount
		jge loc_7E7036

		caveexit :
			push 0x7E6FF9
			retn

		loc_7E7036 :
			push 0x7E7036
			retn
	}
}

void __declspec(naked) CarCountCodeCave_HeliRenderConn_Construct()
{
	__asm
	{
		cmp esi, CarCount
		jge loc_7E70C6

		caveexit :
			push 0x7E7089
			retn

		loc_7E70C6 :
			push 0x7E70C6
			retn
	}
}

void __declspec(naked) CarCountCodeCave_GetCarTypeInfoFromHash()
{
	__asm
	{
		cmp eax, CarCount
		jl loc_7B02C0

		caveexit :
			push 0x7B02D0
			retn

		loc_7B02C0 :
			push 0x7B02C0
			retn
	}
}

void __declspec(naked) CarCountCodeCave_GetCarTypeNameHash()
{
	__asm
	{
		cmp ecx, CarCount
		jz locret_7B023B

		caveexit :
			push 0x7B021B
			retn

		locret_7B023B :
			push 0x7B023B
			retn
	}
}

void __declspec(naked) CarCountCodeCave_RasterizationManager_Initialize()
{
	_asm
	{
		xor eax,eax
		cmp ecx, CarCount
		push 0x7D0D96
		retn
	}
}

void __declspec(naked) CarCountCodeCave_PVehicle_Resource_Resource()
{
	__asm
	{
		cmp eax, CarCount
		jge loc_6C098C

		caveexit :
			push 0x6C0930
			retn

		loc_6C098C :
			push 0x6C098C
			retn
	}
}

int Init()
{
	CIniReader Settings("NFSCUnlimiterSettings.ini");

	// Main
	CarCount = Settings.ReadInteger("Main", "CarModelIDLimit", 127);
	ReplacementCar = Settings.ReadInteger("Main", "ReplacementModel", 1);
	TrafficCarCount = Settings.ReadInteger("Main", "TrafficCarCount", 20);
	// Fixes
	DisappearingWheelsFix = Settings.ReadInteger("Fixes", "DisappearingWheelsFix", 1) == 1;
	MissingPartsFix = Settings.ReadInteger("Fixes", "MissingPartsFix", 1) == 1;
	VinylsFix = Settings.ReadInteger("Fixes", "VinylsFix", 1) == 1;
	SecondaryLogoFix = Settings.ReadInteger("Fixes", "SecondaryLogoFix", 1) == 1;
	//OnlineLoginCrashFix = Settings.ReadInteger("Fixes", "OnlineLoginCrashFix", 1) == 1;
	// Misc
	ExpandMemoryPools = Settings.ReadInteger("Misc", "ExpandMemoryPools", 0) == 1;

	if (MissingPartsFix)
	{
		// Fix Mising Parts (RideInfo::SetStockParts)
		injector::MakeRangedNOP(0x7DA7AD, 0x7DA7B3, true);
		injector::WriteMemory<WORD>(0x7DA7AD, 0xC030, true); // xor al,al
	}
	
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

	injector::WriteMemory<int>(0x7B11F5, CarCount, true);

	injector::WriteMemory<int>(0x7B0270, CarCount * 0xD0, true); // CarPartDatabase::GetCarType
	injector::WriteMemory<int>(0x7B0279, ReplacementCar, true); // Replacement model if model not found

	injector::WriteMemory<int>(0x850819, CarCount * 0xD0, true); // sub_850740

	// Can apply vinyls to new cars
	if (VinylsFix)
	{
		injector::WriteMemory<unsigned char>(0x7C68F2, 0xEB, true);
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
													  
	// Fix Invisible Wheels
	if (DisappearingWheelsFix)
	{
		injector::WriteMemory<unsigned char>(0x7BDDBC, 0x01, true);
	}

	// 2nd logo fix
	if (SecondaryLogoFix)
	{
		injector::MakeRangedNOP(0x4BAB4A, 0x4BAB50, true);
	}

	// Online Login Crash Fix
	/*if (OnlineLoginCrashFix)
	{
		injector::MakeNOP(0x0060BAB7, 10, true);
	}*/
	
	// Expand Memory Pools (ty Berkay)
	if (ExpandMemoryPools)
	{
		injector::WriteMemory<int>(0x61D553, 0x2C8000, true); // GManager::GetVaultAllocator (0x2C8000)
		injector::WriteMemory<int>(0x61D573, 0x2C8000, true);

		injector::WriteMemory<int>(0x6B7659, 0x8000, true); // InitializeEverything (0x8000)

		injector::WriteMemory<DWORD>(0xA60DA0, 0x0BE6E0, true); // FEngMemoryPoolSize (InitFEngMemoryPool)
		injector::WriteMemory<DWORD>(0xA62C48, 0x01CC00, true); // CarLoaderPoolSizes
	}
	
	return 0;
}

BOOL APIENTRY DllMain(HMODULE /*hModule*/, DWORD reason, LPVOID /*lpReserved*/)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		uintptr_t base = (uintptr_t)GetModuleHandleA(NULL);
		IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)(base);
		IMAGE_NT_HEADERS* nt = (IMAGE_NT_HEADERS*)(base + dos->e_lfanew);

		if ((base + nt->OptionalHeader.AddressOfEntryPoint + (0x400000 - base)) == 0x87E926) // Check if .exe file is compatible - Thanks to thelink2012 and MWisBest
		{
			Init();
		}
		else
		{
			MessageBoxA(NULL, "This .exe is not supported.\nPlease use v1.4 English nfsc.exe (6,88 MB (7.217.152 bytes)).", "NFSC Unlimiter", MB_ICONERROR);
			return FALSE;
		}
	}
	return TRUE;
}

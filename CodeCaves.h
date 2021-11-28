#pragma once

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
		xor eax, eax
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

void __declspec(naked) CarCountCodeCave_FECustomizationRecord_SetInstalledPart()
{
	_asm
	{
		cmp ebx, CarCount
		jl loc_4BAC78
		push 0x4BAC66
		retn

		loc_4BAC78 :
			push 0x4BAC78
			retn
	}
}

void __declspec(naked) CarCountCodeCave_FECustomizationRecord_WriteRideIntoRecord()
{
	_asm
	{
		cmp eax, CarCount
		jl loc_4C4840
		push 0x4C482E
		retn

		loc_4C4840 :
			push 0x4C4840
			retn
	}
}

void __declspec(naked) DoUnlimiterStuffCodeCave()
{
	// Get count
	__asm
	{
		mov dword ptr ds : [CarTypeInfoArray] , edx
		sub edx, 0x0C
		mov edx, [edx]
		mov CarArraySize, edx
		mov edx, dword ptr ds : [CarTypeInfoArray]
		pushad
	}

	CarArraySize -= 8;
	CarCount = CarArraySize / SingleCarTypeInfoBlockSize;

	// Do required stuff
	injector::WriteMemory<int>(0x7B11F5, CarCount, true);
	injector::WriteMemory<int>(0x7B0270, CarCount * SingleCarTypeInfoBlockSize, true); // CarPartDatabase::GetCarType
	injector::WriteMemory<int>(0x850819, CarCount * SingleCarTypeInfoBlockSize, true); // sub_850740

	// Continue
	__asm
	{
		popad
		push 0x7CD30C
		retn
	}
}

void __declspec(naked) AddOnCopsDamageFixCodeCave()
{
	__asm
	{
		cmp eax, 0x55 // COPHELI
		je jWindowDamage
		cmp eax, 0x56 // COPMIDSIZEINT
		je jWindowDamage
		push eax // Car Type ID
		call IsCop
		add esp, 4
		cmp al, 1
		je jDamageParts
		jmp jWindowDamage

		jDamageParts :
			push 0x7E62AB
			retn

		jWindowDamage :
			push 0x7E62E2
			retn
	}
}

void __declspec(naked) ForceStockPartsOnAddOnsCodeCave()
{
	__asm
	{
		cmp[ecx], 95
		jge jLessRandomParts // 95+ = Add-On
		jmp jSetRandomParts

		jLessRandomParts :
			cmp eax, 0x17 // BODY
			je jCaveExit
			cmp eax, 0x30 // SPOILER
			je jCaveExit
			cmp eax, 0x4D // ROOF_SCOOP
			je jCaveExit
			cmp eax, 0x4E // HOOD
			je jCaveExit

		jSetRandomParts :
			push -1
			push eax
			call RideInfo_SetRandomPart

		jCaveExit :
			sub esi, ebx
			push 0x7E19DD
			retn
	}
}

void __declspec(naked) NoPartsFixCodeCave()
{
	_asm
	{
		test eax, eax
		jnz jContinue

		pop esi
		retn

		jContinue :
			mov ecx, [eax + 0x98]
			push 0x8401FF
			retn
	}
}

void __declspec(naked) ReplacementCarCodeCave_CarLoader_Load()
{
	_asm
	{
		mov edx, ReplacementCar
		mov[ebx], edx
		push 0x7E4AE7
		retn
	}
}
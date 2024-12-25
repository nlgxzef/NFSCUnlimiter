#pragma once
#include "Defines.h"

struct FECarRecord
{
	DWORD Handle;
	DWORD FEKey;
	DWORD VehicleKey;
	DWORD PresetKey;
	BYTE Customization;
	BYTE CareerHandle;
	WORD Padd;

	static FECarRecord* Instance()
	{
		FECarRecord** gFECarRecord = (FECarRecord**)0x00BBABAC;
		return *gFECarRecord;
	}

	static CarType GetCarType()
	{
		auto record = Instance();
		return record ? record->GetType() : CarType(-1);
	}

	CarType GetType()
	{
		static auto _GetType = (CarType(__thiscall*)(FECarRecord*))0x004AE150;
		return _GetType(this);
	}
};
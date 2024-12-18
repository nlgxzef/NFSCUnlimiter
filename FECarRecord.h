#pragma once
#include "Defines.h"

struct FECarRecord
{
	unsigned int Handle;
	unsigned int FEKey;
	unsigned int VehicleKey;
	unsigned int PresetKey;
	unsigned int Customization;

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
#pragma once
#include "FECustomizationRecord.h"
#include "FECarRecord.h"

struct FEPlayerCarDB
{
	FECarRecord* GetCarByIndex(int i)
	{
		FUNC(0x0049C080, FECarRecord*, __thiscall, _GetCarByIndex, FEPlayerCarDB*, int);
		return _GetCarByIndex(this, i);
	}

	FECarRecord* GetCarByHandle(Hash i)
	{
		FUNC(0x0049C020, FECarRecord*, __thiscall, _GetCarByHandle, FEPlayerCarDB*, Hash);
		return _GetCarByHandle(this, i);
	}

	FECustomizationRecord* GetCustomizationRecordByHandle(unsigned char handle)
	{
		FUNC(0x0049C360, FECustomizationRecord*, __thiscall, _GetCustomizationRecordByHandle, FEPlayerCarDB*, unsigned char);
		return _GetCustomizationRecordByHandle(this, handle);
	}
};

struct FEManager
{
	static FEManager* Instance()
	{
		return *(FEManager**)0x00A97A7C;
	}

	char* GetUserProfile(int a)
	{
		FUNC(0x00572B90, char*, __thiscall, _GetUserProfile, FEManager*, int);
		return _GetUserProfile(this, a);
	}

	FEPlayerCarDB* GetPlayerCarDB()
	{
		return (FEPlayerCarDB*)(this->GetUserProfile(0) + 0x234);
	}
};
#pragma once
#include "DBCarPart.h"
#include "Defines.h"
#include "Slots.h"

struct RecordColorData
{
	BYTE Brightness;
	BYTE Saturation;
};

struct RecordVinylColor
{
	BYTE Brightness;
	BYTE Saturation;
	DBCarPart* Hue;
};

struct VinylPacked
{
	short TranslationX;
	short TranslationY;
	char Rotation;
	char Shear;
	char ScaleX;
	char ScaleY;
};

struct ColorData
{
	BYTE Brightness;
	BYTE Saturation;
	DBCarPart* Part1;
	DBCarPart* Part2;
};

struct FECustomizationRecord
{
	void SetVinylColor(int vinyl, int col, RecordColorData color, DBCarPart* hue)
	{
		FUNC(0x004AE490, void, __thiscall, _SetVinyl, FECustomizationRecord*, int, int, RecordColorData, DBCarPart*, int);
		_SetVinyl(this, vinyl, col, color, hue, 0);
	}

	void SetInstalledVinyl(int vinyl, DBCarPart* part)
	{
		FUNC(0x004AE3E0, DBCarPart*, __thiscall, _SetInstalledVinyl, FECustomizationRecord*, int, DBCarPart*);
		_SetInstalledVinyl(this, vinyl, part);
	}

	bool SetInstalledPart(Slot slot, DBCarPart* part, CarType carId, bool setOnly)
	{
		static auto _SetInstalledPart = (bool(__thiscall*)(FECustomizationRecord*, Slot, DBCarPart*, CarType, bool))0x004BAC50;
		return _SetInstalledPart(this, slot, part, carId, setOnly);
	}

	void WriteColor(int colorNum, RecordColorData hs, DBCarPart* part1, DBCarPart* part2)
	{
		FUNC(0x0049C5C0, void, __thiscall, _WriteColor, FECustomizationRecord*, int, RecordColorData, DBCarPart*, DBCarPart*);
		_WriteColor(this, colorNum, hs, part1, part2);
	}

	float GetSculptZoneAmount(int part, int zone)
	{
		FUNC(0x0049C790, float, __thiscall, _GetSculptZoneAmount, FECustomizationRecord*, int, int);
		return _GetSculptZoneAmount(this, part, zone);
	}

	void GetVinylColor(int vinyl, int col, RecordVinylColor* out)
	{
		FUNC(0x004AE5F0, void, __thiscall, _GetVinylColor, FECustomizationRecord*, int, int, RecordVinylColor*);
		_GetVinylColor(this, vinyl, col, out);
	}

	DBCarPart* GetInstalledVinyl(int vinyl)
	{
		FUNC(0x004AE570, DBCarPart*, __thiscall, _GetInstalledVinyl, FECustomizationRecord*, int);
		return _GetInstalledVinyl(this, vinyl);
	}

	VinylPacked* GetInstalledVinylPacked(int vinyl)
	{
		FUNC(0x004AE5C0, VinylPacked*, __thiscall, _GetInstalledVinyl, FECustomizationRecord*, int);
		return _GetInstalledVinyl(this, vinyl);
	}

	DBCarPart* GetInstalledPart(CarType carId, Slot slot)
	{
		static auto _GetInstalledPart = (DBCarPart * (__thiscall*)(FECustomizationRecord*, CarType, Slot))0x004AE350;
		return _GetInstalledPart(this, carId, slot);
	}

	void GetColor(int colorNum, ColorData* paintData)
	{
		FUNC(0x0049C540, void, __thiscall, _GetColor, FECustomizationRecord*, int, ColorData*);
		_GetColor(this, colorNum, paintData);
	}
};
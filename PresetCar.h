#pragma once
#include "Defines.h"

struct PresetCarVinylColor
{
	Hash Swatch;
	BYTE Saturation;
	BYTE Brightness;
};

struct PresetCarVinyl
{
	Hash VectorVinyl;
	short PositionX;
	short PositionY;
	BYTE Rotation;
	BYTE Skew;
	BYTE ScaleX;
	BYTE ScaleY;

	PresetCarVinylColor Fill;
	PresetCarVinylColor Stroke;
	PresetCarVinylColor InnerShadow;
	PresetCarVinylColor InnerGlow;
};

struct PresetCarAutosculpt
{
	BYTE FrontBumper[11];
	BYTE RearBumper[11];
	BYTE Skirt[11];
	BYTE Wheels[11];
	BYTE Hood[11];
	BYTE Spoiler[11];
	BYTE RoofScoop[11];
	BYTE ChopTop[11];
	BYTE Exhaust[11];
	BYTE Pad = 0;
};

struct PresetCar
{
	__int64 Version = 0;

	char Model[32];
	char CollectionName[32];

	Hash VaultHash;
	Hash PresetKey;
	Hash PVehicle;

	int Zero1[3] = { 0, 0, 0 };

	Hash Parts[0x6A];

	int IsCarbonStyle = true;
	Hash PaintGroup;
	Hash PaintSwatch;
	float Saturation;
	float Brightness;

	int Zero2[4] = { 0, 0, 0, 0 };

	PresetCarAutosculpt Autosculpt;

	PresetCarVinyl Vinyls[20];
};
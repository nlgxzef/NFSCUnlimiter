#pragma once
#include <stdio.h>
#include "Defines.h"

struct ProfileData
{
	BYTE unk[0x330];
	char Folder[32];
	char Name[32];
	char Path[260];
};

struct MemCard
{
	BYTE unk[0xB4];
	ProfileData** Profile;

	char* GetPresetPath()
	{
		static char PresetPath[260];

		ProfileData* profileData = *this->Profile;
		sprintf(PresetPath, "%s\\%s\\PRESETS", profileData->Path, profileData->Folder);
		return PresetPath;
	}
};

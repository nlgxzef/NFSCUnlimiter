#pragma once

//static injector::hook_back<HRESULT(WINAPI*)(HWND, int, HANDLE, DWORD, LPSTR)> hb_SHGetFolderPathA;
static injector::hook_back<unsigned int(*)(char const*)> hb_rmdir;

int Presitter_Delete(char const* Path)
{
	char PresetFolderPath[MAX_PATH];
	char PresetPath[MAX_PATH];

	// Get preset folder
	sprintf(PresetFolderPath, "%s\\Presets", Path);

	// Get rid of SkipSave and SkipLoad first
	sprintf(PresetPath, "%s\\SkipSave", Path);
	FILE* SkipFile = fopen(PresetPath, "rb");
	if (SkipFile)
	{
		fclose(SkipFile); // Close the file
		remove(PresetPath); // Delete the file we just opened
	}

	sprintf(PresetPath, "%s\\SkipLoad", Path);
	SkipFile = fopen(PresetPath, "rb");
	if (SkipFile)
	{
		fclose(SkipFile); // Close the file
		remove(PresetPath); // Delete the file we just opened
	}

	// Empty the directory
	for (int i = 0; i < NumFECustomizationRecords; i++)
	{
		// Create file handle
		sprintf(PresetPath, "%s\\%02d.bin", PresetFolderPath, i);
		FILE* PresetFile = fopen(PresetPath, "rb");

		if (PresetFile)
		{
			fclose(PresetFile); // Close the file
			remove(PresetPath); // Delete the file we just opened
		}
	}

	// Delete the directory
	hb_rmdir.fun(PresetFolderPath);

#ifdef _DEBUG
	bReleasePrintf("Presitter: Deleted preset data.\n");
#endif

	return hb_rmdir.fun(Path);
}

#include "DumpCarPreset.h"
#include "SaveCarPreset.h"
#include "LoadCarPreset.h"
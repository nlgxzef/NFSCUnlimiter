#pragma once

#include "stdio.h"
#include "InGameFunctions.h"

static injector::hook_back<int(__fastcall*)(MemCard*, void*, char const*)> hb_MemcardManager_SaveDone;
int __fastcall MemcardManager_SaveDone(MemCard* memcard, void* EDX_Unused, char const* ProfileName)
{
	SavePresets(memcard->GetPresetPath());

	return hb_MemcardManager_SaveDone.fun(memcard, EDX_Unused, ProfileName);
}

static injector::hook_back<int(__fastcall*)(MemCard*, void*, char const*)> hb_MemcardManager_LoadDone;
int __fastcall MemcardManager_LoadDone(MemCard* memcard, void* EDX_Unused, char const* ProfileName)
{
	int result = hb_MemcardManager_LoadDone.fun(memcard, EDX_Unused, ProfileName);

	LoadPresets(memcard->GetPresetPath());

	return result;
}
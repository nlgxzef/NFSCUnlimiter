#pragma once

#include "stdio.h"
#include "InGameFunctions.h"

static injector::hook_back<int(__fastcall*)(DWORD*, void*, char const*)> hb_MemcardManager_SaveDone;
int __fastcall MemcardManager_SaveDone(DWORD* MemcardManager, void* EDX_Unused, char const* ProfileName)
{
	//Presitter_Save(ProfileName);

	return hb_MemcardManager_SaveDone.fun(MemcardManager, EDX_Unused, ProfileName);
}

static injector::hook_back<int(__fastcall*)(DWORD*, void*, char const*)> hb_MemcardManager_LoadDone;
int __fastcall MemcardManager_LoadDone(DWORD* MemcardManager, void* EDX_Unused, char const* ProfileName)
{
	int result = hb_MemcardManager_LoadDone.fun(MemcardManager, EDX_Unused, ProfileName);

	//Presitter_Load(ProfileName);

	return result;
}
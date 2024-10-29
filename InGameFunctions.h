#pragma once

#include "stdio.h"
#include <windows.h>
#include "GlobalVariables.h"

unsigned int(*bStringHash)(char* StringToHash) = (unsigned int(*)(char*))0x471050;
unsigned int(*stringhash32)(char* StringToHash) = (unsigned int(*)(char*))0x606B60;
bool(*bFileExists)(char* Path) = (bool(*)(char*))0x6B2360;
int(*bFileSize)(char* Path) = (int(*)(char*))0x6B2300;
void* (*j_malloc)(size_t) = (void* (*)(size_t))0x6A1550;
DWORD*(*Attrib_DefaultDataArea)(unsigned int Unk) = (DWORD * (*)(unsigned int))0x678410;
void(__thiscall* Attrib_Instance_ctInstance)(DWORD* Attrib, DWORD* Collection, unsigned int msgPort) = (void(__thiscall*)(DWORD*, DWORD*, unsigned int))0x461340;
void(__thiscall* Attrib_Instance_dtInstance)(DWORD* Attrib) = (void(__thiscall*)(DWORD*))0x469870;
void(__thiscall* RideInfo_SetRandomPart)(DWORD* RideInfo, int CarSlotID, int Unk) = (void(__thiscall*)(DWORD*, int, int))0x7DA970;
DWORD*(__thiscall* Attrib_Instance_GetAttributePointer)(DWORD* Attrib, unsigned int CollectionKey, unsigned int msgPort) = (DWORD*(__thiscall*)(DWORD*, unsigned int, unsigned int))0x463A80;
DWORD*(* Attrib_FindCollection)(unsigned int CollectionKey, unsigned int msgPort) = (DWORD*(*)(unsigned int, unsigned int))0x465930;
void(__thiscall* Attrib_Gen_pvehicle_Create)(DWORD* Attrib_Gen_pvehicle, unsigned int CollectionKey, unsigned int msgPort) = (void(__thiscall*)(DWORD*, unsigned int, unsigned int))0x412520;
void(__thiscall* Attrib_Gen_frontend_Create)(DWORD* Attrib_Gen_frontend, unsigned int CollectionKey, unsigned int msgPort) = (void(__thiscall*)(DWORD*, unsigned int, unsigned int))0x4ABF30;
bool(__thiscall* FEPackage_Startup)(DWORD* FEPackage, DWORD* FEGameInterface) = (bool(__thiscall*)(DWORD*, DWORD*))0x5F7B30;
DWORD* (__thiscall* FEPackage_FindObjectByHash)(DWORD* FEPackage, unsigned int ObjectHash) = (DWORD * (__thiscall*)(DWORD*, unsigned int))0x5F3760;
DWORD* (__thiscall* FEObject_Clone)(DWORD* FEObject, bool) = (DWORD * (__thiscall*)(DWORD*, bool))0x5FEB80;
DWORD* (__thiscall* FEGroup_Clone)(DWORD* FEGroup, bool) = (DWORD * (__thiscall*)(DWORD*, bool))0x6001C0;
void(__thiscall* FEPackage_BuildMouseObjectStateList)(DWORD*) = (void(__thiscall*)(DWORD*))0x5F3B70;
void(__thiscall* FEPackage_ConnectObjectResources)(DWORD*) = (void(__thiscall*)(DWORD*))0x5F3A80;
void(__thiscall* FEMinList_AddNode)(DWORD* FEMinList, DWORD* FEMinNode, DWORD* FEObject) = (void(__thiscall*)(DWORD*, DWORD*, DWORD*))0x5EA370;
int(* Physics_Info_InductionType)(DWORD* Attrib_Gen_induction) = (int(*)(DWORD*))0x6C2750;
bool(__thiscall* DALManager_GetInt)(DWORD* TheDALManager, const int valueType, int* getVal, const int arg1, const int arg2, const int arg3) = (bool(__thiscall*)(DWORD*, int, int*, const int, const int, const int))0x4A0490;
bool(__thiscall* DALManager_GetFloat)(DWORD* TheDALManager, const int valueType, float* getVal, const int arg1, const int arg2, const int arg3) = (bool(__thiscall*)(DWORD*, int, float*, const int, const int, const int))0x4A0350;
DWORD*(*EventSys_Event_Allocate)(int size, int priority) = (DWORD*(*)(int, int))0x561590;
char const*(*GetLocalizedString)(DWORD StringHash) = (char const*(*)(DWORD))0x578830;
void(__thiscall* EFlasherGeneric_ct)(DWORD* EFlasherGeneric, int pPlayerIndex, const char* pString, int pIconHash, int pScript, int pMessageMode, int pMessagePlacement, int pMessagePriority) = (void(__thiscall*)(DWORD*, int, char const*, int, int, int, int, int))0x67C290;
void(__thiscall* EHideLoopingFlasherGeneric_ct)(DWORD* EHideLoopingFlasherGeneric, int pPlayerIndex, int pMessagePlacement, int pMessagePriority) = (void(__thiscall*)(DWORD*, int, int, int))0x67C640;
int(*bSNPrintf)(char* buf, int len, char const* fmt, ...) = (int(*)(char*, int, char const*, ...))0x475C30;
void(__thiscall* PursuitInformation_ShowFlashers_Game)(DWORD* PursuitInformation, DWORD* IPlayer, bool ShouldShowBountyMessage) = (void(__thiscall*)(DWORD*, DWORD*, bool))0x5D3CF0;
bool(*DoesStringExist)(unsigned int StringHash) = (bool(*)(unsigned int))0x578670;
void(*InitSpaceNodes)() = (void(*)())0x7AFEF0;
void(*CarInfo_InitResourceCost_Game)() = (void(*)())0x7B11F0;
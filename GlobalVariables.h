#pragma once

#define CarTypeInfoArray 0xB74CCC
#define SingleCarTypeInfoBlockSize 0xD0

#define NumFECarRecords 200
#define NumFECustomizationRecords 75
#define NumCarSlots 106
#define NumAutosculptMorphTargets 11
#define NumVinylLayers 20
#define CarNameLength 32
#define PresetNameLength 32
#define PresetFileLength 1536

#define _FEGroup_vtbl 0x9D7654
#define _gFECarRecord 0xBBABAC
#define _gTheDALManager 0xA8AD30
#define _WorldTimer 0xA99C3C
#define _FEManager_mInstance 0xA97A7C
#define _CarPartDB 0xB76690

bool EMPCompatibility = 0;
bool LimitAdjusterCompatibility = 0;

// Default values for Vinyl Groups if _CopDestroyedStrings.ini is N/A
#define DefaultCopDestroyedStringCount 13

char* DefaultCopDestroyedStringPVehicles[]
{
	(char*)"",
	(char*)"copcross",
	(char*)"copsport",
	(char*)"copmidsize",
	(char*)"copmidsize_ce",
	(char*)"copmidsize_weak",
	(char*)"copghost",
	(char*)"copgto",
	(char*)"copgtoghost",
	(char*)"copsporthench",
	(char*)"copsportghost",
	(char*)"copsuv",
	(char*)"copsuvpatrol",
	(char*)"copsuvl"
};

char* DefaultCopDestroyedStrings[]
{
	(char*)"HUD_COPDESTROYED_DEFAULT",
	(char*)"HUD_COPDESTROYED_COPCROSS",
	(char*)"HUD_COPDESTROYED_COPCROSS",
	(char*)"HUD_COPDESTROYED_COPMIDSIZE",
	(char*)"HUD_COPDESTROYED_COPMIDSIZE",
	(char*)"HUD_COPDESTROYED_COPMIDSIZE",
	(char*)"HUD_COPDESTROYED_COPGHOST",
	(char*)"HUD_COPDESTROYED_COPGTO",
	(char*)"HUD_COPDESTROYED_COPGTOGHOST",
	(char*)"HUD_COPDESTROYED_COPSPORTHENCH",
	(char*)"HUD_COPDESTROYED_COPSPORTGHOST",
	(char*)"HUD_COPDESTROYED_COPSUV",
	(char*)"HUD_COPDESTROYED_COPSUV",
	(char*)"HUD_COPDESTROYED_COPSUVL"
};

// _FNGFixes.ini
typedef struct
{
	char Prefix[64];
} Child;

typedef struct
{
	char FNGName[64];
	char ObjectPrefix[64];
	int NumberOfObjects;
	std::vector<Child> Children;
} FNGFix;

std::vector<FNGFix> FNGFixes;

// _CopDestroyedStrings.ini
typedef struct
{
	DWORD PVehicle;
	DWORD StringHash;
} CopDestroyedString;

std::vector<CopDestroyedString> CopDestroyedStrings;

std::filesystem::path CurrentWorkingDirectory;

int* CarInfoResourceCost;
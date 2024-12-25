#pragma once

#include "stdafx.h"
#include "stdio.h"
#include "InGameFunctions.h"
#include "GlobalVariables.h"

bool IsCop(BYTE CarTypeID)
{
	return *(BYTE*)((*(DWORD*)CarTypeInfoArray) + CarTypeID * SingleCarTypeInfoBlockSize + 0x94) == 1;
}

inline bool DoesFileExist(char const* path)
{
	struct stat buffer;
	return (stat(path, &buffer) == 0);
}

void InitSpaceNodesHook()
{
	InitSpaceNodes();
	GRacerInfo_CountRandomNames();
}

// mINI stuff

int mINI_ReadInteger(mINI::INIStructure& ini, std::string Section, std::string Key, int DefaultValue = 0)
{
	int result = DefaultValue;

	if (ini.has(Section) && ini[Section].has(Key))
	{
		try
		{
			if (ini[Section][Key].starts_with("0x") || ini[Section][Key].starts_with("-0x")) result = std::stol(ini[Section][Key], 0, 16);
			else result = std::stol(ini[Section][Key]);
		}
		catch (const std::exception& ex)
		{
			result = DefaultValue;
		}
	}

	return result;
}

float mINI_ReadFloat(mINI::INIStructure& ini, std::string Section, std::string Key, float DefaultValue = 0.0f)
{
	float result = DefaultValue;

	if (ini.has(Section) && ini[Section].has(Key))
	{
		try
		{
			result = std::stof(ini[Section][Key]);
		}
		catch (const std::exception& ex)
		{
			result = DefaultValue;
		}
	}

	return result;
}

char* mINI_ReadString(mINI::INIStructure& ini, std::string Section, std::string Key, const char* DefaultValue = "")
{
	char* result = (char*)DefaultValue;

	if (ini.has(Section) && ini[Section].has(Key))
	{
		try
		{
			result = (char*)ini[Section][Key].c_str();
		}
		catch (const std::exception& ex)
		{
			result = (char*)DefaultValue;
		}
	}

	return result;
}

DWORD mINI_ReadHash(mINI::INIStructure& ini, std::string Section, std::string Key, DWORD DefaultValue = -1)
{
	DWORD result = DefaultValue;

	if (ini.has(Section) && ini[Section].has(Key))
	{
		try
		{
			result = bStringHash((char*)ini[Section][Key].c_str());
		}
		catch (const std::exception& ex)
		{
			result = DefaultValue;
		}
	}

	return result;
}

DWORD mINI_ReadHashS(mINI::INIStructure& ini, std::string Section, std::string Key, const char* DefaultValue = "")
{
	DWORD result = bStringHash((char*)DefaultValue);

	if (ini.has(Section) && ini[Section].has(Key))
	{
		try
		{
			result = bStringHash((char*)ini[Section][Key].c_str());
		}
		catch (const std::exception& ex)
		{
			result = bStringHash((char*)DefaultValue);
		}
	}

	return result;
}

DWORD mINI_ReadVLTHash(mINI::INIStructure& ini, std::string Section, std::string Key, DWORD DefaultValue = 0x82FC1624)
{
	DWORD result = DefaultValue;

	if (ini.has(Section) && ini[Section].has(Key))
	{
		try
		{
			result = Attrib_StringToLowerCaseKey(ini[Section][Key].c_str());
		}
		catch (const std::exception& ex)
		{
			result = DefaultValue;
		}
	}

	return result;
}

DWORD mINI_ReadVLTHashS(mINI::INIStructure& ini, std::string Section, std::string Key, const char* DefaultValue = "")
{
	DWORD result = Attrib_StringToLowerCaseKey(DefaultValue);

	if (ini.has(Section) && ini[Section].has(Key))
	{
		try
		{
			result = Attrib_StringToLowerCaseKey(ini[Section][Key].c_str());
		}
		catch (const std::exception& ex)
		{
			result = Attrib_StringToLowerCaseKey(DefaultValue);
		}
	}

	return result;
}

char* GetDefaultCopDestroyedStringPVehicle(int ID)
{
	if (ID > DefaultCopDestroyedStringCount) return (char*)"";
	else return DefaultCopDestroyedStringPVehicles[ID];
}

char* GetDefaultCopDestroyedString(int ID)
{
	if (ID > DefaultCopDestroyedStringCount) return (char*)"";
	else return DefaultCopDestroyedStrings[ID];
}
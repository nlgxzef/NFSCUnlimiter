#pragma once

#include "stdafx.h"
#include "stdio.h"
#include "InGameFunctions.h"
#include "GlobalVariables.h"
#include "Helpers.h"
#include "includes\ini.h"

//#include "FEPlayerCarDB.h"
//#include "QuickRaceUnlocker.h"
//#include "UnlockSystem.h"
//#include "UIQRCarSelect.h"

void LoadFNGFixes()
{
	// Done in FEPackage.h instead
}

void LoadCopDestroyedStrings()
{
	CopDestroyedString ACopDestroyedString;
	std::vector<CopDestroyedString> CopDestroyedStrings_temp;

	auto CopDestroyedStringsINIPath = CurrentWorkingDirectory / "UnlimiterData" / "_CopDestroyedStrings.ini";
	mINI::INIFile CopDestroyedStringsINIFile(CopDestroyedStringsINIPath.string());
	mINI::INIStructure CopDestroyedStringsINI;
	CopDestroyedStringsINIFile.read(CopDestroyedStringsINI);

	char StringID[15];

	int NumCopDestroyedStrings = mINI_ReadInteger(CopDestroyedStringsINI, "CopDestroyedStrings", "NumberOfCopDestroyedStrings", DefaultCopDestroyedStringCount);

	for (int i = 0; i <= NumCopDestroyedStrings; i++)
	{
		sprintf(StringID, "String%d", i);

		ACopDestroyedString.PVehicle = mINI_ReadVLTHashS(CopDestroyedStringsINI, StringID, "PVehicle", GetDefaultCopDestroyedStringPVehicle(i));
		ACopDestroyedString.StringHash = mINI_ReadHashS(CopDestroyedStringsINI, StringID, "String", GetDefaultCopDestroyedString(i));

		CopDestroyedStrings_temp.push_back(ACopDestroyedString); // Add to temp list
	}

	CopDestroyedStrings = std::move(CopDestroyedStrings_temp); // Replace global list with temp
}
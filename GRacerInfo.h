#include "stdio.h"
#include "InGameFunctions.h"

void GRacerInfo_CountRandomNames()
{
	_asm pushad;
	int i;
	char OppNameBuffer[15];

	for (i = 0; i <= 999; i++)
	{
		sprintf(OppNameBuffer, "RACERNAME_%03d", i);
		if (!DoesStringExist(bStringHash(OppNameBuffer))) break;
	}

	if (i > 0)
	{
		injector::WriteMemory<int>(0x613111, i, true); // GRacerInfo::ChooseRandomName
		injector::WriteMemory<int>(0x6BDB23, i, true); // DriftScoring::Reset
	}
	_asm popad;
}
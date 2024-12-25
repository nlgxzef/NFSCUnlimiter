#pragma once
#include "Defines.h"

struct DBCarPart
{
	Hash GetPartNameHash()
	{
		FUNC(0x007CD930, Hash, __thiscall, _GetPartNameHash, DBCarPart*);
		return _GetPartNameHash(this);
	}
};
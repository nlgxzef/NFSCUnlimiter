#pragma once

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
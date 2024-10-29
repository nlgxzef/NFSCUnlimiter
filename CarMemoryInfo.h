#pragma once

#pragma pack(push, 1)

typedef struct
{
	/* 0x0000 */ char* CarMemType;
	/* 0x0004 */ int Sizes[7];
} CarMemoryInfo; /* size: 0x0004 */

#pragma pack(pop)

void CarInfo_InitResourceCost()
{
	CarInfoResourceCost = (int*)j_malloc(sizeof(int) * CarCount);

	for (int i = 0; i < CarCount; i++)
	{
		CarInfoResourceCost[i] = bFileSize((char*)((*(DWORD*)CarTypeInfoArray) + i * SingleCarTypeInfoBlockSize + 0x20));
	}

	injector::WriteMemory(0x7B12D2, CarInfoResourceCost, true); // CarInfo_GetResourceCost
}
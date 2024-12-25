#pragma once
#include "Defines.h"

struct FEStateManager
{
	int vTable;
	int LastButton;

	void Pop(Hash hash)
	{
		FUNC(0x0059B0D0, void, __thiscall, _Pop, FEStateManager*, Hash);
		_Pop(this, hash);
	}
};

struct FECustomizeStateManager : FEStateManager
{
	int HandleButtonPressed(int a)
	{
		FUNC(0x008463F0, int, __thiscall, _HandleButtonPressed, FECustomizeStateManager*, int);
		return _HandleButtonPressed(this, a);
	}
};

struct FEDialogScreen
{
	static void ShowOk(const char* message)
	{
		FUNC(0x005CF440, void, __cdecl, _ShowOk, const char*);
		_ShowOk(message);
	}
};
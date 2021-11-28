#pragma once
#include "stdio.h"
#include "InGameFunctions.h"

void __fastcall Attrib_Gen_induction_Create(DWORD* AttribGen, void* EDX_Unused, unsigned int CollectionKey, unsigned int msgPort)
{
    DWORD* Collection = Attrib_FindCollection(0xC92A0142, CollectionKey);
    Attrib_Instance_ctInstance(AttribGen, Collection, msgPort);
    if (!AttribGen[1])
        AttribGen[1] = (DWORD)Attrib_DefaultDataArea(92);
}
#include "stdio.h"
#include "InGameFunctions.h"
#include "includes\ini.h"

void __fastcall PursuitInformation_ShowFlashers(DWORD* PursuitInformation, void* EDX_Unused, DWORD* Player, bool ShouldShowBountyMessage)
{
    DWORD* _EFlasherGeneric; // esi MAPDST
    int PlayerIndex; // eax MAPDST
    const char* CostToStateString; // eax
    float FlasherTimer; // eax
    const char* BountyString; // eax
    int CopCarPVehicleHash; // eax MAPDST
    unsigned int HudCopDestroyeedStringHash; // eax
    const char* HudCopDestroyeedString; // eax
    int CopsDestroyedIconHash; // [esp-Ch] [ebp-80h]
    const char* BustedString; // [esp-8h] [ebp-7Ch]
    int BustedStringHash; // [esp+0h] [ebp-74h]
    double Bounty_1; // [esp+0h] [ebp-74h]
    int ComboBounty; // [esp+4h] [ebp-70h]

    int IsPlayerBusted; // [esp+24h] [ebp-50h] BYREF
    char StringID[15];
    char StringBuffer[64]; // [esp+28h] [ebp-4Ch] BYREF

    char const* aS00f = (char const*)0x9D60A8;
    float flt_9C2664 = *(float*)0x9C2664;
    float flt_9CA2C4 = *(float*)0x9CA2C4;
    float WorldTimer = *(float*)_WorldTimer;

    if (CopDestroyedStrings.size() == 0) return PursuitInformation_ShowFlashers_Game(PursuitInformation, Player, ShouldShowBountyMessage);

    if (!PursuitInformation[24] && DALManager_GetInt((DWORD*)_gTheDALManager, 11011, &IsPlayerBusted, -1, -1, -1) && IsPlayerBusted)// GetIsPlayerBusted
    {
        PursuitInformation[24] = IsPlayerBusted;
        _EFlasherGeneric = EventSys_Event_Allocate(36, 0);
        if (_EFlasherGeneric)
        {
            BustedStringHash = bStringHash((char*)"BUSTED");
            BustedString = GetLocalizedString(0x3D6C4706);// HUD_BUSTED
            PlayerIndex = (*(int(__thiscall**)(DWORD*))(*(DWORD*)Player + 28))(Player);
            EFlasherGeneric_ct(_EFlasherGeneric, PlayerIndex, BustedString, 0, BustedStringHash, 1, 1, 3);
        }
        return;
    }
    float CostToState = 0.0;
    float Bounty = 0.0;
    DALManager_GetFloat((DWORD*)_gTheDALManager, 11008, &CostToState, -1, -1, -1);// GetCostToState
    DALManager_GetFloat((DWORD*)_gTheDALManager, 11009, &Bounty, -1, -1, -1);// GetBounty
    if (CostToState > (double)*((float*)PursuitInformation + 29))
    {
        *((float*)PursuitInformation + 29) = CostToState;
        *((float*)PursuitInformation + 28) = WorldTimer;
        CostToStateString = GetLocalizedString(0x9ECCFA3A);// HUD_COST_TO_STATE
        bSNPrintf(StringBuffer, 64, aS00f, CostToStateString, CostToState);
        _EFlasherGeneric = EventSys_Event_Allocate(36, 0);
        if (_EFlasherGeneric)
        {
            PlayerIndex = (*(int(__thiscall**)(DWORD*))(*(DWORD*)Player + 28))(Player);
            EFlasherGeneric_ct(_EFlasherGeneric, PlayerIndex, StringBuffer, 0, 0x2B3213E9, 2, 2, 1);
        }
        goto FlashBounty;
    }
    FlasherTimer = *((float*)PursuitInformation + 28);
    if (FlasherTimer)
    {
        if (FlasherTimer != 0x7FFFFFFF)
        {
            float FlasherTimeRemaining = WorldTimer - FlasherTimer;
            if ((FlasherTimeRemaining * flt_9C2664) >= flt_9CA2C4)
            {
                PursuitInformation[28] = 0;
                _EFlasherGeneric = EventSys_Event_Allocate(20, 0);
                if (_EFlasherGeneric)
                {
                    PlayerIndex = (*(int(__thiscall**)(DWORD*))(*(DWORD*)Player + 28))(Player);
                    EHideLoopingFlasherGeneric_ct(_EFlasherGeneric, PlayerIndex, 2, 1);
                }
            }
        }
    }
FlashBounty:
    if (Bounty > (double)*((float*)PursuitInformation + 30))
    {
        *((float*)PursuitInformation + 30) = Bounty;
        BountyString = GetLocalizedString(0x3D00B540);// HUD_BOUNTY
        bSNPrintf(StringBuffer, 64, aS00f, BountyString, Bounty);
        _EFlasherGeneric = EventSys_Event_Allocate(36, 0);
        if (_EFlasherGeneric)
        {
            PlayerIndex = (*(int(__thiscall**)(DWORD*))(*(DWORD*)Player + 28))(Player);
            EFlasherGeneric_ct(_EFlasherGeneric, PlayerIndex, StringBuffer, 0, 0x8AB83EDB, 1, 2, 2);
        }
    }
    if (ShouldShowBountyMessage)
    {
        int LastCopDestroyedType = 0;
        int LastCopDestroyedMultiplier = 0;
        int LastCopDestroyedBounty = 0;
        DALManager_GetInt((DWORD*)_gTheDALManager, 11016, &LastCopDestroyedType, -1, -1, -1);// pvehicle hash
        DALManager_GetInt((DWORD*)_gTheDALManager, 11017, &LastCopDestroyedMultiplier, -1, -1, -1);
        DALManager_GetInt((DWORD*)_gTheDALManager, 11018, &LastCopDestroyedBounty, -1, -1, -1);

        // Read from ini file
        for (int i = 1; i <= CopDestroyedStrings.size(); i++)
        {
            sprintf(StringID, "String%d", i);
            if (CopDestroyedStrings[i].PVehicle == LastCopDestroyedType)
            {
                HudCopDestroyeedString = GetLocalizedString(CopDestroyedStrings[i].StringHash);
                break;
            }
            if (i == CopDestroyedStrings.size()) HudCopDestroyeedString = 0;
        }

        ComboBounty = LastCopDestroyedMultiplier * LastCopDestroyedBounty;
        //HudCopDestroyeedString = GetLocalizedString(HudCopDestroyeedStringHash);
        bSNPrintf(StringBuffer, 64, HudCopDestroyeedString, ComboBounty);
        _EFlasherGeneric = EventSys_Event_Allocate(36, 0);
        if (_EFlasherGeneric)
        {
            CopsDestroyedIconHash = bStringHash((char*)"COPS_DESTROYED");
            PlayerIndex = (*(int(__thiscall**)(DWORD*))(*(DWORD*)Player + 28))(Player);
            EFlasherGeneric_ct(_EFlasherGeneric, PlayerIndex, StringBuffer, CopsDestroyedIconHash, 0x8AB83EDB, 1, 1, 2);
        }
    }
}
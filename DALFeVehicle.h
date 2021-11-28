#include "stdio.h"
#include "InGameFunctions.h"

#include "Attrib.h"

bool __stdcall DALFeVehicle_GetCarUsesSupercharger(int& result)
{
	DWORD* FECarRecord = *(DWORD**)_gFECarRecord;
	DWORD AttribGenPVehicle[4], AttribGenInduction[4]; // [0] = collection

	Attrib_Gen_pvehicle_Create(AttribGenPVehicle, FECarRecord[2], 0); // [2] = pvehicle hash
	
	if (DWORD* InductionField = Attrib_Instance_GetAttributePointer(AttribGenPVehicle, 0xC92A0142, 0))
	{
		if (InductionField[0]) // [0] = collection
		{
			Attrib_Gen_induction_Create(AttribGenInduction, 0, InductionField[4], 0); // [4] = collection key

			if (AttribGenInduction[0])
			{
				result = Physics_Info_InductionType(AttribGenInduction) == 2; // eInductionType::SuperCharger
				Attrib_Instance_dtInstance(AttribGenPVehicle);
				Attrib_Instance_dtInstance(AttribGenInduction);
				return true;
			}
		}
		
	}

	result = 0;
	Attrib_Instance_dtInstance(AttribGenPVehicle);
	return true;
}
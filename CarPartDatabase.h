#pragma once
#include "DBCarPart.h"

struct CarPartDatabase
{
	static CarPartDatabase* Instance()
	{
		return (CarPartDatabase*)0x00B76690;
	}

	DBCarPart* GetCarPart(Slot slot, CarType carId, DBCarPart* prevPart)
	{
		static auto _GetCarPart = (DBCarPart * (__thiscall*)(CarPartDatabase*, const char*, CarType, Slot, Hash, DBCarPart*, int))0x007CDDF0;
		return _GetCarPart(this, 0, carId, slot, 0, prevPart, -1);
	}

	DBCarPart* GetByPartName(Slot slot, CarType carId, Hash partName)
	{
		DBCarPart* part = 0;
		while (true)
		{
			part = this->GetCarPart(slot, carId, part);
			if (!part)
			{
				break;
			}

			if (part->GetPartNameHash() == partName)
			{
				return part;
			}
		}

		return NULL;
	}
};
#pragma once
typedef unsigned char BYTE;
typedef unsigned int Hash;
typedef int CarType;

#define FUNC(address, return_t, callconv, name, ...) return_t (callconv* name)(__VA_ARGS__) = reinterpret_cast<decltype(name)>(address)

const int ZoneFrontBumper = 0;
const int ZoneRearBumper = 1;
const int ZoneSkirt = 2;
const int ZoneFrontWheel = 3;
const int ZoneHood = 4;
const int ZoneSpoiler = 5;
const int ZoneRoofScoop = 6;
const int ZoneRoof = 7;
const int ZoneExhaust = 8;

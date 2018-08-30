#pragma once
#include <string>
#include <iostream>
#ifdef WIN32
#include <objbase.h>
#else
#include <uuid/uuid.h>
#endif
#include "stringHelper.h"

namespace helper {
static std::string uuid()
{
#define GUID_LEN 64 
	char buffer[GUID_LEN] = { 0 };
	uuid_t guid;

#ifdef WIN32

	if (CoCreateGuid(&guid)) {
		std::cerr << "create guid error\n";
		return buffer;
	}
	_snprintf(buffer, sizeof(buffer),
		"%08X%04X%04x%02X%02X%02X%02X%02X%02X%02X%02X",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1], guid.Data4[2],
		guid.Data4[3], guid.Data4[4], guid.Data4[5],
		guid.Data4[6], guid.Data4[7]);
	return helper::string::toLower(std::string(buffer));
#else
	uuid_generate(guid);
	uuid_unparse(guid, buffer);
	return std::string(buffer);

#endif
}
}

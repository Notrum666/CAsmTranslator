#include "Types.h"

bool equal(void* lhs, void* rhs, Type type)
{
	switch (type)
	{
	case Type::type_int:
		return *((int*)lhs) == *((int*)rhs);
		break;
	//case Type::type_string:
	//	return std::strcmp((char*)lhs, (char*)rhs);
	//	break;
	}
	return false;
}
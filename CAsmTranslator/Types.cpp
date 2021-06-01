#include "Types.h"

bool equal(void* lhs, void* rhs, ValueType type)
{
	switch (type)
	{
	case ValueType::INT32:
		return *((int*)lhs) == *((int*)rhs);
	//case Type::type_string:
	//	return std::strcmp((char*)lhs, (char*)rhs);
	}
	return false;
}
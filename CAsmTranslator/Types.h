#pragma once
#include <cstring>

enum class ValueType { INT32 };

bool equal(void* lhs, void* rhs, ValueType type);

enum class IdentifierType { VARIABLE, FUNCTION };
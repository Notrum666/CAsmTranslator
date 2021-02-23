#pragma once
#include <cstring>

enum class Type { type_int };

bool equal(void* lhs, void* rhs, Type type);
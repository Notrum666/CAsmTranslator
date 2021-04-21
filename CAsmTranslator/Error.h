#pragma once

struct Error
{
public:
	const char* file;
	int row;
	int column;
	const char* message;
	Error(const char* file, int row, int column, const char* message);
};

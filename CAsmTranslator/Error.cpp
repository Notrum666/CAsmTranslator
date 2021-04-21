#include "Error.h"

Error::Error(const char* file, int row, int column, const char* message)
{
	this->file = file;
	this->row = row;
	this->column = column;
	this->message = message;
}
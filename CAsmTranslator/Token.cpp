#include "Token.h"

Token::Token(short table_id, short record_id)
{
	this->table_id = table_id;
	this->record_id = record_id;
}
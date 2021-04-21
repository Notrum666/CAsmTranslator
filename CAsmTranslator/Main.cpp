#include "Translator.h"
#include "Error.h"

int main()
{
	Translator::Init();
	Error* err = Translator::TranslateFile("code.cpp", "code.asm");
	if (err)
		printf_s("%s (%d,%d): message : %s\n", err->file, err->row, err->column, err->message);
	else printf_s("done\n");
	Translator::keywords->print();
	printf_s("\n");
	Translator::delimeters->print();
	printf_s("\n");
	Translator::identifiers->print();	
	printf_s("\n");
	Translator::constants->print();
	scanf_s("%*c");
	return 0;
}
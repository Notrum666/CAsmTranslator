#include "Translator.h"

int main()
{
	Translator::Init();
	bool success = Translator::TranslateFile("code.cpp", "code.asm");
	printf_s("\n%d", success);
	scanf_s("%*c");
	return 0;
}
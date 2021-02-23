#include "Translator.h"

int main()
{
	Translator translator = Translator();
	bool success = translator.translateFile("code.cpp", "code.asm");
	printf_s("\n%d", success);
	scanf_s("%*c");
	return 0;
}
#include <stdio.h>
#include <type_traits>

int main()
{
	if (std::is_same<int, int>::value)
		return 1;
	return 0;
}
#include <Windows.h>
#include <iostream>
#include <thread>

void Foo()
{
	while (1)
	{
		std::cout << "!";
		Sleep(1000);
	}
}

int main()
{
	char test[3][100] = {
		{"##################"},
		{"# Mot hai ba bon #"},
		{"##################"}
	};

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 18; ++j)
		{
			std::cout << test[i][j];
		}
		std::cout << '\n';
	}

	std::cout << sizeof(test[1]);

	return 0;
}

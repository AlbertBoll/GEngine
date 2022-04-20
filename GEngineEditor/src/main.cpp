#include "GEngine/GEngine.h"
#include <iostream>

int main()
{
	std::cout << "3 + " << "4 = " << GEngine::Add(3, 4) << std::endl;

	GEngine::GetInfo();
}
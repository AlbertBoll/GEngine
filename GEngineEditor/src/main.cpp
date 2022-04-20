#include "GEngine/GEngine.h"
#include <iostream>

int main()
{
	GEngine::GetInfo();
	if (GEngine::Initialize())
		GEngine::Shutdown();

}
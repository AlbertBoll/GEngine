#pragma once
#pragma warning (disable : 4005)

#ifdef GENGINE_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		#define NOMINMAX

	#endif 
#endif 

#include <string>
#include <map>
#include <unordered_map>
#include <unordered_set>

#include <memory>
#include <vector>
#include <glad/glad.h> 
#include <filesystem>
#include <cstdint>
#include <chrono>
#include <iostream>
#include <functional>
#include "sdl2/SDL.h"
//#include "Core/Utility.h"
#include "Core/Log.h"
#include "Core/Base.h"

#ifdef GENGINE_PLATFORM_WINDOWS
	#include<Windows.h>
#endif 



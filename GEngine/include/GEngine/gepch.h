#pragma once

//suppress the warning of macro redefinition
#pragma warning (disable : 4005)

//Since the NOMINMAX conflicts the standard library(std::min and std::max) using the following the
#ifdef GENGINE_PLATFORM_WINDOWS
	#ifndef NOMINMAX   
		#define NOMINMAX

	#endif 
#endif 

#include <string>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <limits>
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
#include "Math/Math.h"

#ifdef GENGINE_PLATFORM_WINDOWS
	#include<Windows.h>
#endif 



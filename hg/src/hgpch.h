#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <sstream>
#include <cstdint>

#include <array>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "hg/Core/Log.h"
#include "hg/Debug/instrumentor.h"

#ifdef HG_PLATFORM_WINDOWS
	#include <Windows.h>
#endif // !HG_PLATFORM_WINDOWS

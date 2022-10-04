#pragma once

#include "resource.h"
#include <tchar.h>
#include <Window.h>

#define SCREEN_HEIGHT (720)
#define SCREEN_WIDTH  (1280)

#define SAFE_RELEASE(x){\
if(x)\
 {\
 (x)->Release();x=nullptr;\
 }\
}

#pragma once
#pragma warning( disable: 4152 )
#pragma warning( disable: 4201 )

#define RGBQUAD _RGBQUAD
#pragma warning( push, 0 )
#include <windows.h>
#pragma warning( pop )
#undef RGBQUAD

#pragma comment(lib, "winmm.lib")

#ifndef __cplusplus // Avoid conflicts if compiling as C++
typedef unsigned char bool;
#define true 1
#define false 0
#endif

#include <accctrl.h>
#include <aclapi.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdint.h>
#include "def.h"
#include "math.h"
#include "color.h"
#include "callbacks.h"
#include "threads.h"
#include "payloads.h"
#include "extra_payloads.h"

#pragma region Public Variables
extern HWND hwndDesktop;
extern HDC hdcDesktop;
extern RECT rcScrBounds;
extern HHOOK hMsgHook;
extern INT nCounter; 
extern bool hasPayloadsFinished;
#pragma endregion Public Variables
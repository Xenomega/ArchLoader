// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include <xtl.h>
#include <xboxmath.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <XInput2.h>

using namespace std;

#if FDEBUG
#include <xbdm.h>
#pragma comment(lib, "xbdm.lib")
#endif

// standard..
#include "ArchConfig_std.h"
#include "ArchConfig_Controller.h"
#include "Generic.h"
#include "KernelExports.h"
#include "XamExports.h"


#include "stdafx.h"
#include "assembly.h"
#include "Patches.h"

#pragma once
class ArchMenu
{
private:
	static D3DDevice* g_pd3dDevice;
public:
	static VOID Init();
	static VOID Update();

};


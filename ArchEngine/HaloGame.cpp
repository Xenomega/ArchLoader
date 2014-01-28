#include "HaloGame.h"
#include "Patches.h"
#include "assembly.h"

// d3d
D3DDevice* HaloGame::GetD3DDevice()
{
	D3DDevice* g_pd3dDevice = NULL;

	// Obtain our d3d device.
	while(g_pd3dDevice == NULL)
		g_pd3dDevice = (D3DDevice*)*((DWORD*)ARCH_ADDR_D3DDEVICE);

	return g_pd3dDevice;
}

// Game speed
FLOAT HaloGame::_backupGameSpeed = 1;
FLOAT* HaloGame::_GetGametimeSpeed()
{
	// Get our addresses
	FLOAT* gameTimeGlobalsAddr = (FLOAT*)*((DWORD*)ARCH_ADDR_GAMETIMEGLOBALS);
	FLOAT* gameSpeedAddr = gameTimeGlobalsAddr + 0x04; // four floats in
	return gameSpeedAddr;
}
FLOAT HaloGame::GetGameSpeed()
{
	FLOAT* speedAddr =  _GetGametimeSpeed();
	return *speedAddr;
}
VOID HaloGame::SetGameSpeed(FLOAT speedMul)
{
	if(speedMul < 0)
		speedMul = 0;
	FLOAT* speedAddr =  _GetGametimeSpeed();
	SetMemory(speedAddr, &speedMul, sizeof(speedMul));

	// Print our message
	PrintLine("Gamespeed set at %.2f..", speedMul);
}
VOID HaloGame::ToggleGameSpeed()
{
	FLOAT speedMul = GetGameSpeed();
	if(speedMul == 0)
	{
		if(_backupGameSpeed == 0)
			_backupGameSpeed = 1;
		SetGameSpeed(_backupGameSpeed);
	}
	else
	{
		_backupGameSpeed = speedMul;
		SetGameSpeed(0);
	}
}
VOID HaloGame::IncrementGameSpeed(BOOL positive)
{
	FLOAT speed = GetGameSpeed();
	FLOAT modifier = ARCH_VALUE_GAMESPEEDMODIFIER;
	if(!positive)
		modifier *= -1;
	speed += modifier;
	SetGameSpeed(speed);
}

// Game information
CHAR* HaloGame::GetCurrentMapName()
{
	CHAR* mapName = (CHAR*)ARCH_ADDR_MAPPATH;
	return mapName;
}
BOOL HaloGame::IsInMainmenu()
{
	CHAR* mapName = GetCurrentMapName();
	return (strcmp(mapName, ARCH_MAP_MAINMENU) == 0);
}
BOOL HaloGame::IsIngame()
{
	CHAR* mapName = GetCurrentMapName();
	return !(IsInMainmenu() | (strcmp(mapName, "") == 0));
}
BOOL HaloGame::IsInHalo()
{
	return (XamGetCurrentTitleId() == ARCH_TITLEID ||
		XamGetCurrentTitleId() == ARCH_TITLEID2);
}

// Map function
VOID HaloGame::ReloadMap()
{
	// Reload our map.
	BYTE* ptrReload = (BYTE*)ARCH_ADDR_MAPRELOAD;
	BYTE reloadData = 1;
	SetMemory(ptrReload, &reloadData, 1);
}
VOID HaloGame::LoadMap(const CHAR* const path, DWORD type)
{
	// Copy the path
	CHAR* ptrMapPath = (CHAR*)ARCH_ADDR_MAPPATH;
	if(strlen(ptrMapPath) > 0)
	{
		memset(ptrMapPath, 0, 255);
		memcpy(ptrMapPath, path, strlen(path));

		DWORD* ptrMapType = (DWORD*)ARCH_ADDR_MAPTYPE;
		SetMemory(ptrMapType, &type, 4);

		ReloadMap();

		PrintLine("Loaded map %s as type %i.", path, type);
	}
}
NETWORKMODE HaloGame::GetNetworkMode()
{
		return NETWORKMODE((*(DWORD*)ARCH_ADDR_DEFAULTNETWORKMODE) & 0xFF);
}
VOID HaloGame::SetNetworkMode(NETWORKMODE mode)
{
	if(mode == GetNetworkMode())
		return;

	DWORD* addr = (DWORD*)ARCH_ADDR_DEFAULTNETWORKMODE;
	DWORD patchData = assembly::li(3, mode);
	SetMemory(addr, &patchData, 4);

	if(mode == NETWORKMODE_LOCAL)
		PrintLine("Set network mode to local..");
	else if (mode == NETWORKMODE_SYSTEMLINK)
		PrintLine("Set network mode to system link..");
	else if (mode == NETWORKMODE_XBOXLIVE)
		PrintLine("Set network mode to xbox live..");
	else
		PrintLine("Unknown network mode set.");
}
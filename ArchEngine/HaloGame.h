
#include "stdafx.h"
#pragma once

class HaloGame
{
private:
	static FLOAT _backupGameSpeed;
	static FLOAT* _GetGametimeSpeed();
public:
	static D3DDevice* GetD3DDevice();

	static FLOAT GetGameSpeed();
	static VOID SetGameSpeed(FLOAT speedMul);
	static VOID ToggleGameSpeed();
	static VOID IncrementGameSpeed(BOOL positive);

	static CHAR* GetCurrentMapName();
	static BOOL IsInMainmenu();
	static BOOL IsIngame();
	static BOOL IsInHalo();

	static VOID ReloadMap();
	static VOID LoadMap(const CHAR* const path, DWORD type);

	static NETWORKMODE GetNetworkMode();
	static VOID SetNetworkMode(NETWORKMODE mode);
};

#include "stdafx.h"
#include "assembly.h"
#include "Patches.h"
#pragma once
class Camera
{
private:
	static D3DDevice* g_pd3dDevice;
	static DWORD CURRENT_VIEW;
public:

	static VOID CameraViewTypeHook();
	static VOID Init();

	static VOID SetCameraViewType(CAMERATYPE view);


	static D3DFILLMODE GetD3DFillMode();
	static VOID SetD3DFillMode(D3DFILLMODE fillMode);
	static VOID ToggleD3DFillMode();

	static BOOL GetPrintCamCoordsEnabled();
	static VOID SetPrintCamCoordsEnabled(BOOL enabled);

	static FLOAT GetFieldOfView();
	static VOID SetFieldOfView(FLOAT fov);
};


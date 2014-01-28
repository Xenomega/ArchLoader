#include "Camera.h"
#include "HaloGame.h"

D3DDevice* Camera::g_pd3dDevice = NULL;

void _declspec(naked) Camera::CameraViewTypeHook()
{
	__asm
	{
			//mr		r26, r12 // back up return address, compiler optimization for the move register crap can kill this.
			li		r28, 3 // CAMERATYPE_FIRST_PERSION - replace this
			cmpw	cr6, r4, r28
			bne		cr6, dont_replace 

			//li		r28, 0 // CAMERATYPE_FOLLOWING - replace this
			//cmpw	cr6, r4, r28
			//bne		cr6, dont_replace 

replace:
			mr	r4,  r26 // preprocessor definition of LTCG doesn't allow this =(

dont_replace:
			lwz		r11, 4(r3) // r11 is destroyed to get here, restore it.

			//mr		r12, r26 // restore return address

			mr        r29, r3 // original code we replaced
			fmr		fp31, fp1 // original code we replaced
			mr		r3, r31 // original code we replaced
			mr		r28, r4 // original code we replaced
			mr		r26, r6 // original code we replaced

			blr
	}
}

VOID Camera::Init() 
{
	// Obtain our device
	g_pd3dDevice = HaloGame::GetD3DDevice();

	// Hook our director_choose_game_perspective
	SetCameraViewType(CAMERATYPE_FIRST_PERSON);
	PatchInJump((DWORD*)ARCH_ADDR_CAMERAVIEWTYPE, (DWORD)CameraViewTypeHook, TRUE);
	PrintLine("Hooked director_choose_game_perspective..");
}

VOID Camera::SetCameraViewType(CAMERATYPE view) 
{ 
	DWORD patchData = assembly::li(26, (WORD)view);
	SetMemory((((DWORD*)ARCH_ADDR_CAMERAVIEWTYPE) - 1), &patchData, sizeof(patchData));
}


D3DFILLMODE Camera::GetD3DFillMode()
{
	// Get our fill mode.
	DWORD fillMode;
	g_pd3dDevice->GetRenderState(D3DRS_FILLMODE, &fillMode);
	return (D3DFILLMODE)fillMode;
}
VOID Camera::SetD3DFillMode(D3DFILLMODE fillMode)
{
	// Set our fill mode.
	g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, fillMode);

	switch(fillMode)
	{
	case D3DFILL_SOLID:
		PrintLine("Changed fill mode to solid..");
		break;
	case D3DFILL_POINT:
		PrintLine("Changed fill mode to point..");
		break;
	case D3DFILL_WIREFRAME:
		PrintLine("Changed fill mode to wireframe..");
		break;
	}
}
VOID Camera::ToggleD3DFillMode()
{
	// Get our fill mode.
	D3DFILLMODE fillMode = GetD3DFillMode();

	// Rotate our fill modes.
	switch(fillMode)
	{
	case D3DFILL_SOLID:
		fillMode = D3DFILL_POINT;
		break;
	case D3DFILL_POINT:
		fillMode = D3DFILL_WIREFRAME;
		break;
	case D3DFILL_WIREFRAME:
		fillMode = D3DFILL_SOLID;
		break;
	}

	SetD3DFillMode(fillMode);
}

BOOL Camera::GetPrintCamCoordsEnabled()
{
	DWORD* ptrAddr1 = (DWORD*)ARCH_ADDR_PRINTCAMCOORDS1;
	return *ptrAddr1 == assembly::nop();
}
VOID Camera::SetPrintCamCoordsEnabled(BOOL enabled)
{
	DWORD* ptrAddr1 = (DWORD*)ARCH_ADDR_PRINTCAMCOORDS1;
	DWORD* ptrAddr2 = (DWORD*)ARCH_ADDR_PRINTCAMCOORDS2;
	DWORD asm_orig[2];
	asm_orig[0] = 0x419A0200;
	asm_orig[1] = 0x419A01E8;
	DWORD asm_new = 0x60000000;

	// We'll be wanting our toggle to act as [normal]->[pancam]->[off]=>(repeat)
	if(!enabled)
	{
		if(*ptrAddr1 != asm_orig[0])
		{
			// Turn it back off.
			SetMemory(ptrAddr2, &asm_orig[1], 4);
			SetMemory(ptrAddr1, &asm_orig[0], 4);
			PrintLine("Print camera coordinates disabled..");
		}
	}
	else
	{
		if(*ptrAddr1 != asm_new)
		{
			// Set normal print cam on.
			SetMemory(ptrAddr2, &asm_new, 4);
			SetMemory(ptrAddr1, &asm_new, 4);
			PrintLine("Print camera coordinates enabled..");
		}
	}
}

FLOAT Camera::GetFieldOfView()
{
	FLOAT* addr = (FLOAT*)ARCH_ADDR_CAMERAFOV;
	return *addr;
}
VOID Camera::SetFieldOfView(FLOAT fov)
{
	FLOAT* addr = (FLOAT*)ARCH_ADDR_CAMERAFOV;
	if(fov <= 0.1f)
		fov = 0.1f;
	else if(fov >= 2.75f)
		fov = 2.75f;
	if(*addr != fov)
	{
		SetMemory(addr, &fov, sizeof(fov));
		PrintLine("Set field of view at %.3f..", fov);
	}
}
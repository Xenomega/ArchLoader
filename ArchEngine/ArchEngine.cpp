#include "stdafx.h"
#include "Camera.h"
#include "HaloGame.h"
#include "Patches.h"
#include "ArchMenu.h"

HANDLE moduleHandle;

BOOL ValidateButtonSequence(XINPUTID* inputSequence, DWORD count)
{
	//Our context for our input.
	XINPUT2CONTEXT context;
	BOOL changed;

	//Clear our context.
	memset( &context, 0, sizeof(context) );

	// Enumerate gamepads for all users
	if( XInput2Sample( XInput2InputDevice(0), &context, &changed ) )
	{
		// If a controller is plugged in..
		if( XInput2HasProperty( context, XINPUTID_GAMEPAD))
		{
			// Gamepad detected a state change, update cached info accordingly.
			BOOL clicked = TRUE;
			while(count > 0 && clicked)
			{
				if(*inputSequence == XINPUTID_BUTTONS)
				{
					DWORD bC = 0;
					XInput2GetDWord(context, *inputSequence, &bC);
					clicked &= bC > 0;
				}
				else if(*inputSequence == XINPUTID_LEFT_TRIGGER | *inputSequence == XINPUTID_RIGHT_TRIGGER)
				{
					FLOAT fL = 0;
					XInput2GetFloat(context, *inputSequence, &fL);
					clicked &= fL > 0.5f;
				}
				else
				{
					BOOL bL = FALSE;
					XInput2GetBool(context, *inputSequence, &bL);
					clicked &= bL;
				}
				inputSequence += 1;
				count--;
			}
			if(clicked)
				return TRUE;
		}
	}
	return FALSE;
}
VOID CheckButtonCombinations()
{
	//---------------------------------------------
	// FORCE-LOAD MAP
	//---------------------------------------------
	if(ValidateButtonSequence((XINPUTID*)ARCH_CONTROLS_FORCELOAD_MAINMENU, ARRAYSIZE(ARCH_CONTROLS_FORCELOAD_MAINMENU)))
		HaloGame::LoadMap(ARCH_MAP_MAINMENU, ARCH_MAPTYPE_MAINMENU);
	else if(ValidateButtonSequence((XINPUTID*)ARCH_CONTROLS_FORCELOAD_LONGBOW, ARRAYSIZE(ARCH_CONTROLS_FORCELOAD_LONGBOW)))
		HaloGame::LoadMap(ARCH_MAP_LONGBOW, ARCH_MAPTYPE_MULTIPLAYER);
	else if(ValidateButtonSequence((XINPUTID*)ARCH_CONTROLS_FORCELOAD_ADRIFT, ARRAYSIZE(ARCH_CONTROLS_FORCELOAD_ADRIFT)))
		HaloGame::LoadMap(ARCH_MAP_ADRIFT, ARCH_MAPTYPE_MULTIPLAYER);
	else if(ValidateButtonSequence((XINPUTID*)ARCH_CONTROLS_FORCELOAD_HAVEN, ARRAYSIZE(ARCH_CONTROLS_FORCELOAD_HAVEN)))
		HaloGame::LoadMap(ARCH_MAP_HAVEN, ARCH_MAPTYPE_MULTIPLAYER);

	//---------------------------------------------
	// PRINT CAM DEBUG INFO
	//---------------------------------------------
	else if(ValidateButtonSequence((XINPUTID*)ARCH_CONTROLS_TOGGLEPRINTCAM, ARRAYSIZE(ARCH_CONTROLS_TOGGLEPRINTCAM)))
	{
		if(HaloGame::IsIngame())
			Camera::SetPrintCamCoordsEnabled(!Camera::GetPrintCamCoordsEnabled());
	}
	//---------------------------------------------
	// D3D FILL-MODE
	//---------------------------------------------
	else if(ValidateButtonSequence((XINPUTID*)ARCH_CONTROLS_TOGGLEFILLMODE, ARRAYSIZE(ARCH_CONTROLS_TOGGLEFILLMODE)))
		Camera::ToggleD3DFillMode();

	//---------------------------------------------
	// CAMERA TYPES
	//---------------------------------------------
	else if(ValidateButtonSequence((XINPUTID*)ARCH_CONTROLS_CAMERAVIEW_FIRSTPERSON, ARRAYSIZE(ARCH_CONTROLS_CAMERAVIEW_FIRSTPERSON)))
		Camera::SetCameraViewType(CAMERATYPE_FIRST_PERSON);
	else if(ValidateButtonSequence((XINPUTID*)ARCH_CONTROLS_CAMERAVIEW_THIRDPERSON, ARRAYSIZE(ARCH_CONTROLS_CAMERAVIEW_THIRDPERSON)))
		Camera::SetCameraViewType(CAMERATYPE_FOLLOWING);
	else if(ValidateButtonSequence((XINPUTID*)ARCH_CONTROLS_CAMERAVIEW_FLYCAM, ARRAYSIZE(ARCH_CONTROLS_CAMERAVIEW_FLYCAM)))
		Camera::SetCameraViewType(CAMERATYPE_FLYING);
	else if(ValidateButtonSequence((XINPUTID*)ARCH_CONTROLS_CAMERAVIEW_STATIC, ARRAYSIZE(ARCH_CONTROLS_CAMERAVIEW_STATIC)))
		Camera::SetCameraViewType(CAMERATYPE_STATIC);

	else if(ValidateButtonSequence((XINPUTID*)ARCH_CONTROLS_CAMERA_FOV_INCREASE, ARRAYSIZE(ARCH_CONTROLS_CAMERA_FOV_INCREASE)))
		Camera::SetFieldOfView(Camera::GetFieldOfView() + ARCH_VALUE_CAMERAFOVMODIFIER);
	else if(ValidateButtonSequence((XINPUTID*)ARCH_CONTROLS_CAMERA_FOV_DECREASE, ARRAYSIZE(ARCH_CONTROLS_CAMERA_FOV_DECREASE)))
		Camera::SetFieldOfView(Camera::GetFieldOfView() - ARCH_VALUE_CAMERAFOVMODIFIER);
	else
	{ 
		// Ingame values below..
		if(HaloGame::IsIngame())
		{
			//---------------------------------------------
			// GAME SPEED
			//---------------------------------------------
			if(ValidateButtonSequence((XINPUTID*)ARCH_CONTROLS_TIME_TOGGLE, ARRAYSIZE(ARCH_CONTROLS_TIME_TOGGLE)))
				HaloGame::ToggleGameSpeed();
			else if(ValidateButtonSequence((XINPUTID*)ARCH_CONTROLS_TIME_ACCELERATE, ARRAYSIZE(ARCH_CONTROLS_TIME_ACCELERATE)))
				HaloGame::IncrementGameSpeed(TRUE);
			else if(ValidateButtonSequence((XINPUTID*)ARCH_CONTROLS_TIME_DECELERATE, ARRAYSIZE(ARCH_CONTROLS_TIME_DECELERATE)))
				HaloGame::IncrementGameSpeed(FALSE);
			else
				return;
		}
		else
			return;
	}
	
	// Buttons were pressed, slow down to avoid crazy timing repeats.
	Sleep(200);
}
XOVERLAPPED m_Overlapped = {0};
BOOL m_bDeviceUIActive = FALSE;
VOID Update()
{
	// Set our print cam off, it will error
	if(HaloGame::IsInMainmenu())
		Camera::SetPrintCamCoordsEnabled(FALSE);

	//PatchUserInformation();
	PatchUserRewards();

	// Update our menu possibly
	ArchMenu::Update();

	// Update and check our button presses
	CheckButtonCombinations();
}
VOID WaitForHalo()
{	

	// Create a symbolic link so we can read data
	CreateSymbolicLink("HDD:", "\\Device\\Harddisk0\\Partition1", TRUE);
	
	// Display we loaded our module
	PrintLine("Module initialized..");
	PrintLine("Created by Xenomega9..");
	PrintLine("Special thanks to CLK, kornman00 for their contributions..");

	Beginning:

	// Wait until our title id is ingame.
	PrintLine("Waiting for appropriate title to launch..");
	while(!HaloGame::IsInHalo()) { }
	PrintLine("Title has been loaded..");

	// Sleep for our init delay
	Sleep(ARCH_INIT_DELAY);

	// Apply startup patches.
	PrintLine("Applying startup patches..");
	ApplyStartupPatches();
	PrintLine("Startup patches applied.");

	// Initialize our camera class
	Camera::Init();
	ArchMenu::Init();

	// While our user is in game.
	while(HaloGame::IsInHalo())
		Update();

	// Title unloaded.
	PrintLine("Title has been unloaded..");

	// Go back to beginning
	goto Beginning;
}

HRESULT Initialize() {

	// Create a symbolic link so we can read data
	if(CreateSymbolicLink("Hdd1:", "\\Device\\Harddisk0\\Partition1", TRUE) != S_OK)
		return S_FALSE;

	//Create our new thread to wait on halo for. 
	DWORD threadId;
	ExCreateThread(&moduleHandle, 0, &threadId, (VOID*)WaitForHalo , (LPTHREAD_START_ROUTINE)WaitForHalo, NULL, 0x02);

	// All finished
	return S_OK;
}

BOOL APIENTRY DllMain(HANDLE hInstDLL, DWORD reason, LPVOID lpReserved) {
	moduleHandle = hInstDLL;
	switch(reason)
	{
		case DLL_PROCESS_ATTACH:
			if(Initialize() != S_OK)
				return FALSE;
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}
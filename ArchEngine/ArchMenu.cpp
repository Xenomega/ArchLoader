#include "ArchMenu.h"
#include "HaloGame.h"

D3DDevice* ArchMenu::g_pd3dDevice = NULL;

VOID ArchMenu::Init()
{
	// Obtain our device
	g_pd3dDevice = HaloGame::GetD3DDevice();
}
VOID ArchMenu::Update()
{
	// Draw shit
	if(HaloGame::IsIngame() && HaloGame::IsInHalo())
	{
		// Structure to hold vertex data.
		struct COLORVERTEX
		{
			FLOAT Position[3];
			DWORD Color;
		};

		COLORVERTEX Vertices[3] =
		{
			{ -1.0f, -1.0f, 0.0f, 0x00FF0000 },
			{  0.0f,  1.0f, 0.0f, 0x0000FF00 },
			{  1.0f, -1.0f, 0.0f, 0x000000FF }
		};

			// Draw the vertices.  Note that it is more efficient to draw large amounts
			// of vertices using vertex and index buffers.
		//D3DDevice_Clear(g_pd3dDevice, 0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		//						 0xff000000, 1.0f, 0L, FALSE);
		//D3DDevice_DrawPrimitiveUP(g_pd3dDevice, D3DPT_TRIANGLELIST, 1, Vertices, sizeof( COLORVERTEX ) );
		//D3DDevice_Present(g_pd3dDevice);
	}
}
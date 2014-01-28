#pragma once

VOID StampWatermark();
VOID ApplyStartupPatches();

DWORD* GetCameraViewTypePtr();
VOID PatchAuthStatus(DWORD dwUserIndex);
VOID PatchUserRewards();
VOID PatchUserInformation();
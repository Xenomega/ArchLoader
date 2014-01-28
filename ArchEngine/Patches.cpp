#include "stdafx.h"
#include "HaloGame.h"
#include "Patches.h"
#include "assembly.h"


// backing out of customs brings you to matchmaking
// backing out of other lobbies typically gives you infinity_menu
// because of this, matchmaking should always be after customs in the list (since exitting it will bring you to the correct lobby).
DWORD _switchLobbyCurrentLobby = 0;
DWORD _switchLobbyLobbyList[] = {
	0x400BA, // campaign menu
	0x400BE, // campaign custom game
	//0x400BD, // spartan ops
	//0x400C3, // development only custom (doesn't exit to correct menu so can't be used in hook)
	//0x400BF, // campaign matchmaking
	0x400C0, // custom games
	0x400C1, // matchmaking
	0x400C5, // forge
	0x400C6, // theater
	0x400BA // (the last entry is put here to loop)
};
void _declspec(naked) SwitchLobbyHook()
{
	__asm
	{

		    // normal code we replaced (loads the stringID)
			lis		r11, 4
			lwz		r9, 0x54(r3) 

			// if it's 0x301 (title), jump to our replacement area.
			li		r10, 0x301
			cmpw	cr6, r10, r9
			beq		cr6, replace_start 

			// if it's not 0x000400BB (infinity_menu), jump to the end
			lis		r10, 0x4
			ori		r10, r10, 0xBB
			cmpw	cr6, r10, r9
			bne		cr6, replace_ending

replace_start:
			// if the current lobby is equal to matchmaking (0x000400C1), we jump to theater
			lau     r10, _switchLobbyCurrentLobby
			lal		r10, r10, _switchLobbyCurrentLobby
			lwz		r9, 0(r10)

			li		r11, 0
compare_next:
			// load our entry
			lau		r10, _switchLobbyLobbyList
			lal		r10, r10, _switchLobbyLobbyList
			add		r10, r10, r11
			lwz		r10, 0(r10)

			cmpwi	r9, 0
			beq		set_lobby
			addi	r11, r11, 4 // increment to the next integer
			cmpw	cr6, r9, r10 // compare until theyre equal
			bne		cr6, compare_next

set_lobby:
			// load our entry (again)
			lau		r10, _switchLobbyLobbyList
			lal		r10, r10, _switchLobbyLobbyList
			add		r10, r10, r11
			lwz		r9, 0(r10)
			stw		r9, 0x54(r3)
			b		replace_ending

			// ENDING
			// ---------------------------------------------
replace_ending:
			// Save the current lobby
			lau     r10, _switchLobbyCurrentLobby
			lal		r10, r10, _switchLobbyCurrentLobby
			stw		r9, 0(r10)

			// restore some variables
			lis		r10, 4
			lis		r11, 4
			ori		r11, r11, 0xBC

			blr
	}
}

BOOL FilmCanRecordHelper()
{
	// We want to make sure that we are not on the main menu, and are not attempting to play a film (status = 0 when playing a film)
	// if both of these criteria are met, we flag recording as enabled
	if(HaloGame::IsInMainmenu() || (*(DWORD*)ARCH_ADDR_GAMESTATUS != -1))
		return FALSE;
	return TRUE;
}
void _declspec(naked) FilmCanRecordHook()
{
	__asm
	{
		// Setup the stack and save the link register
		mflr	r12
		stw		r12, -8(r1)
		stwu	r1, -0x20(r1) // 32 bytes of stack

		// Call the helper function
		bl FilmCanRecordHelper();

		// Compare the result into cr6
		cmplwi	cr6, r3, 0

		// Restore the stack and return
		addi	r1, r1, 0x20
		lwz		r12, -8(r1)
		mtlr	r12
		blr
	}
}


VOID ConsolePrintHelper(CHAR* lineStr)
{
	std::string str;
	str = lineStr;
	// Blacklist these strings, allow all others. (These can flood your console).
	if (
		str.find("resolved public ip address") == string::npos && // don't want your external ip in logs incase.
		str.find("http_request_queue: request url '") == string::npos &&
		str.find("http_request_queue: url '") == string::npos &&
		str.find("choosing best one.") == string::npos &&
		str.find("downloader: Download failed for ") == string::npos &&
		str.find("downloader: Download started for ") == string::npos &&
		str.find("downloader: Cache expired for ") == string::npos &&
		str.find("starting transfer with url ") == string::npos &&
		str.find("transfer failed [3]") == string::npos &&
		str.find("choosing best one.") == string::npos &&
		str.find("register_best_server() failed in get_best_server_index()") == string::npos &&
		str.find("failed to register a server for service type ") == string::npos &&
		str.find("which doesn't exist in player. Will be invisible!") == string::npos &&
		str.find("customization: spartan armor effect choice ") == string::npos &&
		str.find("customization: player model customization choice ") == string::npos &&
		str.find("observer:status: est") == string::npos &&
		str.find("observer:status:voice: ") == string::npos &&
		str.find("task 'stats-query' failed.") == string::npos &&
		str.find("item_absolute_index is NONE in get_purchase_property_flags_for_controller_const.") == string::npos &&
		str.find("cookie_purchase: Out of range category provided.") == string::npos &&
		str.find("cookie_purchase_item_set_player_appearance: Invalid item.") == string::npos &&
		str.find("failed. calling result=") == string::npos &&
		str.find("friends: friends enumeration failed") == string::npos &&
		str.find("party: failed to call XPartyGetUserList") == string::npos &&
		str.find("thread mainmenu attempted to access unplaced object") == string::npos &&
		str.find("async:io_error:") == string::npos &&
		str.find("async:create_file: failed in CreateFile for d:\\maps\\") == string::npos &&
		str.find("failed to open map ") == string::npos &&
		str.find("map open failed ") == string::npos &&
		str.find("webstats:") == string::npos &&
		//str.find("") == string::npos &&
		//str.find("") == string::npos &&
		//str.find("") == string::npos &&
		//str.find("") == string::npos &&
		//str.find("") == string::npos &&
		//str.find("") == string::npos &&
		//str.find("") == string::npos &&
		//str.find("") == string::npos &&
		//str.find("") == string::npos &&
		str.find("All for the convenience of the programmer :D") == string::npos
		) 
	{
		OutputDebugString("[Halo 4]: ");
		OutputDebugString(lineStr);
		OutputDebugString("\n");
	} 

}
void __declspec(naked) ConsolePrintHook()
{

	__asm
	{
		// Setup the stack and save the link register
		mflr	r12
		stw		r12, -8(r1)
		stwu	r1, -0x20(r1) // 32 bytes of stack

		// Increment by 4 and print
		addi	r3, r3, 4
		bl		ConsolePrintHelper();
	
		// Restore the stack and return
		addi	r1, r1, 0x20
		lwz		r12, -8(r1)
		mtlr	r12
		blr
	}
}

VOID HttpDownloadSucceedHelper(CHAR* lineStr, DWORD* data)
{

	std::string str;
	str = lineStr;

	// Blacklist heartbeat as it's not needed.
	if (str.find("/midnightpresenceapi/") == string::npos)
	{
		DWORD checksum = 0;
		for(DWORD x = 0; x < strlen(lineStr); x+=4)
			checksum = checksum ^ *((DWORD*)(lineStr + x));

		DWORD size = *(data);
		data += 5;

		CHAR filePath[0x200];
		ZeroMemory(filePath, ARRAYSIZE(filePath));
		sprintf(filePath, "GAME:\\logs\\halo4_0x%08X.bin", checksum);
		MemoryBuffer buffer;
		buffer.Add(lineStr, 0x100);
		buffer.Add(data, size);
		CWriteFile(filePath, (CHAR*)buffer.GetData(), buffer.GetDataLength());
		PrintLine("Data '%s' saved!", lineStr);
	}
}
void __declspec(naked) HttpDownloadSucceedHook()
{

	__asm
	{
		// r11 was replaced to get here, restore it.
		lis		r11, 0x821C
		ori		r11, r11, 0x95E4

		// Setup the stack and save the link register
		mr		r6, r12
		mflr	r12
		std		r0, -0x0008(r1)
		std		r2,	-0x0010(r1)
		std		r3, -0x0018(r1)
		std		r4, -0x0020(r1)
		std		r5, -0x0028(r1)
		std		r6, -0x0030(r1)
		std		r7, -0x0038(r1)
		std		r8, -0x0040(r1)
		std		r9, -0x0048(r1)
		std		r10, -0x0050(r1)
		std		r11, -0x0058(r1)
		std		r12, -0x0060(r1)
		std		r13, -0x0068(r1)
		std		r14, -0x0070(r1)
		std		r15, -0x0078(r1)
		std		r16, -0x0080(r1)
		std		r17, -0x0088(r1)
		std		r18, -0x0090(r1)
		std		r19, -0x0098(r1)
		std		r20, -0x00A0(r1)
		std		r21, -0x00A8(r1)
		std		r22, -0x00B0(r1)
		std		r23, -0x00B8(r1)
		std		r24, -0x00C0(r1)
		std		r25, -0x00C8(r1)
		std		r26, -0x00D0(r1)
		std		r27, -0x00D8(r1)
		std		r28, -0x00E0(r1)
		std		r29, -0x00E8(r1)
		std		r30, -0x00F0(r1)
		std		r31, -0x00F8(r1)
		stwu	r1, -0x160(r1)

		// Call the function
		mr		r4, r31
		mr		r3, r20
		bl		HttpDownloadSucceedHelper();
	
		// Restore the stack and return
		addi	r1, r1, 0x160
		ld		r0, -0x0008(r1)
		ld		r2,	-0x0010(r1)
		ld		r3, -0x0018(r1)
		ld		r4, -0x0020(r1)
		ld		r5, -0x0028(r1)
		ld		r6, -0x0030(r1)
		ld		r7, -0x0038(r1)
		ld		r8, -0x0040(r1)
		ld		r9, -0x0048(r1)
		ld		r10, -0x0050(r1)
		ld		r11, -0x0058(r1)
		ld		r12, -0x0060(r1)
		ld		r13, -0x0068(r1)
		ld		r14, -0x0070(r1)
		ld		r15, -0x0078(r1)
		ld		r16, -0x0080(r1)
		ld		r17, -0x0088(r1)
		ld		r18, -0x0090(r1)
		ld		r19, -0x0098(r1)
		ld		r20, -0x00A0(r1)
		ld		r21, -0x00A8(r1)
		ld		r22, -0x00B0(r1)
		ld		r23, -0x00B8(r1)
		ld		r24, -0x00C0(r1)
		ld		r25, -0x00C8(r1)
		ld		r26, -0x00D0(r1)
		ld		r27, -0x00D8(r1)
		ld		r28, -0x00E0(r1)
		ld		r29, -0x00E8(r1)
		ld		r30, -0x00F0(r1)
		ld		r31, -0x00F8(r1)
		mtlr	r12
		mr		r12, r6

		// Original code
		mr		r9, r24
		li		r7, 0xB
		li		r6, 2
		li		r5, 0x26E
		blr
	}
}

DWORD HaloUserSigninInfoHook(DWORD dwUserIndex, DWORD dwFlags, XUSER_SIGNIN_INFO* pSigninInfo)
{
	// Get our sign in info
	DWORD result = XamUserGetSigninInfo(dwUserIndex, dwFlags, pSigninInfo);

	if(pSigninInfo->UserSigninState != eXUserSigninState_NotSignedIn)
	{
		pSigninInfo->UserSigninState = eXUserSigninState_SignedInToLive;
		pSigninInfo->dwInfoFlags = XUSER_INFO_FLAG_LIVE_ENABLED;
		return ERROR_SUCCESS;
	}

	return result;
}
XUSER_SIGNIN_STATE HaloUserSigninStateHook(DWORD dwUserIndex)
{
	// Create our properties to determine network
	BOOL bEthernet = XNetGetEthernetLinkStatus() != NULL;
	BOOL bOfflineAccountSignedIn = FALSE;
	BOOL bOnlineAccountSignedIn = FALSE;

	// Get our signin states
	XUSER_SIGNIN_STATE logonState[XUSER_MAX_COUNT];
	for(DWORD x = 0; x < ARRAYSIZE(logonState); x++)
	{
		// Get our state and properties
		logonState[x] = XUserGetSigninState(x);
		if(logonState[x] == eXUserSigninState_SignedInLocally)
			bOfflineAccountSignedIn = TRUE;
		else if(logonState[x] == eXUserSigninState_SignedInToLive)
			bOnlineAccountSignedIn = TRUE;
	}

	// Get our network mode
	if(bEthernet && !bOfflineAccountSignedIn && bOnlineAccountSignedIn)
		HaloGame::SetNetworkMode(NETWORKMODE_XBOXLIVE);
	else if(bEthernet && bOfflineAccountSignedIn)
		HaloGame::SetNetworkMode(NETWORKMODE_SYSTEMLINK);
	else
		HaloGame::SetNetworkMode(NETWORKMODE_LOCAL);

	// Spoof the local account to appear as live
	if(logonState[dwUserIndex] == eXUserSigninState_SignedInLocally)
		logonState[dwUserIndex] = eXUserSigninState_SignedInToLive;

	// Patch our authorization status
	if(logonState[dwUserIndex] != eXUserSigninState_NotSignedIn)
		PatchAuthStatus(dwUserIndex);
	
	return logonState[dwUserIndex];
}
DWORD HaloUserCheckPrivilegeHook(DWORD dwUserIndex, XPRIVILEGE_TYPE PrivilegeType, BOOL* pfResult)
{ 
	DWORD result = XUserCheckPrivilege(dwUserIndex, PrivilegeType, pfResult);
	if(XUserGetSigninState(dwUserIndex) != eXUserSigninState_NotSignedIn)
	{
		*pfResult = TRUE;
		return ERROR_SUCCESS;
	}
	return result;
}
DWORD XNetGetEthernetLinkStatusHook()
{
	// Make it appear as though we have ethernet connection (required to enter past start screen)
	DWORD status = XNetGetEthernetLinkStatus();
	return (status || (DWORD)XNET_ETHERNET_LINK_ACTIVE);
}

CHAR watermark[0x20];
VOID StampWatermark()
{
	// Stamp our watermark.
	sprintf(watermark, "%s %.2f", ARCH_NAME, ARCH_VERSION);

	// Patch the code for the watermark
	DWORD* addr = (DWORD*)ARCH_ADDR_WATERMARK;
	DWORD address = (DWORD)watermark;
	DWORD patchData;

	if(address & 0x8000)
	{
		patchData = assembly::lis(11, ((address >> 16) & 0xFFFF) + 1);
		SetMemory(addr, &patchData, 4);
		patchData = assembly::addi(4, 11, (address & 0xFFFF));
		SetMemory(addr + 2, &patchData, 4);
	}
	else
	{
		patchData = assembly::lis(11, (address >> 16) & 0xFFFF);
		SetMemory(addr, &patchData, 4);
		patchData = assembly::addi(4, 11, address & 0xFFFF);
		SetMemory(addr + 2, &patchData, 4);
	}
}

VOID PatchMapVerification()
{
	// Apply patches to executable.
	DWORD patchData = assembly::li(3, 1);

	DWORD* signatureChecks = (DWORD*)ARCH_ADDR_MAPHEADERVALIDATION; //header validation
	SetMemory(signatureChecks, &patchData, 4);
	PrintLine("Patched map header validation..");

	signatureChecks = (DWORD*)ARCH_ADDR_RSAVALIDATION; // rsa validation
	SetMemory(signatureChecks, &patchData, 4);
	signatureChecks = (DWORD*)ARCH_ADDR_RSAVALIDATION2; // rsa validation
	SetMemory(signatureChecks, &patchData, 4);
	PrintLine("Patched RSA signature validation..");

	patchData = assembly::li(7, 1);
	signatureChecks = (DWORD*)ARCH_ADDR_STRINGVALIDATION; //string validation
	SetMemory(signatureChecks, &patchData, 4);
	PrintLine("Patched map string validation..");
}
VOID PatchAuthStatus(DWORD dwUserIndex)
{
	// Create patch data
	BYTE patchData[2] = { 0x01, 0xFF }; //The default 0x05 (auth_success) value won't let us into customs, so use 0xFF.
	// Set our authorization.
	BYTE* addrAuthStatus = (BYTE*)ARCH_ADDR_AUTHSTATUS;
	addrAuthStatus += (0x08 * dwUserIndex);
	if(memcmp(addrAuthStatus, patchData, sizeof(patchData)) != 0)
		SetMemory(addrAuthStatus, patchData, sizeof(patchData));
}
VOID PatchSessionLifeCycleLeave()
{
	DWORD* patchAddr = (DWORD*)ARCH_ADDR_LOBBYSESSIONKICK;
	DWORD patchData = assembly::li(15,0);
	SetMemory(patchAddr, &patchData, 4);
	PrintLine("Patched session life-cycle leave..");
}
VOID PatchUserRewards()
{
	DWORD* patchAddr = (DWORD*)ARCH_ADDR_REWARDS;
	DWORD patchData = INT_MAX;

	// If we haven't already patched.
	if(*patchAddr != patchData)
	{
		// Patch our unlocks first
		BYTE* patchAddr2 = (BYTE*)(ARCH_ADDR_REWARDS + 0x110);
		BYTE patchData2 = 1;
		for(int i = 0; i < 0xA0; i++)
		{
			SetMemory(patchAddr2, &patchData2, 1);
			patchAddr2 += 1;
		}

		// Patch our spartan points	
		SetMemory(patchAddr, &patchData, 4);
		// Patch our credits/xp.
		patchAddr+=2;
		SetMemory(patchAddr, &patchData, 4);
	}
}

VOID ApplyStartupPatches()
{
	// Reset some values
	_switchLobbyCurrentLobby = 0;

	//Stamp watermark
	StampWatermark();

	// Patch our map verification
	PatchMapVerification();
	PatchSessionLifeCycleLeave();

	// Hook our switch lobby code.
	DWORD* addr = (DWORD*)ARCH_ADDR_HOOKSWITCHLOBBY;
	PatchInJump(addr, (DWORD)SwitchLobbyHook, TRUE);
	PrintLine("Hooked switch_lobby function..");

	// Hook our film recording code
	addr = (DWORD*)ARCH_ADDR_HOOKFILMCANRECORD;
	PatchInJump(addr, (DWORD)FilmCanRecordHook, TRUE);
	PrintLine("Hooked film recording check..");

	// Hook to print to console
	addr = (DWORD*)ARCH_ADDR_CONSOLEHOOKADDR;
	PatchInJump(addr, (DWORD)ConsolePrintHook, TRUE);
	PrintLine("Hooked debug event output..");

#if 0
	// Hook to save downloads from server
	addr = (DWORD*)ARCH_ADDR_HTTPDOWNLOADHOOK;
	PatchInJump(addr, (DWORD)HttpDownloadSucceedHook, TRUE);
	PrintLine("Hooked http buffer downloader..");
#endif

	// Disable data mining
	DWORD patchData = assembly::li(3, 0);
	addr = (DWORD*)ARCH_ADDR_DATAMINING;
	SetMemory(addr, &patchData, 4);
	patchData = assembly::li(11, 0);
	addr = (DWORD*)ARCH_ADDR_DATAMININGENABLED;
	SetMemory(addr, &patchData, 4);
	PrintLine("Disabled data mining..");

	// Set our default network mode.
	addr = (DWORD*)ARCH_ADDR_DEFAULTNETWORKMODE_GARBAGE;
	patchData = assembly::nop();
	for(DWORD x = 0; x < 10; x++)
	{
		SetMemory(addr, &patchData, 4);
		addr += 1;
	}
	PrintLine("Patched network status (no ethernet = local, ethernet=systemlink, online=xboxlive)..");
	HaloGame::SetNetworkMode(NETWORKMODE_LOCAL);

	// This lets us unplug ethernet, wifi, whatever and still be able to play
	patchData = assembly::li(10, 1);
	addr = (DWORD*)ARCH_ADDR_ISONLIVE;
	SetMemory(addr, &patchData, 4);
	PrintLine("Forced the game to think we are always connected to live..");

	// Patch the sign in defense system so no controllers are kicked.
	patchData = assembly::li(8, 1);
	addr = (DWORD*)ARCH_ADDR_SETUPLOCALPLAYERDATA;
	SetMemory(addr, &patchData, 4);
	PrintLine("Patched user sign-in defense system..");

	// Allow us to actually use the armor
	patchData = assembly::li(3, 0);
	addr = (DWORD*)ARCH_ADDR_USELOCALREWARDS;
	SetMemory(addr, &patchData, 4);
	PrintLine("Hooked game to use local reward file instead of server..");

	// Hook user signin state for authorization and spoofing offline accounts as online.
	if(PatchModuleImport("xam.xex", 0x210, (DWORD)HaloUserSigninStateHook) != S_OK)
		PrintLine("Could not hook UserSigninState..");
	if(PatchModuleImport("xam.xex", 0x212, (DWORD)HaloUserCheckPrivilegeHook) != S_OK)
		PrintLine("Could not hook UserCheckPrivilege..");
	if(PatchModuleImport("xam.xex", 0x227, (DWORD)HaloUserSigninInfoHook) != S_OK)
		PrintLine("Could not hook UserSigninInfo..");
	if(PatchModuleImport("xam.xex", 0x4B, (DWORD)XNetGetEthernetLinkStatusHook) != S_OK)
		PrintLine("Could not hook XNetGetEthernetLinkStatus..");

	// Hook our title id to act as the full Halo 4 game to attempt to grab network settings.
	//if(PatchModuleImport("xam.xex", "xboxkrnl.exe", 0x12B, (DWORD)RtlImageXexHeaderFieldHook) != S_OK)
	//	PrintLine("Could not hook RtlImageXexHeaderField (xam)..");
	//if(PatchModuleImport("xboxkrnl.exe", 0x12B, (DWORD)RtlImageXexHeaderFieldHook) != S_OK)
	//	PrintLine("Could not hook RtlImageXexHeaderField (game)..");
	//if(PatchModuleImport("xam.xex", 0x136, (DWORD)XNetGetLogonGetTitleIDHook) != S_OK)
	//	PrintLine("Could not hook XNetLogonGetTitleID..");
}

//---------------------------------------------
// APPLICATION INFORMATION
//---------------------------------------------
const char* const ARCH_NAME = "ArchEngine";

const float ARCH_VERSION = 0.26f;
const int ARCH_TITLEID = 0x4D538A06;
const int ARCH_TITLEID2 = 0x4D530919;
const int ARCH_INIT_DELAY = 250;




//---------------------------------------------
//---------------------------------------------
//-------------FUN TRAINER STUFF---------------
//---------------------------------------------
//---------------------------------------------


//---------------------------------------------
// DirectX
//---------------------------------------------
const int ARCH_ADDR_D3DDEVICE = 0x83F2B750;

//---------------------------------------------
// Camera Information
//---------------------------------------------
// The addresses of the branches to make false in order to print our debug information on camera.
const int ARCH_ADDR_PRINTCAMCOORDS1 = 0x822F3E3C;
const int ARCH_ADDR_PRINTCAMCOORDS2 = 0x822F3E54;


const int ARCH_ADDR_CAMERAVIEWTYPE = 0x822F5AA4;

const int ARCH_ADDR_CAMERAFOV = 0x821099D0;
const float ARCH_VALUE_CAMERAFOVMODIFIER = 0.05f;

// Camera types we can choose from.
const enum CAMERATYPE
{
	CAMERATYPE_FOLLOWING = 0x00,
	CAMERATYPE_ORBITING = 0x01,
	CAMERATYPE_FLYING = 0x02,
	CAMERATYPE_FIRST_PERSON = 0x03,
	CAMERATYPE_DEAD = 0x04,
	CAMERATYPE_STATIC = 0x05,
	CAMERATYPE_SCRIPTED = 0x06,
	CAMERATYPE_AUTHORED  = 0x07,
	CAMERATYPE_RESPAWNING  = 0x08,
	CAMERATYPE_ANIMATED_TRICK = 0x09,
	CAMERATYPE_TRACKED_TARGET  = 0x0A,
	CAMERATYPE_SANDBOX = 0x0B,
	CAMERATYPE_SPACE_FIGHTER  = 0x0C,
	CAMERATYPE_REMOTE_STRIKER = 0x0D
};

//---------------------------------------------
// Globals
//---------------------------------------------
const int ARCH_ADDR_GLOBALINDEX = 0x30013BC0;

const int ARCH_ADDR_GAMETIMEGLOBALS = ARCH_ADDR_GLOBALINDEX + 0x5C;
const float ARCH_VALUE_GAMESPEEDMODIFIER = 0.3f;

const int ARCH_ADDR_PLAYERGLOBALS = ARCH_ADDR_GLOBALINDEX + 0x18;
const int ARCH_ADDR_POOLOBJECTS = ARCH_ADDR_GLOBALINDEX + 0x188;






//---------------------------------------------
//---------------------------------------------
//-------------FORCE LOADING MAPS--------------
//---------------------------------------------
//---------------------------------------------

// Map filenames that are used respectively with ARCH_ADDR_MAPPATH to specify map location.
const char* const ARCH_MAP_MAINMENU = "d:\\maps\\mainmenu";
const char* const ARCH_MAP_LONGBOW = "d:\\maps\\ca_gore_valley";
const char* const ARCH_MAP_ADRIFT = "d:\\maps\\ca_warhouse";
const char* const ARCH_MAP_HAVEN = "d:\\maps\\wraparound";

// Map types (incorrect, but here for the sake of play, we just use 0x02, infintiy)
const enum ARCH_MAPTYPE
{
	ARCH_MAPTYPE_CAMPAIGN = 0x01,
	ARCH_MAPTYPE_INFINITY = 0x02,
	ARCH_MAPTYPE_MULTIPLAYER = 0x04,
	ARCH_MAPTYPE_MAINMENU = 0x05
};

// the address of the code that uses the "PRE-RELEASE BUILD" watermark
const int ARCH_ADDR_WATERMARK = 0x824A3C54;
// [char*] the path of the map we currently have loaded or want to load.
const int ARCH_ADDR_MAPPATH = 0x842F0B24;
// [dword] the type of the map we're playing or want to load
const int ARCH_ADDR_MAPTYPE = 0x842DD2F0;
// [byte] the toggle for whether to reload or not (1=TRUE)
const int ARCH_ADDR_MAPRELOAD = 0x842DD2DF;











//---------------------------------------------
//---------------------------------------------
//--------------CHECKS & UNLOCKS---------------
//---------------------------------------------
//---------------------------------------------

//---------------------------------------------
// Console Printing
//---------------------------------------------
const int ARCH_ADDR_CONSOLEHOOKADDR = 0x822746E4;

//---------------------------------------------
// Storage Content Device ID
//---------------------------------------------
const int ARCH_ADDR_STORAGEDEVICE = 0x8343C2E4;

//---------------------------------------------
// Map Signature Checks
//---------------------------------------------
const int ARCH_ADDR_MAPHEADERVALIDATION = 0x822A5C70;
const int ARCH_ADDR_RSAVALIDATION = 0x822988C4;
const int ARCH_ADDR_RSAVALIDATION2 = 0x822A6178;
const int ARCH_ADDR_STRINGVALIDATION = 0x822E8F40;

//---------------------------------------------
// Authorization
//---------------------------------------------
// [byte] auth status. set to 0x05 to make the game authorize you.
const int ARCH_ADDR_AUTHSTATUS = 0x84BF4F38;
// address
const int ARCH_ADDR_HOOKSWITCHLOBBY = 0x82711094;
// hopper structure in exe mem
const int ARCH_ADDR_HOPPERLIST = 0x84B1E8C0;
// forge and some other lobbies try kicking us
const int ARCH_ADDR_LOBBYSESSIONKICK = 0x82686C78;

//---------------------------------------------
// Rewards
//---------------------------------------------
const int ARCH_ADDR_REWARDS = 0x84709B80;
const int ARCH_ADDR_USERSTRUCT = 0x84854548;




//---------------------------------------------
// Forge mode
//---------------------------------------------
const int ARCH_ADDR_FORGEMODEHOOK = 0x822D9FE4;
//---------------------------------------------

// Theater
//---------------------------------------------
const int ARCH_ADDR_HOOKFILMCANRECORD = 0x82803F00;
const int ARCH_ADDR_GAMESTATUS = 0x84226168;




//---------------------------------------------
// Disable data mining
//---------------------------------------------
const int ARCH_ADDR_DATAMINING = 0x822FEAE0;
const int ARCH_ADDR_DATAMININGENABLED = 0x822FDEE8;



//---------------------------------------------
// Network Mode
//---------------------------------------------
const int ARCH_ADDR_DEFAULTNETWORKMODE_GARBAGE = 0x82687A88;
const int ARCH_ADDR_DEFAULTNETWORKMODE = 0x82687AB0;
const int ARCH_ADDR_ISONLIVE = 0x8281BD04;

//---------------------------------------------
// Local Player Data
//---------------------------------------------
const int ARCH_ADDR_SETUPLOCALPLAYERDATA = 0x82687A34;
const int ARCH_ADDR_USELOCALREWARDS = 0x8268C954;

// Enumeration for network mode
const enum NETWORKMODE
{
	NETWORKMODE_LOCAL = 1,
	NETWORKMODE_SYSTEMLINK = 2,
	NETWORKMODE_XBOXLIVE = 3
};

//---------------------------------------------
// Http Client
//---------------------------------------------
const int ARCH_ADDR_HTTPDOWNLOADHOOK = 0x828C8B50; // r30 = name, r31 = data


/*
SP Grav = 0.61086524 = 0x82109680
MP Grav = 4.1712594 = 0x82109024
*/

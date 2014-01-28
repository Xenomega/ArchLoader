#pragma once

typedef long							NTSTATUS;
#define NT_EXTRACT_ST(Status)			((((ULONG)(Status)) >> 30)& 0x3)
#define NT_SUCCESS(Status)              (((NTSTATUS)(Status)) >= 0)
#define NT_INFORMATION(Status)          (NT_EXTRACT_ST(Status) == 1)
#define NT_WARNING(Status)              (NT_EXTRACT_ST(Status) == 2)
#define NT_ERROR(Status)                (NT_EXTRACT_ST(Status) == 3)

typedef struct _ANSI_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PCHAR Buffer;
} ANSI_STRING, *PANSI_STRING;

typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWCHAR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _EX_TITLE_TERMINATE_REGISTRATION {
	void*	   NotificationRoutine;
	DWORD	   Priority;
	LIST_ENTRY ListEntry;
} EX_TITLE_TERMINATE_REGISTRATION, *PEX_TITLE_TERMINATE_REGISTRATION;

typedef struct _XEX_IMPORT_DESCRIPTOR {
   DWORD Size;
   DWORD NameTableSize;
   DWORD ModuleCount;
} XEX_IMPORT_DESCRIPTOR, *PXEX_IMPORT_DESCRIPTOR;

typedef struct _HV_IMAGE_IMPORT_TABLE {
   BYTE  NextImportDigest[0x14];
   DWORD ModuleNumber;
   DWORD Version[0x02];
   BYTE  Unused;
   BYTE  ModuleIndex;
   WORD  ImportCount;
} HV_IMAGE_IMPORT_TABLE, *PHV_IMAGE_IMPORT_TABLE;

typedef struct _XEX_EXECUTION_ID {
	DWORD		 MediaID;
	DWORD		 Version;
	DWORD		 BaseVersion;
	union {
		struct {
			WORD PublisherID;
			WORD GameID;
		};
		DWORD	 TitleID;
	};
	BYTE		 Platform;
	BYTE		 ExecutableType;
	BYTE		 DiscNum;
	BYTE		 DiscsInSet;
	DWORD		 SaveGameID;
} XEX_EXECUTION_ID, *PXEX_EXECUTION_ID;

typedef struct _XEX_IMPORT_TABLE {
   DWORD                 TableSize;
   HV_IMAGE_IMPORT_TABLE ImportTable;
} XEX_IMPORT_TABLE, *PXEX_IMPORT_TABLE;

typedef struct _LDR_DATA_TABLE_ENTRY { 
	LIST_ENTRY     InLoadOrderLinks;
	LIST_ENTRY     InClosureOrderLinks;
	LIST_ENTRY     InInitializationOrderLinks;
	VOID*          NtHeadersBase;
	VOID*          ImageBase;
	DWORD          SizeOfNtImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	DWORD          Flags;
	DWORD          SizeOfFullImage;
	VOID*          EntryPoint;
	WORD           LoadCount;
	WORD           ModuleIndex;
	VOID*          DllBaseOriginal;
	DWORD          CheckSum;
	DWORD          ModuleLoadFlags;
	DWORD          TimeDateStamp;
	VOID*          LoadedImports;
	VOID*          XexHeaderBase;
	union {
		ANSI_STRING               LoadFileName;
		struct {
			_LDR_DATA_TABLE_ENTRY* ClosureRoot;
			_LDR_DATA_TABLE_ENTRY* TraversalParent;
		} asEntry;
	};
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

typedef struct _XBOX_HARDWARE_INFO {
	DWORD Flags;
	BYTE  NumberOfProcessors;
	BYTE  PCIBridgeRevisionID;
	BYTE  Reserved[6];
	WORD  BldrMagic;
	WORD  BldrFlags;
} XBOX_HARDWARE_INFO, *PXBOX_HARDWARE_INFO;

typedef struct _KERNEL_VERSION {
	WORD Major;
	WORD Minor;
	WORD Build;
	BYTE ApprovalType;
	BYTE QFE;
} KERNEL_VERSION, *PKERNEL_VERSION;

// Valid values for the Attributes field
#define OBJ_INHERIT             0x00000002L
#define OBJ_PERMANENT           0x00000010L
#define OBJ_EXCLUSIVE           0x00000020L
#define OBJ_CASE_INSENSITIVE    0x00000040L
#define OBJ_OPENIF              0x00000080L
#define OBJ_OPENLINK            0x00000100L
#define OBJ_VALID_ATTRIBUTES    0x000001F2L

typedef struct _OBJECT_ATTRIBUTES {
    HANDLE		 RootDirectory;
	PANSI_STRING ObjectName;
    ULONG		 Attributes;
} OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;

// object type strings
#define OBJ_TYP_SYMBLINK	0x626d7953
#define OBJ_TYP_DIRECTORY	0x65726944
#define OBJ_TYP_DEVICE		0x69766544
#define OBJ_TYP_EVENT       0x76657645
#define OBJ_TYP_DEBUG       0x63706d64

typedef struct _OBJECT_DIRECTORY_INFORMATION{
	ANSI_STRING Name;
	DWORD		Type;
	CHAR		NameEx[MAX_PATH];
} OBJDIR_INFORMATION, *POBJDIR_INFORMATION;

typedef struct _IO_STATUS_BLOCK {
    union {
        NTSTATUS Status;
        PVOID	 Pointer;
    } st;
    ULONG_PTR	 Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

typedef VOID (NTAPI *PIO_APC_ROUTINE) (
    IN PVOID ApcContext,
    IN PIO_STATUS_BLOCK IoStatusBlock,
    IN ULONG Reserved
);

typedef struct _FILE_DIRECTORY_INFORMATION {
	ULONG		  NextEntryOffset; 
	ULONG		  FileIndex; 
	LARGE_INTEGER CreationTime; 
	LARGE_INTEGER LastAccessTime; 
	LARGE_INTEGER LastWriteTime; 
	LARGE_INTEGER ChangeTime; 
	LARGE_INTEGER EndOfFile; 
	LARGE_INTEGER AllocationSize; 
	ULONG		  FileAttributes; 
	ULONG		  FileNameLength; 
	CHAR		  FileName[MAX_PATH];
} FILE_DIRECTORY_INFORMATION, *PFILE_DIRECTORY_INFORMATION;

EXTERN_C {

	extern XBOX_HARDWARE_INFO*	  XboxHardwareInfo;
	extern KERNEL_VERSION*		  XboxKrnlVersion;
	extern PLDR_DATA_TABLE_ENTRY* XexExecutableModuleHandle;

	void ExRegisterTitleTerminateNotification(PEX_TITLE_TERMINATE_REGISTRATION, BOOL);

	void RtlInitAnsiString(PANSI_STRING DestinationString, const char* SourceString);

	void*	RtlImageXexHeaderField(void* XexHeaderBase, DWORD Key);
	HRESULT XexStartExecutable(FARPROC TitleProcessInitThreadProc);
	BOOL	XexCheckExecutablePrivilege(DWORD Privilege);

	DWORD XamGetCurrentTitleId();

	DWORD ExGetXConfigSetting(WORD categoryNum, WORD settingNum, 
		BYTE* outputBuff, DWORD outputBuffSize, WORD* settingSize);

	DWORD ExSetXConfigSetting(WORD dwCategory, WORD dwSetting, PVOID pBuffer, WORD szSetting);

	DWORD XeKeysHmacSha(DWORD keyNum,
		BYTE* input1, DWORD input1Size,
		BYTE* input2, DWORD input2Size,
		BYTE* input3, DWORD input3Size,
		BYTE* digest, DWORD digestSize
		);

	NTSTATUS ObCreateSymbolicLink(PANSI_STRING, PANSI_STRING);
	NTSTATUS ObDeleteSymbolicLink(PANSI_STRING);
	NTSTATUS NtOpenSymbolicLinkObject(PHANDLE LinkHandle, POBJECT_ATTRIBUTES ObjectAttributes);
	NTSTATUS NtQuerySymbolicLinkObject(HANDLE LinkHandle, PANSI_STRING LinkTarget, PULONG ReturnedLength);
	NTSTATUS NtClose(HANDLE Handle);

	NTSTATUS XeKeysGetKey(DWORD KeyNum, void* KeyBuffer, DWORD* KeySize);

	BOOL MmIsAddressValid(unsigned __int64 Address);

	void HalReturnToFirmware(DWORD);

	void  XapiThreadStartup(void (__cdecl *StartRoutine)(void*), void* StartContext);
	DWORD ExCreateThread(PHANDLE pHandle, DWORD dwStackSize, 
		LPDWORD lpThreadId, VOID* apiThreadStartup , 
		LPTHREAD_START_ROUTINE lpStartAddress, 
		LPVOID lpParameter, DWORD dwCreationFlagsMod);

	NTSTATUS NtCreateFile(HANDLE* FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes,
		PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER AllocationSize, ULONG FileAttributes, 
		ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions);

	NTSTATUS NtOpenFile(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes,
		PIO_STATUS_BLOCK IoStatusBlock, ULONG ShareAccess, ULONG OpenOptions); 

	NTSTATUS NtQueryDirectoryFile(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, 
		PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation, ULONG Length, PANSI_STRING FileMask, DWORD Unkn);

	NTSTATUS NtOpenDirectoryObject(PHANDLE DirectoryHandle, POBJECT_ATTRIBUTES ObjectAttributes);

	NTSTATUS NtQueryDirectoryObject(HANDLE DirectoryHandle, PVOID Buffer, ULONG Length, 
		BOOLEAN ReturnSingleEntry, PULONG Context, PULONG ReturnLength);

	NTSTATUS NtClose(HANDLE Handle);

	UINT64 MmGetPhysicalAddress(UINT64 Address);

	UINT64
	NTAPI 
	XeKeysExecute(
		UINT64		pBuffer, 
		DWORD		dwFileSize, 
		UINT64		Input1, 
		UINT64		Input2, 
		UINT64		Input3, 
		UINT64		Input4
		); 	
}
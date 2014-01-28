#include "stdafx.h"
#include "Generic.h"

VOID PatchInJump(DWORD* Address, DWORD Destination, BOOL Linked) {

	DWORD setData[4];

	if(Destination & 0x8000)
		setData[0] = 0x3D600000 + (((Destination >> 16) & 0xFFFF) + 1);
	else
		setData[0] = 0x3D600000 + ((Destination >> 16) & 0xFFFF);

	setData[1] = 0x396B0000 + (Destination & 0xFFFF);
	setData[2] = 0x7D6903A6;

	if(Linked)
		setData[3] = 0x4E800421;
	else
		setData[3] = 0x4E800420;

	SetMemory(Address, setData, 16);
}

FARPROC ResolveFunction(CHAR* ModuleName, DWORD Ordinal) {

	// Get our module handle
	HMODULE mHandle = GetModuleHandle(ModuleName);
	if(mHandle == NULL)
		return NULL;

	// Return our address
	return GetProcAddress(mHandle, (LPCSTR)Ordinal);
}
DWORD PatchModuleImport(CHAR* ImportedModuleName, DWORD Ordinal, DWORD PatchAddress) {
	// Call our function now
	return PatchModuleImport(*XexExecutableModuleHandle, ImportedModuleName, Ordinal, PatchAddress);
}
DWORD PatchModuleImport(CHAR* Module, CHAR* ImportedModuleName, DWORD Ordinal, DWORD PatchAddress) {

	// Get our module handle
	LDR_DATA_TABLE_ENTRY* moduleHandle = 
		(LDR_DATA_TABLE_ENTRY*)GetModuleHandle(Module);
	
	// Check our handle
	if(moduleHandle == NULL) 
		return S_FALSE;

	// Call our function now
	return PatchModuleImport(moduleHandle, ImportedModuleName, 
		Ordinal, PatchAddress);
}
DWORD PatchModuleImport(PLDR_DATA_TABLE_ENTRY Module, CHAR* ImportedModuleName, DWORD Ordinal, DWORD PatchAddress) {

	// First resolve this imports address
	DWORD address = (DWORD)ResolveFunction(ImportedModuleName, Ordinal);
	if(address == NULL)
		return S_FALSE;

	// Get our header field from this module
	VOID* headerBase = Module->XexHeaderBase;
	PXEX_IMPORT_DESCRIPTOR importDesc = (PXEX_IMPORT_DESCRIPTOR)
		RtlImageXexHeaderField(headerBase, 0x000103FF);
	if(importDesc == NULL)
		return S_FALSE;

	// Our result
	DWORD result = 2; // No occurances patched

	// Get our string table position
	CHAR* stringTable = (CHAR*)(importDesc + 1);
	
	// Get our first entry
	PXEX_IMPORT_TABLE importTable = (PXEX_IMPORT_TABLE)
		(stringTable + importDesc->NameTableSize);

	// Loop through our table
	for(DWORD x = 0; x < importDesc->ModuleCount; x++) {
		
		// Go through and search all addresses for something that links
		DWORD* importAdd = (DWORD*)(importTable + 1);
		for(DWORD y = 0; y < importTable->ImportTable.ImportCount; y++) {

			// Check the address of this import
			DWORD value = *((DWORD*)importAdd[y]);
			if(value == address) {

				// We found a matching address address
				SetMemory((DWORD*)importAdd[y], &PatchAddress, 4);
				DWORD newCode[4];
				PatchInJump(newCode, PatchAddress, FALSE);
				SetMemory((DWORD*)importAdd[y + 1], newCode, 16);

				// We patched at least one occurance
				result = S_OK;
			}
		}

		// Goto the next table
		importTable = (PXEX_IMPORT_TABLE)(((BYTE*)importTable) + 
			importTable->TableSize);
	}

	// Return our result
	return result;
}
HRESULT SetCodeBranch(DWORD SourceAddress, DWORD TargetAddress) {

	// Calculate our code
	DWORD code = 0x4C000001 + (TargetAddress - SourceAddress);
	SetMemory((VOID*)SourceAddress, &code, 4);

	// All done
	return S_OK;
}
HRESULT CreateSymbolicLink(CHAR* szDrive, CHAR* szDeviceName, BOOL System) {

	// Setup our path
	CHAR szDestinationDrive[MAX_PATH];
	if(System)
		sprintf_s(szDestinationDrive, MAX_PATH, "\\System??\\%s", szDrive);
	else
		sprintf_s(szDestinationDrive, MAX_PATH, "\\??\\%s", szDrive);

	// Setup our strings
	ANSI_STRING linkname, devicename;
	RtlInitAnsiString(&linkname, szDestinationDrive);
	RtlInitAnsiString(&devicename, szDeviceName);

	// Create finally
	NTSTATUS status = ObCreateSymbolicLink(&linkname, &devicename);
	if (status >= 0)
		return S_OK;
	return S_FALSE;
}
HRESULT DeleteSymbolicLink(CHAR* szDrive, BOOL System) {

	// Setup our path
	CHAR szDestinationDrive[MAX_PATH];
	if(System)
		sprintf_s(szDestinationDrive, MAX_PATH, "\\System??\\%s", szDrive);
	else
		sprintf_s(szDestinationDrive, MAX_PATH, "\\??\\%s", szDrive);

	// Setup our string
	ANSI_STRING linkname;
	RtlInitAnsiString(&linkname, szDestinationDrive);
	
	// Delete finally
	NTSTATUS status = ObDeleteSymbolicLink(&linkname);
	if (status >= 0)
		return S_OK;
	return S_FALSE;
}
VOID __cdecl PrintLine( const CHAR* strFormat, ... ) {

    va_list pArgList;
    va_start( pArgList, strFormat );

    CHAR buffer[ 0x1000 ];
    vsprintf( buffer, strFormat, pArgList );

    printf("[%s %.2f]: %s\n", ARCH_NAME, ARCH_VERSION, buffer );
}

BOOL CReadFile(const CHAR * FileName, MemoryBuffer &pBuffer) {

	HANDLE hFile;
	DWORD dwFileSize, dwNumberOfBytesRead;
	hFile = CreateFile(FileName, 
		GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		PrintLine("CreateFile failed with %08X.", GetLastError());
		return FALSE;
	}
	dwFileSize = GetFileSize(hFile, NULL);
	PBYTE lpBuffer = (BYTE*)malloc(dwFileSize);
	if(ReadFile(hFile, lpBuffer, dwFileSize, &dwNumberOfBytesRead, NULL) == FALSE)
	{
		PrintLine("ReadFile failed with %08X.", GetLastError());
		return FALSE;
	}
	else if (dwNumberOfBytesRead != dwFileSize)
	{
		PrintLine("ReadFile did not read the correct ammount of bytes.");
		return FALSE;
	}
	CloseHandle(hFile);
	pBuffer.Add(lpBuffer, dwFileSize);
	return TRUE;
}
BOOL CWriteFile(const CHAR* FilePath, const CHAR* Data, DWORD Size) {

	// Open our file
	HANDLE fHandle = CreateFile(FilePath, GENERIC_WRITE, FILE_SHARE_WRITE,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// Read our data
	DWORD writeSize = Size;
	WriteFile(fHandle, Data, writeSize, &writeSize, NULL);

	// Close our file
	CloseHandle(fHandle);

	// All done
	return TRUE;
}
#pragma once

#include "KernelExports.h"

#if FDEBUG
#define SetMemory(Dest, Source, Size) { DmSetMemory(Dest, Size, Source, NULL); }
#else
#define SetMemory(Dest, Source, Size) { memcpy(Dest, Source, Size); }
#endif

class MemoryBuffer
{
public:

            MemoryBuffer( DWORD dwSize = 512 )
            {
                m_pBuffer = NULL;
                m_dwDataLength = 0;
                m_dwBufferSize = 0;

                if( ( dwSize < UINT_MAX ) && ( dwSize != 0 ) )
                {
                    m_pBuffer = ( BYTE* )malloc( dwSize + 1 );    // one more char, in case when using string funcions
                    if( m_pBuffer )
                    {
                        m_dwBufferSize = dwSize;
                        m_pBuffer[0] = 0;
                    }
                }
            };

            ~MemoryBuffer()
            {
                if( m_pBuffer )
                    free( m_pBuffer );

                m_pBuffer = NULL;
                m_dwDataLength = 0;
                m_dwBufferSize = 0;
            };

    // Add chunk of memory to buffer
    BOOL    Add( const void* p, DWORD dwSize )
    {
        if( CheckSize( dwSize ) )
        {
            memcpy( m_pBuffer + m_dwDataLength, p, dwSize );
            m_dwDataLength += dwSize;
            *( m_pBuffer + m_dwDataLength ) = 0;    // fill end zero
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    };

    // Get the data in buffer
    BYTE* GetData() const
    {
        return m_pBuffer;
    };

    // Get the length of data in buffer
    DWORD   GetDataLength() const
    {
        return m_dwDataLength;
    };

    // Rewind the data pointer to the begining
    void    Rewind()
    {
        m_dwDataLength = 0; m_pBuffer[ 0 ] = 0;
    };

private:

    BYTE* m_pBuffer;

    DWORD m_dwDataLength;

    DWORD m_dwBufferSize;

    // Automatically adjust increase buffer size if necessary
    BOOL    CheckSize( DWORD dwSize )
    {
        if( m_dwBufferSize >= ( m_dwDataLength + dwSize ) )
        {
            return TRUE;    // Enough space
        }
        else
        {
            // Try to double it
            DWORD dwNewSize = max( m_dwDataLength + dwSize, m_dwBufferSize * 2 );
            BYTE* pNewBuffer = ( UCHAR* )realloc( m_pBuffer, dwNewSize + 1 );        // one more char
            if( pNewBuffer )
            {
                m_pBuffer = pNewBuffer;
                m_dwBufferSize = dwNewSize;
                return TRUE;
            }
            else
            {
                // Failed
                return FALSE;
            }
        }
    }
};

VOID PatchInJump(DWORD* Address, DWORD Destination, BOOL Linked);
FARPROC ResolveFunction(CHAR* ModuleName, DWORD Ordinal);
DWORD PatchModuleImport(CHAR* ImportedModuleName, DWORD Ordinal, DWORD PatchAddress);
DWORD PatchModuleImport(CHAR* Module, CHAR* ImportedModuleName, DWORD Ordinal, DWORD PatchAddress);
DWORD PatchModuleImport(PLDR_DATA_TABLE_ENTRY Module, CHAR* ImportedModuleName, DWORD Ordinal, DWORD PatchAddress);

HRESULT SetCodeBranch(DWORD SourceAddress, DWORD TargetAddress);

HRESULT CreateSymbolicLink(CHAR* szDrive, CHAR* szDeviceName, BOOL System = TRUE);
HRESULT DeleteSymbolicLink(CHAR* szDrive, BOOL System = TRUE);

VOID __cdecl PrintLine(const CHAR* strFormat, ...);
BOOL CReadFile(const CHAR * FileName, MemoryBuffer &pBuffer);
BOOL CWriteFile(const CHAR* FilePath, const CHAR* Data, DWORD Size);

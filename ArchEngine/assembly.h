#include "stdafx.h"
#pragma once

class assembly
{
private:

public:

static DWORD nop()
{
	return 0x60000000;
}
static DWORD addi(WORD rD, WORD rA, WORD VALUE)
{
            return (DWORD)(
                (0x38 << 24) |
                (rD << 21) |
                (rA << 16 ) |
                VALUE
                );
}
static DWORD addis(WORD rD, WORD rA, WORD VALUE)
{
			return (DWORD)(
                (0x3D << 24) |
                (rD << 21) |
                (rA << 16 ) |
                VALUE
                );
}

static DWORD li(WORD rD, WORD VALUE)
{
	return addi(rD, 0, VALUE);
}

static DWORD lis(WORD rD, WORD VALUE)
{
	return addis(rD, 0, VALUE);
}

};

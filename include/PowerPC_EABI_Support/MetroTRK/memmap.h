#ifndef METROTRK_MEMMAP_H
#define METROTRK_MEMMAP_H

#include "PowerPC_EABI_Support/MetroTRK/trk.h"

typedef struct memRange {
	u8* start;
	u8* end;
	BOOL readable;
	BOOL writeable;
} memRange;

const memRange gTRKMemMap[1] = { { (u8*)0, (u8*)-1, TRUE, TRUE } };

#endif

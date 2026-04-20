#ifndef FFCC_REDSOUND_REDGLOBALS_H
#define FFCC_REDSOUND_REDGLOBALS_H

#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/file_io.h"
#include "dolphin/os.h"
#include "ffcc/RedSound/RedStream.h"
#include "types.h"

class CRedDriver;
class CRedEntry;
class CRedMemory;

extern int gRedCommandHandlerTable[];
extern FILE DAT_8021d1a8;
extern u32 DAT_8021d7f0[];
extern int DAT_8021d820[];
extern int DAT_8021dc20[];
extern signed char DAT_8021dcce[];
extern s16 DAT_8021ddce[];
extern s16 DAT_8021de4e;
extern s16 DAT_8021dfce[];
extern int DAT_8021e1d0[];
extern int DAT_8021ec10[];
extern CRedEntry DAT_8032e154;
extern OSSemaphore DAT_8032e120;
extern void* DAT_8032e12c[];
extern int DAT_8032e17c[];
extern unsigned int DAT_8032ec30;
extern int DAT_8032f3c0;
extern int DAT_8032f3c4;
extern int DAT_8032f3c8;
extern int* DAT_8032f3cc;
extern void* DAT_8032f3d0;
extern void* DAT_8032f3d4;
extern void* DAT_8032f3d8;
extern void* DAT_8032f3dc;
extern void* DAT_8032f3f0;
extern void* DAT_8032f3f4;
extern int DAT_8032f3f8;
extern void* DAT_8032f3fc;
extern int DAT_8032f400;
extern int DAT_8032f404;
extern int DAT_8032f408;
extern int gRedMemoryDebugEnabled;
extern int DAT_8032f40c;
extern int DAT_8032f410;
extern int DAT_8032f414;
extern void* DAT_8032f418;
extern int* DAT_8032f41c;
extern int* DAT_8032f420;
extern int DAT_8032f424;
extern int* DAT_8032f428;
extern int DAT_8032f42c;
extern int DAT_8032f430;
extern int DAT_8032f434;
extern RedStreamDATA* p_Stream;
extern int DAT_8032f43c;
extern int DAT_8032f440;
extern unsigned int* DAT_8032f444;
extern void* DAT_8032f450;
extern void* DAT_8032f454;
extern int DAT_8032f458;
extern void* DAT_8032f45c;
extern int DAT_8032f460;
extern void* DAT_8032f464;
extern int gRedDriverStatus;
extern void* DAT_8032f46c;
extern int DAT_8032f470;
extern void* DAT_8032f474;
extern int DAT_8032f478[2];
extern int DAT_8032f484;
extern CRedMemory DAT_8032f468;
extern u8 m_RandomIndex;
extern int p_ReverbData;
extern u32* p_ReverbSize;
extern u32 m_ChangeStatus;
extern int* p_SkipKeyOn;
extern CRedDriver gRedDriver;
extern volatile unsigned int DAT_8032f4c4;
extern volatile int DAT_8032f4c8;

#endif

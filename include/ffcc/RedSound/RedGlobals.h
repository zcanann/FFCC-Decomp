#ifndef FFCC_REDSOUND_REDGLOBALS_H
#define FFCC_REDSOUND_REDGLOBALS_H

#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/file_io.h"
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
extern void* DAT_8032e170;
extern int DAT_8032e17c[];
extern unsigned int DAT_8032ec30;
extern void* DAT_8032f3f0;
extern void* DAT_8032f3f4;
extern int DAT_8032f3f8;
extern void* DAT_8032f3fc;
extern int DAT_8032f408;
extern int DAT_8032f40c;
extern int DAT_8032f410;
extern int DAT_8032f414;
extern int* DAT_8032f41c;
extern int* DAT_8032f420;
extern int DAT_8032f424;
extern int DAT_8032f430;
extern int DAT_8032f434;
extern void* DAT_8032f438;
extern unsigned int* DAT_8032f444;
extern int DAT_8032f470;
extern void* DAT_8032f474;
extern int DAT_8032f478;
extern CRedMemory DAT_8032f480;
extern u8 DAT_8032f4a8;
extern int DAT_8032f4ac;
extern u32* DAT_8032f4b0;
extern u32 DAT_8032f4b4;
extern int* DAT_8032f4b8;
extern CRedDriver CRedDriver_8032f4c0;
extern volatile unsigned int DAT_8032f4c4;
extern void* DAT_8032f4c8;

#endif

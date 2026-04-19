#ifndef _FFCC_FS_USB_PROCESS_H_
#define _FFCC_FS_USB_PROCESS_H_

#include "types.h"
#include "dolphin/gx/GXStruct.h"

class CDataHeader;
class CFunnyShapePcs;

struct FS_DISPLAY_STATUS
{
    u32 flags;        // 0x00
    GXColor clear;    // 0x04
    u32 unk08;        // 0x08
    u32 unk0C;        // 0x0C
    u32 unk10;        // 0x10
    u32 unk14;        // 0x14
    u32 unk18;        // 0x18
    u32 unk1C;        // 0x1C
    u32 unk20;        // 0x20
    u32 unk24;        // 0x24
    u16 unk28;        // 0x28
    u16 unk2A;        // 0x2A
    u32 unk2C;        // 0x2C
    u32 unk30;        // 0x30
    u8 unk34[0xC];    // 0x34

	FS_DISPLAY_STATUS& operator=(const FS_DISPLAY_STATUS&);
};

struct OSFS_SHAPE_ST
{
    u16 flags;      // 0x00
    s16 count;      // 0x02
    u32 unk04;      // 0x04
    u16 unk08;      // 0x08
    u8 unk0A[4];    // 0x0A
    u16 unk0E;      // 0x0E

	OSFS_SHAPE_ST& operator=(const OSFS_SHAPE_ST&);
};

struct OSFS_ANM_ST
{
    u32 unk00;       // 0x00
    u16 unk04;       // 0x04
    u16 unk06;       // 0x06
    u16 unk08;       // 0x08
    u16 unk0A;       // 0x0A
    void* anmData;   // 0x0C
};

#endif // _FFCC_FS_USB_PROCESS_H_

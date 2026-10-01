#ifndef GUARD_GLOBAL_H
#define GUARD_GLOBAL_H

#include "gba_types.h"

typedef char *va_list;
#define __va_rounded_size(type) (((sizeof(type) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))
#define va_start(ap, last) ((ap) = (va_list)__builtin_next_arg(last))
#define va_arg(ap, type) ((ap) = (va_list)((char *)(ap) + __va_rounded_size(type)), *((type *)(void *)((char *)(ap) - __va_rounded_size(type))))
#define va_end(ap)

#define PLTT 0x05000000
#define VRAM 0x06000000
#define OAM  0x07000000

#define REG_DISPCNT      (*(vu16 *)0x04000000)
#define REG_DISPSTAT     (*(vu16 *)0x04000004)
#define REG_VCOUNT_MATCH (*(vu8 *)0x04000005)
#define REG_VCOUNT       (*(vu8 *)0x04000006)
#define REG_BG0CNT       (*(vu16 *)0x04000008)
#define REG_BG1CNT       (*(vu16 *)0x0400000A)
#define REG_BG2CNT       (*(vu16 *)0x0400000C)
#define REG_BG0HOFS      (*(vu16 *)0x04000010)
#define REG_BG0VOFS      (*(vu16 *)0x04000012)
#define REG_BG1HOFS      (*(vu16 *)0x04000014)
#define REG_BG1VOFS      (*(vu16 *)0x04000016)
#define REG_BG2PA        (*(vu16 *)0x04000020)
#define REG_BG2PB        (*(vu16 *)0x04000022)
#define REG_BG2PC        (*(vu16 *)0x04000024)
#define REG_BG2PD        (*(vu16 *)0x04000026)
#define REG_BG2X_L       (*(vu16 *)0x04000028)
#define REG_BG2X_H       (*(vu16 *)0x0400002A)
#define REG_BG2Y_L       (*(vu16 *)0x0400002C)
#define REG_BG2Y_H       (*(vu16 *)0x0400002E)
#define REG_MOSAIC       (*(vu16 *)0x0400004C)
#define REG_BLDCNT       (*(vu16 *)0x04000050)
#define REG_BLDALPHA     (*(vu16 *)0x04000052)
#define REG_DMA0CNT_H    (*(vu16 *)0x040000BA)
#define REG_KEYINPUT     (*(vu16 *)0x04000130)
#define REG_KEYCNT       (*(vu16 *)0x04000132)
#define REG_RCNT         (*(vu16 *)0x04000134)
#define REG_JOYCNT       (*(vu16 *)0x04000140)
#define REG_JOY_RECV     (*(vu32 *)0x04000150)
#define REG_JOY_TRANS    (*(vu32 *)0x04000154)
#define REG_JOYSTAT      (*(vu16 *)0x04000158)
#define REG_IE           (*(vu16 *)0x04000200)
#define REG_IF           (*(vu16 *)0x04000202)
#define REG_WAITCNT      (*(vu16 *)0x04000204)
#define REG_IME          (*(vu16 *)0x04000208)

#define REG_ADDR_DMA0 0x040000B0
#define REG_ADDR_DMA3 0x040000D4

#define INTR_FLAG_VBLANK  0x0001
#define INTR_FLAG_VCOUNT  0x0004
#define INTR_FLAG_SERIAL  0x0080
#define INTR_FLAG_KEYPAD  0x1000
#define INTR_FLAG_GAMEPAK 0x2000

#define DISPCNT_BG0_ON 0x0100
#define DISPCNT_BG1_ON 0x0200
#define DISPCNT_BG2_ON 0x0400
#define DISPCNT_OBJ_ON 0x1000

#define JOYCNT_RESET 0x1
#define JOYCNT_RECV  0x2
#define JOYCNT_SEND  0x4

#define INTR_CHECK  (*(vu16 *)0x03007FF8)
#define INTR_VECTOR (*(void **)0x03007FFC)

#define KEY_MASK 0x3FF
#define A_BUTTON      0x001
#define B_BUTTON      0x002
#define SELECT_BUTTON 0x004
#define START_BUTTON  0x008
#define DPAD_RIGHT    0x010
#define DPAD_LEFT     0x020
#define DPAD_UP       0x040
#define DPAD_DOWN     0x080
#define R_BUTTON      0x100
#define L_BUTTON      0x200

#define DmaSet(src, dst, control)                   \
    {                                               \
        vu32 *dmaRegs = (vu32 *)REG_ADDR_DMA3;      \
        dmaRegs[0] = (u32)(src);                    \
        dmaRegs[1] = (u32)(dst);                    \
        dmaRegs[2] = (u32)(control);                \
        dmaRegs[2];                                 \
    }

#define DmaFill16(value, dst, control)              \
    {                                               \
        vu16 tmp = (vu16)(value);                   \
        DmaSet(&tmp, dst, control);                 \
    }

#define DmaFill32(value, dst, control)              \
    {                                               \
        vu32 tmp = (vu32)(value);                   \
        DmaSet(&tmp, dst, control);                 \
    }

#define DmaWait()                                   \
    {                                               \
        vu32 *dmaRegs = (vu32 *)REG_ADDR_DMA3;      \
        while (dmaRegs[2] & 0x80000000)             \
            ;                                       \
    }

struct Vec3 {
    s16 x;
    s16 y;
    s16 z;
};

struct Point {
    s16 x;
    s16 y;
};

/* BIOS calls */
void VBlankIntrWait(void);
void RegisterRamReset(u32 flags);
void CpuFastSet(const void *src, void *dst, u32 control);
void LZ77UnCompWram(const void *src, void *dst);
void LZ77UnCompVram(const void *src, void *dst);
u32 Sqrt(u32 num);
s16 ArcTan2(s16 x, s16 y);
void SoundBiasReset(void);
void SoundBiasSet(void);

/* libc */
void *memcpy(void *dst, const void *src, unsigned long n);
int vsprintf(char *buf, const char *fmt, va_list ap);

/* crt0 / joy_reset */
extern u8 start_vector[];
void intr_main(void);
void JoyBus_HardReset(void);

/* Scratch buffer for decompressing data before DMA to VRAM */
extern u8 gDecompBuffer[];

void AssertFailed(const char *file, s32 line);

#endif

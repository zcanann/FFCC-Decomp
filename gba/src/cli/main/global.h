#ifndef GUARD_GLOBAL_H
#define GUARD_GLOBAL_H

#include "gba_types.h"
#include <stddef.h>

#define ARRAY_COUNT(array) (sizeof(array) / sizeof((array)[0]))
#define ABS(x) ((x) < 0 ? -(x) : (x))

#define REG_DISPCNT   (*(vu16 *)0x04000000)
#define REG_DISPSTAT  (*(vu16 *)0x04000004)
#define REG_BG0CNT    (*(vu16 *)0x04000008)
#define REG_BG1CNT    (*(vu16 *)0x0400000A)
#define REG_BG2CNT    (*(vu16 *)0x0400000C)
#define REG_BG3CNT    (*(vu16 *)0x0400000E)
#define REG_WINOUT    (*(vu16 *)0x0400004A)
#define REG_BLDCNT    (*(vu16 *)0x04000050)
#define REG_BLDALPHA  (*(vu16 *)0x04000052)
#define REG_KEYINPUT  (*(vu16 *)0x04000130)
#define REG_RCNT      (*(vu16 *)0x04000134)
#define REG_JOYCNT    (*(vu16 *)0x04000140)
#define REG_JOY_RECV  (*(vu32 *)0x04000150)
#define REG_JOY_TRANS (*(vu32 *)0x04000154)
#define REG_JOYSTAT   (*(vu16 *)0x04000158)
#define REG_IE        (*(vu16 *)0x04000200)
#define REG_IF        (*(vu16 *)0x04000202)
#define REG_WAITCNT   (*(vu16 *)0x04000204)
#define REG_IME       (*(vu16 *)0x04000208)

#define REG_ADDR_DMA0 0x040000B0
#define REG_ADDR_DMA3 0x040000D4

#define INTR_CHECK  (*(vu16 *)0x03007FF8)
#define INTR_VECTOR (*(void **)0x03007FFC)

#define KEY_MASK      0x3FF
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
#define DPAD_ANY      (DPAD_RIGHT | DPAD_LEFT | DPAD_UP | DPAD_DOWN)

/* DMA helpers in the style of the AGB SDK; dmaNo is 0 or 3 */
#define DmaSet(dmaNo, src, dst, control)                  \
    {                                                     \
        vu32 *dmaRegs = (vu32 *)REG_ADDR_DMA##dmaNo;      \
        dmaRegs[0] = (u32)(src);                          \
        dmaRegs[1] = (u32)(dst);                          \
        dmaRegs[2] = (u32)(control);                      \
        dmaRegs[2];                                       \
    }

#define DmaCopy16(dmaNo, src, dst, size) DmaSet(dmaNo, src, dst, 0x80000000 | ((size) / (16 / 8)))
#define DmaCopy32(dmaNo, src, dst, size) DmaSet(dmaNo, src, dst, 0x84000000 | ((size) / 4))

#define DmaClear16(dmaNo, value, dst, size)                         \
    {                                                               \
        vu16 tmp = (vu16)(value);                                   \
        DmaSet(dmaNo, &tmp, dst, 0x81000000 | ((size) / 2));        \
    }

#define DmaClear32(dmaNo, value, dst, size)                         \
    {                                                               \
        vu32 tmp = (vu32)(value);                                   \
        DmaSet(dmaNo, &tmp, dst, 0x85000000 | ((size) / 4));        \
    }

#define CpuFastCopy(src, dst, size) CpuFastSet(src, dst, ((size) / 4) & 0x1FFFFF)
#define CpuFastClear(value, dst, size)                                          \
    {                                                                           \
        vu32 tmp = (vu32)(value);                                               \
        CpuFastSet((void *)&tmp, dst, 0x01000000 | (((size) / 4) & 0x1FFFFF));  \
    }

/* BIOS calls */
void VBlankIntrWait(void);
void CpuFastSet(const void *src, void *dst, u32 control);
void LZ77UnCompWram(const void *src, void *dst);
void LZ77UnCompVram(const void *src, void *dst);

/* libc */
void *memcpy(void *dst, const void *src, size_t n);
int memcmp(const void *a, const void *b, size_t n);
char *strstr(const char *str, const char *substr);
void *memset(void *dst, int c, size_t n);
char *strcat(char *dst, const char *src);
char *strchr(const char *s, int c);
char *strcpy(char *dst, const char *src);
size_t strlen(const char *s);

/* m4a */
void m4aSoundInit(void);
void m4aSoundMain(void);
void m4aSoundVSync(void);
void m4aSongNumStart(u16 n);
void m4aMPlayAllStop(void);

/* crt0 / joy_reset */
void intr_main(void);
void JoyBus_HardReset(void);

#endif

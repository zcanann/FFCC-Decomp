#include <dolphin/exi.h>
#include "dolphin/os.h"
#include <dolphin/hw_regs.h>

typedef void (*MTRCallbackType)(int);

static MTRCallbackType MTRCallback;

static void (*DBGCallback)(s16);

static u32 SendMailData;

static s32 RecvDataLeng;

static u8* pEXIInputFlag;

static u8 EXIInputFlag;

static u8 SendCount = 0x80;

#define IS_TRUE(x) ((x) != FALSE)
#define IS_FALSE(x) !IS_TRUE(x)
#define ROUND_UP(x, align) (((x) + (align)-1) & (-(align)))

void DBGEXIInit() {
    __OSMaskInterrupts(0x18000);
    __EXIRegs[10] = 0;
}

static u32 DBGEXISelect(u32 v) {
    u32 regs = __EXIRegs[10];
    regs &= 0x405;
    regs |= 0x80 | (v << 4);
    __EXIRegs[10] = regs;
    return TRUE;
}

BOOL DBGEXIDeselect(void) {
    __EXIRegs[10] &= 0x405;
    return TRUE;
}

static BOOL DBGEXISync() {
    while (__EXIRegs[13] & 1)
        ;

    return TRUE;
}

static BOOL DBGEXIImm(void* buffer, s32 bytecounter, u32 write) {
    s32 i;
    s32 rem;
    u32 value;
    u8* p;
    u32 chunkCount;

    if (write != 0) {
        i = 0;
        value = 0;
        if (0 < bytecounter) {
            if ((8 < bytecounter) && (chunkCount = ((u32)bytecounter - 1) >> 3, p = buffer, 0 < bytecounter - 8)) {
                do {
                    value |= (u32)p[0] << ((3 - i) * 8);
                    value |= (u32)p[1] << ((3 - (i + 1)) * 8);
                    value |= (u32)p[2] << ((3 - (i + 2)) * 8);
                    value |= (u32)p[3] << ((3 - (i + 3)) * 8);
                    value |= (u32)p[4] << ((3 - (i + 4)) * 8);
                    value |= (u32)p[5] << ((3 - (i + 5)) * 8);
                    value |= (u32)p[6] << ((3 - (i + 6)) * 8);
                    value |= (u32)p[7] << ((3 - (i + 7)) * 8);
                    p += 8;
                    i += 8;
                    chunkCount--;
                } while (chunkCount != 0);
            }

            p = (u8*)buffer + i;
            rem = bytecounter - i;
            if (i < bytecounter) {
                do {
                    value |= (u32)(*p) << ((3 - i) * 8);
                    p++;
                    i++;
                    rem--;
                } while (rem != 0);
            }
        }
        __EXIRegs[14] = value;
    }

    __EXIRegs[13] = (write << 2) | 1U | ((bytecounter - 1) << 4);
    do {
        value = __EXIRegs[13];
    } while (value & 1);

    if (write == 0) {
        i = 0;
        value = __EXIRegs[14];
        if (0 < bytecounter) {
            if ((8 < bytecounter) && (chunkCount = ((u32)bytecounter - 1) >> 3, 0 < bytecounter - 8)) {
                do {
                    ((u8*)buffer)[0] = (u8)(value >> ((3 - i) * 8));
                    ((u8*)buffer)[1] = (u8)(value >> ((3 - (i + 1)) * 8));
                    ((u8*)buffer)[2] = (u8)(value >> ((3 - (i + 2)) * 8));
                    ((u8*)buffer)[3] = (u8)(value >> ((3 - (i + 3)) * 8));
                    ((u8*)buffer)[4] = (u8)(value >> ((3 - (i + 4)) * 8));
                    ((u8*)buffer)[5] = (u8)(value >> ((3 - (i + 5)) * 8));
                    ((u8*)buffer)[6] = (u8)(value >> ((3 - (i + 6)) * 8));
                    ((u8*)buffer)[7] = (u8)(value >> ((3 - (i + 7)) * 8));
                    buffer = (u8*)buffer + 8;
                    i += 8;
                    chunkCount--;
                } while (chunkCount != 0);
            }

            rem = bytecounter - i;
            if (i < bytecounter) {
                do {
                    *(u8*)buffer = (u8)(value >> ((3 - i) * 8));
                    buffer = (u8*)buffer + 1;
                    i++;
                    rem--;
                } while (rem != 0);
            }
        }
    }

    return TRUE;
}

static BOOL DBGWriteMailbox(u32 p1) {
    u32 cmd = 0xc0000000;
    u32 v;
    u32 base = p1;
    BOOL total = FALSE;

    DBGEXISelect(4);
    v = (base & 0x1fffffff) | (cmd);
    total |= IS_FALSE(DBGEXIImm(&v, sizeof(v), 1));
    total |= IS_FALSE(DBGEXISync());
    total |= IS_FALSE(DBGEXIDeselect());

    return IS_FALSE(total);
}

#pragma dont_inline on
static BOOL DBGReadMailbox(u32* p1) {
    BOOL total = FALSE;
    u32 v;

    DBGEXISelect(4);

    v = 0x60000000;
    total |= IS_FALSE(DBGEXIImm(&v, 2, 1));
    total |= IS_FALSE(DBGEXISync());

    total |= IS_FALSE(DBGEXIImm(p1, 4, 0));
    total |= IS_FALSE(DBGEXISync());

    total |= IS_FALSE(DBGEXIDeselect());

    return IS_FALSE(total);
}
#pragma dont_inline reset

static BOOL DBGRead(u32 count, u32* buffer, s32 param3) {
    u32 busyFlag;
    u32 regs;
    u32 result;
    u32 value;

    value = ((count & 0x1fffc) << 8) | 0x20000000;
    regs = __EXIRegs[10];
    __EXIRegs[10] = (regs & 0x405) | 0xc0;

    result = ((u32)__cntlzw(DBGEXIImm(&value, 4, TRUE))) >> 5;
    do {
        busyFlag = __EXIRegs[13];
    } while (busyFlag & 1);

    while (param3 != 0) {
        result |= ((u32)__cntlzw(DBGEXIImm(&value, 4, FALSE))) >> 5;
        do {
            busyFlag = __EXIRegs[13];
        } while (busyFlag & 1);

        param3 -= 4;
        *buffer++ = value;
        if (param3 < 0) {
            param3 = 0;
        }
    }

    regs = __EXIRegs[10];
    __EXIRegs[10] = regs & 0x405;
    return ((u32)__cntlzw(result)) >> 5;
}

static BOOL DBGWrite(u32 count, void* buffer, s32 param3) {
    u32 busyFlag;
    u32 regs;
    u32 result;
    u32* data;
    u32 value;

    value = ((count & 0x1fffc) << 8) | 0xa0000000;
    regs = __EXIRegs[10];
    __EXIRegs[10] = (regs & 0x405) | 0xc0;

    result = ((u32)__cntlzw(DBGEXIImm(&value, 4, TRUE))) >> 5;
    do {
        busyFlag = __EXIRegs[13];
    } while (busyFlag & 1);

    data = (u32*)buffer;
    while (param3 != 0) {
        value = *data++;
        result |= ((u32)__cntlzw(DBGEXIImm(&value, 4, TRUE))) >> 5;
        do {
            busyFlag = __EXIRegs[13];
        } while (busyFlag & 1);

        param3 -= 4;
        if (param3 < 0) {
            param3 = 0;
        }
    }

    regs = __EXIRegs[10];
    __EXIRegs[10] = regs & 0x405;
    return ((u32)__cntlzw(result)) >> 5;
}

inline static BOOL _DBGReadStatus(u32* p1) {
    BOOL total = FALSE;
    u32 v;

    DBGEXISelect(4);

    v = 1 << 30;
    total |= IS_FALSE(DBGEXIImm(&v, 2, 1));
    total |= IS_FALSE(DBGEXISync());

    total |= IS_FALSE(DBGEXIImm(p1, 4, 0));
    total |= IS_FALSE(DBGEXISync());

    total |= IS_FALSE(DBGEXIDeselect());

    return IS_FALSE(total);
}
#pragma dont_inline on
static BOOL DBGReadStatus(u32* p1) {
    return _DBGReadStatus(p1);
}
#pragma dont_inline reset

static void MWCallback(s16 a) {
    EXIInputFlag = TRUE;
    if (MTRCallback) {
        MTRCallback(0);
    }
}

static void DBGHandler(s16 a, OSContext* b) {
    *__PIRegs = 0x1000;
    if (DBGCallback) {
        DBGCallback(a);
    }
}

void DBInitComm(u8** a, MTRCallbackType b) {
    BOOL interrupts = OSDisableInterrupts();
    pEXIInputFlag = &EXIInputFlag;
    *a = pEXIInputFlag;
    MTRCallback = b;
    DBGEXIInit();
    OSRestoreInterrupts(interrupts);
}

void DBInitInterrupts(void) {
    __OSMaskInterrupts(0x18000);
    __OSMaskInterrupts(0x40);
    DBGCallback = &MWCallback;
    __OSSetInterruptHandler(0x19, DBGHandler);
    __OSUnmaskInterrupts(0x40);
}

static void CheckMailBox(void) {
    u32 v;
    DBGReadStatus(&v);
    if (v & 1) {
        DBGReadMailbox(&v);
        v &= 0x1fffffff;

        if ((v & 0x1f000000) == 0x1f000000) {
            SendMailData = v;
            RecvDataLeng = v & 0x7fff;
            EXIInputFlag = 1;
        }
    }
}

u32 DBQueryData(void) {
    EXIInputFlag = 0;
    if (!RecvDataLeng) {
        BOOL interrupts = OSDisableInterrupts();
        CheckMailBox();
        OSRestoreInterrupts(interrupts);
    }
    return RecvDataLeng;
}

BOOL DBRead(u32* buffer, s32 count) {
    u32 interrupts = OSDisableInterrupts();
    u32 v;

    if ((SendMailData & 0x10000) == 0) {
        v = 0;
    } else {
        v = 0x1000;
    }

    DBGRead(v + 0x1e000, buffer, (count + 3U) & ~3U);

    RecvDataLeng = 0;
    EXIInputFlag = 0;

    OSRestoreInterrupts(interrupts);

    return 0;
}

BOOL DBWrite(void* src, u32 size) {
    u32 v;
    u32 busyFlag;
    BOOL interrupts = OSDisableInterrupts();

    do {
        _DBGReadStatus(&busyFlag);
    } while (busyFlag & 2);

    SendCount++;
    v = ((SendCount & 1) ? 0x1000 : 0);

    while (!DBGWrite(v | 0x1c000, src, ROUND_UP(size, 4)))
        ;

    do {
        _DBGReadStatus(&busyFlag);
    } while (busyFlag & 2);

    v = SendCount;
    while (!DBGWriteMailbox((0x1f000000) | v << 0x10 | size))
        ;

    do {
        while (!_DBGReadStatus(&busyFlag))
            ;
    } while (busyFlag & 2);

    OSRestoreInterrupts(interrupts);

    return 0;
}

void DBOpen(void) {}

void DBClose(void) {}

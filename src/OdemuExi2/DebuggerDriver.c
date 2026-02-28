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

/*
 * --INFO--
 * PAL Address: 0x801bcc74
 * PAL Size: 664b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static BOOL DBGEXIImm(u8* buffer, s32 bytecounter, s32 write) {
    s32 i;
    u32 value;
    u8* ptr;

    if (write != 0) {
        i = 0;
        value = 0U;
        ptr = buffer;
        while (i < bytecounter) {
            value |= (u32)*ptr++ << ((3 - i) * 8);
            i++;
        }
        __EXIRegs[14] = value;
    }

    __EXIRegs[13] = (write << 2) | 1U | ((bytecounter - 1) << 4);
    do {
        value = __EXIRegs[13];
    } while (value & 1);

    if (write == 0) {
        i = 0;
        ptr = buffer;
        value = __EXIRegs[14];
        while (i < bytecounter) {
            *ptr++ = (u8)(value >> ((3 - i) * 8));
            i++;
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
    total |= IS_FALSE(DBGEXIImm((u8*)&v, sizeof(v), 1));
    total |= IS_FALSE(DBGEXISync());
    total |= IS_FALSE(DBGEXIDeselect());

    return IS_FALSE(total);
}

#pragma dont_inline on
static BOOL DBGReadMailbox(u32* p1) {
    u32 busyFlag;
    u32 regs;
    u32 result;
    u32 cmd;

    regs = __EXIRegs[10];
    __EXIRegs[10] = (regs & 0x405) | 0xc0;

    cmd = 0x60000000;
    result = ((u32)__cntlzw(DBGEXIImm((u8*)&cmd, 2, TRUE))) >> 5;
    do {
        busyFlag = __EXIRegs[13];
    } while (busyFlag & 1);

    result |= ((u32)__cntlzw(DBGEXIImm((u8*)p1, 4, FALSE))) >> 5;
    do {
        busyFlag = __EXIRegs[13];
    } while (busyFlag & 1);

    regs = __EXIRegs[10];
    __EXIRegs[10] = regs & 0x405;
    return ((u32)__cntlzw(result)) >> 5;
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

    result = ((u32)__cntlzw(DBGEXIImm((u8*)&value, 4, TRUE))) >> 5;
    do {
        busyFlag = __EXIRegs[13];
    } while (busyFlag & 1);

    while (param3 != 0) {
        result |= ((u32)__cntlzw(DBGEXIImm((u8*)&value, 4, FALSE))) >> 5;
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

/*
 * --INFO--
 * PAL Address: 0x801bca10
 * PAL Size: 220b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static BOOL DBGWrite(u32 count, u32* buffer, s32 param3) {
    u32 regs;
    u32 result;
    u32 cmd;
    u32 word;

    cmd = ((count & 0x1fffc) << 8) | 0xa0000000;
    regs = __EXIRegs[10];
    __EXIRegs[10] = (regs & 0x405) | 0xc0;

    result = ((u32)__cntlzw(DBGEXIImm((u8*)&cmd, 4, TRUE))) >> 5;
    while (__EXIRegs[13] & 1)
        ;

    while (param3 != 0) {
        word = *buffer++;
        result |= (u32)__cntlzw(DBGEXIImm((u8*)&word, 4, TRUE)) >> 5;
        while (__EXIRegs[13] & 1)
            ;

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
    u32 busyFlag;
    u32 regs;
    u32 result;
    u32 cmd;

    regs = __EXIRegs[10];
    __EXIRegs[10] = (regs & 0x405) | 0xc0;

    cmd = 0x40000000;
    result = ((u32)__cntlzw(DBGEXIImm((u8*)&cmd, 2, TRUE))) >> 5;
    do {
        busyFlag = __EXIRegs[13];
    } while (busyFlag & 1);

    result |= ((u32)__cntlzw(DBGEXIImm((u8*)p1, 4, FALSE))) >> 5;
    do {
        busyFlag = __EXIRegs[13];
    } while (busyFlag & 1);

    regs = __EXIRegs[10];
    __EXIRegs[10] = regs & 0x405;
    return ((u32)__cntlzw(result)) >> 5;
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

u32 DBQueryData(void) {
    u32 value;
    u32 interrupts;
    u32 mailbox[3];

    EXIInputFlag = 0;
    if (RecvDataLeng == 0) {
        interrupts = OSDisableInterrupts();
        DBGReadStatus(mailbox);
        value = mailbox[0];
        if ((mailbox[0] & 1) != 0) {
            DBGReadMailbox(mailbox);
            value = mailbox[0] & 0x1fffffff;
            if ((mailbox[0] & 0x1f000000) == 0x1f000000) {
                RecvDataLeng = mailbox[0] & 0x7fff;
                EXIInputFlag = 1;
                SendMailData = value;
            }
        }
        mailbox[0] = value;
        OSRestoreInterrupts(interrupts);
    }
    return RecvDataLeng;
}

BOOL DBRead(u32* buffer, s32 count) {
    BOOL interrupts;
    s32 value;

    interrupts = OSDisableInterrupts();

    if ((SendMailData & 0x10000) == 0) {
        value = 0;
    } else {
        value = 0x1000;
    }

    DBGRead(value + 0x1e000, buffer, (count + 3U) & 0xfffffffc);

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

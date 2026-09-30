#include "gba_types.h"

typedef char *va_list;
#define va_start(ap, last) ((ap) = (va_list)__builtin_next_arg(last))
#define va_end(ap)

#define REG_DISPCNT (*(vu16 *)0x04000000)
#define REG_KEYINPUT (*(vu16 *)0x04000130)
#define REG_IME (*(vu16 *)0x04000208)
#define REG_DISPSTAT (*(vu16 *)0x04000004)
#define REG_WAITCNT (*(vu16 *)0x04000204)
#define INTR_VECTOR (*(void **)0x03007FFC)
#define REG_KEYCNT (*(vu16 *)0x04000132)
#define REG_IE (*(vu16 *)0x04000200)
#define REG_VCOUNT_SET (*(vu8 *)0x04000005)
#define REG_VCOUNT (*(vu8 *)0x04000006)
#define REG_BG1HOFS (*(vu16 *)0x04000014)
#define REG_DMA0CNT_H (*(vu16 *)0x040000BA)
#define INTR_CHECK (*(vu16 *)0x03007FF8)

#define DmaCopy32(src, dst, cnt) \
    { \
        vu32 *dmaRegs = (vu32 *)0x040000D4; \
        dmaRegs[0] = (u32)(src); \
        dmaRegs[1] = (u32)(dst); \
        dmaRegs[2] = (u32)(cnt); \
        dmaRegs[2]; \
    }

struct Work {
    u16 unk0;
    u16 unk2;
    u8 unk4;
    u8 unk5;
    s8 unk6;
    u8 unk7;
    u8 unk8;
    s8 unk9;
    s8 unkA;
    s8 unkB;
    u8 unkC[0x14 - 0xC];
    s8 unk14;
    s8 unk15;
    u8 unk16;
    u8 unk17;
    u8 unk18;
    u8 unk19;
    u16 unk1A;
    u32 unk1C;
    u32 unk20;
    u32 unk24;
    u32 unk28;
    u32 unk2C;
    union {
        s8 b[4];
        u8 ub[4];
        s32 w;
    } unk30;
    u8 unk34;
    u8 unk35;
    u8 unk36;
    u8 unk37;
    vu8 unk38;
    vu8 unk39;
    vu8 unk3A;
    vu8 unk3B;
    vu16 unk3C;
    u16 unk3E;
    vu8 unk40;
    vu8 unk41;
};

struct Point {
    s16 x;
    s16 y;
};

struct Unk02010248 {
    u8 unk0[0x10];
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
};

struct Unk0202C669 {
    s8 unk0;
    u8 unk1[0x58 - 0x1];
};

struct Unk0202C66D {
    u8 unk0;
    u8 unk1[0x58 - 0x1];
};

struct Unk030060F8 {
    u8 unk0[0x4A];
    u8 unk4A;
};

struct Unk0202C618 {
    u8 unk0[0xA];
    u8 unkA;
    u8 unkB[0x58 - 0xB];
};

extern vu32 lbl_03005248;
extern struct Work lbl_03000000;
extern u8 lbl_03005D61;
extern u8 lbl_03005D63;
extern u8 lbl_03005D64;
extern s32 lbl_0300524C;
extern struct Unk0202C669 lbl_0202C669[];
extern struct Unk0202C66D lbl_0202C66D[];
extern const char lbl_0200ECF4[];
extern const u8 lbl_020163C0[];
extern const u8 lbl_02016540[];
extern struct Unk02010248 lbl_02010248[];
extern u8 lbl_03006144[];
extern u8 lbl_03004248[];
extern u8 lbl_03005258[];
extern vu16 lbl_03005254;
extern vu16 lbl_03005256;
extern vu8 lbl_03005C5C;
extern u8 lbl_03000248[];
extern u8 lbl_03004C48[];
extern u8 lbl_0202BB94[];
extern u8 lbl_03000048[];
extern u32 lbl_03005C68;
extern u32 lbl_03005C6C;
extern struct Unk030060F8 lbl_030060F8;
extern u8 lbl_030063C8[];
extern u8 lbl_030063E0[];
extern struct Unk0202C618 lbl_0202C618[];
extern u8 lbl_030063F8[];
extern u8 lbl_0201DDCC[];
extern u8 lbl_02030000[];
extern s32 lbl_03005250;
extern vu8 lbl_03005D65;
extern vu8 lbl_03005D66;
extern vu8 lbl_03005D67;
extern volatile s8 lbl_03005C5D;
extern u8 lbl_03005C5E;
extern u32 lbl_03005C60;
extern u32 lbl_03005C64;
extern const u8 lbl_0201C2F9;
extern const u8 lbl_0201C2FA;
extern u8 lbl_020157D0[];
extern vu8 lbl_03005D60;
extern vu16 lbl_03005D58[4];
extern u16 lbl_03005D76;
extern u8 lbl_02015850[];
extern const char lbl_0200ED68[];
extern u8 lbl_030060F4;
extern u8 lbl_030060F5;
extern const char lbl_0200ED00[];
extern const char lbl_0200ED18[];
extern const char lbl_0200ED2C[];
extern const char lbl_0200ED44[];
extern const char lbl_0200ED48[];
extern const char lbl_0200ED4C[];
extern const char lbl_0200ED50[];
extern const char lbl_0200ED54[];
extern const char lbl_0200ED58[];
extern const char lbl_0200ED5C[];
extern const char lbl_0200ED60[];
extern const char lbl_0200ED64[];

void VBlankIntrWait(void);
void m4aSoundMain(void);
void m4aSoundVSync(void);
void m4aSoundInit(void);
void m4aSoundVSyncOff(void);
void m4aSoundVSyncOn(void);
void RegisterRamReset(u32);
void LZ77UnCompWram(const void *, void *);
void fn_020012AC(struct Work *, u8);
void fn_0200731C(u32);
void fn_02006F0C(void *);
void fn_02002070(void);
void fn_02005D28(void *);
void fn_02006B30(void *);
void fn_02006ED0(void *);
void fn_02006268(void *);
void fn_02003E94(void *);
void fn_020072E4(void *);
void intr_main(void);
int vsprintf(char *, const char *, va_list);
void fn_02001BA8(void);
void m4aSongNumStart(u16);
void m4aSongNumStop(u16);
void m4aMPlayFadeOut(void *, u16);
void fn_02003E28(void *);
void fn_02004E54(void *, u8, u8);
void fn_02004E8C(void *, s32);
s16 *fn_02006EFC(void *, u32);
void fn_020054CC(void *, u32, s32);
void fn_020071E4(void *);
void fn_020071C8(void *);
void fn_020072AC(void *, u8);
void fn_020072D4(void *);
void fn_0200726C(void *);
void fn_02007238(void *);
void m4aMPlayFadeOutTemporarily(void *, u16);
void m4aMPlayFadeIn(void *, u16);
void SoundBiasReset(void);
void SoundBiasSet(void);
void fn_02001540(struct Work *);
void fn_02001774(struct Work *);
void fn_020010FC(struct Work *);
void fn_02006FC0(void *, s32);
void fn_02006FF8(void *, s32, s32, s32, s32);
void fn_02007088(void *, s32, s32, s32);
void fn_02006374(void *);
void fn_020062F8(void *);
u8 fn_02004E20(void *, u8);
u32 fn_02004E38(void *, u8, u8);
void fn_02007184(void *, const void *);
void fn_020072E8(void *);
void fn_0200455C(void *);
void fn_02005D5C(void *);
void fn_02004930(void *, s16, struct Point *, s16);
void fn_0200468C(void *);
void fn_020045DC(void *);
void fn_020046E8(void *);
void fn_02004DD0(void *, u8, u8, u32);
void fn_02001934(struct Work *);
void fn_020019A0(struct Point *, u8);
void fn_02001518(struct Work *);
void fn_020015F8(struct Work *);
void fn_02007148();
void fn_020070F8();
u32 fn_020044F4(void *, u8);
void fn_0200652C(void *);
void fn_02006794(void *);
void fn_020019C8(struct Work *);
void fn_020005E0(struct Work *);
void fn_020007F4(struct Work *);
void fn_02002270(void);
void fn_020025B0(void);
void fn_0200720C(void *);
void fn_0200027C(void);

void fn_0200022C(u32 frames)
{
    u32 end = lbl_03005248 + frames;

    while (lbl_03005248 < end) {
        VBlankIntrWait();
        fn_0200027C();
    }
}

static inline void SetPlayerNo(struct Unk030060F8 *p, u8 no)
{
    p->unk4A = no;
}

void fn_02000254(const char *fmt, ...)
{
    char buf[512];
    va_list ap;

    va_start(ap, fmt);
    vsprintf(buf, fmt, ap);
    va_end(ap);
}

void fn_0200027C(void)
{
    m4aSoundMain();
}

void AgbMain(void)
{
    struct Work *work;
    u16 keys;

    lbl_03005248 = 0;
    REG_IME = 0;
    fn_020005E0(&lbl_03000000);
    work = &lbl_03000000;
    for (;;) {
        fn_02001BA8();
        keys = REG_KEYINPUT ^ 0x3FF;
        work->unk2 = keys & ~work->unk0;
        work->unk0 = keys;
        if (lbl_03005D61 != 0 && (u8)(work->unk4 - 2) <= 3) {
            fn_0200652C(lbl_03006144);
            fn_02006794(lbl_03006144);
        }
        fn_020019C8(work);
        fn_0200027C();
        fn_020007F4(work);
        while (lbl_03005248 == 0) {
            VBlankIntrWait();
        }
        fn_0200027C();
        fn_02002270();
        fn_020025B0();
        VBlankIntrWait();
        lbl_03005248 = 0;
        if (lbl_03000000.unk40) {
            DmaCopy32(lbl_03004248, lbl_03005258, 0x84000280);
            DmaCopy32(lbl_03000248, 0x06008000, 0x84001000);
            lbl_03000000.unk40 = 0;
        }
        if (lbl_03000000.unk41) {
            lbl_03000000.unk41 = 0;
            DmaCopy32(lbl_03004C48, 0x07000000, 0x84000100);
        }
        fn_0200720C(lbl_0202BB94);
        if (lbl_03000000.unk38) {
            lbl_03000000.unk3C = lbl_03000000.unk3E;
        } else {
            lbl_03000000.unk3C = 0x1000;
        }
        if (work->unk3A) {
            REG_DISPCNT |= 0x100;
        } else {
            REG_DISPCNT &= ~0x100;
        }
        if (lbl_03000000.unk3B) {
            REG_DISPCNT |= 0x1000;
        } else {
            REG_DISPCNT &= ~0x1000;
        }
    }
}

void fn_02000424(void)
{
    REG_IE &= ~0x4;
    REG_DISPCNT &= ~0x400;
    m4aSoundVSync();
    if (lbl_03000000.unk39) {
        REG_DISPCNT |= 0x200;
        if (lbl_03005248 == 0) {
            REG_BG1HOFS = (lbl_03005256 + lbl_03005254) >> 1;
        } else {
            REG_BG1HOFS = lbl_03005256;
            lbl_03005254 = lbl_03005256;
        }
    } else {
        REG_DISPCNT &= ~0x200;
    }
    lbl_03005248++;
    if (lbl_03000000.unk38) {
        REG_IE |= 0x4;
    }
    INTR_CHECK = 1;
}

void fn_020004F4(void)
{
    u8 line;

    switch (lbl_03005C5C) {
    case 0:
        REG_DMA0CNT_H = 0;
        line = REG_VCOUNT;
        {
            vu32 *dmaRegs = (vu32 *)0x040000B0;
            dmaRegs[0] = (u32)&lbl_03005258[line * 16];
            dmaRegs[1] = 0x04000020;
            dmaRegs[2] = 0xA6600004;
        }
        if (line < lbl_03000000.unk3C) {
            lbl_03005C5C = 1;
            REG_VCOUNT_SET = lbl_03000000.unk3C;
            break;
        }
    case 1:
        if (lbl_03000000.unk38) {
            REG_DISPCNT |= 0x400;
        }
        lbl_03005C5C = 2;
        REG_VCOUNT_SET = REG_VCOUNT + 6;
        break;
    case 2:
        REG_DISPCNT &= ~0x200;
        lbl_03005C5C = 0;
        REG_VCOUNT_SET = 0;
        lbl_03005C5C = 3;
        REG_VCOUNT_SET = 158;
        break;
    case 3:
        REG_DMA0CNT_H = 0;
        lbl_03005C5C = 0;
        REG_VCOUNT_SET = 0;
        break;
    }
}

void fn_020005DC(void)
{
}

void fn_020005E0(struct Work *work)
{
    vu32 fill;
    vu32 *dma;

    RegisterRamReset(0xC2);
    fill = 0;
    dma = (vu32 *)0x040000D4;
    dma[0] = (u32)&fill;
    dma[1] = 0x03000000;
    dma[2] = 0x85001F80;
    dma[2];
    REG_WAITCNT = 0x4014;
    fill = 0;
    dma[0] = (u32)&fill;
    dma[1] = 0x06000000;
    dma[2] = 0x85006000;
    dma[2];
    fill = 0xA0;
    dma[0] = (u32)&fill;
    dma[1] = 0x07000000;
    dma[2] = 0x85000100;
    dma[2];
    fill = 0;
    dma[0] = (u32)&fill;
    dma[1] = 0x05000000;
    dma[2] = 0x85000100;
    dma[2];
    dma[0] = (u32)intr_main;
    dma[1] = (u32)lbl_03000048;
    dma[2] = 0x84000080;
    dma[2];
    INTR_VECTOR = lbl_03000048;
    fill = 0xA0;
    dma[0] = (u32)&fill;
    dma[1] = (u32)lbl_03004C48;
    dma[2] = 0x85000100;
    dma[2];
    *(vu16 *)0x04000010 = 0;
    *(vu16 *)0x04000012 = 0;
    *(vu16 *)0x04000014 = 0;
    *(vu16 *)0x04000016 = 0;
    *(vu16 *)0x04000020 = 0x100;
    *(vu16 *)0x04000022 = 0;
    *(vu16 *)0x04000024 = 0;
    *(vu16 *)0x04000026 = 0x100;
    *(vu16 *)0x04000028 = 0;
    *(vu16 *)0x0400002A = 0;
    *(vu16 *)0x0400002C = 0;
    *(vu16 *)0x0400002E = 0;
    *(vu16 *)0x0400004C = 0;
    *(vu16 *)0x04000050 = 0x1044;
    *(vu16 *)0x04000052 = 0xF08;
    m4aSoundInit();
    m4aSoundVSyncOff();
    REG_DISPCNT = 0x1001;
    fn_020012AC(work, 0);
    lbl_03005C5C = 0xFF;
    work->unk5 = 0;
    work->unk38 = work->unk39 = work->unk3A = work->unk3B = 0;
    lbl_03005C68 = 0;
    lbl_03005C6C = 0;
    while (dma[2] & 0x80000000)
        ;
    fn_0200731C(10000);
    fn_02006F0C(lbl_0202BB94);
    fn_02002070();
    fn_02005D28(&lbl_030060F8);
    fn_02006B30(lbl_030063C8);
    fn_02006ED0(lbl_030063E0);
    fn_02006268(lbl_03006144);
    fn_02003E94(lbl_0202C618);
    fn_02006F0C(lbl_0202BB94);
    fn_020072E4(lbl_030063F8);
    LZ77UnCompWram(lbl_0201DDCC, lbl_02030000);
    REG_IE = 0x2085;
    REG_DISPSTAT = 0x28;
    REG_IME = 1;
    m4aSoundVSyncOn();
}

void fn_020007F4(struct Work *work)
{
    s32 i;
    s8 rank;
    u8 ready;
    u8 buf[16];

    lbl_0300524C++;
    lbl_03005250++;
    fn_02001774(work);
    switch (work->unk4) {
    case 0:
        if (work->unk2C == 0) {
            fn_02006FC0(lbl_0202BB94, 15);
            fn_02007148(lbl_0202BB94, 10, 9, lbl_0200ECF4);
            work->unk3A = 1;
        }
        work->unk2C++;
        if (lbl_03005D60) {
            ready = lbl_03005D63;
        } else {
            ready = work->unk2C > 29;
        }
        if (!ready) {
            return;
        }
        fn_0200731C(10000);
        SetPlayerNo(&lbl_030060F8, lbl_03005D65);
        fn_020012AC(work, 1);
        break;
    case 1:
        if (work->unk5) {
            break;
        }
        work->unk34 &= lbl_03005D67;
        if (work->unk34 == lbl_03005D67) {
            fn_020012AC(work, 2);
            break;
        }
        if (work->unk2C == 0) {
            work->unk38 = 0;
            work->unk39 = 1;
            work->unk3B = 1;
            fn_02006374(lbl_03006144);
        }
        if (work->unk2C > 15) {
            s32 j;

            for (j = 0; j <= 3; j++) {
                if ((work->unk34 >> j) & 1) {
                    continue;
                }
                if (lbl_03005D58[j] & 0x80) {
                    if (++work->unk30.b[j] > 3) {
                        work->unk30.b[j] = 0;
                    }
                    if (j == lbl_03005D65) {
                        m4aSongNumStart(0);
                    }
                }
                if (lbl_03005D58[j] & 0x40) {
                    if (--work->unk30.b[j] < 0) {
                        work->unk30.b[j] = 3;
                    }
                    if (j == lbl_03005D65) {
                        m4aSongNumStart(0);
                    }
                }
                if (lbl_03005D58[j] & 0x1) {
                    work->unk34 |= 1 << j;
                    if (j == lbl_03005D65) {
                        m4aSongNumStart(1);
                    }
                }
            }
        }
        work->unk2C++;
        break;
    case 2:
        if (work->unk5) {
            break;
        }
        if (work->unk2C == 0) {
            fn_020062F8(lbl_03006144);
            work->unk38 = 1;
            lbl_03005250 = 0;
            lbl_03005C5C = 0;
            fn_02006FC0(lbl_0202BB94, 15);
        }
        if (work->unk2C == 11) {
            m4aSongNumStart(53);
        }
        if (work->unk2C == 80) {
            fn_02006FF8(lbl_0202BB94, 13, 4, 5, 14);
            m4aSongNumStart(4);
        } else if (work->unk2C == 110) {
            fn_02006FF8(lbl_0202BB94, 13, 4, 6, 14);
            m4aSongNumStart(4);
        } else if (work->unk2C == 140) {
            fn_02006FF8(lbl_0202BB94, 13, 4, 7, 14);
            m4aSongNumStart(4);
        } else if (work->unk2C == 170) {
            fn_02006FF8(lbl_0202BB94, 11, 4, 8, 14);
            fn_020012AC(work, 3);
            m4aSongNumStart(5);
            lbl_030060F4 = 0xFF;
            goto race;
        }
        work->unk2C++;
        break;
    case 3:
    race:
        if (work->unk5) {
            break;
        }
        if (work->unk2C == 30) {
            m4aSongNumStart(50);
            if (work->unk2C == 30) {
                fn_02006FC0(lbl_0202BB94, 15);
                (lbl_0202C66D + lbl_03005D65)->unk0 &= ~0x10;
            }
        }
        if (work->unk2C > 29) {
            rank = (lbl_0202C669 + lbl_03005D65)->unk0;
            if (work->unk15 != rank) {
                if ((s8)(rank - lbl_03005C5D) > 0 && rank >= 0) {
                    if (work->unk28 > work->unk1C) {
                        work->unk28 = work->unk20 = work->unk1C;
                        work->unk1C = 0;
                    }
                    if (rank != work->unk9) {
                        work->unk1C = 0;
                    }
                    if (work->unk24 == -1) {
                        work->unk24 = 0;
                    }
                }
                work->unk15 = rank;
                fn_02006FF8(lbl_0202BB94, 21, 0, 14, 14);
                if (work->unk9 == 3) {
                    fn_02006FF8(lbl_0202BB94, 26, 0, 19, 14);
                } else {
                    fn_02006FF8(lbl_0202BB94, 26, 0, 18, 14);
                }
                work->unk17 = 1;
                lbl_03005C5D = rank;
                if (lbl_03005C5D >= work->unk9) {
                    lbl_03005C5D = work->unk9 - 1;
                }
                if (rank == work->unk9) {
                    fn_020012AC(work, 4);
                    break;
                }
                if (rank == work->unk9 - 1 && !work->unk16) {
                    work->unk16 = 1;
                    work->unk1A = 96;
                }
            }
            fn_020010FC(work);
            if (fn_02004E20(lbl_0202C618, lbl_030060F8.unk4A)) {
                if (work->unk18 == 0 && work->unk1A == 0 && !lbl_03005C5E) {
                    fn_02006FF8(lbl_0202BB94, 9, 5, 15, 14);
                    fn_02006FF8(lbl_0202BB94, 15, 5, 16, 14);
                    fn_02006FF8(lbl_0202BB94, 21, 5, 17, 14);
                    lbl_03005C5E = 1;
                }
            } else if (lbl_03005C5E) {
                fn_02007088(lbl_0202BB94, 9, 5, 15);
                fn_02007088(lbl_0202BB94, 15, 5, 16);
                fn_02007088(lbl_0202BB94, 21, 5, 17);
                lbl_03005C5E = 0;
            }
            lbl_03005C60 = fn_02004E38(lbl_0202C618, lbl_03005D65, 0);
            lbl_03005C64 = fn_02004E38(lbl_0202C618, lbl_03005D65, 4);
        }
        if (work->unk1A) {
            if ((work->unk1A & 31) == 16) {
                m4aSongNumStart(17);
                fn_02006FF8(lbl_0202BB94, 11, 4, 20, 14);
            } else if ((work->unk1A & 31) == 1) {
                fn_02007088(lbl_0202BB94, 11, 4, 20);
            }
            work->unk1A--;
        }
        if (++work->unk2C > 0xFFFFFFF0) {
            work->unk2C = 0xFFFFFFF0;
        }
        break;
    case 4:
        if (work->unk5) {
            break;
        }
        if (work->unk2C == 0) {
            lbl_03005D76 = work->unk14 | 0x1000;
            fn_02006FF8(lbl_0202BB94, 9, 4, 9, 14);
            work->unk18 = 1;
        }
        fn_020010FC(work);
        if (work->unk2C == 60) {
            fn_02007088(lbl_0202BB94, 9, 4, 9);
            work->unk18 = 0;
            switch (work->unk14) {
            case 0:
            case 1:
                fn_02006FF8(lbl_0202BB94, 13, 4, 7, 14);
                fn_02006FF8(lbl_0202BB94, 17, 6, 10, 14);
                break;
            case 2:
                fn_02006FF8(lbl_0202BB94, 13, 4, 6, 14);
                fn_02006FF8(lbl_0202BB94, 17, 6, 11, 14);
                break;
            case 3:
                fn_02006FF8(lbl_0202BB94, 13, 4, 5, 14);
                fn_02006FF8(lbl_0202BB94, 17, 6, 12, 14);
                break;
            case 4:
                fn_02006FF8(lbl_0202BB94, 14, 6, 4, 14);
                fn_02006FF8(lbl_0202BB94, 16, 6, 13, 14);
                break;
            case 5:
                fn_02006FF8(lbl_0202BB94, 14, 6, 3, 14);
                fn_02006FF8(lbl_0202BB94, 16, 6, 13, 14);
                break;
            case 6:
                fn_02006FF8(lbl_0202BB94, 14, 6, 2, 14);
                fn_02006FF8(lbl_0202BB94, 16, 6, 13, 14);
                break;
            case 7:
                fn_02006FF8(lbl_0202BB94, 14, 6, 1, 14);
                fn_02006FF8(lbl_0202BB94, 16, 6, 13, 14);
                break;
            case 8:
                fn_02006FF8(lbl_0202BB94, 14, 6, 0, 14);
                fn_02006FF8(lbl_0202BB94, 16, 6, 13, 14);
                break;
            }
        }
        work->unk2C++;
        if (work->unk30.w != -1) {
            if (work->unk30.w == 122) {
                lbl_03005D76 = 0x1100;
                fn_020012AC(work, 5);
            } else {
                work->unk30.w++;
            }
        } else if ((work->unk8 & lbl_03005D67) == lbl_03005D67) {
            work->unk30.w = 0;
        }
        break;
    case 5:
        if (work->unk2C == 0) {
        setup:
            work->unk36 = lbl_03005D60;
            if (work->unk36) {
                fn_02007184(lbl_0202BB94, lbl_020163C0);
            } else {
                fn_02007184(lbl_0202BB94, lbl_02016540);
            }
        }
        fn_020010FC(work);
        if (lbl_03005D60) {
            for (i = 0; i <= 3; i++) {
                if ((work->unk35 >> i) & 1) {
                    continue;
                }
                if (lbl_03005D58[i] & 0xC0) {
                    work->unk30.ub[i] ^= 1;
                    m4aSongNumStart(0);
                }
                if (lbl_03005D58[i] & 0x1) {
                    m4aSongNumStart(0);
                    if (work->unk30.ub[i] == 0) {
                        work->unk30.ub[i] = 0xFF;
                        work->unk34 |= 1 << i;
                        work->unk35 |= 1 << i;
                        if (work->unk34 == lbl_03005D67) {
                            if (i == lbl_03005D65) {
                                lbl_03005D76 = 0x1300;
                            }
                            fn_020012AC(work, 1);
                            goto end;
                        }
                    } else {
                        work->unk30.ub[i] |= 0xFF;
                        if (i == lbl_03005D65) {
                            lbl_03005D76 = 0x1200;
                        }
                        work->unk35 |= 1 << i;
                    }
                }
            }
        } else if (work->unk36) {
            goto setup;
        } else if (lbl_03005D58[lbl_03005D65] & 0xFF) {
            m4aSongNumStart(0);
            fn_020012AC(work, 1);
            break;
        }
        work->unk2C++;
        break;
    }
end:
    fn_020072E8(lbl_030063F8);
    if (lbl_03005D64 && !work->unk5) {
        fn_0200455C(lbl_0202C618);
        fn_02005D5C(&lbl_030060F8);
    }
}

void fn_02001084(struct Work *work, u32 frames, s32 x, s32 y, const char *fmt)
{
    u16 min, sec, frac;
    u16 total;

    total = frames / 30;
    frac = (frames % 30) * 100 / 30;
    min = total / 60;
    sec = total % 60;
    fn_02007148(lbl_0202BB94, x, y, fmt, min, sec, frac);
}

void fn_020010FC(struct Work *work)
{
    const char *str;
    u8 rank;

    if (work->unk20 != -1) {
        if (work->unk4 == 3) {
            work->unk24++;
            work->unk1C++;
            if ((lbl_03005250 & 15) > 4) {
                fn_02001084(work, work->unk20, 0, 1, lbl_0200ED00);
            } else {
                fn_02007148(lbl_0202BB94, 0, 1, lbl_0200ED18);
            }
            if (work->unk1C > 150) {
                work->unk20 = -1;
            }
        } else {
            work->unk1C++;
            if ((lbl_03005250 & 15) > 4 || work->unk1C > 150) {
                fn_02001084(work, work->unk20, 0, 1, lbl_0200ED00);
            } else {
                fn_02007148(lbl_0202BB94, 0, 1, lbl_0200ED18);
            }
        }
    } else if (work->unk1C != work->unk20) {
        if (work->unk4 == 3) {
            work->unk24++;
            work->unk1C++;
        }
        fn_02001084(work, work->unk1C, 0, 1, lbl_0200ED00);
    }
    if (work->unk24 != -1) {
        fn_02001084(work, work->unk24, 0, 2, lbl_0200ED2C);
    }
    if (work->unk4 == 3) {
        rank = fn_020044F4(lbl_0202C618, lbl_03005D65);
    } else {
        rank = work->unk14;
    }
    switch (rank) {
    case 0:
    case 1:
        str = lbl_0200ED44;
        break;
    case 2:
        str = lbl_0200ED48;
        break;
    case 3:
        str = lbl_0200ED4C;
        break;
    case 4:
        str = lbl_0200ED50;
        break;
    case 5:
        str = lbl_0200ED54;
        break;
    case 6:
        str = lbl_0200ED58;
        break;
    case 7:
        str = lbl_0200ED5C;
        break;
    case 8:
        str = lbl_0200ED60;
        break;
    default:
        str = lbl_0200ED64;
        break;
    }
    fn_020070F8(lbl_0202BB94, 25, 4, 14, str);
}

void fn_020012AC(struct Work *work, u8 state)
{
    s16 *count;
    s32 i;

    work->unk4 = state;
    switch (work->unk4) {
    case 0:
        work->unk2C = 0;
        break;
    case 1:
        m4aSongNumStop(3);
        m4aSongNumStop(8);
        m4aSongNumStop(7);
        m4aSongNumStop(9);
        m4aMPlayFadeOut(lbl_020157D0, 4);
        work->unk2C = 0;
        work->unk34 = 0;
        for (i = 0; i <= 3; i++) {
            work->unk30.b[i] = 0;
        }
        break;
    case 2:
        SetPlayerNo(&lbl_030060F8, lbl_03005D65);
        work->unk17 = 0;
        lbl_03005C5D = -1;
        work->unk20 = work->unk1C = work->unk24 = work->unk28 = -1;
        lbl_03005C5E = 0;
        lbl_03005C60 = lbl_03005C64 = 0;
        work->unkA = lbl_0201C2F9;
        work->unk9 = lbl_0201C2FA;
        fn_02003E28(lbl_0202C618);
        for (i = 0; i <= 3; i++) {
            if ((u8)(1 << i) & lbl_03005D67) {
                fn_02004E54(lbl_0202C618, i, work->unk30.ub[i]);
            }
        }
        fn_02004E8C(lbl_0202C618, work->unkA - lbl_03005D66);
        count = fn_02006EFC(lbl_030063E0, 1);
        for (i = 0; i < *count; i++) {
            fn_020054CC(lbl_0202C618, 0, i);
        }
        count = fn_02006EFC(lbl_030063E0, 2);
        for (i = 0; i < *count; i++) {
            fn_020054CC(lbl_0202C618, 1, i);
        }
        work->unk2C = 0;
        work->unkB = 0;
        work->unk15 = 0x80;
        break;
    case 3:
        work->unk2C = 0;
        work->unk1A = 0;
        work->unk16 = 0;
        work->unk8 = 0;
        work->unk17 = 0;
        work->unk18 = 0;
        break;
    case 4:
        work->unk2C = 0;
        work->unk30.w = -1;
        work->unk14 = work->unkB;
        m4aSongNumStart(3);
        if (work->unk14 <= 1) {
            m4aSongNumStart(51);
        } else {
            m4aSongNumStart(52);
        }
        break;
    case 5:
        work->unk2C = 0;
        work->unk34 = 0;
        work->unk35 = 0;
        work->unk36 = 0;
        for (i = 0; i <= 3; i++) {
            work->unk30.b[i] = 0;
        }
        break;
    }
}

void fn_02001490(struct Work *work, u8 id)
{
    work->unkC[work->unkB] = id;
    work->unkB++;
    if (id <= 3) {
        work->unk8 |= 1 << id;
    }
}

void fn_020014BC(struct Work *work, u8 id)
{
    s32 i;
    s32 bit = 1 << id;

    if (bit & lbl_03005D67) {
        (lbl_0202C618 + id)->unkA = 0;
        lbl_03005D67 &= ~bit;
        lbl_03005D66 = 0;
        for (i = 0; i <= 3; i++) {
            if ((lbl_03005D67 >> i) & 1) {
                lbl_03005D66++;
            }
        }
    }
}

void fn_02001518(struct Work *work)
{
    lbl_030060F4 = 0xFF;
    lbl_030060F5 = 0xFF;
    work->unk5 = 0;
    fn_020071E4(lbl_0202BB94);
}

void fn_02001540(struct Work *work)
{
    m4aSongNumStart(1);
    m4aMPlayFadeOut(lbl_02015850, 2);
    work->unk6 = 0;
    work->unk5 = 1;
    fn_020071C8(lbl_0202BB94);
    switch (work->unk4) {
    case 3:
        if (work->unk7 == lbl_03005D65) {
            fn_020072AC(lbl_0202BB94, lbl_03005D60);
        } else {
            fn_020070F8(lbl_0202BB94, 12, 5, 14, lbl_0200ED68);
        }
        break;
    case 1:
        work->unk38 = 0;
        work->unk39 = 0;
        work->unk3A = 1;
        work->unk3B = 1;
        work->unk3C = 0x1000;
        REG_DMA0CNT_H = 0;
        REG_IE &= ~0x4;
        fn_020072D4(lbl_0202BB94);
        break;
    }
}

void fn_020015F8(struct Work *work)
{
    fn_0200726C(lbl_0202BB94);
    fn_0200720C(lbl_0202BB94);
    {
        u8 save38 = work->unk38;
        u8 save39 = work->unk39;
        u8 save3A = work->unk3A;
        u8 save3B = work->unk3B;
        u16 ie = REG_IE;
        u16 keycnt;

        REG_IE &= ~0x4;
        work->unk38 = 0;
        work->unk39 = 0;
        work->unk3A = 1;
        work->unk3B = 0;
        work->unk3C = 0x1000;
        REG_DISPCNT &= 0x81FF;
        REG_DMA0CNT_H = 0;
        m4aSongNumStop(3);
        m4aSongNumStop(7);
        m4aSongNumStop(9);
        if (work->unk4 == 3) {
            m4aMPlayFadeOutTemporarily(lbl_020157D0, 4);
        }
        fn_0200022C(360);
        m4aSongNumStop(1);
        REG_DISPCNT &= 0xE0FF;
        fn_0200022C(60);
        keycnt = REG_KEYCNT;
        REG_KEYCNT = 0xC304;
        REG_IE = 0x1000;
        SoundBiasReset();
        asm("swi 3");
        SoundBiasSet();
        REG_KEYCNT = keycnt;
        REG_IE = ie;
        fn_0200022C(60);
        REG_KEYCNT = 0;
        REG_IE &= ~0x1000;
        work->unk38 = save38;
        work->unk39 = save39;
        work->unk3A = save3A;
        work->unk3B = save3B;
        fn_02007238(lbl_0202BB94);
        fn_020071E4(lbl_0202BB94);
        if (work->unk4 == 3) {
            m4aMPlayFadeIn(lbl_020157D0, 4);
        }
        fn_02001540(work);
    }
}

void fn_02001774(struct Work *work)
{
    u16 keys;
    u8 max;
    s32 i;

    if (work->unk5) {
        keys = lbl_03005D58[work->unk7];
        switch (work->unk4) {
        case 3:
        case 4:
            max = lbl_03005D60 ? 1 : 2;
            break;
        case 1:
            max = 1;
            break;
        }
        if (keys & 0x8) {
            m4aSongNumStart(1);
            if (work->unk4 == 1) {
                goto resume;
            }
            goto close;
        } else if (keys & 0x40) {
            m4aSongNumStart(0);
            if (--work->unk6 < 0) {
                work->unk6 = max;
            }
        } else if (keys & 0x80) {
            m4aSongNumStart(0);
            work->unk6++;
            if (work->unk6 > max) {
                work->unk6 = 0;
            }
        } else if (keys & 0x1) {
            m4aSongNumStart(1);
            switch (work->unk4) {
            case 3:
            case 4:
                switch (work->unk6) {
                case 0:
                    fn_02001518(work);
                    break;
                case 1:
                    work->unk5 = 0;
                    if (work->unk7 == lbl_03005D65) {
                        lbl_03005D76 = 0x1300;
                    }
                    fn_020012AC(work, 1);
                    break;
                case 2:
                    fn_020015F8(work);
                    break;
                }
                break;
            case 1:
                lbl_03005D58[work->unk7] &= ~0x1;
                switch (work->unk6) {
                case 0:
                resume:
                    work->unk38 = 0;
                    work->unk39 = 1;
                    work->unk3A = 1;
                    work->unk3B = 1;
                close:
                    fn_02001518(work);
                    break;
                case 1:
                    fn_020015F8(work);
                    break;
                }
                break;
            }
        }
    } else if (work->unk2C != 0) {
        for (i = 0; i <= 3; i++) {
            if (lbl_03005D58[i] & 0x8) {
                switch (work->unk4) {
                case 3:
                case 4:
                    if (!((work->unk8 >> i) & 1)) {
                        work->unk7 = i;
                        fn_02001540(work);
                    }
                    return;
                case 1:
                    if (!lbl_03005D60) {
                        work->unk7 = i;
                        fn_02001540(work);
                    }
                    return;
                }
            }
        }
    }
}

void fn_02001934(struct Work *work)
{
    struct Point pos[1];

    if (work->unk5 && lbl_03005D65 == work->unk7) {
        switch (work->unk4) {
        case 1:
            pos->x = 86;
            pos->y = work->unk6 * 16 + 86;
            break;
        case 2:
        case 3:
        case 4:
            pos->x = 86;
            pos->y = work->unk6 * 16 + 78;
            break;
        }
        fn_02004930(lbl_0202C618, 57, pos, 0);
    }
}

void fn_020019A0(struct Point *pos, u8 n)
{
    u8 idx = n - 1;

    fn_02004930(lbl_0202C618, idx + 62, pos, 0);
}

static inline void SetPoint(struct Point *p, s16 x, s16 y)
{
    p->x = x;
    p->y = y;
}

void fn_020019C8(struct Work *work)
{
    struct Point pos;
    struct Point cursor;
    struct Point num;
    struct Unk02010248 *data;
    s32 i;

    switch (work->unk4) {
    case 0:
        break;
    case 1:
        fn_0200468C(lbl_0202C618);
        if (work->unk5 == 0) {
            SetPoint(&pos, 64, 64);
            fn_02004930(lbl_0202C618, 58, &pos, 0);
            for (i = 0; i <= 3; i++) {
                pos.y = 55 + i * 32;
                data = &lbl_02010248[i];
                pos.x = 87;
                fn_020019A0(&pos, data->unk10);
                pos.x += 56;
                fn_020019A0(&pos, data->unk11);
                pos.x += 56;
                fn_020019A0(&pos, data->unk12);
                if (work->unk30.b[lbl_03005D65] == i) {
                    pos.x = 8;
                    fn_02004930(lbl_0202C618, 57, &pos, 0);
                }
            }
        } else {
            fn_02001934(work);
        }
        fn_020046E8(lbl_0202C618);
        break;
    case 2:
    case 3:
    case 4:
    case 5:
        if (lbl_03005D61 == 0) {
            break;
        }
        fn_0200468C(lbl_0202C618);
        fn_020045DC(lbl_0202C618);
        if (work->unk4 == 5) {
            if (lbl_03005D60 && work->unk30.ub[lbl_03005D65] != 0xFF) {
                SetPoint(&cursor, 78, work->unk30.ub[lbl_03005D65] * 24 + 94);
                fn_02004930(lbl_0202C618, 57, &cursor, 0);
            }
        } else {
            SetPoint(&num, 208, 14);
            if (work->unk17 && lbl_03005C5D < work->unk9) {
                if (lbl_03005C5D <= 0) {
                    fn_02004930(lbl_0202C618, 41, &num, 0);
                } else {
                    fn_02004930(lbl_0202C618, lbl_03005C5D + 41, &num, 0);
                }
            }
            fn_02004DD0(lbl_0202C618, 0, lbl_03005D65, lbl_03005C60);
            fn_02004DD0(lbl_0202C618, 1, lbl_03005D65, lbl_03005C64);
        }
        fn_02001934(work);
        fn_020046E8(lbl_0202C618);
        break;
    }
}

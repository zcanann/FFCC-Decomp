#include "gba_types.h"

#define REG_KEYINPUT (*(vu16 *)0x04000130)
#define REG_RCNT (*(vu16 *)0x04000134)
#define REG_JOYCNT (*(vu16 *)0x04000140)
#define REG_JOY_RECV (*(vu32 *)0x04000150)
#define REG_JOY_TRANS (*(vu32 *)0x04000154)
#define REG_JOYSTAT (*(vu16 *)0x04000158)
#define REG_IE (*(vu16 *)0x04000200)
#define REG_IF (*(vu16 *)0x04000202)
#define REG_IME (*(vu16 *)0x04000208)

struct JoyWork {
    vu8 unk0;
    vu8 unk1;
    vu8 unk2;
    vu8 unk3;
    vu8 unk4;
    vu8 unk5;
    vu8 unk6;
    u8 unk7;
    u8 unk8;
    u8 unk9[3];
    u32 unkC;
    u32 unk10;
    u32 unk14;
    u8 send[0x60];
    union {
        u8 raw[0x60];
        struct {
            u8 unk0[0x14];
            u8 unk14[4][16];
        } info;
    } recv;
};

struct JoyRow {
    vu8 valid[8];
    vu32 data[5];
};

struct JoyRecvLog {
    vu8 idx;
    vu8 unk1;
    vu8 mask;
    u8 unk3;
    struct JoyRow rows[4];
};

struct AnimFrame {
    u16 unk0;
    u16 duration;
};

struct Anim {
    u16 unk0;
    u16 unk2;
    u16 count;
    u16 unk6;
    struct AnimFrame frames[0];
};

struct AnimBank {
    u32 unk0;
    struct Anim *anims[0];
};

struct AnimState {
    u16 id;
    u16 timer;
    u16 duration;
    u8 frame;
    u8 unk7;
    u8 loop : 1;
};

struct ActorData {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    u16 unk8;
    u16 unkA;
    u16 unkC;
    u8 unkE;
    u8 unkF;
    u8 unk10[4];
};

struct Vec {
    s16 x;
    s16 unk2;
    s16 y;
    s16 unk6;
};

struct Vec3 {
    s16 x;
    s16 y;
    s16 z;
};

struct Actor {
    struct Vec pos;
    u16 unk8;
    u8 unkA;
    u8 unkB;
    struct AnimState anim;
    struct ActorData *data;
    u16 unk1C;
    u16 unk1E;
    s16 unk20;
    u16 unk22;
    u16 unk24;
    u16 unk26;
    u16 unk28;
    s16 unk2A;
    s16 unk2C;
    u16 unk2E;
    s16 unk30;
    u16 unk32;
    u16 unk34;
    u16 unk36;
    struct Vec3 vel;
    u16 unk40;
    u16 unk42;
    u16 unk44;
    u16 unk46;
    u16 unk48;
    u8 unk4A;
    u8 unk4B;
    u8 unk4C;
    u8 unk4D;
    u8 unk4E;
    u8 unk4F;
    u8 unk50;
    s8 unk51;
    u8 unk52;
    s8 unk53;
    u8 unk54;
    u8 unk55_0 : 1;
    u8 unk55_1 : 1;
    u8 unk55_2 : 1;
    u8 unk55_3 : 1;
    u8 unk55_4 : 1;
};

struct PathNode {
    u16 x;
    u16 y;
    u8 unk4[5];
    u8 unk9;
    u8 unkA[6];
};

struct Path {
    s16 count;
    s16 unk2;
    struct PathNode *nodes;
};

struct MapPoint {
    u16 x;
    u16 y;
};

struct MapPoints {
    u32 unk0;
    struct MapPoint *points;
};

struct Camera {
    u8 unk0[0x46];
    u16 unk46;
};

struct Dir {
    s16 x;
    s16 y;
};

struct Item {
    struct Vec pos;
    u16 unk8;
    u8 active;
    u8 unkB[13];
    u8 type;
    u8 unk19[3];
    u16 unk1C;
    u8 unk1E;
};

struct Game {
    struct Actor players[4];
};

struct Work {
    u8 unk0[4];
    u8 unk4;
    u8 unk5[4];
    s8 unk9;
};

extern u16 lbl_03000044;
extern u16 lbl_03000046;
extern struct JoyWork lbl_03005C78;
extern u32 lbl_03005C58;
extern vu8 lbl_03005D60;
extern u8 lbl_03005D61;
extern u8 lbl_03005D62;
extern u8 lbl_03005D63;
extern u8 lbl_03005D64;
extern u8 lbl_03005D68;
extern u32 lbl_03005D6C;
extern u16 lbl_03005D76;
extern u16 lbl_03005DEC;
extern u8 lbl_0201C2F8;
extern u32 lbl_03005248;
extern vu16 lbl_03005D50[4];
extern vu16 lbl_03005D58[4];
extern u16 lbl_03005D70;
extern u16 lbl_03005D74;
extern char lbl_0200ED80[];
extern u8 lbl_0202BB94[];
extern u8 lbl_030063C8[];
extern struct Game lbl_0202C618;
extern u8 lbl_0202C662[];
extern u8 lbl_0202CA38[];
extern u8 lbl_0202DFFE;
extern u8 lbl_0202DFFC;
extern u8 lbl_030063E0[];
extern u16 lbl_0201C320;
extern s16 lbl_0200EE10[];
extern u8 lbl_0201C31C[];
extern struct ActorData lbl_02010248[];
extern struct Camera lbl_030060F8;
extern u8 lbl_020159A4[];
extern s16 lbl_0201C2FC[];
extern s16 lbl_0201C300[];
extern u32 lbl_0300524C;
extern u8 lbl_030060F4;
extern u8 lbl_030060F5;
extern u8 lbl_03006144[];
extern u8 lbl_030063F8[];
extern u8 lbl_02015850[];
extern struct Work lbl_03000000;
extern u32 lbl_0200ED70;
extern u32 lbl_0200ED78;
extern vu8 lbl_03005D65;
extern vu8 lbl_03005D66;
extern vu8 lbl_03005D67;
extern vu8 lbl_03005D69;
extern u8 lbl_03005D6A;
extern struct JoyRecvLog lbl_03005D78;
extern vu8 lbl_03005DEE;
extern u8 lbl_03005DEF;
extern vu8 lbl_03005DF0;
extern u8 start_vector[];
extern struct AnimBank *lbl_0202D954;

void fn_020001A0();
void fn_02001490(struct Work *, u8);
void fn_020014BC(struct Work *, u8);
s16 *fn_02006B68(void *, u8);
void fn_02004C40(void *, struct AnimState *, struct Actor *);
u8 fn_02006C94(struct Path *, u8, s16, s16, u16 *);
struct MapPoints *fn_02006EFC(void *, s32);
void fn_020035B8(struct Actor *);
s16 ArcTan2(s16, s16);
s32 Sqrt(s32);
s16 fn_02007520(s16, s16);
void fn_020054A4();
void fn_0200411C(void *, struct Vec3 *, struct Actor *);
void fn_0200692C(void *, struct Vec3 *, struct Vec3 *, u16 *);
u8 fn_020069A0(void *, struct Actor *, struct Vec3 *, u16 *);
void fn_02007308(void *, s32, struct Actor *);
void m4aSongNumStart(u16);
void m4aSongNumStop(u16);
void m4aMPlayPitchControl(void *, u16, s16);
void fn_0200720C(void *);
void fn_02009170(void);

static inline struct Anim *GetAnim(u16 id)
{
    return lbl_0202D954->anims[id];
}

void fn_02001BA8(void)
{
    u16 keys = REG_KEYINPUT ^ 0x3FF;

    lbl_03000046 = keys & ~lbl_03000044;
    lbl_03000044 = keys;
}

u32 fn_02001BD8(u32 data)
{
    u32 crc = 0;
    u32 i;
    u32 bit;

    for (i = 2; i != 0; i--) {
        for (bit = 0x80; bit != 0; bit >>= 1) {
            crc <<= 1;
            if (data & bit) {
                if (crc & 0x100)
                    crc ^= 0xCC;
                else
                    crc++;
            } else if (crc & 0x100) {
                crc ^= 0xCD;
            }
        }
        data >>= 8;
    }
    for (i = 0; i < 8; i++) {
        crc <<= 1;
        if (crc & 0x100)
            crc ^= 0xCD;
    }
    return crc & 0xFF;
}

s32 fn_02001C48(u32 data)
{
    s32 i;

    lbl_03005D6A = data;
    if ((data & 0xFF) == 0x80) {
        fn_02009170();
        return 0;
    }
    if (lbl_03005C78.unk0 == 0) {
        if (lbl_03005C78.unk1 == 2) {
            if (data != lbl_03005C78.unk14)
                return 0;
            REG_JOYSTAT = 0x30;
            lbl_03005C78.unk10 = data;
            lbl_03005C78.unk1 = 3;
        } else if (lbl_03005C78.unk1 == 3) {
            if (data != 0x60)
                return 0;
            REG_JOY_TRANS = *(u32 *)&lbl_03005C78.send[0];
            lbl_03005C78.unk1 = 4;
            lbl_03005C78.unk5 = 4;
        } else if (lbl_03005C78.unk1 == 5) {
            REG_JOY_TRANS = data;
            *(u32 *)&lbl_03005C78.send[8] = data;
            lbl_03005C78.unk1 = 6;
        } else {
            return 0;
        }
    } else {
        switch (lbl_03005C78.unk4) {
        case 0:
            lbl_03005C78.unk5 = 0;
            if (data == 0x30) {
                lbl_03005C78.unk4 = 0x30;
            } else if (data == 0x50) {
                return 0;
            } else {
                if (*(start_vector + 4) == 0 && lbl_03005C78.send[3] == 0)
                    return 0;
                if ((data & 0xFF) == 0x10) {
                    REG_JOY_TRANS = lbl_03005C58;
                    REG_JOYSTAT = 0x30;
                    lbl_03005C78.unk4 = 0x10;
                } else if ((data & 0xFF) == 0x70) {
                    lbl_03005D69++;
                    lbl_03005C78.unk4 = 0x40;
                }
            }
            break;
        case 0x30:
            if (lbl_03005C78.unk5 >= 0x60)
                return 0;
            *(u32 *)&lbl_03005C78.recv.raw[lbl_03005C78.unk5] = data;
            lbl_03005C78.unk5 += 4;
            if (lbl_03005C78.unk5 == 0x60) {
                lbl_03005C78.recv.raw[2] = lbl_03005C78.send[2];
                *(u32 *)&lbl_03005C78.recv.raw[12] = *(u32 *)&lbl_03005C78.send[12];
                REG_JOY_TRANS = *(u32 *)&lbl_03005C78.recv.raw[0];
                lbl_03005C78.unk5 += 4;
            }
            break;
        case 0x40:
            i = (data & 0xFF) - 0x40;
            if (i <= 4) {
                lbl_03005D78.rows[lbl_03005D78.idx].data[i] = data;
                lbl_03005D78.rows[lbl_03005D78.idx].valid[i] = 1;
                lbl_03005D78.mask |= 1 << i;
            }
            lbl_03005C78.unk5++;
            if (lbl_03005D78.mask == 0x1F) {
                lbl_03005D78.mask = 0;
                REG_JOYSTAT = 0x20;
                lbl_03005C78.unk4 = 0;
                lbl_03005D78.idx++;
                if (lbl_03005D78.idx > 3)
                    lbl_03005D78.idx = 0;
                lbl_03005DEF = 0;
            }
            break;
        default:
            return 0;
        }
    }
    return 1;
}

s32 fn_02001E04(void)
{
    u32 i;
    s32 j;

    if (lbl_03005C78.unk0 == 0) {
        if (lbl_03005C78.unk1 == 1) {
            lbl_03005C78.unk1 = 2;
        } else if (lbl_03005C78.unk1 == 4) {
            if (lbl_03005C78.unk5 != 0x60)
                goto send;
            if (lbl_03005C78.send[3] != 0) {
                lbl_03005C78.unk1 = 5;
            } else {
                lbl_03005C78.unk0 = 1;
                lbl_03005C78.unk4 = 0;
                lbl_03005C78.unk1 = 0;
            }
        } else if (lbl_03005C78.unk1 == 6) {
            lbl_03005C78.unk0 = 1;
            lbl_03005C78.unk4 = 0;
            lbl_03005C78.unk1 = 0;
        } else {
            return 0;
        }
    } else {
        switch (lbl_03005C78.unk4) {
        case 0x10:
            lbl_03005C78.unk4 = 0x40;
            break;
        case 0x30:
            if (lbl_03005C78.unk5 < 0x60)
                return 0;
            if (lbl_03005C78.unk5 != 0xC0)
                goto send;
            for (i = 0; i < 0x60; i += 4)
                *(u32 *)&lbl_03005C78.send[i] = *(u32 *)&lbl_03005C78.recv.raw[i];
            lbl_03005C78.unk4 = 0;
            lbl_03005D65 = lbl_03005C78.recv.raw[1];
            lbl_03005D67 = lbl_03005C78.recv.raw[0x11];
            lbl_03005DEE = 0;
            lbl_03005D66 = 0;
            for (j = 0; j < 4; j++) {
                if ((lbl_03005D67 >> j) & 1)
                    lbl_03005D66++;
            }
            break;
        default:
            return 0;
        }
    }
    return 1;
send:
    REG_JOY_TRANS = *(u32 *)&lbl_03005C78.send[lbl_03005C78.unk5];
    lbl_03005C78.unk5 += 4;
    return 1;
}

void fn_02001F00(void)
{
    REG_JOY_RECV;
    REG_JOY_TRANS = lbl_03005C78.unkC;
    REG_JOYSTAT = 0x20;
    lbl_03005C78.unk0 = 0;
    lbl_03005C78.unk1 = 1;
}

void fn_02001F2C(void)
{
    struct JoyWork *w;
    u16 stat;

    lbl_03005DF0++;
    REG_IE &= ~0x80;
    stat = REG_JOYCNT;
    if (((stat & 4) && !fn_02001E04()) || ((stat & 2) && !fn_02001C48(REG_JOY_RECV))) {
        REG_JOYSTAT = 0;
        lbl_03005C78.unk0 = 0;
        lbl_03005C78.unk1 = 0;
    }
    if (stat & 1) {
        fn_02001F00();
        if (lbl_03005C78.unk8 <= 2 && ++lbl_03005C78.unk7 >= 30)
            fn_02009170();
        lbl_03005C78.unk8 = 0;
    } else if (lbl_03005C78.unk8 >= 2) {
        lbl_03005C78.unk7 = 0;
    } else {
        lbl_03005C78.unk8++;
    }
    REG_JOYCNT = stat;
    lbl_03005C78.unk2 = 0;
    REG_IE |= 0x80;
}

void fn_02002000(void)
{
    u16 ime = REG_IME;

    REG_IME = 0;
    if (lbl_03005C78.unk6 == 0)
        REG_RCNT = 0x8000;
    REG_RCNT = 0xC000;
    REG_JOYSTAT = 0;
    REG_JOY_RECV;
    REG_JOY_TRANS = 0;
    REG_JOYCNT = 0x47;
    REG_IF = 0x80;
    lbl_03005C78.unk2 = 0;
    lbl_03005C78.unk0 = 0;
    lbl_03005C78.unk1 = 0;
    lbl_03005C78.unk6 = 0;
    lbl_03005C78.unk7 = 0;
    lbl_03005C78.unk8 = 0;
    REG_IME = ime;
}

void fn_02002070(void)
{
    s32 i;
    s32 j;
    u32 k;
    u16 ime;
    s32 m;
    s32 n;

    lbl_03005D60 = lbl_0201C2F8;
    lbl_03005D78.idx = 0;
    lbl_03005D78.unk1 = 0;
    lbl_03005D78.mask = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++)
            lbl_03005D78.rows[i].valid[j] = 0;
    }
    if (lbl_03005D60 != 0) {
        lbl_03005DEC = 0;
        lbl_03005D61 = 0;
        lbl_03005D62 = 1;
        lbl_03005D63 = 0;
        lbl_03005D64 = 0;
        lbl_03005D66 = 0;
        lbl_03005DEE = 0;
        lbl_03005D67 = 0;
        lbl_03005D68 = 1;
        lbl_03005D6C = 0;
        lbl_03005DEF = 0;
        lbl_03005D69 = 0xFF;
        lbl_03005DF0 = 0;
        lbl_03005D76 = 0xFFFF;
        ime = REG_IME;
        REG_IME = 0;
        for (k = 0; k < sizeof(lbl_03005C78); k++)
            ((u8 *)&lbl_03005C78)[k] = 0;
        lbl_03005C78.unk6 = 1;
        fn_02002000();
        lbl_03005C78.unkC = lbl_0200ED70;
        lbl_03005C78.unk14 = lbl_0200ED78;
        lbl_03005C78.send[2] = *(u16 *)0x080000B2;
        *(u32 *)&lbl_03005C78.send[12] = *(u32 *)0x080000AC;
        REG_IME = ime;
    } else {
        lbl_03005D61 = 0;
        lbl_03005D62 = 1;
        lbl_03005D63 = 0;
        lbl_03005D64 = 0;
        lbl_03005D66 = 1;
        lbl_03005D67 = 1;
        lbl_03005D68 = 1;
        lbl_03005D6C = 0;
        lbl_03005D76 = 0xFFFF;
        for (m = 0; m < 4; m++) {
            for (n = 0; n < 8; n++)
                lbl_03005C78.recv.info.unk14[m][n] = n * 100 / 8 + 5;
        }
    }
}

s32 fn_02002238(void)
{
    s32 ret;

    if (lbl_03005C78.unk2 > 10) {
        lbl_03005C78.unk3 = 1;
        fn_02002000();
        ret = 1;
    } else {
        REG_IME = 0;
        lbl_03005C78.unk2++;
        REG_IME = 1;
        ret = 0;
    }
    return ret;
}

void fn_02002270(void)
{
    u32 limit;
    s32 n;
    s32 i;
    s32 j;
    s32 k;
    u16 keys;

    if (lbl_03005D60) {
        lbl_03005D63 = 0;
        if (lbl_03005D66 == 0) {
            lbl_03005D64 = 0;
            return;
        }
        if (lbl_03005DEE < 4) {
            lbl_03005D64 = 0;
            return;
        }
        if (lbl_03005D61)
            limit = lbl_03005248 + 240;
        else
            limit = lbl_03005248 + 7200;

        n = 0;
        if (lbl_03005D68)
            goto fail;
    retry:
        if (lbl_03005248 > limit) {
            for (j = 0; j < 4; j++) {
                if (j != lbl_03005D65)
                    fn_020014BC(&lbl_03000000, j);
            }
            lbl_03005D60 = 0;
            return;
        }
        if (lbl_03005D78.unk1 == lbl_03005D78.idx) {
            if (lbl_03005D61 == 0)
                goto fail;
            lbl_03005D70++;
            if (++n > 1000) {
                fn_0200720C(lbl_0202BB94);
                lbl_03005D6A = 0;
                n = 0;
            }
            goto retry;
        }

        *(vu16 *)0x050001FE = 0xFFFF;
        for (i = 0; i < 4; i++) {
            if (lbl_03005D78.rows[lbl_03005D78.unk1].valid[i]) {
                if (fn_02001BD8(lbl_03005D78.rows[lbl_03005D78.unk1].data[i] >> 8)
                    == lbl_03005D78.rows[lbl_03005D78.unk1].data[i] >> 24) {
                    keys = lbl_03005D78.rows[lbl_03005D78.unk1].data[i] >> 8;
                    if (keys == 0x2001)
                        fn_020014BC(&lbl_03000000, i);
                    if ((keys & 0xF000) == 0) {
                        lbl_03005D58[i] = keys & ~lbl_03005D50[i];
                        lbl_03005D50[i] = keys;
                    }
                } else {
                    fn_020001A0(lbl_0200ED80, 839);
                }
            } else if ((u32)(1 << i) & lbl_03005D67) {
                if (lbl_03005D61)
                    fn_020001A0(lbl_0200ED80, 844);
                goto fail;
            }
            lbl_03005D78.rows[lbl_03005D78.unk1].valid[i] = 0;
        }

        lbl_03005D74 = lbl_03005D78.rows[lbl_03005D78.unk1].data[4] >> 8;
        lbl_03005D78.unk1++;
        if (lbl_03005D78.unk1 > 3)
            lbl_03005D78.unk1 = 0;
        if (lbl_03005D62) {
            if (lbl_03005D74 != 30)
                goto fail;
            lbl_03005D62 = 0;
            lbl_03005D63 = 1;
            lbl_03005DEC = 0;
        }
        lbl_03005D61 = 1;
        lbl_03005D64 = 1;
        goto end;
    fail:
        lbl_03005D64 = 0;
    end:
        lbl_03005D68 = 0;
    } else {
        lbl_03005C58 = (fn_02001BD8(lbl_03000044) << 24) | (lbl_03000044 << 8) | 0x20;
        for (k = 0; k < 4; k++) {
            lbl_03005D58[k] = 0;
            lbl_03005D50[k] = 0;
        }
        lbl_03005D58[lbl_03005D65] = lbl_03000046;
        lbl_03005D50[lbl_03005D65] = lbl_03000044;
        lbl_03005D63 = 0;
        if (lbl_03005D62) {
            lbl_03005D62 = 0;
            lbl_03005D63 = 1;
        }
        lbl_03005D61 = 1;
        lbl_03005D64 = 1;
    }
}

void fn_020025B0(void)
{
    u32 v;

    if (lbl_03005D60 == 0)
        return;
    if (lbl_03005D66 == 0) {
        lbl_03005D64 = 0;
        return;
    }
    if (lbl_03005DEE < 3) {
        lbl_03005DEE++;
        lbl_03005D64 = 0;
        return;
    }
    if (lbl_03005DEE < 4)
        lbl_03005DEE++;
    if (lbl_03005DEF == 0) {
        if (lbl_03005D76 != 0xFFFF) {
            v = lbl_03005D76 | 0x8000;
            lbl_03005C58 = (fn_02001BD8(v) << 24) | (v << 8) | 0x20;
            lbl_03005D76 = 0xFFFF;
        } else {
            lbl_03005C58 = (fn_02001BD8(lbl_03000044) << 24) | (lbl_03000044 << 8) | 0x20;
        }
        REG_JOYSTAT = 0x10;
        lbl_03005DEF = 1;
    }
    if (lbl_03005D61)
        lbl_03005DEC++;
}

void fn_0200269C(struct AnimState *s)
{
    s->id = 0xFFFF;
    s->timer = 0;
    s->duration = 0;
    s->frame = 0;
    s->loop = 1;
}

void fn_020026B8(struct AnimState *s, u16 id, u8 arg2)
{
    s->id = id;
    s->unk7 = arg2;
    s->timer = 0;
    s->frame = 0;
    s->loop = 1;
    s->duration = (GetAnim(s->id))->frames[0].duration;
}

void fn_020026EC(struct AnimState *s, u16 id, u8 arg2)
{
    s->id = id;
    if (arg2 != 0xFF)
        s->unk7 = arg2;
}

s32 fn_02002700(struct AnimState *s)
{
    struct Anim *anim;

    if ((s->timer += 2) >= s->duration) {
        s->timer = 0;
        s->frame++;
        anim = GetAnim(s->id);
        if (s->frame >= anim->count) {
            if (s->loop)
                s->frame = 0;
            else
                s->frame--;
            s->duration = anim->frames[s->frame].duration;
            return 1;
        }
        s->duration = anim->frames[s->frame].duration;
    }
    return 0;
}

void fn_0200276C(struct Actor *a)
{
    a->unkA = 1;
    a->unk8 = 100;
}

void fn_02002778(struct Actor *a)
{
}

void fn_0200277C(struct Actor *a)
{
    fn_0200276C(a);
    fn_0200269C(&a->anim);
}

void fn_02002794(struct Actor *a)
{
    s32 n;

    a->unk44 = 0;
    n = *fn_02006B68(lbl_030063C8, a->unk4B);
    a->unk4D = n;
    a->unk4C = n - 1;
    a->unk51 = 0xFF;
    a->unk53 = -1;
    a->unk46 = 0;
    fn_0200277C(a);
    a->unk8 = 100;
    a->unk40 = 0;
    a->unk55_3 = 0;
    a->unk55_2 = 0;
    a->unk55_1 = 0;
    a->unk55_0 = 0;
    a->unk54 = 0;
    a->unk32 = 0;
    a->unk34 = 0;
    a->unk55_4 = 0;
}

void fn_0200281C(struct Actor *a)
{
    s32 n;

    if (a->unk52 <= 3) {
        a->unk4E = 1;
        n = *fn_02006B68(lbl_030063C8, 1);
        a->unk50 = n;
        a->unk4F = n - 1;
    }
    fn_02001490(&lbl_03000000, a->unk52);
}

u16 fn_02002860(struct Actor *a)
{
    return ((a->unk51 + 128) << 8) | a->unk4A;
}

struct Actor *fn_0200287C(struct Actor *a, u8 mode)
{
    s32 i;
    s32 start;
    s32 end;
    u32 mask;
    u16 key;
    u32 best;
    u16 k;
    struct Actor *other;
    struct Actor *result;

    if (mode == 0xFF) {
        start = 4;
        end = lbl_0202DFFE + 4;
        mask = ~(1 << a->unk52);
    } else if (mode == 0) {
        start = 0;
        end = 4;
        mask = lbl_03005D67 & ~(1 << a->unk52);
    } else {
        start = 4;
        end = lbl_0202DFFE + 4;
        mask = ~(1 << a->unk52);
    }
    key = fn_02002860(a);
    best = 0;
    result = NULL;
    for (i = start; i < end; i++) {
        if ((1 << i) & mask) {
            other = &lbl_0202C618.players[(u8)i];
            k = fn_02002860(other);
            if (k < key && best < k) {
                best = k;
                result = other;
            }
        }
    }
    return result;
}

s32 fn_02002928(struct Actor *a, struct Vec *pos, u8 *outA, u16 *outB, u16 *outC, u16 *outD, u16 *outE, u32 *outF)
{
    s32 n;
    u32 mask;
    s8 best;
    s8 d;
    struct Actor *found;
    struct Actor *other;
    struct Item *item;
    struct Item *p;
    s32 i;

    n = lbl_0202DFFE + 4;
    mask = ~(1 << a->unk52);
    best = 0x7F;
    found = NULL;
    for (i = 0; i < n; i++) {
        if ((1 << i) & mask) {
            other = &lbl_0202C618.players[(u8)i];
            d = lbl_0202C662[(u8)i * sizeof(struct Actor)] - a->unk4A;
            if (d >= 0 && best > d) {
                best = d;
                found = other;
            }
        }
    }
    item = NULL;
    p = (struct Item *)lbl_0202CA38;
    for (i = 0; i < 64; i++) {
        if (p->active && p->type == 9) {
            d = p->unk1E - a->unk4A;
            if (d >= 0 && best > d) {
                best = d;
                item = p;
                found = NULL;
            }
        }
        p = (struct Item *)((u8 *)p + 28);
    }
    if (item != NULL) {
        *pos = item->pos;
        *outA = item->unk1E;
        *outB = item->unk1C;
        *outC = 0;
        *outD = 1800;
        *outE = 800;
        *outF = 64000000;
    } else if (found != NULL) {
        *pos = found->pos;
        *outA = found->unk4A;
        *outB = found->unk48;
        *outC = found->unk40;
        *outD = 1000;
        *outE = 400;
        *outF = 25000000;
    } else {
        return 0;
    }
    return 1;
}

void fn_02002A88(struct Actor *a)
{
    struct Path *path;
    struct PathNode *node;
    u8 prev;
    s16 dx;
    s16 dy;
    s16 v;
    u8 lo;
    u8 hi;

    path = (struct Path *)fn_02006B68(lbl_030063C8, a->unk4B);
    prev = a->unk4C;
    a->unk4C = fn_02006C94(path, prev, a->pos.x, a->pos.y, &a->unk48);
    node = &path->nodes[a->unk4C];
    dx = node->x - a->pos.x;
    if (dx < 0)
        dx = -dx;
    dy = node->y - a->pos.y;
    if (dy < 0)
        dy = -dy;
    a->unk2E = dx + dy;
    v = node->unk9 + (a->unk2E << 4) / path->unk2;
    if (v > 255)
        v = 255;
    a->unk4A = v;
    lo = a->unk4D >> 2;
    hi = lo + (a->unk4D >> 1);
    if (a->unk4C <= lo && prev >= hi) {
        a->unk51++;
        if (lbl_03000000.unk9 == a->unk51)
            fn_0200281C(a);
    } else if (a->unk4C >= hi && prev <= lo) {
        a->unk51--;
    }
}

void fn_02002B88(struct Actor *a)
{
    fn_02004C40(&lbl_0202C618, &a->anim, a);
}

static inline void GetDir(struct Dir *dir, u16 angle)
{
    dir->x = lbl_0200EE10[angle >> 5];
    dir->y = lbl_0200EE10[(angle >> 5) + 0x200];
}

void fn_02002BA0(struct Actor *a)
{
    struct ActorData *d = a->data;
    struct Dir dir;
    

    a->unk1C = d->unk0;
    a->unk1E = d->unk2;
    a->unk22 = d->unk4;
    a->unk20 = d->unk6;
    a->unk24 = d->unk8;
    a->unk28 = d->unkA;
    a->unk2C = d->unkC;
    a->unk2A = 0;
    a->unk26 = lbl_0201C320;
    a->unk44 = lbl_0201C320;
    a->unk42 = a->unk26;
    GetDir(&dir, a->unk26);
    a->vel.x = dir.x;
    a->vel.z = dir.y;
    a->unk40 = 0x100;
}

void fn_02002C24(struct Actor *a, u8 id, u8 kind)
{
    struct MapPoint *pt;

    a->unk4E = 0xFF;
    a->unk4B = 0;
    fn_02002794(a);
    a->data = &lbl_02010248[lbl_0201C31C[kind]];
    fn_02002BA0(a);
    a->unk52 = id;
    a->pos.unk2 = 0;
    pt = &fn_02006EFC(lbl_030063E0, 0)->points[lbl_0202DFFC];
    a->pos.x = pt->x;
    a->pos.y = pt->y;
    if (a->data->unkF <= 3)
        fn_020026B8(&a->anim, 0, a->data->unkF);
    else
        fn_020026B8(&a->anim, 0, a->data->unkF + 8);
    a->unk55_4 = 1;
}

void fn_02002CD0(struct Actor *a)
{
    u16 camera = lbl_030060F8.unk46;
    u8 *tbl = lbl_020159A4;
    s32 dir = ((u16)(a->unk44 - camera) + 0x1000) >> 13 & 7;

    fn_020026EC(&a->anim, tbl[dir], 0xFF);
}

static inline void Vec3Add(struct Vec3 *dst, struct Vec3 *src)
{
    dst->x += src->x;
    dst->y += src->y;
    dst->z += src->z;
}

void fn_02002D0C(struct Actor *a)
{
    s16 maxSpeed;
    s16 accel;
    u16 keys;
    struct Vec3 delta;
    s16 angle;
    s16 ax;
    s16 ay;
    s16 turn;
    s32 over;
    u8 sound;
    s32 moving;
    s16 newSpeed;
    s16 oldSpeed;
    struct Dir dir;
    struct Vec3 old;
    struct Vec3 next;
    u8 hit;
    s32 snd;
    s32 grip;
    s16 pitch;

    if (a->unk4E != 0xFF) {
        fn_020035B8(a);
        return;
    }
    if (lbl_03000000.unk4 < 3) {
        fn_02002700(&a->anim);
        return;
    }
    maxSpeed = a->unk24;
    accel = a->unk1C;
    if (a->unk55_2) {
        maxSpeed += *lbl_0201C2FC;
        accel += *lbl_0201C300;
    } else if (a->unk55_3) {
        maxSpeed += *(lbl_0201C2FC + 1);
        accel += *(lbl_0201C300 + 1);
    }
    if (a->unk34 != 0 && --a->unk34 == 0) {
        a->unk55_3 = 0;
        a->unk55_2 = 0;
    }
    if (!a->unk55_1) {
        if (lbl_03005D50[a->unk52] & 0x20) {
            a->unk2A -= a->unk28;
            if (a->unk2A < a->unk2C)
                a->unk2A = -a->unk2C;
        } else if (lbl_03005D50[a->unk52] & 0x10) {
            a->unk2A += a->unk28;
            if (a->unk2A > a->unk2C)
                a->unk2A = a->unk2C;
        } else if (a->unk2A > 0) {
            a->unk2A -= a->unk2C >> 2;
            if (a->unk2A < 0)
                a->unk2A = 0;
        } else if (a->unk2A < 0) {
            a->unk2A += a->unk2C >> 2;
            if (a->unk2A > 0)
                a->unk2A = 0;
        }
    }

    (&delta)->z = 0;
    (&delta)->y = 0;
    (&delta)->x = 0;
    a->unk26 += a->unk2A;
    angle = a->unk26;
    ax = a->vel.x;
    if (ax < 0)
        ax = -ax;
    ay = a->vel.z;
    if (ay < 0)
        ay = -ay;
    if (ax > 15 || ay > 15) {
        turn = ArcTan2(a->vel.z, a->vel.x);
        turn = fn_02007520(angle, turn);
    } else {
        turn = 0;
    }
    a->unk44 = angle + turn;
    a->unk42 = angle;
    if (turn < 0)
        turn = -turn;
    if (lbl_03005D65 == a->unk52) {
        if ((s16)(turn - 0xAAA) > 0)
            sound = 7;
        else
            sound = 0xFF;
    }
    over = (s16)(turn - 0xAAA);
    if (over > 0) {
        a->unk46 -= over;
        if ((s16)a->unk46 < 0) {
            a->unk46 += 0x4000;
            fn_020054A4(&lbl_0202C618, 11, a, &a->vel);
        }
    }
    if (a->unk32 != 0) {
        angle += a->unk30;
        a->unk32--;
    }
    GetDir(&dir, angle);
    moving = 1;
    a->unk40 = Sqrt(a->vel.x * a->vel.x + a->vel.z * a->vel.z);
    if ((s16)a->unk40 > maxSpeed) {
        newSpeed = a->unk40 - a->unk22;
        if (newSpeed < maxSpeed)
            newSpeed = maxSpeed;
        a->vel.x = a->vel.x * newSpeed / (s16)a->unk40;
        a->vel.z = a->vel.z * newSpeed / (s16)a->unk40;
        a->unk40 = newSpeed;
        moving = 0;
    }
    keys = lbl_03005D50[a->unk52];
    if ((keys & 1) && !a->unk55_0 && moving) {
        (&delta)->x = dir.x * accel >> 8;
        (&delta)->z = dir.y * accel >> 8;
        Vec3Add(&a->vel, &delta);
    } else if ((lbl_03005D50[a->unk52] & 2) && !a->unk55_0) {
        oldSpeed = a->unk40;
        a->unk40 = oldSpeed - a->unk1E;
        if ((s16)a->unk40 <= 0) {
            a->vel.z = 0;
            a->vel.x = 0;
            a->unk40 = 0;
        } else {
            a->vel.x = a->vel.x * (s16)a->unk40 / oldSpeed;
            a->vel.z = a->vel.z * (s16)a->unk40 / oldSpeed;
            sound = 6;
        }
    } else {
        oldSpeed = a->unk40;
        a->unk40 = oldSpeed - a->unk22;
        if ((s16)a->unk40 <= 0) {
            a->vel.z = 0;
            a->vel.x = 0;
            a->unk40 = 0;
        } else {
            a->vel.x = a->vel.x * (s16)a->unk40 / oldSpeed;
            a->vel.z = a->vel.z * (s16)a->unk40 / oldSpeed;
        }
    }
    if (lbl_03005D65 == a->unk52 && (lbl_0300524C & 15) == lbl_03005D65 && lbl_030060F5 != sound) {
        if (sound == 0xFF) {
            m4aSongNumStop(lbl_030060F5);
            lbl_030060F4 = sound;
        } else {
            m4aSongNumStart(sound);
        }
        lbl_030060F5 = sound;
    }
    grip = a->unk20 * (s16)a->unk40;
    a->vel.x = ((dir.x * grip >> 8) + a->vel.x * (256 - a->unk20)) >> 8;
    a->vel.z = ((dir.y * grip >> 8) + a->vel.z * (256 - a->unk20)) >> 8;
    old.x = a->pos.x;
    (&old)->z = a->pos.y;
    next.x = a->pos.x + (a->vel.x >> 4);
    (&next)->y = a->pos.unk2;
    (&next)->z = a->pos.y + (a->vel.z >> 4);
    fn_0200411C(&lbl_0202C618, &next, a);
    fn_0200692C(lbl_03006144, &next, &a->vel, &a->unk40);
    a->pos.x += a->vel.x >> 4;
    a->pos.y += a->vel.z >> 4;
    hit = fn_020069A0(lbl_03006144, a, &a->vel, &a->unk40);
    if (hit & 1) {
        a->pos.x = old.x;
        a->pos.y = old.z;
    }
    if (lbl_03005D65 == a->unk52 && lbl_030060F4 != 5) {
        if ((s16)a->unk40 <= 4)
            snd = 0xFF;
        else if (hit & 4)
            snd = 8;
        else
            snd = 3;
        if (lbl_030060F4 != snd) {
            if (snd == 0xFF)
                m4aSongNumStop(lbl_030060F4);
            else
                m4aSongNumStart(snd);
            lbl_030060F4 = snd;
        }
        if (snd != 0xFF) {
            pitch = ((s16)a->unk40 << 8) / 320;
            m4aMPlayPitchControl(lbl_02015850, 0xFFFF, pitch);
        }
    }
    fn_02002700(&a->anim);
    fn_02002A88(a);
    if ((lbl_03005D58[a->unk52] & 0x200) && (u8)a->unk53 != 0xFF) {
        if (lbl_03005D65 == a->unk52)
            fn_02007308(lbl_030063F8, 13, a);
        switch ((u8)a->unk53 % 3) {
        case 0:
            fn_020054A4(&lbl_0202C618, 3, a->unk52, a, a->unk44, a->unk4B, a->unk4C);
            break;
        case 1:
            fn_020054A4(&lbl_0202C618, 6, a->unk52, a, a->unk44, a->unk4B, a->unk4C);
            break;
        case 2:
            fn_020054A4(&lbl_0202C618, 8, a->unk52, a, a->unk44, &a->vel);
            break;
        }
        a->unk53 = 0xFF;
    }
    a->unk55_1 = 0;
    a->unk55_0 = 0;
}

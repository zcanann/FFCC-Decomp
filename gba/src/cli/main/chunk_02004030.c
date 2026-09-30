#include "gba_types.h"

#define REG_DMA3 ((vu32 *)0x040000D4)

#define DmaSet3(src, dest, control)       \
    {                                     \
        vu32 *dmaRegs = REG_DMA3;         \
        dmaRegs[0] = (vu32)(src);         \
        dmaRegs[1] = (vu32)(dest);        \
        dmaRegs[2] = (vu32)(control);     \
        dmaRegs[2];                       \
    }

void *memset(void *dst, int c, u32 n);
void *memcpy(void *dst, const void *src, u32 n);
char *strcpy(char *dst, const char *src);
u32 strlen(const char *s);

struct Cmd {
    u8 unk0;
    u8 unk1;
    u16 unk2;
};

struct Cmd8 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
};

struct ObjEntry {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    u8 *unk8;
};

struct GfxInfo {
    u8 unk0[12];
    u8 unkC;
    u8 unkD;
    u8 unkE[6];
    u8 *unk14;
    u8 *unk18;
    u8 *unk1C;
};

struct Work {
    s8 unk0;
    u8 unk1[3];
    u8 unk4[4];
    u8 unk8[4];
    char names[4][18];
    u8 unk54[8];
    u8 unk5C;
    u8 unk5D;
    u8 unk5E[4];
    u8 unk62[2];
    s16 unk64[64];
    s16 unkE4[8];
    u16 unkF4[8];
    union {
        u32 word;
        u8 bytes[4];
    } unk104;
    u8 unk108[12];
    u8 unk114[12];
    s16 unk120[4];
    u8 unk128;
    u8 unk129;
};

struct Member {
    void *unk0;
    u16 unk4;
    s8 unk6;
    s8 unk7;
};

struct MemberData {
    u8 entries[8][16];
    s8 slots[4];
};

struct MarkerEntry {
    u8 unk0;
    u8 unk1[3];
    u16 unk4;
    u16 unk6;
    u16 unk8;
    u16 unkA;
};

struct MarkerList {
    u8 count;
    u32 unk4;
    struct MarkerEntry entries[32];
};

struct Flag3 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
};

extern u16 lbl_03002AEC;
extern u8 lbl_03002AC4;
extern struct GfxInfo lbl_03002670;
extern struct ObjEntry lbl_03001970[];
extern s16 lbl_0202FA20[];
extern u8 lbl_02036A30[][32];
extern u8 lbl_03002070[];
extern u8 lbl_03002738[];
extern u8 lbl_03002690;
extern u8 lbl_03001168[2][0x400];
extern struct Work lbl_03002CA0;
extern struct Member lbl_03002FD0[4];
extern struct MemberData lbl_03003000;
extern struct MarkerList lbl_03002B10;
extern char lbl_03002F20[2][65];
extern u8 lbl_03002DCC[4];
extern s8 lbl_03002770;
extern u8 lbl_03002ED0;
extern u8 lbl_03002FF0;
extern u8 lbl_03002B00;
extern u8 lbl_03002C98;
extern u16 lbl_03002754[2];
extern u16 lbl_03002758[2];
extern u8 lbl_03003080[8];
extern struct Flag3 lbl_03002760[4];
extern struct Flag3 lbl_03002DD0[64];
extern struct Flag3 lbl_03002EE0[16];
extern u32 lbl_03002750;
extern u32 lbl_03003090;
extern u32 lbl_03003094;
extern u32 lbl_030032F4;
extern u8 lbl_0203D800[];

int fn_02002FAC(void);
u16 fn_02002130(s32 n, u8 *data, u16 *crc);
void *fn_0201A73C(int);
void fn_020007D8(s32);
void fn_02000990(void);
void fn_02000B98(void);
void fn_02005844(void);
void fn_0200EB80(void);
void fn_0200F010(int);
void fn_02010F88(int);
void fn_02017E48(int);
void fn_02019310(int);
void fn_0201A6C8(int);
void fn_02009508(int);
void fn_0200A63C(void);

void fn_02004668(void);
int fn_02004AC4(u8 *p);
int fn_02004CC8(int);
int fn_02004E00(int);

int fn_02004030(int idx, int pos)
{
    int sum;
    int i;
    struct ObjEntry *e;
    s8 *p;

    if (!(lbl_03002AEC & 1))
        return 0;

    p = (s8 *)((u8 *)lbl_03001970 + (lbl_03002670.unk1C - lbl_03002670.unk14));
    e = lbl_03001970;
    sum = 0;
    for (i = 0; i < idx; i++, e++)
        sum += e->unk1;
    sum += pos;
    p += sum >> 1;
    if (sum & 1)
        return *p & 0xF;
    else
        return *p >> 4;
}

void fn_02004098(int idx, int bank, int mode, int frame)
{
    struct ObjEntry *e;
    int size;
    u32 dest;
    u32 pal;
    u8 *src;

    if (idx == 17)
        frame = fn_02002FAC();
    if (!(lbl_03002AEC & 1))
        return;

    e = &lbl_03001970[idx];
    size = lbl_0202FA20[e->unk0] / 32 * 32;
    size *= e->unk1;
    if (bank == 0) {
        dest = 0;
        pal = 0x05000140;
    } else if (bank == 1) {
        dest = 0x400;
        pal = 0x05000160;
    } else if (bank == 2) {
        dest = 0x800;
        pal = 0x05000180;
    } else if (bank == 3) {
        dest = 0xC00;
        pal = 0x050001A0;
    } else {
        dest = 0x6000;
        pal = 0x050001C0;
    }
    if (frame < 0)
        pal = 0x05000020;
    dest += 0x80;
    if (mode <= 1)
        dest += 0x06000000;
    else
        dest += 0x06008000;
    DmaSet3(e->unk8, dest, 0x80000000 | (size >> 1));

    src = lbl_03002AC4 == 0 ? (u8 *)lbl_03001970 + (lbl_03002670.unk18 - lbl_03002670.unk14)
                            : lbl_02036A30[lbl_03002670.unkD];
    if (frame < 0) {
        size = e->unk4 * 32;
        src += e->unk3 * 32;
    } else {
        size = 32;
        src += (e->unk3 + frame) * 32;
    }
    DmaSet3(src, pal, 0x80000000 | (size >> 1));
}

void fn_020041D4(int idx, int frame)
{
    struct ObjEntry *e;
    int count;
    u16 used;
    int i;
    u8 *src;
    u32 dest;

    if (idx == 17)
        frame = fn_02002FAC();
    if (!(lbl_03002AEC & 1))
        return;

    e = &lbl_03001970[idx];
    if (e->unk5)
        return;

    count = 1;
    if (frame < 0)
        count = e->unk4;

    used = 0;
    for (i = 3; i < lbl_03002670.unkC; i++) {
        if (i != idx && lbl_03001970[i].unk5)
            used |= 1 << (lbl_03001970[i].unk2 >> 4);
    }

    e = &lbl_03001970[idx];
    for (i = lbl_03002670.unkD; i <= 15; i++) {
        if (!((used >> i) & 1))
            break;
    }
    e->unk2 = (i << 4) | 1;
    e->unk5 = 1;

    src = lbl_03002AC4 == 0 ? (u8 *)lbl_03001970 + (lbl_03002670.unk18 - lbl_03002670.unk14)
                            : lbl_02036A30[lbl_03002670.unkD];
    if (frame < 0)
        src += e->unk3 * 32;
    else
        src += (e->unk3 + frame) * 32;
    dest = 0x05000200 + i * 32;
    DmaSet3(src, dest, 0x80000000 | (count * 16));
    lbl_03002738[idx - 3] = count;
}

void fn_02004320(int idx)
{
    struct ObjEntry *e;

    if ((lbl_03002AEC & 1) && idx > 2) {
        e = lbl_03001970;
        e += idx;
        e->unk2 = 0xFF;
        e->unk5 = 0;
        lbl_03002738[idx - 3] = 0;
    }
}

void fn_02004360(void)
{
    int i;

    for (i = 3; i <= 20; i++)
        fn_02004320(i);
    memset(lbl_03002738, 0, 18);
}

void fn_02004384(void)
{
    DmaSet3(lbl_03001168[(s8)(lbl_03002690 ^ 1)], 0x07000000, 0x84000100);
}

void fn_020043B8(void)
{
    u8 *src;
    int size;

    src = lbl_03002AC4 == 0 ? lbl_03002070 : lbl_02036A30[0];
    size = lbl_03002670.unkD * 32;
    DmaSet3(src, 0x05000200, 0x80000000 | (size >> 1));
}

void fn_020043FC(void)
{
    int i;

    memset(&lbl_03002CA0, 0, sizeof(lbl_03002CA0));
    memset(lbl_03002FD0, 0, sizeof(lbl_03002FD0));
    memset(&lbl_03003000, 0, sizeof(lbl_03003000));
    memset(&lbl_03002B10, 0, sizeof(lbl_03002B10));
    memset(lbl_03002F20, 0, sizeof(lbl_03002F20));
    memset(lbl_03002DCC, 0xFF, sizeof(lbl_03002DCC));
    lbl_03002770 = 0;
    lbl_03002ED0 = 1;
    lbl_03002FF0 = 1;
    lbl_03002B00 = 0;
    lbl_03002C98 = 0;
    for (i = 0; i < 2; i++) {
        lbl_03002754[i] = 0;
        lbl_03002758[i] = 0;
    }
    for (i = 0; i < 8; i++)
        lbl_03003080[i] |= 0xFF;
    for (i = 0; i < 4; i++)
        lbl_03002FD0[i].unk0 = fn_0201A73C(0);
    for (i = 0; i < 8; i++)
        lbl_03002CA0.unkF4[i] |= 0xFFFF;
    lbl_03002CA0.unk5D = 8;
    for (i = 0; i < 4; i++)
        lbl_03002CA0.unk5E[i] |= 0xFF;
    fn_02004668();
}

void fn_02004514(u32 data)
{
    struct Cmd *cmd = (struct Cmd *)&data;
    u8 type = cmd->unk0 & 0xC0;
    u8 idx = cmd->unk1 & 0x3F;
    s16 val = cmd->unk2;

    if (type != 0)
        return;

    lbl_03002CA0.unk64[idx] = val;
    if (lbl_03003094 == 0) {
        if (lbl_03003090 == 1)
            fn_0200EB80();
        else if (lbl_03003090 == 2 && lbl_030032F4 == 1)
            fn_02010F88(idx);
    } else if (lbl_03003094 == 2) {
        if (lbl_03003090 == 2 && lbl_030032F4 == 1)
            fn_02017E48(idx);
    } else if (lbl_03003094 == 3) {
        if (val > 0)
            fn_02019310(idx);
    }
}

void fn_020045B4(u16 x, u16 y)
{
    lbl_03002754[0] = x;
    lbl_03002754[1] = y;
    if (!(lbl_03002AEC & 0x400)) {
        lbl_03002AEC |= 0x400;
        lbl_03002758[0] = x;
        lbl_03002758[1] = y;
    }
}

void fn_020045F4(u16 *x, u16 *y)
{
    *x = lbl_03002754[0];
    *y = lbl_03002754[1];
}

void fn_02004604(u16 *dx, u16 *dy)
{
    u16 flag = lbl_03002AEC & 0x400;

    if (!flag) {
        *dx = flag;
        *dy = flag;
        lbl_03002758[0] = lbl_03002754[0];
        lbl_03002758[1] = lbl_03002754[1];
    } else {
        *dx = lbl_03002754[0] - lbl_03002758[0];
        *dy = lbl_03002754[1] - lbl_03002758[1];
        lbl_03002758[0] = lbl_03002754[0];
        lbl_03002758[1] = lbl_03002754[1];
    }
}

void fn_02004668(void)
{
    memset(lbl_03002760, 0, sizeof(lbl_03002760));
    memset(lbl_03002DD0, 0, sizeof(lbl_03002DD0));
    memset(lbl_03002EE0, 0, sizeof(lbl_03002EE0));
}

void fn_0200469C(s8 *p)
{
    struct Flag3 *e = lbl_03002760;
    u8 flags = p[1];

    e[0].unk0 = p[1] & 1;
    e[0].unk1 = p[2];
    e[0].unk2 = p[3];
    p += 4;
    e[1].unk0 = (flags >> 1) & 1;
    e[1].unk1 = p[1];
    e[1].unk2 = p[2];
    e[2].unk0 = (flags >> 2) & 1;
    e[2].unk1 = p[3];
    p += 4;
    e[2].unk2 = p[1];
    e[3].unk0 = (flags >> 3) & 1;
    e[3].unk1 = p[2];
    e[3].unk2 = p[3];
}

struct Flag3 *fn_020046F0(int idx)
{
    return &lbl_03002760[idx];
}

void fn_020046FC(s8 *p)
{
    int idx = p[1] & 0x7F;

    lbl_03002DD0[idx].unk0 = p[1] >> 7;
    lbl_03002DD0[idx].unk1 = p[2];
    lbl_03002DD0[idx].unk2 = p[3];
}

void fn_0200471C(s8 *p)
{
    int idx = (p[1] & 0x7F) - 64;

    lbl_03002EE0[idx].unk0 = p[1] >> 7;
    lbl_03002EE0[idx].unk1 = p[2];
    lbl_03002EE0[idx].unk2 = p[3];
}

void fn_02004740(u8 *p)
{
    int i;
    int n;
    u8 *dst;

    memset(&lbl_03002CA0, 0, sizeof(lbl_03002CA0));
    memset(lbl_03002FD0, 0, sizeof(lbl_03002FD0));
    memset(lbl_03002CA0.unk64, 0xFF, sizeof(lbl_03002CA0.unk64));
    memset(lbl_03002CA0.unkE4, 0xFF, sizeof(lbl_03002CA0.unkE4));
    memset(lbl_03002CA0.unk5E, 0xFF, sizeof(lbl_03002CA0.unk5E));
    for (i = 0; i < 4; i++) {
        lbl_03002FD0[i].unk4 |= 0xFFFF;
        lbl_03002FD0[i].unk0 = fn_0201A73C(0);
    }

    memcpy(&lbl_03003000, p, sizeof(lbl_03003000));
    p += sizeof(lbl_03003000);
    for (i = 0; i < 8; i++) {
        n = lbl_03003000.slots[i >> 1];
        if (i & 1)
            n &= 15;
        else
            n = (n & 0xF0) >> 4;
        if (n != 15)
            lbl_03002FD0[n].unk4 = i;
    }
    for (i = 0; i < 4; i++) {
        n = (s16)lbl_03002FD0[i].unk4;
        if (n != -1)
            lbl_03002FD0[i].unk0 = lbl_03003000.entries[n];
        lbl_03002FD0[i].unk6 = p[0];
        lbl_03002FD0[i].unk7 = p[1];
        p += 2;
    }

    lbl_03002CA0.unk0 = *p++;
    memcpy(lbl_03002CA0.unk1, p, 3);
    p += 3;
    dst = lbl_03002CA0.unk62;
    for (i = 2; i != 0; i--)
        *dst++ = *p++;

    n = fn_02004AC4(p);
    p += n;
    memcpy(lbl_03002CA0.unk54, p, 8);
    p += 8;
    dst = lbl_03002CA0.unk104.bytes;
    for (i = 4; i != 0; i--)
        *dst++ = *p++;

    n = lbl_03002CA0.unk0 & 3;
    if (n != lbl_03002770) {
        fn_020007D8(n);
        lbl_03002770 = n;
    }
    if (lbl_03003090 <= 5) {
        fn_02005844();
        fn_02000990();
    }
}

void fn_020048B4(s8 *p)
{
    int i;
    struct Member *m;

    for (i = 0, m = lbl_03002FD0; i < 4; m++, i++) {
        if (i == fn_02002FAC()) {
            if ((p[1] & 0x80) && m->unk7 > p[2])
                fn_02000B98();
            m->unk7 = p[2];
        } else if ((p[1] >> i) & 1) {
            m->unk7 = m->unk6;
        } else {
            m->unk7 = 0;
        }
    }
    lbl_03002CA0.unk128 = p[3];
}

void fn_02004920(u8 *p)
{
    int i;
    u32 val;
    struct MarkerEntry *e;

    memset(&lbl_03002B10, 0, sizeof(lbl_03002B10));
    lbl_03002B10.count = *p++;
    val = p[0];
    val |= p[1] << 8;
    val |= p[2] << 16;
    val |= p[3] << 24;
    p += 4;
    lbl_03002B10.unk4 = val;
    for (i = 0; i < lbl_03002B10.count; i++) {
        e = &lbl_03002B10.entries[i];
        e->unk0 = *p++;
        e->unk4 = *p++;
        e->unk4 |= *p++ << 8;
        e->unk6 = *p++;
        e->unk6 |= *p++ << 8;
        e->unk8 = *p++;
        e->unk8 |= *p++ << 8;
        e->unkA = *p++;
        e->unkA |= *p++ << 8;
    }
}

void fn_020049B8(u8 *p)
{
    u8 *prev;
    u16 sum;
    u16 crc;
    u32 val;

    if ((p[0] >> 6) == 0) {
        lbl_03002750 = *(u32 *)p;
        return;
    }
    prev = (u8 *)&lbl_03002750;
    sum = prev[1] | (prev[2] << 8);
    val = prev[3];
    val |= p[1] << 8;
    val |= p[2] << 16;
    val |= p[3] << 24;
    crc = 0xFFFF;
    if (fn_02002130(4, (u8 *)&val, &crc) == sum)
        lbl_03002B10.unk4 = val;
}

void fn_02004A30(u8 *p)
{
    int i;

    memcpy(lbl_03002CA0.unk64, p, sizeof(lbl_03002CA0.unk64));
    p += sizeof(lbl_03002CA0.unk64);
    memcpy(lbl_03002CA0.unk114, lbl_03002CA0.unk108, 12);
    memcpy(lbl_03002CA0.unk108, p, 12);
    p += 12;
    memcpy(lbl_03002CA0.unk120, p, 8);
    p += 8;
    for (i = 0; i < 4; i++)
        lbl_03002CA0.unk5E[i] = *p++;
    memcpy(lbl_03002CA0.unkF4, p, 16);
    lbl_03002CA0.unk5D = p[16];
}

void fn_02004AA0(u8 *p)
{
    memcpy(lbl_03002CA0.unk54, p, 8);
}

void fn_02004AB4(u32 val)
{
    lbl_03002CA0.unk104.word = val;
}

int fn_02004AC4(u8 *p)
{
    int n;
    int size;
    int i;
    int len;

    lbl_03002CA0.unk129 = *p++;
    n = *p++;
    size = 2;
    memset(lbl_03002CA0.unk4, 0, 8);
    memset(lbl_03002CA0.names, 0, sizeof(lbl_03002CA0.names));
    for (i = 0; i < n; i++) {
        lbl_03002CA0.unk4[i] = *p++;
        lbl_03002CA0.unk8[i] = *p++;
    }
    size += n * 2;
    for (i = 0; i < n; i++) {
        len = strlen(p);
        strcpy(lbl_03002CA0.names[i], p);
        p += len + 1;
        size += len + 1;
    }
    return size;
}

void fn_02004B68(u8 *p)
{
    int i;
    int size;
    int n;

    for (i = 0; i < 4; i++)
        lbl_03002CA0.unk5E[i] = *p++;
    n = *p;
    size = n + 1;
    if (size & 3)
        size = ((size >> 2) + 1) << 2;
    size += n * 8;
    memcpy(lbl_0203D800, p, size);
    lbl_03002AEC |= 0x10;
}

void fn_02004BB8(u32 data)
{
    struct Cmd8 *cmd = (struct Cmd8 *)&data;
    u8 idx = cmd->unk1;
    u8 val = cmd->unk2;

    lbl_03002CA0.unk5E[idx] = val;
}

void fn_02004BD4(u32 data)
{
    struct Cmd *cmd = (struct Cmd *)&data;
    s8 idx = cmd->unk1;
    u16 val = cmd->unk2;

    lbl_03002CA0.unkF4[idx] = val;
    if (lbl_03003090 == 1)
        fn_0200F010(idx);
    else if (lbl_03003090 == 2)
        fn_02010F88((s16)val);
}

void fn_02004C1C(u32 data)
{
    struct Cmd8 *cmd = (struct Cmd8 *)&data;
    u8 idx = cmd->unk1;
    u8 val = cmd->unk2;

    lbl_03002CA0.unk120[idx] = (val != 0xFF) ? val + 159 : -1;
    if (lbl_03003090 == 1)
        fn_0200EB80();
    else if (lbl_03003090 == 5)
        fn_0201A6C8(idx);
}

void fn_02004C74(char *s)
{
    memset(lbl_03002F20, 0, sizeof(lbl_03002F20));
    strcpy(lbl_03002F20[0], s);
    s += strlen(s);
    s++;
    strcpy(lbl_03002F20[1], s);
}

int fn_02004CAC(int idx)
{
    return fn_02004CC8(lbl_03002CA0.unk64[idx]);
}

int fn_02004CC8(int val)
{
    int level;

    if (val <= 0)
        level = 0;
    else if (val <= 158)
        level = 1;
    else if (val <= 255)
        level = 2;
    else if (val <= 292)
        level = 3;
    else if (val == 293)
        level = 4;
    else if (val <= 297)
        level = 5;
    else if (val <= 380)
        level = 6;
    else if (val <= 392)
        level = 7;
    else if (val <= 400)
        level = 8;
    else
        level = 9;
    return level;
}

int fn_02004D3C(int id)
{
    int i;

    if (id < 64 && lbl_03002CA0.unk64[id] <= 0)
        return 0;
    for (i = 2; i < 8; i++) {
        if ((s16)lbl_03002CA0.unkF4[i] == id)
            return 1;
    }
    if (id < 64)
        return fn_02004E00(id);
    return 0;
}

void fn_02004D88(u32 data)
{
    struct Cmd8 *cmd = (struct Cmd8 *)&data;

    lbl_03002CA0.unk5C = cmd->unk2;
}

int fn_02004DA0(u16 *p)
{
    int a = *p & 0xF;
    int b = *p & 0x30;
    int mask = 1 << (lbl_03002CA0.unk0 & 3);
    int mask2 = (lbl_03002CA0.unk0 & 0x80) ? 32 : 16;

    if (a) {
        if (b) {
            a &= mask;
            return a && (b & mask2);
        }
        return (a & mask) != 0;
    }
    return (b & mask2) != 0;
}

int fn_02004E00(int id)
{
    int i;

    for (i = 0; i < 4; i++) {
        if ((s8)lbl_03002CA0.unk5E[i] == id)
            break;
    }
    return i < 4;
}

void fn_02004E38(u32 data)
{
    struct Cmd8 *cmd = (struct Cmd8 *)&data;
    int i;
    u8 *p = &cmd->unk1;

    for (i = 0; i < 3; i++)
        lbl_03002CA0.unk1[i] = *p++;
    if (lbl_03003090 <= 3)
        fn_02009508(0);
}

int fn_02004E74(int id)
{
    if (id == 9 || id == 10 || id == 12)
        return -1;
    return 0;
}

void fn_02004E90(u8 *p)
{
    memcpy(lbl_03002CA0.unk114, lbl_03002CA0.unk108, 12);
    memcpy(lbl_03002CA0.unk108, p, 12);
    if (lbl_03003090 == 4)
        fn_0200A63C();
    else if (lbl_03003090 == 1)
        fn_0200EB80();
}

void fn_02004ED4(u8 *p)
{
    memcpy(lbl_03002CA0.unk120, p, 8);
}

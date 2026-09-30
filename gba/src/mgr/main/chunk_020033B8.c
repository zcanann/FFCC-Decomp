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

#define DmaFill32_3(value, dest, size)                       \
    {                                                        \
        vu32 tmp = (vu32)(value);                            \
        DmaSet3(&tmp, dest, 0x85000000 | ((size) / 4));      \
    }

struct Vec3 {
    s16 x;
    s16 y;
    s16 z;
};

struct PathNode {
    s16 x;
    s16 z;
    u8 unk4[4];
    s8 speedType;
    u8 unk9[7];
};

struct Path {
    s16 count;
    u16 unk2;
    struct PathNode *nodes;
};

struct Map {
    u8 (*tiles)[256];
};

struct TileInfo {
    u16 flags;
    u16 unk2;
};

struct SpeedInfo {
    s16 value;
    u16 unk2;
};

struct ActorData {
    u8 unk0[0xE];
    u8 unkE;
    u8 unkF;
    u8 unk10[4];
};

struct Actor {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 unk6[4];
    u8 unkA;
    u8 unkB;
    u8 unkC[0xC];
    struct ActorData *unk18;
    s16 unk1C;
    s16 unk1E;
    u16 unk20;
    u8 unk22[2];
    s16 unk24;
    u16 unk26;
    u8 unk28[8];
    u16 unk30;
    u16 unk32;
    u16 unk34;
    u8 unk36[2];
    struct Vec3 vel;
    s16 speed;
    u16 unk42;
    u16 unk44;
    u8 unk46[2];
    s16 unk48;
    u8 unk4A;
    u8 unk4B;
    u8 unk4C;
    u8 unk4D;
    u8 unk4E;
    u8 unk4F;
    u8 unk50;
    u8 unk51;
    u8 unk52;
    u8 unk53;
    u8 unk54;
    u8 unk55_0 : 1;
    u8 unk55_1 : 1;
    u8 unk55_2 : 1;
    u8 unk55_3 : 1;
    u8 unk55_4 : 1;
    u8 unk56[2];
};

struct Pos {
    s16 x;
    s16 y;
};

struct Game {
    u8 unk0[0x8C];
    u8 unk8C[8][16];
};

struct Effect {
    s16 x;
    s16 y;
    s16 z;
    u8 unk6[6];
    u8 unkC;
    u8 unkD;
    u8 unkE[2];
};

struct Obj {
    u8 unk0[0xA];
    u8 unkA;
    u8 unkB[0xE];
    u8 unk19;
    u8 unk1A[0x22];
};

struct Node {
    struct Node *next;
    u32 data[2];
};

struct Scene {
    struct Actor actors[12];
    struct Obj objs[64];
    u8 unk1320[0xC];
    u8 unk132C[0xC];
    struct Table *objTable;
    struct Table *animTable;
    struct Node *lists[40];
    struct Node nodes[128];
    struct Node *freeNode;
    u8 unk19E4;
    u8 unk19E5;
    u8 enemyCount;
    u8 actorCount;
};

struct OamData {
    u16 y : 8;
    u16 affineMode : 2;
    u16 objMode : 2;
    u16 mosaic : 1;
    u16 bpp : 1;
    u16 shape : 2;
    u16 x : 9;
    u16 matrixNum : 5;
    u16 size : 2;
    u16 tileNum : 10;
    u16 priority : 2;
    u16 paletteNum : 4;
    u16 affineParam;
};

struct OamMatrix {
    s16 a;
    s16 b;
    s16 c;
    s16 d;
};

struct SpriteDef {
    u16 count;
    u16 pad;
    struct OamData oam[1];
};

struct Table {
    u32 count;
    u32 offsets[0];
};

struct Chunk {
    u32 id;
    u32 size;
};

struct ChunkReader {
    u8 unk0[0x14];
};

struct EffectDef {
    s16 x;
    s16 y;
    s16 z;
    s16 type;
};

struct Work {
    u8 unk0[4];
    u8 unk4;
    u8 unk5[0x3C];
    vu8 unk41;
    u8 unk42[2];
};

struct Frame {
    u16 x;
    u16 y;
};

struct Anim {
    u32 unk0;
    struct Frame *unk4;
};

extern struct Scene lbl_0202C618;
extern vu8 lbl_03005D65;
extern struct ActorData lbl_020102E8[];
extern char lbl_0200EDAC[];
extern u8 lbl_030063C8[];
extern u8 lbl_030063E0[];
extern s16 lbl_0201C320;
extern u8 lbl_0202DFFC;
extern struct OamData lbl_03004C48[];
extern struct OamMatrix lbl_03005048[];
extern struct EffectDef lbl_02014018[];
extern u8 lbl_02017404[];
extern u8 lbl_020182F4[];
extern u8 lbl_0201C19C[];
extern u8 lbl_02038000[];
extern u8 lbl_030060F4;
extern u8 lbl_030060F5;
extern u32 lbl_03005250;
extern struct Map lbl_03006144;
extern struct TileInfo lbl_02013C14[];
extern struct SpeedInfo lbl_02010230[];
extern struct Work lbl_03000000;
extern u8 lbl_03005D67;
extern struct Effect lbl_03005DF4[];
extern const u16 lbl_02014014;
extern s16 lbl_0200EE10[];
extern struct Game lbl_03005C78;
extern s16 lbl_0201C304;
extern s16 lbl_0201C306;
extern u16 lbl_0201C308[];

void fn_020001A0();
void fn_02002CD0(struct Actor *);
void fn_02002B88(void *);
void fn_02002794(struct Actor *);
void fn_02002BA0(struct Actor *);
void fn_02002D0C(struct Actor *);
void LZ77UnCompWram(const void *, void *);
void fn_020075A8(struct ChunkReader *);
void fn_020075BC(struct ChunkReader *, const void *);
u8 fn_020075E4(struct ChunkReader *, struct Chunk *);
void *fn_0200762C(struct ChunkReader *);
s32 Sqrt(s32);
struct Actor *fn_02004218(struct Scene *, struct Vec3 *, u8, u32);
void fn_0200411C(struct Scene *, struct Vec3 *, struct Actor *);
void fn_02005C6C(struct Obj *);
u16 fn_02002860(struct Actor *);
void fn_020026B8(void *, u8, u8);
void fn_02004CAC(void *, s32, void *);
void fn_02004D1C(void *, s32, struct Actor *, s32, s32, s32);
void fn_02004828(void *, s32, struct Pos *, s32);
struct Path *fn_02006B68(void *, u8);
struct Anim *fn_02006EFC(void *, s32);
s32 fn_02006E74(struct Path *, u8, s16, s16);
u8 fn_02006DF0(struct Path *, u8, s16, s16);
u8 fn_02002928(struct Actor *, struct Vec3 *, u8 *, s16 *, s16 *, s16 *, s16 *, s32 *);
void fn_02006A38(struct Map *, struct Vec3 *, struct Vec3 *, s16 *);
void fn_02002700(void *);
void fn_02002A88(struct Actor *);
s16 ArcTan2(s16, s16);
void m4aSongNumStart(u16);
void CpuFastSet(void *, void *, u32);

void fn_020033B8(struct Actor *actor)
{
    fn_02002CD0(actor);
    fn_02002B88(actor);
    if (actor->unk55_2) {
        fn_02004CAC(&lbl_0202C618, 28, actor);
    } else if (actor->unk55_3) {
        fn_02004CAC(&lbl_0202C618, 29, actor);
    }
    if (lbl_03005D65 != actor->unk52) {
        fn_02004CAC(&lbl_0202C618, actor->unk52 + 22, actor);
    } else if (actor->unk55_4) {
        fn_02004D1C(&lbl_0202C618, actor->unk52 + 22, actor, -6, -8, -1);
    }
}

void fn_02003454(struct Actor *a, struct Actor *b, s32 id)
{
    struct Pos pos;
    s32 diff;
    u16 depth;
    u16 da;
    s16 *pa;
    s16 *pb;

    da = fn_02002860(a);
    diff = (s16)da - (s16)fn_02002860(b);
    depth = diff;
    if ((u16)(depth - 1) <= 18) {
        pa = &a->unk48;
        pb = &b->unk48;
        pos.x = ((*pa - *pb) >> 6) + 120;
        if (pos.x >= -16 && pos.x <= 256) {
            (&pos)->y = 150;
            fn_02004828(&lbl_0202C618, id, &pos, 0);
        }
    }
}

void fn_020034DC(struct Actor *actor, u8 type)
{
    s32 n;
    struct Frame *frame;

    actor->unk4B = 0;
    fn_02002794(actor);
    actor->unk18 = &lbl_020102E8[type];
    if (actor->unk18->unkE > 1) {
        fn_020001A0(lbl_0200EDAC, 0x428);
    }
    actor->unk4E = actor->unk18->unkE + 1;
    n = fn_02006B68(lbl_030063C8, actor->unk4E)->count;
    actor->unk50 = n;
    actor->unk4F = n - 1;
    fn_02002BA0(actor);
    actor->unk26 = (lbl_0201C320 << 15) / 180;
    actor->unk52 = type + 4;
    actor->unk2 = 0;
    frame = &fn_02006EFC(lbl_030063E0, 0)->unk4[lbl_0202DFFC % 8];
    actor->unk0 = frame->x;
    actor->unk4 = frame->y;
    if (actor->unk18->unkF <= 3) {
        fn_020026B8(actor->unkC, 0, actor->unk18->unkF);
    } else {
        fn_020026B8(actor->unkC, 0, actor->unk18->unkF + 8);
    }
}

static inline void Vec3Add(struct Vec3 *dst, struct Vec3 *src)
{
    dst->x += src->x;
    dst->y += src->y;
    dst->z += src->z;
}

static inline s32 IsTileWalkable(struct Map *map, struct Vec3 *pos)
{
    s32 x = pos->x + 0x4000;
    s32 z = pos->z + 0x4000;
    struct TileInfo *info = &lbl_02013C14[map->tiles[z >> 7][x >> 7]];

    return info->flags & 2;
}

void fn_020035B8(struct Actor *actor)
{
    u8 height;
    s16 targetY;
    s16 minSpeed;
    s16 range;
    s16 targetSpeed;
    struct Vec3 target;
    s32 maxDist;
    struct Vec3 left;
    struct Vec3 right;
    struct Vec3 accel;
    struct Pos dir;
    struct Vec3 next;
    struct Path *path;
    struct PathNode *node;
    struct PathNode *nextNode;
    u16 nextPos;
    u8 nextIndex;
    s16 idx;
    s16 dx;
    s16 dz;
    s16 ex;
    s16 ez;
    s16 len;
    u16 dist;
    s16 px;
    s16 pz;
    s16 lx;
    s16 lz;
    s16 rx;
    s16 rz;
    s32 leftDot;
    s32 sq;
    s16 delta;

    if (lbl_03000000.unk4 <= 2) {
        fn_02002700(actor->unkC);
        return;
    }
    actor->unk55_3 = 0;
    actor->unk55_2 = 0;
    path = fn_02006B68(lbl_030063C8, actor->unk4E);
    actor->unk4F = fn_02006DF0(path, actor->unk4F, actor->unk0, actor->unk4);
    if (actor->unk4F == 0xFF) {
        fn_020001A0(lbl_0200EDAC, 0x468);
    }
    if ((s16)(nextPos = actor->unk4F + 1) >= path->count) {
        idx = 0;
    } else {
        idx = nextPos;
    }
    nextIndex = idx;
    node = &path->nodes[actor->unk4F];
    nextNode = &path->nodes[nextIndex];
    dx = nextNode->x - actor->unk0;
    dz = nextNode->z - actor->unk4;

    if ((actor->unk54 != 0 || (lbl_03005250 & 1) == (actor->unk52 & 1))
        && fn_02002928(actor, &target, &height, &targetY, &minSpeed, &range, &targetSpeed, &maxDist)
        && actor->speed > minSpeed
        && (u8)(height - actor->unk4A) <= 5) {
        delta = actor->unk48 - targetY;
        if (delta < 0) {
            delta = -delta;
        }
        if (delta < range) {
            ex = target.x - actor->unk0;
            ez = target.z - actor->unk4;
            sq = ex * ex + ez * ez;
            if (sq < maxDist && ex * dx + ez * dz > 0) {
                sq = dx * dx + dz * dz;
                dist = Sqrt(sq);
                px = dx * targetSpeed / dist;
                pz = dz * targetSpeed / dist;
                if (actor->unk54 == 0) {
                eval:
                    left.x = target.x + pz;
                    (&left)->z = target.z - px;
                    lx = left.x - actor->unk0;
                    lz = left.z - actor->unk4;
                    leftDot = (actor->vel.x * lx + actor->vel.z * lz) / (s16)Sqrt(lx * lx + lz * lz);
                    right.x = target.x - pz;
                    (&right)->z = px + target.z;
                    rx = right.x - actor->unk0;
                    rz = right.z - actor->unk4;
                    if (leftDot > (actor->vel.x * rx + actor->vel.z * rz) / (s16)Sqrt(rx * rx + rz * rz)) {
                        if (IsTileWalkable(&lbl_03006144, &left)) {
                            actor->unk54 = 1;
                            dx = lx;
                            dz = lz;
                        } else {
                            actor->unk54 = 2;
                            dx = rx;
                            dz = rz;
                        }
                    } else {
                        if (IsTileWalkable(&lbl_03006144, &right)) {
                            actor->unk54 = 2;
                            dx = rx;
                            dz = rz;
                        } else {
                            actor->unk54 = 1;
                            dx = lx;
                            dz = lz;
                        }
                    }
                } else {
                    if (actor->unk54 == 1) {
                        left.x = pz + target.x;
                        left.z = target.z - px;
                        dx = left.x - actor->unk0;
                        dz = left.z - actor->unk4;
                        if (!IsTileWalkable(&lbl_03006144, &left)) {
                            goto eval;
                        }
                    } else {
                        right.x = target.x - pz;
                        right.z = px + target.z;
                        dx = right.x - actor->unk0;
                        dz = right.z - actor->unk4;
                        if (!IsTileWalkable(&lbl_03006144, &right)) {
                            goto eval;
                        }
                    }
                }
                goto move;
            }
        }
    }
    actor->unk54 = 0;
move:
    (&accel)->x = (&accel)->y = (&accel)->z = 0;
    len = Sqrt(dx * dx + dz * dz);
    if (len != 0) {
        s16 friction;
        s16 turn;
        s16 brake;
        s16 limit;
        u16 angle;
        s16 sin;
        s16 cos;
        s32 speed;
        s16 maxSpeed;
        u16 newSpeed;
        s32 force;

        if (actor->vel.x != 0 || actor->vel.z != 0) {
            actor->unk26 = ArcTan2(actor->vel.z, actor->vel.x);
        }
        actor->unk44 = actor->unk26;
        actor->unk42 = actor->unk26;
        dir.x = (dx << 8) / len;
        (&dir)->y = (dz << 8) / len;
        if (actor->unk32 != 0) {
            angle = actor->unk30;
            sin = lbl_0200EE10[angle >> 5];
            cos = lbl_0200EE10[(angle >> 5) + 0x200];
            dir.x = (cos * dir.x - sin * dir.y) >> 8;
            dir.y = (dir.x * sin + dir.y * cos) >> 8;
            actor->unk32--;
        }
        friction = actor->unk20;
        if (actor->unk55_1) {
            friction = 0;
        }
        turn = actor->unk1C;
        brake = actor->unk1E;
        limit = actor->unk24;
        if (actor->unk55_0) {
            turn >>= 3;
            brake >>= 3;
            limit >>= 1;
        }
        (&accel)->x = (dir.x * turn) >> 8;
        (&accel)->z = (dir.y * turn) >> 8;
        Vec3Add(&actor->vel, &accel);
        speed = Sqrt(actor->vel.x * actor->vel.x + actor->vel.z * actor->vel.z);
        actor->speed = speed;
        maxSpeed = (limit * lbl_02010230[node->speedType].value) >> 8;
        if ((s16)speed > maxSpeed) {
            newSpeed = speed - brake;
            if ((s16)newSpeed < maxSpeed) {
                newSpeed = maxSpeed;
            }
            actor->vel.x = actor->vel.x * (s16)newSpeed / actor->speed;
            actor->vel.z = actor->vel.z * (s16)newSpeed / actor->speed;
            actor->speed = newSpeed;
        }
        force = friction * actor->speed;
        actor->vel.x = (((dir.x * force) >> 8) + actor->vel.x * (0x100 - friction)) >> 8;
        actor->vel.z = (((dir.y * force) >> 8) + actor->vel.z * (0x100 - friction)) >> 8;
    }
    next.x = (actor->vel.x >> 4) + actor->unk0;
    (&next)->y = actor->unk2;
    (&next)->z = (actor->vel.z >> 4) + actor->unk4;
    fn_0200411C(&lbl_0202C618, &next, actor);
    fn_02006A38(&lbl_03006144, &next, &actor->vel, &actor->speed);
    actor->unk0 += actor->vel.x >> 4;
    actor->unk4 += actor->vel.z >> 4;
    fn_02002700(actor->unkC);
    fn_02002A88(actor);
    actor->unk55_1 = 0;
    actor->unk55_0 = 0;
}

s32 fn_02003CA8(struct Actor *actor)
{
    struct Pos dir;
    struct Pos *p;
    u16 angle;

    if (actor->unk4C != 0xFF) {
        angle = actor->unk26;
        p = &dir;
        p->x = lbl_0200EE10[angle >> 5];
        p->y = lbl_0200EE10[(angle >> 5) + 0x200];
        return fn_02006E74(fn_02006B68(lbl_030063C8, actor->unk4B), actor->unk4C, p->x, p->y) <= 0;
    }
    return 0;
}

void fn_02003D14(struct Actor *actor, u8 state)
{
    if (lbl_03005D65 == actor->unk52) {
        m4aSongNumStart(9);
    }
    actor->unk53 = state;
}

void fn_02003D40(struct Actor *actor, u8 idx)
{
    u8 value;

    value = lbl_03005C78.unk8C[actor->unk52][idx];
    if (value >= lbl_0201C306) {
        if (lbl_03005D65 == actor->unk52) {
            m4aSongNumStart(15);
        }
        actor->unk55_2 = 1;
        actor->unk55_3 = 0;
        actor->unk34 = lbl_0201C308[(value - 1) / 10];
    } else if (value <= lbl_0201C304) {
        if (lbl_03005D65 == actor->unk52) {
            m4aSongNumStart(16);
        }
        actor->unk55_2 = 0;
        actor->unk55_3 = 1;
        actor->unk34 = lbl_0201C308[(value - 1) / 10];
    } else {
        m4aSongNumStart(18);
        actor->unk55_2 = 0;
        actor->unk55_3 = 0;
        actor->unk34 = 0;
    }
}

void fn_02003E14(struct Effect *effect)
{
    fn_02004CAC(&lbl_0202C618, effect->unkC, effect);
}

void fn_02003E28(struct Scene *scene)
{
    u32 zero;

    scene->unk19E4 = 0;
    scene->unk19E5 = 0;
    scene->enemyCount = 0;
    zero = 0;
    CpuFastSet(&zero, scene->objs, 0x010003C0);
    zero = 0;
    CpuFastSet(&zero, scene, 0x01000108);
    fn_020026B8(scene->unk1320, 46, 255);
    fn_020026B8(scene->unk132C, 50, 255);
}

void fn_02003E94(struct Scene *scene)
{
    struct ChunkReader reader;
    struct Chunk chunk;
    struct OamData *oam;
    struct SpriteDef *sprite;
    struct OamMatrix *matrix;
    struct Effect *effect;
    struct EffectDef *def;
    u32 i;
    s32 j;
    s32 k;
    u32 m;
    s32 n;
    u16 scale;
    s32 x;
    s32 y;
    s32 z;
    s32 type;

    LZ77UnCompWram(lbl_020182F4, lbl_02038000);
    DmaSet3(lbl_02038000, 0x06010000, 0x84002000);
    LZ77UnCompWram(lbl_0201C19C, lbl_02038000);
    DmaSet3(lbl_02038000, 0x05000200, 0x84000080);
    fn_020075A8(&reader);
    fn_020075BC(&reader, lbl_02017404);
    while (fn_020075E4(&reader, &chunk)) {
        switch (chunk.id) {
        case 0x4F424A20:
            scene->objTable = fn_0200762C(&reader);
            for (i = 0; i < scene->objTable->count; i++) {
                scene->objTable->offsets[i] = (u32)scene->objTable + scene->objTable->offsets[i];
                sprite = (struct SpriteDef *)scene->objTable->offsets[i];
                for (k = sprite->count - 1; k >= 0; k--) {
                    oam = &sprite->oam[k];
                    if (oam->objMode == 1) {
                        oam->priority = 2;
                    } else {
                        oam->priority = 1;
                    }
                }
            }
            break;
        case 0x414E494D:
            scene->animTable = fn_0200762C(&reader);
            for (m = 0; m < scene->animTable->count; m++) {
                scene->animTable->offsets[m] = (u32)scene->animTable + scene->animTable->offsets[m];
            }
            break;
        }
    }
    scene->enemyCount = 0;
    scene->unk19E5 = 0;
    scene->unk19E4 = 0;
    DmaFill32_3(0, lbl_03005048, sizeof(struct OamMatrix) * 32);
    matrix = lbl_03005048;
    for (j = 0; j < 28; j++) {
        scale = (0x100 - lbl_0200EE10[((j << 14) / 26 + 0x4000) >> 5]) * 2 + 0x100;
        matrix->d = scale;
        matrix->a = scale;
        matrix++;
    }
    matrix->d = 224;
    matrix->a = 224;
    matrix++;
    matrix->d = 192;
    matrix->a = 192;
    matrix++;
    matrix->d = 160;
    matrix->a = 160;
    matrix++;
    matrix->d = 128;
    matrix->a = 128;
    effect = lbl_03005DF4;
    for (n = 0; n < lbl_02014014; n++, effect++) {
        def = &lbl_02014018[n];
        if (def->type >= 72) {
            fn_020001A0(lbl_0200EDAC, 0x661);
        }
        x = def->x;
        y = def->y;
        z = def->z;
        type = def->type;
        effect->x = x;
        effect->y = y;
        effect->z = z;
        effect->unkC = type;
        effect->unkD = 0;
    }
    fn_02003E28(scene);
    lbl_03000000.unk41 = 0;
    lbl_030060F4 = 0xFF;
    lbl_030060F5 = 0xFF;
}

void fn_0200411C(struct Scene *scene, struct Vec3 *box, struct Actor *actor)
{
    struct Actor *other;
    s16 dx;
    s16 dz;
    s16 vx;
    s16 vz;
    s16 dist;
    s16 speed;
    s16 px;
    s16 pz;

    other = fn_02004218(scene, box, 100, -2 << actor->unk52);
    if (other != NULL) {
        if (actor->unk52 == lbl_03005D65 || other->unk52 == lbl_03005D65) {
            m4aSongNumStart(14);
        }
        dx = other->unk0 - actor->unk0;
        dz = other->unk4 - actor->unk4;
        vx = actor->vel.x - other->vel.x;
        vz = actor->vel.z - other->vel.z;
        dist = Sqrt(dx * dx + dz * dz);
        speed = Sqrt(vx * vx + vz * vz);
        px = dx * speed / dist;
        pz = dz * speed / dist;
        other->vel.x += px;
        other->vel.z += pz;
        actor->vel.x -= px;
        actor->vel.z -= pz;
    }
}

struct Actor *fn_02004218(struct Scene *scene, struct Vec3 *box, u8 size, u32 mask)
{
    struct Actor *actor;
    s32 i;
    u32 bit;
    s16 minX;
    s16 minY;
    s16 minZ;
    s16 maxX;
    s16 maxY;
    s16 maxZ;
    s16 lo;
    s16 hi;

    actor = scene->actors;
    minX = box->x - size;
    minY = box->y - size;
    minZ = box->z - size;
    maxX = box->x + size;
    maxY = box->y + size;
    maxZ = box->z + size;
    bit = 1;
    for (i = 0; i < scene->actorCount; i++, actor++, bit <<= 1) {
        if (actor->unkA && (mask & bit)) {
            lo = actor->unk0 - size;
            hi = actor->unk0 + size;
            if (minX < lo ? lo <= maxX : minX <= lo || minX <= hi) {
                lo = actor->unk4 - size;
                hi = actor->unk4 + size;
                if (minZ < lo ? lo <= maxZ : minZ <= lo || minZ <= hi) {
                    lo = actor->unk2 - size;
                    hi = actor->unk2 + size;
                    if (minY < lo ? lo <= maxY : minY <= lo || minY <= hi) {
                        return actor;
                    }
                }
            }
        }
    }
    return NULL;
}

struct Actor *fn_02004344(struct Scene *scene, struct Actor *target, s32 range, s32 *outDist, u32 mask)
{
    struct Actor *actor;
    struct Actor *nearest;
    s32 i;
    u32 bit;
    s32 min;
    s16 dx;
    s16 dy;
    s32 dist;
    s16 x;
    s16 y;

    min = -range;
    actor = scene->actors;
    nearest = NULL;
    bit = 1;
    x = target->unk0;
    y = target->unk4;
    for (i = 0; i < scene->actorCount; i++, actor++, bit <<= 1) {
        if (actor->unkA && (mask & bit)) {
            dx = actor->unk0 - x;
            if (dx < range && dx > min) {
                dy = actor->unk4 - y;
                if (dy < range && dy > min) {
                    dist = dx * dx + dy * dy;
                    if (dist < range && range > dist) {
                        range = dist;
                        min = -range;
                        nearest = actor;
                    }
                }
            }
        }
    }
    *outDist = range;
    return nearest;
}

struct Actor *fn_020043E8(struct Scene *scene, struct Actor *target, s32 range, u16 *outDist, s16 dirX, s16 dirZ, s16 minDot, u32 mask)
{
    struct Actor *nearest;
    struct Actor *actor;
    u32 bit;
    s16 x;
    s16 y;
    s32 i;
    s32 min;
    s16 dx;
    s16 dz;
    s32 dist;
    u16 root;
    s16 dot;

    min = -range;
    actor = scene->actors;
    nearest = NULL;
    bit = 1;
    x = target->unk0;
    y = target->unk4;
    for (i = 0; i < scene->actorCount; i++, actor++, bit <<= 1) {
        if (actor->unkA && (mask & bit)) {
            dx = actor->unk0 - x;
            if (dx < range && dx > min) {
                dz = actor->unk4 - y;
                if (dz < range && dz > min) {
                    dist = dx * dx + dz * dz;
                    if (dist < range && range > dist) {
                        root = Sqrt(dist);
                        dot = (dirX * dx + dirZ * dz) / (s16)root;
                        if (dot >= minDot) {
                            *outDist = root;
                            range = dist;
                            min = -range;
                            nearest = actor;
                        }
                    }
                }
            }
        }
    }
    return nearest;
}

u8 fn_020044F4(struct Scene *scene, s32 index)
{
    struct Actor *actor;
    u16 depth;
    u8 rank;
    s32 i;

    depth = fn_02002860(&scene->actors[index]);
    actor = scene->actors;
    rank = 1;
    for (i = 0; i < scene->actorCount; i++, actor++) {
        if (i != index && actor->unkA && fn_02002860(actor) > depth) {
            rank++;
        }
    }
    return rank;
}

void fn_0200455C(struct Scene *scene)
{
    s32 i; s32 j;

    if (scene->unk19E4) {
        for (i = 0; i < 4; i++) {
            if ((lbl_03005D67 >> i) & 1) {
                fn_02002D0C(&scene->actors[i]);
            }
        }
        for (j = 0; j < scene->enemyCount; j++) {
            fn_020035B8(&scene->actors[4 + j]);
        }
    }
    for (j = 0; j < 64; j++) {
        if (scene->objs[j].unkA) {
            fn_02005C6C(&scene->objs[j]);
        }
    }
}

void fn_020045DC(struct Scene *scene)
{
    s32 i;
    struct Effect *effect;
    u16 count;

    if (scene->unk19E4) {
        for (i = 0; i < 4; i++) {
            if ((lbl_03005D67 >> i) & 1) {
                fn_020033B8(&scene->actors[i]);
            }
        }
        for (i = 0; i < scene->enemyCount; i++) {
            fn_02002CD0(&scene->actors[4 + i]);
            fn_02002B88(&scene->actors[4 + i]);
        }
    }
    for (i = 0; i < 64; i++) {
        if (scene->objs[i].unkA && scene->objs[i].unk19) {
            fn_02002B88(&scene->objs[i]);
        }
    }
    effect = lbl_03005DF4;
    count = lbl_02014014;
    for (i = 0; i < count; i++, effect++) {
        fn_02003E14(effect);
    }
}

void fn_0200468C(struct Scene *scene)
{
    s16 i;

    DmaFill32_3(160, lbl_03004C48, 0x400);
    for (i = 0; i < 40; i++) {
        scene->lists[i] = NULL;
    }
    scene->freeNode = scene->nodes;
}

void fn_020046E8(struct Scene *scene)
{
    struct Node *node;
    struct OamData *oam;
    struct OamMatrix *matrix;
    s16 count;
    s16 i;
    s16 j;

    count = 0;
    for (i = 0; i < 40; i++) {
        for (node = scene->lists[i]; node != NULL; node = node->next) {
            oam = &lbl_03004C48[count++];
            DmaSet3(node->data, oam, 0x84000002);
        }
    }
    oam = lbl_03004C48;
    matrix = lbl_03005048;
    for (j = 0; j < 32; j++, matrix++) {
        oam->affineParam = matrix->a;
        oam++;
        oam->affineParam = matrix->b;
        oam++;
        oam->affineParam = matrix->c;
        oam++;
        oam->affineParam = matrix->d;
        oam++;
    }
    lbl_03000000.unk41 = 1;
}

void fn_020047AC(struct Scene *scene, struct Node *node, u16 index)
{
    if (index >= 40) {
        fn_020001A0(lbl_0200EDAC, 1999);
    }
    node->next = scene->lists[index];
    scene->lists[index] = node;
}

struct Node *fn_020047E4(struct Scene *scene, void *data)
{
    struct Node *node;

    if (scene->freeNode >= (struct Node *)&scene->freeNode) {
        fn_020001A0(lbl_0200EDAC, 2010);
    }
    node = scene->freeNode++;
    DmaSet3(data, node->data, 0x84000002);
    return node;
}

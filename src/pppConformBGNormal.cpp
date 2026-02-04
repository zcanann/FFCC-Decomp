#include "ffcc/pppConformBGNormal.h"
#include "types.h"
#include "dolphin/mtx.h"
#include "ffcc/game.h"
#include "dolphin/gx.h"

extern u32 DAT_8032ed70;
extern f32 FLOAT_80331908;
extern f32 FLOAT_8033190c;
extern f32 FLOAT_80331910;
extern f32 FLOAT_80331914;
extern f32 FLOAT_80331918;
extern f32 FLOAT_8033191c;

extern void* pppMngStPtr;
extern void* MapMng;

/*
 * --INFO--
 * PAL Address: 0x801097e4
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructConformBGNormal(struct pppConformBGNormal* conformBG, struct UnkC* param2)
{
    f32 fVar1;
    f32* pfVar2;
    
    fVar1 = FLOAT_80331908;
    pfVar2 = (f32*)((int)(&conformBG->field0_0x0 + 2) + *param2->m_serializedDataOffsets);
    pfVar2[2] = FLOAT_80331908;
    pfVar2[1] = fVar1;
    *pfVar2 = fVar1;
    *(u8*)(pfVar2 + 3) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801091d4
 * PAL Size: 1552b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameConformBGNormal(struct pppConformBGNormal* conformBG, struct UnkB* param2, struct UnkC* param3)
{
    // This is a complex function - implementing basic structure first
    if (DAT_8032ed70 == 0) {
        // Basic implementation stub
        // TODO: Full implementation requires more game state understanding
        return;
    }
}
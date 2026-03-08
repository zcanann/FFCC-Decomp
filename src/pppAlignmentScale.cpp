#include "ffcc/pppAlignmentScale.h"
#include "ffcc/partMng.h"

#include <dolphin/mtx.h>

extern unsigned char CameraPcs[];
extern float FLOAT_80331920;
extern float FLOAT_80331924;

extern "C" {
void* pppSetFpMatrix__FP9_pppMngSt(struct _pppMngSt*);
}

/*
 * --INFO--
 * PAL Address: 0x8010992c
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructAlignmentScale(pppAlignmentScale*, pppAlignmentScaleData*)
{
    return;
}

/*
 * --INFO--
 * PAL Address: 0x80109810
 * PAL Size: 284b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
struct pppAlignmentScale* pppFrameAlignmentScale(struct pppAlignmentScale* alignmentScale, struct pppAlignmentScaleData* data)
{
    float xS;
    struct _pppMngSt* pppMngSt;
    Vec cameraPos;
    Vec objPos;
    Mtx scaleMtx;

    if (gPppCalcDisabled == 0) {
        unsigned char* camera = CameraPcs;
        pppMngSt = pppMngStPtr;
        cameraPos.x = *reinterpret_cast<float*>(camera + 0xE0);
        cameraPos.y = *reinterpret_cast<float*>(camera + 0xE4);
        cameraPos.z = *reinterpret_cast<float*>(camera + 0xE8);

        objPos.x = pppMngStPtr->m_matrix.value[0][3];
        objPos.y = pppMngStPtr->m_matrix.value[1][3];
        objPos.z = pppMngStPtr->m_matrix.value[2][3];

        xS = PSVECDistance(&cameraPos, &objPos) / data->m_unk0x4;
        if (FLOAT_80331920 < xS) {
            xS = (xS - FLOAT_80331920) * data->m_unk0x8 + FLOAT_80331920;
        } else {
            xS = FLOAT_80331920;
        }

        PSMTXScale(scaleMtx, xS, xS, xS);

        pppMngStPtr->m_matrix.value[0][3] = FLOAT_80331924;
        pppMngStPtr->m_matrix.value[1][3] = FLOAT_80331924;
        pppMngStPtr->m_matrix.value[2][3] = FLOAT_80331924;
        PSMTXConcat(scaleMtx, pppMngStPtr->m_matrix.value, pppMngStPtr->m_matrix.value);
        pppMngStPtr->m_matrix.value[0][3] = objPos.x;
        pppMngStPtr->m_matrix.value[1][3] = objPos.y;
        pppMngStPtr->m_matrix.value[2][3] = objPos.z;

        alignmentScale = (struct pppAlignmentScale*)pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
    }

    return alignmentScale;
}

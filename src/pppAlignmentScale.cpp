#include "ffcc/pppAlignmentScale.h"
#include "ffcc/partMng.h"
#include "ffcc/p_camera.h"

#include <dolphin/mtx.h>

extern const float FLOAT_80331920;
extern const float FLOAT_80331924;
extern const float FLOAT_80331928 = 640.0f;
extern const float FLOAT_8033192c = 224.0f;

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
    float scale;
    struct _pppMngSt* pppMngSt;
    Vec cameraPos;
    Vec objPos;
    Mtx scaleMtx;

    if (gPppCalcDisabled == 0) {
        pppMngSt = pppMngStPtr;
        cameraPos.x = CameraPcs._224_4_;
        cameraPos.y = CameraPcs._228_4_;
        cameraPos.z = CameraPcs._232_4_;

        objPos.x = pppMngStPtr->m_matrix.value[0][3];
        objPos.y = pppMngStPtr->m_matrix.value[1][3];
        objPos.z = pppMngStPtr->m_matrix.value[2][3];

        scale = PSVECDistance(&cameraPos, &objPos) / data->m_unk0x4;
        if (scale <= FLOAT_80331920) {
            scale = FLOAT_80331920;
        } else {
            float deltaScale = scale - FLOAT_80331920;
            float scaleFactor = data->m_unk0x8;
            scale = deltaScale * scaleFactor + FLOAT_80331920;
        }

        PSMTXScale(scaleMtx, scale, scale, scale);

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

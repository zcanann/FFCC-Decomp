#include "ffcc/pppAlignmentScale.h"
#include "ffcc/partMng.h"

#include <dolphin/mtx.h>

extern struct {
    char pad[0xE0];
    float _224_4_;
    float _228_4_;
    float _232_4_;
} CameraPcs;


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
        CCameraPcs* camera = &CameraPcs;

        pppMngSt = pppMngStPtr;
        {
            float x = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(camera) + 0xE0);
            float y = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(camera) + 0xE4);
            float z = *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(camera) + 0xE8);
            cameraPos.x = x;
            cameraPos.y = y;
            cameraPos.z = z;
        }

        objPos.x = pppMngStPtr->m_matrix.value[0][3];
        objPos.y = pppMngStPtr->m_matrix.value[1][3];
        objPos.z = pppMngStPtr->m_matrix.value[2][3];

        scale = PSVECDistance(&cameraPos, &objPos) / data->m_unk0x4;
        if (scale <= 1.0f) {
            scale = 1.0f;
        } else {
            scale = (scale - 1.0f) * data->m_unk0x8 + 1.0f;
        }

        PSMTXScale(scaleMtx, scale, scale, scale);

        pppMngStPtr->m_matrix.value[0][3] = 0.0f;
        pppMngStPtr->m_matrix.value[1][3] = 0.0f;
        pppMngStPtr->m_matrix.value[2][3] = 0.0f;
        PSMTXConcat(scaleMtx, pppMngStPtr->m_matrix.value, pppMngStPtr->m_matrix.value);
        pppMngStPtr->m_matrix.value[0][3] = objPos.x;
        pppMngStPtr->m_matrix.value[1][3] = objPos.y;
        pppMngStPtr->m_matrix.value[2][3] = objPos.z;

        alignmentScale = (struct pppAlignmentScale*)pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
    }

    return alignmentScale;
}

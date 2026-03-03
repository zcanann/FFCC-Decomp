#include "ffcc/pppAlignmentScale.h"
#include "ffcc/partMng.h"

#include <dolphin/mtx.h>

extern int lbl_8032ED70;
extern struct _pppMngSt* pppMngStPtr;

extern class CCameraPcs {
public:
    unsigned char _0[0xe0];
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
void pppConstructAlignmentScale(void)
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

    if (lbl_8032ED70 == 0) {
        pppMngSt = pppMngStPtr;
        cameraPos.x = CameraPcs._224_4_;
        cameraPos.y = CameraPcs._228_4_;
        cameraPos.z = CameraPcs._232_4_;

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

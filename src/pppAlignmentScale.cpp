#include "ffcc/pppAlignmentScale.h"
#include "ffcc/partMng.h"

#include <dolphin/mtx.h>

extern int DAT_8032ed70;
extern float FLOAT_80331920;
extern float FLOAT_80331924;
extern struct _pppMngSt* pppMngStPtr;

extern class CCameraPcs {
public:
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
    float distanceScale;
    double distance;
    float zero;
    struct _pppMngSt* pppMngSt;
    Vec cameraPos;
    Vec objPos;
    Mtx scaleMtx;

    pppMngSt = pppMngStPtr;
    if (DAT_8032ed70 == 0) {
        cameraPos.x = CameraPcs._224_4_;
        cameraPos.y = CameraPcs._228_4_;
        cameraPos.z = CameraPcs._232_4_;

        objPos.x = pppMngStPtr->m_matrix.value[0][3];
        objPos.y = pppMngStPtr->m_matrix.value[1][3];
        objPos.z = pppMngStPtr->m_matrix.value[2][3];

        distance = (double)PSVECDistance(&cameraPos, &objPos);
        distanceScale = (float)(distance / (double)data->m_unk0x4);
        scale = FLOAT_80331920;
        if (FLOAT_80331920 < distanceScale) {
            scale = (distanceScale - FLOAT_80331920) * data->m_unk0x8 + FLOAT_80331920;
        }

        PSMTXScale(scaleMtx, scale, scale, scale);

        zero = FLOAT_80331924;
        pppMngStPtr->m_matrix.value[0][3] = FLOAT_80331924;
        pppMngStPtr->m_matrix.value[1][3] = zero;
        pppMngStPtr->m_matrix.value[2][3] = zero;
        PSMTXConcat(scaleMtx, pppMngStPtr->m_matrix.value, pppMngStPtr->m_matrix.value);
        pppMngStPtr->m_matrix.value[0][3] = objPos.x;
        pppMngStPtr->m_matrix.value[1][3] = objPos.y;
        pppMngStPtr->m_matrix.value[2][3] = objPos.z;

        alignmentScale = (struct pppAlignmentScale*)pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
    }

    return alignmentScale;
}

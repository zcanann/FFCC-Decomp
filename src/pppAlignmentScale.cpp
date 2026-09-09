#include "ffcc/pppAlignmentScale.h"
#include "ffcc/partMng.h"
#include "ffcc/p_camera.h"
#include "ffcc/pppPart.h"

#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x80109810
 * PAL Size: 284b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameAlignmentScale(struct pppAlignmentScale*, struct pppAlignmentScaleData* data)
{
    float scale;
    struct _pppMngSt* pppMngSt;
    Vec cameraPos;
    Vec objPos;
    Mtx scaleMtx;

    if (ppvUserStopPartF == 0) {
        pppMngSt = ppvMng;
        cameraPos.x = CameraPcs.m_positionX;
        cameraPos.y = CameraPcs.m_positionY;
        cameraPos.z = CameraPcs.m_positionZ;

        objPos.x = ppvMng->m_matrix.value[0][3];
        objPos.y = ppvMng->m_matrix.value[1][3];
        objPos.z = ppvMng->m_matrix.value[2][3];

        scale = PSVECDistance(&cameraPos, &objPos) / data->m_unk0x4;
        if (scale <= 1.0f) {
            scale = 1.0f;
        } else {
            float deltaScale = scale - 1.0f;
            float scaleFactor = data->m_unk0x8;
            scale = deltaScale * scaleFactor + 1.0f;
        }

        PSMTXScale(scaleMtx, scale, scale, scale);

        ppvMng->m_matrix.value[0][3] = 0.0f;
        ppvMng->m_matrix.value[1][3] = 0.0f;
        ppvMng->m_matrix.value[2][3] = 0.0f;
        PSMTXConcat(scaleMtx, ppvMng->m_matrix.value, ppvMng->m_matrix.value);
        ppvMng->m_matrix.value[0][3] = objPos.x;
        ppvMng->m_matrix.value[1][3] = objPos.y;
        ppvMng->m_matrix.value[2][3] = objPos.z;

        pppSetFpMatrix(pppMngSt);
    }
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

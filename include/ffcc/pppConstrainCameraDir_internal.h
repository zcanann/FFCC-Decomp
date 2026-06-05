#ifndef PPP_CONSTRAIN_CAMERA_DIR_INTERNAL_H
#define PPP_CONSTRAIN_CAMERA_DIR_INTERNAL_H

#include "ffcc/partMng.h"

struct pppConstrainCameraDir {
    _pppPObjLink m_link;
    s32 m_graphId;
    pppFMATRIX m_localMatrix;
    pppFMATRIX m_drawMatrix;
    Vec* m_drawMatrixPtr;
    void* m_field74;
    u8 m_pad78[0x7C - 0x78];
    u8 m_field7C;
    u8 m_pad7D[0x80 - 0x7D];
    u8 m_workArea[1];
};

struct pppConstrainCameraDirUnkB {
    int m_graphId;
    float m_dataValIndex;
    float m_initWOrk;
    float m_stepValue;
    u8 m_applyPosition;
    u8 m_applyCameraInverse;
    u8 _pad12[2];
};

#endif

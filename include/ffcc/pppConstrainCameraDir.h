#ifndef _FFCC_PPPCONSTRAINCAMERADIR_H_
#define _FFCC_PPPCONSTRAINCAMERADIR_H_

#include "ffcc/partMng.h"

typedef struct pppConstrainCameraDir {
    _pppPObjLink m_link;        // 0x00
    s32 m_graphId;              // 0x0C
    pppFMATRIX m_localMatrix;   // 0x10
    pppFMATRIX m_drawMatrix;    // 0x40
    Vec* m_drawMatrixPtr;       // 0x70
    void* m_field74;            // 0x74
    u8 m_pad78[0x7C - 0x78];    // 0x78
    u8 m_field7C;               // 0x7C
    u8 m_pad7D[0x80 - 0x7D];    // 0x7D
    u8 m_workArea[1];           // 0x80
} pppConstrainCameraDir;

typedef struct pppConstrainCameraDirUnkB {
    int m_graphId;
    float m_dataValIndex;
    float m_initWOrk;
    float m_stepValue;
    u8 m_applyPosition;
    u8 m_applyCameraInverse;
    u8 _pad12[2];
} pppConstrainCameraDirUnkB;

#ifdef __cplusplus
extern "C" {
#endif

extern const float kConstrainCameraDirScaleOne;
extern const float kConstrainCameraDirWideAspect;
extern const float kConstrainCameraDirZero;

void pppConstructConstrainCameraDir(pppConstrainCameraDir* param1, _pppCtrlTable* param2);
void pppConstruct2ConstrainCameraDir(pppConstrainCameraDir* param1, _pppCtrlTable* param2);
void pppDestructConstrainCameraDir(_pppPObjLink*, _pppCtrlTable*);
void pppFrameConstrainCameraDir(pppConstrainCameraDir* param1, pppConstrainCameraDirUnkB* param2, _pppCtrlTable* param3);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCONSTRAINCAMERADIR_H_

#ifndef _FFCC_PPPCONSTRAINCAMERADIR_H_
#define _FFCC_PPPCONSTRAINCAMERADIR_H_

typedef struct pppConstrainCameraDir {
    float field0_0x0;
} pppConstrainCameraDir;

typedef struct pppConstrainCameraDirUnkB {
    int m_graphId;
    float m_dataValIndex;
    float m_initWOrk;
    float m_stepValue;
    char m_arg3;
    char pad[3];
} pppConstrainCameraDirUnkB;

typedef struct pppConstrainCameraDirUnkC {
    int pad0;
    int pad4;
    int pad8;
    int* m_serializedDataOffsets;
} pppConstrainCameraDirUnkC;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructConstrainCameraDir(pppConstrainCameraDir* param1, pppConstrainCameraDirUnkC* param2);
void pppConstruct2ConstrainCameraDir(pppConstrainCameraDir* param1, pppConstrainCameraDirUnkC* param2);
void pppDestructConstrainCameraDir(void);
void pppFrameConstrainCameraDir(pppConstrainCameraDir* param1, pppConstrainCameraDirUnkB* param2, pppConstrainCameraDirUnkC* param3);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCONSTRAINCAMERADIR_H_


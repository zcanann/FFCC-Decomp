#ifndef _FFCC_PPPCONSTRAINCAMERADIR_H_
#define _FFCC_PPPCONSTRAINCAMERADIR_H_

typedef struct pppConstrainCameraDir {
    float field0_0x0;
} pppConstrainCameraDir;

typedef struct UnkB {
    float m_dataValIndex;
    float m_initWOrk;
    float m_stepValue;
    int m_graphId;
    char m_arg3;
    char pad[3];
} UnkB;

typedef struct UnkC {
    int* m_serializedDataOffsets;
} UnkC;

void pppConstructConstrainCameraDir(pppConstrainCameraDir* param1, UnkC* param2);
void pppConstruct2ConstrainCameraDir(pppConstrainCameraDir* param1, UnkC* param2);
void pppDestructConstrainCameraDir(void);
void pppFrameConstrainCameraDir(pppConstrainCameraDir* param1, UnkB* param2, UnkC* param3);

#endif // _FFCC_PPPCONSTRAINCAMERADIR_H_

#ifndef _FFCC_PPPCONSTRAINCAMERADIR2_H_
#define _FFCC_PPPCONSTRAINCAMERADIR2_H_

#include "ffcc/partMng.h"

// Forward declarations for parameter types
typedef struct pppConstrainCameraDir pppConstrainCameraDir;
typedef struct pppConstrainCameraDirUnkB pppConstrainCameraDirUnkB;

#ifdef __cplusplus
extern "C" {
#endif

void pppFrameConstrainCameraDir2(pppConstrainCameraDir* param_1, pppConstrainCameraDirUnkB* param_2,
                                 _pppCtrlTable* param_3);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCONSTRAINCAMERADIR2_H_


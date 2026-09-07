#ifndef _FFCC_MONOBJ_BOSS_H_
#define _FFCC_MONOBJ_BOSS_H_

#include "ffcc/monobj.h"

class CGItemObj;

struct LastBossWork {
    CGMonObj* m_boss;
    CChara::CNode* m_node;
    CGItemObj* m_capsules[4];
    Vec m_targetPosition;
    int m_phaseTimer;
};
typedef char LastBossWork_size_mismatch[(sizeof(LastBossWork) == 0x28) ? 1 : -1];

#endif // _FFCC_MONOBJ_BOSS_H_

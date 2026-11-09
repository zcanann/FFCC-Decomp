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

struct LichBossWork {
    int m_lichTeleportIndex;
    Vec m_lichTeleportVec;
    union {
        u8 m_lichFlags;
        struct {
            s8 m_lichBit80 : 1;
            s8 m_lichBit40 : 1;
            u8 m_lichRest : 6;
        } lichBits;
    };
};

struct MeteoParasiteCBossWork {
    CChara::CNode* m_nodes[14];
    CGObject* m_rotObjects[12];
    CGMonObj* m_objs[4];
    union {
        int m_coreIndex;
        int m_index;
    };
    union {
        u8 m_coreFlags;
        u8 m_flags;
        struct {
            s8 m_bit80 : 1;
            s8 m_meteo3 : 1;
            u8 m_rest : 6;
        } bits;
    };
    u8 m_pad7D[3];
    int m_coreMode;
    union {
        int m_coreWait;
        int m_wait;
    };
    int m_coreDamage;
};

#endif // _FFCC_MONOBJ_BOSS_H_

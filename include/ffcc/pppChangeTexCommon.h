#ifndef _FFCC_PPPCHANGETEXCOMMON_H_
#define _FFCC_PPPCHANGETEXCOMMON_H_

#include "ffcc/chara.h"
#include <dolphin/types.h>

typedef CChara::CMesh::CDisplayList ChangeTexDisplayList;

struct ChangeTexDisplayListCopy {
	void* m_data;
	u32 m_size;
};

typedef CChara::CMesh::CRefData ChangeTexMeshData;
typedef CChara::CMesh ChangeTexMeshRef;

struct ChangeTexDataOffsets {
    s32 _unused0;
    s32 m_colorBlockOffset;
    s32 m_workOffset;
};

struct ChangeTexStep {
    s32 m_graphId;
    s32 m_dataValIndex;
    float m_initWOrk;
    float m_stepValue;
    float m_arg3;
    union {
        u8 m_payload[6];
        struct Payload {
            u8 m_mode;
            u8 m_pad01[5];
        } m_changeTex;
    };
    u8 _pad1[1];
};

static inline ChangeTexMeshRef* ChangeTexMeshes(CChara::CModel* model)
{
	return model->m_meshes;
}

static inline void ClearChangeTexModelCallbacks(CChara::CModel* model)
{
	model->SetCallbackContext(0, 0);
	model->SetBeforeMeshLockEnvCallback(0);
	model->SetDrawMeshDLCallback(0);
	model->SetAfterDrawMeshCallback(0);
}

#endif // _FFCC_PPPCHANGETEXCOMMON_H_

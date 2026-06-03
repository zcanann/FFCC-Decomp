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

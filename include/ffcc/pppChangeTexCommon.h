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

#endif // _FFCC_PPPCHANGETEXCOMMON_H_

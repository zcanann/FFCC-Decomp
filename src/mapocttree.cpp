#include "ffcc/mapocttree.h"
#include "ffcc/chunkfile.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/mapmesh.h"
#include "ffcc/memory.h"
#include "ffcc/linkage.h"
#include "ffcc/materialman.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_light.h"
#include "ffcc/system.h"
extern "C" {
extern const float kMapOctTreeDefaultOffsetZ;
}

// Linkage definitions from config/GCCP01/symbols.txt.
const float kOctTreeBoundMinInit = 10000000000.0f;
const float kOctTreeBoundMaxInit = -10000000000.0f;
const float kOctTreeCylinderPad = 1.0f;
unsigned long s_clearFlagMask;
struct CBoundRaw
{
    CBoundRaw()
    {
        float min = kOctTreeBoundMinInit;
        float max = kOctTreeBoundMaxInit;
        float* bound = (float*)this;
        bound[2] = min;
        bound[1] = min;
        bound[0] = min;
        bound[5] = max;
        bound[4] = max;
        bound[3] = max;
    }

    Vec m_min;
    Vec m_max;
};
struct CMapCylinderRaw
{
    CMapCylinderRaw()
    {
        m_direction2.y = kOctTreeBoundMinInit;
        m_direction2.x = kOctTreeBoundMinInit;
        m_top.z = kOctTreeBoundMinInit;
        m_height2 = kOctTreeBoundMaxInit;
        m_radius2 = kOctTreeBoundMaxInit;
        m_direction2.z = kOctTreeBoundMaxInit;
    }

    Vec m_bottom;
    Vec m_direction;
    float m_radius;
    float m_height;
    Vec m_top;
    Vec m_direction2;
    float m_radius2;
    float m_height2;
};

struct CMaterialManEnvRaw
{
    unsigned char m_pad004[0x40];
    unsigned int m_stdEnvTevBit;
    unsigned int m_activeEnvTevBit;
    unsigned int m_curEnvTevBit;
    unsigned char m_alphaRef;
    unsigned char m_pad04D[0x0B];
    unsigned int m_lockedEnvTevBit;
    unsigned int m_lockedEnvUnknown5c;
    unsigned char m_pad060[0xBC];
    int m_texMapIdCur;
    int m_texMtxCur;
    int m_texCoordIdCur;
    int m_stdTexMapId;
    int m_stdTexMtx;
    int m_stdTexCoordId;
    int m_texMapIdCurShadow;
    int m_texMtxCurShadow;
    int m_texCoordIdCurShadow;
    unsigned char m_pad140[0xC5];
    unsigned char m_blendMode;
    unsigned char m_fogEnable;
    unsigned char m_blendOverrideMode;
    unsigned char m_shadowKColorMask;
};

CBoundRaw s_bound;
CMapCylinderRaw s_cyl;
Vec s_mvec;
static unsigned long s_checkHitCylinderMask;
static unsigned long s_insertLightBitIndex;
static unsigned long s_insertShadowBitIndex;
static int s_insertShadowDepth;

extern "C" void __dl__FPv(void*);
extern "C" void __dla__FPv(void*);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void __ct__8COctNodeFv(void*);
extern "C" void* __construct_new_array(void*, void*, void*, unsigned long, unsigned long);
extern "C" void Printf__7CSystemFPce(CSystem* system, const char* format, ...);
extern "C" const char s_m_node_pctd_m_meshtype_pctd_801D7268[];

static const char s_mapocttree_cpp[] = "mapocttree.cpp";

namespace {
static inline unsigned char* Ptr(void* ptr, unsigned int offset)
{
    return reinterpret_cast<unsigned char*>(ptr) + offset;
}

static inline COctNode* GetMapObjByIndex(unsigned short index)
{
    return reinterpret_cast<COctNode*>(reinterpret_cast<unsigned char*>(&MapMng) + 0x960 + (index * 0xF0));
}

}

/*
 * --INFO--
 * PAL Address: 8002d9fc
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void setbit32(unsigned long* arg0, unsigned long arg1)
{
	unsigned long* bits;
	unsigned long offset;
	unsigned long mask;

	bits = (unsigned long*)((unsigned char*)arg0 + ((arg1 >> 3) & 0x1ffffffc));
	offset = arg1 & 0x1f;
	mask = 1UL << offset;
	*bits |= mask;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
COctTree::COctTree()
{
	m_nodePool = 0;
	m_mapObject = 0;
	m_drawFlags = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8002f384
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
COctTree::~COctTree()
{
	COctNode* rootNode = m_nodePool;

	if (rootNode != 0) {
		delete[] rootNode;
		m_nodePool = 0;
	}

	m_mapObject = 0;
	m_nodeCount = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8002ef9c
 * PAL Size: 952b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void COctTree::ReadOtmOctTree(CChunkFile& chunkFile)
{
    CChunkFile::CChunk chunk;

    m_unk01 = 0;
    chunkFile.PushChunk();

    while (chunkFile.GetNextChunk(chunk)) {
        switch (chunk.m_id) {
        case 'OBJN': {
            unsigned short objIndex = chunkFile.Get2();
            unsigned char* mapObj;

            m_mapObject = GetMapObjByIndex(objIndex);
            mapObj = reinterpret_cast<unsigned char*>(m_mapObject);
            if (mapObj[0x1E] == 4) {
                mapObj[0x15] = 0xFF;
                mapObj[0x14] = 0xFF;
                mapObj[0x22] = 0;
            } else if (mapObj[0x1E] == 3) {
                mapObj[0x22] = 0;
            }
            break;
        }

        case 'NODN': {
            unsigned short nodeCount = chunkFile.Get2();
            void* rootNode;

            m_nodeCount = nodeCount;
            if ((*reinterpret_cast<unsigned char*>(Ptr(m_mapObject, 0x1E)) != 1) &&
                (static_cast<unsigned int>(System.m_execParam) > 2U)) {
                Printf__7CSystemFPce(&System, s_m_node_pctd_m_meshtype_pctd_801D7268, nodeCount);
            }

            rootNode = __nwa__FUlPQ27CMemory6CStagePci(
                nodeCount * 0x4C + 0x10, *reinterpret_cast<CMemory::CStage**>(&MapMng), const_cast<char*>(s_mapocttree_cpp),
                0x59);
            m_nodePool = reinterpret_cast<COctNode*>(
                __construct_new_array(rootNode, reinterpret_cast<void*>(__ct__8COctNodeFv), 0, 0x4C, nodeCount));
            break;
        }

        case 'INFO':
            m_unk01 = chunkFile.Get1();
            break;

        case 'TYPE':
            m_type = static_cast<unsigned char>(chunkFile.Get2());
            break;

        case 'TREE':
            chunkFile.PushChunk();
            while (chunkFile.GetNextChunk(chunk)) {
                if (chunk.m_id == 'NODE') {
                    COctNode* node = 0;

                    chunkFile.PushChunk();
                    while (chunkFile.GetNextChunk(chunk)) {
                        switch (chunk.m_id) {
                        case 'OBJ ': {
                            unsigned short nodeIndex = chunkFile.Get2();

                            node = m_nodePool + nodeIndex;
                            node->m_meshCount = chunkFile.Get2();
                            node->m_meshStart = chunkFile.Get2();
                            break;
                        }

                        case 'BOND':
                            if (node != 0) {
                                node->m_boundMinX = chunkFile.GetF4();
                                node->m_boundMinY = chunkFile.GetF4();
                                node->m_boundMinZ = chunkFile.GetF4();
                                node->m_boundMaxX = chunkFile.GetF4();
                                node->m_boundMaxY = chunkFile.GetF4();
                                node->m_boundMaxZ = chunkFile.GetF4();
                            }
                            break;

                        case 'CHLD':
                            if (node != 0) {
                                int childCount = 0;
                                COctNode** childNode = node->m_children;

                                for (int i = 0; i < 8; i++) {
                                    unsigned short childIndex = chunkFile.Get2();

                                    if (childIndex != 0xFFFF) {
                                        *childNode = m_nodePool + childIndex;
                                        childNode++;
                                        childCount++;
                                    }
                                }

                                for (int i = childCount; i < 8; i++) {
                                    *childNode = 0;
                                    childNode++;
                                }
                            }
                            break;
                        }
                    }
                    chunkFile.PopChunk();
                }
            }
            chunkFile.PopChunk();
            break;
        }
    }

    chunkFile.PopChunk();
}

/*
 * --INFO--
 * PAL Address: 0x8002ebc0
 * PAL Size: 868b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void COctTree::DrawTypeMeshFlag_r(COctNode* octNode)
{
	int iVar1;
	int iVar2;
	COctNode* pCVar3;
	COctNode* pCVar4;
	int iVar5;

	if ((*reinterpret_cast<unsigned short*>(Ptr(octNode, 0x3C)) != 0) &&
	    ((*reinterpret_cast<unsigned long*>(Ptr(octNode, 0x40)) & 1) != 0)) {
		MaterialMan.InitEnv();
		if (*reinterpret_cast<unsigned char*>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0x22)) != 0) {
			CameraPcs.SetFullScreenShadow(reinterpret_cast<float(*)[4]>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xB8)), 0);
		}
		if (*reinterpret_cast<unsigned long*>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0x3C)) != 0) {
			MaterialMan.SetShadowBit32(static_cast<CMapShadow::TARGET>(1), reinterpret_cast<unsigned long*>(Ptr(octNode, 0x48)),
			                           reinterpret_cast<float(*)[4]>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xB8)));
		}
		MaterialMan.LockEnv();
		LightPcs.SetBit32(static_cast<CLightPcs::TARGET>(1), reinterpret_cast<unsigned long*>(Ptr(octNode, 0x44)));
		(*reinterpret_cast<CMapObj**>(Ptr(this, 0x8)))->SetDrawEnv();
		(*reinterpret_cast<CMapMesh**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xC)))
			->DrawMesh(*reinterpret_cast<unsigned short*>(Ptr(octNode, 0x3E)),
			           *reinterpret_cast<unsigned short*>(Ptr(octNode, 0x3C)));
	}
	iVar2 = 0;
	do {
		pCVar4 = *reinterpret_cast<COctNode**>(Ptr(octNode, 0x1C));
		if (pCVar4 == 0) {
			return;
		}
		if ((*reinterpret_cast<unsigned short*>(Ptr(pCVar4, 0x3C)) != 0) &&
		    ((*reinterpret_cast<unsigned long*>(Ptr(pCVar4, 0x40)) & 1) != 0)) {
			MaterialMan.InitEnv();
			if (*reinterpret_cast<unsigned char*>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0x22)) != 0) {
				CameraPcs.SetFullScreenShadow(reinterpret_cast<float(*)[4]>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xB8)), 0);
			}
			if (*reinterpret_cast<unsigned long*>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0x3C)) != 0) {
				MaterialMan.SetShadowBit32(static_cast<CMapShadow::TARGET>(1), reinterpret_cast<unsigned long*>(Ptr(pCVar4, 0x48)),
				                           reinterpret_cast<float(*)[4]>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xB8)));
			}
			MaterialMan.LockEnv();
			LightPcs.SetBit32(static_cast<CLightPcs::TARGET>(1), reinterpret_cast<unsigned long*>(Ptr(pCVar4, 0x44)));
			(*reinterpret_cast<CMapObj**>(Ptr(this, 0x8)))->SetDrawEnv();
			(*reinterpret_cast<CMapMesh**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xC)))
				->DrawMesh(*reinterpret_cast<unsigned short*>(Ptr(pCVar4, 0x3E)),
				           *reinterpret_cast<unsigned short*>(Ptr(pCVar4, 0x3C)));
		}
		iVar5 = 0;
		do {
			pCVar3 = *reinterpret_cast<COctNode**>(Ptr(pCVar4, 0x1C));
			if (pCVar3 == 0) {
				break;
			}
			if ((*reinterpret_cast<unsigned short*>(Ptr(pCVar3, 0x3C)) != 0) &&
			    ((*reinterpret_cast<unsigned long*>(Ptr(pCVar3, 0x40)) & 1) != 0)) {
				MaterialMan.InitEnv();
				if (*reinterpret_cast<unsigned char*>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0x22)) != 0) {
					CameraPcs.SetFullScreenShadow(reinterpret_cast<float(*)[4]>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xB8)), 0);
				}
				if (*reinterpret_cast<unsigned long*>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0x3C)) != 0) {
					MaterialMan.SetShadowBit32(static_cast<CMapShadow::TARGET>(1), reinterpret_cast<unsigned long*>(Ptr(pCVar3, 0x48)),
					                           reinterpret_cast<float(*)[4]>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xB8)));
				}
				MaterialMan.LockEnv();
				LightPcs.SetBit32(static_cast<CLightPcs::TARGET>(1), reinterpret_cast<unsigned long*>(Ptr(pCVar3, 0x44)));
				(*reinterpret_cast<CMapObj**>(Ptr(this, 0x8)))->SetDrawEnv();
				(*reinterpret_cast<CMapMesh**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xC)))
					->DrawMesh(*reinterpret_cast<unsigned short*>(Ptr(pCVar3, 0x3E)),
					           *reinterpret_cast<unsigned short*>(Ptr(pCVar3, 0x3C)));
			}
			iVar1 = 0;
			do {
				if (*reinterpret_cast<COctNode**>(Ptr(pCVar3, 0x1C)) == 0) {
					break;
				}
				DrawTypeMeshFlag_r(*reinterpret_cast<COctNode**>(Ptr(pCVar3, 0x1C)));
				iVar1 = iVar1 + 1;
				pCVar3 = reinterpret_cast<COctNode*>(Ptr(pCVar3, 4));
			} while (iVar1 < 8);
			iVar5 = iVar5 + 1;
			pCVar4 = reinterpret_cast<COctNode*>(Ptr(pCVar4, 4));
		} while (iVar5 < 8);
		iVar2 = iVar2 + 1;
		octNode = reinterpret_cast<COctNode*>(Ptr(octNode, 4));
		if (7 < iVar2) {
			return;
		}
	} while (true);
}

/*
 * --INFO--
 * PAL Address: 0x8002e994
 * PAL Size: 556b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void COctTree::DrawCharaShadowTypeMeshFlag_r(COctNode* octNode)
{
	int iVar1;
	int iVar2;
	COctNode* pCVar3;
	COctNode* pCVar4;
	COctNode* pCVar5;
	COctNode* pCVar6;
	COctNode* pCVar7;
	COctNode* pCVar8;
	int iVar9;
	int iVar10;
	int iVar11;
	int iVar12;
	int iVar13;

	if ((*reinterpret_cast<unsigned short*>(Ptr(octNode, 0x3C)) != 0) &&
	    ((*reinterpret_cast<unsigned long*>(Ptr(octNode, 0x40)) & 1) != 0)) {
		reinterpret_cast<CMapMesh*>(*reinterpret_cast<void**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xC)))
			->DrawMeshCharaShadow(*reinterpret_cast<unsigned short*>(Ptr(octNode, 0x3E)),
			                      *reinterpret_cast<unsigned short*>(Ptr(octNode, 0x3C)));
	}

	iVar1 = 0;
	do {
		pCVar3 = *reinterpret_cast<COctNode**>(Ptr(octNode, 0x1C));
		if (pCVar3 == 0) {
			return;
		}
		if ((*reinterpret_cast<unsigned short*>(Ptr(pCVar3, 0x3C)) != 0) &&
		    ((*reinterpret_cast<unsigned long*>(Ptr(pCVar3, 0x40)) & 1) != 0)) {
			reinterpret_cast<CMapMesh*>(*reinterpret_cast<void**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xC)))
				->DrawMeshCharaShadow(*reinterpret_cast<unsigned short*>(Ptr(pCVar3, 0x3E)),
				                      *reinterpret_cast<unsigned short*>(Ptr(pCVar3, 0x3C)));
		}
		iVar2 = 0;
		do {
			pCVar8 = *reinterpret_cast<COctNode**>(Ptr(pCVar3, 0x1C));
			if (pCVar8 == 0) {
				break;
			}
			if ((*reinterpret_cast<unsigned short*>(Ptr(pCVar8, 0x3C)) != 0) &&
			    ((*reinterpret_cast<unsigned long*>(Ptr(pCVar8, 0x40)) & 1) != 0)) {
				reinterpret_cast<CMapMesh*>(*reinterpret_cast<void**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xC)))
					->DrawMeshCharaShadow(*reinterpret_cast<unsigned short*>(Ptr(pCVar8, 0x3E)),
					                      *reinterpret_cast<unsigned short*>(Ptr(pCVar8, 0x3C)));
			}
			iVar13 = 0;
			do {
				pCVar7 = *reinterpret_cast<COctNode**>(Ptr(pCVar8, 0x1C));
				if (pCVar7 == 0) {
					break;
				}
				if ((*reinterpret_cast<unsigned short*>(Ptr(pCVar7, 0x3C)) != 0) &&
				    ((*reinterpret_cast<unsigned long*>(Ptr(pCVar7, 0x40)) & 1) != 0)) {
					reinterpret_cast<CMapMesh*>(*reinterpret_cast<void**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xC)))
						->DrawMeshCharaShadow(*reinterpret_cast<unsigned short*>(Ptr(pCVar7, 0x3E)),
						                      *reinterpret_cast<unsigned short*>(Ptr(pCVar7, 0x3C)));
				}
				iVar12 = 0;
				do {
					pCVar6 = *reinterpret_cast<COctNode**>(Ptr(pCVar7, 0x1C));
					if (pCVar6 == 0) {
						break;
					}
					if ((*reinterpret_cast<unsigned short*>(Ptr(pCVar6, 0x3C)) != 0) &&
					    ((*reinterpret_cast<unsigned long*>(Ptr(pCVar6, 0x40)) & 1) != 0)) {
						reinterpret_cast<CMapMesh*>(*reinterpret_cast<void**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xC)))
							->DrawMeshCharaShadow(*reinterpret_cast<unsigned short*>(Ptr(pCVar6, 0x3E)),
							                      *reinterpret_cast<unsigned short*>(Ptr(pCVar6, 0x3C)));
					}
					iVar11 = 0;
					do {
						pCVar5 = *reinterpret_cast<COctNode**>(Ptr(pCVar6, 0x1C));
						if (pCVar5 == 0) {
							break;
						}
						if ((*reinterpret_cast<unsigned short*>(Ptr(pCVar5, 0x3C)) != 0) &&
						    ((*reinterpret_cast<unsigned long*>(Ptr(pCVar5, 0x40)) & 1) != 0)) {
							reinterpret_cast<CMapMesh*>(*reinterpret_cast<void**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xC)))
								->DrawMeshCharaShadow(*reinterpret_cast<unsigned short*>(Ptr(pCVar5, 0x3E)),
								                      *reinterpret_cast<unsigned short*>(Ptr(pCVar5, 0x3C)));
						}
						iVar10 = 0;
						do {
							pCVar4 = *reinterpret_cast<COctNode**>(Ptr(pCVar5, 0x1C));
							if (pCVar4 == 0) {
								break;
							}
							if ((*reinterpret_cast<unsigned short*>(Ptr(pCVar4, 0x3C)) != 0) &&
							    ((*reinterpret_cast<unsigned long*>(Ptr(pCVar4, 0x40)) & 1) != 0)) {
								reinterpret_cast<CMapMesh*>(*reinterpret_cast<void**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xC)))
									->DrawMeshCharaShadow(*reinterpret_cast<unsigned short*>(Ptr(pCVar4, 0x3E)),
									                      *reinterpret_cast<unsigned short*>(Ptr(pCVar4, 0x3C)));
							}
							iVar9 = 0;
							do {
								if (*reinterpret_cast<COctNode**>(Ptr(pCVar4, 0x1C)) == 0) {
									break;
								}
								DrawCharaShadowTypeMeshFlag_r(*reinterpret_cast<COctNode**>(Ptr(pCVar4, 0x1C)));
								iVar9 = iVar9 + 1;
								pCVar4 = reinterpret_cast<COctNode*>(Ptr(pCVar4, 4));
							} while (iVar9 < 8);
							iVar10 = iVar10 + 1;
							pCVar5 = reinterpret_cast<COctNode*>(Ptr(pCVar5, 4));
						} while (iVar10 < 8);
						iVar11 = iVar11 + 1;
						pCVar6 = reinterpret_cast<COctNode*>(Ptr(pCVar6, 4));
					} while (iVar11 < 8);
					iVar12 = iVar12 + 1;
					pCVar7 = reinterpret_cast<COctNode*>(Ptr(pCVar7, 4));
				} while (iVar12 < 8);
				iVar13 = iVar13 + 1;
				pCVar8 = reinterpret_cast<COctNode*>(Ptr(pCVar8, 4));
			} while (iVar13 < 8);
			iVar2 = iVar2 + 1;
			pCVar3 = reinterpret_cast<COctNode*>(Ptr(pCVar3, 4));
		} while (iVar2 < 8);
		iVar1 = iVar1 + 1;
		octNode = reinterpret_cast<COctNode*>(Ptr(octNode, 4));
		if (7 < iVar1) {
			return;
		}
	} while (true);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void COctTree::DrawTypeMeshFrustumIn_r(COctNode* octNode)
{
	COctNode* child1;
	COctNode* child2;
	COctNode* child3;
	COctNode* child4;
	COctNode* child5;
	COctNode* child6;
	COctNode* child7;
	COctNode* child8;
	if (*reinterpret_cast<unsigned short*>(Ptr(octNode, 0x3C)) != 0) {
		*reinterpret_cast<unsigned long*>(Ptr(octNode, 0x40)) |= 1;
	}

	for (int i = 0; i < 8; i++) {
		child1 = *reinterpret_cast<COctNode**>(Ptr(octNode, 0x1C));
		if (child1 == 0) {
			return;
		}
		if (*reinterpret_cast<unsigned short*>(Ptr(child1, 0x3C)) != 0) {
			*reinterpret_cast<unsigned long*>(Ptr(child1, 0x40)) |= 1;
		}

		for (int j = 0; j < 8; j++) {
			child2 = *reinterpret_cast<COctNode**>(Ptr(child1, 0x1C));
			if (child2 == 0) {
				break;
			}
			if (*reinterpret_cast<unsigned short*>(Ptr(child2, 0x3C)) != 0) {
				*reinterpret_cast<unsigned long*>(Ptr(child2, 0x40)) |= 1;
			}

			for (int k = 0; k < 8; k++) {
				child3 = *reinterpret_cast<COctNode**>(Ptr(child2, 0x1C));
				if (child3 == 0) {
					break;
				}
				if (*reinterpret_cast<unsigned short*>(Ptr(child3, 0x3C)) != 0) {
					*reinterpret_cast<unsigned long*>(Ptr(child3, 0x40)) |= 1;
				}

				for (int m = 0; m < 8; m++) {
					child4 = *reinterpret_cast<COctNode**>(Ptr(child3, 0x1C));
					if (child4 == 0) {
						break;
					}
					if (*reinterpret_cast<unsigned short*>(Ptr(child4, 0x3C)) != 0) {
						*reinterpret_cast<unsigned long*>(Ptr(child4, 0x40)) |= 1;
					}

					for (int n = 0; n < 8; n++) {
						child5 = *reinterpret_cast<COctNode**>(Ptr(child4, 0x1C));
						if (child5 == 0) {
							break;
						}
						if (*reinterpret_cast<unsigned short*>(Ptr(child5, 0x3C)) != 0) {
							*reinterpret_cast<unsigned long*>(Ptr(child5, 0x40)) |= 1;
						}

						for (int o = 0; o < 8; o++) {
							child6 = *reinterpret_cast<COctNode**>(Ptr(child5, 0x1C));
							if (child6 == 0) {
								break;
							}
							if (*reinterpret_cast<unsigned short*>(Ptr(child6, 0x3C)) != 0) {
								*reinterpret_cast<unsigned long*>(Ptr(child6, 0x40)) |= 1;
							}

							for (int p = 0; p < 8; p++) {
								child7 = *reinterpret_cast<COctNode**>(Ptr(child6, 0x1C));
								if (child7 == 0) {
									break;
								}
								if (*reinterpret_cast<unsigned short*>(Ptr(child7, 0x3C)) != 0) {
									*reinterpret_cast<unsigned long*>(Ptr(child7, 0x40)) |= 1;
								}

								for (int q = 0; q < 8; q++) {
									child8 = *reinterpret_cast<COctNode**>(Ptr(child7, 0x1C));
									if (child8 == 0) {
										break;
									}
									if (*reinterpret_cast<unsigned short*>(Ptr(child8, 0x3C)) != 0) {
										*reinterpret_cast<unsigned long*>(Ptr(child8, 0x40)) |= 1;
									}

									for (int r = 0; r < 8; r++) {
										if (*reinterpret_cast<COctNode**>(Ptr(child8, 0x1C)) == 0) {
											break;
										}
										DrawTypeMeshFrustumIn_r(*reinterpret_cast<COctNode**>(Ptr(child8, 0x1C)));
										child8 = reinterpret_cast<COctNode*>(Ptr(child8, 4));
									}

									child7 = reinterpret_cast<COctNode*>(Ptr(child7, 4));
								}

								child6 = reinterpret_cast<COctNode*>(Ptr(child6, 4));
							}

							child5 = reinterpret_cast<COctNode*>(Ptr(child5, 4));
						}

						child4 = reinterpret_cast<COctNode*>(Ptr(child4, 4));
					}

					child3 = reinterpret_cast<COctNode*>(Ptr(child3, 4));
				}

				child2 = reinterpret_cast<COctNode*>(Ptr(child2, 4));
			}

			child1 = reinterpret_cast<COctNode*>(Ptr(child1, 4));
		}

		octNode = reinterpret_cast<COctNode*>(Ptr(octNode, 4));
	}
}

/*
 * --INFO--
 * PAL Address: 0x8002e490
 * PAL Size: 712b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void COctTree::DrawTypeMesh_r(COctNode* octNode)
{
	float localX = *reinterpret_cast<float*>(Ptr(this, 0x3C));
	float localY = *reinterpret_cast<float*>(Ptr(this, 0x40));
	float localZ = *reinterpret_cast<float*>(Ptr(this, 0x44));
	unsigned int orMask;

	if (((*reinterpret_cast<float*>(Ptr(octNode, 0x0C)) < localX) || (*reinterpret_cast<float*>(Ptr(octNode, 0x10)) < localY) ||
	     (*reinterpret_cast<float*>(Ptr(octNode, 0x14)) < localZ)) ||
	    ((localX < *reinterpret_cast<float*>(Ptr(octNode, 0x00))) || (localY < *reinterpret_cast<float*>(Ptr(octNode, 0x04))) ||
	     (localZ < *reinterpret_cast<float*>(Ptr(octNode, 0x08))))) {
		Vec localCorner;
		Vec viewPos;
		float maxDepth = kOctTreeBoundMinInit;
		float minDepth = kOctTreeBoundMaxInit;
		unsigned int andMask = 0xF;
		int farCount = 0;

		orMask = 0;

		for (int x = 0; x < 2; x++) {
			localCorner.x = (x == 0) ? *reinterpret_cast<float*>(Ptr(octNode, 0x00)) : *reinterpret_cast<float*>(Ptr(octNode, 0x0C));
			for (int y = 0; y < 2; y++) {
				localCorner.y = (y == 0) ? *reinterpret_cast<float*>(Ptr(octNode, 0x04)) : *reinterpret_cast<float*>(Ptr(octNode, 0x10));
				for (int z = 0; z < 2; z++) {
					unsigned int clipFlags;
					double depth;

					localCorner.z = (z == 0) ? *reinterpret_cast<float*>(Ptr(octNode, 0x08)) : *reinterpret_cast<float*>(Ptr(octNode, 0x14));
					PSMTXMultVec(reinterpret_cast<float(*)[4]>(Ptr(this, 0x0C)), &localCorner, &viewPos);

					depth = static_cast<double>(viewPos.z);
					if (maxDepth < viewPos.z) {
						maxDepth = viewPos.z;
					}

					if (depth <= static_cast<double>(minDepth)) {
						if (static_cast<double>(viewPos.x) <= -depth) {
							if (depth <= static_cast<double>(viewPos.x)) {
								clipFlags = 0;
							} else {
								clipFlags = 2;
							}
						} else {
							clipFlags = 1;
						}

						if (static_cast<double>(viewPos.y) <= -depth) {
							if (static_cast<double>(viewPos.y) < depth) {
								clipFlags |= 8;
							}
						} else {
							clipFlags |= 4;
						}
					} else {
						farCount++;
						if (static_cast<double>(viewPos.x) <= -depth) {
							if (depth <= static_cast<double>(viewPos.x)) {
								clipFlags = 0x10;
							} else {
								clipFlags = 0x12;
							}
						} else {
							clipFlags = 0x11;
						}

						if (static_cast<double>(viewPos.y) <= -depth) {
							if (static_cast<double>(viewPos.y) < depth) {
								clipFlags |= 0x18;
							}
						} else {
							clipFlags |= 0x14;
						}
					}

					andMask &= clipFlags;
					orMask |= clipFlags;
				}
			}
		}

		if (farCount > 7) {
			return;
		}
		if (maxDepth < *reinterpret_cast<float*>(Ptr(&MapMng, 0x22A70))) {
			return;
		}
		if (andMask != 0) {
			return;
		}
	} else {
		orMask = 0xF;
	}

	if (*reinterpret_cast<unsigned short*>(Ptr(octNode, 0x3C)) != 0) {
		*reinterpret_cast<unsigned long*>(Ptr(octNode, 0x40)) |= 1;
	}

	if (orMask == 0) {
		for (int i = 0; i < 8; i++) {
			if (*reinterpret_cast<COctNode**>(Ptr(octNode, 0x1C)) == 0) {
				return;
			}
			DrawTypeMeshFrustumIn_r(*reinterpret_cast<COctNode**>(Ptr(octNode, 0x1C)));
			octNode = reinterpret_cast<COctNode*>(Ptr(octNode, 4));
		}
	} else {
		for (int i = 0; i < 8; i++) {
			if (*reinterpret_cast<COctNode**>(Ptr(octNode, 0x1C)) == 0) {
				return;
			}
			DrawTypeMesh_r(*reinterpret_cast<COctNode**>(Ptr(octNode, 0x1C)));
			octNode = reinterpret_cast<COctNode*>(Ptr(octNode, 4));
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8002e338
 * PAL Size: 344b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void COctTree::Draw(unsigned char drawType)
{
	unsigned char* thisBytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* mapObj;
	unsigned char* mapMng;
	unsigned char* bumpLight;

	if (*thisBytes != 0) {
		return;
	}

	mapObj = *reinterpret_cast<unsigned char**>(thisBytes + 8);
	if ((mapObj[0x15] != drawType) || ((mapObj[0x18] & 1) == 0)) {
		return;
	}

	mapMng = reinterpret_cast<unsigned char*>(&MapMng);
	bumpLight = *reinterpret_cast<unsigned char**>(mapObj + 0x10);
	if ((mapMng[0x2298A] != 0) && (bumpLight != 0) && (bumpLight[0xB1] == 2)) {
		MaterialMan.SetUnderWaterTex();
		mapMng[0x2298A] = 0;
	}

	LightPcs.SetBumpTexMatirx(reinterpret_cast<float(*)[4]>(mapObj + 0xB8),
	                          reinterpret_cast<CLightPcs::CBumpLight*>(*reinterpret_cast<void**>(mapObj + 0x10)),
	                          reinterpret_cast<Vec*>(mapObj + 0x58), mapObj[0x1A]);

	if (kMapOctTreeDefaultOffsetZ != *reinterpret_cast<float*>(mapObj + 0x40)) {
		CameraPcs.SetOffsetZBuff(*reinterpret_cast<float*>(mapObj + 0x40));
	}

	if (mapObj[0x27] != 0) {
		GXSetZMode(1, GX_LEQUAL, 0);
	}

	reinterpret_cast<CMapMesh*>(*reinterpret_cast<void**>(mapObj + 0xC))->SetRenderArray();
	DrawTypeMeshFlag_r(*reinterpret_cast<COctNode**>(thisBytes + 4));

	if (mapObj[0x27] != 0) {
		GXSetZMode(1, GX_LEQUAL, 1);
	}

	if (kMapOctTreeDefaultOffsetZ != *reinterpret_cast<float*>(mapObj + 0x40)) {
		CameraPcs.SetOffsetZBuff(*reinterpret_cast<float*>(mapObj + 0x40));
	}
}

/*
 * --INFO--
 * PAL Address: 0x8002e27c
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void COctTree::DrawCharaShadow(unsigned char drawType)
{
	unsigned char* thisBytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* mapObj;

	if (*thisBytes != 0) {
		return;
	}

	mapObj = *reinterpret_cast<unsigned char**>(thisBytes + 8);
	if (mapObj[0x15] != drawType) {
		return;
	}

	LightPcs.SetBumpTexMatirx(reinterpret_cast<float(*)[4]>(mapObj + 0xB8), 0, reinterpret_cast<Vec*>(mapObj + 0x58), mapObj[0x1A]);

	if (kMapOctTreeDefaultOffsetZ != *reinterpret_cast<float*>(mapObj + 0x40)) {
		CameraPcs.SetOffsetZBuff(*reinterpret_cast<float*>(mapObj + 0x40));
	}

	reinterpret_cast<CMapMesh*>(*reinterpret_cast<void**>(mapObj + 0xC))->SetRenderArray();
	DrawCharaShadowTypeMeshFlag_r(*reinterpret_cast<COctNode**>(thisBytes + 4));

	if (kMapOctTreeDefaultOffsetZ != *reinterpret_cast<float*>(mapObj + 0x40)) {
		CameraPcs.SetOffsetZBuff(*reinterpret_cast<float*>(mapObj + 0x40));
	}
}

/*
 * --INFO--
 * PAL Address: 0x8002e1c0
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void COctTree::SetDrawFlag()
{
	unsigned char* thisBytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* mapObj;
	float localMtx[4][4];

	if ((*reinterpret_cast<unsigned long*>(thisBytes + 0x48) & 1) != 0) {
		return;
	}

	mapObj = *reinterpret_cast<unsigned char**>(thisBytes + 8);
	if (mapObj[0x1D] != 1) {
		return;
	}

	PSMTXConcat(reinterpret_cast<float(*)[4]>(Ptr(&MapMng, 0x22928)), reinterpret_cast<float(*)[4]>(mapObj + 0xB8),
	            reinterpret_cast<float(*)[4]>(thisBytes + 0xC));
	PSMTXConcat(reinterpret_cast<float(*)[4]>(Ptr(&MapMng, 0x228F8)), reinterpret_cast<float(*)[4]>(mapObj + 0xB8), localMtx);
	PSMTXInverse(localMtx, localMtx);

	*reinterpret_cast<float*>(thisBytes + 0x3C) = localMtx[0][3];
	*reinterpret_cast<float*>(thisBytes + 0x40) = localMtx[1][3];
	*reinterpret_cast<float*>(thisBytes + 0x44) = localMtx[2][3];

	ClearFlag(1);
	DrawTypeMesh_r(*reinterpret_cast<COctNode**>(thisBytes + 4));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void COctTree::GetLocalPosition(Vec&, Vec&)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8002e028
 * PAL Size: 408b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void ClearLight_r(COctNode* octNode)
{
	int iVar1;
	int iVar2;
	COctNode* pCVar3;
	COctNode* pCVar4;
	COctNode* pCVar5;
	COctNode* pCVar6;
	COctNode* pCVar7;
	COctNode* pCVar8;
	int iVar9;
	int iVar10;
	int iVar11;
	int iVar12;
	int iVar13;

	if (*reinterpret_cast<unsigned short*>(Ptr(octNode, 0x3C)) != 0) {
		*reinterpret_cast<unsigned long*>(Ptr(octNode, 0x44)) = 0;
	}
	iVar1 = 0;
	do {
		pCVar8 = *reinterpret_cast<COctNode**>(Ptr(octNode, 0x1C));
		if (pCVar8 == 0) {
			return;
		}
		if (*reinterpret_cast<unsigned short*>(Ptr(pCVar8, 0x3C)) != 0) {
			*reinterpret_cast<unsigned long*>(Ptr(pCVar8, 0x44)) = 0;
		}
		iVar2 = 0;
		do {
			pCVar7 = *reinterpret_cast<COctNode**>(Ptr(pCVar8, 0x1C));
			if (pCVar7 == 0) break;
			if (*reinterpret_cast<unsigned short*>(Ptr(pCVar7, 0x3C)) != 0) {
				*reinterpret_cast<unsigned long*>(Ptr(pCVar7, 0x44)) = 0;
			}
			iVar13 = 0;
			do {
				pCVar6 = *reinterpret_cast<COctNode**>(Ptr(pCVar7, 0x1C));
				if (pCVar6 == 0) break;
				if (*reinterpret_cast<unsigned short*>(Ptr(pCVar6, 0x3C)) != 0) {
					*reinterpret_cast<unsigned long*>(Ptr(pCVar6, 0x44)) = 0;
				}
				iVar12 = 0;
				do {
					pCVar5 = *reinterpret_cast<COctNode**>(Ptr(pCVar6, 0x1C));
					if (pCVar5 == 0) break;
					if (*reinterpret_cast<unsigned short*>(Ptr(pCVar5, 0x3C)) != 0) {
						*reinterpret_cast<unsigned long*>(Ptr(pCVar5, 0x44)) = 0;
					}
					iVar11 = 0;
					do {
						pCVar4 = *reinterpret_cast<COctNode**>(Ptr(pCVar5, 0x1C));
						if (pCVar4 == 0) break;
						if (*reinterpret_cast<unsigned short*>(Ptr(pCVar4, 0x3C)) != 0) {
							*reinterpret_cast<unsigned long*>(Ptr(pCVar4, 0x44)) = 0;
						}
						iVar10 = 0;
						do {
							pCVar3 = *reinterpret_cast<COctNode**>(Ptr(pCVar4, 0x1C));
							if (pCVar3 == 0) break;
							if (*reinterpret_cast<unsigned short*>(Ptr(pCVar3, 0x3C)) != 0) {
								*reinterpret_cast<unsigned long*>(Ptr(pCVar3, 0x44)) = 0;
							}
							iVar9 = 0;
							do {
								if (*reinterpret_cast<COctNode**>(Ptr(pCVar3, 0x1C)) == 0) break;
								ClearLight_r(*reinterpret_cast<COctNode**>(Ptr(pCVar3, 0x1C)));
								iVar9 = iVar9 + 1;
								pCVar3 = reinterpret_cast<COctNode*>(Ptr(pCVar3, 4));
							} while (iVar9 < 8);
							iVar10 = iVar10 + 1;
							pCVar4 = reinterpret_cast<COctNode*>(Ptr(pCVar4, 4));
						} while (iVar10 < 8);
						iVar11 = iVar11 + 1;
						pCVar5 = reinterpret_cast<COctNode*>(Ptr(pCVar5, 4));
					} while (iVar11 < 8);
					iVar12 = iVar12 + 1;
					pCVar6 = reinterpret_cast<COctNode*>(Ptr(pCVar6, 4));
				} while (iVar12 < 8);
				iVar13 = iVar13 + 1;
				pCVar7 = reinterpret_cast<COctNode*>(Ptr(pCVar7, 4));
			} while (iVar13 < 8);
			iVar2 = iVar2 + 1;
			pCVar8 = reinterpret_cast<COctNode*>(Ptr(pCVar8, 4));
		} while (iVar2 < 8);
		iVar1 = iVar1 + 1;
		octNode = reinterpret_cast<COctNode*>(Ptr(octNode, 4));
		if (7 < iVar1) {
			return;
		}
	} while (true);
}

/*
 * --INFO--
 * PAL Address: 8002e004
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void COctTree::ClearLight()
{
	ClearLight_r(m_nodePool);
}

/*
 * --INFO--
 * PAL Address: 0x8002dca8
 * PAL Size: 860b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void InsertLight_r(COctNode* node)
{
	float boundMinX = node->m_boundMinX;
	bool xOverlap = false;
	bool xyOverlap = false;
	bool overlap = false;

	if (boundMinX < s_bound.m_min.x) {
		xOverlap = s_bound.m_min.x <= node->m_boundMaxX;
	} else {
		if (boundMinX > s_bound.m_min.x) {
			xOverlap = boundMinX <= s_bound.m_max.x;
		} else {
			xOverlap = true;
		}
	}

	if (xOverlap) {
		float boundMinY = node->m_boundMinY;
		if (boundMinY < s_bound.m_min.y) {
			xOverlap = s_bound.m_min.y <= node->m_boundMaxY;
		} else {
			if (boundMinY > s_bound.m_min.y) {
				xOverlap = boundMinY <= s_bound.m_max.y;
			} else {
				xOverlap = true;
			}
		}
		if (xOverlap) {
			xyOverlap = true;
		}
	}

	if (xyOverlap) {
		float boundMinZ = node->m_boundMinZ;
		if (boundMinZ < s_bound.m_min.z) {
			xyOverlap = s_bound.m_min.z <= node->m_boundMaxZ;
		} else {
			if (boundMinZ > s_bound.m_min.z) {
				xyOverlap = boundMinZ <= s_bound.m_max.z;
			} else {
				xyOverlap = true;
			}
		}
		if (xyOverlap) {
			overlap = true;
		}
	}

	if (!overlap) {
		return;
	}

	if (node->m_meshCount != 0) {
		unsigned long byteOffset = (s_insertLightBitIndex >> 3) & 0x1ffffffc;
		unsigned long* bits = reinterpret_cast<unsigned long*>(Ptr(&node->m_lightFlags, byteOffset));
		*bits |= 1UL << (s_insertLightBitIndex & 0x1f);
	}

	for (int i = 0; i < 8; i++) {
		COctNode* child = node->m_children[0];
		if (child == 0) {
			return;
		}

		float childBoundMinX = child->m_boundMinX;
		bool childXOverlap = false;
		bool childXYOverlap = false;
		bool childOverlap = false;
		if (childBoundMinX < s_bound.m_min.x) {
			childXOverlap = s_bound.m_min.x <= child->m_boundMaxX;
		} else {
			if (childBoundMinX > s_bound.m_min.x) {
				childXOverlap = childBoundMinX <= s_bound.m_max.x;
			} else {
				childXOverlap = true;
			}
		}

		if (childXOverlap) {
			float childBoundMinY = child->m_boundMinY;
			if (childBoundMinY < s_bound.m_min.y) {
				childXOverlap = s_bound.m_min.y <= child->m_boundMaxY;
			} else {
				if (childBoundMinY > s_bound.m_min.y) {
					childXOverlap = childBoundMinY <= s_bound.m_max.y;
				} else {
					childXOverlap = true;
				}
			}
			if (childXOverlap) {
				childXYOverlap = true;
			}
		}

		if (childXYOverlap) {
			float childBoundMinZ = child->m_boundMinZ;
			if (childBoundMinZ < s_bound.m_min.z) {
				childXYOverlap = s_bound.m_min.z <= child->m_boundMaxZ;
			} else {
				if (childBoundMinZ > s_bound.m_min.z) {
					childXYOverlap = childBoundMinZ <= s_bound.m_max.z;
				} else {
					childXYOverlap = true;
				}
			}
			if (childXYOverlap) {
				childOverlap = true;
			}
		}

		if (childOverlap) {
			if (child->m_meshCount != 0) {
				unsigned long byteOffset = (s_insertLightBitIndex >> 3) & 0x1ffffffc;
				unsigned long* bits = reinterpret_cast<unsigned long*>(Ptr(&child->m_lightFlags, byteOffset));
				*bits |= 1UL << (s_insertLightBitIndex & 0x1f);
			}

			for (int j = 0; j < 8; j++) {
				COctNode* grandChild = child->m_children[0];
				if (grandChild == 0) {
					break;
				}

				if ((reinterpret_cast<CBound*>(&s_bound)->CheckCross(*reinterpret_cast<CBound*>(grandChild))) != 0) {
					if (grandChild->m_meshCount != 0) {
						setbit32(reinterpret_cast<unsigned long*>(Ptr(grandChild, 0x44)), s_insertLightBitIndex);
					}

					for (int k = 0; k < 8; k++) {
						COctNode* greatGrandChild = grandChild->m_children[0];
						if (greatGrandChild == 0) {
							break;
						}
						InsertLight_r(greatGrandChild);
						grandChild = reinterpret_cast<COctNode*>(Ptr(grandChild, 4));
					}
				}
				child = reinterpret_cast<COctNode*>(Ptr(child, 4));
			}
		}
		node = reinterpret_cast<COctNode*>(Ptr(node, 4));
	}
}

/*
 * --INFO--
 * PAL Address: 0x8002dbd8
 * PAL Size: 208b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void COctTree::InsertLight(long bitIndex, Vec& position, float radius, unsigned long mask)
{
	Mtx inverseMtx;
	Vec localPosition;
	unsigned char* mapObj = reinterpret_cast<unsigned char*>(m_mapObject);

	if ((m_type != 0) || ((*reinterpret_cast<unsigned long*>(mapObj + 0x38) & mask) == 0)) {
		return;
	}

	s_insertLightBitIndex = bitIndex;
	PSMTXInverse(reinterpret_cast<MtxPtr>(mapObj + 0xB8), inverseMtx);
	PSMTXMultVec(inverseMtx, &position, &localPosition);

	s_bound.m_min.x = localPosition.x - radius;
	s_bound.m_max.x = localPosition.x + radius;
	s_bound.m_min.y = localPosition.y - radius;
	s_bound.m_min.z = localPosition.z - radius;
	s_bound.m_max.y = localPosition.y + radius;
	s_bound.m_max.z = localPosition.z + radius;

	InsertLight_r(m_nodePool);
}

/*
 * --INFO--
 * PAL Address: 0x8002da40
 * PAL Size: 408b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void ClearShadow_r(COctNode* node)
{
	unsigned char* nodeBytes = (unsigned char*)node;

	if (*(unsigned short*)(nodeBytes + 0x3c) != 0) {
		*(void**)(nodeBytes + 0x48) = 0;
	}

	COctNode** children = (COctNode**)(nodeBytes + 0x1c);
	for (int i = 0; i < 8; i++) {
		COctNode* child = children[i];
		if (child == 0) {
			return;
		}
		ClearShadow_r(child);
	}
}

/*
 * --INFO--
 * PAL Address: 8002da1c
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void COctTree::ClearShadow()
{
	ClearShadow_r(m_nodePool);
}

/*
 * --INFO--
 * PAL Address: 0x8002d628
 * PAL Size: 980b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void InsertShadow_r(COctNode* node)
{
	float boundMinX = node->m_boundMinX;
	bool xOverlap = false;
	bool xyOverlap = false;
	bool overlap = false;

	if (boundMinX < s_bound.m_min.x) {
		xOverlap = s_bound.m_min.x <= node->m_boundMaxX;
	} else {
		if (boundMinX > s_bound.m_min.x) {
			xOverlap = boundMinX <= s_bound.m_max.x;
		} else {
			xOverlap = true;
		}
	}

	if (xOverlap) {
		float boundMinY = node->m_boundMinY;
		if (boundMinY < s_bound.m_min.y) {
			xOverlap = s_bound.m_min.y <= node->m_boundMaxY;
		} else {
			if (boundMinY > s_bound.m_min.y) {
				xOverlap = boundMinY <= s_bound.m_max.y;
			} else {
				xOverlap = true;
			}
		}
		if (xOverlap) {
			xyOverlap = true;
		}
	}

	if (xyOverlap) {
		float boundMinZ = node->m_boundMinZ;
		if (boundMinZ < s_bound.m_min.z) {
			xyOverlap = s_bound.m_min.z <= node->m_boundMaxZ;
		} else {
			if (boundMinZ > s_bound.m_min.z) {
				xyOverlap = boundMinZ <= s_bound.m_max.z;
			} else {
				xyOverlap = true;
			}
		}
		if (xyOverlap) {
			overlap = true;
		}
	}

	if (!overlap) {
		return;
	}

	if ((s_insertShadowDepth > 2) && (node->m_meshCount != 0)) {
		unsigned long byteOffset = (s_insertShadowBitIndex >> 3) & 0x1ffffffc;
		unsigned long* bits = reinterpret_cast<unsigned long*>(Ptr(&node->m_shadowFlags, byteOffset));
		*bits |= 1UL << (s_insertShadowBitIndex & 0x1f);
	}

	for (int i = 0; i < 8; i++) {
		COctNode* child = node->m_children[0];
		if (child == 0) {
			return;
		}

		s_insertShadowDepth++;

		float childBoundMinX = child->m_boundMinX;
		bool childXOverlap = false;
		bool childXYOverlap = false;
		bool childOverlap = false;
		if (childBoundMinX < s_bound.m_min.x) {
			childXOverlap = s_bound.m_min.x <= child->m_boundMaxX;
		} else {
			if (childBoundMinX > s_bound.m_min.x) {
				childXOverlap = childBoundMinX <= s_bound.m_max.x;
			} else {
				childXOverlap = true;
			}
		}

		if (childXOverlap) {
			float childBoundMinY = child->m_boundMinY;
			if (childBoundMinY < s_bound.m_min.y) {
				childXOverlap = s_bound.m_min.y <= child->m_boundMaxY;
			} else {
				if (childBoundMinY > s_bound.m_min.y) {
					childXOverlap = childBoundMinY <= s_bound.m_max.y;
				} else {
					childXOverlap = true;
				}
			}
			if (childXOverlap) {
				childXYOverlap = true;
			}
		}

		if (childXYOverlap) {
			float childBoundMinZ = child->m_boundMinZ;
			if (childBoundMinZ < s_bound.m_min.z) {
				childXYOverlap = s_bound.m_min.z <= child->m_boundMaxZ;
			} else {
				if (childBoundMinZ > s_bound.m_min.z) {
					childXYOverlap = childBoundMinZ <= s_bound.m_max.z;
				} else {
					childXYOverlap = true;
				}
			}
			if (childXYOverlap) {
				childOverlap = true;
			}
		}

		if (childOverlap) {
			if ((s_insertShadowDepth > 2) && (child->m_meshCount != 0)) {
				unsigned long byteOffset = (s_insertShadowBitIndex >> 3) & 0x1ffffffc;
				unsigned long* bits = reinterpret_cast<unsigned long*>(Ptr(&child->m_shadowFlags, byteOffset));
				*bits |= 1UL << (s_insertShadowBitIndex & 0x1f);
			}

			for (int j = 0; j < 8; j++) {
				COctNode* grandChild = child->m_children[0];
				if (grandChild == 0) {
					break;
				}

				s_insertShadowDepth++;

				if ((reinterpret_cast<CBound*>(&s_bound)->CheckCross(*reinterpret_cast<CBound*>(grandChild))) != 0) {
					if ((s_insertShadowDepth > 2) && (grandChild->m_meshCount != 0)) {
						setbit32(reinterpret_cast<unsigned long*>(Ptr(grandChild, 0x48)), s_insertShadowBitIndex);
					}

					for (int k = 0; k < 8; k++) {
						COctNode* greatGrandChild = grandChild->m_children[0];
						if (greatGrandChild == 0) {
							break;
						}
						s_insertShadowDepth++;
						InsertShadow_r(greatGrandChild);
						grandChild = reinterpret_cast<COctNode*>(Ptr(grandChild, 4));
						s_insertShadowDepth--;
					}
				}
				child = reinterpret_cast<COctNode*>(Ptr(child, 4));
				s_insertShadowDepth--;
			}
		}
		node = reinterpret_cast<COctNode*>(Ptr(node, 4));
		s_insertShadowDepth--;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8002d550
 * PAL Size: 216b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void COctTree::InsertShadow(long bitIndex, Vec& position, CBound& bound)
{
	Vec localPosition;
	Mtx inverseMtx;
	float* srcBound = reinterpret_cast<float*>(&bound);

	if (m_type == 0) {
		s_insertShadowBitIndex = bitIndex;
		PSMTXInverse(reinterpret_cast<MtxPtr>(reinterpret_cast<unsigned char*>(m_mapObject) + 0xB8), inverseMtx);
		PSMTXMultVec(inverseMtx, &position, &localPosition);

		s_bound.m_min.x = srcBound[0];
		s_bound.m_min.y = srcBound[1];
		s_bound.m_min.z = srcBound[2];
		s_bound.m_max.x = srcBound[3];
		s_bound.m_max.y = srcBound[4];
		s_bound.m_max.z = srcBound[5];

		PSVECAdd(&s_bound.m_min, &localPosition, &s_bound.m_min);
		PSVECAdd(&s_bound.m_max, &localPosition, &s_bound.m_max);

		s_insertShadowDepth = 0;
		InsertShadow_r(m_nodePool);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CBound::operator= (const CBound&)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8002d308
 * PAL Size: 584b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void ClearFlag_r(COctNode* node)
{
	COctNode* child1;
	COctNode* child2;
	COctNode* child3;
	COctNode* child4;
	COctNode* child5;
	COctNode* child6;
	COctNode* child7;
	COctNode* child8;

	if (*reinterpret_cast<unsigned short*>(Ptr(node, 0x3C)) != 0) {
		*reinterpret_cast<unsigned long*>(Ptr(node, 0x40)) &= s_clearFlagMask;
	}

	for (int i = 0; i < 8; i++) {
		child1 = *reinterpret_cast<COctNode**>(Ptr(node, 0x1C));
		if (child1 == 0) {
			return;
		}
		if (*reinterpret_cast<unsigned short*>(Ptr(child1, 0x3C)) != 0) {
			*reinterpret_cast<unsigned long*>(Ptr(child1, 0x40)) &= s_clearFlagMask;
		}

		for (int j = 0; j < 8; j++) {
			child2 = *reinterpret_cast<COctNode**>(Ptr(child1, 0x1C));
			if (child2 == 0) {
				break;
			}
			if (*reinterpret_cast<unsigned short*>(Ptr(child2, 0x3C)) != 0) {
				*reinterpret_cast<unsigned long*>(Ptr(child2, 0x40)) &= s_clearFlagMask;
			}

			for (int k = 0; k < 8; k++) {
				child3 = *reinterpret_cast<COctNode**>(Ptr(child2, 0x1C));
				if (child3 == 0) {
					break;
				}
				if (*reinterpret_cast<unsigned short*>(Ptr(child3, 0x3C)) != 0) {
					*reinterpret_cast<unsigned long*>(Ptr(child3, 0x40)) &= s_clearFlagMask;
				}

				for (int m = 0; m < 8; m++) {
					child4 = *reinterpret_cast<COctNode**>(Ptr(child3, 0x1C));
					if (child4 == 0) {
						break;
					}
					if (*reinterpret_cast<unsigned short*>(Ptr(child4, 0x3C)) != 0) {
						*reinterpret_cast<unsigned long*>(Ptr(child4, 0x40)) &= s_clearFlagMask;
					}

					for (int n = 0; n < 8; n++) {
						child5 = *reinterpret_cast<COctNode**>(Ptr(child4, 0x1C));
						if (child5 == 0) {
							break;
						}
						if (*reinterpret_cast<unsigned short*>(Ptr(child5, 0x3C)) != 0) {
							*reinterpret_cast<unsigned long*>(Ptr(child5, 0x40)) &= s_clearFlagMask;
						}

						for (int o = 0; o < 8; o++) {
							child6 = *reinterpret_cast<COctNode**>(Ptr(child5, 0x1C));
							if (child6 == 0) {
								break;
							}
							if (*reinterpret_cast<unsigned short*>(Ptr(child6, 0x3C)) != 0) {
								*reinterpret_cast<unsigned long*>(Ptr(child6, 0x40)) &= s_clearFlagMask;
							}

							for (int p = 0; p < 8; p++) {
								child7 = *reinterpret_cast<COctNode**>(Ptr(child6, 0x1C));
								if (child7 == 0) {
									break;
								}
								if (*reinterpret_cast<unsigned short*>(Ptr(child7, 0x3C)) != 0) {
									*reinterpret_cast<unsigned long*>(Ptr(child7, 0x40)) &= s_clearFlagMask;
								}

								for (int q = 0; q < 8; q++) {
									child8 = *reinterpret_cast<COctNode**>(Ptr(child7, 0x1C));
									if (child8 == 0) {
										break;
									}
									if (*reinterpret_cast<unsigned short*>(Ptr(child8, 0x3C)) != 0) {
										*reinterpret_cast<unsigned long*>(Ptr(child8, 0x40)) &= s_clearFlagMask;
									}

									for (int r = 0; r < 8; r++) {
										if (*reinterpret_cast<COctNode**>(Ptr(child8, 0x1C)) == 0) {
											break;
										}
										ClearFlag_r(*reinterpret_cast<COctNode**>(Ptr(child8, 0x1C)));
										child8 = reinterpret_cast<COctNode*>(Ptr(child8, 4));
									}

									child7 = reinterpret_cast<COctNode*>(Ptr(child7, 4));
								}

								child6 = reinterpret_cast<COctNode*>(Ptr(child6, 4));
							}

							child5 = reinterpret_cast<COctNode*>(Ptr(child5, 4));
						}

						child4 = reinterpret_cast<COctNode*>(Ptr(child4, 4));
					}

					child3 = reinterpret_cast<COctNode*>(Ptr(child3, 4));
				}

				child2 = reinterpret_cast<COctNode*>(Ptr(child2, 4));
			}

			child1 = reinterpret_cast<COctNode*>(Ptr(child1, 4));
		}

		node = reinterpret_cast<COctNode*>(Ptr(node, 4));
	}
}

/*
 * --INFO--
 * PAL Address: 8002d2dc
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void COctTree::ClearFlag(unsigned long flag)
{
	s_clearFlagMask = ~flag;
	ClearFlag_r(m_nodePool);
}

/*
 * --INFO--
 * PAL Address: 0x8002cef0
 * PAL Size: 1004b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int COctTree::CheckHitCylinder_r(COctNode* node)
{
	float boundMinX = *reinterpret_cast<float*>(Ptr(node, 0x0));
	bool xOverlap = false;
	bool xyOverlap = false;
	bool overlap = false;

	if (boundMinX < *reinterpret_cast<float*>(Ptr(&s_cyl, 0x28))) {
		xOverlap = *reinterpret_cast<float*>(Ptr(&s_cyl, 0x28)) <= *reinterpret_cast<float*>(Ptr(node, 0xC));
	} else {
		if (boundMinX > *reinterpret_cast<float*>(Ptr(&s_cyl, 0x28))) {
			xOverlap = boundMinX <= *reinterpret_cast<float*>(Ptr(&s_cyl, 0x34));
		} else {
			xOverlap = true;
		}
	}

	if (xOverlap) {
		float boundMinY = *reinterpret_cast<float*>(Ptr(node, 0x4));
		if (boundMinY < *reinterpret_cast<float*>(Ptr(&s_cyl, 0x2C))) {
			xOverlap = *reinterpret_cast<float*>(Ptr(&s_cyl, 0x2C)) <= *reinterpret_cast<float*>(Ptr(node, 0x10));
		} else {
			if (boundMinY > *reinterpret_cast<float*>(Ptr(&s_cyl, 0x2C))) {
				xOverlap = boundMinY <= *reinterpret_cast<float*>(Ptr(&s_cyl, 0x38));
			} else {
				xOverlap = true;
			}
		}
		if (xOverlap) {
			xyOverlap = true;
		}
	}

	if (xyOverlap) {
		float boundMinZ = *reinterpret_cast<float*>(Ptr(node, 0x8));
		if (boundMinZ < *reinterpret_cast<float*>(Ptr(&s_cyl, 0x30))) {
			xyOverlap = *reinterpret_cast<float*>(Ptr(&s_cyl, 0x30)) <= *reinterpret_cast<float*>(Ptr(node, 0x14));
		} else {
			if (boundMinZ > *reinterpret_cast<float*>(Ptr(&s_cyl, 0x30))) {
				xyOverlap = boundMinZ <= *reinterpret_cast<float*>(Ptr(&s_cyl, 0x3C));
			} else {
				xyOverlap = true;
			}
		}
		if (xyOverlap) {
			overlap = true;
		}
	}

	if (!overlap) {
		return 0;
	}

	if ((*reinterpret_cast<unsigned short*>(Ptr(node, 0x3C)) != 0) &&
	    ((*reinterpret_cast<CMapHit**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 8)), 0xC)))
	         ->CheckHitCylinder((CMapCylinder*)&s_cyl, &s_mvec,
	                            *reinterpret_cast<unsigned short*>(Ptr(node, 0x3E)),
	                            *reinterpret_cast<unsigned short*>(Ptr(node, 0x3C)),
	                            s_checkHitCylinderMask) != 0)) {
		return 1;
	}

	for (int i = 0; i < 8; i++) {
		COctNode* child = *reinterpret_cast<COctNode**>(Ptr(node, 0x1C));
		if (child == 0) {
			return 0;
		}

		float childBoundMinX = *reinterpret_cast<float*>(Ptr(child, 0x0));
		bool childXOverlap = false;
		bool childXYOverlap = false;
		bool childOverlap = false;
		if (childBoundMinX < *reinterpret_cast<float*>(Ptr(&s_cyl, 0x28))) {
			childXOverlap = *reinterpret_cast<float*>(Ptr(&s_cyl, 0x28)) <= *reinterpret_cast<float*>(Ptr(child, 0xC));
		} else {
			if (childBoundMinX > *reinterpret_cast<float*>(Ptr(&s_cyl, 0x28))) {
				childXOverlap = childBoundMinX <= *reinterpret_cast<float*>(Ptr(&s_cyl, 0x34));
			} else {
				childXOverlap = true;
			}
		}

		if (childXOverlap) {
			float childBoundMinY = *reinterpret_cast<float*>(Ptr(child, 0x4));
			if (childBoundMinY < *reinterpret_cast<float*>(Ptr(&s_cyl, 0x2C))) {
				childXOverlap = *reinterpret_cast<float*>(Ptr(&s_cyl, 0x2C)) <= *reinterpret_cast<float*>(Ptr(child, 0x10));
			} else {
				if (childBoundMinY > *reinterpret_cast<float*>(Ptr(&s_cyl, 0x2C))) {
					childXOverlap = childBoundMinY <= *reinterpret_cast<float*>(Ptr(&s_cyl, 0x38));
				} else {
					childXOverlap = true;
				}
			}
			if (childXOverlap) {
				childXYOverlap = true;
			}
		}

		if (childXYOverlap) {
			float childBoundMinZ = *reinterpret_cast<float*>(Ptr(child, 0x8));
			if (childBoundMinZ < *reinterpret_cast<float*>(Ptr(&s_cyl, 0x30))) {
				childXYOverlap = *reinterpret_cast<float*>(Ptr(&s_cyl, 0x30)) <= *reinterpret_cast<float*>(Ptr(child, 0x14));
			} else {
				if (childBoundMinZ > *reinterpret_cast<float*>(Ptr(&s_cyl, 0x30))) {
					childXYOverlap = childBoundMinZ <= *reinterpret_cast<float*>(Ptr(&s_cyl, 0x3C));
				} else {
					childXYOverlap = true;
				}
			}
			if (childXYOverlap) {
				childOverlap = true;
			}
		}

		if (childOverlap) {
			if ((*reinterpret_cast<unsigned short*>(Ptr(child, 0x3C)) != 0) &&
			    ((*reinterpret_cast<CMapHit**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 8)), 0xC)))
			         ->CheckHitCylinder((CMapCylinder*)&s_cyl, &s_mvec,
			                            *reinterpret_cast<unsigned short*>(Ptr(child, 0x3E)),
			                            *reinterpret_cast<unsigned short*>(Ptr(child, 0x3C)),
			                            s_checkHitCylinderMask) != 0)) {
				return 1;
			}

			for (int j = 0; j < 8; j++) {
				COctNode* grandChild = *reinterpret_cast<COctNode**>(Ptr(child, 0x1C));
				if (grandChild == 0) {
					break;
				}

				if ((reinterpret_cast<CBound*>(grandChild)->CheckCross(*reinterpret_cast<CBound*>(Ptr(&s_cyl, 0x28)))) != 0) {
					if ((*reinterpret_cast<unsigned short*>(Ptr(grandChild, 0x3C)) != 0) &&
					    ((*reinterpret_cast<CMapHit**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 8)), 0xC)))
					         ->CheckHitCylinder((CMapCylinder*)&s_cyl, &s_mvec,
					                            *reinterpret_cast<unsigned short*>(Ptr(grandChild, 0x3E)),
					                            *reinterpret_cast<unsigned short*>(Ptr(grandChild, 0x3C)),
					                            s_checkHitCylinderMask) != 0)) {
						return 1;
					}

					for (int k = 0; k < 8; k++) {
						COctNode* greatGrandChild = *reinterpret_cast<COctNode**>(Ptr(grandChild, 0x1C));
						if (greatGrandChild == 0) {
							break;
						}

						if (CheckHitCylinder_r(greatGrandChild) != 0) {
							return 1;
						}
						grandChild = reinterpret_cast<COctNode*>(Ptr(grandChild, 4));
					}
				}
				child = reinterpret_cast<COctNode*>(Ptr(child, 4));
			}
		}
		node = reinterpret_cast<COctNode*>(Ptr(node, 4));
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8002cd38
 * PAL Size: 440b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int COctTree::CheckHitCylinder(CMapCylinder* cylinder, Vec* move, unsigned long flag)
{
	float radiusPad;
	Mtx inverseMtx;
	CMapHit* mapHit;

	if (m_type == 2) {
		mapHit = *reinterpret_cast<CMapHit**>(reinterpret_cast<u8*>(m_mapObject) + 0xC);
		if (mapHit != 0) {
			PSMTXInverse(reinterpret_cast<MtxPtr>(reinterpret_cast<u8*>(m_mapObject) + 0xB8), inverseMtx);
			PSMTXMultVec(inverseMtx, &cylinder->m_bottom, &s_cyl.m_bottom);
			PSMTXMultVec(inverseMtx, &cylinder->m_direction, &s_cyl.m_direction);
			PSMTXMultVecSR(inverseMtx, reinterpret_cast<Vec*>(&cylinder->m_radius), reinterpret_cast<Vec*>(&s_cyl.m_radius));
			PSMTXMultVecSR(inverseMtx, move, &s_mvec);

			s_cyl.m_top.y = cylinder->m_top.y;
			radiusPad = kOctTreeCylinderPad + s_cyl.m_top.y;
			if (s_cyl.m_bottom.x < s_cyl.m_direction.x) {
				s_cyl.m_top.z = s_cyl.m_bottom.x - radiusPad;
				s_cyl.m_direction2.z = s_cyl.m_direction.x + radiusPad;
			} else {
				s_cyl.m_top.z = s_cyl.m_direction.x - radiusPad;
				s_cyl.m_direction2.z = s_cyl.m_bottom.x + radiusPad;
			}

			radiusPad = kOctTreeCylinderPad + s_cyl.m_top.y;
			if (s_cyl.m_bottom.y < s_cyl.m_direction.y) {
				s_cyl.m_direction2.x = s_cyl.m_bottom.y - radiusPad;
				s_cyl.m_radius2 = s_cyl.m_direction.y + radiusPad;
			} else {
				s_cyl.m_direction2.x = s_cyl.m_direction.y - radiusPad;
				s_cyl.m_radius2 = s_cyl.m_bottom.y + radiusPad;
			}

			radiusPad = kOctTreeCylinderPad + s_cyl.m_top.y;
			if (s_cyl.m_bottom.z < s_cyl.m_direction.z) {
				s_cyl.m_direction2.y = s_cyl.m_bottom.z - radiusPad;
				s_cyl.m_height2 = s_cyl.m_direction.z + radiusPad;
			} else {
				s_cyl.m_direction2.y = s_cyl.m_direction.z - radiusPad;
				s_cyl.m_height2 = s_cyl.m_bottom.z + radiusPad;
			}
			s_checkHitCylinderMask = flag;
			if (CheckHitCylinder_r(m_nodePool) != 0) {
				return 1;
			}
		}
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8002c8a8
 * PAL Size: 896b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void COctTree::CheckHitCylinderNear_r(COctNode* octNode)
{
	float boundMinX = *reinterpret_cast<float*>(Ptr(octNode, 0x0));
	bool xOverlap = false;
	bool xyOverlap = false;
	bool overlap = false;

	if (boundMinX < *reinterpret_cast<float*>(Ptr(&s_cyl, 0x28))) {
		xOverlap = *reinterpret_cast<float*>(Ptr(&s_cyl, 0x28)) <= *reinterpret_cast<float*>(Ptr(octNode, 0xC));
	} else {
		if (boundMinX > *reinterpret_cast<float*>(Ptr(&s_cyl, 0x28))) {
			xOverlap = boundMinX <= *reinterpret_cast<float*>(Ptr(&s_cyl, 0x34));
		} else {
			xOverlap = true;
		}
	}

	if (xOverlap) {
		float boundMinY = *reinterpret_cast<float*>(Ptr(octNode, 0x4));
		if (boundMinY < *reinterpret_cast<float*>(Ptr(&s_cyl, 0x2C))) {
			xOverlap = *reinterpret_cast<float*>(Ptr(&s_cyl, 0x2C)) <= *reinterpret_cast<float*>(Ptr(octNode, 0x10));
		} else {
			if (boundMinY > *reinterpret_cast<float*>(Ptr(&s_cyl, 0x2C))) {
				xOverlap = boundMinY <= *reinterpret_cast<float*>(Ptr(&s_cyl, 0x38));
			} else {
				xOverlap = true;
			}
		}
		if (xOverlap) {
			xyOverlap = true;
		}
	}

	if (xyOverlap) {
		float boundMinZ = *reinterpret_cast<float*>(Ptr(octNode, 0x8));
		if (boundMinZ < *reinterpret_cast<float*>(Ptr(&s_cyl, 0x30))) {
			xyOverlap = *reinterpret_cast<float*>(Ptr(&s_cyl, 0x30)) <= *reinterpret_cast<float*>(Ptr(octNode, 0x14));
		} else {
			if (boundMinZ > *reinterpret_cast<float*>(Ptr(&s_cyl, 0x30))) {
				xyOverlap = boundMinZ <= *reinterpret_cast<float*>(Ptr(&s_cyl, 0x3C));
			} else {
				xyOverlap = true;
			}
		}
		if (xyOverlap) {
			overlap = true;
		}
	}

	if (!overlap) {
		return;
	}

	if (*reinterpret_cast<unsigned short*>(Ptr(octNode, 0x3C)) != 0) {
		(*reinterpret_cast<CMapHit**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 8)), 0xC)))
		    ->CheckHitCylinderNear((CMapCylinder*)&s_cyl, &s_mvec,
		                           *reinterpret_cast<unsigned short*>(Ptr(octNode, 0x3E)),
		                           *reinterpret_cast<unsigned short*>(Ptr(octNode, 0x3C)),
		                           s_checkHitCylinderMask);
	}

	for (int i = 0; i < 8; i++) {
		COctNode* child = *reinterpret_cast<COctNode**>(Ptr(octNode, 0x1C));
		if (child == 0) {
			return;
		}

		float childBoundMinX = *reinterpret_cast<float*>(Ptr(child, 0x0));
		bool childXOverlap = false;
		bool childXYOverlap = false;
		bool childOverlap = false;
		if (childBoundMinX < *reinterpret_cast<float*>(Ptr(&s_cyl, 0x28))) {
			childXOverlap = *reinterpret_cast<float*>(Ptr(&s_cyl, 0x28)) <= *reinterpret_cast<float*>(Ptr(child, 0xC));
		} else {
			if (childBoundMinX > *reinterpret_cast<float*>(Ptr(&s_cyl, 0x28))) {
				childXOverlap = childBoundMinX <= *reinterpret_cast<float*>(Ptr(&s_cyl, 0x34));
			} else {
				childXOverlap = true;
			}
		}

		if (childXOverlap) {
			float childBoundMinY = *reinterpret_cast<float*>(Ptr(child, 0x4));
			if (childBoundMinY < *reinterpret_cast<float*>(Ptr(&s_cyl, 0x2C))) {
				childXOverlap = *reinterpret_cast<float*>(Ptr(&s_cyl, 0x2C)) <= *reinterpret_cast<float*>(Ptr(child, 0x10));
			} else {
				if (childBoundMinY > *reinterpret_cast<float*>(Ptr(&s_cyl, 0x2C))) {
					childXOverlap = childBoundMinY <= *reinterpret_cast<float*>(Ptr(&s_cyl, 0x38));
				} else {
					childXOverlap = true;
				}
			}
			if (childXOverlap) {
				childXYOverlap = true;
			}
		}

		if (childXYOverlap) {
			float childBoundMinZ = *reinterpret_cast<float*>(Ptr(child, 0x8));
			if (childBoundMinZ < *reinterpret_cast<float*>(Ptr(&s_cyl, 0x30))) {
				childXYOverlap = *reinterpret_cast<float*>(Ptr(&s_cyl, 0x30)) <= *reinterpret_cast<float*>(Ptr(child, 0x14));
			} else {
				if (childBoundMinZ > *reinterpret_cast<float*>(Ptr(&s_cyl, 0x30))) {
					childXYOverlap = childBoundMinZ <= *reinterpret_cast<float*>(Ptr(&s_cyl, 0x3C));
				} else {
					childXYOverlap = true;
				}
			}
			if (childXYOverlap) {
				childOverlap = true;
			}
		}

		if (childOverlap) {
			if (*reinterpret_cast<unsigned short*>(Ptr(child, 0x3C)) != 0) {
				(*reinterpret_cast<CMapHit**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 8)), 0xC)))
				    ->CheckHitCylinderNear((CMapCylinder*)&s_cyl, &s_mvec,
				                           *reinterpret_cast<unsigned short*>(Ptr(child, 0x3E)),
				                           *reinterpret_cast<unsigned short*>(Ptr(child, 0x3C)),
				                           s_checkHitCylinderMask);
			}

			for (int j = 0; j < 8; j++) {
				COctNode* grandChild = *reinterpret_cast<COctNode**>(Ptr(child, 0x1C));
				if (grandChild == 0) {
					break;
				}

				if ((reinterpret_cast<CBound*>(grandChild)->CheckCross(*reinterpret_cast<CBound*>(Ptr(&s_cyl, 0x28)))) != 0) {
					if (*reinterpret_cast<unsigned short*>(Ptr(grandChild, 0x3C)) != 0) {
						(*reinterpret_cast<CMapHit**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 8)), 0xC)))
						    ->CheckHitCylinderNear((CMapCylinder*)&s_cyl, &s_mvec,
						                           *reinterpret_cast<unsigned short*>(Ptr(grandChild, 0x3E)),
						                           *reinterpret_cast<unsigned short*>(Ptr(grandChild, 0x3C)),
						                           s_checkHitCylinderMask);
					}

					for (int k = 0; k < 8; k++) {
						COctNode* greatGrandChild = *reinterpret_cast<COctNode**>(Ptr(grandChild, 0x1C));
						if (greatGrandChild == 0) {
							break;
						}
						CheckHitCylinderNear_r(greatGrandChild);
						grandChild = reinterpret_cast<COctNode*>(Ptr(grandChild, 4));
					}
				}
				child = reinterpret_cast<COctNode*>(Ptr(child, 4));
			}
		}
		octNode = reinterpret_cast<COctNode*>(Ptr(octNode, 4));
	}
}

/*
 * --INFO--
 * PAL Address: 0x8002c704
 * PAL Size: 420b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void COctTree::CheckHitCylinderNear(CMapCylinder* cylinder, Vec* move, unsigned long flag)
{
	float radiusPad;
	Mtx inverseMtx;
	CMapHit* mapHit;

	if (m_type == 2) {
		mapHit = *reinterpret_cast<CMapHit**>(reinterpret_cast<u8*>(m_mapObject) + 0xC);
		if (mapHit != 0) {
			PSMTXInverse(reinterpret_cast<MtxPtr>(reinterpret_cast<u8*>(m_mapObject) + 0xB8), inverseMtx);
			PSMTXMultVec(inverseMtx, &cylinder->m_bottom, &s_cyl.m_bottom);
			PSMTXMultVec(inverseMtx, &cylinder->m_direction, &s_cyl.m_direction);
			PSMTXMultVecSR(inverseMtx, reinterpret_cast<Vec*>(&cylinder->m_radius), reinterpret_cast<Vec*>(&s_cyl.m_radius));
			PSMTXMultVecSR(inverseMtx, move, &s_mvec);

			s_cyl.m_top.y = cylinder->m_top.y;
			radiusPad = kOctTreeCylinderPad + s_cyl.m_top.y;
			if (s_cyl.m_bottom.x < s_cyl.m_direction.x) {
				s_cyl.m_top.z = s_cyl.m_bottom.x - radiusPad;
				s_cyl.m_direction2.z = s_cyl.m_direction.x + radiusPad;
			} else {
				s_cyl.m_top.z = s_cyl.m_direction.x - radiusPad;
				s_cyl.m_direction2.z = s_cyl.m_bottom.x + radiusPad;
			}

			radiusPad = kOctTreeCylinderPad + s_cyl.m_top.y;
			if (s_cyl.m_bottom.y < s_cyl.m_direction.y) {
				s_cyl.m_direction2.x = s_cyl.m_bottom.y - radiusPad;
				s_cyl.m_radius2 = s_cyl.m_direction.y + radiusPad;
			} else {
				s_cyl.m_direction2.x = s_cyl.m_direction.y - radiusPad;
				s_cyl.m_radius2 = s_cyl.m_bottom.y + radiusPad;
			}

			radiusPad = kOctTreeCylinderPad + s_cyl.m_top.y;
			if (s_cyl.m_bottom.z < s_cyl.m_direction.z) {
				s_cyl.m_direction2.y = s_cyl.m_bottom.z - radiusPad;
				s_cyl.m_height2 = s_cyl.m_direction.z + radiusPad;
			} else {
				s_cyl.m_direction2.y = s_cyl.m_direction.z - radiusPad;
				s_cyl.m_height2 = s_cyl.m_bottom.z + radiusPad;
			}
			s_checkHitCylinderMask = flag;
			CheckHitCylinderNear_r(m_nodePool);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 8002ef24
 * PAL Size: 36b
 */
void CMaterialMan::LockEnv()
{
	CMaterialManEnvRaw* env = reinterpret_cast<CMaterialManEnvRaw*>(this);

	env->m_stdTexMapId = env->m_texMapIdCur;
	env->m_stdTexMtx = env->m_texMtxCur;
	env->m_stdTexCoordId = env->m_texCoordIdCur;
	env->m_stdEnvTevBit = env->m_curEnvTevBit;
}

/*
 * --INFO--
 * PAL Address: 8002ef48
 * PAL Size: 84b
 */
void CMaterialMan::InitEnv()
{
	CMaterialManEnvRaw* env = reinterpret_cast<CMaterialManEnvRaw*>(this);

	env->m_curEnvTevBit = 0x000ACE0F;
	env->m_activeEnvTevBit = 0xFFFFFFFF;
	env->m_alphaRef = 0xFF;
	env->m_stdTexMapId = 0;
	env->m_texMapIdCur = 0;
	env->m_stdTexMtx = 0x1E;
	env->m_texMtxCur = 0x1E;
	env->m_stdTexCoordId = 0;
	env->m_texCoordIdCur = 0;
	env->m_blendMode = 0xFF;
	env->m_fogEnable = 0xFF;
	env->m_lockedEnvTevBit = 0;
	env->m_lockedEnvUnknown5c = 0;
	env->m_shadowKColorMask = 0;
}

/*
 * --INFO--
 * PAL Address: 8002cc28
 * PAL Size: 272b
 */
int CBound::CheckCross(CBound& other)
{
	bool xOverlap;
	bool xyOverlap;
	bool overlap;

	xyOverlap = false;
	overlap = false;
	if (m_min.x < other.m_min.x) {
		xOverlap = other.m_min.x <= m_max.x;
	} else {
		if (m_min.x > other.m_min.x) {
			xOverlap = m_min.x <= other.m_max.x;
		} else {
			xOverlap = true;
		}
	}

	if (xOverlap) {
		if (m_min.y < other.m_min.y) {
			xOverlap = other.m_min.y <= m_max.y;
		} else {
			if (m_min.y > other.m_min.y) {
				xOverlap = m_min.y <= other.m_max.y;
			} else {
				xOverlap = true;
			}
		}

		if (xOverlap) {
			xyOverlap = true;
		}
	}

	if (xyOverlap) {
		if (m_min.z < other.m_min.z) {
			xyOverlap = other.m_min.z <= m_max.z;
		} else {
			if (m_min.z > other.m_min.z) {
				xyOverlap = m_min.z <= other.m_max.z;
			} else {
				xyOverlap = true;
			}
		}

		if (xyOverlap) {
			overlap = true;
		}
	}

	return overlap;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
COctNode::COctNode()
{
	float min = kOctTreeBoundMinInit;
	float max = kOctTreeBoundMaxInit;
	float* bounds = (float*)this;

	bounds[2] = min;
	bounds[1] = min;
	bounds[0] = min;
	bounds[5] = max;
	bounds[4] = max;
	bounds[3] = max;
	m_lightFlags = 0;
	m_shadowFlags = 0;
}

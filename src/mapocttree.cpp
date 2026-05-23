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

	void operator=(const CBound& other)
	{
		*this = *reinterpret_cast<const CBoundRaw*>(&other);
	}

    Vec m_min;
    Vec m_max;
};

struct CMapCylinderRaw
{
    CMapCylinderRaw()
    {
        m_boundsMin.z = kOctTreeBoundMinInit;
        m_boundsMin.y = kOctTreeBoundMinInit;
        m_boundsMin.x = kOctTreeBoundMinInit;
        m_boundsMax.z = kOctTreeBoundMaxInit;
        m_boundsMax.y = kOctTreeBoundMaxInit;
        m_boundsMax.x = kOctTreeBoundMaxInit;
    }

    Vec m_bottom;
    Vec m_top;
    Vec m_axis;
    float m_radius;
    Vec m_boundsMin;
    Vec m_boundsMax;
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
int s_light_no = 0;
unsigned long s_shadow_no = 0;
unsigned long InsertShadow_level = 0;
unsigned long clear_flag_mask = 0;
UMapHitDrawMode gMapHitDrawMode;
unsigned long octtree_draw_node_ct = 0;

extern unsigned long g_pStage;
extern unsigned long s_insertShadowNo;

extern "C" const char s_m_node_pctd_m_meshtype_pctd_801D7268[] =
    "\n\n===============================================\n\n\t\t\tm_node=%d   m_meshtype=%d\n\n\n"
    "===============================================\n\n";
extern "C" const char s_mapocttree_cpp_801D72EC[] = "mapocttree.cpp";

namespace {
static inline unsigned char* Ptr(void* ptr, unsigned int offset)
{
    return reinterpret_cast<unsigned char*>(ptr) + offset;
}

static inline CMapObj* GetMapObjByIndex(unsigned short index)
{
    return reinterpret_cast<CMapObj*>(reinterpret_cast<unsigned char*>(&MapMng) + 0x954 + (index * 0xF0));
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
#pragma dont_inline on
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
#pragma dont_inline reset

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
int COctTree::ReadOtmOctTree(CChunkFile& chunkFile)
{
    CChunkFile::CChunk chunk;
    int nodeCount;

    m_unk01 = 0;
    chunkFile.PushChunk();

    while (chunkFile.GetNextChunk(chunk)) {
        switch (chunk.m_id) {
        case 'TYPE':
            m_type = static_cast<unsigned char>(chunkFile.Get2());
            break;

        case 'OBJN': {
            unsigned short objIndex = chunkFile.Get2();

            m_mapObject = GetMapObjByIndex(objIndex);
            if (*reinterpret_cast<signed char*>(Ptr(m_mapObject, 0x1E)) == 4) {
                *reinterpret_cast<unsigned char*>(Ptr(m_mapObject, 0x15)) = 0xFF;
                *reinterpret_cast<unsigned char*>(Ptr(m_mapObject, 0x14)) = 0xFF;
                *reinterpret_cast<signed char*>(Ptr(m_mapObject, 0x22)) = 0;
            } else if (*reinterpret_cast<signed char*>(Ptr(m_mapObject, 0x1E)) == 3) {
                *reinterpret_cast<signed char*>(Ptr(m_mapObject, 0x22)) = 0;
            }
            break;
        }

        case 'NODN': {
            m_nodeCount = chunkFile.Get2();
            signed char mapObjType = *reinterpret_cast<signed char*>(Ptr(m_mapObject, 0x1E));
            if ((mapObjType != 1) && (static_cast<unsigned int>(System.m_execParam) >= 3U)) {
                System.Printf(const_cast<char*>(s_m_node_pctd_m_meshtype_pctd_801D7268), m_nodeCount, mapObjType);
            }

            nodeCount = m_nodeCount;
            m_nodePool = new (*reinterpret_cast<CMemory::CStage**>(&MapMng), const_cast<char*>(s_mapocttree_cpp_801D72EC), 0x59)
                COctNode[nodeCount];
            break;
        }

        case 'INFO':
            m_unk01 = chunkFile.Get1();
            break;

        case 'TREE':
            chunkFile.PushChunk();
            while (chunkFile.GetNextChunk(chunk)) {
                if (chunk.m_id == 'NODE') {
                    COctNode* node;

                    chunkFile.PushChunk();
                    while (chunkFile.GetNextChunk(chunk)) {
                        switch (chunk.m_id) {
                        case 'OBJ ': {
                            node = m_nodePool + static_cast<unsigned short>(chunkFile.Get2());
                            node->m_meshCount = chunkFile.Get2();
                            node->m_meshStart = chunkFile.Get2();
                            break;
                        }

                        case 'BOND':
                            node->m_boundMinX = chunkFile.GetF4();
                            node->m_boundMinY = chunkFile.GetF4();
                            node->m_boundMinZ = chunkFile.GetF4();
                            node->m_boundMaxX = chunkFile.GetF4();
                            node->m_boundMaxY = chunkFile.GetF4();
                            node->m_boundMaxZ = chunkFile.GetF4();
                            break;

                        case 'CHLD':
                            int childCount = 0;

                            for (int i = 0; i < 8; i++) {
                                short childIndex = chunkFile.Get2();

                                if (childIndex != -1) {
                                    node->m_children[childCount] = m_nodePool + static_cast<unsigned short>(childIndex);
                                    childCount++;
                                }
                            }

                            for (int i = childCount; i < 8; i++) {
                                node->m_children[i] = 0;
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
    return 1;
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
	COctNode* nodeIter;
	COctNode* pCVar4;
	COctNode* pCVar3;
	CMaterialManEnvRaw* env;
	int iVar5;

	if ((octNode->m_meshCount != 0) &&
	    ((octNode->m_drawFlags & 1) != 0)) {
		env = reinterpret_cast<CMaterialManEnvRaw*>(&MaterialMan);
		env->m_curEnvTevBit = 0xACE0F;
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
		if (*reinterpret_cast<unsigned char*>(Ptr(m_mapObject, 0x22)) != 0) {
			CameraPcs.SetFullScreenShadow(m_mapObject->m_worldMtx, 0);
		}
		if (*reinterpret_cast<unsigned long*>(Ptr(m_mapObject, 0x3C)) != 0) {
			MaterialMan.SetShadowBit32(static_cast<CMapShadow::TARGET>(1), &octNode->m_shadowFlags,
			                           m_mapObject->m_worldMtx);
		}
		env->m_stdTexMapId = env->m_texMapIdCur;
		env->m_stdTexMtx = env->m_texMtxCur;
		env->m_stdTexCoordId = env->m_texCoordIdCur;
		env->m_stdEnvTevBit = env->m_curEnvTevBit;
		LightPcs.SetBit32(static_cast<CLightPcs::TARGET>(1), &octNode->m_lightFlags);
		static_cast<CMapObj*>(m_mapObject)->SetDrawEnv();
		static_cast<CMapMesh*>(m_mapObject->m_mapData)
			->DrawMesh(octNode->m_meshStart,
			           octNode->m_meshCount);
	}
	env = reinterpret_cast<CMaterialManEnvRaw*>(&MaterialMan);
	nodeIter = octNode;
	iVar2 = 0;
	do {
		pCVar4 = nodeIter->m_children[0];
		if (pCVar4 == 0) {
			return;
		}
		if ((pCVar4->m_meshCount != 0) &&
		    ((pCVar4->m_drawFlags & 1) != 0)) {
			env->m_curEnvTevBit = 0xACE0F;
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
			if (*reinterpret_cast<unsigned char*>(Ptr(m_mapObject, 0x22)) != 0) {
				CameraPcs.SetFullScreenShadow(m_mapObject->m_worldMtx, 0);
			}
			if (*reinterpret_cast<unsigned long*>(Ptr(m_mapObject, 0x3C)) != 0) {
				MaterialMan.SetShadowBit32(static_cast<CMapShadow::TARGET>(1), &pCVar4->m_shadowFlags,
				                           m_mapObject->m_worldMtx);
			}
			env->m_stdTexMapId = env->m_texMapIdCur;
			env->m_stdTexMtx = env->m_texMtxCur;
			env->m_stdTexCoordId = env->m_texCoordIdCur;
			env->m_stdEnvTevBit = env->m_curEnvTevBit;
			LightPcs.SetBit32(static_cast<CLightPcs::TARGET>(1), &pCVar4->m_lightFlags);
			static_cast<CMapObj*>(m_mapObject)->SetDrawEnv();
			static_cast<CMapMesh*>(m_mapObject->m_mapData)
				->DrawMesh(pCVar4->m_meshStart,
				           pCVar4->m_meshCount);
		}
		iVar5 = 0;
		do {
			pCVar3 = pCVar4->m_children[0];
			if (pCVar3 == 0) {
				break;
			}
			if ((pCVar3->m_meshCount != 0) &&
			    ((pCVar3->m_drawFlags & 1) != 0)) {
				MaterialMan.InitEnv();
				if (*reinterpret_cast<unsigned char*>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0x22)) != 0) {
					CameraPcs.SetFullScreenShadow(m_mapObject->m_worldMtx, 0);
				}
				if (*reinterpret_cast<unsigned long*>(Ptr(m_mapObject, 0x3C)) != 0) {
					MaterialMan.SetShadowBit32(static_cast<CMapShadow::TARGET>(1), &pCVar3->m_shadowFlags,
					                           m_mapObject->m_worldMtx);
				}
				MaterialMan.LockEnv();
				LightPcs.SetBit32(static_cast<CLightPcs::TARGET>(1), &pCVar3->m_lightFlags);
				static_cast<CMapObj*>(m_mapObject)->SetDrawEnv();
				static_cast<CMapMesh*>(m_mapObject->m_mapData)
					->DrawMesh(pCVar3->m_meshStart,
					           pCVar3->m_meshCount);
			}
			iVar1 = 0;
			do {
				if (pCVar3->m_children[0] == 0) {
					break;
				}
				DrawTypeMeshFlag_r(pCVar3->m_children[0]);
				iVar1 = iVar1 + 1;
				pCVar3 = reinterpret_cast<COctNode*>(Ptr(pCVar3, 4));
			} while (iVar1 < 8);
			iVar5 = iVar5 + 1;
			pCVar4 = reinterpret_cast<COctNode*>(Ptr(pCVar4, 4));
		} while (iVar5 < 8);
		iVar2 = iVar2 + 1;
		nodeIter = reinterpret_cast<COctNode*>(Ptr(nodeIter, 4));
	} while (iVar2 < 8);
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
	} while (iVar1 < 8);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void COctTree::DrawTypeMeshFrustumIn_r(COctNode* octNode)
{
	int i;
	int j;
	int k;
	int m;
	int n;
	int o;
	int p;
	int q;
	int r;
	COctNode* child1;
	COctNode* child2;
	COctNode* child3;
	COctNode* child4;
	COctNode* child5;
	COctNode* child6;
	COctNode* child7;
	COctNode* child8;
	COctNode* node;

	if (octNode->m_meshCount != 0) {
		octNode->m_drawFlags |= 1;
	}

	node = octNode;
	for (i = 0; i < 8; i++) {
		child1 = node->m_children[0];
		if (child1 == 0) {
			return;
		}
		if (child1->m_meshCount != 0) {
			child1->m_drawFlags |= 1;
		}

		for (j = 0; j < 8; j++) {
			child2 = child1->m_children[0];
			if (child2 == 0) {
				break;
			}
			if (child2->m_meshCount != 0) {
				child2->m_drawFlags |= 1;
			}

			for (k = 0; k < 8; k++) {
				child3 = child2->m_children[0];
				if (child3 == 0) {
					break;
				}
				if (child3->m_meshCount != 0) {
					child3->m_drawFlags |= 1;
				}

				for (m = 0; m < 8; m++) {
					child4 = child3->m_children[0];
					if (child4 == 0) {
						break;
					}
					if (child4->m_meshCount != 0) {
						child4->m_drawFlags |= 1;
					}

					for (n = 0; n < 8; n++) {
						child5 = child4->m_children[0];
						if (child5 == 0) {
							break;
						}
						if (child5->m_meshCount != 0) {
							child5->m_drawFlags |= 1;
						}

						for (o = 0; o < 8; o++) {
							child6 = child5->m_children[0];
							if (child6 == 0) {
								break;
							}
							if (child6->m_meshCount != 0) {
								child6->m_drawFlags |= 1;
							}

							for (p = 0; p < 8; p++) {
								child7 = child6->m_children[0];
								if (child7 == 0) {
									break;
								}
								if (child7->m_meshCount != 0) {
									child7->m_drawFlags |= 1;
								}

								for (q = 0; q < 8; q++) {
									child8 = child7->m_children[0];
									if (child8 == 0) {
										break;
									}
									if (child8->m_meshCount != 0) {
										child8->m_drawFlags |= 1;
									}

									for (r = 0; r < 8; r++) {
										if (child8->m_children[0] == 0) {
											break;
										}
										DrawTypeMeshFrustumIn_r(child8->m_children[0]);
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
 * PAL Address: 0x8002e490
 * PAL Size: 712b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void COctTree::DrawTypeMesh_r(COctNode* octNode)
{
	float localX = m_localPosX;
	unsigned char andMask;
	unsigned char orMask;
	int farCount;

	if ((localX <= octNode->m_boundMaxX) && (m_localPosY <= octNode->m_boundMaxY) &&
	    (m_localPosZ <= octNode->m_boundMaxZ) && (localX >= octNode->m_boundMinX) &&
	    (m_localPosY >= octNode->m_boundMinY) && (m_localPosZ >= octNode->m_boundMinZ)) {
		orMask = 0xF;
	} else {
		Vec localCorner;
		Vec viewPos;
		float maxDepth = kOctTreeBoundMinInit;
		float minDepth = kOctTreeBoundMaxInit;

		andMask = 0xF;
		farCount = 0;
		orMask = 0;

		for (int x = 0; x < 2; x++) {
			localCorner.x = (x == 0) ? octNode->m_boundMinX : octNode->m_boundMaxX;
			for (int y = 0; y < 2; y++) {
				localCorner.y = (y == 0) ? octNode->m_boundMinY : octNode->m_boundMaxY;
				for (int z = 0; z < 2; z++) {
					unsigned char clipFlags;
					double depth;

					localCorner.z = (z == 0) ? octNode->m_boundMinZ : octNode->m_boundMaxZ;
					PSMTXMultVec(reinterpret_cast<float(*)[4]>(m_pad0C), &localCorner, &viewPos);

					if (maxDepth < viewPos.z) {
						maxDepth = viewPos.z;
					}

					depth = static_cast<double>(viewPos.z);
					if (viewPos.z > minDepth) {
						farCount++;
						if (static_cast<double>(viewPos.x) > -depth) {
							clipFlags = 0x11;
						} else if (static_cast<double>(viewPos.x) < depth) {
							clipFlags = 0x12;
						} else {
							clipFlags = 0x10;
						}

						if (static_cast<double>(viewPos.y) > -depth) {
							clipFlags |= 0x14;
						} else if (static_cast<double>(viewPos.y) < depth) {
							clipFlags |= 0x18;
						}
					} else {
						if (static_cast<double>(viewPos.x) > -depth) {
							clipFlags = 1;
						} else if (static_cast<double>(viewPos.x) < depth) {
							clipFlags = 2;
						} else {
							clipFlags = 0;
						}

						if (static_cast<double>(viewPos.y) > -depth) {
							clipFlags |= 4;
						} else if (static_cast<double>(viewPos.y) < depth) {
							clipFlags |= 8;
						}
					}

					andMask &= clipFlags;
					orMask |= clipFlags;
				}
			}
		}

		if (farCount >= 8) {
			return;
		}
		if (maxDepth < *reinterpret_cast<float*>(Ptr(&MapMng, 0x22A70))) {
			return;
		}
		if (andMask != 0) {
			return;
		}
	}

	if (octNode->m_meshCount != 0) {
		octNode->m_drawFlags |= 1;
	}

	if (orMask == 0) {
		for (int i = 0; i < 8; i++) {
			if (octNode->m_children[0] == 0) {
				return;
			}
			DrawTypeMeshFrustumIn_r(octNode->m_children[0]);
			octNode = reinterpret_cast<COctNode*>(Ptr(octNode, 4));
		}
	} else {
		for (int i = 0; i < 8; i++) {
			if (octNode->m_children[0] == 0) {
				return;
			}
			DrawTypeMesh_r(octNode->m_children[0]);
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
	CMapObj* mapObj;

	if (m_type == 0) {
		mapObj = m_mapObject;
		unsigned char mapDrawType = *reinterpret_cast<unsigned char*>(Ptr(mapObj, 0x15));
		unsigned char targetDrawType = drawType;
		if ((mapDrawType == targetDrawType) &&
		    ((*reinterpret_cast<unsigned char*>(Ptr(mapObj, 0x18)) & 1) != 0)) {
			if ((*reinterpret_cast<unsigned char*>(Ptr(&MapMng, 0x2298A)) != 0) &&
			    ((*reinterpret_cast<void**>(Ptr(mapObj, 0x10)) != 0) &&
			     (*reinterpret_cast<unsigned char*>(Ptr(*reinterpret_cast<void**>(Ptr(mapObj, 0x10)), 0xB1)) == 2))) {
				MaterialMan.SetUnderWaterTex();
				*reinterpret_cast<unsigned char*>(Ptr(&MapMng, 0x2298A)) = 0;
			}

			mapObj = m_mapObject;
			LightPcs.SetBumpTexMatirx(mapObj->m_worldMtx,
			                          *reinterpret_cast<CLightPcs::CBumpLight**>(Ptr(mapObj, 0x10)),
			                          reinterpret_cast<Vec*>(Ptr(mapObj, 0x58)),
			                          *reinterpret_cast<unsigned char*>(Ptr(mapObj, 0x1A)));
			if (kMapOctTreeDefaultOffsetZ != *reinterpret_cast<float*>(Ptr(m_mapObject, 0x40))) {
				CameraPcs.SetOffsetZBuff(*reinterpret_cast<float*>(Ptr(m_mapObject, 0x40)));
			}
			if (*reinterpret_cast<unsigned char*>(Ptr(m_mapObject, 0x27)) != 0) {
				GXSetZMode(1, (GXCompare)3, 0);
			}
			static_cast<CMapMesh*>(m_mapObject->m_mapData)->SetRenderArray();
			DrawTypeMeshFlag_r(m_nodePool);
			if (*reinterpret_cast<unsigned char*>(Ptr(m_mapObject, 0x27)) != 0) {
				GXSetZMode(1, (GXCompare)3, 1);
			}
			float offsetZ = *reinterpret_cast<float*>(Ptr(m_mapObject, 0x40));
			if (kMapOctTreeDefaultOffsetZ != offsetZ) {
				CameraPcs.SetOffsetZBuff(kMapOctTreeDefaultOffsetZ);
			}
		}
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
	CMapObj* mapObj;

	if (m_type == 0) {
		mapObj = m_mapObject;
		unsigned char mapDrawType = *reinterpret_cast<unsigned char*>(Ptr(mapObj, 0x15));
		unsigned char targetDrawType = drawType;
		if (mapDrawType != targetDrawType) {
			return;
		}

		LightPcs.SetBumpTexMatirx(mapObj->m_worldMtx, 0, reinterpret_cast<Vec*>(Ptr(mapObj, 0x58)),
		                          *reinterpret_cast<unsigned char*>(Ptr(mapObj, 0x1A)));

		if (kMapOctTreeDefaultOffsetZ != *reinterpret_cast<float*>(Ptr(m_mapObject, 0x40))) {
			CameraPcs.SetOffsetZBuff(*reinterpret_cast<float*>(Ptr(m_mapObject, 0x40)));
		}

		static_cast<CMapMesh*>(m_mapObject->m_mapData)->SetRenderArray();
		DrawCharaShadowTypeMeshFlag_r(m_nodePool);

		float offsetZ = *reinterpret_cast<float*>(Ptr(m_mapObject, 0x40));
		if (kMapOctTreeDefaultOffsetZ != offsetZ) {
			CameraPcs.SetOffsetZBuff(kMapOctTreeDefaultOffsetZ);
		}
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
	Mtx localMtx;

	if (((m_drawFlags & 1) == 0) && (*reinterpret_cast<unsigned char*>(Ptr(m_mapObject, 0x1D)) == 1)) {
		PSMTXConcat(reinterpret_cast<float(*)[4]>(Ptr(&MapMng, 0x22928)),
		            m_mapObject->m_worldMtx, reinterpret_cast<float(*)[4]>(Ptr(this, 0xC)));
		PSMTXConcat(reinterpret_cast<float(*)[4]>(Ptr(&MapMng, 0x228F8)),
		            m_mapObject->m_worldMtx, localMtx);
		PSMTXInverse(localMtx, localMtx);

		m_localPosX = localMtx[0][3];
		m_localPosY = localMtx[1][3];
		m_localPosZ = localMtx[2][3];
		ClearFlag(1);
		DrawTypeMesh_r(m_nodePool);
	}
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
	COctNode* nodeIter;
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
	nodeIter = octNode;
	do {
		pCVar8 = *reinterpret_cast<COctNode**>(Ptr(nodeIter, 0x1C));
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
		nodeIter = reinterpret_cast<COctNode*>(Ptr(nodeIter, 4));
	} while (iVar1 < 8);
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
	bool overlap = false;
	bool xyOverlap = false;
	int xOverlap = false;

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
			xOverlap = s_bound.m_min.z <= node->m_boundMaxZ;
		} else {
			if (boundMinZ > s_bound.m_min.z) {
				xOverlap = boundMinZ <= s_bound.m_max.z;
			} else {
				xOverlap = true;
			}
		}
		if (xOverlap) {
			overlap = true;
		}
	}

	if (!overlap) {
		return;
	}

	if (node->m_meshCount != 0) {
		unsigned long byteOffset = (g_pStage >> 3) & 0x1ffffffc;
		unsigned long* bits = reinterpret_cast<unsigned long*>(Ptr(&node->m_lightFlags, byteOffset));
		*bits |= 1UL << (g_pStage & 0x1f);
	}

	COctNode* nodeIter = node;
	for (int i = 0; i < 8; i++) {
		COctNode* child = nodeIter->m_children[0];
		if (child == 0) {
			return;
		}

		float childBoundMinX = child->m_boundMinX;
		bool childOverlap = false;
		bool childXYOverlap = false;
		int childXOverlap = false;
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
				childXOverlap = s_bound.m_min.z <= child->m_boundMaxZ;
			} else {
				if (childBoundMinZ > s_bound.m_min.z) {
					childXOverlap = childBoundMinZ <= s_bound.m_max.z;
				} else {
					childXOverlap = true;
				}
			}
			if (childXOverlap) {
				childOverlap = true;
			}
		}

		if (childOverlap) {
			if (child->m_meshCount != 0) {
				unsigned long byteOffset = (g_pStage >> 3) & 0x1ffffffc;
				unsigned long* bits = reinterpret_cast<unsigned long*>(Ptr(child, byteOffset));
				bits[0x44 / sizeof(unsigned long)] |= 1UL << (g_pStage & 0x1f);
			}

			COctNode* childIter = child;
			for (int j = 0; j < 8; j++) {
				COctNode* grandChild = childIter->m_children[0];
				if (grandChild == 0) {
					break;
				}

				if ((reinterpret_cast<CBound*>(grandChild)->CheckCross(*reinterpret_cast<CBound*>(&s_bound))) != 0) {
					if (grandChild->m_meshCount != 0) {
						setbit32(reinterpret_cast<unsigned long*>(Ptr(grandChild, 0x44)), g_pStage);
					}

					COctNode* grandChildIter = grandChild;
					for (int k = 0; k < 8; k++) {
						COctNode* greatGrandChild = grandChildIter->m_children[0];
						if (greatGrandChild == 0) {
							break;
						}
						InsertLight_r(greatGrandChild);
						grandChildIter = reinterpret_cast<COctNode*>(Ptr(grandChildIter, 4));
					}
				}
				childIter = reinterpret_cast<COctNode*>(Ptr(childIter, 4));
			}
		}
		nodeIter = reinterpret_cast<COctNode*>(Ptr(nodeIter, 4));
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
	unsigned char* mapObj;

	if (m_type != 0) {
		return;
	}

	mapObj = reinterpret_cast<unsigned char*>(m_mapObject);
	if ((*reinterpret_cast<unsigned long*>(mapObj + 0x38) & mask) == 0) {
		return;
	}

	g_pStage = bitIndex;
	PSMTXInverse(m_mapObject->m_worldMtx, inverseMtx);
	PSMTXMultVec(inverseMtx, &position, &localPosition);

	s_bound.m_min.x = localPosition.x - radius;
	s_bound.m_min.y = localPosition.y - radius;
	s_bound.m_min.z = localPosition.z - radius;
	s_bound.m_max.x = localPosition.x + radius;
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
	COctNode* nodeIter;
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

	if (*reinterpret_cast<unsigned short*>(Ptr(node, 0x3C)) != 0) {
		*reinterpret_cast<unsigned long*>(Ptr(node, 0x48)) = 0;
	}
	iVar1 = 0;
	nodeIter = node;
	do {
		pCVar8 = *reinterpret_cast<COctNode**>(Ptr(nodeIter, 0x1C));
		if (pCVar8 == 0) {
			return;
		}
		if (*reinterpret_cast<unsigned short*>(Ptr(pCVar8, 0x3C)) != 0) {
			*reinterpret_cast<unsigned long*>(Ptr(pCVar8, 0x48)) = 0;
		}
		iVar2 = 0;
		do {
			pCVar7 = *reinterpret_cast<COctNode**>(Ptr(pCVar8, 0x1C));
			if (pCVar7 == 0) break;
			if (*reinterpret_cast<unsigned short*>(Ptr(pCVar7, 0x3C)) != 0) {
				*reinterpret_cast<unsigned long*>(Ptr(pCVar7, 0x48)) = 0;
			}
			iVar13 = 0;
			do {
				pCVar6 = *reinterpret_cast<COctNode**>(Ptr(pCVar7, 0x1C));
				if (pCVar6 == 0) break;
				if (*reinterpret_cast<unsigned short*>(Ptr(pCVar6, 0x3C)) != 0) {
					*reinterpret_cast<unsigned long*>(Ptr(pCVar6, 0x48)) = 0;
				}
				iVar12 = 0;
				do {
					pCVar5 = *reinterpret_cast<COctNode**>(Ptr(pCVar6, 0x1C));
					if (pCVar5 == 0) break;
					if (*reinterpret_cast<unsigned short*>(Ptr(pCVar5, 0x3C)) != 0) {
						*reinterpret_cast<unsigned long*>(Ptr(pCVar5, 0x48)) = 0;
					}
					iVar11 = 0;
					do {
						pCVar4 = *reinterpret_cast<COctNode**>(Ptr(pCVar5, 0x1C));
						if (pCVar4 == 0) break;
						if (*reinterpret_cast<unsigned short*>(Ptr(pCVar4, 0x3C)) != 0) {
							*reinterpret_cast<unsigned long*>(Ptr(pCVar4, 0x48)) = 0;
						}
						iVar10 = 0;
						do {
							pCVar3 = *reinterpret_cast<COctNode**>(Ptr(pCVar4, 0x1C));
							if (pCVar3 == 0) break;
							if (*reinterpret_cast<unsigned short*>(Ptr(pCVar3, 0x3C)) != 0) {
								*reinterpret_cast<unsigned long*>(Ptr(pCVar3, 0x48)) = 0;
							}
							iVar9 = 0;
							do {
								if (*reinterpret_cast<COctNode**>(Ptr(pCVar3, 0x1C)) == 0) break;
								ClearShadow_r(*reinterpret_cast<COctNode**>(Ptr(pCVar3, 0x1C)));
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
		nodeIter = reinterpret_cast<COctNode*>(Ptr(nodeIter, 4));
	} while (iVar1 < 8);
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
	bool overlap = false;
	bool xyOverlap = false;
	int xOverlap = false;

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
			xOverlap = s_bound.m_min.z <= node->m_boundMaxZ;
		} else {
			if (boundMinZ > s_bound.m_min.z) {
				xOverlap = boundMinZ <= s_bound.m_max.z;
			} else {
				xOverlap = true;
			}
		}
		if (xOverlap) {
			overlap = true;
		}
	}

	if (!overlap) {
		return;
	}

	if ((s_light_no >= 3) && (node->m_meshCount != 0)) {
		unsigned long byteOffset = (s_insertShadowNo >> 3) & 0x1ffffffc;
		unsigned long* bits = reinterpret_cast<unsigned long*>(Ptr(&node->m_shadowFlags, byteOffset));
		*bits |= 1UL << (s_insertShadowNo & 0x1f);
	}

	COctNode* nodeIter = node;
	for (int i = 0; i < 8; i++) {
		if (nodeIter->m_children[0] == 0) {
			return;
		}

		s_light_no++;
		COctNode* child = nodeIter->m_children[0];

		float childBoundMinX = child->m_boundMinX;
		bool childOverlap = false;
		bool childXYOverlap = false;
		int childXOverlap = false;
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
				childXOverlap = s_bound.m_min.z <= child->m_boundMaxZ;
			} else {
				if (childBoundMinZ > s_bound.m_min.z) {
					childXOverlap = childBoundMinZ <= s_bound.m_max.z;
				} else {
					childXOverlap = true;
				}
			}
			if (childXOverlap) {
				childOverlap = true;
			}
		}

		if (childOverlap) {
			if ((s_light_no >= 3) && (child->m_meshCount != 0)) {
				unsigned long byteOffset = (s_insertShadowNo >> 3) & 0x1ffffffc;
				unsigned long* bits = reinterpret_cast<unsigned long*>(Ptr(child, byteOffset));
				bits[0x48 / sizeof(unsigned long)] |= 1UL << (s_insertShadowNo & 0x1f);
			}

			COctNode* childIter = child;
			for (int j = 0; j < 8; j++) {
				if (childIter->m_children[0] == 0) {
					break;
				}

				s_light_no++;
				COctNode* grandChild = childIter->m_children[0];

				if ((reinterpret_cast<CBound*>(grandChild)->CheckCross(*reinterpret_cast<CBound*>(&s_bound))) != 0) {
					if ((s_light_no >= 3) && (grandChild->m_meshCount != 0)) {
						setbit32(reinterpret_cast<unsigned long*>(Ptr(grandChild, 0x48)), s_insertShadowNo);
					}

					COctNode* grandChildIter = grandChild;
					for (int k = 0; k < 8; k++) {
						if (grandChildIter->m_children[0] == 0) {
							break;
						}
						s_light_no++;
						COctNode* greatGrandChild = grandChildIter->m_children[0];
						InsertShadow_r(greatGrandChild);
						grandChildIter = reinterpret_cast<COctNode*>(Ptr(grandChildIter, 4));
						s_light_no--;
					}
				}
				childIter = reinterpret_cast<COctNode*>(Ptr(childIter, 4));
				s_light_no--;
			}
		}
		nodeIter = reinterpret_cast<COctNode*>(Ptr(nodeIter, 4));
		s_light_no--;
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

	if (m_type == 0) {
		s_insertShadowNo = bitIndex;
		PSMTXInverse(m_mapObject->m_worldMtx, inverseMtx);
		PSMTXMultVec(inverseMtx, &position, &localPosition);

		s_bound = bound;

		PSVECAdd(&s_bound.m_min, &localPosition, &s_bound.m_min);
		PSVECAdd(&s_bound.m_max, &localPosition, &s_bound.m_max);

		s_light_no = 0;
		InsertShadow_r(m_nodePool);
	}
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
	int i;
	COctNode* child1;
	COctNode* child2;
	COctNode* child3;
	COctNode* child4;
	COctNode* child5;
	COctNode* child6;
	COctNode* child7;
	COctNode* child8;

	if (node->m_meshCount != 0) {
		node->m_drawFlags &= s_shadow_no;
	}

	i = 0;
	COctNode* nodeIter = node;
	do {
		child1 = nodeIter->m_children[0];
		if (child1 == 0) {
			return;
		}
		if (child1->m_meshCount != 0) {
			child1->m_drawFlags &= s_shadow_no;
		}

		for (int j = 0; j < 8; j++) {
			child2 = child1->m_children[0];
			if (child2 == 0) {
				break;
			}
			if (child2->m_meshCount != 0) {
				child2->m_drawFlags &= s_shadow_no;
			}

			for (int k = 0; k < 8; k++) {
				child3 = child2->m_children[0];
				if (child3 == 0) {
					break;
				}
				if (child3->m_meshCount != 0) {
					child3->m_drawFlags &= s_shadow_no;
				}

				for (int m = 0; m < 8; m++) {
					child4 = child3->m_children[0];
					if (child4 == 0) {
						break;
					}
					if (child4->m_meshCount != 0) {
						child4->m_drawFlags &= s_shadow_no;
					}

					for (int n = 0; n < 8; n++) {
						child5 = child4->m_children[0];
						if (child5 == 0) {
							break;
						}
						if (child5->m_meshCount != 0) {
							child5->m_drawFlags &= s_shadow_no;
						}

						for (int o = 0; o < 8; o++) {
							child6 = child5->m_children[0];
							if (child6 == 0) {
								break;
							}
							if (child6->m_meshCount != 0) {
								child6->m_drawFlags &= s_shadow_no;
							}

							for (int p = 0; p < 8; p++) {
								child7 = child6->m_children[0];
								if (child7 == 0) {
									break;
								}
								if (child7->m_meshCount != 0) {
									child7->m_drawFlags &= s_shadow_no;
								}

								for (int q = 0; q < 8; q++) {
									child8 = child7->m_children[0];
									if (child8 == 0) {
										break;
									}
									if (child8->m_meshCount != 0) {
										child8->m_drawFlags &= s_shadow_no;
									}

									for (int r = 0; r < 8; r++) {
										if (child8->m_children[0] == 0) {
											break;
										}
										ClearFlag_r(child8->m_children[0]);
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

		i++;
		nodeIter = reinterpret_cast<COctNode*>(Ptr(nodeIter, 4));
	} while (i < 8);
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
	s_shadow_no = ~flag;
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
	float boundMinX = node->m_boundMinX;
	bool overlap = false;
	bool xyOverlap = false;
	int xOverlap = false;

	if (boundMinX < s_cyl.m_boundsMin.x) {
		xOverlap = s_cyl.m_boundsMin.x <= node->m_boundMaxX;
	} else {
		if (boundMinX > s_cyl.m_boundsMin.x) {
			xOverlap = boundMinX <= s_cyl.m_boundsMax.x;
		} else {
			xOverlap = true;
		}
	}

	if (xOverlap) {
		float boundMinY = node->m_boundMinY;
		if (boundMinY < s_cyl.m_boundsMin.y) {
			xOverlap = s_cyl.m_boundsMin.y <= node->m_boundMaxY;
		} else {
			if (boundMinY > s_cyl.m_boundsMin.y) {
				xOverlap = boundMinY <= s_cyl.m_boundsMax.y;
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
		if (boundMinZ < s_cyl.m_boundsMin.z) {
			xOverlap = s_cyl.m_boundsMin.z <= node->m_boundMaxZ;
		} else {
			if (boundMinZ > s_cyl.m_boundsMin.z) {
				xOverlap = boundMinZ <= s_cyl.m_boundsMax.z;
			} else {
				xOverlap = true;
			}
		}
		if (xOverlap) {
			overlap = true;
		}
	}

	if (overlap) {
		if ((node->m_meshCount != 0) &&
			(static_cast<CMapHit*>(m_mapObject->m_mapData)
				 ->CheckHitCylinder((CMapCylinder*)&s_cyl, &s_mvec,
									node->m_meshStart,
									node->m_meshCount,
									InsertShadow_level) != 0)) {
			return 1;
		}

		COctNode* nodeIter = node;
		for (int i = 0; i < 8; i++) {
			COctNode* child = nodeIter->m_children[0];
			if (child == 0) {
				break;
			}

			float childBoundMinX = child->m_boundMinX;
			bool childOverlap = false;
			bool childXYOverlap = false;
			int childXOverlap = false;
			if (childBoundMinX < s_cyl.m_boundsMin.x) {
				childXOverlap = s_cyl.m_boundsMin.x <= child->m_boundMaxX;
			} else {
				if (childBoundMinX > s_cyl.m_boundsMin.x) {
					childXOverlap = childBoundMinX <= s_cyl.m_boundsMax.x;
				} else {
					childXOverlap = true;
				}
			}

			if (childXOverlap) {
				float childBoundMinY = child->m_boundMinY;
				if (childBoundMinY < s_cyl.m_boundsMin.y) {
					childXOverlap = s_cyl.m_boundsMin.y <= child->m_boundMaxY;
				} else {
					if (childBoundMinY > s_cyl.m_boundsMin.y) {
						childXOverlap = childBoundMinY <= s_cyl.m_boundsMax.y;
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
				if (childBoundMinZ < s_cyl.m_boundsMin.z) {
					childXOverlap = s_cyl.m_boundsMin.z <= child->m_boundMaxZ;
				} else {
					if (childBoundMinZ > s_cyl.m_boundsMin.z) {
						childXOverlap = childBoundMinZ <= s_cyl.m_boundsMax.z;
					} else {
						childXOverlap = true;
					}
				}
				if (childXOverlap) {
					childOverlap = true;
				}
			}

			if (childOverlap) {
				int childHit = false;
				if ((child->m_meshCount != 0) &&
					(static_cast<CMapHit*>(m_mapObject->m_mapData)
						 ->CheckHitCylinder((CMapCylinder*)&s_cyl, &s_mvec,
											child->m_meshStart,
											child->m_meshCount,
											InsertShadow_level) != 0)) {
					childHit = true;
				} else {
					for (int j = 0; j < 8; j++) {
						COctNode* grandChild = child->m_children[0];
						if (grandChild == 0) {
							break;
						}

						if ((reinterpret_cast<CBound*>(grandChild)->CheckCross(*reinterpret_cast<CBound*>(&s_cyl.m_boundsMin))) != 0) {
							if ((grandChild->m_meshCount != 0) &&
								(static_cast<CMapHit*>(m_mapObject->m_mapData)
									 ->CheckHitCylinder((CMapCylinder*)&s_cyl, &s_mvec,
														grandChild->m_meshStart,
														grandChild->m_meshCount,
														InsertShadow_level) != 0)) {
								childHit = true;
							} else {
								for (int k = 0; k < 8; k++) {
									COctNode* greatGrandChild = grandChild->m_children[0];
									if (greatGrandChild == 0) {
										break;
									}

									if (CheckHitCylinder_r(greatGrandChild) != 0) {
										childHit = true;
										break;
									}
									grandChild = reinterpret_cast<COctNode*>(Ptr(grandChild, 4));
								}
							}
						}
						if (childHit) {
							break;
						}
						child = reinterpret_cast<COctNode*>(Ptr(child, 4));
					}
				}
				if (childHit) {
					return 1;
				}
			}
			nodeIter = reinterpret_cast<COctNode*>(Ptr(nodeIter, 4));
		}
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
		mapHit = static_cast<CMapHit*>(m_mapObject->m_mapData);
		if (mapHit != 0) {
			PSMTXInverse(m_mapObject->m_worldMtx, inverseMtx);
			PSMTXMultVec(inverseMtx, &cylinder->m_bottom, &s_cyl.m_bottom);
			PSMTXMultVec(inverseMtx, &cylinder->m_top, &s_cyl.m_top);
			PSMTXMultVecSR(inverseMtx, &cylinder->m_axis, &s_cyl.m_axis);
			PSMTXMultVecSR(inverseMtx, move, &s_mvec);

			s_cyl.m_radius = cylinder->m_radius;
			radiusPad = 1.0f + s_cyl.m_radius;
			if (s_cyl.m_bottom.x < s_cyl.m_top.x) {
				s_cyl.m_boundsMin.x = s_cyl.m_bottom.x - radiusPad;
				s_cyl.m_boundsMax.x = s_cyl.m_top.x + radiusPad;
			} else {
				s_cyl.m_boundsMin.x = s_cyl.m_top.x - radiusPad;
				s_cyl.m_boundsMax.x = s_cyl.m_bottom.x + radiusPad;
			}

			radiusPad = 1.0f + s_cyl.m_radius;
			if (s_cyl.m_bottom.y < s_cyl.m_top.y) {
				s_cyl.m_boundsMin.y = s_cyl.m_bottom.y - radiusPad;
				s_cyl.m_boundsMax.y = s_cyl.m_top.y + radiusPad;
			} else {
				s_cyl.m_boundsMin.y = s_cyl.m_top.y - radiusPad;
				s_cyl.m_boundsMax.y = s_cyl.m_bottom.y + radiusPad;
			}

			radiusPad = 1.0f + s_cyl.m_radius;
			if (s_cyl.m_bottom.z < s_cyl.m_top.z) {
				s_cyl.m_boundsMin.z = s_cyl.m_bottom.z - radiusPad;
				s_cyl.m_boundsMax.z = s_cyl.m_top.z + radiusPad;
			} else {
				s_cyl.m_boundsMin.z = s_cyl.m_top.z - radiusPad;
				s_cyl.m_boundsMax.z = s_cyl.m_bottom.z + radiusPad;
			}
			InsertShadow_level = flag;
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
	float boundMinX = octNode->m_boundMinX;
	bool overlap = false;
	bool xyOverlap = false;
	int xOverlap = false;

	if (boundMinX < s_cyl.m_boundsMin.x) {
		xOverlap = s_cyl.m_boundsMin.x <= octNode->m_boundMaxX;
	} else {
		if (boundMinX > s_cyl.m_boundsMin.x) {
			xOverlap = boundMinX <= s_cyl.m_boundsMax.x;
		} else {
			xOverlap = true;
		}
	}

	if (xOverlap) {
		float boundMinY = octNode->m_boundMinY;
		if (boundMinY < s_cyl.m_boundsMin.y) {
			xOverlap = s_cyl.m_boundsMin.y <= octNode->m_boundMaxY;
		} else {
			if (boundMinY > s_cyl.m_boundsMin.y) {
				xOverlap = boundMinY <= s_cyl.m_boundsMax.y;
			} else {
				xOverlap = true;
			}
		}
		if (xOverlap) {
			xyOverlap = true;
		}
	}

	if (xyOverlap) {
		float boundMinZ = octNode->m_boundMinZ;
		if (boundMinZ < s_cyl.m_boundsMin.z) {
			xOverlap = s_cyl.m_boundsMin.z <= octNode->m_boundMaxZ;
		} else {
			if (boundMinZ > s_cyl.m_boundsMin.z) {
				xOverlap = boundMinZ <= s_cyl.m_boundsMax.z;
			} else {
				xOverlap = true;
			}
		}
		if (xOverlap) {
			overlap = true;
		}
	}

	if (!overlap) {
		return;
	}

	if (octNode->m_meshCount != 0) {
		static_cast<CMapHit*>(m_mapObject->m_mapData)
		    ->CheckHitCylinderNear((CMapCylinder*)&s_cyl, &s_mvec,
		                           octNode->m_meshStart,
		                           octNode->m_meshCount,
		                           InsertShadow_level);
	}

	for (int i = 0; i < 8; i++) {
		COctNode* child = octNode->m_children[0];
		if (child == 0) {
			return;
		}

		float childBoundMinX = child->m_boundMinX;
		bool childOverlap = false;
		bool childXYOverlap = false;
		int childXOverlap = false;
		if (childBoundMinX < s_cyl.m_boundsMin.x) {
			childXOverlap = s_cyl.m_boundsMin.x <= child->m_boundMaxX;
		} else {
			if (childBoundMinX > s_cyl.m_boundsMin.x) {
				childXOverlap = childBoundMinX <= s_cyl.m_boundsMax.x;
			} else {
				childXOverlap = true;
			}
		}

		if (childXOverlap) {
			float childBoundMinY = child->m_boundMinY;
			if (childBoundMinY < s_cyl.m_boundsMin.y) {
				childXOverlap = s_cyl.m_boundsMin.y <= child->m_boundMaxY;
			} else {
				if (childBoundMinY > s_cyl.m_boundsMin.y) {
					childXOverlap = childBoundMinY <= s_cyl.m_boundsMax.y;
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
			if (childBoundMinZ < s_cyl.m_boundsMin.z) {
				childXOverlap = s_cyl.m_boundsMin.z <= child->m_boundMaxZ;
			} else {
				if (childBoundMinZ > s_cyl.m_boundsMin.z) {
					childXOverlap = childBoundMinZ <= s_cyl.m_boundsMax.z;
				} else {
					childXOverlap = true;
				}
			}
			if (childXOverlap) {
				childOverlap = true;
			}
		}

		if (childOverlap) {
			if (child->m_meshCount != 0) {
				static_cast<CMapHit*>(m_mapObject->m_mapData)
				    ->CheckHitCylinderNear((CMapCylinder*)&s_cyl, &s_mvec,
				                           child->m_meshStart,
				                           child->m_meshCount,
				                           InsertShadow_level);
			}

			for (int j = 0; j < 8; j++) {
				COctNode* grandChild = child->m_children[0];
				if (grandChild == 0) {
					break;
				}

				if ((reinterpret_cast<CBound*>(grandChild)->CheckCross(*reinterpret_cast<CBound*>(&s_cyl.m_boundsMin))) != 0) {
					if (grandChild->m_meshCount != 0) {
						static_cast<CMapHit*>(m_mapObject->m_mapData)
						    ->CheckHitCylinderNear((CMapCylinder*)&s_cyl, &s_mvec,
						                           grandChild->m_meshStart,
						                           grandChild->m_meshCount,
						                           InsertShadow_level);
					}

					for (int k = 0; k < 8; k++) {
						COctNode* greatGrandChild = grandChild->m_children[0];
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
		mapHit = static_cast<CMapHit*>(m_mapObject->m_mapData);
		if (mapHit != 0) {
			PSMTXInverse(m_mapObject->m_worldMtx, inverseMtx);
			PSMTXMultVec(inverseMtx, &cylinder->m_bottom, &s_cyl.m_bottom);
			PSMTXMultVec(inverseMtx, &cylinder->m_top, &s_cyl.m_top);
			PSMTXMultVecSR(inverseMtx, &cylinder->m_axis, &s_cyl.m_axis);
			PSMTXMultVecSR(inverseMtx, move, &s_mvec);

			s_cyl.m_radius = cylinder->m_radius;
			radiusPad = 1.0f + s_cyl.m_radius;
			if (s_cyl.m_bottom.x < s_cyl.m_top.x) {
				s_cyl.m_boundsMin.x = s_cyl.m_bottom.x - radiusPad;
				s_cyl.m_boundsMax.x = s_cyl.m_top.x + radiusPad;
			} else {
				s_cyl.m_boundsMin.x = s_cyl.m_top.x - radiusPad;
				s_cyl.m_boundsMax.x = s_cyl.m_bottom.x + radiusPad;
			}

			radiusPad = 1.0f + s_cyl.m_radius;
			if (s_cyl.m_bottom.y < s_cyl.m_top.y) {
				s_cyl.m_boundsMin.y = s_cyl.m_bottom.y - radiusPad;
				s_cyl.m_boundsMax.y = s_cyl.m_top.y + radiusPad;
			} else {
				s_cyl.m_boundsMin.y = s_cyl.m_top.y - radiusPad;
				s_cyl.m_boundsMax.y = s_cyl.m_bottom.y + radiusPad;
			}

			radiusPad = 1.0f + s_cyl.m_radius;
			if (s_cyl.m_bottom.z < s_cyl.m_top.z) {
				s_cyl.m_boundsMin.z = s_cyl.m_bottom.z - radiusPad;
				s_cyl.m_boundsMax.z = s_cyl.m_top.z + radiusPad;
			} else {
				s_cyl.m_boundsMin.z = s_cyl.m_top.z - radiusPad;
				s_cyl.m_boundsMax.z = s_cyl.m_bottom.z + radiusPad;
			}
			InsertShadow_level = flag;
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
	bool overlap;
	bool xyOverlap;
	int xOverlap;

	overlap = false;
	xyOverlap = false;
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
			xOverlap = other.m_min.z <= m_max.z;
		} else {
			if (m_min.z > other.m_min.z) {
				xOverlap = m_min.z <= other.m_max.z;
			} else {
				xOverlap = true;
			}
		}

		if (xOverlap) {
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

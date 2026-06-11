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

static const float kMapOctTreeBoundMinInit = 10000000000.0f;
static const float kMapOctTreeBoundMaxInit = -10000000000.0f;
static const float kMapOctTreeRadiusPad = 1.0f;
static const float kMapOctTreeDefaultOffsetZ = 0.0f;

static CBound s_bound(kMapOctTreeBoundMinInit, kMapOctTreeBoundMaxInit);
static CMapCylinder s_cyl(kMapOctTreeBoundMinInit, kMapOctTreeBoundMaxInit);
static Vec s_mvec;
static unsigned long s_insertLightBitIndex = 0;
static unsigned long s_insertShadowBitIndex = 0;
static int s_light_no = 0;
static unsigned long s_shadow_no = 0;
static unsigned long InsertShadow_level = 0;
static unsigned long clear_flag_mask = 0;
unsigned char s_bitMask;
unsigned char s_bitMaskDrawFlags;
static unsigned long octtree_draw_node_ct = 0;

static const char sMapOctTreeNodeMeshTypeFmt[] =
    "\n\n===============================================\n\n\t\t\tm_node=%d   m_meshtype=%d\n\n\n"
    "===============================================\n\n";
static const char s_mapocttree_cpp[] = "mapocttree.cpp";

namespace {
static inline unsigned char* Ptr(void* ptr, unsigned int offset)
{
    return reinterpret_cast<unsigned char*>(ptr) + offset;
}

static inline CMapObj* GetMapObjByIndex(unsigned short index)
{
    return MapMng.GetMapObj(index);
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
            signed char meshType = m_mapObject->m_meshType;
            if (meshType == 4) {
                m_mapObject->m_drawPriority = 0xFF;
                m_mapObject->m_baseDrawPriority = 0xFF;
                m_mapObject->m_enableFullScreenShadow = 0;
            } else if (meshType == 3) {
                m_mapObject->m_enableFullScreenShadow = 0;
            }
            break;
        }

        case 'NODN': {
            m_nodeCount = chunkFile.Get2();
            signed char mapObjType = m_mapObject->m_meshType;
            if ((mapObjType != 1) && (static_cast<unsigned int>(System.m_execParam) >= 3U)) {
                System.Printf(const_cast<char*>(sMapOctTreeNodeMeshTypeFmt), m_nodeCount, mapObjType);
            }

            nodeCount = m_nodeCount;
            m_nodePool = new (MapMng.m_stage, const_cast<char*>(s_mapocttree_cpp), 0x59)
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
                            node->m_bound.m_min.x = chunkFile.GetF4();
                            node->m_bound.m_min.y = chunkFile.GetF4();
                            node->m_bound.m_min.z = chunkFile.GetF4();
                            node->m_bound.m_max.x = chunkFile.GetF4();
                            node->m_bound.m_max.y = chunkFile.GetF4();
                            node->m_bound.m_max.z = chunkFile.GetF4();
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
	int iVar5;
	COctNode* nodeIter;
	COctNode* pCVar4;
	COctNode* pCVar3;
	int iVar2;

	if ((octNode->m_meshCount != 0) &&
	    ((octNode->m_drawFlags & 1) != 0)) {
		MaterialMan.SetDefaultDrawEnv(0xACE0F);
		if (m_mapObject->m_enableFullScreenShadow != 0) {
			CameraPcs.SetFullScreenShadow(m_mapObject->m_worldMtx, 0);
		}
		if (m_mapObject->m_shadowTarget != 0) {
			MaterialMan.SetShadowBit32(static_cast<CMapShadow::TARGET>(1), &octNode->m_shadowFlags,
			                           m_mapObject->m_worldMtx);
		}
		MaterialMan.LockEnvInline();
		LightPcs.SetBit32(static_cast<CLightPcs::TARGET>(1), &octNode->m_lightFlags);
		m_mapObject->SetDrawEnv();
		static_cast<CMapMesh*>(m_mapObject->m_mapData)
			->DrawMesh(octNode->m_meshStart,
			           octNode->m_meshCount);
	}
	nodeIter = octNode;
	iVar2 = 0;
	do {
		pCVar4 = nodeIter->m_children[0];
		if (pCVar4 == 0) {
			return;
		}
		if ((pCVar4->m_meshCount != 0) &&
		    ((pCVar4->m_drawFlags & 1) != 0)) {
			MaterialMan.SetDefaultDrawEnv(0xACE0F);
			if (m_mapObject->m_enableFullScreenShadow != 0) {
				CameraPcs.SetFullScreenShadow(m_mapObject->m_worldMtx, 0);
			}
			if (m_mapObject->m_shadowTarget != 0) {
				MaterialMan.SetShadowBit32(static_cast<CMapShadow::TARGET>(1), &pCVar4->m_shadowFlags,
				                           m_mapObject->m_worldMtx);
			}
			MaterialMan.LockEnvInline();
			LightPcs.SetBit32(static_cast<CLightPcs::TARGET>(1), &pCVar4->m_lightFlags);
			m_mapObject->SetDrawEnv();
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
				if (m_mapObject->m_enableFullScreenShadow != 0) {
					CameraPcs.SetFullScreenShadow(m_mapObject->m_worldMtx, 0);
				}
				if (m_mapObject->m_shadowTarget != 0) {
					MaterialMan.SetShadowBit32(static_cast<CMapShadow::TARGET>(1), &pCVar3->m_shadowFlags,
					                           m_mapObject->m_worldMtx);
				}
				MaterialMan.LockEnv();
				LightPcs.SetBit32(static_cast<CLightPcs::TARGET>(1), &pCVar3->m_lightFlags);
				m_mapObject->SetDrawEnv();
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
#pragma inline_depth(6)
#pragma inline_max_size(10000)
#pragma inline_max_total_size(10000)
void COctTree::DrawCharaShadowTypeMeshFlag_r(COctNode* octNode)
{
	int i;

	if ((octNode->m_meshCount != 0) && ((octNode->m_drawFlags & 1) != 0)) {
		static_cast<CMapMesh*>(m_mapObject->m_mapData)
			->DrawMeshCharaShadow(octNode->m_meshStart, octNode->m_meshCount);
	}
	for (i = 0; i < 8; i++) {
		if (octNode->m_children[i] == 0) {
			return;
		}
		DrawCharaShadowTypeMeshFlag_r(octNode->m_children[i]);
	}
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
	unsigned char andMask;
	unsigned char orMask;
	int farCount;

	if ((m_localPos.x <= octNode->m_bound.m_max.x) && (m_localPos.y <= octNode->m_bound.m_max.y) &&
	    (m_localPos.z <= octNode->m_bound.m_max.z) && (m_localPos.x >= octNode->m_bound.m_min.x) &&
	    (m_localPos.y >= octNode->m_bound.m_min.y) && (m_localPos.z >= octNode->m_bound.m_min.z)) {
		orMask = 0xF;
	} else {
		Vec localCorner;
		Vec viewPos;
		float maxDepth = kMapOctTreeBoundMinInit;
		float minDepth = kMapOctTreeBoundMaxInit;

		andMask = 0xF;
		orMask = 0;
		farCount = 0;

		for (int x = 0; x < 2; x++) {
			localCorner.x = (x == 0) ? octNode->m_bound.m_min.x : octNode->m_bound.m_max.x;
			for (int y = 0; y < 2; y++) {
				localCorner.y = (y == 0) ? octNode->m_bound.m_min.y : octNode->m_bound.m_max.y;
				for (int z = 0; z < 2; z++) {
					unsigned char clipFlags;
					double depth;

					localCorner.z = (z == 0) ? octNode->m_bound.m_min.z : octNode->m_bound.m_max.z;
					PSMTXMultVec(m_cullMtx, &localCorner, &viewPos);

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
		if (maxDepth < MapMng.m_octTreeDrawMinDepth) {
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
		unsigned char mapDrawType = mapObj->m_drawPriority;
		unsigned char targetDrawType = drawType;
		if ((mapDrawType == targetDrawType) && ((mapObj->m_showFlags & 1) != 0)) {
			if ((MapMng.m_underWaterTexPending != 0) &&
			    ((mapObj->m_bumpLight != 0) &&
			     (reinterpret_cast<CLightPcs::CBumpLight*>(mapObj->m_bumpLight)->m_useViewSpace == 2))) {
				MaterialMan.SetUnderWaterTex();
				MapMng.m_underWaterTexPending = 0;
			}

			mapObj = m_mapObject;
			LightPcs.SetBumpTexMatirx(mapObj->m_worldMtx,
			                          reinterpret_cast<CLightPcs::CBumpLight*>(mapObj->m_bumpLight),
			                          reinterpret_cast<Vec*>(&mapObj->m_transRateX),
			                          mapObj->m_bumpTexMatrixMode);
			if (kMapOctTreeDefaultOffsetZ != m_mapObject->m_zBufferOffset) {
				CameraPcs.SetOffsetZBuff(m_mapObject->m_zBufferOffset);
			}
			if (m_mapObject->m_disableZWrite != 0) {
				GXSetZMode(1, (GXCompare)3, 0);
			}
			static_cast<CMapMesh*>(m_mapObject->m_mapData)->SetRenderArray();
			DrawTypeMeshFlag_r(m_nodePool);
			if (m_mapObject->m_disableZWrite != 0) {
				GXSetZMode(1, (GXCompare)3, 1);
			}
			float offsetZ = m_mapObject->m_zBufferOffset;
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
		unsigned char mapDrawType = mapObj->m_drawPriority;
		unsigned char targetDrawType = drawType;
		if (mapDrawType != targetDrawType) {
			return;
		}

		LightPcs.SetBumpTexMatirx(mapObj->m_worldMtx, 0, reinterpret_cast<Vec*>(&mapObj->m_transRateX),
		                          mapObj->m_bumpTexMatrixMode);

		if (kMapOctTreeDefaultOffsetZ != m_mapObject->m_zBufferOffset) {
			CameraPcs.SetOffsetZBuff(m_mapObject->m_zBufferOffset);
		}

		static_cast<CMapMesh*>(m_mapObject->m_mapData)->SetRenderArray();
		DrawCharaShadowTypeMeshFlag_r(m_nodePool);

		float offsetZ = m_mapObject->m_zBufferOffset;
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

	if (((m_drawFlags & 1) == 0) && (m_mapObject->m_mapDataType == 1)) {
		PSMTXConcat(MapMng.m_scaledViewMtxPrimary, m_mapObject->m_worldMtx, m_cullMtx);
		PSMTXConcat(MapMng.m_viewMtx,
		            m_mapObject->m_worldMtx, localMtx);
		PSMTXInverse(localMtx, localMtx);

		m_localPos.x = localMtx[0][3];
		m_localPos.y = localMtx[1][3];
		m_localPos.z = localMtx[2][3];
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
#pragma inline_depth(6)
void ClearLight_r(COctNode* octNode)
{
	int i;

	if (octNode->m_meshCount != 0) {
		octNode->m_lightFlags = 0;
	}
	for (i = 0; i < 8; i++) {
		if (octNode->m_children[i] == 0) {
			return;
		}
		ClearLight_r(octNode->m_children[i]);
	}
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
	float boundMinX = node->m_bound.m_min.x;
	bool overlap = false;
	bool xyOverlap = false;
	int xOverlap = false;

	if (boundMinX < s_bound.m_min.x) {
		xOverlap = s_bound.m_min.x <= node->m_bound.m_max.x;
	} else {
		if (boundMinX > s_bound.m_min.x) {
			xOverlap = boundMinX <= s_bound.m_max.x;
		} else {
			xOverlap = true;
		}
	}

	if (xOverlap) {
		float boundMinY = node->m_bound.m_min.y;
		if (boundMinY < s_bound.m_min.y) {
			xOverlap = s_bound.m_min.y <= node->m_bound.m_max.y;
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
		float boundMinZ = node->m_bound.m_min.z;
		if (boundMinZ < s_bound.m_min.z) {
			xOverlap = s_bound.m_min.z <= node->m_bound.m_max.z;
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
		unsigned long byteOffset = (s_insertLightBitIndex >> 3) & 0x1ffffffc;
		unsigned long* bits = reinterpret_cast<unsigned long*>(Ptr(&node->m_lightFlags, byteOffset));
		*bits |= 1UL << (s_insertLightBitIndex & 0x1f);
	}

	COctNode* nodeIter = node;
	for (int i = 0; i < 8; i++) {
		COctNode* child = nodeIter->m_children[0];
		if (child == 0) {
			return;
		}

		float childBoundMinX = child->m_bound.m_min.x;
		bool childOverlap = false;
		bool childXYOverlap = false;
		int childXOverlap = false;
		if (childBoundMinX < s_bound.m_min.x) {
			childXOverlap = s_bound.m_min.x <= child->m_bound.m_max.x;
		} else {
			if (childBoundMinX > s_bound.m_min.x) {
				childXOverlap = childBoundMinX <= s_bound.m_max.x;
			} else {
				childXOverlap = true;
			}
		}

		if (childXOverlap) {
			float childBoundMinY = child->m_bound.m_min.y;
			if (childBoundMinY < s_bound.m_min.y) {
				childXOverlap = s_bound.m_min.y <= child->m_bound.m_max.y;
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
			float childBoundMinZ = child->m_bound.m_min.z;
			if (childBoundMinZ < s_bound.m_min.z) {
				childXOverlap = s_bound.m_min.z <= child->m_bound.m_max.z;
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
				unsigned long byteOffset = (s_insertLightBitIndex >> 3) & 0x1ffffffc;
				unsigned long* bits = reinterpret_cast<unsigned long*>(Ptr(child, byteOffset));
				bits[0x44 / sizeof(unsigned long)] |= 1UL << (s_insertLightBitIndex & 0x1f);
			}

			for (int j = 0; j < 8; j++) {
				COctNode* grandChild = child->m_children[0];
				if (grandChild == 0) {
					break;
				}

				if (grandChild->GetBound()->CheckCross(s_bound) != 0) {
					if (grandChild->m_meshCount != 0) {
						setbit32(&grandChild->m_lightFlags, s_insertLightBitIndex);
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
				child = reinterpret_cast<COctNode*>(Ptr(child, 4));
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
	if (m_type != 0) {
		return;
	}

	if ((m_mapObject->m_lightSetIndex & mask) == 0) {
		return;
	}

	s_insertLightBitIndex = bitIndex;
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
	int i;

	if (node->m_meshCount != 0) {
		node->m_shadowFlags = 0;
	}
	for (i = 0; i < 8; i++) {
		if (node->m_children[i] == 0) {
			return;
		}
		ClearShadow_r(node->m_children[i]);
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
 * PAL Address: UNUSED
 * PAL Size: 500b
 * EN Address: UNUSED
 * EN Size: 156b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void SetShadow_r(COctNode* node)
{
	if (node->m_meshCount != 0) {
		setbit32(&node->m_shadowFlags, s_shadow_no);
	}

	COctNode* nodeIter = node;
	for (int i = 0; i < 8; i++) {
		COctNode* child = nodeIter->m_children[0];
		if (child == 0) {
			return;
		}

		if (child->m_meshCount != 0) {
			setbit32(&child->m_shadowFlags, s_shadow_no);
		}

		COctNode* childIter = child;
		for (int j = 0; j < 8; j++) {
			COctNode* grandChild = childIter->m_children[0];
			if (grandChild == 0) {
				break;
			}

			if (grandChild->m_meshCount != 0) {
				setbit32(&grandChild->m_shadowFlags, s_shadow_no);
			}

			COctNode* grandChildIter = grandChild;
			for (int k = 0; k < 8; k++) {
				COctNode* greatGrandChild = grandChildIter->m_children[0];
				if (greatGrandChild == 0) {
					break;
				}

				SetShadow_r(greatGrandChild);
				grandChildIter = reinterpret_cast<COctNode*>(Ptr(grandChildIter, 4));
			}

			childIter = reinterpret_cast<COctNode*>(Ptr(childIter, 4));
		}

		nodeIter = reinterpret_cast<COctNode*>(Ptr(nodeIter, 4));
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 40b
 * EN Address: UNUSED
 * EN Size: 60b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void COctTree::SetShadow(long bitIndex)
{
	s_shadow_no = bitIndex;
	SetShadow_r(m_nodePool);
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
	int j;
	COctNode* child;
	float boundMinX = node->m_bound.m_min.x;
	bool overlap = false;
	bool xyOverlap = false;
	int xOverlap = false;

	if (boundMinX < s_bound.m_min.x) {
		xOverlap = s_bound.m_min.x <= node->m_bound.m_max.x;
	} else {
		if (boundMinX > s_bound.m_min.x) {
			xOverlap = boundMinX <= s_bound.m_max.x;
		} else {
			xOverlap = true;
		}
	}

	if (xOverlap) {
		float boundMinY = node->m_bound.m_min.y;
		if (boundMinY < s_bound.m_min.y) {
			xOverlap = s_bound.m_min.y <= node->m_bound.m_max.y;
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
		float boundMinZ = node->m_bound.m_min.z;
		if (boundMinZ < s_bound.m_min.z) {
			xOverlap = s_bound.m_min.z <= node->m_bound.m_max.z;
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
		unsigned long byteOffset = (s_insertShadowBitIndex >> 3) & 0x1ffffffc;
		unsigned long* bits = reinterpret_cast<unsigned long*>(Ptr(&node->m_shadowFlags, byteOffset));
		*bits |= 1UL << (s_insertShadowBitIndex & 0x1f);
	}

	COctNode* nodeIter = node;
	for (int i = 0; i < 8; i++) {
		if (nodeIter->m_children[0] == 0) {
			return;
		}

		s_light_no++;
		child = nodeIter->m_children[0];

		float childBoundMinX = child->m_bound.m_min.x;
		bool childOverlap = false;
		bool childXYOverlap = false;
		int childXOverlap = false;
		if (childBoundMinX < s_bound.m_min.x) {
			childXOverlap = s_bound.m_min.x <= child->m_bound.m_max.x;
		} else {
			if (childBoundMinX > s_bound.m_min.x) {
				childXOverlap = childBoundMinX <= s_bound.m_max.x;
			} else {
				childXOverlap = true;
			}
		}

		if (childXOverlap) {
			float childBoundMinY = child->m_bound.m_min.y;
			if (childBoundMinY < s_bound.m_min.y) {
				childXOverlap = s_bound.m_min.y <= child->m_bound.m_max.y;
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
			float childBoundMinZ = child->m_bound.m_min.z;
			if (childBoundMinZ < s_bound.m_min.z) {
				childXOverlap = s_bound.m_min.z <= child->m_bound.m_max.z;
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
				unsigned long byteOffset = (s_insertShadowBitIndex >> 3) & 0x1ffffffc;
				unsigned long* bits = reinterpret_cast<unsigned long*>(Ptr(child, byteOffset));
				bits[0x48 / sizeof(unsigned long)] |= 1UL << (s_insertShadowBitIndex & 0x1f);
			}

			for (j = 0; j < 8; j++) {
				if (child->m_children[0] == 0) {
					break;
				}

				s_light_no++;
				COctNode* grandChild = child->m_children[0];

				if (grandChild->GetBound()->CheckCross(s_bound) != 0) {
					if ((s_light_no >= 3) && (grandChild->m_meshCount != 0)) {
						setbit32(&grandChild->m_shadowFlags, s_insertShadowBitIndex);
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
				child = reinterpret_cast<COctNode*>(Ptr(child, 4));
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
		s_insertShadowBitIndex = bitIndex;
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
#pragma inline_depth(8)
void ClearFlag_r(COctNode* node)
{
	int i;

	if (node->m_meshCount != 0) {
		node->m_drawFlags &= s_shadow_no;
	}
	for (i = 0; i < 8; i++) {
		if (node->m_children[i] == 0) {
			return;
		}
		ClearFlag_r(node->m_children[i]);
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
	float boundMinX = node->m_bound.m_min.x;
	bool overlap;
	bool xyOverlap;
	int xOverlap;

	xyOverlap = overlap = false;
	if (boundMinX < s_cyl.m_bound.m_min.x) {
		xOverlap = s_cyl.m_bound.m_min.x <= node->m_bound.m_max.x;
	} else {
		if (boundMinX > s_cyl.m_bound.m_min.x) {
			xOverlap = boundMinX <= s_cyl.m_bound.m_max.x;
		} else {
			xOverlap = true;
		}
	}

	if (xOverlap) {
		float boundMinY = node->m_bound.m_min.y;
		if (boundMinY < s_cyl.m_bound.m_min.y) {
			xOverlap = s_cyl.m_bound.m_min.y <= node->m_bound.m_max.y;
		} else {
			if (boundMinY > s_cyl.m_bound.m_min.y) {
				xOverlap = boundMinY <= s_cyl.m_bound.m_max.y;
			} else {
				xOverlap = true;
			}
		}
		if (xOverlap) {
			xyOverlap = true;
		}
	}

	if (xyOverlap) {
		float boundMinZ = node->m_bound.m_min.z;
		if (boundMinZ < s_cyl.m_bound.m_min.z) {
			xOverlap = s_cyl.m_bound.m_min.z <= node->m_bound.m_max.z;
		} else {
			if (boundMinZ > s_cyl.m_bound.m_min.z) {
				xOverlap = boundMinZ <= s_cyl.m_bound.m_max.z;
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
				 ->CheckHitCylinder(&s_cyl, &s_mvec,
									node->m_meshStart,
									node->m_meshCount,
									InsertShadow_level) != 0)) {
			return 1;
		}

		CBound* cylBound = s_cyl.GetBound();
		COctNode* nodeIter = node;
		for (int i = 0; i < 8; i++) {
			COctNode* child = nodeIter->m_children[0];
			if (child == 0) {
				break;
			}

			float childBoundMinX = child->m_bound.m_min.x;
			bool childOverlap;
			bool childXYOverlap;
			int childXOverlap;

			childXYOverlap = childOverlap = false;
			if (childBoundMinX < s_cyl.m_bound.m_min.x) {
				childXOverlap = s_cyl.m_bound.m_min.x <= child->m_bound.m_max.x;
			} else {
				if (childBoundMinX > s_cyl.m_bound.m_min.x) {
					childXOverlap = childBoundMinX <= s_cyl.m_bound.m_max.x;
				} else {
					childXOverlap = true;
				}
			}

			if (childXOverlap) {
				float childBoundMinY = child->m_bound.m_min.y;
				if (childBoundMinY < s_cyl.m_bound.m_min.y) {
					childXOverlap = s_cyl.m_bound.m_min.y <= child->m_bound.m_max.y;
				} else {
					if (childBoundMinY > s_cyl.m_bound.m_min.y) {
						childXOverlap = childBoundMinY <= s_cyl.m_bound.m_max.y;
					} else {
						childXOverlap = true;
					}
				}
				if (childXOverlap) {
					childXYOverlap = true;
				}
			}

			if (childXYOverlap) {
				float childBoundMinZ = child->m_bound.m_min.z;
				if (childBoundMinZ < s_cyl.m_bound.m_min.z) {
					childXOverlap = s_cyl.m_bound.m_min.z <= child->m_bound.m_max.z;
				} else {
					if (childBoundMinZ > s_cyl.m_bound.m_min.z) {
						childXOverlap = childBoundMinZ <= s_cyl.m_bound.m_max.z;
					} else {
						childXOverlap = true;
					}
				}
				if (childXOverlap) {
					childOverlap = true;
				}
			}

			int childHit;
			if (childOverlap) {
				if ((child->m_meshCount != 0) &&
					(static_cast<CMapHit*>(m_mapObject->m_mapData)
						 ->CheckHitCylinder(&s_cyl, &s_mvec,
											child->m_meshStart,
											child->m_meshCount,
											InsertShadow_level) != 0)) {
					childHit = true;
					goto childJoin;
				}

				for (int j = 0; j < 8; j++) {
					COctNode* grandChild = child->m_children[0];
					int grandHit;
					if (grandChild == 0) {
						break;
					}

					if (grandChild->GetBound()->CheckCross(*cylBound) != 0) {
						if ((grandChild->m_meshCount != 0) &&
							(static_cast<CMapHit*>(m_mapObject->m_mapData)
								 ->CheckHitCylinder(&s_cyl, &s_mvec,
													grandChild->m_meshStart,
													grandChild->m_meshCount,
													InsertShadow_level) != 0)) {
							grandHit = true;
						} else {
							for (int k = 0; k < 8; k++) {
								COctNode* greatGrandChild = grandChild->m_children[0];
								if (greatGrandChild == 0) {
									break;
								}

								if (CheckHitCylinder_r(greatGrandChild) != 0) {
									grandHit = true;
									goto grandJoin;
								}
								grandChild = reinterpret_cast<COctNode*>(Ptr(grandChild, 4));
							}
							grandHit = false;
						}
					} else {
						grandHit = false;
					}
				grandJoin:
					if (grandHit) {
						childHit = true;
						goto childJoin;
					}
					child = reinterpret_cast<COctNode*>(Ptr(child, 4));
				}
			}
			childHit = false;
		childJoin:
			if (childHit) {
				return 1;
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
			radiusPad = kMapOctTreeRadiusPad + s_cyl.m_radius;
			if (s_cyl.m_bottom.x < s_cyl.m_top.x) {
				s_cyl.m_bound.m_min.x = s_cyl.m_bottom.x - radiusPad;
				s_cyl.m_bound.m_max.x = s_cyl.m_top.x + radiusPad;
			} else {
				s_cyl.m_bound.m_min.x = s_cyl.m_top.x - radiusPad;
				s_cyl.m_bound.m_max.x = s_cyl.m_bottom.x + radiusPad;
			}

			radiusPad = kMapOctTreeRadiusPad + s_cyl.m_radius;
			if (s_cyl.m_bottom.y < s_cyl.m_top.y) {
				s_cyl.m_bound.m_min.y = s_cyl.m_bottom.y - radiusPad;
				s_cyl.m_bound.m_max.y = s_cyl.m_top.y + radiusPad;
			} else {
				s_cyl.m_bound.m_min.y = s_cyl.m_top.y - radiusPad;
				s_cyl.m_bound.m_max.y = s_cyl.m_bottom.y + radiusPad;
			}

			radiusPad = kMapOctTreeRadiusPad + s_cyl.m_radius;
			if (s_cyl.m_bottom.z < s_cyl.m_top.z) {
				s_cyl.m_bound.m_min.z = s_cyl.m_bottom.z - radiusPad;
				s_cyl.m_bound.m_max.z = s_cyl.m_top.z + radiusPad;
			} else {
				s_cyl.m_bound.m_min.z = s_cyl.m_top.z - radiusPad;
				s_cyl.m_bound.m_max.z = s_cyl.m_bottom.z + radiusPad;
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
	float boundMinX = octNode->m_bound.m_min.x;
	bool overlap = false;
	bool xyOverlap = false;
	int xOverlap = false;

	if (boundMinX < s_cyl.m_bound.m_min.x) {
		xOverlap = s_cyl.m_bound.m_min.x <= octNode->m_bound.m_max.x;
	} else {
		if (boundMinX > s_cyl.m_bound.m_min.x) {
			xOverlap = boundMinX <= s_cyl.m_bound.m_max.x;
		} else {
			xOverlap = true;
		}
	}

	if (xOverlap) {
		float boundMinY = octNode->m_bound.m_min.y;
		if (boundMinY < s_cyl.m_bound.m_min.y) {
			xOverlap = s_cyl.m_bound.m_min.y <= octNode->m_bound.m_max.y;
		} else {
			if (boundMinY > s_cyl.m_bound.m_min.y) {
				xOverlap = boundMinY <= s_cyl.m_bound.m_max.y;
			} else {
				xOverlap = true;
			}
		}
		if (xOverlap) {
			xyOverlap = true;
		}
	}

	if (xyOverlap) {
		float boundMinZ = octNode->m_bound.m_min.z;
		if (boundMinZ < s_cyl.m_bound.m_min.z) {
			xOverlap = s_cyl.m_bound.m_min.z <= octNode->m_bound.m_max.z;
		} else {
			if (boundMinZ > s_cyl.m_bound.m_min.z) {
				xOverlap = boundMinZ <= s_cyl.m_bound.m_max.z;
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
		    ->CheckHitCylinderNear(&s_cyl, &s_mvec,
		                           octNode->m_meshStart,
		                           octNode->m_meshCount,
		                           InsertShadow_level);
	}

	CBound* cylBound = s_cyl.GetBound();
	COctNode* nodeIter = octNode;
	for (int i = 0; i < 8; i++) {
		COctNode* child = nodeIter->m_children[0];
		if (child == 0) {
			return;
		}

		float childBoundMinX = child->m_bound.m_min.x;
		bool childOverlap = false;
		bool childXYOverlap = false;
		int childXOverlap = false;
		if (childBoundMinX < s_cyl.m_bound.m_min.x) {
			childXOverlap = s_cyl.m_bound.m_min.x <= child->m_bound.m_max.x;
		} else {
			if (childBoundMinX > s_cyl.m_bound.m_min.x) {
				childXOverlap = childBoundMinX <= s_cyl.m_bound.m_max.x;
			} else {
				childXOverlap = true;
			}
		}

		if (childXOverlap) {
			float childBoundMinY = child->m_bound.m_min.y;
			if (childBoundMinY < s_cyl.m_bound.m_min.y) {
				childXOverlap = s_cyl.m_bound.m_min.y <= child->m_bound.m_max.y;
			} else {
				if (childBoundMinY > s_cyl.m_bound.m_min.y) {
					childXOverlap = childBoundMinY <= s_cyl.m_bound.m_max.y;
				} else {
					childXOverlap = true;
				}
			}
			if (childXOverlap) {
				childXYOverlap = true;
			}
		}

		if (childXYOverlap) {
			float childBoundMinZ = child->m_bound.m_min.z;
			if (childBoundMinZ < s_cyl.m_bound.m_min.z) {
				childXOverlap = s_cyl.m_bound.m_min.z <= child->m_bound.m_max.z;
			} else {
				if (childBoundMinZ > s_cyl.m_bound.m_min.z) {
					childXOverlap = childBoundMinZ <= s_cyl.m_bound.m_max.z;
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
				    ->CheckHitCylinderNear(&s_cyl, &s_mvec,
				                           child->m_meshStart,
				                           child->m_meshCount,
				                           InsertShadow_level);
			}

			for (int j = 0; j < 8; j++) {
				COctNode* grandChild = child->m_children[0];
				if (grandChild == 0) {
					break;
				}

				if (grandChild->GetBound()->CheckCross(*cylBound) != 0) {
					if (grandChild->m_meshCount != 0) {
						static_cast<CMapHit*>(m_mapObject->m_mapData)
						    ->CheckHitCylinderNear(&s_cyl, &s_mvec,
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
		nodeIter = reinterpret_cast<COctNode*>(Ptr(nodeIter, 4));
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
			radiusPad = kMapOctTreeRadiusPad + s_cyl.m_radius;
			if (s_cyl.m_bottom.x < s_cyl.m_top.x) {
				s_cyl.m_bound.m_min.x = s_cyl.m_bottom.x - radiusPad;
				s_cyl.m_bound.m_max.x = s_cyl.m_top.x + radiusPad;
			} else {
				s_cyl.m_bound.m_min.x = s_cyl.m_top.x - radiusPad;
				s_cyl.m_bound.m_max.x = s_cyl.m_bottom.x + radiusPad;
			}

			radiusPad = kMapOctTreeRadiusPad + s_cyl.m_radius;
			if (s_cyl.m_bottom.y < s_cyl.m_top.y) {
				s_cyl.m_bound.m_min.y = s_cyl.m_bottom.y - radiusPad;
				s_cyl.m_bound.m_max.y = s_cyl.m_top.y + radiusPad;
			} else {
				s_cyl.m_bound.m_min.y = s_cyl.m_top.y - radiusPad;
				s_cyl.m_bound.m_max.y = s_cyl.m_bottom.y + radiusPad;
			}

			radiusPad = kMapOctTreeRadiusPad + s_cyl.m_radius;
			if (s_cyl.m_bottom.z < s_cyl.m_top.z) {
				s_cyl.m_bound.m_min.z = s_cyl.m_bottom.z - radiusPad;
				s_cyl.m_bound.m_max.z = s_cyl.m_top.z + radiusPad;
			} else {
				s_cyl.m_bound.m_min.z = s_cyl.m_top.z - radiusPad;
				s_cyl.m_bound.m_max.z = s_cyl.m_bottom.z + radiusPad;
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
	m_stdTexMapId = m_texMapIdCur;
	m_stdTexMtx = m_texMtxCur;
	m_stdTexCoordId = m_texCoordIdCur;
	m_stdEnvTevBit = m_curEnvTevBit;
}

/*
 * --INFO--
 * PAL Address: 8002ef48
 * PAL Size: 84b
 */
void CMaterialMan::InitEnv()
{
	m_curEnvTevBit = 0x000ACE0F;
	m_activeEnvTevBit = 0xFFFFFFFF;
	m_vtxDescMode = 0xFF;
	m_stdTexMapId = 0;
	m_texMapIdCur = 0;
	m_stdTexMtx = 0x1E;
	m_texMtxCur = 0x1E;
	m_stdTexCoordId = 0;
	m_texCoordIdCur = 0;
	m_blendMode = 0xFF;
	m_fogEnable = 0xFF;
	m_shadowMaterialCount = 0;
	m_shadowTextureCount = 0;
	m_shadowKColorMask = 0;
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
	xyOverlap = overlap;
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

	return (unsigned char)overlap;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
COctNode::COctNode() : m_bound(kMapOctTreeBoundMinInit, kMapOctTreeBoundMaxInit)
{
	m_lightFlags = 0;
	m_shadowFlags = 0;
}

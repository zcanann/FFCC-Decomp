#include "ffcc/mapocttree.h"
#include "ffcc/chunkfile.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/mapmesh.h"
#include "ffcc/memory.h"
#include "ffcc/materialman.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_light.h"

extern float lbl_8032F96C;
extern float lbl_8032F970;
extern float lbl_8032F960;
extern float lbl_8032F964;
extern CMaterialMan MaterialMan;
extern CLightPcs LightPcs;
static unsigned long s_clearFlagMask;
static CBound s_bound;
static CMapCylinder s_cyl;
static Vec s_mvec;
static unsigned long s_checkHitCylinderMask;
static unsigned long s_insertShadowBitIndex;
static int s_insertShadowDepth;

extern "C" void __dl__FPv(void*);
extern "C" void __dla__FPv(void*);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void __ct__8COctNodeFv(void*);
extern "C" void* __construct_new_array(void*, void*, void*, unsigned long, unsigned long);

static char s_mapocttree_cpp[] = "mapocttree.cpp";

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
	*(unsigned int*)((unsigned char*)this + 0x4) = 0;
	*(unsigned int*)((unsigned char*)this + 0x8) = 0;
	*(unsigned int*)((unsigned char*)this + 0x48) = 0;
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
	COctNode* rootNode = *(COctNode**)((unsigned char*)this + 0x4);

	if (rootNode != 0) {
		__dla__FPv(rootNode);
		*(COctNode**)((unsigned char*)this + 0x4) = 0;
	}

	*(void**)((unsigned char*)this + 0x8) = 0;
	*(unsigned short*)((unsigned char*)this + 0x2) = 0;
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
extern "C" COctTree* dtor_8002F384(COctTree* octTree, short param_2)
{
	if (octTree != 0) {
		octTree->~COctTree();
		if (0 < param_2) {
			__dl__FPv(octTree);
		}
	}

	return octTree;
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

    *Ptr(this, 1) = 0;
    chunkFile.PushChunk();

    for (;;) {
        if (!chunkFile.GetNextChunk(chunk)) {
            chunkFile.PopChunk();
            return;
        }

        if (chunk.m_id == 'OBJN') {
            unsigned short objIndex = chunkFile.Get2();
            *reinterpret_cast<void**>(Ptr(this, 8)) = GetMapObjByIndex(objIndex);

            unsigned char* mapObj = *reinterpret_cast<unsigned char**>(Ptr(this, 8));
            if (mapObj[0x1E] == 4) {
                mapObj[0x15] = 0xFF;
                mapObj[0x14] = 0xFF;
                mapObj[0x22] = 0;
            } else if (mapObj[0x1E] == 3) {
                mapObj[0x22] = 0;
            }
            continue;
        }

        if (chunk.m_id == 'NODN') {
            unsigned short nodeCount = chunkFile.Get2();
            *reinterpret_cast<unsigned short*>(Ptr(this, 2)) = nodeCount;
            void* rootNode = __nwa__FUlPQ27CMemory6CStagePci(
                nodeCount * 0x4C + 0x10, *reinterpret_cast<CMemory::CStage**>(&MapMng), s_mapocttree_cpp, 0x59);
            *reinterpret_cast<void**>(Ptr(this, 4)) = __construct_new_array(
                rootNode, reinterpret_cast<void*>(__ct__8COctNodeFv), 0, 0x4C, nodeCount);
            continue;
        }

        if (chunk.m_id == 'INFO') {
            *Ptr(this, 1) = chunkFile.Get1();
            continue;
        }

        if (chunk.m_id == 'TYPE') {
            *Ptr(this, 0) = static_cast<unsigned char>(chunkFile.Get2());
            continue;
        }

        if (chunk.m_id != 'TREE') {
            continue;
        }

        chunkFile.PushChunk();
        while (chunkFile.GetNextChunk(chunk)) {
            if (chunk.m_id != 'NODE') {
                continue;
            }

            chunkFile.PushChunk();
            COctNode* node = 0;
            while (chunkFile.GetNextChunk(chunk)) {
                if (chunk.m_id == 'OBJ ') {
                    unsigned short nodeIndex = chunkFile.Get2();
                    node = reinterpret_cast<COctNode*>(Ptr(*reinterpret_cast<void**>(Ptr(this, 4)), nodeIndex * 0x4C));

                    *reinterpret_cast<unsigned short*>(Ptr(node, 0x3C)) = chunkFile.Get2();
                    *reinterpret_cast<unsigned short*>(Ptr(node, 0x3E)) = chunkFile.Get2();
                    continue;
                }

                if (node == 0) {
                    continue;
                }

                if (chunk.m_id == 'BOND') {
                    *reinterpret_cast<float*>(Ptr(node, 0x00)) = chunkFile.GetF4();
                    *reinterpret_cast<float*>(Ptr(node, 0x04)) = chunkFile.GetF4();
                    *reinterpret_cast<float*>(Ptr(node, 0x08)) = chunkFile.GetF4();
                    *reinterpret_cast<float*>(Ptr(node, 0x0C)) = chunkFile.GetF4();
                    *reinterpret_cast<float*>(Ptr(node, 0x10)) = chunkFile.GetF4();
                    *reinterpret_cast<float*>(Ptr(node, 0x14)) = chunkFile.GetF4();
                    continue;
                }

                if (chunk.m_id == 'CHLD') {
                    int childCount = 0;

                    for (int i = 0; i < 8; i++) {
                        unsigned short childIndex = chunkFile.Get2();
                        if (childIndex != 0xFFFF) {
                            COctNode* child = reinterpret_cast<COctNode*>(Ptr(*reinterpret_cast<void**>(Ptr(this, 4)), childIndex * 0x4C));
                            *reinterpret_cast<COctNode**>(Ptr(node, 0x1C + (childCount * 4))) = child;
                            childCount++;
                        }
                    }

                    for (int i = childCount; i < 8; i++) {
                        *reinterpret_cast<COctNode**>(Ptr(node, 0x1C + (i * 4))) = 0;
                    }
                }
            }
            chunkFile.PopChunk();
        }
        chunkFile.PopChunk();
    }
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

	if ((*reinterpret_cast<unsigned short*>(Ptr(octNode, 0x3E)) != 0) &&
	    ((*reinterpret_cast<unsigned long*>(Ptr(octNode, 0x40)) & 1) != 0)) {
		MaterialMan.InitEnv();
		if (*reinterpret_cast<unsigned char*>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0x22)) != 0) {
			CameraPcs.SetFullScreenShadow(reinterpret_cast<float(*)[4]>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xB8)), 0);
		}
		if (*reinterpret_cast<unsigned long*>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0x3C)) != 0) {
			MaterialMan.SetShadowBit32(static_cast<CMapShadow::TARGET>(1), reinterpret_cast<unsigned long*>(Ptr(octNode, 0x44)),
			                           reinterpret_cast<float(*)[4]>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xB8)));
		}
		MaterialMan.LockEnv();
		LightPcs.SetBit32(static_cast<CLightPcs::TARGET>(1), reinterpret_cast<unsigned long*>(Ptr(octNode, 0x40)));
		(*reinterpret_cast<CMapObj**>(Ptr(this, 0x8)))->SetDrawEnv();
		(*reinterpret_cast<CMapMesh**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xC)))
			->DrawMesh(*reinterpret_cast<unsigned short*>(Ptr(octNode, 0x3C)),
			           *reinterpret_cast<unsigned short*>(Ptr(octNode, 0x3E)));
	}
	iVar2 = 0;
	do {
		pCVar4 = *reinterpret_cast<COctNode**>(Ptr(octNode, 0x1C));
		if (pCVar4 == 0) {
			return;
		}
		if ((*reinterpret_cast<unsigned short*>(Ptr(pCVar4, 0x3E)) != 0) &&
		    ((*reinterpret_cast<unsigned long*>(Ptr(pCVar4, 0x40)) & 1) != 0)) {
			MaterialMan.InitEnv();
			if (*reinterpret_cast<unsigned char*>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0x22)) != 0) {
				CameraPcs.SetFullScreenShadow(reinterpret_cast<float(*)[4]>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xB8)), 0);
			}
			if (*reinterpret_cast<unsigned long*>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0x3C)) != 0) {
				MaterialMan.SetShadowBit32(static_cast<CMapShadow::TARGET>(1), reinterpret_cast<unsigned long*>(Ptr(pCVar4, 0x44)),
				                           reinterpret_cast<float(*)[4]>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xB8)));
			}
			MaterialMan.LockEnv();
			LightPcs.SetBit32(static_cast<CLightPcs::TARGET>(1), reinterpret_cast<unsigned long*>(Ptr(pCVar4, 0x40)));
			(*reinterpret_cast<CMapObj**>(Ptr(this, 0x8)))->SetDrawEnv();
			(*reinterpret_cast<CMapMesh**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xC)))
				->DrawMesh(*reinterpret_cast<unsigned short*>(Ptr(pCVar4, 0x3C)),
				           *reinterpret_cast<unsigned short*>(Ptr(pCVar4, 0x3E)));
		}
		iVar5 = 0;
		do {
			pCVar3 = *reinterpret_cast<COctNode**>(Ptr(pCVar4, 0x1C));
			if (pCVar3 == 0) {
				break;
			}
			if ((*reinterpret_cast<unsigned short*>(Ptr(pCVar3, 0x3E)) != 0) &&
			    ((*reinterpret_cast<unsigned long*>(Ptr(pCVar3, 0x40)) & 1) != 0)) {
				MaterialMan.InitEnv();
				if (*reinterpret_cast<unsigned char*>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0x22)) != 0) {
					CameraPcs.SetFullScreenShadow(reinterpret_cast<float(*)[4]>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xB8)), 0);
				}
				if (*reinterpret_cast<unsigned long*>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0x3C)) != 0) {
					MaterialMan.SetShadowBit32(static_cast<CMapShadow::TARGET>(1), reinterpret_cast<unsigned long*>(Ptr(pCVar3, 0x44)),
					                           reinterpret_cast<float(*)[4]>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xB8)));
				}
				MaterialMan.LockEnv();
				LightPcs.SetBit32(static_cast<CLightPcs::TARGET>(1), reinterpret_cast<unsigned long*>(Ptr(pCVar3, 0x40)));
				(*reinterpret_cast<CMapObj**>(Ptr(this, 0x8)))->SetDrawEnv();
				(*reinterpret_cast<CMapMesh**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xC)))
					->DrawMesh(*reinterpret_cast<unsigned short*>(Ptr(pCVar3, 0x3C)),
					           *reinterpret_cast<unsigned short*>(Ptr(pCVar3, 0x3E)));
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

	if ((*reinterpret_cast<unsigned short*>(Ptr(octNode, 0x3E)) != 0) &&
	    ((*reinterpret_cast<unsigned long*>(Ptr(octNode, 0x40)) & 1) != 0)) {
		reinterpret_cast<CMapMesh*>(*reinterpret_cast<void**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xC)))
			->DrawMeshCharaShadow(*reinterpret_cast<unsigned short*>(Ptr(octNode, 0x3C)),
			                      *reinterpret_cast<unsigned short*>(Ptr(octNode, 0x3E)));
	}

	iVar1 = 0;
	do {
		pCVar3 = *reinterpret_cast<COctNode**>(Ptr(octNode, 0x1C));
		if (pCVar3 == 0) {
			return;
		}
		if ((*reinterpret_cast<unsigned short*>(Ptr(pCVar3, 0x3E)) != 0) &&
		    ((*reinterpret_cast<unsigned long*>(Ptr(pCVar3, 0x40)) & 1) != 0)) {
			reinterpret_cast<CMapMesh*>(*reinterpret_cast<void**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xC)))
				->DrawMeshCharaShadow(*reinterpret_cast<unsigned short*>(Ptr(pCVar3, 0x3C)),
				                      *reinterpret_cast<unsigned short*>(Ptr(pCVar3, 0x3E)));
		}
		iVar2 = 0;
		do {
			pCVar8 = *reinterpret_cast<COctNode**>(Ptr(pCVar3, 0x1C));
			if (pCVar8 == 0) {
				break;
			}
			if ((*reinterpret_cast<unsigned short*>(Ptr(pCVar8, 0x3E)) != 0) &&
			    ((*reinterpret_cast<unsigned long*>(Ptr(pCVar8, 0x40)) & 1) != 0)) {
				reinterpret_cast<CMapMesh*>(*reinterpret_cast<void**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xC)))
					->DrawMeshCharaShadow(*reinterpret_cast<unsigned short*>(Ptr(pCVar8, 0x3C)),
					                      *reinterpret_cast<unsigned short*>(Ptr(pCVar8, 0x3E)));
			}
			iVar13 = 0;
			do {
				pCVar7 = *reinterpret_cast<COctNode**>(Ptr(pCVar8, 0x1C));
				if (pCVar7 == 0) {
					break;
				}
				if ((*reinterpret_cast<unsigned short*>(Ptr(pCVar7, 0x3E)) != 0) &&
				    ((*reinterpret_cast<unsigned long*>(Ptr(pCVar7, 0x40)) & 1) != 0)) {
					reinterpret_cast<CMapMesh*>(*reinterpret_cast<void**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xC)))
						->DrawMeshCharaShadow(*reinterpret_cast<unsigned short*>(Ptr(pCVar7, 0x3C)),
						                      *reinterpret_cast<unsigned short*>(Ptr(pCVar7, 0x3E)));
				}
				iVar12 = 0;
				do {
					pCVar6 = *reinterpret_cast<COctNode**>(Ptr(pCVar7, 0x1C));
					if (pCVar6 == 0) {
						break;
					}
					if ((*reinterpret_cast<unsigned short*>(Ptr(pCVar6, 0x3E)) != 0) &&
					    ((*reinterpret_cast<unsigned long*>(Ptr(pCVar6, 0x40)) & 1) != 0)) {
						reinterpret_cast<CMapMesh*>(*reinterpret_cast<void**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xC)))
							->DrawMeshCharaShadow(*reinterpret_cast<unsigned short*>(Ptr(pCVar6, 0x3C)),
							                      *reinterpret_cast<unsigned short*>(Ptr(pCVar6, 0x3E)));
					}
					iVar11 = 0;
					do {
						pCVar5 = *reinterpret_cast<COctNode**>(Ptr(pCVar6, 0x1C));
						if (pCVar5 == 0) {
							break;
						}
						if ((*reinterpret_cast<unsigned short*>(Ptr(pCVar5, 0x3E)) != 0) &&
						    ((*reinterpret_cast<unsigned long*>(Ptr(pCVar5, 0x40)) & 1) != 0)) {
							reinterpret_cast<CMapMesh*>(*reinterpret_cast<void**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xC)))
								->DrawMeshCharaShadow(*reinterpret_cast<unsigned short*>(Ptr(pCVar5, 0x3C)),
								                      *reinterpret_cast<unsigned short*>(Ptr(pCVar5, 0x3E)));
						}
						iVar10 = 0;
						do {
							pCVar4 = *reinterpret_cast<COctNode**>(Ptr(pCVar5, 0x1C));
							if (pCVar4 == 0) {
								break;
							}
							if ((*reinterpret_cast<unsigned short*>(Ptr(pCVar4, 0x3E)) != 0) &&
							    ((*reinterpret_cast<unsigned long*>(Ptr(pCVar4, 0x40)) & 1) != 0)) {
								reinterpret_cast<CMapMesh*>(*reinterpret_cast<void**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 0x8)), 0xC)))
									->DrawMeshCharaShadow(*reinterpret_cast<unsigned short*>(Ptr(pCVar4, 0x3C)),
									                      *reinterpret_cast<unsigned short*>(Ptr(pCVar4, 0x3E)));
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
	if (*reinterpret_cast<unsigned short*>(Ptr(octNode, 0x3E)) != 0) {
		*reinterpret_cast<unsigned long*>(Ptr(octNode, 0x40)) |= 1;
	}

	for (int i = 0; i < 8; i++) {
		child1 = *reinterpret_cast<COctNode**>(Ptr(octNode, 0x1C));
		if (child1 == 0) {
			return;
		}
		if (*reinterpret_cast<unsigned short*>(Ptr(child1, 0x3E)) != 0) {
			*reinterpret_cast<unsigned long*>(Ptr(child1, 0x40)) |= 1;
		}

		for (int j = 0; j < 8; j++) {
			child2 = *reinterpret_cast<COctNode**>(Ptr(child1, 0x1C));
			if (child2 == 0) {
				break;
			}
			if (*reinterpret_cast<unsigned short*>(Ptr(child2, 0x3E)) != 0) {
				*reinterpret_cast<unsigned long*>(Ptr(child2, 0x40)) |= 1;
			}

			for (int k = 0; k < 8; k++) {
				child3 = *reinterpret_cast<COctNode**>(Ptr(child2, 0x1C));
				if (child3 == 0) {
					break;
				}
				if (*reinterpret_cast<unsigned short*>(Ptr(child3, 0x3E)) != 0) {
					*reinterpret_cast<unsigned long*>(Ptr(child3, 0x40)) |= 1;
				}

				for (int m = 0; m < 8; m++) {
					child4 = *reinterpret_cast<COctNode**>(Ptr(child3, 0x1C));
					if (child4 == 0) {
						break;
					}
					if (*reinterpret_cast<unsigned short*>(Ptr(child4, 0x3E)) != 0) {
						*reinterpret_cast<unsigned long*>(Ptr(child4, 0x40)) |= 1;
					}

					for (int n = 0; n < 8; n++) {
						child5 = *reinterpret_cast<COctNode**>(Ptr(child4, 0x1C));
						if (child5 == 0) {
							break;
						}
						if (*reinterpret_cast<unsigned short*>(Ptr(child5, 0x3E)) != 0) {
							*reinterpret_cast<unsigned long*>(Ptr(child5, 0x40)) |= 1;
						}

						for (int o = 0; o < 8; o++) {
							child6 = *reinterpret_cast<COctNode**>(Ptr(child5, 0x1C));
							if (child6 == 0) {
								break;
							}
							if (*reinterpret_cast<unsigned short*>(Ptr(child6, 0x3E)) != 0) {
								*reinterpret_cast<unsigned long*>(Ptr(child6, 0x40)) |= 1;
							}

							for (int p = 0; p < 8; p++) {
								child7 = *reinterpret_cast<COctNode**>(Ptr(child6, 0x1C));
								if (child7 == 0) {
									break;
								}
								if (*reinterpret_cast<unsigned short*>(Ptr(child7, 0x3E)) != 0) {
									*reinterpret_cast<unsigned long*>(Ptr(child7, 0x40)) |= 1;
								}

								for (int q = 0; q < 8; q++) {
									child8 = *reinterpret_cast<COctNode**>(Ptr(child7, 0x1C));
									if (child8 == 0) {
										break;
									}
									if (*reinterpret_cast<unsigned short*>(Ptr(child8, 0x3E)) != 0) {
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
		float maxDepth = lbl_8032F96C;
		float minDepth = lbl_8032F970;
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

	if (*reinterpret_cast<unsigned short*>(Ptr(octNode, 0x3E)) != 0) {
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

	if (lbl_8032F964 != *reinterpret_cast<float*>(mapObj + 0x40)) {
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

	if (lbl_8032F964 != *reinterpret_cast<float*>(mapObj + 0x40)) {
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

	if (lbl_8032F964 != *reinterpret_cast<float*>(mapObj + 0x40)) {
		CameraPcs.SetOffsetZBuff(*reinterpret_cast<float*>(mapObj + 0x40));
	}

	reinterpret_cast<CMapMesh*>(*reinterpret_cast<void**>(mapObj + 0xC))->SetRenderArray();
	DrawCharaShadowTypeMeshFlag_r(*reinterpret_cast<COctNode**>(thisBytes + 4));

	if (lbl_8032F964 != *reinterpret_cast<float*>(mapObj + 0x40)) {
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

	if (*reinterpret_cast<unsigned short*>(Ptr(octNode, 0x3E)) != 0) {
		*reinterpret_cast<unsigned long*>(Ptr(octNode, 0x40)) = 0;
	}
	iVar1 = 0;
	do {
		pCVar8 = *reinterpret_cast<COctNode**>(Ptr(octNode, 0x1C));
		if (pCVar8 == 0) {
			return;
		}
		if (*reinterpret_cast<unsigned short*>(Ptr(pCVar8, 0x3E)) != 0) {
			*reinterpret_cast<unsigned long*>(Ptr(pCVar8, 0x40)) = 0;
		}
		iVar2 = 0;
		do {
			pCVar7 = *reinterpret_cast<COctNode**>(Ptr(pCVar8, 0x1C));
			if (pCVar7 == 0) break;
			if (*reinterpret_cast<unsigned short*>(Ptr(pCVar7, 0x3E)) != 0) {
				*reinterpret_cast<unsigned long*>(Ptr(pCVar7, 0x40)) = 0;
			}
			iVar13 = 0;
			do {
				pCVar6 = *reinterpret_cast<COctNode**>(Ptr(pCVar7, 0x1C));
				if (pCVar6 == 0) break;
				if (*reinterpret_cast<unsigned short*>(Ptr(pCVar6, 0x3E)) != 0) {
					*reinterpret_cast<unsigned long*>(Ptr(pCVar6, 0x40)) = 0;
				}
				iVar12 = 0;
				do {
					pCVar5 = *reinterpret_cast<COctNode**>(Ptr(pCVar6, 0x1C));
					if (pCVar5 == 0) break;
					if (*reinterpret_cast<unsigned short*>(Ptr(pCVar5, 0x3E)) != 0) {
						*reinterpret_cast<unsigned long*>(Ptr(pCVar5, 0x40)) = 0;
					}
					iVar11 = 0;
					do {
						pCVar4 = *reinterpret_cast<COctNode**>(Ptr(pCVar5, 0x1C));
						if (pCVar4 == 0) break;
						if (*reinterpret_cast<unsigned short*>(Ptr(pCVar4, 0x3E)) != 0) {
							*reinterpret_cast<unsigned long*>(Ptr(pCVar4, 0x40)) = 0;
						}
						iVar10 = 0;
						do {
							pCVar3 = *reinterpret_cast<COctNode**>(Ptr(pCVar4, 0x1C));
							if (pCVar3 == 0) break;
							if (*reinterpret_cast<unsigned short*>(Ptr(pCVar3, 0x3E)) != 0) {
								*reinterpret_cast<unsigned long*>(Ptr(pCVar3, 0x40)) = 0;
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
	ClearLight_r(*(COctNode**)((unsigned char*)this + 0x4));
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
	float boundMinX = *reinterpret_cast<float*>(Ptr(node, 0x0));
	bool xOverlap = false;
	bool xyOverlap = false;
	bool overlap = false;

	if (*reinterpret_cast<float*>(Ptr(&s_bound, 0x0)) <= boundMinX) {
		if (boundMinX <= *reinterpret_cast<float*>(Ptr(&s_bound, 0x0))) {
			xOverlap = true;
		} else {
			xOverlap = boundMinX <= *reinterpret_cast<float*>(Ptr(&s_bound, 0xC));
		}
	} else {
		xOverlap = *reinterpret_cast<float*>(Ptr(&s_bound, 0x0)) <= *reinterpret_cast<float*>(Ptr(node, 0xC));
	}

	if (xOverlap) {
		float boundMinY = *reinterpret_cast<float*>(Ptr(node, 0x4));
		if (*reinterpret_cast<float*>(Ptr(&s_bound, 0x4)) <= boundMinY) {
			if (boundMinY <= *reinterpret_cast<float*>(Ptr(&s_bound, 0x4))) {
				xOverlap = true;
			} else {
				xOverlap = boundMinY <= *reinterpret_cast<float*>(Ptr(&s_bound, 0x10));
			}
		} else {
			xOverlap = *reinterpret_cast<float*>(Ptr(&s_bound, 0x4)) <= *reinterpret_cast<float*>(Ptr(node, 0x10));
		}
		if (xOverlap) {
			xyOverlap = true;
		}
	}

	if (xyOverlap) {
		float boundMinZ = *reinterpret_cast<float*>(Ptr(node, 0x8));
		if (*reinterpret_cast<float*>(Ptr(&s_bound, 0x8)) <= boundMinZ) {
			if (boundMinZ <= *reinterpret_cast<float*>(Ptr(&s_bound, 0x8))) {
				xyOverlap = true;
			} else {
				xyOverlap = boundMinZ <= *reinterpret_cast<float*>(Ptr(&s_bound, 0x14));
			}
		} else {
			xyOverlap = *reinterpret_cast<float*>(Ptr(&s_bound, 0x8)) <= *reinterpret_cast<float*>(Ptr(node, 0x14));
		}
		if (xyOverlap) {
			overlap = true;
		}
	}

	if (!overlap) {
		return;
	}

	if (*reinterpret_cast<unsigned short*>(Ptr(node, 0x3E)) != 0) {
		unsigned long byteOffset = (s_insertShadowBitIndex >> 3) & 0x1ffffffc;
		unsigned long* bits = reinterpret_cast<unsigned long*>(Ptr(node, 0x48 + byteOffset));
		*bits |= 1UL << (s_insertShadowBitIndex & 0x1f);
	}

	for (int i = 0; i < 8; i++) {
		COctNode* child = *reinterpret_cast<COctNode**>(Ptr(node, 0x1C));
		if (child == 0) {
			return;
		}

		float childBoundMinX = *reinterpret_cast<float*>(Ptr(child, 0x0));
		bool childXOverlap = false;
		bool childXYOverlap = false;
		bool childOverlap = false;
		if (*reinterpret_cast<float*>(Ptr(&s_bound, 0x0)) <= childBoundMinX) {
			if (childBoundMinX <= *reinterpret_cast<float*>(Ptr(&s_bound, 0x0))) {
				childXOverlap = true;
			} else {
				childXOverlap = childBoundMinX <= *reinterpret_cast<float*>(Ptr(&s_bound, 0xC));
			}
		} else {
			childXOverlap = *reinterpret_cast<float*>(Ptr(&s_bound, 0x0)) <= *reinterpret_cast<float*>(Ptr(child, 0xC));
		}

		if (childXOverlap) {
			float childBoundMinY = *reinterpret_cast<float*>(Ptr(child, 0x4));
			if (*reinterpret_cast<float*>(Ptr(&s_bound, 0x4)) <= childBoundMinY) {
				if (childBoundMinY <= *reinterpret_cast<float*>(Ptr(&s_bound, 0x4))) {
					childXOverlap = true;
				} else {
					childXOverlap = childBoundMinY <= *reinterpret_cast<float*>(Ptr(&s_bound, 0x10));
				}
			} else {
				childXOverlap = *reinterpret_cast<float*>(Ptr(&s_bound, 0x4)) <= *reinterpret_cast<float*>(Ptr(child, 0x10));
			}
			if (childXOverlap) {
				childXYOverlap = true;
			}
		}

		if (childXYOverlap) {
			float childBoundMinZ = *reinterpret_cast<float*>(Ptr(child, 0x8));
			if (*reinterpret_cast<float*>(Ptr(&s_bound, 0x8)) <= childBoundMinZ) {
				if (childBoundMinZ <= *reinterpret_cast<float*>(Ptr(&s_bound, 0x8))) {
					childXYOverlap = true;
				} else {
					childXYOverlap = childBoundMinZ <= *reinterpret_cast<float*>(Ptr(&s_bound, 0x14));
				}
			} else {
				childXYOverlap = *reinterpret_cast<float*>(Ptr(&s_bound, 0x8)) <= *reinterpret_cast<float*>(Ptr(child, 0x14));
			}
			if (childXYOverlap) {
				childOverlap = true;
			}
		}

		if (childOverlap) {
			if (*reinterpret_cast<unsigned short*>(Ptr(child, 0x3E)) != 0) {
				unsigned long byteOffset = (s_insertShadowBitIndex >> 3) & 0x1ffffffc;
				unsigned long* bits = reinterpret_cast<unsigned long*>(Ptr(child, 0x48 + byteOffset));
				*bits |= 1UL << (s_insertShadowBitIndex & 0x1f);
			}

			for (int j = 0; j < 8; j++) {
				COctNode* grandChild = *reinterpret_cast<COctNode**>(Ptr(child, 0x1C));
				if (grandChild == 0) {
					break;
				}

				if ((s_bound.CheckCross(*reinterpret_cast<CBound*>(grandChild))) != 0) {
					if (*reinterpret_cast<unsigned short*>(Ptr(grandChild, 0x3E)) != 0) {
						setbit32(reinterpret_cast<unsigned long*>(Ptr(grandChild, 0x48)), s_insertShadowBitIndex);
					}

					for (int k = 0; k < 8; k++) {
						COctNode* greatGrandChild = *reinterpret_cast<COctNode**>(Ptr(grandChild, 0x1C));
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
	unsigned char* thisBytes = reinterpret_cast<unsigned char*>(this);
	unsigned char* mapObj = *reinterpret_cast<unsigned char**>(Ptr(this, 8));
	Mtx inverseMtx;
	Vec localPosition;

	if ((*thisBytes != 0) || ((*reinterpret_cast<unsigned long*>(mapObj + 0x38) & mask) == 0)) {
		return;
	}

	s_insertShadowBitIndex = bitIndex;
	PSMTXInverse(reinterpret_cast<MtxPtr>(mapObj + 0xB8), inverseMtx);
	PSMTXMultVec(inverseMtx, &position, &localPosition);

	float* bound = reinterpret_cast<float*>(&s_bound);
	bound[0] = localPosition.x - radius;
	bound[3] = localPosition.x + radius;
	bound[1] = localPosition.y - radius;
	bound[2] = localPosition.z - radius;
	bound[4] = localPosition.y + radius;
	bound[5] = localPosition.z + radius;

	InsertLight_r(*reinterpret_cast<COctNode**>(Ptr(this, 4)));
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

	if (*(unsigned short*)(nodeBytes + 0x3e) != 0) {
		*(void**)(nodeBytes + 0x44) = 0;
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
	ClearShadow_r(*(COctNode**)((unsigned char*)this + 0x4));
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
	bool overlap = false;

	if (s_bound.CheckCross(*(CBound*)node) != 0) {
		overlap = true;
	}

	if (overlap != false) {
		if ((s_insertShadowDepth > 2) && (*(unsigned short*)((unsigned char*)node + 0x3e) != 0)) {
			unsigned long byteOffset = (s_insertShadowBitIndex >> 3) & 0x1ffffffc;
			unsigned long* bits = (unsigned long*)((unsigned char*)node + 0x48 + byteOffset);
			*bits |= 1UL << (s_insertShadowBitIndex & 0x1f);
		}

		COctNode** children = (COctNode**)((unsigned char*)node + 0x1c);
		for (int i = 0; i < 8; i++) {
			COctNode* child = children[i];
			if (child == 0) {
				return;
			}

			s_insertShadowDepth++;

			overlap = false;

			if (s_bound.CheckCross(*(CBound*)child) != 0) {
				overlap = true;
			}

			if (overlap != false) {
				if ((s_insertShadowDepth > 2) && (*(unsigned short*)((unsigned char*)child + 0x3e) != 0)) {
					unsigned long byteOffset = (s_insertShadowBitIndex >> 3) & 0x1ffffffc;
					unsigned long* bits = (unsigned long*)((unsigned char*)child + 0x48 + byteOffset);
					*bits |= 1UL << (s_insertShadowBitIndex & 0x1f);
				}

				COctNode** childChildren = (COctNode**)((unsigned char*)child + 0x1c);
				for (int j = 0; j < 8; j++) {
					COctNode* child2 = childChildren[j];
					if (child2 == 0) {
						break;
					}

					s_insertShadowDepth++;

					if (s_bound.CheckCross(*(CBound*)child2) != 0) {
						if ((s_insertShadowDepth > 2) &&
							(*(unsigned short*)((unsigned char*)child2 + 0x3e) != 0)) {
							setbit32((unsigned long*)((unsigned char*)child2 + 0x48), s_insertShadowBitIndex);
						}

						COctNode** child2Children = (COctNode**)((unsigned char*)child2 + 0x1c);
						for (int k = 0; k < 8; k++) {
							COctNode* child3 = child2Children[k];
							if (child3 == 0) {
								break;
							}

							s_insertShadowDepth++;
							InsertShadow_r(child3);
							s_insertShadowDepth--;
						}
					}

					s_insertShadowDepth--;
				}
			}

			s_insertShadowDepth--;
		}
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
	Mtx inverseMtx;
	Vec localPosition;
	unsigned char* thisBytes = (unsigned char*)this;
	float* srcBound = (float*)&bound;
	float* dstBound = (float*)&s_bound;

	if (*thisBytes != 0) {
		return;
	}

	s_insertShadowBitIndex = bitIndex;
	PSMTXInverse((MtxPtr)(*(unsigned char**)(thisBytes + 0x8) + 0xb8), inverseMtx);
	PSMTXMultVec(inverseMtx, &position, &localPosition);

	dstBound[0] = srcBound[0];
	dstBound[1] = srcBound[1];
	dstBound[2] = srcBound[2];
	dstBound[3] = srcBound[3];
	dstBound[4] = srcBound[4];
	dstBound[5] = srcBound[5];

	PSVECAdd((Vec*)&s_bound, &localPosition, (Vec*)&s_bound);
	PSVECAdd((Vec*)((unsigned char*)&s_bound + 0xc), &localPosition, (Vec*)((unsigned char*)&s_bound + 0xc));

	s_insertShadowDepth = 0;
	InsertShadow_r(*(COctNode**)(thisBytes + 0x4));
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

	if (*reinterpret_cast<unsigned short*>(Ptr(node, 0x3E)) != 0) {
		*reinterpret_cast<unsigned long*>(Ptr(node, 0x40)) &= s_clearFlagMask;
	}

	for (int i = 0; i < 8; i++) {
		child1 = *reinterpret_cast<COctNode**>(Ptr(node, 0x1C));
		if (child1 == 0) {
			return;
		}
		if (*reinterpret_cast<unsigned short*>(Ptr(child1, 0x3E)) != 0) {
			*reinterpret_cast<unsigned long*>(Ptr(child1, 0x40)) &= s_clearFlagMask;
		}

		for (int j = 0; j < 8; j++) {
			child2 = *reinterpret_cast<COctNode**>(Ptr(child1, 0x1C));
			if (child2 == 0) {
				break;
			}
			if (*reinterpret_cast<unsigned short*>(Ptr(child2, 0x3E)) != 0) {
				*reinterpret_cast<unsigned long*>(Ptr(child2, 0x40)) &= s_clearFlagMask;
			}

			for (int k = 0; k < 8; k++) {
				child3 = *reinterpret_cast<COctNode**>(Ptr(child2, 0x1C));
				if (child3 == 0) {
					break;
				}
				if (*reinterpret_cast<unsigned short*>(Ptr(child3, 0x3E)) != 0) {
					*reinterpret_cast<unsigned long*>(Ptr(child3, 0x40)) &= s_clearFlagMask;
				}

				for (int m = 0; m < 8; m++) {
					child4 = *reinterpret_cast<COctNode**>(Ptr(child3, 0x1C));
					if (child4 == 0) {
						break;
					}
					if (*reinterpret_cast<unsigned short*>(Ptr(child4, 0x3E)) != 0) {
						*reinterpret_cast<unsigned long*>(Ptr(child4, 0x40)) &= s_clearFlagMask;
					}

					for (int n = 0; n < 8; n++) {
						child5 = *reinterpret_cast<COctNode**>(Ptr(child4, 0x1C));
						if (child5 == 0) {
							break;
						}
						if (*reinterpret_cast<unsigned short*>(Ptr(child5, 0x3E)) != 0) {
							*reinterpret_cast<unsigned long*>(Ptr(child5, 0x40)) &= s_clearFlagMask;
						}

						for (int o = 0; o < 8; o++) {
							child6 = *reinterpret_cast<COctNode**>(Ptr(child5, 0x1C));
							if (child6 == 0) {
								break;
							}
							if (*reinterpret_cast<unsigned short*>(Ptr(child6, 0x3E)) != 0) {
								*reinterpret_cast<unsigned long*>(Ptr(child6, 0x40)) &= s_clearFlagMask;
							}

							for (int p = 0; p < 8; p++) {
								child7 = *reinterpret_cast<COctNode**>(Ptr(child6, 0x1C));
								if (child7 == 0) {
									break;
								}
								if (*reinterpret_cast<unsigned short*>(Ptr(child7, 0x3E)) != 0) {
									*reinterpret_cast<unsigned long*>(Ptr(child7, 0x40)) &= s_clearFlagMask;
								}

								for (int q = 0; q < 8; q++) {
									child8 = *reinterpret_cast<COctNode**>(Ptr(child7, 0x1C));
									if (child8 == 0) {
										break;
									}
									if (*reinterpret_cast<unsigned short*>(Ptr(child8, 0x3E)) != 0) {
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
	ClearFlag_r(*(COctNode**)((unsigned char*)this + 0x4));
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
	float* bounds = (float*)node;
	CMapHit* mapHit;
	unsigned short meshStart;
	unsigned short meshEnd;

	if ((s_cyl.m_top.z > bounds[3]) || (bounds[0] > s_cyl.m_direction2.z)) {
		return 0;
	}
	if ((s_cyl.m_direction2.x > bounds[4]) || (bounds[1] > s_cyl.m_radius2)) {
		return 0;
	}
	if ((s_cyl.m_direction2.y > bounds[5]) || (bounds[2] > s_cyl.m_height2)) {
		return 0;
	}

	if (*(void**)((unsigned char*)this + 0x8) == 0) {
		return 0;
	}

	mapHit = *(CMapHit**)(*(unsigned char**)((unsigned char*)this + 0x8) + 0xc);
	if (mapHit == 0) {
		return 0;
	}

	meshStart = *(unsigned short*)((unsigned char*)node + 0x3c);
	meshEnd = *(unsigned short*)((unsigned char*)node + 0x3e);
	if ((meshEnd != 0) &&
		(mapHit->CheckHitCylinder(&s_cyl, &s_mvec, meshStart, meshEnd, s_checkHitCylinderMask) != 0)) {
		return 1;
	}

	COctNode** children = (COctNode**)((unsigned char*)node + 0x1c);
	for (int i = 0; i < 8; i++) {
		COctNode* child = children[i];
		if (child == 0) {
			return 0;
		}
		if (CheckHitCylinder_r(child) != 0) {
			return 1;
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
	float minValue;
	float maxValue;
	float margin;
	Mtx inverseMtx;
	unsigned char* thisBytes = (unsigned char*)this;
	unsigned char* mapData = *(unsigned char**)(thisBytes + 0x8);

	if ((*thisBytes != 2) || (mapData == 0) || (*(CMapHit**)(mapData + 0xc) == 0)) {
		return 0;
	}

	PSMTXInverse((MtxPtr)(mapData + 0xb8), inverseMtx);
	PSMTXMultVec(inverseMtx, &cylinder->m_bottom, &s_cyl.m_bottom);
	PSMTXMultVec(inverseMtx, &cylinder->m_direction, &s_cyl.m_direction);
	PSMTXMultVecSR(inverseMtx, (Vec*)&cylinder->m_radius, (Vec*)&s_cyl.m_radius);
	PSMTXMultVecSR(inverseMtx, move, &s_mvec);

	s_cyl.m_top.y = cylinder->m_top.y;
	margin = s_cyl.m_top.y;

	minValue = s_cyl.m_direction.x;
	maxValue = s_cyl.m_bottom.x;
	if (maxValue < minValue) {
		minValue = s_cyl.m_bottom.x;
		maxValue = s_cyl.m_direction.x;
	}
	s_cyl.m_direction2.z = maxValue + margin;
	s_cyl.m_top.z = minValue - margin;

	minValue = s_cyl.m_direction.y;
	maxValue = s_cyl.m_bottom.y;
	if (maxValue < minValue) {
		minValue = s_cyl.m_bottom.y;
		maxValue = s_cyl.m_direction.y;
	}
	s_cyl.m_radius2 = maxValue + margin;
	s_cyl.m_direction2.x = minValue - margin;

	minValue = s_cyl.m_direction.z;
	maxValue = s_cyl.m_bottom.z;
	if (maxValue < minValue) {
		minValue = s_cyl.m_bottom.z;
		maxValue = s_cyl.m_direction.z;
	}
	s_cyl.m_height2 = maxValue + margin;
	s_cyl.m_direction2.y = minValue - margin;

	s_checkHitCylinderMask = flag;

	return CheckHitCylinder_r(*(COctNode**)(thisBytes + 0x4));
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
int COctTree::CheckHitCylinderNear_r(COctNode* octNode)
{
	bool hit = false;
	bool axisYOk = false;
	bool axisXOk = false;
	float minValue;

	minValue = *reinterpret_cast<float*>(Ptr(octNode, 0x0));
	if (s_cyl.m_top.z <= minValue) {
		if (minValue <= s_cyl.m_top.z) {
			axisXOk = true;
		} else {
			axisXOk = minValue <= s_cyl.m_direction2.z;
		}
	} else {
		axisXOk = s_cyl.m_top.z <= *reinterpret_cast<float*>(Ptr(octNode, 0xC));
	}

	if (axisXOk) {
		minValue = *reinterpret_cast<float*>(Ptr(octNode, 0x4));
		if (s_cyl.m_direction2.x <= minValue) {
			if (minValue <= s_cyl.m_direction2.x) {
				axisXOk = true;
			} else {
				axisXOk = minValue <= s_cyl.m_radius2;
			}
		} else {
			axisXOk = s_cyl.m_direction2.x <= *reinterpret_cast<float*>(Ptr(octNode, 0x10));
		}
		if (axisXOk) {
			axisYOk = true;
		}
	}

	if (axisYOk) {
		minValue = *reinterpret_cast<float*>(Ptr(octNode, 0x8));
		if (s_cyl.m_direction2.y <= minValue) {
			if (minValue <= s_cyl.m_direction2.y) {
				axisYOk = true;
			} else {
				axisYOk = minValue <= s_cyl.m_height2;
			}
		} else {
			axisYOk = s_cyl.m_direction2.y <= *reinterpret_cast<float*>(Ptr(octNode, 0x14));
		}
		if (axisYOk) {
			hit = true;
		}
	}

	if (!hit) {
		return 0;
	}

	if (*reinterpret_cast<unsigned short*>(Ptr(octNode, 0x3E)) != 0) {
		(*reinterpret_cast<CMapHit**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 8)), 0xC)))
		    ->CheckHitCylinderNear(&s_cyl, &s_mvec,
		                           *reinterpret_cast<unsigned short*>(Ptr(octNode, 0x3C)),
		                           *reinterpret_cast<unsigned short*>(Ptr(octNode, 0x3E)),
		                           s_checkHitCylinderMask);
	}

	for (int i = 0; i < 8; i++) {
		COctNode* child = *reinterpret_cast<COctNode**>(Ptr(octNode, 0x1C + (i * 4)));
		if (child == 0) {
			return 0;
		}

		hit = false;
		axisYOk = false;
		minValue = *reinterpret_cast<float*>(Ptr(child, 0x0));
		if (s_cyl.m_top.z <= minValue) {
			if (minValue <= s_cyl.m_top.z) {
				axisXOk = true;
			} else {
				axisXOk = minValue <= s_cyl.m_direction2.z;
			}
		} else {
			axisXOk = s_cyl.m_top.z <= *reinterpret_cast<float*>(Ptr(child, 0xC));
		}

		if (axisXOk) {
			minValue = *reinterpret_cast<float*>(Ptr(child, 0x4));
			if (s_cyl.m_direction2.x <= minValue) {
				if (minValue <= s_cyl.m_direction2.x) {
					axisXOk = true;
				} else {
					axisXOk = minValue <= s_cyl.m_radius2;
				}
			} else {
				axisXOk = s_cyl.m_direction2.x <= *reinterpret_cast<float*>(Ptr(child, 0x10));
			}
			if (axisXOk) {
				axisYOk = true;
			}
		}

		if (axisYOk) {
			minValue = *reinterpret_cast<float*>(Ptr(child, 0x8));
			if (s_cyl.m_direction2.y <= minValue) {
				if (minValue <= s_cyl.m_direction2.y) {
					axisYOk = true;
				} else {
					axisYOk = minValue <= s_cyl.m_height2;
				}
			} else {
				axisYOk = s_cyl.m_direction2.y <= *reinterpret_cast<float*>(Ptr(child, 0x14));
			}
			if (axisYOk) {
				hit = true;
			}
		}

		if (!hit) {
			continue;
		}

		if (*reinterpret_cast<unsigned short*>(Ptr(child, 0x3E)) != 0) {
			(*reinterpret_cast<CMapHit**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 8)), 0xC)))
			    ->CheckHitCylinderNear(&s_cyl, &s_mvec,
			                           *reinterpret_cast<unsigned short*>(Ptr(child, 0x3C)),
			                           *reinterpret_cast<unsigned short*>(Ptr(child, 0x3E)),
			                           s_checkHitCylinderMask);
		}

		for (int j = 0; j < 8; j++) {
			COctNode* grandChild = *reinterpret_cast<COctNode**>(Ptr(child, 0x1C + (j * 4)));
			if (grandChild == 0) {
				break;
			}

			if (reinterpret_cast<CBound*>(grandChild)->CheckCross(s_bound) != 0) {
				if (*reinterpret_cast<unsigned short*>(Ptr(grandChild, 0x3E)) != 0) {
					(*reinterpret_cast<CMapHit**>(Ptr(*reinterpret_cast<void**>(Ptr(this, 8)), 0xC)))
					    ->CheckHitCylinderNear(&s_cyl, &s_mvec,
					                           *reinterpret_cast<unsigned short*>(Ptr(grandChild, 0x3C)),
					                           *reinterpret_cast<unsigned short*>(Ptr(grandChild, 0x3E)),
					                           s_checkHitCylinderMask);
				}

				for (int k = 0; k < 8; k++) {
					COctNode* greatGrandChild =
					    *reinterpret_cast<COctNode**>(Ptr(grandChild, 0x1C + (k * 4)));
					if (greatGrandChild == 0) {
						break;
					}
					CheckHitCylinderNear_r(greatGrandChild);
				}
			}
		}
	}

	return 0;
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
int COctTree::CheckHitCylinderNear(CMapCylinder* cylinder, Vec* move, unsigned long flag)
{
	float minValue;
	float maxValue;
	float margin;
	Mtx inverseMtx;
	unsigned char* thisBytes = (unsigned char*)this;
	unsigned char* mapData = *(unsigned char**)(thisBytes + 0x8);

	if ((*thisBytes != 2) || (mapData == 0) || (*(CMapHit**)(mapData + 0xc) == 0)) {
		return 0;
	}

	PSMTXInverse((MtxPtr)(mapData + 0xb8), inverseMtx);
	PSMTXMultVec(inverseMtx, &cylinder->m_bottom, &s_cyl.m_bottom);
	PSMTXMultVec(inverseMtx, &cylinder->m_direction, &s_cyl.m_direction);
	PSMTXMultVecSR(inverseMtx, (Vec*)&cylinder->m_radius, (Vec*)&s_cyl.m_radius);
	PSMTXMultVecSR(inverseMtx, move, &s_mvec);

	s_cyl.m_top.y = cylinder->m_top.y;
	margin = lbl_8032F960 + s_cyl.m_top.y;

	minValue = s_cyl.m_direction.x;
	maxValue = s_cyl.m_bottom.x;
	if (maxValue < minValue) {
		minValue = s_cyl.m_bottom.x;
		maxValue = s_cyl.m_direction.x;
	}
	s_cyl.m_direction2.z = maxValue + margin;
	s_cyl.m_top.z = minValue - margin;

	minValue = s_cyl.m_direction.y;
	maxValue = s_cyl.m_bottom.y;
	if (maxValue < minValue) {
		minValue = s_cyl.m_bottom.y;
		maxValue = s_cyl.m_direction.y;
	}
	s_cyl.m_radius2 = maxValue + margin;
	s_cyl.m_direction2.x = minValue - margin;

	minValue = s_cyl.m_direction.z;
	maxValue = s_cyl.m_bottom.z;
	if (maxValue < minValue) {
		minValue = s_cyl.m_bottom.z;
		maxValue = s_cyl.m_direction.z;
	}
	s_cyl.m_height2 = maxValue + margin;
	s_cyl.m_direction2.y = minValue - margin;

	s_checkHitCylinderMask = flag;
	CheckHitCylinderNear_r(*(COctNode**)(thisBytes + 0x4));
	return 0;
}

/*
 * --INFO--
 * PAL Address: 8002ef24
 * PAL Size: 36b
 */
void CMaterialMan::LockEnv()
{
	// Copy current values to locked values
	// Based on Ghidra decomp field assignments
	*((unsigned int*)this + 0x128/4) = *((unsigned int*)this + 0x11c/4);
	*((unsigned int*)this + 300/4) = *((unsigned int*)this + 0x120/4);
	*((unsigned int*)this + 0x130/4) = *((unsigned int*)this + 0x124/4);
	*((unsigned int*)this + 0x40/4) = *((unsigned int*)this + 0x48/4);
}

/*
 * --INFO--
 * PAL Address: 8002ef48
 * PAL Size: 84b
 */
void CMaterialMan::InitEnv()
{
	// Initialize environment settings
	// Based on Ghidra decomp initialization values
	*((unsigned int*)this + 0x48/4) = 0xace0f;
	*((unsigned int*)this + 0x44/4) = 0xffffffff;
	*((unsigned char*)this + 0x4c) = 0xff;
	*((unsigned int*)this + 0x128/4) = 0;
	*((unsigned int*)this + 0x11c/4) = 0;
	*((unsigned int*)this + 300/4) = 0x1e;
	*((unsigned int*)this + 0x120/4) = 0x1e;
	*((unsigned int*)this + 0x130/4) = 0;
	*((unsigned int*)this + 0x124/4) = 0;
	*((unsigned char*)this + 0x205) = 0xff;
	*((unsigned char*)this + 0x206) = 0xff;
	*((unsigned int*)this + 0x58/4) = 0;
	*((unsigned int*)this + 0x5c/4) = 0;
	*((unsigned char*)this + 0x208) = 0;
}

/*
 * --INFO--
 * PAL Address: 8002cc28
 * PAL Size: 272b
 */
int CBound::CheckCross(CBound& other)
{
	float* a = (float*)this;
	float* b = (float*)&other;

	if ((b[0] > a[3]) || (a[0] > b[3])) {
		return 0;
	}
	if ((b[1] > a[4]) || (a[1] > b[4])) {
		return 0;
	}
	if ((b[2] > a[5]) || (a[2] > b[5])) {
		return 0;
	}
	return 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
COctNode::COctNode()
{
	float min = lbl_8032F96C;
	float max = lbl_8032F970;
	float* bounds = (float*)this;

	bounds[2] = min;
	bounds[1] = min;
	bounds[0] = min;
	bounds[5] = max;
	bounds[4] = max;
	bounds[3] = max;
	*(void**)((unsigned char*)this + 0x44) = 0;
	*(void**)((unsigned char*)this + 0x48) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8002f410
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_mapocttree_cpp()
{
	float max = lbl_8032F970;
	float min = lbl_8032F96C;
	float* bounds = (float*)&s_bound;

	bounds[0] = min;
	bounds[1] = min;
	bounds[2] = min;
	bounds[3] = max;
	bounds[4] = max;
	bounds[5] = max;

	s_cyl.m_direction2.y = min;
	s_cyl.m_direction2.x = min;
	s_cyl.m_top.z = min;
	s_cyl.m_height2 = max;
	s_cyl.m_radius2 = max;
	s_cyl.m_direction2.z = max;
}

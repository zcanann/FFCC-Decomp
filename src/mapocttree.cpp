#include "ffcc/mapocttree.h"
#include "ffcc/maphit.h"
#include "ffcc/materialman.h"

extern float lbl_8032F96C;
extern float lbl_8032F970;
static unsigned long s_clearFlagMask;
static CBound s_bound;
static CMapCylinder s_cyl;

extern "C" void __dl__FPv(void*);
extern "C" void __dla__FPv(void*);

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
 * Address:	TODO
 * Size:	TODO
 */
void COctTree::ReadOtmOctTree(CChunkFile&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void COctTree::DrawTypeMeshFlag_r(COctNode*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void COctTree::DrawCharaShadowTypeMeshFlag_r(COctNode*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void COctTree::DrawTypeMeshFrustumIn_r(COctNode*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void COctTree::DrawTypeMesh_r(COctNode*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void COctTree::Draw(unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void COctTree::DrawCharaShadow(unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void COctTree::SetDrawFlag()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void ClearLight_r(COctNode*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void InsertLight_r(COctNode*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void COctTree::InsertLight(long, Vec&, float, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void ClearShadow_r(COctNode*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void InsertShadow_r(COctNode*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void COctTree::InsertShadow(long, Vec&, CBound&)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void ClearFlag_r(COctNode*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
int COctTree::CheckHitCylinder_r(COctNode*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int COctTree::CheckHitCylinder(CMapCylinder*, Vec*, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int COctTree::CheckHitCylinderNear_r(COctNode*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int COctTree::CheckHitCylinderNear(CMapCylinder*, Vec*, unsigned long)
{
	// TODO
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

	*(float*)((unsigned char*)this + 0x0) = min;
	*(float*)((unsigned char*)this + 0x4) = min;
	*(float*)((unsigned char*)this + 0x8) = min;
	*(float*)((unsigned char*)this + 0xC) = max;
	*(float*)((unsigned char*)this + 0x10) = max;
	*(float*)((unsigned char*)this + 0x14) = max;
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

#include "ffcc/mapocttree.h"
#include "ffcc/materialman.h"

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
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
COctTree::~COctTree()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void COctTree::ClearLight()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void COctTree::ClearShadow()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void COctTree::ClearFlag(unsigned long)
{
	// TODO
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
	float* thisBound = (float*)this;
	float* otherBound = (float*)&other;
	int cross;

	if (otherBound[0] <= thisBound[0]) {
		cross = 0;
		if (thisBound[0] <= otherBound[0]) {
			cross = 1;
		} else if (thisBound[0] <= otherBound[3]) {
			cross = 1;
		}
	} else {
		cross = otherBound[0] <= thisBound[3];
	}
	if (!cross) {
		return 0;
	}

	if (otherBound[1] <= thisBound[1]) {
		cross = 0;
		if (thisBound[1] <= otherBound[1]) {
			cross = 1;
		} else if (thisBound[1] <= otherBound[4]) {
			cross = 1;
		}
	} else {
		cross = otherBound[1] <= thisBound[4];
	}
	if (!cross) {
		return 0;
	}

	if (otherBound[2] <= thisBound[2]) {
		cross = 0;
		if (thisBound[2] <= otherBound[2]) {
			cross = 1;
		} else if (thisBound[2] <= otherBound[5]) {
			cross = 1;
		}
	} else {
		cross = otherBound[2] <= thisBound[5];
	}

	return cross;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
COctNode::COctNode()
{
	// TODO
}

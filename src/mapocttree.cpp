#include "ffcc/mapocttree.h"
#include "ffcc/materialman.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void setbit32(unsigned long*, unsigned long)
{
	// TODO
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
	float thisMin, thisMax, otherMin, otherMax;
	bool crossX, crossY, crossZ;
	
	// Cast to float arrays for easy access
	float* thisBound = (float*)this;
	float* otherBound = (float*)&other;
	
	// Check X axis overlap
	thisMin = thisBound[0];
	otherMin = otherBound[0];
	thisMax = thisBound[3];
	otherMax = otherBound[3];
	
	if (otherMin <= thisMin) {
		crossX = (thisMin <= otherMin) || (thisMin <= otherMax);
	} else {
		crossX = (otherMin <= thisMax);
	}
	
	if (!crossX) return 0;
	
	// Check Y axis overlap
	thisMin = thisBound[1];
	otherMin = otherBound[1];  
	thisMax = thisBound[4];
	otherMax = otherBound[4];
	
	if (otherMin <= thisMin) {
		crossY = (thisMin <= otherMin) || (thisMin <= otherMax);
	} else {
		crossY = (otherMin <= thisMax);
	}
	
	if (!crossY) return 0;
	
	// Check Z axis overlap
	thisMin = thisBound[2];
	otherMin = otherBound[2];
	thisMax = thisBound[5];
	otherMax = otherBound[5];
	
	if (otherMin <= thisMin) {
		crossZ = (thisMin <= otherMin) || (thisMin <= otherMax);
	} else {
		crossZ = (otherMin <= thisMax);
	}
	
	return crossZ ? 1 : 0;
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

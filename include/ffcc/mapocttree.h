#ifndef _FFCC_MAPOCTTREE_H_
#define _FFCC_MAPOCTTREE_H_

#include <Dolphin/types.h>

class CChunkFile;
class CMapCylinder;
class COctNode;
class CBound;
struct Vec;

void ClearLight_r(COctNode*);
void InsertLight_r(COctNode*);
void ClearShadow_r(COctNode*);
void InsertShadow_r(COctNode*);
void ClearFlag_r(COctNode*);
void setbit32(unsigned long*, unsigned long);

class COctNode
{
public:
	COctNode();

private:
	float m_boundMinX;      // 0x00
	float m_boundMinY;      // 0x04
	float m_boundMinZ;      // 0x08
	float m_boundMaxX;      // 0x0C
	float m_boundMaxY;      // 0x10
	float m_boundMaxZ;      // 0x14
	u8 m_pad18[0x2C];       // 0x18
	void* m_unk44;          // 0x44
	void* m_unk48;          // 0x48
};

class CBound
{
public:
	CBound();
	void operator=(const CBound&);
	void SetMinMax(Vec*, Vec*);
	int CheckCross(CBound&);
};

class COctTree
{
public:
	COctTree();
	~COctTree();
	void ReadOtmOctTree(CChunkFile&);
	void DrawTypeMeshFlag_r(COctNode*);
	void DrawCharaShadowTypeMeshFlag_r(COctNode*);
	void DrawTypeMeshFrustumIn_r(COctNode*);
	void DrawTypeMesh_r(COctNode*);
	void Draw(unsigned char);
	void DrawCharaShadow(unsigned char);
	void SetDrawFlag();
	void GetLocalPosition(Vec&, Vec&);
	void ClearLight();
	void InsertLight(long, Vec&, float, unsigned long);
	void ClearShadow();
	void InsertShadow(long, Vec&, CBound&);
	void ClearFlag(unsigned long);
	int CheckHitCylinder_r(COctNode*);
	int CheckHitCylinder(CMapCylinder*, Vec*, unsigned long);
	void CheckHitCylinderNear_r(COctNode*);
	void CheckHitCylinderNear(CMapCylinder*, Vec*, unsigned long);
	void SetOctTreeMapObj(int);

private:
	u8 m_type;              // 0x00
	u8 m_unk01;             // 0x01
	u16 m_nodeCount;        // 0x02
	COctNode* m_nodePool;   // 0x04
	void* m_mapObject;      // 0x08
	u8 m_pad0C[0x30];       // 0x0C
	float m_localPosX;      // 0x3C
	float m_localPosY;      // 0x40
	float m_localPosZ;      // 0x44
	u32 m_drawFlags;        // 0x48
};

#endif // _FFCC_MAPOCTTREE_H_

#ifndef _FFCC_MAPOCTTREE_H_
#define _FFCC_MAPOCTTREE_H_

#include <Dolphin/mtx.h>
#include <Dolphin/types.h>

class CChunkFile;
class CMapCylinder;
class CMapObj;
class COctNode;
class CBound;

void ClearLight_r(COctNode*);
void InsertLight_r(COctNode*);
void ClearShadow_r(COctNode*);
void SetShadow_r(COctNode*);
void InsertShadow_r(COctNode*);
void ClearFlag_r(COctNode*);
void setbit32(unsigned long*, unsigned long);

class COctNode
{
public:
	COctNode();

	float m_boundMinX;      // 0x00
	float m_boundMinY;      // 0x04
	float m_boundMinZ;      // 0x08
	float m_boundMaxX;      // 0x0C
	float m_boundMaxY;      // 0x10
	float m_boundMaxZ;      // 0x14
	u32 m_unk18;            // 0x18
	COctNode* m_children[8]; // 0x1C
	u16 m_meshCount;        // 0x3C
	u16 m_meshStart;        // 0x3E
	u32 m_drawFlags;        // 0x40
	u32 m_lightFlags;       // 0x44
	u32 m_shadowFlags;      // 0x48
};

class CBound
{
public:
	CBound();
	void operator=(const CBound& other)
	{
		m_min = other.m_min;
		m_max = other.m_max;
	}
	static void SetFrustum(Vec&, float(*)[4]);
	int CheckFrustum0(CBound&);
	int CheckFrustum0(float);
	int CheckFrustum(Vec&, float(*)[4], float);
	void SetMinMax(Vec*, Vec*);
	int CheckCross(CBound&);

	Vec m_min;              // 0x00
	Vec m_max;              // 0x0C
};

class COctTree
{
public:
	COctTree();
	~COctTree();
	int ReadOtmOctTree(CChunkFile&);
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
	void SetShadow(long);
	void InsertShadow(long, Vec&, CBound&);
	void ClearFlag(unsigned long);
	int CheckHitCylinder_r(COctNode*);
	int CheckHitCylinder(CMapCylinder*, Vec*, unsigned long);
	void CheckHitCylinderNear_r(COctNode*);
	void CheckHitCylinderNear(CMapCylinder*, Vec*, unsigned long);
	void SetOctTreeMapObj(int);
	COctNode* GetRootNode() { return m_nodePool; }
	CMapObj* GetMapObject() { return m_mapObject; }
	void SetMapObject(CMapObj* mapObject) { m_mapObject = mapObject; }

private:
	u8 m_type;              // 0x00
	u8 m_unk01;             // 0x01
	u16 m_nodeCount;        // 0x02
	COctNode* m_nodePool;   // 0x04
	CMapObj* m_mapObject;   // 0x08
	Mtx m_cullMtx;          // 0x0C
	Vec m_localPos;         // 0x3C
	u32 m_drawFlags;        // 0x48
};

#endif // _FFCC_MAPOCTTREE_H_

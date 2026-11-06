#ifndef _FFCC_MAPOCTTREE_H_
#define _FFCC_MAPOCTTREE_H_

#include <Dolphin/mtx.h>
#include <Dolphin/types.h>

class CChunkFile;
class CMapCylinder;
class CMapObj;
class COctNode;

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: 0x8001DBC4
 * EN Size: 156b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void VECMinimize(const Vec* a, const Vec* b, Vec* out)
{
	out->x = (a->x < b->x) ? a->x : b->x;
	out->y = (a->y < b->y) ? a->y : b->y;
	out->z = (a->z < b->z) ? a->z : b->z;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: 0x8001DB28
 * EN Size: 156b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void VECMaximize(const Vec* a, const Vec* b, Vec* out)
{
	out->x = (a->x > b->x) ? a->x : b->x;
	out->y = (a->y > b->y) ? a->y : b->y;
	out->z = (a->z > b->z) ? a->z : b->z;
}

class CBound
{
public:
	/*
	 * --INFO--
	 * PAL Address: 0x8002BE10
	 * PAL Size: 36b
	 * EN Address: 0x8002BC04
	 * EN Size: 36b
	 * JP Address: TODO
	 * JP Size: TODO
	 */
	CBound()
	{
		Reset();
	}
	/*
	 * --INFO--
	 * PAL Address: UNUSED
	 * PAL Size: TODO
	 * EN Address: 0x8001DC60
	 * EN Size: 36b
	 * JP Address: TODO
	 * JP Size: TODO
	 */
	void Reset()
	{
		float max = -10000000000.0f;
		float min = 10000000000.0f;

		m_min.x = m_min.y = m_min.z = min;
		m_max.x = m_max.y = m_max.z = max;
	}
	/*
	 * --INFO--
	 * PAL Address: UNUSED
	 * PAL Size: TODO
	 * EN Address: 0x8001DAD4
	 * EN Size: 84b
	 * JP Address: TODO
	 * JP Size: TODO
	 */
	void Add(Vec* point)
	{
		VECMinimize(&m_min, point, &m_min);
		VECMaximize(&m_max, point, &m_max);
	}
	/*
	 * --INFO--
	 * PAL Address: UNUSED
	 * PAL Size: TODO
	 * EN Address: TODO
	 * EN Size: TODO
	 * JP Address: TODO
	 * JP Size: TODO
	 */
	/*
	 * --INFO--
	 * PAL Address: UNUSED
	 * PAL Size: UNUSED
	 * EN Address: 0x80044378
	 * EN Size: 84b
	 * JP Address: TODO
	 * JP Size: TODO
	 */
	void Add(CBound* other)
	{
		VECMinimize(&m_min, &other->m_min, &m_min);
		VECMaximize(&m_max, &other->m_max, &m_max);
	}
	/*
	 * --INFO--
	 * PAL Address: UNUSED
	 * PAL Size: UNUSED
	 * EN Address: 0x800401C4
	 * EN Size: 76b
	 * JP Address: TODO
	 * JP Size: TODO
	 */
	void GetCenter(Vec* center)
	{
		center->x = (m_min.x + m_max.x) / 2.0f;
		center->y = (m_min.y + m_max.y) / 2.0f;
		center->z = (m_min.z + m_max.z) / 2.0f;
	}
	CBound(Vec* position, float rangeXZ, float rangeY)
	{
		m_min.x = position->x - rangeXZ;
		m_max.x = position->x + rangeXZ;
		m_min.z = position->z - rangeXZ;
		m_max.z = position->z + rangeXZ;
		m_min.y = position->y;
		m_max.y = position->y + rangeY;
	}
	static void SetFrustum(Vec&, float(*)[4]);
	int CheckFrustum0(CBound&);
	int CheckFrustum0(float);
	int CheckFrustum(Vec&, float(*)[4], float);
	void SetMinMax(Vec*, Vec*);
	/*
	 * --INFO--
	 * PAL Address: 0x8002CC28
	 * PAL Size: 272b
	 * EN Address: 0x80031B7C
	 * EN Size: 412b
	 * JP Address: TODO
	 * JP Size: TODO
	 */
	int CheckCross(CBound& other)
	{
		return (m_min.x < other.m_min.x ? other.m_min.x <= m_max.x : (m_min.x > other.m_min.x ? m_min.x <= other.m_max.x : 1)) &&
		       (m_min.y < other.m_min.y ? other.m_min.y <= m_max.y : (m_min.y > other.m_min.y ? m_min.y <= other.m_max.y : 1)) &&
		       (m_min.z < other.m_min.z ? other.m_min.z <= m_max.z : (m_min.z > other.m_min.z ? m_min.z <= other.m_max.z : 1));
	}

	Vec m_min;              // 0x00
	Vec m_max;              // 0x0C
};

class COctNode
{
public:
	COctNode()
	{
		m_lightFlags = 0;
		m_shadowFlags = 0;
	}
	CBound* GetBound() { return &m_bound; }

	CBound m_bound;         // 0x00
	u32 m_unk18;            // 0x18
	COctNode* m_children[8]; // 0x1C
	u16 m_meshCount;        // 0x3C
	u16 m_meshStart;        // 0x3E
	u32 m_drawFlags;        // 0x40
	u32 m_lightFlags;       // 0x44
	u32 m_shadowFlags;      // 0x48
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

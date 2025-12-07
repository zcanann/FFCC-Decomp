#ifndef _FFCC_MAPOCTTREE_H_
#define _FFCC_MAPOCTTREE_H_

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
};

class CBound
{
public:
	void operator=(const CBound&);
	void SetMinMax(Vec*, Vec*);
	void CheckCross(CBound&);
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
	int CheckHitCylinderNear_r(COctNode*);
	int CheckHitCylinderNear(CMapCylinder*, Vec*, unsigned long);
	void SetOctTreeMapObj(int);
};

#endif // _FFCC_MAPOCTTREE_H_

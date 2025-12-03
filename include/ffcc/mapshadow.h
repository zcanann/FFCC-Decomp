#ifndef _FFCC_MAPSHADOW_H_
#define _FFCC_MAPSHADOW_H_

class COctTree;
class CTexture;
class CMapPcs;

void CMapShadowInsertOctTree(CMapShadow::TARGET, COctTree&);

class CMapShadow
{
public:
    enum TARGET
	{
		TODO,
	}
	
    void Init();
    void Calc();
    void Draw();
};

#endif // _FFCC_MAPSHADOW_H_

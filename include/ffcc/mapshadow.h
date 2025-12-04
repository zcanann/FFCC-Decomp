#ifndef _FFCC_MAPSHADOW_H_
#define _FFCC_MAPSHADOW_H_

class CMapPcs;
class COctTree;
class CTexture;

class CMapShadow
{
public:
    enum TARGET
	{
		TODO,
	};
	
    void Init();
    void Calc();
    void Draw();
};

void CMapShadowInsertOctTree(CMapShadow::TARGET, COctTree&);

#endif // _FFCC_MAPSHADOW_H_

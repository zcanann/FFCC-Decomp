#ifndef _FFCC_MAPSHADOW_H_
#define _FFCC_MAPSHADOW_H_

#include "ffcc/mapocttree.h"
#include "ffcc/vector.h"
#include <Dolphin/types.h>
#include <dolphin/mtx.h>

class CMapPcs;
class CMapObj;
class COctTree;
class CTexture;

class CMapShadow
{
public:
    enum TARGET
	{
		TODO,
	};
	
    CMapShadow()
    {
        m_enabled = 1;
        m_materialIndex = 0;
        m_modelA = 0;
        m_modelB = 0;
        m_modelC = 0;
    }
    void Init();
    void Calc();
    void Draw();

    int m_enabled;           // 0x00
    u16 m_materialIndex;     // 0x04
    u8 m_useFrustum;         // 0x06
    u8 m_materialMode;       // 0x07
    u8 m_shadowMaterialType;  // 0x08
    u8 m_yFilterMode;        // 0x09
    u8 m_unknown0A;          // 0x0A
    u8 m_unknown0B;          // 0x0B
    CMapObj* m_modelA;       // 0x0C
    CMapObj* m_modelB;       // 0x10
    CMapObj* m_modelC;       // 0x14
    Mtx m_viewMtx;           // 0x18
    Mtx m_lightMtx;          // 0x48
    Mtx m_shadowMtx;         // 0x78
    float m_shadowScale;     // 0xA8
    float m_frustumNear;     // 0xAC
    float m_frustumFar;      // 0xB0
    float m_targetBoundsScale; // 0xB4
    float m_scrollStepX;     // 0xB8
    float m_scrollStepY;     // 0xBC
    CBound m_targetBounds[2]; // 0xC0
    u8 m_targetEnabled[2];   // 0xF0
};

typedef char CMapShadow_size_check[(sizeof(CMapShadow) == 0xF4) ? 1 : -1];

void CMapShadowInsertOctTree(CMapShadow::TARGET, COctTree&);

#endif // _FFCC_MAPSHADOW_H_

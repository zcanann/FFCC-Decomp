#ifndef _FFCC_MAPSHADOW_H_
#define _FFCC_MAPSHADOW_H_

#include "ffcc/vector.h"
#include <Dolphin/types.h>
#include <dolphin/mtx.h>

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

    u8 _pad00[4];            // 0x00
    u16 m_materialIndex;     // 0x04
    u8 m_useFrustum;         // 0x06
    u8 m_materialMode;       // 0x07
    u32 _pad08;              // 0x08
    void* m_modelA;          // 0x0C
    void* m_modelB;          // 0x10
    void* m_modelC;          // 0x14
    Mtx m_viewMtx;           // 0x18
    Mtx m_lightMtx;          // 0x48
    Mtx m_shadowMtx;         // 0x78
    float m_shadowScale;     // 0xA8
    float m_frustumNear;     // 0xAC
    u8 _padB0[8];            // 0xB0
    float m_scrollStepX;     // 0xB8
    float m_scrollStepY;     // 0xBC
    u8 m_targetBounds[0x30]; // 0xC0
    u8 m_targetEnabled[2];   // 0xF0
};

void CMapShadowInsertOctTree(CMapShadow::TARGET, COctTree&);

#endif // _FFCC_MAPSHADOW_H_

#include "ffcc/mapshadow.h"
#include "ffcc/linkage.h"
#include "ffcc/mapocttree.h"
#include "ffcc/materialman.h"
#include "ffcc/vector.h"
#include <dolphin/mtx.h>

template <class T>
class CPtrArray
{
public:
	int GetSize();
	T operator[](unsigned long index);
};

extern const double DOUBLE_8032fce8;
extern const float FLOAT_8032fcf0;

/*
 * --INFO--
 * PAL Address: 0x8004c71c
 * PAL Size: 236b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapShadowInsertOctTree(CMapShadow::TARGET mapShadow, COctTree& octTree)
{
	CPtrArray<CMapShadow*>* mapShadowArray;
	CMapShadow* shadow;
	u32 boundOffset;
	u32 i;
	u32 octTreeMask;
	Vec pos;
	CBound* bound;

	octTree.ClearShadow();
	if (*(u32*)(*(u32*)((char*)&octTree + 0x8) + 0x3c) != 0) {
		mapShadowArray = reinterpret_cast<CPtrArray<CMapShadow*>*>((char*)&MapMng + 0x21434);
		boundOffset = (u32)mapShadow * 0x18;
		for (i = 0; i < mapShadowArray->GetSize(); i++) {
			octTreeMask = *(u32*)(*(u32*)((char*)&octTree + 0x8) + 0x3c);
			if ((octTreeMask & (1U << i)) == 0) {
				continue;
			}
			shadow = (*mapShadowArray)[i];
			if ((shadow->m_targetEnabled[(int)mapShadow] == 0) || (shadow->m_materialMode != 0)) {
				continue;
			}

			pos.x = *(float*)((int)shadow->m_modelA + 0xc4);
			pos.y = *(float*)((int)shadow->m_modelA + 0xd4);
			pos.z = *(float*)((int)shadow->m_modelA + 0xe4);

			bound = reinterpret_cast<CBound*>(shadow->m_targetBounds + boundOffset);
			octTree.InsertShadow(i, pos, *bound);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8004c808
 * PAL Size: 192b
 */
void CMapShadow::Draw()
{
	int iVar1;
	Vec local_14;
	Vec local_20;
	Vec local_2c;
	Vec VStack_38;
	
	iVar1 = (int)m_modelA;
	local_14.x = *(float*)(iVar1 + 0xc4);
	local_14.y = *(float*)(iVar1 + 0xd4);
	local_14.z = *(float*)(iVar1 + 0xe4);
	iVar1 = (int)m_modelC;
	local_20.x = *(float*)(iVar1 + 0xc4);
	local_20.y = *(float*)(iVar1 + 0xd4);
	local_20.z = *(float*)(iVar1 + 0xe4);
	iVar1 = (int)m_modelB;
	local_2c.x = *(float*)(iVar1 + 0xc4);
	local_2c.y = *(float*)(iVar1 + 0xd4);
	local_2c.z = *(float*)(iVar1 + 0xe4);
	PSVECSubtract(&local_20, &local_14, &local_20);
	PSVECSubtract(&local_2c, &local_14, &VStack_38);
	C_MTXLookAt(m_viewMtx, (Point3d*)&local_14, &local_20, (Point3d*)&local_2c);
	PSMTXConcat(m_lightMtx, m_viewMtx, m_shadowMtx);
}

/*
 * --INFO--
 * PAL Address: 0x8004c8c8
 * PAL Size: 84b
 */
void CMapShadow::Calc()
{
	m_lightMtx[0][3] = m_lightMtx[0][3] + m_scrollStepX;
	if (m_lightMtx[0][3] > 1.0f) {
		m_lightMtx[0][3] = m_lightMtx[0][3] - 1.0f;
	}
	m_lightMtx[1][3] = m_lightMtx[1][3] + m_scrollStepY;
	if (m_lightMtx[1][3] > 1.0f) {
		m_lightMtx[1][3] = m_lightMtx[1][3] - 1.0f;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8004c91c
 * PAL Size: 236b
 */
void CMapShadow::Init()
{
	float width;
	float height;
	CMaterial* material;
	int materialSet;

	materialSet = *(int*)((char*)&MapMng + 0x213d4);
	material = (*reinterpret_cast<CPtrArray<CMaterial*>*>(materialSet + 8))[m_materialIndex];
	material = *reinterpret_cast<CMaterial**>(reinterpret_cast<int>(material) + 0x3c);
	width = (float)*reinterpret_cast<u32*>(reinterpret_cast<int>(material) + 0x64);
	height = (float)*reinterpret_cast<u32*>(reinterpret_cast<int>(material) + 0x68);
	m_materialMode = *reinterpret_cast<u32*>(reinterpret_cast<int>(material) + 0x6c);
	if (m_useFrustum != 0) {
		float scale = m_shadowScale;
		double scaleBias = DOUBLE_8032fce8;
		float scaleStep = FLOAT_8032fcf0;
		C_MTXLightFrustum(m_lightMtx, -height, height, -width, width, m_frustumNear,
		                  (float)(scaleBias * (double)scale), scaleStep * scale, scaleStep, scaleStep);
	} else {
		float scale = m_shadowScale;
		double scaleBias = DOUBLE_8032fce8;
		float scaleStep = FLOAT_8032fcf0;
		C_MTXLightOrtho(m_lightMtx, -height, height, -width, width,
		                (float)(scaleBias * (double)scale), scaleStep * scale, scaleStep, scaleStep);
	}
}

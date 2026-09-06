#define FFCC_PTRARRAY_NO_INLINE_ACCESSORS

#include "ffcc/mapshadow.h"
#include "ffcc/linkage.h"
#include "ffcc/map.h"
#include "ffcc/mapobj.h"
#include "ffcc/mapocttree.h"
#include "ffcc/materialman.h"
#include "ffcc/textureman.h"
#include "ffcc/vector.h"
#include <dolphin/mtx.h>

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
	CMapShadow* shadow;
	int target;
	int i;
	u32 octTreeMask;
	Vec pos;

	target = (int)mapShadow;
	octTree.ClearShadow();
	if (octTree.GetMapObject()->m_shadowTarget != 0) {
		for (i = 0; i < (u32)MapMng.m_mapShadowArray.GetSize(); i++) {
			octTreeMask = octTree.GetMapObject()->m_shadowTarget;
			if (((octTreeMask & (1U << i)) != 0) &&
			    ((shadow = MapMng.m_mapShadowArray[i])->m_targetEnabled[target] != 0) &&
			    (shadow->m_materialMode == 0)) {
				pos.x = shadow->m_modelA->m_worldMtx[0][3];
				pos.y = shadow->m_modelA->m_worldMtx[1][3];
				pos.z = shadow->m_modelA->m_worldMtx[2][3];

				octTree.InsertShadow(i, pos, shadow->m_targetBounds[target]);
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8004c808
 * PAL Size: 192b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapShadow::Draw()
{
	Vec local_14;
	Vec local_20;
	Vec local_2c;
	Vec VStack_38;
	
	local_14.x = m_modelA->m_worldMtx[0][3];
	local_14.y = m_modelA->m_worldMtx[1][3];
	local_14.z = m_modelA->m_worldMtx[2][3];
	local_20.x = m_modelC->m_worldMtx[0][3];
	local_20.y = m_modelC->m_worldMtx[1][3];
	local_20.z = m_modelC->m_worldMtx[2][3];
	local_2c.x = m_modelB->m_worldMtx[0][3];
	local_2c.y = m_modelB->m_worldMtx[1][3];
	local_2c.z = m_modelB->m_worldMtx[2][3];
	PSVECSubtract(&local_20, &local_14, &local_20);
	PSVECSubtract(&local_2c, &local_14, &VStack_38);
	C_MTXLookAt(m_viewMtx, (Point3d*)&local_14, &local_20, (Point3d*)&local_2c);
	PSMTXConcat(m_lightMtx, m_viewMtx, m_shadowMtx);
}

/*
 * --INFO--
 * PAL Address: 0x8004c8c8
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapShadow::Init()
{
	float width;
	float height;
	CMaterial* material;
	CMaterialSet* materialSet;

	materialSet = MapMng.m_materialSet;
	material = materialSet->m_materials[m_materialIndex];
	CTexture* texture = material->GetTexture(0);
	width = (float)texture->m_width;
	height = (float)texture->m_height;
	m_materialMode = texture->m_wrapMode;
	if (m_useFrustum != 0) {
		float scale = m_shadowScale;
		double scaleBias = 0.5;
		float scaleStep = 0.5f;
		C_MTXLightFrustum(m_lightMtx, -height, height, -width, width, m_frustumNear,
		                  (float)(scaleBias * (double)scale), scaleStep * scale, scaleStep, scaleStep);
	} else {
		float scale = m_shadowScale;
		double scaleBias = 0.5;
		float scaleStep = 0.5f;
		C_MTXLightOrtho(m_lightMtx, -height, height, -width, width,
		                (float)(scaleBias * (double)scale), scaleStep * scale, scaleStep, scaleStep);
	}
}

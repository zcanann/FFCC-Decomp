
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
void CMapShadowInsertOctTree(CMapShadow::TARGET target, COctTree& octTree)
{
	CMapShadow* shadow;
	int i;
	u32 octTreeMask;
	Vec pos;

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
	Vec eye;
	Vec up;
	Vec at;
	Vec lookDir;

	eye.x = m_modelA->m_worldMtx[0][3];
	eye.y = m_modelA->m_worldMtx[1][3];
	eye.z = m_modelA->m_worldMtx[2][3];
	up.x = m_modelC->m_worldMtx[0][3];
	up.y = m_modelC->m_worldMtx[1][3];
	up.z = m_modelC->m_worldMtx[2][3];
	at.x = m_modelB->m_worldMtx[0][3];
	at.y = m_modelB->m_worldMtx[1][3];
	at.z = m_modelB->m_worldMtx[2][3];
	PSVECSubtract(&up, &eye, &up);
	PSVECSubtract(&at, &eye, &lookDir);
	C_MTXLookAt(m_viewMtx, (Point3d*)&eye, &up, (Point3d*)&at);
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
		C_MTXLightFrustum(m_lightMtx, -height, height, -width, width, m_frustumNear,
		                  (float)(0.5 * scale), 0.5f * scale, 0.5f, 0.5f);
	} else {
		float scale = m_shadowScale;
		C_MTXLightOrtho(m_lightMtx, -height, height, -width, width,
		                (float)(0.5 * scale), 0.5f * scale, 0.5f, 0.5f);
	}
}

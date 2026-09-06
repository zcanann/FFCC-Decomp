#include "ffcc/quadobj.h"
#include "ffcc/color.h"
#include "ffcc/linkage.h"
#include "ffcc/p_camera.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x8010B2A4
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGQuadObj::GetCID()
{
	return 3;
}

/*
 * --INFO--
 * PAL Address: 0x8010B2AC
 * PAL Size: 208b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGQuadObj::Add(float x, float z)
{
    m_vertices[m_vertexCount].x = x;
    m_vertices[m_vertexCount].z = z;

    m_bboxMinX = (m_bboxMinX < m_vertices[m_vertexCount].x) ? m_bboxMinX : m_vertices[m_vertexCount].x;
    m_bboxMinZ = (m_bboxMinZ < m_vertices[m_vertexCount].z) ? m_bboxMinZ : m_vertices[m_vertexCount].z;
    m_bboxMaxX = (m_bboxMaxX < m_vertices[m_vertexCount].x) ? m_vertices[m_vertexCount].x : m_bboxMaxX;
    m_bboxMaxZ = (m_bboxMaxZ < m_vertices[m_vertexCount].z) ? m_vertices[m_vertexCount].z : m_bboxMaxZ;

    m_vertexCount++;
}

/*
 * --INFO--
 * PAL Address: 0x8010B37C
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGQuadObj::Reset(float base, float height)
{
	m_vertexCount = 0;
	m_yBase = base;
	m_yHeight = height;
	m_bboxMinZ = 10000000.0f;
	m_bboxMinX = 10000000.0f;
	m_bboxMaxZ = -10000000.0f;
	m_bboxMaxX = -10000000.0f;
}

/*
 * --INFO--
 * PAL Address: 0x8010b3a8
 * PAL Size: 256b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGQuadObj::isInner(Vec* vec)
{
	u32 count = m_vertexCount;
	if ((((count != 0) && (m_bboxMinX <= vec->x)) && (m_bboxMinZ <= vec->z)) && ((m_bboxMaxX >= vec->x) && (m_bboxMaxZ >= vec->z))) {
		if ((m_yBase <= vec->y) && ((m_yBase + m_yHeight) >= vec->y)) {
			int i = 0;
			for (; i < (int)count; i++) {
				float z0 = m_vertices[i].z;
				float x0 = m_vertices[i].x;
				int next = (i + 1) % (int)count;
				if (((m_vertices[next].x - x0) * (vec->z - z0) - (m_vertices[next].z - z0) * (vec->x - x0)) < 0.0f) {
					break;
				}
			}

			if (i == (int)count) {
				return true;
			}
		}
	}

	return false;
}

/*
 * --INFO--
 * PAL Address: 0x8010b4a8
 * PAL Size: 424b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGQuadObj::onDraw()
{
    if (m_vertexCount != 0 && (CFlatRuntimeDebugFlags() & CFlatRuntimeDebugFlag_QuadBounds) != 0) {
        GXSetChanMatColor(GX_COLOR0A0, CColor(0xff, 0xff, 0xff, 0xff).color);
        GXLoadPosMtxImm(CameraPcs.m_cameraMatrix, GX_PNMTX0);
        GXBegin(GX_LINES, GX_VTXFMT0, ((u32)m_vertexCount << 1) + ((u32)m_vertexCount << 2));

        for (int i = 0; i < m_vertexCount; i++) {
            GXPosition3f32(m_vertices[i].x, m_yBase, m_vertices[i].z);
            int next = (i + 1) % m_vertexCount;
            GXPosition3f32(m_vertices[next].x, m_yBase, m_vertices[next].z);
            GXPosition3f32(m_vertices[i].x, m_yBase + m_yHeight, m_vertices[i].z);
            next = (i + 1) % m_vertexCount;
            GXPosition3f32(m_vertices[next].x, m_yBase + m_yHeight, m_vertices[next].z);
            GXPosition3f32(m_vertices[i].x, m_yBase, m_vertices[i].z);
            GXPosition3f32(m_vertices[i].x, m_yBase + m_yHeight, m_vertices[i].z);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8010B650
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGQuadObj::onDestroy()
{
}

/*
 * --INFO--
 * PAL Address: 0x8010B654
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGQuadObj::onCreate()
{
	m_vertexCount = 0;
}

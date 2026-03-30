#include "ffcc/quadobj.h"
#include "ffcc/color.h"
#include "ffcc/linkage.h"
#include "ffcc/p_camera.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

static const float MaxBounds = 10000000.0;
static const float MinBounds = -10000000.0;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGQuadObj::onCreate()
{ 
	m_vertexCount = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGQuadObj::onDestroy()
{
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
    if (m_vertexCount != 0 && (*(u32*)(CFlat + 0x129C) & 0x10000) != 0) {
        GXSetChanMatColor(GX_COLOR0A0, CColor(0xff, 0xff, 0xff, 0xff).color);
        GXLoadPosMtxImm(*reinterpret_cast<Mtx*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0x4), GX_PNMTX0);
        GXBegin(GX_LINES, GX_VTXFMT0, ((u32)m_vertexCount << 1) + ((u32)m_vertexCount << 2));

        CGQuadObj* self = this;
        int i = 0;

        while (i < (int)(u32)m_vertexCount) {
            int next = i + 1;
            QuadVertex* vertex = self->m_vertices;

            i++;

            GXPosition3f32(vertex->x, m_yBase, vertex->z);
            next = next - (next / (int)(u32)m_vertexCount) * (u32)m_vertexCount;
            GXPosition3f32(m_vertices[next].x, m_yBase, m_vertices[next].z);
            GXPosition3f32(vertex->x, m_yBase + m_yHeight, vertex->z);
            next = next - (next / (int)(u32)m_vertexCount) * (u32)m_vertexCount;
            GXPosition3f32(m_vertices[next].x, m_yBase + m_yHeight, m_vertices[next].z);
            GXPosition3f32(vertex->x, m_yBase, vertex->z);

            self = reinterpret_cast<CGQuadObj*>(reinterpret_cast<unsigned char*>(self) + sizeof(QuadVertex));
            GXPosition3f32(vertex->x, m_yBase + m_yHeight, vertex->z);
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CGQuadObj::GetCID()
{ 
	return 3;
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
bool CGQuadObj::isInner(Vec* vec)
{
	CGQuadObj* self;
	u32 count = m_vertexCount;
	if ((((count != 0) && (m_bboxMinX <= vec->x)) && (m_bboxMinZ <= vec->z)) && ((m_bboxMaxX >= vec->x) && (m_bboxMaxZ >= vec->z))) {
		if ((m_yBase <= vec->y) && ((m_yBase + m_yHeight) >= vec->y)) {
			self = this;
			int i = 0;
			for (; i < (int)count; i++) {
				float z0 = self->m_vertices[0].z;
				float x0 = self->m_vertices[0].x;
				int quotient = (i + 1) / (int)count;
				int next = (i + 1) - quotient * (int)count;
				if (((m_vertices[next].x - x0) * (vec->z - z0) - (m_vertices[next].z - z0) * (vec->x - x0)) < 0.0f) {
					break;
				}
				self = reinterpret_cast<CGQuadObj*>(reinterpret_cast<unsigned char*>(self) + sizeof(QuadVertex));
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
 * Address:	TODO
 * Size:	TODO
 */
void CGQuadObj::Reset(float base, float height)
{ 
	m_vertexCount = 0;
	m_yBase = base;
	m_yHeight = height;
	m_bboxMinZ = MaxBounds;
	m_bboxMinX = MaxBounds;
	m_bboxMaxZ = MinBounds;
	m_bboxMaxX = MinBounds;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
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

#include "ffcc/quadobj.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

static const float MaxBounds = 10000000.0;
static const float MinBounds = -10000000.0;
static const float EPS = 0.0;

extern u32 CFlatFlags;     // CFlat._4764_4_
extern Mtx gFlatPosMtx;    // at 0x802687ac

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
 * Address:	TODO
 * Size:	TODO
 */
void CGQuadObj::onDraw()
{
    if (m_vertexCount == 0 || (CFlatFlags & 0x10000) == 0)
        return;

    GXColor white = { 0xFF, 0xFF, 0xFF, 0xFF };
    GXSetChanMatColor(GX_COLOR0A0, white);
    GXLoadPosMtxImm(gFlatPosMtx, GX_PNMTX0);
    GXBegin(GX_TRIANGLES, GX_VTXFMT0, m_vertexCount * 6);

    float y0 = m_yBase;
    float y1 = m_yBase + m_yHeight;

    for (int i = 0; i < m_vertexCount; i++)
    {
        int next = (i + 1) % m_vertexCount;
        QuadVertex& v0 = m_vertices[i];
        QuadVertex& v1 = m_vertices[next];

        GXPosition3f32(v0.x, y0, v0.z);
        GXPosition3f32(v1.x, y0, v1.z);
        GXPosition3f32(v0.x, y1, v0.z);
        GXPosition3f32(v1.x, y1, v1.z);
        GXPosition3f32(v0.x, y0, v0.z);
        GXPosition3f32(v0.x, y1, v0.z);
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
 * Address:	TODO
 * Size:	TODO
 */
bool CGQuadObj::isInner(Vec* vec)
{
    int count = m_vertexCount;

    if (count != 0)
    {
        float px = vec->x;
        float py = vec->y;
        float pz = vec->z;

        if (m_bboxMinX <= px && m_bboxMinZ <= pz && m_bboxMaxX >= px && m_bboxMaxZ >= pz && m_yBase <= py)
        {
            float top = m_yBase + m_yHeight;

            if (top >= py)
            {
                int i;

                for (i = 0; i < count; i++)
                {
                    const QuadVertex& v0 = m_vertices[i];
                    int next = (i + 1) % count;
                    const QuadVertex& v1 = m_vertices[next];
                    
                    float dz0 = pz - v0.z;
                    float dx0 = px - v0.x;
                    float dz1 = v1.z - v0.z;
                    float dx1 = v1.x - v0.x;
                    float cross = dx1 * dz0 - dz1 * dx0;

                    if (cross < EPS)
                    {
                        break;
                    }
                }

                if (i == count)
                {
                    return true;
                }
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

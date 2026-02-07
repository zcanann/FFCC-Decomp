#include "ffcc/quadobj.h"
#include "ffcc/color.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

static const float MaxBounds = 10000000.0;
static const float MinBounds = -10000000.0;
static const float EPS = 0.0;

extern u32 CFlatFlags;     // CFlat._4764_4_
extern void* CameraPcs;    // matrix at +0x4

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
    if ((m_vertexCount != 0) && ((CFlatFlags & 0x10000) != 0)) {
        CColor white(0xff, 0xff, 0xff, 0xff);
        GXSetChanMatColor(GX_COLOR0A0, *(GXColor*)&white);
        MtxPtr posMtx = (MtxPtr)((char*)&CameraPcs + 0x4);
        GXLoadPosMtxImm(posMtx, GX_PNMTX0);
        GXBegin(GX_TRIANGLES, GX_VTXFMT0, (u32)m_vertexCount * 6);

        int i = 0;
        QuadVertex* pVert = m_vertices;
        while (i < (int)(u32)m_vertexCount) {
            int next = i + 1;
            i = i + 1;

            GXPosition3f32(pVert->x, m_yBase, pVert->z);

            int idx = next - (next / (int)(u32)m_vertexCount) * (u32)m_vertexCount;
            GXPosition3f32(m_vertices[idx].x, m_yBase, m_vertices[idx].z);

            GXPosition3f32(pVert->x, m_yBase + m_yHeight, pVert->z);

            idx = next - (next / (int)(u32)m_vertexCount) * (u32)m_vertexCount;
            GXPosition3f32(m_vertices[idx].x, m_yBase + m_yHeight, m_vertices[idx].z);

            GXPosition3f32(pVert->x, m_yBase, pVert->z);
            pVert++;
            GXPosition3f32(pVert[-1].x, m_yBase + m_yHeight, pVert[-1].z);
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
 * Address:	TODO
 * Size:	TODO
 */
bool CGQuadObj::isInner(Vec* vec)
{
    u32 count = (u32)m_vertexCount;
    
    if (count != 0) {
        float px = vec->x;
        float pz = vec->z;
        
        if ((m_bboxMinX <= px && m_bboxMinZ <= pz) && 
            (px <= m_bboxMaxX && pz <= m_bboxMaxZ)) {
            if (m_yBase <= vec->y && vec->y <= m_yBase + m_yHeight) {
                u32 i = 0;
                u32 remaining = count;
                QuadVertex* pVert = m_vertices;
                
                while (remaining != 0) {
                    float z0 = pVert->z;
                    float x0 = pVert->x;
                    int next = ((i + 1) - ((int)(i + 1) / (int)count) * count);
                    float cross = (m_vertices[next].x - x0) * (pz - z0) - 
                                  (m_vertices[next].z - z0) * (px - x0);
                    
                    if (cross < EPS) {
                        break;
                    }
                    
                    pVert++;
                    i++;
                    remaining--;
                }
                
                if (i == count) {
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

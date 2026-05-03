#include "ffcc/maphit.h"
#include "ffcc/chunkfile.h"
#include "ffcc/map.h"
#include "ffcc/memory.h"
#include "ffcc/system.h"

#include <math.h>

extern "C" const float FLOAT_8032F8EC;
extern "C" const float FLOAT_8032F8F0;

CMapCylinder g_hit_cyl;
CMapCylinder g_hit_cyl_min;
Vec g_hit_mvec;
Vec g_hit_mvec_min;
Vec g_hit_hpv;
Vec g_hit_hpv_min;

namespace {
static const char s_maphit_cpp[] = "maphit.cpp";
static const float s_large_pos = 3.4e38f;
static const float s_large_neg = -3.4e38f;
static const float s_epsilon = 0.0001f;
static const float s_push = 0.01f;

static inline unsigned char* Ptr(void* p, unsigned int offset)
{
    return reinterpret_cast<unsigned char*>(p) + offset;
}
}

int g_hit_edge_idx_min;
float g_hit_t;
float g_hit_t_min;
float g_hit_t_slide_min;
unsigned char g_hit_f;
CMapHitFace* g_hit_lpface;
CMapHitFace* g_hit_lpface_min;

/*
 * --INFO--
 * PAL Address: 0x80026e24
 * PAL Size: 2308b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int FindIntersection(const Vec& start, const Vec& direction, const CMapCylinder& cyl, float& outT)
{
    outT = 0.0f;

    Vec axis = cyl.m_direction2;
    f32 axisLen = PSVECMag(&axis);
    if (axisLen <= 0.0f) {
        return 0;
    }
    PSVECScale(&axis, &axis, 1.0f / axisLen);

    Vec orthogonal;
    if (fabsf(axis.x) < fabsf(axis.y) || fabsf(axis.x) < fabsf(axis.z)) {
        orthogonal.x = 0.0f;
        orthogonal.y = axis.z;
        orthogonal.z = -axis.y;
    } else {
        orthogonal.x = -axis.y;
        orthogonal.y = axis.x;
        orthogonal.z = 0.0f;
    }
    PSVECNormalize(&orthogonal, &orthogonal);

    Vec bitangent;
    PSVECCrossProduct(&axis, &orthogonal, &bitangent);

    Vec relStart;
    PSVECSubtract(&start, &cyl.m_top, &relStart);

    const f32 px = PSVECDotProduct(&orthogonal, &relStart);
    const f32 py = PSVECDotProduct(&bitangent, &relStart);
    const f32 pz = PSVECDotProduct(&axis, &relStart);

    const f32 vx = PSVECDotProduct(&orthogonal, &direction);
    const f32 vy = PSVECDotProduct(&bitangent, &direction);
    const f32 vz = PSVECDotProduct(&axis, &direction);

    const f32 radius = cyl.m_radius2;
    const f32 halfHeight = cyl.m_height2;

    f32 bestT = -1.0f;

    const f32 a = vx * vx + vy * vy;
    const f32 b = 2.0f * (px * vx + py * vy);
    const f32 c = (px * px + py * py) - (radius * radius);
    if (a > 0.0f) {
        const f32 disc = b * b - 4.0f * a * c;
        if (disc >= 0.0f) {
            const f32 sqrtDisc = sqrtf(disc);
            const f32 inv2a = 0.5f / a;
            f32 t0 = (-b - sqrtDisc) * inv2a;
            f32 t1 = (-b + sqrtDisc) * inv2a;
            if (t0 > t1) {
                const f32 tmp = t0;
                t0 = t1;
                t1 = tmp;
            }

            if (t0 >= 0.0f) {
                const f32 z0 = pz + t0 * vz;
                if (-halfHeight <= z0 && z0 <= halfHeight) {
                    bestT = t0;
                }
            }

            if (bestT < 0.0f && t1 >= 0.0f) {
                const f32 z1 = pz + t1 * vz;
                if (-halfHeight <= z1 && z1 <= halfHeight) {
                    bestT = t1;
                }
            }
        }
    }

    if (fabsf(vz) > 0.0f) {
        const f32 capZ[2] = { -halfHeight, halfHeight };
        for (int i = 0; i < 2; i++) {
            const f32 t = (capZ[i] - pz) / vz;
            if (t < 0.0f) {
                continue;
            }
            if (bestT >= 0.0f && t >= bestT) {
                continue;
            }

            const f32 x = px + t * vx;
            const f32 y = py + t * vy;
            if ((x * x + y * y) <= radius * radius) {
                bestT = t;
            }
        }
    }

    outT = bestT;
    return bestT >= 0.0f;
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void CheckLineCylinder(const Vec& start, const Vec& end, const CMapCylinder& cyl, float& outT)
{
    Vec line;
    PSVECSubtract(&end, &start, &line);
    FindIntersection(start, line, cyl, outT);
}

/*
 * --INFO--
 * PAL Address: 0x80026dec
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapHit::CMapHit()
{
    m_positionMin.z = 0.0f;
    m_positionMin.y = 0.0f;
    m_positionMin.x = 0.0f;

    m_positionMax.z = 1.0f;
    m_positionMax.y = 1.0f;
    m_positionMax.x = 1.0f;

    m_vertexCount = 0;
    m_faceCount = 0;
    m_vertices = 0;
    m_faces = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80026d5c
 * PAL Size: 144b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapHit::~CMapHit()
{
    if (m_vertices != 0) {
        delete m_vertices;
        m_vertices = 0;
    }

    if (m_faces != 0) {
        delete[] m_faces;
        m_faces = 0;
    }

    m_vertexCount = 0;
    m_faceCount = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800266f0
 * PAL Size: 1608b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapHit::ReadOtmHit(CChunkFile& chunkFile)
{
    CChunkFile::CChunk chunk;
    CMemory::CStage* const stage = *reinterpret_cast<CMemory::CStage**>(&MapMng);

    chunkFile.PushChunk();

    while (chunkFile.GetNextChunk(chunk)) {
        if (chunk.m_id == 'HITV') {
            m_vertexCount = static_cast<unsigned short>(chunk.m_arg0);
            m_vertices = new (stage, const_cast<char*>(s_maphit_cpp), 0x143) Vec[m_vertexCount];

            m_positionMin.x = s_large_pos;
            m_positionMin.y = s_large_pos;
            m_positionMin.z = s_large_pos;
            m_positionMax.x = s_large_neg;
            m_positionMax.y = s_large_neg;
            m_positionMax.z = s_large_neg;

            for (unsigned int i = 0; i < m_vertexCount; i++) {
                Vec& v = m_vertices[i];
                v.x = chunkFile.GetF4();
                v.y = chunkFile.GetF4();
                v.z = chunkFile.GetF4();

                if (v.x < m_positionMin.x) {
                    m_positionMin.x = v.x;
                }
                if (v.y < m_positionMin.y) {
                    m_positionMin.y = v.y;
                }
                if (v.z < m_positionMin.z) {
                    m_positionMin.z = v.z;
                }

                if (m_positionMax.x < v.x) {
                    m_positionMax.x = v.x;
                }
                if (m_positionMax.y < v.y) {
                    m_positionMax.y = v.y;
                }
                if (m_positionMax.z < v.z) {
                    m_positionMax.z = v.z;
                }
            }

            m_positionMin.x -= 0.1f;
            m_positionMin.y -= 0.1f;
            m_positionMin.z -= 0.1f;
            m_positionMax.x += 0.1f;
            m_positionMax.y += 0.1f;
            m_positionMax.z += 0.1f;
        } else if (chunk.m_id == 'HITF') {
            m_faceCount = static_cast<unsigned short>(chunk.m_arg0);
            m_faces = new (stage, const_cast<char*>(s_maphit_cpp), 0x159) CMapHitFace[m_faceCount];

            for (unsigned int faceIdx = 0; faceIdx < m_faceCount; faceIdx++) {
                chunkFile.Align(4);

                CMapHitFace& face = m_faces[faceIdx];

                face.m_normal.x = chunkFile.GetF4();
                face.m_normal.y = chunkFile.GetF4();
                face.m_normal.z = chunkFile.GetF4();
                face.m_planeD = chunkFile.GetF4();

                face.m_edgeFlags = chunkFile.Get1();
                face.m_projectionAxis = chunkFile.Get1();
                face.m_vertexCount = chunkFile.Get1();
                face.m_groupIndex = chunkFile.Get1();
                face.m_flags = 0;
                face.m_drawFlags = 0;

                const unsigned int vertexCount = face.m_vertexCount;
                for (unsigned int i = 0; i < vertexCount; i++) {
                    face.m_vertexOffsets[i][0] = 0.0f;
                    face.m_vertexOffsets[i][1] = 0.0f;
                }

                if (chunk.m_version == 0) {
                    chunkFile.Align(4);
                    for (unsigned int i = 0; i < vertexCount; i++) {
                        (void)chunkFile.GetF4();
                        (void)chunkFile.GetF4();
                    }
                    face.m_radiusScale = 0.0f;
                } else if (chunk.m_version == 1) {
                    face.m_radiusScale = chunkFile.GetF4();
                    chunkFile.Align(4);
                } else {
                    face.m_radiusScale = chunkFile.GetF4();
                    chunkFile.Align(4);
                    for (unsigned int i = 0; i < vertexCount; i++) {
                        face.m_vertexOffsets[i][0] = chunkFile.GetF4() * 0.01f;
                        face.m_vertexOffsets[i][1] = chunkFile.GetF4() * 0.01f;
                    }
                }

                face.m_boundsMin.x = s_large_pos;
                face.m_boundsMin.y = s_large_pos;
                face.m_boundsMin.z = s_large_pos;
                face.m_boundsMax.x = s_large_neg;
                face.m_boundsMax.y = s_large_neg;
                face.m_boundsMax.z = s_large_neg;

                for (unsigned int i = 0; i < vertexCount; i++) {
                    const unsigned short idx = chunkFile.Get2();
                    face.m_vertexIndices[i] = idx;

                    const Vec& v = m_vertices[idx];
                    if (v.x < face.m_boundsMin.x) {
                        face.m_boundsMin.x = v.x;
                    }
                    if (v.y < face.m_boundsMin.y) {
                        face.m_boundsMin.y = v.y;
                    }
                    if (v.z < face.m_boundsMin.z) {
                        face.m_boundsMin.z = v.z;
                    }

                    if (face.m_boundsMax.x < v.x) {
                        face.m_boundsMax.x = v.x;
                    }
                    if (face.m_boundsMax.y < v.y) {
                        face.m_boundsMax.y = v.y;
                    }
                    if (face.m_boundsMax.z < v.z) {
                        face.m_boundsMax.z = v.z;
                    }
                }

                float width = face.m_radiusScale * 0.5f;
                face.m_boundsMin.x -= (0.1f + width);
                face.m_boundsMin.y -= (0.1f + width);
                face.m_boundsMin.z -= (0.1f + width);
                face.m_boundsMax.x += (0.1f + width);
                face.m_boundsMax.y += (0.1f + width);
                face.m_boundsMax.z += (0.1f + width);
                face.m_radiusScale = 1.0f - width;
            }
        } else if (chunk.m_id == 'NAME') {
            char* mapHitName = chunkFile.GetString();
            MapMng.AttachMapHit(this, mapHitName);
        }
    }

    chunkFile.PopChunk();
}

/*
 * --INFO--
 * PAL Address: 0x80025df4
 * PAL Size: 2300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMapHit::CheckHitFaceCylinder(unsigned long mask)
{
    unsigned char* mapMngBytes = reinterpret_cast<unsigned char*>(&MapMng);
    unsigned long groupMask =
        *reinterpret_cast<unsigned long*>(mapMngBytes + 0x214E8 + g_hit_lpface->m_groupIndex * 0x14);
    if ((groupMask & mask) == 0) {
        return 0;
    }

    bool overlap = false;
    if (g_hit_cyl.m_top.z <= g_hit_lpface->m_boundsMin.x) {
        if (g_hit_lpface->m_boundsMin.x <= g_hit_cyl.m_top.z) {
            overlap = true;
        } else {
            overlap = g_hit_lpface->m_boundsMin.x <= g_hit_cyl.m_direction2.z;
        }
    } else {
        overlap = g_hit_cyl.m_top.z <= g_hit_lpface->m_boundsMax.x;
    }
    if (!overlap) {
        return 0;
    }

    overlap = false;
    if (g_hit_cyl.m_direction2.x <= g_hit_lpface->m_boundsMin.y) {
        if (g_hit_lpface->m_boundsMin.y <= g_hit_cyl.m_direction2.x) {
            overlap = true;
        } else {
            overlap = g_hit_lpface->m_boundsMin.y <= g_hit_cyl.m_radius2;
        }
    } else {
        overlap = g_hit_cyl.m_direction2.x <= g_hit_lpface->m_boundsMax.y;
    }
    if (!overlap) {
        return 0;
    }

    overlap = false;
    if (g_hit_cyl.m_direction2.y <= g_hit_lpface->m_boundsMin.z) {
        if (g_hit_lpface->m_boundsMin.z <= g_hit_cyl.m_direction2.y) {
            overlap = true;
        } else {
            overlap = g_hit_lpface->m_boundsMin.z <= g_hit_cyl.m_height2;
        }
    } else {
        overlap = g_hit_cyl.m_direction2.y <= g_hit_lpface->m_boundsMax.z;
    }
    if (!overlap) {
        return 0;
    }

    Vec* normal = &g_hit_lpface->m_normal;
    Vec* hitDirection = reinterpret_cast<Vec*>(&g_hit_cyl.m_radius);
    float dot = PSVECDotProduct(hitDirection, normal);
    if (dot >= 0.0f) {
        return 0;
    }

    float hitDot = PSVECDotProduct(&g_hit_cyl.m_bottom, normal);
    float hitT = -((hitDot - (g_hit_lpface->m_planeD + g_hit_cyl.m_top.y)) / dot);
    int edgeIndex = -1;

    if (0.0f < hitT && hitT < g_hit_t_min) {
        PSVECScale(hitDirection, &g_hit_hpv, hitT);
        PSVECAdd(&g_hit_cyl.m_bottom, &g_hit_hpv, &g_hit_hpv);

        Vec pushedHit;
        PSVECScale(normal, &pushedHit, g_hit_cyl.m_top.y);
        PSVECSubtract(&g_hit_hpv, &pushedHit, &pushedHit);

        Vec previous = m_vertices[g_hit_lpface->m_vertexIndices[g_hit_lpface->m_vertexCount - 1]];
        unsigned int sideMask = 3;
        for (int i = 0; i < static_cast<int>(g_hit_lpface->m_vertexCount); i++) {
            Vec current = m_vertices[g_hit_lpface->m_vertexIndices[i]];
            Vec edgeStart;
            Vec edgeEnd;
            Vec point;

            if (g_hit_lpface->m_projectionAxis == 1) {
                edgeStart.x = previous.x + g_hit_lpface->m_vertexOffsets[i][0];
                edgeStart.y = previous.z + g_hit_lpface->m_vertexOffsets[i][1];
                edgeStart.z = 0.0f;
                edgeEnd.x = current.x + g_hit_lpface->m_vertexOffsets[i][0];
                edgeEnd.y = current.z + g_hit_lpface->m_vertexOffsets[i][1];
                edgeEnd.z = 0.0f;
                point.x = pushedHit.x;
                point.y = pushedHit.z;
                point.z = 0.0f;
            } else if (g_hit_lpface->m_projectionAxis == 0) {
                edgeStart.x = previous.y + g_hit_lpface->m_vertexOffsets[i][0];
                edgeStart.y = previous.z + g_hit_lpface->m_vertexOffsets[i][1];
                edgeStart.z = 0.0f;
                edgeEnd.x = current.y + g_hit_lpface->m_vertexOffsets[i][0];
                edgeEnd.y = current.z + g_hit_lpface->m_vertexOffsets[i][1];
                edgeEnd.z = 0.0f;
                point.x = pushedHit.y;
                point.y = pushedHit.z;
                point.z = 0.0f;
            } else {
                edgeStart.x = previous.x + g_hit_lpface->m_vertexOffsets[i][0];
                edgeStart.y = previous.y + g_hit_lpface->m_vertexOffsets[i][1];
                edgeStart.z = 0.0f;
                edgeEnd.x = current.x + g_hit_lpface->m_vertexOffsets[i][0];
                edgeEnd.y = current.y + g_hit_lpface->m_vertexOffsets[i][1];
                edgeEnd.z = 0.0f;
                point.x = pushedHit.x;
                point.y = pushedHit.y;
                point.z = 0.0f;
            }

            Vec edge;
            Vec toPoint;
            Vec cross;
            PSVECSubtract(&edgeEnd, &edgeStart, &edge);
            PSVECSubtract(&point, &edgeEnd, &toPoint);
            PSVECCrossProduct(&edge, &toPoint, &cross);
            if (cross.z < 0.0f) {
                sideMask &= 2;
            } else {
                sideMask &= 1;
            }

            if (sideMask == 0) {
                edgeIndex = i;
                break;
            }

            previous = current;
        }

        if (sideMask != 0) {
            edgeIndex = -1;
        }
    }

    if (edgeIndex != -1 || hitT <= 0.0f || g_hit_t_min <= hitT) {
        Vec previous = m_vertices[g_hit_lpface->m_vertexIndices[g_hit_lpface->m_vertexCount - 1]];
        for (int i = 0; i < static_cast<int>(g_hit_lpface->m_vertexCount); i++) {
            Vec current = m_vertices[g_hit_lpface->m_vertexIndices[i]];
            if ((g_hit_lpface->m_edgeFlags & (1 << i)) != 0) {
                Vec edge;
                PSVECSubtract(&current, &previous, &edge);

                CMapCylinder edgeCylinder;
                edgeCylinder.m_bottom = previous;
                *reinterpret_cast<Vec*>(&edgeCylinder.m_radius) = edge;
                edgeCylinder.m_top.y = g_hit_cyl.m_top.y;

                float edgeT;
                if (FindIntersection(g_hit_cyl.m_bottom, *hitDirection, edgeCylinder, edgeT) != 0 &&
                    edgeT < g_hit_t_min) {
                    hitT = edgeT;
                    edgeIndex = i;
                    PSVECScale(hitDirection, &g_hit_hpv, hitT);
                    PSVECAdd(&g_hit_cyl.m_bottom, &g_hit_hpv, &g_hit_hpv);
                    break;
                }
            }
            previous = current;
        }

        if (edgeIndex == -1 || g_hit_t_min <= hitT) {
            return 0;
        }
    }

    g_hit_t = hitT;
    g_hit_t_min = hitT;
    g_hit_t_slide_min = hitT;
    g_hit_edge_idx_min = edgeIndex;
    g_hit_lpface_min = g_hit_lpface;
    g_hit_cyl_min = g_hit_cyl;
    if (gMapHitDrawMode != 0) {
        g_hit_lpface->m_drawFlags = 1;
    }
    g_hit_mvec_min = g_hit_mvec;
    g_hit_hpv_min = g_hit_hpv;
    g_hit_f = 1;
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x80025dd4
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapHit::GetHitFaceNormal(Vec* out)
{
    float* const normal = reinterpret_cast<float*>(gMapHitFace);
    out->x = normal[0];
    out->y = normal[1];
    out->z = normal[2];
}

/*
 * --INFO--
 * PAL Address: 0x80025a4c
 * PAL Size: 904b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMapHit::CalcHitSlide(Vec* out, float y)
{
    Vec* hitDirection = reinterpret_cast<Vec*>(&g_hit_cyl_min.m_radius);

    if (g_hit_edge_idx_min == -1) {
        if (y <= gMapHitFace->m_normal.y) {
            float len = PSVECMag(hitDirection);
            PSVECScale(hitDirection, out, g_hit_t - (s_push / len));
            return 0;
        }

        if (s_epsilon < g_hit_t) {
            Vec push;
            float planeDot = PSVECDotProduct(&g_hit_cyl_min.m_direction, &gMapHitFace->m_normal);
            PSVECScale(&gMapHitFace->m_normal, &push,
                       s_push - (planeDot - (gMapHitFace->m_planeD + g_hit_cyl_min.m_top.y)));
            PSVECAdd(&g_hit_cyl_min.m_direction, &push, &push);
            PSVECSubtract(&push, &g_hit_cyl_min.m_bottom, out);
            return 1;
        }

        out->z = 0.0f;
        out->y = 0.0f;
        out->x = 0.0f;
        return 1;
    }

    if (y <= gMapHitFace->m_normal.y) {
        float len = PSVECMag(hitDirection);
        PSVECScale(hitDirection, out, g_hit_t - (s_push / len));
        return 0;
    }

    Vec previous;
    Vec current;
    if (g_hit_edge_idx_min == 0) {
        previous = m_vertices[gMapHitFace->m_vertexIndices[gMapHitFace->m_vertexCount - 1]];
        current = m_vertices[gMapHitFace->m_vertexIndices[0]];
    } else {
        previous = m_vertices[gMapHitFace->m_vertexIndices[g_hit_edge_idx_min - 1]];
        current = m_vertices[gMapHitFace->m_vertexIndices[g_hit_edge_idx_min]];
    }

    Vec edge;
    Vec edgeToCenter;
    PSVECSubtract(&current, &previous, &edge);
    PSVECSubtract(&current, &g_hit_cyl_min.m_direction, &edgeToCenter);

    float edgeDot = PSVECDotProduct(&edge, &edgeToCenter);
    float edgeLenSq = PSVECDotProduct(&edge, &edge);

    Vec edgeProjection;
    Vec nearestPoint;
    PSVECScale(&edge, &edgeProjection, edgeDot / edgeLenSq);
    PSVECSubtract(&current, &edgeProjection, &nearestPoint);

    Vec slideDir;
    PSVECSubtract(&g_hit_cyl_min.m_direction, &nearestPoint, &slideDir);

    float side = PSVECDotProduct(hitDirection, &slideDir);
    float slideLen = PSVECMag(&slideDir);
    if (slideLen < s_epsilon) {
        out->z = 0.0f;
        out->y = 0.0f;
        out->x = 0.0f;
    } else {
        PSVECScale(&slideDir, &slideDir, s_push / slideLen);
        if (0.0f < side) {
            PSVECScale(&slideDir, &slideDir, -g_hit_cyl_min.m_top.y);
        } else {
            PSVECScale(&slideDir, &slideDir, g_hit_cyl_min.m_top.y);
        }

        PSVECAdd(&nearestPoint, &slideDir, &nearestPoint);
        PSVECSubtract(&nearestPoint, &g_hit_cyl_min.m_bottom, out);
    }

    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x80025984
 * PAL Size: 200b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapHit::CalcHitPosition(Vec* position)
{
    if (g_hit_edge_idx_min != -1) {
        float len = PSVECMag(reinterpret_cast<Vec*>(&g_hit_cyl_min.m_radius));
        PSVECScale(reinterpret_cast<Vec*>(&g_hit_cyl_min.m_radius), position, g_hit_t - (s_epsilon / len));
        PSVECAdd(&g_hit_cyl_min.m_bottom, position, position);
    } else {
        float len = PSVECMag(reinterpret_cast<Vec*>(&g_hit_cyl_min.m_radius));
        PSVECScale(reinterpret_cast<Vec*>(&g_hit_cyl_min.m_radius), position, g_hit_t - (s_push / len));
        PSVECAdd(&g_hit_cyl_min.m_bottom, position, position);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80025838
 * PAL Size: 332b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMapHit::CheckHitCylinder(CMapCylinder* mapCylinder, Vec* position, unsigned long mask)
{
    g_hit_cyl = *mapCylinder;
    g_hit_mvec = *position;

    int faceIndex = 0;
    int faceOffset = 0;
    while (faceIndex < static_cast<int>(m_faceCount)) {
        g_hit_lpface = reinterpret_cast<CMapHitFace*>(Ptr(m_faces, faceOffset));
        g_hit_t_min = s_large_pos;
        if (CheckHitFaceCylinder(mask) != 0) {
            return 1;
        }
        faceOffset += 0x50;
        faceIndex++;
    }

    return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMapHit::CheckHitCylinder(CMapCylinder* mapCylinder, Vec* position, unsigned short startFace, unsigned short faceCount, unsigned long mask)
{
    g_hit_cyl = *mapCylinder;
    g_hit_mvec = *position;

    unsigned int faceIndex = static_cast<unsigned short>(startFace);
    unsigned int endFace = static_cast<unsigned short>(startFace + faceCount);
    int faceOffset = static_cast<int>(faceIndex) * 0x50;

    while (faceIndex < endFace) {
        g_hit_lpface = reinterpret_cast<CMapHitFace*>(Ptr(m_faces, faceOffset));
        g_hit_t_min = s_large_pos;

        if (CheckHitFaceCylinder(mask) != 0) {
            return 1;
        }

        faceOffset += 0x50;
        faceIndex++;
    }

    return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapHit::CheckHitCylinderNear(CMapCylinder* mapCylinder, Vec* position, unsigned long mask)
{
    g_hit_cyl = *mapCylinder;
    g_hit_mvec = *position;

    CMapHitFace* face = m_faces;
    int faceOffset = 0;
    for (int i = 0; i < m_faceCount; i++) {
        g_hit_lpface = reinterpret_cast<CMapHitFace*>(Ptr(face, faceOffset));
        CheckHitFaceCylinder(mask);
        faceOffset += 0x50;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800254d0
 * PAL Size: 268b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapHit::CheckHitCylinderNear(CMapCylinder* mapCylinder, Vec* position, unsigned short startFace, unsigned short faceCount, unsigned long mask)
{
    g_hit_cyl = *mapCylinder;
    g_hit_mvec = *position;

    unsigned int faceIndex = startFace;
    unsigned int endFace = static_cast<unsigned short>(startFace + faceCount);
    int faceOffset = static_cast<int>(faceIndex) * 0x50;

    while (faceIndex < endFace) {
        g_hit_lpface = reinterpret_cast<CMapHitFace*>(Ptr(m_faces, faceOffset));
        CheckHitFaceCylinder(mask);
        faceOffset += 0x50;
        faceIndex++;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800273f4
 * PAL Size: 1376b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapHit::Draw()
{
    static const u32 kOverlayColor = 0x40FF40FF;
    unsigned char* mapMngBytes = reinterpret_cast<unsigned char*>(&MapMng);

    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_NRM, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);

    unsigned char* face = reinterpret_cast<unsigned char*>(m_faces);
    int faceIndex = 0;
    while (faceIndex < m_faceCount) {
        if ((reinterpret_cast<CMapHitFace*>(face)->m_drawFlags & 1) == 0) {
            const unsigned char vertexCount = face[0x46];
            const unsigned char groupIndex = face[0x47];
            const u32 colorA = *reinterpret_cast<u32*>(mapMngBytes + 0x214E8 + groupIndex * 0x14 + 0x4);
            const u32 colorB = *reinterpret_cast<u32*>(mapMngBytes + 0x214E8 + groupIndex * 0x14 + 0x8);

            GXBegin(GX_TRIANGLES, GX_VTXFMT7, 3);
            unsigned char* index = face + 0x48;
            int i = 0;
            while (i < static_cast<int>(vertexCount)) {
                Vec* vertex = m_vertices + *reinterpret_cast<unsigned short*>(index);
                GXPosition3f32(vertex->x, vertex->y, vertex->z);
                GXNormal3f32(*reinterpret_cast<float*>(face + 0x00), *reinterpret_cast<float*>(face + 0x04),
                             *reinterpret_cast<float*>(face + 0x08));
                GXColor1u32(colorA);
                i++;
                index += 2;
            }

            GXBegin(GX_TRIANGLES, GX_VTXFMT7, 3);
            i = static_cast<int>(vertexCount) - 1;
            while (i >= 0) {
                Vec* vertex = m_vertices + *reinterpret_cast<unsigned short*>(face + 0x48 + i * 2);
                GXPosition3f32(vertex->x, vertex->y, vertex->z);
                GXNormal3f32(*reinterpret_cast<float*>(face + 0x00), *reinterpret_cast<float*>(face + 0x04),
                             *reinterpret_cast<float*>(face + 0x08));
                GXColor1u32(colorB);
                i--;
            }
        }

        face += 0x50;
        faceIndex++;
    }

    GXClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);

    face = reinterpret_cast<unsigned char*>(m_faces);
    faceIndex = 0;
    while (faceIndex < m_faceCount) {
        CMapHitFace* hitFace = reinterpret_cast<CMapHitFace*>(face);
        if ((hitFace->m_drawFlags & 1) == 0) {
            hitFace->m_drawFlags = 0;
            face += 0x50;
            faceIndex++;
            continue;
        }

        hitFace->m_drawFlags = 0;
        hitFace->m_drawFlags = 0;

        const unsigned char vertexCount = face[0x46];

        GXBegin(GX_TRIANGLES, GX_VTXFMT7, 3);
        unsigned char* index = face + 0x48;
        int i = 0;
        while (i < static_cast<int>(vertexCount)) {
            Vec* vertex = m_vertices + *reinterpret_cast<unsigned short*>(index);
            GXPosition3f32(vertex->x, vertex->y, vertex->z);
            GXColor1u32(kOverlayColor);
            i++;
            index += 2;
        }

        GXBegin(GX_TRIANGLES, GX_VTXFMT7, 3);
        i = static_cast<int>(vertexCount) - 1;
        while (i >= 0) {
            Vec* vertex = m_vertices + *reinterpret_cast<unsigned short*>(face + 0x48 + i * 2);
            GXPosition3f32(vertex->x, vertex->y, vertex->z);
            GXColor1u32(kOverlayColor);
            i--;
        }

        face += 0x50;
        faceIndex++;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80024e64
 * PAL Size: 268b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapHit::DrawWire()
{
    static const u32 kFaceStride = 0x50;

    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);

    unsigned char* face = reinterpret_cast<unsigned char*>(m_faces);
    int faceIndex = 0;
    while (faceIndex < static_cast<int>(m_faceCount)) {
        GXBegin(static_cast<GXPrimitive>(0xB0), GX_VTXFMT7, static_cast<u16>(4));

        unsigned char* index = face;
        int i = 0;
        while (i < static_cast<int>(face[0x46])) {
            Vec* vertex = m_vertices + *reinterpret_cast<unsigned short*>(index + 0x48);
            GXPosition3f32(vertex->x, vertex->y, vertex->z);
            i++;
            index += sizeof(unsigned short);
        }

        const unsigned short firstIndex = *reinterpret_cast<unsigned short*>(face + 0x48);
        face += kFaceStride;
        faceIndex++;

        Vec* firstVertex = m_vertices + firstIndex;
        GXPosition3f32(firstVertex->x, firstVertex->y, firstVertex->z);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapHit::DrawNormal()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80026d38
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapHitFace::CMapHitFace()
{
    m_boundsMin.z = FLOAT_8032F8EC;
    m_boundsMin.y = FLOAT_8032F8EC;
    m_boundsMin.x = FLOAT_8032F8EC;

    m_boundsMax.z = FLOAT_8032F8F0;
    m_boundsMax.y = FLOAT_8032F8F0;
    m_boundsMax.x = FLOAT_8032F8F0;
}

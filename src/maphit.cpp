#include "ffcc/maphit.h"
#include "ffcc/chunkfile.h"
#include "ffcc/map.h"
#include "ffcc/memory.h"
#include "ffcc/system.h"

#include <math.h>

extern "C" const float FLOAT_8032F8EC;
extern "C" const float FLOAT_8032F8F0;
extern "C" const char s_old_mid_format_801D7094[];

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
float g_hit_edge_t;
float g_hit_t_min;
float g_hit_t;
unsigned char gMapHitFaceFlag;
CMapHitFace* g_hit_lpface;
CMapHitFace* g_hit_f;
float g_hit_t_slide_min;
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
    Vec axis = cyl.m_axis;
    const f32 axisLen = PSVECMag(&axis);
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

    Vec localDirection;
    localDirection.x = PSVECDotProduct(&orthogonal, &direction);
    localDirection.y = PSVECDotProduct(&bitangent, &direction);
    localDirection.z = PSVECDotProduct(&axis, &direction);

    const f32 directionLen = PSVECMag(&localDirection);
    const f32 tScale = 1.0f / directionLen;
    PSVECScale(&localDirection, &localDirection, tScale);

    Vec relStart;
    PSVECSubtract(&start, &cyl.m_bottom, &relStart);

    const f32 px = PSVECDotProduct(&orthogonal, &relStart);
    const f32 py = PSVECDotProduct(&bitangent, &relStart);
    const f32 pz = PSVECDotProduct(&axis, &relStart);

    const f32 vx = localDirection.x;
    const f32 vy = localDirection.y;
    const f32 vz = localDirection.z;
    const f32 radius = cyl.m_radius;
    const f32 radiusSq = radius * radius;

    if (fabsf(vz) < 1.0f) {
        const f32 radialC = (px * px + py * py) - radiusSq;
        const f32 radialB = px * vx + py * vy;
        const f32 radialA = vx * vx + vy * vy;
        f32 disc = radialB * radialB - radialA * radialC;
        if (disc < 0.0f) {
            return 0;
        }

        if (disc == 0.0f) {
            const f32 t = -radialB / radialA;
            const f32 z = (t * vz) + pz;
            if (0.0f <= z && z <= axisLen) {
                outT = t * tScale;
                if (0.0f <= outT && outT <= 1.0f) {
                    return 1;
                }
                return 0;
            }
        } else {
            disc = sqrtf(disc);
            const f32 t = (-radialB - disc) / radialA;
            const f32 z = (t * vz) + pz;
            if (0.0f <= z && z <= axisLen) {
                outT = t * tScale;
                if (0.0f <= outT && outT <= 1.0f) {
                    return 1;
                }
                return 0;
            }
        }

        if (g_hit_lpface->m_projectionAxis == 1) {
            f32 capC = (pz * pz) + radialC;
            f32 capB = (pz * vz) + radialB;
            disc = capB * capB - capC;
            if (disc == 0.0f) {
                const f32 t = -capB;
                if ((t * vz) + pz <= 0.0f) {
                    outT = t * tScale;
                    if (0.0f <= outT && outT <= 1.0f) {
                        return 1;
                    }
                    return 0;
                }
            } else if (disc > 0.0f) {
                disc = sqrtf(disc);
                f32 t = -capB - disc;
                if ((t * vz) + pz <= 0.0f) {
                    outT = t * tScale;
                    if (0.0f <= outT && outT <= 1.0f) {
                        return 1;
                    }
                    return 0;
                }

                t = -capB + disc;
                if ((t * vz) + pz <= 0.0f) {
                    outT = t * tScale;
                    if (0.0f <= outT && outT <= 1.0f) {
                        return 1;
                    }
                    return 0;
                }
            }

            capB = -((vz * axisLen) - capB);
            disc = capB * capB - (axisLen * -((2.0f * pz) - axisLen) + capC);
            if (disc == 0.0f) {
                const f32 t = -capB;
                if (axisLen <= (t * vz) + pz) {
                    outT = t * tScale;
                    if (0.0f <= outT && outT <= 1.0f) {
                        return 1;
                    }
                    return 0;
                }
            } else if (disc > 0.0f) {
                disc = sqrtf(disc);
                f32 t = -capB - disc;
                if (axisLen <= (t * vz) + pz) {
                    outT = t * tScale;
                    if (0.0f <= outT && outT <= 1.0f) {
                        return 1;
                    }
                    return 0;
                }

                t = -capB + disc;
                if (axisLen <= (t * vz) + pz) {
                    outT = t * tScale;
                    if (0.0f <= outT && outT <= 1.0f) {
                        return 1;
                    }
                    return 0;
                }
            }
        }

        return 0;
    }

    f32 disc = radiusSq - (px * px + py * py);
    if (disc < 0.0f) {
        return 0;
    }

    disc = sqrtf(disc);
    outT = (-(pz + disc)) * tScale;
    return 1;
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
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: 0x8002fed0
 * EN Size: 52b
 * JP Address: TODO
 * JP Size: TODO
 */
CMapCylinder::CMapCylinder()
{
    m_boundsMin.z = 0.0f;
    m_boundsMin.y = 0.0f;
    m_boundsMin.x = 0.0f;
    m_boundsMax.z = 1.0f;
    m_boundsMax.y = 1.0f;
    m_boundsMax.x = 1.0f;
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
    m_positionMin.z = FLOAT_8032F8EC;
    m_positionMin.y = FLOAT_8032F8EC;
    m_positionMin.x = FLOAT_8032F8EC;

    m_positionMax.z = FLOAT_8032F8F0;
    m_positionMax.y = FLOAT_8032F8F0;
    m_positionMax.x = FLOAT_8032F8F0;

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

    chunkFile.PushChunk();

    while (chunkFile.GetNextChunk(chunk)) {
        if (chunk.m_id == 'HITV') {
            m_vertexCount = static_cast<unsigned short>(chunk.m_arg0);
            m_vertices =
                new (*reinterpret_cast<CMemory::CStage**>(&MapMng), const_cast<char*>(s_maphit_cpp), 0x143)
                    Vec[m_vertexCount];

            for (unsigned int i = 0; i < m_vertexCount; i++) {
                Vec& v = m_vertices[i];
                v.x = chunkFile.GetF4();
                v.y = chunkFile.GetF4();
                v.z = chunkFile.GetF4();

                m_positionMin.x = (m_positionMin.x < v.x) ? m_positionMin.x : v.x;
                m_positionMin.y = (m_positionMin.y < v.y) ? m_positionMin.y : v.y;
                m_positionMin.z = (m_positionMin.z < v.z) ? m_positionMin.z : v.z;

                m_positionMax.x = (m_positionMax.x < v.x) ? v.x : m_positionMax.x;
                m_positionMax.y = (m_positionMax.y < v.y) ? v.y : m_positionMax.y;
                m_positionMax.z = (m_positionMax.z < v.z) ? v.z : m_positionMax.z;
            }

            m_positionMin.x -= 0.1f;
            m_positionMin.y -= 0.1f;
            m_positionMin.z -= 0.1f;
            m_positionMax.x += 0.1f;
            m_positionMax.y += 0.1f;
            m_positionMax.z += 0.1f;
        } else if (chunk.m_id == 'HITF') {
            m_faceCount = static_cast<unsigned short>(chunk.m_arg0);
            m_faces =
                new (*reinterpret_cast<CMemory::CStage**>(&MapMng), const_cast<char*>(s_maphit_cpp), 0x159)
                    CMapHitFace[m_faceCount];

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
                    if (System.m_execParam != 0) {
                        System.Printf(const_cast<char*>(s_old_mid_format_801D7094));
                    }
                    chunkFile.Align(4);
                    for (unsigned int i = 0; i < vertexCount; i++) {
                        (void)chunkFile.GetF4();
                        (void)chunkFile.GetF4();
                    }
                    face.m_radiusScale = 0.0f;
                } else if (chunk.m_version == 1) {
                    if (System.m_execParam != 0) {
                        System.Printf(const_cast<char*>(s_old_mid_format_801D7094));
                    }
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

                for (unsigned int i = 0; i < vertexCount; i++) {
                    const unsigned short idx = chunkFile.Get2();
                    face.m_vertexIndices[i] = idx;

                    const Vec& v = m_vertices[idx];
                    face.m_boundsMin.x = (face.m_boundsMin.x < v.x) ? face.m_boundsMin.x : v.x;
                    face.m_boundsMin.y = (face.m_boundsMin.y < v.y) ? face.m_boundsMin.y : v.y;
                    face.m_boundsMin.z = (face.m_boundsMin.z < v.z) ? face.m_boundsMin.z : v.z;

                    face.m_boundsMax.x = (face.m_boundsMax.x < v.x) ? v.x : face.m_boundsMax.x;
                    face.m_boundsMax.y = (face.m_boundsMax.y < v.y) ? v.y : face.m_boundsMax.y;
                    face.m_boundsMax.z = (face.m_boundsMax.z < v.z) ? v.z : face.m_boundsMax.z;
                }

                face.m_radiusScale *= 0.5f;
                face.m_boundsMin.x -= (0.1f + face.m_radiusScale);
                face.m_boundsMin.y -= (0.1f + face.m_radiusScale);
                face.m_boundsMin.z -= (0.1f + face.m_radiusScale);
                face.m_boundsMax.x += (0.1f + face.m_radiusScale);
                face.m_boundsMax.y += (0.1f + face.m_radiusScale);
                face.m_boundsMax.z += (0.1f + face.m_radiusScale);
                face.m_radiusScale = 1.0f - face.m_radiusScale;
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
    if (g_hit_cyl.m_boundsMin.x <= g_hit_lpface->m_boundsMin.x) {
        if (g_hit_lpface->m_boundsMin.x <= g_hit_cyl.m_boundsMin.x) {
            overlap = true;
        } else {
            overlap = g_hit_lpface->m_boundsMin.x <= g_hit_cyl.m_boundsMax.x;
        }
    } else {
        overlap = g_hit_cyl.m_boundsMin.x <= g_hit_lpface->m_boundsMax.x;
    }
    if (!overlap) {
        return 0;
    }

    overlap = false;
    if (g_hit_cyl.m_boundsMin.y <= g_hit_lpface->m_boundsMin.y) {
        if (g_hit_lpface->m_boundsMin.y <= g_hit_cyl.m_boundsMin.y) {
            overlap = true;
        } else {
            overlap = g_hit_lpface->m_boundsMin.y <= g_hit_cyl.m_boundsMax.y;
        }
    } else {
        overlap = g_hit_cyl.m_boundsMin.y <= g_hit_lpface->m_boundsMax.y;
    }
    if (!overlap) {
        return 0;
    }

    overlap = false;
    if (g_hit_cyl.m_boundsMin.z <= g_hit_lpface->m_boundsMin.z) {
        if (g_hit_lpface->m_boundsMin.z <= g_hit_cyl.m_boundsMin.z) {
            overlap = true;
        } else {
            overlap = g_hit_lpface->m_boundsMin.z <= g_hit_cyl.m_boundsMax.z;
        }
    } else {
        overlap = g_hit_cyl.m_boundsMin.z <= g_hit_lpface->m_boundsMax.z;
    }
    if (!overlap) {
        return 0;
    }

    Vec* normal = &g_hit_lpface->m_normal;
    Vec* hitDirection = &g_hit_cyl.m_axis;
    float dot = PSVECDotProduct(hitDirection, normal);
    if (dot >= 0.0f) {
        return 0;
    }

    float hitDot = PSVECDotProduct(&g_hit_cyl.m_bottom, normal);
    float hitT = -((hitDot - (g_hit_lpface->m_planeD + g_hit_cyl.m_radius)) / dot);
    int edgeIndex = -1;

    if (0.0f < hitT && hitT < g_hit_t_min) {
        PSVECScale(hitDirection, &g_hit_hpv, hitT);
        PSVECAdd(&g_hit_cyl.m_bottom, &g_hit_hpv, &g_hit_hpv);

        Vec pushedHit;
        PSVECScale(normal, &pushedHit, g_hit_cyl.m_radius);
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
                edgeCylinder.m_axis = edge;
                edgeCylinder.m_radius = g_hit_cyl.m_radius;

                if (FindIntersection(g_hit_cyl.m_bottom, *hitDirection, edgeCylinder, g_hit_edge_t) != 0 &&
                    g_hit_edge_t < g_hit_t_min) {
                    hitT = g_hit_edge_t;
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
    g_hit_edge_idx_min = edgeIndex;
    g_hit_f = g_hit_lpface;
    g_hit_cyl_min = g_hit_cyl;
    if (gMapHitDrawMode != 0) {
        g_hit_lpface->m_drawFlags = 1;
    }
    g_hit_mvec_min = g_hit_mvec;
    g_hit_hpv_min = g_hit_hpv;
    gMapHitFaceFlag = 1;
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
    if (g_hit_edge_idx_min != -1) {
        if (gMapHitFace->m_normal.y < y) {
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
            PSVECSubtract(&current, &g_hit_cyl_min.m_top, &edgeToCenter);

            float edgeDot = PSVECDotProduct(&edge, &edgeToCenter);
            float edgeLenSq = PSVECDotProduct(&edge, &edge);

            Vec edgeProjection;
            Vec nearestPoint;
            PSVECScale(&edge, &edgeProjection, edgeDot / edgeLenSq);
            PSVECSubtract(&current, &edgeProjection, &nearestPoint);

            Vec slideDir;
            PSVECSubtract(&g_hit_cyl_min.m_top, &nearestPoint, &slideDir);

            float side = PSVECDotProduct(&g_hit_cyl_min.m_axis, &slideDir);
            float slideLen = PSVECMag(&slideDir);
            if (s_epsilon <= slideLen) {
                PSVECScale(&slideDir, &slideDir, s_push / slideLen);
                if (side <= 0.0f) {
                    PSVECScale(&slideDir, &slideDir, 0.5f * g_hit_cyl_min.m_radius);
                } else {
                    PSVECScale(&slideDir, &slideDir, 0.5f * -g_hit_cyl_min.m_radius);
                }

                PSVECAdd(&nearestPoint, &slideDir, &nearestPoint);
                PSVECSubtract(&nearestPoint, &g_hit_cyl_min.m_bottom, out);
            } else {
                out->z = 0.0f;
                out->y = 0.0f;
                out->x = 0.0f;
            }

            return 1;
        }

        float len = PSVECMag(&g_hit_cyl_min.m_axis);
        PSVECScale(&g_hit_cyl_min.m_axis, out, g_hit_t - (s_push / len));
        return 0;
    }

    if (gMapHitFace->m_normal.y < y) {
        if (g_hit_t <= s_epsilon) {
            out->z = 0.0f;
            out->y = 0.0f;
            out->x = 0.0f;
            return 1;
        } else {
            Vec push;
            float planeDot = PSVECDotProduct(&g_hit_cyl_min.m_top, &gMapHitFace->m_normal);
            float planeError = -(planeDot - (gMapHitFace->m_planeD + g_hit_cyl_min.m_radius));
            PSVECScale(&gMapHitFace->m_normal, &push, s_push + planeError);
            PSVECAdd(&g_hit_cyl_min.m_top, &push, &push);
            PSVECSubtract(&push, &g_hit_cyl_min.m_bottom, out);
            return 1;
        }
    }

    float len = PSVECMag(&g_hit_cyl_min.m_axis);
    PSVECScale(&g_hit_cyl_min.m_axis, out, g_hit_t - (s_push / len));
    return 0;
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
        float len = PSVECMag(&g_hit_cyl_min.m_axis);
        PSVECScale(&g_hit_cyl_min.m_axis, position, g_hit_t - (s_epsilon / len));
        PSVECAdd(&g_hit_cyl_min.m_bottom, position, position);
    } else {
        float len = PSVECMag(&g_hit_cyl_min.m_axis);
        PSVECScale(&g_hit_cyl_min.m_axis, position, g_hit_t - (s_push / len));
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

    int faceOffset = 0;
    for (int i = 0; i < m_faceCount; i++) {
        g_hit_lpface = reinterpret_cast<CMapHitFace*>(Ptr(m_faces, faceOffset));
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

    int endFace = static_cast<unsigned short>(startFace + faceCount);
    int faceIndex = static_cast<unsigned short>(startFace);
    int faceOffset = faceIndex * 0x50;

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
            const unsigned char groupIndex = face[0x47];
            unsigned char* mapMngBytes = reinterpret_cast<unsigned char*>(&MapMng);
            const u32 colorA = *reinterpret_cast<u32*>(mapMngBytes + 0x214E8 + groupIndex * 0x14 + 0x4);
            const u32 colorB = *reinterpret_cast<u32*>(mapMngBytes + 0x214E8 + groupIndex * 0x14 + 0x8);
            const GXColor* colorABytes = reinterpret_cast<const GXColor*>(&colorA);
            const GXColor* colorBBytes = reinterpret_cast<const GXColor*>(&colorB);

            GXBegin(GX_TRIANGLES, GX_VTXFMT7, 3);
            unsigned char* index = face + 0x48;
            int i = 0;
            while (i < static_cast<int>(face[0x46])) {
                Vec* vertex = m_vertices + *reinterpret_cast<unsigned short*>(index);
                GXPosition3f32(vertex->x, vertex->y, vertex->z);
                GXNormal3f32(*reinterpret_cast<float*>(face + 0x00), *reinterpret_cast<float*>(face + 0x04),
                             *reinterpret_cast<float*>(face + 0x08));
                GXColor4u8(colorABytes->r, colorABytes->g, colorABytes->b, colorABytes->a);
                i++;
                index += 2;
            }

            GXBegin(GX_TRIANGLES, GX_VTXFMT7, 3);
            i = static_cast<int>(face[0x46]) - 1;
            while (i >= 0) {
                Vec* vertex = m_vertices + *reinterpret_cast<unsigned short*>(face + 0x48 + i * 2);
                GXPosition3f32(vertex->x, vertex->y, vertex->z);
                GXNormal3f32(*reinterpret_cast<float*>(face + 0x00), *reinterpret_cast<float*>(face + 0x04),
                             *reinterpret_cast<float*>(face + 0x08));
                GXColor4u8(colorBBytes->r, colorBBytes->g, colorBBytes->b, colorBBytes->a);
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
    while (true) {
        if (static_cast<int>(m_faceCount) <= faceIndex) {
            return;
        }

        CMapHitFace* hitFace = reinterpret_cast<CMapHitFace*>(face);
        if ((hitFace->m_drawFlags & 1) == 0) {
            hitFace->m_drawFlags = 0;
        } else {
            hitFace->m_drawFlags = 0;
            hitFace->m_drawFlags = 0;

            GXBegin(GX_TRIANGLES, GX_VTXFMT7, 3);
            unsigned char* index = face + 0x48;
            int i = 0;
            while (i < static_cast<int>(face[0x46])) {
                Vec* vertex = m_vertices + *reinterpret_cast<unsigned short*>(index);
                GXPosition3f32(vertex->x, vertex->y, vertex->z);
                GXColor4u8(0x40, 0xFF, 0x40, 0xFF);
                i++;
                index += 2;
            }

            GXBegin(GX_TRIANGLES, GX_VTXFMT7, 3);
            i = static_cast<int>(face[0x46]) - 1;
            while (i >= 0) {
                Vec* vertex = m_vertices + *reinterpret_cast<unsigned short*>(face + 0x48 + i * 2);
                GXPosition3f32(vertex->x, vertex->y, vertex->z);
                GXColor4u8(0x40, 0xFF, 0x40, 0xFF);
                i--;
            }
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

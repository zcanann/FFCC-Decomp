#include "ffcc/maphit.h"
#include "ffcc/chunkfile.h"
#include "ffcc/map.h"
#include "ffcc/memory.h"
#include "ffcc/system.h"

#include <math.h>

extern CMapCylinder g_hit_cyl;
extern CMapCylinder g_hit_cyl_min;
extern Vec g_hit_mvec;

namespace {
static char s_maphit_cpp[] = "maphit.cpp";
static const float s_large_pos = 3.4e38f;
static const float s_large_neg = -3.4e38f;
static const float s_epsilon = 0.0001f;
static const float s_push = 0.01f;

static CMapHitFace* s_hit_face_min = 0;
static int s_hit_edge_index = -1;
static float s_hit_t_min = s_large_pos;

static inline unsigned char* Ptr(void* p, unsigned int offset)
{
    return reinterpret_cast<unsigned char*>(p) + offset;
}
}

/*
 * --INFO--
 * PAL Address: 0x80026e24
 * PAL Size: 2308b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void FindIntersection(const Vec& start, const Vec& direction, const CMapCylinder& cyl, float& outT)
{
    outT = -1.0f;

    Vec axis = cyl.m_direction2;
    f32 axisLen = PSVECMag(&axis);
    if (axisLen <= 0.0f) {
        return;
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
 * Address:	TODO
 * Size:	TODO
 */
CMapCylinder::CMapCylinder()
{
	// TODO
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
        delete[] m_vertices;
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
 * PAL Address: 0x80026d5c
 * PAL Size: 144b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CMapHit* dtor_80026D5C(CMapHit* mapHit, short shouldDelete)
{
    if (mapHit != 0) {
        if (mapHit->m_vertices != 0) {
            delete[] mapHit->m_vertices;
            mapHit->m_vertices = 0;
        }

        if (mapHit->m_faces != 0) {
            delete[] mapHit->m_faces;
            mapHit->m_faces = 0;
        }

        mapHit->m_vertexCount = 0;
        mapHit->m_faceCount = 0;

        if (shouldDelete > 0) {
            operator delete(mapHit);
        }
    }

    return mapHit;
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
            m_vertices = new (stage, s_maphit_cpp, 0x143) Vec[m_vertexCount];

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
            m_faces = new (stage, s_maphit_cpp, 0x159) CMapHitFace[m_faceCount];

            for (unsigned int faceIdx = 0; faceIdx < m_faceCount; faceIdx++) {
                chunkFile.Align(4);

                unsigned char* face = Ptr(&m_faces[faceIdx], 0);
                float* nrm = reinterpret_cast<float*>(face + 0x00);

                nrm[0] = chunkFile.GetF4();
                nrm[1] = chunkFile.GetF4();
                nrm[2] = chunkFile.GetF4();
                nrm[3] = chunkFile.GetF4();

                face[0x44] = chunkFile.Get1();
                face[0x45] = chunkFile.Get1();
                face[0x46] = chunkFile.Get1();
                face[0x47] = chunkFile.Get1();
                face[0x4E] = 0;
                face[0x4F] = 0;

                const unsigned int vertexCount = face[0x46];
                for (unsigned int i = 0; i < vertexCount; i++) {
                    *reinterpret_cast<float*>(face + 0x2C + i * 8 + 0) = 0.0f;
                    *reinterpret_cast<float*>(face + 0x2C + i * 8 + 4) = 0.0f;
                }

                if (chunk.m_version == 0) {
                    chunkFile.Align(4);
                    for (unsigned int i = 0; i < vertexCount; i++) {
                        (void)chunkFile.GetF4();
                        (void)chunkFile.GetF4();
                    }
                    *reinterpret_cast<float*>(face + 0x28) = 0.0f;
                } else if (chunk.m_version == 1) {
                    *reinterpret_cast<float*>(face + 0x28) = chunkFile.GetF4();
                    chunkFile.Align(4);
                } else {
                    *reinterpret_cast<float*>(face + 0x28) = chunkFile.GetF4();
                    chunkFile.Align(4);
                    for (unsigned int i = 0; i < vertexCount; i++) {
                        *reinterpret_cast<float*>(face + 0x2C + i * 8 + 0) = chunkFile.GetF4() * 0.01f;
                        *reinterpret_cast<float*>(face + 0x2C + i * 8 + 4) = chunkFile.GetF4() * 0.01f;
                    }
                }

                float* boundsMin = reinterpret_cast<float*>(face + 0x10);
                float* boundsMax = reinterpret_cast<float*>(face + 0x1C);
                boundsMin[0] = s_large_pos;
                boundsMin[1] = s_large_pos;
                boundsMin[2] = s_large_pos;
                boundsMax[0] = s_large_neg;
                boundsMax[1] = s_large_neg;
                boundsMax[2] = s_large_neg;

                for (unsigned int i = 0; i < vertexCount; i++) {
                    const unsigned short idx = chunkFile.Get2();
                    *reinterpret_cast<unsigned short*>(face + 0x48 + i * 2) = idx;

                    const Vec& v = m_vertices[idx];
                    if (v.x < boundsMin[0]) {
                        boundsMin[0] = v.x;
                    }
                    if (v.y < boundsMin[1]) {
                        boundsMin[1] = v.y;
                    }
                    if (v.z < boundsMin[2]) {
                        boundsMin[2] = v.z;
                    }

                    if (boundsMax[0] < v.x) {
                        boundsMax[0] = v.x;
                    }
                    if (boundsMax[1] < v.y) {
                        boundsMax[1] = v.y;
                    }
                    if (boundsMax[2] < v.z) {
                        boundsMax[2] = v.z;
                    }
                }

                float width = *reinterpret_cast<float*>(face + 0x28) * 0.5f;
                boundsMin[0] -= (0.1f + width);
                boundsMin[1] -= (0.1f + width);
                boundsMin[2] -= (0.1f + width);
                boundsMax[0] += (0.1f + width);
                boundsMax[1] += (0.1f + width);
                boundsMax[2] += (0.1f + width);
                *reinterpret_cast<float*>(face + 0x28) = 1.0f - width;
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
    for (int faceIndex = 0; faceIndex < m_faceCount; faceIndex++) {
        unsigned char* face = Ptr(m_faces, faceIndex * 0x98);
        unsigned char groupIndex = face[0x47];
        unsigned char* mapMngBytes = reinterpret_cast<unsigned char*>(&MapMng);
        unsigned long groupMask = *reinterpret_cast<unsigned long*>(mapMngBytes + 0x214E8 + groupIndex * 0x14);
        if ((groupMask & mask) == 0) {
            continue;
        }

        float* boundsMin = reinterpret_cast<float*>(face + 0x10);
        float* boundsMax = reinterpret_cast<float*>(face + 0x1C);
        if (g_hit_cyl.m_direction2.z < boundsMin[0] || boundsMax[0] < g_hit_cyl.m_top.z) {
            continue;
        }
        if (g_hit_cyl.m_radius2 < boundsMin[1] || boundsMax[1] < g_hit_cyl.m_direction2.x) {
            continue;
        }
        if (g_hit_cyl.m_height2 < boundsMin[2] || boundsMax[2] < g_hit_cyl.m_direction2.y) {
            continue;
        }

        Vec* normal = reinterpret_cast<Vec*>(face + 0x00);
        Vec* hitDirection = reinterpret_cast<Vec*>(&g_hit_cyl.m_radius);
        float dot = PSVECDotProduct(hitDirection, normal);
        if (dot >= 0.0f) {
            continue;
        }

        float hitT;
        float planeD = *reinterpret_cast<float*>(face + 0x0C);
        float topY = g_hit_cyl.m_top.y;
        float hitDot = PSVECDotProduct(&g_hit_cyl.m_bottom, normal);
        hitT = -((hitDot - (planeD + topY)) / dot);
        if (hitT < 0.0f || s_hit_t_min <= hitT) {
            continue;
        }

        s_hit_t_min = hitT;
        s_hit_face_min = reinterpret_cast<CMapHitFace*>(face);
        s_hit_edge_index = -1;
        g_hit_cyl_min = g_hit_cyl;
        return 1;
    }

    return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapCylinder::operator= (const CMapCylinder& other)
{
    m_bottom = other.m_bottom;
    m_direction = other.m_direction;
    m_radius = other.m_radius;
    m_height = other.m_height;
    m_top = other.m_top;
    m_direction2 = other.m_direction2;
    m_radius2 = other.m_radius2;
    m_height2 = other.m_height2;
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
    float* const normal = reinterpret_cast<float*>(s_hit_face_min);
    out->x = normal[0];
    out->y = normal[1];
    out->z = normal[2];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapHit::CalcHitSlide(Vec* out, float y)
{
    if (s_hit_edge_index == -1) {
        if (s_hit_face_min != 0 && y <= s_hit_face_min->m_boundsMin.y) {
            float len = PSVECMag(&g_hit_cyl_min.m_direction);
            if (len > s_epsilon) {
                PSVECScale(&g_hit_cyl_min.m_direction, out, s_hit_t_min - (s_push / len));
            } else {
                out->x = 0.0f;
                out->y = 0.0f;
                out->z = 0.0f;
            }
            return;
        }
    }

    out->x = 0.0f;
    out->y = 0.0f;
    out->z = 0.0f;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapHit::CalcHitPosition(Vec* position)
{
    float len = PSVECMag(&g_hit_cyl_min.m_direction);
    if (s_hit_edge_index == -1) {
        PSVECScale(&g_hit_cyl_min.m_direction, position, s_hit_t_min - (s_push / len));
    } else {
        PSVECScale(&g_hit_cyl_min.m_direction, position, s_hit_t_min - (s_epsilon / len));
    }
    PSVECAdd(&g_hit_cyl_min.m_bottom, position, position);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMapHit::CheckHitCylinder(CMapCylinder* mapCylinder, Vec* position, unsigned long mask)
{
    (void)position;

    g_hit_cyl = *mapCylinder;
    s_hit_t_min = s_large_pos;
    s_hit_face_min = 0;
    s_hit_edge_index = -1;

    return CheckHitFaceCylinder(mask);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMapHit::CheckHitCylinder(CMapCylinder* mapCylinder, Vec* position, unsigned short startFace, unsigned short faceCount, unsigned long mask)
{
    (void)position;

    const unsigned int start = static_cast<unsigned int>(startFace);
    const unsigned int end = start + static_cast<unsigned int>(faceCount);
    if (start >= static_cast<unsigned int>(m_faceCount)) {
        return 0;
    }

    g_hit_cyl = *mapCylinder;
    s_hit_t_min = s_large_pos;
    s_hit_face_min = 0;
    s_hit_edge_index = -1;

    CMapHitFace* savedFaces = m_faces;
    const unsigned short savedFaceCount = m_faceCount;
    m_faces = reinterpret_cast<CMapHitFace*>(Ptr(m_faces, start * 0x98));
    if (end >= static_cast<unsigned int>(savedFaceCount)) {
        m_faceCount = static_cast<unsigned short>(savedFaceCount - start);
    } else {
        m_faceCount = static_cast<unsigned short>(faceCount);
    }

    const int hit = CheckHitFaceCylinder(mask);
    m_faces = savedFaces;
    m_faceCount = savedFaceCount;
    return hit;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMapHit::CheckHitCylinderNear(CMapCylinder* mapCylinder, Vec* position, unsigned long mask)
{
    g_hit_cyl = *mapCylinder;
    g_hit_mvec = *position;
    s_hit_t_min = s_large_pos;
    s_hit_face_min = 0;
    s_hit_edge_index = -1;

    return CheckHitFaceCylinder(mask);
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

    CMapHitFace* savedFaces = m_faces;
    unsigned short savedFaceCount = m_faceCount;
    while (faceIndex < endFace) {
        m_faces = reinterpret_cast<CMapHitFace*>(Ptr(savedFaces, faceOffset));
        m_faceCount = 1;
        CheckHitFaceCylinder(mask);
        faceOffset += 0x50;
        faceIndex++;
    }

    m_faces = savedFaces;
    m_faceCount = savedFaceCount;
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
    static const u32 kFaceStride = 0x50;
    unsigned char* mapMngBytes = reinterpret_cast<unsigned char*>(&MapMng);

    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_NRM, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);

    for (int faceIndex = 0; faceIndex < m_faceCount; ++faceIndex) {
        unsigned char* face = Ptr(m_faces, faceIndex * kFaceStride);
        if ((face[0x4B] & 1) != 0) {
            continue;
        }

        const unsigned char vertexCount = face[0x46];
        const float nx = *reinterpret_cast<float*>(face + 0x00);
        const float ny = *reinterpret_cast<float*>(face + 0x04);
        const float nz = *reinterpret_cast<float*>(face + 0x08);
        const unsigned char groupIndex = face[0x47];
        const u32 colorA = *reinterpret_cast<u32*>(mapMngBytes + 0x214E8 + groupIndex * 0x14 + 0x4);
        const u32 colorB = *reinterpret_cast<u32*>(mapMngBytes + 0x214E8 + groupIndex * 0x14 + 0x8);

        GXBegin(GX_TRIANGLES, GX_VTXFMT7, 3);
        const unsigned short* index = reinterpret_cast<unsigned short*>(face + 0x48);
        for (int i = 0; i < vertexCount; ++i) {
            Vec* vertex = m_vertices + *index;
            GXPosition3f32(vertex->x, vertex->y, vertex->z);
            GXNormal3f32(nx, ny, nz);
            GXColor1u32(colorA);
            index++;
        }

        GXBegin(GX_TRIANGLES, GX_VTXFMT7, 3);
        const unsigned short* reverse = reinterpret_cast<unsigned short*>(face + 0x48 + (vertexCount - 1) * 2);
        for (int i = vertexCount - 1; i >= 0; --i) {
            Vec* vertex = m_vertices + *reverse;
            GXPosition3f32(vertex->x, vertex->y, vertex->z);
            GXNormal3f32(nx, ny, nz);
            GXColor1u32(colorB);
            reverse--;
        }
    }

    GXClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);

    for (int faceIndex = 0; faceIndex < m_faceCount; ++faceIndex) {
        unsigned char* face = Ptr(m_faces, faceIndex * kFaceStride);
        if ((face[0x4B] & 1) == 0) {
            face[0x4B] = 0;
            continue;
        }

        face[0x4B] = 0;
        face[0x4B] = 0;

        const unsigned char vertexCount = face[0x46];
        GXBegin(GX_TRIANGLES, GX_VTXFMT7, 3);
        const unsigned short* index = reinterpret_cast<unsigned short*>(face + 0x48);
        for (int i = 0; i < vertexCount; ++i) {
            Vec* vertex = m_vertices + *index;
            GXPosition3f32(vertex->x, vertex->y, vertex->z);
            GXColor1u32(kOverlayColor);
            index++;
        }

        GXBegin(GX_TRIANGLES, GX_VTXFMT7, 3);
        const unsigned short* reverse = reinterpret_cast<unsigned short*>(face + 0x48 + (vertexCount - 1) * 2);
        for (int i = vertexCount - 1; i >= 0; --i) {
            Vec* vertex = m_vertices + *reverse;
            GXPosition3f32(vertex->x, vertex->y, vertex->z);
            GXColor1u32(kOverlayColor);
            reverse--;
        }
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
    m_boundsMin.z = 0.0f;
    m_boundsMin.y = 0.0f;
    m_boundsMin.x = 0.0f;

    m_boundsMax.z = 1.0f;
    m_boundsMax.y = 1.0f;
    m_boundsMax.x = 1.0f;
}

/*
 * --INFO--
 * PAL Address: 0x80027728
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_maphit_cpp()
{
    g_hit_cyl.m_direction2.y = 0.0f;
    g_hit_cyl.m_direction2.x = 0.0f;
    g_hit_cyl.m_top.z = 0.0f;
    g_hit_cyl.m_height2 = 1.0f;
    g_hit_cyl.m_radius2 = 1.0f;
    g_hit_cyl.m_direction2.z = 1.0f;

    g_hit_cyl_min.m_direction2.y = 0.0f;
    g_hit_cyl_min.m_direction2.x = 0.0f;
    g_hit_cyl_min.m_top.z = 0.0f;
    g_hit_cyl_min.m_height2 = 1.0f;
    g_hit_cyl_min.m_radius2 = 1.0f;
    g_hit_cyl_min.m_direction2.z = 1.0f;
}

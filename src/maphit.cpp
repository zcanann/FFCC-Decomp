#include "ffcc/maphit.h"
#include "ffcc/chunkfile.h"
#include "ffcc/map.h"
#include "ffcc/memory.h"
#include "ffcc/system.h"

#include <math.h>

extern "C" const float kMapHitBoundsMinInit;
extern "C" const float kMapHitBoundsMaxInit;
extern "C" const float kMapHitInitialTMin;
extern "C" const float kMapHitEdgeBackoff;
extern "C" const float kMapHitFaceBackoff;
extern "C" const float kMapHitUnitScale;
extern "C" const float kMapHitZero;
extern "C" const float kMapHitRadiusSlideScale;
extern "C" const float kMapHitSlideTLimit;
extern "C" const double kMapHitEdgeMaxT;
extern "C" const float kMapHitEdgeMinT;
extern "C" const float kMapHitVertexOffsetScale;
extern "C" const float kMapHitRadiusScale;
extern "C" const double kMapHitRadiusBase;
extern "C" const char sOldMidFormat[];

CMapCylinder g_hit_cyl;
CMapCylinder g_hit_cyl_min;
Vec g_hit_mvec;
Vec g_hit_mvec_min;
Vec g_hit_hpv;
Vec g_hit_hpv_min;

namespace {
static inline unsigned char* Ptr(void* p, unsigned int offset)
{
    return reinterpret_cast<unsigned char*>(p) + offset;
}
}

extern const char s_maphit_cpp[] = "maphit.cpp";

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
 * Address:	TODO
 * Size:	TODO
 */
void CMapHit::DrawNormal()
{
	// TODO
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
            const CMapIdGrp* mapIdGrp = MapMng.GetMapIdGrpArray() + groupIndex;
            const GXColor colorABytes = *reinterpret_cast<const GXColor*>(&mapIdGrp->m_primaryColor);
            const GXColor colorBBytes = *reinterpret_cast<const GXColor*>(&mapIdGrp->m_secondaryColor);

            GXBegin(GX_TRIANGLES, GX_VTXFMT7, 3);
            unsigned char* index = face + 0x48;
            int i = 0;
            while (i < static_cast<int>(face[0x46])) {
                Vec* vertex = m_vertices + *reinterpret_cast<unsigned short*>(index);
                GXPosition3f32(vertex->x, vertex->y, vertex->z);
                GXNormal3f32(*reinterpret_cast<float*>(face + 0x00), *reinterpret_cast<float*>(face + 0x04),
                             *reinterpret_cast<float*>(face + 0x08));
                GXColor4u8(colorABytes.r, colorABytes.g, colorABytes.b, colorABytes.a);
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
                GXColor4u8(colorBBytes.r, colorBBytes.g, colorBBytes.b, colorBBytes.a);
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
    while (faceIndex < static_cast<int>(m_faceCount)) {
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
 * PAL Address: 0x800254d0
 * PAL Size: 268b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapHit::CheckHitCylinderNear(CMapCylinder* mapCylinder, Vec* position, unsigned short startFace, unsigned short faceCount, unsigned long mask)
{
    unsigned int faceIndex = startFace;
    unsigned int faceOffset = faceIndex * sizeof(CMapHitFace);
    int endFace = static_cast<unsigned short>(faceCount + startFace);

    g_hit_cyl = *mapCylinder;
    g_hit_mvec = *position;

    while (static_cast<int>(faceIndex) < endFace) {
        g_hit_lpface = reinterpret_cast<CMapHitFace*>(Ptr(m_faces, faceOffset));
        CheckHitFaceCylinder(mask);
        faceOffset += sizeof(CMapHitFace);
        faceIndex++;
    }
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
 * Address:	TODO
 * Size:	TODO
 */
int CMapHit::CheckHitCylinder(CMapCylinder* mapCylinder, Vec* position, unsigned short startFace, unsigned short faceCount, unsigned long mask)
{
    unsigned int faceIndex = startFace;
    unsigned int faceOffset = faceIndex * sizeof(CMapHitFace);
    int endFace = static_cast<unsigned short>(faceCount + startFace);

    g_hit_cyl = *mapCylinder;
    g_hit_mvec = *position;

    while (static_cast<int>(faceIndex) < endFace) {
        g_hit_lpface = reinterpret_cast<CMapHitFace*>(Ptr(m_faces, faceOffset));
        g_hit_t_min = kMapHitInitialTMin;

        if (CheckHitFaceCylinder(mask) != 0) {
            return 1;
        }

        faceOffset += sizeof(CMapHitFace);
        faceIndex++;
    }

    return 0;
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

    int faceOffset = 0;
    int faceIndex = 0;
    while (faceIndex < static_cast<int>(m_faceCount)) {
        g_hit_lpface = reinterpret_cast<CMapHitFace*>(Ptr(m_faces, faceOffset));
        g_hit_t_min = kMapHitInitialTMin;
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
        PSVECScale(&g_hit_cyl_min.m_axis, position, g_hit_t - (kMapHitEdgeBackoff / len));
        PSVECAdd(&g_hit_cyl_min.m_bottom, position, position);
    } else {
        float len = PSVECMag(&g_hit_cyl_min.m_axis);
        PSVECScale(&g_hit_cyl_min.m_axis, position, g_hit_t - (kMapHitFaceBackoff / len));
        PSVECAdd(&g_hit_cyl_min.m_bottom, position, position);
    }
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
        CMapHitFace* face = gMapHitFace;
        if (face->m_normal.y < y) {
            Vec previous;
            Vec current;
            if (g_hit_edge_idx_min == 0) {
                previous = m_vertices[face->m_vertexIndices[face->m_vertexCount - 1]];
                current = m_vertices[face->m_vertexIndices[g_hit_edge_idx_min]];
            } else {
                previous = m_vertices[face->m_vertexIndices[g_hit_edge_idx_min - 1]];
                current = m_vertices[face->m_vertexIndices[g_hit_edge_idx_min]];
            }

            Vec edge;
            Vec nearestPoint;
            Vec edgeToCenter;
            Vec edgeProjection;
            PSVECSubtract(&current, &previous, &edge);
            PSVECSubtract(&current, &g_hit_cyl_min.m_top, &edgeToCenter);

            float edgeDot = PSVECDotProduct(&edge, &edgeToCenter);
            float edgeLenSq = PSVECDotProduct(&edge, &edge);

            PSVECScale(&edge, &edgeProjection, edgeDot / edgeLenSq);
            PSVECSubtract(&current, &edgeProjection, &nearestPoint);

            Vec slideDir;
            PSVECSubtract(&g_hit_cyl_min.m_top, &nearestPoint, &slideDir);

            float side = PSVECDotProduct(&g_hit_cyl_min.m_axis, &slideDir);
            float slideLen = PSVECMag(&slideDir);
            if (slideLen >= kMapHitEdgeBackoff) {
                PSVECScale(&slideDir, &slideDir, kMapHitUnitScale / slideLen);
                if (side <= kMapHitZero) {
                    PSVECScale(&slideDir, &slideDir, kMapHitRadiusSlideScale * g_hit_cyl_min.m_radius);
                } else {
                    PSVECScale(&slideDir, &slideDir, kMapHitRadiusSlideScale * -g_hit_cyl_min.m_radius);
                }

                PSVECAdd(&nearestPoint, &slideDir, &nearestPoint);
                PSVECSubtract(&nearestPoint, &g_hit_cyl_min.m_bottom, out);
            } else {
                out->z = kMapHitZero;
                out->y = kMapHitZero;
                out->x = kMapHitZero;
            }

            return 1;
        }

        float len = PSVECMag(&g_hit_cyl_min.m_axis);
        PSVECScale(&g_hit_cyl_min.m_axis, out, g_hit_t - (kMapHitFaceBackoff / len));
        return 0;
    }

    if (gMapHitFace->m_normal.y < y) {
        if (g_hit_t <= kMapHitSlideTLimit) {
            out->z = kMapHitZero;
            out->y = kMapHitZero;
            out->x = kMapHitZero;
            return 1;
        } else {
            Vec push;
            float planeDot = PSVECDotProduct(&g_hit_cyl_min.m_top, &gMapHitFace->m_normal);
            float planeError = -(planeDot - (gMapHitFace->m_planeD + g_hit_cyl_min.m_radius));
            PSVECScale(&gMapHitFace->m_normal, &push, kMapHitFaceBackoff + planeError);
            PSVECAdd(&g_hit_cyl_min.m_top, &push, &push);
            PSVECSubtract(&push, &g_hit_cyl_min.m_bottom, out);
            return 1;
        }
    }

    float len = PSVECMag(&g_hit_cyl_min.m_axis);
    PSVECScale(&g_hit_cyl_min.m_axis, out, g_hit_t - (kMapHitFaceBackoff / len));
    return 0;
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
 * PAL Address: 0x80025df4
 * PAL Size: 2300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMapHit::CheckHitFaceCylinder(unsigned long mask)
{
    unsigned long groupMask = MapMng.GetMapIdGrpArray()[g_hit_lpface->m_groupIndex].m_mask;
    if ((groupMask & mask) == 0) {
        return 0;
    }

    bool boundsOverlap = false;
    bool partialOverlap = false;
    bool axisOverlap;
    if (g_hit_lpface->m_boundsMin.x < g_hit_cyl.m_boundsMin.x) {
        axisOverlap = g_hit_cyl.m_boundsMin.x <= g_hit_lpface->m_boundsMax.x;
    } else {
        axisOverlap = g_hit_lpface->m_boundsMin.x <= g_hit_cyl.m_boundsMax.x;
    }

    if (axisOverlap) {
        if (g_hit_lpface->m_boundsMin.y < g_hit_cyl.m_boundsMin.y) {
            axisOverlap = g_hit_cyl.m_boundsMin.y <= g_hit_lpface->m_boundsMax.y;
        } else {
            axisOverlap = g_hit_lpface->m_boundsMin.y <= g_hit_cyl.m_boundsMax.y;
        }

        if (axisOverlap) {
            partialOverlap = true;
        }
    }

    if (partialOverlap) {
        if (g_hit_lpface->m_boundsMin.z < g_hit_cyl.m_boundsMin.z) {
            axisOverlap = g_hit_cyl.m_boundsMin.z <= g_hit_lpface->m_boundsMax.z;
        } else {
            axisOverlap = g_hit_lpface->m_boundsMin.z <= g_hit_cyl.m_boundsMax.z;
        }

        if (axisOverlap) {
            boundsOverlap = true;
        }
    }

    if (!boundsOverlap) {
        return 0;
    }

    Vec* normal = &g_hit_lpface->m_normal;
    Vec* hitDirection = &g_hit_cyl.m_axis;
    float dot = PSVECDotProduct(hitDirection, normal);
    if (dot >= kMapHitZero) {
        return 0;
    }

    float hitDot = PSVECDotProduct(&g_hit_cyl.m_bottom, normal);
    g_hit_edge_t = -((hitDot - (g_hit_lpface->m_planeD + g_hit_cyl.m_radius)) / dot);
    int edgeIndex = -1;

    if (g_hit_edge_t > kMapHitEdgeMaxT) {
        return 0;
    }

    if (!(g_hit_edge_t < kMapHitEdgeMinT) && g_hit_edge_t < g_hit_t_min) {
        PSVECScale(hitDirection, &g_hit_hpv, g_hit_edge_t);
        PSVECAdd(&g_hit_cyl.m_bottom, &g_hit_hpv, &g_hit_hpv);

        Vec pushedHit;
        PSVECScale(normal, &pushedHit, g_hit_cyl.m_radius);
        PSVECSubtract(&g_hit_hpv, &pushedHit, &pushedHit);

        unsigned int sideMask = 3;
        Vec previous = m_vertices[g_hit_lpface->m_vertexIndices[g_hit_lpface->m_vertexCount - 1]];
        Vec current;
        Vec edgeStart;
        Vec edgeEnd;
        Vec point;
        Vec edge;
        Vec toPoint;
        Vec cross;
        if (g_hit_lpface->m_projectionAxis == 1) {
            point.x = pushedHit.x;
            point.y = pushedHit.z;
            point.z = kMapHitZero;

            for (int i = 0; i < static_cast<int>(g_hit_lpface->m_vertexCount); i++) {
                current = m_vertices[g_hit_lpface->m_vertexIndices[i]];
                edgeStart.x = previous.x + g_hit_lpface->m_vertexOffsets[i][0];
                edgeStart.y = previous.z + g_hit_lpface->m_vertexOffsets[i][1];
                edgeStart.z = kMapHitZero;
                edgeEnd.x = current.x + g_hit_lpface->m_vertexOffsets[i][0];
                edgeEnd.y = current.z + g_hit_lpface->m_vertexOffsets[i][1];
                edgeEnd.z = kMapHitZero;

                PSVECSubtract(&edgeEnd, &edgeStart, &edge);
                PSVECSubtract(&point, &edgeEnd, &toPoint);
                PSVECCrossProduct(&edge, &toPoint, &cross);
                if (cross.z < kMapHitZero) {
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
        } else if (g_hit_lpface->m_projectionAxis == 0) {
            point.x = pushedHit.y;
            point.y = pushedHit.z;
            point.z = kMapHitZero;

            for (int i = 0; i < static_cast<int>(g_hit_lpface->m_vertexCount); i++) {
                current = m_vertices[g_hit_lpface->m_vertexIndices[i]];
                edgeStart.x = previous.y + g_hit_lpface->m_vertexOffsets[i][0];
                edgeStart.y = previous.z + g_hit_lpface->m_vertexOffsets[i][1];
                edgeStart.z = kMapHitZero;
                edgeEnd.x = current.y + g_hit_lpface->m_vertexOffsets[i][0];
                edgeEnd.y = current.z + g_hit_lpface->m_vertexOffsets[i][1];
                edgeEnd.z = kMapHitZero;

                PSVECSubtract(&edgeEnd, &edgeStart, &edge);
                PSVECSubtract(&point, &edgeEnd, &toPoint);
                PSVECCrossProduct(&edge, &toPoint, &cross);
                if (cross.z < kMapHitZero) {
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
        } else if (g_hit_lpface->m_projectionAxis < 3) {
            point.x = pushedHit.x;
            point.y = pushedHit.y;
            point.z = kMapHitZero;

            for (int i = 0; i < static_cast<int>(g_hit_lpface->m_vertexCount); i++) {
                current = m_vertices[g_hit_lpface->m_vertexIndices[i]];
                edgeStart.x = previous.x + g_hit_lpface->m_vertexOffsets[i][0];
                edgeStart.y = previous.y + g_hit_lpface->m_vertexOffsets[i][1];
                edgeStart.z = kMapHitZero;
                edgeEnd.x = current.x + g_hit_lpface->m_vertexOffsets[i][0];
                edgeEnd.y = current.y + g_hit_lpface->m_vertexOffsets[i][1];
                edgeEnd.z = kMapHitZero;

                PSVECSubtract(&edgeEnd, &edgeStart, &edge);
                PSVECSubtract(&point, &edgeEnd, &toPoint);
                PSVECCrossProduct(&edge, &toPoint, &cross);
                if (cross.z < kMapHitZero) {
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
        }

        if (sideMask != 0) {
            edgeIndex = -1;
        }
    }

    if (edgeIndex != -1 || g_hit_edge_t < kMapHitEdgeMinT || g_hit_t_min <= g_hit_edge_t) {
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

                float edgeT;
                if (FindIntersection(g_hit_cyl.m_bottom, *hitDirection, edgeCylinder, edgeT) != 0 &&
                    edgeT < g_hit_t_min) {
                    g_hit_edge_t = edgeT;
                    edgeIndex = i;
                    PSVECScale(hitDirection, &g_hit_hpv, g_hit_edge_t);
                    PSVECAdd(&g_hit_cyl.m_bottom, &g_hit_hpv, &g_hit_hpv);
                    break;
                }
            }
            previous = current;
        }

        if (edgeIndex == -1 || g_hit_t_min <= g_hit_edge_t) {
            return 0;
        }
    }

    g_hit_t = g_hit_edge_t;
    g_hit_t_min = g_hit_edge_t;
    g_hit_edge_idx_min = edgeIndex;
    g_hit_f = g_hit_lpface;
    g_hit_cyl_min = g_hit_cyl;
    if (gMapHitDrawMode.m_byte != 0) {
        g_hit_lpface->m_drawFlags = gMapHitDrawMode.m_byte;
    }
    g_hit_mvec_min = g_hit_mvec;
    g_hit_hpv_min = g_hit_hpv;
    gMapHitFaceFlag = 1;
    return 1;
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
int CMapHit::ReadOtmHit(CChunkFile& chunkFile)
{
    CChunkFile::CChunk chunk;

    chunkFile.PushChunk();

    while (chunkFile.GetNextChunk(chunk)) {
        switch (chunk.m_id) {
        case 'NAME': {
            char* mapHitName = chunkFile.GetString();
            MapMng.AttachMapHit(this, mapHitName);
            break;
        }
        case 'HITV': {
            m_vertexCount = static_cast<unsigned short>(chunk.m_arg0);
            m_vertices =
                new (MapMng.m_stage, const_cast<char*>(s_maphit_cpp), 0x143)
                    Vec[m_vertexCount];

            for (int i = 0; i < m_vertexCount; i++) {
                m_vertices[i].x = chunkFile.GetF4();
                m_vertices[i].y = chunkFile.GetF4();
                m_vertices[i].z = chunkFile.GetF4();

                Vec* v = &m_vertices[i];
                m_positionMin.x = (m_positionMin.x < v->x) ? m_positionMin.x : v->x;
                m_positionMin.y = (m_positionMin.y < v->y) ? m_positionMin.y : v->y;
                m_positionMin.z = (m_positionMin.z < v->z) ? m_positionMin.z : v->z;

                m_positionMax.x = (m_positionMax.x > v->x) ? m_positionMax.x : v->x;
                m_positionMax.y = (m_positionMax.y > v->y) ? m_positionMax.y : v->y;
                m_positionMax.z = (m_positionMax.z > v->z) ? m_positionMax.z : v->z;
            }

            m_positionMin.x -= kMapHitUnitScale;
            m_positionMin.y -= kMapHitUnitScale;
            m_positionMin.z -= kMapHitUnitScale;
            m_positionMax.x += kMapHitUnitScale;
            m_positionMax.y += kMapHitUnitScale;
            m_positionMax.z += kMapHitUnitScale;
            break;
        }
        case 'HITF': {
            m_faceCount = static_cast<unsigned short>(chunk.m_arg0);
            m_faces =
                new (MapMng.m_stage, const_cast<char*>(s_maphit_cpp), 0x159)
                    CMapHitFace[m_faceCount];

            const float& offsetScale = kMapHitVertexOffsetScale;
            const float& radiusScale = kMapHitRadiusScale;
            const float& zero = kMapHitZero;
            const double& radiusBase = kMapHitRadiusBase;

            for (int faceIdx = 0; faceIdx < m_faceCount; faceIdx++) {
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

                for (int i = 0; i < face.m_vertexCount; i++) {
                    face.m_vertexOffsets[i][1] = zero;
                    face.m_vertexOffsets[i][0] = zero;
                }

                if (chunk.m_version == 0) {
                    if ((unsigned int)System.m_execParam >= 1) {
                        System.Printf(const_cast<char*>(sOldMidFormat));
                    }
                    chunkFile.Align(4);
                    for (int i = 0; i < face.m_vertexCount; i++) {
                        (void)chunkFile.GetF4();
                        (void)chunkFile.GetF4();
                    }
                    face.m_radiusScale = kMapHitZero;
                } else if (chunk.m_version == 1) {
                    if ((unsigned int)System.m_execParam >= 1) {
                        System.Printf(const_cast<char*>(sOldMidFormat));
                    }
                    face.m_radiusScale = chunkFile.GetF4();
                    chunkFile.Align(4);
                } else {
                    face.m_radiusScale = chunkFile.GetF4();
                    chunkFile.Align(4);
                    const float vertexOffsetScale = kMapHitVertexOffsetScale;
                    for (int i = 0; i < face.m_vertexCount; i++) {
                        face.m_vertexOffsets[i][0] = chunkFile.GetF4() * vertexOffsetScale;
                        face.m_vertexOffsets[i][1] = chunkFile.GetF4() * vertexOffsetScale;
                    }
                }

                for (int i = 0; i < face.m_vertexCount; i++) {
                    face.m_vertexIndices[i] = chunkFile.Get2();

                    const Vec& v = m_vertices[face.m_vertexIndices[i]];
                    face.m_boundsMin.x = (face.m_boundsMin.x < v.x) ? face.m_boundsMin.x : v.x;
                    face.m_boundsMin.y = (face.m_boundsMin.y < v.y) ? face.m_boundsMin.y : v.y;
                    face.m_boundsMin.z = (face.m_boundsMin.z < v.z) ? face.m_boundsMin.z : v.z;

                    face.m_boundsMax.x = (face.m_boundsMax.x > v.x) ? face.m_boundsMax.x : v.x;
                    face.m_boundsMax.y = (face.m_boundsMax.y > v.y) ? face.m_boundsMax.y : v.y;
                    face.m_boundsMax.z = (face.m_boundsMax.z > v.z) ? face.m_boundsMax.z : v.z;
                }

                face.m_radiusScale *= radiusScale;
                face.m_boundsMin.x -= (offsetScale + face.m_radiusScale);
                face.m_boundsMin.y -= (offsetScale + face.m_radiusScale);
                face.m_boundsMin.z -= (offsetScale + face.m_radiusScale);
                face.m_boundsMax.x += (offsetScale + face.m_radiusScale);
                face.m_boundsMax.y += (offsetScale + face.m_radiusScale);
                face.m_boundsMax.z += (offsetScale + face.m_radiusScale);
                face.m_radiusScale = static_cast<float>(radiusBase - face.m_radiusScale);
            }
            break;
        }
        }
    }

    chunkFile.PopChunk();
    return 1;
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
    m_boundsMin.z = kMapHitBoundsMinInit;
    m_boundsMin.y = kMapHitBoundsMinInit;
    m_boundsMin.x = kMapHitBoundsMinInit;

    m_boundsMax.z = kMapHitBoundsMaxInit;
    m_boundsMax.y = kMapHitBoundsMaxInit;
    m_boundsMax.x = kMapHitBoundsMaxInit;
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
 * PAL Address: 0x80026dec
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapHit::CMapHit()
{
    m_positionMin.z = kMapHitBoundsMinInit;
    m_positionMin.y = kMapHitBoundsMinInit;
    m_positionMin.x = kMapHitBoundsMinInit;

    m_positionMax.z = kMapHitBoundsMaxInit;
    m_positionMax.y = kMapHitBoundsMaxInit;
    m_positionMax.x = kMapHitBoundsMaxInit;

    m_vertexCount = 0;
    m_faceCount = 0;
    m_vertices = 0;
    m_faces = 0;
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
int FindIntersection(const Vec& start, const Vec& direction, const CMapCylinder& cyl, float& outT)
{
    Vec orthogonal;
    Vec bitangent;
    Vec axis = cyl.m_axis;
    const f32 axisLen = PSVECMag(&axis);
    PSVECScale(&axis, &axis, 1.0f / axisLen);

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

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
static const char s_maphit_cpp[] = "maphit.cpp";
extern "C" const char sOldMidFormat[] = {
    (char)0x8C, (char)0xC3, (char)0x82, (char)0xA2, (char)0x20, (char)0x4D, (char)0x49, (char)0x44,
    (char)0x20, (char)0x82, (char)0xCC, (char)0x8C, (char)0x60, (char)0x8E, (char)0xAE, (char)0x82,
    (char)0xC5, (char)0x82, (char)0xB7, (char)0x81, (char)0x42, (char)0x0A, (char)0x00,
};

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

int g_hit_edge_idx_min;
float g_hit_t;
float g_hit_t_min;
float g_hit_t_slide_min;
unsigned char g_MapHitFaceFlag;
CMapHitFace* g_hit_lpface;
CMapHitFace* g_hit_f;
CMapHitFace* g_hit_lpface_min;
int g_hitTgt;

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

    int faceIndex = 0;
    CMapHitFace* face = m_faces;
    while (faceIndex < m_faceCount) {
        if ((face->m_drawFlags & 1) == 0) {
            const CMapIdGrp* mapIdGrp = &MapMng.m_mapIdGrpArray[face->m_groupIndex];
            GXColor colorABytes = *reinterpret_cast<const GXColor*>(&mapIdGrp->m_primaryColor);
            GXColor colorBBytes = *reinterpret_cast<const GXColor*>(&mapIdGrp->m_secondaryColor);

            GXBegin(GX_TRIANGLES, GX_VTXFMT7, 3);
            unsigned char* index = reinterpret_cast<unsigned char*>(face);
            int i = 0;
            while (i < static_cast<int>(face->m_vertexCount)) {
                Vec* vertex = m_vertices + *reinterpret_cast<unsigned short*>(index + 0x48);
                GXPosition3f32(vertex->x, vertex->y, vertex->z);
                GXNormal3f32(face->m_normal.x, face->m_normal.y, face->m_normal.z);
                GXColor4u8(colorABytes.r, colorABytes.g, colorABytes.b, colorABytes.a);
                i++;
                index += sizeof(unsigned short);
            }

            GXBegin(GX_TRIANGLES, GX_VTXFMT7, 3);
            i = static_cast<int>(face->m_vertexCount) - 1;
            while (i >= 0) {
                Vec* vertex = m_vertices + face->m_vertexIndices[i];
                GXPosition3f32(vertex->x, vertex->y, vertex->z);
                GXNormal3f32(face->m_normal.x, face->m_normal.y, face->m_normal.z);
                GXColor4u8(colorBBytes.r, colorBBytes.g, colorBBytes.b, colorBBytes.a);
                i--;
            }
        }

        faceIndex++;
        face++;
    }

    GXClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);

    face = m_faces;
    for (faceIndex = 0; faceIndex < static_cast<int>(m_faceCount); face++, faceIndex++) {
        if ((face->m_drawFlags & 1) != 0) {
            face->m_drawFlags = 0;
        } else {
            face->m_drawFlags = 0;
            continue;
        }

        face->m_drawFlags = 0;

        GXBegin(GX_TRIANGLES, GX_VTXFMT7, 3);
        int i = 0;
        while (i < static_cast<int>(face->m_vertexCount)) {
            Vec* vertex = m_vertices + face->m_vertexIndices[i];
            GXPosition3f32(vertex->x, vertex->y, vertex->z);
            GXColor4u8(0x40, 0xFF, 0x40, 0xFF);
            i++;
        }

        GXBegin(GX_TRIANGLES, GX_VTXFMT7, 3);
        i = static_cast<int>(face->m_vertexCount) - 1;
        while (i >= 0) {
            Vec* vertex = m_vertices + face->m_vertexIndices[i];
            GXPosition3f32(vertex->x, vertex->y, vertex->z);
            GXColor4u8(0x40, 0xFF, 0x40, 0xFF);
            i--;
        }
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
    int endFace = static_cast<unsigned short>(faceCount + startFace);

    g_hit_cyl = *mapCylinder;
    g_hit_mvec = *position;

    while (static_cast<int>(faceIndex) < endFace) {
        g_hit_lpface = reinterpret_cast<CMapHitFace*>(Ptr(m_faces, faceIndex * sizeof(CMapHitFace)));
        CheckHitFaceCylinder(mask);
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
        g_hit_lpface = reinterpret_cast<CMapHitFace*>(Ptr(m_faces, faceIndex * sizeof(CMapHitFace)));
        g_hit_t_min = kMapHitInitialTMin;

        if (CheckHitFaceCylinder(mask) != 0) {
            return 1;
        }

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

    int faceOffset;
    int faceIndex;
    faceIndex = 0;
    faceOffset = 0;
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
        PSVECScale(&g_hit_cyl_min.m_axis, position, g_hit_t_slide_min - (kMapHitEdgeBackoff / len));
        PSVECAdd(&g_hit_cyl_min.m_bottom, position, position);
    } else {
        float len = PSVECMag(&g_hit_cyl_min.m_axis);
        PSVECScale(&g_hit_cyl_min.m_axis, position, g_hit_t_slide_min - (kMapHitFaceBackoff / len));
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
        PSVECScale(&g_hit_cyl_min.m_axis, out, g_hit_t_slide_min - (kMapHitFaceBackoff / len));
        return 0;
    }

    if (gMapHitFace->m_normal.y < y) {
        if (g_hit_t_slide_min <= kMapHitSlideTLimit) {
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
    PSVECScale(&g_hit_cyl_min.m_axis, out, g_hit_t_slide_min - (kMapHitFaceBackoff / len));
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

    CMapCylinder& cyl = g_hit_cyl;
    unsigned char boundsOverlap = 0;
    unsigned char partialOverlap = 0;
    int axisOverlap;
    if (g_hit_lpface->m_boundsMin.x < g_hit_cyl.m_bound.m_min.x) {
        axisOverlap = g_hit_cyl.m_bound.m_min.x <= g_hit_lpface->m_boundsMax.x;
    } else if (g_hit_lpface->m_boundsMin.x > g_hit_cyl.m_bound.m_min.x) {
        axisOverlap = g_hit_lpface->m_boundsMin.x <= g_hit_cyl.m_bound.m_max.x;
    } else {
        axisOverlap = 1;
    }

    if (axisOverlap) {
        if (g_hit_lpface->m_boundsMin.y < g_hit_cyl.m_bound.m_min.y) {
            axisOverlap = g_hit_cyl.m_bound.m_min.y <= g_hit_lpface->m_boundsMax.y;
        } else if (g_hit_lpface->m_boundsMin.y > g_hit_cyl.m_bound.m_min.y) {
            axisOverlap = g_hit_lpface->m_boundsMin.y <= g_hit_cyl.m_bound.m_max.y;
        } else {
            axisOverlap = 1;
        }

        if (axisOverlap) {
            partialOverlap = 1;
        }
    }

    if (partialOverlap) {
        if (g_hit_lpface->m_boundsMin.z < g_hit_cyl.m_bound.m_min.z) {
            axisOverlap = g_hit_cyl.m_bound.m_min.z <= g_hit_lpface->m_boundsMax.z;
        } else if (g_hit_lpface->m_boundsMin.z > g_hit_cyl.m_bound.m_min.z) {
            axisOverlap = g_hit_lpface->m_boundsMin.z <= g_hit_cyl.m_bound.m_max.z;
        } else {
            axisOverlap = 1;
        }

        if (axisOverlap) {
            boundsOverlap = 1;
        }
    }

    if (!boundsOverlap) {
        return 0;
    }

    Vec* hitDirection = reinterpret_cast<Vec*>(Ptr(&g_hit_cyl, 0x18));
    float dot = PSVECDotProduct(hitDirection, &g_hit_lpface->m_normal);
    if (dot >= kMapHitZero) {
        return 0;
    }

    float hitDot = PSVECDotProduct(&g_hit_cyl.m_bottom, &g_hit_lpface->m_normal);
    g_hit_t = -((hitDot - (g_hit_lpface->m_planeD + g_hit_cyl.m_radius)) / dot);
    float hitT = g_hit_t;
    int edgeIndex = -1;
    int i;

    if (hitT > kMapHitEdgeMaxT) {
        return 0;
    }

    if (hitT < kMapHitEdgeMinT || !(hitT < g_hit_t_min)) {
        goto edge_loop;
    }

    {
        PSVECScale(hitDirection, &g_hit_hpv, hitT);
        PSVECAdd(&g_hit_cyl.m_bottom, &g_hit_hpv, &g_hit_hpv);

        Vec pushedHit;
        Vec scaledNormal;
        Vec edgeStart;
        Vec edgeEnd;
        PSVECScale(&g_hit_lpface->m_normal, &scaledNormal, g_hit_cyl.m_radius);
        PSVECSubtract(&g_hit_hpv, &scaledNormal, &pushedHit);

        unsigned int sideMask = 3;
        Vec previous = m_vertices[g_hit_lpface->m_vertexIndices[g_hit_lpface->m_vertexCount - 1]];
        Vec edge;
        Vec toPoint;
        Vec cross;
        Vec current;
        switch (g_hit_lpface->m_projectionAxis) {
        case 0:
            pushedHit.x = pushedHit.y;
            pushedHit.y = pushedHit.z;
            pushedHit.z = kMapHitZero;

            for (i = 0; i < static_cast<int>(g_hit_lpface->m_vertexCount); i++) {
                current = m_vertices[g_hit_lpface->m_vertexIndices[i]];
                edgeStart.x = previous.y + g_hit_lpface->m_vertexOffsets[i][0];
                edgeStart.y = previous.z + g_hit_lpface->m_vertexOffsets[i][1];
                edgeStart.z = kMapHitZero;
                edgeEnd.x = current.y + g_hit_lpface->m_vertexOffsets[i][0];
                edgeEnd.y = current.z + g_hit_lpface->m_vertexOffsets[i][1];
                edgeEnd.z = kMapHitZero;

                PSVECSubtract(&edgeEnd, &edgeStart, &edge);
                PSVECSubtract(&pushedHit, &edgeEnd, &toPoint);
                PSVECCrossProduct(&edge, &toPoint, &cross);
                if (cross.z >= kMapHitZero) {
                    sideMask &= 1;
                    if (sideMask == 0) {
                        goto edge_loop;
                    }
                } else if (cross.z <= kMapHitZero) {
                    sideMask &= 2;
                    if (sideMask == 0) {
                        goto edge_loop;
                    }
                }

                previous = current;
            }
            break;
        case 1:
            pushedHit.y = pushedHit.z;
            pushedHit.z = kMapHitZero;

            for (i = 0; i < static_cast<int>(g_hit_lpface->m_vertexCount); i++) {
                current = m_vertices[g_hit_lpface->m_vertexIndices[i]];
                edgeStart.x = previous.x + g_hit_lpface->m_vertexOffsets[i][0];
                edgeStart.y = previous.z + g_hit_lpface->m_vertexOffsets[i][1];
                edgeStart.z = kMapHitZero;
                edgeEnd.x = current.x + g_hit_lpface->m_vertexOffsets[i][0];
                edgeEnd.y = current.z + g_hit_lpface->m_vertexOffsets[i][1];
                edgeEnd.z = kMapHitZero;

                PSVECSubtract(&edgeEnd, &edgeStart, &edge);
                PSVECSubtract(&pushedHit, &edgeEnd, &toPoint);
                PSVECCrossProduct(&edge, &toPoint, &cross);
                if (cross.z >= kMapHitZero) {
                    sideMask &= 1;
                    if (sideMask == 0) {
                        goto edge_loop;
                    }
                } else if (cross.z <= kMapHitZero) {
                    sideMask &= 2;
                    if (sideMask == 0) {
                        goto edge_loop;
                    }
                }

                previous = current;
            }
            break;
        case 2:
            pushedHit.z = kMapHitZero;

            for (i = 0; i < static_cast<int>(g_hit_lpface->m_vertexCount); i++) {
                current = m_vertices[g_hit_lpface->m_vertexIndices[i]];
                edgeStart.x = previous.x + g_hit_lpface->m_vertexOffsets[i][0];
                edgeStart.y = previous.y + g_hit_lpface->m_vertexOffsets[i][1];
                edgeStart.z = kMapHitZero;
                edgeEnd.x = current.x + g_hit_lpface->m_vertexOffsets[i][0];
                edgeEnd.y = current.y + g_hit_lpface->m_vertexOffsets[i][1];
                edgeEnd.z = kMapHitZero;

                PSVECSubtract(&edgeEnd, &edgeStart, &edge);
                PSVECSubtract(&pushedHit, &edgeEnd, &toPoint);
                PSVECCrossProduct(&edge, &toPoint, &cross);
                if (cross.z >= kMapHitZero) {
                    sideMask &= 1;
                    if (sideMask == 0) {
                        goto edge_loop;
                    }
                } else if (cross.z <= kMapHitZero) {
                    sideMask &= 2;
                    if (sideMask == 0) {
                        goto edge_loop;
                    }
                }

                previous = current;
            }
            break;
        }
    }

commit:
    if (static_cast<signed char>(s_bitMask) != 0) {
        g_hit_lpface->m_drawFlags = s_bitMaskDrawFlags;
    }
    g_hit_t_slide_min = g_hit_t;
    g_hit_t_min = g_hit_t;
    g_hit_f = g_hit_lpface;
    g_hit_cyl_min = g_hit_cyl;
    g_hit_mvec_min = g_hit_mvec;
    g_hit_hpv_min = g_hit_hpv;
    g_hit_edge_idx_min = edgeIndex;
    gMapHitFaceFlag = 1;
    return 1;

edge_loop:
    if (static_cast<signed char>(s_bitMask) != 0) {
        g_hit_lpface->m_drawFlags = s_bitMaskDrawFlags;
    }

    if (g_hit_lpface->m_edgeFlags == 0) {
        return 0;
    }

    {
        Vec previous = m_vertices[g_hit_lpface->m_vertexIndices[g_hit_lpface->m_vertexCount - 1]];
        for (int i = 0; i < static_cast<int>(g_hit_lpface->m_vertexCount); i++) {
            Vec current;
            Vec* vertex = &m_vertices[g_hit_lpface->m_vertexIndices[i]];
            current.x = vertex->x;
            current.y = vertex->y;
            current.z = vertex->z;
            if ((g_hit_lpface->m_edgeFlags & (1 << i)) != 0) {
                Vec edge;
                PSVECSubtract(&current, &previous, &edge);

                Vec rayDirection = *reinterpret_cast<Vec*>(Ptr(&g_hit_cyl, 0x18));
                Vec rayStart = cyl.m_bottom;

                CMapCylinder edgeCylinder;
                edgeCylinder.m_bottom = previous;
                edgeCylinder.m_axis = edge;
                edgeCylinder.m_radius = g_hit_cyl.m_radius;

                float edgeT;
                if (FindIntersection(rayStart, rayDirection, edgeCylinder, edgeT) != 0 &&
                    edgeT < g_hit_t_min) {
                    g_hit_t = edgeT;
                    edgeIndex = i;
                    goto commit;
                }
            }
            previous = current;
        }
    }

    return 0;
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
    PSVECScale(&axis, &axis, kMapHitUnitScale / axisLen);

    const f32 axisX = axis.x;
    const double absAxisX = fabs(axisX);
    if (absAxisX >= fabs(axis.y) && absAxisX >= fabs(axis.z)) {
        orthogonal.x = -axis.y;
        orthogonal.y = axisX;
        orthogonal.z = kMapHitZero;
    } else {
        orthogonal.x = kMapHitZero;
        orthogonal.y = axis.z;
        orthogonal.z = -axis.y;
    }
    PSVECNormalize(&orthogonal, &orthogonal);

    PSVECCrossProduct(&axis, &orthogonal, &bitangent);

    Vec localDirection;
    localDirection.x = PSVECDotProduct(&orthogonal, &direction);
    localDirection.y = PSVECDotProduct(&bitangent, &direction);
    localDirection.z = PSVECDotProduct(&axis, &direction);

    const f32 directionLen = PSVECMag(&localDirection);
    const f32 tScale = kMapHitUnitScale / directionLen;
    PSVECScale(&localDirection, &localDirection, tScale);

    Vec relStart;
    PSVECSubtract(&start, &cyl.m_bottom, &relStart);

    const f32 px = PSVECDotProduct(&orthogonal, &relStart);
    const f32 py = PSVECDotProduct(&bitangent, &relStart);
    const f32 pz = PSVECDotProduct(&axis, &relStart);

    const f32 radius = cyl.m_radius;
    const f32 radiusSq = radius * radius;

    if (fabs(localDirection.z) >= 1.0f) {
        f32 disc = radiusSq - px * px - py * py;
        if (disc >= 0.0) {
            disc = sqrtf(disc);
            outT = (-(pz + disc)) * tScale;
            return 1;
        }
        return 0;
    }

cylinder_body:
    {
        const f32 vy = localDirection.y;
        const f32 radialC = (px * px + py * py) - radiusSq;
        const f32 radialB = px * localDirection.x + py * vy;
        const f32 vxSq = localDirection.x * localDirection.x;
        const f32 vySq = vy * vy;
        const f32 radialA = vxSq + vySq;
        f32 disc = radialB * radialB - radialA * radialC;
        if (disc < 0.0) {
            return 0;
        }

        if (disc > 0.0) {
            disc = sqrtf(disc);
            const f32 invA = 1.0 / radialA;
            const f32 t = (-radialB - disc) * invA;
            const f32 z = (t * localDirection.z) + pz;
            if (0.0 <= z && z <= axisLen) {
                outT = t * tScale;
                if (outT >= kMapHitZero && outT <= kMapHitUnitScale) {
                    return 1;
                }
                return 0;
            }
        } else {
            const f32 t = -radialB / radialA;
            const f32 z = (t * localDirection.z) + pz;
            if (0.0 <= z && z <= axisLen) {
                outT = t * tScale;
                if (outT >= kMapHitZero && outT <= kMapHitUnitScale) {
                    return 1;
                }
                return 0;
            }
        }

        if (g_hit_lpface->m_projectionAxis != 1) {
            return 0;
        }

        f32 capC = (pz * pz) + radialC;
        f32 capB = (pz * localDirection.z) + radialB;
        disc = capB * capB - capC;
        if (disc > 0.0) {
            disc = sqrtf(disc);
            f32 t;
            f32 negB = -capB;
            t = negB - disc;
            if ((t * localDirection.z) + pz <= 0.0) {
                outT = t * tScale;
                if (outT >= kMapHitZero && outT <= kMapHitUnitScale) {
                    return 1;
                }
                return 0;
            }

            t = negB + disc;
            if ((t * localDirection.z) + pz <= 0.0) {
                outT = t * tScale;
                if (outT >= kMapHitZero && outT <= kMapHitUnitScale) {
                    return 1;
                }
                return 0;
            }
        } else if (disc == 0.0) {
            const f32 t = -capB;
            if ((t * localDirection.z) + pz <= 0.0) {
                outT = t * tScale;
                if (outT >= kMapHitZero && outT <= kMapHitUnitScale) {
                    return 1;
                }
                return 0;
            }
        }

        capB = capB - (localDirection.z * axisLen);
        disc = capB * capB - (f32)(axisLen * -((2.0 * pz) - axisLen) + capC);
        if (disc > 0.0) {
            disc = sqrtf(disc);
            f32 t;
            f32 negB = -capB;
            t = negB - disc;
            if ((t * localDirection.z) + pz >= axisLen) {
                outT = t * tScale;
                if (outT >= kMapHitZero && outT <= kMapHitUnitScale) {
                    return 1;
                }
                return 0;
            }

            t = negB + disc;
            if ((t * localDirection.z) + pz >= axisLen) {
                outT = t * tScale;
                if (outT >= kMapHitZero && outT <= kMapHitUnitScale) {
                    return 1;
                }
                return 0;
            }
        } else if (disc == 0.0) {
            const f32 t = -capB;
            if ((t * localDirection.z) + pz >= axisLen) {
                outT = t * tScale;
                if (outT >= kMapHitZero && outT <= kMapHitUnitScale) {
                    return 1;
                }
                return 0;
            }
        }

    }

    return 0;
}

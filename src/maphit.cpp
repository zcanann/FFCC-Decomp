#include "ffcc/maphit.h"

#include <math.h>

extern CMapCylinder g_hit_cyl;
extern CMapCylinder g_hit_cyl_min;

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
 * Address:	TODO
 * Size:	TODO
 */
void CMapHit::ReadOtmHit(CChunkFile&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapHit::CheckHitFaceCylinder(unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapCylinder::operator= (const CMapCylinder&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapHit::GetHitFaceNormal(Vec*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapHit::CalcHitSlide(Vec*, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapHit::CalcHitPosition(Vec*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMapHit::CheckHitCylinder(CMapCylinder*, Vec*, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMapHit::CheckHitCylinder(CMapCylinder*, Vec*, unsigned short, unsigned short, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMapHit::CheckHitCylinderNear(CMapCylinder*, Vec*, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMapHit::CheckHitCylinderNear(CMapCylinder*, Vec*, unsigned short, unsigned short, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapHit::Draw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapHit::DrawWire()
{
	// TODO
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

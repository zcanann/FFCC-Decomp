#include "ffcc/maphit.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void FindIntersection(const Vec&, const Vec&, const CMapCylinder&, float&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CheckLineCylinder(const Vec&, const Vec&, const CMapCylinder&, float&)
{
	// TODO
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

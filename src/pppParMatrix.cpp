#include "ffcc/pppParMatrix.h"
#include "global.h"
#include "dolphin/mtx.h"
#include <stddef.h>

STATIC_ASSERT(offsetof(pppParMatrixWork, m_matrix) == 0x04);
STATIC_ASSERT(offsetof(pppParMatrixWork, m_positionX) == 0x1C);
STATIC_ASSERT(offsetof(pppParMatrixWork, m_positionY) == 0x2C);
STATIC_ASSERT(offsetof(pppParMatrixWork, m_positionZ) == 0x3C);

/*
 * --INFO--
 * Address:	TODO
 * Size:	108
 */
void pppParMatrix(pppParMatrixWork* work)
{
	Vec position;
	MtxPtr matrix = work->m_matrix;

	position.x = work->m_positionX;
	position.y = work->m_positionY;
	position.z = work->m_positionZ;

	PSMTXMultVec(matrix + 1, &position, &position);

	work->m_positionX = position.x;
	work->m_positionY = position.y;
	work->m_positionZ = position.z;
}

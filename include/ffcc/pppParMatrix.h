#ifndef _PPP_PARMATRIX_H_
#define _PPP_PARMATRIX_H_

#include <dolphin/mtx.h>
#include <dolphin/types.h>

struct pppParMatrixWork {
	u32 m_graphId;
	MtxPtr m_matrix;
	u8 m_pad08[0x1C - 0x08];
	f32 m_positionX;
	u8 m_pad20[0x2C - 0x20];
	f32 m_positionY;
	u8 m_pad30[0x3C - 0x30];
	f32 m_positionZ;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppParMatrix(pppParMatrixWork* work);

#ifdef __cplusplus
}
#endif

#endif // _PPP_PARMATRIX_H_

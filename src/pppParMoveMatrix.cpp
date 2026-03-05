#include "ffcc/pppParMoveMatrix.h"
#include "ffcc/pppPart.h"

#include <dolphin/mtx.h>

extern unsigned char* lbl_8032ED50;
extern float lbl_80330E38;
extern float lbl_80330E3C;

/*
 * --INFO--
 * PAL Address: 0x800e092c
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppParMoveMatrix(void)
{
	_pppMngSt *pppMngSt;
	Vec local_44;
	Vec local_50;
	Vec local_5c;
	Vec local_68;
	Mtx MStack_38;
	
	pppMngSt = (_pppMngSt*)lbl_8032ED50;
	Vec* previousPosition = (Vec*)(lbl_8032ED50 + 0x48);
	Vec* position = (Vec*)(lbl_8032ED50 + 0x8);
	PSVECSubtract(previousPosition, position, &local_44);
	
	if (((lbl_80330E38 != local_44.x) || (lbl_80330E38 != local_44.y)) || (lbl_80330E38 != local_44.z)) {
		PSVECNormalize(&local_44, &local_68);
		local_50.x = local_68.z;
		local_50.y = lbl_80330E38;
		local_50.z = -local_68.x;
		if (!((local_68.z != lbl_80330E38) || (lbl_80330E38 != local_50.z))) {
			local_50.y = lbl_80330E38;
			local_50.x = lbl_80330E3C;
			local_50.z = lbl_80330E38;
			local_5c.x = lbl_80330E38;
			local_5c.y = lbl_80330E38;
			local_5c.z = lbl_80330E3C;
		}
		else {
			PSVECNormalize(&local_50, &local_50);
			PSVECCrossProduct(&local_68, &local_50, &local_5c);
			PSVECNormalize(&local_5c, &local_5c);
		}
		*(float*)(lbl_8032ED50 + 0x78) = local_50.x;
		*(float*)(lbl_8032ED50 + 0x88) = local_50.y;
		*(float*)(lbl_8032ED50 + 0x98) = local_50.z;
		*(float*)(lbl_8032ED50 + 0x7C) = local_5c.x;
		*(float*)(lbl_8032ED50 + 0x8C) = local_5c.y;
		*(float*)(lbl_8032ED50 + 0x9C) = local_5c.z;
		*(float*)(lbl_8032ED50 + 0x80) = local_68.x;
		*(float*)(lbl_8032ED50 + 0x90) = local_68.y;
		*(float*)(lbl_8032ED50 + 0xA0) = local_68.z;
		PSMTXScale(MStack_38, *(float*)(lbl_8032ED50 + 0x28), *(float*)(lbl_8032ED50 + 0x2C),
		           *(float*)(lbl_8032ED50 + 0x30));
		PSMTXConcat(MStack_38, (MtxPtr)(lbl_8032ED50 + 0x78), (MtxPtr)(lbl_8032ED50 + 0x78));
		*(float*)(lbl_8032ED50 + 0x84) = *(float*)((unsigned char*)pppMngSt + 0x8);
		*(float*)(lbl_8032ED50 + 0x94) = *(float*)((unsigned char*)pppMngSt + 0xC);
		*(float*)(lbl_8032ED50 + 0xA4) = *(float*)((unsigned char*)pppMngSt + 0x10);
		pppSetFpMatrix(pppMngSt);
	}
}

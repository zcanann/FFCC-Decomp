#include "ffcc/pppSclAccele.h"

typedef struct {
	char pad[0xc];
	int m_graphId;
} pppSclAcceleObj;

extern int lbl_8032ED70;
extern float DAT_8032fec8;

/*
 * --INFO--
 * PAL Address: 0x80063150
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSclAcceleCon(void* arg1, void* arg2)
{
	int* serializedDataOffsets = *(int**)((char*)arg2 + 0xc);
	float* pfVar2 = (float*)((char*)arg1 + serializedDataOffsets[1] + 0x80);
	float fVar1 = DAT_8032fec8;

	pfVar2[2] = fVar1;
	pfVar2[1] = fVar1;
	*pfVar2 = fVar1;
}

/*
 * --INFO--
 * PAL Address: 0x80063174
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSclAccele(void* arg1, void* arg2, void* arg3)
{
	int* serializedDataOffsets = *(int**)((char*)arg3 + 0xc);
	float* pfVar1 = (float*)((char*)arg1 + serializedDataOffsets[0] + 0x80);
	float* pfVar2 = (float*)((char*)arg1 + serializedDataOffsets[1] + 0x80);

	if (lbl_8032ED70 != 0) {
		return;
	}

	if (*(int*)arg2 == ((pppSclAcceleObj*)arg1)->m_graphId) {
		*pfVar2 = *pfVar2 + ((float*)arg2)[2];
		pfVar2[1] = pfVar2[1] + ((float*)arg2)[3];
		pfVar2[2] = pfVar2[2] + ((float*)arg2)[4];
	}

	*pfVar1 = *pfVar1 + *pfVar2;
	pfVar1[1] = pfVar1[1] + pfVar2[1];
	pfVar1[2] = pfVar1[2] + pfVar2[2];
}

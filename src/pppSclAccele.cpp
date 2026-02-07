#include "ffcc/pppSclAccele.h"

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
	void* ptr = (void*)((int*)((char*)arg2 + 0xC))[0];
	ptr = (void*)((int*)((char*)ptr + 0x4))[0];
	float* value = (float*)((char*)arg1 + (int)ptr + 0x80);

	value[2] = 0.0f;
	value[1] = 0.0f;
	value[0] = 0.0f;
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
	int* data = (int*)((int*)((char*)arg3 + 0xC))[0];
	int data1 = data[0];
	int data2 = data[1];

	extern int lbl_8032ED70;
	if (lbl_8032ED70 != 0) {
		return;
	}

	float* ptr1 = (float*)((char*)arg1 + data1 + 0x80);
	float* ptr2 = (float*)((char*)arg1 + data2 + 0x80);
	if (((int*)arg2)[0] == ((int*)arg1)[3]) {
		ptr2[0] += ((float*)arg2)[2];
		ptr2[1] += ((float*)arg2)[3];
		ptr2[2] += ((float*)arg2)[4];
	}

	ptr1[0] += ptr2[0];
	ptr1[1] += ptr2[1];
	ptr1[2] += ptr2[2];
}

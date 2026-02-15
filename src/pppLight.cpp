#include "ffcc/pppLight.h"
#include "dolphin/mtx.h"

extern float lbl_80330F60;
extern float lbl_80330F64;
extern float lbl_80330F68;
extern float lbl_80330F6C;
extern int lbl_8032ED70;
extern unsigned char lbl_8032ED78;
extern unsigned char lbl_8032ED79;
extern unsigned char* lbl_8032ED50;
extern unsigned char lbl_801EADC8[];

extern "C" {
void __ct__Q29CLightPcs6CLightFv(void*);
void Add__9CLightPcsFPQ29CLightPcs6CLight(void*, void*);
unsigned char LightPcs[];
}

/*
 * --INFO--
 * PAL Address: 0x800dab00
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppLightCon3(void* param1, void* param2)
{
	// Based on assembly: accesses param2+0xc, then deref twice, then +0x80
	// Stores zeros and a float constant to various offsets
	void** ptr1 = (void**)((char*)param2 + 0xc);
	void** ptr2 = (void**)*ptr1;
	void* ptr3 = *ptr2;
	char* base = (char*)param1 + (int)ptr3 + 0x80;
	float zero = lbl_80330F60;
	
	// Clear some integer values
	*(int*)((char*)base + 0x10) = 0;
	*(int*)((char*)base + 0x14) = 0;
	
	// Set float values to 0.0f
	*(float*)((char*)base + 0x20) = zero;
	*(float*)((char*)base + 0x2c) = zero;
	*(float*)((char*)base + 0x38) = zero;
	*(float*)((char*)base + 0x44) = zero;
}

/*
 * --INFO--
 * PAL Address: 0x800dab34
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppLightCon(void* param1, void* param2)
{
	// Similar pattern to pppLightCon3 but clears more values
	void** ptr1 = (void**)((char*)param2 + 0xc);
	void** ptr2 = (void**)*ptr1;
	void* ptr3 = *ptr2;
	char* base = (char*)param1 + (int)ptr3 + 0x80;
	float zero = lbl_80330F60;
	
	// Clear integer values
	*(int*)((char*)base + 0x0) = 0;
	*(int*)((char*)base + 0x4) = 0;
	*(int*)((char*)base + 0x8) = 0;
	*(int*)((char*)base + 0xc) = 0;
	*(int*)((char*)base + 0x10) = 0;
	*(int*)((char*)base + 0x14) = 0;
	
	// Clear float values
	*(float*)((char*)base + 0x20) = zero;
	*(float*)((char*)base + 0x1c) = zero;
	*(float*)((char*)base + 0x18) = zero;
	*(float*)((char*)base + 0x2c) = zero;
	*(float*)((char*)base + 0x28) = zero;
	*(float*)((char*)base + 0x24) = zero;
	*(float*)((char*)base + 0x38) = zero;
	*(float*)((char*)base + 0x34) = zero;
	*(float*)((char*)base + 0x30) = zero;
	*(float*)((char*)base + 0x44) = zero;
	*(float*)((char*)base + 0x40) = zero;
	*(float*)((char*)base + 0x3c) = zero;
}

/*
 * --INFO--
 * PAL Address: 0x800dab98
 * PAL Size: 1276b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppLight(void* param1, void* param2, void* param3)
{
	unsigned char* pppMng = (unsigned char*)param1;
	unsigned char* lightParam = (unsigned char*)param2;
	unsigned char* work = pppMng + *(int*)(*(unsigned char**)((unsigned char*)param3 + 0xc)) + 0x80;
	unsigned char lightData[0xb0];
	Vec sourcePos;
	Vec targetPos;

	if (lbl_8032ED70 == 0) {
		*(float*)(work + 0x1c) = *(float*)(work + 0x1c) + *(float*)(work + 0x20);
		*(float*)(work + 0x18) = *(float*)(work + 0x18) + *(float*)(work + 0x1c);
		*(float*)(work + 0x28) = *(float*)(work + 0x28) + *(float*)(work + 0x2c);
		*(float*)(work + 0x24) = *(float*)(work + 0x24) + *(float*)(work + 0x28);
		*(float*)(work + 0x34) = *(float*)(work + 0x34) + *(float*)(work + 0x38);
		*(float*)(work + 0x30) = *(float*)(work + 0x30) + *(float*)(work + 0x34);
		*(float*)(work + 0x40) = *(float*)(work + 0x40) + *(float*)(work + 0x44);
		*(float*)(work + 0x3c) = *(float*)(work + 0x3c) + *(float*)(work + 0x40);

		*(short*)(work + 0x8) = *(short*)(work + 0x8) + *(short*)(work + 0x10);
		*(short*)(work + 0xa) = *(short*)(work + 0xa) + *(short*)(work + 0x12);
		*(short*)(work + 0xc) = *(short*)(work + 0xc) + *(short*)(work + 0x14);
		*(short*)(work + 0xe) = *(short*)(work + 0xe) + *(short*)(work + 0x16);

		*(short*)(work + 0x0) = *(short*)(work + 0x0) + *(short*)(work + 0x8);
		*(short*)(work + 0x2) = *(short*)(work + 0x2) + *(short*)(work + 0xa);
		*(short*)(work + 0x4) = *(short*)(work + 0x4) + *(short*)(work + 0xc);
		*(short*)(work + 0x6) = *(short*)(work + 0x6) + *(short*)(work + 0xe);

		if (*(int*)lightParam == *(int*)(pppMng + 0xc)) {
			*(short*)(work + 0x0) = *(short*)(work + 0x0) + *(short*)(lightParam + 0x8);
			*(short*)(work + 0x2) = *(short*)(work + 0x2) + *(short*)(lightParam + 0xa);
			*(short*)(work + 0x4) = *(short*)(work + 0x4) + *(short*)(lightParam + 0xc);
			*(short*)(work + 0x6) = *(short*)(work + 0x6) + *(short*)(lightParam + 0xe);
			*(short*)(work + 0x8) = *(short*)(work + 0x8) + *(short*)(lightParam + 0x10);
			*(short*)(work + 0xa) = *(short*)(work + 0xa) + *(short*)(lightParam + 0x12);
			*(short*)(work + 0xc) = *(short*)(work + 0xc) + *(short*)(lightParam + 0x14);
			*(short*)(work + 0xe) = *(short*)(work + 0xe) + *(short*)(lightParam + 0x16);
			*(short*)(work + 0x10) = *(short*)(work + 0x10) + *(short*)(lightParam + 0x18);
			*(short*)(work + 0x12) = *(short*)(work + 0x12) + *(short*)(lightParam + 0x1a);
			*(short*)(work + 0x14) = *(short*)(work + 0x14) + *(short*)(lightParam + 0x1c);
			*(short*)(work + 0x16) = *(short*)(work + 0x16) + *(short*)(lightParam + 0x1e);
			*(float*)(work + 0x18) = *(float*)(work + 0x18) + *(float*)(lightParam + 0x20);
			*(float*)(work + 0x1c) = *(float*)(work + 0x1c) + *(float*)(lightParam + 0x24);
			*(float*)(work + 0x20) = *(float*)(work + 0x20) + *(float*)(lightParam + 0x28);
			*(float*)(work + 0x24) = *(float*)(work + 0x24) + *(float*)(lightParam + 0x2c);
			*(float*)(work + 0x28) = *(float*)(work + 0x28) + *(float*)(lightParam + 0x30);
			*(float*)(work + 0x2c) = *(float*)(work + 0x2c) + *(float*)(lightParam + 0x34);
			*(float*)(work + 0x30) = *(float*)(work + 0x30) + *(float*)(lightParam + 0x38);
			*(float*)(work + 0x34) = *(float*)(work + 0x34) + *(float*)(lightParam + 0x3c);
			*(float*)(work + 0x38) = *(float*)(work + 0x38) + *(float*)(lightParam + 0x40);
			*(float*)(work + 0x3c) = *(float*)(work + 0x3c) + *(float*)(lightParam + 0x4c);
			*(float*)(work + 0x40) = *(float*)(work + 0x40) + *(float*)(lightParam + 0x50);
			*(float*)(work + 0x44) = *(float*)(work + 0x44) + *(float*)(lightParam + 0x54);
		}

		__ct__Q29CLightPcs6CLightFv(lightData);

		sourcePos.x = *(float*)(pppMng + 0x1c);
		sourcePos.y = *(float*)(pppMng + 0x2c);
		sourcePos.z = *(float*)(pppMng + 0x3c);
		PSMTXMultVec((MtxPtr)(lbl_8032ED50 + 0x78), &sourcePos, &sourcePos);

		*(float*)(lightData + 0xc) = sourcePos.x;
		*(float*)(lightData + 0x10) = sourcePos.y;
		*(float*)(lightData + 0x14) = sourcePos.z;
		*(float*)(lightData + 0x24) = *(float*)(work + 0x24);
		*(float*)(lightData + 0x28) = *(float*)(work + 0x18);
		*(float*)(lightData + 0x30) = lbl_80330F64;
		*(unsigned char**)(lightData + 0x6c) = lbl_8032ED50;
		*(int*)(lightData + 0x70) = 0;

		int c0 = *(short*)(work + 0x0) >> 7;
		int c1 = *(short*)(work + 0x2) >> 7;
		int c2 = *(short*)(work + 0x4) >> 7;
		int c3 = *(short*)(work + 0x6) >> 7;
		lightData[0x58] = (unsigned char)c0;
		lightData[0x59] = (unsigned char)c1;
		lightData[0x5a] = (unsigned char)c2;
		lightData[0x5b] = (unsigned char)c3;

		if (lightParam[0x5a] != 0) {
			lightData[0x5c] = (unsigned char)c0;
			lightData[0x5d] = (unsigned char)c1;
			lightData[0x5e] = (unsigned char)c2;
			lightData[0x5f] = (unsigned char)c3;
		} else {
			*(int*)(lightData + 0x5c) = 0;
		}

		if (lightParam[0x5b] != 0) {
			lightData[0x60] = lightData[0x58];
			lightData[0x61] = lightData[0x59];
			lightData[0x62] = lightData[0x5a];
			lightData[0x63] = lightData[0x5b];
		} else {
			*(int*)(lightData + 0x60) = 0;
		}

		if (lightParam[0x59] == 0) {
			*(int*)(lightData + 0x58) = 0;
		}

		if (lbl_8032ED78 == 0 && lbl_8032ED79 == 0) {
			if (lightParam[0x58] == 0) {
				*(int*)(lightData + 0x8) = 0;
				*(float*)(lightData + 0x40) = lbl_80330F60;
				*(float*)(lightData + 0x44) = lbl_80330F60;
				*(float*)(lightData + 0x48) = lbl_80330F64;
				*(float*)(lightData + 0x4c) = lbl_80330F68;
				Add__9CLightPcsFPQ29CLightPcs6CLight(LightPcs, lightData);
			} else {
				unsigned char* obj;

				*(int*)(lightData + 0x8) = 1;
				if (*(int*)(lightParam + 0x44) == -1) {
					obj = lbl_801EADC8;
				} else {
					int objId = *(int*)(lightParam + 0x44);
					obj = *(unsigned char**)(*(unsigned char**)(lbl_8032ED50 + 0xd4) + (objId << 4) + 0x4);
				}

				targetPos.x = *(float*)(obj + 0x1c);
				targetPos.y = *(float*)(obj + 0x2c);
				targetPos.z = *(float*)(obj + 0x3c);
				PSMTXMultVec((MtxPtr)(lbl_8032ED50 + 0x78), &targetPos, &targetPos);

				PSVECSubtract(&targetPos, &sourcePos, (Vec*)(lightData + 0x40));
				PSVECNormalize((Vec*)(lightData + 0x40), (Vec*)(lightData + 0x40));
				*(float*)(lightData + 0x4c) = lbl_80330F6C * *(float*)(work + 0x30);

				if (lightParam[0x58] == 2) {
					*(float*)(lightData + 0x50) = *(float*)(work + 0x3c);
					lightData[0x57] = 1;
				}

				Add__9CLightPcsFPQ29CLightPcs6CLight(LightPcs, lightData);
			}
		}
	}
}

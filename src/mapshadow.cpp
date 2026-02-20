#include "ffcc/mapshadow.h"
#include "ffcc/mapocttree.h"
#include "ffcc/CPtrArray.h"
#include "ffcc/materialman.h"
#include "ffcc/vector.h"
#include <dolphin/mtx.h>

// External constants referenced in decompilation
extern double DOUBLE_8032fce8;
extern float FLOAT_8032fcf0;
extern float FLOAT_8032fce0;

class CMapMng;
extern CMapMng MapMng;

/*
 * --INFO--
 * PAL Address: 0x8004c71c
 * PAL Size: 236b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapShadowInsertOctTree(CMapShadow::TARGET mapShadow, COctTree& octTree)
{
	CMapShadow* shadow;
	int model;
	u32 i;
	Vec pos;
	CBound* bound;

	octTree.ClearShadow();
	if (*(u32*)(*(u32*)((char*)&octTree + 0x8) + 0x3c) != 0) {
		for (i = 0; i < ((CPtrArray<CMapShadow>*)((char*)&MapMng + 0x21434))->GetSize(); i++) {
			if (((*(u32*)(*(u32*)((char*)&octTree + 0x8) + 0x3c) & (1U << i)) != 0)
			    && ((shadow = (*(CPtrArray<CMapShadow>*)((char*)&MapMng + 0x21434))[i]),
			        (*((char*)shadow + (int)mapShadow + 0xf0) != 0))
			    && (*(char*)((char*)shadow + 0x7) == 0)) {
				model = *(int*)((char*)shadow + 0xc);
				pos.x = *(float*)(model + 0xc4);
				pos.y = *(float*)(model + 0xd4);
				pos.z = *(float*)(model + 0xe4);

				bound = (CBound*)((char*)shadow + (int)mapShadow * 0x18 + 0xc0);
				octTree.InsertShadow(i, pos, *bound);
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8004c91c
 * PAL Size: 236b
 */
void CMapShadow::Init()
{
	float width;
	float height;
	float scale;
	int material;
	int materialArray;
	u32 materialWidth;
	u32 materialHeight;
	u32 materialMode;

	materialArray = *(int*)((char*)&MapMng + 0x213d4);
	material = (int)(((CPtrArray<CMaterial>*)(materialArray + 8))->operator[](*(u16*)((char*)this + 4)));
	material = *(int*)(material + 0x3c);
	materialWidth = *(u32*)(material + 0x64);
	materialHeight = *(u32*)(material + 0x68);
	materialMode = *(u32*)(material + 0x6c);
	*((u8*)this + 7) = materialMode;
	width = (float)materialWidth;
	height = (float)materialHeight;
	scale = *(float*)((char*)this + 0xa8);
	if (*(u8*)((char*)this + 6) != 0) {
		C_MTXLightFrustum((MtxPtr)((char*)this + 0x48), -height, height, -width, width, *(float*)((char*)this + 0xac),
		                  (float)(DOUBLE_8032fce8 * (double)scale), FLOAT_8032fcf0 * scale, FLOAT_8032fcf0,
		                  FLOAT_8032fcf0);
	} else {
		C_MTXLightOrtho((MtxPtr)((char*)this + 0x48), -height, height, -width, width,
		                (float)(DOUBLE_8032fce8 * (double)scale), FLOAT_8032fcf0 * scale, FLOAT_8032fcf0,
		                FLOAT_8032fcf0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8004c8c8
 * PAL Size: 84b
 */
void CMapShadow::Calc()
{
	float fVar1;
	
	fVar1 = FLOAT_8032fce0;
	*(float*)((char*)this + 0x54) = *(float*)((char*)this + 0x54) + *(float*)((char*)this + 0xb8);
	if (fVar1 < *(float*)((char*)this + 0x54)) {
		*(float*)((char*)this + 0x54) = *(float*)((char*)this + 0x54) - fVar1;
	}
	fVar1 = FLOAT_8032fce0;
	*(float*)((char*)this + 0x64) = *(float*)((char*)this + 0x64) + *(float*)((char*)this + 0xbc);
	if (*(float*)((char*)this + 0x64) > fVar1) {
		*(float*)((char*)this + 0x64) = *(float*)((char*)this + 0x64) - fVar1;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8004c808
 * PAL Size: 192b
 */
void CMapShadow::Draw()
{
	int iVar1;
	Vec local_14;
	Vec local_20;
	Vec local_2c;
	Vec VStack_38;
	
	iVar1 = *(int*)((char*)this + 0xc);
	local_14.x = *(float*)(iVar1 + 0xc4);
	local_14.y = *(float*)(iVar1 + 0xd4);
	local_14.z = *(float*)(iVar1 + 0xe4);
	iVar1 = *(int*)((char*)this + 0x14);
	local_20.x = *(float*)(iVar1 + 0xc4);
	local_20.y = *(float*)(iVar1 + 0xd4);
	local_20.z = *(float*)(iVar1 + 0xe4);
	iVar1 = *(int*)((char*)this + 0x10);
	local_2c.x = *(float*)(iVar1 + 0xc4);
	local_2c.y = *(float*)(iVar1 + 0xd4);
	local_2c.z = *(float*)(iVar1 + 0xe4);
	PSVECSubtract(&local_20, &local_14, &local_20);
	PSVECSubtract(&local_2c, &local_14, &VStack_38);
	C_MTXLookAt((MtxPtr)((char*)this + 0x18), (Point3d*)&local_14, &local_20, (Point3d*)&local_2c);
	PSMTXConcat((MtxPtr)((char*)this + 0x48), (MtxPtr)((char*)this + 0x18), (MtxPtr)((char*)this + 0x78));
}

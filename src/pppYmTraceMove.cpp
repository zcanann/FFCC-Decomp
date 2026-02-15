#include "ffcc/pppYmTraceMove.h"
#include "ffcc/partMng.h"
#include "dolphin/mtx.h"

extern int DAT_8032ed70;

extern "C" {
	void pppCopyVector__FR3Vec3Vec(Vec*, const Vec*);
	void pppSubVector__FR3Vec3Vec3Vec(Vec*, const Vec*, const Vec*);
	void pppNormalize__FR3Vec3Vec(float*, Vec*);
	void pppAddVector__FR3Vec3Vec3Vec(Vec*, const Vec*, const Vec*);
}

/*
 * --INFO--
 * PAL Address: 0x800d4bd0
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmTraceMove(pppYmTraceMove* pppYmTraceMove, UnkC* param_2)
{
	Vec* dest;
	f32 fVar1;
	Vec local_20;
	f32 local_24;
	f32 local_28;
	f32 local_2c;
	Vec local_38;
	f32 local_18;
	f32 local_1c;

	local_2c = *(f32*)((u8*)pppMngStPtr + 0x58);
	local_28 = *(f32*)((u8*)pppMngStPtr + 0x5c);
	dest = (Vec*)((u8*)pppYmTraceMove + 0x80 + *param_2->m_serializedDataOffsets);
	local_24 = *(f32*)((u8*)pppMngStPtr + 0x60);
	local_20.x = *(f32*)((u8*)pppMngStPtr + 0x68);
	local_1c = *(f32*)((u8*)pppMngStPtr + 0x6c);
	local_18 = *(f32*)((u8*)pppMngStPtr + 0x70);
	local_20.y = local_1c;
	local_20.z = local_18;
	pppSubVector__FR3Vec3Vec3Vec((Vec*)&dest[1].y, &local_20, (Vec*)&local_2c);
	local_38.x = dest[1].y;
	local_38.y = dest[1].z;
	local_38.z = dest[2].x;
	pppCopyVector__FR3Vec3Vec(dest, &local_38);
	fVar1 = 0.0f;
	dest[3].x = 0.0f;
	dest[2].z = fVar1;
	dest[2].y = fVar1;
}

/*
 * --INFO--
 * PAL Address: 0x800d4828
 * PAL Size: 936b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmTraceMove(pppYmTraceMove* pppYmTraceMove, UnkB* param_2, UnkC* param_3)
{
	u8* owner;
	Vec* dest;
	Vec local_b0;
	Vec local_a4;
	Quaternion local_98;
	Quaternion local_88;
	Quaternion local_78;
	Vec local_68;
	Vec local_5c;
	Vec local_50;
	Vec local_44;
	Vec local_38;
	Vec local_8c;
	Vec local_2c;
	Vec local_20;
	f32 fVar1;

	if (DAT_8032ed70 != 0) {
		return;
	}

	owner = *(u8**)((u8*)pppMngStPtr + 0xdc);
	dest = (Vec*)((u8*)pppYmTraceMove + 0x80 + *param_3->m_serializedDataOffsets);
	dest[2].z = dest[2].z + dest[3].x;
	dest[2].y = dest[2].y + dest[2].z;

	if (param_2->m_graphId == pppYmTraceMove->m_graphId) {
		dest[2].y = dest[2].y + param_2->m_initWOrk;
		dest[2].z = dest[2].z + param_2->m_stepValue;
		dest[3].x = dest[3].x + param_2->m_arg3;
	}

	if (owner == nullptr) {
		local_8c.x = dest->x;
		local_8c.y = dest->y;
		local_8c.z = dest->z;
		pppCopyVector__FR3Vec3Vec(&local_20, &local_8c);

		local_8c.x = dest[1].y;
		local_8c.y = dest[1].z;
		local_8c.z = dest[2].x;
		pppCopyVector__FR3Vec3Vec(&local_2c, &local_8c);
	} else {
		local_b0.x = *(f32*)(owner + 0x15c);
		local_b0.y = *(f32*)(owner + 0x160);
		local_b0.z = *(f32*)(owner + 0x164);
		local_a4.x = *(f32*)((u8*)pppMngStPtr + 0x8);
		local_a4.y = *(f32*)((u8*)pppMngStPtr + 0xc);
		local_a4.z = *(f32*)((u8*)pppMngStPtr + 0x10);
		pppSubVector__FR3Vec3Vec3Vec(&local_20, &local_b0, &local_a4);

		local_20.y = local_20.y + param_2->m_payload;
		local_5c.x = local_20.x;
		local_5c.y = local_20.y;
		local_5c.z = local_20.z;
		pppNormalize__FR3Vec3Vec((float*)&local_20, &local_5c);
		pppCopyVector__FR3Vec3Vec(dest, &local_20);

		local_50.x = *(f32*)((u8*)pppMngStPtr + 0x48);
		local_50.y = *(f32*)((u8*)pppMngStPtr + 0x4c);
		local_50.z = *(f32*)((u8*)pppMngStPtr + 0x50);
		local_44.x = *(f32*)((u8*)pppMngStPtr + 0x8);
		local_44.y = *(f32*)((u8*)pppMngStPtr + 0xc);
		local_44.z = *(f32*)((u8*)pppMngStPtr + 0x10);
		pppSubVector__FR3Vec3Vec3Vec(&local_2c, &local_44, &local_50);

		if ((local_2c.x == 0.0f) && (local_2c.y == 0.0f) && (local_2c.z == 0.0f)) {
			local_38.x = dest[1].y;
			local_38.y = dest[1].z;
			local_38.z = dest[2].x;
			pppCopyVector__FR3Vec3Vec(&local_2c, &local_38);
		}

		local_5c.x = local_2c.x;
		local_5c.y = local_2c.y;
		local_5c.z = local_2c.z;
		pppNormalize__FR3Vec3Vec((float*)&local_2c, &local_5c);
	}

	local_98.x = local_20.x;
	local_98.y = local_20.y;
	local_98.z = local_20.z;
	local_98.w = 1.0f;
	local_88.x = local_2c.x;
	local_88.y = local_2c.y;
	local_88.z = local_2c.z;
	local_88.w = 1.0f;
	C_QUATLerp(&local_88, &local_98, &local_78, param_2->m_dataValIndex);
	PSQUATNormalize(&local_78, &local_78);

	local_68.x = local_78.x;
	local_68.y = local_78.y;
	local_68.z = local_78.z;
	fVar1 = *(f32*)((u8*)pppMngStPtr + 0x24);
	PSVECScale(&local_68, &local_68, dest[2].y * fVar1);

	local_a4.x = *(f32*)((u8*)pppMngStPtr + 0x8);
	local_a4.y = *(f32*)((u8*)pppMngStPtr + 0xc);
	local_a4.z = *(f32*)((u8*)pppMngStPtr + 0x10);
	pppAddVector__FR3Vec3Vec3Vec(&local_44, &local_68, &local_a4);

	local_b0.x = *(f32*)((u8*)pppMngStPtr + 0x8);
	local_b0.y = *(f32*)((u8*)pppMngStPtr + 0xc);
	local_b0.z = *(f32*)((u8*)pppMngStPtr + 0x10);
	pppCopyVector__FR3Vec3Vec((Vec*)((u8*)pppMngStPtr + 0x48), &local_b0);

	pppCopyVector__FR3Vec3Vec((Vec*)((u8*)pppMngStPtr + 0x8), &local_44);
	pppMngStPtr->m_matrix.value[0][3] = local_44.x;
	pppMngStPtr->m_matrix.value[1][3] = local_44.y;
	pppMngStPtr->m_matrix.value[2][3] = local_44.z;
}

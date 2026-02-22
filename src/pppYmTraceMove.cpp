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
	Vec local_20;
	Vec local_38;
	Vec local_2c;
	u32* mngWords;

	mngWords = (u32*)pppMngStPtr;
	dest = (Vec*)((u8*)pppYmTraceMove + 0x80 + *param_2->m_serializedDataOffsets);

	((u32*)&local_2c)[0] = mngWords[0x58 / 4];
	((u32*)&local_2c)[1] = mngWords[0x5c / 4];
	((u32*)&local_2c)[2] = mngWords[0x60 / 4];

	((u32*)&local_20)[0] = mngWords[0x68 / 4];
	((u32*)&local_20)[1] = mngWords[0x6c / 4];
	((u32*)&local_20)[2] = mngWords[0x70 / 4];

	pppSubVector__FR3Vec3Vec3Vec((Vec*)&dest[1].y, &local_20, &local_2c);
	((u32*)&local_38)[0] = ((u32*)&dest[1].y)[0];
	((u32*)&local_38)[1] = ((u32*)&dest[1].y)[1];
	((u32*)&local_38)[2] = ((u32*)&dest[1].y)[2];
	pppCopyVector__FR3Vec3Vec(dest, &local_38);
	dest[3].x = 0.0f;
	dest[2].z = 0.0f;
	dest[2].y = 0.0f;
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
	_pppMngSt* pppMngSt;
	u8* owner;
	Vec* dest;
	Vec local_128;
	Vec local_11c;
	Vec local_110;
	Vec local_104;
	Vec local_f8;
	Vec local_ec;
	Vec local_e0;
	Vec local_d4;
	Vec local_c8;
	Quaternion local_bc;
	Quaternion local_ac;
	Quaternion local_9c;
	Vec local_8c;
	Vec local_80;
	Vec local_74;
	Vec local_68;
	Vec local_5c;
	Vec local_50;
	Vec local_44;
	Vec local_38;
	Vec local_2c;
	Vec local_20;

	if (DAT_8032ed70 != 0) {
		return;
	}

	pppMngSt = pppMngStPtr;
	dest = (Vec*)((u8*)pppYmTraceMove + 0x80 + *param_3->m_serializedDataOffsets);
	owner = *(u8**)((u8*)pppMngSt + 0xdc);

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

		local_80.x = dest[1].y;
		local_80.y = dest[1].z;
		local_80.z = dest[2].x;
		pppCopyVector__FR3Vec3Vec(&local_2c, &local_80);
	} else {
		local_74.x = *(f32*)(owner + 0x15c);
		local_74.y = *(f32*)(owner + 0x160);
		local_74.z = *(f32*)(owner + 0x164);

		local_68.x = *(f32*)((u8*)pppMngSt + 0x8);
		local_68.y = *(f32*)((u8*)pppMngSt + 0xc);
		local_68.z = *(f32*)((u8*)pppMngSt + 0x10);
		pppSubVector__FR3Vec3Vec3Vec(&local_20, &local_74, &local_68);

		local_20.y = local_20.y + param_2->m_payload;
		local_5c.x = local_20.x;
		local_5c.y = local_20.y;
		local_5c.z = local_20.z;
		pppNormalize__FR3Vec3Vec((float*)&local_20, &local_5c);

		local_50.x = local_20.x;
		local_50.y = local_20.y;
		local_50.z = local_20.z;
		pppCopyVector__FR3Vec3Vec(dest, &local_50);

		local_44.x = *(f32*)((u8*)pppMngSt + 0x48);
		local_44.y = *(f32*)((u8*)pppMngSt + 0x4c);
		local_44.z = *(f32*)((u8*)pppMngSt + 0x50);
		local_38.x = *(f32*)((u8*)pppMngSt + 0x8);
		local_38.y = *(f32*)((u8*)pppMngSt + 0xc);
		local_38.z = *(f32*)((u8*)pppMngSt + 0x10);
		pppSubVector__FR3Vec3Vec3Vec(&local_2c, &local_38, &local_44);

		if ((local_2c.x == 0.0f) && (local_2c.y == 0.0f) && (local_2c.z == 0.0f)) {
			local_e0.x = dest[1].y;
			local_e0.y = dest[1].z;
			local_e0.z = dest[2].x;
			pppCopyVector__FR3Vec3Vec(&local_2c, &local_e0);
		}

		local_d4.x = local_2c.x;
		local_d4.y = local_2c.y;
		local_d4.z = local_2c.z;
		pppNormalize__FR3Vec3Vec((float*)&local_2c, &local_d4);
	}

	local_ac.x = local_20.x;
	local_ac.y = local_20.y;
	local_ac.z = local_20.z;
	local_ac.w = 1.0f;
	local_bc.x = local_2c.x;
	local_bc.y = local_2c.y;
	local_bc.z = local_2c.z;
	local_bc.w = 1.0f;
	C_QUATLerp(&local_bc, &local_ac, &local_9c, param_2->m_dataValIndex);
	PSQUATNormalize(&local_9c, &local_9c);

	local_8c.x = local_9c.x;
	local_8c.y = local_9c.y;
	local_8c.z = local_9c.z;
	PSVECScale(&local_8c, &local_8c, dest[2].y * *(f32*)((u8*)pppMngSt + 0x24));

	local_110.x = *(f32*)((u8*)pppMngSt + 0x8);
	local_110.y = *(f32*)((u8*)pppMngSt + 0xc);
	local_110.z = *(f32*)((u8*)pppMngSt + 0x10);
	local_104.x = local_8c.x;
	local_104.y = local_8c.y;
	local_104.z = local_8c.z;
	pppAddVector__FR3Vec3Vec3Vec(&local_ec, &local_104, &local_110);

	local_11c.x = *(f32*)((u8*)pppMngSt + 0x8);
	local_11c.y = *(f32*)((u8*)pppMngSt + 0xc);
	local_11c.z = *(f32*)((u8*)pppMngSt + 0x10);
	pppCopyVector__FR3Vec3Vec((Vec*)((u8*)pppMngSt + 0x48), &local_11c);

	local_128.x = local_ec.x;
	local_128.y = local_ec.y;
	local_128.z = local_ec.z;
	pppCopyVector__FR3Vec3Vec((Vec*)((u8*)pppMngSt + 0x8), &local_128);

	pppMngSt->m_matrix.value[0][3] = local_ec.x;
	pppMngSt->m_matrix.value[1][3] = local_ec.y;
	pppMngSt->m_matrix.value[2][3] = local_ec.z;
}

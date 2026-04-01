#include "ffcc/pppYmTraceMove.h"
#include "ffcc/partMng.h"
#include "ffcc/symbols_shared.h"
#include "dolphin/mtx.h"


extern "C" {
	void pppCopyVector__FR3Vec3Vec(Vec*, const Vec*);
	void pppSubVector__FR3Vec3Vec3Vec(Vec*, const Vec*, const Vec*);
	void pppNormalize__FR3Vec3Vec(float*, Vec*);
	void pppAddVector__FR3Vec3Vec3Vec(Vec*, const Vec*, const Vec*);
}

struct pppYmTraceMoveMngStRaw {
	char pad00[0x08];
	Vec m_position;
	char pad14[0x34];
	float m_userFloat0;
	float m_userFloat1;
	Vec m_savedPosition;
	char pad5c[0x80];
	void* m_owner;
};

/*
 * --INFO--
 * PAL Address: 0x800d4bd0
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmTraceMove(pppYmTraceMove* pppYmTraceMove, pppYmTraceMoveUnkC* param_2)
{
	Vec* dest = (Vec*)((u8*)pppYmTraceMove + 0x80 + *param_2->m_serializedDataOffsets);
	Vec savedPosition = *(Vec*)&pppMngStPtr->m_savedPosition.z;
	Vec paramVec = pppMngStPtr->m_paramVec0;
	f32 zero;

	pppSubVector__FR3Vec3Vec3Vec((Vec*)&dest[1].y, &paramVec, &savedPosition);
	Vec dir = *(Vec*)&dest[1].y;
	pppCopyVector__FR3Vec3Vec(dest, &dir);
	zero = kPppYmTraceMoveZero;
	dest[3].x = zero;
	dest[2].z = zero;
	dest[2].y = zero;
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
void pppFrameYmTraceMove(pppYmTraceMove* pppYmTraceMove, pppYmTraceMoveUnkB* param_2, pppYmTraceMoveUnkC* param_3)
{
	_pppMngSt* pppMngSt;
	pppYmTraceMoveMngStRaw* rawPppMngSt;
	u8* owner;
	Vec* dest;
	Vec local_128;
	Vec local_11c;
	Vec local_110;
	Vec local_104;
	Vec local_ec;
	Vec local_98;
	Vec local_8c;
	Vec local_74;
	Vec local_68;
	Vec local_5c;
	Vec local_50;
	Vec local_44;
	Vec local_38;
	Vec local_2c;
	Vec local_20;
	Quaternion local_80;
	Quaternion local_70;
	Quaternion local_60;

	if (gPppCalcDisabled != 0) {
		return;
	}

	pppMngSt = pppMngStPtr;
	rawPppMngSt = (pppYmTraceMoveMngStRaw*)pppMngSt;
	dest = (Vec*)((u8*)pppYmTraceMove + 0x80 + *param_3->m_serializedDataOffsets);
	owner = (u8*)rawPppMngSt->m_owner;

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

		local_98.x = dest[1].y;
		local_98.y = dest[1].z;
		local_98.z = dest[2].x;
		pppCopyVector__FR3Vec3Vec(&local_2c, &local_98);
	} else {
		local_74.x = *(f32*)(owner + 0x15c);
		local_74.y = *(f32*)(owner + 0x160);
		local_74.z = *(f32*)(owner + 0x164);

		local_68.x = rawPppMngSt->m_position.x;
		local_68.y = rawPppMngSt->m_position.y;
		local_68.z = rawPppMngSt->m_position.z;
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

		local_44.x = rawPppMngSt->m_userFloat0;
		local_44.y = rawPppMngSt->m_userFloat1;
		local_44.z = rawPppMngSt->m_savedPosition.x;
		local_38.x = rawPppMngSt->m_position.x;
		local_38.y = rawPppMngSt->m_position.y;
		local_38.z = rawPppMngSt->m_position.z;
		pppSubVector__FR3Vec3Vec3Vec(&local_2c, &local_38, &local_44);

		if ((local_2c.x == 0.0f) && (local_2c.y == 0.0f) && (local_2c.z == 0.0f)) {
			local_ec.x = dest[1].y;
			local_ec.y = dest[1].z;
			local_ec.z = dest[2].x;
			pppCopyVector__FR3Vec3Vec(&local_2c, &local_ec);
		}
		local_44.x = local_2c.x;
		local_44.y = local_2c.y;
		local_44.z = local_2c.z;
		pppNormalize__FR3Vec3Vec((float*)&local_2c, &local_44);
	}

	local_60.x = local_20.x;
	local_60.y = local_20.y;
	local_60.z = local_20.z;
	local_60.w = 1.0f;
	local_70.x = local_2c.x;
	local_70.y = local_2c.y;
	local_70.z = local_2c.z;
	local_70.w = 1.0f;
	C_QUATLerp(&local_70, &local_60, &local_80, param_2->m_dataValIndex);
	PSQUATNormalize(&local_80, &local_80);

	local_8c.x = local_80.x;
	local_8c.y = local_80.y;
	local_8c.z = local_80.z;
	PSVECScale(&local_8c, &local_8c, dest[2].y * *(f32*)((u8*)pppMngSt + 0x54));

	local_110.x = pppMngSt->m_position.x;
	local_110.y = pppMngSt->m_position.y;
	local_110.z = pppMngSt->m_position.z;
	local_104.x = local_8c.x;
	local_104.y = local_8c.y;
	local_104.z = local_8c.z;
	pppAddVector__FR3Vec3Vec3Vec(&local_ec, &local_104, &local_110);

	local_11c.x = pppMngSt->m_position.x;
	local_11c.y = pppMngSt->m_position.y;
	local_11c.z = pppMngSt->m_position.z;
	pppCopyVector__FR3Vec3Vec((Vec*)((u8*)pppMngSt + 0x48), &local_11c);

	local_128.x = local_ec.x;
	local_128.y = local_ec.y;
	local_128.z = local_ec.z;
	pppCopyVector__FR3Vec3Vec(&pppMngSt->m_position, &local_128);

	pppMngStPtr->m_matrix.value[0][3] = local_ec.x;
	pppMngStPtr->m_matrix.value[1][3] = local_ec.y;
	pppMngStPtr->m_matrix.value[2][3] = local_ec.z;
}

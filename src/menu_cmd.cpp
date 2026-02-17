#include "ffcc/menu_cmd.h"
#include "ffcc/joybus.h"
#include "ffcc/p_game.h"
#include "dolphin/types.h"

extern "C" int GetItemType__8CMenuPcsFii(CMenuPcs*, int, int);
extern "C" int GetItemIcon__8CMenuPcsFi(CMenuPcs*, int);
extern "C" void CalcStatus__12CCaravanWorkFv(void*);
extern "C" unsigned int CmdCtrlCur__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int CmdOpen0__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int CmdClose0__8CMenuPcsFv(CMenuPcs*);
extern "C" void CmdInit1__8CMenuPcsFv(CMenuPcs*);
extern "C" int UniteOpenAnim__8CMenuPcsFi(CMenuPcs*, int);
extern "C" unsigned int CmdOpen1__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int CmdClose1__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int CmdClose2__8CMenuPcsFv(CMenuPcs*);

extern double DOUBLE_80332a58;
extern double DOUBLE_80332a60;
extern double DOUBLE_80332a68;
extern double DOUBLE_80332a78;
extern float FLOAT_80332a70;
extern float FLOAT_80332a88;
extern const char* PTR_s_Flamestrike_80214d28[];
extern const char* PTR_s_Feuer_Hieb_80214d3c[];
extern const char* PTR_s_Colpo_Fire_80214d50[];
extern const char* PTR_s_Pyro_Frappe_80214d64[];
extern const char* PTR_s_Efecto_Fuego_80214d78[];

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
bool IsMagicArti(int)
{
	// TODO
	return false;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmdInit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmdInit0()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmdInit1()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmdInit2()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmdOpen()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8014f4e8
 * PAL Size: 1424b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CmdCtrl()
{
	u8* self = reinterpret_cast<u8*>(this);
	u32 actionHandled = 0;
	s32 caravanWork = Game.game.m_scriptFoodBase[0];
	s32 cmd = *reinterpret_cast<s32*>(self + 0x82c);

	CalcStatus__12CCaravanWorkFv(reinterpret_cast<void*>(caravanWork));

	*reinterpret_cast<s16*>(cmd + 0x32) = *reinterpret_cast<s16*>(cmd + 0x30);

	s16 mode = *reinterpret_cast<s16*>(cmd + 0x30);
	s16 state = *reinterpret_cast<s16*>(cmd + 0x12);

	if ((mode == 0) || ((mode != 0) && (state == 1))) {
		actionHandled = CmdCtrlCur__8CMenuPcsFv(this);
	} else if ((mode == 1) && (state == 0)) {
		actionHandled = CmdOpen0__8CMenuPcsFv(this);
		if (actionHandled != 0) {
			actionHandled = 0;
			*reinterpret_cast<s16*>(cmd + 0x12) = static_cast<s16>(*reinterpret_cast<s16*>(cmd + 0x12) + 1);
		}
	} else if ((mode == 1) && (state == 2)) {
		actionHandled = CmdClose0__8CMenuPcsFv(this);
		if (actionHandled != 0) {
			if (*reinterpret_cast<u8*>(cmd + 8) == 0) {
				*reinterpret_cast<s16*>(cmd + 0x12) = static_cast<s16>(*reinterpret_cast<s16*>(cmd + 0x12) + 1);
			} else {
				*reinterpret_cast<s16*>(cmd + 0x12) = 0;
				*reinterpret_cast<s16*>(cmd + 0x30) = 3;
				*reinterpret_cast<s16*>(cmd + 0x22) = 0;
				*reinterpret_cast<u8*>(cmd + 8) = 0;
				CmdInit1__8CMenuPcsFv(this);
			}
			actionHandled = 0;
		}
	} else if ((mode == 1) && (state == 3)) {
		actionHandled = static_cast<u32>(UniteOpenAnim__8CMenuPcsFi(this, -1));
		if (actionHandled != 0) {
			*reinterpret_cast<s16*>(cmd + 0x12) = 0;
			*reinterpret_cast<s16*>(cmd + 0x30) = 0;
			*reinterpret_cast<s16*>(cmd + 0x22) = 0;
			CmdInit1__8CMenuPcsFv(this);
			actionHandled = 0;
		}
	} else if ((mode == 2) && (state == 0)) {
		actionHandled = CmdOpen1__8CMenuPcsFv(this);
		if (actionHandled != 0) {
			actionHandled = 0;
			*reinterpret_cast<s16*>(cmd + 0x12) = static_cast<s16>(*reinterpret_cast<s16*>(cmd + 0x12) + 1);
		}
	} else if ((mode == 2) && (state == 2)) {
		actionHandled = CmdClose1__8CMenuPcsFv(this);
		if (actionHandled != 0) {
			if (*reinterpret_cast<u8*>(cmd + 8) == 0) {
				*reinterpret_cast<s16*>(cmd + 0x30) = 0;
			} else {
				*reinterpret_cast<s16*>(cmd + 0x14) = 0;
				*reinterpret_cast<s16*>(cmd + 0x30) = 3;
			}
			actionHandled = 0;
			*reinterpret_cast<s16*>(cmd + 0x12) = 0;
			*reinterpret_cast<s16*>(cmd + 0x22) = 0;
		}
	} else if ((mode == 3) && (state == 0)) {
		*reinterpret_cast<s16*>(cmd + 0x22) = static_cast<s16>(*reinterpret_cast<s16*>(cmd + 0x22) + 1);

		s32 selected = static_cast<s32>(*reinterpret_cast<s16*>(cmd + 0x26));
		s32 prev = selected - 1;
		for (; prev > 2; --prev) {
			if (*reinterpret_cast<s16*>(caravanWork + prev * 2 + 0x214) >= 0) {
				break;
			}
		}

		s32 next = selected + 1;
		s32 limit = static_cast<s32>(*reinterpret_cast<s16*>(caravanWork + 0xbaa));
		for (; next < limit; ++next) {
			if (*reinterpret_cast<s16*>(caravanWork + next * 2 + 0x214) >= 0) {
				break;
			}
		}

		s16* list = *reinterpret_cast<s16**>(self + 0x850);
		float minAnim = static_cast<float>(DOUBLE_80332a60);
		double timer = static_cast<double>(static_cast<s32>(*reinterpret_cast<s16*>(cmd + 0x22)));
		double anim = -((DOUBLE_80332a68 * timer) - DOUBLE_80332a58);
		for (s32 i = 0; i < static_cast<s32>(list[0]); i++) {
			if ((i < prev) || (next < i)) {
				float value = static_cast<float>(anim);
				if (static_cast<double>(value) < static_cast<double>(minAnim)) {
					value = FLOAT_80332a88;
				}
				*reinterpret_cast<float*>(list + i * 0x20 + 0x0c) = value;
			}
		}

		actionHandled = (static_cast<double>(static_cast<s32>(*reinterpret_cast<s16*>(cmd + 0x22))) >= DOUBLE_80332a78);
		if (actionHandled != 0) {
			*reinterpret_cast<s16*>(cmd + mode * 2 + 0x26) = static_cast<s16>(prev);
			actionHandled = 0;
			*reinterpret_cast<s16*>(cmd + 0x12) = static_cast<s16>(*reinterpret_cast<s16*>(cmd + 0x12) + 1);
		}
	} else if ((mode == 3) && (state == 2)) {
		actionHandled = CmdClose2__8CMenuPcsFv(this);
		if (actionHandled != 0) {
			actionHandled = 0;
			*reinterpret_cast<s16*>(cmd + 0x12) = 0;
			*reinterpret_cast<s16*>(cmd + 0x30) = 0;
			*reinterpret_cast<s16*>(cmd + 0x22) = 0;
			*reinterpret_cast<u8*>(cmd + 8) = 0;
		}
	}

	if (actionHandled == 0) {
		return;
	}

	s16* list = *reinterpret_cast<s16**>(self + 0x850);
	for (s32 i = 0; i < static_cast<s32>(list[0]); i++) {
		*reinterpret_cast<float*>(list + i * 0x20 + 0x0c) = FLOAT_80332a70;
		*reinterpret_cast<float*>(list + i * 0x20 + 0x0e) = FLOAT_80332a70;
	}

	u32 count = static_cast<u32>(*reinterpret_cast<s16*>(caravanWork + 0xbaa));
	for (s32 i = static_cast<s32>(count) - 1, idx = 0; i >= 0; i--, idx++) {
		*reinterpret_cast<s32*>(list + i * 0x20 + 0x14) = idx;
		*reinterpret_cast<s32*>(list + i * 0x20 + 0x16) = 3;
	}

	*reinterpret_cast<u8*>(cmd + 8) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8014f2e8
 * PAL Size: 512b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::CmdClose()
{
	u8* self = reinterpret_cast<u8*>(this);
	s32 cmd = *reinterpret_cast<s32*>(self + 0x82c);
	if (*reinterpret_cast<u8*>(cmd + 8) == 0) {
		if (UniteCloseAnim(-1) != 0) {
			*reinterpret_cast<s16*>(cmd + 0x22) = 0;
			*reinterpret_cast<u8*>(cmd + 8) = 1;
		}
		return 0;
	}

	s32 doneCount = 0;
	*reinterpret_cast<s16*>(cmd + 0x22) = *reinterpret_cast<s16*>(cmd + 0x22) + 1;

	s16* list = *reinterpret_cast<s16**>(self + 0x850);
	u32 count = static_cast<u32>(list[0]);
	s16* entry = list + 4;
	s32 closeTimer = static_cast<s32>(*reinterpret_cast<s16*>(cmd + 0x22));
	u32 remaining = count;

	if (remaining != 0) {
		do {
			if (*reinterpret_cast<s32*>(entry + 0x12) <= closeTimer) {
				if (closeTimer < (*reinterpret_cast<s32*>(entry + 0x12) + *reinterpret_cast<s32*>(entry + 0x14))) {
					*reinterpret_cast<s32*>(entry + 0x10) = *reinterpret_cast<s32*>(entry + 0x10) + 1;
					*reinterpret_cast<float*>(entry + 8) =
					    static_cast<float>(
					        -((1.0 / static_cast<double>(*reinterpret_cast<s32*>(entry + 0x14))) *
					              static_cast<double>(*reinterpret_cast<s32*>(entry + 0x10)) -
					          1.0));
					if (static_cast<double>(*reinterpret_cast<float*>(entry + 8)) < 0.0) {
						*reinterpret_cast<float*>(entry + 8) = 0.0f;
					}
				} else {
					doneCount = doneCount + 1;
					*reinterpret_cast<float*>(entry + 8) = 0.0f;
				}
			}
			entry = entry + 0x20;
			remaining = remaining - 1;
		} while (remaining != 0);
	}

	if (list[0] == doneCount) {
		entry = list + 4;
		if (count != 0) {
			u32 blockCount = count >> 3;
			if (blockCount != 0) {
				do {
					entry[0x12] = 0;
					entry[0x13] = 0;
					entry[0x14] = 0;
					entry[0x15] = 1;
					*reinterpret_cast<float*>(entry + 8) = 0.0f;
					entry[0x32] = 0;
					entry[0x33] = 0;
					entry[0x34] = 0;
					entry[0x35] = 1;
					*reinterpret_cast<float*>(entry + 0x28) = 0.0f;
					entry[0x52] = 0;
					entry[0x53] = 0;
					entry[0x54] = 0;
					entry[0x55] = 1;
					*reinterpret_cast<float*>(entry + 0x48) = 0.0f;
					entry[0x72] = 0;
					entry[0x73] = 0;
					entry[0x74] = 0;
					entry[0x75] = 1;
					*reinterpret_cast<float*>(entry + 0x68) = 0.0f;
					entry[0x92] = 0;
					entry[0x93] = 0;
					entry[0x94] = 0;
					entry[0x95] = 1;
					*reinterpret_cast<float*>(entry + 0x88) = 0.0f;
					entry[0xb2] = 0;
					entry[0xb3] = 0;
					entry[0xb4] = 0;
					entry[0xb5] = 1;
					*reinterpret_cast<float*>(entry + 0xa8) = 0.0f;
					entry[0xd2] = 0;
					entry[0xd3] = 0;
					entry[0xd4] = 0;
					entry[0xd5] = 1;
					*reinterpret_cast<float*>(entry + 200) = 0.0f;
					entry[0xf2] = 0;
					entry[0xf3] = 0;
					entry[0xf4] = 0;
					entry[0xf5] = 1;
					*reinterpret_cast<float*>(entry + 0xe8) = 0.0f;
					entry = entry + 0x100;
					blockCount = blockCount - 1;
				} while (blockCount != 0);
				count = count & 7;
				if (count == 0) {
					return 1;
				}
			}
			do {
				entry[0x12] = 0;
				entry[0x13] = 0;
				entry[0x14] = 0;
				entry[0x15] = 1;
				*reinterpret_cast<float*>(entry + 8) = 0.0f;
				entry = entry + 0x20;
				count = count - 1;
			} while (count != 0);
		}
		return 1;
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: 5472b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CmdDraw()
{
	// Basic menu drawing operations
	int i;
	
	// Initialize graphics state
	for (i = 0; i < 16; i++) {
		// Placeholder drawing operations
	}
	
	// Main draw loop
	i = 0;
	do {
		// Draw menu elements
		i++;
	} while (i < 32);
}

/*
 * --INFO--
 * PAL Address: TODO  
 * PAL Size: 2836b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::CmdCtrlCur()
{
	// Cursor control for menu commands
	int cursorPos = 0;
	int maxPos = 8;
	
	// Basic cursor update logic
	if (cursorPos < maxPos) {
		cursorPos++;
	}
	
	// Input handling placeholder
	for (int i = 0; i < 16; i++) {
		// Process input states
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8014d0c4
 * PAL Size: 432b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::CmdOpen0()
{
	u8* self = reinterpret_cast<u8*>(this);
	u8* menuState = *reinterpret_cast<u8**>(self + 0x82c);

	*reinterpret_cast<s16*>(menuState + 0x22) = static_cast<s16>(*reinterpret_cast<s16*>(menuState + 0x22) + 1);
	s32 time = static_cast<s32>(*reinterpret_cast<s16*>(menuState + 0x22));
	s32 selectedOffset = static_cast<s32>(*reinterpret_cast<s16*>(menuState + 0x26)) * 0x40 + 8;

	if (time < 5) {
		*reinterpret_cast<s16*>(*reinterpret_cast<u8**>(self + 0x850) + selectedOffset) =
		    static_cast<s16>(*reinterpret_cast<s16*>(*reinterpret_cast<u8**>(self + 0x850) + selectedOffset) - 0x13);
	}

	s16* base = *reinterpret_cast<s16**>(self + 0x850);
	s32 doneCount = 0;
	s32 entryCount = static_cast<s32>(base[1]) - static_cast<s32>(base[0]);
	s16* entry = base + base[0] * 0x20 + 4;

	for (s32 i = 0; i < entryCount; i++) {
		if (*reinterpret_cast<s32*>(entry + 0x12) <= time) {
			if (time < (*reinterpret_cast<s32*>(entry + 0x12) + *reinterpret_cast<s32*>(entry + 0x14))) {
				*reinterpret_cast<s32*>(entry + 0x10) = *reinterpret_cast<s32*>(entry + 0x10) + 1;
				const f64 denom = static_cast<f64>(*reinterpret_cast<s32*>(entry + 0x14));
				const f64 numer = static_cast<f64>(*reinterpret_cast<s32*>(entry + 0x10));

				*reinterpret_cast<f32*>(entry + 8) = static_cast<f32>(numer / denom);
				if ((*reinterpret_cast<u32*>(entry + 0x16) & 2) == 0) {
					const f32 t = static_cast<f32>(numer / denom);
					*reinterpret_cast<f32*>(entry + 0x18) =
					    (*reinterpret_cast<f32*>(entry + 0x1c) - static_cast<f32>(entry[0])) * t;
					*reinterpret_cast<f32*>(entry + 0x1a) =
					    (*reinterpret_cast<f32*>(entry + 0x1e) - static_cast<f32>(entry[1])) * t;
				}
			} else {
				doneCount++;
				*reinterpret_cast<f32*>(entry + 8) = 1.0f;
				*reinterpret_cast<f32*>(entry + 0x18) = 0.0f;
				*reinterpret_cast<f32*>(entry + 0x1a) = 0.0f;
			}
		}
		entry += 0x20;
	}

	return static_cast<unsigned int>(entryCount == doneCount);
}

/*
 * --INFO--
 * PAL Address: 0x8014cef8
 * PAL Size: 460b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::CmdClose0()
{
	u8* self = reinterpret_cast<u8*>(this);
	u8* menuState = *reinterpret_cast<u8**>(self + 0x82c);

	*reinterpret_cast<s16*>(menuState + 0x22) = static_cast<s16>(*reinterpret_cast<s16*>(menuState + 0x22) + 1);
	s32 time = static_cast<s32>(*reinterpret_cast<s16*>(menuState + 0x22));
	s32 selectedOffset = static_cast<s32>(*reinterpret_cast<s16*>(menuState + 0x26)) * 0x40 + 8;

	if (time > 7) {
		*reinterpret_cast<s16*>(*reinterpret_cast<u8**>(self + 0x850) + selectedOffset) =
		    static_cast<s16>(*reinterpret_cast<s16*>(*reinterpret_cast<u8**>(self + 0x850) + selectedOffset) + 0x13);
	}

	s16* base = *reinterpret_cast<s16**>(self + 0x850);
	s32 doneCount = 0;
	s32 entryCount = static_cast<s32>(base[1]) - static_cast<s32>(base[0]);
	s16* entry = base + base[0] * 0x20 + 4;

	for (s32 i = 0; i < entryCount; i++) {
		if (*reinterpret_cast<s32*>(entry + 0x12) <= time) {
			if (time < (*reinterpret_cast<s32*>(entry + 0x12) + *reinterpret_cast<s32*>(entry + 0x14))) {
				*reinterpret_cast<s32*>(entry + 0x10) = *reinterpret_cast<s32*>(entry + 0x10) + 1;
				const f64 denom = static_cast<f64>(*reinterpret_cast<s32*>(entry + 0x14));
				const f64 numer = static_cast<f64>(*reinterpret_cast<s32*>(entry + 0x10));

				*reinterpret_cast<f32*>(entry + 8) = static_cast<f32>(1.0 - (numer / denom));
				if ((*reinterpret_cast<u32*>(entry + 0x16) & 2) == 0) {
					const f32 t = static_cast<f32>(1.0 - (numer / denom));
					*reinterpret_cast<f32*>(entry + 0x18) =
					    (*reinterpret_cast<f32*>(entry + 0x1c) - static_cast<f32>(entry[0])) * t;
					*reinterpret_cast<f32*>(entry + 0x1a) =
					    (*reinterpret_cast<f32*>(entry + 0x1e) - static_cast<f32>(entry[1])) * t;
				}
			} else {
				doneCount++;
				*reinterpret_cast<f32*>(entry + 8) = 0.0f;
				*reinterpret_cast<f32*>(entry + 0x18) = 0.0f;
				*reinterpret_cast<f32*>(entry + 0x1a) = 0.0f;
			}
		}
		entry += 0x20;
	}

	if (entryCount == doneCount) {
		*reinterpret_cast<s16*>(*reinterpret_cast<u8**>(self + 0x850) + selectedOffset) =
		    *reinterpret_cast<s16*>(*reinterpret_cast<u8**>(self + 0x850) + 8);
	}

	return static_cast<unsigned int>(entryCount == doneCount);
}

/*
 * --INFO--
 * PAL Address: 0x8014cce0
 * PAL Size: 536b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetCmdItem()
{
	u32 scriptFood = Game.game.m_scriptFoodBase[0];
	s16* list = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
	s16* write = list;
	s32 count = 0;
	u32 itemIndexPtr = scriptFood + 0xb6;

	for (s32 i = 0; i < 0x40; i++) {
		s32 itemType = GetItemType__8CMenuPcsFii(this, i, 0);
		if ((itemType != 0) && (itemType != 5) && (itemType != 6) && (itemType != 8) && (itemType != 9)) {
			if ((itemType != 1) ||
			    (static_cast<u32>(GetItemIcon__8CMenuPcsFi(this, *reinterpret_cast<s16*>(itemIndexPtr))) ==
			     (*reinterpret_cast<u16*>(scriptFood + 0x3e0) & 3))) {
				write++;
				*write = static_cast<s16>(i);
				count++;
			}
		}
		itemIndexPtr += 2;
	}

	s16* write2 = list + count;
	u32 artifactPtr = scriptFood;
	for (s32 i = 0; i < 0x49; i++) {
		s32 arti = i + 0x9f;
		if (*reinterpret_cast<s16*>(artifactPtr + 0x136) == arti) {
			if ((arti > 0xde) && (arti < 0xe4)) {
				count++;
				write2++;
				*write2 = static_cast<s16>(i + 0x40);
			}
		}
		artifactPtr += 2;
	}

	s16* write3 = list + count;
	if ((*reinterpret_cast<s16*>(scriptFood + 0x1f6) > 0xde) && (*reinterpret_cast<s16*>(scriptFood + 0x1f6) < 0xe4)) {
		count++;
		write3++;
		*write3 = 0xa0;
	}
	if ((*reinterpret_cast<s16*>(scriptFood + 0x1f8) > 0xde) && (*reinterpret_cast<s16*>(scriptFood + 0x1f8) < 0xe4)) {
		count++;
		write3++;
		*write3 = 0xa1;
	}
	if ((*reinterpret_cast<s16*>(scriptFood + 0x1fa) > 0xde) && (*reinterpret_cast<s16*>(scriptFood + 0x1fa) < 0xe4)) {
		count++;
		write3++;
		*write3 = 0xa2;
	}
	if ((*reinterpret_cast<s16*>(scriptFood + 0x1fc) > 0xde) && (*reinterpret_cast<s16*>(scriptFood + 0x1fc) < 0xe4)) {
		count++;
		write3[1] = 0xa3;
	}

	*reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0)) = static_cast<s16>(count + 2);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ChkCmdActive(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ChkUnite(int, int (*) [2])
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmdUnite(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmdDismantle(int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8014ba20
 * PAL Size: 3228b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawUniteList()
{
	// Basic implementation structure for unite list drawing
	int i;
	int j;
	bool isActive = false;
	int itemCount = 0;
	
	// Initialize graphics state
	// GXSetBlendMode operations would go here
	
	// Main processing loop for unite items
	for (i = 0; i < 16; i++) {
		if (itemCount > 0) {
			isActive = true;
		}
		
		// Draw unite list item
		for (j = 0; j < 8; j++) {
			// Item rendering logic
		}
		
		itemCount++;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::UniteOpenAnim(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMenuPcs::UniteCloseAnim(int)
{
	// TODO
	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmdOpen1()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmdClose1()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmdOpen2()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmdClose2()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
const char* CMenuPcs::GetSkillStr(int index)
{
	if (Game.game.m_gameWork.m_languageId == '\x03') {
		return PTR_s_Colpo_Fire_80214d50[index];
	}
	if (Game.game.m_gameWork.m_languageId < 3) {
		if ((Game.game.m_gameWork.m_languageId != '\x01') && (Game.game.m_gameWork.m_languageId != '\0')) {
			return PTR_s_Feuer_Hieb_80214d3c[index];
		}
	} else {
		if (Game.game.m_gameWork.m_languageId == '\x05') {
			return PTR_s_Efecto_Fuego_80214d78[index];
		}
		if (Game.game.m_gameWork.m_languageId < 5) {
			return PTR_s_Pyro_Frappe_80214d64[index];
		}
	}
	return PTR_s_Flamestrike_80214d28[index];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetFontItem()
{
	// TODO
}

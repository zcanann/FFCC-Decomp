#include "ffcc/menu_cmd.h"
#include "ffcc/joybus.h"
#include "ffcc/pad.h"
#include "ffcc/p_game.h"
#include "ffcc/sound.h"
#include "dolphin/types.h"

extern "C" int GetItemType__8CMenuPcsFii(CMenuPcs*, int, int);
extern "C" int GetItemIcon__8CMenuPcsFi(CMenuPcs*, int);
extern "C" int EquipChk__8CMenuPcsFi(CMenuPcs*, int);
extern "C" void CalcStatus__12CCaravanWorkFv(void*);
extern "C" void ChgCmdLst__12CCaravanWorkFii(void*, int, int);
extern "C" void UniteComList__12CCaravanWorkFiii(void*, int, int, int);
extern "C" void UnuniteComList__12CCaravanWorkFii(void*, int, int);
extern "C" unsigned int CmdCtrlCur__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int CmdOpen0__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int CmdClose0__8CMenuPcsFv(CMenuPcs*);
extern "C" void CmdInit1__8CMenuPcsFv(CMenuPcs*);
extern "C" void CmdInit2__8CMenuPcsFv(CMenuPcs*);
extern "C" int UniteOpenAnim__8CMenuPcsFi(CMenuPcs*, int);
extern "C" int ChkUnite__8CMenuPcsFiPA2_i(CMenuPcs*, int, int (*)[2]);
extern "C" unsigned int CmdOpen1__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int CmdClose1__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int CmdClose2__8CMenuPcsFv(CMenuPcs*);

extern double DOUBLE_80332a58;
extern double DOUBLE_80332a60;
extern double DOUBLE_80332a68;
extern double DOUBLE_80332a78;
extern double DOUBLE_80332a80;
extern double DOUBLE_80332a90;
extern double DOUBLE_80332a98;
extern double DOUBLE_80332aa0;
extern double DOUBLE_80332aa8;
extern float FLOAT_80332a70;
extern float FLOAT_80332ab0;
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
	bool blocked = false;
	u16 press;
	u16 hold;
	int caravanWork = Game.game.m_scriptFoodBase[0];

	if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
		blocked = true;
	}
	if (blocked) {
		press = 0;
	} else {
		press = Pad._8_2_;
	}

	blocked = false;
	if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
		blocked = true;
	}
	if (blocked) {
		hold = 0;
	} else {
		hold = *reinterpret_cast<u16*>(reinterpret_cast<u8*>(&Pad) + 0x20);
	}

	if (hold == 0) {
		return 0;
	}

	s16* menuState = *reinterpret_cast<s16**>(reinterpret_cast<u8*>(this) + 0x82C);
	int mode = menuState[0x18];

	if (mode == 0) {
		s16 cmdCount = *reinterpret_cast<s16*>(caravanWork + 0xBAA);

		if ((hold & 8) == 0) {
			if ((hold & 4) != 0) {
				if (menuState[0x13] < cmdCount - 1) {
					menuState[0x13]++;
				} else {
					menuState[0x13] = 2;
				}

				int cursor = menuState[0x13];
				if (*reinterpret_cast<s16*>(caravanWork + cursor * 2 + 0x214) < 0) {
					if (*reinterpret_cast<s16*>(caravanWork + (cursor + 1) * 2 + 0x214) < 0) {
						if (*reinterpret_cast<s16*>(caravanWork + (cursor + 2) * 2 + 0x214) >= 0) {
							menuState[0x13] = static_cast<s16>(cursor + 2);
						}
					} else {
						menuState[0x13] = static_cast<s16>(cursor + 1);
					}
					if (menuState[0x13] > cmdCount - 1) {
						menuState[0x13] = 2;
					}
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			}
		} else {
			if (menuState[0x13] < 3) {
				menuState[0x13] = static_cast<s16>(cmdCount - 1);
			} else {
				menuState[0x13]--;
			}

			int cursor = menuState[0x13];
			if (*reinterpret_cast<s16*>(caravanWork + cursor * 2 + 0x214) < 0) {
				if (*reinterpret_cast<s16*>(caravanWork + (cursor - 1) * 2 + 0x214) < 0) {
					if (*reinterpret_cast<s16*>(caravanWork + (cursor - 2) * 2 + 0x214) >= 0) {
						menuState[0x13] = static_cast<s16>(cursor - 2);
					}
				} else {
					menuState[0x13] = static_cast<s16>(cursor - 1);
				}
			}
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		}

		if ((hold & 0xC) == 0) {
			if ((press & 0x20) != 0) {
				menuState[0x0F] = 1;
				Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
				return 1;
			}
			if ((press & 0x40) != 0) {
				menuState[0x0F] = -1;
				Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
				return 1;
			}
			if ((press & 0x100) == 0) {
				if ((press & 0x200) != 0) {
					*reinterpret_cast<u8*>(menuState + 6) = 1;
					Sound.PlaySe(3, 0x40, 0x7F, 0);
					return 1;
				}
			} else {
				if (*reinterpret_cast<s16*>(caravanWork + menuState[0x13] * 2 + 0x214) == 0) {
					menuState[0x18] = 1;
				} else {
					*reinterpret_cast<u8*>(menuState + 6) = 0;
					menuState[0x18] = 2;
				}
				menuState[0x09] = 0;
				menuState[0x11] = 0;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
			}
		}
	} else if (mode == 1) {
		s16* list = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		int itemCount = static_cast<int>(list[0]);

		if ((hold & 8) == 0) {
			if ((hold & 4) != 0) {
				if (((itemCount < 9) || (menuState[0x14] < 7)) &&
				    ((itemCount <= 8) || ((itemCount - 1) > menuState[0x14]))) {
					if (itemCount < 9) {
						menuState[0x14] = 0;
					} else if (menuState[0x1A] < itemCount - 1) {
						menuState[0x1A]++;
					} else {
						menuState[0x1A] = 0;
					}
				} else {
					menuState[0x14]++;
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			}
		} else {
			if (menuState[0x14] == 0) {
				if (itemCount < 9) {
					menuState[0x14] = static_cast<s16>(itemCount - 1);
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				} else if (menuState[0x1A] == 0) {
					menuState[0x1A] = static_cast<s16>(itemCount - 1);
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				} else {
					menuState[0x1A]--;
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				}
			} else {
				menuState[0x14]--;
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			}
		}

		if ((hold & 0xC) == 0) {
			if ((press & 0x100) == 0) {
				if ((press & 0x200) != 0) {
					menuState[0x09]++;
					menuState[0x11] = 0;
					*reinterpret_cast<u8*>(menuState + 4) = 0;
					CmdInit2__8CMenuPcsFv(this);
					Sound.PlaySe(3, 0x40, 0x7F, 0);
				}
			} else {
				int selected = static_cast<int>(menuState[0x1A]) + static_cast<int>(menuState[0x14]);
				if (itemCount <= selected) {
					selected -= itemCount;
				}

				u32 canUse = 0;
				if (selected < 0 || list[0] <= selected) {
					canUse = 0;
				} else if (selected == 0) {
					canUse = static_cast<u32>(*reinterpret_cast<s16*>(caravanWork + menuState[0x13] * 2 + 0x204) >= 0);
				} else if (selected == 1) {
					int combo[5][2];
					canUse = static_cast<u32>(ChkUnite__8CMenuPcsFiPA2_i(this, menuState[0x13], combo) > 0);
				} else {
					canUse = static_cast<u32>(EquipChk__8CMenuPcsFi(this, static_cast<int>(list[selected - 1])) != 0);
				}

				if ((canUse & 0xFF) == 0) {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				} else {
					if (selected == 0) {
						ChgCmdLst__12CCaravanWorkFii(reinterpret_cast<void*>(caravanWork), menuState[0x13], -1);
					} else if (selected != 1) {
						ChgCmdLst__12CCaravanWorkFii(reinterpret_cast<void*>(caravanWork), menuState[0x13], list[selected - 1]);
					}

					*reinterpret_cast<u8*>(menuState + 4) = 0;
					if (selected != 0) {
						int comboChoice[2][2];
						int comboCount = ChkUnite__8CMenuPcsFiPA2_i(this, menuState[0x13], comboChoice);
						if (comboCount == 1) {
							UniteComList__12CCaravanWorkFiii(reinterpret_cast<void*>(caravanWork), comboChoice[0][1], 0, 0);
						} else if (comboCount > 1) {
							*reinterpret_cast<u8*>(menuState + 4) = 1;
						}
					}

					menuState[0x09]++;
					menuState[0x11] = 0;
					CmdInit2__8CMenuPcsFv(this);
					Sound.PlaySe(2, 0x40, 0x7F, 0);
				}
			}
		}
	} else if (mode == 2) {
		int maxPos;
		if (DOUBLE_80332a58 == static_cast<double>(*reinterpret_cast<float*>(
		                         reinterpret_cast<u8*>(*reinterpret_cast<s16**>(reinterpret_cast<u8*>(this) + 0x850)) +
		                         ((*reinterpret_cast<s16*>(*reinterpret_cast<s16**>(reinterpret_cast<u8*>(this) + 0x850) + 2) + 3) * 0x40 + 0x1C)))) {
			maxPos = 2;
		} else {
			maxPos = 3;
		}

		if ((hold & 8) == 0) {
			if ((hold & 4) != 0) {
				if (menuState[0x15] < maxPos - 1) {
					menuState[0x15]++;
				} else {
					menuState[0x15] = 0;
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			}
		} else {
			if (menuState[0x15] == 0) {
				menuState[0x15] = static_cast<s16>(maxPos - 1);
			} else {
				menuState[0x15]--;
			}
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		}

		if ((hold & 0xC) == 0) {
			menuState[0x0A] = 0;
			if ((press & 0x100) == 0) {
				if ((press & 0x200) != 0) {
					menuState[0x09]++;
					menuState[0x11] = 0;
					*reinterpret_cast<u8*>(menuState + 4) = 0xFF;
					Sound.PlaySe(3, 0x40, 0x7F, 0);
				}
			} else {
				menuState[0x09]++;
				menuState[0x11] = 0;
				*reinterpret_cast<u8*>(menuState + 4) = 1;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
			}
		}
	} else {
		if ((hold & 0xC) != 0) {
			int selected = menuState[0x13];
			int prev = selected - 1;
			int remaining = selected - 3;
			int check = caravanWork + prev * 2;
			if (prev > 2) {
				do {
					if (*reinterpret_cast<s16*>(check + 0x214) >= 0) {
						break;
					}
					check -= 2;
					prev--;
					remaining--;
				} while (remaining != 0);
			}

			int next = selected + 1;
			remaining = *reinterpret_cast<s16*>(caravanWork + 0xBAA) - next;
			check = caravanWork + next * 2;
			if (next < *reinterpret_cast<s16*>(caravanWork + 0xBAA)) {
				do {
					if (*reinterpret_cast<s16*>(check + 0x214) >= 0) {
						break;
					}
					check += 2;
					next++;
					remaining--;
				} while (remaining != 0);
			}

			s16* modeCursor = menuState + mode;
			if (modeCursor[0x13] == prev) {
				modeCursor[0x13] = static_cast<s16>(next);
			} else {
				modeCursor[0x13] = static_cast<s16>(prev);
			}
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		}

		if ((hold & 0xC) == 0) {
			*reinterpret_cast<u8*>(menuState + 4) = 0;
			menuState[0x0A] = 0;
			if ((press & 0x100) == 0) {
				if ((press & 0x200) != 0) {
					*reinterpret_cast<u8*>(menuState + 4) = 0xFF;
					menuState[0x09]++;
					menuState[0x11] = 0;
					Sound.PlaySe(3, 0x40, 0x7F, 0);
				}
			} else {
				menuState[0x09]++;
				menuState[0x11] = 0;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
			}
		}
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
int CMenuPcs::ChkUnite(int, int (*) [2])
{
	// TODO
	return 0;
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
 * PAL Address: 0x8014b244
 * PAL Size: 904b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::CmdOpen1()
{
	u8* self = reinterpret_cast<u8*>(this);
	const s32 caravanWork = Game.game.m_scriptFoodBase[0];
	s16* const cmd = *reinterpret_cast<s16**>(self + 0x82c);
	s16* const list = *reinterpret_cast<s16**>(self + 0x850);

	cmd[0x11] = static_cast<s16>(cmd[0x11] + 1);

	const s32 selected = static_cast<s32>(cmd[0x13]);
	const f32 t = static_cast<f32>(-((DOUBLE_80332a90 * static_cast<f64>(cmd[0x11])) - DOUBLE_80332a58));
	*reinterpret_cast<f32*>(list + selected * 0x20 + 0x0c) = t;

	s32 chainCount = 1;
	if (*reinterpret_cast<s16*>(caravanWork + (selected + 1) * 2 + 0x214) == -1) {
		chainCount = 2;
		*reinterpret_cast<f32*>(list + (selected + 1) * 0x20 + 0x0c) = t;
		if (*reinterpret_cast<s16*>(caravanWork + (selected + 2) * 2 + 0x214) == -1) {
			chainCount = 3;
			*reinterpret_cast<f32*>(list + (selected + 2) * 0x20 + 0x0c) = t;
		}
	}

	s32 slot = 3;
	for (s32 i = 0; i < 3; i++) {
		if (selected == static_cast<s32>(cmd[0x13 + i])) {
			slot = i;
			break;
		}
	}

	s16* const baseEntry = list + (static_cast<s32>(list[1]) + slot) * 0x20 + 4;
	s16* const animEntry = list + (static_cast<s32>(list[1]) + 3) * 0x20 + 4;

	if (*reinterpret_cast<u8*>(cmd + 6) == 0) {
		const s32 endX = static_cast<s32>(baseEntry[0] + baseEntry[2]) - static_cast<s32>(DOUBLE_80332a98);
		animEntry[0] = static_cast<s16>(endX);

		s32 uniteCount = 0;
		if (chainCount == 2) {
			int combo[5][2];
			uniteCount = ChkUnite__8CMenuPcsFiPA2_i(this, static_cast<int>(cmd[0x13]), combo);
		}

		animEntry[0x0A] = 1.0f;
		if (uniteCount != 0) {
			animEntry[0x0A] = static_cast<f32>(DOUBLE_80332aa0);
		}
		animEntry[2] = 0xC0;
		animEntry[3] = 0x40;
		animEntry[1] = static_cast<s16>(((-((static_cast<f64>(animEntry[3]) * animEntry[0x0A]) -
		                                    static_cast<f64>(baseEntry[3])) *
		                                   DOUBLE_80332a60) +
		                                  static_cast<f64>(baseEntry[1])) -
		                                 DOUBLE_80332aa8);
		animEntry[4] = FLOAT_80332ab0;
		animEntry[6] = FLOAT_80332ab0;
		*reinterpret_cast<s32*>(animEntry + 0x0e) = 0x39;
		*reinterpret_cast<u8*>(cmd + 6) = 1;
	}

	animEntry[8] = static_cast<f32>(DOUBLE_80332a90 * static_cast<f64>(cmd[0x11]));
	if (static_cast<f64>(cmd[0x11]) >= DOUBLE_80332a78) {
		cmd[0x15] = 0;
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8014ad90
 * PAL Size: 1204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::CmdClose1()
{
	u8* self = reinterpret_cast<u8*>(this);
	s32 caravanWork = Game.game.m_scriptFoodBase[0];
	s32 cmd = *reinterpret_cast<s32*>(self + 0x82c);
	s16* list = *reinterpret_cast<s16**>(self + 0x850);

	*reinterpret_cast<s16*>(cmd + 0x22) = static_cast<s16>(*reinterpret_cast<s16*>(cmd + 0x22) + 1);
	const s16 timer = *reinterpret_cast<s16*>(cmd + 0x22);
	const s16 selected = *reinterpret_cast<s16*>(cmd + 0x26);
	s32 state = *reinterpret_cast<s16*>(cmd + 0x14);
	u32 done = 0;

	if (state == 0) {
		const float t = static_cast<float>(timer) * 0.125f;
		*reinterpret_cast<float*>(list + selected * 0x20 + 0x0c) = t;

		if (*reinterpret_cast<s16*>(caravanWork + (selected + 1) * 2 + 0x214) < 0) {
			*reinterpret_cast<float*>(list + (selected + 1) * 0x20 + 0x0c) = t;
			if (*reinterpret_cast<s16*>(caravanWork + (selected + 2) * 2 + 0x214) < 0) {
				*reinterpret_cast<float*>(list + (selected + 2) * 0x20 + 0x0c) = t;
			}
		}

		float pos = 1.0f - t;
		if (pos < 0.0f) {
			pos = 0.0f;
		}
		*reinterpret_cast<float*>(list + (static_cast<s32>(list[1]) + 3) * 0x20 + 0x0c) = pos;

		done = static_cast<u32>(static_cast<float>(timer) >= 8.0f);
		if ((done != 0) && (*reinterpret_cast<u8*>(cmd + 8) != 0)) {
			*reinterpret_cast<u8*>(cmd + 8) = 0;
			if (*reinterpret_cast<s16*>(cmd + 0x2a) == 0) {
				*reinterpret_cast<s16*>(cmd + 0x14) = 1;
				done = 0;
			} else if ((static_cast<double>(*reinterpret_cast<float*>(list + (static_cast<s32>(list[1]) + 3) * 0x20 + 0x0d)) ==
			            DOUBLE_80332a58) &&
			           (*reinterpret_cast<s16*>(cmd + 0x2a) == 1)) {
				*reinterpret_cast<s16*>(cmd + 0x14) = 2;
				done = 0;
			}
		}
		if (done != 0) {
			*reinterpret_cast<u8*>(cmd + 8) = 0;
		}
	} else if (state == 1) {
		s32 uniteIdx = 0;
		s32 topCount = static_cast<s32>(list[0]);
		for (; uniteIdx < topCount; uniteIdx++) {
			if (list[uniteIdx * 0x20 + 2] == selected) {
				break;
			}
		}

		done = static_cast<u32>(UniteCloseAnim(uniteIdx) != 0);
		if (done != 0) {
			s32 ununiteCount = 1;
			if (*reinterpret_cast<s16*>(caravanWork + (selected + 1) * 2 + 0x214) < 0) {
				ununiteCount = 2;
				if (*reinterpret_cast<s16*>(caravanWork + (selected + 2) * 2 + 0x214) < 0) {
					ununiteCount = 3;
				}
			}
			UnuniteComList__12CCaravanWorkFii(reinterpret_cast<void*>(caravanWork), selected, ununiteCount);
		}
	} else if (state == 2) {
		int combo[2][2];
		const s32 count = ChkUnite__8CMenuPcsFiPA2_i(this, static_cast<int>(selected), combo);
		if (count == 1) {
			done = 0;
			*reinterpret_cast<s16*>(cmd + 0x14) = 3;
		} else {
			done = 1;
			*reinterpret_cast<u8*>(cmd + 8) = 1;
		}
	} else if (state == 3) {
		s32 uniteIdx = 0;
		s32 topCount = static_cast<s32>(list[0]);
		for (; uniteIdx < topCount; uniteIdx++) {
			if (list[uniteIdx * 0x20 + 2] == selected) {
				break;
			}
		}

		done = static_cast<u32>(UniteCloseAnim(uniteIdx) != 0);
		if (done != 0) {
			int combo[2][2];
			ChkUnite__8CMenuPcsFiPA2_i(this, static_cast<int>(selected), combo);

			s32 ununiteCount = 1;
			if (*reinterpret_cast<s16*>(caravanWork + (selected + 1) * 2 + 0x214) < 0) {
				ununiteCount = 2;
				if (*reinterpret_cast<s16*>(caravanWork + (selected + 2) * 2 + 0x214) < 0) {
					ununiteCount = 3;
				}
			}

			UnuniteComList__12CCaravanWorkFii(reinterpret_cast<void*>(caravanWork), selected, ununiteCount);
			UniteComList__12CCaravanWorkFiii(reinterpret_cast<void*>(caravanWork), combo[0][1], 0, 0);

			done = 0;
			*reinterpret_cast<s16*>(cmd + 0x26) = static_cast<s16>(combo[0][1]);
			*reinterpret_cast<s16*>(cmd + 0x14) = 4;
		}
	} else if (state == 4) {
		done = static_cast<u32>(UniteOpenAnim__8CMenuPcsFi(this, -1) != 0);
	}

	return done;
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
 * PAL Address: 0x8014a9dc
 * PAL Size: 948b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::CmdClose2()
{
	u8* self = reinterpret_cast<u8*>(this);
	s16* const cmd = *reinterpret_cast<s16**>(self + 0x82c);
	s16* const list = *reinterpret_cast<s16**>(self + 0x850);
	const s32 caravanWork = Game.game.m_scriptFoodBase[0];

	const s32 selected = static_cast<s32>(cmd[0x13]);
	const s32 modeSel = static_cast<s32>(cmd[0x13 + cmd[0x18]]);

	cmd[0x11] = static_cast<s16>(cmd[0x11] + 1);

	switch (cmd[0x0A]) {
	case 0:
		cmd[0x11] = 0;
		if (*reinterpret_cast<s8*>(cmd + 4) < 0) {
			cmd[0x0A] = 3;
		} else if (*reinterpret_cast<s16*>(caravanWork + selected * 2 + 0x214) == 0) {
			cmd[0x0A] = 2;
		} else {
			cmd[0x0A] = 1;
		}
		return 0;
	case 1: {
		s32 uniteIdx = 0;
		for (; uniteIdx < static_cast<s32>(list[0]); uniteIdx++) {
			if (list[uniteIdx * 0x20 + 2] == selected) {
				break;
			}
		}

		if (UniteCloseAnim(uniteIdx) != 0) {
			int combo[2][2];
			ChkUnite__8CMenuPcsFiPA2_i(this, selected, combo);

			s32 comboIdx = 0;
			if (combo[0][1] < combo[1][1]) {
				comboIdx = (combo[0][1] == modeSel) ? 0 : 1;
			} else {
				comboIdx = (combo[1][1] == modeSel) ? 1 : 0;
			}

			s32 ununiteCount = 1;
			if (*reinterpret_cast<s16*>(caravanWork + (selected + 1) * 2 + 0x214) == -1) {
				ununiteCount = 2;
				if (*reinterpret_cast<s16*>(caravanWork + (selected + 2) * 2 + 0x214) == -1) {
					ununiteCount = 3;
				}
			}

			UnuniteComList__12CCaravanWorkFii(reinterpret_cast<void*>(caravanWork), selected, ununiteCount);
			UniteComList__12CCaravanWorkFiii(reinterpret_cast<void*>(caravanWork), combo[comboIdx][1], 0, 0);
			cmd[0x13] = static_cast<s16>(combo[comboIdx][1]);
			cmd[0x0A] = 2;
		}
		return 0;
	}
	case 2:
		if (*reinterpret_cast<s16*>(caravanWork + selected * 2 + 0x214) == 0) {
			int combo[2][2];
			ChkUnite__8CMenuPcsFiPA2_i(this, selected, combo);

			s32 comboIdx = 0;
			if (combo[0][1] < combo[1][1]) {
				comboIdx = (combo[0][1] == modeSel) ? 0 : 1;
			} else {
				comboIdx = (combo[1][1] == modeSel) ? 1 : 0;
			}

			UniteComList__12CCaravanWorkFiii(reinterpret_cast<void*>(caravanWork), combo[comboIdx][1], 0, 0);
			cmd[0x13] = static_cast<s16>(combo[comboIdx][1]);
		} else if (UniteOpenAnim__8CMenuPcsFi(this, -1) != 0) {
			cmd[0x0A] = 3;
		}
		return 0;
	case 3:
		for (s32 i = 0; i < static_cast<s32>(list[0]); i++) {
			f32* const xAnim = reinterpret_cast<f32*>(list + i * 0x20 + 0x0c);
			if (static_cast<f64>(*xAnim) < DOUBLE_80332a58) {
				*xAnim = static_cast<f32>((DOUBLE_80332a68 * static_cast<f64>(cmd[0x11])) + DOUBLE_80332a60);
				if (static_cast<f64>(*xAnim) > DOUBLE_80332a58) {
					*xAnim = FLOAT_80332a70;
				}
			}
		}
		return static_cast<u32>(static_cast<f64>(cmd[0x11]) >= DOUBLE_80332a78);
	default:
		return 0;
	}
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

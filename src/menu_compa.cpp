#include "ffcc/menu_compa.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"
#include <string.h>

/*
 * --INFO--
 * PAL Address: 801620f8
 * PAL Size: 616b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CompaInit()
{
	int menuData = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850);
	memset(reinterpret_cast<void*>(menuData), 0, 0x1008);

	float one = 1.0f;
	int block = menuData + 8;
	for (int i = 0; i < 8; ++i) {
		*reinterpret_cast<float*>(block + 0x14) = one;
		*reinterpret_cast<float*>(block + 0x54) = one;
		*reinterpret_cast<float*>(block + 0x94) = one;
		*reinterpret_cast<float*>(block + 0xd4) = one;
		*reinterpret_cast<float*>(block + 0x114) = one;
		*reinterpret_cast<float*>(block + 0x154) = one;
		*reinterpret_cast<float*>(block + 0x194) = one;
		*reinterpret_cast<float*>(block + 0x1d4) = one;
		block += 0x200;
	}

	*reinterpret_cast<int*>(menuData + 0x24) = 0x52;
	*reinterpret_cast<int*>(menuData + 0x20) = 4;
	*reinterpret_cast<short*>(menuData + 8) = 0x28;
	*reinterpret_cast<short*>(menuData + 10) = 0x30;
	*reinterpret_cast<short*>(menuData + 0xc) = 0x198;
	*reinterpret_cast<short*>(menuData + 0xe) = 0x18;
	*reinterpret_cast<float*>(menuData + 0x10) = 0.0f;
	*reinterpret_cast<float*>(menuData + 0x14) = 0.0f;
	*reinterpret_cast<float*>(menuData + 0x1c) = 1.0f;
	*reinterpret_cast<int*>(menuData + 0x2c) = 5;
	*reinterpret_cast<int*>(menuData + 0x30) = 5;

	*reinterpret_cast<int*>(menuData + 100) = 0x51;
	*reinterpret_cast<short*>(menuData + 0x48) = 0x28;
	*reinterpret_cast<short*>(menuData + 0x4a) = 0x48;
	*reinterpret_cast<short*>(menuData + 0x4c) = 0x198;
	*reinterpret_cast<short*>(menuData + 0x4e) = 200;
	*reinterpret_cast<float*>(menuData + 0x50) = 0.0f;
	*reinterpret_cast<float*>(menuData + 0x54) = 0.0f;
	*reinterpret_cast<float*>(menuData + 0x5c) = 1.0f;
	*reinterpret_cast<int*>(menuData + 0x6c) = 5;
	*reinterpret_cast<int*>(menuData + 0x70) = 5;

	*reinterpret_cast<int*>(menuData + 0xa4) = 0x52;
	*reinterpret_cast<short*>(menuData + 0x88) = 0x28;
	*reinterpret_cast<short*>(menuData + 0x8a) = 0x110;
	*reinterpret_cast<short*>(menuData + 0x8c) = 0x198;
	*reinterpret_cast<short*>(menuData + 0x8e) = 0x18;
	*reinterpret_cast<float*>(menuData + 0x90) = 0.0f;
	*reinterpret_cast<float*>(menuData + 0x94) = 0.0f;
	*reinterpret_cast<float*>(menuData + 0x9c) = 1.0f;
	*reinterpret_cast<int*>(menuData + 0xac) = 5;
	*reinterpret_cast<int*>(menuData + 0xb0) = 5;

	*reinterpret_cast<int*>(menuData + 0xe4) = 0x5e;
	*reinterpret_cast<short*>(menuData + 200) = 0x10;
	*reinterpret_cast<short*>(menuData + 0xca) = 0xe;
	*reinterpret_cast<short*>(menuData + 0xcc) = 0x30;
	*reinterpret_cast<short*>(menuData + 0xce) = 0x30;
	*reinterpret_cast<float*>(menuData + 0xd0) = 0.0f;
	*reinterpret_cast<float*>(menuData + 0xd4) = 0.0f;
	*reinterpret_cast<float*>(menuData + 0xdc) = 1.0f;
	*reinterpret_cast<int*>(menuData + 0xec) = 0;
	*reinterpret_cast<int*>(menuData + 0xf0) = 5;

	*reinterpret_cast<int*>(menuData + 0x124) = 0x5e;
	*reinterpret_cast<short*>(menuData + 0x108) = 0x15;
	*reinterpret_cast<short*>(menuData + 0x10c) = 0x30;
	*reinterpret_cast<short*>(menuData + 0x10e) = 0x30;
	*reinterpret_cast<short*>(menuData + 0x10a) = static_cast<short>(0x150 - *reinterpret_cast<short*>(menuData + 0x10e));
	*reinterpret_cast<float*>(menuData + 0x110) = 0.0f;
	*reinterpret_cast<float*>(menuData + 0x114) = 0.0f;
	*reinterpret_cast<float*>(menuData + 0x11c) = -13.0f;
	*reinterpret_cast<int*>(menuData + 300) = 0;
	*reinterpret_cast<int*>(menuData + 0x130) = 5;

	*reinterpret_cast<int*>(menuData + 0x174) = 2;
	*reinterpret_cast<int*>(menuData + 0x164) = 0x2e;
	*reinterpret_cast<short*>(menuData + 0x148) = 0x10;
	*reinterpret_cast<short*>(menuData + 0x14a) = 8;
	*reinterpret_cast<short*>(menuData + 0x14c) = 0x30;
	*reinterpret_cast<short*>(menuData + 0x14e) = 0x140;
	*reinterpret_cast<float*>(menuData + 0x150) = 6.0f;
	*reinterpret_cast<float*>(menuData + 0x154) = 0.0f;
	*reinterpret_cast<int*>(menuData + 0x16c) = 0;
	*reinterpret_cast<int*>(menuData + 0x170) = 5;

	**reinterpret_cast<short**>(reinterpret_cast<char*>(this) + 0x850) = 6;
	int menuState = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82c);
	*reinterpret_cast<short*>(menuState + 0x26) = 0;
	*reinterpret_cast<char*>(menuState + 0xb) = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CompaInit0()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 80161f48
 * PAL Size: 432b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
bool CMenuPcs::CompaOpen()
{
	int menuState = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82c);
	if (*reinterpret_cast<char*>(menuState + 0xb) == 0) {
		CompaInit();
	}

	*reinterpret_cast<short*>(menuState + 0x22) = static_cast<short>(*reinterpret_cast<short*>(menuState + 0x22) + 1);
	int time = static_cast<int>(*reinterpret_cast<short*>(menuState + 0x22));

	int entryCount = static_cast<int>(**reinterpret_cast<short**>(reinterpret_cast<char*>(this) + 0x850));
	short* entry = *reinterpret_cast<short**>(reinterpret_cast<char*>(this) + 0x850) + 4;
	int completeCount = 0;
	for (int i = 0; i < entryCount; ++i) {
		if (*reinterpret_cast<int*>(entry + 0x12) <= time) {
			int duration = *reinterpret_cast<int*>(entry + 0x14);
			if (time < *reinterpret_cast<int*>(entry + 0x12) + duration) {
				*reinterpret_cast<int*>(entry + 0x10) = *reinterpret_cast<int*>(entry + 0x10) + 1;
				float t = static_cast<float>(*reinterpret_cast<int*>(entry + 0x10)) / static_cast<float>(duration);
				*reinterpret_cast<float*>(entry + 8) = t;

				if ((*reinterpret_cast<unsigned int*>(entry + 0x16) & 2) == 0) {
					*reinterpret_cast<float*>(entry + 0x18) =
						(*reinterpret_cast<float*>(entry + 0x1c) - static_cast<float>(*entry)) * t;
					*reinterpret_cast<float*>(entry + 0x1a) =
						(*reinterpret_cast<float*>(entry + 0x1e) - static_cast<float>(entry[1])) * t;
				}
			} else {
				completeCount = completeCount + 1;
				*reinterpret_cast<float*>(entry + 8) = 1.0f;
				*reinterpret_cast<float*>(entry + 0x18) = 0.0f;
				*reinterpret_cast<float*>(entry + 0x1a) = 0.0f;
			}
		}

		entry += 0x20;
	}
	return entryCount == completeCount;
}

/*
 * --INFO--
 * PAL Address: 80161c28
 * PAL Size: 800b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CompaCtrl()
{
	bool activeInput = false;
	unsigned short press;
	unsigned short hold;
	bool doReset = false;

	if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
		activeInput = true;
	}

	if (activeInput) {
		press = 0;
	} else {
		press = Pad._8_2_;
	}

	if (activeInput) {
		hold = 0;
	} else {
		hold = *reinterpret_cast<unsigned short*>(reinterpret_cast<char*>(&Pad) + 0x20);
	}

	if (hold != 0) {
		if ((press & 0x20) != 0) {
			*reinterpret_cast<short*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82c) + 0x1e) = 1;
			Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
			doReset = true;
		} else if ((press & 0x40) != 0) {
			*reinterpret_cast<short*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82c) + 0x1e) = -1;
			Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
			doReset = true;
		} else if ((press & 0x100) != 0) {
			Sound.PlaySe(4, 0x40, 0x7f, 0);
		} else if ((press & 0x200) != 0) {
			*reinterpret_cast<char*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82c) + 0xd) = 1;
			Sound.PlaySe(3, 0x40, 0x7f, 0);
			doReset = true;
		}
	}

	if (!doReset) {
		return;
	}

	int menuData = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850);
	*reinterpret_cast<int*>(menuData + 0x2c) = 2;
	*reinterpret_cast<int*>(menuData + 0x30) = 5;
	*reinterpret_cast<int*>(menuData + 0x6c) = 2;
	*reinterpret_cast<int*>(menuData + 0x70) = 5;
	*reinterpret_cast<int*>(menuData + 0xac) = 2;
	*reinterpret_cast<int*>(menuData + 0xb0) = 5;
	*reinterpret_cast<int*>(menuData + 0xec) = 7;
	*reinterpret_cast<int*>(menuData + 0xf0) = 5;
	*reinterpret_cast<int*>(menuData + 300) = 7;
	*reinterpret_cast<int*>(menuData + 0x130) = 5;
	*reinterpret_cast<int*>(menuData + 0x174) = 2;
	*reinterpret_cast<int*>(menuData + 0x16c) = 7;
	*reinterpret_cast<int*>(menuData + 0x170) = 5;

	int entryCount = static_cast<int>(**reinterpret_cast<short**>(reinterpret_cast<char*>(this) + 0x850));
	short* entry = *reinterpret_cast<short**>(reinterpret_cast<char*>(this) + 0x850) + 4;
	for (int i = 0; i < entryCount; ++i) {
		*reinterpret_cast<int*>(entry + 0x10) = 0;
		*reinterpret_cast<int*>(entry + 0x12) = 0;
		*reinterpret_cast<float*>(entry + 8) = 1.0f;
		entry += 0x20;
	}
}

/*
 * --INFO--
 * PAL Address: 80161aac
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CompaClose()
{
	int menuState = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82c);
	*reinterpret_cast<short*>(menuState + 0x22) = static_cast<short>(*reinterpret_cast<short*>(menuState + 0x22) + 1);
	int time = static_cast<int>(*reinterpret_cast<short*>(menuState + 0x22));

	int entryCount = static_cast<int>(**reinterpret_cast<short**>(reinterpret_cast<char*>(this) + 0x850));
	short* entry = *reinterpret_cast<short**>(reinterpret_cast<char*>(this) + 0x850) + 4;
	for (int i = 0; i < entryCount; ++i) {
		if (*reinterpret_cast<int*>(entry + 0x12) <= time) {
			int duration = *reinterpret_cast<int*>(entry + 0x14);
			if (time < *reinterpret_cast<int*>(entry + 0x12) + duration) {
				*reinterpret_cast<int*>(entry + 0x10) = *reinterpret_cast<int*>(entry + 0x10) + 1;
				float t = static_cast<float>(*reinterpret_cast<int*>(entry + 0x10)) / static_cast<float>(duration);
				float fade = 1.0f - t;
				*reinterpret_cast<float*>(entry + 8) = fade;

				if ((*reinterpret_cast<unsigned int*>(entry + 0x16) & 2) == 0) {
					*reinterpret_cast<float*>(entry + 0x18) =
						(*reinterpret_cast<float*>(entry + 0x1c) - static_cast<float>(*entry)) * fade;
					*reinterpret_cast<float*>(entry + 0x1a) =
						(*reinterpret_cast<float*>(entry + 0x1e) - static_cast<float>(entry[1])) * fade;
				}
			} else {
				*reinterpret_cast<float*>(entry + 8) = 0.0f;
				*reinterpret_cast<float*>(entry + 0x18) = 0.0f;
				*reinterpret_cast<float*>(entry + 0x1a) = 0.0f;
			}
		}

		entry += 0x20;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CompaDraw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CompaCtrlCur()
{
	// TODO
}

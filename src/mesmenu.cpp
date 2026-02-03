#include "ffcc/mesmenu.h"
#include "ffcc/p_game.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMesMenu::CMesMenu()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMesMenu::~CMesMenu()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMesMenu::Create()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMesMenu::Destroy()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMesMenu::onCalc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMesMenu::onDraw()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8009bcec
 * PAL Size: 496b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::CalcHeart()
{
	unsigned int scriptFoodBase = Game.game.m_scriptFoodBase[*(int*)((char*)this + 0x18)];
	if (scriptFoodBase == 0) {
		return;
	}
	
	unsigned int heartCount = (unsigned int)*(unsigned short*)(scriptFoodBase + 0x1c);
	int targetHeartValue = heartCount * 6;
	
	if (*(int*)((char*)this + 0x3dac) < targetHeartValue) {
		*(int*)((char*)this + 0x3dac) = targetHeartValue;
	}
	else if (targetHeartValue < *(int*)((char*)this + 0x3dac)) {
		*(unsigned int*)((char*)this + 0x3dac) = heartCount * 6;
	}
	
	int currentHeartValue = *(int*)((char*)this + 0x3da8);
	if (currentHeartValue < *(int*)((char*)this + 0x3dac)) {
		int heartIndex = currentHeartValue / 0xc + (currentHeartValue >> 0x1f);
		char* heartOffset = (char*)this + (heartIndex - (heartIndex >> 0x1f)) * 4;
		if (*(int*)(heartOffset + 0x3db0) == 0) {
			*(int*)(heartOffset + 0x3db0) = 0x10;
		}
		
		int newHeartValue = *(int*)((char*)this + 0x3da8) + 2;
		int maxHeartValue = *(int*)((char*)this + 0x3dac);
		if (newHeartValue < *(int*)((char*)this + 0x3dac)) {
			maxHeartValue = newHeartValue;
		}
		*(int*)((char*)this + 0x3da8) = maxHeartValue;
	}
	else if (*(int*)((char*)this + 0x3dac) < currentHeartValue) {
		*(unsigned int*)((char*)this + 0x3da8) = (currentHeartValue - 2) & ~((int)(currentHeartValue - 2) >> 0x1f);
		int heartIndex = *(int*)((char*)this + 0x3da8) / 0xc + (*(int*)((char*)this + 0x3da8) >> 0x1f);
		char* heartOffset = (char*)this + (heartIndex - (heartIndex >> 0x1f)) * 4;
		if (*(int*)(heartOffset + 0x3dd0) == 0) {
			*(int*)(heartOffset + 0x3dd0) = 0x10;
		}
		if (*(int*)((char*)this + 0x3df0) == 0) {
			*(int*)((char*)this + 0x3df0) = 0x10;
		}
	}
	
	// Decrement timers for heart animation effects
	int loopCount = 2;
	char* currentOffset = (char*)this;
	do {
		unsigned int val = *(int*)(currentOffset + 0x3db0) - 1;
		*(unsigned int*)(currentOffset + 0x3db0) = val & ~((int)val >> 0x1f);
		val = *(int*)(currentOffset + 0x3dd0) - 1;
		*(unsigned int*)(currentOffset + 0x3dd0) = val & ~((int)val >> 0x1f);
		val = *(int*)(currentOffset + 0x3db4) - 1;
		*(unsigned int*)(currentOffset + 0x3db4) = val & ~((int)val >> 0x1f);
		val = *(int*)(currentOffset + 0x3dd4) - 1;
		*(unsigned int*)(currentOffset + 0x3dd4) = val & ~((int)val >> 0x1f);
		val = *(int*)(currentOffset + 0x3db8) - 1;
		*(unsigned int*)(currentOffset + 0x3db8) = val & ~((int)val >> 0x1f);
		val = *(int*)(currentOffset + 0x3dd8) - 1;
		*(unsigned int*)(currentOffset + 0x3dd8) = val & ~((int)val >> 0x1f);
		val = *(int*)(currentOffset + 0x3dbc) - 1;
		*(unsigned int*)(currentOffset + 0x3dbc) = val & ~((int)val >> 0x1f);
		val = *(int*)(currentOffset + 0x3ddc) - 1;
		*(unsigned int*)(currentOffset + 0x3ddc) = val & ~((int)val >> 0x1f);
		
		currentOffset = currentOffset + 0x10;
		loopCount = loopCount - 1;
	} while (loopCount != 0);
	
	unsigned int val = *(int*)((char*)this + 0x3df0) - 1;
	*(unsigned int*)((char*)this + 0x3df0) = val & ~((int)val >> 0x1f);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMesMenu::DrawHeart(float, float, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMesMenu::onScriptChanging(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMesMenu::onScriptChanged(char*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMesMenu::Open(char*, int, int, int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMesMenu::CloseRequest(int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8009b4e4
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::SetPos(float x, float y, float z)
{
	*(float*)((char*)this + 0x3d74) = x;
	*(float*)((char*)this + 0x3d78) = y;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMesMenu::close(int)
{
	// TODO
}

#include "ffcc/menu_arti.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ArtiInit()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801609d8
 * PAL Size: 604b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ArtiInit1()
{
	int iVar2;
	float fVar1;
	short* psVar3;
	unsigned int uVar4;
	unsigned int uVar5;
	int* workPtr;

	fVar1 = 0.0f;
	workPtr = (int*)((char*)this + 0x850);

	iVar2 = *workPtr;
	*(int*)(iVar2 + 0x24) = 0x2e;
	*(int*)(iVar2 + 0x2c) = 2;
	*(int*)(iVar2 + 0x30) = 5;
	iVar2 = *workPtr;
	*(int*)(iVar2 + 100) = 0x44;
	*(int*)(iVar2 + 0x6c) = 7;
	*(int*)(iVar2 + 0x70) = 5;
	iVar2 = *workPtr;
	*(int*)(iVar2 + 0xa4) = 0x44;
	*(int*)(iVar2 + 0xac) = 7;
	*(int*)(iVar2 + 0xb0) = 5;
	iVar2 = *workPtr;
	*(int*)(iVar2 + 0xf4) = 2;
	*(int*)(iVar2 + 0xe4) = 0x2e;
	*(int*)(iVar2 + 0xec) = 7;
	*(int*)(iVar2 + 0xf0) = 5;
	iVar2 = *workPtr;
	*(int*)(iVar2 + 0x134) = 2;
	*(int*)(iVar2 + 0x124) = 0x37;
	*(int*)(iVar2 + 300) = 0;
	*(int*)(iVar2 + 0x130) = 5;
	iVar2 = *workPtr;
	*(int*)(iVar2 + 0x174) = 2;
	*(int*)(iVar2 + 0x164) = 0x37;
	*(int*)(iVar2 + 0x16c) = 0;
	*(int*)(iVar2 + 0x170) = 5;
	iVar2 = *workPtr;
	*(int*)(iVar2 + 0x1b4) = 2;
	*(int*)(iVar2 + 0x1a4) = 0x37;
	*(int*)(iVar2 + 0x1ac) = 0;
	*(int*)(iVar2 + 0x1b0) = 5;
	iVar2 = *workPtr;
	*(int*)(iVar2 + 500) = 2;
	*(int*)(iVar2 + 0x1e4) = 0x37;
	*(int*)(iVar2 + 0x1ec) = 0;
	*(int*)(iVar2 + 0x1f0) = 5;
	iVar2 = *workPtr;
	*(int*)(iVar2 + 0x234) = 2;
	*(int*)(iVar2 + 0x224) = 0x37;
	*(int*)(iVar2 + 0x22c) = 0;
	*(int*)(iVar2 + 0x230) = 5;
	iVar2 = *workPtr;
	*(int*)(iVar2 + 0x274) = 2;
	*(int*)(iVar2 + 0x264) = 0x37;
	*(int*)(iVar2 + 0x26c) = 0;
	*(int*)(iVar2 + 0x270) = 5;
	iVar2 = *workPtr;
	*(int*)(iVar2 + 0x2b4) = 2;
	*(int*)(iVar2 + 0x2a4) = 0x37;
	*(int*)(iVar2 + 0x2ac) = 0;
	*(int*)(iVar2 + 0x2b0) = 5;
	iVar2 = *workPtr;
	*(int*)(iVar2 + 0x2f4) = 2;
	*(int*)(iVar2 + 0x2e4) = 0x37;
	*(int*)(iVar2 + 0x2ec) = 0;
	*(int*)(iVar2 + 0x2f0) = 5;

	uVar4 = (unsigned int)**(short**)workPtr;
	psVar3 = *(short**)workPtr + 4;
	if (0 < (int)uVar4) {
		uVar5 = uVar4 >> 3;
		if (uVar5 != 0) {
			do {
				psVar3[0x10] = 0;
				psVar3[0x11] = 0;
				*(float*)(psVar3 + 8) = fVar1;
				psVar3[0x30] = 0;
				psVar3[0x31] = 0;
				*(float*)(psVar3 + 0x28) = fVar1;
				psVar3[0x50] = 0;
				psVar3[0x51] = 0;
				*(float*)(psVar3 + 0x48) = fVar1;
				psVar3[0x70] = 0;
				psVar3[0x71] = 0;
				*(float*)(psVar3 + 0x68) = fVar1;
				psVar3[0x90] = 0;
				psVar3[0x91] = 0;
				*(float*)(psVar3 + 0x88) = fVar1;
				psVar3[0xb0] = 0;
				psVar3[0xb1] = 0;
				*(float*)(psVar3 + 0xa8) = fVar1;
				psVar3[0xd0] = 0;
				psVar3[0xd1] = 0;
				*(float*)(psVar3 + 200) = fVar1;
				psVar3[0xf0] = 0;
				psVar3[0xf1] = 0;
				*(float*)(psVar3 + 0xe8) = fVar1;
				psVar3 = psVar3 + 0x100;
				uVar5 = uVar5 - 1;
			} while (uVar5 != 0);
			uVar4 = uVar4 & 7;
			if (uVar4 == 0) {
				return;
			}
		}
		do {
			psVar3[0x10] = 0;
			psVar3[0x11] = 0;
			*(float*)(psVar3 + 8) = fVar1;
			psVar3 = psVar3 + 0x20;
			uVar4 = uVar4 - 1;
		} while (uVar4 != 0);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ArtiOpen()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ArtiCtrl()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ArtiClose()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ArtiDraw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMenuPcs::ArtiCtrlCur()
{
    // Simplified implementation to get it compiling
    // TODO: Properly implement controller input handling
    
    // Check for basic pad input
    unsigned short uVar3 = Pad._8_2_;
    unsigned short uVar4 = Pad._8_2_; // Using same field temporarily
    
    if (uVar4 == 0) {
        return 0;
    }
    
    // Basic navigation logic (simplified)
    if ((uVar4 & 4) != 0) {
        // Down movement
        Sound.PlaySe(1, 0x40, 0x7f, 0);
    }
    
    if ((uVar4 & 8) != 0) {
        // Up movement  
        Sound.PlaySe(1, 0x40, 0x7f, 0);
    }
    
    if ((uVar3 & 0x20) != 0) {
        // A button
        Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
        return 1;
    }
    
    if ((uVar3 & 0x40) != 0) {
        // B button
        Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
        return 1;
    }
    
    return 0;
}

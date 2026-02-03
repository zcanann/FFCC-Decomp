#include "ffcc/menu_money.h"
#include <string.h>

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::MoneyInit()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 8015f688
 * PAL Size: 928b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::MoneyOpen()
{
	if (*(char *)(*(int *)((char*)this + 0x82c) + 0xb) == '\0') {
		memset(*(void**)((char*)this + 0x850), 0, 0x1008);
		
		// Initialize display elements
		float fVar1 = 1.0f; // FLOAT_80332f70
		int iVar8 = *(int *)((char*)this + 0x850) + 8;
		int iVar15 = 8;
		do {
			*(float *)(iVar8 + 0x14) = fVar1;
			*(float *)(iVar8 + 0x54) = fVar1;
			*(float *)(iVar8 + 0x94) = fVar1;
			*(float *)(iVar8 + 0xd4) = fVar1;
			*(float *)(iVar8 + 0x114) = fVar1;
			*(float *)(iVar8 + 0x154) = fVar1;
			*(float *)(iVar8 + 0x194) = fVar1;
			*(float *)(iVar8 + 0x1d4) = fVar1;
			iVar8 = iVar8 + 0x200;
			iVar15 = iVar15 + -1;
		} while (iVar15 != 0);
		
		// Setup base values
		int iVar8_2 = *(int *)((char*)this + 0x850);
		*(int *)(iVar8_2 + 0x24) = 0x3b;
		*(short *)(iVar8_2 + 10) = 0x68;
		*(short *)(iVar8_2 + 0xc) = 0xf8;
		*(short *)(iVar8_2 + 0xe) = 0x88;
		
		// Mark as initialized
		*(char *)(*(int *)((char*)this + 0x82c) + 0xb) = 1;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::MoneyCtrl()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::MoneyClose()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 8015eda8
 * PAL Size: 1636b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::MoneyDraw()
{
	// Set blend mode for rendering
	// _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
	// SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs, 0);
	
	short sVar1 = *(short *)(*(int *)((char*)this + 0x82c) + 0x10);
	short sVar2 = *(short *)(*(int *)((char*)this + 0x82c) + 0x30);
	short *psVar6 = (short *)(*(int *)((char*)this + 0x850) + 8);
	
	// Draw UI elements
	for (int iVar7 = 0; iVar7 < **(short**)((char*)this + 0x850); iVar7++) {
		if (-1 < *(int *)(psVar6 + 0xe)) {
			// SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs, *(int *)(psVar6 + 0xe));
			
			// Calculate positions and render rectangle
			float dVar14 = (float)*psVar6;
			float dVar13 = (float)psVar6[1];
			float dVar15 = (float)psVar6[2];
			float dVar16 = (float)psVar6[3];
			float dVar11 = *(float *)(psVar6 + 4);
			float dVar12 = *(float *)(psVar6 + 6);
			
			// Set material color
			int local_cc = 0xffffffff;
			// GXSetChanMatColor(4, &local_cc);
			
			// DrawRect__8CMenuPcsFUlfffffffff(
			//	dVar14, dVar13, dVar15, dVar16, dVar11, dVar12, 
			//	(float)*(float *)(psVar6 + 10), (float)*(float *)(psVar6 + 10), 
			//	&MenuPcs, 0);
		}
		psVar6 = psVar6 + 0x20;
	}
	
	// Draw money digits
	// SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs, 0x5d);
	
	// Draw cursor if in selection mode
	if ((sVar2 == 0) && (sVar1 == 1)) {
		// SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs, 0x48);
		
		// Draw cursor rectangle
		short *psVar6_cursor = (short *)(*(int *)((char*)this + 0x850) + 8);
		float cursorX = (float)*psVar6_cursor + (7 - *(short *)(*(int *)((char*)this + 0x82c) + 0x26)) * 18 + 36;
		float cursorY = (float)*(short *)(*(int *)((char*)this + 0x850) + 10) + 92;
		
		// DrawRect__8CMenuPcsFUlfffffffff(
		//	cursorX, cursorY, 24.0f, 18.0f, 0.0f, 0.0f, 1.0f, 1.0f, &MenuPcs, 0);
	}
	
	// Draw text elements
	void *font = *(void **)((char*)this + 0x108);
	// SetMargin__5CFontFf(1.0f, font);
	// SetShadow__5CFontFi(font, 0);
	// SetScale__5CFontFf(1.0f, font);
	// DrawInit__5CFontFv(font);
	
	int local_dc = 0xffffffff;
	// SetColor__5CFontF8_GXColor(font, &local_dc);
	
	void *uVar3 = 0; // GetMenuStr__8CMenuPcsFi(this, 0x15);
	// SetPosX__5CFontFf(100.0f, font);
	// SetPosY__5CFontFf(50.0f, font);
	// Draw__5CFontFPc(font, uVar3);
	
	// DrawInit__8CMenuPcsFv(this);
}

/*
 * --INFO--
 * PAL Address: 8015e37c
 * PAL Size: 2604b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::MoneyCtrlCur()
{
	// Get pad input (simplified for now)
	unsigned short uVar3 = 0; // Pad input buttons
	unsigned short uVar4 = 1; // Assume some input available for testing
	
	if (uVar4 == 0) {
		return;
	}
	
	int iVar11 = (int)*(short *)(*(int *)((char*)this + 0x82c) + 0x30);
	
	// Handle input based on current state
	if (iVar11 != 0) {
		// Handle digit selection mode
		if ((uVar4 & 8) == 0) {
			if ((uVar4 & 4) != 0) {
				int iVar5 = *(int *)((char*)this + 0x82c) + iVar11 * 2;
				if (*(short *)(iVar5 + 0x26) < 1) {
					*(short *)(iVar5 + 0x26) = *(short *)(iVar5 + 0x26) + 1;
				} else {
					*(short *)(iVar5 + 0x26) = 0;
				}
				// PlaySe__6CSoundFiiii(&Sound, 1, 0x40, 0x7f, 0);
			}
		} else {
			int iVar5 = *(int *)((char*)this + 0x82c) + iVar11 * 2;
			if (*(short *)(iVar5 + 0x26) == 0) {
				*(short *)(iVar5 + 0x26) = 1;
			} else {
				*(short *)(iVar5 + 0x26) = *(short *)(iVar5 + 0x26) + -1;
			}
			// PlaySe__6CSoundFiiii(&Sound, 1, 0x40, 0x7f, 0);
		}
	} else {
		// Handle main money amount controls
		if ((uVar4 & 8) == 0) {
			if ((uVar4 & 4) != 0) {
				// Decrease money amount
				// PlaySe__6CSoundFiiii(&Sound, 1, 0x40, 0x7f, 0);
			}
		} else {
			// Increase money amount  
			// PlaySe__6CSoundFiiii(&Sound, 1, 0x40, 0x7f, 0);
		}
		
		// Handle left/right digit navigation
		if ((uVar4 & 1) == 0) {
			if ((uVar4 & 2) != 0) {
				short sVar1 = *(short *)(*(int *)((char*)this + 0x82c) + 0x26);
				if (sVar1 == 0) {
					// PlaySe__6CSoundFiiii(&Sound, 4, 0x40, 0x7f, 0);
				} else {
					*(short *)(*(int *)((char*)this + 0x82c) + 0x26) = sVar1 + -1;
					// PlaySe__6CSoundFiiii(&Sound, 1, 0x40, 0x7f, 0);
				}
			}
		} else {
			// PlaySe__6CSoundFiiii(&Sound, 1, 0x40, 0x7f, 0);
		}
		
		// Handle confirm/cancel buttons
		if ((uVar4 & 0xf) == 0) {
			if ((uVar3 & 0x100) != 0) {
				// PlaySe__6CSoundFiiii(&Sound, 2, 0x40, 0x7f, 0);
			} else if ((uVar3 & 0x200) != 0) {
				// PlaySe__6CSoundFiiii(&Sound, 3, 0x40, 0x7f, 0);
			}
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::MoneySetPlace(int)
{
	// TODO
}
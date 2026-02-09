#include "ffcc/menu_lst.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"
#include <string.h>

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::MLstInit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::MLstInit1()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80175210
 * PAL Size: 720b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO  
 * JP Size: TODO
 */
void CMenuPcs::MLstOpen()
{
	// Initialize menu list data if not already initialized
	if (*(char*)((char*)this + 0x82c + 0xb) == 0) {
		// Clear menu list data structure
		memset(*(void**)((char*)this + 0x850), 0, 0x1008);
		
		// Initialize 9 menu items with default properties
		float defaultAlpha = 1.0f;
		short yPos = 0x18;
		int itemIndex = 0;
		
		for (int i = 0; i < 9; i++) {
			short* itemPtr = (short*)(*(int*)((char*)this + 0x850) + i * 0x40 + 8);
			
			// Set item properties
			*(int*)(itemPtr + 0x16) = 2;      // Some flag/type
			*(int*)(itemPtr + 0xe) = 0x5b;    // Texture ID
			itemPtr[2] = 0xe0;                // Width
			itemPtr[3] = 0x28;                // Height
			
			// Calculate X position (centered)
			*itemPtr = (short)(int)-(((double)(itemPtr[2] ^ 0x80000000) - 4503599627370496.0) * 0.5 - 320.0);
			itemPtr[1] = yPos;                // Y position
			yPos += 0x20;                     // Move down for next item
			
			*(float*)(itemPtr + 4) = 1.0f;    // Scale/alpha values
			*(float*)(itemPtr + 6) = 1.0f;
			*(int*)(itemPtr + 0x12) = itemIndex;    // Animation start frame
			*(int*)(itemPtr + 0x14) = 4;            // Animation duration
			
			itemIndex++;
		}
		
		// Set item count
		**(short**)((char*)this + 0x850) = 9;
		
		// Mark as initialized
		*(char*)((char*)this + 0x82c + 0xb) = 1;
	}
	
	// Handle fade-in animation
	int completedItems = 0;
	*(short*)((char*)this + 0x82c + 0x22) += 1; // Increment animation frame
	int currentFrame = *(short*)((char*)this + 0x82c + 0x22);
	
	int itemCount = **(short**)((char*)this + 0x850);
	short* itemPtr = *(short**)((char*)this + 0x850) + 4;
	
	// Update each item's fade-in animation
	for (int i = 0; i < itemCount; i++) {
		int startFrame = *(int*)(itemPtr + 0x12);
		int duration = *(int*)(itemPtr + 0x14);
		
		if (startFrame <= currentFrame) {
			if (currentFrame < startFrame + duration) {
				// Animate fade-in
				*(int*)(itemPtr + 0x10) += 1;
				float progress = (float)(*(int*)(itemPtr + 0x10)) / (float)duration;
				*(float*)(itemPtr + 8) = progress;
			} else {
				// Animation complete
				completedItems++;
				*(float*)(itemPtr + 8) = 1.0f;
			}
		}
		
		itemPtr += 0x20;
	}
	
	// Check if all animations are complete
	if (itemCount == completedItems) {
		// Reset all animation states
		itemPtr = *(short**)((char*)this + 0x850) + 4;
		for (int i = 0; i < itemCount; i++) {
			*(short*)(itemPtr + 0x12) = 0;  // Reset start frame
			*(short*)(itemPtr + 0x13) = 0;
			*(short*)(itemPtr + 0x14) = 0;  // Reset duration
			*(short*)(itemPtr + 0x15) = 1;
			*(float*)(itemPtr + 8) = 1.0f;  // Full alpha
			itemPtr += 0x20;
		}
		// Animation complete - no return needed for void function
	}
	
	// Still animating - no return needed for void function
}

/*
 * --INFO--
 * PAL Address: 0x80174e94
 * PAL Size: 892b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::MLstCtrl()
{
	unsigned short press = 0;
	unsigned short hold = 0;
	bool resetAnim = false;

	if (Pad._452_4_ == 0 && Pad._448_4_ == -1) {
		press = Pad._8_2_;
		hold = *reinterpret_cast<unsigned short*>(reinterpret_cast<char*>(&Pad) + 0x20);
	}

	if (hold != 0) {
		int menuState = *(int*)((char*)this + 0x82c);
		short* cursor = (short*)(menuState + 0x26);

		if ((hold & 0x48) != 0) {
			if (*cursor == 0) {
				*cursor = 8;
			} else {
				*cursor = *cursor - 1;
			}
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		} else if ((hold & 0x24) != 0) {
			if (*cursor < 8) {
				*cursor = *cursor + 1;
			} else {
				*cursor = 0;
			}
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		}

		if ((hold & 0x6c) == 0) {
			if ((press & 0x100) != 0) {
				Sound.PlaySe(2, 0x40, 0x7f, 0);
				resetAnim = true;
			} else if ((press & 0x200) != 0) {
				*(char*)(menuState + 0xd) = (char)0xff;
				Sound.PlaySe(3, 0x40, 0x7f, 0);
				resetAnim = true;
			}
		}
	}

	if (!resetAnim) {
		return;
	}

	short itemCount = **(short**)((char*)this + 0x850);
	int listBase = *(int*)((char*)this + 0x850);
	int item = listBase + 8;

	for (int i = 0; i < itemCount; i++) {
		*(float*)(item + 0x10) = 1.0f;
		*(float*)(item + 0x14) = 1.0f;
		item += 0x40;
	}

	int startFrame = 0;
	for (int i = itemCount - 1; i >= 0; i--) {
		int entry = listBase + i * 0x40 + 8;
		*(int*)(entry + 0x24) = startFrame;
		*(int*)(entry + 0x28) = 4;
		startFrame++;
	}

	*(short*)(*(int*)((char*)this + 0x82c) + 0x22) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80174ce8
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO  
 * JP Size: TODO
 */
int CMenuPcs::MLstClose()
{
	int completedItems = 0;
	
	// Increment animation frame counter
	*(short*)((char*)this + 0x82c + 0x22) += 1;
	int currentFrame = *(short*)((char*)this + 0x82c + 0x22);
	
	int itemCount = **(short**)((char*)this + 0x850);
	short* itemPtr = *(short**)((char*)this + 0x850) + 4;
	
	// Update each item's fade-out animation
	for (int i = 0; i < itemCount; i++) {
		int startFrame = *(int*)(itemPtr + 0x12);
		int duration = *(int*)(itemPtr + 0x14);
		
		if (startFrame <= currentFrame) {
			if (currentFrame < startFrame + duration) {
				// Animate fade-out
				*(int*)(itemPtr + 0x10) += 1;
				int progress = *(int*)(itemPtr + 0x10);
				
				// Calculate fade-out alpha (1.0 - progress/duration)
				float alpha = 1.0f - (float)progress / (float)duration;
				if (alpha < 0.0f) {
					alpha = 0.0f;
				}
				*(float*)(itemPtr + 8) = alpha;
			} else {
				// Animation complete
				completedItems++;
				*(float*)(itemPtr + 8) = 0.0f;
			}
		}
		
		itemPtr += 0x20;
	}
	
	// Check if all animations are complete
	if (itemCount == completedItems) {
		// Reset all animation states
		itemPtr = *(short**)((char*)this + 0x850) + 4;
		for (int i = 0; i < itemCount; i++) {
			*(short*)(itemPtr + 0x12) = 0;  // Reset start frame
			*(short*)(itemPtr + 0x13) = 0;
			*(short*)(itemPtr + 0x14) = 0;  // Reset duration
			*(short*)(itemPtr + 0x15) = 1;
			*(float*)(itemPtr + 8) = 0.0f;  // Zero alpha
			itemPtr += 0x20;
		}
		return 1;  // Close animation complete
	}
	
	return 0;  // Still animating
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::MLstDraw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::MLstCtrlCur()
{
	// TODO
}

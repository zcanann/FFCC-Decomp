#include "ffcc/chara_fur.h"
#include "ffcc/chara.h"
#include "ffcc/charaobj.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void mySrand(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void myRand(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void myRandFPM(float)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800e2174
 * PAL Size: 1140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void brush(unsigned short* pixels, int width, int height, float fx, float fy, int mode, _GXColor targetColor, _GXColor* centerBefore, _GXColor* centerAfter)
{
	int texelCountBytes = width * height * 2;
	int centerX = (int)((float)width * fx);
	int centerY = (int)((float)height * fy);
	int dy;

	*centerBefore = CColor(0x0f, 0x0f, 0x0f, 0).color;
	*centerAfter = *centerBefore;

	DCInvalidateRange(pixels, texelCountBytes);

	for (dy = -2; dy <= 2; dy++) {
		int dx;
		int py = centerY + dy;
		for (dx = -2; dx <= 2; dx++) {
			int px = centerX + dx;
			int distance;
			int tileIndex;
			unsigned short packed;
			int r;
			int g;
			int b;
			int a;

			if (px < 0 || px >= width || py < 0 || py >= height) {
				continue;
			}

			distance = (dx < 0 ? -dx : dx) + (dy < 0 ? -dy : dy);
			tileIndex = ((((px >> 2) & 1) + (((py >> 2) & 1) * 4) + (px >> 3) * 0x10 + (py >> 3) * width * 4) * 2) +
			            (((px & 3) + ((py & 3) * 4)) * 2);
			packed = *(unsigned short*)(((char*)pixels) + tileIndex);

			b = packed & 0x0f;
			g = (packed >> 4) & 0x0f;
			r = (packed >> 8) & 0x0f;
			a = (packed >> 12) & 0x07;

			if (distance == 0) {
				*centerBefore = CColor((unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a).color;
			}

			if (mode == 0) {
				float k = (float)(distance + (7 - targetColor.a)) / 8.0f;
				if (k > 1.0f) {
					k = 1.0f;
				}
				{
					float inv = 1.0f - k;
					r = (int)((float)r * k + (float)targetColor.r * inv);
					g = (int)((float)g * k + (float)targetColor.g * inv);
					b = (int)((float)b * k + (float)targetColor.b * inv);
				}
				if (r < 0) {
					r = 0;
				} else if (r > 0x0f) {
					r = 0x0f;
				}
				if (g < 0) {
					g = 0;
				} else if (g > 0x0f) {
					g = 0x0f;
				}
				if (b < 0) {
					b = 0;
				} else if (b > 0x0f) {
					b = 0x0f;
				}
			} else {
				int reduce = (targetColor.a * (4 - distance)) / 4;
				a -= reduce;
				if (a < 0) {
					a = 0;
				}
			}

			*(unsigned short*)(((char*)pixels) + tileIndex) = (unsigned short)((b & 0x0f) | ((g & 0x0f) << 4) | ((r & 0x0f) << 8) | ((a & 0x07) << 12));

			if (distance == 0) {
				*centerAfter = CColor((unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a).color;
			}
		}
	}

	DCFlushRange(pixels, texelCountBytes);
	GXInvalidateTexAll();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void nearColor(CColor, CColor)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CHairSet::CHairSet()
    : m_vec0(), m_vec1()
{}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GXSetTexCoordGen(void)
{
	// TODO
}

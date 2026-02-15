#include "ffcc/chara_fur.h"
#include "ffcc/chara.h"
#include "ffcc/charaobj.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"

#include <string.h>

/*
 * --INFO--
 * PAL Address: 0x800df618
 * PAL Size: 480b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::TimeMogFur()
{
	unsigned int* const timeStamp = reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(this) + 0x2014);
	unsigned short* const texels = reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(this) + 4);

	if (*timeStamp + 0x1A5E0 < System.m_frameCounter) {
		*timeStamp = System.m_frameCounter;
		if (static_cast<unsigned int>(System.m_execParam) > 2U) {
			System.Printf("");
		}
		if (static_cast<unsigned int>(System.m_execParam) > 2U) {
			System.Printf("");
		}
		if (static_cast<unsigned int>(System.m_execParam) > 2U) {
			System.Printf("");
		}
	}

	memset(reinterpret_cast<unsigned char*>(this) + 0x2018, 0, 0x40);

	for (unsigned int y = 0; y < 0x40; y++) {
		for (unsigned int x = 0; x < 0x40; x++) {
			int light;
			int r;
			int g;
			int b;
			int a;
			unsigned int newA;
			unsigned int tileIndex = ((((x >> 2) & 1) + (((y >> 2) & 1) * 4) + (x >> 3) * 0x10 + (y >> 3) * 0x100) * 2) +
			                         (((x & 3) + ((y & 3) * 4)) * 2);
			unsigned short packed = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(texels) + tileIndex);

			a = (packed >> 12) & 7;
			light = 7 - a;
			r = light + ((packed >> 8) & 0xF) + 4;
			g = light + ((packed >> 4) & 0xF) + 4;
			b = light + (packed & 0xF) + 4;

			if (r > 0xF) {
				r = 0xF;
			}
			if (g > 0xF) {
				g = 0xF;
			}
			if (b > 0xF) {
				b = 0xF;
			}

			newA = static_cast<unsigned int>(a + 2);
			if (newA > 7) {
				newA = 7;
			}

			*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(texels) + tileIndex) =
			    static_cast<unsigned short>((b & 0xF) | ((g & 0xF) << 4) | ((r & 0xF) << 8) | ((newA & 7) << 12));
		}
	}

	CalcMogScore();
}

/*
 * --INFO--
 * PAL Address: 0x800df7f8
 * PAL Size: 2224b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CalcMogScore()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800e10c0
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::ChangeMogMode(int mogMode)
{
	int* const mogSoundHandle = reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x200c);

	if (mogMode == 0) {
		if (*mogSoundHandle != 0) {
			Sound.StopSe(*mogSoundHandle);
			*mogSoundHandle = 0;
		}
	} else {
		memset(reinterpret_cast<unsigned char*>(this) + 0x1FE8, 0, 0x2C);
		*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(this) + 0x200c) = 0x140;
		*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(this) + 0x2010) = 0xE0;
		*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(this) + 0x2004) = 0;
	}
}

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

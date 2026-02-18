#include "ffcc/chara_fur.h"
#include "ffcc/chara.h"
#include "ffcc/charaobj.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include "ffcc/textureman.h"

#include <math.h>
#include <string.h>

template <class T>
class CPtrArray
{
public:
	T operator[](unsigned long index);
};

extern "C" unsigned char Graphic[];
extern "C" void Printf__8CGraphicFUlUlPce(void*, unsigned long, unsigned long, const char*, ...);
extern "C" unsigned char Game[];
extern "C" char lbl_801DB694[];
extern "C" char lbl_801DB6B4[];

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
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	unsigned short* texels = reinterpret_cast<unsigned short*>(self + 4);
	int bitCount = 0;
	int lineCount = 0;
	int circleCount = 0;

	memset(self + 0x2018, 0, 0x40);

	for (int y = 0; y < 0x40; y++) {
		for (int x = 0; x < 0x40; x++) {
			const int dx = x - 0x20;
			const int dy = y - 0x20;
			const int dist = static_cast<int>(sqrt(static_cast<double>(dx * dx + dy * dy)));

			if (dist >= 0x40) {
				continue;
			}

			const int tileIndex =
			    ((((x >> 2) & 1) + (((y >> 2) & 1) * 4) + (x >> 3) * 0x10 + (y >> 3) * 0x100) * 2) +
			    (((x & 3) + ((y & 3) * 4)) * 2);

			const unsigned short packed = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(texels) + tileIndex);
			const int a = (packed >> 12) & 7;
			const int r = (packed >> 8) & 0xF;
			const int g = (packed >> 4) & 0xF;
			const int b = packed & 0xF;

			*reinterpret_cast<int*>(self + 0x2054) += a;

			int colorHit[3];
			{
				const int d0 = ((r - 0xF) < 0 ? -(r - 0xF) : (r - 0xF)) + (7 - a);
				const int d1 = ((g - 4) < 0 ? -(g - 4) : (g - 4)) + (7 - a);
				const int d2 = ((b - 4) < 0 ? -(b - 4) : (b - 4)) + (7 - a);
				colorHit[0] = (d0 < 6 && d1 < 6 && d2 < 6) ? 1 : 0;
			}
			{
				const int d0 = ((r - 4) < 0 ? -(r - 4) : (r - 4)) + (7 - a);
				const int d1 = ((g - 0xF) < 0 ? -(g - 0xF) : (g - 0xF)) + (7 - a);
				const int d2 = ((b - 4) < 0 ? -(b - 4) : (b - 4)) + (7 - a);
				colorHit[1] = (d0 < 6 && d1 < 6 && d2 < 6) ? 1 : 0;
			}
			{
				const int d0 = ((r - 4) < 0 ? -(r - 4) : (r - 4)) + (7 - a);
				const int d1 = ((g - 8) < 0 ? -(g - 8) : (g - 8)) + (7 - a);
				const int d2 = ((b - 0xF) < 0 ? -(b - 0xF) : (b - 0xF)) + (7 - a);
				colorHit[2] = (d0 < 6 && d1 < 6 && d2 < 6) ? 1 : 0;
			}

			const int ring = dist % 12;
			int angle = static_cast<int>(57.29577951308232 * atan2(static_cast<double>(dx), static_cast<double>(dy))) + 0x168;
			angle %= 0x2D;
			if (angle < 0) {
				angle += 0x2D;
			}

			for (int i = 0; i < 3; i++) {
				if (ring >= i * 4 && ring < (i + 1) * 4) {
					circleCount++;
					*reinterpret_cast<int*>(self + 0x203C + i * 4) += colorHit[i];
				} else if (angle >= i * 0xF && angle < (i + 1) * 0xF) {
					lineCount++;
					*reinterpret_cast<int*>(self + 0x2030 + i * 4) += colorHit[i];
				} else {
					bitCount++;
					*reinterpret_cast<int*>(self + 0x2024 + i * 4) += colorHit[i];
				}
			}
		}
	}

	*reinterpret_cast<int*>(self + 0x2054) = (*reinterpret_cast<int*>(self + 0x2054) * 100) / 0x7000;

	const int bitDiv = bitCount / 3;
	const int lineDiv = lineCount / 3;
	const int circleDiv = circleCount / 3;

	*reinterpret_cast<int*>(self + 0x2024) = (*reinterpret_cast<int*>(self + 0x2024) * 100) / bitDiv;
	*reinterpret_cast<int*>(self + 0x2028) = (*reinterpret_cast<int*>(self + 0x2028) * 100) / bitDiv;
	*reinterpret_cast<int*>(self + 0x202C) = (*reinterpret_cast<int*>(self + 0x202C) * 100) / bitDiv;
	*reinterpret_cast<int*>(self + 0x2030) = (*reinterpret_cast<int*>(self + 0x2030) * 100) / lineDiv;
	*reinterpret_cast<int*>(self + 0x2034) = (*reinterpret_cast<int*>(self + 0x2034) * 100) / lineDiv;
	*reinterpret_cast<int*>(self + 0x2038) = (*reinterpret_cast<int*>(self + 0x2038) * 100) / lineDiv;
	*reinterpret_cast<int*>(self + 0x203C) = (*reinterpret_cast<int*>(self + 0x203C) * 100) / circleDiv;
	*reinterpret_cast<int*>(self + 0x2040) = (*reinterpret_cast<int*>(self + 0x2040) * 100) / circleDiv;
	*reinterpret_cast<int*>(self + 0x2044) = (*reinterpret_cast<int*>(self + 0x2044) * 100) / circleDiv;

	for (int i = 0; i < 3; i++) {
		const int bit = *reinterpret_cast<int*>(self + 0x2024 + i * 4);
		const int line = *reinterpret_cast<int*>(self + 0x2030 + i * 4);
		const int circle = *reinterpret_cast<int*>(self + 0x203C + i * 4);
		int score = (line + circle * 2 - bit * 2) / 3;
		int level;

		if (score < 0) {
			score = 0;
		} else if (score > 100) {
			score = 100;
		}
		*reinterpret_cast<int*>(self + 0x2018 + i * 4) = score;

		level = (100 - score) / 5;
		if (level < 5) {
			level = 5;
		} else if (level > 0xF) {
			level = 0xF;
		}
		*reinterpret_cast<int*>(self + 0x2048 + i * 4) = level;
	}

	{
		const unsigned int b0 = *reinterpret_cast<unsigned int*>(self + 0x2018);
		const unsigned int b1 = *reinterpret_cast<unsigned int*>(self + 0x201C);
		const unsigned int b2 = *reinterpret_cast<unsigned int*>(self + 0x2020);
		unsigned char radarType = 0;

		if (b0 > 2 && b0 > static_cast<unsigned int>(0.75f * static_cast<float>(b1 + b2))) {
			radarType = 1;
		} else if (b1 > 2 && b1 > static_cast<unsigned int>(0.75f * static_cast<float>(b0 + b2))) {
			radarType = 2;
		} else if (b2 > 2 && b2 > static_cast<unsigned int>(0.75f * static_cast<float>(b0 + b1))) {
			radarType = 3;
		}

		Game[0x13E9] = radarType;
	}

	{
		char** radarLabel = reinterpret_cast<char**>(lbl_801DB694);
		Printf__8CGraphicFUlUlPce(
		    Graphic,
		    5,
		    0xB,
		    lbl_801DB6B4 + 0x18,
		    *reinterpret_cast<int*>(self + 0x2048),
		    *reinterpret_cast<int*>(self + 0x204C),
		    *reinterpret_cast<int*>(self + 0x2050),
		    *reinterpret_cast<int*>(self + 0x2054),
		    *reinterpret_cast<int*>(self + 0x2018),
		    *reinterpret_cast<int*>(self + 0x201C),
		    *reinterpret_cast<int*>(self + 0x2020),
		    *reinterpret_cast<int*>(self + 0x2024),
		    *reinterpret_cast<int*>(self + 0x2028),
		    *reinterpret_cast<int*>(self + 0x202C));

		Printf__8CGraphicFUlUlPce(
		    Graphic,
		    5,
		    0xC,
		    lbl_801DB6B4 + 0x4C,
		    *reinterpret_cast<int*>(self + 0x2030),
		    *reinterpret_cast<int*>(self + 0x2034),
		    *reinterpret_cast<int*>(self + 0x2038),
		    *reinterpret_cast<int*>(self + 0x203C),
		    *reinterpret_cast<int*>(self + 0x2040),
		    *reinterpret_cast<int*>(self + 0x2044),
		    radarLabel[Game[0x13E9]]);
	}
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

extern "C" unsigned char Chara[];
extern "C" void CalcMogScore__6CCharaFv(CChara*);
extern "C" int Find__11CTextureSetFPc(CTextureSet*, char*);
extern "C" void _WaitDrawDone__8CGraphicFPci(void*, const char*, int);
extern "C" char lbl_80331114;
extern "C" char lbl_801DB72C[];

/*
 * --INFO--
 * PAL Address: 0x800e1148
 * PAL Size: 292b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void InitFurTexBuffer__6CCharaFv(CChara* chara)
{
	int i = 0;
	int row = 0;
	do {
		int inner = 0;
		int idx0 = row << 1;
		int count = 8;
		do {
			int idxBase = inner + row;
			*reinterpret_cast<unsigned short*>(Chara + idx0 + 4) = 0x7FFF;
			idx0 += 0x10;
			*reinterpret_cast<unsigned short*>(Chara + ((idxBase + 1) << 1) + 4) = 0x7FFF;
			inner += 8;
			*reinterpret_cast<unsigned short*>(Chara + ((idxBase + 2) << 1) + 4) = 0x7FFF;
			*reinterpret_cast<unsigned short*>(Chara + ((idxBase + 3) << 1) + 4) = 0x7FFF;
			*reinterpret_cast<unsigned short*>(Chara + ((idxBase + 4) << 1) + 4) = 0x7FFF;
			*reinterpret_cast<unsigned short*>(Chara + ((idxBase + 5) << 1) + 4) = 0x7FFF;
			*reinterpret_cast<unsigned short*>(Chara + ((idxBase + 6) << 1) + 4) = 0x7FFF;
			*reinterpret_cast<unsigned short*>(Chara + ((idxBase + 7) << 1) + 4) = 0x7FFF;
			count--;
		} while (count != 0);
		i++;
		row += 0x40;
	} while (i < 0x40);

	*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(chara) + 0x2004) = 0;
	*reinterpret_cast<unsigned int*>(Chara + 0x2014) = System.m_frameCounter;
	memset(reinterpret_cast<unsigned char*>(chara) + 0x2018, 0, 0x40);
	CalcMogScore__6CCharaFv(chara);
}

/*
 * --INFO--
 * PAL Address: 0x800e126c
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void SaveFurTexBuffer__6CCharaFPUs(CChara*, unsigned short* outTexels)
{
	memcpy(outTexels, Chara + 4, 0x2000);
}

/*
 * --INFO--
 * PAL Address: 0x800e12a0
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void LoadFurTexBuffer__6CCharaFPUs(CChara* chara, unsigned short* inTexels)
{
	memcpy(Chara + 4, inTexels, 0x2000);
	CalcMogScore__6CCharaFv(chara);
}

/*
 * --INFO--
 * PAL Address: 0x800e12e4
 * PAL Size: 280b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::InitMogFurTex()
{
	CTextureSet* textureSet = *reinterpret_cast<CTextureSet**>(reinterpret_cast<char*>(this) + 0xB0);
	CPtrArray<CTexture*>* textureArray = reinterpret_cast<CPtrArray<CTexture*>*>(reinterpret_cast<char*>(textureSet) + 8);
	unsigned int textureIdx = static_cast<unsigned int>(Find__11CTextureSetFPc(textureSet, &lbl_80331114));
	CTexture* texture = (*textureArray)[textureIdx];

	if ((texture != 0) && (*reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(texture) + 0x60) == 4)) {
		*reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(texture) + 0x60) = 5;
		_WaitDrawDone__8CGraphicFPci(Graphic, lbl_801DB72C, 0x506);

		textureSet = *reinterpret_cast<CTextureSet**>(reinterpret_cast<char*>(this) + 0xB0);
		textureArray = reinterpret_cast<CPtrArray<CTexture*>*>(reinterpret_cast<char*>(textureSet) + 8);
		textureIdx = static_cast<unsigned int>(Find__11CTextureSetFPc(textureSet, &lbl_80331114));
		CTexture* textureData = (*textureArray)[textureIdx];
		if (textureData != 0) {
			void* dstBuffer = *reinterpret_cast<void**>(reinterpret_cast<char*>(textureData) + 0x78);
			int texelCountBytes = *reinterpret_cast<int*>(reinterpret_cast<char*>(textureData) + 0x64) *
			                      *reinterpret_cast<int*>(reinterpret_cast<char*>(textureData) + 0x68) * 2;

			DCInvalidateRange(dstBuffer, texelCountBytes);
			memcpy(dstBuffer, Chara + 4, 0x2000);
			DCFlushRange(dstBuffer, texelCountBytes);
			GXInvalidateTexAll();
		}

		texture->InitTexObj();
		unsigned char flags = *reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(this) + 0xA0);
		*reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(this) + 0xA0) = flags | 0x40;
	}
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

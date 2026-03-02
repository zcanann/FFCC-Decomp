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
extern "C" unsigned char m_mogWork[];
extern "C" char lbl_801DB694[];
extern "C" char lbl_801DB6B4[];
extern "C" void* lbl_8032EDF0;
extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory*, unsigned long, CMemory::CStage*, char*, int, int);

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
			CColor srcColor(static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b),
			                static_cast<unsigned char>(a));

			*reinterpret_cast<int*>(self + 0x2054) += a;

			int colorHit[3];
			{
				CColor refColor(0xF, 4, 4, 2);
				CColor tmp(srcColor);
				const int d0 =
				    ((static_cast<int>(tmp.color.r) - static_cast<int>(refColor.color.r)) < 0
				         ? -(static_cast<int>(tmp.color.r) - static_cast<int>(refColor.color.r))
				         : (static_cast<int>(tmp.color.r) - static_cast<int>(refColor.color.r))) +
				    (7 - static_cast<int>(tmp.color.a));
				const int d1 =
				    ((static_cast<int>(tmp.color.g) - static_cast<int>(refColor.color.g)) < 0
				         ? -(static_cast<int>(tmp.color.g) - static_cast<int>(refColor.color.g))
				         : (static_cast<int>(tmp.color.g) - static_cast<int>(refColor.color.g))) +
				    (7 - static_cast<int>(tmp.color.a));
				const int d2 =
				    ((static_cast<int>(tmp.color.b) - static_cast<int>(refColor.color.b)) < 0
				         ? -(static_cast<int>(tmp.color.b) - static_cast<int>(refColor.color.b))
				         : (static_cast<int>(tmp.color.b) - static_cast<int>(refColor.color.b))) +
				    (7 - static_cast<int>(tmp.color.a));
				colorHit[0] = (d0 < 6 && d1 < 6 && d2 < 6) ? 1 : 0;
			}
			{
				CColor refColor(4, 0xF, 4, 2);
				CColor tmp(srcColor);
				const int d0 =
				    ((static_cast<int>(tmp.color.r) - static_cast<int>(refColor.color.r)) < 0
				         ? -(static_cast<int>(tmp.color.r) - static_cast<int>(refColor.color.r))
				         : (static_cast<int>(tmp.color.r) - static_cast<int>(refColor.color.r))) +
				    (7 - static_cast<int>(tmp.color.a));
				const int d1 =
				    ((static_cast<int>(tmp.color.g) - static_cast<int>(refColor.color.g)) < 0
				         ? -(static_cast<int>(tmp.color.g) - static_cast<int>(refColor.color.g))
				         : (static_cast<int>(tmp.color.g) - static_cast<int>(refColor.color.g))) +
				    (7 - static_cast<int>(tmp.color.a));
				const int d2 =
				    ((static_cast<int>(tmp.color.b) - static_cast<int>(refColor.color.b)) < 0
				         ? -(static_cast<int>(tmp.color.b) - static_cast<int>(refColor.color.b))
				         : (static_cast<int>(tmp.color.b) - static_cast<int>(refColor.color.b))) +
				    (7 - static_cast<int>(tmp.color.a));
				colorHit[1] = (d0 < 6 && d1 < 6 && d2 < 6) ? 1 : 0;
			}
			{
				CColor refColor(4, 8, 0xF, 2);
				CColor tmp(srcColor);
				const int d0 =
				    ((static_cast<int>(tmp.color.r) - static_cast<int>(refColor.color.r)) < 0
				         ? -(static_cast<int>(tmp.color.r) - static_cast<int>(refColor.color.r))
				         : (static_cast<int>(tmp.color.r) - static_cast<int>(refColor.color.r))) +
				    (7 - static_cast<int>(tmp.color.a));
				const int d1 =
				    ((static_cast<int>(tmp.color.g) - static_cast<int>(refColor.color.g)) < 0
				         ? -(static_cast<int>(tmp.color.g) - static_cast<int>(refColor.color.g))
				         : (static_cast<int>(tmp.color.g) - static_cast<int>(refColor.color.g))) +
				    (7 - static_cast<int>(tmp.color.a));
				const int d2 =
				    ((static_cast<int>(tmp.color.b) - static_cast<int>(refColor.color.b)) < 0
				         ? -(static_cast<int>(tmp.color.b) - static_cast<int>(refColor.color.b))
				         : (static_cast<int>(tmp.color.b) - static_cast<int>(refColor.color.b))) +
				    (7 - static_cast<int>(tmp.color.a));
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
	*reinterpret_cast<int*>(self + 0x203C) = (*reinterpret_cast<int*>(self + 0x203C) * 100) / circleDiv;
	*reinterpret_cast<int*>(self + 0x2030) = (*reinterpret_cast<int*>(self + 0x2030) * 100) / lineDiv;
	*reinterpret_cast<int*>(self + 0x2028) = (*reinterpret_cast<int*>(self + 0x2028) * 100) / bitDiv;
	*reinterpret_cast<int*>(self + 0x2040) = (*reinterpret_cast<int*>(self + 0x2040) * 100) / circleDiv;
	*reinterpret_cast<int*>(self + 0x2034) = (*reinterpret_cast<int*>(self + 0x2034) * 100) / lineDiv;
	*reinterpret_cast<int*>(self + 0x202C) = (*reinterpret_cast<int*>(self + 0x202C) * 100) / bitDiv;
	*reinterpret_cast<int*>(self + 0x2044) = (*reinterpret_cast<int*>(self + 0x2044) * 100) / circleDiv;
	*reinterpret_cast<int*>(self + 0x2038) = (*reinterpret_cast<int*>(self + 0x2038) * 100) / lineDiv;

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
	if (mogMode != 0) {
		memset(m_mogWork, 0, 0x2C);
		*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(this) + 0x200c) = 0x140;
		*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(this) + 0x2010) = 0xE0;
		*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(this) + 0x2004) = 0;
		return;
	}

	int* const mogSoundHandle = reinterpret_cast<int*>(m_mogWork + 0x24);
	if (*mogSoundHandle != 0) {
		Sound.StopSe(*mogSoundHandle);
		*mogSoundHandle = 0;
	}
}

extern "C" unsigned char Chara[];
extern "C" void CalcMogScore__6CCharaFv(CChara*);
extern "C" int Find__11CTextureSetFPc(CTextureSet*, char*);
extern "C" void _WaitDrawDone__8CGraphicFPci(void*, const char*, int);
extern "C" char lbl_80331114;
extern "C" char lbl_801DB72C[];
extern "C" void makeFurTex__6CCharaFv();

static inline unsigned short PackFurTexel(int r, int g, int b, int a)
{
	if (r < 0) {
		r = 0;
	} else if (r > 0xF) {
		r = 0xF;
	}
	if (g < 0) {
		g = 0;
	} else if (g > 0xF) {
		g = 0xF;
	}
	if (b < 0) {
		b = 0;
	} else if (b > 0xF) {
		b = 0xF;
	}
	if (a < 0) {
		a = 0;
	} else if (a > 7) {
		a = 7;
	}
	return static_cast<unsigned short>((b & 0xF) | ((g & 0xF) << 4) | ((r & 0xF) << 8) | ((a & 7) << 12));
}

extern "C" int PickFur__Q26CChara6CModelFPA4_f8_GXColoriiP8_GXColorP8_GXColorP3Vec(
    void*, Mtx, _GXColor, int, int, _GXColor*, _GXColor*, Vec*);
void brush(unsigned short*, int, int, float, float, int, _GXColor, _GXColor*, _GXColor*);

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
 * PAL Address: 0x800e00a8
 * PAL Size: 4120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void MogFurFrame__Q26CChara6CModelFP8CGObject(void* model, void*)
{
	unsigned char* modelBytes = reinterpret_cast<unsigned char*>(model);
	if ((modelBytes[0x10C] & 0x40) == 0) {
		return;
	}

	unsigned char* charaBytes = Chara;
	unsigned int* mogState = reinterpret_cast<unsigned int*>(m_mogWork);
	unsigned int* cursorX = reinterpret_cast<unsigned int*>(charaBytes + 0x200C);
	unsigned int* cursorY = reinterpret_cast<unsigned int*>(charaBytes + 0x2010);
	_GXColor brushColor = CColor(0xF, 4, 4, 2).color;
	_GXColor before = CColor(0, 0, 0, 0).color;
	_GXColor after = before;
	Vec worldPos;

	if (mogState[1] == 0) {
		mogState[6] = *reinterpret_cast<unsigned int*>(charaBytes + 0x2018);
		mogState[7] = *reinterpret_cast<unsigned int*>(charaBytes + 0x201C);
		mogState[8] = *reinterpret_cast<unsigned int*>(charaBytes + 0x2020);
	}

	if (Game[0x13E9] == 1) {
		brushColor = CColor(0xF, 4, 4, 2).color;
	} else if (Game[0x13E9] == 2) {
		brushColor = CColor(4, 0xF, 4, 2).color;
	} else if (Game[0x13E9] == 3) {
		brushColor = CColor(4, 8, 0xF, 2).color;
	} else if (Game[0x13E9] == 4) {
		brushColor = CColor(0, 0, 0, 2).color;
	}

	*cursorX = (*cursorX + 1 + (System.m_frameCounter & 1)) % 0x280;
	*cursorY = (*cursorY + 1 + ((System.m_frameCounter >> 1) & 1)) % 0x1C0;

	PickFur__Q26CChara6CModelFPA4_f8_GXColoriiP8_GXColorP8_GXColorP3Vec(model, 0, brushColor, 1, 0, &before, &after,
	                                                                     &worldPos);
	CalcMogScore__6CCharaFv(reinterpret_cast<CChara*>(charaBytes));
	mogState[1]++;
}

/*
 * --INFO--
 * PAL Address: 0x800e13fc
 * PAL Size: 3448b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" int PickFur__Q26CChara6CModelFPA4_f8_GXColoriiP8_GXColorP8_GXColorP3Vec(
    void* model, Mtx, _GXColor brushColor, int doPaint, int mode, _GXColor* centerBefore, _GXColor* centerAfter, Vec* worldPos)
{
	unsigned char* modelBytes = reinterpret_cast<unsigned char*>(model);
	if ((modelBytes[0x10C] & 0x40) == 0) {
		return -1;
	}

	if (centerBefore != 0) {
		centerBefore->r = 0;
		centerBefore->g = 0;
		centerBefore->b = 0;
		centerBefore->a = 0;
	}
	if (centerAfter != 0) {
		centerAfter->r = 0;
		centerAfter->g = 0;
		centerAfter->b = 0;
		centerAfter->a = 0;
	}
	if (worldPos != 0) {
		worldPos->x = 0.0f;
		worldPos->y = 0.0f;
		worldPos->z = 0.0f;
	}

	CTextureSet* textureSet = *reinterpret_cast<CTextureSet**>(modelBytes + 0xB0);
	if (textureSet == 0) {
		return 0;
	}
	CPtrArray<CTexture*>* textureArray = reinterpret_cast<CPtrArray<CTexture*>*>(reinterpret_cast<char*>(textureSet) + 8);
	unsigned int textureIdx = static_cast<unsigned int>(Find__11CTextureSetFPc(textureSet, &lbl_80331114));
	CTexture* texture = (*textureArray)[textureIdx];
	if (texture == 0) {
		return 0;
	}

	unsigned int format = *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(texture) + 0x60);
	if (format != 5) {
		return 0;
	}

	if (doPaint == 0) {
		return 1;
	}

	unsigned short* dstPixels = *reinterpret_cast<unsigned short**>(reinterpret_cast<unsigned char*>(texture) + 0x78);
	int width = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(texture) + 0x64);
	int height = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(texture) + 0x68);
	if ((dstPixels == 0) || (width <= 0) || (height <= 0)) {
		return 0;
	}

	float fx = static_cast<float>(*reinterpret_cast<unsigned int*>(Chara + 0x200C)) / 640.0f;
	float fy = static_cast<float>(*reinterpret_cast<unsigned int*>(Chara + 0x2010)) / 448.0f;
	if (fx < 0.0f) {
		fx = 0.0f;
	} else if (fx > 1.0f) {
		fx = 1.0f;
	}
	if (fy < 0.0f) {
		fy = 0.0f;
	} else if (fy > 1.0f) {
		fy = 1.0f;
	}

	if (worldPos != 0) {
		worldPos->x = fx;
		worldPos->y = fy;
		worldPos->z = 0.0f;
	}
	brush(dstPixels, width, height, fx, fy, mode, brushColor, centerBefore, centerAfter);
	return 1;
}

/*
 * --INFO--
 * PAL Address: 0x800e25e8
 * PAL Size: 3296b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void DrawFur__Q26CChara6CModelFPA4_fi(void* model, Mtx, int shadowPass)
{
	unsigned char* modelBytes = reinterpret_cast<unsigned char*>(model);

	if ((modelBytes[0x10C] & 0x40) == 0) {
		return;
	}

	if ((shadowPass != 0) && ((modelBytes[0x10C] & 0x80) == 0)) {
		return;
	}

	if (lbl_8032EDF0 == 0) {
		makeFurTex__6CCharaFv();
	}
	if (lbl_8032EDF0 == 0) {
		return;
	}

	GXTexObj texObj;
	int layer = static_cast<int>((System.m_frameCounter >> 2) & 7);
	void* texData = reinterpret_cast<unsigned char*>(lbl_8032EDF0) + layer * 0x4000;
	GXInitTexObj(&texObj, texData, 0x80, 0x80, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, GX_FALSE);
	GXLoadTexObj(&texObj, GX_TEXMAP1);
	GXSetNumTexGens(1);
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
	GXSetNumTevStages(1);
	GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
}

/*
 * --INFO--
 * PAL Address: 0x800e32c8
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void freeFurTex__6CCharaFv()
{
    if (lbl_8032EDF0 != 0) {
        Memory.Free(lbl_8032EDF0);
        lbl_8032EDF0 = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800e3304
 * PAL Size: 4996b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void makeFurTex__6CCharaFv()
{
	if (lbl_8032EDF0 == 0) {
		lbl_8032EDF0 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(&Memory, 0x20000, 0, lbl_801DB72C, 0xE9, 0);
	}
	if (lbl_8032EDF0 == 0) {
		return;
	}

	unsigned short* tex = reinterpret_cast<unsigned short*>(lbl_8032EDF0);
	unsigned int rng = 0x1234ABCD;
	for (int layer = 0; layer < 8; layer++) {
		unsigned short* layerTex = tex + (layer * 0x4000 / 2);
		for (int y = 0; y < 0x80; y++) {
			for (int x = 0; x < 0x80; x++) {
				int dx = x - 0x40;
				int dy = y - 0x40;
				int dist = static_cast<int>(sqrt(static_cast<double>(dx * dx + dy * dy)));
				int edge = 0x40 - dist;
				if (edge < 0) {
					edge = 0;
				}
				rng = rng * 0x41C64E6D + 0x3039;
				int noise = static_cast<int>((rng >> 16) & 0x1F) - 0x10;
				int tone = (layer * 2) + (edge >> 2) + (noise >> 2);
				int a = (edge + layer) >> 4;
				layerTex[(y * 0x80) + x] = PackFurTexel(tone, tone, tone, a);
			}
		}
	}

	DCFlushRange(lbl_8032EDF0, 0x20000);
	GXInvalidateTexAll();
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
	// Decompiled helper currently side-effect free in this unit.
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CHairSet::CHairSet()
    : m_vec0(), m_vec1()
{
	m_colors[0] = CColor(0x80, 0x80, 0x80, 0xFF);
	m_colors[1] = CColor(0xF0, 0xF0, 0xF0, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GXSetTexCoordGen(void)
{
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
}

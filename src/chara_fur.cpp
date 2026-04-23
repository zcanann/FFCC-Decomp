#include "ffcc/chara_fur.h"
#include "ffcc/chara.h"
#include "ffcc/charaobj.h"
#include "ffcc/cflat_data.h"
#include "ffcc/math.h"
#include "ffcc/gobject.h"
#include "ffcc/graphic.h"
#include "ffcc/linkage.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_menu.h"
#include "ffcc/p_light.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include "ffcc/textureman.h"

#include <math.h>
#include <string.h>

struct Vec4d
{
	float x;
	float y;
	float z;
	float w;
};

template <class T>
class CPtrArray
{
public:
	T operator[](unsigned long index);
};

extern "C" void Printf__8CGraphicFUlUlPce(void*, unsigned long, unsigned long, const char*, ...);
extern "C" char* sMogRadarTypeLabels[];
extern "C" char sMogRadarDebugFormatBlock[];
extern "C" char sMogFurTextureName[];
extern "C" {
unsigned char m_mogWork[0x30];
void* gMogFurTexBuffer;
}
extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory*, unsigned long, CMemory::CStage*, char*, int, int);
extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" void _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(int, int, int, int, int);
static inline unsigned char* GameRaw() { return reinterpret_cast<unsigned char*>(&Game); }

namespace {

struct FurPtrArrayRaw
{
    unsigned long m_numItems;
    unsigned long m_size;
    unsigned long m_defaultSize;
    void** m_items;
    CMemory::CStage* m_stage;
    int m_growCapacity;
};

struct FurMaterialSetRaw
{
    void* m_vtable;
    int m_refCount;
    FurPtrArrayRaw m_materials;
};

struct FurMaterialRaw
{
    unsigned char m_pad0[0x3C];
    CTexture* m_textures[4];
    unsigned char m_pad4C[0x5B];
    unsigned char m_furEnable;
};

struct FurDisplayListRaw
{
    void* m_data;
    int m_size;
    unsigned short m_material;
    unsigned short m_padA;
};

struct FurMeshRefRaw
{
    char m_name[0x10];
    unsigned char m_flags;
    unsigned char m_pad11[3];
    unsigned int m_vertexCount;
    S16Vec* m_vertices;
    unsigned int m_normalCount;
    S16Vec* m_normals;
    unsigned int m_colorCount;
    void* m_colors;
    unsigned int m_uvCount;
    void* m_uvs;
    unsigned int m_oneWeightCountOrSize;
    void* m_oneWeightData;
    unsigned int m_twoWeightCountOrSize;
    void* m_twoWeightData;
    unsigned int m_threeWeightCountOrSize;
    void* m_threeWeightData;
    unsigned int m_displayListCount;
    FurDisplayListRaw* m_displayLists;
    unsigned int m_skinCount;
    void* m_skins;
    unsigned int m_infoWord1;
    unsigned int m_nodeIndex;
};

struct FurMeshRaw
{
    FurMeshRefRaw* m_data;
    S16Vec* m_workPositions;
    S16Vec* m_workNormals;
    unsigned char m_padC[8];
};

struct FurTexCoordRaw
{
    short s;
    short t;
};

struct FurProjectedVertex
{
    bool m_valid;
    Vec m_viewPos;
    float m_screenX;
    float m_screenY;
    float m_u;
    float m_v;
};

static inline unsigned char* ModelRaw(void* model)
{
    return reinterpret_cast<unsigned char*>(model);
}

static inline void* ModelRef(void* model)
{
    return *reinterpret_cast<void**>(ModelRaw(model) + 0xA4);
}

static inline CMaterialSet* ModelMaterialSet(void* model)
{
    return *reinterpret_cast<CMaterialSet**>(reinterpret_cast<unsigned char*>(ModelRef(model)) + 0x20);
}

static inline FurMeshRaw* ModelMeshes(void* model)
{
    return *reinterpret_cast<FurMeshRaw**>(ModelRaw(model) + 0xAC);
}

static inline void* ModelNodes(void* model)
{
    return *reinterpret_cast<void**>(ModelRaw(model) + 0xA8);
}

static inline unsigned short ModelMeshCount(void* model)
{
    return *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(ModelRef(model)) + 0x0A);
}

static inline unsigned int ModelMeshVisibleMask(void* model)
{
    return *reinterpret_cast<unsigned int*>(ModelRaw(model) + 0x98);
}

static inline float (*ModelDrawMtx(void* model))[4]
{
    return reinterpret_cast<float(*)[4]>(ModelRaw(model) + 0x08);
}

static inline int ModelPosQuant(void* model)
{
    return *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(ModelRef(model)) + 0x2C);
}

static inline int ModelNormQuant(void* model)
{
    return *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(ModelRef(model)) + 0x30);
}

static inline float ModelLightAlpha(void* model)
{
    return *reinterpret_cast<float*>(ModelRaw(model) + 0x9C);
}

static inline float ModelFurLenScale(void* model)
{
    return *reinterpret_cast<float*>(ModelRaw(model) + 0x110);
}

static inline float ModelFurStep(void* model)
{
    return *reinterpret_cast<float*>(ModelRaw(model) + 0x114);
}

static inline float ModelFurCur(void* model)
{
    return *reinterpret_cast<float*>(ModelRaw(model) + 0x11C);
}

static inline unsigned char ModelFlags10C(void* model)
{
    return *(ModelRaw(model) + 0x10C);
}

static inline float QuantizedToFloat(short value, int frac)
{
    if (frac <= 0) {
        return static_cast<float>(value);
    }
    return static_cast<float>(value) / static_cast<float>(1 << frac);
}

static bool ProjectFurVertex(FurProjectedVertex& out, const FurMeshRaw* mesh, const Mtx modelViewMtx, unsigned short posIdx,
                             unsigned short uvIdx, int posQuant)
{
    out.m_valid = false;
    if (mesh == 0 || mesh->m_data == 0 || mesh->m_workPositions == 0 || mesh->m_data->m_uvs == 0) {
        return false;
    }
    if (posIdx >= mesh->m_data->m_vertexCount || uvIdx >= mesh->m_data->m_uvCount) {
        return false;
    }

    const S16Vec& pos = mesh->m_workPositions[posIdx];
    const FurTexCoordRaw& uv = reinterpret_cast<FurTexCoordRaw*>(mesh->m_data->m_uvs)[uvIdx];
    Vec localPos;
    localPos.x = QuantizedToFloat(pos.x, posQuant);
    localPos.y = QuantizedToFloat(pos.y, posQuant);
    localPos.z = QuantizedToFloat(pos.z, posQuant);
    PSMTXMultVec(modelViewMtx, &localPos, &out.m_viewPos);

    if (out.m_viewPos.z >= -0.0001f) {
        return false;
    }

    Vec4d clipPos;
    Math.MTX44MultVec4(CameraPcs.m_screenMatrix, &out.m_viewPos, &clipPos);
    if (clipPos.w == 0.0f) {
        return false;
    }

    const float invW = 1.0f / clipPos.w;
    out.m_screenX = clipPos.x * invW * 320.0f + 320.0f;
    out.m_screenY = 224.0f - clipPos.y * invW * 224.0f;
    out.m_u = static_cast<float>(uv.s) / 4096.0f;
    out.m_v = static_cast<float>(uv.t) / 4096.0f;
    out.m_valid = true;
    return true;
}

static bool FurPointInTriangle(float px, float py, const FurProjectedVertex& a, const FurProjectedVertex& b,
                               const FurProjectedVertex& c, float& outW0, float& outW1, float& outW2)
{
    const float v0x = b.m_screenX - a.m_screenX;
    const float v0y = b.m_screenY - a.m_screenY;
    const float v1x = c.m_screenX - a.m_screenX;
    const float v1y = c.m_screenY - a.m_screenY;
    const float v2x = px - a.m_screenX;
    const float v2y = py - a.m_screenY;
    const float denom = v0x * v1y - v1x * v0y;

    if (denom > -0.0001f && denom < 0.0001f) {
        return false;
    }

    const float invDenom = 1.0f / denom;
    outW1 = (v2x * v1y - v1x * v2y) * invDenom;
    outW2 = (v0x * v2y - v2x * v0y) * invDenom;
    outW0 = 1.0f - outW1 - outW2;
    return outW0 >= 0.0f && outW1 >= 0.0f && outW2 >= 0.0f;
}

static void FurInterpolateHit(Vec& outViewPos, float& outU, float& outV, const FurProjectedVertex& a,
                              const FurProjectedVertex& b, const FurProjectedVertex& c, float w0, float w1, float w2)
{
    outViewPos.x = a.m_viewPos.x * w0 + b.m_viewPos.x * w1 + c.m_viewPos.x * w2;
    outViewPos.y = a.m_viewPos.y * w0 + b.m_viewPos.y * w1 + c.m_viewPos.y * w2;
    outViewPos.z = a.m_viewPos.z * w0 + b.m_viewPos.z * w1 + c.m_viewPos.z * w2;
    outU = a.m_u * w0 + b.m_u * w1 + c.m_u * w2;
    outV = a.m_v * w0 + b.m_v * w1 + c.m_v * w2;
}

static void DrawFurDisplayListShell(const FurMeshRaw* mesh, const FurDisplayListRaw* displayList, float shellOffset,
                                    int posQuant, int normQuant)
{
    if (mesh == 0 || mesh->m_data == 0 || mesh->m_workPositions == 0 || mesh->m_workNormals == 0 || displayList == 0 ||
        displayList->m_data == 0 || displayList->m_size <= 0) {
        return;
    }

    const unsigned char* cursor = reinterpret_cast<const unsigned char*>(displayList->m_data);
    int remaining = displayList->m_size;

    while (remaining > 0) {
        const unsigned char command = cursor[0];
        if ((command & 0xF8) == 0) {
            break;
        }
        if (remaining < 3) {
            break;
        }

        const GXPrimitive primitive = static_cast<GXPrimitive>(command & 0xF8);
        const unsigned short count = *reinterpret_cast<const unsigned short*>(cursor + 1);
        cursor += 3;
        remaining -= 3;

        if ((primitive != static_cast<GXPrimitive>(0x90) && primitive != static_cast<GXPrimitive>(0x98)) ||
            remaining < static_cast<int>(count) * 8) {
            const int skip = static_cast<int>(count) * 8;
            if (skip > remaining) {
                break;
            }
            cursor += skip;
            remaining -= skip;
            continue;
        }

        GXBegin(primitive, GX_VTXFMT0, count);
        for (unsigned short i = 0; i < count; i++) {
            const unsigned short* indices = reinterpret_cast<const unsigned short*>(cursor);
            const unsigned short posIdx = indices[0];
            const unsigned short nrmIdx = indices[1];
            const unsigned short uvIdx = indices[3];
            const S16Vec& pos = mesh->m_workPositions[posIdx];
            const S16Vec& nrm = mesh->m_workNormals[nrmIdx];

            const float px = QuantizedToFloat(pos.x, posQuant) + QuantizedToFloat(nrm.x, normQuant) * shellOffset;
            const float py = QuantizedToFloat(pos.y, posQuant) + QuantizedToFloat(nrm.y, normQuant) * shellOffset;
            const float pz = QuantizedToFloat(pos.z, posQuant) + QuantizedToFloat(nrm.z, normQuant) * shellOffset;

            GXPosition3f32(px, py, pz);
            GXNormal1x16(static_cast<short>(nrmIdx));
            GXTexCoord1x16(static_cast<short>(uvIdx));

            cursor += 8;
            remaining -= 8;
        }
    }
}

} // namespace

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

		GameRaw()[0x13E9] = radarType;
	}

	{
		char** radarLabel = reinterpret_cast<char**>(sMogRadarTypeLabels);
		Printf__8CGraphicFUlUlPce(
		    &Graphic,
		    5,
		    0xB,
		    sMogRadarDebugFormatBlock + 0x18,
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
		    &Graphic,
		    5,
		    0xC,
		    sMogRadarDebugFormatBlock + 0x4C,
		    *reinterpret_cast<int*>(self + 0x2030),
		    *reinterpret_cast<int*>(self + 0x2034),
		    *reinterpret_cast<int*>(self + 0x2038),
		    *reinterpret_cast<int*>(self + 0x203C),
		    *reinterpret_cast<int*>(self + 0x2040),
		    *reinterpret_cast<int*>(self + 0x2044),
		    radarLabel[GameRaw()[0x13E9]]);
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

extern "C" void CalcMogScore__6CCharaFv(CChara*);
extern "C" int Find__11CTextureSetFPc(CTextureSet*, char*);
extern "C" void _WaitDrawDone__8CGraphicFPci(void*, const char*, int);
extern "C" void SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
    void*, int, int, int, int, void*, void*);
extern "C" int GetWait__4CMesFv(void*);
extern "C" void Open__8CMesMenuFPciiiiii(void*, char*, int, int, int, int, int, int);
static const char s_chara_fur_cpp_801db72c[] = "chara_fur.cpp";
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

static float FurRand01(unsigned int& rng)
{
	rng = rng * 0x41C64E6D + 0x3039;
	return static_cast<float>((rng >> 16) & 0x7FFF) / 32767.0f;
}

static int FurBlendNibble(int base, int add, float t)
{
	int value = static_cast<int>(base + (add - base) * t);
	if (value < 0) {
		return 0;
	}
	if (value > 0xF) {
		return 0xF;
	}
	return value;
}

static void FurWriteTexel(unsigned short* tex, int x, int y, int r, int g, int b, int a)
{
	if (x < 0 || x >= 0x80 || y < 0 || y >= 0x80) {
		return;
	}

	unsigned short* texel = tex + y * 0x80 + x;
	unsigned short oldPacked = *texel;
	int oldB = oldPacked & 0x0F;
	int oldG = (oldPacked >> 4) & 0x0F;
	int oldR = (oldPacked >> 8) & 0x0F;
	int oldA = (oldPacked >> 12) & 0x07;

	if (a < oldA) {
		a = oldA;
	}
	if (r < oldR) {
		r = oldR;
	}
	if (g < oldG) {
		g = oldG;
	}
	if (b < oldB) {
		b = oldB;
	}

	*texel = PackFurTexel(r, g, b, a);
}

static void FurInitHairSet(CHairSet& hair, unsigned int& rng)
{
	hair.m_vec0.x = 64.0f + (FurRand01(rng) - 0.5f) * 56.0f;
	hair.m_vec0.y = 72.0f + FurRand01(rng) * 40.0f;
	hair.m_vec0.z = 0.0f;
	hair.m_vec1.x = (FurRand01(rng) - 0.5f) * 2.0f;
	hair.m_vec1.y = -(0.6f + FurRand01(rng) * 1.4f);
	hair.m_vec1.z = 0.0f;
	hair.m_colors[0].color = CColor(
	    static_cast<unsigned char>(6 + static_cast<int>(FurRand01(rng) * 5.0f)),
	    static_cast<unsigned char>(6 + static_cast<int>(FurRand01(rng) * 5.0f)),
	    static_cast<unsigned char>(6 + static_cast<int>(FurRand01(rng) * 5.0f)),
	    0).color;
	hair.m_colors[1].color = CColor(
	    static_cast<unsigned char>(0xB + static_cast<int>(FurRand01(rng) * 4.0f)),
	    static_cast<unsigned char>(0xB + static_cast<int>(FurRand01(rng) * 4.0f)),
	    static_cast<unsigned char>(0xB + static_cast<int>(FurRand01(rng) * 4.0f)),
	    0).color;
}

static void FurPlotHair(unsigned short* tex, const CHairSet& hair, int layer, unsigned int& rng)
{
	CVector pos = hair.m_vec0;
	CVector vel = hair.m_vec1;
	const float layerT = static_cast<float>(layer) / 7.0f;
	const int steps = 10 + layer * 2;

	for (int step = 0; step < steps; step++) {
		float t = (steps > 1) ? static_cast<float>(step) / static_cast<float>(steps - 1) : 0.0f;
		int radius = (step < 2) ? 2 : 1;
		int alpha = 1 + ((layer + step) >> 2);
		int r = FurBlendNibble(hair.m_colors[0].color.r, hair.m_colors[1].color.r, t);
		int g = FurBlendNibble(hair.m_colors[0].color.g, hair.m_colors[1].color.g, t);
		int b = FurBlendNibble(hair.m_colors[0].color.b, hair.m_colors[1].color.b, t);

		for (int oy = -radius; oy <= radius; oy++) {
			for (int ox = -radius; ox <= radius; ox++) {
				int falloff = (ox < 0 ? -ox : ox) + (oy < 0 ? -oy : oy);
				FurWriteTexel(tex, static_cast<int>(pos.x) + ox, static_cast<int>(pos.y) + oy,
				              r - falloff, g - falloff, b - falloff, alpha - (falloff >> 1));
			}
		}

		vel.x += (FurRand01(rng) - 0.5f) * (0.18f + layerT * 0.15f);
		vel.y += 0.08f + layerT * 0.06f;
		pos.x += vel.x;
		pos.y += vel.y;
	}
}

extern "C" int PickFur__Q26CChara6CModelFPA4_f8_GXColoriiP8_GXColorP8_GXColorP3Vec(
    void*, Mtx, _GXColor, int, int, _GXColor*, _GXColor*, Vec*);
void brush(unsigned short*, int, int, float, float, int, _GXColor, _GXColor*, _GXColor*);

namespace {

struct MogWorkRaw
{
	int m_state;
	int m_frameCount;
	int m_pickTicks;
	int m_idleTicks;
	int m_offColorTicks;
	int m_eraseTicks;
	int m_prevScoreA;
	int m_prevScoreB;
	int m_prevScoreC;
	int m_loopSeHandle;
	int m_started;
	int m_pad2C;
};

static inline MogWorkRaw& MogWork()
{
	return *reinterpret_cast<MogWorkRaw*>(m_mogWork);
}

static inline int& CharaS32(int offset)
{
	return *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&Chara) + offset);
}

static inline unsigned int& CharaU32(int offset)
{
	return *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(&Chara) + offset);
}

static inline bool HasDebugPadOverride()
{
	return (Pad._452_4_ != 0) || (Pad._448_4_ != -1);
}

static inline unsigned short MogHeldButtons()
{
	if (HasDebugPadOverride()) {
		return 0;
	}
	return static_cast<unsigned short>(Pad._4_2_);
}

static inline unsigned short MogTriggerButtons()
{
	if (HasDebugPadOverride()) {
		return 0;
	}
	return static_cast<unsigned short>(Pad._8_2_);
}

static inline int MogPadInt(int offset)
{
	if (HasDebugPadOverride()) {
		return 0;
	}
	return *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&Pad) + offset);
}

static inline unsigned char MogRadarType()
{
	return GameRaw()[0x13E9];
}

static inline _GXColor MogBrushColor(unsigned char radarType)
{
	switch (radarType) {
	case 1:
		return CColor(0xF, 4, 4, 2).color;
	case 2:
		return CColor(4, 0xF, 4, 2).color;
	case 3:
		return CColor(4, 8, 0xF, 2).color;
	case 4:
		return CColor(0, 0, 0, 2).color;
	default:
		return CColor(0xF, 0xF, 0xF, 4).color;
	}
}

static inline bool MogColorChanged(const _GXColor& a, const _GXColor& b)
{
	return a.r != b.r || a.g != b.g || a.b != b.b || a.a != b.a;
}

static inline bool MogColorNear(const _GXColor& a, const _GXColor& b, int threshold)
{
	const int dr = static_cast<int>(a.r) - static_cast<int>(b.r);
	const int dg = static_cast<int>(a.g) - static_cast<int>(b.g);
	const int db = static_cast<int>(a.b) - static_cast<int>(b.b);
	const int da = static_cast<int>(a.a) - static_cast<int>(b.a);
	const int total = (dr < 0 ? -dr : dr) + (dg < 0 ? -dg : dg) + (db < 0 ? -db : db) + (da < 0 ? -da : da);
	return total <= threshold;
}

static inline void StopMogLoopSe(MogWorkRaw& work)
{
	if (work.m_loopSeHandle != 0) {
		Sound.StopSe(work.m_loopSeHandle);
		work.m_loopSeHandle = 0;
	}
}

static CTexture* FindMogFurTexture(void* model)
{
	unsigned char* modelBytes = reinterpret_cast<unsigned char*>(model);
	CTextureSet* textureSet = *reinterpret_cast<CTextureSet**>(modelBytes + 0xB0);
	if (textureSet == 0) {
		return 0;
	}

	CPtrArray<CTexture*>* textureArray = reinterpret_cast<CPtrArray<CTexture*>*>(reinterpret_cast<char*>(textureSet) + 8);
	unsigned int textureIdx = static_cast<unsigned int>(Find__11CTextureSetFPc(textureSet, &sMogFurTextureName[0]));
	return (*textureArray)[textureIdx];
}

static void CopyMogTextureFromChara(void* model)
{
	CTexture* texture = FindMogFurTexture(model);
	if (texture == 0) {
		return;
	}

	void* dstBuffer = *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(texture) + 0x78);
	const int texelCountBytes = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(texture) + 0x64) *
	                            *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(texture) + 0x68) * 2;
	if (dstBuffer == 0 || texelCountBytes <= 0) {
		return;
	}

	_WaitDrawDone__8CGraphicFPci(&Graphic, const_cast<char*>(s_chara_fur_cpp_801db72c), 0x506);
	DCInvalidateRange(dstBuffer, texelCountBytes);
	memcpy(dstBuffer, reinterpret_cast<unsigned char*>(&Chara) + 4, 0x2000);
	DCFlushRange(dstBuffer, texelCountBytes);
	GXInvalidateTexAll();
}

static void CopyMogTextureToChara(void* model)
{
	CTexture* texture = FindMogFurTexture(model);
	if (texture == 0) {
		return;
	}

	void* srcBuffer = *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(texture) + 0x78);
	const int texelCountBytes = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(texture) + 0x64) *
	                            *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(texture) + 0x68) * 2;
	if (srcBuffer == 0 || texelCountBytes <= 0) {
		return;
	}

	_WaitDrawDone__8CGraphicFPci(&Graphic, const_cast<char*>(s_chara_fur_cpp_801db72c), 0x506);
	memcpy(reinterpret_cast<unsigned char*>(&Chara) + 4, srcBuffer, 0x2000);
	DCFlushRange(srcBuffer, texelCountBytes);
	GXInvalidateTexAll();
}

static void OpenMogHintMessage(int messageId)
{
	if (messageId < 0) {
		return;
	}

	void* mesMenu = *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(&MenuPcs) + 0x288);
	if (mesMenu == 0) {
		return;
	}

	const bool isBusy = (*(reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(mesMenu) + 8)) != 0) &&
	                    (*(reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(mesMenu) + 0x0C)) < 2) &&
	                    (GetWait__4CMesFv(reinterpret_cast<unsigned char*>(mesMenu) + 0x1C) != 4);
	if (isBusy) {
		return;
	}

	CFlatData* flatData = reinterpret_cast<CFlatData*>(reinterpret_cast<unsigned char*>(&Game) + 0xCC38 + sizeof(CFlatData));
	char** mesPtr = reinterpret_cast<char**>(reinterpret_cast<unsigned char*>(flatData) + 0xD4);
	Open__8CMesMenuFPciiiiii(mesMenu, mesPtr[messageId + 8], 0x160, 0x20, 0x220, 0, -1, -1);
}

} // namespace

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
			*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(&Chara) + idx0 + 4) = 0x7FFF;
			idx0 += 0x10;
			*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(&Chara) + ((idxBase + 1) << 1) + 4) = 0x7FFF;
			inner += 8;
			*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(&Chara) + ((idxBase + 2) << 1) + 4) = 0x7FFF;
			*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(&Chara) + ((idxBase + 3) << 1) + 4) = 0x7FFF;
			*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(&Chara) + ((idxBase + 4) << 1) + 4) = 0x7FFF;
			*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(&Chara) + ((idxBase + 5) << 1) + 4) = 0x7FFF;
			*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(&Chara) + ((idxBase + 6) << 1) + 4) = 0x7FFF;
			*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(&Chara) + ((idxBase + 7) << 1) + 4) = 0x7FFF;
			count--;
		} while (count != 0);
		i++;
		row += 0x40;
	} while (i < 0x40);

	*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(chara) + 0x2004) = 0;
	*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(&Chara) + 0x2014) = System.m_frameCounter;
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
	memcpy(outTexels, reinterpret_cast<unsigned char*>(&Chara) + 4, 0x2000);
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
	memcpy(reinterpret_cast<unsigned char*>(&Chara) + 4, inTexels, 0x2000);
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
	unsigned int textureIdx = static_cast<unsigned int>(Find__11CTextureSetFPc(textureSet, &sMogFurTextureName[0]));
	CTexture* texture = (*textureArray)[textureIdx];

	if ((texture != 0) && (*reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(texture) + 0x60) == 4)) {
		*reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(texture) + 0x60) = 5;
		_WaitDrawDone__8CGraphicFPci(&Graphic, const_cast<char*>(s_chara_fur_cpp_801db72c), 0x506);

		textureSet = *reinterpret_cast<CTextureSet**>(reinterpret_cast<char*>(this) + 0xB0);
		textureArray = reinterpret_cast<CPtrArray<CTexture*>*>(reinterpret_cast<char*>(textureSet) + 8);
		textureIdx = static_cast<unsigned int>(Find__11CTextureSetFPc(textureSet, &sMogFurTextureName[0]));
		CTexture* textureData = (*textureArray)[textureIdx];
		if (textureData != 0) {
			void* dstBuffer = *reinterpret_cast<void**>(reinterpret_cast<char*>(textureData) + 0x78);
			int texelCountBytes = *reinterpret_cast<int*>(reinterpret_cast<char*>(textureData) + 0x64) *
			                      *reinterpret_cast<int*>(reinterpret_cast<char*>(textureData) + 0x68) * 2;

			DCInvalidateRange(dstBuffer, texelCountBytes);
			memcpy(dstBuffer, reinterpret_cast<unsigned char*>(&Chara) + 4, 0x2000);
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
extern "C" void MogFurFrame__Q26CChara6CModelFP8CGObject(void* model, void* object)
{
	unsigned char* modelBytes = reinterpret_cast<unsigned char*>(model);
	if ((modelBytes[0x10C] & 0x40) == 0) {
		return;
	}

	CGObject* gObject = reinterpret_cast<CGObject*>(object);
	MogWorkRaw& work = MogWork();
	const unsigned short heldButtons = MogHeldButtons();
	const unsigned short triggerButtons = MogTriggerButtons();
	const unsigned short rotateButtons = (MogPadInt(64) == 0) ? heldButtons : 0;
	int messageId = -1;

	if (work.m_started == 0) {
		if ((heldButtons & 0x100) != 0) {
			return;
		}
		work.m_started = 1;
	}

	if (work.m_frameCount == 0) {
		work.m_prevScoreA = CharaS32(0x2018);
		work.m_prevScoreB = CharaS32(0x201C);
		work.m_prevScoreC = CharaS32(0x2020);
	}

	if (gObject != 0) {
		if (work.m_state == 0) {
			if ((rotateButtons & 1) != 0) {
				gObject->m_rotTargetY -= 0.03125f;
				if (gObject->m_currentAnimSlot < 0) {
					gObject->PlayAnim(1, 0, 0, -1, -1, 0);
				}
			} else if ((rotateButtons & 2) != 0) {
				gObject->m_rotTargetY += 0.03125f;
				if (gObject->m_currentAnimSlot < 0) {
					gObject->PlayAnim(1, 0, 0, -1, -1, 0);
				}
			} else if (gObject->m_currentAnimSlot >= 0) {
				gObject->CancelAnim(1);
			}

			if ((rotateButtons & 8) != 0) {
				work.m_state = 1;
				gObject->PlayAnim(0x37, 1, 0, -1, -1, 0);
				messageId = 7;
			}
		} else if (gObject->IsLoopAnim(1) != 0) {
			gObject->CancelAnim(1);
			work.m_state = 0;
		}
	}

	const float cursorStep = 0.1f;
	const int cursorX = static_cast<int>(static_cast<float>(static_cast<int>(CharaU32(0x200C))) +
	                                     static_cast<float>(MogPadInt(36)) * cursorStep);
	const int cursorY = static_cast<int>(static_cast<float>(static_cast<int>(CharaU32(0x2010))) -
	                                     static_cast<float>(MogPadInt(40)) * cursorStep);

	if (cursorX < 0) {
		CharaU32(0x200C) = 0;
	} else if (cursorX > 0x280) {
		CharaU32(0x200C) = 0x280;
	} else {
		CharaU32(0x200C) = static_cast<unsigned int>(cursorX);
	}
	if (cursorY < 0) {
		CharaU32(0x2010) = 0;
	} else if (cursorY > 0x1C0) {
		CharaU32(0x2010) = 0x1C0;
	} else {
		CharaU32(0x2010) = static_cast<unsigned int>(cursorY);
	}

	if ((heldButtons & 0x100) != 0) {
		const unsigned char radarType = MogRadarType();
		const _GXColor brushColor = MogBrushColor(radarType);
		const int eraseMode = (radarType == 4) ? 1 : 0;
		const int doPaint = (radarType == 4) ? (((System.m_frameCounter & 3U) == 0) ? 0 : 1) : 1;
		_GXColor centerBefore = CColor(0xF, 0xF, 0xF, 0).color;
		_GXColor centerAfter = centerBefore;
		Vec worldPos;
		Mtx cameraMtx;

		PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
		CopyMogTextureFromChara(model);
		int pickResult = PickFur__Q26CChara6CModelFPA4_f8_GXColoriiP8_GXColorP8_GXColorP3Vec(
		    model, cameraMtx, brushColor, doPaint, eraseMode, &centerBefore, &centerAfter, &worldPos);
		CopyMogTextureToChara(model);
		CalcMogScore__6CCharaFv(&Chara);

		if (pickResult >= 0) {
			work.m_pickTicks++;

			const int scoreDeltaA = CharaS32(0x2018) - work.m_prevScoreA;
			const int scoreDeltaB = CharaS32(0x201C) - work.m_prevScoreB;
			const int scoreDeltaC = CharaS32(0x2020) - work.m_prevScoreC;
			if (((scoreDeltaA < 0 ? -scoreDeltaA : scoreDeltaA) >= 5) ||
			    ((scoreDeltaB < 0 ? -scoreDeltaB : scoreDeltaB) >= 5) ||
			    ((scoreDeltaC < 0 ? -scoreDeltaC : scoreDeltaC) >= 5)) {
				work.m_prevScoreA = CharaS32(0x2018);
				work.m_prevScoreB = CharaS32(0x201C);
				work.m_prevScoreC = CharaS32(0x2020);
				messageId = 1;
			}

			if (pickResult == 0) {
				work.m_idleTicks++;
				if (work.m_idleTicks == 0x3C && messageId < 0) {
					messageId = 3;
				} else if (work.m_idleTicks == 0xF0 && messageId < 0) {
					messageId = 4;
				}
			} else {
				work.m_idleTicks = 0;
			}

			if (eraseMode != 0) {
				work.m_offColorTicks = 0;
				if ((centerBefore.a != 0) && (centerAfter.a < centerBefore.a)) {
					work.m_eraseTicks++;
					if (work.m_eraseTicks == 10 && messageId < 0) {
						messageId = 5;
					} else if (work.m_eraseTicks == 0x32 && messageId < 0) {
						messageId = 6;
					}
				}
			} else {
				work.m_eraseTicks = 0;
				if ((centerAfter.a != 0) && !MogColorNear(centerAfter, brushColor, 8)) {
					work.m_offColorTicks++;
					if (work.m_offColorTicks == 10 && messageId < 0) {
						messageId = 2;
					}
				} else {
					work.m_offColorTicks = 0;
				}
			}
		}

		if ((radarType < 4) && (pickResult > 0)) {
			if (work.m_loopSeHandle == 0) {
				work.m_loopSeHandle = Sound.PlaySe(0x249f2, 0x40, 0x7F, 0);
			}
		} else {
			StopMogLoopSe(work);
		}
	} else {
		StopMogLoopSe(work);
	}

	if ((triggerButtons & 0x200) != 0) {
		int stack[3];
		stack[0] = 2;
		stack[1] = 0;
		stack[2] = 0;
		SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
		    &CFlat, 0, 1, 9, 3, stack, 0);
	}

	OpenMogHintMessage(messageId);
	work.m_frameCount++;
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
    void* model, Mtx param_2, _GXColor brushColor, int doPaint, int mode, _GXColor* centerBefore, _GXColor* centerAfter, Vec* worldPos)
{
	if ((ModelFlags10C(model) & 0x40) == 0) {
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

	CTexture* texture = FindMogFurTexture(model);
	if (texture == 0) {
		return 0;
	}

	const unsigned int format = *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(texture) + 0x60);
	if (format != 5) {
		return 0;
	}

	unsigned short* dstPixels = *reinterpret_cast<unsigned short**>(reinterpret_cast<unsigned char*>(texture) + 0x78);
	const int width = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(texture) + 0x64);
	const int height = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(texture) + 0x68);
	if ((dstPixels == 0) || (width <= 0) || (height <= 0)) {
		return 0;
	}

	CMaterialSet* materialSet = ModelMaterialSet(model);
	FurMeshRaw* mesh = ModelMeshes(model);
	void* nodes = ModelNodes(model);
	if (materialSet == 0 || mesh == 0 || nodes == 0) {
		return 0;
	}

	FurMaterialSetRaw* materialSetRaw = reinterpret_cast<FurMaterialSetRaw*>(materialSet);
	if (materialSetRaw->m_materials.m_items == 0 || materialSetRaw->m_materials.m_numItems == 0) {
		return 0;
	}

	const unsigned short meshCount = ModelMeshCount(model);
	const int posQuant = ModelPosQuant(model) & 0xFF;
	const float cursorX = static_cast<float>(CharaU32(0x200C));
	const float cursorY = static_cast<float>(CharaU32(0x2010));
	float hitU = 0.0f;
	float hitV = 0.0f;
	float nearestDepth = 1000000.0f;
	bool hitFound = false;
	Vec hitViewPos;

	for (unsigned int meshIndex = 0; meshIndex < meshCount; meshIndex++, mesh++) {
		if (mesh->m_data == 0 || mesh->m_workPositions == 0 || mesh->m_data->m_uvs == 0) {
			continue;
		}
		if (((ModelMeshVisibleMask(model) >> meshIndex) & 1) == 0) {
			continue;
		}

		Mtx meshMtx;
		if (mesh->m_data->m_skinCount == 0) {
			PSMTXConcat(ModelDrawMtx(model),
			            reinterpret_cast<float(*)[4]>(reinterpret_cast<unsigned char*>(nodes) + mesh->m_data->m_nodeIndex * 0xC0 + 0x44),
			            meshMtx);
		} else {
			PSMTXCopy(ModelDrawMtx(model), meshMtx);
		}

		Mtx modelViewMtx;
		PSMTXConcat(reinterpret_cast<MtxPtr>(param_2), meshMtx, modelViewMtx);

		FurDisplayListRaw* displayList = mesh->m_data->m_displayLists;
		for (unsigned int displayIndex = 0; displayIndex < mesh->m_data->m_displayListCount; displayIndex++, displayList++) {
			if (displayList == 0 || displayList->m_data == 0 || displayList->m_size <= 0 ||
			    displayList->m_material >= materialSetRaw->m_materials.m_numItems) {
				continue;
			}

			FurMaterialRaw* material =
			    reinterpret_cast<FurMaterialRaw*>(materialSetRaw->m_materials.m_items[displayList->m_material]);
			if (material == 0 || material->m_furEnable == 0 || material->m_textures[0] == 0 ||
			    *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(material->m_textures[0]) + 0x60) != 5) {
				continue;
			}

			const unsigned char* cursor = reinterpret_cast<const unsigned char*>(displayList->m_data);
			int remaining = displayList->m_size;
			while (remaining > 0) {
				const unsigned char command = cursor[0];
				if ((command & 0xF8) == 0 || remaining < 3) {
					break;
				}

				const unsigned char primitive = command & 0xF8;
				const unsigned short count = *reinterpret_cast<const unsigned short*>(cursor + 1);
				cursor += 3;
				remaining -= 3;

				if (remaining < static_cast<int>(count) * 8) {
					break;
				}

				FurProjectedVertex prev2;
				FurProjectedVertex prev1;
				prev2.m_valid = false;
				prev1.m_valid = false;

				for (unsigned short vertexIndex = 0; vertexIndex < count; vertexIndex++) {
					const unsigned short* indices = reinterpret_cast<const unsigned short*>(cursor);
					FurProjectedVertex current;
					ProjectFurVertex(current, mesh, modelViewMtx, indices[0], indices[3], posQuant);

					if (primitive == 0x90) {
						if ((vertexIndex % 3) == 2) {
							const unsigned short* triIndices = reinterpret_cast<const unsigned short*>(cursor - 16);
							FurProjectedVertex a;
							FurProjectedVertex b;
							ProjectFurVertex(a, mesh, modelViewMtx, triIndices[0], triIndices[3], posQuant);
							ProjectFurVertex(b, mesh, modelViewMtx, triIndices[4], triIndices[7], posQuant);

							if (a.m_valid && b.m_valid && current.m_valid) {
								float w0;
								float w1;
								float w2;
								if (FurPointInTriangle(cursorX, cursorY, a, b, current, w0, w1, w2)) {
									Vec viewHit;
									float uvU;
									float uvV;
									FurInterpolateHit(viewHit, uvU, uvV, a, b, current, w0, w1, w2);
									const float depth = -viewHit.z;
									if (depth < nearestDepth) {
										nearestDepth = depth;
										hitViewPos = viewHit;
										hitU = uvU;
										hitV = uvV;
										hitFound = true;
									}
								}
							}
						}
					} else if (primitive == 0x98) {
						if (prev2.m_valid && prev1.m_valid && current.m_valid) {
							const bool odd = (vertexIndex & 1) != 0;
							const FurProjectedVertex& a = odd ? prev1 : prev2;
							const FurProjectedVertex& b = odd ? prev2 : prev1;
							float w0;
							float w1;
							float w2;
							if (FurPointInTriangle(cursorX, cursorY, a, b, current, w0, w1, w2)) {
								Vec viewHit;
								float uvU;
								float uvV;
								FurInterpolateHit(viewHit, uvU, uvV, a, b, current, w0, w1, w2);
								const float depth = -viewHit.z;
								if (depth < nearestDepth) {
									nearestDepth = depth;
									hitViewPos = viewHit;
									hitU = uvU;
									hitV = uvV;
									hitFound = true;
								}
							}
						}
						prev2 = prev1;
						prev1 = current;
					}

					cursor += 8;
					remaining -= 8;
				}
			}
		}
	}

	if (!hitFound) {
		return 0;
	}

	if (worldPos != 0) {
		*worldPos = hitViewPos;
		Mtx invViewMtx;
		PSMTXInverse(param_2, invViewMtx);
		PSMTXMultVec(invViewMtx, worldPos, worldPos);
	}

	if (doPaint == 0) {
		return 1;
	}

	if (hitU < 0.0f) {
		hitU = 0.0f;
	} else if (hitU > 1.0f) {
		hitU = 1.0f;
	}
	if (hitV < 0.0f) {
		hitV = 0.0f;
	} else if (hitV > 1.0f) {
		hitV = 1.0f;
	}

	brush(dstPixels, width, height, hitU, hitV, mode, brushColor, centerBefore, centerAfter);
	if (centerBefore != 0 && centerAfter != 0 && !MogColorChanged(*centerBefore, *centerAfter)) {
		return 0;
	}
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
extern "C" void DrawFur__Q26CChara6CModelFPA4_fi(void* model, Mtx viewMtx, int shadowPass)
{
	if ((ModelFlags10C(model) & 0x40) == 0) {
		return;
	}
	if ((shadowPass != 0) && ((ModelFlags10C(model) & 0x80) == 0)) {
		return;
	}

	CMaterialSet* materialSet = ModelMaterialSet(model);
	FurMeshRaw* mesh = ModelMeshes(model);
	void* nodes = ModelNodes(model);
	if (materialSet == 0 || mesh == 0 || nodes == 0) {
		return;
	}

	FurMaterialSetRaw* materialSetRaw = reinterpret_cast<FurMaterialSetRaw*>(materialSet);
	if (materialSetRaw->m_materials.m_items == 0 || materialSetRaw->m_materials.m_numItems == 0) {
		return;
	}

	if (gMogFurTexBuffer == 0) {
		makeFurTex__6CCharaFv();
	}
	if (gMogFurTexBuffer == 0) {
		return;
	}

	float furStep = ModelFurStep(model);
	if (furStep == 0.0f) {
		furStep = 1.0f;
	}
	float furLength = ModelFurLenScale(model);
	if (furLength <= 0.0f) {
		furLength = 1.0f;
	}
	const int furShade = static_cast<int>(255.0f * ModelFurCur(model));
	const GXColor furColor = CColor(static_cast<unsigned char>(furShade), static_cast<unsigned char>(furShade),
	                                static_cast<unsigned char>(furShade), 0xFF)
	                             .color;

	_GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
	GXSetZCompLoc((u8)0);
	_GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6, 1, 0, 7, 0);
	GXSetZMode((u8)1, (GXCompare)3, (u8)0);
	GXSetCullMode(GX_CULL_BACK);
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
	GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_S16, ModelNormQuant(model) & 0xFF);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 0x0C);
	GXSetNumTexGens(1);
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
	GXSetNumTevStages(1);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
	GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
	GXSetChanMatColor(GX_COLOR0A0, furColor);
	LightPcs.EnableLight(1, 1);
	LightPcs.SetAmbientAlpha(ModelLightAlpha(model));

	Mtx texMtx;
	PSMTXIdentity(texMtx);
	texMtx[0][0] = furStep;
	texMtx[1][1] = furStep;
	GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);

	const unsigned short meshCount = ModelMeshCount(model);
	const int posQuant = ModelPosQuant(model) & 0xFF;
	const int normQuant = ModelNormQuant(model) & 0xFF;

	for (unsigned int meshIndex = 0; meshIndex < meshCount; meshIndex++, mesh++) {
		if (mesh->m_data == 0 || mesh->m_workPositions == 0 || mesh->m_workNormals == 0) {
			continue;
		}
		if (((ModelMeshVisibleMask(model) >> meshIndex) & 1) == 0) {
			continue;
		}

		Mtx meshMtx;
		if (mesh->m_data->m_skinCount == 0) {
			PSMTXConcat(ModelDrawMtx(model),
			            reinterpret_cast<float(*)[4]>(reinterpret_cast<unsigned char*>(nodes) + mesh->m_data->m_nodeIndex * 0xC0 + 0x44),
			            meshMtx);
		} else {
			PSMTXCopy(ModelDrawMtx(model), meshMtx);
		}

		Mtx modelViewMtx;
		PSMTXConcat(viewMtx, meshMtx, modelViewMtx);
		GXLoadPosMtxImm(modelViewMtx, GX_PNMTX0);

		Mtx normalMtx;
		PSMTXCopy(modelViewMtx, normalMtx);
		normalMtx[0][3] = 0.0f;
		normalMtx[1][3] = 0.0f;
		normalMtx[2][3] = 0.0f;
		GXLoadNrmMtxImm(normalMtx, GX_PNMTX0);
		GXSetArray(GX_VA_NRM, mesh->m_workNormals, 6);
		GXSetArray(GX_VA_TEX0, mesh->m_data->m_uvs, 4);

		FurDisplayListRaw* displayList = mesh->m_data->m_displayLists;
		for (unsigned int displayIndex = 0; displayIndex < mesh->m_data->m_displayListCount; displayIndex++, displayList++) {
			if (displayList->m_material >= materialSetRaw->m_materials.m_numItems) {
				continue;
			}

			FurMaterialRaw* material =
			    reinterpret_cast<FurMaterialRaw*>(materialSetRaw->m_materials.m_items[displayList->m_material]);
			if (material == 0 || material->m_furEnable == 0) {
				continue;
			}

			for (unsigned int layer = 0; layer < 8; layer++) {
				GXTexObj texObj;
				void* texData = reinterpret_cast<unsigned char*>(gMogFurTexBuffer) + (layer * 0x4000);
				GXInitTexObj(&texObj, texData, 0x80, 0x80, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, GX_FALSE);
				GXLoadTexObj(&texObj, GX_TEXMAP0);

				const float shellOffset = furLength * (static_cast<float>(layer) * 0.125f);
				DrawFurDisplayListShell(mesh, displayList, shellOffset, posQuant, normQuant);
			}
		}
	}

	LightPcs.EnableLight(1, 0);
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
    if (gMogFurTexBuffer != 0) {
        Memory.Free(gMogFurTexBuffer);
        gMogFurTexBuffer = 0;
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
	if (gMogFurTexBuffer == 0) {
		gMogFurTexBuffer = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
			&Memory, 0x20000, 0, const_cast<char*>(s_chara_fur_cpp_801db72c), 0xE9, 0);
	}
	if (gMogFurTexBuffer == 0) {
		return;
	}

	unsigned short* tex = reinterpret_cast<unsigned short*>(gMogFurTexBuffer);
	CHairSet hairSet[0x20];
	unsigned int rng = 0x1234ABCD;

	for (int i = 0; i < 0x20; i++) {
		FurInitHairSet(hairSet[i], rng);
	}

	for (int layer = 0; layer < 8; layer++) {
		unsigned short* layerTex = tex + (layer * 0x4000 / 2);
		float layerT = static_cast<float>(layer) / 7.0f;
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
				int tone = 2 + layer + (edge >> 3) + (noise >> 3);
				int a = static_cast<int>((edge >> 4) + layerT * 2.0f);
				layerTex[(y * 0x80) + x] = PackFurTexel(tone, tone, tone, a);
			}
		}

		for (int i = 0; i < 0x20; i++) {
			FurPlotHair(layerTex, hairSet[i], layer, rng);
		}
	}

	DCFlushRange(gMogFurTexBuffer, 0x20000);
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
{
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

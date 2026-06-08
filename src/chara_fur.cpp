#include "ffcc/chara_fur.h"
#include "global.h"
#include "ffcc/chara.h"
#include "ffcc/charaobj.h"
#include "ffcc/cflat_data.h"
#include "ffcc/math.h"
#include "ffcc/mesmenu.h"
#include "ffcc/gobject.h"
#include "ffcc/game.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/linkage.h"
#include "ffcc/materialman.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_chara.h"
#include "ffcc/p_menu.h"
#include "ffcc/p_light.h"
#include "ffcc/p_tina.h"
#include "ffcc/partMng.h"
#include "ffcc/pad.h"
#include "ffcc/ptrarray_fwd.h"
#include "ffcc/render_buffers.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include "ffcc/textureman.h"
#include "ffcc/cflat_runtime2.h"

#include <stddef.h>
#include <string.h>

extern const float kPppLensFlareZero = 0.0f;
extern const float kPppLensFlareAlphaScale = 0.0078125f;
extern const float kPppLensFlareNegate = -1.0f;
extern const float kPppLensFlareZScale = 16777215.0f;
extern const double kPppLensFlareDoubleMagic = 4503599627370496.0;
extern const float kPppColumScreenCenterX = 320.0f;
extern const float kPppColumScreenCenterY = 224.0f;
extern const float kPppColumCameraZOffset = -0.5f;
extern const float kPppColumZero = 0.0f;
extern const double kPppColumSqrtHalf = 0.5;
extern const double kPppColumSqrtThree = 3.0;
extern const double kPppColumZeroD = 0.0;
extern const float kPppColumNormalizeEpsilon = 0.000001f;
extern const float kPppColumOne = 1.0f;
extern const float kPppColumSegmentScale = 2.0f;
extern const double kYmEnvRadToDeg;
extern const float kYmEnvDefaultScale;
extern "C" {
double atan2(double, double);
double sqrt(double);
}
extern const unsigned long long g_chara_fur_1;
extern const unsigned long long g_chara_fur_2;

STATIC_ASSERT(sizeof(CChara::MogFurState) == 0x2054);
STATIC_ASSERT(offsetof(CChara::MogFurState, m_dirty) == 0x2000);
STATIC_ASSERT(offsetof(CChara::MogFurState, m_cursorX) == 0x2008);
STATIC_ASSERT(offsetof(CChara::MogFurState, m_cursorY) == 0x200C);
STATIC_ASSERT(offsetof(CChara::MogFurState, m_timestamp) == 0x2010);
STATIC_ASSERT(offsetof(CChara::MogFurState, m_score) == 0x2014);
STATIC_ASSERT(offsetof(CChara::MogFurState, m_alphaScore) == 0x2050);

class CMaterial;

extern "C" char* sMogRadarTypeLabels[];
extern "C" char sMogRadarDebugFormatBlock[];
extern "C" char sMogFurTextureName[8];
extern "C" {
extern unsigned char m_mogWork[0x2C];
void* DAT_8032EDEC;
void* gMogFurTexBuffer;
}
extern float kCharaFurDepthZero;
extern float kCharaFurDepthScaleBase;
extern float kCharaFurColorComponentScale;
extern float kCharaFurAlphaComponentScale;
extern float kCharaFurNoHitDepth;
extern float kCharaFurScreenCenterY;
extern float kCharaFurScreenCenterX;
extern float kCharaFurTriangleVertexCount;
extern float kCharaFurPickRayFarZ;
extern float kCharaFurWeightScale;
extern float kCharaFurViewDepthThreshold;
extern float kCharaFurShadeScale;
extern float kCharaFurShadowRange;
extern float kCharaFurShadowFade;
extern float FLOAT_8033115C;
extern float FLOAT_80331160;
extern float FLOAT_80331164;
extern float FLOAT_80331168;
extern float FLOAT_8033116C;
extern float kYmEnvQuarter;
extern double kYmEnvSignedDoubleMagic;
extern double kPppEmissionDoubleBias;

namespace {

typedef CChara::CMesh::CDisplayList FurDisplayListRaw;
typedef CChara::CMesh::CRefData FurMeshRefRaw;
typedef CChara::CMesh FurMeshRaw;

struct FurTexCoordRaw
{
    short s;
    short t;
};

struct FurProjectedVertex
{
    unsigned char m_valid;
    Vec m_viewPos;
    float m_clipX;
    float m_clipY;
    float m_clipZ;
    float m_clipW;
    float m_screenX;
    float m_screenY;
    float m_u;
    float m_v;
};

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
};

static inline MogWorkRaw& MogWork()
{
    return *reinterpret_cast<MogWorkRaw*>(m_mogWork);
}

static inline CMaterialSet* ModelMaterialSet(CChara::CModel* model)
{
    return model->m_data->m_materialSet;
}

static inline FurMeshRaw* ModelMeshes(CChara::CModel* model)
{
    return model->m_meshes;
}

static inline CChara::CNode* ModelNodes(CChara::CModel* model)
{
    return model->m_nodes;
}

static inline unsigned short ModelMeshCount(CChara::CModel* model)
{
    return model->m_data->m_meshCount;
}

static inline unsigned int ModelMeshVisibleMask(CChara::CModel* model)
{
    return model->m_meshVisibleMask;
}

static inline float (*ModelDrawMtx(CChara::CModel* model))[4]
{
    return model->m_matrix;
}

static inline int ModelPosQuant(CChara::CModel* model)
{
    return model->m_data->m_posQuant;
}

static inline int ModelNormQuant(CChara::CModel* model)
{
    return model->m_data->m_normQuant;
}

static inline float ModelLightAlpha(CChara::CModel* model)
{
    return model->m_lightAlpha;
}

static inline float ModelFurLenScale(CChara::CModel* model)
{
    return model->m_furLenScale;
}

static inline float ModelFurStep(CChara::CModel* model)
{
    return model->m_furStep;
}

static inline float ModelFurCur(CChara::CModel* model)
{
    return model->m_furCur;
}

static inline unsigned char ModelFlags10C(CChara::CModel* model)
{
    return model->m_flags10C;
}

static inline float QuantizedToFloat(short value, int frac)
{
    if (frac <= 0) {
        return static_cast<float>(value);
    }
    return static_cast<float>(value) / static_cast<float>(1 << frac);
}

static inline void LoadFurPosition(register Vec* out, register const S16Vec* in)
{
	register float xy;
	register float z;

	asm {
		psq_l xy, 0(in), 0, 5
		psq_l z, 4(in), 1, 5
		psq_st xy, 0(out), 0, 0
		psq_st z, 8(out), 1, 0
	}
}

static inline void LoadFurTexCoord(register float* out, register const FurTexCoordRaw* in)
{
	register float st;

	asm {
		psq_l st, 0(in), 0, 7
		psq_st st, 0(out), 0, 0
	}
}

static inline bool ProjectFurVertex(FurProjectedVertex& out, const FurMeshRaw* mesh, const Mtx modelViewMtx, Mtx44 screenMtx,
                                    unsigned short posIdx, unsigned short uvIdx, int posQuant)
{
    static_cast<void>(posQuant);
    out.m_valid = 0;

    const S16Vec& pos = mesh->m_workPositions[posIdx];
    const FurTexCoordRaw& uv = reinterpret_cast<FurTexCoordRaw*>(mesh->m_data->m_uvs)[uvIdx];
    Vec localPos;
    LoadFurPosition(&localPos, &pos);
    PSMTXMultVec(modelViewMtx, &localPos, &out.m_viewPos);

    if (out.m_viewPos.z >= 0.0f) {
        return false;
    }

    Vec4d clipPos;
    Math.MTX44MultVec4(screenMtx, &out.m_viewPos, &clipPos);

    const float invW = kCharaFurDepthScaleBase / clipPos.w;
    out.m_clipX = clipPos.x;
    out.m_clipY = clipPos.y;
    out.m_clipZ = clipPos.z;
    out.m_clipW = clipPos.w;
    out.m_screenX = clipPos.x * invW * kCharaFurScreenCenterX + kCharaFurScreenCenterX;
    out.m_screenY = kCharaFurScreenCenterY - clipPos.y * invW * kCharaFurScreenCenterY;
    LoadFurTexCoord(&out.m_u, &uv);
    out.m_valid = 0x80;
    return true;
}

static inline bool FurPointInTriangle(float px, float py, const FurProjectedVertex& a, const FurProjectedVertex& b,
                                      const FurProjectedVertex& c)
{
    const float edge0 = (py - a.m_screenY) * (b.m_screenX - a.m_screenX) -
                        (px - a.m_screenX) * (b.m_screenY - a.m_screenY);
    if (edge0 > 0.0f) {
        return false;
    }
    const float edge1 = (py - b.m_screenY) * (c.m_screenX - b.m_screenX) -
                        (px - b.m_screenX) * (c.m_screenY - b.m_screenY);
    if (edge1 > 0.0f) {
        return false;
    }
    const float edge2 = (py - c.m_screenY) * (a.m_screenX - c.m_screenX) -
                        (px - c.m_screenX) * (a.m_screenY - c.m_screenY);
    return edge2 <= 0.0f;
}

static inline float FurHitDepth(const FurProjectedVertex& a, const FurProjectedVertex& b, const FurProjectedVertex& c)
{
    return (a.m_clipW + b.m_clipW + c.m_clipW) / kCharaFurTriangleVertexCount;
}

static inline void FurInterpolateHit(Vec& outViewPos, float& outU, float& outV, Mtx44 screenMtx, float cursorX,
                                     float cursorY, const FurProjectedVertex& a, const FurProjectedVertex& b,
                                     const FurProjectedVertex& c)
{
    Mtx44 invScreenMtx;
    PSMTX44Copy(screenMtx, invScreenMtx);
    C_MTX44Inverse(invScreenMtx, invScreenMtx);

    CVector rayStart((cursorX - kCharaFurScreenCenterX) / kCharaFurScreenCenterX,
                     -(cursorY - kCharaFurScreenCenterY) / kCharaFurScreenCenterY, kCharaFurDepthZero);
    CVector rayEnd(rayStart.x, rayStart.y, kCharaFurPickRayFarZ);

    PSMTX44MultVec(invScreenMtx, reinterpret_cast<Vec*>(&rayStart), reinterpret_cast<Vec*>(&rayStart));
    PSMTX44MultVec(invScreenMtx, reinterpret_cast<Vec*>(&rayEnd), reinterpret_cast<Vec*>(&rayEnd));

    CVector ray;
    PSVECSubtract(reinterpret_cast<Vec*>(&rayEnd), reinterpret_cast<Vec*>(&rayStart), reinterpret_cast<Vec*>(&ray));

    CVector normalA;
    CVector normalB;
    CVector normal;
    PSVECCrossProduct(&b.m_viewPos, &a.m_viewPos, reinterpret_cast<Vec*>(&normalA));
    PSVECCrossProduct(&c.m_viewPos, &a.m_viewPos, reinterpret_cast<Vec*>(&normalB));
    PSVECCrossProduct(reinterpret_cast<Vec*>(&normalA), reinterpret_cast<Vec*>(&normalB), reinterpret_cast<Vec*>(&normal));
    normal.Normalize();

    CVector vertA(a.m_viewPos);
    CVector planeDelta;
    PSVECSubtract(reinterpret_cast<Vec*>(&vertA), reinterpret_cast<Vec*>(&rayStart), reinterpret_cast<Vec*>(&planeDelta));
    CVector scaledRay;
    const float rayDot = PSVECDotProduct(reinterpret_cast<Vec*>(&normal), reinterpret_cast<Vec*>(&ray));
    const float planeDot = PSVECDotProduct(reinterpret_cast<Vec*>(&normal), reinterpret_cast<Vec*>(&planeDelta));
    PSVECScale(reinterpret_cast<Vec*>(&ray), reinterpret_cast<Vec*>(&scaledRay), planeDot / rayDot);
    PSVECAdd(reinterpret_cast<Vec*>(&rayStart), reinterpret_cast<Vec*>(&scaledRay), &outViewPos);

    CVector hitToA;
    CVector hitToB;
    CVector hitToC;
    PSVECSubtract(reinterpret_cast<Vec*>(&vertA), &outViewPos, reinterpret_cast<Vec*>(&hitToA));
    CVector vertB(b.m_viewPos);
    PSVECSubtract(reinterpret_cast<Vec*>(&vertB), &outViewPos, reinterpret_cast<Vec*>(&hitToB));
    CVector vertC(c.m_viewPos);
    PSVECSubtract(reinterpret_cast<Vec*>(&vertC), &outViewPos, reinterpret_cast<Vec*>(&hitToC));

    CVector areaAB;
    CVector areaBC;
    CVector areaCA;
    PSVECCrossProduct(reinterpret_cast<Vec*>(&hitToA), reinterpret_cast<Vec*>(&hitToB), reinterpret_cast<Vec*>(&areaAB));
    PSVECCrossProduct(reinterpret_cast<Vec*>(&hitToB), reinterpret_cast<Vec*>(&hitToC), reinterpret_cast<Vec*>(&areaBC));
    PSVECCrossProduct(reinterpret_cast<Vec*>(&hitToC), reinterpret_cast<Vec*>(&hitToA), reinterpret_cast<Vec*>(&areaCA));

    CVector weights;
    weights.x = PSVECMag(reinterpret_cast<Vec*>(&areaBC));
    weights.y = PSVECMag(reinterpret_cast<Vec*>(&areaCA));
    weights.z = PSVECMag(reinterpret_cast<Vec*>(&areaAB));
    PSVECScale(reinterpret_cast<Vec*>(&weights), reinterpret_cast<Vec*>(&weights), kCharaFurWeightScale);
    PSVECScale(reinterpret_cast<Vec*>(&weights), reinterpret_cast<Vec*>(&weights),
               kCharaFurDepthScaleBase / (weights.x + weights.y + weights.z));

    outU = a.m_u * weights.x + b.m_u * weights.y + c.m_u * weights.z;
    outV = a.m_v * weights.x + b.m_v * weights.y + c.m_v * weights.z;
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
	const int frameCounter = static_cast<int>(System.m_frameCounter);

	if (MogFur().m_timestamp + 0x1A5E0 < frameCounter) {
		MogFur().m_timestamp = frameCounter;
		if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
			System.Printf("");
		}
		if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
			System.Printf(sMogRadarDebugFormatBlock);
		}
		if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
			System.Printf("");
		}
	}

	MogFurState& fur = MogFur();
	unsigned short* const texels = fur.m_texels;
	memset(fur.m_score, 0, 0x40);

	for (int y = 0; y < 0x40; y++) {
		for (int x = 0; x < 0x40; x++) {
			int light;
			int r;
			int g;
			int b;
			int a;
			int newA;
			unsigned int tileIndex = ((x % 4) + ((y % 4) * 4) + (x / 4) * 0x10 + (y / 4) * 0x100) * 2;
			unsigned short packed = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(texels) + tileIndex);

			a = (packed >> 12) & 7;
			light = 7 - a;
			r = light + ((packed >> 8) & 0xF) + 4;
			g = light + ((packed >> 4) & 0xF) + 4;
			b = light + (packed & 0xF) + 4;

			int clampedR = 0xF;
			if (r < 0xF) {
				clampedR = r;
			}
			r = clampedR;
			int clampedG = 0xF;
			if (g < 0xF) {
				clampedG = g;
			}
			g = clampedG;
			int clampedB = 0xF;
			if (b < 0xF) {
				clampedB = b;
			}
			b = clampedB;

			newA = static_cast<unsigned int>(a + 2);
			unsigned int clampedA = 7;
			if (newA < 7) {
				clampedA = newA;
			}
			newA = clampedA;

			*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(texels) + tileIndex) =
			    static_cast<unsigned short>((newA << 12) | (r << 8) | (g << 4) | b);
		}
	}

	CalcMogScore();
}

static int FurColorMatch(CColor src, CColor ref)
{
	int dr = static_cast<int>(src.color.r) - static_cast<int>(ref.color.r);
	if (dr < 0) {
		dr = -dr;
	}
	dr += 7 - static_cast<int>(src.color.a);

	int dg = static_cast<int>(src.color.g) - static_cast<int>(ref.color.g);
	if (dg < 0) {
		dg = -dg;
	}
	dg += 7 - static_cast<int>(src.color.a);

	int db = static_cast<int>(src.color.b) - static_cast<int>(ref.color.b);
	if (db < 0) {
		db = -db;
	}
	db += 7 - static_cast<int>(src.color.a);

	int hits = (dr < 5) + (dg < 5) + (db < 5);
	return static_cast<unsigned int>(__cntlzw(3 - hits)) >> 5;
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
	MogFurState& fur = MogFur();
	unsigned short* texels = fur.m_texels;
	int bitCount = 0;
	int lineCount = 0;
	int circleCount = 0;

	memset(fur.m_score, 0, 0x40);

	for (int y = 0; y < 0x40; y++) {
		for (int x = 0; x < 0x40; x++) {
			const int dx = x - 0x20;
			const int dy = y - 0x20;
			const int dist = static_cast<int>(sqrt(static_cast<double>(dx * dx + dy * dy)));

			if (dist >= 0x40) {
				continue;
			}

			const int tileIndex = ((x % 4) + ((y % 4) * 4) + (x / 4) * 0x10 + (y / 4) * 0x100) * 2;

			const unsigned short packed = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(texels) + tileIndex);
			const int a = (packed >> 12) & 7;
			const int r = (packed >> 8) & 0xF;
			const int g = (packed >> 4) & 0xF;
			const int b = packed & 0xF;
			CColor srcColor(static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b),
			                static_cast<unsigned char>(a));

			int colorHit[3];
			colorHit[0] = FurColorMatch(srcColor, CColor(0xF, 4, 4, 2));
			colorHit[1] = FurColorMatch(srcColor, CColor(4, 0xF, 4, 2));
			colorHit[2] = FurColorMatch(srcColor, CColor(4, 8, 0xF, 2));
			fur.m_alphaScore += a;

			const int ring = dist % 12;
			int angle = static_cast<int>(kYmEnvRadToDeg * atan2(static_cast<double>(dx), static_cast<double>(dy))) + 0x168;
			angle %= 0x2D;

			for (int i = 0; i < 3; i++) {
				if (ring >= i * 4 && ring < (i + 1) * 4) {
					circleCount++;
					fur.m_circleScore[i] += colorHit[i];
				} else if (angle >= i * 0xF && angle < (i + 1) * 0xF) {
					lineCount++;
					fur.m_lineScore[i] += colorHit[i];
				} else {
					bitCount++;
					fur.m_bitScore[i] += colorHit[i];
				}
			}
		}
	}

	fur.m_alphaScore = (fur.m_alphaScore * 100) / 0x7000;

	bitCount /= 3;
	fur.m_bitScore[0] = (fur.m_bitScore[0] * 100) / bitCount;
	circleCount /= 3;
	fur.m_circleScore[0] = (fur.m_circleScore[0] * 100) / circleCount;
	lineCount /= 3;
	fur.m_lineScore[0] = (fur.m_lineScore[0] * 100) / lineCount;
	fur.m_bitScore[1] = (fur.m_bitScore[1] * 100) / bitCount;
	fur.m_circleScore[1] = (fur.m_circleScore[1] * 100) / circleCount;
	fur.m_lineScore[1] = (fur.m_lineScore[1] * 100) / lineCount;
	fur.m_bitScore[2] = (fur.m_bitScore[2] * 100) / bitCount;
	fur.m_circleScore[2] = (fur.m_circleScore[2] * 100) / circleCount;
	fur.m_lineScore[2] = (fur.m_lineScore[2] * 100) / lineCount;

	for (int i = 0; i < 3; i++) {
		int* scorePtr = &fur.m_score[i];
		const int bit = fur.m_bitScore[i];
		const int line = fur.m_lineScore[i];
		const int circle = fur.m_circleScore[i];
		int level;

		*scorePtr = (line + circle * 2 - bit * 2) / 3;
		if (*scorePtr < 0) {
			*scorePtr = 0;
		} else if (*scorePtr > 100) {
			*scorePtr = 100;
		}

		level = (100 - *scorePtr) / 5;
		if (level < 5) {
			level = 5;
		} else if (level > 0xF) {
			level = 0xF;
		}
		fur.m_radarLevel[i] = level;
	}

	{
		const int b0 = fur.m_score[0];
		const int b1 = fur.m_score[1];
		const int b2 = fur.m_score[2];

		if (b0 > 2 && kYmEnvDefaultScale * static_cast<float>(b1 + b2) < static_cast<float>(b0)) {
			Game.m_gameWork.m_mogScoreRadarType = 1;
		} else if (b1 > 2 && kYmEnvDefaultScale * static_cast<float>(b0 + b2) < static_cast<float>(b1)) {
			Game.m_gameWork.m_mogScoreRadarType = 2;
		} else if (b2 > 2 && kYmEnvDefaultScale * static_cast<float>(b0 + b1) < static_cast<float>(b2)) {
			Game.m_gameWork.m_mogScoreRadarType = 3;
		} else {
			Game.m_gameWork.m_mogScoreRadarType = 0;
		}
	}

	{
		char** radarLabel = reinterpret_cast<char**>(sMogRadarTypeLabels);
		Graphic.Printf(
		    5,
		    0xB,
		    sMogRadarDebugFormatBlock + 0x18,
		    fur.m_radarLevel[0],
		    fur.m_radarLevel[1],
		    fur.m_radarLevel[2],
		    fur.m_alphaScore,
		    fur.m_score[0],
		    fur.m_score[1],
		    fur.m_score[2],
		    fur.m_bitScore[0],
		    fur.m_bitScore[1],
		    fur.m_bitScore[2]);

		Graphic.Printf(
		    5,
		    0xC,
		    sMogRadarDebugFormatBlock + 0x4C,
		    fur.m_lineScore[0],
		    fur.m_lineScore[1],
		    fur.m_lineScore[2],
		    fur.m_circleScore[0],
		    fur.m_circleScore[1],
		    fur.m_circleScore[2],
		    radarLabel[Game.m_gameWork.m_mogScoreRadarType]);
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
		memset(m_mogWork, 0, sizeof(MogWorkRaw));
		MogFur().m_cursorX = 0x140;
		MogFur().m_cursorY = 0xE0;
		MogFur().m_dirty = 0;
		return;
	}

	int& mogSoundHandle = MogWork().m_loopSeHandle;
	if (mogSoundHandle != 0) {
		Sound.StopSe(mogSoundHandle);
		mogSoundHandle = 0;
	}
}

extern "C" const char s_chara_fur_cpp[] = "chara_fur.cpp";

extern "C" {
unsigned char m_mogWork[0x2C];
}
static unsigned int s_mogFurRand;
static float s_mogFurMaxY;

static inline unsigned int FurRandNext()
{
	s_mogFurRand = s_mogFurRand * 0x41C64E6D + 0x3039;
	return (s_mogFurRand >> 16) % 32767;
}

static inline float FurRandScale()
{
	return kCharaFurDepthScaleBase * (FLOAT_80331164 * static_cast<float>(FurRandNext()) + kCharaFurViewDepthThreshold);
}

static inline CColor FurNoiseColor(const CColor& base, const CColor& noise, float scale)
{
	return CColor(
	    static_cast<unsigned char>(base.color.r + static_cast<int>(noise.color.r * scale)),
	    static_cast<unsigned char>(base.color.g + static_cast<int>(noise.color.g * scale)),
	    static_cast<unsigned char>(base.color.b + static_cast<int>(noise.color.b * scale)),
	    static_cast<unsigned char>(base.color.a + static_cast<int>(noise.color.a * scale)));
}

void brush(unsigned short*, int, int, float, float, int, _GXColor, _GXColor*, _GXColor*);

namespace {

static inline bool HasDebugPadOverride()
{
	return (Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1);
}

static inline unsigned short MogHeldButtons()
{
	if (HasDebugPadOverride()) {
		return 0;
	}
	return static_cast<unsigned short>(Pad.GetPadInputs()[0].button[0]);
}

static inline unsigned short MogTriggerButtons()
{
	if (HasDebugPadOverride()) {
		return 0;
	}
	return static_cast<unsigned short>(Pad.GetPadInputs()[0].buttonDown[0]);
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
	return Game.m_gameWork.m_mogScoreRadarType;
}

static inline _GXColor MogBrushColor(unsigned char radarType)
{
	switch (radarType) {
	case 0:
		return CColor(0xF, 4, 4, 2).color;
	case 1:
		return CColor(4, 8, 0xF, 2).color;
	case 2:
		return CColor(4, 0xF, 4, 2).color;
	case 3:
		return CColor(0xF, 0xF, 0xF, 4).color;
	case 4:
		return CColor(0, 0, 0, 2).color;
	default:
		return CColor(0xF, 4, 4, 2).color;
	}
}

static inline void StopMogLoopSe(MogWorkRaw& work)
{
	if (work.m_loopSeHandle != 0) {
		Sound.StopSe(work.m_loopSeHandle);
		work.m_loopSeHandle = 0;
	}
}

static inline CTexture* FindMogFurTexture(CChara::CModel* model)
{
	CTextureSet* textureSet = model->m_texSet;

	unsigned int textureIdx = static_cast<unsigned int>(textureSet->Find(&sMogFurTextureName[0]));
	return textureSet->GetTexture(textureIdx);
}

static inline void CopyMogTextureFromChara(CChara::CModel* model)
{
	CTexture* texture = FindMogFurTexture(model);
	if (texture == 0) {
		return;
	}

	void* dstBuffer = texture->m_imageData;
	const int texelCountBytes = texture->m_width * texture->m_height * 2;

	Graphic._WaitDrawDone(const_cast<char*>(s_chara_fur_cpp), 0x506);
	DCInvalidateRange(dstBuffer, texelCountBytes);
	memcpy(dstBuffer, Chara.MogFur().m_texels, 0x2000);
	DCFlushRange(dstBuffer, texelCountBytes);
	GXInvalidateTexAll();
}

static void CopyMogTextureToChara(CChara::CModel* model)
{
	CTexture* texture = FindMogFurTexture(model);
	if (texture == 0) {
		return;
	}

	void* srcBuffer = texture->m_imageData;
	const int texelCountBytes = texture->m_width * texture->m_height * 2;

	Graphic._WaitDrawDone(const_cast<char*>(s_chara_fur_cpp), 0x506);
	memcpy(Chara.MogFur().m_texels, srcBuffer, 0x2000);
	DCFlushRange(srcBuffer, texelCountBytes);
	GXInvalidateTexAll();
}

static void OpenMogHintMessage(int messageId)
{
	if (messageId < 0) {
		return;
	}

	CMesMenu* mesMenu = *reinterpret_cast<CMesMenu**>(reinterpret_cast<unsigned char*>(&MenuPcs) + 0x288);
	if (mesMenu == 0) {
		return;
	}

	if (mesMenu->IsActiveMessage()) {
		return;
	}

	CFlatData* flatData = reinterpret_cast<CFlatData*>(reinterpret_cast<unsigned char*>(&Game) + 0xCC38 + sizeof(CFlatData));
	char** mesPtr = reinterpret_cast<char**>(reinterpret_cast<unsigned char*>(flatData) + 0xD4);
	mesMenu->Open(mesPtr[messageId + 8], 0x160, 0x20, 0x220, 0, -1, -1);
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
void CChara::InitFurTexBuffer()
{
	MogFurState& fur = MogFur();
	int rowCount = 0;
	int row = 0;
	do {
		unsigned int inner = 0;
		int byteOffset = row << 1;
		int count = 8;
		do {
			unsigned short* texels = Chara.MogFur().m_texels;
			int idxBase = inner + row;
			*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(texels) + byteOffset) = 0x7FFF;
			byteOffset += 0x10;
			texels[idxBase + 1] = 0x7FFF;
			texels[idxBase + 2] = 0x7FFF;
			texels[idxBase + 3] = 0x7FFF;
			texels[idxBase + 4] = 0x7FFF;
			texels[idxBase + 5] = 0x7FFF;
			texels[idxBase + 6] = 0x7FFF;
			texels[idxBase + 7] = 0x7FFF;
			inner += 8;
			count--;
		} while (count != 0);
		rowCount++;
		row += 0x40;
	} while (rowCount < 0x40);

	fur.m_dirty = 0;
	Chara.MogFur().m_timestamp = System.m_frameCounter;
	memset(fur.m_score, 0, 0x40);
	CalcMogScore();
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
void CChara::SaveFurTexBuffer(unsigned short* outTexels)
{
	memcpy(outTexels, Chara.MogFur().m_texels, 0x2000);
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
void CChara::LoadFurTexBuffer(unsigned short* inTexels)
{
	memcpy(Chara.MogFur().m_texels, inTexels, 0x2000);
	CalcMogScore();
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
	CTextureSet* textureSet = m_texSet;
	unsigned int textureIdx = static_cast<unsigned int>(textureSet->Find(&sMogFurTextureName[0]));
	CTexture* texture = textureSet->GetTexture(textureIdx);

	if ((texture != 0) && (texture->m_format == 4)) {
		texture->m_format = 5;
		Graphic._WaitDrawDone(const_cast<char*>(s_chara_fur_cpp), 0x506);

		textureSet = m_texSet;
		textureIdx = static_cast<unsigned int>(textureSet->Find(&sMogFurTextureName[0]));
		CTexture* textureData = textureSet->GetTexture(textureIdx);
		if (textureData != 0) {
			void* dstBuffer = textureData->m_imageData;
			int texelCountBytes = textureData->m_width * textureData->m_height * 2;

			DCInvalidateRange(dstBuffer, texelCountBytes);
			memcpy(dstBuffer, Chara.MogFur().m_texels, 0x2000);
			DCFlushRange(dstBuffer, texelCountBytes);
			GXInvalidateTexAll();
		}

		texture->InitTexObj();
		m_flagsA0 = static_cast<unsigned char>(__rlwimi(m_flagsA0, 1, 6, 25, 25));
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
void CChara::CModel::MogFurFrame(CGObject* gObject)
{
	MogWorkRaw& work = MogWork();
	const short heldButtons = MogHeldButtons();
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
		messageId = 0;
		work.m_prevScoreA = Chara.MogFur().m_score[0];
		work.m_prevScoreB = Chara.MogFur().m_score[1];
		work.m_prevScoreC = Chara.MogFur().m_score[2];
	}

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
	} else if (work.m_state == 1) {
		unsigned char* objectBytes = reinterpret_cast<unsigned char*>(gObject);
		if (gObject->m_currentAnimSlot == static_cast<char>(objectBytes[0xD4])) {
			if (gObject->IsLoopAnim(1) != 0) {
				gObject->PlayAnim(0x38, 1, 0, -1, -1, 0);
			}
		} else if (gObject->m_currentAnimSlot == static_cast<char>(objectBytes[0xD5])) {
			if ((rotateButtons & 4) != 0) {
				gObject->PlayAnim(0x39, 1, 0, -1, -1, 0);
			}
		} else if (gObject->IsLoopAnim(1) != 0) {
			gObject->CancelAnim(1);
			work.m_state = 0;
		}
	}

	const float cursorStep = 0.1f;
	const unsigned int cursorX = static_cast<int>(static_cast<float>(static_cast<int>(Chara.MogFur().m_cursorX)) +
	                                     static_cast<float>(MogPadInt(36)) * cursorStep);
	const int cursorY = static_cast<int>(static_cast<float>(static_cast<int>(Chara.MogFur().m_cursorY)) -
	                                     static_cast<float>(MogPadInt(40)) * cursorStep);

	if (cursorX < 0) {
		Chara.MogFur().m_cursorX = 0;
	} else if (cursorX > 0x280) {
		Chara.MogFur().m_cursorX = 0x280;
	} else {
		Chara.MogFur().m_cursorX = static_cast<unsigned int>(cursorX);
	}
	if (cursorY < 0) {
		Chara.MogFur().m_cursorY = 0;
	} else if (cursorY > 0x1C0) {
		Chara.MogFur().m_cursorY = 0x1C0;
	} else {
		Chara.MogFur().m_cursorY = static_cast<unsigned int>(cursorY);
	}

	Mtx cameraMtx;
	PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);

	if ((heldButtons & 0x100) != 0) {
		const signed char radarType = MogRadarType();
		if (Chara.MogFur().m_prevRadarType != radarType) {
			Chara.MogFur().m_prevRadarType = radarType;
			work.m_pickTicks = 0;
			Sound.StopSe(work.m_loopSeHandle);
			work.m_loopSeHandle = 0;
		}
		const _GXColor brushColor = MogBrushColor(radarType);
		const int eraseMode = (radarType == 4) ? 1 : 0;
		const int doPaint = (radarType == 3 || radarType == 4) ? (((System.m_frameCounter & 3U) == 0) ? 1 : 0) : 1;
		_GXColor centerBefore = CColor(0xF, 0xF, 0xF, 0).color;
		_GXColor centerAfter = centerBefore;
		Vec worldPos;

		CopyMogTextureFromChara(this);
		int pickResult = PickFur(cameraMtx, brushColor, doPaint, eraseMode, &centerBefore, &centerAfter, &worldPos);
		CopyMogTextureToChara(this);
		Chara.CalcMogScore();

		if (pickResult >= 0) {
			work.m_pickTicks++;

			if (Chara.MogFur().m_score[0] >= work.m_prevScoreA + 5) {
				work.m_prevScoreA = Chara.MogFur().m_score[0];
				messageId = 1;
			} else if (Chara.MogFur().m_score[0] < work.m_prevScoreA - 5) {
				work.m_prevScoreA = Chara.MogFur().m_score[0];
				messageId = 6;
			}
			if (Chara.MogFur().m_score[1] >= work.m_prevScoreB + 5) {
				work.m_prevScoreB = Chara.MogFur().m_score[1];
				messageId = 1;
			} else if (Chara.MogFur().m_score[1] < work.m_prevScoreB - 5) {
				work.m_prevScoreB = Chara.MogFur().m_score[1];
				messageId = 6;
			}
			if (Chara.MogFur().m_score[2] >= work.m_prevScoreC + 5) {
				work.m_prevScoreC = Chara.MogFur().m_score[2];
				messageId = 1;
			} else if (Chara.MogFur().m_score[2] < work.m_prevScoreC - 5) {
				work.m_prevScoreC = Chara.MogFur().m_score[2];
				messageId = 6;
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
				}
				if ((System.m_frameCounter & 7) == 0) {
					Sound.PlaySe(0x249f3, 0x40, 0x7F, 0);
				}
			} else if (radarType == 3) {
				work.m_eraseTicks = 0;
				if ((((centerAfter.r < 0x0D) || (centerAfter.g < 0x0D)) || (centerAfter.b < 0x0D)) && (centerAfter.a != 0)) {
					work.m_offColorTicks++;
				}
				if ((System.m_frameCounter & 0xF) == 0) {
					Sound.PlaySe(0x249f4, 0x40, 0x7F, 0);
				}
			} else {
				work.m_offColorTicks = 0;
				work.m_eraseTicks = 0;
			}

			int particleNo = 0;
			int emitParticle = 0;
			_GXColor particleColor = centerBefore;
			if (radarType < 3) {
				particleNo = 0x73;
				particleColor = brushColor;
				emitParticle = ((System.m_frameCounter & 1) == 0);
			} else if (eraseMode != 0) {
				particleNo = 0x72;
				emitParticle = 1;
			} else if (radarType == 3) {
				particleNo = 0x74;
				emitParticle = ((System.m_frameCounter & 7) == 0);
			}
			if (emitParticle != 0) {
				CFlatRuntime2Storage().ResetParticleWork(particleNo | 0x100, 0);
				CFlatRuntime2Storage().SetParticleWorkPos(worldPos, kCharaFurDepthZero);
				const int particleIndex = CFlatRuntime2Storage().PutParticleWork();
				pppFVECTOR4 color;
				color.x = static_cast<float>(particleColor.r) / kCharaFurColorComponentScale;
				color.y = static_cast<float>(particleColor.g) / kCharaFurColorComponentScale;
				color.z = static_cast<float>(particleColor.b) / kCharaFurColorComponentScale;
				color.w = static_cast<float>(particleColor.a) / kCharaFurAlphaComponentScale;
				PartPcs.SetParColIdx(particleIndex, color);
			}

			if (work.m_offColorTicks == 10) {
				if (messageId < 0) {
					messageId = 2;
				}
				work.m_offColorTicks = 0x0B;
			}
			if (work.m_eraseTicks == 10) {
				if (messageId < 0) {
					messageId = 5;
				}
				work.m_eraseTicks = 0x0B;
			}
			if (work.m_eraseTicks == 0x32) {
				if (messageId < 0) {
					messageId = 6;
				}
				work.m_eraseTicks = 0x33;
			}

			if (radarType < 3) {
				if (work.m_loopSeHandle == 0) {
					work.m_loopSeHandle = Sound.PlaySe(0x249f2, 0x40, 0x7F, 0);
				}
			}
		}
	} else {
		if (MogRadarType() < 3) {
			StopMogLoopSe(work);
		}
	}

	if ((triggerButtons & 0x200) != 0) {
		CFlatRuntime::CStack stack[3];
		stack[0].m_word = 2;
		stack[1].m_word = 0;
		stack[2].m_word = 0;
		gCFlatRuntime().SystemCall(0, 1, 9, 3, stack, 0);
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
int CChara::CModel::PickFur(
    Mtx param_2, _GXColor brushColor, int doPaint, int mode, _GXColor* centerBefore, _GXColor* centerAfter, Vec* worldPos)
{
	if (static_cast<signed char>(m_flags10C << 1) >= 0) {
		return -1;
	}
	register Vec* outWorldPos = worldPos;

	CMaterialSet* materialSet = ModelMaterialSet(this);
	FurMeshRaw* mesh = ModelMeshes(this);
	CChara::CNode* nodes = ModelNodes(this);

	const unsigned short meshCount = ModelMeshCount(this);
	const float cursorX = static_cast<float>(Chara.MogFur().m_cursorX);
	const float cursorY = static_cast<float>(Chara.MogFur().m_cursorY);
	float hitU = 0.0f;
	float hitV = 0.0f;
	float nearestDepth = kCharaFurNoHitDepth;
	int hitAny = 0;
	int hitPaintable = 0;
	CVector hitViewPos;
	hitViewPos.Identity();
	Mtx44 screenMtx;
	PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);

	for (unsigned int meshIndex = 0; meshIndex < meshCount; meshIndex++, mesh++) {
		if (mesh->m_workPositions == 0) {
			continue;
		}
		if (((ModelMeshVisibleMask(this) >> meshIndex) & 1) == 0) {
			continue;
		}

		Mtx meshMtx;
		if (mesh->m_data->m_skinCount == 0) {
			PSMTXConcat(ModelDrawMtx(this), nodes[mesh->m_data->m_nodeIndex].m_mtx, meshMtx);
		} else {
			PSMTXCopy(ModelDrawMtx(this), meshMtx);
		}

		Mtx modelViewMtx;
		PSMTXConcat(reinterpret_cast<MtxPtr>(param_2), meshMtx, modelViewMtx);
		const unsigned int posGqr = ModelPosQuant(this);
		const int normGqr = ModelNormQuant(this);
		Chara.gqrInit(posGqr << 0x18 | 0x70000 | posGqr << 8 | 7,
		              normGqr << 0x18 | 0x70000 | normGqr << 8 | 7, 0xc070c07);

		FurDisplayListRaw* displayList = mesh->m_data->m_displayLists;
		int displayCount = mesh->m_data->m_displayListCount;
		while (--displayCount >= 0) {
			CMaterial* material = materialSet->m_materials[displayList->m_material];
			int paintableMaterial = 0;
			CTexture* pickTexture = material->GetFurPickTexture();
			if (pickTexture != 0 && pickTexture->m_format == 5) {
				paintableMaterial = 1;
			}
			const int furMaterial = material->IsFurEnabled();

			const unsigned char* cursor = reinterpret_cast<const unsigned char*>(displayList->m_data);
			int remaining = displayList->m_size;
			if ((cursor[0] & 7) != 0) {
				displayList++;
				continue;
			}
			while (remaining > 0) {
				const unsigned char command = cursor[0];
				if ((command & 0xF8) == 0) {
					break;
				}

				const unsigned char primitive = command & 0xF8;
				const unsigned short count = *reinterpret_cast<const unsigned short*>(cursor + 1);
				cursor += 3;
				remaining -= static_cast<int>(count) * 8 + 3;
				if (primitive != 0x90 && primitive != 0x98) {
					break;
				}

				FurProjectedVertex prev2;
				FurProjectedVertex prev1;
				prev2.m_valid = false;
				prev1.m_valid = false;

				for (unsigned short vertexIndex = 0; vertexIndex < count; vertexIndex++) {
					const unsigned short* indices = reinterpret_cast<const unsigned short*>(cursor);
					FurProjectedVertex current;
					ProjectFurVertex(current, mesh, modelViewMtx, screenMtx, indices[0], indices[3], posGqr);

					const FurProjectedVertex* a = 0;
					const FurProjectedVertex* b = 0;
					if (primitive == 0x90) {
						if ((vertexIndex % 3) == 2 && prev2.m_valid && prev1.m_valid && current.m_valid) {
							a = &prev2;
							b = &prev1;
						}
					} else if (primitive == 0x98) {
						if (prev2.m_valid && prev1.m_valid && current.m_valid) {
							if ((vertexIndex & 1) != 0) {
								a = &prev1;
								b = &prev2;
							} else {
								a = &prev2;
								b = &prev1;
							}
						}
					}

					if (a != 0) {
						if (FurPointInTriangle(cursorX, cursorY, *a, *b, current)) {
							const float depth = FurHitDepth(*a, *b, current);
							if (depth < nearestDepth) {
								float uvU;
								float uvV;
								FurInterpolateHit(hitViewPos, uvU, uvV, screenMtx, cursorX, cursorY, *a, *b, current);
								hitAny = 1;
								if (outWorldPos != 0) {
									*outWorldPos = hitViewPos;
								}
								if (furMaterial) {
									nearestDepth = depth;
									hitU = uvU;
									hitV = uvV;
									hitPaintable = paintableMaterial;
								}
							}
						}
					}

					prev2 = prev1;
					prev1 = current;
					cursor += 8;
				}
			}
			displayList++;
		}
	}

	if (doPaint != 0 && hitPaintable != 0) {
		CTexture* texture = FindMogFurTexture(this);
		if (texture != 0 && texture->m_format == 5 && nearestDepth != kCharaFurDepthZero) {
			_GXColor paintColor = brushColor;
			_GXColor before;
			_GXColor after;
			brush(reinterpret_cast<unsigned short*>(texture->m_imageData), texture->m_width, texture->m_height, hitU, hitV, mode,
			      paintColor, &before, &after);
			if (centerBefore != 0) {
				*centerBefore = before;
			}
			if (centerAfter != 0) {
				*centerAfter = after;
			}
		}
	}

	if (outWorldPos != 0) {
		Mtx invViewMtx;
		PSMTXInverse(param_2, invViewMtx);
		PSMTXMultVec(invViewMtx, outWorldPos, outWorldPos);
	}

	return nearestDepth == kCharaFurNoHitDepth ? -(hitAny == 0) : 1;
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
void CChara::CModel::DrawFur(Mtx viewMtx, int shadowPass)
{
	if (static_cast<signed char>(m_flags10C << 1) >= 0) {
		return;
	}

	CMaterialSet* materialSet = ModelMaterialSet(this);
	FurMeshRaw* mesh = ModelMeshes(this);
	CChara::CNode* nodes = ModelNodes(this);

	const int materialCount = materialSet->m_materials.GetSize();

	bool hasFurMaterial = false;
	for (int i = 0; i < materialCount; i++) {
		CMaterial* material = materialSet->m_materials[i];
		if (material->IsFurEnabled()) {
			hasFurMaterial = true;
			break;
		}
	}
	if (!hasFurMaterial) {
		return;
	}

	float furStep = ModelFurStep(this);
	float furDepth = kCharaFurDepthZero;
	CVector modelPos;
	CVector viewPos;
	modelPos.x = ModelDrawMtx(this)[0][3];
	modelPos.y = ModelDrawMtx(this)[1][3];
	modelPos.z = ModelDrawMtx(this)[2][3];
	PSMTXMultVec(viewMtx, reinterpret_cast<Vec*>(&modelPos), reinterpret_cast<Vec*>(&viewPos));
	if (viewPos.z < kCharaFurViewDepthThreshold) {
		Vec4d clipPos;
		Math.MTX44MultVec4(CameraPcs.m_screenMatrix, reinterpret_cast<Vec*>(&viewPos), &clipPos);
		furDepth = -clipPos.z / clipPos.w;
	}

	float furLength = ModelFurLenScale(this) * (kCharaFurDepthScaleBase - furDepth) + ModelFurLenScale(this);
	const int furShade = static_cast<int>(kCharaFurShadeScale * ModelFurCur(this));
	const GXColor furColor = CColor(static_cast<unsigned char>(furShade), static_cast<unsigned char>(furShade),
	                                static_cast<unsigned char>(furShade), 0xFF)
	                             .color;

	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	GXSetZCompLoc((u8)0);
	_GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_ALWAYS, 0);
	GXSetZMode((u8)1, (GXCompare)3, (u8)0);
	GXSetCullMode(GX_CULL_FRONT);
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
	GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_S16, ModelNormQuant(this) & 0xFF);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 0x0C);
	LightPcs.EnableLight(1, 1);
	GXSetZMode((u8)1, (GXCompare)3, (u8)0);
	GXSetChanMatColor(GX_COLOR0A0, furColor);
	LightPcs.SetAmbientAlpha(ModelLightAlpha(this));
	GXSetNumIndStages(0);
	GXSetNumTevStages(2);
	GXSetTevDirect(GX_TEVSTAGE0);
	_GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
	_GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
	_GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
	_GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	_GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	_GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
	GXSetTevDirect(GX_TEVSTAGE1);
	_GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
	_GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_ZERO);
	_GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
	_GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	_GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	_GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);

	Mtx texMtx;
	PSMTXIdentity(texMtx);
	texMtx[0][0] = furStep;
	texMtx[1][1] = furStep;
	GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);

	const unsigned short meshCount = ModelMeshCount(this);
	const int posQuant = ModelPosQuant(this) & 0xFF;
	const int normQuant = ModelNormQuant(this) & 0xFF;
	unsigned int prevExtraTexture = 0xFFFFFFFF;
	int prevExtraTextureFormat = -1;

	for (unsigned int meshIndex = 0; meshIndex < meshCount; meshIndex++, mesh++) {
		if (mesh->m_workPositions == 0) {
			continue;
		}
		if (((ModelMeshVisibleMask(this) >> meshIndex) & 1) == 0) {
			continue;
		}

		Mtx meshMtx;
		if (mesh->m_data->m_skinCount == 0) {
			PSMTXConcat(ModelDrawMtx(this), nodes[mesh->m_data->m_nodeIndex].m_mtx, meshMtx);
		} else {
			PSMTXCopy(ModelDrawMtx(this), meshMtx);
		}

		int shadowCount = 0;
		CMaterial* shadowMaterials[2];
		MtxPtr shadowMatrices[2];
		if (shadowPass != 0) {
			shadowCount = MaterialMan.GetCharaShadow(2, shadowMaterials, shadowMatrices, reinterpret_cast<Vec*>(&modelPos), kCharaFurShadowRange, kCharaFurShadowFade, 0);
			for (int shadowIndex = 0; shadowIndex < shadowCount; shadowIndex++) {
				TextureMan.SetTexture(static_cast<GXTexMapID>(shadowIndex + 3), shadowMaterials[shadowIndex]->GetFurTexture(0));

				Mtx shadowTexMtx;
				PSMTXConcat(shadowMatrices[shadowIndex], meshMtx, shadowTexMtx);
				GXLoadTexMtxImm(shadowTexMtx, 0x21 + shadowIndex * 3, GX_MTX3x4);
				GXSetTexCoordGen2(static_cast<GXTexCoordID>(shadowIndex + 3), GX_TG_MTX3x4, GX_TG_POS,
				                  0x21 + shadowIndex * 3, GX_FALSE, GX_PTIDENTITY);
			}
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

		unsigned int posGqr = ModelPosQuant(this);
		int normGqr = ModelNormQuant(this);
		FurDisplayListRaw* displayList = mesh->m_data->m_displayLists;
		Chara.gqrInit(posGqr << 0x18 | 0x70000 | posGqr << 8 | 7, normGqr << 0x18 | 0x70000 | normGqr << 8 | 7,
		              0xC070C07);
		for (unsigned int displayIndex = 0; displayIndex < mesh->m_data->m_displayListCount; displayIndex++, displayList++) {
			CMaterial* material = materialSet->m_materials[displayList->m_material];
			if (!material->IsFurEnabled()) {
				continue;
			}

			TextureMan.SetTexture(GX_TEXMAP0, material->GetFurTexture(0));
			unsigned int hasExtraTexture = 0;
			int extraTextureFormat = -1;
			if (static_cast<short>(material->GetTextureIndex(1)) != -1) {
				CTexture* extraTexture = material->GetFurTexture(1);
				TextureMan.SetTexture(GX_TEXMAP2, extraTexture);
				hasExtraTexture = 1;
				extraTextureFormat = extraTexture->m_format;
			}

			if (prevExtraTexture != hasExtraTexture || prevExtraTextureFormat != extraTextureFormat) {
				GXSetTevDirect(GX_TEVSTAGE0);
				_GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
				_GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
				_GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
				_GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				_GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				_GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);

				int tevStage = 1;
				for (int shadowStage = 0; shadowStage < shadowCount; shadowStage++, tevStage++) {
					GXSetTevDirect(static_cast<GXTevStageID>(tevStage));
					_GXSetTevSwapMode(static_cast<GXTevStageID>(tevStage), GX_TEV_SWAP0, GX_TEV_SWAP0);
					_GXSetTevColorIn(static_cast<GXTevStageID>(tevStage), GX_CC_CPREV, GX_CC_TEXC, GX_CC_C1, GX_CC_ZERO);
					_GXSetTevAlphaIn(static_cast<GXTevStageID>(tevStage), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
					_GXSetTevColorOp(static_cast<GXTevStageID>(tevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE,
					                 GX_TEVPREV);
					_GXSetTevAlphaOp(static_cast<GXTevStageID>(tevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE,
					                 GX_TEVPREV);
					_GXSetTevOrder(static_cast<GXTevStageID>(tevStage), static_cast<GXTexCoordID>(shadowStage + 3),
					               static_cast<GXTexMapID>(shadowStage + 3), GX_COLOR_NULL);
				}

				GXSetTevDirect(static_cast<GXTevStageID>(tevStage));
				_GXSetTevSwapMode(static_cast<GXTevStageID>(tevStage), GX_TEV_SWAP0, GX_TEV_SWAP0);
				_GXSetTevColorIn(static_cast<GXTevStageID>(tevStage), GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_ZERO);
				_GXSetTevAlphaIn(static_cast<GXTevStageID>(tevStage), GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
				_GXSetTevColorOp(static_cast<GXTevStageID>(tevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, GX_TRUE,
				                 GX_TEVPREV);
				_GXSetTevAlphaOp(static_cast<GXTevStageID>(tevStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE,
				                 GX_TEVPREV);
				_GXSetTevOrder(static_cast<GXTevStageID>(tevStage), GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);

				int tevStageCount = tevStage + 1;
				if (hasExtraTexture == 0) {
					GXSetNumTexGens(static_cast<u8>(shadowCount + 2));
					GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, GX_PTIDENTITY);
					GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, 0x1E, GX_FALSE, GX_PTIDENTITY);
				} else {
					GXSetTevDirect(static_cast<GXTevStageID>(tevStageCount));
					_GXSetTevSwapMode(static_cast<GXTevStageID>(tevStageCount), GX_TEV_SWAP0, GX_TEV_SWAP0);
					if (extraTextureFormat == 5) {
						_GXSetTevColorIn(static_cast<GXTevStageID>(tevStageCount), GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC,
						                 GX_CC_ZERO);
						_GXSetTevAlphaIn(static_cast<GXTevStageID>(tevStageCount), GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA,
						                 GX_CA_ZERO);
					} else {
						_GXSetTevColorIn(static_cast<GXTevStageID>(tevStageCount), GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO,
						                 GX_CC_CPREV);
						_GXSetTevAlphaIn(static_cast<GXTevStageID>(tevStageCount), GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA,
						                 GX_CA_ZERO);
					}
					_GXSetTevColorOp(static_cast<GXTevStageID>(tevStageCount), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE,
					                 GX_TEVPREV);
					_GXSetTevAlphaOp(static_cast<GXTevStageID>(tevStageCount), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE,
					                 GX_TEVPREV);
					_GXSetTevOrder(static_cast<GXTevStageID>(tevStageCount), GX_TEXCOORD2, GX_TEXMAP2, GX_COLOR_NULL);
					tevStageCount++;
					GXSetNumTexGens(static_cast<u8>(shadowCount + 3));
					GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, GX_PTIDENTITY);
					GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, 0x1E, GX_FALSE, GX_PTIDENTITY);
					GXSetTexCoordGen2(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, GX_PTIDENTITY);
				}
				GXSetNumTevStages(static_cast<u8>(tevStageCount));
				prevExtraTexture = hasExtraTexture;
				prevExtraTextureFormat = extraTextureFormat;
			}

			for (unsigned int layer = 0; layer < 8; layer++) {
				GXTexObj texObj;
				void* texData = reinterpret_cast<unsigned char*>(gMogFurTexBuffer) + (layer * 0x4000);
				GXInitTexObj(&texObj, texData, 0x80, 0x80, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, GX_FALSE);
				GXLoadTexObj(&texObj, GX_TEXMAP1);

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
void CChara::freeFurTex()
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
void CChara::makeFurTex()
{
	CHairSet hairSet[0x20];

	static CColor furBaseColor(0x80, 0x80, 0x80, 0xFF);
	static CColor furTipColor(0xF0, 0xF0, 0xF0, 0);
	static CColor furNoiseBase(0, 0, 0, 0);
	static CColor furNoiseRange(8, 8, 8, 0);
	static Vec velBase = CVector(kCharaFurDepthZero, FLOAT_80331160, kCharaFurDepthZero);
	static Vec velRand = CVector(kCharaFurDepthZero, kYmEnvQuarter, kCharaFurDepthZero);
	static Vec accelBase = CVector(kCharaFurDepthZero, kCharaFurDepthZero, kCharaFurDepthZero);
	static Vec accelRand = CVector(kCharaFurDepthZero, kCharaFurDepthZero, kCharaFurDepthZero);

	s_mogFurRand = 0;
	s_mogFurMaxY = 0.0f;

	for (unsigned int i = 0; i < 0x20; i++) {
		CVector scaled;
		PSVECScale(&velRand, scaled, FurRandScale());
		PSVECAdd(&velBase, scaled, hairSet[i].m_vec0);

		PSVECScale(&accelRand, scaled, FurRandScale());
		PSVECAdd(&accelBase, scaled, hairSet[i].m_vec1);

		hairSet[i].m_colors[0] = FurNoiseColor(furBaseColor, furNoiseBase, FurRandScale());
		hairSet[i].m_colors[1] = FurNoiseColor(furTipColor, furNoiseRange, FurRandScale());

		float endY = hairSet[i].m_vec0.y + kCharaFurWeightScale * hairSet[i].m_vec1.y;
		if (s_mogFurMaxY < endY) {
			s_mogFurMaxY = endY;
		}
	}

	GXSetPixelFmt(GX_PF_RGBA6_Z24, GX_ZC_LINEAR);
	_GXColor savedCopyClear = Graphic.m_defaultCopyClearColor;
	GXSetAlphaUpdate(GX_TRUE);
	GXSetViewport(kCharaFurDepthZero, kCharaFurDepthZero, FLOAT_80331168, FLOAT_80331168, kCharaFurDepthZero,
	              kCharaFurDepthScaleBase);
	GXSetScissor(0, 0, 0x80, 0x80);
	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	GXSetZCompLoc(GX_FALSE);
	_GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_ALWAYS, 0);
	GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
	GXSetCullMode(GX_CULL_NONE);
	GXSetNumTevStages(1);
	_GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
	_GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
	GXSetNumChans(1);
	GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	GXSetTexCopySrc(0, 0, 0x80, 0x80);
	GXSetTexCopyDst(0x80, 0x80, GX_TF_IA4, GX_FALSE);

	Mtx posMtx;
	posMtx[0][0] = kCharaFurDepthScaleBase;
	posMtx[1][0] = kCharaFurDepthZero;
	posMtx[2][0] = kCharaFurDepthZero;
	posMtx[0][1] = kCharaFurDepthZero;
	posMtx[1][1] = kCharaFurDepthZero;
	posMtx[2][1] = kCharaFurDepthScaleBase;
	posMtx[0][2] = kCharaFurDepthZero;
	posMtx[1][2] = FLOAT_8033116C * (kCharaFurViewDepthThreshold / s_mogFurMaxY);
	posMtx[2][2] = kCharaFurDepthZero;
	posMtx[0][3] = kCharaFurDepthZero;
	posMtx[1][3] = kCharaFurDepthZero;
	posMtx[2][3] = kCharaFurDepthZero;

	Mtx44 projection;
	PSMTX44Identity(projection);
	GXSetProjection(projection, GX_ORTHOGRAPHIC);

	gMogFurTexBuffer = Memory._Alloc(0x20000, CharaPcs.m_viewerAnimStage, const_cast<char*>(s_chara_fur_cpp), 0xE9, 0);
	DCInvalidateRange(gMogFurTexBuffer, 0x20000);

	for (int layer = 0; layer < 8; layer++) {
		posMtx[2][3] -= s_mogFurMaxY * FLOAT_8033115C;
		GXLoadPosMtxImm(posMtx, GX_PNMTX0);
		GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);

		float layerFactor = static_cast<float>(layer) * FLOAT_8033115C;
		layerFactor = layerFactor * layerFactor;
		CColor layerColor(
		    static_cast<unsigned char>(static_cast<int>(furBaseColor.color.r * (kCharaFurDepthScaleBase - layerFactor)) +
		                               static_cast<int>(furTipColor.color.r * layerFactor)),
		    static_cast<unsigned char>(static_cast<int>(furBaseColor.color.g * (kCharaFurDepthScaleBase - layerFactor)) +
		                               static_cast<int>(furTipColor.color.g * layerFactor)),
		    static_cast<unsigned char>(static_cast<int>(furBaseColor.color.b * (kCharaFurDepthScaleBase - layerFactor)) +
		                               static_cast<int>(furTipColor.color.b * layerFactor)),
		    static_cast<unsigned char>(static_cast<int>(furBaseColor.color.a * (kCharaFurDepthScaleBase - layerFactor)) +
		                               static_cast<int>(furTipColor.color.a * layerFactor)));
		Graphic.SetCopyClear(layerColor, 0xFFFFFF);
		GXCopyTex(static_cast<unsigned char*>(gMogFurTexBuffer) + layer * 0x4000, GX_TRUE);
		GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);

		s_mogFurRand = 0;
		for (int hair = 0; hair < 0x4000; hair++) {
			GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);

			float rootX = kCharaFurDepthScaleBase * (FLOAT_80331164 * static_cast<float>(FurRandNext()) + kCharaFurViewDepthThreshold);
			float rootZ = kCharaFurDepthScaleBase * (FLOAT_80331164 * static_cast<float>(FurRandNext()) + kCharaFurViewDepthThreshold);
			CVector root(rootX, kCharaFurDepthZero, rootZ);

			s_mogFurRand = s_mogFurRand * 0x41C64E6D + 0x3039;
			CHairSet& src = hairSet[(s_mogFurRand >> 11) & 0x1F];

			float t = kCharaFurDepthZero;
			for (int v = 0; v < 5; v++) {
				float t2 = t * t;
				CVector accelTerm;
				PSVECScale(src.m_vec1, accelTerm, kCharaFurWeightScale * t2);
				CVector velTerm;
				PSVECScale(src.m_vec0, velTerm, t);
				CVector tmp;
				PSVECAdd(root, velTerm, tmp);
				CVector pos;
				PSVECAdd(tmp, accelTerm, pos);
				float px = pos.x;
				float py = pos.y;
				float pz = pos.z;

				CColor color(
				    static_cast<unsigned char>(static_cast<int>(src.m_colors[0].color.r * (kCharaFurDepthScaleBase - t2)) +
				                               static_cast<int>(src.m_colors[1].color.r * t2)),
				    static_cast<unsigned char>(static_cast<int>(src.m_colors[0].color.g * (kCharaFurDepthScaleBase - t2)) +
				                               static_cast<int>(src.m_colors[1].color.g * t2)),
				    static_cast<unsigned char>(static_cast<int>(src.m_colors[0].color.b * (kCharaFurDepthScaleBase - t2)) +
				                               static_cast<int>(src.m_colors[1].color.b * t2)),
				    0);
				GXWGFifo.f32 = px;
				GXWGFifo.f32 = py;
				GXWGFifo.f32 = pz;
				GXWGFifo.u32 = *reinterpret_cast<unsigned int*>(&color.color);
				t += kYmEnvQuarter;
			}

			GXBegin(GX_POINTS, GX_VTXFMT0, 5);
			t = kCharaFurDepthZero;
			for (int v = 0; v < 5; v++) {
				float t2 = t * t;
				CVector accelTerm;
				PSVECScale(src.m_vec1, accelTerm, kCharaFurWeightScale * t2);
				CVector velTerm;
				PSVECScale(src.m_vec0, velTerm, t);
				CVector tmp;
				PSVECAdd(root, velTerm, tmp);
				CVector pos;
				PSVECAdd(tmp, accelTerm, pos);
				float px = pos.x;
				float py = pos.y;
				float pz = pos.z;

				CColor color(
				    static_cast<unsigned char>(static_cast<int>(src.m_colors[0].color.r * (kCharaFurDepthScaleBase - t2)) +
				                               static_cast<int>(src.m_colors[1].color.r * t2)),
				    static_cast<unsigned char>(static_cast<int>(src.m_colors[0].color.g * (kCharaFurDepthScaleBase - t2)) +
				                               static_cast<int>(src.m_colors[1].color.g * t2)),
				    static_cast<unsigned char>(static_cast<int>(src.m_colors[0].color.b * (kCharaFurDepthScaleBase - t2)) +
				                               static_cast<int>(src.m_colors[1].color.b * t2)),
				    0);
				GXWGFifo.f32 = pz;
				GXWGFifo.f32 = py;
				GXWGFifo.f32 = px;
				GXWGFifo.u32 = *reinterpret_cast<unsigned int*>(&color.color);
				t += kYmEnvQuarter;
			}
		}

		GXCopyTex(static_cast<unsigned char*>(gMogFurTexBuffer) + layer * 0x4000, GX_TRUE);
	}

	GXPixModeSync();
	Graphic.SetViewport();
	Graphic.SetCopyClear(savedCopyClear, 0xFFFFFF);
	GXSetTexCopySrc(0, 0, 0x280, 0x1C0);
	GXCopyTex(gRenderScratchTextureBuffer, GX_TRUE);
	Graphic._WaitDrawDone(const_cast<char*>(s_chara_fur_cpp), 0x138);
	if (DAT_8032EDEC != 0) {
		Memory.Free(DAT_8032EDEC);
		DAT_8032EDEC = 0;
	}
	Graphic.SetViewport();
	Graphic.SetStdPixelFmt();
	GXSetAlphaUpdate(GX_FALSE);
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
	int dy;

	_GXColor defaultColor = CColor(0x0f, 0x0f, 0x0f, 0).color;
	*centerAfter = defaultColor;
	*centerBefore = *centerAfter;

	int texelCountBytes = width * height * 2;
	int centerX = (int)((float)width * fx);
	int centerY = (int)((float)height * fy);

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

			if (px < 0 || width <= px || py < 0 || height <= py) {
				continue;
			}

			distance = (dx < 0 ? -dx : dx) + (dy < 0 ? -dy : dy);
			int ux = px;
			unsigned int uy = py;
			tileIndex = ((ux & 3) + ((uy & 3) * 4) + (ux >> 2) * 0x10 + (uy >> 2) * width * 4) * 2;
			packed = *(unsigned short*)(((char*)pixels) + tileIndex);

			b = packed & 0x0f;
			g = (packed >> 4) & 0x0f;
			r = (packed >> 8) & 0x0f;
			a = (packed >> 12) & 0x07;

			if (distance == 0) {
				_GXColor beforeColor = CColor((unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a).color;
				*centerBefore = beforeColor;
			}

			if (mode != 0) {
				int reduce = (targetColor.a * (4 - distance)) / 4;
				a -= reduce;
				if (a < 0) {
					a = 0;
				}
			} else {
				float k = (float)(7 - targetColor.a) / kCharaFurAlphaComponentScale + (float)(distance / 4);
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
			}

			*(unsigned short*)(((char*)pixels) + tileIndex) = (unsigned short)((a << 12) | (r << 8) | (g << 4) | b);

			if (distance == 0) {
				_GXColor afterColor = CColor((unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a).color;
				*centerAfter = afterColor;
			}
		}
	}

	DCFlushRange(pixels, texelCountBytes);
	GXInvalidateTexAll();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int nearColor(CColor src, CColor ref)
{
	int dr = static_cast<int>(src.color.r) - static_cast<int>(ref.color.r);
	if (dr < 0) {
		dr = -dr;
	}
	dr += 7 - static_cast<int>(src.color.a);

	int dg = static_cast<int>(src.color.g) - static_cast<int>(ref.color.g);
	if (dg < 0) {
		dg = -dg;
	}
	dg += 7 - static_cast<int>(src.color.a);

	int db = static_cast<int>(src.color.b) - static_cast<int>(ref.color.b);
	if (db < 0) {
		db = -db;
	}
	db += 7 - static_cast<int>(src.color.a);

	return (dr < 6 && dg < 6 && db < 6) ? 1 : 0;
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

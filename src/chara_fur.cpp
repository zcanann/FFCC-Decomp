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

extern "C" void __ct__7CVectorFv(CVector*);

struct FurPickPointerTable {
	CVector* volatile m_areaCA2;
	CVector* volatile m_areaBC2;
	CVector* volatile m_hitToC2;
	CVector* volatile m_hitToB2;
	CVector* volatile m_areaCA1;
	CVector* volatile m_areaBC1;
	CVector* volatile m_hitToC1;
	CVector* volatile m_hitToB1;
	CVector* volatile m_rayEndB;
	CVector* volatile m_rayEndA;
};

struct FurPickWorkPointers {
	CVector* volatile m_areaCAw;
	CVector* volatile m_areaBCw;
	CVector* volatile m_hitToBw;
	CVector* volatile m_areaCAc;
	CVector* volatile m_areaBCc;
	CVector* volatile m_hitToCc;
	CVector* volatile m_hitToBc;
	CVector* volatile m_rayEndc;
};

extern char sYmEnvSeparator[4];
extern "C" char* sMogRadarTypeLabels[];
extern "C" char sMogRadarDebugFormatBlock[];
extern "C" char lbl_801DB648[];
extern "C" char sMogFurTextureName[8];
extern "C" {
extern unsigned char m_mogWork[0x2C];
float m_height;
void* m_pDisplayList;
void* m_pTexBuf;
unsigned int m_seed;
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
extern float kYmEnvTen;
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
    union
    {
        unsigned long m_valid;
        struct
        {
            signed char m_projValid : 1;
            signed char m_edgeFlag : 1;
        } m_flagBits;
    };
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

static inline unsigned int ModelMeshCount(CChara::CModel* model)
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

static inline float (*ModelWorldDrawMtx(CChara::CModel* model))[4]
{
    return model->m_drawMtx;
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

static inline void DrawFurDisplayListShell(const FurMeshRaw* mesh, const FurDisplayListRaw* displayList, float shellOffset,
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
#pragma push
#pragma optimization_level 3
#pragma opt_dead_assignments off
void CChara::TimeMogFur()
{
	const int frameCounter = static_cast<int>(System.m_frameCounter);

	if (MogFur().m_timestamp + 0x1A5E0 < frameCounter) {
		MogFur().m_timestamp = frameCounter;
		if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
			System.Printf(sYmEnvSeparator);
		}
		if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
			System.Printf(sMogRadarDebugFormatBlock);
		}
		if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
			System.Printf(sYmEnvSeparator);
		}
	}

	unsigned short* const texels = MogFur().m_texels;
	memset(MogFur().m_score, 0, 0x40);

	for (int y = 0; y < 0x40; y++) {
		for (int x = 0; x < 0x40; x++) {
			int tileIndex = ((y / 4) * 0x100 + (y % 4) * 4 + (x % 4) + (x / 4) * 0x10) * 2;
			unsigned short packed = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(texels) + tileIndex);

			unsigned int a = (packed >> 12) & 7;
			int baseLight = 7 - static_cast<int>(a);
			int r = ((packed >> 8) & 0xF) + 4 + baseLight;
			int b = (packed & 0xF) + 4 + baseLight;
			int gNibble = (packed >> 4) & 0xF;
			int g = gNibble + 4 + baseLight;

			int light = 0xF;
			if (r < 0xF) {
				light = r;
			}
			r = 0xF;
			if (g < 0xF) {
				r = g;
			}
			g = 0xF;
			if (b < 0xF) {
				g = b;
			}

			int aPlus = static_cast<int>(a) + 2;
			int clampedA = 7;
			if (aPlus < 7) {
				clampedA = aPlus;
			}

			*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(texels) + tileIndex) =
			    static_cast<unsigned short>((clampedA << 12) | (light << 8) | (r << 4) | g);
		}
	}

	CalcMogScore();
}
#pragma pop

#pragma push
#pragma bool off
static inline int FurColorMatch(CColor src, CColor ref, int limit)
{
	int hits = 0;

	int dr = static_cast<int>(src.color.r) - static_cast<int>(ref.color.r);
	if (dr < 0) {
		dr = -dr;
	}
	dr += 7 - static_cast<int>(src.color.a);
	hits += (dr <= limit);

	int dg = static_cast<int>(src.color.g) - static_cast<int>(ref.color.g);
	if (dg < 0) {
		dg = -dg;
	}
	dg += 7 - static_cast<int>(src.color.a);
	hits += (dg <= limit);

	int db = static_cast<int>(src.color.b) - static_cast<int>(ref.color.b);
	if (db < 0) {
		db = -db;
	}
	db += 7 - static_cast<int>(src.color.a);
	hits += (db <= limit);

	return static_cast<unsigned int>(__cntlzw(3 - hits)) >> 5;
}
#pragma pop

/*
 * --INFO--
 * PAL Address: 0x800df7f8
 * PAL Size: 2224b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma push
#pragma opt_common_subs off
void CChara::CalcMogScore()
{
	char* fmtBase = lbl_801DB648;
	#define fur m_sharedState.m_mogFur
	unsigned short* texels = fur.m_texels;

	memset(fur.m_score, 0, 0x40);

	int bitCount = 0;
	int circleCount = 0;
	int lineCount = 0;

	for (int y = 0; y < 0x40; y++) {
		for (int x = 0; x < 0x40; x++) {
			const int dx = x - 0x20;
			const int dy = y - 0x20;
			const int dist = static_cast<int>(sqrt(static_cast<double>(static_cast<int>(dx * dx + dy * dy))));

			if (dist >= 0x40) {
				continue;
			}

			const int tileIndex = (((y % 4) * 4 + (x / 4) * 0x10 + (y / 4) * 0x100) + (x % 4)) * 2;

			const unsigned short packed = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(texels) + tileIndex);
			const int a = (packed >> 12) & 7;
			const int r = (packed >> 8) & 0xF;
			const int g = (packed >> 4) & 0xF;
			const int b = packed & 0xF;
			CColor srcColor(static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b),
			                static_cast<unsigned char>(a));

			int colorHit[3];
			colorHit[0] = FurColorMatch(srcColor, CColor(0xF, 4, 4, 2), 5);
			colorHit[1] = FurColorMatch(srcColor, CColor(4, 0xF, 4, 2), 5);
			colorHit[2] = FurColorMatch(srcColor, CColor(4, 8, 0xF, 2), 5);
			fur.m_alphaScore += a;

			const int ring = dist % 12;
			int angle = static_cast<int>(kYmEnvRadToDeg * atan2(static_cast<double>(dx), static_cast<double>(dy))) + 0x168;
			angle = static_cast<unsigned int>(angle);
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
		int sc;
		if (*scorePtr < 0) {
			sc = 0;
		} else {
			sc = 100;
			if (*scorePtr <= 100) sc = *scorePtr;
		}
		*scorePtr = sc;

		fur.m_radarLevel[i] = (100 - *scorePtr) / 5;
		const int lv = fur.m_radarLevel[i];
		if (lv < 5) {
			level = 5;
		} else {
			level = 0xF;
			if (lv <= 0xF) level = lv;
		}
		fur.m_radarLevel[i] = level;
	}

	{
		int sc0 = fur.m_score[0];
		int sc1 = fur.m_score[1];
		if (sc0 >= 3
		    && kYmEnvDefaultScale * static_cast<float>(sc1 + fur.m_score[2]) < static_cast<float>(sc0)) {
			Game.m_gameWork.m_mogScoreRadarType = 1;
		} else if (sc1 >= 3
		           && kYmEnvDefaultScale * static_cast<float>(sc0 + fur.m_score[2])
		                  < static_cast<float>(sc1)) {
			Game.m_gameWork.m_mogScoreRadarType = 2;
		} else if (fur.m_score[2] >= 3
		           && kYmEnvDefaultScale * static_cast<float>(sc0 + sc1)
		                  < static_cast<float>(fur.m_score[2])) {
			Game.m_gameWork.m_mogScoreRadarType = 3;
		} else {
			Game.m_gameWork.m_mogScoreRadarType = 0;
		}
	}

	{
		char* radarLabel[4];
		char** typeLabels = reinterpret_cast<char**>(fmtBase + 0x4C);
		radarLabel[0] = typeLabels[4];
		radarLabel[1] = typeLabels[5];
		radarLabel[2] = typeLabels[6];
		radarLabel[3] = typeLabels[7];
		Graphic.Printf(
		    5,
		    0xB,
		    fmtBase + 0x84,
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
		    fmtBase + 0xB8,
		    fur.m_lineScore[0],
		    fur.m_lineScore[1],
		    fur.m_lineScore[2],
		    fur.m_circleScore[0],
		    fur.m_circleScore[1],
		    fur.m_circleScore[2],
		    radarLabel[Game.m_gameWork.m_mogScoreRadarType]);
	}
}
#pragma pop

extern "C" const char s_chara_fur_cpp[] = "chara_fur.cpp";

static inline unsigned int FurRandNext()
{
	m_seed = m_seed * 0x41C64E6D + 0x3039;
	return (m_seed >> 16) % 32767;
}

static inline float FurRandScale()
{
	return kCharaFurDepthScaleBase * (FLOAT_80331164 * static_cast<float>(static_cast<int>(FurRandNext())) + kCharaFurViewDepthThreshold);
}

static inline float FurRandScaleL(float scaleBase, float randScale, float depthThreshold)
{
	return scaleBase * (randScale * static_cast<float>(static_cast<int>(FurRandNext())) + depthThreshold);
}

static inline CColor FurNoiseColor(const CColor& base, const CColor& noise, float scale)
{
	CColor scaledNoiseTmp;
	scaledNoiseTmp.color.r = static_cast<unsigned char>(static_cast<int>(noise.color.r * scale));
	scaledNoiseTmp.color.g = static_cast<unsigned char>(static_cast<int>(noise.color.g * scale));
	scaledNoiseTmp.color.b = static_cast<unsigned char>(static_cast<int>(noise.color.b * scale));
	scaledNoiseTmp.color.a = static_cast<unsigned char>(static_cast<int>(noise.color.a * scale));
	CColor scaledNoise = scaledNoiseTmp;

	CColor resultTmp;
	resultTmp.color.r = static_cast<unsigned char>(base.color.r + scaledNoise.color.r);
	resultTmp.color.g = static_cast<unsigned char>(base.color.g + scaledNoise.color.g);
	resultTmp.color.b = static_cast<unsigned char>(base.color.b + scaledNoise.color.b);
	resultTmp.color.a = static_cast<unsigned char>(base.color.a + scaledNoise.color.a);
	return resultTmp;
}

void brush(unsigned short*, int, int, float, float, int, _GXColor, _GXColor*, _GXColor*);

namespace {

static inline bool HasDebugPadOverride(int debugPadLock)
{
	return (debugPadLock != 0) || (Pad.m_debugPadPort != -1);
}

static inline unsigned short MogHeldButtons(int debugPadLock)
{
	if (HasDebugPadOverride(debugPadLock)) {
		return 0;
	}
	int padIndex = 0;
	padIndex &= ~-((__cntlzw(static_cast<unsigned int>(Pad.m_debugPadPort)) & 0x20) >> 5);
	return static_cast<unsigned short>(Pad.GetPadInputs()[padIndex].button[0]);
}

static inline unsigned short MogTriggerButtons(int debugPadLock)
{
	if (HasDebugPadOverride(debugPadLock)) {
		return 0;
	}
	int padIndex = 0;
	padIndex &= ~-((__cntlzw(static_cast<unsigned int>(Pad.m_debugPadPort)) & 0x20) >> 5);
	return static_cast<unsigned short>(Pad.GetPadInputs()[padIndex].buttonDown[0]);
}

static inline int MogPadInt(int debugPadLock, int offset)
{
	if (HasDebugPadOverride(debugPadLock)) {
		return 0;
	}
	int padIndex = 0;
	padIndex &= ~-((__cntlzw(static_cast<unsigned int>(Pad.m_debugPadPort)) & 0x20) >> 5);
	return *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&Pad) + padIndex * sizeof(CPad::PadInput) + offset);
}

static inline float MogPadFloat(int debugPadLock, int offset)
{
	if (HasDebugPadOverride(debugPadLock)) {
		return kCharaFurDepthZero;
	}
	int padIndex = 0;
	padIndex &= ~-((__cntlzw(static_cast<unsigned int>(Pad.m_debugPadPort)) & 0x20) >> 5);
	return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + padIndex * sizeof(CPad::PadInput) + offset);
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
	Graphic._WaitDrawDone(const_cast<char*>(s_chara_fur_cpp), 0x506);
	CTexture* texture = FindMogFurTexture(model);
	if (texture == 0) {
		return;
	}

	void* dstBuffer = texture->m_imageData;
	const int texelCountBytes = texture->m_width * texture->m_height * 2;

	DCInvalidateRange(dstBuffer, texelCountBytes);
	memcpy(dstBuffer, Chara.MogFur().m_texels, 0x2000);
	DCFlushRange(dstBuffer, texelCountBytes);
	GXInvalidateTexAll();
}

static inline void CopyMogTextureToChara(CChara::CModel* model)
{
	Graphic._WaitDrawDone(const_cast<char*>(s_chara_fur_cpp), 0x506);
	CTexture* texture = FindMogFurTexture(model);
	if (texture == 0) {
		return;
	}

	void* srcBuffer = texture->m_imageData;
	const int texWidth = texture->m_width;
	const int texHeight = texture->m_height;

	memcpy(Chara.MogFur().m_texels, srcBuffer, 0x2000);
	DCFlushRange(srcBuffer, texWidth * texHeight * 2);
	GXInvalidateTexAll();
}

static inline void OpenMogHintMessage(int messageId)
{
	if (messageId < 0) {
		return;
	}

	if ((*reinterpret_cast<CMesMenu**>(reinterpret_cast<unsigned char*>(&MenuPcs) + 0x120))->IsActiveMessage()) {
		return;
	}

	CFlatData* flatData = reinterpret_cast<CFlatData*>(reinterpret_cast<unsigned char*>(&Game) + 0xCC38 + sizeof(CFlatData));
	char** mesPtr = reinterpret_cast<char**>(reinterpret_cast<unsigned char*>(flatData) + 0xD4);
	(*reinterpret_cast<CMesMenu**>(reinterpret_cast<unsigned char*>(&MenuPcs) + 0x120))->Open(mesPtr[messageId + 8], 0x160, 0x20, 0x220, 0, -1, -1);
}

} // namespace

/*
 * --INFO--
 * PAL Address: 0x800e00a8
 * PAL Size: 4120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma push
#pragma optimization_level 3
void CChara::CModel::MogFurFrame(CGObject* gObject)
{
	int messageId = -1;
	const int debugPadLock = Pad.m_debugPadLock;
	const int heldButtons = (unsigned short)MogHeldButtons(debugPadLock);
	const int triggerButtons = (unsigned short)MogTriggerButtons(debugPadLock);
	const unsigned short rotateButtons = static_cast<unsigned short>((MogPadInt(debugPadLock, 64) == 0) ? MogHeldButtons(debugPadLock) : static_cast<short>(0));

	if (MogWork().m_started == 0) {
		if ((heldButtons & 0x100) != 0) {
			return;
		}
		MogWork().m_started = 1;
	}

	if (MogWork().m_frameCount == 0) {
		messageId = 0;
		MogWork().m_prevScoreA = Chara.MogFur().m_score[0];
		MogWork().m_prevScoreB = Chara.MogFur().m_score[1];
		MogWork().m_prevScoreC = Chara.MogFur().m_score[2];
	}

	if (MogWork().m_state == 0) {
		if ((rotateButtons & 1) != 0) {
			gObject->m_rotTargetY -= kYmEnvQuarter;
			if (gObject->m_currentAnimSlot < 0) {
				gObject->PlayAnim(1, 0, 0, -1, -1, 0);
			}
		} else if ((rotateButtons & 2) != 0) {
			gObject->m_rotTargetY += kYmEnvQuarter;
			if (gObject->m_currentAnimSlot < 0) {
				gObject->PlayAnim(1, 0, 0, -1, -1, 0);
			}
		} else if (gObject->m_currentAnimSlot >= 0) {
			gObject->CancelAnim(1);
		}

		if ((rotateButtons & 8) != 0) {
			MogWork().m_state = 1;
			gObject->PlayAnim(0x37, 1, 0, -1, -1, 0);
			messageId = 7;
		}
	} else if (MogWork().m_state == 1) {
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
			MogWork().m_state = 0;
		}
	}

	Chara.MogFur().m_cursorX = static_cast<int>(kYmEnvTen * MogPadFloat(debugPadLock, 36) +
	                                     static_cast<float>(static_cast<int>(Chara.MogFur().m_cursorX)));
	Chara.MogFur().m_cursorY = static_cast<int>(-(kYmEnvTen * MogPadFloat(debugPadLock, 40) -
	                                     static_cast<float>(static_cast<int>(Chara.MogFur().m_cursorY))));

	const int cursorXv = static_cast<int>(Chara.MogFur().m_cursorX);
	int cursorXc;
	if (cursorXv < 0) {
		cursorXc = 0;
	} else {
		cursorXc = 0x280;
		if (cursorXv <= 0x280) {
			cursorXc = cursorXv;
		}
	}
	Chara.MogFur().m_cursorX = cursorXc;
	const int cursorYv = static_cast<int>(Chara.MogFur().m_cursorY);
	int cursorYc;
	if (cursorYv < 0) {
		cursorYc = 0;
	} else {
		cursorYc = 0x1C0;
		if (cursorYv <= 0x1C0) {
			cursorYc = cursorYv;
		}
	}
	Chara.MogFur().m_cursorY = cursorYc;

	Mtx cameraMtx;
	PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);

	if ((heldButtons & 0x100) != 0) {
		if (Chara.MogFur().m_trackedCommandIndex != Chara.MogFur().m_commandIndex) {
			Chara.MogFur().m_trackedCommandIndex = Chara.MogFur().m_commandIndex;
			MogWork().m_pickTicks = 0;
			Sound.StopSe(MogWork().m_loopSeHandle);
			MogWork().m_loopSeHandle = 0;
		}
		int eraseMode = 0;
		int doPaint = 1;
		_GXColor brushColor;
		switch (Chara.MogFur().m_commandIndex) {
		case 0: {
			const _GXColor c = CColor(0xF, 4, 4, 2).color;
			brushColor = c;
			break;
		}
		case 1: {
			const _GXColor c = CColor(4, 8, 0xF, 2).color;
			brushColor = c;
			break;
		}
		case 2: {
			const _GXColor c = CColor(4, 0xF, 4, 2).color;
			brushColor = c;
			break;
		}
		case 3: {
			const _GXColor c = CColor(0xF, 0xF, 0xF, 4).color;
			brushColor = c;
			doPaint = (static_cast<int>(System.m_frameCounter) % 4) == 0;
			break;
		}
		case 4:
			{
				const _GXColor c = CColor(0, 0, 0, 2).color;
				brushColor = c;
			}
			eraseMode = 1;
			doPaint = (static_cast<int>(System.m_frameCounter) % 4) == 0;
			break;
		}
		_GXColor centerBefore;
		_GXColor centerAfter;
		Vec worldPos;

		CopyMogTextureFromChara(this);
		const _GXColor initColor = CColor(0xF, 0xF, 0xF, 0).color;
		centerAfter.r = initColor.r;
		centerAfter.g = initColor.g;
		centerAfter.b = initColor.b;
		centerAfter.a = initColor.a;
		centerBefore.r = initColor.r;
		centerBefore.g = initColor.g;
		centerBefore.b = initColor.b;
		centerBefore.a = initColor.a;
		int pickResult = PickFur(cameraMtx, brushColor, doPaint, eraseMode, &centerBefore, &centerAfter, &worldPos);
		CopyMogTextureToChara(this);
		Chara.CalcMogScore();

		if (pickResult >= 0) {
			MogWork().m_pickTicks++;

			int* prevScoreP = &MogWork().m_prevScoreA;
			int* scoreP = &Chara.MogFur().m_score[0];
			if (prevScoreP[0] + 5 <= scoreP[0]) {
				prevScoreP[0] = scoreP[0];
				messageId = 1;
			} else if (prevScoreP[0] - 5 > scoreP[0]) {
				prevScoreP[0] = scoreP[0];
				messageId = 6;
			}
			prevScoreP++;
			scoreP++;
			if (prevScoreP[0] + 5 <= scoreP[0]) {
				prevScoreP[0] = scoreP[0];
				messageId = 1;
			} else if (prevScoreP[0] - 5 > scoreP[0]) {
				prevScoreP[0] = scoreP[0];
				messageId = 6;
			}
			prevScoreP++;
			scoreP++;
			if (prevScoreP[0] + 5 <= scoreP[0]) {
				prevScoreP[0] = scoreP[0];
				messageId = 1;
			} else if (prevScoreP[0] - 5 > scoreP[0]) {
				prevScoreP[0] = scoreP[0];
				messageId = 6;
			}

			if (pickResult == 0) {
				MogWork().m_idleTicks++;
				if (MogWork().m_idleTicks == 0x3C && messageId == -1) {
					messageId = 3;
				} else if (MogWork().m_idleTicks == 0xF0 && messageId == -1) {
					messageId = 4;
				}
			} else {
				MogWork().m_idleTicks = 0;
			}

			if (doPaint != 0) {
				int particleNo = 0;
				int seId = 0;
				int emitParticle = ((static_cast<int>(System.m_frameCounter) % 2) == 0);
				int playGate = ((static_cast<int>(System.m_frameCounter) % 4) == 0);
				CColor particleColorObj(centerBefore);
				_GXColor& particleColor = particleColorObj.color;
				switch (Chara.MogFur().m_commandIndex) {
				case 0:
					MogWork().m_offColorTicks = 0;
					particleNo = 0x73;
					MogWork().m_eraseTicks = 0;
					particleColor = CColor(0xF, 4, 4, 2).color;
					break;
				case 1:
					MogWork().m_offColorTicks = 0;
					particleNo = 0x73;
					MogWork().m_eraseTicks = 0;
					particleColor = CColor(4, 8, 0xF, 2).color;
					break;
				case 2:
					MogWork().m_offColorTicks = 0;
					particleNo = 0x73;
					MogWork().m_eraseTicks = 0;
					particleColor = CColor(4, 0xF, 4, 2).color;
					break;
				case 3:
					MogWork().m_eraseTicks = 0;
					if ((((centerBefore.r < 0x0D) || (centerBefore.g < 0x0D)) || (centerBefore.b < 0x0D)) && (centerBefore.a != 0)) {
						MogWork().m_offColorTicks++;
					}
					seId = 0x249f4;
					particleNo = 0x74;
					emitParticle = ((static_cast<int>(System.m_frameCounter) % 8) == 0);
					playGate = ((static_cast<int>(System.m_frameCounter) % 16) == 0);
					break;
				case 4:
					MogWork().m_offColorTicks = 0;
					if ((doPaint != 0) && (centerBefore.a != 0) && (centerAfter.a == 0)) {
						MogWork().m_eraseTicks++;
					}
					emitParticle = 1;
					particleNo = 0x72;
					if (doPaint == 0) {
						particleColor.a = 0;
					}
					seId = 0x249f3;
					playGate = ((static_cast<int>(System.m_frameCounter) % 8) == 0);
					break;
				}

				if (emitParticle != 0) {
					CFlatRuntime2Storage().ResetParticleWork(particleNo | 0x100, 0);
					CFlatRuntime2Storage().SetParticleWorkPos(worldPos, kCharaFurDepthZero);
					const int particleIndex = CFlatRuntime2Storage().PutParticleWork();
					pppFVECTOR4 color = *reinterpret_cast<const pppFVECTOR4*>(sMogRadarTypeLabels);
					color.x = static_cast<float>(particleColor.r) / kCharaFurColorComponentScale;
					color.y = static_cast<float>(particleColor.g) / kCharaFurColorComponentScale;
					color.z = static_cast<float>(particleColor.b) / kCharaFurColorComponentScale;
					color.w = static_cast<float>(particleColor.a) / kCharaFurAlphaComponentScale;
					PartPcs.SetParColIdx(particleIndex, color);
				}
				if ((playGate != 0) && (seId != 0)) {
					Sound.PlaySe(seId, 0x40, 0x7F, 0);
				}

				if (MogWork().m_offColorTicks == 10) {
					if (messageId == -1) {
						messageId = 2;
					}
					MogWork().m_offColorTicks++;
				}
				if (MogWork().m_eraseTicks == 10) {
					if (messageId == -1) {
						messageId = 5;
					}
					MogWork().m_eraseTicks++;
				}
				if (MogWork().m_eraseTicks == 0x32) {
					if (messageId == -1) {
						messageId = 6;
					}
					MogWork().m_eraseTicks++;
				}

				if (Chara.MogFur().m_commandIndex < 3 && Chara.MogFur().m_commandIndex >= 0 && doPaint != 0
				    && MogWork().m_loopSeHandle == 0) {
					MogWork().m_loopSeHandle = Sound.PlaySe(0x249f2, 0x40, 0x7F, 0);
				}
			}
		}
	} else {
		if (Chara.MogFur().m_commandIndex < 3 && Chara.MogFur().m_commandIndex >= 0) {
			StopMogLoopSe(MogWork());
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
	MogWork().m_frameCount++;
}
#pragma pop

/*
 * --INFO--
 * PAL Address: 0x800e10c0
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#undef fur

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

/*
 * --INFO--
 * PAL Address: 0x800e1148
 * PAL Size: 292b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma push
#pragma opt_propagation off
#pragma global_optimizer off
void CChara::InitFurTexBuffer()
{
	MogFurState& fur = MogFur();
	int rowCount = 0;
	int row = 0;
	do {
		unsigned int inner = 0;
		int byteOffset = row << 1;
		int idx;
		for (idx = row; idx < row + 0x40; idx += 8) {
			int idxBase = inner + row;
			*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Chara.MogFur().m_texels) + byteOffset) = 0x7FFF;
			byteOffset += 0x10;
			Chara.MogFur().m_texels[idxBase + 1] = 0x7FFF;
			Chara.MogFur().m_texels[idxBase + 2] = 0x7FFF;
			Chara.MogFur().m_texels[idxBase + 3] = 0x7FFF;
			Chara.MogFur().m_texels[idxBase + 4] = 0x7FFF;
			Chara.MogFur().m_texels[idxBase + 5] = 0x7FFF;
			Chara.MogFur().m_texels[idxBase + 6] = 0x7FFF;
			Chara.MogFur().m_texels[idxBase + 7] = 0x7FFF;
			inner += 8;
		}
		rowCount++;
		row += 0x40;
	} while (rowCount < 0x40);

	fur.m_dirty = 0;
	Chara.MogFur().m_timestamp = System.m_frameCounter;
	memset(fur.m_score, 0, 0x40);
	CalcMogScore();
}
#pragma pop

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
#pragma push
#pragma opt_common_subs off
#pragma opt_propagation off
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
		int flagsBit = 1;
		unsigned int flagsTemp = m_flagsA0;
		m_flagsA0 = static_cast<unsigned char>(__rlwimi(flagsTemp, flagsBit, 6, 25, 25));
	}
}
#pragma pop

/*
 * --INFO--
 * PAL Address: 0x800e13fc
 * PAL Size: 3448b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma push
#pragma optimization_level 3
int CChara::CModel::PickFur(
    Mtx param_2, _GXColor brushColor, int doPaint, int mode, _GXColor* centerBefore, _GXColor* centerAfter, Vec* worldPos)
{
	if (m_flags10CBits.m_flag10C_40 == 0) {
		return -1;
	}
	register Vec* outWorldPos = worldPos;

	const double cursorXd = static_cast<float>(Chara.MogFur().m_cursorX);
	const double cursorYd = static_cast<float>(Chara.MogFur().m_cursorY);
	float hitU = kCharaFurDepthZero;
	float hitV = kCharaFurDepthZero;
	float nearestDepth = kCharaFurNoHitDepth;
	int hitAny = 0;
	unsigned int hitPaintable = 0;
	CVector hitViewPos;
	hitViewPos.Identity();
	Mtx44 screenMtx;
	PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
	const double negCursorY = -static_cast<double>(static_cast<float>(cursorYd) - kCharaFurScreenCenterY);

	FurMeshRaw* mesh = ModelMeshes(this);

	FurProjectedVertex verts[3];
	FurProjectedVertex incoming;
	Mtx44 invScreenMtx;
	Vec rayEndMem;
	Vec hitToBMem;
	Vec hitToCMem;
	Vec areaBCMem;
	Vec areaCAMem;
	volatile FurPickPointerTable ptrTable;
	volatile FurPickWorkPointers workPtrs;

	for (unsigned int meshIndex = 0; meshIndex < ModelMeshCount(this); meshIndex++, mesh++) {
		if (mesh->m_workPositions == 0) {
			continue;
		}
		if (((ModelMeshVisibleMask(this) >> meshIndex) & 1) == 0) {
			continue;
		}

		Mtx meshMtx;
		if (mesh->m_data->m_skinCount != 0) {
			PSMTXCopy(ModelWorldDrawMtx(this), meshMtx);
		} else {
			PSMTXConcat(ModelWorldDrawMtx(this), ModelNodes(this)[mesh->m_data->m_nodeIndex].m_mtx, meshMtx);
		}

		Mtx modelViewMtx;
		PSMTXConcat(reinterpret_cast<MtxPtr>(param_2), meshMtx, modelViewMtx);
		const unsigned int posGqr = ModelPosQuant(this);
		const int normGqr = ModelNormQuant(this);
		Chara.gqrInit(posGqr << 0x18 | 0x70000 | posGqr << 8 | 7,
		              normGqr << 0x18 | 0x70000 | normGqr << 8 | 7, 0xc070c07);

		ptrTable.m_rayEndA = reinterpret_cast<CVector*>(&rayEndMem);
		ptrTable.m_rayEndB = reinterpret_cast<CVector*>(&rayEndMem);
		ptrTable.m_hitToB1 = reinterpret_cast<CVector*>(&hitToBMem);
		ptrTable.m_hitToC1 = reinterpret_cast<CVector*>(&hitToCMem);
		ptrTable.m_areaBC1 = reinterpret_cast<CVector*>(&areaBCMem);
		ptrTable.m_areaCA1 = reinterpret_cast<CVector*>(&areaCAMem);
		ptrTable.m_hitToB2 = reinterpret_cast<CVector*>(&hitToBMem);
		ptrTable.m_hitToC2 = reinterpret_cast<CVector*>(&hitToCMem);
		ptrTable.m_areaBC2 = reinterpret_cast<CVector*>(&areaBCMem);
		ptrTable.m_areaCA2 = reinterpret_cast<CVector*>(&areaCAMem);

		FurDisplayListRaw* displayList = mesh->m_data->m_displayLists;
		int displayCount = mesh->m_data->m_displayListCount;
		while (--displayCount >= 0) {
			CMaterial* material = ModelMaterialSet(this)->m_materials[displayList->m_material];
			unsigned int paintableMaterial = 0;
			CTexture* pickTexture = material->GetFurPickTexture();
			if (pickTexture != 0 && pickTexture->m_format == 5) {
				paintableMaterial = 1;
			}

			const unsigned char* cursor = reinterpret_cast<const unsigned char*>(displayList->m_data);
			if ((cursor[0] & 7) == 0) {
				int remaining = displayList->m_size;
				unsigned char command;
				do {
				while (true) {
				if (remaining == 0) {
					goto displayDone;
				}
				command = cursor[0];
				const unsigned short count = *reinterpret_cast<const short*>(cursor + 1);
				cursor += 3;
				const int primitive = command & 0xF8;
				remaining -= static_cast<int>(static_cast<unsigned short>(count)) * 8 + 3;
				if (primitive != 0x90 && primitive != 0x98) {
					break;
				}

				workPtrs.m_rayEndc = ptrTable.m_rayEndA;
				CVector* rayEndP = ptrTable.m_rayEndB;
				workPtrs.m_hitToBc = ptrTable.m_hitToB1;
				workPtrs.m_hitToCc = ptrTable.m_hitToC1;
				workPtrs.m_areaBCc = ptrTable.m_areaBC1;
				workPtrs.m_areaCAc = ptrTable.m_areaCA1;
				CVector* hitToCP = ptrTable.m_hitToB2;
				workPtrs.m_hitToBw = ptrTable.m_hitToC2;
				workPtrs.m_areaBCw = ptrTable.m_areaBC2;
				workPtrs.m_areaCAw = ptrTable.m_areaCA2;

				for (unsigned int vertexIndex = 0; vertexIndex < count; vertexIndex++) {
					const unsigned short* indices = reinterpret_cast<const unsigned short*>(cursor);

					register const S16Vec* posPtr = &mesh->m_workPositions[indices[0]];
					register const unsigned char* uvPtr = mesh->m_data->m_uvs;
					register int uvOff = static_cast<unsigned int>(indices[3]) << 2;
					Vec localPos;
					float curUV[2];
					register Vec* localPosPtr = &localPos;
					register float* curUVPtr = curUV;
					register float posXY;
					register float posZ;
					register float uvST;
					asm {
						psq_l posXY, 0(posPtr), 0, 5
						psq_lx uvST, uvPtr, uvOff, 0, 7
						psq_l posZ, 4(posPtr), 1, 5
						psq_st uvST, 0(curUVPtr), 0, 0
						psq_st posXY, 0(localPosPtr), 0, 0
						psq_st posZ, 8(localPosPtr), 1, 0
					}
					float curU = curUV[0];
					float curV = curUV[1];

					Vec curViewPos;
					PSMTXMultVec(modelViewMtx, &localPos, &curViewPos);

					if (static_cast<double>(curViewPos.z) >= static_cast<double>(kCharaFurDepthZero)) {
						incoming.m_flagBits.m_projValid = 0;
					} else {
						Vec4d curClip;
						incoming.m_flagBits.m_projValid = 1;
						Math.MTX44MultVec4(screenMtx, &curViewPos, &curClip);
						const float invW = kCharaFurDepthScaleBase / curClip.w;
						incoming.m_clipX = curClip.x;
						incoming.m_clipY = curClip.y;
						incoming.m_clipZ = curClip.z;
						incoming.m_clipW = curClip.w;
						incoming.m_screenX = kCharaFurScreenCenterX * curClip.x * invW + kCharaFurScreenCenterX;
						incoming.m_screenY = kCharaFurScreenCenterY - kCharaFurScreenCenterY * curClip.y * invW;
					}
					incoming.m_viewPos = curViewPos;
					incoming.m_u = curU;
					incoming.m_v = curV;
					{
						int* d0 = reinterpret_cast<int*>(&verts[0]);
						int* s0 = reinterpret_cast<int*>(&verts[1]);
						int* s1 = reinterpret_cast<int*>(&verts[2]);
						int* si = reinterpret_cast<int*>(&incoming);
						d0[0] = s0[0]; d0[1] = s0[1]; d0[2] = s0[2]; d0[3] = s0[3];
						d0[4] = s0[4]; d0[5] = s0[5]; d0[6] = s0[6]; d0[7] = s0[7];
						d0[8] = s0[8]; d0[9] = s0[9]; d0[10] = s0[10];
						s0[0] = s1[0]; s0[1] = s1[1]; s0[2] = s1[2]; s0[3] = s1[3];
						s0[4] = s1[4]; s0[5] = s1[5]; s0[6] = s1[6]; s0[7] = s1[7];
						s0[8] = s1[8]; s0[9] = s1[9]; s0[10] = s1[10];
						s1[0] = si[0]; s1[1] = si[1]; s1[2] = si[2]; s1[3] = si[3];
						s1[4] = si[4]; s1[5] = si[5]; s1[6] = si[6]; s1[7] = si[7];
						s1[8] = si[8]; s1[9] = si[9]; s1[10] = si[10];
					}

					if ((primitive == 0x90 && static_cast<int>(vertexIndex) % 3 == 2) ||
					    (primitive == 0x98 && static_cast<int>(vertexIndex) >= 2)) {
						FurProjectedVertex* vp = &verts[0];
						int passed = 0;
						float depthAccum = kCharaFurDepthZero;
						for (int remainEdges = 3; remainEdges != 0; remainEdges--) {
							if (vp->m_flagBits.m_projValid == 0) {
								break;
							}
							int next = (passed + 1) % 3;
							const float edge =
							    (static_cast<float>(cursorYd) - vp->m_screenY) * (verts[next].m_screenX - vp->m_screenX) -
							    (static_cast<float>(cursorXd) - vp->m_screenX) * (verts[next].m_screenY - vp->m_screenY);
							if (primitive == 0x90 || (vertexIndex & 1) == 0) {
								vp->m_flagBits.m_edgeFlag = 0;
								if (edge > kCharaFurDepthZero) {
									break;
								}
							} else {
								vp->m_flagBits.m_edgeFlag = 1;
								if (edge < kCharaFurDepthZero) {
									break;
								}
							}
							depthAccum = depthAccum + vp->m_clipW;
							vp++;
							passed++;
						}

						float depth;
						if (passed != 3 || nearestDepth <= (depth = depthAccum / kCharaFurTriangleVertexCount)) {
							goto nextVertex;
						}

						hitAny = 1;
						PSMTX44Copy(screenMtx, invScreenMtx);
						C_MTX44Inverse(invScreenMtx, invScreenMtx);

						CVector rayStart;
						__ct__7CVectorFv(workPtrs.m_rayEndc);
						CVector rayStartInit(
						    (static_cast<float>(cursorXd) - kCharaFurScreenCenterX) / kCharaFurScreenCenterX,
						    static_cast<float>(negCursorY) / kCharaFurScreenCenterY, kCharaFurDepthZero);
						rayStart.x = rayStartInit.x;
						rayStart.y = rayStartInit.y;
						rayStart.z = rayStartInit.z;
						CVector rayEndInit(rayStartInit.x, rayStartInit.y, kCharaFurPickRayFarZ);
						rayEndP->x = rayEndInit.x;
						rayEndMem.y = rayEndInit.y;
						rayEndMem.z = rayEndInit.z;
						PSMTX44MultVec(invScreenMtx, rayStart, rayStart);
						PSMTX44MultVec(invScreenMtx, *rayEndP, *rayEndP);

						Vec ray;
						CVector raySub;
						PSVECSubtract(*rayEndP, rayStart, raySub);
						ray.x = raySub.x;
						ray.y = raySub.y;
						ray.z = raySub.z;

						CVector normal;
						CVector normalA;
						CVector normalB;
						PSVECCrossProduct(&verts[1].m_viewPos, &verts[0].m_viewPos, normalA);
						PSVECCrossProduct(&verts[2].m_viewPos, &verts[0].m_viewPos, normalB);
						PSVECCrossProduct(normalA, normalB, normal);
						if (verts[2].m_flagBits.m_edgeFlag != 0) {
							CVector normalNeg(-normal.x, -normal.y, -normal.z);
							normal.x = normalNeg.x;
							normal.y = normalNeg.y;
							normal.z = normalNeg.z;
						}
						normal.Normalize();

						Vec planeDelta;
						const CVector& vertA0 = CVector(verts[0].m_viewPos);
						CVector planeSub;
						PSVECSubtract(const_cast<CVector&>(vertA0), rayStart, planeSub);
						planeDelta.x = planeSub.x;
						planeDelta.y = planeSub.y;
						planeDelta.z = planeSub.z;
						const float rayDot = PSVECDotProduct(normal, &ray);
						const float planeDot = PSVECDotProduct(normal, &planeDelta);
						Vec scaledRay;
						PSVECScale(&ray, &scaledRay, planeDot / rayDot);
						PSVECAdd(rayStart, &scaledRay, hitViewPos);

						CVector hitToA;
						__ct__7CVectorFv(workPtrs.m_hitToBc);
						__ct__7CVectorFv(workPtrs.m_hitToCc);
						CVector areaAB;
						__ct__7CVectorFv(workPtrs.m_areaBCc);
						__ct__7CVectorFv(workPtrs.m_areaCAc);
						const CVector& vertA1 = CVector(verts[0].m_viewPos);
						CVector hitToASub;
						PSVECSubtract(const_cast<CVector&>(vertA1), hitViewPos, hitToASub);
						hitToA.x = hitToASub.x;
						hitToA.y = hitToASub.y;
						hitToA.z = hitToASub.z;
						const CVector& vertB = CVector(verts[1].m_viewPos);
						CVector hitToBSub;
						PSVECSubtract(const_cast<CVector&>(vertB), hitViewPos, hitToBSub);
						hitToCMem.y = hitToBSub.y;
						workPtrs.m_hitToBw->x = hitToBSub.x;
						hitToCMem.z = hitToBSub.z;
						const CVector& vertC = CVector(verts[2].m_viewPos);
						CVector hitToCSub;
						PSVECSubtract(const_cast<CVector&>(vertC), hitViewPos, hitToCSub);
						hitToCP->x = hitToCSub.x;
						hitToBMem.y = hitToCSub.y;
						hitToBMem.z = hitToCSub.z;

						PSVECCrossProduct(hitToA, *workPtrs.m_hitToBw, areaAB);
						PSVECCrossProduct(*workPtrs.m_hitToBw, *hitToCP, *workPtrs.m_areaBCw);
						PSVECCrossProduct(*hitToCP, hitToA, *workPtrs.m_areaCAw);
						const float magAB = PSVECMag(areaAB);
						const float magCA = PSVECMag(*workPtrs.m_areaCAw);
						const float magBC = PSVECMag(*workPtrs.m_areaBCw);
						const CVector& weightsInit = CVector(magBC, magCA, magAB);
						Vec weightsScale;
						CVector weights;
						PSVECScale(const_cast<CVector&>(weightsInit), &weightsScale, kCharaFurWeightScale);
						weights.x = weightsScale.x;
						weights.y = weightsScale.y;
						weights.z = weightsScale.z;
						PSVECScale(weights, weights,
						           kCharaFurDepthScaleBase / (weights.z + weights.x + weights.y));

						const float outU =
						    verts[2].m_u * weights.z + (verts[0].m_u * weights.x + verts[1].m_u * weights.y);
						const float outV =
						    verts[2].m_v * weights.z + (verts[0].m_v * weights.x + verts[1].m_v * weights.y);

						if (outWorldPos != 0) {
							outWorldPos->x = hitViewPos.x;
							outWorldPos->y = hitViewPos.y;
							outWorldPos->z = hitViewPos.z;
						}
						hitU = outU;
						hitV = outV;
						if (material->IsFurEnabled()) {
							hitPaintable = paintableMaterial;
							nearestDepth = depth;
						}
					}
nextVertex:
					cursor += 8;
				}
				}
				} while ((command & 0xF8) != 0);
displayDone:;
			}
			displayList++;
		}
	}

	if (doPaint != 0 && hitPaintable != 0) {
		CTexture* texture = FindMogFurTexture(this);
		if (texture != 0 && texture->m_format == 5 && nearestDepth != kCharaFurDepthZero) {
			unsigned short* furTexels = reinterpret_cast<unsigned short*>(texture->m_imageData);
			int furTexWidth = texture->m_width;
			int furTexHeight = texture->m_height;
			_GXColor paintColor = brushColor;
			_GXColor before;
			_GXColor after;
			brush(furTexels, furTexWidth, furTexHeight, hitU, hitV, mode, paintColor, &before, &after);
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

	if (kCharaFurNoHitDepth == nearestDepth) {
		goto noHitReturn;
	}
	return 1;
noHitReturn:
	return -(hitAny == 0);
}

#pragma pop
extern "C" {
unsigned char m_mogWork[0x2C];
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
#pragma push
#pragma opt_loop_invariants off
void brush(unsigned short* pixels, int width, int height, float fx, float fy, int mode, _GXColor targetColor, _GXColor* centerBefore, _GXColor* centerAfter)
{
	_GXColor defaultColor = CColor(0x0f, 0x0f, 0x0f, 0).color;
	*centerAfter = defaultColor;
	*centerBefore = *centerAfter;

	int texelCountBytes = width * height * 2;
	int centerX = (int)((float)width * fx);
	int centerY = (int)((float)height * fy);

	DCInvalidateRange(pixels, texelCountBytes);

	const int rowStride = width * 4;
	for (int dy = -2; dy <= 2; dy++) {
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

			const int sdx = dx >> 31;
			const int adx = (dx ^ sdx) - sdx;
			const int sdy = dy >> 31;
			const int ady = (dy ^ sdy) - sdy;
			distance = adx + ady;
			tileIndex = ((unsigned int)px % 4 + ((py % 4) * 4 + ((unsigned int)px / 4 * 0x10 + (py / 4) * rowStride))) * 2;
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
				unsigned int reduce = (targetColor.a * (4 - distance)) / 4;
				a = a - reduce;
				a = a < 0 ? 0 : a;
			} else {
				float k = (float)(7 - targetColor.a) / kCharaFurAlphaComponentScale + (float)(distance / 4);
				k = (1.0f < k) ? 1.0f : k;
				{
					float inv = 1.0f - k;
					r = (int)((float)r * k + (float)targetColor.r * inv);
					g = (int)((float)g * k + (float)targetColor.g * inv);
					b = (int)((float)b * k + (float)targetColor.b * inv);
				}
				r = (r < 0) ? 0 : (r > 0x0f ? 0x0f : r);
				g = (g < 0) ? 0 : (g > 0x0f ? 0x0f : g);
				b = (b < 0) ? 0 : (b > 0x0f ? 0x0f : b);
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
#pragma pop

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
	if (m_flags10CBits.m_flag10C_40 == 0) {
		return;
	}

	const int materialCount = ModelMaterialSet(this)->m_materials.GetSize();

	int hasFurMaterial = 0;
	for (int i = 0; i < materialCount; i++) {
		CMaterial* material = ModelMaterialSet(this)->m_materials[i];
		if (material->IsFurEnabled()) {
			hasFurMaterial = 1;
			break;
		}
	}
	if (!hasFurMaterial) {
		return;
	}

	float furDepth;
	CVector modelPos;
	CVector viewPos;
	modelPos.x = ModelDrawMtx(this)[0][3];
	modelPos.y = ModelDrawMtx(this)[1][3];
	modelPos.z = ModelDrawMtx(this)[2][3];
	PSMTXMultVec(viewMtx, reinterpret_cast<Vec*>(&modelPos), reinterpret_cast<Vec*>(&viewPos));
	if (kCharaFurViewDepthThreshold <= viewPos.z) {
		furDepth = kCharaFurDepthZero;
	} else {
		Vec4d clipPos;
		Math.MTX44MultVec4(CameraPcs.m_screenMatrix, reinterpret_cast<Vec*>(&viewPos), &clipPos);
		furDepth = -clipPos.z / clipPos.w;
	}

	const float lenScale = ModelFurLenScale(this);
	float furLength = lenScale * (kCharaFurDepthScaleBase - furDepth) + lenScale;
	float furStep = ModelFurStep(this);

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
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 0x0C);
	LightPcs.EnableLight(1, 1);
	GXSetZMode((u8)1, (GXCompare)3, (u8)0);
	const float shadeScale = kCharaFurShadeScale;
	const float furCurVal = ModelFurCur(this);
	GXSetChanMatColor(GX_COLOR0A0, CColor(static_cast<unsigned char>(shadeScale * furCurVal),
	                                static_cast<unsigned char>(shadeScale * furCurVal),
	                                static_cast<unsigned char>(shadeScale * furCurVal), 0xFF)
	                             .color);
	LightPcs.SetAmbientAlpha(ModelLightAlpha(this));
	GXSetNumIndStages(0);
	GXSetNumTevStages(2);
	GXSetTevDirect(GX_TEVSTAGE0);
	_GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
	_GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
	_GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_KONST, GX_CA_TEXA, GX_CA_ZERO);
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

	const int posQuant = ModelPosQuant(this) & 0xFF;
	const int normQuant = ModelNormQuant(this) & 0xFF;
	int prevExtraTexture = -1;
	int prevExtraTextureFormat = -1;

	FurMeshRaw* mesh = ModelMeshes(this);

	for (unsigned int meshIndex = 0; meshIndex < ModelMeshCount(this); meshIndex++, mesh++) {
		if (mesh->m_workPositions == 0) {
			continue;
		}
		if (((ModelMeshVisibleMask(this) >> meshIndex) & 1) == 0) {
			continue;
		}

		Mtx meshMtx;
		if (mesh->m_data->m_skinCount != 0) {
			PSMTXCopy(ModelWorldDrawMtx(this), meshMtx);
		} else {
			PSMTXConcat(ModelWorldDrawMtx(this), ModelNodes(this)[mesh->m_data->m_nodeIndex].m_mtx, meshMtx);
		}

		int shadowCount = 0;
		CMaterial* shadowMaterials[2];
		MtxPtr shadowMatrices[2];
		if (shadowPass != 0) {
			*reinterpret_cast<unsigned long long*>(shadowMaterials) = g_chara_fur_1;
			*reinterpret_cast<unsigned long long*>(shadowMatrices) = g_chara_fur_2;
			shadowCount = MaterialMan.GetCharaShadow(2, shadowMaterials, shadowMatrices, reinterpret_cast<Vec*>(&modelPos), kCharaFurShadowRange, kCharaFurShadowFade, 0);
			CMaterial** shadowMatP = shadowMaterials;
			MtxPtr* shadowMtxP = shadowMatrices;
			int shadowTexMtxBase = 0;
			for (unsigned int shadowIndex = 0; shadowIndex < shadowCount; shadowIndex++) {
				const int shadowTexMap = shadowIndex + 3;
				const int shadowTexMtxId = shadowTexMtxBase + 0x21;
				TextureMan.SetTexture(static_cast<GXTexMapID>(shadowTexMap), (*shadowMatP)->GetTexture(0));

				Mtx shadowTexMtx;
				PSMTXConcat(*shadowMtxP, meshMtx, shadowTexMtx);
				GXLoadTexMtxImm(shadowTexMtx, shadowTexMtxId, GX_MTX3x4);
				GXSetTexCoordGen2(static_cast<GXTexCoordID>(shadowTexMap), GX_TG_MTX3x4, GX_TG_POS,
				                  shadowTexMtxId, GX_FALSE, GX_PTIDENTITY);
				shadowTexMtxBase += 3;
				shadowMatP++;
				shadowMtxP++;
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
		int displayCount = mesh->m_data->m_displayListCount - 1;
		for (; displayCount >= 0; displayCount--, displayList++) {
			CMaterial* material = ModelMaterialSet(this)->m_materials[displayList->m_material];
			if (!material->IsFurEnabled()) {
				continue;
			}

			TextureMan.SetTexture(GX_TEXMAP0, material->GetTexture(0));
			int hasExtraTexture;
			int extraTextureFormat;
			if (material->GetTextureIndex(1) != -1) {
				CTexture* extraTexture = material->GetTexture(1);
				hasExtraTexture = 1;
				TextureMan.SetTexture(GX_TEXMAP2, extraTexture);
				extraTextureFormat = extraTexture->m_format;
			} else {
				hasExtraTexture = 0;
				extraTextureFormat = -1;
			}

			if (prevExtraTexture != hasExtraTexture || prevExtraTextureFormat != extraTextureFormat) {
				prevExtraTexture = hasExtraTexture;
				prevExtraTextureFormat = extraTextureFormat;
				GXSetTevDirect(GX_TEVSTAGE0);
				_GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
				_GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
				_GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_KONST, GX_CA_TEXA, GX_CA_ZERO);
				_GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				_GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				_GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);

				int tevStage = 1;
				for (int shadowStage = 0; shadowStage < shadowCount; shadowStage++, tevStage++) {
					GXSetTevDirect(static_cast<GXTevStageID>(tevStage));
					_GXSetTevSwapMode(static_cast<GXTevStageID>(tevStage), GX_TEV_SWAP0, GX_TEV_SWAP0);
					_GXSetTevColorIn(static_cast<GXTevStageID>(tevStage), GX_CC_CPREV, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
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
						_GXSetTevColorOp(static_cast<GXTevStageID>(tevStageCount), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
						                 GX_TRUE, GX_TEVPREV);
						_GXSetTevAlphaOp(static_cast<GXTevStageID>(tevStageCount), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
						                 GX_TRUE, GX_TEVPREV);
					} else {
						_GXSetTevColorIn(static_cast<GXTevStageID>(tevStageCount), GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO,
						                 GX_CC_CPREV);
						_GXSetTevAlphaIn(static_cast<GXTevStageID>(tevStageCount), GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA,
						                 GX_CA_ZERO);
						_GXSetTevColorOp(static_cast<GXTevStageID>(tevStageCount), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
						                 GX_TRUE, GX_TEVPREV);
						_GXSetTevAlphaOp(static_cast<GXTevStageID>(tevStageCount), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
						                 GX_TRUE, GX_TEVPREV);
					}
					_GXSetTevOrder(static_cast<GXTevStageID>(tevStageCount), GX_TEXCOORD2, GX_TEXMAP2, GX_COLOR_NULL);
					tevStageCount++;
					GXSetNumTexGens(static_cast<u8>(shadowCount + 3));
					GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, GX_PTIDENTITY);
					GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, 0x1E, GX_FALSE, GX_PTIDENTITY);
					GXSetTexCoordGen2(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, GX_PTIDENTITY);
				}
				GXSetNumTevStages(static_cast<u8>(tevStageCount));
			}

			if ((reinterpret_cast<const unsigned char*>(displayList->m_data)[0] & 7) != 0) {
				continue;
			}

			for (int layer = 0; layer < 8; layer++) {
				register float shellReg = static_cast<float>(static_cast<int>(layer)) * 0.125f * furLength;
				GXTexObj texObj;
				void* texData = reinterpret_cast<unsigned char*>(*reinterpret_cast<void**>(&m_height)) + (layer * 0x4000);
				GXInitTexObj(&texObj, texData, 0x80, 0x80, GX_TF_IA4, GX_REPEAT, GX_REPEAT, GX_FALSE);
				GXLoadTexObj(&texObj, GX_TEXMAP1);

				{
					register const FurMeshRaw* meshReg = mesh;
					register int remainingReg = displayList->m_size;
					register const unsigned char* cursorReg =
					    reinterpret_cast<const unsigned char*>(displayList->m_data);
					register int cmdReg;
					register int countReg;
					Vec posScratch;
					register float* psPtr = reinterpret_cast<float*>(&posScratch);
					asm {
						b _furChk
					_furCmd:
						lbz r3, 0x0(cursorReg)
						lhz r0, 0x1(cursorReg)
						addi cursorReg, cursorReg, 0x3
						rlwinm r3, r3, 0, 24, 28
						clrlslwi r4, r0, 16, 3
						mr countReg, r0
						addi r0, r4, 0x3
						cmpwi r3, 0x90
						mr cmdReg, cursorReg
						subf remainingReg, r0, remainingReg
						beq _furBegin
						cmpwi r3, 0x98
						bne _furSkip
					_furBegin:
						clrlwi r5, countReg, 16
						li r4, 0x0
						bl GXBegin
						cmpwi countReg, 0x0
						mr r3, countReg
						lis r4, 0xcc01
						beq _furEnd
						srwi. r0, countReg, 1
						mtctr r0
						beq _furOddInit
					_furPair:
						lhz r5, 0x0(cmdReg)
						lhz r0, 0x2(cmdReg)
						mulli r6, r5, 0x6
						lwz r7, 0xc(meshReg)
						lwz r5, 0x10(meshReg)
						mulli r0, r0, 0x6
						add r6, r7, r6
						add r5, r5, r0
						psq_l f0, 0x0(r5), 0, 6
						psq_l f1, 0x0(r6), 0, 5
						psq_l f2, 0x4(r5), 1, 6
						psq_l f3, 0x4(r6), 1, 5
						ps_madd f0, f0, shellReg, f1
						ps_madd f2, f2, shellReg, f3
						psq_st f0, 0(psPtr), 0, 0
						lfs f0, 0(psPtr)
						psq_st f2, 8(psPtr), 1, 0
						lfs f1, 4(psPtr)
						stfs f0, -0x8000(r4)
						lfs f0, 8(psPtr)
						stfs f1, -0x8000(r4)
						stfs f0, -0x8000(r4)
						lhz r0, 0x2(cmdReg)
						sth r0, -0x8000(r4)
						lhz r0, 0x6(cmdReg)
						sth r0, -0x8000(r4)
						lhz r5, 0x8(cmdReg)
						lhz r0, 0xa(cmdReg)
						mulli r6, r5, 0x6
						lwz r7, 0xc(meshReg)
						lwz r5, 0x10(meshReg)
						mulli r0, r0, 0x6
						add r6, r7, r6
						add r5, r5, r0
						psq_l f0, 0x0(r5), 0, 6
						psq_l f1, 0x0(r6), 0, 5
						psq_l f2, 0x4(r5), 1, 6
						psq_l f3, 0x4(r6), 1, 5
						ps_madd f0, f0, shellReg, f1
						ps_madd f2, f2, shellReg, f3
						psq_st f0, 0(psPtr), 0, 0
						lfs f0, 0(psPtr)
						psq_st f2, 8(psPtr), 1, 0
						lfs f1, 4(psPtr)
						stfs f0, -0x8000(r4)
						lfs f0, 8(psPtr)
						stfs f1, -0x8000(r4)
						stfs f0, -0x8000(r4)
						lhz r0, 0xa(cmdReg)
						sth r0, -0x8000(r4)
						lhz r0, 0xe(cmdReg)
						addi cmdReg, cmdReg, 0x10
						sth r0, -0x8000(r4)
						bdnz _furPair
						andi. r3, r3, 0x1
						beq _furEnd
					_furOddInit:
						mtctr r3
					_furOdd:
						lhz r5, 0x0(cmdReg)
						lhz r0, 0x2(cmdReg)
						mulli r6, r5, 0x6
						lwz r7, 0xc(meshReg)
						lwz r5, 0x10(meshReg)
						mulli r0, r0, 0x6
						add r6, r7, r6
						add r5, r5, r0
						psq_l f0, 0x0(r5), 0, 6
						psq_l f1, 0x0(r6), 0, 5
						psq_l f2, 0x4(r5), 1, 6
						psq_l f3, 0x4(r6), 1, 5
						ps_madd f0, f0, shellReg, f1
						ps_madd f2, f2, shellReg, f3
						psq_st f0, 0(psPtr), 0, 0
						lfs f0, 0(psPtr)
						psq_st f2, 8(psPtr), 1, 0
						lfs f1, 4(psPtr)
						stfs f0, -0x8000(r4)
						lfs f0, 8(psPtr)
						stfs f1, -0x8000(r4)
						stfs f0, -0x8000(r4)
						lhz r0, 0x2(cmdReg)
						sth r0, -0x8000(r4)
						lhz r0, 0x6(cmdReg)
						addi cmdReg, cmdReg, 0x8
						sth r0, -0x8000(r4)
						bdnz _furOdd
						b _furEnd
					_furSkip:
						cmpwi r3, 0x0
						beq _furDone
						b _furChk2
					_furEnd:
						mr cursorReg, cmdReg
					_furChk:
						cmpwi remainingReg, 0x0
						bne _furCmd
					_furChk2:
					_furDone:
					}
				}
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
	if (*reinterpret_cast<void**>(&m_height) != 0) {
		Memory.Free(*reinterpret_cast<void**>(&m_height));
		*reinterpret_cast<void**>(&m_height) = 0;
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
static inline CColor& FurColorLval(const CColor& c)
{
	return const_cast<CColor&>(c);
}

#pragma push
#pragma opt_common_subs off
#pragma opt_lifetimes off
void CChara::makeFurTex()
{
	CHairSet hairSet[0x20];

	static CColor color[2] = { FurColorLval(CColor(0x80, 0x80, 0x80, 0xFF)),
		                       FurColorLval(CColor(0xF0, 0xF0, 0xF0, 0)) };
#define furBaseColor (color[0])
#define furTipColor (color[1])
	static CColor colorr[2] = { FurColorLval(CColor(0, 0, 0, 0)), FurColorLval(CColor(8, 8, 8, 0)) };
#define furNoiseBase (colorr[0])
#define furNoiseRange (colorr[1])
	static Vec vel = CVector(kCharaFurDepthZero, FLOAT_80331160, kCharaFurDepthZero);
	static Vec velr = CVector(kCharaFurDepthZero, kYmEnvQuarter, kCharaFurDepthZero);
	static Vec accel = CVector(kCharaFurDepthZero, kCharaFurDepthZero, kCharaFurDepthZero);
	static Vec accelr = CVector(kCharaFurDepthZero, kCharaFurDepthZero, kCharaFurDepthZero);

	m_seed = 0;

	float scaleBase = kCharaFurDepthScaleBase;
	float randScale = FLOAT_80331164;
	float depthThreshold = kCharaFurViewDepthThreshold;
	float weightScale = kCharaFurWeightScale;

	for (int i = 0; i < 0x20; i++) {
		float velRandScale = FurRandScaleL(scaleBase, randScale, depthThreshold);
		CVector velScaleOut;
		PSVECScale(&velr, velScaleOut, velRandScale);
		Vec velScaled;
		velScaled.x = velScaleOut.x;
		velScaled.y = velScaleOut.y;
		velScaled.z = velScaleOut.z;
		CVector velAddOut;
		PSVECAdd(&vel, &velScaled, velAddOut);
		hairSet[i].m_vec0.x = velAddOut.x;
		hairSet[i].m_vec0.y = velAddOut.y;
		hairSet[i].m_vec0.z = velAddOut.z;

		float accelRandScale = FurRandScaleL(scaleBase, randScale, depthThreshold);
		CVector accelScaleOut;
		PSVECScale(&accelr, accelScaleOut, accelRandScale);
		Vec accelScaled;
		accelScaled.x = accelScaleOut.x;
		accelScaled.y = accelScaleOut.y;
		accelScaled.z = accelScaleOut.z;
		CVector accelAddOut;
		PSVECAdd(&accel, &accelScaled, accelAddOut);
		hairSet[i].m_vec1.x = accelAddOut.x;
		hairSet[i].m_vec1.y = accelAddOut.y;
		hairSet[i].m_vec1.z = accelAddOut.z;

		const CColor& noise0 = FurNoiseColor(furBaseColor, furNoiseBase, FurRandScaleL(scaleBase, randScale, depthThreshold));
		hairSet[i].m_colors[0].color.r = noise0.color.r;
		hairSet[i].m_colors[0].color.g = noise0.color.g;
		hairSet[i].m_colors[0].color.b = noise0.color.b;
		hairSet[i].m_colors[0].color.a = noise0.color.a;
		const CColor& noise1 = FurNoiseColor(furTipColor, furNoiseRange, FurRandScaleL(scaleBase, randScale, depthThreshold));
		hairSet[i].m_colors[1].color.r = noise1.color.r;
		hairSet[i].m_colors[1].color.g = noise1.color.g;
		hairSet[i].m_colors[1].color.b = noise1.color.b;
		hairSet[i].m_colors[1].color.a = noise1.color.a;

		float endY = hairSet[i].m_vec0.y + weightScale * hairSet[i].m_vec1.y;
		if (m_height < endY) {
			m_height = endY;
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
	GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPOT);
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
	posMtx[1][2] = FLOAT_8033116C * (kCharaFurViewDepthThreshold / m_height);
	posMtx[2][2] = kCharaFurDepthZero;
	posMtx[0][3] = kCharaFurDepthZero;
	posMtx[1][3] = kCharaFurDepthZero;
	posMtx[2][3] = kCharaFurDepthZero;

	Mtx44 projection;
	PSMTX44Identity(projection);
	GXSetProjection(projection, GX_ORTHOGRAPHIC);

	m_pTexBuf = Memory._Alloc(0x20000, CharaPcs.m_viewerAnimStage, const_cast<char*>(s_chara_fur_cpp), 0xE9, 0);
	DCInvalidateRange(m_pTexBuf, 0x20000);

	float weightScale2 = kCharaFurWeightScale;
	float scaleBase2 = kCharaFurDepthScaleBase;
	float quarterStep = kYmEnvQuarter;
	float randScale2 = FLOAT_80331164;
	float depthThr2 = kCharaFurViewDepthThreshold;
	float layerStep = FLOAT_8033115C;

	for (int layer = 0; layer < 8; layer++) {
		posMtx[2][3] -= m_height * layerStep;
		GXLoadPosMtxImm(posMtx, GX_PNMTX0);
		GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);

		float layerFactor = static_cast<float>(layer) * layerStep;
		layerFactor = layerFactor * layerFactor;

		CColor tipPartTmp;
		tipPartTmp.color.r = static_cast<unsigned char>(static_cast<int>(furTipColor.color.r * layerFactor));
		tipPartTmp.color.g = static_cast<unsigned char>(static_cast<int>(furTipColor.color.g * layerFactor));
		tipPartTmp.color.b = static_cast<unsigned char>(static_cast<int>(furTipColor.color.b * layerFactor));
		tipPartTmp.color.a = static_cast<unsigned char>(static_cast<int>(furTipColor.color.a * layerFactor));
		CColor tipPart = tipPartTmp;

		CColor basePartTmp;
		basePartTmp.color.r =
		    static_cast<unsigned char>(static_cast<int>(furBaseColor.color.r * (scaleBase2 - layerFactor)));
		basePartTmp.color.g =
		    static_cast<unsigned char>(static_cast<int>(furBaseColor.color.g * (scaleBase2 - layerFactor)));
		basePartTmp.color.b =
		    static_cast<unsigned char>(static_cast<int>(furBaseColor.color.b * (scaleBase2 - layerFactor)));
		basePartTmp.color.a =
		    static_cast<unsigned char>(static_cast<int>(furBaseColor.color.a * (scaleBase2 - layerFactor)));
		CColor basePart = basePartTmp;

		CColor layerColorTmp;
		layerColorTmp.color.r = static_cast<unsigned char>(basePart.color.r + tipPart.color.r);
		layerColorTmp.color.g = static_cast<unsigned char>(basePart.color.g + tipPart.color.g);
		layerColorTmp.color.b = static_cast<unsigned char>(basePart.color.b + tipPart.color.b);
		layerColorTmp.color.a = static_cast<unsigned char>(basePart.color.a + tipPart.color.a);
		CColor layerColor = layerColorTmp;
		CColor clearColor(layerColor);
		clearColor.color.a = 0;
		Graphic.SetCopyClear(clearColor.color, 0xFFFFFF);
		GXCopyTex(static_cast<unsigned char*>(m_pTexBuf) + layer * 0x4000, GX_TRUE);
		GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);

		m_seed = 0;
		for (int hair = 0; hair < 0x4000; hair++) {
			GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);

			float rootX = scaleBase2 * (randScale2 * static_cast<float>(static_cast<int>(FurRandNext())) + depthThr2);
			float rootZ = scaleBase2 * (randScale2 * static_cast<float>(static_cast<int>(FurRandNext())) + depthThr2);
			CVector rootTmp(rootX, kCharaFurDepthZero, rootZ);
			CVector root = rootTmp;

			m_seed = m_seed * 0x41C64E6D + 0x3039;
			CHairSet& src = hairSet[(m_seed >> 16) & 0x1F];

			float t = kCharaFurDepthZero;
			for (int v = 0; v < 5; v++) {
				float t2 = t * t;
				CVector accelScaleOut;
				PSVECScale(src.m_vec1, accelScaleOut, weightScale2 * t2);
				Vec accelTerm;
				accelTerm.x = accelScaleOut.x;
				accelTerm.y = accelScaleOut.y;
				accelTerm.z = accelScaleOut.z;
				CVector velScaleOut;
				PSVECScale(src.m_vec0, velScaleOut, t);
				Vec velTerm;
				velTerm.x = velScaleOut.x;
				velTerm.y = velScaleOut.y;
				velTerm.z = velScaleOut.z;
				CVector addOut1;
				PSVECAdd(root, &velTerm, addOut1);
				Vec tmp;
				tmp.x = addOut1.x;
				tmp.y = addOut1.y;
				tmp.z = addOut1.z;
				CVector pos;
				PSVECAdd(&tmp, &accelTerm, pos);
				float px = pos.x;
				float py = pos.y;
				float pz = pos.z;

				CColor tipPartTmp;
				tipPartTmp.color.r = static_cast<unsigned char>(static_cast<int>(src.m_colors[1].color.r * t2));
				tipPartTmp.color.g = static_cast<unsigned char>(static_cast<int>(src.m_colors[1].color.g * t2));
				tipPartTmp.color.b = static_cast<unsigned char>(static_cast<int>(src.m_colors[1].color.b * t2));
				tipPartTmp.color.a = static_cast<unsigned char>(static_cast<int>(src.m_colors[1].color.a * t2));
				CColor tipPart = tipPartTmp;

				CColor basePartTmp;
				basePartTmp.color.r =
				    static_cast<unsigned char>(static_cast<int>(src.m_colors[0].color.r * (scaleBase2 - t2)));
				basePartTmp.color.g =
				    static_cast<unsigned char>(static_cast<int>(src.m_colors[0].color.g * (scaleBase2 - t2)));
				basePartTmp.color.b =
				    static_cast<unsigned char>(static_cast<int>(src.m_colors[0].color.b * (scaleBase2 - t2)));
				basePartTmp.color.a =
				    static_cast<unsigned char>(static_cast<int>(src.m_colors[0].color.a * (scaleBase2 - t2)));
				CColor basePart = basePartTmp;

				CColor colorTmp;
				colorTmp.color.r = static_cast<unsigned char>(basePart.color.r + tipPart.color.r);
				colorTmp.color.g = static_cast<unsigned char>(basePart.color.g + tipPart.color.g);
				colorTmp.color.b = static_cast<unsigned char>(basePart.color.b + tipPart.color.b);
				colorTmp.color.a = static_cast<unsigned char>(basePart.color.a + tipPart.color.a);
				CColor colorCopy = colorTmp;
				CColor color = colorCopy;
				GXWGFifo.f32 = px;
				GXWGFifo.f32 = py;
				GXWGFifo.f32 = pz;
				GXWGFifo.u32 = *reinterpret_cast<unsigned int*>(&color.color);
				t += quarterStep;
			}

			GXBegin(GX_POINTS, GX_VTXFMT0, 5);
			t = kCharaFurDepthZero;
			for (int v = 0; v < 5; v++) {
				float t2 = t * t;
				CVector accelScaleOut;
				PSVECScale(src.m_vec1, accelScaleOut, weightScale2 * t2);
				Vec accelTerm;
				accelTerm.x = accelScaleOut.x;
				accelTerm.y = accelScaleOut.y;
				accelTerm.z = accelScaleOut.z;
				CVector velScaleOut;
				PSVECScale(src.m_vec0, velScaleOut, t);
				Vec velTerm;
				velTerm.x = velScaleOut.x;
				velTerm.y = velScaleOut.y;
				velTerm.z = velScaleOut.z;
				CVector addOut1;
				PSVECAdd(root, &velTerm, addOut1);
				Vec tmp;
				tmp.x = addOut1.x;
				tmp.y = addOut1.y;
				tmp.z = addOut1.z;
				CVector pos;
				PSVECAdd(&tmp, &accelTerm, pos);
				float px = pos.x;
				float py = pos.y;
				float pz = pos.z;

				CColor tipPartTmp;
				tipPartTmp.color.r = static_cast<unsigned char>(static_cast<int>(src.m_colors[1].color.r * t2));
				tipPartTmp.color.g = static_cast<unsigned char>(static_cast<int>(src.m_colors[1].color.g * t2));
				tipPartTmp.color.b = static_cast<unsigned char>(static_cast<int>(src.m_colors[1].color.b * t2));
				tipPartTmp.color.a = static_cast<unsigned char>(static_cast<int>(src.m_colors[1].color.a * t2));
				CColor tipPart = tipPartTmp;

				CColor basePartTmp;
				basePartTmp.color.r =
				    static_cast<unsigned char>(static_cast<int>(src.m_colors[0].color.r * (scaleBase2 - t2)));
				basePartTmp.color.g =
				    static_cast<unsigned char>(static_cast<int>(src.m_colors[0].color.g * (scaleBase2 - t2)));
				basePartTmp.color.b =
				    static_cast<unsigned char>(static_cast<int>(src.m_colors[0].color.b * (scaleBase2 - t2)));
				basePartTmp.color.a =
				    static_cast<unsigned char>(static_cast<int>(src.m_colors[0].color.a * (scaleBase2 - t2)));
				CColor basePart = basePartTmp;

				CColor colorTmp;
				colorTmp.color.r = static_cast<unsigned char>(basePart.color.r + tipPart.color.r);
				colorTmp.color.g = static_cast<unsigned char>(basePart.color.g + tipPart.color.g);
				colorTmp.color.b = static_cast<unsigned char>(basePart.color.b + tipPart.color.b);
				colorTmp.color.a = static_cast<unsigned char>(basePart.color.a + tipPart.color.a);
				CColor colorCopy = colorTmp;
				CColor color = colorCopy;
				GXWGFifo.f32 = pz;
				GXWGFifo.f32 = py;
				GXWGFifo.f32 = px;
				GXWGFifo.u32 = *reinterpret_cast<unsigned int*>(&color.color);
				t += quarterStep;
			}
		}

		GXCopyTex(static_cast<unsigned char*>(m_pTexBuf) + layer * 0x4000, GX_TRUE);
	}

	GXPixModeSync();
	Graphic.SetViewport();
	Graphic.SetCopyClear(savedCopyClear, 0xFFFFFF);
	GXSetTexCopySrc(0, 0, 0x280, 0x1C0);
	GXCopyTex(Graphic.m_scratchTextureBuffer, GX_TRUE);
	Graphic._WaitDrawDone(const_cast<char*>(s_chara_fur_cpp), 0x138);
	if (m_pDisplayList != 0) {
		Memory.Free(m_pDisplayList);
		m_pDisplayList = 0;
	}
	Graphic.SetViewport();
	Graphic.SetStdPixelFmt();
	GXSetAlphaUpdate(GX_FALSE);
}
#undef furBaseColor
#undef furTipColor
#undef furNoiseBase
#undef furNoiseRange
#pragma pop


/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int nearColor(CColor src, CColor ref)
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
inline void GXSetTexCoordGen(void)
{
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
}

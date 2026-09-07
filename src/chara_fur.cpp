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

extern const char sYmEnvMapLabel[] = "MAP";
extern const char sYmEnvMonsterLabel[] = "MON";
extern const char sYmEnvScoreLabel[] = "SCO";
extern const char sYmEnvTreeLabel[] = "TRE";
extern const char sYmEnvSeparator[4] = "|\n";
extern const double kYmEnvRadToDeg;
extern const float kYmEnvDefaultScale;
extern const float kYmEnvQuarter;
extern const float kCharaFurDepthZero;
extern const float kYmEnvTen;
extern const char sMogFurTextureName[] = "n915m_2";
extern const float kCharaFurColorComponentScale;
extern const float kCharaFurAlphaComponentScale;
extern const float kCharaFurNoHitDepth;
extern const float kCharaFurScreenCenterY;
extern const float kCharaFurDepthScaleBase;
extern const float kCharaFurScreenCenterX;
extern const float kCharaFurTriangleVertexCount;
extern const float kCharaFurPickRayFarZ;
extern const float kCharaFurWeightScale;
extern const float kCharaFurViewDepthThreshold;
extern const float kCharaFurShadeScale;
extern const float kCharaFurShadowRange;
extern const float kCharaFurShadowFade;
extern const float FLOAT_8033115C;
extern const float FLOAT_80331160;
extern const float FLOAT_80331164;
extern const float FLOAT_80331168;
extern const float FLOAT_8033116C;

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
extern "C" char lbl_801DB648[];
struct MogWorkState
{
    int m_state;
    int m_frameCount;
    int m_pickTicks;
    int m_idleTicks;
    int m_offColorTicks;
    int m_eraseTicks;
    int m_prevScore[3];
    int m_loopSeHandle;
    int m_started;
};

STATIC_ASSERT(sizeof(MogWorkState) == 0x2C);
extern MogWorkState m_mogWork;
static float m_height;
static void* m_pDisplayList;
static void* m_pTexBuf;
static unsigned int m_seed;

namespace {

typedef CChara::CMesh::CDisplayList FurDisplayListRaw;
typedef CChara::CMesh::CRefData FurMeshRefRaw;
typedef CChara::CMesh FurMeshRaw;

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
 * EN Address: 0x80101240
 * EN Size: 728b
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::TimeMogFur()
{
	const int frameCounter = static_cast<int>(System.m_frameCounter);

	if (MogFur().m_timestamp + 0x1A5E0 < frameCounter) {
		MogFur().m_timestamp = frameCounter;
		if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
			System.Printf(const_cast<char*>(sYmEnvSeparator));
		}
		if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
			System.Printf(sMogRadarDebugFormatBlock);
		}
		if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
			System.Printf(const_cast<char*>(sYmEnvSeparator));
		}
	}

	unsigned short* const texels = MogFur().m_texels;
	memset(MogFur().m_score, 0, 0x40);

	for (int y = 0; y < 0x40; y++) {
		for (int x = 0; x < 0x40; x++) {
			int tileIndex = (y / 4) * 0x100 + (x / 4) * 0x10 + (y % 4) * 4 + (x % 4);
			unsigned short packed = texels[tileIndex];
			int a = (packed >> 12) & 7;
			int baseLight = 7 - a;
			int r = ((packed >> 8) & 0xF) + 4 + baseLight;
			int g = ((packed >> 4) & 0xF) + 4 + baseLight;
			int b = (packed & 0xF) + 4 + baseLight;
			r = r < 0xF ? r : 0xF;
			g = g < 0xF ? g : 0xF;
			b = b < 0xF ? b : 0xF;
			a += 2;
			a = a < 7 ? a : 7;
			texels[tileIndex] = static_cast<unsigned short>((a << 12) | (r << 8) | (g << 4) | b);
		}
	}

	CalcMogScore();
}

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

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 8b
 * EN Address: 0x800FC56C
 * EN Size: 8b
 * JP Address: TODO
 * JP Size: TODO
 */
static inline void mySrand(int seed)
{
	m_seed = seed;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 44b
 * EN Address: 0x800FC574
 * EN Size: 48b
 * JP Address: TODO
 * JP Size: TODO
 */
static inline int myRand(int range)
{
	m_seed = m_seed * 0x41C64E6D + 0x3039;
	return (m_seed >> 16) % range;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 144b
 * EN Address: 0x800FC5A4
 * EN Size: 124b
 * JP Address: TODO
 * JP Size: TODO
 */
static inline float myRandFPM(float scale)
{
	return scale * ((2.0f / 32767.0f) * static_cast<float>(myRand(32767)) - 1.0f);
}

static void brush(unsigned short*, int, int, float, float, int, _GXColor, _GXColor*, _GXColor*);

namespace {

static inline bool HasDebugPadOverride(int debugPadLock)
{
	return (debugPadLock != 0) || (Pad.m_debugPadPort != -1);
}

static inline int MogPadIndex(int padIndex)
{
	return Pad.m_debugPadPort == padIndex ? 0 : padIndex;
}

static inline unsigned short MogHeldButtons(int debugPadLock)
{
	if (HasDebugPadOverride(debugPadLock)) {
		return 0;
	}
	int padIndex = MogPadIndex(0);
	return static_cast<unsigned short>(Pad.GetPadInputs()[padIndex].button[0]);
}

static inline unsigned short MogTriggerButtons(int debugPadLock)
{
	if (HasDebugPadOverride(debugPadLock)) {
		return 0;
	}
	int padIndex = MogPadIndex(0);
	return static_cast<unsigned short>(Pad.GetPadInputs()[padIndex].buttonDown[0]);
}

static inline int MogDigitalStickOverride(int debugPadLock)
{
	if (HasDebugPadOverride(debugPadLock)) {
		return 0;
	}
	int padIndex = MogPadIndex(0);
	return Pad.GetPadInputs()[padIndex].digitalStickOverride;
}

static inline float MogLeftStickX(int debugPadLock)
{
	if (HasDebugPadOverride(debugPadLock)) {
		return kCharaFurDepthZero;
	}
	int padIndex = MogPadIndex(0);
	return Pad.GetPadInputs()[padIndex].stickXF;
}

static inline float MogLeftStickY(int debugPadLock)
{
	if (HasDebugPadOverride(debugPadLock)) {
		return kCharaFurDepthZero;
	}
	int padIndex = MogPadIndex(0);
	return Pad.GetPadInputs()[padIndex].stickYF;
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

static inline void StopMogLoopSe(MogWorkState& work)
{
	if (work.m_loopSeHandle != 0) {
		Sound.StopSe(work.m_loopSeHandle);
		work.m_loopSeHandle = 0;
	}
}

static inline CTexture* FindMogFurTexture(CChara::CModel* model)
{
	CTextureSet* textureSet = model->m_texSet;

	unsigned int textureIdx = static_cast<unsigned int>(textureSet->Find(const_cast<char*>(sMogFurTextureName)));
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

	if (MenuPcs.m_battleMesMenus[5]->IsActiveMessage()) {
		return;
	}

	MenuPcs.m_battleMesMenus[5]->Open(Game.m_cFlatDataArr[1].Message(messageId + 8), 0x160, 0x20, 0x220, 0, -1, -1);
}

} // namespace

/*
 * --INFO--
 * PAL Address: 0x800e00a8
 * PAL Size: 4120b
 * EN Address: 0x800FF818
 * EN Size: 4068b
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::CModel::MogFurFrame(CGObject* gObject)
{
	int messageId = -1;
	const int debugPadLock = Pad.m_debugPadLock;
	const int heldButtons = (unsigned short)MogHeldButtons(debugPadLock);
	const int triggerButtons = (unsigned short)MogTriggerButtons(debugPadLock);
	const unsigned short rotateButtons = static_cast<unsigned short>((MogDigitalStickOverride(debugPadLock) == 0) ? MogHeldButtons(debugPadLock) : static_cast<short>(0));

	if (m_mogWork.m_started == 0) {
		if ((heldButtons & 0x100) != 0) {
			return;
		}
		m_mogWork.m_started = 1;
	}

	if (m_mogWork.m_frameCount == 0) {
		messageId = 0;
		for (int i = 0; i < 3; i++) {
			m_mogWork.m_prevScore[i] = Chara.MogFur().m_score[i];
		}
	}

	if (m_mogWork.m_state == 0) {
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
			m_mogWork.m_state = 1;
			gObject->PlayAnim(0x37, 1, 0, -1, -1, 0);
			messageId = 7;
		}
	} else if (m_mogWork.m_state == 1) {
		if (gObject->m_currentAnimSlot == gObject->m_animSlots[0x37]) {
			if (gObject->IsLoopAnim(1) != 0) {
				gObject->PlayAnim(0x38, 1, 0, -1, -1, 0);
			}
		} else if (gObject->m_currentAnimSlot == gObject->m_animSlots[0x38]) {
			if ((rotateButtons & 4) != 0) {
				gObject->PlayAnim(0x39, 1, 0, -1, -1, 0);
			}
		} else if (gObject->IsLoopAnim(1) != 0) {
			gObject->CancelAnim(1);
			m_mogWork.m_state = 0;
		}
	}

	Chara.MogFur().m_cursorX = static_cast<int>(kYmEnvTen * MogLeftStickX(debugPadLock) +
	                                     static_cast<float>(static_cast<int>(Chara.MogFur().m_cursorX)));
	Chara.MogFur().m_cursorY = static_cast<int>(-(kYmEnvTen * MogLeftStickY(debugPadLock) -
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
			m_mogWork.m_pickTicks = 0;
			Sound.StopSe(m_mogWork.m_loopSeHandle);
			m_mogWork.m_loopSeHandle = 0;
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
			m_mogWork.m_pickTicks++;

			for (int i = 0; i < 3; i++) {
				if (m_mogWork.m_prevScore[i] + 5 <= Chara.MogFur().m_score[i]) {
					m_mogWork.m_prevScore[i] = Chara.MogFur().m_score[i];
					messageId = 1;
				} else if (m_mogWork.m_prevScore[i] - 5 > Chara.MogFur().m_score[i]) {
					m_mogWork.m_prevScore[i] = Chara.MogFur().m_score[i];
					messageId = 6;
				}
			}

			if (pickResult == 0) {
				m_mogWork.m_idleTicks++;
				if (m_mogWork.m_idleTicks == 0x3C && messageId == -1) {
					messageId = 3;
				} else if (m_mogWork.m_idleTicks == 0xF0 && messageId == -1) {
					messageId = 4;
				}
			} else {
				m_mogWork.m_idleTicks = 0;
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
					m_mogWork.m_offColorTicks = 0;
					particleNo = 0x73;
					m_mogWork.m_eraseTicks = 0;
					particleColor = CColor(0xF, 4, 4, 2).color;
					break;
				case 1:
					m_mogWork.m_offColorTicks = 0;
					particleNo = 0x73;
					m_mogWork.m_eraseTicks = 0;
					particleColor = CColor(4, 8, 0xF, 2).color;
					break;
				case 2:
					m_mogWork.m_offColorTicks = 0;
					particleNo = 0x73;
					m_mogWork.m_eraseTicks = 0;
					particleColor = CColor(4, 0xF, 4, 2).color;
					break;
				case 3:
					m_mogWork.m_eraseTicks = 0;
					if ((((centerBefore.r < 0x0D) || (centerBefore.g < 0x0D)) || (centerBefore.b < 0x0D)) && (centerBefore.a != 0)) {
						m_mogWork.m_offColorTicks++;
					}
					seId = 0x249f4;
					particleNo = 0x74;
					emitParticle = ((static_cast<int>(System.m_frameCounter) % 8) == 0);
					playGate = ((static_cast<int>(System.m_frameCounter) % 16) == 0);
					break;
				case 4:
					m_mogWork.m_offColorTicks = 0;
					if ((doPaint != 0) && (centerBefore.a != 0) && (centerAfter.a == 0)) {
						m_mogWork.m_eraseTicks++;
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

				if (m_mogWork.m_offColorTicks == 10) {
					if (messageId == -1) {
						messageId = 2;
					}
					m_mogWork.m_offColorTicks++;
				}
				if (m_mogWork.m_eraseTicks == 10) {
					if (messageId == -1) {
						messageId = 5;
					}
					m_mogWork.m_eraseTicks++;
				}
				if (m_mogWork.m_eraseTicks == 0x32) {
					if (messageId == -1) {
						messageId = 6;
					}
					m_mogWork.m_eraseTicks++;
				}

				if (Chara.MogFur().m_commandIndex < 3 && Chara.MogFur().m_commandIndex >= 0 && doPaint != 0
				    && m_mogWork.m_loopSeHandle == 0) {
					m_mogWork.m_loopSeHandle = Sound.PlaySe(0x249f2, 0x40, 0x7F, 0);
				}
			}
		}
	} else {
		if (Chara.MogFur().m_commandIndex < 3 && Chara.MogFur().m_commandIndex >= 0) {
			StopMogLoopSe(m_mogWork);
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
	m_mogWork.m_frameCount++;
}

/*
 * --INFO--
 * PAL Address: 0x800e10c0
 * PAL Size: 136b
 * EN Address: 0x800FF774
 * EN Size: 164b
 * JP Address: TODO
 * JP Size: TODO
 */
#undef fur

void CChara::ChangeMogMode(int mogMode)
{
	if (mogMode != 0) {
		memset(&m_mogWork, 0, sizeof(m_mogWork));
		MogFur().m_cursorX = 0x140;
		MogFur().m_cursorY = 0xE0;
		MogFur().m_dirty = 0;
		return;
	}

	int& mogSoundHandle = m_mogWork.m_loopSeHandle;
	if (mogSoundHandle != 0) {
		Sound.StopSe(mogSoundHandle);
		mogSoundHandle = 0;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800e1148
 * PAL Size: 292b
 * EN Address: 0x800FF560
 * EN Size: 184b
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::InitFurTexBuffer()
{
	MogFurState& fur = MogFur();
	for (int y = 0; y < 0x40; y++) {
		for (int x = 0; x < 0x40; x++) {
			Chara.MogFur().m_texels[y * 0x40 + x] = 0x7FFF;
		}
	}

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
 * EN Address: 0x800FF390
 * EN Size: 340b
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma push
#pragma opt_common_subs off
#pragma opt_propagation off
void CChara::CModel::InitMogFurTex()
{
	CTextureSet* textureSet = m_texSet;
	unsigned int textureIdx = static_cast<unsigned int>(textureSet->Find(const_cast<char*>(sMogFurTextureName)));
	CTexture* texture = textureSet->GetTexture(textureIdx);

	if ((texture != 0) && (texture->m_format == GX_TF_RGB565)) {
		texture->m_format = GX_TF_RGB5A3;
		Graphic._WaitDrawDone(const_cast<char*>(s_chara_fur_cpp), 0x506);

		textureSet = m_texSet;
		textureIdx = static_cast<unsigned int>(textureSet->Find(const_cast<char*>(sMogFurTextureName)));
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
		m_flagsA0Bits.m_flagA0_40 = 1;
	}
}
#pragma pop

/*
 * --INFO--
 * PAL Address: 0x800e13fc
 * PAL Size: 3448b
 * EN Address: 0x800FE5B8
 * EN Size: 3544b
 * JP Address: TODO
 * JP Size: TODO
 */
int CChara::CModel::PickFur(
    Mtx viewMtx, _GXColor brushColor, int doPaint, int mode, _GXColor* centerBefore, _GXColor* centerAfter, Vec* outWorldPos)
{
	struct CWork
	{
		signed int m_projValid : 1;
		signed int m_edgeFlag : 1;
		Vec m_viewPos;
		Vec4d m_clip;
		Vec2d m_screen;
		Vec2d m_uv;
	};

	STATIC_ASSERT(sizeof(CWork) == 0x30);
	STATIC_ASSERT(offsetof(CWork, m_uv) == 0x28);

	if (m_flags10CBits.m_flag10C_40 == 0) {
		return -1;
	}

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

	FurMeshRaw* mesh = m_meshes;

	CWork verts[3];
	CWork incoming;
	Mtx44 invScreenMtx;

	for (unsigned int meshIndex = 0; meshIndex < m_data->m_meshCount; meshIndex++, mesh++) {
		if (mesh->m_workPositions == 0) {
			continue;
		}
		if (((m_meshVisibleMask >> meshIndex) & 1) == 0) {
			continue;
		}

		Mtx meshMtx;
		if (mesh->m_data->m_skinCount != 0) {
			PSMTXCopy(m_drawMtx, meshMtx);
		} else {
			PSMTXConcat(m_drawMtx, m_nodes[mesh->m_data->m_nodeIndex].m_mtx, meshMtx);
		}

		Mtx modelViewMtx;
		PSMTXConcat(viewMtx, meshMtx, modelViewMtx);
		const unsigned int posGqr = m_data->m_posQuant;
		const int normGqr = m_data->m_normQuant;
		Chara.gqrInit(posGqr << 0x18 | 0x70000 | posGqr << 8 | 7,
			          normGqr << 0x18 | 0x70000 | normGqr << 8 | 7, 0xc070c07);

		FurDisplayListRaw* displayList = mesh->m_data->m_displayLists;
		int displayCount = mesh->m_data->m_displayListCount;
		while (--displayCount >= 0) {
			CMaterial* material = m_data->m_materialSet->m_materials[displayList->m_material];
			unsigned int paintableMaterial = 0;
			CTexture* pickTexture = material->GetFurPickTexture();
			if (pickTexture != 0 && pickTexture->m_format == GX_TF_RGB5A3) {
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
						if (primitive != GX_TRIANGLES && primitive != GX_TRIANGLESTRIP) {
							break;
						}

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

							PSMTXMultVec(modelViewMtx, &localPos, &incoming.m_viewPos);

							if (static_cast<double>(incoming.m_viewPos.z) >= static_cast<double>(kCharaFurDepthZero)) {
								incoming.m_projValid = 0;
							} else {
								incoming.m_projValid = 1;
								Math.MTX44MultVec4(screenMtx, &incoming.m_viewPos, &incoming.m_clip);
								const float invW = kCharaFurDepthScaleBase / incoming.m_clip.w;
								incoming.m_screen.x = kCharaFurScreenCenterX * incoming.m_clip.x * invW + kCharaFurScreenCenterX;
								incoming.m_screen.y = kCharaFurScreenCenterY - kCharaFurScreenCenterY * incoming.m_clip.y * invW;
								incoming.m_uv.x = curU;
								incoming.m_uv.y = curV;
							}
							verts[0] = verts[1];
							verts[1] = verts[2];
							verts[2] = incoming;

							if ((primitive == GX_TRIANGLES && static_cast<int>(vertexIndex) % 3 == 2) ||
								(primitive == GX_TRIANGLESTRIP && static_cast<int>(vertexIndex) >= 2)) {
								CWork* vp = &verts[0];
								int passed = 0;
								float depthAccum = kCharaFurDepthZero;
								for (int remainEdges = 3; remainEdges != 0; remainEdges--) {
									if (vp->m_projValid == 0) {
										break;
									}
									int next = (passed + 1) % 3;
									const float edge =
										(static_cast<float>(cursorYd) - vp->m_screen.y) * (verts[next].m_screen.x - vp->m_screen.x) -
										(static_cast<float>(cursorXd) - vp->m_screen.x) * (verts[next].m_screen.y - vp->m_screen.y);
									if (primitive == GX_TRIANGLES || (vertexIndex & 1) == 0) {
										vp->m_edgeFlag = 0;
										if (edge > kCharaFurDepthZero) {
											break;
										}
									} else {
										vp->m_edgeFlag = 1;
										if (edge < kCharaFurDepthZero) {
											break;
										}
									}
									depthAccum = depthAccum + vp->m_clip.w;
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
								CVector rayEnd;
								rayStart = CVector(
									(static_cast<float>(cursorXd) - kCharaFurScreenCenterX) / kCharaFurScreenCenterX,
									static_cast<float>(negCursorY) / kCharaFurScreenCenterY, kCharaFurDepthZero);
								rayEnd = CVector(rayStart.x, rayStart.y, kCharaFurPickRayFarZ);
								PSMTX44MultVec(invScreenMtx, rayStart, rayStart);
								PSMTX44MultVec(invScreenMtx, rayEnd, rayEnd);

								CVector ray = rayEnd - rayStart;

								CVector normal;
								CVector normalA;
								CVector normalB;
								PSVECCrossProduct(&verts[1].m_viewPos, &verts[0].m_viewPos, normalA);
								PSVECCrossProduct(&verts[2].m_viewPos, &verts[0].m_viewPos, normalB);
								PSVECCrossProduct(normalA, normalB, normal);
								if (verts[2].m_edgeFlag != 0) {
									normal = CVector(-normal.x, -normal.y, -normal.z);
								}
								normal.Normalize();

								CVector planeDelta = CVector(verts[0].m_viewPos) - rayStart;
								const float rayDot = PSVECDotProduct(normal, ray);
								const float planeDot = PSVECDotProduct(normal, planeDelta);
								Vec scaledRay;
								PSVECScale(ray, &scaledRay, planeDot / rayDot);
								PSVECAdd(rayStart, &scaledRay, hitViewPos);

								CVector hitToA;
								CVector hitToB;
								CVector hitToC;
								CVector areaAB;
								CVector areaBC;
								CVector areaCA;
								hitToA = CVector(verts[0].m_viewPos) - hitViewPos;
								hitToB = CVector(verts[1].m_viewPos) - hitViewPos;
								hitToC = CVector(verts[2].m_viewPos) - hitViewPos;

								PSVECCrossProduct(hitToA, hitToB, areaAB);
								PSVECCrossProduct(hitToB, hitToC, areaBC);
								PSVECCrossProduct(hitToC, hitToA, areaCA);
								const float magAB = PSVECMag(areaAB);
								const float magCA = PSVECMag(areaCA);
								const float magBC = PSVECMag(areaBC);
								CVector weights = CVector(magBC, magCA, magAB) * kCharaFurWeightScale;
								PSVECScale(weights, weights,
									       kCharaFurDepthScaleBase / (weights.z + weights.x + weights.y));

								const float outU =
									verts[2].m_uv.x * weights.z + (verts[0].m_uv.x * weights.x + verts[1].m_uv.x * weights.y);
								const float outV =
									verts[2].m_uv.y * weights.z + (verts[0].m_uv.y * weights.x + verts[1].m_uv.y * weights.y);

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
		if (texture != 0 && texture->m_format == GX_TF_RGB5A3 && nearestDepth != kCharaFurDepthZero) {
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
		PSMTXInverse(viewMtx, invViewMtx);
		PSMTXMultVec(invViewMtx, outWorldPos, outWorldPos);
	}

	if (kCharaFurNoHitDepth == nearestDepth) {
		goto noHitReturn;
	}
	return 1;
noHitReturn:
	return -(hitAny == 0);
}


/*
 * --INFO--
 * PAL Address: 0x800e2174
 * PAL Size: 1140b
 * EN Address: 0x800FDF78
 * EN Size: 1600b
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma push
#pragma opt_loop_invariants off
static void brush(unsigned short* pixels, int width, int height, float fx, float fy, int mode, _GXColor targetColor, _GXColor* centerBefore, _GXColor* centerAfter)
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
			tileIndex = ((unsigned int)px % 4 + ((py % 4) * 4 + ((unsigned int)px / 4 * 0x10 + (py / 4) * rowStride)));
			packed = pixels[tileIndex];

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

			pixels[tileIndex] = (unsigned short)((a << 12) | (r << 8) | (g << 4) | b);

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
				void* texData = reinterpret_cast<unsigned char*>(m_pTexBuf) + (layer * 0x4000);
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
	if (m_pTexBuf != 0) {
		Memory.Free(m_pTexBuf);
		m_pTexBuf = 0;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800e3304
 * PAL Size: 4996b
 * EN Address: 0x800FC620
 * EN Size: 2652b
 * JP Address: TODO
 * JP Size: TODO
 */
void CChara::makeFurTex()
{
	CHairSet hairSet[0x20];

	static CColor color[2] = { CColor(0x80, 0x80, 0x80, 0xFF), CColor(0xF0, 0xF0, 0xF0, 0) };
	static CColor colorr[2] = { CColor(0, 0, 0, 0), CColor(8, 8, 8, 0) };
	static CVector vel = CVector(kCharaFurDepthZero, FLOAT_80331160, kCharaFurDepthZero);
	static CVector velr = CVector(kCharaFurDepthZero, kYmEnvQuarter, kCharaFurDepthZero);
	static CVector accel = CVector(kCharaFurDepthZero, kCharaFurDepthZero, kCharaFurDepthZero);
	static CVector accelr = CVector(kCharaFurDepthZero, kCharaFurDepthZero, kCharaFurDepthZero);

	mySrand(0);

	float weightScale = kCharaFurWeightScale;

	for (int i = 0; i < 0x20; i++) {
		hairSet[i].m_vec0 = vel + velr * myRandFPM(1.0f);
		hairSet[i].m_vec1 = accel + accelr * myRandFPM(1.0f);

		hairSet[i].m_colors[0] = color[0] + colorr[0] * myRandFPM(1.0f);
		hairSet[i].m_colors[1] = color[1] + colorr[1] * myRandFPM(1.0f);

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
	float layerStep = FLOAT_8033115C;

	for (int layer = 0; layer < 8; layer++) {
		posMtx[2][3] -= m_height * layerStep;
		GXLoadPosMtxImm(posMtx, GX_PNMTX0);
		GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);

		float layerFactor = static_cast<float>(layer) * layerStep;
		layerFactor = layerFactor * layerFactor;

		CColor layerColor = color[0] * (scaleBase2 - layerFactor) + color[1] * layerFactor;
		CColor clearColor(layerColor);
		clearColor.color.a = 0;
		Graphic.SetCopyClear(clearColor.color, 0xFFFFFF);
		GXCopyTex(static_cast<unsigned char*>(m_pTexBuf) + layer * 0x4000, GX_TRUE);
		GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);

		mySrand(0);
		for (int hair = 0; hair < 0x4000; hair++) {
			GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);

			float rootX = myRandFPM(1.0f);
			float rootZ = myRandFPM(1.0f);
			CVector rootTmp(rootX, kCharaFurDepthZero, rootZ);
			CVector root = rootTmp;

			CHairSet& src = hairSet[myRand(0x20)];

			float t = kCharaFurDepthZero;
			for (int v = 0; v < 5; v++) {
				float t2 = t * t;
				CVector pos = root + src.m_vec0 * t + src.m_vec1 * (weightScale2 * t2);
				float px = pos.x;
				float py = pos.y;
				float pz = pos.z;

				CColor color = src.m_colors[0] * (scaleBase2 - t2) + src.m_colors[1] * t2;
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
				CVector pos = root + src.m_vec0 * t + src.m_vec1 * (weightScale2 * t2);
				float px = pos.x;
				float py = pos.y;
				float pz = pos.z;

				CColor color = src.m_colors[0] * (scaleBase2 - t2) + src.m_colors[1] * t2;
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

MogWorkState m_mogWork;

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
inline void GXSetTexCoordGen(void)
{
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
}

extern const double kYmEnvRadToDeg = 57.295780181884766;
extern const float kYmEnvDefaultScale = 1.5f;
extern const float kYmEnvQuarter = 0.25f;
extern const float kCharaFurDepthZero = 0.0f;
extern const float kYmEnvTen = 10.0f;
extern const float kCharaFurColorComponentScale = 15.0f;
extern const float kCharaFurAlphaComponentScale = 7.0f;
extern const float kCharaFurNoHitDepth = 10000000.0f;
extern const float kCharaFurScreenCenterY = 224.0f;
extern const float kCharaFurDepthScaleBase = 1.0f;
extern const float kCharaFurScreenCenterX = 320.0f;
extern const float kCharaFurTriangleVertexCount = 3.0f;
extern const float kCharaFurPickRayFarZ = -100.0f;
extern const float kCharaFurWeightScale = 0.5f;
extern const float kCharaFurViewDepthThreshold = -1.0f;
extern const float kCharaFurShadeScale = 255.0f;
extern const float kCharaFurShadowRange = 100.0f;
extern const float kCharaFurShadowFade = 20.0f;
extern const float FLOAT_8033115C = 0.125f;
extern const float FLOAT_80331160 = 4.0f;
extern const float FLOAT_80331164 = 6.103701889514923e-05f;
extern const float FLOAT_80331168 = 128.0f;
extern const float FLOAT_8033116C = 8.0f;

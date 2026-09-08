#include "ffcc/bonus_menu.h"
#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/gbaque.h"
#include "ffcc/gobjwork.h"
#include "ffcc/gxfunc.h"
#include "ffcc/p_chara.h"
#include "ffcc/game.h"
#include "ffcc/linkage.h"
#include "ffcc/mes.h"
#include "ffcc/pad.h"
#include "ffcc/p_tina.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include "ffcc/util.h"
#include "ffcc/wind.h"
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdlib.h>

extern char lbl_801DD5D4[];
extern const double kPppCrystal2RefractionScale;
extern const float kBonusZClearOrigin;
extern const float FLOAT_80331EB0;
extern const float FLOAT_80331ED0;
extern const float FLOAT_80331F6C;
extern const float FLOAT_80331F5C;
extern const float FLOAT_80331F60;
extern const float FLOAT_80331F64;
extern const float FLOAT_80331F68;
extern const double DOUBLE_80331E78;
extern const double DOUBLE_80331EE8;
extern const double DOUBLE_80331EF0;
extern const float FLOAT_80331EF8;
extern const float FLOAT_80331EFC;
extern const float FLOAT_80331E98;
extern const double DOUBLE_80331EC8;
extern const float FLOAT_80331F38;
extern const float FLOAT_80331F3C;
extern const float FLOAT_80331F90;
extern const float FLOAT_80331F00;
extern const float FLOAT_80331F04;
extern const double DOUBLE_80331F08;
extern const float FLOAT_80331F10;
extern const float FLOAT_80331F14;
extern const float FLOAT_80331F18;
extern const double DOUBLE_80331F20;
extern const float FLOAT_80331F28;
extern const float FLOAT_80331F2C;
extern const float FLOAT_80331F94;
extern const float FLOAT_80331FA0;
extern const float FLOAT_80331FA4;
extern const float FLOAT_80331FA8;
extern const double DOUBLE_80331E90;
extern const double DOUBLE_80331F98;
extern const double DOUBLE_80331ED8;
extern const double DOUBLE_80331EE0;
extern const double DOUBLE_80331FB0;
extern const float kBonusZClearWidth;
extern const float kBonusZClearHeight;
extern const float FLOAT_80331E9C;
extern const float FLOAT_80331EA0;
extern const float FLOAT_80331EA4;
extern const float FLOAT_80331EA8;
extern const float FLOAT_80331F40;
extern const float FLOAT_80331F44;
extern const float FLOAT_80331F48;
extern const float FLOAT_80331F4C;
extern const float FLOAT_80331F50;
extern const float FLOAT_80331F58;
extern const char lbl_80331F54[2];
extern const double DOUBLE_80331F30;
extern const double DOUBLE_80331F70;
extern const float FLOAT_80331F78;
extern const double DOUBLE_80331F80;
extern const double DOUBLE_80331F88;

static const float s_PCYpos[4] = {-11.14f, -7.1f, -11.55f, -11.14f};
static const float s_PCScl[4] = {0.87f, 0.78f, 0.78f, 0.87f};
static const float s_AnimX[3] = {9.1f, 13.7f, 27.9f};

static float s_BallTrnsXspl[] = {
    0.03333299979567528f, 27.700000762939453f, 0.0f, 0.0f,
    0.23524600267410278f, 12.29898452758789f, -55.570411682128906f, -55.570411682128906f,
    0.3703629970550537f, 6.334517955780029f, -25.889270782470703f, -25.889270782470703f,
    1.0f, -14.300000190734863f, 0.0f, 0.0f,
};

static float s_BallTrnsYspl[] = {
    0.03333299979567528f, 8.5f, 0.0f, 0.0f,
    0.241907000541687f, -1.2000000476837158f, 0.0f, 0.0f,
    0.3153750002384186f, 1.6390860080718994f, 0.0f, 0.0f,
    0.3817799985408783f, -1.2000000476837158f, 0.0f, 0.0f,
    1.0f, -1.2000000476837158f, 0.0f, 0.0f,
    1.3333330154418945f, 0.30000001192092896f, 0.0f, 0.0f,
};

static CMenuPcs::FCV s_BallTrnsX = {4, s_BallTrnsXspl};
static CMenuPcs::FCV s_BallTrnsY = {6, s_BallTrnsYspl};

extern const char sBonusTextureSetName[] = "bonus";
extern const char sBonusTextureName1[] = "bonus1";
extern const char sBonusTextureName2[] = "bonus2";
extern const char sBonusTextureName3[] = "bonus3";
extern const char sBonusTextureName4[] = "bonus4";
extern const char sBonusTextureName5[] = "bonus5";
extern const char sBonusTextureName6[] = "bonus6";
extern const char sBonusTextureName7[] = "bonus7";
extern const char sBonusTextureName8[] = "bonus8";
extern const char sBonusTextureName9[] = "bonus9";
extern const char sBonusTextureName10[] = "bonus10";
extern const char sBonusTextureName11[] = "bonus11";
extern const char sBonusTextureName12[] = "bonus12";
extern const char sBonusTextureName13[] = "bonus13";
extern const char sBonusTextureName14[] = "bonus14";
extern const char sBonusTextureName15[] = "bonus15";
extern const char sBonusTextureName16[] = "bonus16";
extern const char sBonusTextureName17[] = "bonus17";
extern const char sBonusTextureName18[] = "bonus18";

extern const double DOUBLE_80331E78 = 0.5;
extern const double DOUBLE_80331E80 = 0.25;
extern const double DOUBLE_80331E88 = 4503601774854144.0;
extern const double DOUBLE_80331E90 = 0.0;
extern const float FLOAT_80331E98 = 255.0f;
extern const float FLOAT_80331E9C = 28.0f;
extern const float FLOAT_80331EA0 = 20.0f;
extern const float FLOAT_80331EA4 = 56.0f;
extern const float FLOAT_80331EA8 = 64.0f;
extern const float kBonusZClearOrigin = 0.0f;
extern const float FLOAT_80331EB0 = 1.0f;
extern const float FLOAT_80331EB4 = 0.699999988079071f;
extern const float FLOAT_80331EB8 = 32.0f;
extern const double DOUBLE_80331EC0 = 64.0;
extern const double DOUBLE_80331EC8 = 3.0;
extern const float FLOAT_80331ED0 = 240.0f;
extern const double DOUBLE_80331ED8 = 1.0;
extern const double DOUBLE_80331EE0 = 4.0;
extern const double DOUBLE_80331EE8 = 320.0;
extern const double DOUBLE_80331EF0 = 224.0;
extern const float FLOAT_80331EF8 = 12.0f;
extern const float FLOAT_80331EFC = 8.0f;
extern const float FLOAT_80331F00 = 0.5799999833106995f;
extern const float FLOAT_80331F04 = 0.01745329238474369f;
extern const double DOUBLE_80331F08 = -45.0;
extern const float FLOAT_80331F10 = 3.1415927410125732f;
extern const float FLOAT_80331F14 = -1.1693705320358276f;
extern const float FLOAT_80331F18 = 0.9670329689979553f;
extern const double DOUBLE_80331F20 = 5.0;
extern const float FLOAT_80331F28 = 3.4000000953674316f;
extern const float FLOAT_80331F2C = 5.0f;
extern const double DOUBLE_80331F30 = 10.0;
extern const float FLOAT_80331F38 = 0.7300000190734863f;
extern const float FLOAT_80331F3C = 4.0f;
extern const float FLOAT_80331F40 = 0.7200000286102295f;
extern const float FLOAT_80331F44 = 0.8999999761581421f;
extern const float FLOAT_80331F48 = 44.0f;
extern const float FLOAT_80331F4C = 11.0f;
extern const float FLOAT_80331F50 = 7.0f;
extern const char lbl_80331F54[2] = "\n";
extern const float FLOAT_80331F58 = 22.0f;
extern const float FLOAT_80331F5C = -8.0f;
extern const float FLOAT_80331F60 = -240.0f;
extern const float FLOAT_80331F64 = 0.8333333134651184f;
extern const float FLOAT_80331F68 = 176.0f;
extern const float FLOAT_80331F6C = 100.0f;
extern const double DOUBLE_80331F70 = 450.0;
extern const float FLOAT_80331F78 = -90.0f;
extern const double DOUBLE_80331F80 = 45.0;
extern const double DOUBLE_80331F88 = -90.0;
extern const float FLOAT_80331F90 = 0.800000011920929f;
extern const float FLOAT_80331F94 = 0.2617993950843811f;
extern const double DOUBLE_80331F98 = 8.333333134651184;
extern const float FLOAT_80331FA0 = 80.0f;
extern const float FLOAT_80331FA4 = 40.0f;
extern const float FLOAT_80331FA8 = 0.5f;
extern const double DOUBLE_80331FB0 = 1.8;
extern const float kBonusZClearWidth = 640.0f;
extern const float kBonusZClearHeight = 448.0f;

char* sBonusTextureSetNames[] = {
    const_cast<char*>(sBonusTextureSetName),
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

CMenuPcs::CTmp sBonusTextureTable[] = {
    {2, const_cast<char*>(sBonusTextureName1)},
    {2, const_cast<char*>(sBonusTextureName2)},
    {2, const_cast<char*>(sBonusTextureName3)},
    {2, const_cast<char*>(sBonusTextureName4)},
    {2, const_cast<char*>(sBonusTextureName5)},
    {2, const_cast<char*>(sBonusTextureName6)},
    {2, const_cast<char*>(sBonusTextureName7)},
    {2, const_cast<char*>(sBonusTextureName8)},
    {2, const_cast<char*>(sBonusTextureName9)},
    {2, const_cast<char*>(sBonusTextureName10)},
    {2, const_cast<char*>(sBonusTextureName11)},
    {2, const_cast<char*>(sBonusTextureName12)},
    {2, const_cast<char*>(sBonusTextureName13)},
    {2, const_cast<char*>(sBonusTextureName14)},
    {2, const_cast<char*>(sBonusTextureName15)},
    {2, const_cast<char*>(sBonusTextureName16)},
    {2, const_cast<char*>(sBonusTextureName17)},
    {2, const_cast<char*>(sBonusTextureName18)},
};

struct BonusPartySummary {
	int m_partySlot;
	CCharaPcs::CHandle* m_partyHandle;
	int m_bonusCondition;
	int m_totalValue;
	int m_foodValue;
	int m_artifactValue;
	int m_rank;
	unsigned int m_ownedArtifactMask;
	int m_selectedItemId;
	int m_selectedSlot;
	unsigned int m_tribeId;
};

STATIC_ASSERT(sizeof(BonusPartySummary) == 0x2C);
STATIC_ASSERT(offsetof(BonusPartySummary, m_partyHandle) == 0x04);
STATIC_ASSERT(offsetof(BonusPartySummary, m_rank) == 0x18);
STATIC_ASSERT(offsetof(BonusPartySummary, m_tribeId) == 0x28);

struct BonusSummaryData {
	enum { kTemporaryArtifactCount = 4, kBossArtifactCount = 4, kArtifactCount = 8 };

	int m_partyCount;
	int m_winnerTotalValue;
	unsigned char m_selectedArtifactMask;
	unsigned char m_missingArtifactMask;
	short m_artifacts[kArtifactCount];
	short pad_001A;
	BonusPartySummary m_party[4];
};

STATIC_ASSERT(sizeof(BonusSummaryData) == 0xCC);
STATIC_ASSERT(offsetof(BonusSummaryData, m_artifacts) == 0x0A);
STATIC_ASSERT(offsetof(BonusSummaryData, m_artifacts) + BonusSummaryData::kTemporaryArtifactCount * sizeof(short) == 0x12);
STATIC_ASSERT(offsetof(BonusSummaryData, m_party) == 0x1C);

static BonusSummaryData* s_Rinfo = 0;
static unsigned char s_CntTop = 0;
static unsigned char s_ArtiTop = 0;
static unsigned char s_PlayerTop = 0;
static float* s_Base[1];

namespace {

struct BonusBaseRaw {
	float values[18];
};

STATIC_ASSERT(sizeof(BonusBaseRaw) == 0x48);

static inline void InitBonusEffectSlots(CMenuPcs* menu)
{
	for (int i = 0; i < 40; i++) {
		menu->m_effectWork[i].m_effectNo = -1;
		menu->m_effectWork[i].m_partNo = -1;
		menu->m_effectWork[i].m_slotNo = -1;
	}
}

static inline void ReleaseBonusRefObject(void* object)
{
	CRef* ref = reinterpret_cast<CRef*>(object);
	if (ref->DecRef() == 0) {
		delete ref;
	}
}

static inline void SetupSelectCloseSpriteMotion(CMenuPcs::Sprt2* sprite)
{
	sprite->startFrame = 0;
	sprite->duration = 8;
	sprite->x = (short)(int)sprite->targetX;
	sprite->y = (short)(int)sprite->targetY;
	sprite->motionX = FLOAT_80331ED0;
	sprite->motionY = kBonusZClearOrigin;
	sprite->targetX = (float)sprite->x + sprite->motionX;
	sprite->targetY = (float)sprite->y + sprite->motionY;
}

} // namespace

/*
 * --INFO--
 * PAL Address: 0x80133108
 * PAL Size: 104b
 * EN Address: 0x8015DF54
 * EN Size: 144b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ClrBattleItem()
{
	for (int i = 0; i < 4; i++) {
		if (Game.m_scriptFoodBase[i] != 0) {
			reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i])->SafeDeleteTempItem();
			reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i])->SortBeforeReturnWorldMap();
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x80133170
 * PAL Size: 940b
 * EN Address: 0x8015DA98
 * EN Size: 1080b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ArtiBaseInfoInit(CMenuPcs::Sprt2* a, CMenuPcs::Sprt2* b)
{
	Sprt2* board = a;
	Sprt2* icon = b;

	s_Base[0][0] = (float)(board->x + board->w * 0.5);
	s_Base[0][1] = (float)(board->y + board->h * 0.5);

	float iconW = (float)icon->w;
	float iconH = (float)icon->h;

	float v14 = (float)((double)s_Base[0][0] - (double)iconW * 0.5);
	float v15 = (float)board->y;
	for (int r0 = 0; r0 < 2; r0++) {
		if (r0 != 0) {
			v15 = v15 + ((float)board->h - iconH);
		}
		if (r0 == 0) {
			s_Base[0][14] = v14;
			s_Base[0][15] = v15;
		} else {
			s_Base[0][6] = v14;
			s_Base[0][7] = v15;
		}
	}

	float v10 = (float)board->x;
	float v11 = (float)((double)s_Base[0][1] - (double)iconH * 0.5);
	for (int r1 = 0; r1 < 2; r1++) {
		if (r1 != 0) {
			v10 = v10 + ((float)board->w - iconW);
		}
		if (r1 == 0) {
			s_Base[0][10] = v10;
			s_Base[0][11] = v11;
		} else {
			s_Base[0][2] = v10;
			s_Base[0][3] = v11;
		}
	}

	for (int row = 0; row < 2; row++) {
		float slotX = (float)((double)(float)(board->x + board->w * 0.25) - (double)iconW * 0.5);
		float slotY = (float)((double)(float)(board->y + board->h * 0.25) - (double)iconH * 0.5);
		if (row != 0) {
			slotY = (float)(board->h * 0.5 + slotY);
			s_Base[0][8] = slotX;
			s_Base[0][9] = slotY;
		} else {
			s_Base[0][12] = slotX;
			s_Base[0][13] = slotY;
		}
		float nextX = (float)(board->w * 0.5 + slotX);
		if (row == 0) {
			s_Base[0][16] = nextX;
			s_Base[0][17] = slotY;
		} else {
			s_Base[0][4] = nextX;
			s_Base[0][5] = slotY;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013351C
 * PAL Size: 616b
 * EN Address: 0x8015D554
 * EN Size: 788b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawArtiBase(CMenuPcs::Sprt2* sprt, float alpha)
{
	if (alpha <= 0.0) {
		return;
	}

	_GXColor color;
	if (this->m_bonusState->m_phase != 4) {
		color.r = 0xFF;
		color.g = 0xFF;
		color.b = 0xFF;
		color.a = (unsigned char)(alpha * 255.0f);
		GXSetChanMatColor(GX_COLOR0A0, color);
	}

	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1A));

	CMenuPcs::Sprt2* sprite = sprt;
	float width = (float)sprite->w;
	float height = (float)sprite->h;

	int partyIndex = 0;
	for (; partyIndex < s_Rinfo->m_partyCount; partyIndex++) {
		if ((int)this->m_bonusState->m_currentRank == s_Rinfo->m_party[partyIndex].m_rank) {
			break;
		}
	}

	for (int i = 0; i < 8; i++) {
		if (this->m_bonusState->m_phase == 4) {
			float gray;
			unsigned int mask = ((int)(signed char)s_Rinfo->m_selectedArtifactMask | (int)(signed char)s_Rinfo->m_missingArtifactMask) |
			    s_Rinfo->m_party[partyIndex].m_ownedArtifactMask;
			if ((mask & (1 << i)) != 0) {
				gray = 0.7f * 255.0f;
			} else {
				gray = 1.0f * 255.0f;
			}
			color.r = (unsigned char)gray;
			color.g = (unsigned char)gray;
			color.b = (unsigned char)gray;
			color.a = (unsigned char)(alpha * 255.0f);
			GXSetChanMatColor(GX_COLOR0A0, color);
		}
		MenuPcs.DrawRect(0, s_Base[0][i * 2 + 2], s_Base[0][i * 2 + 3], width, height,
		    0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80133784
 * PAL Size: 852b
 * EN Address: 0x8015D124
 * EN Size: 1072b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawBonusFrame(float x, float y, float w, float h, float alpha)
{
	if (alpha <= 0.0) {
		return;
	}

	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	_GXColor color;
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = (unsigned char)(255.0f * alpha);
	const float corner = 8.0f;
	const float texScale = 1.0f;

	GXSetChanMatColor(GX_COLOR0A0, color);

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1B));
	const float right = (x + w) - corner;
	const float bottom = (y + h) - corner;
	for (int i = 0; i < 4; i++) {
		float drawX = x;
		float drawY = y;
		float texU;
		float texV;
		if (i == 0) {
			texU = 0.0f;
			texV = 0.0f;
		} else if (i == 1) {
			texU = corner;
			drawX = right;
			texV = 0.0f;
		} else {
			drawY = bottom;
			if (i == 2) {
				texU = 0.0f;
				texV = corner;
			} else {
				texU = corner;
				drawX = right;
				texV = corner;
			}
		}
		MenuPcs.DrawRect(0, drawX, drawY, corner, corner, texU, texV, texScale, texScale, 0.0f);
	}

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1C));
	float innerW = (float)((double)w - 16.0);
	float xCorner = corner + x;
	MenuPcs.DrawRect(0, xCorner, y, innerW, corner, 0.0f, 0.0f, texScale, texScale, 0.0f);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x22));
	MenuPcs.DrawRect(0, xCorner, bottom, innerW, corner, 0.0f, 0.0f, texScale, texScale, 0.0f);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1D));
	float yCorner = corner + y;
	float innerH = (float)((double)h - 16.0);
	MenuPcs.DrawRect(0, x, yCorner, corner, innerH, 0.0f, 0.0f, texScale, texScale, 0.0f);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x21));
	MenuPcs.DrawRect(0, right, yCorner, corner, innerH, 0.0f, 0.0f, texScale, texScale, 0.0f);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1E));
	MenuPcs.DrawRect(0, xCorner, yCorner, (float)((double)w - 16.0), innerH, 0.0f, 0.0f, texScale, texScale, 0.0f);
}

/*
 * --INFO--
 * PAL Address: 0x80133AD8
 * PAL Size: 3172b
 * EN Address: 0x8015C0EC
 * EN Size: 3440b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcSelectCloseAnim()
{
	int activePartyCount = s_Rinfo->m_partyCount;
	int twice;
	int i;
	CMenuPcs::Sprt2* alphaSprite;
	int doneCount;
	CCharaPcs::CHandle* handle;
	int total;
	int tribeId;

	if (this->m_bonusState->m_initialized == 0) {
		int idx;

		m_bonusAnim->header.count =
		    (short)(m_bonusAnim->header.count - 1);

		{
			int i = 0;
			for (; i < (int)m_bonusAnim->header.count; i++) {
				CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[i];
				spr->alpha = FLOAT_80331EB0;
				spr->timer = 0;
				spr->flags = 0;
			}
		}

		idx = 0;
		{
			CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[idx];
			spr->kind = 0x16;
			spr->startFrame = 8;
			spr->duration = 8;
			idx++;
		}
		int i1 = 0;
		{
			CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[idx];
			spr->startFrame = i1;
			spr->duration = 8;
			spr->flags = 2;
			idx++;
		}
		{
			CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[idx];
			spr->kind = 0x1f;
			spr->startFrame = i1;
			spr->duration = i1;
			spr->flags = 2;
			idx++;
		}
		{
			CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[idx];
			spr->kind = -4;
			spr->startFrame = i1;
			spr->duration = 8;
		}

		for (; i1 < activePartyCount; i1++) {
			CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[i1 + 4];
			spr->startFrame = 0;
			spr->duration = 8;
			spr->depth = FLOAT_80331EB0;
			spr->x = (short)(int)spr->targetX;
			spr->y = (short)(int)spr->targetY;
			spr->motionX = FLOAT_80331ED0;
			spr->motionY = kBonusZClearOrigin;
			spr->targetX = (float)spr->x + spr->motionX;
			spr->targetY = (float)spr->y + spr->motionY;
		}

		int base;
		base = activePartyCount + 4;
		s_PlayerTop = (unsigned char)base;
		for (int i = 0; i < activePartyCount; i++) {
			CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[base + i];
			SetupSelectCloseSpriteMotion(spr);
		}

		base += activePartyCount;
		s_ArtiTop = (unsigned char)base;
		for (int i = 0; i < 8; i++) {
			CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[base + i];
			spr->startFrame = 0;
			spr->duration = 8;
			spr->flags = 0;
		}

		base += 8;
		for (int i = 0; i < activePartyCount; i++) {
			CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[base + i];
			SetupSelectCloseSpriteMotion(spr);
		}

		base += activePartyCount;
		for (int i = 0; i < activePartyCount; i++) {
			CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[base + i];
			SetupSelectCloseSpriteMotion(spr);
		}

		base += activePartyCount;
		{
			int delta = base - 4;
			for (int i = 0; i < activePartyCount; i++) {
				CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[base + i];
				CMenuPcs::Sprt2* src = spr - delta;
				spr->kind = -1;
				spr->x = (short)(src->x + 0x50);
				spr->y = (short)(src->y + 0x48);
				spr->startFrame = src->startFrame;
				spr->duration = 8;
				spr->motionX = FLOAT_80331ED0;
				spr->motionY = kBonusZClearOrigin;
				spr->targetX = (float)spr->x + spr->motionX;
				spr->targetY = (float)spr->y + spr->motionY;
			}
		}

		m_bonusAnim->header.finished = 0;
		this->m_bonusState->m_initialized = 1;
	}

	int i0 = 0;

	doneCount = 0;
	this->m_bonusState->m_frame++;
	int frame = (int)this->m_bonusState->m_frame;

	for (; i0 < (int)m_bonusAnim->header.count; i0++) {
		CMenuPcs::Sprt2* sprite = &m_bonusAnim->sprites[i0];

		if ((sprite->flags & 1) != 0) {
			sprite->alpha = FLOAT_80331EB0;
		} else {
			if (frame < sprite->startFrame) {
				sprite->alpha = FLOAT_80331EB0;
			}
			if (sprite->startFrame + sprite->duration <= frame) {
				sprite->alpha = kBonusZClearOrigin;
			} else {
				sprite->alpha = (float)(1.0 - (1.0 / (double)sprite->duration) * (double)sprite->timer);
			}
		}

		if (sprite->startFrame + sprite->duration <= frame || sprite->startFrame >= 9999) {
			doneCount++;
		}

		if ((sprite->flags & 2) == 0 && (sprite->motionX != kBonusZClearOrigin || sprite->motionY != kBonusZClearOrigin)) {
			float progress = (float)(1.0 - (1.0 / (double)sprite->duration) * (double)sprite->timer);
			float fy = (float)sprite->y;
			float ty = sprite->targetY;
			sprite->motionX = (sprite->targetX - (float)sprite->x) * progress;
			sprite->motionY = (ty - fy) * progress;
		}

		if (sprite->startFrame < frame && frame <= sprite->startFrame + sprite->duration) {
			sprite->timer++;
		}
	}

	{
		int i = 0;
		for (; i < activePartyCount; i++) {
			CMenuPcs::Sprt2* sprite = &m_bonusAnim->sprites[4 + i];
			int centerX = (int)(float)((double)(float)(DOUBLE_80331EE0 + ((double)sprite->w * DOUBLE_80331E78 + (double)((float)sprite->x + sprite->motionX))) - DOUBLE_80331EE8);
			int centerY = (int)(float)((double)(float)((double)sprite->h * DOUBLE_80331E78 + (double)((float)sprite->y + sprite->motionY)) - DOUBLE_80331EF0);
			m_wm.m_worldObjData[i].m_viewportX = (short)centerX;
			m_wm.m_worldObjData[i].m_viewportY = (short)centerY;
			m_wm.m_worldObjData[i].m_scissorX = (int)(FLOAT_80331EF8 + ((float)sprite->x + sprite->motionX));
			m_wm.m_worldObjData[i].m_scissorY = (int)(((float)sprite->y + sprite->motionY) - FLOAT_80331EFC);
			if ((double)m_wm.m_worldObjData[i].m_scissorX < DOUBLE_80331E90) {
				m_wm.m_worldObjData[i].m_scissorX = 0;
			}
			if ((double)m_wm.m_worldObjData[i].m_scissorY < DOUBLE_80331E90) {
				m_wm.m_worldObjData[i].m_scissorY = 0;
			}
			m_wm.m_worldObjData[i].m_scissorWidth = 0x48;
			m_wm.m_worldObjData[i].m_scissorHeight = 0x58;
		}
	}

	Mtx scaleMtx;
	Mtx rotZMtx;
	Mtx rotYMtx;
	Mtx rotXMtx;
	Vec srcVec;
	Vec dstVec;
	{
		i = 0;
		twice = activePartyCount * 2;
		total = activePartyCount + 8;
		for (; i < total; i++) {
			alphaSprite = &m_bonusAnim->sprites[(int)(signed char)s_PlayerTop + i];
			if (i < activePartyCount) {
				tribeId = s_Rinfo->m_party[i].m_tribeId;
				handle = s_Rinfo->m_party[i].m_partyHandle;
				float modelScale = s_PCScl[tribeId];
				PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
			} else {
				tribeId = twice + (i - activePartyCount);
				handle = m_wm.m_handles[tribeId];
				if (handle == 0) {
					continue;
				}
				float modelScale = FLOAT_80331F00;
				PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
			}
			if (i < activePartyCount) {
				scaleMtx[0][3] = kBonusZClearOrigin;
				scaleMtx[1][3] = s_PCYpos[tribeId];
				scaleMtx[2][3] = kBonusZClearOrigin;
			} else {
				int rotIndex = i - activePartyCount;
				srcVec.x = s_AnimX[0];
				srcVec.y = kBonusZClearOrigin;
				srcVec.z = kBonusZClearOrigin;
				PSMTXRotRad(rotZMtx, 'z', FLOAT_80331F04 * (float)(DOUBLE_80331F08 * (double)rotIndex));
				PSMTXMultVecSR(rotZMtx, &srcVec, &dstVec);
				if ((unsigned int)handle->m_charaNo == 0x44) {
					PSMTXRotRad(rotYMtx, 'y', FLOAT_80331F10);
					PSMTXConcat(scaleMtx, rotYMtx, scaleMtx);
					PSMTXRotRad(rotXMtx, 'x', FLOAT_80331F14);
					PSMTXConcat(scaleMtx, rotXMtx, scaleMtx);
				}
				scaleMtx[0][3] = dstVec.x;
				float modelY = (float)((double)(FLOAT_80331F18 * dstVec.y) - DOUBLE_80331F20);
				if ((unsigned int)handle->m_charaNo == 0x41 || (unsigned int)handle->m_charaNo == 0x37) {
					modelY += FLOAT_80331F28;
				} else if ((unsigned int)handle->m_charaNo == 0x44) {
					modelY += FLOAT_80331F2C;
				}
				scaleMtx[1][3] = modelY;
				scaleMtx[2][3] = kBonusZClearOrigin;
			}

			handle->m_model->m_flags10CBits.m_flag10C_80 = 1;
			handle->m_model->SetMatrix(scaleMtx);
			handle->m_model->CalcMatrix();
			handle->m_model->CalcSkin();
			handle->m_model->m_lightAlpha = alphaSprite->alpha;
		}
	}

	if ((int)m_bonusAnim->header.count == doneCount) {
		m_bonusAnim->header.finished = 1;
	}
}

namespace {
struct BonusModelFlags {
	unsigned char m_visible : 1;
	unsigned char m_rest : 7;
};
} // namespace

/*
 * --INFO--
 * PAL Address: 0x8013473C
 * PAL Size: 2844b
 * EN Address: 0x8015B508
 * EN Size: 3004b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcSelectWait()
{
	int frame;
	int i;
	int activePartyCount = s_Rinfo->m_partyCount;

	if (this->m_bonusState->m_initialized == 0) {
		this->m_menuWindowInfo->state = 3;
		{
			i = 0;
			while (i < (int)m_bonusAnim->header.count) {
				Sprt2* sprite = &m_bonusAnim->sprites[i];
				sprite->alpha = FLOAT_80331EB0;
				sprite->flags = 3;
				i++;
			}
		}
		{
			short count = m_bonusAnim->header.count;
			CMenuPcs::Sprt2* cursor = &m_bonusAnim->sprites[count];
			CMenuPcs::Sprt2* partySprite = cursor - activePartyCount * 2;
			cursor->kind = 0x20;
			cursor->x = (short)(partySprite->x - 3);
			cursor->y = (short)(partySprite->y - 8);
			cursor->w = 0x40;
			cursor->h = 0x30;
			cursor->mulX = kBonusZClearOrigin;
			cursor->mulY = kBonusZClearOrigin;
			cursor->startFrame = 0;
			cursor->duration = 8;
			cursor->depth = FLOAT_80331EB0;
			cursor->flags = 0;
			m_bonusAnim->header.count = (short)(count + 1);
			m_bonusAnim->sprites[2].flags = 0;
			this->m_bonusState->m_currentRank = 0;
			this->m_bonusState->m_selection = 4;
			this->m_bonusState->m_finishDelay = 0;
			m_bonusAnim->header.finished = 0;
			this->m_bonusState->m_initialized = 1;
			this->m_bonusState->m_selectionDelay = 0;
			this->m_bonusState->m_selectionResult = 0;
		}
	}

	this->m_bonusState->m_frame++;
	frame = (int)this->m_bonusState->m_frame;

	for (i = 0; i < activePartyCount; i++) {
		if (s_Rinfo->m_party[i].m_rank == this->m_bonusState->m_currentRank) {
			break;
		}
	}

	if (this->m_menuWindowInfo->state != 3) {
		if (this->m_menuWindowInfo->state == 1) {
			int padSlot = s_Rinfo->m_party[i].m_partySlot;
			unsigned short repeat = Pad.GetButtonRepeat(padSlot);
			unsigned short down = Pad.GetButtonDown(padSlot);
			if ((repeat & 3) != 0) {
				this->m_bonusState->m_confirmSelection ^= 1;
				Sound.PlaySe(1, 0x40, 0x7f, 0);
			}
			if ((repeat & 3) == 0) {
				if ((down & 0x100) != 0) {
					this->m_menuWindowInfo->state = 2;
					Sound.PlaySe(2, 0x40, 0x7f, 0);
				} else if ((down & 0x200) != 0) {
					this->m_menuWindowInfo->state = 2;
					this->m_bonusState->m_confirmSelection = 1;
					Sound.PlaySe(3, 0x40, 0x7f, 0);
				}
			}
		} else if (this->m_menuWindowInfo->state == 2) {
			if (this->m_menuWindowInfo->frame - 1 <= 0 && this->m_bonusState->m_confirmSelection == 0) {
				this->m_bonusState->m_selectionDelay = 10;
				this->m_bonusState->m_selectionResult = -1;
			}
		}
	} else {
		if ((int)this->m_bonusState->m_selectionDelay == 0 && this->m_bonusState->m_currentRank < activePartyCount) {
			int padSlot = s_Rinfo->m_party[i].m_partySlot;
			unsigned short repeat = Pad.GetButtonRepeat(padSlot);
			unsigned short down = Pad.GetButtonDown(padSlot);
			if ((repeat & 9) != 0) {
				this->m_bonusState->m_selection++;
				if (this->m_bonusState->m_selection > 7) {
					this->m_bonusState->m_selection = 0;
				}
				Sound.PlaySe(0x4e, 0x40, 0x7f, 0);
			} else if ((repeat & 6) != 0) {
				this->m_bonusState->m_selection--;
				if (this->m_bonusState->m_selection < 0) {
					this->m_bonusState->m_selection = 7;
				}
				Sound.PlaySe(0x4e, 0x40, 0x7f, 0);
			}

			if ((repeat & 0xf) == 0) {
				int unavailableMask = ((int)(signed char)s_Rinfo->m_selectedArtifactMask | (int)(signed char)s_Rinfo->m_missingArtifactMask)
				    | s_Rinfo->m_party[i].m_ownedArtifactMask;
				if ((down & 0x100) != 0) {
					if (!((unavailableMask & (1 << this->m_bonusState->m_selection)) == 0)) {
						Sound.PlaySe(4, 0x40, 0x7f, 0);
					} else {
						this->m_bonusState->m_selectionDelay = 10;
						this->m_bonusState->m_selectionResult = 1;
						Sound.PlaySe(0x4f, 0x40, 0x7f, 0);
					}
				} else if ((down & 0x200) != 0) {
					short winW;
					short winH;
					GetWinSize(0x18, &winW, &winH, 1);
					SetMcWinInfo((int)winW, (int)winH);
					this->m_menuWindowInfo->state = 0;
					this->m_bonusState->m_confirmSelection = 1;
					Sound.PlaySe(3, 0x40, 0x7f, 0);
				}
			}
		} else if (this->m_bonusState->m_currentRank < activePartyCount) {
			this->m_bonusState->m_selectionDelay--;
			if (this->m_bonusState->m_selectionDelay == 0) {
				if (this->m_bonusState->m_selectionResult > 0) {
					int bit = 1 << this->m_bonusState->m_selection;
					s_Rinfo->m_selectedArtifactMask = (unsigned char)(s_Rinfo->m_selectedArtifactMask | bit);
					s_Rinfo->m_party[i].m_selectedSlot = this->m_bonusState->m_selection;
					s_Rinfo->m_party[i].m_selectedItemId = s_Rinfo->m_artifacts[this->m_bonusState->m_selection];
				}
				if (this->m_bonusState->m_currentRank < activePartyCount) {
					this->m_bonusState->m_currentRank++;
				}
				this->m_bonusState->m_selectionResult = 0;
			}
		} else {
			this->m_bonusState->m_selectionDelay = 0;
		}
	}

	short count2;
	{
		CMenuPcs::Sprt2* spr2 = &m_bonusAnim->sprites[2];
		count2 = m_bonusAnim->header.count;
		spr2->x = (short)(int)s_Base[0][this->m_bonusState->m_selection * 2 + 2];
		spr2 = &m_bonusAnim->sprites[2];
		spr2->y = (short)(int)s_Base[0][this->m_bonusState->m_selection * 2 + 3];
		if (spr2->timer < spr2->duration) {
			spr2->alpha = (float)spr2->timer / (float)spr2->duration;
			spr2->timer++;
		} else {
			spr2->alpha = FLOAT_80331EB0;
		}
	}
	{
		CMenuPcs::Sprt2* cursor = &m_bonusAnim->sprites[count2 - 1];
		if (this->m_bonusState->m_currentRank < activePartyCount) {
			CMenuPcs::Sprt2* partySprite = cursor - (activePartyCount * 2 - this->m_bonusState->m_currentRank);
			int pulseFrame = frame % 20 - 10;
			if (pulseFrame < 0) {
				pulseFrame = -pulseFrame;
			}
			cursor->x = (short)(partySprite->x - 3);
			cursor->y = (short)(partySprite->y - 8);
			cursor->alpha = (float)((double)pulseFrame / DOUBLE_80331F30);
		} else {
			cursor->alpha = kBonusZClearOrigin;
		}
	}

	Mtx scaleMtx;
	Mtx rotMtx;
	Mtx tempMtx;
	Mtx tempMtx2;
	Vec srcVec;
	Vec dstVec;
	{
		int doubleCount = activePartyCount * 2;
		for (i = 0; i < activePartyCount + 8; i++) {
			CMenuPcs::Sprt2* alphaSprite = &m_bonusAnim->sprites[(int)(signed char)s_PlayerTop + i];
			CCharaPcs::CHandle* handle;
			int tribeOrSlot;
			if (i < activePartyCount) {
				tribeOrSlot = s_Rinfo->m_party[i].m_tribeId;
				handle = s_Rinfo->m_party[i].m_partyHandle;
				float modelScale = s_PCScl[tribeOrSlot];
				PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
			} else {
				tribeOrSlot = doubleCount + (i - activePartyCount);
				handle = m_wm.m_handles[tribeOrSlot];
				if (handle == 0) {
					continue;
				}
				PSMTXScale(scaleMtx, FLOAT_80331F00, FLOAT_80331F00, FLOAT_80331F00);
			}

			if (i < activePartyCount) {
				scaleMtx[0][3] = kBonusZClearOrigin;
				scaleMtx[1][3] = s_PCYpos[tribeOrSlot];
				scaleMtx[2][3] = kBonusZClearOrigin;
			} else {
				int artifactIndex = i - activePartyCount;
				srcVec.x = s_AnimX[0];
				srcVec.y = kBonusZClearOrigin;
				srcVec.z = kBonusZClearOrigin;
				PSMTXRotRad(rotMtx, 'z', FLOAT_80331F04 * (float)(DOUBLE_80331F08 * (double)artifactIndex));
				PSMTXMultVecSR(rotMtx, &srcVec, &dstVec);

				if (handle->m_charaNo == 0x44u) {
					PSMTXRotRad(tempMtx, 'y', FLOAT_80331F10);
					PSMTXConcat(scaleMtx, tempMtx, scaleMtx);
					PSMTXRotRad(tempMtx2, 'x', FLOAT_80331F14);
					PSMTXConcat(scaleMtx, tempMtx2, scaleMtx);
				}

				scaleMtx[0][3] = dstVec.x;
				float modelY = (float)((double)(FLOAT_80331F18 * dstVec.y) - DOUBLE_80331F20);
				if (handle->m_charaNo == 0x41u || handle->m_charaNo == 0x37u) {
					modelY += FLOAT_80331F28;
				} else if (handle->m_charaNo == 0x44u) {
					modelY += FLOAT_80331F2C;
				}
				scaleMtx[1][3] = modelY;
				scaleMtx[2][3] = kBonusZClearOrigin;
			}

			((BonusModelFlags*)&handle->m_model->m_flags10C)->m_visible = 1;
			handle->m_model->SetMatrix(scaleMtx);
			handle->m_model->CalcMatrix();
			handle->m_model->CalcSkin();
			handle->m_model->m_lightAlpha = alphaSprite->alpha;
		}
	}

	if (this->m_bonusState->m_currentRank >= activePartyCount && this->m_bonusState->m_selectionDelay == 0) {
		if (this->m_bonusState->m_finishDelay >= 10) {
			this->m_bonusState->m_finishDelay = 0;
			i = 0;
			m_bonusAnim->header.finished = 1;
			for (; i < activePartyCount; i++) {
				int itemId = s_Rinfo->m_party[i].m_selectedItemId;
				int partySlot = s_Rinfo->m_party[i].m_partySlot;
				if (itemId > 0) {
					if (itemId < 0xff) {
						int artIdx = itemId - 0x9f;
						CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[partySlot]);
						caravanWork->m_artifacts[artIdx] = static_cast<unsigned short>(itemId);
					} else {
						CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[partySlot]);
						caravanWork->AddItem(itemId, 0);
					}
				}
			}
		} else {
			this->m_bonusState->m_finishDelay++;
		}
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 372b
 * EN Address: 0x8015D868
 * EN Size: 560b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::DrawBonusChkMark(float artiAlpha)
{
	if (!((double)artiAlpha <= DOUBLE_80331E90)) {
		_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
		GXColor markColor;
		markColor.r = 0xFF;
		markColor.g = 0xFF;
		markColor.b = 0xFF;
		markColor.a = (unsigned char)(FLOAT_80331E98 * artiAlpha);
		GXSetChanMatColor(GX_COLOR0A0, markColor);
		MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x23));

		unsigned int activeMask = 0;
		for (int i = 0; i < s_Rinfo->m_partyCount; i++) {
			int selection = s_Rinfo->m_party[i].m_selectedSlot;
			if (selection >= 0) {
				activeMask |= 1 << selection;
			}
		}

		{
			int i = 0;
			for (; i < 8; i++) {
				if ((activeMask & (1 << i)) == 0) {
					continue;
				}
				float x = s_Base[0][i * 2 + 2] + FLOAT_80331E9C;
				float y = s_Base[0][i * 2 + 3] + FLOAT_80331EA0;
				MenuPcs.DrawRect(0, x, y, FLOAT_80331EA4, FLOAT_80331EA8, kBonusZClearOrigin, kBonusZClearOrigin, FLOAT_80331EB0, FLOAT_80331EB0, kBonusZClearOrigin);
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x80135258
 * PAL Size: 2824b
 * EN Address: 0x8015A968
 * EN Size: 2976b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawSelectOpenAnim()
{
	if (this->m_bonusState->m_initialized == 0) {
		return;
	}

	int idx;
	int activePartyCount = s_Rinfo->m_partyCount;
	CMenuPcs::Sprt2* sprite;

	DrawInit();
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	int doubleCount;
	int modelIndex = 0;
	int i;
	int kind;
	doubleCount = activePartyCount * 2;

	int lastKind =  (int)(unsigned int)(0);
	CMenuPcs::Sprt2* artiSprite = 0;
	for (i = 0; i < (int)m_bonusAnim->header.count; i++) {
		sprite = &m_bonusAnim->sprites[i];
		kind = sprite->kind;
		if (kind >= 0 || kind != -1) {
			if (kind == -3) {
				DrawBonusFrame((float)sprite->x, (float)sprite->y, (float)sprite->w, (float)sprite->h, sprite->alpha);
				lastKind = sprite->kind;
			} else if (kind == -4) {
				if (artiSprite == 0) {
					artiSprite = sprite;
				}
				DrawArtiBase((CMenuPcs::Sprt2*)sprite, sprite->alpha);
				lastKind = sprite->kind;
			} else if (kind == -2) {
				CCharaPcs::CHandle* handle;
				if (modelIndex < activePartyCount) {
					for (int j = 0; j < activePartyCount; j++) {
						if (modelIndex == s_Rinfo->m_party[j].m_rank) {
							idx = j;
							break;
						}
					}
					handle = s_Rinfo->m_party[idx].m_partyHandle;
					SetProjection(modelIndex);
				} else {
					idx = doubleCount + (modelIndex - activePartyCount);
					handle = m_wm.m_handles[idx];
					if (handle == 0) {
						lastKind = kind;
						modelIndex++;
						continue;
					}
					SetProjection(idx);
				}
				SetLight(1);
				unsigned int oldFlags = handle->m_flags;
				handle->m_flags = 0x300543;
				handle->Draw(5);
				handle->m_flags = oldFlags;
				if (modelIndex >= activePartyCount) {
					PartPcs.DrawMenuIdx(m_effectWork[idx].m_partNo);
				}
				RestoreProjection();
				lastKind = sprite->kind;
				modelIndex++;
			} else {
				if (lastKind < 0) {
					DrawInit();
					MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
				}
				GXColor color;
				color.r = 0xFF;
				color.g = 0xFF;
				color.b = 0xFF;
				color.a = (unsigned char)(FLOAT_80331E98 * sprite->alpha);
				GXSetChanMatColor(GX_COLOR0A0, color);
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(sprite->kind));
				if (sprite->kind == 0x20) {
					_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
				}
				MenuPcs.DrawRect(0,
				    (float)sprite->x + sprite->motionX, (float)sprite->y + sprite->motionY,
				    (float)sprite->w, (float)sprite->h,
				    sprite->mulX, sprite->mulY, sprite->depth, sprite->depth, kBonusZClearOrigin);
				if (sprite->kind == 0x20) {
					_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
				}
				lastKind = sprite->kind;
			}
		}
	}

	DrawBonusChkMark(artiSprite->alpha);

	DrawInit();
	CFont* font = this->m_fonts[0];
	font->SetMargin(FLOAT_80331EB0);
	font->SetShadow(1);
	font->SetScale(FLOAT_80331F38);
	font->SetTlut(7);
	font->DrawInit();

	int textIndex = 0;
	char text[268];
	{
		int i = 0;
		for (; i < (int)m_bonusAnim->header.count && textIndex < activePartyCount; i++) {
			sprite = &m_bonusAnim->sprites[i];
			if (sprite->kind != -1) {
				continue;
			}
			CColor color(0xFF, 0xFF, 0xFF, (unsigned char)(FLOAT_80331E98 * sprite->alpha));
			font->SetColor(color.color);

			for (int j = 0; j < activePartyCount; j++) {
				if (textIndex == s_Rinfo->m_party[j].m_rank) {
					idx = j;
					break;
				}
			}
			int partySlot = s_Rinfo->m_party[idx].m_partySlot;
			if (textIndex < activePartyCount) {
				CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[partySlot]);
				strcpy(text, reinterpret_cast<char*>(caravanWork->m_name));
			}

			float x = (float)sprite->x + sprite->motionX;
			float y = (float)sprite->y + sprite->motionY;
			if (textIndex < activePartyCount) {
				y -= FLOAT_80331F3C;
			}
			font->SetPosX(x);
			font->SetPosY(y - FLOAT_80331F3C);
			font->Draw(text);
			textIndex++;
		}
	}

	if (this->m_bonusState->m_phase == 4
	    && s_Rinfo->m_artifacts[this->m_bonusState->m_selection] > 0) {
		{
			for (int i = 0; i < (int)m_bonusAnim->header.count; i++) {
				sprite = &m_bonusAnim->sprites[i];
				if (sprite->kind == -3) {
					break;
				}
			}
		}

		font = this->m_fonts[1];
		font->SetMargin(FLOAT_80331EB0);
		font->SetShadow(0);
		font->SetScaleX(FLOAT_80331F40);
		font->SetScaleY(FLOAT_80331F44);
		font->DrawInit();
		CColor color(0xFF, 0xFF, 0xFF, 0xFF);
		font->SetColor(color.color);

		idx = (int)s_Rinfo->m_artifacts[this->m_bonusState->m_selection];
		char* title = Game.m_cFlatDataArr[1].TableStrings(0)[idx * 5 + 4];
		float centerX = (float)((double)sprite->x + (double)(float)sprite->w * DOUBLE_80331E78);
		float centerY = (float)((double)sprite->y + (double)(float)sprite->h * DOUBLE_80331E78);
		font->SetPosX((float)-(DOUBLE_80331E78 * (double)font->GetWidth(title) - (double)centerX));
		font->SetPosY(centerY - FLOAT_80331F48 - FLOAT_80331F3C);
		font->Draw(title);

		char* source = new (MenuPcs.m_menuStage, "bonus_menu.cpp", 0xA9C) char[0x200];
		if ((source == 0) && ((unsigned int)System.m_execParam >= 1)) {
			System.Printf("%s(%d): Error: memory allocation error\n", "bonus_menu.cpp", 0xA9F);
		}
		memset(source, 0, 0x200);
		char* converted = new (MenuPcs.m_menuStage, "bonus_menu.cpp", 0xAA5) char[0x200];
		if ((converted == 0) && ((unsigned int)System.m_execParam >= 1)) {
			System.Printf("%s(%d): Error: memory allocation error\n", "bonus_menu.cpp", 0xAA8);
		}
		memset(converted, 0, 0x200);
		strcpy(source, Game.m_cFlatDataArr[1].TableStrings(6)[idx]);
		CMes::MakeAgbString(converted, source, 0, 0);
		strlen(converted);

		float lineY = centerY - FLOAT_80331F4C - FLOAT_80331F50;
		for (int line = 0;; line++) {
			char* lineText = (line != 0) ? strtok(0, const_cast<char*>(lbl_80331F54)) : strtok(converted, const_cast<char*>(lbl_80331F54));
			if (lineText == 0) {
				break;
			}
			font->SetPosX((float)-(DOUBLE_80331E78 * (double)font->GetWidth(lineText) - (double)centerX));
			font->SetPosY(lineY - FLOAT_80331F3C);
			font->Draw(lineText);
			lineY += FLOAT_80331F58;
		}

		delete[] source;
		delete[] converted;
	}

	DrawInit();
	if (this->m_menuWindowInfo->state == 3) {
		return;
	}

	DrawMcWin(-1, 1);
	if (this->m_menuWindowInfo->state == 1) {
		DrawMcWinMess(0x18, 1);
		DrawInit();
		float cursorY = (float)(this->m_menuWindowInfo->y + this->m_menuWindowInfo->height - 0x3e);
		float cursorX = (float)GetYesNoXPos((int)this->m_bonusState->m_confirmSelection);
		DrawCursor((int)cursorX, (int)cursorY, FLOAT_80331EB0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80135D60
 * PAL Size: 4668b
 * EN Address: 0x8015946C
 * EN Size: 5372b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcSelectOpenAnim()
{
	int activePartyCount = s_Rinfo->m_partyCount;
	int frame;
	int doneCount;
	int twice;
	CMenuPcs::Sprt2* iconSprite;
	int i;
	int tribeId;
	CCharaPcs::CHandle* handle;
	int total;

	if (this->m_bonusState->m_initialized == 0) {
		int idx;

		this->m_bonusCursorFlag = 0;
		Sound.PlaySe(0x4c, 0x40, 0x7f, 0);
		memset(m_bonusAnim, 0, sizeof(BonusAnimList));

		idx = 0;
		{
			CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[idx];
			spr->kind = 0x16;
			spr->y = 0;
			spr->x = 0;
			spr->w = 0x280;
			spr->h = 0x1c0;
			spr->mulY = kBonusZClearOrigin;
			spr->mulX = kBonusZClearOrigin;
			spr->startFrame = 0;
			spr->duration = 0;
			spr->depth = FLOAT_80331EB0;
			spr->flags = 3;
			idx = 1;
		}
		{
			CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[idx];
			spr->kind = -3;
			spr->x = 0xf0;
			spr->y = 0x38;
			spr->w = 0x168;
			spr->h = 0x148;
			spr->mulY = kBonusZClearOrigin;
			spr->mulX = kBonusZClearOrigin;
			spr->startFrame = 0;
			spr->duration = 8;
			spr->depth = FLOAT_80331EB0;
			idx = 2;
		}
		{
			CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[idx];
			spr->kind = 0x1f;
			spr->x = 0;
			spr->y = 0;
			spr->w = 0x80;
			spr->h = 0x78;
			spr->mulY = kBonusZClearOrigin;
			spr->mulX = kBonusZClearOrigin;
			spr->startFrame = 9999;
			spr->duration = 8;
			spr->depth = FLOAT_80331EB0;
			spr->motionX = FLOAT_80331F5C;
			spr->motionY = FLOAT_80331F5C;
			spr->flags = 2;
			idx = 3;
		}
		{
			CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[idx];
			spr->kind = -4;
			spr->x = 0;
			spr->y = 0;
			spr->w = 0x70;
			spr->h = 0x68;
			spr->mulY = kBonusZClearOrigin;
			spr->mulX = kBonusZClearOrigin;
			spr->startFrame = 0;
			spr->duration = 8;
			spr->depth = FLOAT_80331EB0;
			idx = 4;
		}

		int top;
		int y = 0x28;
		for (int i = 0; i < activePartyCount; i++) {
			int partySlot;
			for (int j = 0; activePartyCount > j; j++) {
				if (i == s_Rinfo->m_party[j].m_rank) {
					partySlot = s_Rinfo->m_party[j].m_partySlot;
					break;
				}
			}
			CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[4 + i];
			spr->kind = 0x18;
			spr->x = ((1 <= i) && (i <= 2)) ? 0x30 : 0x48;
			spr->y = y;
			spr->w = 0x60;
			spr->h = 0x58;
			spr->mulX = (float)((partySlot & 1) ? spr->w : 0);
			spr->mulY = (float)((partySlot >> 1) ? spr->h : 0);
			spr->startFrame = 0;
			spr->duration = 8;
			spr->depth = FLOAT_80331EB0;
			spr->motionX = FLOAT_80331F60;
			spr->motionY = kBonusZClearOrigin;
			spr->targetX = (float)spr->x + spr->motionX;
			spr->targetY = (float)spr->y + spr->motionY;
			spr->flags = 1;
			y += 0x60;
		}

		top = activePartyCount + 4;
		s_PlayerTop = (unsigned char)top;
		for (int i = 0; i < activePartyCount; i++) {
			CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[top + i];
			spr->kind = -2;
			spr->x = 0;
			spr->y = 0;
			spr->w = 0;
			spr->h = 0;
			spr->mulX = kBonusZClearOrigin;
			spr->mulY = kBonusZClearOrigin;
			spr->startFrame = (spr - activePartyCount)->startFrame;
			spr->duration = 8;
			spr->depth = FLOAT_80331EB0;
			spr->motionX = FLOAT_80331F60;
			spr->motionY = kBonusZClearOrigin;
			spr->targetX = (float)spr->x + spr->motionX;
			spr->targetY = (float)spr->y + spr->motionY;
			spr->flags = 1;
		}

		top += activePartyCount;
		s_ArtiTop = (unsigned char)top;
		{
			int start = 10;
			for (int i = 0; i < 8; i++) {
				CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[top + i];
				spr->kind = -2;
				spr->x = 0;
				spr->y = 0;
				spr->w = 0;
				spr->h = 0;
				spr->mulX = kBonusZClearOrigin;
				spr->mulY = kBonusZClearOrigin;
				spr->startFrame = start;
				spr->startFrame = (int)(FLOAT_80331F64 * (float)spr->startFrame);
				spr->duration = 0x21;
				spr->depth = FLOAT_80331EB0;
				spr->flags = 1;
				start += 5;
			}
		}

		int copyDelta = top + 4;
		top += 8;
		for (int i = 0; i < activePartyCount; i++) {
			CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[top + i];
			*spr = *(spr - copyDelta);
			spr->y = (short)(spr->y + 0x20);
			spr->w = 0xA8;
			spr->h = 0x38;
			spr->mulX = kBonusZClearOrigin;
			spr->mulY = FLOAT_80331F68;
			spr->motionX = FLOAT_80331F60;
			spr->motionY = kBonusZClearOrigin;
			spr->targetX = (float)spr->x + spr->motionX;
			spr->targetY = (float)spr->y + spr->motionY;
			spr->flags = 1;
		}

		top += activePartyCount;
		y = 0x28;
		for (int i = 0; i < activePartyCount; i++) {
			CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[top + i];
			spr->kind = 0x19;
			spr->x = ((1 <= i) && (i <= 2)) ? 8 : 0x20;
			spr->y = y;
			spr->w = 0x38;
			spr->h = 0x28;
			spr->mulX = (float)(i * spr->w);
			spr->mulY = kBonusZClearOrigin;
			spr->startFrame = 0;
			spr->duration = 8;
			spr->depth = FLOAT_80331EB0;
			spr->motionX = FLOAT_80331F60;
			spr->motionY = kBonusZClearOrigin;
			spr->targetX = (float)spr->x + spr->motionX;
			spr->targetY = (float)spr->y + spr->motionY;
			spr->flags = 1;
			y += 0x60;
		}

		top += activePartyCount;
		int nameDelta = top - 4;
		for (int i = 0; i < activePartyCount; i++) {
			CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[top + i];
			CMenuPcs::Sprt2* prev = spr - nameDelta;
			spr->kind = -1;
			spr->x = (short)(prev->x + 0x50);
			spr->y = (short)(prev->y + 0x48);
			spr->w = 0;
			spr->h = 0;
			spr->mulX = kBonusZClearOrigin;
			spr->mulY = kBonusZClearOrigin;
			spr->startFrame = prev->startFrame;
			spr->duration = 8;
			spr->depth = FLOAT_80331EB0;
			spr->motionX = FLOAT_80331F60;
			spr->motionY = kBonusZClearOrigin;
			spr->targetX = (float)spr->x + spr->motionX;
			spr->targetY = (float)spr->y + spr->motionY;
			spr->flags = 1;
		}

		top += activePartyCount;
		{
			CMenuPcs::Sprt2* p3 = &m_bonusAnim->sprites[3];
			ArtiBaseInfoInit(p3 - 2, p3);
		}
		{
			Sprt2* frameSprite = &m_bonusAnim->sprites[1];
			for (int i = 0; i < 8; i++) {
				m_wm.m_worldObjData[activePartyCount * 2 + i].m_transform.Identity();
				m_wm.m_worldObjData[activePartyCount * 2 + i].m_active = 0;
				m_wm.m_worldObjData[activePartyCount * 2 + i].m_frameCounter = 0;
				int centerX = (int)((double)(float)((double)frameSprite->w * DOUBLE_80331E78 + (double)frameSprite->x) - DOUBLE_80331EE8);
				m_wm.m_worldObjData[activePartyCount * 2 + i].m_viewportX = (short)centerX;
				int centerY = (int)((double)(float)((double)frameSprite->h * DOUBLE_80331E78 + (double)frameSprite->y) - DOUBLE_80331EF0);
				m_wm.m_worldObjData[activePartyCount * 2 + i].m_viewportY = (short)centerY;
				m_wm.m_worldObjData[activePartyCount * 2 + i].m_viewportWidth = 0x280;
				m_wm.m_worldObjData[activePartyCount * 2 + i].m_viewportHeight = 0x1C0;
				m_wm.m_worldObjData[activePartyCount * 2 + i].m_cameraPosition.x = kBonusZClearOrigin;
				m_wm.m_worldObjData[activePartyCount * 2 + i].m_cameraPosition.y = kBonusZClearOrigin;
				m_wm.m_worldObjData[activePartyCount * 2 + i].m_cameraPosition.z = FLOAT_80331F6C;
				m_wm.m_worldObjData[activePartyCount * 2 + i].m_scissorX = 0;
				m_wm.m_worldObjData[activePartyCount * 2 + i].m_scissorY = 0;
				m_wm.m_worldObjData[activePartyCount * 2 + i].m_scissorWidth = 0x280;
				m_wm.m_worldObjData[activePartyCount * 2 + i].m_scissorHeight = 0x1C0;
			}
		}

		m_bonusAnim->header.count = (short)top;
		m_bonusAnim->header.finished = 0;
		this->m_bonusState->m_initialized = 1;
	}

	this->m_bonusState->m_frame++;
	frame = (int)this->m_bonusState->m_frame;
	int i0 = 0;

	doneCount = 0;

	for (; i0 < (int)m_bonusAnim->header.count; i0++) {
		CMenuPcs::Sprt2* sprite = &m_bonusAnim->sprites[i0];

		if ((sprite->flags & 1) != 0) {
			sprite->alpha = FLOAT_80331EB0;
		} else {
			if (frame < sprite->startFrame) {
				sprite->alpha = kBonusZClearOrigin;
			}
			if (sprite->startFrame + sprite->duration <= frame) {
				sprite->alpha = FLOAT_80331EB0;
			} else {
				sprite->alpha = (float)((1.0 / (double)sprite->duration) * (double)sprite->timer);
			}
		}

		if (sprite->startFrame + sprite->duration <= frame || sprite->startFrame >= 9999) {
			doneCount++;
		}

		if ((sprite->flags & 2) == 0 && (sprite->motionX != kBonusZClearOrigin || sprite->motionY != kBonusZClearOrigin)) {
			float progress = (float)(1.0 - (1.0 / (double)sprite->duration) * (double)sprite->timer);
			float fy = (float)sprite->y;
			float ty = sprite->targetY;
			sprite->motionX = (sprite->targetX - (float)sprite->x) * progress;
			sprite->motionY = (ty - fy) * progress;
		}

		if (sprite->startFrame < frame && frame <= sprite->startFrame + sprite->duration) {
			sprite->timer++;
		}
	}

	{
		int i = 0;
		for (; i < activePartyCount; i++) {
			CMenuPcs::Sprt2* sprite = &m_bonusAnim->sprites[4 + i];
			int centerX = (int)(float)((double)(float)(4.0 + ((double)sprite->w * DOUBLE_80331E78 + (double)((float)sprite->x + sprite->motionX))) - DOUBLE_80331EE8);
			int centerY = (int)(float)((double)(float)((double)sprite->h * DOUBLE_80331E78 + (double)((float)sprite->y + sprite->motionY)) - DOUBLE_80331EF0);
			m_wm.m_worldObjData[i].m_viewportX = (short)centerX;
			m_wm.m_worldObjData[i].m_viewportY = (short)centerY;
			m_wm.m_worldObjData[i].m_scissorX = (int)(FLOAT_80331EF8 + ((float)sprite->x + sprite->motionX));
			m_wm.m_worldObjData[i].m_scissorY = (int)(((float)sprite->y + sprite->motionY) - FLOAT_80331EFC);
			if ((double)m_wm.m_worldObjData[i].m_scissorX < 0.0) {
				m_wm.m_worldObjData[i].m_scissorX = 0;
			}
			if ((double)m_wm.m_worldObjData[i].m_scissorY < 0.0) {
				m_wm.m_worldObjData[i].m_scissorY = 0;
			}
			m_wm.m_worldObjData[i].m_scissorWidth = 0x48;
			m_wm.m_worldObjData[i].m_scissorHeight = 0x58;
		}
	}

	Mtx scaleMtx;
	Mtx rotZMtx;
	Mtx rotYMtx;
	Mtx rotXMtx;
	Vec srcVec;
	Vec dstVec;
	{
		i = 0;
		twice = activePartyCount * 2;
		total = activePartyCount + 8;
		for (; i < total; i++) {
			iconSprite = &m_bonusAnim->sprites[(int)(signed char)s_PlayerTop + i];
			if (i < activePartyCount) {
				tribeId = s_Rinfo->m_party[i].m_tribeId;
				handle = s_Rinfo->m_party[i].m_partyHandle;
				float modelScale = s_PCScl[tribeId];
				PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
			} else {
				tribeId = twice + (i - activePartyCount);
				handle = m_wm.m_handles[tribeId];
				if (handle == 0) {
					continue;
				}
				PSMTXScale(scaleMtx, FLOAT_80331F00, FLOAT_80331F00, FLOAT_80331F00);
			}
			if (i < activePartyCount) {
				scaleMtx[0][3] = kBonusZClearOrigin;
				scaleMtx[1][3] = s_PCYpos[tribeId];
				scaleMtx[2][3] = kBonusZClearOrigin;
			} else {
				int duration = iconSprite->duration;
				int artifactIndex = i - activePartyCount;
				int fcvIndex = duration / 5;
				int rem = 8 - artifactIndex;
				int phase = (int)(((double)duration / 10.0) * (double)(rem + 2));
				float rate = (float)(450.0 / (double)(float)duration);

				if (frame == iconSprite->startFrame && *(signed char*)&this->m_bonusCursorFlag == 0) {
					this->m_bonusCursorFlag = 1;
					Sound.PlaySe(0x4d, 0x40, 0x7f, 0);
				}

				float angle;
				if (frame < iconSprite->startFrame) {
					srcVec.x = s_AnimX[2];
					angle = FLOAT_80331F78;
				} else if (iconSprite->timer >= phase) {
					srcVec.x = s_AnimX[0];
					angle = (float)(DOUBLE_80331F80 * (double)rem);
				} else {
					int last = iconSprite->timer - 1;
					if (last <= fcvIndex) {
						srcVec.x = s_AnimX[2] -
						    (float)last * ((s_AnimX[2] - s_AnimX[1]) / (float)fcvIndex);
					} else {
						srcVec.x = s_AnimX[1] -
						    ((s_AnimX[1] - s_AnimX[0]) /
						    ((float)phase - (float)fcvIndex)) *
						    (float)(last - fcvIndex);
					}
					angle = (float)(DOUBLE_80331F88 + (double)(rate * (float)last));
				}
				srcVec.y = kBonusZClearOrigin;
				srcVec.z = kBonusZClearOrigin;
				PSMTXRotRad(rotZMtx, 'z', FLOAT_80331F04 * angle);
				PSMTXMultVecSR(rotZMtx, &srcVec, &dstVec);

				if ((unsigned int)handle->m_charaNo == 0x44) {
					PSMTXRotRad(rotYMtx, 'y', FLOAT_80331F10);
					PSMTXConcat(scaleMtx, rotYMtx, scaleMtx);
					PSMTXRotRad(rotXMtx, 'x', FLOAT_80331F14);
					PSMTXConcat(scaleMtx, rotXMtx, scaleMtx);
				}

				scaleMtx[0][3] = dstVec.x;
				float modelY = (float)((double)(FLOAT_80331F18 * dstVec.y) - DOUBLE_80331F20);
				if ((unsigned int)handle->m_charaNo == 0x41 || (unsigned int)handle->m_charaNo == 0x37) {
					modelY += FLOAT_80331F28;
				} else if ((unsigned int)handle->m_charaNo == 0x44) {
					modelY += FLOAT_80331F2C;
				}
				scaleMtx[1][3] = modelY;
				scaleMtx[2][3] = kBonusZClearOrigin;
			}

			handle->m_model->m_flags10CBits.m_flag10C_80 = 1;
			handle->m_model->SetMatrix(scaleMtx);
			handle->m_model->CalcMatrix();
			handle->m_model->CalcSkin();
			handle->m_model->m_lightAlpha = iconSprite->alpha;
		}
	}

	if ((int)m_bonusAnim->header.count == doneCount) {
		m_bonusAnim->header.finished = 1;
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 572b
 * EN Address: 0x8015CE84
 * EN Size: 672b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::DrawBonusCnt(CMenuPcs::Sprt2* sprite, int value)
{
	int digits[3];
	int digitCount;

	if (value >= 100) {
		digitCount = 3;
		digits[0] = value / 100;
		value %= 100;
		digits[1] = value / 10;
		digits[2] = value % 10;
	} else if (value >= 10) {
		digitCount = 2;
		digits[0] = value / 10;
		digits[1] = value % 10;
	} else {
		digitCount = 1;
		digits[0] = value;
	}

	float digitX = (float)((DOUBLE_80331EC8 * (double)sprite->w - (float)(digitCount * sprite->w)) * DOUBLE_80331E78 + (double)sprite->x);
	float digitW = (float)sprite->w;
	int* dp = digits;
	for (int digitIndex = 0; digitIndex < digitCount; digitIndex++) {
		MenuPcs.DrawRect(0, digitX, (float)sprite->y, digitW, (float)sprite->h,
		    (float)(sprite->w * *dp), sprite->mulY,
		    sprite->depth, sprite->depth, kBonusZClearOrigin);
		digitX += digitW;
		dp++;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80136F9C
 * PAL Size: 2452b
 * EN Address: 0x80158B34
 * EN Size: 2360b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawResultCloseAnim()
{
	if (this->m_bonusState->m_initialized == 0) {
		return;
	}

	int activePartyCount = s_Rinfo->m_partyCount;

	DrawInit();
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	int modelIndex = 0;
	int lastKind = 0;

	for (int i = 0; i < (int)m_bonusAnim->header.count; i++) {
		CMenuPcs::Sprt2* sprite = &m_bonusAnim->sprites[i];

		if (sprite->kind >= 0 || sprite->kind == -2) {
			if (sprite->kind == -2) {
				CCharaPcs::CHandle* handle;
				if (modelIndex < activePartyCount) {
					handle = s_Rinfo->m_party[modelIndex].m_partyHandle;
				} else if (modelIndex / activePartyCount > 1) {
					modelIndex++;
					continue;
				} else {
					handle = m_wm.m_handles[modelIndex - activePartyCount];
				}

				if ((double)handle->m_model->m_lightAlpha <= DOUBLE_80331E90) {
					modelIndex++;
					continue;
				}
				SetProjection(modelIndex);
				SetLight(1);
				unsigned int oldFlags = handle->m_flags;
				handle->m_flags = 0x300543;
				handle->Draw(5);
				handle->m_flags = oldFlags;
				RestoreProjection();
				lastKind = sprite->kind;
				modelIndex++;
				continue;
			} else {
				if (lastKind < 0) {
					DrawInit();
				}
				if (lastKind != 0x17 && sprite->kind == 0x17) {
					MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(1));
				} else if (lastKind == 0x17 && sprite->kind != 0x17) {
					MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
				}

				_GXColor colors[4];
				if (sprite->kind == 0x17) {
					colors[0].r = 0xFF;
					colors[0].g = 0xFF;
					colors[0].b = 0xFF;
					colors[0].a = 0xFF;
					colors[1].r = 0xFF;
					colors[1].g = 0xFF;
					colors[1].b = 0xFF;
					colors[1].a = 0xFF;
					colors[2].r = 0xFF;
					colors[2].g = 0xFF;
					colors[2].b = 0xFF;
					colors[2].a = 0xFF;
					colors[3].r = 0xFF;
					colors[3].g = 0xFF;
					colors[3].b = 0xFF;
					colors[3].a = 0xFF;
					GXSetChanMatColor(GX_COLOR0A0, colors[0]);
				}
				if (sprite->kind != 0x17) {
					colors[0].r = 0xFF;
					colors[0].g = 0xFF;
					colors[0].b = 0xFF;
					colors[0].a = (unsigned char)(FLOAT_80331E98 * sprite->alpha);
					GXSetChanMatColor(GX_COLOR0A0, colors[0]);
				}
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(sprite->kind));

				if (sprite->kind == 0x17) {
					if (sprite->duration <= sprite->timer) {
						lastKind = sprite->kind;
						continue;
					}
					{
						float x = (float)sprite->x;
						float y = (float)sprite->y;
						float fillWidth;
						if (sprite->duration > sprite->timer) {
							fillWidth = (float)(DOUBLE_80331ED8 - (DOUBLE_80331ED8 / (double)sprite->duration) * (double)(sprite->timer - 1));
							if (fillWidth < kBonusZClearOrigin) {
								fillWidth = kBonusZClearOrigin;
							}
						} else {
							fillWidth = kBonusZClearOrigin;
						}
						float mulX = sprite->mulX;
						fillWidth *= (float)sprite->w;
						if (fillWidth > kBonusZClearOrigin) {
							MenuPcs.DrawRect(0, x, y, fillWidth, (float)sprite->h,
							    mulX, sprite->mulY, colors, FLOAT_80331EB0, FLOAT_80331EB0, kBonusZClearOrigin);
							x += fillWidth;
						}
						if (fillWidth < (float)sprite->w) {
							colors[1].r = 0xFF;
							colors[1].g = 0xFF;
							colors[1].b = 0xFF;
							colors[1].a = 0;
							colors[3].r = 0xFF;
							colors[3].g = 0xFF;
							colors[3].b = 0xFF;
							colors[3].a = 0;
							MenuPcs.DrawRect(0, x, y, (float)(DOUBLE_80331ED8 / (double)sprite->duration) * (float)sprite->w, (float)sprite->h,
							    fillWidth, sprite->mulY, colors, FLOAT_80331EB0, FLOAT_80331EB0, kBonusZClearOrigin);
						}
					}
				} else {
					if ((signed char)s_CntTop <= i && i < (signed char)s_CntTop + activePartyCount) {
						int value = s_Rinfo->m_party[i - (signed char)s_CntTop].m_totalValue;
						DrawBonusCnt(sprite, value);
					} else {
						MenuPcs.DrawRect(0, (float)sprite->x + sprite->motionX, (float)sprite->y + sprite->motionY,
						    (float)sprite->w, (float)sprite->h,
						    sprite->mulX, sprite->mulY, sprite->depth, sprite->depth, kBonusZClearOrigin);
					}
				}
				lastKind = sprite->kind;
			}
		}
	}

	DrawInit();
	CFont* font0 = this->m_fonts[0];
	CFont* font = font0;
	font0->SetMargin(FLOAT_80331EB0);
	font0->SetShadow(1);
	font0->SetScale(FLOAT_80331F38);
	font0->SetTlut(7);
	font0->DrawInit();

	int textIndex = 0;
	char text[128];
	{
		int i = 0;
		for (; i < (int)m_bonusAnim->header.count; i++) {
			CMenuPcs::Sprt2* sprite = &m_bonusAnim->sprites[i];
			if (sprite->kind == -1) {
				font->SetColor(CColor(0xFF, 0xFF, 0xFF, (unsigned char)(FLOAT_80331E98 * sprite->alpha)).color);

				int partyIndex = textIndex % activePartyCount;
				int partySlot = s_Rinfo->m_party[partyIndex].m_partySlot;
				if (textIndex < activePartyCount) {
					CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[partySlot]);
					strcpy(text, reinterpret_cast<char*>(caravanWork->m_name));
				} else {
					CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[partySlot]);
					strcpy(text, Game.m_cFlatDataArr[1].TableStrings(7)[(int)caravanWork->m_bonusCondition * 2 + 1]);
				}

				float x = (float)sprite->x + sprite->motionX;
				float y = (float)sprite->y + sprite->motionY;
				if (textIndex < activePartyCount) {
					y -= FLOAT_80331F3C;
				}
				font->SetPosX(x);
				font->SetPosY(y - FLOAT_80331F3C);
				font->Draw(text);

				textIndex++;
				if (textIndex == activePartyCount) {
					CFont* font1 = this->m_fonts[1];
					font = font1;
					font1->SetMargin(FLOAT_80331EB0);
					font1->SetShadow(0);
					font1->SetScaleX(FLOAT_80331F90);
					font1->SetScaleY(FLOAT_80331EB0);
					font1->DrawInit();
				}
			}
		}
	}
	DrawInit();
}

/*
 * --INFO--
 * PAL Address: 0x80137930
 * PAL Size: 8676b
 * EN Address: 0x80157E64
 * EN Size: 3280b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcResultCloseAnim()
{
	int doneCount;
	int delta;
	const int activePartyCount = s_Rinfo->m_partyCount;

	if (this->m_bonusState->m_initialized == 0) {
		for (int i = 0; i < (int)m_bonusAnim->header.count; i++) {
			m_bonusAnim->sprites[i].timer = 0;
			m_bonusAnim->sprites[i].motionX = kBonusZClearOrigin;
			m_bonusAnim->sprites[i].motionY = kBonusZClearOrigin;
		}

		{
			int idx = 0;
			CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[idx];
			spr->startFrame = 9999;
			spr->flags = 3;
		}

		for (int i = 0; activePartyCount > i; i++) {
			Sprt2* sprite = &m_bonusAnim->sprites[i + 1];
			sprite->startFrame = 0x10;
		}

		int base = activePartyCount + 1;

		for (int i = 0; i < activePartyCount; i++) {
			Sprt2* spr = &m_bonusAnim->sprites[base + i];
			Sprt2* src = spr - activePartyCount;
			spr->startFrame = src->startFrame + src->duration;
			spr->flags = 1;
			spr->targetX = (float)spr->x;
			spr->motionX = FLOAT_80331ED0;
			spr->x = (short)(int)((float)spr->x - spr->motionX);
		}

		base += activePartyCount;
		for (int i = 0; i < activePartyCount; i++) {
			Sprt2* sprite = &m_bonusAnim->sprites[base + i];
			Sprt2* source = sprite - activePartyCount;
			sprite->startFrame = source->startFrame + source->duration;
			sprite->flags = 1;
		}

		base += activePartyCount;
		for (int i = 0; i < activePartyCount; i++) {
			Sprt2* sprite = &m_bonusAnim->sprites[base + i];
			sprite->startFrame = 0;
		}

		base += activePartyCount;
		for (int i = 0; i < activePartyCount; i++) {
			Sprt2* sprite = &m_bonusAnim->sprites[base + i];
			sprite->startFrame = 9999;
			sprite->flags = 3;
		}

		base += activePartyCount;
		{
			int back = base - (activePartyCount + 1);

			for (int i = 0; activePartyCount > i; i++) {
				Sprt2* spr = &m_bonusAnim->sprites[base + i];
				Sprt2* src = spr - back;
				spr->startFrame = src->startFrame;
				spr->flags = 1;
				spr->targetX = (float)spr->x;
				spr->motionX = FLOAT_80331ED0;
				spr->x = (unsigned short)(int)((float)spr->x - spr->motionX);
			}
		}

		base += activePartyCount;
		{
			Sprt2* sprite = &m_bonusAnim->sprites[base];
			sprite->startFrame = m_bonusAnim->sprites[1].startFrame;
		}
		base += 1;
		s_CntTop = (signed char)base;

		for (int i = 0; i < activePartyCount; i++) {
			Sprt2* sprite = &m_bonusAnim->sprites[base + i];
			sprite->startFrame = 8;
			sprite->duration = 8;
		}

		base += activePartyCount;
		{
			int back = base - (activePartyCount + 1);

			for (int i = 0; i < activePartyCount; i++) {
				Sprt2* spr = &m_bonusAnim->sprites[base + i];
				Sprt2* src = spr - back;
				spr->startFrame = src->startFrame;
				spr->flags = 1;
				spr->targetX = (float)spr->x;
				spr->motionX = FLOAT_80331ED0;
				spr->x = (unsigned short)(int)((float)spr->x - spr->motionX);
			}
		}

		base += activePartyCount;
		for (int i = 0; i < activePartyCount; i++) {
			Sprt2* sprite = &m_bonusAnim->sprites[base + i];
			sprite->startFrame = 0;
		}

		base += activePartyCount;
		{
			int back = activePartyCount;

			for (int i = 0; i < activePartyCount; i++) {
				Sprt2* spr = &m_bonusAnim->sprites[base + i];
				Sprt2* src = spr - back;
				spr->startFrame = src->startFrame;
				spr->flags = 1;
				spr->targetX = (float)spr->x;
				spr->motionX = FLOAT_80331ED0;
				spr->x = (short)(int)((float)spr->x - spr->motionX);
			}
		}

		{
			int i = 0;
			for (; i < m_bonusAnim->header.count; i++) {
				Sprt2* sprite = &m_bonusAnim->sprites[i];
				if (kBonusZClearOrigin == sprite->motionX) {
					sprite->targetX = (float)(int)sprite->x;
				}
				if (kBonusZClearOrigin == sprite->motionY) {
					sprite->targetY = (float)(int)sprite->y;
				}

			}
		}

		m_bonusAnim->header.finished = 0;
		this->m_bonusState->m_initialized = 1;
	}

	doneCount = 0;
	this->m_bonusState->m_frame++;
	int frame = (int)this->m_bonusState->m_frame;

	for (int i = 0; i < m_bonusAnim->header.count; i++) {
		CMenuPcs::Sprt2* sprite = &m_bonusAnim->sprites[i];

		if ((sprite->flags & 1) != 0) {
			sprite->alpha = FLOAT_80331EB0;
		} else {
			if (sprite->startFrame > frame) {
				sprite->alpha = FLOAT_80331EB0;
			}
			if (sprite->startFrame + sprite->duration <= frame) {
				sprite->alpha = kBonusZClearOrigin;
			} else {
				sprite->alpha = (float)(DOUBLE_80331ED8 - (DOUBLE_80331ED8 / (double)sprite->duration) * (double)sprite->timer);
			}
		}

		if (sprite->startFrame + sprite->duration <= frame || sprite->startFrame >= 9999) {
			doneCount++;
		}

		if ((sprite->flags & 2) == 0 && (sprite->motionX != kBonusZClearOrigin || sprite->motionY != kBonusZClearOrigin)) {
			float fy = (float)sprite->y;
			float ty = sprite->targetY;
			float progress = (float)(DOUBLE_80331ED8 - (DOUBLE_80331ED8 / (double)sprite->duration) * (double)sprite->timer);
			sprite->motionX = (sprite->targetX - (float)sprite->x) * progress;
			sprite->motionY = (ty - fy) * progress;
		}

		if (sprite->startFrame < frame && frame <= sprite->startFrame + sprite->duration) {
			sprite->timer++;
		}

	}

	{
		int i = 0;
		int base2 = activePartyCount + 1;
		for (; i < activePartyCount; i++) {
			CMenuPcs::Sprt2* sprite = &m_bonusAnim->sprites[base2 + i];
			int centerX = (int)(float)((double)(float)(DOUBLE_80331EE0 + ((double)sprite->w * DOUBLE_80331E78 + (double)((float)sprite->x + sprite->motionX))) - DOUBLE_80331EE8);
			int centerY = (int)(float)((double)(float)((double)sprite->h * DOUBLE_80331E78 + (double)((float)sprite->y + sprite->motionY)) - DOUBLE_80331EF0);
			m_wm.m_worldObjData[i].m_viewportX = (short)centerX;
			m_wm.m_worldObjData[i].m_viewportY = (short)centerY;
			m_wm.m_worldObjData[i].m_scissorX = (int)(FLOAT_80331EF8 + ((float)sprite->x + sprite->motionX));
			m_wm.m_worldObjData[i].m_scissorY = (int)(((float)sprite->y + sprite->motionY) - FLOAT_80331EFC);
			if ((double)m_wm.m_worldObjData[i].m_scissorX < DOUBLE_80331E90) {
				m_wm.m_worldObjData[i].m_scissorX = 0;
			}
			if ((double)m_wm.m_worldObjData[i].m_scissorY < DOUBLE_80331E90) {
				m_wm.m_worldObjData[i].m_scissorY = 0;
			}
			m_wm.m_worldObjData[i].m_scissorWidth = 0x48;
			m_wm.m_worldObjData[i].m_scissorHeight = 0x58;
		}
	}
	Mtx scaleMtx;
	Mtx rotXMtx;
	Mtx rotYMtx;
	{
		int total2 = activePartyCount * 2;
		int i = 0;

		for (; i < total2; i++) {
			CMenuPcs::Sprt2* alphaSprite = &m_bonusAnim->sprites[total2 + 1 + i];
			CCharaPcs::CHandle* handle;
			if (i < activePartyCount) {
				handle = s_Rinfo->m_party[i].m_partyHandle;
				delta = s_Rinfo->m_party[i].m_tribeId;
			} else {
				handle = m_wm.m_handles[i - activePartyCount];
			}
			if (i < activePartyCount) {
				float modelScale = s_PCScl[delta];
				PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
			} else {
				PSMTXScale(scaleMtx, FLOAT_80331EB0, FLOAT_80331EB0, FLOAT_80331EB0);
			}

			if (i / activePartyCount == 1) {
				PSMTXRotRad(rotXMtx, 'x', FLOAT_80331F94);
				PSMTXConcat(scaleMtx, rotXMtx, scaleMtx);
				PSMTXRotRad(rotYMtx, 'y', FLOAT_80331F04 * this->m_bonusState->m_modelRotation);
				PSMTXConcat(scaleMtx, rotYMtx, scaleMtx);
			}

			if (i < activePartyCount) {
				scaleMtx[0][3] = kBonusZClearOrigin;
				scaleMtx[2][3] = kBonusZClearOrigin;
				scaleMtx[1][3] = s_PCYpos[delta];
			} else {
				scaleMtx[0][3] = kBonusZClearOrigin;
				scaleMtx[1][3] = kBonusZClearOrigin;
				scaleMtx[2][3] = kBonusZClearOrigin;
			}

			handle->m_model->m_flags10CBits.m_flag10C_80 = 1;
			handle->m_model->SetMatrix(scaleMtx);
			handle->m_model->CalcMatrix();
			handle->m_model->CalcSkin();
			if (i < activePartyCount) {
				handle->m_model->m_lightAlpha = FLOAT_80331EB0;
			} else {
				handle->m_model->m_lightAlpha = alphaSprite->alpha;
			}

		}
	}

	if (m_bonusAnim->header.count == doneCount) {
		m_bonusAnim->header.finished = 1;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80139B14
 * PAL Size: 1816b
 * EN Address: 0x801578B0
 * EN Size: 1460b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawResultCountAnim()
{
	if (this->m_bonusState->m_initialized == 0) {
		return;
	}

	int activePartyCount = s_Rinfo->m_partyCount;

	DrawInit();
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	int modelIndex = 0;
	int lastKind = 0;
	int i = 0;

	int doubleCount = activePartyCount * 2;
	for (; i < (int)m_bonusAnim->header.count; i++) {
		CMenuPcs::Sprt2* sprite = &m_bonusAnim->sprites[i];

		if (sprite->kind >= 0 || sprite->kind == -2) {
			if (sprite->kind == -2) {
				CCharaPcs::CHandle* handle = 0;
				if (modelIndex < activePartyCount) {
					handle = s_Rinfo->m_party[modelIndex].m_partyHandle;
				} else if (modelIndex < doubleCount) {
					int __p11 = modelIndex;
					handle = m_wm.m_handles[__p11 - activePartyCount];
				} else {
					continue;
				}

				SetProjection(modelIndex);
				SetLight(1);
				unsigned int oldFlags = handle->m_flags;
				handle->m_flags = 0x300543;
				handle->Draw(5);
				handle->m_flags = oldFlags;
				RestoreProjection();
				lastKind = sprite->kind;
				modelIndex++;
			} else {
				if (lastKind < 0) {
					DrawInit();
					MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
				}
				_GXColor color;
				color.r = 0xFF;
				color.g = 0xFF;
				color.b = 0xFF;
				color.a = (unsigned char)(sprite->alpha * 255.0f);
				GXSetChanMatColor(GX_COLOR0A0, color);
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(sprite->kind));

				if ((signed char)s_CntTop <= i && i < (signed char)s_CntTop + activePartyCount) {
					int total = s_Rinfo->m_party[i - (signed char)s_CntTop].m_totalValue;
					int value;
					if (this->m_bonusState->m_countFinished == 0) {
						double frame = (double)this->m_bonusState->m_frame - DOUBLE_80331F98;
						if (frame <= DOUBLE_80331E90) {
							value = 0;
						} else if (frame < (double)total) {
							value = (int)frame;
						} else {
							value = total;
						}
					} else {
						value = total;
					}
					DrawBonusCnt(sprite, value);
				} else {
					MenuPcs.DrawRect(0, (float)sprite->x + sprite->motionX, (float)sprite->y + sprite->motionY,
					    (float)sprite->w, (float)sprite->h,
					    sprite->mulX, sprite->mulY, sprite->depth, sprite->depth, kBonusZClearOrigin);
				}
				lastKind = sprite->kind;
			}
		}
	}

	DrawInit();
	CFont* font = this->m_fonts[0];
	font->SetMargin(1.0f);
	font->SetShadow(1);
	font->SetScale(0.7300000190734863f);
	font->SetTlut(7);
	font->DrawInit();

	int textIndex = 0;
	char text[128];
	for (i = 0; i < (int)m_bonusAnim->header.count; i++) {
		Sprt2* sprite = &m_bonusAnim->sprites[i];
		if (sprite->kind == -1) {
			CColor color(0xFF, 0xFF, 0xFF, 0xFF);
			font->SetColor(color.color);

			int partyIndex = textIndex % activePartyCount;
			int partySlot = s_Rinfo->m_party[partyIndex].m_partySlot;
			if (textIndex < activePartyCount) {
				int __p12 = partySlot;
				CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[__p12]);
				strcpy(text, reinterpret_cast<char*>(caravanWork->m_name));
			} else {
				CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[partySlot]);
				int strIdx = (int)caravanWork->m_bonusCondition * 2 + 1;
				int __p2 = strIdx;
				strcpy(text, Game.m_cFlatDataArr[1].TableStrings(7)[__p2]);
			}

			float x = (float)sprite->x + sprite->motionX;
			float y = (float)sprite->y + sprite->motionY;
			if (textIndex < activePartyCount) {
				y -= FLOAT_80331F3C;
			}
			font->SetPosX(x);
			font->SetPosY(y - FLOAT_80331F3C);
			font->Draw(text);

			textIndex++;
			if (textIndex == activePartyCount) {
				font = this->m_fonts[1];
				font->SetMargin(1.0f);
				font->SetScaleX(0.7f);
				font->SetScaleY(1.0f);
				font->SetShadow(0);
				font->DrawInit();
			}
		}
	}
	DrawInit();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 152b
 * EN Address: 0x8015DED0
 * EN Size: 132b
 * JP Address: TODO
 * JP Size: TODO
 */
inline unsigned int CMenuPcs::GetAllPadOn()
{
	unsigned int buttons = 0;
	for (int i = 0; i < s_Rinfo->m_partyCount; i++) {
		buttons |= Pad.GetButtonDown(s_Rinfo->m_party[i].m_partySlot);
	}
	return buttons;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 152b
 * EN Address: UNUSED
 * EN Size: 132b
 * JP Address: TODO
 * JP Size: TODO
 */
inline unsigned int CMenuPcs::GetAllPadRep()
{
	unsigned int buttons = 0;
	for (int i = 0; i < s_Rinfo->m_partyCount; i++) {
		buttons |= Pad.GetButtonRepeat(s_Rinfo->m_party[i].m_partySlot);
	}
	return buttons;
}

/*
 * --INFO--
 * PAL Address: 0x8013A22C
 * PAL Size: 1736b
 * EN Address: 0x80157290
 * EN Size: 1568b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcResultCountAnim()
{
	const int activePartyCount = s_Rinfo->m_partyCount;

	if (this->m_bonusState->m_initialized == 0) {
		int countTop = m_bonusAnim->header.count;
		short y = 0x28;
		for (int i = 0; i < activePartyCount; i++) {
			int rank = s_Rinfo->m_party[i].m_rank;
			CMenuPcs::Sprt2* sprite = &m_bonusAnim->sprites[countTop + i];
			sprite->kind = 0x19;
			short stripX = ((1 <= i) && (i <= 2)) ? 8 : 0x20;
			sprite->x = stripX;
			sprite->y = y;
			sprite->w = 0x38;
			y += 0x60;
			sprite->h = 0x28;
			sprite->mulX = (float)(rank * sprite->w);
			sprite->mulY = 0.0f;
			sprite->startFrame = 9999;
			sprite->duration = 4;
			sprite->depth = 1.0f;
			sprite->motionX = 0.0f;
			sprite->motionY = 0.0f;
			sprite->targetX = (float)(sprite->x - 0x60);
			sprite->targetY = (float)(sprite->y - 0x40);
			sprite->timer = 0;
		}

		int newCount = countTop + activePartyCount;
		for (int i = 0; i < 0x18; i++) {
			CCharaPcs::CHandle* handle = m_wm.m_handles[i];
			if (handle != 0) {
				handle->m_model->m_lightAlpha = 0.0f;
			}
		}

		m_bonusAnim->header.count = (short)newCount;
		this->m_bonusState->m_initialized = 1;
	}

	if (this->m_bonusState->m_countFinished == 0) {
		this->m_bonusState->m_frame++;
	}

	int countTop = (int)m_bonusAnim->header.count - activePartyCount;
	int frame;
	frame = (int)this->m_bonusState->m_frame - 8;

	for (int i = 0; i < activePartyCount; i++) {
		CMenuPcs::Sprt2* sprite = &m_bonusAnim->sprites[countTop + i];
		if (this->m_bonusState->m_countFinished != 0) {
			sprite->motionX = 0.0f;
			sprite->motionY = 0.0f;
			sprite->alpha = 1.0f;
		} else {
			int value = s_Rinfo->m_party[i].m_totalValue;
			if (frame == value) {
				Sound.PlaySe(0x4b, 0x40, 0x7f, 0);
				sprite->startFrame = frame;
			}

			if (frame < sprite->startFrame) {
				sprite->alpha = 0.0f;
			} else {
				int elapsed = frame - sprite->startFrame;
				sprite->alpha = 1.0f;
				if (elapsed < sprite->duration) {
					float dx = sprite->targetX - static_cast<float>(sprite->x);
					float dy = sprite->targetY - static_cast<float>(sprite->y);
					double progress = 1.0 - static_cast<double>(static_cast<float>(elapsed) / static_cast<float>(sprite->duration));
					sprite->motionX = static_cast<float>(dx * progress);
					sprite->motionY = static_cast<float>(dy * progress);
				} else {
					sprite->motionX = 0.0f;
					sprite->motionY = 0.0f;
				}
			}
		}
	}

	Mtx scaleMtx;
	Mtx rotXMtx;
	Mtx rotYMtx;
	int tribeId;
	for (int i = 0; i < activePartyCount * 2; i++) {
		CCharaPcs::CHandle* handle;
		if (i < activePartyCount) {
			handle = s_Rinfo->m_party[i].m_partyHandle;
			tribeId = s_Rinfo->m_party[i].m_tribeId;
		} else {
			handle = m_wm.m_handles[i - activePartyCount];
		}

		if (i < activePartyCount) {
			float modelScale = s_PCScl[tribeId];
			PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
		} else {
			PSMTXScale(scaleMtx, 1.0f, 1.0f, 1.0f);
		}

		if (i / activePartyCount == 1) {
			PSMTXRotRad(rotXMtx, 'x', 0.2617993950843811f);
			PSMTXConcat(scaleMtx, rotXMtx, scaleMtx);
			PSMTXRotRad(rotYMtx, 'y', 0.01745329238474369f * this->m_bonusState->m_modelRotation);
			PSMTXConcat(scaleMtx, rotYMtx, scaleMtx);
		}

		if (i < activePartyCount) {
			scaleMtx[0][3] = 0.0f;
			scaleMtx[2][3] = 0.0f;
			scaleMtx[1][3] = s_PCYpos[tribeId];
		} else {
			scaleMtx[0][3] = 0.0f;
			scaleMtx[1][3] = 0.0f;
			scaleMtx[2][3] = 0.0f;
		}

		handle->m_model->m_flags10CBits.m_flag10C_80 = 1;
		handle->m_model->SetMatrix(scaleMtx);
		handle->m_model->CalcMatrix();
		handle->m_model->CalcSkin();
		handle->m_model->m_lightAlpha = 1.0f;
	}

	if (this->m_bonusState->m_countFinished == 0 && frame >= 0 && !(s_Rinfo->m_winnerTotalValue < frame)) {
		Sound.PlaySe(0x4a, 0x40, 0x7f, 0);
	}

	if (this->m_bonusState->m_countFinished == 0 && frame >= 0 &&
	    (double)s_Rinfo->m_winnerTotalValue + 8.333333134651184 <= (double)frame) {
		this->m_bonusState->m_countFinished = 1;
		return;
	}

	if (this->m_bonusState->m_countFinished != 0) {
		unsigned int buttons = GetAllPadOn();
		if ((buttons & 0x300) != 0) {
			Sound.PlaySe(2, 0x40, 0x7f, 0);
			m_bonusAnim->header.finished = 1;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013A8F4
 * PAL Size: 2136b
 * EN Address: 0x801569A8
 * EN Size: 2280b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawResultOpenAnim()
{
	int activePartyCount;
	CMenuPcs::Sprt2* sprite;
	int modelIndex;
	int lastKind;
	int i;

	if (this->m_bonusState->m_initialized != 0) {
		activePartyCount = s_Rinfo->m_partyCount;

		DrawInit();
		MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

		modelIndex = 0;
		lastKind = 0;
		i = 0;
		for (; i < (int)m_bonusAnim->header.count; i++) {
			sprite = &m_bonusAnim->sprites[i];

			if (sprite->kind >= 0 || sprite->kind == -2) {
				if (sprite->kind == -2) {
					CCharaPcs::CHandle* handle;
					if (modelIndex < activePartyCount) {
						handle = s_Rinfo->m_party[modelIndex].m_partyHandle;
					} else {
						handle = m_wm.m_handles[modelIndex - activePartyCount];
					}

					if ((double)handle->m_model->m_lightAlpha <= DOUBLE_80331E90) {
						modelIndex++;
						continue;
					}
					int __p15 = modelIndex;
					SetProjection(__p15);
					SetLight(1);
					handle->m_flags = 0x300543;
					handle->Draw(5);
					RestoreProjection();
					lastKind = sprite->kind;
					modelIndex++;
				} else {
					if (lastKind < 0) {
						DrawInit();
					}
					if (lastKind != 0x17 && sprite->kind == 0x17) {
						MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(1));
					} else if (lastKind == 0x17 && sprite->kind != 0x17) {
						MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
					}

					_GXColor colors[4];
					if (sprite->kind == 0x17) {
						colors[0].r = 0xFF;
						colors[0].g = 0xFF;
						colors[0].b = 0xFF;
						colors[0].a = 0xFF;
						colors[1].r = 0xFF;
						colors[1].g = 0xFF;
						colors[1].b = 0xFF;
						colors[1].a = 0xFF;
						colors[2].r = 0xFF;
						colors[2].g = 0xFF;
						colors[2].b = 0xFF;
						colors[2].a = 0xFF;
						colors[3].r = 0xFF;
						colors[3].g = 0xFF;
						colors[3].b = 0xFF;
						colors[3].a = 0xFF;
						GXSetChanMatColor(GX_COLOR0A0, colors[0]);
					}
					if (sprite->kind != 0x17) {
						colors[0].r = 0xFF;
						colors[0].g = 0xFF;
						colors[0].b = 0xFF;
						colors[0].a = (unsigned char)(FLOAT_80331E98 * sprite->alpha);
						GXSetChanMatColor(GX_COLOR0A0, colors[0]);
					}
					MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(sprite->kind));

					if (sprite->kind == 0x17) {
						float x = (float)sprite->x;
						float y = (float)sprite->y;
						float fillWidth;
						if (sprite->duration > sprite->timer) {
							fillWidth = (float)((DOUBLE_80331ED8 / (double)sprite->duration) * (double)(sprite->timer - 1));
							if (fillWidth < kBonusZClearOrigin) {
								fillWidth = kBonusZClearOrigin;
							}
						} else {
							fillWidth = FLOAT_80331EB0;
						}
						float mulX = sprite->mulX;
						fillWidth *= (float)sprite->w;
						if (fillWidth > kBonusZClearOrigin) {
							MenuPcs.DrawRect(0, x, y, fillWidth, (float)sprite->h,
							    mulX, sprite->mulY, colors, FLOAT_80331EB0, FLOAT_80331EB0, kBonusZClearOrigin);
							x += fillWidth;
						}
						if (fillWidth > kBonusZClearOrigin && fillWidth < (float)sprite->w) {
							colors[1].r = 0xFF;
							colors[1].g = 0xFF;
							colors[1].b = 0xFF;
							colors[1].a = 0;
							colors[3].r = 0xFF;
							colors[3].g = 0xFF;
							colors[3].b = 0xFF;
							colors[3].a = 0;
							MenuPcs.DrawRect(0, x, y, (float)(DOUBLE_80331ED8 / (double)sprite->duration) * (float)sprite->w, (float)sprite->h,
							    fillWidth, sprite->mulY, colors, FLOAT_80331EB0, FLOAT_80331EB0, kBonusZClearOrigin);
						}
					} else {
						if ((signed char)i >= s_CntTop && i < (signed char)s_CntTop + activePartyCount) {
							DrawBonusCnt(sprite, 0);
						} else {
							MenuPcs.DrawRect(0, (float)sprite->x + sprite->motionX, (float)sprite->y + sprite->motionY,
							    (float)sprite->w, (float)sprite->h,
							    sprite->mulX, sprite->mulY, sprite->depth, sprite->depth, kBonusZClearOrigin);
						}
					}
					lastKind = sprite->kind;
				}
			}
		}

		DrawInit();
		CFont* font = this->m_fonts[0];
		font->SetMargin(FLOAT_80331EB0);
		font->SetShadow(1);
		font->SetScale(FLOAT_80331F38);
		font->SetTlut(7);
		font->DrawInit();

		int textIndex = 0;
		char text[128];
		{
			int i = 0;
			for (; i < (int)m_bonusAnim->header.count; i++) {
				CMenuPcs::Sprt2* sprite = &m_bonusAnim->sprites[i];
				if (sprite->kind == -1) {
					font->SetColor(CColor(0xFF, 0xFF, 0xFF, (unsigned char)(FLOAT_80331E98 * sprite->alpha)).color);

					int partyIndex = textIndex % activePartyCount;
					int partySlot = s_Rinfo->m_party[partyIndex].m_partySlot;
					if (textIndex < activePartyCount) {
						CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[partySlot]);
						strcpy(text, reinterpret_cast<char*>(caravanWork->m_name));
					} else {
						CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[partySlot]);
						int strIdx = (int)caravanWork->m_bonusCondition * 2 + 1;
						strcpy(text, Game.m_cFlatDataArr[1].TableStrings(7)[strIdx]);
					}

					float x = (float)sprite->x + sprite->motionX;
					float y = (float)sprite->y + sprite->motionY;
					if (textIndex < activePartyCount) {
						y -= FLOAT_80331F3C;
					}
					font->SetPosX(x);
					font->SetPosY(y - FLOAT_80331F3C);
					font->Draw(text);

					textIndex++;
					if (textIndex == activePartyCount) {
						font = this->m_fonts[1];
						font->SetMargin(FLOAT_80331EB0);
						font->SetShadow(0);
						font->SetScaleX(FLOAT_80331F90);
						font->SetScaleY(FLOAT_80331EB0);
						font->DrawInit();
					}
				}
			}
		}
		DrawInit();
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013B14C
 * PAL Size: 8316b
 * EN Address: 0x801557EC
 * EN Size: 4540b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcResultOpenAnim()
{
	const int activePartyCount = s_Rinfo->m_partyCount;

	if (this->m_bonusState->m_initialized == 0) {
		int idx;

		this->m_bonusAlpha = 0;
		Sound.PlaySe(0x46, 0x40, 0x7f, 0);
		memset(m_bonusAnim, 0, sizeof(BonusAnimList));

		idx = 0;
		{
			CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[idx];
			spr->kind = 0x16;
			spr->y = 0;
			spr->x = 0;
			spr->w = 0x280;
			spr->h = 0x1c0;
			spr->mulY = 0.0f;
			spr->mulX = 0.0f;
			spr->startFrame = 0;
			spr->duration = 8;
			spr->depth = 1.0f;
			spr->alpha = 0.0f;
		}

		for (int i = 0; i < activePartyCount; i++) {
			CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[i + 1];
			spr->kind = 0x17;
			spr->x = 0x80;
			spr->y = (short)(i * 0x60 + 0x38);
			spr->w = 0x1a0;
			spr->h = 0x40;
			spr->mulX = 0.0f;
			spr->mulY = 0.0f;
			spr->duration = 8;
			spr->depth = 1.0f;
		}
		int base = activePartyCount + 1;
		{
			int i = 0;
			int backOffset = base;
			int y = 0x28;
			for (; i < activePartyCount; i++) {
				CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[base + i];
				int partySlot = s_Rinfo->m_party[i].m_partySlot;
				spr->kind = 0x18;
				spr->x = ((1 <= i) && (i <= 2)) ? 0x30 : 0x48;
				spr->y = (short)y;
				spr->w = 0x60;
				spr->h = 0x58;
				spr->mulX = (float)((partySlot & 1) ? spr->w : 0);
				spr->mulY = (float)((partySlot >> 1) ? spr->h : 0);
				if (i == 0) {
					CMenuPcs::Sprt2* src = spr - backOffset;
					spr->startFrame = src->startFrame + src->duration;
					spr->startFrame += 0x18;
				} else {
					spr->startFrame = (spr - 1)->startFrame + 3;
				}
				spr->duration = 8;
				y += 0x60;
				spr->depth = 1.0f;
			}
		}

		// model sprites: startFrame chained from icons
		base += activePartyCount;
		{
			for (int i = 0; i < activePartyCount; i++) {
				int delta = base - (activePartyCount + 1);
				CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[base + i];
				spr->kind = -2;
				CMenuPcs::Sprt2* src = spr - delta;
				spr->x = 0;
				spr->y = 0;
				spr->w = 0;
				spr->h = 0;
				spr->mulX = 0.0f;
				spr->mulY = 0.0f;
				spr->startFrame = src->startFrame + src->duration;
				spr->duration = 8;
				spr->depth = 1.0f;
			}
		}

		// zeroed model sprites; startFrame fixed up later
		base += activePartyCount;
		int zeroBase = base;
		if (0 < activePartyCount) {
			for (int i = 0; i < activePartyCount; i++) {
				CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[base + i];
				spr->kind = -2;
				spr->x = 0;
				spr->y = 0;
				spr->w = 0;
				spr->h = 0;
				spr->mulX = 0.0f;
				spr->mulY = 0.0f;
				spr->duration = 8;
				spr->depth = 1.0f;
			}
		}

		// staggered model sprites
		base += activePartyCount;
		{
			int i = 0;
			int bump = i;
			for (; i < activePartyCount; i++) {
				int delta = base;
				CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[base + i];
				spr->kind = -2;
				CMenuPcs::Sprt2* src = spr - delta;
				spr->x = 0;
				spr->y = 0;
				spr->w = 0;
				spr->h = 0;
				spr->mulX = 0.0f;
				spr->mulY = 0.0f;
				spr->startFrame = src->startFrame + src->duration;
				if (i != 0) {
					spr->startFrame += bump;
				}
				spr->duration = 0x20;
				bump += 3;
				spr->depth = 1.0f;
			}
		}

		// icon echo sprites (copies shifted down)
		base += activePartyCount;
		{
			for (int i = 0; i < activePartyCount; i++) {
				int delta = base - (activePartyCount + 1);
				CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[base + i];
				CMenuPcs::Sprt2* src = spr - delta;
				*spr = *src;
				spr->y = (short)(spr->y + 0x20);
				spr->w = 0xA8;
				spr->h = 0x38;
				spr->mulX = 0.0f;
				spr->mulY = 176.0f;
			}
		}

		base += activePartyCount;

		// frame rows start after their icons
		if (0 < activePartyCount) {
			for (int i = 0; i < activePartyCount; i++) {
				Sprt2* spr = &m_bonusAnim->sprites[i + 1];
				Sprt2* src = spr + activePartyCount;
				spr->startFrame = src->startFrame + src->duration;
			}
		}

		// zeroed model sprites follow the frame rows
		for (int i = 0; i < activePartyCount; i++) {
			Sprt2* spr = &m_bonusAnim->sprites[zeroBase + i];
			Sprt2* src = spr - (zeroBase - 1);
			spr->startFrame = src->startFrame + src->duration;
		}

		{
			CMenuPcs::Sprt2* count = &m_bonusAnim->sprites[base];
			count->kind = 0x19;
			count->y = 0x10;
			count->w = 0x140;
			count->x = (short)((0x280 - count->w) >> 1);
			count->h = 0x28;
			count->mulX = 0.0f;
			count->mulY = 80.0f;
			count->startFrame = m_bonusAnim->sprites[1].startFrame;
			count->duration = 8;
			count->duration = 10;
			count->depth = 1.0f;
		}
		int countTop = base + 1;
		s_CntTop = (signed char)countTop;

		{
			for (int i = 0; i < activePartyCount; i++) {
				int delta = base;
				CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[countTop + i];
				spr->kind = 0x19;
				CMenuPcs::Sprt2* src = spr - delta;
				spr->x = 0x200;
				spr->y = (short)(src->y + 0xC);
				spr->w = 0x20;
				spr->h = 0x28;
				spr->mulX = 0.0f;
				spr->mulY = 40.0f;
				spr->startFrame = src->startFrame + src->duration;
				spr->duration = 8;
				spr->depth = 1.0f;
			}
		}

		// name sprites
		base = countTop + activePartyCount;
		{
			for (int i = 0; i < activePartyCount; i++) {
				int delta = base - (activePartyCount + 1);
				CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[base + i];
				spr->kind = -1;
				CMenuPcs::Sprt2* src = spr - delta;
				spr->x = (short)(src->x + 0x50);
				spr->y = (short)(src->y + 0x48);
				spr->w = 0;
				spr->h = 0;
				spr->mulX = 0.0f;
				spr->mulY = 0.0f;
				spr->startFrame = src->startFrame;
				spr->duration = 8;
				spr->depth = 1.0f;
			}
		}

		// value text sprites
		base += activePartyCount;
		{
			for (int i = 0; i < activePartyCount; i++) {
				int delta = base - 1;
				CMenuPcs::Sprt2* spr = &m_bonusAnim->sprites[base + i];
				spr->kind = -1;
				spr->x = 0xb8;
				CMenuPcs::Sprt2* src = spr - delta;
				spr->y = (short)(src->y + 0x15);
				spr->w = 0;
				spr->h = 0;
				spr->mulX = 0.0f;
				spr->mulY = 0.0f;
				spr->startFrame = src->startFrame + src->duration;
				spr->duration = 8;
				spr->depth = 1.0f;
			}
		}

		base += activePartyCount;

		{
			int i = 0;
			for (; i < activePartyCount; i++) {
				CMenuPcs::Sprt2* sprite = &m_bonusAnim->sprites[activePartyCount + i + 1];
				int centerX = (int)(float)((double)(float)(4.0 + ((double)sprite->w * 0.5 + (double)sprite->x)) - 320.0);
				int centerY = (int)(float)((double)(float)((double)sprite->h * 0.5 + (double)sprite->y) - 224.0);
				m_wm.m_worldObjData[i].m_viewportX = (short)centerX;
				m_wm.m_worldObjData[i].m_viewportY = (short)centerY;
				m_wm.m_worldObjData[i].m_scissorX = sprite->x + 0xC;
				m_wm.m_worldObjData[i].m_scissorY = sprite->y - 8;
				m_wm.m_worldObjData[i].m_scissorWidth = 0x48;
				m_wm.m_worldObjData[i].m_scissorHeight = 0x58;
			}
		}

		{
			unsigned int i = 0;
			for (; i < activePartyCount; i++) {
				CMenuPcs::Sprt2* sprite = &m_bonusAnim->sprites[(unsigned char)s_CntTop + i];
				int w3 = sprite->w * 3;
				int extent = w3 + 0x20;
				int centerX = (int)(float)((double)(float)((double)w3 * 0.5 + (double)sprite->x) - 320.0);
				int centerY = (int)(float)((double)(float)((double)sprite->h * 0.5 + (double)sprite->y) - 224.0);
				m_wm.m_worldObjData[activePartyCount + i].m_viewportX = (short)centerX;
				m_wm.m_worldObjData[activePartyCount + i].m_viewportY = (short)centerY;
				m_wm.m_worldObjData[activePartyCount + i].m_scissorX = sprite->x - 0x10;
				m_wm.m_worldObjData[activePartyCount + i].m_scissorY = sprite->y - 0x10;
				m_wm.m_worldObjData[activePartyCount + i].m_scissorWidth = extent;
				m_wm.m_worldObjData[activePartyCount + i].m_scissorHeight = extent;
			}
		}

		{
			int i = 0;
			int total2 = activePartyCount * 2;
			for (; i < activePartyCount; i++) {
				CMenuPcs::Sprt2* sprite = &m_bonusAnim->sprites[i + 1];
				m_wm.m_worldObjData[total2 + i].m_viewportX = 0;
				int centerY = (int)(float)((double)(float)((double)sprite->h * 0.5 + (double)sprite->y) - 224.0);
				m_wm.m_worldObjData[total2 + i].m_viewportY = (short)centerY;
			}
		}

		{
			for (int i = 0; i < 0x18; i++) {
				CCharaPcs::CHandle* handle = m_wm.m_handles[i];
				if (handle != 0) {
					handle->m_model->m_lightAlpha = 0.0f;
				}
			}
		}

		m_bonusAnim->header.count = (short)base;
		m_bonusAnim->header.finished = 0;
		this->m_bonusState->m_initialized = 1;
		return;
	}

	this->m_bonusState->m_frame++;
	int frame = (int)this->m_bonusState->m_frame;
	int i0 = 0;
	int doneCount = 0;

	for (; i0 < (int)m_bonusAnim->header.count; i0++) {
		Sprt2* sprite = &m_bonusAnim->sprites[i0];

		if (sprite->startFrame <= frame) {
			if (sprite->startFrame + sprite->duration <= frame) {
				doneCount++;
				sprite->alpha = 1.0f;
			} else {
				sprite->timer++;
				sprite->alpha = (float)((1.0 / (double)sprite->duration) * (double)sprite->timer);
			}

			if (sprite->kind == 0x17) {
				for (int j = 0; j < s_Rinfo->m_partyCount; j++) {
					if (sprite->timer - 1 == 0) {
						Sound.PlaySe(0x49, 0x40, 0x7f, 0);
					}
					sprite++;
				}
			}
		}
	}

	Mtx scaleMtx;
	Mtx rotXMtx;
	Mtx rotYMtx;
	{
		int i = 0;
		int total2 = activePartyCount * 2;
		int total3 = activePartyCount * 3;
		int spriteIndex = total2 + 1;
		for (; i < total3; i++, spriteIndex++) {
			Sprt2* sprite = &m_bonusAnim->sprites[spriteIndex];
			CCharaPcs::CHandle* handle;
			int tribeId;
			if (i < activePartyCount) {
				handle = s_Rinfo->m_party[i].m_partyHandle;
				tribeId = s_Rinfo->m_party[i].m_tribeId;
			} else {
				handle = m_wm.m_handles[i - activePartyCount];
			}
			if (i < activePartyCount) {
				float modelScale = s_PCScl[tribeId];
				PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
			} else if (i >= total2) {
				float modelScale = 0.5f;
				if (sprite->timer == 0x18 && m_bonusAlpha == 0) {
					Sound.PlaySe(0x48, 0x40, 0x7f, 0);
					this->m_bonusAlpha = 1;
				}
				if (sprite->timer >= 0x18) {
					modelScale = (float)(0.5 * (double)((float)(sprite->timer - 0x18) /
					                 (float)(sprite->duration - 0x18)) + (double)modelScale);
				}
				PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
			} else {
				float modelScale = 1.0f;
				PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
			}

			if (i / activePartyCount == 1) {
				PSMTXRotRad(rotXMtx, 'x', 0.2617993950843811f);
				PSMTXConcat(scaleMtx, rotXMtx, scaleMtx);
				PSMTXRotRad(rotYMtx, 'y', 0.01745329238474369f * this->m_bonusState->m_modelRotation);
				PSMTXConcat(scaleMtx, rotYMtx, scaleMtx);
			}

			if (i < activePartyCount) {
				scaleMtx[0][3] = 0.0f;
				scaleMtx[2][3] = 0.0f;
				scaleMtx[1][3] = s_PCYpos[tribeId];
			} else if (i >= total2) {
				double tx = GetFcvValue(s_BallTrnsX, (float)(sprite->timer - 1));
				scaleMtx[0][3] = tx;
				if (sprite->timer - 1 == 7) {
					Sound.PlaySe(0x47, 0x40, 0x7f, 0);
				}
				double ty = GetFcvValue(s_BallTrnsY, (float)(sprite->timer - 1));
				int itemIndex = i - total2;
				scaleMtx[1][3] = ty;
				scaleMtx[2][3] = 0.0f;
				if (1 <= itemIndex && itemIndex <= 2) {
					scaleMtx[1][3] = (float)((double)(float)ty - 1.8);
				}
			} else {
				scaleMtx[0][3] = 0.0f;
				scaleMtx[1][3] = 0.0f;
				scaleMtx[2][3] = 0.0f;
			}

			handle->m_model->m_flags10CBits.m_flag10C_80 = 1;
			handle->m_model->SetMatrix(scaleMtx);
			handle->m_model->CalcMatrix();
			handle->m_model->CalcSkin();
			if (i >= total2) {
				if (sprite->timer >= 0x18) {
					sprite->alpha = (float)(1.0 - (double)((float)(sprite->timer - 0x18) /
					                 (float)(sprite->duration - 0x18)));
					if (sprite->alpha < 0.0) {
						sprite->alpha = 0.0f;
					}
				} else {
					sprite->alpha = 1.0f;
				}
			}
			handle->m_model->m_lightAlpha = sprite->alpha;
		}
	}

	if ((int)m_bonusAnim->header.count == doneCount) {
		m_bonusAnim->header.finished = 1;
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 32b
 * EN Address: 0x8015C0C4
 * EN Size: 40b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::DrawSelectWait()
{
	DrawSelectOpenAnim();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 32b
 * EN Address: 0x8015CE5C
 * EN Size: 40b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::DrawSelectCloseAnim()
{
	DrawSelectOpenAnim();
}

/*
 * --INFO--
 * PAL Address: 0x8013D1C8
 * PAL Size: 216b
 * EN Address: 0x80155704
 * EN Size: 232b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::drawBonus()
{
	gUtil.ClearZBufferRect(kBonusZClearOrigin, kBonusZClearOrigin, kBonusZClearWidth, kBonusZClearHeight);

	if ((unsigned int)System.m_execParam >= 1) {
		System.Printf("draw Bonus (%d)\n", (int)this->m_bonusState->m_phase);
	}

	switch (this->m_bonusState->m_phase) {
	case 0:
		DrawResultOpenAnim();
		break;
	case 1:
		DrawResultCountAnim();
		break;
	case 2:
		DrawResultCloseAnim();
		break;
	case 3:
		DrawSelectOpenAnim();
		break;
	case 4:
		DrawSelectWait();
		break;
	case 5:
		DrawSelectCloseAnim();
		break;
	case 6:
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013D2A0
 * PAL Size: 368b
 * EN Address: 0x8015558C
 * EN Size: 376b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::calcBonus()
{
	this->m_bonusState->m_modelRotation =
	    static_cast<float>((double)this->m_bonusState->m_modelRotation - kPppCrystal2RefractionScale);

	if (m_bonusAnim->header.finished != 0) {
		this->m_bonusState->m_phase++;
		m_bonusAnim->header.finished = 0;
		this->m_bonusState->m_initialized = 0;
		this->m_bonusState->m_countFinished = 0;
		this->m_bonusState->m_frame = 0;
	}

	switch (this->m_bonusState->m_phase) {
	case 0:
		CalcResultOpenAnim();
		break;
	case 1:
		CalcResultCountAnim();
		break;
	case 2:
		CalcResultCloseAnim();
		break;
	case 3:
		CalcSelectOpenAnim();
		break;
	case 4:
		CalcSelectWait();
		break;
	case 5:
		CalcSelectCloseAnim();
		if (m_bonusAnim->header.finished != 0) {
			CallWorldParam(8, 0, 0);
		}
		break;
	case 6:
		for (int i = 0; i < 4; i++) {
			if (Game.m_scriptFoodBase[i] != 0) {
				reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i])->SafeDeleteTempItem();
				reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i])->SortBeforeReturnWorldMap();
			}
		}
		changeMode(static_cast<CMenuPcs::MENUMODE>(0));
		break;
	default:
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8013D410
 * PAL Size: 396b
 * EN Address: 0x801553F4
 * EN Size: 408b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::destroyBonus()
{
	Pad.m_stickDigitalThreshold = 1;

	if (this->m_fonts[1] != 0) {
		ReleaseBonusRefObject(this->m_fonts[1]);
		this->m_fonts[1] = 0;
	}

	for (int i = 0; i < 0x18; i++) {
		if (m_wm.m_handles[i] != 0) {
			delete m_wm.m_handles[i];
			m_wm.m_handles[i] = 0;
		}
	}

	CMenuPcs::EffectInfo* list = m_effectWork;
	if (list != 0) {
		delete[] list;
		m_effectWork = 0;
	}

	if (s_Rinfo != 0) {
		delete s_Rinfo;
		s_Rinfo = 0;
	}

	BonusMenuState* state = this->m_bonusState;
	if (state != 0) {
		delete state;
		this->m_bonusState = 0;
	}

	BonusAnimList* anim = m_bonusAnim;
	if (anim != 0) {
		delete anim;
		m_bonusAnim = 0;
	}

	if (s_Base[0] != 0) {
		delete reinterpret_cast<BonusBaseRaw*>(s_Base[0]);
		s_Base[0] = 0;
	}

	WmWorldObjInfo* board = m_wm.m_worldObjData;
	if (board != 0) {
		delete[] board;
		m_wm.m_worldObjData = 0;
	}

	MenuWindowInfo* window = this->m_menuWindowInfo;
	if (window != 0) {
		delete window;
		this->m_menuWindowInfo = 0;
	}

	freeTexture(2, 1, 0x16, 0x12);
}

/*
 * --INFO--
 * PAL Address: 0x8013D59C
 * PAL Size: 3300b
 * EN Address: 0x80154204
 * EN Size: 4592b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::createBonus()
{
	char fontPath[128];

	Pad.m_stickDigitalThreshold = 0x28;
	for (int i = 0; i < 4; i++) {
		GbaQue.OpenMenu(i, 0, 0);
		GbaQue.SetRadarMode(i, 0);
	}

	loadTexture(sBonusTextureSetNames, 2, 1, sBonusTextureTable, 0x16, 0x12, 0);
	sprintf(fontPath, lbl_801DD5D4, Game.GetLangString());
	loadFont(0, fontPath, 1, -1);

	s_Rinfo = new (MenuPcs.m_menuStage, "bonus_menu.cpp", 0xDD) BonusSummaryData;
	memset(s_Rinfo, 0, sizeof(*s_Rinfo));
	for (int i = 0; i < BonusSummaryData::kArtifactCount; i++) {
		s_Rinfo->m_artifacts[i] = -1;
	}

	this->m_bonusState = new (MenuPcs.m_menuStage, "bonus_menu.cpp", 0xE5) BonusMenuState;
	m_effectWork = new (MenuPcs.m_menuStage, "bonus_menu.cpp", 0xE6) EffectInfo[0x28];

	InitBonusEffectSlots(this);
	memset(this->m_bonusState, 0, sizeof(*this->m_bonusState));
	s_Base[0] = reinterpret_cast<float*>(new (MenuPcs.m_menuStage, "bonus_menu.cpp", 0xF1) BonusBaseRaw);
	memset(s_Base[0], 0, sizeof(float) * 18);
	m_bonusAnim = new (MenuPcs.m_menuStage, "bonus_menu.cpp", 0xF5) BonusAnimList;
	memset(m_bonusAnim, 0, sizeof(BonusAnimList));
	m_wm.m_worldObjData = new (MenuPcs.m_menuStage, "bonus_menu.cpp", 0xF8) WmWorldObjInfo[24];
	this->m_menuWindowInfo = new (MenuPcs.m_menuStage, "bonus_menu.cpp", 0xFA) MenuWindowInfo;
	memset(this->m_menuWindowInfo, 0, sizeof(MenuWindowInfo));
	const float depth = FLOAT_80331F6C;
	const float zero = kBonusZClearOrigin;
	for (int i = 0; i < 0x18; i++) {
		m_wm.m_worldObjData[i].m_transform.Identity();
		m_wm.m_worldObjData[i].m_active = 0;
		m_wm.m_worldObjData[i].m_frameCounter = 0;
		m_wm.m_worldObjData[i].m_viewportX = 0;
		m_wm.m_worldObjData[i].m_viewportY = 0;
		m_wm.m_worldObjData[i].m_viewportWidth = 0x280;
		m_wm.m_worldObjData[i].m_viewportHeight = 0x1c0;
		m_wm.m_worldObjData[i].m_cameraPosition.x = zero;
		m_wm.m_worldObjData[i].m_cameraPosition.y = zero;
		m_wm.m_worldObjData[i].m_cameraPosition.z = depth;
		m_wm.m_worldObjData[i].m_scissorX = 0;
		m_wm.m_worldObjData[i].m_scissorY = 0;
		m_wm.m_worldObjData[i].m_scissorWidth = 0x280;
		m_wm.m_worldObjData[i].m_scissorHeight = 0x1c0;
	}

	if (s_Rinfo != 0) {
		int activeCount = 0;
		int totalValue = 0;
		int tempArtifactCount = 0;

		for (int i = 0; i < 4; i++) {
			CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i]);
			if (caravanWork == 0) {
				continue;
			}
			if (Game.m_gameWork.m_menuStageMode != 0 && activeCount != 0) {
				break;
			}

			s_Rinfo->m_party[activeCount].m_partySlot = i;
			s_Rinfo->m_party[activeCount].m_partyHandle =
			    *reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<unsigned char*>(Game.m_partyObjArr[i]) + 0xF8);
			s_Rinfo->m_party[activeCount].m_partyHandle->m_model->m_lightAlpha = kBonusZClearOrigin;
			s_Rinfo->m_party[activeCount].m_bonusCondition = (int)reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i])->m_bonusCondition;
			int foodValue =  (int)(unsigned int)((int)reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i])->m_artifactRelated[3] + (int)reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i])->m_artifactRelated[4]);
			int foodClamped;
			if (foodValue < 0) {
				foodClamped = 0;
			} else {
				foodClamped = 100;
				if (foodValue <= 100) {
					foodClamped = foodValue;
				}
			}
			s_Rinfo->m_party[activeCount].m_foodValue = foodClamped;
			s_Rinfo->m_party[activeCount].m_artifactValue =
			    (int)reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i])->m_artifactRelated[0] + (int)reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i])->m_artifactRelated[1] - (int)reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i])->m_artifactRelated[2];
			s_Rinfo->m_party[activeCount].m_totalValue =
			    s_Rinfo->m_party[activeCount].m_foodValue + s_Rinfo->m_party[activeCount].m_artifactValue;
			s_Rinfo->m_party[activeCount].m_selectedItemId = -1;
			s_Rinfo->m_party[activeCount].m_selectedSlot = -1;
			int rawTotal = s_Rinfo->m_party[activeCount].m_totalValue;
			int totalValueClamped;
			if (rawTotal < 0) {
				totalValueClamped = 0;
			} else {
				totalValueClamped = 999;
				if (rawTotal <= 999) {
					totalValueClamped = rawTotal;
				}
			}
			s_Rinfo->m_party[activeCount].m_totalValue = totalValueClamped;
			totalValue += s_Rinfo->m_party[activeCount].m_totalValue;
			s_Rinfo->m_party[activeCount].m_tribeId = (unsigned int)reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i])->m_tribeId;
			activeCount++;

			unsigned int* slot = &Game.m_scriptFoodBase[i];
			int treasure0 = (int)reinterpret_cast<CCaravanWork*>(*slot)->m_artifacts[CCaravanWork::kPermanentArtifactCount + 0];
			if (treasure0 > 0) {
				s_Rinfo->m_artifacts[tempArtifactCount++] = (short)treasure0;
			}
			int treasure1 = (int)reinterpret_cast<CCaravanWork*>(*slot)->m_artifacts[CCaravanWork::kPermanentArtifactCount + 1];
			if (treasure1 > 0) {
				s_Rinfo->m_artifacts[tempArtifactCount++] = (short)treasure1;
			}
			int treasure2 = (int)reinterpret_cast<CCaravanWork*>(*slot)->m_artifacts[CCaravanWork::kPermanentArtifactCount + 2];
			if (treasure2 > 0) {
				s_Rinfo->m_artifacts[tempArtifactCount++] = (short)treasure2;
			}
			int treasure3 = (int)reinterpret_cast<CCaravanWork*>(*slot)->m_artifacts[CCaravanWork::kPermanentArtifactCount + 3];
			if (treasure3 > 0) {
				s_Rinfo->m_artifacts[tempArtifactCount++] = (short)treasure3;
			}
		}

		s_Rinfo->m_partyCount = activeCount;

		CGame::CBossArtifactEntry* bossArtifact = Game.GetBossArtifact(s_Rinfo->m_partyCount, totalValue);
		for (int i = 0; i < BonusSummaryData::kBossArtifactCount; i++) {
			s_Rinfo->m_artifacts[BonusSummaryData::kTemporaryArtifactCount + i] = bossArtifact->m_values[i];
		}

		s_Rinfo->m_missingArtifactMask = 0;
		for (int i = 0; i < BonusSummaryData::kArtifactCount; i++) {
			if (s_Rinfo->m_artifacts[i] < 0) {
				s_Rinfo->m_missingArtifactMask =
				    (unsigned char)(s_Rinfo->m_missingArtifactMask | (1 << i));
			}
		}

		{
			int i = 0;

			for (; i < s_Rinfo->m_partyCount; i++) {
				unsigned int* slot = &Game.m_scriptFoodBase[s_Rinfo->m_party[i].m_partySlot];

				for (int artifactIndex = 0; artifactIndex < BonusSummaryData::kArtifactCount; artifactIndex++) {
					short itemId = s_Rinfo->m_artifacts[artifactIndex];
					if (itemId <= 0) {
						continue;
					}

					if (GetItemType(itemId, 1) == 2) {
						int artifactSlot = s_Rinfo->m_artifacts[artifactIndex] - 0x9F;
						if (reinterpret_cast<CCaravanWork*>(*slot)->m_artifacts[artifactSlot] == s_Rinfo->m_artifacts[artifactIndex]) {
							s_Rinfo->m_party[i].m_ownedArtifactMask |= (1u << artifactIndex);
						}
					} else if (reinterpret_cast<CCaravanWork*>(*slot)->m_inventoryItemCount + 1 > 0x40) {
						s_Rinfo->m_party[i].m_ownedArtifactMask |= (1u << artifactIndex);
					}
				}
			}
		}

		int order[4];
		order[0] = 0;
		order[1] = 1;
		order[2] = 2;
		order[3] = 3;
		for (int i = 0; i < s_Rinfo->m_partyCount; i++) {
			int leftIndex = order[i];
			for (int j = i + 1; j < s_Rinfo->m_partyCount; j++) {
				int aTotal = s_Rinfo->m_party[leftIndex].m_totalValue;
				int aFood = s_Rinfo->m_party[leftIndex].m_foodValue;
				int bTotal = s_Rinfo->m_party[order[j]].m_totalValue;
				int bFood = s_Rinfo->m_party[order[j]].m_foodValue;
				int aArtifact = s_Rinfo->m_party[leftIndex].m_artifactValue;
				int bArtifact = s_Rinfo->m_party[order[j]].m_artifactValue;
				int coin = rand() & 1;

				if (aTotal < bTotal ||
				    (aTotal == bTotal && aArtifact < bArtifact) ||
				    (aTotal == bTotal && aArtifact == bArtifact && aFood < bFood) ||
				    (aTotal == bTotal && aArtifact == bArtifact && aFood == bFood && coin != 0)) {
					int temp = order[i];
					order[i] = order[j];
					order[j] = temp;
					leftIndex = order[i];
				}
			}
		}

		for (int i = 0; i < s_Rinfo->m_partyCount; i++) {
			s_Rinfo->m_party[order[i]].m_rank = i;
			if (i == 0) {
				s_Rinfo->m_winnerTotalValue = s_Rinfo->m_party[order[i]].m_totalValue;
			}
		}

		for (int i = 0; i < 0x18; i++) {
			this->m_wm.m_handles[i] = 0;
		}

		int slotIdx = 0;
		int i;
		for (i = 0; i < 0x18; i++) {
			int pc = s_Rinfo->m_partyCount;
			if (pc * 2 <= i) {
				break;
			}
			CCharaPcs::CHandle* handle =
			    new (MenuPcs.m_menuStage, "bonus_menu.cpp", 0x183) CCharaPcs::CHandle;
			this->m_wm.m_handles[slotIdx] = handle;
			this->m_wm.m_handles[slotIdx]->Add();
			unsigned long modelCode = s_Rinfo->m_party[i % pc].m_partySlot + 0x83;
			if (i < pc) {
				modelCode = s_Rinfo->m_party[i % pc].m_partySlot + 0x87;
			}
			this->m_wm.m_handles[slotIdx]->LoadModel(3, modelCode & 0xFFF, (modelCode >> 12) & 0xF, 0, -1, 0, 0);
			this->m_wm.m_handles[slotIdx]->m_flags = 0x300543;
			slotIdx++;
		}

		int handleIndex = i;
		for (int artifactIndex = 0; artifactIndex < BonusSummaryData::kArtifactCount; artifactIndex++, handleIndex++) {
			int itemId = s_Rinfo->m_artifacts[artifactIndex];
			if (itemId <= 0) {
				m_wm.m_handles[handleIndex] = 0;
			} else {
				CCharaPcs::CHandle* itemHandle =
				    new (MenuPcs.m_menuStage, "bonus_menu.cpp", 0x19C) CCharaPcs::CHandle;
				m_wm.m_handles[handleIndex] = itemHandle;
				m_wm.m_handles[handleIndex]->Add();
				unsigned short itemModelCode =
				    *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48 + 2);
				int modelNo = itemModelCode & 0x0FFF;
				m_wm.m_handles[handleIndex]->LoadModel(3, modelNo, (itemModelCode >> 12) & 0xF, 0, -1, 0, 0);
				m_wm.m_handles[handleIndex]->m_flags = 0x300543;

				if (modelNo == 0x79) {
					short itemId2 = s_Rinfo->m_artifacts[artifactIndex];
					int effectNo;
					if (itemId2 == 0xDF) {
						effectNo = 0x75;
					} else if (itemId2 == 0xE0) {
						effectNo = 0x76;
					} else if (itemId2 == 0xE1) {
						effectNo = 0x77;
					} else if (itemId2 == 0xE2) {
						effectNo = 0x78;
					} else if (itemId2 == 0xE3) {
						effectNo = 0x79;
					} else {
						continue;
					}
					BindEffect(handleIndex, effectNo, -1);
				}
			}
		}
	}

	GbaQue.SetStartBonusFlg();
	for (int i = 0; i < 4; i++) {
		if (Game.m_scriptFoodBase[i] != 0) {
			reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i])->SafeDeleteTempItem();
			reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[i])->SortBeforeReturnWorldMap();
		}
	}
	this->m_menuWindowInfo->state = 3;
	s_CntTop = 0;
	s_ArtiTop = 0;
	s_PlayerTop = 0;
	this->m_bonusState->m_phase = 0;
	Wind.ClearAll();
	this->m_bonusAlpha = 0;
	this->m_bonusCursorFlag = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8013E280
 * PAL Size: 20b
 * EN Address: 0x801541E8
 * EN Size: 28b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::BonusInit()
{
	s_Rinfo = 0;
	m_bonusAnim = 0;
	s_Base[0] = 0;
}

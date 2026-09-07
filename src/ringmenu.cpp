#include "ffcc/ringmenu.h"
#include "ffcc/chara.h"
#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/gobjwork.h"
#include "ffcc/gxfunc.h"
#include "ffcc/joybus.h"
#include "ffcc/linkage.h"
#include "ffcc/math.h"
#include "ffcc/partyobj.h"
#include "ffcc/p_camera.h"
#include "ffcc/game.h"
#include "ffcc/p_menu.h"
#include "ffcc/pad.h"
#include "ffcc/system.h"
#include "ffcc/textureman.h"
#include "ffcc/vector.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

#include <math.h>

static const char sRingMenuDisplayToggleChangedFmt[] = {
	0x72, 0x69, 0x6E, 0x67, 0x4D, 0x65, 0x6E, 0x75,
	(char)0x95, (char)0x8E, (char)0xA6, 0x6F, 0x6E, 0x2F, 0x6F, 0x66,
	0x66, (char)0x82, (char)0xAA, (char)0x95, (char)0xCF, (char)0x8D, (char)0x58, (char)0x82,
	(char)0xB3, (char)0x82, (char)0xEA, (char)0x82, (char)0xDC, (char)0x82, (char)0xB5, (char)0x82,
	(char)0xBD, (char)0x81, (char)0x42, 0x25, 0x64, 0x2D, 0x25, 0x64,
	0x0A, 0x00, 0x00, 0x00
};

static inline unsigned char* MenuPcsRaw()
{
    return reinterpret_cast<unsigned char*>(&MenuPcs);
}

static inline int clampDecToZero(int value)
{
	int next = value - 1;
	return next < 0 ? 0 : next;
}

/*
 * --INFO--
 * PAL Address: 0x800a2dd4
 * PAL Size: 1388b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRingMenu::DrawIcon()
{
	static unsigned char color[16] = {
		0x00, 0x20, 0x40, 0x60, 0x80, 0xA0, 0xC0, 0xE0,
		0xFF, 0xE0, 0xC0, 0xA0, 0x80, 0x60, 0x40, 0x20,
	};

	drawGBA();

	if (!((Game.m_gameWork.m_menuStageMode == 0) || (m_menuIndex < 2))) {
		return;
	}

	const unsigned int flatFlags = CFlatEnabledEventFlags();
	if ((flatFlags & 1) == 0) {
		return;
	}

	CGPartyObj* partyObj = Game.m_partyObjArr[m_menuIndex];
	if (partyObj == 0) {
		return;
	}
	unsigned char weaponFlagsHi = partyObj->m_weaponNodeFlagBytes.m_flags1;
	if (static_cast<signed char>(
	        static_cast<int>((static_cast<unsigned int>(weaponFlagsHi) << 24) & 0xC0000000) >> 31) == 0) {
		return;
	}

	CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[m_menuIndex]);
	Mtx cameraMtx;
	PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);

	Vec viewPos;
	Vec4d clipPos;
	Vec viewInput;
	CVector offset(0.0f, 0.5f * partyObj->unk_0x188, 0.0f);
	Vec* baseWorldPos = CVector(partyObj->m_worldPosition);
	CVector worldPos;
	PSVECAdd(baseWorldPos, offset, worldPos);

	viewInput.x = worldPos.x;
	viewInput.y = worldPos.y;
	viewInput.z = worldPos.z;
	PSMTXMultVec(cameraMtx, &viewInput, &viewPos);
	viewPos.z = (viewPos.z < -50.0f) ? viewPos.z : -50.0f;

	Mtx44 screenMtx;
	PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
	Math.MTX44MultVec4(screenMtx, &viewPos, &clipPos);

	float invW = 1.0f / clipPos.w;
	clipPos.x = clipPos.x * invW;
	clipPos.y = clipPos.y * invW;
	if ((clipPos.x > -1.0f) && (clipPos.x < 1.0f) && (clipPos.y > -1.0f) &&
	    (clipPos.y < 1.0f)) {
		return;
	}

	float clampedX = (clipPos.x < -0.9f)
	                     ? -0.9f
	                     : ((0.9f < clipPos.x) ? 0.9f : clipPos.x);
	clipPos.x = clampedX;

	float clampedY = (clipPos.y < -0.875f)
	                     ? -0.875f
	                     : ((0.875f < clipPos.y) ? 0.875f : clipPos.y);
	clipPos.y = clampedY;

	float angle = static_cast<float>(atan2(static_cast<double>(clipPos.x), static_cast<double>(clipPos.y)));

	float posX = 320.0f * clipPos.x + 320.0f;
	float posY = 224.0f - 224.0f * clipPos.y;
	unsigned char blinkAlpha = color[static_cast<int>(System.m_frameCounter) % 16];

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x19));
	int iconRow;
	int iconCol;
	if ((Game.m_gameWork.m_menuStageMode != 0) && (m_menuIndex >= 1)) {
		iconRow = 1;
		iconCol = 0x65;
	} else {
		iconRow = caravanWork->m_joybusCaravanId;
		int foodProgress = caravanWork->m_id;
		iconCol = foodProgress % 100 + (foodProgress - 100) / 100 * 4;
	}

	MenuPcs.SetColor(CColor(0, 0, 0, 0x80));
	MenuPcs.DrawRect(3, 4.0f + posX,
	                                 4.0f + posY, 56.0f, 56.0f,
	                                 0.0f, 0.0f, 1.0f, 1.0f, angle);

	MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF));
	MenuPcs.DrawRect(3, posX, posY, 56.0f, 56.0f, 0.0f,
	    static_cast<float>(iconRow * 0x38), 1.0f, 1.0f,
	    angle);

	int uInt = iconCol % 8 * 0x30;
	int vInt = iconCol / 8 * 0x30;
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x18));
	void* tlut = MenuPcs.m_externalFontTlut;
	CTexture* iconTexture = MenuPcs.m_textures[0x18];
	if (caravanWork->m_hp != 0) {
		tlut = 0;
	}
	iconTexture->SetExternalTlut(tlut, 1);
	GXSetTevDirect(GX_TEVSTAGE2);
	_GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_ONE, GX_CC_RASA);
	_GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_KONST, GX_CA_ZERO);
	_GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_DIVIDE_2, GX_TRUE, GX_TEVPREV);
	_GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	_GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
	_GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);

	MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, blinkAlpha));

	float u = static_cast<float>(uInt);
	float v = static_cast<float>(vInt);
	MenuPcs.DrawRect(3, static_cast<float>(posX), static_cast<float>(posY), 49.0f,
	                                 49.0f, u, v, 0.7f, 0.7f, 0.0f);
}

/*
 * --INFO--
 * PAL Address: 0x800a3340
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRingMenu::SetBattleCommand(int buttonGroupIndex, int newCommandId, int newRotation)
{
	if (newCommandId == 0) {
		newCommandId = -1;
	}

	const int currentCommand = m_battleButtons[buttonGroupIndex * 2 + 2];

	if (currentCommand == newCommandId) {
		return;
	}

	if (((currentCommand >= 0) && (newCommandId < 0)) || ((currentCommand < 0) && (newCommandId >= 0))) {
		m_buttonTimers[buttonGroupIndex * 3 + 2] = 8 - m_buttonTimers[buttonGroupIndex * 3 + 2];
	}

	m_battleButtons[buttonGroupIndex * 2 + 3] = m_battleButtons[buttonGroupIndex * 2 + 2];
	m_battleButtons[buttonGroupIndex * 2 + 2] = newCommandId;
	m_buttonTimers[buttonGroupIndex * 3 + 1] = 8 - m_buttonTimers[buttonGroupIndex * 3];
	m_buttonTimers[buttonGroupIndex * 3] = 8 - m_buttonTimers[buttonGroupIndex * 3];

	if (buttonGroupIndex != 2) {
		return;
	}

	m_rotationPhase = m_ringRotation;
	m_ringRotation = newRotation;
}

/*
 * --INFO--
 * PAL Address: 0x800a33dc
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRingMenu::SetBattleButton(int buttonIndex, int newValue)
{
	int current = m_battleButtons[buttonIndex];

	if (current == newValue) {
		return;
	}

	m_battleButtons[buttonIndex] = newValue;
}

/*
 * --INFO--
 * PAL Address: 0x800a33f8
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRingMenu::SetFade(int)
{
}

/*
 * --INFO--
 * PAL Address: 0x800a33fc
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRingMenu::onScriptChanged(char*, int)
{
}

/*
 * --INFO--
 * PAL Address: 0x800a3400
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRingMenu::onScriptChanging(char*)
{
}

/*
 * --INFO--
 * PAL Address: 0x800a3404
 * PAL Size: 1472b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma opt_propagation off
void CRingMenu::drawGBA()
{
	float sinA;
	float sinB;
	float angle;
	float gbaAnim;
	float showScale;
	float posX;
	float posY;
	float sizePulse;
	float cycle;

	if (!((Game.m_gameWork.m_menuStageMode == 0) || (m_menuIndex < 1))) {
		return;
	}

	const unsigned int scriptFood = Game.m_scriptFoodBase[m_menuIndex];
	if (scriptFood == 0) {
		return;
	}

	showScale = m_displayCounter / 16.0f;
	if (m_displayDirection != 0) {
		showScale = 1.0f - showScale;
	}
	if (0.0f == showScale) {
		return;
	}

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x16));

	float gbaAnimRaw = static_cast<float>(
	    sin(static_cast<double>((1.5707963705062866f * static_cast<float>(m_gbaAnimCounter)) / 12.0f)));
	gbaAnim = gbaAnimRaw;
	if (m_gbaConnectedFlag == 1) {
		gbaAnim = 1.0f - gbaAnimRaw;
	}

	int posXInt = 0x30;
	if ((m_menuIndex & 1) != 0) {
		posXInt = 0x250;
	}
	posX = static_cast<float>(posXInt);

	int posYInt = 0x30;
	if ((m_menuIndex & 2) != 0) {
		posYInt = 400;
	}
	posY = static_cast<float>(posYInt);

	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	sizePulse = 0.25f * (1.0f - gbaAnim) + 1.0f;
	float cycleRaw = static_cast<float>(fmod(static_cast<double>(0.05f * static_cast<float>(m_commonFrameCounter)),
	                                         2.0));
	if (cycleRaw > 1.0f) {
		cycle = 2.0f - cycleRaw;
	} else {
		cycle = cycleRaw;
	}

	angle = 3.1415927410125732f * cycle;
	sinA = static_cast<float>(sin(static_cast<double>(angle)));
	sinB = static_cast<float>(sin(static_cast<double>(-1.5707963705062866f + angle)));

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1E));

	const float alphaBase = 255.0f * gbaAnim;
	MenuPcs.SetColor(CColor(0, 0, 0, static_cast<unsigned char>(0.5f * alphaBase * showScale)));

	const float drawAngle = 0.2f * (2.0f * (cycle - 0.5f));
	const float invSize = 1.0f - sizePulse;
	const float orbitX = 5.0f * (sizePulse * sinB);
	const float orbitY = 10.0f * (sizePulse * sinA);
	const float drawX = posX + orbitX;
	const float drawY = posY - orbitY;
	MenuPcs.DrawRect(3, 8.0f + drawX, 8.0f + drawY, 80.0f, 48.0f,
	                                 0.0f, static_cast<float>(m_menuIndex * 0x30), 0.75f * (1.0f + invSize),
	                                 0.75f * (sizePulse + invSize), drawAngle);

	const float alphaLit = alphaBase * showScale;
	MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alphaLit)));
	MenuPcs.DrawRect(3, drawX, drawY, 80.0f, 48.0f, 0.0f, static_cast<float>(m_menuIndex * 0x30),
	                                 0.75f * sizePulse, 0.75f * sizePulse, drawAngle);

	const unsigned int flatFlags = CFlatEnabledEventFlags();
	if (((flatFlags & 8) != 0) && (Joybus.GetGBAStart(m_menuIndex) == 0)) {
		if (static_cast<unsigned char>(Joybus.IsInitSend(m_menuIndex)) == 0) {
			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1D));
			const float blink = static_cast<float>(sin(static_cast<double>(0.1f * static_cast<float>(m_commonFrameCounter))));
			const unsigned int sendAlpha = static_cast<unsigned int>(
			    static_cast<int>(0.5f * (alphaLit * (1.0f + blink))));
			MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(sendAlpha)));
			MenuPcs.DrawRect(3, drawX, drawY, 48.0f, 48.0f, 0.0f, 240.0f,
			                                 1.0f, 1.0f, 0.0f);
		} else {
			int frameTex = (static_cast<int>(System.m_frameCounter) >> 1) % 16;
			if (frameTex >= 4) {
				frameTex &= 1;
			}
			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1D));
			MenuPcs.DrawRect(3, drawX, drawY, 48.0f, 48.0f, 0.0f,
			                                 static_cast<float>(frameTex * 0x30), 1.0f, 1.0f, 0.0f);
		}
	}

	MenuPcs.DrawInit();
}
#pragma opt_propagation reset

/*
 * --INFO--
 * PAL Address: 0x800a39c4
 * PAL Size: 3884b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma opt_lifetimes off
void CRingMenu::onDraw()
{
	if (!((Game.m_gameWork.m_menuStageMode == 0) || (m_menuIndex < 1))) {
		return;
	}

	unsigned int scriptFood = Game.m_scriptFoodBase[m_menuIndex];
	if (scriptFood == 0) {
		return;
	}

	float showScale = m_displayCounter / 16.0f;
	if (m_displayDirection != 0) {
		showScale = 1.0f - showScale;
	}
	if (0.0f == showScale) {
		return;
	}

	float transitionScale;
	if (m_animDirection != 0) {
		transitionScale = -(static_cast<float>(m_transitionCounter) * 0.0625f - 1.0f);
	} else {
		transitionScale = static_cast<float>(m_transitionCounter) * 0.0625f;
	}

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x16));
	sin(static_cast<double>((1.5707963705062866f * static_cast<float>(m_gbaAnimCounter)) / 12.0f));
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	float cycle = static_cast<float>(fmod(static_cast<double>(0.05f * static_cast<float>(m_commonFrameCounter)),
	                                      2.0));
	if (cycle > 1.0f) {
		cycle = 2.0f - cycle;
	}
	float cycleAngle = 3.1415927410125732f * cycle;
	sin(static_cast<double>(cycleAngle));
	sin(static_cast<double>(-1.5707963705062866f + cycleAngle));

	const double pulse = sin(static_cast<double>(1.5707963705062866f * showScale));

	float posLeft;
	float posAltY;
	float posMainX;
	float posMainY;
	float alphaScaleBase;
	float iconAlphaScale;
	float posAltX;

	alphaScaleBase = 255.0f * showScale * transitionScale;
	const float glowOffset = 32.0f * (1.0f - static_cast<float>(pulse));
	iconAlphaScale = showScale * transitionScale;
	posAltX = 472.0f + glowOffset;
	posLeft = -glowOffset;
	posAltY = 256.0f + glowOffset;
	posMainX = posAltX - 40.0f;
	posMainY = 192.0f + glowOffset;

	for (int group = 2; group >= 0; group--) {
		float posX;
		float posY;

		if (group == 2) {
			posX = 16.0f + (((m_menuIndex & 1) != 0) ? posAltX : posLeft);
			posY = 80.0f + (((m_menuIndex & 2) != 0) ? posAltY : posLeft);
		} else {
			posX = 40.0f + (((m_menuIndex & 1) != 0) ? posMainX : posLeft);
			posY = 96.0f + (((m_menuIndex & 2) != 0) ? posMainY : posLeft);
		}

		float buttonAlpha = static_cast<float>(m_buttonTimers[group * 3 + 2]) * 0.125f;
		if (m_battleButtons[group * 2 + 2] >= 0) {
			buttonAlpha = 1.0f - buttonAlpha;
		}

		if (group == 2) {
			CGPartyObj* partyObj = Game.m_partyObjArr[m_menuIndex];
			buttonAlpha = static_cast<float>(static_cast<int>((partyObj->m_partyData.commandMode & 9) != 0));
		}

		if (0.0f == buttonAlpha) {
			continue;
		}

		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1F));
		MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(buttonAlpha * alphaScaleBase)));

		float drawX;
		float drawY;
		switch (group) {
		case 0: {
			const float wobble = static_cast<float>(sin(static_cast<double>(1.5707963705062866f * buttonAlpha)));
			drawX = -(16.0f * wobble - (12.0f + posX));
			drawY = posY;
			MenuPcs.DrawRect(0, drawX, drawY, 144.0f, 32.0f, 0.0f, 0.0f,
			                                 1.0f, 1.0f, 0.0f);
			MenuPcs.DrawRect(0, drawX, drawY, 40.0f, 32.0f, 0.0f, 56.0f,
			                                 1.0f, 1.0f, 0.0f);
			break;
		}
		case 1: {
			const float wobble = static_cast<float>(sin(static_cast<double>(1.5707963705062866f * buttonAlpha)));
			drawX = -(16.0f * wobble - posX);
			drawY = 24.0f + posY;
			MenuPcs.DrawRect(0, drawX, drawY, 144.0f, 24.0f, 0.0f, 32.0f,
			                                 1.0f, 1.0f, 0.0f);
			MenuPcs.DrawRect(0, drawX, drawY, 24.0f, 24.0f, 40.0f, 56.0f,
			                                 1.0f, 1.0f, 0.0f);
			break;
		}
		case 2:
			drawX = posX;
			drawY = posY;
			MenuPcs.DrawRect(0, posX, posY, 128.0f, 32.0f, 0.0f, 88.0f,
			                                 1.0f, 1.0f, 0.0f);
			break;
		}

		if (group == 2) {
			CGPartyObj* partyObj = Game.m_partyObjArr[m_menuIndex];
			if (partyObj != 0) {
				CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(partyObj->m_scriptHandle);
				int cmdIndex = (Game.m_gameWork.m_bossArtifactStageIndex == 0x19)
				                   ? Chara.MogFur().m_commandIndex
				                   : caravanWork->GetIdxCmdList();

				CFont* font = MenuPcs.m_fonts[1];
				font->DrawInit();
				font->SetMargin(-4.0f);
				font->SetShadow(1);
				font->SetTlut(4);

				float scroll = m_spinAccumulator;
				float labelAlpha = 1.0f;
				for (;;) {
					if (scroll >= labelAlpha) {
						if (Game.m_gameWork.m_bossArtifactStageIndex == 0x19) {
							cmdIndex = (cmdIndex + 1) % 5;
						} else {
							cmdIndex = caravanWork->GetNextCmdListIdx(cmdIndex, -1);
						}
						scroll -= 1.0f;
					} else if (scroll <= -1.0f) {
						if (Game.m_gameWork.m_bossArtifactStageIndex == 0x19) {
							cmdIndex = (cmdIndex + 4) % 5;
						} else {
							cmdIndex = caravanWork->GetNextCmdListIdx(cmdIndex, 1);
						}
						scroll += 1.0f;
					} else {
						break;
					}
				}

				double mag = fabs(static_cast<double>(m_spinAccumulator));
				double labelAlphaD;
				if (mag < 0.009999999776482582) {
					labelAlphaD = 100.0 * mag;
				} else {
					labelAlphaD = 1.0;
				}
				labelAlpha = static_cast<float>(labelAlphaD);

				int prev1 = (Game.m_gameWork.m_bossArtifactStageIndex == 0x19)
				                ? (cmdIndex + 4) % 5
				                : caravanWork->GetNextCmdListIdx(cmdIndex, -1);
				int prev2 = (Game.m_gameWork.m_bossArtifactStageIndex == 0x19)
				                ? (prev1 + 4) % 5
				                : caravanWork->GetNextCmdListIdx(prev1, -1);

				labelAlpha *= iconAlphaScale;
				drawCommand(m_menuIndex, font, posX, posY, caravanWork, prev2, scroll - 2.0f, labelAlpha);
				drawCommand(m_menuIndex, font, posX, posY, caravanWork, prev1, scroll - 1.0f, labelAlpha);
				int next1 = (Game.m_gameWork.m_bossArtifactStageIndex == 0x19)
				                ? (cmdIndex + 1) % 5
				                : caravanWork->GetNextCmdListIdx(cmdIndex, 1);
				int next2 = (Game.m_gameWork.m_bossArtifactStageIndex == 0x19)
				                ? (next1 + 1) % 5
				                : caravanWork->GetNextCmdListIdx(next1, 1);
				drawCommand(m_menuIndex, font, posX, posY, caravanWork, next2, 2.0f + scroll, labelAlpha);
				drawCommand(m_menuIndex, font, posX, posY, caravanWork, next1, 1.0f + scroll, labelAlpha);
				drawCommand(m_menuIndex, font, posX, posY, caravanWork, cmdIndex, scroll, iconAlphaScale);
				MenuPcs.DrawInit();
			}
		}

		const float textX2 = 64.0f + drawX;
		const float textX0 = textX2 + 20.0f;
		const float textY0 = (5.0f + drawY) - 4.0f;
		const float textX1 = (56.0f + drawX) + 20.0f;
		const float textY1 = (3.0f + drawY) - 4.0f;
		const float textY2 = 6.0f + drawY;
		CFont* font = MenuPcs.m_fonts[1];
		for (int button = 1; button >= 0; button--) {
			const int buttonValue = (&m_battleButtons[group * 2 + 2])[button];
			if (buttonValue < 0) {
				continue;
			}

			const char* label;
			if ((buttonValue & 0x8000) != 0) {
				label = Game.m_cFlatDataArr[1].TableStrings(0)[(buttonValue & ~0x8000) * 5 + 4];
			} else {
				label = Game.m_cFlatDataArr[1].TableStrings(4)[buttonValue];
			}

			float fade = static_cast<float>((&m_buttonTimers[group * 3])[button]) * 0.125f;
			if (button == 0) {
				fade = 1.0f - fade;
			}

			font->DrawInit();
			font->SetMargin(-4.0f);
			font->SetShadow(1);

			float textScale;
			switch (group) {
			case 0:
				font->SetTlut(0xD);
				textScale = 0.85f;
				break;
			case 1:
				font->SetTlut(0xE);
				textScale = 0.75f;
				break;
			case 2: {
				font->SetTlut((buttonValue == 1) ? 7 : 4);
				const float wobble = static_cast<float>(sin(static_cast<double>(1.5707963705062866f * (1.0f - fade))));
				textScale = 0.75f * (0.3f * wobble + 1.0f);
				break;
			}
			}

			font->SetScaleX(textScale);
			font->SetScaleY(textScale);

			const float width = font->GetWidth(label);
			if ((group == 2) && (m_battleButtons[2] >= 0)) {
				font->SetColor(CColor(0xFF, 0xFF, 0xFF,
					static_cast<unsigned char>(0.35f * (showScale * (255.0f * fade * transitionScale)))).color);
			} else {
				font->SetColor(CColor(0xFF, 0xFF, 0xFF,
					static_cast<unsigned char>(showScale * (255.0f * fade * transitionScale))).color);
			}

			float textX;
			float textY;
			switch (group) {
			case 0:
				textX = -(0.5f * width - textX0);
				textY = textY0;
				break;
			case 1:
				textX = -(0.5f * width - textX1);
				textY = textY1;
				break;
			case 2:
				textX = -(0.5f * width - textX2);
				textY = textY2;
				break;
			}

			font->SetPosX(textX);
			font->SetPosY(textY);
			font->SetPosZ(0.0f);
			if (group != 2) {
				font->Draw(label);
			}
			MenuPcs.DrawInit();

			if (group == 2) {
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1F));
				CGPartyObj* partyObj = Game.m_partyObjArr[m_menuIndex];
				if (partyObj != 0) {
					CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(partyObj->m_scriptHandle);
					if ((caravanWork != 0)
					    && (static_cast<signed char>(
					            static_cast<int>((static_cast<unsigned int>(CFlatGameFlags()) << 30) & 0xC0000000) >> 31)
					        == 0)) {
						const float barY = 20.0f + textY;
						const float fullAlpha = showScale * (255.0f * fade * transitionScale);
						const float dimAlpha = showScale * (128.0f * fade * transitionScale);

						for (int i = 0; i < caravanWork->m_numCmdListSlots; i++) {
							int selected = caravanWork->IsSelectedCmdList(i);

							float blink;
							if (selected != 0) {
								MenuPcs.SetColor(CColor(0x00, 0xFF, 0x00, static_cast<unsigned char>(fullAlpha)));
								blink = static_cast<float>(static_cast<int>((System.m_frameCounter >> 2) & 1));
							} else if (caravanWork->IsUseCmdList(i)) {
								MenuPcs.SetColor(CColor(0x20, 0xFF, 0x20, static_cast<unsigned char>(fullAlpha)));
								blink = 0.0f;
							} else {
								MenuPcs.SetColor(CColor(0x80, 0x80, 0x80, static_cast<unsigned char>(dimAlpha)));
								blink = 0.0f;
							}

							MenuPcs.DrawRect(3,
								4.0f +
									((textX2 - static_cast<float>((caravanWork->m_numCmdListSlots * 8) / 2)) +
									 static_cast<float>(i * 8)),
								barY, 8.0f, 8.0f,
								8.0f * (8.0f + blink), 56.0f,
								1.0f, 1.0f, 0.0f);
						}
					}
				}
			}
		}
	}

	MenuPcs.DrawInit();
}
#pragma opt_lifetimes reset

/*
 * --INFO--
 * PAL Address: 0x800a48f0
 * PAL Size: 844b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void drawCommand(int state, CFont* font, float posX, float posY, CCaravanWork* caravanWork, int cmdIndex, float angle, float alphaScale)
{
	float fVar1;
	float alphaProduct;
	bool reverseDir;
	int waveDirection;
	float clampedAlpha;
	int tlut;
	char** cmdNameTable;
	const char* commandLabel;
	double waveX;
	float waveY;
	float textWidth;
	float textHeight;
	float waveSinY;

	if (Game.m_gameWork.m_bossArtifactStageIndex == 0x19) {
		cmdNameTable = Game.m_cFlatDataArr[1].TableStrings(4);
		commandLabel = cmdNameTable[cmdIndex + 0x1E];
	} else if (cmdIndex < 2) {
		cmdNameTable = Game.m_cFlatDataArr[1].TableStrings(4);
		tlut = 9;
		if (cmdIndex == 0) {
			tlut = 1;
		}
		commandLabel = cmdNameTable[tlut];
	} else {
		commandLabel = caravanWork->GetCmdListItemName(cmdIndex);
	}

	if (Game.m_gameWork.m_bossArtifactStageIndex == 0x19) {
		switch (cmdIndex) {
		case 0:
			tlut = 2;
			break;
		case 1:
			tlut = 1;
			break;
		case 2:
			tlut = 4;
			break;
		case 3:
			tlut = 6;
			break;
		case 4:
		default:
			tlut = 7;
			break;
		}
		font->SetTlut(tlut);
	} else if (cmdIndex == 0) {
		font->SetTlut(7);
	} else {
		font->SetTlut(4);
	}

	waveX = static_cast<double>(30.0f * static_cast<float>(sin(static_cast<double>(angle))));
	waveSinY = static_cast<float>(sin(static_cast<double>(angle)));
	reverseDir = false;
	if ((state == 0) || (state == 3)) {
		reverseDir = true;
	}
	waveDirection = 1;
	if (reverseDir) {
		waveDirection = -1;
	}
	waveY = static_cast<float>(waveDirection) * (10.0f * waveSinY);
	if (Game.m_gameWork.m_bossArtifactStageIndex == 0x19) {
		waveY = waveY + 2.0f;
	}

	font->SetScale(static_cast<float>(0.800000011920929 - 0.25 * fabs(static_cast<double>(angle))));
	textWidth = static_cast<float>(font->GetWidth(commandLabel));
	fVar1 = static_cast<float>(-(0.5 * fabs(static_cast<double>(angle)) - 1.0));
	textHeight = static_cast<float>(font->m_glyphHeight) * font->scaleY;

	clampedAlpha = (fVar1 < 0.0f) ? 0.0f : ((1.0f < fVar1) ? 1.0f : fVar1);

	alphaProduct = 255.0f * alphaScale;
	font->SetColor(CColor(0xFF, 0xFF, 0xFF,
		static_cast<unsigned char>(alphaProduct * clampedAlpha)).color);
	font->SetPosX(static_cast<float>(waveX) +
		((64.0f + posX) - textWidth * 0.5f));
	font->SetPosY(10.0f +
		(waveY + ((4.0f + posY) - textHeight * 0.5f)));
	font->SetPosZ(0.0f);
	font->Draw(commandLabel);
}

/*
 * --INFO--
 * PAL Address: 0x800a4c3c
 * PAL Size: 1392b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRingMenu::onCalc()
{
	if ((Game.m_gameWork.m_menuStageMode == 0) || (m_menuIndex < 1)) {
		const unsigned int targetAnimDirection =
			(CFlatEnabledEventFlags() >> 2) & 1;
		if (m_displayDirection != static_cast<int>(targetAnimDirection)) {
			System.Printf(const_cast<char*>(sRingMenuDisplayToggleChangedFmt), m_menuIndex, targetAnimDirection);
			m_displayDirection = !m_displayDirection;
			m_displayCounter = 0x10 - m_displayCounter;
		}

		m_displayCounter = clampDecToZero(m_displayCounter);
		m_transitionCounter = clampDecToZero(m_transitionCounter);
		m_commonFrameCounter = m_commonFrameCounter + 1;
		m_timerB = clampDecToZero(m_timerB);

		for (int button = 0; button < 9; button++) {
			m_buttonTimers[button] = clampDecToZero(m_buttonTimers[button]);
		}
		for (int anim = 0; anim < 9; anim++) {
			for (int component = 0; component < 3; component++) {
				m_animFloat[anim][component] -= 0.1f;
				if (m_animFloat[anim][component] < 0.0f) {
					m_animFloat[anim][component] = 0.0f;
				}
			}
		}

		fmod(static_cast<double>(m_spinPhase), 1.0);
		int i = 0x1B;
		while (i > 0) {
			i--;
		}

		int ctrlMode = Joybus.GetCtrlMode(m_menuIndex);
		unsigned int gbaConnected = ctrlMode == 1;

		if (!Joybus.GetGBAStart(m_menuIndex)) {
			gbaConnected = 1;
		}

		if ((Joybus.GetPadType(m_menuIndex) == 0x09000000) || (Joybus.GetPadType(m_menuIndex) == 0x8B100000)) {
			gbaConnected = 0;
		}

		if (m_gbaConnectedFlag != static_cast<int>(gbaConnected)) {
			m_gbaConnectedFlag = static_cast<int>(gbaConnected);
			m_gbaAnimCounter = 0x0C - m_gbaAnimCounter;
		}
		m_gbaAnimCounter = clampDecToZero(m_gbaAnimCounter);

		float scrollDelta = 0.0f;
		CGPartyObj* partyObj = Game.m_partyObjArr[m_menuIndex];
		if (partyObj != 0) {
			CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(partyObj->m_scriptHandle);
			int currentCmd = (Game.m_gameWork.m_bossArtifactStageIndex == 0x19)
			                     ? Chara.MogFur().m_commandIndex
			                     : caravanWork->GetIdxCmdList();

			int* trackedCmd = (Game.m_gameWork.m_bossArtifactStageIndex == 0x19)
			                      ? &Chara.MogFur().m_trackedCommandIndex
			                      : &m_currentCommandIndex;

			int next = currentCmd;
			int prev = currentCmd;
			if (*trackedCmd != currentCmd) {
				for (int step = 1; step < 4; step++) {
					next = (Game.m_gameWork.m_bossArtifactStageIndex == 0x19)
					           ? (currentCmd + 1) % 5
					           : caravanWork->GetNextCmdListIdx(next, 1);
					prev = (Game.m_gameWork.m_bossArtifactStageIndex == 0x19)
					           ? (currentCmd + 4) % 5
					           : caravanWork->GetNextCmdListIdx(prev, -1);

					int trackedValue = *trackedCmd;
					if (trackedValue != currentCmd) {
						int prevDir = 0;
						int nextDir = 0;
						if (trackedValue == prev) {
							prevDir = step;
						}
						if (trackedValue == next) {
							nextDir = -step;
						}
						if ((prevDir != 0) || (nextDir != 0)) {
							if ((prevDir != 0) && (nextDir != 0)) {
								unsigned short trigger = Pad.GetButton(m_menuIndex);
								if ((trigger & 0x40) != 0) {
									nextDir = prevDir;
								}
								scrollDelta = static_cast<float>(nextDir);
							} else if (prevDir != 0) {
								scrollDelta = static_cast<float>(prevDir);
							} else if (nextDir != 0) {
								scrollDelta = static_cast<float>(nextDir);
							}
							break;
						}
						scrollDelta = 0.0f;
					}

				}
			}

			*trackedCmd = currentCmd;
			m_spinAccumulator = m_spinAccumulator + scrollDelta;
			m_spinAccumulator *= 0.8f;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800a51ac
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
double CRingMenu::GetDispCounter()
{
	return 1.0f - m_displayCounter / 16.0f;
}

/*
 * --INFO--
 * PAL Address: 0x800a51e4
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRingMenu::Destroy()
{
	CMenu::Destroy();
}

/*
 * --INFO--
 * PAL Address: 0x800a5204
 * PAL Size: 216b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRingMenu::Create()
{
	Destroy();
	CMenu::Create();

	m_displayDirection = 0;
	m_displayCounter = 0;
	m_stateFlag = -1;
	m_transitionCounter = 0x10;
	m_animDirection = 1;
	m_battleButtons[0] = 0;
	m_battleButtons[2] = -1;
	m_battleButtons[3] = -1;
	m_buttonTimers[0] = 0;
	m_buttonTimers[1] = 0;
	m_buttonTimers[2] = 0;
	m_battleButtons[1] = 0;
	m_battleButtons[4] = -1;
	m_battleButtons[5] = -1;
	m_buttonTimers[3] = 0;
	m_buttonTimers[4] = 0;
	m_buttonTimers[5] = 0;
	m_battleButtons[2] = 0;
	m_battleButtons[6] = -1;
	m_battleButtons[7] = -1;
	m_buttonTimers[6] = 0;
	m_buttonTimers[7] = 0;
	m_buttonTimers[8] = 0;
	m_ringRotation = -1;
	m_rotationPhase = -1;
	m_spinPhase = 0.0f;
	m_gbaConnectedFlag = 0;
	m_gbaAnimCounter = 0;
	m_commonFrameCounter = 0;
	m_unk4f8 = 0;
	m_timerB = 0;
	m_currentCommandIndex = 0;
	m_spinAccumulator = 0.0f;
}

/*
 * --INFO--
 * PAL Address: 0x800a52dc
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CRingMenu::~CRingMenu()
{
	Destroy();
}

/*
 * --INFO--
 * PAL Address: 0x800a5350
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CRingMenu::CRingMenu()
{
}

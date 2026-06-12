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

extern unsigned char sRingMenuBlinkAlphaTable[];
static const char sRingMenuDisplayToggleChangedFmt[] = {
	0x72, 0x69, 0x6E, 0x67, 0x4D, 0x65, 0x6E, 0x75,
	(char)0x95, (char)0x8E, (char)0xA6, 0x6F, 0x6E, 0x2F, 0x6F, 0x66,
	0x66, (char)0x82, (char)0xAA, (char)0x95, (char)0xCF, (char)0x8D, (char)0x58, (char)0x82,
	(char)0xB3, (char)0x82, (char)0xEA, (char)0x82, (char)0xDC, (char)0x82, (char)0xB5, (char)0x82,
	(char)0xBD, (char)0x81, (char)0x42, 0x25, 0x64, 0x2D, 0x25, 0x64,
	0x0A, 0x00, 0x00, 0x00
};
extern const float kRingMenuZero = 0.0f;
extern const float kRingMenuHalf = 0.5f;
extern const float kRingMenuCameraClipZ = -50.0f;
extern const float kRingMenuOne = 1.0f;
extern const float kRingMenuNegativeOne = -1.0f;
extern const float kRingMenuClipMinX = -0.9f;
extern const float kRingMenuClipMaxX = 0.9f;
extern const float kRingMenuClipMinY = -0.875f;
extern const float kRingMenuClipMaxY = 0.875f;
extern const float kRingMenuScreenHalfWidth = 320.0f;
extern const float kRingMenuScreenHalfHeight = 224.0f;
extern const float kRingMenuShadowOffset = 4.0f;
extern const float kRingMenuCommandCellSize = 56.0f;
extern const float kRingMenuMarkerSize = 49.0f;
extern const float kRingMenuMarkerUvScale = 0.7f;
extern const double kRingMenuS32DoubleBias = 4503601774854144.0;
extern const float kRingMenuAnimStep = 0.0625f;
extern const float kRingMenuHalfPi = 1.5707963705062866f;
extern const float kRingMenuWobbleDivisor = 12.0f;
extern const float kRingMenuPulseScale = 0.25f;
extern const float kRingMenuCycleStep = 0.05f;
extern const double kRingMenuCycleWrapD = 2.0;
extern const float kRingMenuTwo = 2.0f;
extern const float kRingMenuPi = 3.1415927410125732f;
extern const float kRingMenuNegHalfPi = -1.5707963705062866f;
extern const float kRingMenuAlphaMax = 255.0f;
extern const float kRingMenuSmallIconSize = 8.0f;
extern const float kRingMenuSmallOffset = 5.0f;
extern const float kRingMenuGbaOrbitYScale = 10.0f;
extern const float kRingMenuPanelWidth80 = 80.0f;
extern const float kRingMenuGbaIconSize = 48.0f;
extern const float kRingMenuThreeQuarter = 0.75f;
extern const float kRingMenuDrawAngleScale = 0.2f;
extern const float kRingMenuBlinkPhaseStep = 0.1f;
extern const float kRingMenuCommandIconV = 240.0f;
extern const float kRingMenuButtonHeight = 32.0f;
extern const float kRingMenuAltBaseX = 472.0f;
extern const float kRingMenuAltBaseY = 256.0f;
extern const float kRingMenuButtonWidth = 40.0f;
extern const float kRingMenuMainBaseY = 192.0f;
extern const float kRingMenuButtonInsetX = 16.0f;
extern const float kRingMenuMainButtonY = 96.0f;
extern const float kRingMenuButtonFadeStep = 0.125f;
extern const float kRingMenuLabelPanelWidth = 144.0f;
extern const float kRingMenuIconSize = 24.0f;
extern const float kRingMenuCommandPanelWidth = 128.0f;
extern const float kRingMenuCommandIconY = 88.0f;
extern const float kRingMenuFontMargin = -4.0f;
extern const double kRingMenuSpinAlphaScale = 100.0;
extern const double kRingMenuOneD = 1.0;
extern const double kRingMenuSpinEpsilon = 0.009999999776482582;
extern const float kRingMenuTextBaseX = 64.0f;
extern const float kRingMenuTextOffsetX = 20.0f;
extern const float kRingMenuTextOffsetY = 3.0f;
extern const float kRingMenuCommandTextOffsetY = 6.0f;
extern const float kRingMenuItemTextScale = 0.85f;
extern const float kRingMenuTextWobbleScale = 0.3f;
extern const float kRingMenuDimAlphaScale = 0.35f;
extern const float kRingMenuSpinWaveAmplitude = 30.0f;
extern const double kRingMenuSpinScaleBaseD = 0.800000011920929;
extern const double kRingMenuSpinScaleSlopeD = 0.25;
extern const double kRingMenuSpinAlphaSlopeD = 0.5;
extern const double kRingMenuU32DoubleBias = 4503599627370496.0;
extern const float kRingMenuSpinDamping = 0.8f;

static inline unsigned char* MenuPcsRaw()
{
    return reinterpret_cast<unsigned char*>(&MenuPcs);
}

static inline int clampDecToZero(int value)
{
	unsigned int next = static_cast<unsigned int>(value - 1);
	return static_cast<int>(next & ~static_cast<unsigned int>(static_cast<int>(next) >> 31));
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
	CVector offset(kRingMenuZero, kRingMenuHalf * partyObj->unk_0x188, kRingMenuZero);
	Vec* baseWorldPos = CVector(partyObj->m_worldPosition);
	CVector worldPos;
	PSVECAdd(baseWorldPos, offset, worldPos);

	viewInput.x = worldPos.x;
	viewInput.y = worldPos.y;
	viewInput.z = worldPos.z;
	PSMTXMultVec(cameraMtx, &viewInput, &viewPos);
	viewPos.z = (viewPos.z < kRingMenuCameraClipZ) ? viewPos.z : kRingMenuCameraClipZ;

	Mtx44 screenMtx;
	PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
	Math.MTX44MultVec4(screenMtx, &viewPos, &clipPos);

	float invW = kRingMenuOne / clipPos.w;
	clipPos.x = clipPos.x * invW;
	clipPos.y = clipPos.y * invW;
	if ((clipPos.x > kRingMenuNegativeOne) && (clipPos.x < kRingMenuOne) && (clipPos.y > kRingMenuNegativeOne) &&
	    (clipPos.y < kRingMenuOne)) {
		return;
	}

	float clampedX = (clipPos.x < kRingMenuClipMinX)
	                     ? kRingMenuClipMinX
	                     : ((kRingMenuClipMaxX < clipPos.x) ? kRingMenuClipMaxX : clipPos.x);
	clipPos.x = clampedX;

	float clampedY = (clipPos.y < kRingMenuClipMinY)
	                     ? kRingMenuClipMinY
	                     : ((kRingMenuClipMaxY < clipPos.y) ? kRingMenuClipMaxY : clipPos.y);
	clipPos.y = clampedY;

	float angle = static_cast<float>(atan2(static_cast<double>(clipPos.x), static_cast<double>(clipPos.y)));

	float posX = kRingMenuScreenHalfWidth * clipPos.x + kRingMenuScreenHalfWidth;
	float posY = kRingMenuScreenHalfHeight - kRingMenuScreenHalfHeight * clipPos.y;
	unsigned char blinkAlpha = sRingMenuBlinkAlphaTable[static_cast<int>(System.m_frameCounter) % 16];

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
	MenuPcs.DrawRect(3, kRingMenuShadowOffset + posX,
	                                 kRingMenuShadowOffset + posY, kRingMenuCommandCellSize, kRingMenuCommandCellSize,
	                                 kRingMenuZero, kRingMenuZero, kRingMenuOne, kRingMenuOne, angle);

	MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF));
	MenuPcs.DrawRect(3, posX, posY, kRingMenuCommandCellSize, kRingMenuCommandCellSize, kRingMenuZero,
	    static_cast<float>(iconRow * 0x38), kRingMenuOne, kRingMenuOne,
	    angle);

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x18));
	int uInt = iconCol % 8 * 0x30;
	int vInt = iconCol / 8 * 0x30;
	void* tlut = MenuPcs.m_externalFontTlut;
	if (caravanWork->m_hp != 0) {
		tlut = 0;
	}
	MenuPcs.m_textures[0x18]->SetExternalTlut(tlut, 1);
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
	MenuPcs.DrawRect(3, static_cast<float>(posX), static_cast<float>(posY), kRingMenuMarkerSize,
	                                 kRingMenuMarkerSize, u, v, kRingMenuMarkerUvScale, kRingMenuMarkerUvScale, kRingMenuZero);
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

	showScale = static_cast<float>(m_displayCounter) * kRingMenuAnimStep;
	if (m_displayDirection != 0) {
		showScale = kRingMenuOne - showScale;
	}
	if (kRingMenuZero == showScale) {
		return;
	}

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x16));

	float gbaAnimRaw = static_cast<float>(
	    sin(static_cast<double>((kRingMenuHalfPi * static_cast<float>(m_gbaAnimCounter)) / kRingMenuWobbleDivisor)));
	gbaAnim = gbaAnimRaw;
	if (m_gbaConnectedFlag == 1) {
		gbaAnim = kRingMenuOne - gbaAnimRaw;
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

	sizePulse = kRingMenuPulseScale * (kRingMenuOne - gbaAnim) + kRingMenuOne;
	float cycleRaw = static_cast<float>(fmod(static_cast<double>(kRingMenuCycleStep * static_cast<float>(m_commonFrameCounter)),
	                                         kRingMenuCycleWrapD));
	if (cycleRaw > kRingMenuOne) {
		cycle = kRingMenuTwo - cycleRaw;
	} else {
		cycle = cycleRaw;
	}

	angle = kRingMenuPi * cycle;
	sinA = static_cast<float>(sin(static_cast<double>(angle)));
	sinB = static_cast<float>(sin(static_cast<double>(kRingMenuNegHalfPi + angle)));

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1E));

	const float alphaBase = kRingMenuAlphaMax * gbaAnim;
	MenuPcs.SetColor(CColor(0, 0, 0, static_cast<unsigned char>(kRingMenuHalf * alphaBase * showScale)));

	const float drawAngle = kRingMenuDrawAngleScale * (kRingMenuTwo * (cycle - kRingMenuHalf));
	const float invSize = kRingMenuOne - sizePulse;
	const float orbitX = kRingMenuSmallOffset * (sizePulse * sinB);
	const float orbitY = kRingMenuGbaOrbitYScale * (sizePulse * sinA);
	const float drawX = posX + orbitX;
	const float drawY = posY - orbitY;
	MenuPcs.DrawRect(3, kRingMenuSmallIconSize + drawX, kRingMenuSmallIconSize + drawY, kRingMenuPanelWidth80, kRingMenuGbaIconSize,
	                                 kRingMenuZero, static_cast<float>(m_menuIndex * 0x30), kRingMenuThreeQuarter * (kRingMenuOne + invSize),
	                                 kRingMenuThreeQuarter * (sizePulse + invSize), drawAngle);

	const float alphaLit = alphaBase * showScale;
	MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alphaLit)));
	MenuPcs.DrawRect(3, drawX, drawY, kRingMenuPanelWidth80, kRingMenuGbaIconSize, kRingMenuZero, static_cast<float>(m_menuIndex * 0x30),
	                                 kRingMenuThreeQuarter * sizePulse, kRingMenuThreeQuarter * sizePulse, drawAngle);

	const unsigned int flatFlags = CFlatEnabledEventFlags();
	if (((flatFlags & 8) != 0) && (Joybus.GetGBAStart(m_menuIndex) == 0)) {
		if (static_cast<unsigned char>(Joybus.IsInitSend(m_menuIndex)) == 0) {
			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1D));
			const float blink = static_cast<float>(sin(static_cast<double>(kRingMenuBlinkPhaseStep * static_cast<float>(m_commonFrameCounter))));
			const unsigned int sendAlpha = static_cast<unsigned int>(
			    static_cast<int>(kRingMenuHalf * (alphaLit * (kRingMenuOne + blink))));
			MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(sendAlpha)));
			MenuPcs.DrawRect(3, drawX, drawY, kRingMenuGbaIconSize, kRingMenuGbaIconSize, kRingMenuZero, kRingMenuCommandIconV,
			                                 kRingMenuOne, kRingMenuOne, kRingMenuZero);
		} else {
			int frameTex = (static_cast<int>(System.m_frameCounter) >> 1) % 16;
			if (frameTex >= 4) {
				frameTex &= 1;
			}
			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1D));
			MenuPcs.DrawRect(3, drawX, drawY, kRingMenuGbaIconSize, kRingMenuGbaIconSize, kRingMenuZero,
			                                 static_cast<float>(frameTex * 0x30), kRingMenuOne, kRingMenuOne, kRingMenuZero);
		}
	}

	MenuPcs.DrawInit();
}

/*
 * --INFO--
 * PAL Address: 0x800a39c4
 * PAL Size: 3884b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CRingMenu::onDraw()
{
	if (!((Game.m_gameWork.m_menuStageMode == 0) || (m_menuIndex < 1))) {
		return;
	}

	unsigned int scriptFood = Game.m_scriptFoodBase[m_menuIndex];
	if (scriptFood == 0) {
		return;
	}

	float showScale = static_cast<float>(m_displayCounter) * kRingMenuAnimStep;
	if (m_displayDirection != 0) {
		showScale = kRingMenuOne - showScale;
	}
	if (kRingMenuZero == showScale) {
		return;
	}

	float transitionScale;
	if (m_animDirection != 0) {
		transitionScale = -(static_cast<float>(m_transitionCounter) * kRingMenuAnimStep - kRingMenuOne);
	} else {
		transitionScale = static_cast<float>(m_transitionCounter) * kRingMenuAnimStep;
	}

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x16));
	sin(static_cast<double>((kRingMenuHalfPi * static_cast<float>(m_gbaAnimCounter)) / kRingMenuWobbleDivisor));
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	float cycle = static_cast<float>(fmod(static_cast<double>(kRingMenuCycleStep * static_cast<float>(m_commonFrameCounter)),
	                                      kRingMenuCycleWrapD));
	if (cycle > kRingMenuOne) {
		cycle = kRingMenuTwo - cycle;
	}
	float cycleAngle = kRingMenuPi * cycle;
	sin(static_cast<double>(cycleAngle));
	sin(static_cast<double>(kRingMenuNegHalfPi + cycleAngle));

	const double pulse = sin(static_cast<double>(kRingMenuHalfPi * showScale));

	float posLeft;
	float posAltY;
	float posMainX;
	float posMainY;
	float alphaScaleBase;
	float iconAlphaScale;
	float posAltX;

	alphaScaleBase = kRingMenuAlphaMax * showScale * transitionScale;
	const float glowOffset = kRingMenuButtonHeight * (kRingMenuOne - static_cast<float>(pulse));
	iconAlphaScale = showScale * transitionScale;
	posAltX = kRingMenuAltBaseX + glowOffset;
	posLeft = -glowOffset;
	posAltY = kRingMenuAltBaseY + glowOffset;
	posMainX = posAltX - kRingMenuButtonWidth;
	posMainY = kRingMenuMainBaseY + glowOffset;

	for (int group = 2; group >= 0; group--) {
		float posX;
		float posY;

		if (group == 2) {
			posX = kRingMenuButtonInsetX + (((m_menuIndex & 1) != 0) ? posAltX : posLeft);
			posY = kRingMenuPanelWidth80 + (((m_menuIndex & 2) != 0) ? posAltY : posLeft);
		} else {
			posX = kRingMenuButtonWidth + (((m_menuIndex & 1) != 0) ? posMainX : posLeft);
			posY = kRingMenuMainButtonY + (((m_menuIndex & 2) != 0) ? posMainY : posLeft);
		}

		float buttonAlpha = static_cast<float>(m_buttonTimers[group * 3 + 2]) * kRingMenuButtonFadeStep;
		if (m_battleButtons[group * 2 + 2] >= 0) {
			buttonAlpha = kRingMenuOne - buttonAlpha;
		}

		if (group == 2) {
			CGPartyObj* partyObj = Game.m_partyObjArr[m_menuIndex];
			buttonAlpha = static_cast<float>(static_cast<int>((partyObj->m_partyData.commandMode & 9) != 0));
		}

		if (kRingMenuZero == buttonAlpha) {
			continue;
		}

		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1F));
		MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(buttonAlpha * alphaScaleBase)));

		float drawX;
		float drawY;
		switch (group) {
		case 0: {
			const float wobble = static_cast<float>(sin(static_cast<double>(kRingMenuHalfPi * buttonAlpha)));
			drawX = -(kRingMenuButtonInsetX * wobble - (kRingMenuWobbleDivisor + posX));
			drawY = posY;
			MenuPcs.DrawRect(0, drawX, drawY, kRingMenuLabelPanelWidth, kRingMenuButtonHeight, kRingMenuZero, kRingMenuZero,
			                                 kRingMenuOne, kRingMenuOne, kRingMenuZero);
			MenuPcs.DrawRect(0, drawX, drawY, kRingMenuButtonWidth, kRingMenuButtonHeight, kRingMenuZero, kRingMenuCommandCellSize,
			                                 kRingMenuOne, kRingMenuOne, kRingMenuZero);
			break;
		}
		case 1: {
			const float wobble = static_cast<float>(sin(static_cast<double>(kRingMenuHalfPi * buttonAlpha)));
			drawX = -(kRingMenuButtonInsetX * wobble - posX);
			drawY = kRingMenuIconSize + posY;
			MenuPcs.DrawRect(0, drawX, drawY, kRingMenuLabelPanelWidth, kRingMenuIconSize, kRingMenuZero, kRingMenuButtonHeight,
			                                 kRingMenuOne, kRingMenuOne, kRingMenuZero);
			MenuPcs.DrawRect(0, drawX, drawY, kRingMenuIconSize, kRingMenuIconSize, kRingMenuButtonWidth, kRingMenuCommandCellSize,
			                                 kRingMenuOne, kRingMenuOne, kRingMenuZero);
			break;
		}
		case 2:
			drawX = posX;
			drawY = posY;
			MenuPcs.DrawRect(0, posX, posY, kRingMenuCommandPanelWidth, kRingMenuButtonHeight, kRingMenuZero, kRingMenuCommandIconY,
			                                 kRingMenuOne, kRingMenuOne, kRingMenuZero);
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
				font->SetMargin(kRingMenuFontMargin);
				font->SetShadow(1);
				font->SetTlut(4);

				float scroll = m_spinAccumulator;
				float labelAlpha = kRingMenuOne;
				for (;;) {
					if (scroll >= labelAlpha) {
						if (Game.m_gameWork.m_bossArtifactStageIndex == 0x19) {
							cmdIndex = (cmdIndex + 1) % 5;
						} else {
							cmdIndex = caravanWork->GetNextCmdListIdx(cmdIndex, -1);
						}
						scroll -= kRingMenuOne;
					} else if (scroll <= kRingMenuNegativeOne) {
						if (Game.m_gameWork.m_bossArtifactStageIndex == 0x19) {
							cmdIndex = (cmdIndex + 4) % 5;
						} else {
							cmdIndex = caravanWork->GetNextCmdListIdx(cmdIndex, 1);
						}
						scroll += kRingMenuOne;
					} else {
						break;
					}
				}

				double mag = fabs(static_cast<double>(m_spinAccumulator));
				double labelAlphaD;
				if (mag < kRingMenuSpinEpsilon) {
					labelAlphaD = kRingMenuSpinAlphaScale * mag;
				} else {
					labelAlphaD = kRingMenuOneD;
				}
				labelAlpha = static_cast<float>(labelAlphaD);

				int prev1 = (Game.m_gameWork.m_bossArtifactStageIndex == 0x19)
				                ? (cmdIndex + 4) % 5
				                : caravanWork->GetNextCmdListIdx(cmdIndex, -1);
				int prev2 = (Game.m_gameWork.m_bossArtifactStageIndex == 0x19)
				                ? (prev1 + 4) % 5
				                : caravanWork->GetNextCmdListIdx(prev1, -1);

				labelAlpha *= iconAlphaScale;
				drawCommand(m_menuIndex, font, posX, posY, caravanWork, prev2, scroll - kRingMenuTwo, labelAlpha);
				drawCommand(m_menuIndex, font, posX, posY, caravanWork, prev1, scroll - kRingMenuOne, labelAlpha);
				int next1 = (Game.m_gameWork.m_bossArtifactStageIndex == 0x19)
				                ? (cmdIndex + 1) % 5
				                : caravanWork->GetNextCmdListIdx(cmdIndex, 1);
				int next2 = (Game.m_gameWork.m_bossArtifactStageIndex == 0x19)
				                ? (next1 + 1) % 5
				                : caravanWork->GetNextCmdListIdx(next1, 1);
				drawCommand(m_menuIndex, font, posX, posY, caravanWork, next2, kRingMenuTwo + scroll, labelAlpha);
				drawCommand(m_menuIndex, font, posX, posY, caravanWork, next1, kRingMenuOne + scroll, labelAlpha);
				drawCommand(m_menuIndex, font, posX, posY, caravanWork, cmdIndex, scroll, iconAlphaScale);
				MenuPcs.DrawInit();
			}
		}

		const float textX2 = kRingMenuTextBaseX + drawX;
		const float textX0 = textX2 + kRingMenuTextOffsetX;
		const float textY1 = (kRingMenuTextOffsetY + drawY) - kRingMenuShadowOffset;
		const float textY0 = (kRingMenuSmallOffset + drawY) - kRingMenuShadowOffset;
		const float textX1 = (kRingMenuCommandCellSize + drawX) + kRingMenuTextOffsetX;
		const float textY2 = kRingMenuCommandTextOffsetY + drawY;
		CFont* font = MenuPcs.m_fonts[1];
		for (int button = 1; button >= 0; button--) {
			const int buttonValue = (&m_battleButtons[group * 2 + 2])[button];
			if (buttonValue < 0) {
				continue;
			}

			const char* label;
			if ((buttonValue & 0x8000) == 0) {
				label = Game.m_cFlatDataArr[1].TableStrings(4)[buttonValue];
			} else {
				label = Game.m_cFlatDataArr[1].TableStrings(0)[(buttonValue & ~0x8000) * 5 + 4];
			}

			float fade = static_cast<float>((&m_buttonTimers[group * 3])[button]) * kRingMenuButtonFadeStep;
			if (button == 0) {
				fade = kRingMenuOne - fade;
			}

			font->DrawInit();
			font->SetMargin(kRingMenuFontMargin);
			font->SetShadow(1);

			float textScale;
			switch (group) {
			case 0:
				font->SetTlut(0xD);
				textScale = kRingMenuItemTextScale;
				break;
			case 1:
				font->SetTlut(0xE);
				textScale = kRingMenuThreeQuarter;
				break;
			case 2: {
				font->SetTlut((buttonValue == 1) ? 7 : 4);
				const float wobble = static_cast<float>(sin(static_cast<double>(kRingMenuHalfPi * (kRingMenuOne - fade))));
				textScale = kRingMenuThreeQuarter * (kRingMenuTextWobbleScale * wobble + kRingMenuOne);
				break;
			}
			}

			font->SetScaleX(textScale);
			font->SetScaleY(textScale);

			const float width = font->GetWidth(label);
			if ((group == 2) && (m_battleButtons[2] >= 0)) {
				font->SetColor(CColor(0xFF, 0xFF, 0xFF,
					static_cast<unsigned char>(kRingMenuDimAlphaScale * (showScale * (kRingMenuAlphaMax * fade * transitionScale)))).color);
			} else {
				font->SetColor(CColor(0xFF, 0xFF, 0xFF,
					static_cast<unsigned char>(showScale * (kRingMenuAlphaMax * fade * transitionScale))).color);
			}

			float textX;
			float textY;
			switch (group) {
			case 0:
				textX = -(kRingMenuHalf * width - textX0);
				textY = textY0;
				break;
			case 1:
				textX = -(kRingMenuHalf * width - textX1);
				textY = textY1;
				break;
			case 2:
				textX = -(kRingMenuHalf * width - textX2);
				textY = textY2;
				break;
			}

			font->SetPosX(textX);
			font->SetPosY(textY);
			font->SetPosZ(kRingMenuZero);
			if (group != 2) {
				font->Draw(label);
			}
			MenuPcs.DrawInit();

			if (group == 2) {
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1F));
				CGPartyObj* partyObj = Game.m_partyObjArr[m_menuIndex];
				if (partyObj != 0) {
					CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(partyObj->m_scriptHandle);
					if ((caravanWork != 0) && ((CFlatGameFlags() & CFlatGameFlag_Bit1) == 0)) {
						const float barY = kRingMenuTextOffsetX + textY;
						const float fullAlpha = showScale * (kRingMenuAlphaMax * fade * transitionScale);
						const float dimAlpha = showScale * (kRingMenuCommandPanelWidth * fade * transitionScale);

						for (unsigned int i = 0; i < caravanWork->m_numCmdListSlots; i++) {
							int maxCharge;
							int curCharge;
							int charge = caravanWork->GetMagicCharge(i, maxCharge, curCharge);

							float blink;
							if (charge != 0) {
								MenuPcs.SetColor(CColor(0x00, 0xFF, 0x00, static_cast<unsigned char>(fullAlpha)));
								blink = static_cast<float>(static_cast<int>((System.m_frameCounter >> 2) & 1));
							} else if (caravanWork->IsSelectedCmdList(i)) {
								MenuPcs.SetColor(CColor(0x20, 0xFF, 0x20, static_cast<unsigned char>(fullAlpha)));
								blink = kRingMenuZero;
							} else {
								MenuPcs.SetColor(CColor(0x80, 0x80, 0x80, static_cast<unsigned char>(dimAlpha)));
								blink = kRingMenuZero;
							}

							MenuPcs.DrawRect(3,
								kRingMenuShadowOffset +
									((textX2 - static_cast<float>((caravanWork->m_numCmdListSlots * 8) / 2)) +
									 static_cast<float>(i * 8)),
								barY, kRingMenuSmallIconSize, kRingMenuSmallIconSize,
								kRingMenuSmallIconSize * (kRingMenuSmallIconSize + blink), kRingMenuCommandCellSize,
								kRingMenuOne, kRingMenuOne, kRingMenuZero);
						}
					}
				}
			}
		}
	}

	MenuPcs.DrawInit();
}

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
		commandLabel = caravanWork->GetWeaponAttrib(cmdIndex);
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

	waveX = static_cast<double>(kRingMenuSpinWaveAmplitude * static_cast<float>(sin(static_cast<double>(angle))));
	waveSinY = static_cast<float>(sin(static_cast<double>(angle)));
	reverseDir = false;
	if ((state == 0) || (state == 3)) {
		reverseDir = true;
	}
	waveDirection = 1;
	if (reverseDir) {
		waveDirection = -1;
	}
	waveY = static_cast<float>(waveDirection) * (kRingMenuGbaOrbitYScale * waveSinY);
	if (Game.m_gameWork.m_bossArtifactStageIndex == 0x19) {
		waveY = waveY + kRingMenuTwo;
	}

	font->SetScale(static_cast<float>(-(kRingMenuSpinScaleSlopeD * fabs(static_cast<double>(angle)) - kRingMenuSpinScaleBaseD)));
	textWidth = static_cast<float>(font->GetWidth(commandLabel));
	fVar1 = static_cast<float>(-(kRingMenuSpinAlphaSlopeD * fabs(static_cast<double>(angle)) - kRingMenuOneD));
	textHeight = static_cast<float>(font->m_glyphHeight) * font->scaleY;

	clampedAlpha = (fVar1 < kRingMenuZero) ? kRingMenuZero : ((kRingMenuOne < fVar1) ? kRingMenuOne : fVar1);

	font->SetColor(CColor(0xFF, 0xFF, 0xFF,
		static_cast<unsigned char>((kRingMenuAlphaMax * alphaScale) * clampedAlpha)).color);
	font->SetPosX(static_cast<float>(waveX) +
		((kRingMenuTextBaseX + posX) - textWidth * kRingMenuHalf));
	font->SetPosY(kRingMenuGbaOrbitYScale +
		(waveY + ((kRingMenuShadowOffset + posY) - textHeight * kRingMenuHalf)));
	font->SetPosZ(kRingMenuZero);
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
			m_displayDirection = (static_cast<unsigned int>(__cntlzw(static_cast<unsigned int>(m_displayDirection))) >> 5) & 0xFF;
			m_displayCounter = 0x10 - m_displayCounter;
		}

		float* anim = m_animFloat[0];
		const float animStep = kRingMenuBlinkPhaseStep;
		int count = 9;
		const float animMin = kRingMenuZero;

		m_displayCounter = clampDecToZero(m_displayCounter);
		m_transitionCounter = clampDecToZero(m_transitionCounter);
		m_commonFrameCounter = m_commonFrameCounter + 1;
		m_timerB = clampDecToZero(m_timerB);

		m_buttonTimers[0] = clampDecToZero(m_buttonTimers[0]);
		m_buttonTimers[1] = clampDecToZero(m_buttonTimers[1]);
		m_buttonTimers[2] = clampDecToZero(m_buttonTimers[2]);
		m_buttonTimers[3] = clampDecToZero(m_buttonTimers[3]);
		m_buttonTimers[4] = clampDecToZero(m_buttonTimers[4]);
		m_buttonTimers[5] = clampDecToZero(m_buttonTimers[5]);

		m_buttonTimers[6] = clampDecToZero(m_buttonTimers[6]);
		m_buttonTimers[7] = clampDecToZero(m_buttonTimers[7]);
		m_buttonTimers[8] = clampDecToZero(m_buttonTimers[8]);
		do {
			anim[0] = anim[0] - animStep;
			if (animMin > anim[0]) {
				anim[0] = animMin;
			}
			anim[1] = anim[1] - animStep;
			if (animMin > anim[1]) {
				anim[1] = animMin;
			}
			anim[2] = anim[2] - animStep;
			if (anim[2] < animMin) {
				anim[2] = animMin;
			}
			anim += 3;
			count--;
		} while (count != 0);

		fmod(static_cast<double>(m_spinPhase), kRingMenuOneD);
		int i = 0x1B;
		while (i > 0) {
			i--;
		}

		int ctrlMode = Joybus.GetCtrlMode(m_menuIndex);
		unsigned int gbaConnected = (static_cast<unsigned int>(__cntlzw(1 - ctrlMode)) >> 5) & 0xFF;

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

		float scrollDelta = kRingMenuZero;
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
								const int menuIdx = m_menuIndex;
								unsigned char lockOut = 0;
								if ((Pad.m_debugPadLock != 0) || ((menuIdx == 0) && (Pad.m_debugPadPort != -1))) {
									lockOut = 1;
								}
								unsigned short trigger;
								if (lockOut != 0) {
									trigger = 0;
								} else {
									const int idx =
										menuIdx & ~(~(Pad.m_debugPadPort - menuIdx | menuIdx - Pad.m_debugPadPort) >> 31);
									trigger = Pad.GetPadInputs()[idx].button[0];
								}
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
						scrollDelta = kRingMenuZero;
					}

				}
			}

			*trackedCmd = currentCmd;
			m_spinAccumulator = m_spinAccumulator + scrollDelta;
			m_spinAccumulator *= kRingMenuSpinDamping;
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
	return static_cast<double>(kRingMenuOne - static_cast<float>(m_displayCounter) * kRingMenuAnimStep);
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
	m_spinPhase = kRingMenuZero;
	m_gbaConnectedFlag = 0;
	m_gbaAnimCounter = 0;
	m_commonFrameCounter = 0;
	m_unk4f8 = 0;
	m_timerB = 0;
	m_currentCommandIndex = 0;
	m_spinAccumulator = kRingMenuZero;
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

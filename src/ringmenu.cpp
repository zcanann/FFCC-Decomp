#include "ffcc/ringmenu.h"
#include "ffcc/joybus.h"
#include "ffcc/pad.h"
#include "ffcc/p_game.h"

#include <math.h>

extern "C" {
void* __ct__6CColorFUcUcUcUc(void* color, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(void* menuPcs, int fmt);
void SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(void* menuPcs, int tex);
void SetColor__8CMenuPcsFR6CColor(void* menuPcs, void* color);
void DrawRect__8CMenuPcsFUlfffffffff(
    void* menuPcs, unsigned long flags, float x, float y, float w, float h, float u, float v, float uvScaleX, float uvScaleY,
    float rot);
void DrawInit__8CMenuPcsFv(void* menuPcs);

bool GetGBAStart__6JoyBusFi(void* joyBus, int portIndex);
int IsInitSend__6JoyBusFi(void* joyBus, int portIndex);

extern unsigned char MenuPcs[];
extern unsigned char Joybus[];
extern unsigned char CFlat[];

extern float FLOAT_803309c0;
extern float FLOAT_803309c4;
extern float FLOAT_803309cc;
extern float FLOAT_80330a08;
extern float FLOAT_80330a0c;
extern float FLOAT_80330a10;
extern float FLOAT_80330a14;
extern float FLOAT_80330a18;
extern float FLOAT_80330a28;
extern float FLOAT_80330a2c;
extern float FLOAT_80330a30;
extern float FLOAT_80330a34;
extern float FLOAT_80330a38;
extern float FLOAT_80330a3c;
extern float FLOAT_80330a40;
extern float FLOAT_80330a44;
extern float FLOAT_80330a48;
extern float FLOAT_80330a4c;
extern float FLOAT_80330a54;
extern float FLOAT_80330a58;
extern float FLOAT_80330a5c;

extern double DOUBLE_80330a00;
extern double DOUBLE_80330a20;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CRingMenu::CRingMenu()
{
	// TODO
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
CRingMenu::~CRingMenu()
{
	reinterpret_cast<void (*)(CRingMenu*)>(reinterpret_cast<void**>(this)[4])(this);
	CMenu::Create();

	char* self = reinterpret_cast<char*>(this);
	*reinterpret_cast<int*>(self + 0x504) = 0;
	*reinterpret_cast<int*>(self + 0x500) = 0;
	*reinterpret_cast<int*>(self + 0x0C) = -1;
	*reinterpret_cast<int*>(self + 0x14) = 0x10;
	*reinterpret_cast<int*>(self + 0x10) = 1;
	*reinterpret_cast<int*>(self + 0x18) = 0;
	*reinterpret_cast<int*>(self + 0x20) = -1;
	*reinterpret_cast<int*>(self + 0x24) = -1;
	*reinterpret_cast<int*>(self + 0x38) = 0;
	*reinterpret_cast<int*>(self + 0x3C) = 0;
	*reinterpret_cast<int*>(self + 0x40) = 0;
	*reinterpret_cast<int*>(self + 0x1C) = 0;
	*reinterpret_cast<int*>(self + 0x28) = -1;
	*reinterpret_cast<int*>(self + 0x2C) = -1;
	*reinterpret_cast<int*>(self + 0x44) = 0;
	*reinterpret_cast<int*>(self + 0x48) = 0;
	*reinterpret_cast<int*>(self + 0x4C) = 0;
	*reinterpret_cast<int*>(self + 0x20) = 0;
	*reinterpret_cast<int*>(self + 0x30) = -1;
	*reinterpret_cast<int*>(self + 0x34) = -1;
	*reinterpret_cast<int*>(self + 0x50) = 0;
	*reinterpret_cast<int*>(self + 0x54) = 0;
	*reinterpret_cast<int*>(self + 0x58) = 0;
	*reinterpret_cast<int*>(self + 0x5C) = -1;
	*reinterpret_cast<int*>(self + 0x60) = -1;
	*reinterpret_cast<float*>(self + 0x64) = 0.0f;
	*reinterpret_cast<int*>(self + 0x4EC) = 0;
	*reinterpret_cast<int*>(self + 0x4F0) = 0;
	*reinterpret_cast<int*>(self + 0x4F4) = 0;
	*reinterpret_cast<int*>(self + 0x4F8) = 0;
	*reinterpret_cast<int*>(self + 0x4FC) = 0;
	*reinterpret_cast<int*>(self + 0x508) = 0;
	*reinterpret_cast<float*>(self + 0x50C) = 0.0f;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRingMenu::Create()
{
	// TODO
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
 * PAL Address: 0x800a51ac
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
double CRingMenu::GetDispCounter()
{
	const int displayCounter = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x500);
	return -(static_cast<double>(static_cast<float>(displayCounter) * 0.0625f - 1.0f));
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
	char* self = reinterpret_cast<char*>(this);

	if ((Game.game.m_gameWork.m_menuStageMode != 0) && (*reinterpret_cast<int*>(self + 0x0C) >= 1)) {
		return;
	}

	int* const menuIndex = reinterpret_cast<int*>(self + 0x0C);
	int* const animDirection = reinterpret_cast<int*>(self + 0x10);
	int* const transitionTimer = reinterpret_cast<int*>(self + 0x14);
	int* const displayCounter = reinterpret_cast<int*>(self + 0x500);
	int* const gbaAnimCounter = reinterpret_cast<int*>(self + 0x504);
	int* const gbaConnectedFlag = reinterpret_cast<int*>(self + 0x508);
	float* const commandScrollOffset = reinterpret_cast<float*>(self + 0x50C);
	int* const commonFrameCounter = reinterpret_cast<int*>(self + 0x4EC);
	int* const buttonTimers = reinterpret_cast<int*>(self + 0x38);
	int* const currentCommandIndex = reinterpret_cast<int*>(self + 0x5C);
	float* const animFloat = reinterpret_cast<float*>(self + 0x64);

	const int inputMask = *reinterpret_cast<int*>(CFlat + 0x12A0) & *reinterpret_cast<int*>(CFlat + 0x12A4);
	const int nextDirection = (inputMask >> 2) & 1;
	if (*animDirection != nextDirection) {
		*animDirection = nextDirection;
		*displayCounter = 0x10 - *displayCounter;
	}

	decClamp0(displayCounter);
	decClamp0(transitionTimer);
	*commonFrameCounter += 1;
	decClamp0(reinterpret_cast<int*>(self + 0x4F8));
	for (int i = 0; i < 8; i++) {
		decClamp0(&buttonTimers[i]);
	}
	decClamp0(reinterpret_cast<int*>(self + 0x4FC));

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 3; j++) {
			float& v = animFloat[i * 3 + j];
			v -= 0.1f;
			if (v < 0.0f) {
				v = 0.0f;
			}
		}
	}

	float& spinAccumulator = *reinterpret_cast<float*>(self + 0x4F4);
	spinAccumulator = (float)fmod(spinAccumulator, 360.0f);

	bool gbaConnected = Joybus.GetCtrlMode(*menuIndex) == 1;
	if (!Joybus.GetGBAStart(*menuIndex)) {
		gbaConnected = true;
	}

	const unsigned int padType = Joybus.GetPadType(*menuIndex);
	if ((padType == 0x09000000) || (padType == 0x8B100000)) {
		gbaConnected = false;
	}

	if (*gbaConnectedFlag != static_cast<int>(gbaConnected)) {
		*gbaConnectedFlag = static_cast<int>(gbaConnected);
		*gbaAnimCounter = 0x0C - *gbaAnimCounter;
	}
	decClamp0(gbaAnimCounter);

	CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.game.m_scriptFoodBase[*menuIndex]);
	if (caravanWork == nullptr) {
		return;
	}

	int commandIndex = static_cast<int>(caravanWork->m_currentCmdListIndex);
	if (Game.game.m_gameWork.m_bossArtifactStageIndex == 0x19) {
		commandIndex = *reinterpret_cast<int*>(Chara + 0x2008);
	}

	float step = 0.0f;
	if (*currentCommandIndex != commandIndex) {
		for (int dist = 1; dist < 4; dist++) {
			const int cw = (commandIndex + dist) % 5;
			const int ccw = (commandIndex + 5 - dist) % 5;
			if (*currentCommandIndex == ccw) {
				step = static_cast<float>(dist);
				break;
			}
			if (*currentCommandIndex == cw) {
				step = -static_cast<float>(dist);
				break;
			}
		}
	}

	*currentCommandIndex = commandIndex;
	*commandScrollOffset = (*commandScrollOffset + step) * 0.95f;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void drawCommand(int, CFont*, float, float, CCaravanWork*, int, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRingMenu::onDraw()
{
	// TODO
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
    int menuIndex = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x8);
    if (!((Game.game.m_gameWork.m_menuStageMode == 0 || menuIndex < 1) && (Game.game.m_scriptFoodBase[menuIndex] != 0))) {
        return;
    }

    int displayCounter = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x500);
    double anim = (double)(FLOAT_80330a08 * (float)((double)(displayCounter + 0x80000000ULL) - DOUBLE_80330a00));
    if (*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x504) != 0) {
        anim = (double)(FLOAT_803309cc - (float)anim);
    }
    if ((double)FLOAT_803309c0 == anim) {
        return;
    }

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcs, 0x16);

    int gbaAnimCounter = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x508);
    double phaseSin =
        (double)(float)sin((double)((FLOAT_80330a0c * (float)((double)(gbaAnimCounter + 0x80000000ULL) - DOUBLE_80330a00)) /
                              FLOAT_80330a10));
    if (*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x4FC) == 1) {
        phaseSin = (double)(FLOAT_803309cc - (float)phaseSin);
    }

    float menuX = (menuIndex & 1) != 0 ? 592.0f : 48.0f;
    float menuY = (menuIndex & 2) != 0 ? 400.0f : 48.0f;

    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(MenuPcs, 0);

    int frameCounter = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x4EC);
    double pulseScale = (double)(FLOAT_80330a14 * (FLOAT_803309cc - (float)phaseSin) + FLOAT_803309cc);
    double wave = (double)fmod(
        (double)(FLOAT_80330a18 * (float)((double)(frameCounter + 0x80000000ULL) - DOUBLE_80330a00)),
        DOUBLE_80330a20);
    float waveF = (float)wave;
    if (FLOAT_803309cc < waveF) {
        waveF = FLOAT_80330a28 - waveF;
    }

    double phase = (double)(FLOAT_80330a2c * waveF);
    double sinA = (double)(float)sin(phase);
    double sinB = (double)(float)sin((double)(FLOAT_80330a30 + (float)phase));

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcs, 0x1E);

    double alphaScale = (double)(FLOAT_80330a34 * (float)phaseSin);
    int shadowAlpha = (int)(FLOAT_803309c4 * (float)alphaScale * (float)anim);
    unsigned char colorShadow[8];
    __ct__6CColorFUcUcUcUc(colorShadow, 0, 0, 0, static_cast<unsigned char>(shadowAlpha));
    SetColor__8CMenuPcsFR6CColor(MenuPcs, colorShadow);

    double invPulse = (double)(FLOAT_803309cc - (float)pulseScale);
    double drawX = (double)(menuX + FLOAT_80330a3c * (float)(pulseScale * sinB));
    double drawY = (double)(menuY - FLOAT_80330a40 * (float)(pulseScale * sinA));
    float v = static_cast<float>(menuIndex * 0x30);
    DrawRect__8CMenuPcsFUlfffffffff(
        MenuPcs, 3, (float)(drawX + FLOAT_80330a38), (float)(drawY + FLOAT_80330a38), FLOAT_80330a44, FLOAT_80330a48,
        FLOAT_803309c0, v, FLOAT_80330a4c * (FLOAT_803309cc + (float)invPulse), FLOAT_80330a4c * ((float)pulseScale + (float)invPulse),
        0.0f);

    int iconAlpha = (int)((float)sinB * (float)anim);
    unsigned char colorIcon[8];
    __ct__6CColorFUcUcUcUc(colorIcon, 0xFF, 0xFF, 0xFF, static_cast<unsigned char>(iconAlpha));
    SetColor__8CMenuPcsFR6CColor(MenuPcs, colorIcon);
    DrawRect__8CMenuPcsFUlfffffffff(
        MenuPcs, 3, (float)drawX, (float)drawY, FLOAT_80330a44, FLOAT_80330a48, FLOAT_803309c0, v,
        FLOAT_80330a4c * (float)pulseScale, FLOAT_80330a4c * (float)pulseScale, 0.0f);

    if (((*reinterpret_cast<unsigned int*>(CFlat + 0x12A0) & *reinterpret_cast<unsigned int*>(CFlat + 0x12A4) & 8) != 0) &&
        !GetGBAStart__6JoyBusFi(Joybus, menuIndex)) {
        if (IsInitSend__6JoyBusFi(Joybus, menuIndex) == 0) {
            SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcs, 0x1D);
            double blink = (double)sin(
                (double)(FLOAT_80330a54 *
                         (float)((double)(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x4EC) + 0x80000000ULL) - DOUBLE_80330a00)));
            unsigned int alpha =
                static_cast<unsigned int>(FLOAT_803309c4 * (float)(iconAlpha * (FLOAT_803309cc + (float)blink)));
            unsigned char colorBlink[8];
            __ct__6CColorFUcUcUcUc(colorBlink, 0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alpha & 0xFF));
            SetColor__8CMenuPcsFR6CColor(MenuPcs, colorBlink);
            DrawRect__8CMenuPcsFUlfffffffff(
                MenuPcs, 3, (float)drawX, (float)drawY, FLOAT_80330a48, FLOAT_80330a48, FLOAT_803309c0, FLOAT_80330a58, FLOAT_803309cc,
                FLOAT_803309cc, 0.0f);
        } else {
            int frame = static_cast<int>(System.m_frameCounter);
            int sign = frame >> 0x1F;
            unsigned int texSel = (sign * 0x10 | (unsigned int)(((frame >> 1) * 0x10000000 + sign) >> 0x1C)) - sign;
            if ((int)texSel > 3) {
                texSel &= 1;
            }
            SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcs, 0x1D);
            DrawRect__8CMenuPcsFUlfffffffff(
                MenuPcs, 3, (float)drawX, (float)drawY, FLOAT_80330a48, FLOAT_80330a48, FLOAT_803309c0, (float)(texSel * 0x30),
                FLOAT_803309cc, FLOAT_803309cc, 0.0f);
        }
    }

    DrawInit__8CMenuPcsFv(MenuPcs);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRingMenu::onScriptChanging(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRingMenu::onScriptChanged(char*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRingMenu::SetFade(int)
{
	// TODO
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
	int* battleButtons = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x18);

	if (battleButtons[buttonIndex] == newValue) {
		return;
	}

	battleButtons[buttonIndex] = newValue;
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

	int slot8 = buttonGroupIndex * 8;
	int currentCommand = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + slot8 + 0x20);

	if (currentCommand == newCommandId) {
		return;
	}

	if (((currentCommand >= 0) && (newCommandId < 0)) || ((currentCommand < 0) && (newCommandId >= 0))) {
		int slot12 = buttonGroupIndex * 12;
		int* timer2 = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + slot12 + 0x40);
		*timer2 = 8 - *timer2;
	}

	*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + slot8 + 0x24) = currentCommand;
	*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + slot8 + 0x20) = newCommandId;

	int slot12 = buttonGroupIndex * 12;
	char* self = reinterpret_cast<char*>(this);
	int* timer0 = reinterpret_cast<int*>(self + slot12 + 0x38);
	*reinterpret_cast<int*>(self + slot12 + 0x3c) = 8 - *timer0;
	*timer0 = 8 - *timer0;

	if (buttonGroupIndex != 2) {
		return;
	}

	*reinterpret_cast<int*>(self + 0x60) = *reinterpret_cast<int*>(self + 0x5c);
	*reinterpret_cast<int*>(self + 0x5c) = newRotation;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CRingMenu::DrawIcon()
{
	// TODO
}

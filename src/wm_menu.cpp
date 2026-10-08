#include "ffcc/ptrarray.h"
#include "ffcc/wm_menu.h"
#include "ffcc/joybusconst.h"
#include "ffcc/cardconst.h"

#include "ffcc/baseobj.h"
#include "ffcc/goout.h"
#include "ffcc/gbaque.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/math.h"
#include "ffcc/menu.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_chara.h"
#include "ffcc/game.h"
#include "ffcc/linkage.h"
#include "ffcc/map.h"
#include "ffcc/materialman.h"
#include "ffcc/sound.h"
#include "ffcc/p_light.h"
#include "ffcc/partMng.h"
#include "ffcc/p_tina.h"
#include "ffcc/THPSimple.h"
#include "ffcc/joybus.h"
#include "ffcc/color.h"
#include "ffcc/vector.h"
#include "ffcc/cflat_runtime2.h"
#include "ffcc/textureman.h"
#include "ffcc/mesmenu.h"
#include "ffcc/file.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/os.h>
#include <PowerPC_EABI_Support/Runtime/New.h>
#include <math.h>
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdlib.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>
#include "ffcc/fontman.h"

extern "C" char* strstr(const char*, const char*);

#ifdef VERSION_GCCJGC
#define WM_TEXTURE_START 21
#define WM_TEXTURE_COUNT 44
#else
#define WM_TEXTURE_START 22
#define WM_TEXTURE_COUNT 47
#endif

unsigned char lbl_8032E8AC = 1;
struct WmMenuLightTable
{
	int m_diffuseCount;
	_GXColor m_ambient;
	_GXColor m_diffuseColors[3];
	Vec m_diffuseDirs[3];
};

#ifndef VERSION_GCCJGC
char* g_strWMMenuMes[5][11] = {
	{
		"Select party members and create new characters.",
		"View diary entries.",
		"Import character from another Memory Card.",
		"Configure game settings.",
		"Save game data to a Memory Card.",
		"Select party members.",
		"Select \"Empty\" to create a new character.",
		"Press START when finished.",
		"Select game data to load.",
		"Select character to import.",
		"Select character to delete.",
	},
	{
		"Charaktere kreieren und Gruppenmitglieder bestimmen.",
		"Die niedergeschriebenen Tagebucheintr\344ge lesen.",
		"Charaktere von anderen Memory Cards einladen.",
		"Einstellungen zum Spiel vornehmen.",
		"Aktuelle Spielst\344nde auf die Memory Card speichern.",
		"Bitte die Gruppenmitglieder bestimmen.",
		"\204Frei\" w\344hlen, um einen neuen Charakter zu kreieren.",
		"START dr\374cken, um auf Reisen zu gehen.",
		"Bitte einen Spielstand w\344hlen.",
		"Zu bewegenden Charakter w\344hlen.",
		"Zu l\366schenden Charakter w\344hlen.",
	},
	{
		"Seleziona i membri del gruppo e crea nuovi personaggi.",
		"Leggi il diario.",
		"Importa personaggi da un'altra Memory Card (Scheda Memoria).",
		"Modifica le impostazioni di gioco.",
		"Salva la partita su Memory Card (Scheda Memoria).",
		"Seleziona i membri del gruppo.",
		"Seleziona Vuoto per creare un nuovo personaggio.",
		"Premi START quando hai finito.",
		"Seleziona i dati da caricare.",
		"Seleziona il personaggio che vuoi trasferire.",
		"Seleziona il personaggio che vuoi cancellare.",
	},
	{
		"Composez votre \351quipe et cr\351ez de nouveaux personnages",
		"Consultez le journal",
		"Importez un personnage d'une autre Memory Card (carte m\351moire)",
		"Modifiez les options du jeu",
		"Sauvegardez la partie sur une Memory Card (carte m\351moire)",
		"Composez votre \351quipe",
		"S\351lectionnez \"Vide\" pour cr\351er un nouveau personnage",
		"Appuyez sur START quand vous avez termin\351",
		"S\351lectionnez les donn\351es de jeu \340 charger",
		"S\351lectionnez le personnage \340 importer",
		"S\351lectionnez le personnage \340 effacer",
	},
	{
		"Selecciona los miembros del grupo y crea nuevos personajes.",
		"Ver las anotaciones del diario.",
		"Transferir un personaje de otra Memory Card al juego actual.",
		"Configurar las opciones del juego.",
		"Guardar los datos del juego en la Memory Card.",
		"Selecciona los miembros del grupo.",
		"Selecciona \"Vac\355o\" para crear un nuevo personaje.",
		"Pulsa START cuando termines.",
		"Seleccionar los datos del juego a cargar.",
		"Selecciona el personaje a transferir.",
		"Selecciona el personaje a eliminar.",
	},
};

#endif

static const int s_YearWTbl[] = {21, 12, 19, 18, 22, 20, 19, 19, 19, 18, 35};

static WmMenuLightTable s_Light[] = {
	{
		2, {112, 112, 108, 255},
		{{148, 148, 148, 255}, {16, 11, 51, 255}, {0, 0, 0, 255}},
		{{0.679108f, -0.559193f, -0.475516f}, {-0.079979f, 0.965926f, -0.246152f}, {0.0f, 0.0f, 0.0f}},
	},
	{
		1, {119, 107, 103, 255},
		{{171, 171, 171, 255}, {0, 0, 0, 255}, {0, 0, 0, 255}},
		{{0.579484f, -0.5f, -0.643582f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
	},
	{
		2, {128, 128, 128, 255},
		{{148, 148, 148, 255}, {16, 11, 51, 255}, {0, 0, 0, 255}},
		{{-0.479108f, -0.559193f, -0.475516f}, {0.079979f, 0.965926f, -0.246152f}, {0.0f, 0.0f, 0.0f}},
	},
};

static CMenuPcs::SPL s_WoodTrnsY[] = {
	{0.0f, 0.0f, 0.0f, 0.0f},
	{0.5f, 0.12f, 0.0f, 0.0f},
	{1.0f, 0.0f, 0.0f, 0.0f},
	{1.5f, 0.12f, 0.0f, 0.0f},
	{2.0f, 0.0f, 0.0f, 0.0f},
	{2.5f, 0.12f, 0.0f, 0.0f},
	{3.0f, 0.0f, 0.0f, 0.0f},
	{3.5f, 0.12f, 0.0f, 0.0f},
	{4.0f, 0.0f, 0.0f, 0.0f},
};

static CMenuPcs::SPL s_WoodRotY[] = {
	{0.0f, 0.0f, 0.0f, 0.0f},
	{1.0f, -7.5f, 0.0f, 0.0f},
	{2.0f, 0.0f, 0.0f, 0.0f},
	{3.0f, 7.5f, 0.0f, 0.0f},
	{4.0f, 0.0f, 0.0f, 0.0f},
};

static CMenuPcs::SPL s_YearTrnsY[] = {
	{0.0f, -5.0f, 0.0f, 0.0f},
	{0.3f, 5.0f, 0.0f, 0.0f},
	{0.4f, -2.0f, 0.0f, 0.0f},
	{0.47f, 2.0f, 0.0f, 0.0f},
	{0.5f, 0.0f, 0.0f, 0.0f},
};

static CMenuPcs::SPL s_YearTransparent[] = {
	{0.0f, 0.0f, 0.0f, 0.0f},
	{0.3f, 1.0f, 0.0f, 0.0f},
	{0.5f, 1.0f, 0.0f, 0.0f},
};

static CMenuPcs::SPL s_MenuObjYRotSpl[] = {
	{0.0f, 0.0f, -22.0647f, -22.0647f},
	{0.966667f, -15.0f, 0.0f, 0.0f},
	{2.966667f, 15.0f, 0.0f, 0.0f},
	{3.966667f, 0.0f, -22.0647f, -22.0647f},
};

static CMenuPcs::SPL s_MenuObjZRotSpl[] = {
	{0.0f, 0.0f, -11.0907f, -11.0907f},
	{0.966667f, -8.0f, 0.0f, 0.0f},
	{2.966667f, 8.0f, 0.0f, 0.0f},
	{3.966667f, 0.0f, -11.0907f, -11.0907f},
};

static CMenuPcs::SPL s_MenuObjYTrsSpl[] = {
	{0.0f, 0.25f, 0.0f, 0.0f},
	{0.966667f, -0.25f, 0.0f, 0.0f},
	{1.966667f, 0.25f, 0.0f, 0.0f},
	{2.966667f, -0.25f, 0.0f, 0.0f},
	{3.966667f, 0.25f, 0.0f, 0.0f},
};

static CMenuPcs::SPL s_MenuObjSclSpl[] = {
	{0.0f, 1.0f, 0.0f, 0.0f},
	{0.08888858f, 1.15f, 0.0f, 0.0f},
	{0.1999998f, 1.0f, 0.0f, 0.0f},
	{0.31111103f, 1.2f, 0.0f, 0.0f},
	{0.42222157f, 1.0f, 0.0f, 0.0f},
	{0.5333328f, 1.25f, 0.0f, 0.0f},
	{0.64444405f, 1.0f, 0.0f, 0.0f},
};

static CMenuPcs::FCV s_WoodTrns = {9, s_WoodTrnsY};
static CMenuPcs::FCV s_WoodRot = {5, s_WoodRotY};
static CMenuPcs::FCV s_YearTrns = {5, s_YearTrnsY};
static CMenuPcs::FCV s_YearAlpha = {3, s_YearTransparent};
static CMenuPcs::FCV s_MenuObjYRot = {4, s_MenuObjYRotSpl};
static CMenuPcs::FCV s_MenuObjZRot = {4, s_MenuObjZRotSpl};
static CMenuPcs::FCV s_MenuObjYTrs = {5, s_MenuObjYTrsSpl};
static CMenuPcs::FCV s_MenuObjScl = {7, s_MenuObjSclSpl};
extern char cRam8032ee21;

inline CGBaseObj::CGBaseObj()
{
}

inline CGObject::CGObject()
{
}

static float s_MaxAnimWait;
unsigned char lbl_8032EE1C;
char gWmMenuCursorX[2];
char gWmMenuCursorY[2];
static u64 s_Serial;
unsigned char gWmMenuScriptValueCache;

extern const char lbl_80331380[4] = {'?','?','?','?'};
extern const float FLOAT_803313dc = 0.0f;
extern const float FLOAT_803313e0 = 640.0f;
extern const float FLOAT_803313e4 = 448.0f;
extern const float FLOAT_803313e8 = 1.0f;
extern const double DOUBLE_803313F0 = 4503599627370496.0;
extern const double DOUBLE_803313F8 = 0.5;
extern const char lbl_80331400[3] = "00";
extern const float FLOAT_80331404 = 30.0f;
extern const double DOUBLE_80331408 = 4503601774854144.0;
extern const float FLOAT_80331410 = 32.0f;
extern const float FLOAT_80331414 = 6.0f;
extern const double DOUBLE_80331418 = 2.0;
extern const double DOUBLE_80331420 = 1.0;
extern const double DOUBLE_80331428 = 64.0;
extern const float FLOAT_80331430 = 368.0f;
extern const float FLOAT_80331434 = 0.5f;
extern const double DOUBLE_80331438 = 220.0;
extern const float FLOAT_80331440 = 40.0f;
extern const float FLOAT_80331444 = 369.0f;
extern const double DOUBLE_80331448 = 0.7;
extern const double DOUBLE_80331450 = 0.03;
extern const float FLOAT_80331458 = 255.0f;
extern const double DOUBLE_80331460 = 0.05;
extern const float FLOAT_80331468 = 48.0f;
extern const float FLOAT_8033146C = 248.0f;
extern const float FLOAT_80331470;
extern const float FLOAT_80331474;
extern const float FLOAT_80331478;
extern const float FLOAT_8033147c;
extern const float FLOAT_80331480 = -96.0f;
extern const double DOUBLE_80331488 = 48.0;
extern const double DOUBLE_80331490 = 24.0;
extern const double DOUBLE_80331498 = 88.0;
extern const float FLOAT_803314A0 = 112.0f;
extern const float FLOAT_803314A4 = 50.0f;
#ifdef VERSION_GCCP01
extern const double DOUBLE_803314A8 = 25.0;
#else
extern const double DOUBLE_803314A8 = 30.0;
#endif
extern const float FLOAT_803314B0 = 0.6000000238418579f;
extern const float FLOAT_803314B4 = -1.399999976158142f;
extern const float FLOAT_803314B8 = 0.1745329201221466f;
extern const float FLOAT_803314bc = 0.01745329238474369f;
#ifdef VERSION_GCCP01
extern const float FLOAT_803314c0 = 25.0f;
#else
extern const float FLOAT_803314c0 = 30.0f;
#endif
extern const float FLOAT_803314c4 = 3.0f;
extern const float FLOAT_803314c8 = 2.0f;
extern const float FLOAT_803314cc = -2.0f;
extern const double DOUBLE_803314D0 = 424.0;
extern const float FLOAT_803314D8 = 24.0f;
extern const float FLOAT_803314DC = -260.0f;
extern const float FLOAT_803314E0 = 28.399999618530273f;
extern const double DOUBLE_803314E8 = 0.1;
extern const double DOUBLE_803314F0 = 0.0;
extern const float FLOAT_803314F8 = 80.0f;
extern const float FLOAT_803314FC = 336.0f;
extern const float FLOAT_80331500 = 184.0f;
extern const double DOUBLE_80331508 = 255.0;
extern const double DOUBLE_80331510 = 8.0;
extern const float FLOAT_80331518 = 496.0f;
extern const float FLOAT_8033151c = 72.0f;
extern const float FLOAT_80331520 = 104.0f;
extern const float FLOAT_80331524 = 120.0f;
extern const float FLOAT_80331528 = 360.0f;
extern const double DOUBLE_80331530 = 0.68;
extern const double DOUBLE_80331538 = 360.0;
extern const double DOUBLE_80331540 = 32.0;
extern const float FLOAT_80331548 = 8.0f;
extern const float FLOAT_8033154C = 11.0f;
extern const float FLOAT_80331550 = 4.0f;
extern const float FLOAT_80331554 = 56.0f;
extern const float FLOAT_80331558 = 16.0f;
extern const float FLOAT_8033155C = 144.0f;
extern const float FLOAT_80331560 = 192.0f;
extern const float FLOAT_80331564 = 344.0f;
extern const float FLOAT_80331568 = 296.0f;
extern const double DOUBLE_80331570 = 56.0;
extern const float FLOAT_80331578 = 128.0f;
extern const double DOUBLE_80331580 = 29.0;
extern const float FLOAT_80331588 = 1.100000023841858f;
extern const float FLOAT_8033158C = 0.8999999761581421f;
extern const float FLOAT_80331590 = 26.0f;
extern const float FLOAT_80331594 = 0.800000011920929f;
extern const float FLOAT_80331598 = 100.0f;
extern const double DOUBLE_803315A0 = 320.0;
extern const double DOUBLE_803315A8 = 224.0;
extern const float FLOAT_803315B0 = 320.0f;
extern const float FLOAT_803315B4 = 224.0f;
extern const float FLOAT_803315B8 = 208.0f;
extern const float FLOAT_803315BC = -4.949999809265137f;
extern const double DOUBLE_803315C0 = 100.0;
extern const float FLOAT_803315C8 = 0.057692307978868484f;
extern const float FLOAT_803315cc = 0.1850000023841858f;
extern const float FLOAT_803315d0 = 0.2617993950843811f;
extern const float FLOAT_803315d4 = 1.5f;
extern const double DOUBLE_803315D8 = 0.87;
extern const float FLOAT_803315E0 = 15.0f;
extern const float FLOAT_803315E4 = -72.0f;
extern const float FLOAT_803315E8 = -0.7853981852531433f;
extern const double DOUBLE_803315F0 = 0.01745329238474369;
extern const double DOUBLE_803315F8 = 57.8;
extern const double DOUBLE_80331600 = -22.0;
extern const double DOUBLE_80331608 = 20.0;
extern const float FLOAT_80331610 = 1.0088002681732178f;
extern const float FLOAT_80331614 = -0.0872664600610733f;
extern const float FLOAT_80331618 = 0.10000000149011612f;
extern const float FLOAT_8033161C = -1.0f;
extern const float FLOAT_80331620 = -4.0f;
extern const double DOUBLE_80331628 = -0.2;
extern const double DOUBLE_80331630 = 51.5;
extern const char s_wmCharaAnimStand[6] = "stand";
extern const char s_wmCharaAnimWalk[5] = "walk";
extern const char s_wmCharaAnimRun[4] = "run";
extern const char s_wmCharaAnimGlad[5] = "glad";
extern const char s_wmCharaAnimSleep[6] = "sleep";
extern const char s_wmCharaAnimAngry[6] = "angry";
extern const float FLOAT_80331664 = -0.2617993950843811f;
extern const float FLOAT_80331668 = 0.699999988079071f;
extern const float FLOAT_8033166C = 158.0f;
extern const double DOUBLE_80331670 = 12.0;
extern const double DOUBLE_80331678 = 144.0;
extern const float FLOAT_80331680 = 64.0f;
extern const float FLOAT_80331684 = 130.0f;
extern const float FLOAT_80331688 = 134.0f;
extern const float FLOAT_8033168C = 3.5f;
extern const float FLOAT_80331690 = 0.0546875f;
extern const float FLOAT_80331694 = -50.0f;
extern const float FLOAT_80331698 = 1.2000000476837158f;
extern const float FLOAT_8033169C = 2.200000047683716f;
extern const float FLOAT_803316A0 = 3.3000001907348633f;
extern const float FLOAT_803316A4 = -0.4399999976158142f;
extern const float FLOAT_803316A8 = 1.2999999523162842f;
extern const float FLOAT_803316AC = 0.008377579972147942f;
extern const float FLOAT_803316B0 = -5.639999866485596f;
extern const float FLOAT_803316B4 = 0.6600000262260437f;
extern const float FLOAT_803316B8 = 0.40142571926116943f;
extern const float FLOAT_803316BC = -5.0f;
extern const double DOUBLE_803316C0 = 0.07;
extern const float FLOAT_803316C8 = 152.0f;
extern const float FLOAT_803316CC = 136.0f;
extern const float FLOAT_803316D0 = 288.0f;
extern const float FLOAT_803316D4 = 9.0f;
extern const double DOUBLE_803316D8 = 25.5;
extern const double DOUBLE_803316E0 = 40.0;
extern const double DOUBLE_803316E8 = 10.0;
extern const float FLOAT_803316F0 = 45.0f;
extern const float FLOAT_803316F4 = 96.0f;
extern const float FLOAT_803316F8 = 69.0f;
extern const char lbl_803316FC[8] = "\202\314\212\331\0\0\0";
extern const float FLOAT_80331704 = 240.0f;
extern const float FLOAT_80331708 = 480.0f;
extern const float FLOAT_8033170C = 0.28999999165534973f;
extern const float FLOAT_80331710 = -1.2000000476837158f;
extern const float FLOAT_80331714 = -3.5f;
extern const float FLOAT_80331718 = -1.7000000476837158f;
extern const double DOUBLE_80331720 = 1.6;
extern const float FLOAT_80331728 = 3.5999999046325684f;
extern const float FLOAT_8033172C = 2.4000000953674316f;
extern const double DOUBLE_80331730 = 1.2;
extern const double DOUBLE_80331738 = 0.9;
extern const float FLOAT_80331740 = 0.36000001430511475f;
extern const float FLOAT_80331744 = 0.3490658402442932f;
extern const float FLOAT_80331748 = 6.300000190734863f;
extern const float FLOAT_8033174c = -6.300000190734863f;
extern const float FLOAT_80331750 = -7.400000095367432f;
extern const float FLOAT_80331754 = 0.008726646192371845f;
extern const float FLOAT_80331760 = 0.30000001192092896f;
extern const float FLOAT_80331764 = -0.10000000149011612f;
extern const float FLOAT_80331768 = 200.0f;
extern const double DOUBLE_80331770 = 0.025;
extern const float FLOAT_80331778 = 172.0f;
extern const float FLOAT_8033177C = 321.0f;
extern const float FLOAT_80331780 = 14.0f;
extern const double DOUBLE_80331788 = 0.18;
extern const double DOUBLE_80331790 = 49.333333333333336;
extern const double DOUBLE_80331798 = 5.0;
extern const double DOUBLE_803317A0 = 0.035;
extern const double DOUBLE_803317A8 = 0.04;
extern const double DOUBLE_803317B0 = 0.2;
extern const float FLOAT_803317B8 = 36.0f;
extern const float FLOAT_803317BC = 93.0f;
extern const float FLOAT_803317C0 = 576.0f;
extern const float FLOAT_803317C4 = 52.0f;
extern const float FLOAT_803317C8 = 396.0f;
extern const float FLOAT_803317CC = 544.0f;
extern const float FLOAT_803317D0 = 387.0f;
extern const double DOUBLE_803317D8 = 16.0;
extern const float FLOAT_803317e0 = -0.20000000298023224f;
extern const float FLOAT_803317e4 = 51.5f;
extern const float FLOAT_803317e8 = 35.79999923706055f;
extern const float FLOAT_803317FC = 78.0f;
extern const char lbl_80331800[7] = "w_open";
extern const char lbl_80331808[7] = "idle_o";
extern const char lbl_80331810[7] = "turn_l";
extern const char lbl_80331818[7] = "turn_r";
extern const char lbl_80331820[7] = "last_l";
extern const char lbl_80331828[7] = "last_r";
extern const char lbl_80331830[8] = "w_close";
extern const char lbl_80331838[7] = "w_idle";

extern float FLOAT_80331490;
extern float FLOAT_80331498;
extern float FLOAT_803314e8;
extern float FLOAT_803314f0;

static const int kMcListEntrySize = sizeof(McListInfo);
static const int kMcListCount = 4;
#ifdef VERSION_GCCJGC
static const int kMemoryCardBannerTexture = 30;
static const int kMcSlotLeftTexture = 35;
static const int kMcSlotMiddleTexture = 36;
static const int kMcCharacterFrameTexture = 37;
static const int kMcCharacterFillTexture = 41;
static const int kCharacterNamePlateTexture = 39;
static const int kCharacterPlaceholderTexture = 49;
static const int kCharacterPanelTexture = 40;
static const int kMainMenuFrameTexture = 50;
static const int kCharacterLifeTexture = 38;
static const int kCharacterAwayTexture = 54;
static const int kWorldFrameTexture = 29;
static const int kMcWindowTextureBase = 43;
static const int kAltWindowTextureBase = 35;
static const int kWorldWoodTexture = 21;
static const int kWorldTitleWidth = 184;
static const int kWorldYearDigitY = 63;
static const int kBubbleTexture = 23;
static const int kMcYearTexture = 22;
static const int kMcYearLabelTexture = 32;
static const int kMcFaceTexture = 53;
static const int kMcTimeTexture = 31;
#else
static const int kMemoryCardBannerTexture = 31;
static const int kMcSlotLeftTexture = 36;
static const int kMcSlotMiddleTexture = 37;
static const int kMcCharacterFrameTexture = 38;
static const int kMcCharacterFillTexture = 42;
static const int kCharacterNamePlateTexture = 40;
static const int kCharacterPlaceholderTexture = 50;
static const int kCharacterPanelTexture = 41;
static const int kMainMenuFrameTexture = 51;
static const int kCharacterLifeTexture = 39;
static const int kCharacterAwayTexture = 56;
static const int kWorldFrameTexture = 30;
static const int kMcWindowTextureBase = 44;
static const int kAltWindowTextureBase = 36;
static const int kWorldWoodTexture = 22;
static const int kWorldTitleWidth = 200;
static const int kWorldYearDigitY = 67;
static const int kBubbleTexture = 24;
static const int kMcYearTexture = 23;
static const int kMcYearLabelTexture = 33;
static const int kMcFaceTexture = 55;
static const int kMcTimeTexture = 32;
#endif
static Vec s_RingOrgPos;
#ifdef VERSION_GCCJGC
static const int kTitleDrawLine = 4929;
static const int kTitleMenuTexture = 64;
static const int kTitleLogoTexture = 63;
static const float kTitleSelectionX = 248.0f;
static const float kTitleSelectionWidth = 144.0f;
static const float kTitleLabelX = 260.0f;
static const float kTitleLabelWidth = 120.0f;
static const double kTitleSlideDistance = 24.0;
#else
#ifdef VERSION_GCCE01
static const int kTitleDrawLine = 4736;
#else
static const int kTitleDrawLine = 4770;
#endif
static const int kTitleMenuTexture = 67;
static const int kTitleLogoTexture = 66;
static const float kTitleSelectionX = 172.0f;
static const float kTitleSelectionWidth = 296.0f;
static const float kTitleLabelX = 172.0f;
static const float kTitleLabelWidth = 296.0f;
static const double kTitleSlideDistance = 49.333333333333336;
#endif

#ifdef VERSION_GCCP01
static const int kMcWindowFrames = 6;
static const int kTitleMovieFrames = 2883;
static const int kTitleIdleFrames = 2450;
#else
static const int kMcWindowFrames = 8;
static const int kTitleMovieFrames = 3457;
static const int kTitleIdleFrames = 2940;
#endif

static Vec s_MMenuPos[5];

static const int kWmMenuPlayerCount = 8;
static const int kWmMenuControllerCount = 4;
static const int kWmCharaSelectCount = kWmMenuPlayerCount;
static const int kWmCharaSelectBytes = sizeof(WmCharaSelectEntry) * kWmCharaSelectCount;

static inline CCharaPcs::CHandle** GetWmCharaHandles(CMenuPcs* menu)
{
	return menu->m_wm.m_handles + 0x20;
}

static inline CCharaPcs::CHandle** GetWmWorldHandles(CMenuPcs* menu)
{
	return menu->m_wm.m_handles;
}

static inline WmCharaAnimState* GetWmCharaAnimState(CMenuPcs* menu)
{
	return menu->m_wmCharaAnimState;
}

static inline WmWorldState* GetWmWorldState(CMenuPcs* menu)
{
	return menu->m_wmWorldState;
}

static inline Mc::SaveDat* GetWmCmakeWork(CMenuPcs* menu)
{
	return menu->m_cmakeWorkActive == 1 ? menu->m_cmakeWork : 0;
}

static inline int GetWmMenuFade(short state, short frame)
{
	if (state == 1) {
		return static_cast<int>(FLOAT_80331458 * static_cast<float>(DOUBLE_803314E8 * (static_cast<double>(frame) - DOUBLE_80331408)));
	}
	if (state == 2) {
		return static_cast<int>(FLOAT_80331458);
	}
	return static_cast<int>(FLOAT_80331458 * static_cast<float>(-(DOUBLE_803314E8 * (static_cast<double>(frame) - DOUBLE_80331408) - DOUBLE_80331420)));
}

static inline CFont* GetWmFont(CMenuPcs* menu)
{
	return *reinterpret_cast<CFont**>(reinterpret_cast<unsigned char*>(menu) + 0xF8);
}

static inline void QueueWmCharaAnimState(CMenuPcs* menu, int slot, int state)
{
	if (slot < 0 || slot >= kWmMenuPlayerCount) {
		return;
	}
	GetWmCharaAnimState(menu)[slot].m_nextAnimIndex = state;
}

/*
 * --INFO--
 * PAL Address: 0x80102ED8
 * PAL Size: 220b
 * EN Address: 0x8010229C
 * EN Size: 220b
 * JP Address: 0x800FEF2C
 * JP Size: 188b
 */
void CMenuPcs::WmInit()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	m_wm.m_worldObjData = 0;
	m_wm.m_bubbleData = 0;
	m_wm.m_frameData = 0;
	m_wm.m_frameInfo = 0;
	m_wm.m_charaModelData = 0;
	m_wm.m_charaSelectData = 0;
	m_wmWorldState = 0;
	m_wmCharaState = 0;
	m_wmWorldParams = 0;
	m_effectWork = 0;
	m_wmWorkBuffer = 0;
	s_MaxAnimWait = 0.0f;
	m_wmThpActive = 0;
	m_textureLocIndex = 0;
	memset(bytes + 4, 0, 0x1C);
	bytes[0xD] = 0;
	bytes[0x10] = 0;
	bytes[0x12] = 0;
	bytes[0x13] = 0;
	bytes[0xD] = 1;
	bytes[0x16] = 0;
	gWmMenuCursorX[0] = 0xFF;
	gWmMenuCursorX[1] = 0xFF;
	gWmMenuCursorY[0] = 0xFF;
	gWmMenuCursorY[1] = 0xFF;
	s_Serial = -1;
#ifndef VERSION_GCCJGC
	int scriptValue = static_cast<int>(Game.m_gameWork.m_scriptSysVal0);
	gWmMenuScriptValueCache = scriptValue;
	if (scriptValue > 99) {
		gWmMenuScriptValueCache = 100;
	}
#endif
}

/*
 * --INFO--
 * PAL Address: 0x80102ed4
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::createWorld()
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x80102e9c
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMenuPcs::EffectInfo::EffectInfo()
{
}

/*
 * --INFO--
 * PAL Address: 0x8010172C
 * PAL Size: 6000b
 * EN Address: 0x80100AF0
 * EN Size: 6000b
 * JP Address: 0x800FD790
 * JP Size: 5984b
 */
void CMenuPcs::loadData()
{
	int i;
#ifdef VERSION_GCCJGC
	const int kHandleLine = 0x341;
	const int kWorldObjLine = 0x361;
	const int kBubbleLine = 0x374;
	const int kFrameDataLine = 0x378;
	const int kFrameInfoLine = 0x37E;
	const int kCharaModelLine = 0x384;
	const int kCharaSelectLine = 0x390;
	const int kWorldStateLine = 0x393;
	const int kCharaStateLine = 0x397;
	const int kWorldParamsLine = 0x39B;
	const int kEffectWorkLine = 0x39F;
	const int kCharaAnimLine = 0x3A7;
	const int kWindowInfoLine = 0x3AB;
	const int kMesMenuLine = 0x42F;
	const int kOptionTextureLine = 0x445;
#else
	const int kHandleLine = 0x1F4;
	const int kWorldObjLine = 0x214;
	const int kBubbleLine = 0x227;
	const int kFrameDataLine = 0x22B;
	const int kFrameInfoLine = 0x231;
	const int kCharaModelLine = 0x237;
	const int kCharaSelectLine = 0x243;
	const int kWorldStateLine = 0x246;
	const int kCharaStateLine = 0x24A;
	const int kWorldParamsLine = 0x24E;
	const int kEffectWorkLine = 0x252;
	const int kCharaAnimLine = 0x25A;
	const int kWindowInfoLine = 0x25E;
	const int kMesMenuLine = 0x2EA;
	const int kOptionTextureLine = 0x300;
#endif
#ifdef VERSION_GCCP01
	const int kInitialAnimWait = 250;
#else
	const int kInitialAnimWait = 300;
#endif
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	m_menuResultCode = 0;
	GbaQue.SetControllerMode(1);

	static char* tName[] = {
		"world",
		"world2",
		"cc_logo",
		0,
		0,
		0,
		0,
		0,
		0,
	};

	static CTmp tTmp[] = {
		{2, "world1"},
		{2, "world2"},
		{2, "world3"},
		{2, "world4"},
		{2, "world5"},
		{2, "world6"},
		{2, "world7"},
		{2, "world8"},
		{2, "world9"},
		{2, "world10"},
		{2, "world11"},
		{2, "world12"},
		{2, "world13"},
		{2, "world14"},
		{2, "world15"},
		{2, "world16"},
		{2, "world17"},
		{2, "world18"},
		{2, "world19"},
		{2, "world20"},
		{2, "world21"},
		{2, "world22"},
		{2, "world23"},
		{2, "world24"},
		{2, "world25"},
		{2, "world26"},
		{2, "world30"},
		{2, "world40"},
		{2, "world46"},
		{2, "world47"},
#ifndef VERSION_GCCJGC
		{2, "world50"},
#endif
		{2, "diary1"},
		{2, "diary2"},
		{2, "face"},
		{2, "odekake"},
		{3, "crystal"},
		{3, "world27"},
		{3, "world28"},
		{3, "world29"},
		{3, "world44"},
		{3, "world45"},
		{3, "world48"},
		{3, "world49"},
#ifndef VERSION_GCCJGC
		{3, "world51"},
#endif
		{4, "cc_logo01"},
		{4, "cc_logo02"},
#ifndef VERSION_GCCJGC
		{4, "cc_logo03"},
#endif
	};

	loadTexture(tName, 2, 3, tTmp, WM_TEXTURE_START, WM_TEXTURE_COUNT, 0);

	for (i = 0; i < 40; i++) {
		m_wm.m_handles[i] = 0;
	}

	static const short s_objtbl[] = {
		110, 52, 127, 67, 66, 73, 42, 37,
		85, 87, 86, 88, 89, 36, 90, 92,
		93, 100, 100, 100, 100, 67, 18, 19,
		20, 21, 22, 23, 24, 25, 26, 100,
		300, 500, 700, 200, 400, 600, 800, 0,
	};
	for (i = 0; i < 0x28; i++) {
		m_wm.m_handles[i] = new (MenuPcs.m_menuStage, "wm_menu.cpp", kHandleLine) CCharaPcs::CHandle;
		m_wm.m_handles[i]->Add();

		int charaKind;
		unsigned long charaNo;
		if (i < 0x20) {
			CharaPcs.m_charaAllocStage = 1;
			charaKind = 3;
			charaNo = s_objtbl[i];
		} else {
			CCaravanWork& caravan = Game.m_caravanWorkArr[i - 0x20];
			CharaPcs.m_charaAllocStage = 0;
			if (caravan.m_shopState != 0) {
				charaKind = 0;
				charaNo = GetModelNo(caravan.m_tribeId, caravan.m_appearanceVariant, caravan.m_genderFlag);
			} else {
				charaKind = 3;
				charaNo = s_objtbl[21];
			}
		}

		m_wm.m_handles[i]->LoadModel(charaKind, charaNo, 0, 0, -1, 0, 0);
		m_wm.m_handles[i]->m_flags |= 0x141;
	}
	CharaPcs.m_charaAllocStage = 0;
	m_wm.m_handles[6]->m_model->m_lightAlpha = FLOAT_803314B0;

	m_wm.m_worldObjData = new (MenuPcs.m_menuStage, "wm_menu.cpp", kWorldObjLine) WmWorldObjInfo[40];
	{
		const float bigF = FLOAT_80331598;
		const float zeroF = FLOAT_803313dc;
		for (i = 0; i < 0x28; i++) {
			m_wm.m_worldObjData[i].m_transform.Identity();
			m_wm.m_worldObjData[i].m_active = 0;
			m_wm.m_worldObjData[i].m_frameCounter = 0;
			m_wm.m_worldObjData[i].m_viewportX = 0;
			m_wm.m_worldObjData[i].m_viewportY = 0;
			m_wm.m_worldObjData[i].m_viewportWidth = 0x280;
			m_wm.m_worldObjData[i].m_viewportHeight = 0x1C0;
			m_wm.m_worldObjData[i].m_cameraPosition.x = zeroF;
			m_wm.m_worldObjData[i].m_cameraPosition.y = zeroF;
			m_wm.m_worldObjData[i].m_cameraPosition.z = bigF;
			m_wm.m_worldObjData[i].m_scissorX = 0;
			m_wm.m_worldObjData[i].m_scissorY = 0;
			m_wm.m_worldObjData[i].m_scissorWidth = 0x280;
			m_wm.m_worldObjData[i].m_scissorHeight = 0x1C0;
		}
	}

	m_wm.m_bubbleData =
	    new (MenuPcs.m_menuStage, "wm_menu.cpp", kBubbleLine) WmBubbleInfo;
	memset(m_wm.m_bubbleData, 0, sizeof(WmBubbleInfo));

	m_wm.m_frameData =
	    new (MenuPcs.m_menuStage, "wm_menu.cpp", kFrameDataLine) WmFrameData;
	memset(m_wm.m_frameData, 0, sizeof(WmFrameData));
	InitFrameInfo();

	m_wm.m_frameInfo =
	    new (MenuPcs.m_menuStage, "wm_menu.cpp", kFrameInfoLine) WmFrameInfo;
	memset(m_wm.m_frameInfo, 0, sizeof(WmFrameInfo));
	InitFrame0Info();

	m_wm.m_charaModelData =
	    new (MenuPcs.m_menuStage, "wm_menu.cpp", kCharaModelLine) WmCharaModelInfo[kWmMenuPlayerCount];
	{
		for (i = 0; i < kWmMenuPlayerCount; i++) {
			m_wm.m_charaModelData[i].m_unknown00 = 0;
			m_wm.m_charaModelData[i].m_unknown04 = 0;
			m_wm.m_charaModelData[i].m_modelNo = 0;
			m_wm.m_charaModelData[i].m_modelChanged = 0;
			m_wm.m_charaModelData[i].m_transform.Identity();
		}
	}

	InitCharaInfo();

	m_wm.m_charaSelectData =
	    new (MenuPcs.m_menuStage, "wm_menu.cpp", kCharaSelectLine) WmCharaSelectEntry[kWmCharaSelectCount];

	m_wmWorldState =
	    static_cast<WmWorldState*>(operator new(sizeof(WmWorldState), MenuPcs.m_menuStage, "wm_menu.cpp", kWorldStateLine));
	memset(m_wmWorldState, 0, sizeof(WmWorldState));

	m_wmCharaState =
	    new (MenuPcs.m_menuStage, "wm_menu.cpp", kCharaStateLine) McListInfo[kMcListCount];
	ClrMcList();

	m_wmWorldParams = new (MenuPcs.m_menuStage, "wm_menu.cpp", kWorldParamsLine) WmWorldParams;
	memset(m_wmWorldParams, 0, 0x10);

	m_effectWork = new (MenuPcs.m_menuStage, "wm_menu.cpp", kEffectWorkLine) EffectInfo[0x28];
	for (i = 0; i < 0x28; i++) {
		m_effectWork[i].m_effectNo = -1;
		m_effectWork[i].m_partNo = -1;
		m_effectWork[i].m_slotNo = -1;
	}

	m_wmCharaAnimState =
	    new (MenuPcs.m_menuStage, "wm_menu.cpp", kCharaAnimLine) WmCharaAnimState[8];
	memset(m_wmCharaAnimState, 0, sizeof(WmCharaAnimState) * 8);

	m_menuWindowInfo = new (MenuPcs.m_menuStage, "wm_menu.cpp", kWindowInfoLine) MenuWindowInfo;
	memset(m_menuWindowInfo, 0, sizeof(MenuWindowInfo));

	// Re-initialize the effect work entries.
	for (i = 0; i < 0x28; i++) {
		m_effectWork[i].m_partNo = -1;
		m_effectWork[i].m_slotNo = -1;
		m_effectWork[i].m_effectNo = -1;
	}

	m_textureLocIndex = 0;
	m_wmThpActive = 0;
	m_wmWorkBuffer = 0;
	InitCharaSelectInfo();

	SetManaWaterEffect();
	m_crystalPart = -1;
	m_crystalAttr = -1;
	SetCrystalCageAttr();

	// Crystal cage effect (effect slot 7, effect no 9).
	BindEffect(7, 9, -1);

	for (i = 0; i < 4; i++) {
		BindEffect(i + 8, i + 5, -1);
	}

	for (i = 0; i < 5; i++) {
		BindEffect(i + 0xC, i, -1);
	}

	for (i = 0; i < 4; i++) {
		const unsigned int partNo = BindEffect(i + 0x20, i + 0xA, -1);
		if (i == 0) {
			PartPcs.GetParLocIdx(partNo, s_RingOrgPos);
		}
	}

	s_MaxAnimWait = FLOAT_803317FC;
	for (i = 0; i < 8; i++) {
		int modelNo = (i + 1) * 100;
		CharaPcs.LoadAnim(0, modelNo, const_cast<char*>(s_wmCharaAnimStand), 1, 0, 0);
		CharaPcs.LoadAnim(0, modelNo, const_cast<char*>(s_wmCharaAnimWalk), 1, 0, 0);
		CharaPcs.LoadAnim(0, modelNo, const_cast<char*>(s_wmCharaAnimRun), 1, 0, 0);
		CharaPcs.LoadAnim(0, modelNo, const_cast<char*>(s_wmCharaAnimGlad), 3, 0, 0);
		CharaPcs.LoadAnim(0, modelNo, const_cast<char*>(s_wmCharaAnimSleep), 1, 0, 0);
	}

	{
		for (i = 0; i < 8; i++) {
			int slot = i + 0x20;
			if (m_wm.m_handles[slot]->m_charaKind != 3) {
				const unsigned int charaBase =
				    static_cast<unsigned int>(m_wm.m_handles[slot]->m_charaNo) /
				    100;
				const int modelNo = charaBase * 100;
				int anim = (charaBase - 1) * 6;
				m_wm.m_handles[slot]->LoadAnim(
				    const_cast<char*>(s_wmCharaAnimStand), anim++, 1, 0, modelNo, -1, 0);
				m_wm.m_handles[slot]->LoadAnim(
				    const_cast<char*>(s_wmCharaAnimWalk), anim++, 1, 0, modelNo, -1, 0);
				m_wm.m_handles[slot]->LoadAnim(
				    const_cast<char*>(s_wmCharaAnimRun), anim++, 1, 0, modelNo, -1, 0);
				m_wm.m_handles[slot]->LoadAnim(
				    const_cast<char*>(s_wmCharaAnimGlad), anim++, 3, 0, modelNo, -1, 0);
				m_wm.m_handles[slot]->LoadAnim(
				    const_cast<char*>(s_wmCharaAnimSleep), anim++, 1, 0, modelNo, -1, 0);
				m_wm.m_handles[slot]->LoadAnim(
				    const_cast<char*>(s_wmCharaAnimAngry), anim++, 1, 0, modelNo, -1, 0);
				m_wmCharaAnimState[i].m_animIndex = 0;
				m_wmCharaAnimState[i].m_nextAnimIndex = -1;
				m_wmCharaAnimState[i].m_timer = rand() % kInitialAnimWait;
				m_wm.m_handles[slot]->SetAnim(anim - 6, -1, -1, 0, 0);
				m_wmCharaAnimState[i].m_frame = m_wm.m_handles[slot]->m_model->GetNowFrame();
				m_wmCharaAnimState[i].m_endFrame = m_wm.m_handles[slot]->m_model->GetEndFrame();
				float maxWait = m_wm.m_handles[slot]->GetLoadAnimTotalFrame(anim - 1);
				if (s_MaxAnimWait < maxWait) {
					s_MaxAnimWait = maxWait;
				}
			}
		}
	}

	CCharaPcs::CHandle* const windowHandle = m_wm.m_handles[1];
	windowHandle->LoadAnim(const_cast<char*>(lbl_80331800), 0, 2, -1, -1, -1, 0);
	m_wm.m_handles[1]->LoadAnim(const_cast<char*>(lbl_80331808), 1, 0, -1, -1, -1, 0);
	m_wm.m_handles[1]->LoadAnim(const_cast<char*>(lbl_80331810), 2, 2, -1, -1, -1, 0);
	m_wm.m_handles[1]->LoadAnim(const_cast<char*>(lbl_80331818), 3, 2, -1, -1, -1, 0);
	m_wm.m_handles[1]->LoadAnim(const_cast<char*>(lbl_80331820), 4, 2, -1, -1, -1, 0);
	m_wm.m_handles[1]->LoadAnim(const_cast<char*>(lbl_80331828), 5, 2, -1, -1, -1, 0);
	m_wm.m_handles[1]->LoadAnim(const_cast<char*>(lbl_80331830), 6, 2, -1, -1, -1, 0);
	m_wm.m_handles[1]->LoadAnim(const_cast<char*>(lbl_80331838), 7, 0, -1, -1, -1, 0);
	m_wm.m_handles[1]->SetAnim(0, -1, -1, -1, 0);

	m_wmWorldState->m_menuMode = 0;
	for (i = 0; i < 4; i++) {
		m_wmWorldState->m_originalBackupParams[i] = Game.m_gameWork.m_wmBackupParams[i];
		m_wmWorldState->m_backupParams[i] = Game.m_gameWork.m_wmBackupParams[i];
	}

#ifdef VERSION_GCCJGC
	loadFont(0, "dvd/menu/subfont.fnt", 1, -1);
#else
	char fontPath[128];
	sprintf(fontPath, "dvd/%smenu/subfont.fnt", Game.GetLangString());
	loadFont(0, fontPath, 1, -1);
#endif

	bytes[0xD] = 0;
	bytes[0x10] = 0;
	bytes[0x12] = 0;
	bytes[0x13] = 0;
	m_wmWorldState->m_changeRequest = 0;
	m_wmWorldState->m_nextMenuMode = 0;
	m_wmWorldState->m_delay = 0;
	lbl_8032EE1C = 1;
	lbl_8032E8AC = 1;

	for (i = 4; i < 6; i++) {
		m_battleMesMenus[i] = new (MenuPcs.m_menuStage, "wm_menu.cpp", kMesMenuLine) CMesMenu;
		m_battleMesMenus[i]->SetIndex(i);
		m_battleMesMenus[i]->Create();
	}

	char optionPath[256];
#ifdef VERSION_GCCJGC
	sprintf(optionPath, "dvd/menu/option.tex");
#else
	sprintf(optionPath, "dvd/%smenu/option.tex", Game.GetLangString());
#endif
	CFile::CHandle* const fileHandle = File.Open(optionPath, 0, CFile::PRI_LOW);
	if (fileHandle != 0) {
		File.Read(fileHandle);
		File.SyncCompleted(fileHandle);
		CTextureSet* texSet =
		    new (MenuPcs.m_menuStage, "wm_menu.cpp", kOptionTextureLine) CTextureSet;
		m_wmOptionTextureSet = texSet;
		m_wmOptionTextureSet->Create(File.m_readBuffer, m_menuStage, 0, 0, 0, 0);
		File.Close(fileHandle);
	}

	for (unsigned int i = 0;
	     i < static_cast<unsigned int>(m_wmOptionTextureSet->m_textureArray.GetSize()); i++) {
		m_wmOptionTextures[i] = m_wmOptionTextureSet->GetTexture(i);
	}

	GetOptionData();
	WMSubMenuInit();
	g_pGoOutMenu = &g_GoOutMenu;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 352b
 * EN Address: 0x80105EAC
 * EN Size: 456b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::InitFrameInfo()
{
	int frameBounds[5][4] = {
		{0, 0, 128, 160},
		{128, 0, 120, 64},
		{608, 248, 32, 64},
		{568, 312, 64, 56},
		{416, 368, 200, 80},
	};
	float frameUV[5][2] = {
		{0.0f, 0.0f},
		{128.0f, 0.0f},
		{256.0f, 0.0f},
		{216.0f, 64.0f},
		{64.0f, 120.0f},
	};

	for (int i = 0; i < 5; i++) {
		m_wm.m_frameData->m_frameSprites[i].m_x = static_cast<short>(frameBounds[i][0]);
		m_wm.m_frameData->m_frameSprites[i].m_y = static_cast<short>(frameBounds[i][1]);
		m_wm.m_frameData->m_frameSprites[i].m_width = static_cast<short>(frameBounds[i][2]);
		m_wm.m_frameData->m_frameSprites[i].m_height = static_cast<short>(frameBounds[i][3]);
		m_wm.m_frameData->m_frameSprites[i].m_u = frameUV[i][0];
		m_wm.m_frameData->m_frameSprites[i].m_v = frameUV[i][1];
		m_wm.m_frameData->m_frameSprites[i].m_alpha = 1.0f;
		m_wm.m_frameData->m_frameSprites[i].m_scale = 1.0f;
		m_wm.m_frameData->m_frameSprites[i].m_flags = 0;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80101658
 * PAL Size: 212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::InitFrame0Info()
{
	m_wm.m_frameInfo->m_sprites[0].m_x = 0x10;
	float one = FLOAT_803313e8;
	float zero = FLOAT_803313dc;
	m_wm.m_frameInfo->m_sprites[0].m_y = 0x10;
	m_wm.m_frameInfo->m_sprites[0].m_width = 0xE8;
	m_wm.m_frameInfo->m_sprites[0].m_height = 0x168;
	m_wm.m_frameInfo->m_sprites[0].m_u = zero;
	m_wm.m_frameInfo->m_sprites[0].m_v = zero;
	m_wm.m_frameInfo->m_sprites[0].m_alpha = one;
	m_wm.m_frameInfo->m_sprites[0].m_scale = one;
	m_wm.m_frameInfo->m_sprites[0].m_flags = 0;

	WmFrameInfo* frame = m_wm.m_frameInfo;
	frame->m_sprites[1] = frame->m_sprites[0];

	frame = m_wm.m_frameInfo;
	frame->m_sprites[1].m_x = 0x280 - (frame->m_sprites[0].m_width + frame->m_sprites[0].m_x);
	m_wm.m_frameInfo->m_sprites[1].m_flags = 8;
}

/*
 * --INFO--
 * PAL Address: 0x80101444
 * PAL Size: 532b
 * EN Address: 0x801061A0
 * EN Size: 388b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::InitCharaInfo()
{
	float z;
	float zero;
	int slot;
	int baseX;
	int baseSlot;
	int baseY;
	int row;
	int col;
	int y;

	zero = 0.0f;
	z = 50.0f;
	row = 0;
	baseSlot = 0x20;
	baseY = 0x66;
	while (row < 2) {
		slot = baseSlot;
		col = 0;
		baseX = 0x68;
		for (; col < 4; col++) {
			y = baseY;
			if (row != 0) {
				y = baseY + 8;
			}

			m_wm.m_worldObjData[slot].m_viewportX = static_cast<short>(baseX - 0xA0);
			m_wm.m_worldObjData[slot].m_viewportY = static_cast<short>(y - 0x70);
			m_wm.m_worldObjData[slot].m_viewportWidth = 0x140;
			m_wm.m_worldObjData[slot].m_viewportHeight = 0xE0;
			m_wm.m_worldObjData[slot].m_cameraPosition.x = zero;
			m_wm.m_worldObjData[slot].m_cameraPosition.y = zero;
			m_wm.m_worldObjData[slot].m_cameraPosition.z = z;

			slot += 1;
			baseX = baseX + 0x90;
		}
		row++;
		baseSlot += 4;
		baseY = baseY + 0xB8;
	}

	for (int i = 0; i < kWmMenuPlayerCount; i++) {
		CCaravanWork& caravan = Game.m_caravanWorkArr[i];
		WmCharaModelInfo* entry = &m_wm.m_charaModelData[i];
		if (caravan.m_shopState != 0) {
			entry->m_modelNo = GetModelNo(caravan.m_tribeId, caravan.m_appearanceVariant,
			                            caravan.m_genderFlag);
		} else {
			entry->m_modelNo = -1;
		}
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 576b
 * EN Address: 0x80106324
 * EN Size: 64b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::InitCharaSelectInfo()
{
	memset(m_wm.m_charaSelectData, 0, kWmCharaSelectBytes);
	InitCSelCurPos();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 560b
 * EN Address: 0x80106364
 * EN Size: 428b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::InitCSelCurPos()
{
	signed char usedMask = 0;
	for (int i = 0; i < kWmMenuControllerCount; i++) {
		m_wm.m_charaSelectData[i].m_cmakeReady = 0;
		m_wm.m_charaSelectData[i].m_cmakePending = 0;
		m_wm.m_charaSelectData[i].m_confirmed = 0;
		int slot = m_wmWorldState->m_backupParams[i];
		if (slot < 0) {
			m_wm.m_charaSelectData[i].m_currentSlot = -1;
		} else {
			m_wm.m_charaSelectData[i].m_currentSlot = static_cast<short>(slot);
			usedMask |= 1 << slot;
		}
	}

	for (int i = 0; i < kWmMenuControllerCount; i++) {
		if (m_wm.m_charaSelectData[i].m_currentSlot < 0) {
			int slot;
			for (slot = 0; slot < kWmMenuPlayerCount; slot++) {
				if ((usedMask & (1 << slot)) == 0) {
					break;
				}
			}
			m_wm.m_charaSelectData[i].m_currentSlot = static_cast<short>(slot);
			usedMask |= 1 << slot;
		}
		m_wm.m_charaSelectData[i].m_displaySlot = m_wm.m_charaSelectData[i].m_currentSlot;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80101150
 * PAL Size: 756b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::destroyWorld()
{
	for (int i = 4; i < 6; i++) {
		CRef* const obj = m_battleMesMenus[i];
		if (obj != 0) {
			if (obj->DecRef() == 0) {
				delete obj;
			}
			m_battleMesMenus[i] = 0;
		}
	}

	{
		CRef* const obj = m_fonts[1];
		if (obj != 0) {
			if (obj->DecRef() == 0) {
				delete obj;
			}
			m_fonts[1] = 0;
		}
	}

	if (m_wm.m_frameData != 0) {
		delete m_wm.m_frameData;
		m_wm.m_frameData = 0;
	}

	freeTexture(2, 3, WM_TEXTURE_START, WM_TEXTURE_COUNT);

	if (m_wmOptionTextureSet != 0) {
		delete m_wmOptionTextureSet;
		m_wmOptionTextureSet = 0;
	}

	if (m_wm.m_worldObjData != 0) {
		delete[] m_wm.m_worldObjData;
		m_wm.m_worldObjData = 0;
	}
	if (m_wm.m_bubbleData != 0) {
		delete m_wm.m_bubbleData;
		m_wm.m_bubbleData = 0;
	}
	if (m_wm.m_frameData != 0) {
		delete m_wm.m_frameData;
		m_wm.m_frameData = 0;
	}
	if (m_wm.m_frameInfo != 0) {
		delete m_wm.m_frameInfo;
		m_wm.m_frameInfo = 0;
	}
	if (m_wm.m_charaModelData != 0) {
		delete[] m_wm.m_charaModelData;
		m_wm.m_charaModelData = 0;
	}
	if (m_wm.m_charaSelectData != 0) {
		delete[] m_wm.m_charaSelectData;
		m_wm.m_charaSelectData = 0;
	}
	if (m_wmCharaAnimState != 0) {
		delete[] m_wmCharaAnimState;
		m_wmCharaAnimState = 0;
	}
	if (m_wmWorldState != 0) {
		delete m_wmWorldState;
		m_wmWorldState = 0;
	}
	if (m_wmCharaState != 0) {
		delete[] m_wmCharaState;
		m_wmCharaState = 0;
	}
	if (m_wmWorldParams != 0) {
		delete m_wmWorldParams;
		m_wmWorldParams = 0;
	}
	if (m_effectWork != 0) {
		delete[] m_effectWork;
		m_effectWork = 0;
	}
	if (m_menuWindowInfo != 0) {
		delete m_menuWindowInfo;
		m_menuWindowInfo = 0;
	}

	if (static_cast<signed char>(m_wmThpActive) != 0) {
		THPSimpleAudioStop();
		THPSimpleLoadStop();
		THPSimpleClose();
		THPSimpleQuit();
		if (m_wmWorkBuffer != 0) {
			if (m_wmWorkBuffer != 0) {
				Memory.Free(m_wmWorkBuffer);
				m_wmWorkBuffer = 0;
			}
			m_wmWorkBuffer = 0;
		}
		m_wmThpActive = 0;
	}

	PartMng.pppDestroyAll();
	MemoryCardMan.McEnd();

	GXSetCopyClear(Graphic.GetCopyClearColor(), 0x00FFFFFF);
	GbaQue.SetControllerMode(0);
}

/*
 * --INFO--
 * PAL Address: 0x80100B00
 * PAL Size: 1616b
 * EN Address: 0x800FFF4C
 * EN Size: 1480b
 * JP Address: 0x800FCC34
 * JP Size: 1496b
 */
void CMenuPcs::CalcDiaryMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

#ifdef VERSION_GCCP01
	static bool s_wmMenuLastMountState = false;

	const bool mounted = MemoryCardMan.m_currentSlot != -1;
	if (mounted != s_wmMenuLastMountState) {
		if (static_cast<unsigned int>(System.m_execParam) >= 3) {
			System.Printf("mount = %s\n", mounted ? "TRUE" : "FALSE");
		}
		s_wmMenuLastMountState = mounted;
	}

#endif

	WMChgMenu();
	if (static_cast<char>(bytes[0xD]) == 0) {
		int menuIndex = 4;
		unsigned char* menuPtr = bytes + 0x10;
		do {
			CMenu* const menu = *reinterpret_cast<CMenu**>(menuPtr + 0x10C);
			menu->Calc();
			menuIndex++;
			menuPtr += 4;
		} while (menuIndex < 6);
		return;
	}

	const int menuMode = m_wmWorldState->m_menuMode;
	switch (menuMode) {
	case 0:
		CalcMainMenu();
		break;
	case 1:
		calcWorld();
		break;
	case 2:
		CalcMCardMenu();
		break;
	case 3:
		if (m_singleCmakeMode == 0) {
			CalcCMakeMenu();
		} else {
			CalcSingCMake();
		}
		break;
	case 4:
		CalcMoveMenu();
		break;
	case 5:
		CalcLoadMenu();
		break;
	case 6:
		CalcTitleMenu();
		break;
	case 7:
		CalcOptionMenu();
		break;
	case 8:
		CalcGoOutMenu();
		break;
	default:
		if (static_cast<unsigned int>(System.m_execParam) >= 1) {
#ifdef VERSION_GCCJGC
			System.Printf("%s(%d): Error:WM menu no error(%d)\n", "wm_menu.cpp", 0x5F9, menuMode);
#elif defined(VERSION_GCCE01)
			System.Printf("%s(%d): Error:WM menu no error(%d)\n", "wm_menu.cpp", 0x4B8, menuMode);
#else
			System.Printf("%s(%d): Error:WM menu no error(%d)\n", "wm_menu.cpp", 0x4c0, menuMode);
#endif
		}
		break;
	}

	int menuIndex = 4;
	unsigned char* menuPtr = bytes + 0x10;
	do {
		CMenu* const menu = *reinterpret_cast<CMenu**>(menuPtr + 0x10C);
		menu->Calc();
		menuIndex++;
		menuPtr += 4;
	} while (menuIndex < 6);
}

/*
 * --INFO--
 * PAL Address: 0x801005d8
 * PAL Size: 1320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::calcWorld()
{
	m_wmWorldParams->m_prevAnim = m_wmWorldParams->m_anim;

	if (m_wmWorldState->m_worldReady == 0) {
		Sound.PlaySe(0x138B, 0x40, 0x7F, 0);
		m_wm.m_handles[1]->SetAnim(0, -1, -1, -1, 0);
		m_wmWorldParams->m_anim = 0;
		m_wmWorldState->m_worldReady = 1;
		m_wmWorldState->m_mainState = 1;
	}

	const int animState = m_wmWorldState->m_mainState;
	const float animTime = m_wm.m_handles[1]->m_model->GetNowFrame();
	float animEnd = m_wm.m_handles[1]->m_model->GetEndFrame();

	if (animState == 1) {
		if (animTime < animEnd) {
			m_wm.m_handles[1]->m_model->AddFrame(FLOAT_80331698);
			m_wmWorldState->m_frameCounter = 0;
		} else {
			if (m_wmWorldState->m_frameCounter >= 10) {
				m_wm.m_handles[1]->SetAnim(1, -1, -1, -1, 0);
				m_wmWorldParams->m_anim = 1;
				CallWorldParam(2, 0, 0);
				m_wmWorldState->m_mainState = 2;
				m_wmWorldState->m_frameCounter = 0;
			}
		}
	} else if (animState == 2) {
		int nextAnim = m_wmNextAnim;

		if (nextAnim != 0) {
			if (nextAnim == 1) {
				Sound.PlaySe(0x138C, 0x40, 0x7F, 0);
				nextAnim = 2;
			} else if (nextAnim == 2) {
				Sound.PlaySe(0x138C, 0x40, 0x7F, 0);
				nextAnim = 3;
			} else if (nextAnim == 3) {
				Sound.PlaySe(0x138C, 0x40, 0x7F, 0);
				nextAnim = 4;
			} else if (nextAnim == 4) {
				Sound.PlaySe(0x138C, 0x40, 0x7F, 0);
				nextAnim = 5;
			} else if (nextAnim == 5) {
				Sound.PlaySe(0x138D, 0x40, 0x7F, 0);
				nextAnim = 6;
				m_wmWorldState->m_mainState = 3;
				m_wmWorldState->m_frameCounter = 0;
			}

			if (nextAnim != m_wmWorldParams->m_anim) {
				m_wm.m_handles[1]->SetAnim(nextAnim, -1, -1, -1, 0);
				m_wmWorldParams->m_anim = nextAnim;

				if (nextAnim == 0) {
					animEnd = m_wm.m_handles[1]->m_model->GetEndFrame();
					m_wm.m_handles[1]->m_model->SetFrame(animEnd);
				}
			}
			m_wmNextAnim = 0;
		} else {
			if (animTime < animEnd) {
				m_wm.m_handles[1]->m_model->AddFrame(FLOAT_80331698);
			} else {
				m_wm.m_handles[1]->SetAnim(1, -1, -1, -1, 0);
				m_wmWorldParams->m_anim = 1;
			}
		}
	} else if (animState == 3 && m_wmWorldState->m_frameCounter >= 10) {
		if (animTime < animEnd) {
			m_wm.m_handles[1]->m_model->AddFrame(FLOAT_80331698);
		} else {
			m_wm.m_handles[1]->SetAnim(0, -1, -1, -1, 0);
			m_wmWorldParams->m_anim = 0;
			m_wmWorldState->m_delay = 10;
			m_wmWorldState->m_nextMenuMode = -1;
			m_wmWorldState->m_mainState = 4;
			Sound.PlaySe(0x32, 0x40, 0x7F, 0);
		}
	} else if (animState == 4) {
		if (m_wmWorldState->m_delay != 0) {
			m_wmWorldState->m_delay--;
		} else {
			m_wmWorldState->m_changeRequest = m_wmWorldState->m_nextMenuMode;
			m_wmWorldState->m_nextMenuMode = 0;
		}
	}

	WmWorldObjInfo* const worldObj = m_wm.m_worldObjData;
	worldObj[1].m_viewportX = 0;
	const float kZero = FLOAT_803313dc;
	worldObj[1].m_viewportY = 0;
	float cameraZ = FLOAT_80331598;
	worldObj[1].m_viewportWidth = 0x280;
	const float kScale = FLOAT_803315d4;
	worldObj[1].m_viewportHeight = 0x1C0;
	const float kPosY = FLOAT_803317e0;
	worldObj[1].m_cameraPosition.x = kZero;
	const float kPosZ = FLOAT_803317e4;
	worldObj[1].m_cameraPosition.y = kZero;
	const float kRotX = FLOAT_803317e8;
	worldObj[1].m_cameraPosition.z = cameraZ;
	float degToRad = FLOAT_803314bc;
	worldObj[1].m_active = 1;
	worldObj[1].m_transform.m_scale.x = kScale;
	worldObj[1].m_transform.m_scale.y = kScale;
	worldObj[1].m_transform.m_scale.z = kScale;
	worldObj[1].m_transform.m_position.x = kZero;
	worldObj[1].m_transform.m_position.y = kPosY;
	worldObj[1].m_transform.m_position.z = kPosZ;
	worldObj[1].m_transform.m_rotation.x = kRotX;
	worldObj[1].m_transform.m_rotation.y = kZero;
	worldObj[1].m_transform.m_rotation.z = kZero;

	Mtx matrix;
	PSMTXRotRad(matrix, 'x', degToRad * worldObj[1].m_transform.m_rotation.x);
	matrix[0][3] = worldObj[1].m_transform.m_position.x;
	matrix[1][3] = worldObj[1].m_transform.m_position.y;
	matrix[2][3] = worldObj[1].m_transform.m_position.z;
	PSMTXScaleApply(matrix, matrix, worldObj[1].m_transform.m_scale.x, worldObj[1].m_transform.m_scale.y,
	                worldObj[1].m_transform.m_scale.z);

	m_wm.m_handles[1]->m_model->SetMatrix(matrix);
	m_wm.m_handles[1]->m_model->CalcMatrix();
	m_wm.m_handles[1]->m_model->CalcSkin();

	const int updatedAnimState = m_wmWorldState->m_mainState;

	if (updatedAnimState == 1 && animTime >= animEnd) {
		if (m_wmWorldState->m_frameCounter < 10) {
			m_wmWorldState->m_frameCounter++;
		}
	} else if (updatedAnimState == 3 && m_wmWorldState->m_frameCounter < 10) {
		m_wmWorldState->m_frameCounter++;
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 504b
 * EN Address: 0x80106AB8
 * EN Size: 168b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CalcMainMenu()
{
	if (m_wmWorldState->m_mainState <= 4) {
		const short state = m_wmWorldState->m_mainState;
		int frameStep;
		if (state == 0) {
			frameStep = m_wmWorldState->m_frameCounter - 10;
		} else if (state > 0 && state < 4) {
			frameStep = 0;
		} else {
			frameStep = -m_wmWorldState->m_frameCounter;
		}
		CalcWMFrame0(frameStep);
		CalcMainMenuSub();
	}
}

/*
 * --INFO--
 * PAL Address: 0x800FEC40
 * PAL Size: 6552b
 * EN Address: 0x800FE13C
 * EN Size: 6376b
 * JP Address: 0x800FAE54
 * JP Size: 6304b
 */
void CMenuPcs::CalcMCardMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	int playOpenSe = false;
	unsigned int buttonsDown = Pad.GetButtonDown(0);
	unsigned short buttonsRepeat = GetButtonRepeat(0);

	if ((signed char)m_wmWorldState->m_worldReady == 0) {
		m_mcCtrl.Init();
		if (gWmMenuCursorX[0] >= 0 && gWmMenuCursorX[0] < 2) {
			m_mcCtrl.SetSlot(gWmMenuCursorX[0]);
		} else {
			m_mcCtrl.SetSlot(0);
		}
		if (gWmMenuCursorX[1] >= 0 && gWmMenuCursorX[1] < 4) {
			m_mcCtrl.SetDno(gWmMenuCursorX[1]);
		} else {
			m_mcCtrl.SetDno(0);
		}
		ClrMcList();
		for (int i = 0; i < kWmMenuControllerCount; i++) {
			Game.m_gameWork.m_wmBackupParams[i] = m_wmWorldState->m_originalBackupParams[i];
		}
		m_wmWorldState->m_flag0A = 0;
		m_wmWorldState->m_worldReady = 1;
	}

	int subState;
	short mainState = m_wmWorldState->m_mainState;
	unsigned int frameOffset;
	if (mainState == 0) {
		frameOffset = static_cast<int>(m_wmWorldState->m_frameCounter) - 10;
	} else if (mainState > 0 && mainState < 4) {
		frameOffset = 0;
	} else {
		frameOffset = -static_cast<int>(m_wmWorldState->m_frameCounter);
	}

	CalcWMFrame0(static_cast<int>(frameOffset));

	if (m_wmWorldState->m_mainState != 2) {
		return;
	}

	subState = m_wmWorldState->m_subState;
	switch (subState) {
	case 0:
	case 2:
		if ((signed char)m_wmWorldState->m_flag09 == 0) {
			m_wmWorldState->m_cardChannel = static_cast<short>(m_mcCtrl.GetSlot());
			short windowWidth;
			short windowHeight;
			GetWinSize(0, &windowWidth, &windowHeight, 0);
			SetMcWinInfo(windowWidth, windowHeight);
			m_menuWindowInfo->state = 0;
			ClrMcList();
			m_wmWorldState->m_flag09 = 1;
			m_wmWorldState->m_flag0A = 0;
		}
		if (m_menuWindowInfo->state == 1) {
			if (m_wmWorldState->m_counter1A == 0) {
				if ((buttonsRepeat & 3) != 0) {
					m_wmWorldState->m_cardChannel ^= 1;
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				} else {
					if ((buttonsDown & 0x100) != 0) {
						m_wmWorldState->m_state0E = 1;
						m_mcCtrl.SetSlot(m_wmWorldState->m_cardChannel);
						if (m_wmWorldState->m_cardChannel == static_cast<signed char>(gWmMenuCursorX[0])) {
							m_mcCtrl.SetDno((int)gWmMenuCursorX[1]);
						}
						m_wmWorldState->m_counter1A = 10;
						Sound.PlaySe(2, 0x40, 0x7F, 0);
					} else {
						if ((buttonsDown & 0x200) != 0) {
							m_wmWorldState->m_state0E = -1;
							m_wmWorldState->m_counter1A = 1;
							Sound.PlaySe(3, 0x40, 0x7F, 0);
						}
					}
				}
			}
		}
		if (m_menuWindowInfo->state == 1) {
			if (m_wmWorldState->m_counter1A != 0) {
				m_wmWorldState->m_counter1A--;
				if (m_wmWorldState->m_counter1A == 0) {
					m_menuWindowInfo->state = 2;
				}
			}
		}
		break;
	case 3:
		m_wmWorldState->m_mcResult = static_cast<short>(MemoryCardMan.McChkConnect(m_mcCtrl.GetSlot()));
		break;
	case 5:
	case 6:
	case 7:
	case 9:
	case 10:
	case 0xE:
	case 0xF:
	case 0x14:
	case 0x15:
	case 0x1B:
	case 0x1C: {
		if ((signed char)m_wmWorldState->m_flag09 == 0) {
			playOpenSe = true;
			int winType;
			int messType = 0;
			if (subState == 5) { winType = 1; }
			else if (subState == 6) { winType = 2; }
			else if (subState == 7) { winType = 3; }
			else if (subState == 9) { winType = 10; }
			else if (subState == 10) { winType = 0xB; }
			else if (subState == 0xE) { winType = 0xC; }
			else if (subState == 0xF) { winType = 0xD; }
			else if (subState == 0x1C) { messType = 1; winType = 0x1B; }
			else if (subState == 0x1B) { messType = 1; winType = 0x1C; }
			else if (subState == 0x15) { playOpenSe = false; winType = 0xE; }
			else { winType = 0xF; }
			short windowWidth;
			short windowHeight;
			GetWinSize(winType, &windowWidth, &windowHeight, messType);
			SetMcWinInfo(windowWidth, windowHeight);
			m_menuWindowInfo->state = 0;
			m_wmWorldState->m_flag09 = 1;
			m_wmWorldState->m_counter1A = 0;
			if (playOpenSe) {
				Sound.PlaySe(4, 0x40, 0x7F, 0);
			}
		}
		if (m_menuWindowInfo->state == 1
		    && m_wmWorldState->m_counter1A == 0) {
			short curSub = m_wmWorldState->m_subState;
			if (curSub == 0xE || curSub == 0x15) {
				m_wmWorldState->m_mcResult = (short)MemoryCardMan.McChkConnect(m_mcCtrl.GetSlot());
				if (m_wmWorldState->m_mcResult < 0) goto checkMcResult;
			} else if (curSub == 5) {
				m_wmWorldState->m_mcResult = (short)MemoryCardMan.McChkConnect(m_mcCtrl.GetSlot());
			checkMcResult:
				curSub = m_wmWorldState->m_subState;
				short expectedResult;
				if (curSub == 5) { expectedResult = -1; }
				else if (curSub == 6) { expectedResult = -3; }
				else if (curSub == 7) { expectedResult = -4; }
				else { expectedResult = 0; }
				if (curSub != 7) {
					if (expectedResult != m_wmWorldState->m_mcResult && m_wmWorldState->m_mcResult != 1) {
						m_wmWorldState->m_state0E = -1;
						m_wmWorldState->m_counter1A = 1;
						break;
					}
				} else {
					short chk = m_wmWorldState->m_mcResult;
					if (chk != 0 && chk != expectedResult && chk != 1) {
						m_wmWorldState->m_state0E = -1;
						m_wmWorldState->m_counter1A = 1;
						break;
					}
				}
			}
			if ((buttonsDown & 0x300) != 0) {
				m_wmWorldState->m_state0E = 1;
				m_wmWorldState->m_counter1A = 10;
				if (m_wmWorldState->m_subState == 0x15) {
					Sound.PlaySe(2, 0x40, 0x7F, 0);
				} else {
					Sound.PlaySe(3, 0x40, 0x7F, 0);
				}
			}
		}
		if (m_menuWindowInfo->state == 1) {
			if (m_wmWorldState->m_counter1A != 0) {
				m_wmWorldState->m_counter1A--;
				if (m_wmWorldState->m_counter1A == 0) {
					m_menuWindowInfo->state = 2;
				}
			}
		}
		break;
	}
	case 4:
		if ((signed char)m_wmWorldState->m_flag09 == 0) {
			short windowWidth;
			short windowHeight;
			GetWinSize(6, &windowWidth, &windowHeight, 0);
			SetMcWinInfo(windowWidth, windowHeight);
			m_menuWindowInfo->state = 0;
			m_mcCtrl.Init();
			m_wmWorldState->m_flag09 = 1;
		} else if (m_menuWindowInfo->state == 1
		           && m_wmWorldState->m_counter1A == 0) {
			short chkResult = (short)GetMcCtrl()->ChkEmpty(0);
			int chkResultInt = chkResult;
			m_wmWorldState->m_mcResult = chkResultInt;
			if (m_wmWorldState->m_mcResult < 0) {
#if defined(VERSION_GCCP01)
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = 0xFF;
#endif
				m_wmWorldState->m_state0E = -1;
				m_wmWorldState->m_counter1A = 10;
			}
		}
		if (m_menuWindowInfo->state == 1) {
			if (m_wmWorldState->m_counter1A != 0) {
				m_wmWorldState->m_counter1A--;
				if (m_wmWorldState->m_counter1A == 0) {
					m_menuWindowInfo->state = 2;
				}
			}
		}
		break;
	case 8:
	case 0xB:
	case 0x12:
	case 0x19: {
		if ((signed char)m_wmWorldState->m_flag09 == 0) {
			int messType = 0;
			int winType;
			if (subState == 8) {
				m_wmWorldState->m_cardChannel = 0;
				winType = 4;
			} else if (subState == 0xB) {
				winType = 5;
				m_wmWorldState->m_cardChannel = 1;
			} else if (subState == 0x19) {
				winType = 0x19;
				messType = 1;
				m_wmWorldState->m_cardChannel = 1;
			} else {
				winType = 0x12;
				m_wmWorldState->m_cardChannel = 1;
			}
			short windowWidth;
			short windowHeight;
			GetWinSize(winType, &windowWidth, &windowHeight, messType);
			SetMcWinInfo(windowWidth, windowHeight);
			m_menuWindowInfo->state = 0;
			m_wmWorldState->m_flag09 = 1;
		}
		if (m_menuWindowInfo->state == 1) {
			if (m_wmWorldState->m_counter1A == 0) {
				if (m_wmWorldState->m_subState == 0x19) {
					m_wmWorldState->m_state0E = 1;
					m_wmWorldState->m_counter1A = 0x5A;
					break;
				}
				int chkRes = MemoryCardMan.McChkConnect(m_mcCtrl.GetSlot());
				m_wmWorldState->m_mcResult = (short)chkRes;
				if (m_wmWorldState->m_mcResult != 0) {
					m_wmWorldState->m_state0E = -1;
					m_wmWorldState->m_counter1A = 10;
				} else {
					if ((buttonsRepeat & 3) != 0) {
						m_wmWorldState->m_cardChannel ^= 1;
						Sound.PlaySe(1, 0x40, 0x7F, 0);
					} else {
						if ((buttonsDown & 0x100) != 0) {
							if (m_wmWorldState->m_cardChannel == 0) {
								m_wmWorldState->m_state0E = 1;
							} else {
								m_wmWorldState->m_state0E = -1;
							}
							m_wmWorldState->m_counter1A = 10;
							Sound.PlaySe(2, 0x40, 0x7F, 0);
						} else {
							if ((buttonsDown & 0x200) != 0) {
								m_wmWorldState->m_cardChannel = 1;
								m_wmWorldState->m_state0E = -1;
								m_wmWorldState->m_counter1A = 10;
								Sound.PlaySe(3, 0x40, 0x7F, 0);
							}
						}
					}
				}
			}
		}
		if (m_menuWindowInfo->state == 1
		    && m_wmWorldState->m_counter1A != 0) {
			if (m_wmWorldState->m_subState == 0x19) {
				m_wmWorldState->m_mcResult = (short)MemoryCardMan.McChkConnect(m_mcCtrl.GetSlot());
			}
			m_wmWorldState->m_counter1A--;
			if (m_wmWorldState->m_counter1A == 0) {
				m_menuWindowInfo->state = 2;
			}
		}
		break;
	}
	case 0xD:
	case 0x13:
	case 0x1A: {
		if ((signed char)m_wmWorldState->m_flag09 == 0) {
			int messType;
			messType = 0;
			int winType;
			if (subState == 0xD) { winType = 7; }
			else if (subState == 0x1A) { winType = 0x1A; messType = 1; }
			else { winType = 8; }
			short windowWidth;
			short windowHeight;
			GetWinSize(winType, &windowWidth, &windowHeight, messType);
			SetMcWinInfo(windowWidth, windowHeight);
			m_menuWindowInfo->state = 0;
			m_mcCtrl.Init();
			if (m_wmWorldState->m_menuMode == 8
			    && m_cmakeWork != 0) {
				m_mcCtrl.SetDataBuff(reinterpret_cast<char*>(m_cmakeWork));
			} else {
				m_mcCtrl.SetDataBuff(0);
			}
			m_wmWorldState->m_flag09 = 1;
		} else if (m_menuWindowInfo->state == 1
		           && m_wmWorldState->m_counter1A == 0) {
			if (subState == 0xD) {
#if defined(VERSION_GCCP01)
				GetMcCtrl()->Format(1);
				m_wmWorldState->m_mcResult = (short)m_mcCtrl.m_lastResult;
#else
				m_wmWorldState->m_mcResult = (short)GetMcCtrl()->Format(1);
#endif
#if defined(VERSION_GCCP01)
				if (m_wmWorldState->m_mcResult < 0) {
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
				}
#endif
			} else if (subState == 0x1A) {
				m_wmWorldState->m_mcResult = (short)GetMcCtrl()->EraseDat();
#if defined(VERSION_GCCP01)
				if (m_wmWorldState->m_mcResult < 0) {
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
				}
#endif
			} else {
				m_wmWorldState->m_mcResult = (short)GetMcCtrl()->SaveDat();
#if defined(VERSION_GCCP01)
				if (m_wmWorldState->m_mcResult < 0) {
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
				}
#endif
			}
			if (m_wmWorldState->m_mcResult == 0) break;
			if (m_wmWorldState->m_subState == 0x13) {
				if (m_wmWorldState->m_menuMode != 8) {
					s_Serial = m_mcCtrl.GetSerial();
					gWmMenuCursorX[0] = (unsigned char)m_mcCtrl.GetSlot();
					gWmMenuCursorX[1] = (unsigned char)m_mcCtrl.GetDno();
				}
				m_wmCharaState[m_mcCtrl.GetDno()].m_scriptSysVal0 = Game.m_gameWork.m_scriptSysVal0;
			}
			m_wmWorldState->m_state0E = 1;
			m_wmWorldState->m_counter1A = 10;
		}
		if (m_menuWindowInfo->state == 1) {
			if (m_wmWorldState->m_counter1A != 0) {
				m_wmWorldState->m_counter1A--;
				if (m_wmWorldState->m_counter1A == 0) {
					m_menuWindowInfo->state = 2;
				}
			}
		}
		break;
	}
	case 0xC: {
		if ((signed char)m_wmWorldState->m_flag09 == 0) {
			m_wmWorldState->m_flag09 = 1;
			ClrMcList();
			m_mcCtrl.Init();
		}
		if (m_menuWindowInfo->state == 1
		    && m_wmWorldState->m_counter1A == 0) {
			short listRes = (short)GetMcCtrl()->LoadMcList();
			int listResInt = listRes;
			m_wmWorldState->m_mcResult = listResInt;
			if (m_wmWorldState->m_mcResult == 0) {
#if defined(VERSION_GCCP01)
				if (m_wmWorldState->m_mcResult < 0) {
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
				}
#endif
				break;
			}
			if (m_wmWorldState->m_menuMode == 8) {
				const int dataCount = ChkMcDataCnt();
				if (dataCount == 0) {
					m_wmWorldState->m_mcResult = (short)0xFC19;
				}
			}
			if (gWmMenuCursorX[1] < 0 || (int)gWmMenuCursorX[0] != m_mcCtrl.GetSlot() ||
			    s_Serial != m_mcCtrl.GetSerial()) {
				int sel;
				for (sel = 0; sel < kMcListCount; sel++) {
					if (m_wmCharaState[sel].m_isBroken != 0 ||
					    static_cast<int>(m_wmCharaState[sel].m_scriptSysVal0) <= 0) {
						m_mcCtrl.SetDno(sel);
						break;
					}
				}
				if (sel >= kMcListCount) {
					m_mcCtrl.SetDno(0);
				}
				m_wmWorldState->m_cardChannel = (short)m_mcCtrl.GetDno();
			} else {
				m_mcCtrl.SetDno((int)gWmMenuCursorX[1]);
				m_wmWorldState->m_cardChannel = (short)m_mcCtrl.GetDno();
			}
			subState = 0;
			for (int remaining = 4; remaining != 0; remaining--) {
				if (m_wmCharaState[subState].m_isBroken != 0) {
					m_mcCtrl.SetDno(subState);
					m_wmWorldState->m_cardChannel = (short)subState;
					break;
				}
				subState++;
			}
			m_wmWorldState->m_state0E = 1;
			m_wmWorldState->m_counter1A = 10;
		}
		if (m_menuWindowInfo->state == 1) {
			if (m_wmWorldState->m_counter1A != 0) {
				m_wmWorldState->m_counter1A--;
				if (m_wmWorldState->m_counter1A == 0) {
					m_menuWindowInfo->state = 2;
				}
			}
		}
		break;
	}
	case 0x11:
		m_wmWorldState->m_mcResult = (short)MemoryCardMan.McChkConnect(m_mcCtrl.GetSlot());
		if (m_wmWorldState->m_mcResult == 0 && buttonsRepeat != 0) {
			if ((buttonsRepeat & 8) != 0) {
				if (m_wmWorldState->m_cardChannel < 1) {
					m_wmWorldState->m_cardChannel = 3;
				} else {
					m_wmWorldState->m_cardChannel--;
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			} else {
				if ((buttonsRepeat & 4) != 0) {
					if (!(m_wmWorldState->m_cardChannel < 3)) {
						m_wmWorldState->m_cardChannel = 0;
					} else {
						m_wmWorldState->m_cardChannel++;
					}
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				}
			}
			if ((buttonsRepeat & 0xC) == 0) {
				if ((buttonsDown & 0x100) != 0) {
					short decideState = m_wmWorldState->m_state0E;
					if (decideState != -1 && decideState != 1) {
						m_mcCtrl.SetDno((int)m_wmWorldState->m_cardChannel);
						m_wmWorldState->m_state0E = 1;
						Sound.PlaySe(2, 0x40, 0x7F, 0);
					}
				}
				if ((buttonsDown & 0x200) != 0) {
					short decideState = m_wmWorldState->m_state0E;
					if (decideState != -1 && decideState != 1) {
						m_wmWorldState->m_state0E = -1;
						Sound.PlaySe(3, 0x40, 0x7F, 0);
					}
				}
			}
		}
		break;
	}

	if (m_wmWorldState->m_subState != 0) {
		CalcMcObj();
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 636b
 * EN Address: 0x801084A0
 * EN Size: 304b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CalcCMakeMenu()
{
	if (m_wmWorldState->m_modelFlagsInitialized == 0) {
		for (int i = 0; i < kWmMenuPlayerCount; i++) {
			m_wm.m_charaModelData[i].m_modelChanged = 1;
		}
		m_wmWorldState->m_modelFlagsInitialized = 1;
	}
	if (m_wmWorldState->m_mainState <= 4) {
		CalcCharaSelect();
		CalcCharaBase();
		const short state = m_wmWorldState->m_mainState;
		int frameStep;
		if (state == 0) {
			frameStep = m_wmWorldState->m_frameCounter - 10;
		} else if (state > 0 && state < 4) {
			frameStep = 0;
		} else {
			frameStep = -m_wmWorldState->m_frameCounter;
		}
		CalcWMFrame0(frameStep);
		const short animState = m_wmWorldState->m_mainState;
		if (animState > 0 && animState < 4) {
			CalcChara();
		}
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 164b
 * EN Address: 0x801085D0
 * EN Size: 172b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CalcMoveMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	if (((m_wmWorldState->m_mainState != 0) || bytes[0x12] != 0) &&
	    m_wmWorldState->m_mainState <= 3) {
		if (Game.m_gameWork.m_chaliceElement != m_crystalElem) {
			SetCrystalCageAttr();
		}
		if (Game.m_gameWork.m_timerA != m_manaWaterTimerA) {
			SetManaWaterEffect();
		}
		CalcFukidashi();
		CalcPitcher();
		CalcWMFrame();
	}
}

/*
 * --INFO--
 * PAL Address: 0x800feba0
 * PAL Size: 160b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::InitSaveLoadMenu()
{
	float posX = FLOAT_803313dc;
	float posY = FLOAT_803313e8;
	int zero = 0;

	MenuPcs.m_wmWorldState->m_frameCounter = zero;
	MenuPcs.m_wmWorldState->m_titleState = zero;
	MenuPcs.m_wmWorldState->m_worldReady = static_cast<unsigned char>(zero);
	MenuPcs.m_wmWorldState->m_flag09 = static_cast<unsigned char>(zero);
	MenuPcs.m_wmWorldState->m_flag0A = static_cast<unsigned char>(zero);
	MenuPcs.m_wmWorldState->m_state0E = zero;
	MenuPcs.m_wmWorldState->m_mainState = zero;
	MenuPcs.m_wmWorldState->m_state12 = zero;
	MenuPcs.m_wmWorldState->m_subState = zero;
	MenuPcs.m_wmWorldState->m_delay = zero;
	MenuPcs.m_wmWorldState->m_counter1A = zero;
	MenuPcs.m_wmWorldState->m_posY = posY;
	MenuPcs.m_wmWorldState->m_posX = posX;
	MenuPcs.m_wmWorldState->m_mcResult = zero;
	MenuPcs.m_wmWorldState->m_flag0B = static_cast<unsigned char>(zero);
	MenuPcs.m_wmWorldState->m_cardChannel = zero;
	MenuPcs.m_wmTransitionCode = zero;
	MenuPcs.m_textureLocIndex = static_cast<unsigned char>(zero);
}

/*
 * --INFO--
 * PAL Address: 0x800FCFB4
 * PAL Size: 7148b
 * EN Address: 0x800FC55C
 * EN Size: 6976b
 * JP Address: 0x800F92CC
 * JP Size: 6888b
 */
void CMenuPcs::CalcLoadMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	int playOpenSe = 0;
	m_textureLocIndex = 0;

	unsigned int buttonsDown = Pad.GetButtonDown(0);
	unsigned short buttonsRepeat = GetButtonRepeat(0);

	if (m_wmWorldState->m_worldReady == 0) {
		InitFrame0Info();

		m_mcCtrl.Init();
		m_mcCtrl.SetSlot(0);
		m_mcCtrl.SetDno(0);
		ClrMcList();

		for (int i = 0; i < kWmMenuControllerCount; i++) {
			Game.m_gameWork.m_wmBackupParams[i] = m_wmWorldState->m_originalBackupParams[i];
		}
		if (m_wmWorldState->m_menuMode == 8 && m_cmakeWorkCardChannel != 0) {
			m_mcCtrl.SetSlot((int)m_cmakeWorkCardChannel - 1);
			m_wmWorldState->m_subState = 3;
			m_wmWorldState->m_flag09 = 1;
		}
		m_wmWorldState->m_flag0A = 0;
		m_wmWorldState->m_worldReady = 1;
	}

	short mainState = m_wmWorldState->m_mainState;
	unsigned int frameOffset;
	if (mainState == 0) {
		frameOffset = static_cast<int>(m_wmWorldState->m_frameCounter) - 10;
	} else if (mainState > 0 && mainState < 4) {
		frameOffset = 0;
	} else {
		frameOffset = -static_cast<int>(m_wmWorldState->m_frameCounter);
	}

	CalcWMFrame0(static_cast<int>(frameOffset));
	int subState;

	if (m_wmWorldState->m_mainState != 2) {
		return;
	}

	subState = m_wmWorldState->m_subState;
	switch (subState) {
	case 0:
	case 2:
		if ((signed char)m_wmWorldState->m_flag09 == 0) {
			m_wmWorldState->m_cardChannel = (short)m_mcCtrl.GetSlot();
			short windowWidth;
			short windowHeight;
			GetWinSize(0, &windowWidth, &windowHeight, 0);
			SetMcWinInfo(windowWidth, windowHeight);
			m_menuWindowInfo->state = 0;
			ClrMcList();
			m_wmWorldState->m_flag09 = 1;
			m_wmWorldState->m_flag0A = 0;
		}
		if (m_menuWindowInfo->state == 1) {
			if (m_wmWorldState->m_counter1A == 0) {
				if ((buttonsRepeat & 3) != 0) {
					m_wmWorldState->m_cardChannel ^= 1;
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				} else {
					if ((buttonsDown & 0x100) != 0) {
						m_wmWorldState->m_state0E = 1;
						m_mcCtrl.SetSlot((int)m_wmWorldState->m_cardChannel);
						m_wmWorldState->m_counter1A = 10;
						Sound.PlaySe(2, 0x40, 0x7F, 0);
					} else {
						if ((buttonsDown & 0x200) != 0) {
							m_wmWorldState->m_state0E = -1;
							m_wmWorldState->m_counter1A = 1;
							Sound.PlaySe(3, 0x40, 0x7F, 0);
						}
					}
				}
			}
		}
		if (m_menuWindowInfo->state == 1) {
			int cnt1A = m_wmWorldState->m_counter1A;
			if (cnt1A != 0) {
				m_wmWorldState->m_counter1A = cnt1A - 1;
				if (m_wmWorldState->m_counter1A == 0) {
					m_menuWindowInfo->state = 2;
				}
			}
		}
		break;
	case 3:
		m_wmWorldState->m_mcResult = (short)MemoryCardMan.McChkConnect(m_mcCtrl.GetSlot());
		break;
	case 5:
	case 6:
	case 7:
	case 10:
	case 0xE:
	case 0xF:
	case 0x10:
	case 0x17:
	case 0x18:
	case 0x1B:
	case 0x1C: {
		if ((signed char)m_wmWorldState->m_flag09 == 0) {
			playOpenSe = true;
			int messType = 0;
			int winType;
			if (subState == 5) { winType = 1; }
			else if (subState == 6) { winType = 2; }
			else if (subState == 7) { winType = 3; }
			else if (subState == 10) { winType = 0xB; }
			else if (subState == 0xE) { winType = 0xC; }
			else if (subState == 0xF) { winType = 0xD; }
			else if (subState == 0x1C) { winType = 0x1B; messType = 1; }
			else if (subState == 0x1B) { winType = 0x1C; messType = 1; }
			else if (subState == 0x18) { playOpenSe = false; winType = 0x10; }
			else if (subState == 0x17) { winType = 0x11; }
			else { winType = 0x13; }
			if (playOpenSe) {
				Sound.PlaySe(4, 0x40, 0x7F, 0);
			}
			short windowWidth;
			short windowHeight;
			GetWinSize(winType, &windowWidth, &windowHeight, messType);
			SetMcWinInfo(windowWidth, windowHeight);
			m_menuWindowInfo->state = 0;
			m_wmWorldState->m_flag09 = 1;
			m_wmWorldState->m_counter1A = 0;
		}
		if (m_menuWindowInfo->state == 1
		    && m_wmWorldState->m_counter1A == 0) {
			if (m_wmWorldState->m_subState == 0xE) {
				m_wmWorldState->m_mcResult = (short)MemoryCardMan.McChkConnect(m_mcCtrl.GetSlot());
				if (m_wmWorldState->m_mcResult < 0) goto checkLoadResult;
			} else if (m_wmWorldState->m_subState == 5) {
				m_wmWorldState->m_mcResult = (short)MemoryCardMan.McChkConnect(m_mcCtrl.GetSlot());
			checkLoadResult:
				short curSub = m_wmWorldState->m_subState;
				short expectedResult;
				if (curSub == 5) { expectedResult = -1; }
				else if (curSub == 6) { expectedResult = -3; }
				else if (curSub == 7) { expectedResult = -4; } else { expectedResult = 0; }
				if (curSub != 7) {
					if (m_wmWorldState->m_mcResult != 0 && m_wmWorldState->m_mcResult != expectedResult && m_wmWorldState->m_mcResult != 1) {
						m_wmWorldState->m_state0E = -1;
						m_wmWorldState->m_counter1A = 1;
						break;
					}
				} else {
					short chk = m_wmWorldState->m_mcResult;
					if (chk != 0 && chk != expectedResult && chk != 1) {
						m_wmWorldState->m_state0E = -1;
						m_wmWorldState->m_counter1A = 1;
						break;
					}
				}
			}
			if ((buttonsDown & 0x300) != 0) {
				m_wmWorldState->m_state0E = 1;
				m_wmWorldState->m_counter1A = 10;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
			}
		}
		if (m_menuWindowInfo->state == 1) {
			int cnt1A = m_wmWorldState->m_counter1A;
			if (cnt1A != 0) {
				m_wmWorldState->m_counter1A = cnt1A - 1;
				if (m_wmWorldState->m_counter1A == 0) {
					m_menuWindowInfo->state = 2;
				}
			}
		}
		break;
	}
	case 4:
		if ((signed char)m_wmWorldState->m_flag09 == 0) {
			short windowWidth;
			short windowHeight;
			GetWinSize(6, &windowWidth, &windowHeight, 0);
			SetMcWinInfo(windowWidth, windowHeight);
			m_menuWindowInfo->state = 0;
			m_mcCtrl.Init();
			m_wmWorldState->m_flag09 = 1;
		} else if (m_menuWindowInfo->state == 1
		           && m_wmWorldState->m_counter1A == 0) {
			short chkResult = (short)GetMcCtrl()->ChkEmpty(1);
			m_wmWorldState->m_mcResult = chkResult;
			if (m_wmWorldState->m_mcResult < 0) {
#if defined(VERSION_GCCP01)
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = 0xFF;
#endif
				m_wmWorldState->m_state0E = -1;
				m_wmWorldState->m_counter1A = 10;
			}
		}
		if (m_menuWindowInfo->state == 1) {
			int cnt1A = m_wmWorldState->m_counter1A;
			if (cnt1A != 0) {
				m_wmWorldState->m_counter1A = cnt1A - 1;
				if (m_wmWorldState->m_counter1A == 0) {
					m_menuWindowInfo->state = 2;
				}
			}
		}
		break;
	case 8:
	case 0xB:
	case 0x19: {
		if ((signed char)m_wmWorldState->m_flag09 == 0) {
			int messType = 0;
			int winType;
			if (subState == 8) {
				m_wmWorldState->m_cardChannel = 0;
				winType = 4;
			} else if (subState == 0x19) {
				messType = 1;
				winType = 0x19;
				m_wmWorldState->m_cardChannel = 1;
			} else {
				winType = 5;
				m_wmWorldState->m_cardChannel = 1;
			}
			short windowWidth;
			short windowHeight;
			GetWinSize(winType, &windowWidth, &windowHeight, messType);
			SetMcWinInfo(windowWidth, windowHeight);
			m_menuWindowInfo->state = 0;
			m_wmWorldState->m_flag09 = 1;
		}
		if (m_menuWindowInfo->state == 1) {
			if (m_wmWorldState->m_counter1A == 0) {
				if (m_wmWorldState->m_subState == 0x19) {
					m_wmWorldState->m_state0E = 1;
					m_wmWorldState->m_counter1A = 0x5A;
					break;
				}
				int chkRes = MemoryCardMan.McChkConnect(m_mcCtrl.GetSlot());
				m_wmWorldState->m_mcResult = (short)chkRes;
				if (m_wmWorldState->m_mcResult != 0) {
					m_wmWorldState->m_state0E = -1;
					m_wmWorldState->m_counter1A = 10;
				} else {
					if ((buttonsRepeat & 3) != 0) {
						m_wmWorldState->m_cardChannel ^= 1;
						Sound.PlaySe(1, 0x40, 0x7F, 0);
					} else {
						if ((buttonsDown & 0x100) != 0) {
							if (m_wmWorldState->m_cardChannel == 0) {
								m_wmWorldState->m_state0E = 1;
							} else {
								m_wmWorldState->m_state0E = -1;
							}
							m_wmWorldState->m_counter1A = 10;
							Sound.PlaySe(2, 0x40, 0x7F, 0);
						} else {
							if ((buttonsDown & 0x200) != 0) {
								m_wmWorldState->m_cardChannel = 1;
								m_wmWorldState->m_state0E = -1;
								m_wmWorldState->m_counter1A = 10;
								Sound.PlaySe(3, 0x40, 0x7F, 0);
							}
						}
					}
				}
			}
		}
		if (m_menuWindowInfo->state == 1
		    && m_wmWorldState->m_counter1A != 0) {
			if (m_wmWorldState->m_subState == 0x19) {
				int chkRes = MemoryCardMan.McChkConnect(m_mcCtrl.GetSlot());
				m_wmWorldState->m_mcResult = (short)chkRes;
			}
			m_wmWorldState->m_counter1A--;
			if (m_wmWorldState->m_counter1A == 0) {
				m_menuWindowInfo->state = 2;
			}
		}
		break;
	}
	case 0xD:
	case 0x16:
	case 0x1A: {
		if ((signed char)m_wmWorldState->m_flag09 == 0) {
			int messType = 0;
			int winType;
			if (subState == 0xD) { winType = 7; }
			else if (subState == 0x1A) {
				winType = 0x1A;
#if !defined(VERSION_GCCJGC)
				messType = 1;
#endif
			}
			else { winType = 9; }
			short windowWidth;
			short windowHeight;
			GetWinSize(winType, &windowWidth, &windowHeight, messType);
			SetMcWinInfo(windowWidth, windowHeight);
			m_menuWindowInfo->state = 0;
			m_mcCtrl.Init();
			if (m_wmWorldState->m_menuMode == 8
			    && m_cmakeWork != 0) {
				m_mcCtrl.SetDataBuff(reinterpret_cast<char*>(m_cmakeWork));
			} else {
				m_mcCtrl.SetDataBuff(0);
			}
			m_wmWorldState->m_flag09 = 1;
		} else if (m_menuWindowInfo->state == 1
		           && m_wmWorldState->m_counter1A == 0) {
			subState = (int)m_wmWorldState->m_subState;
			if (subState == 0xD) {
				short fmtRes = (short)GetMcCtrl()->Format(1);
				m_wmWorldState->m_mcResult = fmtRes;
#if defined(VERSION_GCCP01)
				if (m_wmWorldState->m_mcResult < 0) {
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
				}
#endif
			} else if (subState == 0x1A) {
				short erRes = (short)GetMcCtrl()->EraseDat();
				m_wmWorldState->m_mcResult = erRes;
#if defined(VERSION_GCCP01)
				if (m_wmWorldState->m_mcResult < 0) {
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
				}
#endif
			} else {
				m_wmWorldState->m_mcResult = (short)GetMcCtrl()->LoadDat();
			}

			if (m_wmWorldState->m_mcResult != 0) {
#if defined(VERSION_GCCP01)
				if (m_wmWorldState->m_mcResult < 0) {
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
				}
#endif
				if (m_wmWorldState->m_subState == 0x16) {
					if (m_wmWorldState->m_menuMode != 8 && m_wmWorldState->m_mcResult == 1) {
						s_Serial = m_mcCtrl.GetSerial();
						gWmMenuCursorX[0] = (unsigned char)m_mcCtrl.GetSlot();
						gWmMenuCursorX[1] = (unsigned char)m_mcCtrl.GetDno();
					} else {
						gWmMenuCursorY[0] = (unsigned char)m_mcCtrl.GetSlot();
						gWmMenuCursorY[1] = (unsigned char)m_mcCtrl.GetDno();
					}
					for (int charaIdx = 0; charaIdx < kWmMenuPlayerCount; charaIdx++) {
						WmCharaModelInfo* modelInfo = &m_wm.m_charaModelData[charaIdx];
						int tribe;
						int gender;
						int variant;
						if (m_wmWorldState->m_menuMode == 8 && m_cmakeWork != 0) {
							Mc::CharaDat& character = m_cmakeWork->m_characters[charaIdx];
							if (character.m_exists != 0) {
								tribe = character.m_tribeId;
								variant = character.m_appearanceVariant;
								gender = character.m_genderFlag;
							} else {
								modelInfo->m_modelNo = -1;
								tribe = -1;
								variant = -1;
								gender = -1;
							}
						} else if (Game.m_caravanWorkArr[charaIdx].m_shopState != 0) {
							CCaravanWork& work = Game.m_caravanWorkArr[charaIdx];
							tribe = work.m_tribeId;
							gender = work.m_genderFlag;
							variant = work.m_appearanceVariant;
							modelInfo->m_modelNo = GetModelNo(tribe, variant, gender);
						} else {
							modelInfo->m_modelNo = -1;
							tribe = -1;
							variant = -1;
							gender = -1;
						}
						modelInfo = &m_wm.m_charaModelData[charaIdx];
						int charaId;
						int loadMode;
						if (tribe >= 0) {
							charaId = GetModelNo(tribe, variant, gender);
							loadMode = 0;
							modelInfo->m_modelChanged = 1;
						} else {
							loadMode = 3;
							modelInfo->m_modelChanged = 0;
							charaId = 0x43;
						}
						GetWmCharaHandles(this)[charaIdx]->LoadModelASync(loadMode, charaId, 0);
					}

					if (m_wmWorldState->m_menuMode != 8) {
						for (int i = 0; i < kWmMenuControllerCount; i++) {
							m_wmWorldState->m_originalBackupParams[i] = static_cast<short>(Game.m_gameWork.m_wmBackupParams[i]);
							m_wmWorldState->m_backupParams[i] = static_cast<short>(Game.m_gameWork.m_wmBackupParams[i]);
						}
					}
				}
				m_wmWorldState->m_state0E = 1;
				m_wmWorldState->m_counter1A = 10;
			}
		}
		if (m_menuWindowInfo->state == 1) {
			int cnt1A = m_wmWorldState->m_counter1A;
			if (cnt1A != 0) {
				m_wmWorldState->m_counter1A = cnt1A - 1;
				if (m_wmWorldState->m_counter1A == 0) {
					m_menuWindowInfo->state = 2;
				}
			}
		}
		break;
	}
	case 0xC: {
		if ((signed char)m_wmWorldState->m_flag09 == 0) {
			m_wmWorldState->m_flag09 = 1;
			ClrMcList();
			m_mcCtrl.Init();
		}
		if (m_menuWindowInfo->state == 1
		    && m_wmWorldState->m_counter1A == 0) {
			short listRes = (short)GetMcCtrl()->LoadMcList();
			m_wmWorldState->m_mcResult = listRes;
			short listResult = m_wmWorldState->m_mcResult;
			if (listResult == 0) {
				if (listResult < 0) {
#if defined(VERSION_GCCP01)
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
#endif
				}
			} else {
				int dataCount = 0;
				if (m_wmWorldState->m_menuMode == 8) {
					dataCount = ChkMcDataCnt();
					if (dataCount == 0) {
						m_wmWorldState->m_mcResult = (short)0xFC19;
					}
				}
				OSCalendarTime saveTimes[kMcListCount];
				OSCalendarTime* currentTime = saveTimes;
				subState = 0;
				do {
					OSTicksToCalendarTime(m_wmCharaState[subState].m_saveTime,
					                      &currentTime[subState]);
					subState++;
				} while (subState < 4);

				int entryIdx = 0;
				int bestIdx = -1;
				for (; entryIdx < 4; entryIdx++) {
					const McListInfo& entry = m_wmCharaState[entryIdx];
					if (entry.m_isBroken == 0
					    && static_cast<int>(entry.m_scriptSysVal0) > 0) {
						if (bestIdx < 0) {
							bestIdx = entryIdx;
						} else if (saveTimes[bestIdx].year <= currentTime->year
						           && (saveTimes[bestIdx].year < currentTime->year
						               || (saveTimes[bestIdx].yday <= currentTime->yday
						                   && (saveTimes[bestIdx].yday < currentTime->yday
						                       || (saveTimes[bestIdx].hour <= currentTime->hour
						                           && (saveTimes[bestIdx].hour < currentTime->hour
						                               || (saveTimes[bestIdx].min <= currentTime->min
						                                   && (saveTimes[bestIdx].min < currentTime->min
						                                       || (saveTimes[bestIdx].sec <= currentTime->sec
						                                           && (saveTimes[bestIdx].sec < currentTime->sec
						                                               || (saveTimes[bestIdx].msec <= currentTime->msec
						                                                   && (saveTimes[bestIdx].msec < currentTime->msec
						                                                       || saveTimes[bestIdx].usec < currentTime->usec)))))))))))) {
							bestIdx = entryIdx;
						}
					}
					currentTime++;
				}
				if (bestIdx < 0) bestIdx = 0;

				m_wmWorldState->m_cardChannel = (short)bestIdx;
				for (subState = 0; subState < 4; subState++) {
					const McListInfo& entry = m_wmCharaState[subState];
					if (entry.m_isBroken != 0) {
						m_mcCtrl.SetDno(subState);
						m_wmWorldState->m_cardChannel = (short)subState;
						break;
					}
				}
				m_wmWorldState->m_state0E = 1;
				m_wmWorldState->m_counter1A = 10;
			}
		}
		if (m_menuWindowInfo->state == 1) {
			int cnt1A = m_wmWorldState->m_counter1A;
			if (cnt1A != 0) {
				m_wmWorldState->m_counter1A = cnt1A - 1;
				if (m_wmWorldState->m_counter1A == 0) {
					m_menuWindowInfo->state = 2;
				}
			}
		}
		break;
	}
	case 0x11: {
		int chkRes = MemoryCardMan.McChkConnect(m_mcCtrl.GetSlot());
		m_wmWorldState->m_mcResult = (short)chkRes;
		if (m_wmWorldState->m_mcResult == 0 && buttonsRepeat != 0) {
			if ((buttonsRepeat & 8) != 0) {
				if (m_wmWorldState->m_cardChannel <= 0) {
					m_wmWorldState->m_cardChannel = 3;
				} else {
					m_wmWorldState->m_cardChannel--;
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			} else {
				if ((buttonsRepeat & 4) != 0) {
					if (m_wmWorldState->m_cardChannel >= 3) {
						m_wmWorldState->m_cardChannel = 0;
					} else {
						m_wmWorldState->m_cardChannel++;
					}
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				}
			}
			if ((buttonsRepeat & 0xC) == 0) {
				if ((buttonsDown & 0x100) != 0) {
					short decideState = m_wmWorldState->m_state0E;
					if (decideState != -1 && decideState != 1) {
						int saveIdx = (int)m_wmWorldState->m_cardChannel;
						const McListInfo& entry = m_wmCharaState[saveIdx];
						if (entry.m_hasData == 0 || entry.m_isBroken != 0) {
							Sound.PlaySe(4, 0x40, 0x7F, 0);
						} else {
							m_mcCtrl.SetDno(saveIdx);
							m_wmWorldState->m_state0E = 1;
							Sound.PlaySe(2, 0x40, 0x7F, 0);
						}
					}
				}
				if ((buttonsDown & 0x200) != 0) {
					short decideState = m_wmWorldState->m_state0E;
					if (decideState != -1 && decideState != 1) {
						m_wmWorldState->m_state0E = -1;
						Sound.PlaySe(3, 0x40, 0x7F, 0);
					}
				}
			}
		}
		break;
	}
	}

	if (m_wmWorldState->m_subState != 0) {
		CalcMcObj();
	}
}

/*
 * --INFO--
 * PAL Address: 0x800FCA2C
 * PAL Size: 1416b
 * EN Address: 0x800FBFD4
 * EN Size: 1416b
 * JP Address: 0x800F8D60
 * JP Size: 1388b
 */
void CMenuPcs::CalcTitleMenu()
{
#ifdef VERSION_GCCJGC
	char* const OPMOVIE_FNAME = "dvd/movie/ffcc_op.thp";
	const int kMovieBufferLine = 0xBC9;
#else
	static char* OPMOVIE_FNAME = "dvd/movie/ffcc_op.thp";
#ifdef VERSION_GCCE01
	const int kMovieBufferLine = 0xA98;
#else
	const int kMovieBufferLine = 0xABA;
#endif
#endif

	int down = Pad.GetButtonDown(0);
	const unsigned short repeat = GetButtonRepeat(0);

	{
		if (static_cast<signed char>(m_wmWorldState->m_worldReady) == 0) {
			if (static_cast<signed char>(lbl_8032EE1C) == 1) {
				PPPCREATEPARAM param;
				EffectInfo* titleEffect = &m_effectWork[23];
				titleEffect->m_effectNo = 0x1F;
				CGObject* titleObject = &titleEffect->m_object;
				titleEffect->m_slotNo = 0x17;
				titleObject->Create();
				titleObject->m_charaModelHandle = m_wm.m_handles[23];
				param.m_lookTargetPtr = titleObject;
				param.m_bindObject = titleObject;
				titleEffect->m_partNo = PartMng.pppCreate(0, 0x1F, &param, 1);
				m_wmWorldState->m_delay = 0;
				m_wmWorldState->m_worldReady = 1;
				m_wmWorldState->m_flag09 = 1;
				m_wmThpActive = 0;
				m_wmWorldState->m_titleState = 0;
				m_wmWorldState->m_state0E = -1;
				m_wmWorldState->m_state12 = 0;
				CallWorldParam(9, 0, 0);
				m_wmWorldState->m_cardChannel = 0;
				lbl_8032EE1C = 0;
				return;
			}
			lbl_8032E8AC = 0;
			THPSimpleInit(1);
			THPSimpleOpen(OPMOVIE_FNAME);
			int thpMemory = THPSimpleCalcNeedMemory();
			m_wmWorkBuffer =
			    static_cast<unsigned char*>(Memory._Alloc(thpMemory, CharaPcs.GetAnimStage(), "wm_menu.cpp", kMovieBufferLine, 0));
			THPSimpleSetBuffer(m_wmWorkBuffer);
			THPSimplePreLoad(0);
			THPSimpleAudioStart();
			PPPCREATEPARAM param;
			EffectInfo* titleEffect = &m_effectWork[23];
			titleEffect->m_effectNo = 0x1F;
			CGObject* titleObject = &titleEffect->m_object;
			titleEffect->m_slotNo = 0x17;
			titleObject->Create();
			titleObject->m_charaModelHandle = m_wm.m_handles[23];
			param.m_lookTargetPtr = titleObject;
			param.m_bindObject = titleObject;
			titleEffect->m_partNo = PartMng.pppCreate(0, 0x1F, &param, 1);
			m_wmThpActive = 1;
			m_wmWorldState->m_cardChannel = 0;
			m_wmWorldState->m_delay = 0;
			m_wmWorldState->m_worldReady = 1;
			m_wmWorldState->m_flag09 = 1;
		}

		if (m_wmWorldState->m_mainState == 0) {
			if ((down & 0x1000) != 0) {
				THPSimpleAudioStop();
				THPSimpleLoadStop();
				THPSimpleClose();
				THPSimpleQuit();
				if (m_wmWorkBuffer != 0) {
					Memory.Free(m_wmWorkBuffer);
					m_wmWorkBuffer = 0;
				}
				m_wmThpActive = 0;
				m_wmWorldState->m_titleState = 0;
				m_wmWorldState->m_state0E = -1;
			} else if (THPSimpleDecode(0) == 0) {
				m_wmWorldState->m_frameCounter = static_cast<short>(m_wmWorldState->m_frameCounter + 1);
			}
		}

		if (m_wmWorldState->m_mainState != 2) {
			if (m_wmWorldState->m_mainState < 2) {
				if (MemoryCardMan.McChkConnect(0) == 0) {
					m_wmWorldState->m_cardChannel = 1;
				} else if (MemoryCardMan.McChkConnect(1) == 0) {
					m_wmWorldState->m_cardChannel = 1;
				} else {
					m_wmWorldState->m_cardChannel = 0;
				}
			}
		} else {
			if (m_wmWorldState->m_delay == 0) {
			if ((repeat & 0xC) != 0) {
				m_wmWorldState->m_cardChannel ^= 1;
				m_wmWorldState->m_titleState = 0;
				m_wmWorldState->m_state12 = 0;
				m_wmWorldState->m_flag09 = 0;
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			} else if ((down & 0x100) != 0) {
				if (m_wmWorldState->m_cardChannel == 0) {
					s_Serial = -1;
					gWmMenuCursorX[0] = -1;
					gWmMenuCursorX[1] = -1;
					Game.InitNewGame();
				}
				m_wmWorldState->m_delay = 0x14;
				m_wmWorldState->m_state0E = 1;
				Sound.PlaySe(0x0B, 0x40, 0x7F, 0);
			} else if ((down & 0x200) != 0) {
				Sound.PlaySe(4, 0x40, 0x7F, 0);
			}

			if (repeat == 0) {
				m_wmWorldState->m_frameCounter = static_cast<short>(m_wmWorldState->m_frameCounter + 1);
			} else {
				m_wmWorldState->m_frameCounter = 0;
			}
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800fc4bc
 * PAL Size: 1392b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcGoOutCharaSelect(unsigned char state)
{
	if (m_wmWorldState->m_mainState != 2) {
		return;
	}

	if (!IsAsyncCharaLoadFinish()) {
		return;
	}
	WmCharaSelectEntry& entry = m_wm.m_charaSelectData[0];
	if (entry.m_confirmed != 0) {
		return;
	}

	entry.m_padType = Joybus.GetPadType(0);
	if (entry.m_padType == 0x09000000 || entry.m_padType == -0x74F00000 || entry.m_padType == -0x78000000) {
		entry.m_connected = 1;
	} else if (Game.m_gameWork.m_menuStageMode == 0) {
		entry.m_connected = Joybus.GetGBAConnect(0);
	} else {
		entry.m_connected = 0;
	}

	unsigned short repeat;
	unsigned short down;
	if (entry.m_connected == 1 && entry.m_cmakePending == 0) {
		repeat = Pad.GetButtonRepeat(0);
		down = Pad.GetButtonDown(0);
	} else {
		repeat = 0;
		down = repeat;
	}

	if (m_wmWorldState->m_mainState != 2 || m_wmWorldState->m_nextMenuMode != 0) {
		return;
	}

	WmCharaSelectEntry& curEntry = m_wm.m_charaSelectData[0];
	int cursor = static_cast<int>(curEntry.m_currentSlot);
	if ((repeat & 0x0C) != 0) {
		if (cursor < 4) {
			cursor += 4;
		} else {
			cursor -= 4;
		}
		Sound.PlaySe(1, 0x40, 0x7F, 0);
	}

	if ((repeat & 1) != 0) {
		const int row = static_cast<int>(cursor) >> 2;
		if (cursor > ((row != 0) ? 4 : 0)) {
			cursor--;
		} else {
			cursor += 3;
		}
		Sound.PlaySe(1, 0x40, 0x7F, 0);
	} else if ((repeat & 2) != 0) {
		int rowEnd = 3;
		if ((cursor >> 2) != 0) {
			rowEnd = 7;
		}
		if (cursor < rowEnd) {
			cursor++;
		} else {
			cursor -= 3;
		}
		Sound.PlaySe(1, 0x40, 0x7F, 0);
	}

	curEntry.m_currentSlot = static_cast<short>(cursor);
	if ((repeat & 0x6F) != 0) {
		return;
	}

	if ((down & 0x100) != 0) {
		int exists;
		if (m_cmakeWorkActive == 1 && m_cmakeWork != 0) {
			exists = m_cmakeWork->m_characters[curEntry.m_currentSlot].m_exists;
		} else {
			exists = Game.m_caravanWorkArr[curEntry.m_currentSlot].m_shopState;
		}

		if (exists == 0) {
			Sound.PlaySe(4, 0x40, 0x7F, 0);
		} else {
			curEntry.m_confirmed = 1;
			Sound.PlaySe(0x33, 0x40, 0x7F, 0);
			if (state != 0) {
				GetWmCharaAnimState(this)[cursor].m_nextAnimIndex = 3;
			}
		}
	} else if ((down & 0x200) != 0) {
		curEntry.m_cancelled = 1;
		Sound.PlaySe(0x34, 0x40, 0x7F, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800fc234
 * PAL Size: 648b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::CalcGoOutSelChar(unsigned char state, unsigned char slot)
{
	if (m_wmWorldState->m_mainState > 4) {
		return -1;
	}

	if (state != 0) {
		CalcGoOutCharaSelect(slot);
	}

	short menuAnim = m_wmWorldState->m_mainState;
	int offset;
	if (menuAnim == 0) {
		offset = static_cast<int>(m_wmWorldState->m_frameCounter) - 10;
	} else if (menuAnim > 0 && menuAnim < 4) {
		offset = 0;
	} else {
		offset = -static_cast<int>(m_wmWorldState->m_frameCounter);
	}

	CalcWMFrame0(offset);

	if (m_wmWorldState->m_mainState > 0 && m_wmWorldState->m_mainState < 4) {
		CalcChara();
	}

	WmCharaSelectEntry* const entry = m_wm.m_charaSelectData;
	if (entry->m_cancelled != 0) {
		return -2;
	}

	if (entry->m_confirmed != 0 &&
	    (m_wmCharaAnimState[entry->m_currentSlot].m_animIndex != 3 || slot == 0)) {
		return static_cast<int>(entry->m_currentSlot);
	}

	return -1;
}

/*
 * --INFO--
 * PAL Address: 0x800fc220
 * PAL Size: 20b
 * EN Address: 0x8010a840
 * EN Size: 40b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcGoOutSelCharInit()
{
	WmCharaSelectEntry* const entry = m_wm.m_charaSelectData;

	entry->m_confirmed = 0;
	entry->m_cancelled = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800fc20c
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetMenuCharaAnim(int charaIndex, int animIndex)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	WmCharaAnimState* const menuCharaAnims = m_wmCharaAnimState;

	menuCharaAnims[charaIndex].m_nextAnimIndex = animIndex;
}

/*
 * --INFO--
 * PAL Address: 0x800fc1f4
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::IsMenuCharaAnimIdle(int charaIndex)
{
	return m_wmCharaAnimState[charaIndex].m_animIndex == 0;
}

/*
 * --INFO--
 * PAL Address: 0x800fc0b0
 * PAL Size: 324b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::drawWorld()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	if (static_cast<signed char>(bytes[0xD]) == 0) {
		int i = 4;
		unsigned char* menuSlot = bytes + 0x10;
		for (; i < 6; i++) {
			CMenu* const menu = *reinterpret_cast<CMenu**>(menuSlot + 0x10C);
			menu->Draw();
			menuSlot += 4;
		}
	} else {
		const short menuMode = m_wmWorldState->m_menuMode;

		switch (menuMode) {
		case 0:
			DrawMainMenu();
			break;
		case 1:
			DrawDiaryMenu();
			break;
		case 2:
			DrawMCardMenu();
			break;
		case 3:
			if (m_singleCmakeMode == 0) {
				DrawCMakeMenu();
			} else {
				DrawSingCMake();
			}
			break;
		case 4:
			DrawMoveMenu();
			break;
		case 5:
			DrawLoadMenu();
			break;
		case 6:
			DrawTitleMenu();
			break;
		case 7:
			DrawOptionMenu();
			break;
		case 8:
			DrawGoOutMenu();
			break;
		default:
			if (static_cast<unsigned int>(System.m_execParam) >= 1) {
				System.Printf("%s(%d): Error:WM menu no error(%d)\n", "wm_menu.cpp", 0xC59, menuMode);
			}
			break;
		}

		unsigned char* menuSlot;
		int i = 4;
		menuSlot = bytes + 0x10;
		for (; i < 6; i++) {
			CMenu* const menu = *reinterpret_cast<CMenu**>(menuSlot + 0x10C);
			menu->Draw();
			menuSlot += 4;
		}
		DrawInit();
	}
}

/*
 * --INFO--
 * PAL Address: 0x800fb910
 * PAL Size: 1952b
 * EN Address: 0x800FAEB8
 * EN Size: 1952b
 * JP Address: 0x800F7CA4
 * JP Size: 1848b
 */
void CMenuPcs::DrawMainMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	short state = m_wmWorldState->m_mainState;
	float frameAlpha;
	if (state == 0) {
		const double* pRmm1 = &DOUBLE_803314E8;
		frameAlpha = static_cast<float>(*pRmm1 * static_cast<double>(m_wmWorldState->m_frameCounter));
	} else if (state > 0 && state < 4) {
		const float* pOmm1 = &FLOAT_803313e8;
		frameAlpha = *pOmm1;
	} else {
		const double* pRmm2 = &DOUBLE_803314E8;
		const double* pUmm1 = &DOUBLE_80331420;
		frameAlpha = static_cast<float>(-(*pRmm2 * static_cast<double>(m_wmWorldState->m_frameCounter) - *pUmm1));
	}

	DrawWMFrame0(1, frameAlpha);

	if (m_wmWorldState->m_mainState >= 1 && m_wmWorldState->m_mainState <= 3) {
		const int tileState = m_wmWorldState->m_mainState;
		float tileAlpha;
		if (tileState == 1) {
			const double* pRmm3 = &DOUBLE_803314E8;
			tileAlpha = static_cast<float>(*pRmm3 * static_cast<double>(m_wmWorldState->m_frameCounter));
		} else if (tileState == 2) {
			const float* pOmm3 = &FLOAT_803313e8;
			tileAlpha = *pOmm3;
		} else {
			const double* pRmm4 = &DOUBLE_803314E8;
			const double* pUmm2 = &DOUBLE_80331420;
			tileAlpha = static_cast<float>(-(*pRmm4 * static_cast<double>(m_wmWorldState->m_frameCounter) - *pUmm2));
		}
		tileAlpha *= 0.5;
		DrawMainMenuBase(tileAlpha);
	}

	DrawMainMenuSub();
	RestoreProjection();

	if (m_wmWorldState->m_mainState > 0 && m_wmWorldState->m_mainState < 4) {
		const int helpState = m_wmWorldState->m_mainState;
		float helpAlpha;
		if (helpState == 1) {
			const double* pRmm5 = &DOUBLE_803314E8;
			helpAlpha = static_cast<float>(*pRmm5 * static_cast<double>(m_wmWorldState->m_frameCounter));
		} else if (helpState == 2) {
			const float* pOmm8 = &FLOAT_803313e8;
			helpAlpha = *pOmm8;
		} else {
			const double* pRmm6 = &DOUBLE_803314E8;
			const double* pUmm3 = &DOUBLE_80331420;
			helpAlpha = static_cast<float>(-(*pRmm6 * static_cast<double>(m_wmWorldState->m_frameCounter) - *pUmm3));
		}
		const double* pFmm1 = &DOUBLE_803314F0;
		if (static_cast<double>(helpAlpha) > *pFmm1) {
			DrawHelpBase(kMemoryCardBannerTexture, helpAlpha);

#ifdef VERSION_GCCJGC
			char textList[5][256] = {
				"\220\126\202\265\202\242\203\114\203\203\203\211\203\116\203\136\201\133\202\314\215\354\220\254\202\306\203\160\201\133\203\145\203\102\202\314\203\201\203\223\203\157\201\133\202\360\214\210\222\350\202\265\202\334\202\267",
				"\203\121\201\133\203\200\222\206\202\311\217\221\202\253\202\306\202\337\202\347\202\352\202\275\223\372\213\114\202\360\214\251\202\351\202\261\202\306\202\252\202\305\202\253\202\334\202\267",
				"\221\274\202\314\203\201\203\202\203\212\201\133\203\112\201\133\203\150\202\314\203\114\203\203\203\211\203\116\203\136\201\133\202\360\214\273\215\335\202\314\203\146\201\133\203\136\202\311\210\332\223\256\202\265\202\334\202\267",
				"\203\124\203\105\203\223\203\150\202\310\202\307\202\314\212\145\216\355\220\335\222\350\202\360\225\317\215\130\202\265\202\334\202\267",
				"\214\273\215\335\202\314\203\166\203\214\203\103\203\146\201\133\203\136\202\360\203\201\203\202\203\212\201\133\203\112\201\133\203\150\202\311\203\132\201\133\203\165\202\265\202\334\202\267",
			};
#else
			int mesNo = 0;
			char* textList[5] = {0};
			char** mes = g_strWMMenuMes[Game.m_gameWork.GetLanguage() - 1];
			for (int i = 0; i < 5; i++) {
				textList[i] = mes[mesNo++];
			}
#endif
			unsigned int textAlpha;
			if (helpAlpha > FLOAT_803313e8) {
				textAlpha = 0xFF;
			} else {
				textAlpha = static_cast<unsigned int>(static_cast<int>(FLOAT_80331458 * helpAlpha));
			}
#ifdef VERSION_GCCJGC
			DrawFont(static_cast<int>(CalcCenteringPos(textList[m_wmWorldState->m_cardChannel], 22)), 391,
			         CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(textAlpha & 0xFF)).color, 7,
			         textList[m_wmWorldState->m_cardChannel], 1.0f, 1.0f);
#else
			const float* pY = &FLOAT_803317D0;
			DrawFont2(static_cast<int>(CalcCenteringPos2(textList[m_wmWorldState->m_cardChannel], FLOAT_80331594, FLOAT_803313e8)),
			          static_cast<int>(*pY),
			          CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(textAlpha)).color, 7,
			          textList[m_wmWorldState->m_cardChannel], FLOAT_80331594, FLOAT_803313e8, FLOAT_803313e8);
#endif
		}
	}

	if (m_wmWorldState->m_mainState != 2) {
		m_wmWorldState->m_frameCounter++;
		if (m_wmWorldState->m_frameCounter >= 10) {
			m_wmWorldState->m_mainState++;
			m_wmWorldState->m_frameCounter = 0;
			if (m_wmWorldState->m_mainState >= 5) {
				m_wmWorldState->m_changeRequest = m_wmWorldState->m_nextMenuMode;
				m_wmWorldState->m_nextMenuMode = 0;
			}
		}
	} else {
		if (m_wmWorldState->m_mainState == 2 && m_wmWorldState->m_delay != 0) {
			m_wmWorldState->m_delay--;
			if (m_wmWorldState->m_delay <= 0) {
				m_wmWorldState->m_mainState++;
				m_wmWorldState->m_frameCounter = 0;
				Sound.PlaySe(0x31, 0x40, 0x7F, 0);
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800FB440
 * PAL Size: 1232b
 * EN Address: 0x800FA9E8
 * EN Size: 1232b
 * JP Address: 0x800F77C4
 * JP Size: 1248b
 */
void CMenuPcs::DrawDiaryMenu()
{
	m_wm.m_handles[1]->m_model->m_lightAlpha = FLOAT_803313e8;
	{
		SetProjection(1);
		m_wm.m_handles[1]->Draw(5);
		RestoreProjection();
	}

	const int state = m_wmWorldState->m_mainState;
	if (state >= 1 && state <= 3) {
		float alpha;
		if (state == 1) {
			alpha = static_cast<float>(DOUBLE_803314E8 * static_cast<double>(m_wmWorldState->m_frameCounter));
		} else if (state == 2) {
			alpha = FLOAT_803313e8;
		} else {
			alpha = static_cast<float>(-(DOUBLE_803314E8 * static_cast<double>(m_wmWorldState->m_frameCounter) -
			                             DOUBLE_80331420));
		}
		DrawDiaryBase(0, alpha);
	}

	DrawInit();

	DrawPageMark();
}

/*
 * --INFO--
 * PAL Address: 0x800FA1CC
 * PAL Size: 4724b
 * EN Address: 0x800F9774
 * EN Size: 4724b
 * JP Address: 0x800F6498
 * JP Size: 4908b
 */
void CMenuPcs::DrawMCardMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	float cursorX;
	float cursorY;
	short state = m_wmWorldState->m_mainState;
	if (state > 0 && state < 4) {
		float alpha;
		if (state == 1) {
			const double* pRate = &DOUBLE_803314E8;
			alpha = (float)(*pRate * (double)(int)m_wmWorldState->m_frameCounter);
		} else if (state == 2) {
			const float* pOne = &FLOAT_803313e8;
			alpha = *pOne;
		} else {
			const double* pRate = &DOUBLE_803314E8;
			const double* pFull = &DOUBLE_80331420;
			alpha = (float)-(*pRate * (double)(int)m_wmWorldState->m_frameCounter - *pFull);
		}
		const double* pThresh = &DOUBLE_803314F0;
		if (alpha > *pThresh) {
			DrawHelpBase(kMemoryCardBannerTexture, alpha);
		}
	}

	DrawMCList();

	if (m_wmWorldState->m_mainState == 2 && m_wmWorldState->m_subState >= 0x11) {
		cursorY = FLOAT_803314D8;
		cursorX = cursorY;
		cursorY = (float)((double)cursorY - DOUBLE_803317D8);
		cursorX += FLOAT_80331410;
		int saveIdx;
		if (m_wmWorldState->m_subState == 0x11) {
			saveIdx = m_wmWorldState->m_cardChannel;
		} else {
			saveIdx = m_mcCtrl.GetDno();
		}
		cursorX += DOUBLE_80331498 * (double)saveIdx;
		DrawCursor((int)cursorY, (int)cursorX, 1.0f);

		DrawMcObj();
	}

	// State machine for MC operations
	state = m_wmWorldState->m_mainState;
	if (state == 2 && m_wmWorldState->m_delay == 0) {
		short winState;
		short subState = m_wmWorldState->m_subState;
		switch ((int)subState) {
		case 0:
		case 2:
			winState = m_menuWindowInfo->state;
			DrawMcWin(-1, 0);
			if (winState == 1) {
				DrawMcWinMess(0, 0);
#ifdef VERSION_GCCJGC
				float rectX = (float)(m_menuWindowInfo->x + 28) + (float)(m_wmWorldState->m_cardChannel * 124);
				float rectY = (float)(m_menuWindowInfo->y + m_menuWindowInfo->height - 54);
#else
				float rectY = (float)((int)m_menuWindowInfo->y + m_menuWindowInfo->height - 0x3e);
				float rectX = (float)GetSlotABXPos((int)m_wmWorldState->m_cardChannel);
#endif
				DrawCursor((int)rectX, (int)rectY, 1.0f);
			}
			if (winState == 2 && m_menuWindowInfo->state == 3) {
				if (m_wmWorldState->m_state0E < 0) {
					m_wmWorldState->m_nextMenuMode = -1;
					m_wmWorldState->m_delay = 1;
					m_wmTransitionCode = 1;
				} else if (m_wmWorldState->m_subState == 2) {
					m_wmWorldState->m_subState = 3;
				} else {
					m_wmWorldState->m_subState = 1;
				}
			}
			break;
		case 1:
			if (m_wmWorldState->m_frameCounter >= 0x13) {
				m_wmWorldState->m_subState = 3;
			}
			m_wmWorldState->m_frameCounter++;
			break;
		case 3:
			if (m_wmWorldState->m_mcResult != 1) {
				ClrMcList();
				short mcResult = m_wmWorldState->m_mcResult;
				if (mcResult == -1) m_wmWorldState->m_subState = 5;
				else if (mcResult == -2) m_wmWorldState->m_subState = 8;
				else if (mcResult == -3) m_wmWorldState->m_subState = 6;
				else if (mcResult == -4) m_wmWorldState->m_subState = 7;
				else if (mcResult == 0) m_wmWorldState->m_subState = 4;
			}
			break;
		case 5:
		case 6:
		case 7:
		case 9:
		case 10:
		case 0x0E:
		case 0x0F:
		case 0x14:
		case 0x15:
		case 0x1B:
		case 0x1C:
			winState = m_menuWindowInfo->state;
			DrawMcWin(-1, 0);
			if (winState == 1) {
				int msgParam = 0;
				int msgId;
				short ss = m_wmWorldState->m_subState;
				if (ss == 5) msgId = 1;
				else if (ss == 6) msgId = 2;
				else if (ss == 7) msgId = 3;
				else if (ss == 9) msgId = 10;
				else if (ss == 10) msgId = 0xb;
				else if (ss == 0x0E) msgId = 0xc;
				else if (ss == 0x0F) msgId = 0xd;
				else if (ss == 0x1C) { msgId = 0x1b; msgParam = 1; }
				else if (ss == 0x1B) { msgId = 0x1c; msgParam = 1; }
				else if (ss == 0x15) msgId = 0xe;
				else msgId = 0xf;
				DrawMcWinMess(msgId, msgParam);
			}
			if (winState == 2 && m_menuWindowInfo->state == 3) {
				short ss = m_wmWorldState->m_subState;
				if (m_wmWorldState->m_state0E < 0 || ss == 0x14 || ss == 0x1c || ss == 0x1b) {
					m_wmWorldState->m_subState = 3;
				} else if (ss == 0x0E) {
					ClrMcList();
					m_wmWorldState->m_subState = 0x11;
					m_wmWorldState->m_cardChannel = 0;
				} else if (ss == 0x15) {
					m_wmWorldState->m_subState = 0x11;
					m_wmWorldState->m_cardChannel = (short)m_mcCtrl.GetDno();
					if (m_wmWorldState->m_menuMode == 8) {
						m_wmWorldState->m_nextMenuMode = -1;
						m_wmWorldState->m_delay = 0xb;
						m_wmTransitionCode = 3;
					}
				} else {
					m_wmWorldState->m_subState = 2;
				}
			}
			break;
		case 4:
			winState = m_menuWindowInfo->state;
			DrawMcWin(-1, 0);
			if (winState == 1) {
				DrawMcWinMess(6, 0);
				short r = m_wmWorldState->m_mcResult;
				if (r != 0 && r == 1) {
					m_wmWorldState->m_subState = 0xc;
				}
			} else if (winState == 2 && m_menuWindowInfo->state == 3) {
				short mcRes = m_wmWorldState->m_mcResult;
				if (mcRes == -2) m_wmWorldState->m_subState = 9;
				else if (mcRes == -3) m_wmWorldState->m_subState = 8;
				else if (mcRes == -4) m_wmWorldState->m_subState = 8;
				else if (mcRes == -5) m_wmWorldState->m_subState = 7;
				else m_wmWorldState->m_subState = 10;
			}
			break;
		case 8:
		case 0x0B:
		case 0x12:
		case 0x19:
			winState = m_menuWindowInfo->state;
			DrawMcWin(-1, 0);
			if (winState == 1) {
				int msgParam = 0;
#ifdef VERSION_GCCJGC
				int msgId;
				float rectX;
				short ss = m_wmWorldState->m_subState;
				if (ss == 8) { msgId = 4; rectX = (float)(m_menuWindowInfo->x + 72); }
				else if (ss == 0x0B) { msgId = 5; rectX = (float)(m_menuWindowInfo->x + 83); }
				else if (ss == 0x19) { msgId = 0x19; msgParam = 1; rectX = (float)(m_menuWindowInfo->x + 55); }
				else { msgId = 0x12; rectX = (float)(m_menuWindowInfo->x + 77); }
				DrawMcWinMess(msgId, msgParam);
				rectX += (float)(m_wmWorldState->m_cardChannel * 80);
				float rectY = (float)(m_menuWindowInfo->y + m_menuWindowInfo->height - 54);
#else
				int msgId;
				short ss = m_wmWorldState->m_subState;
				if (ss == 8) msgId = 4;
				else if (ss == 0x0B) msgId = 5;
				else if (ss == 0x19) { msgId = 0x19; msgParam = 1; }
				else msgId = 0x12;
				DrawMcWinMess(msgId, msgParam);
				float rectY = (float)((int)m_menuWindowInfo->y + m_menuWindowInfo->height - 0x3e);
				float rectX = (float)GetYesNoXPos((int)m_wmWorldState->m_cardChannel);
#endif
				if (m_wmWorldState->m_subState != 0x19) {
					DrawCursor((int)rectX, (int)rectY, 1.0f);
				} else {
					short ss2 = m_wmWorldState->m_mcResult;
					if (ss2 < 0) {
						if (ss2 == -1) m_wmWorldState->m_subState = 5;
						else if (ss2 == -2) m_wmWorldState->m_subState = 8;
						else if (ss2 == -3) m_wmWorldState->m_subState = 6;
						else m_wmWorldState->m_subState = 7;
					}
				}
			}
			if (winState == 2 && m_menuWindowInfo->state == 3) {
				short ss = m_wmWorldState->m_subState;
				if (ss == 0x12) {
					if (m_wmWorldState->m_state0E < 0) {
						m_wmWorldState->m_subState = 0x11;
						m_wmWorldState->m_cardChannel = (short)m_mcCtrl.GetDno();
					} else {
						m_wmWorldState->m_subState = 0x13;
					}
				} else {
					short ss2 = m_wmWorldState->m_mcResult;
					if (ss2 < 0) {
						if (ss2 == -1) m_wmWorldState->m_subState = 5;
						else if (ss2 == -2) m_wmWorldState->m_subState = 8;
						else if (ss2 == -3) m_wmWorldState->m_subState = 6;
						else m_wmWorldState->m_subState = 7;
					} else if (m_wmWorldState->m_state0E < 0) {
						if (ss == 0x19) {
							m_wmWorldState->m_subState = 0x11;
							m_wmWorldState->m_cardChannel = (short)m_mcCtrl.GetDno();
						} else {
							m_wmWorldState->m_subState = 2;
						}
					} else if (ss == 8) {
						m_wmWorldState->m_subState = 0xb;
					} else if (ss == 0x19) {
						m_wmWorldState->m_subState = 0x1a;
					} else {
						m_wmWorldState->m_subState = 0xd;
					}
				}
			}
			break;
		case 0x0D:
		case 0x13:
		case 0x1A:
			winState = m_menuWindowInfo->state;
			DrawMcWin(-1, 0);
			if (winState == 1) {
				int msgParam = 0;
				int msgId;
				short ss = m_wmWorldState->m_subState;
				if (ss == 0xd) msgId = 7;
				else if (ss == 0x1A) { msgId = 0x1a; msgParam = 1; }
				else msgId = 8;
				DrawMcWinMess(msgId, msgParam);
			} else if (winState == 2 && m_menuWindowInfo->state == 3) {
				short ss = m_wmWorldState->m_subState;
				if (ss == 0xd) {
					if (m_wmWorldState->m_mcResult == 1) {
						m_wmWorldState->m_subState = 0xe;
					} else if (m_wmWorldState->m_mcResult == -2) {
						m_wmWorldState->m_subState = 7;
					} else {
						m_wmWorldState->m_subState = 0xf;
					}
				} else if (ss == 0x1a) {
					if (m_wmWorldState->m_mcResult == 1) {
						m_wmWorldState->m_subState = 0x1c;
					} else if (m_wmWorldState->m_mcResult == -2) {
						m_wmWorldState->m_subState = 7;
					} else {
						m_wmWorldState->m_subState = 0x1b;
					}
				} else if (m_wmWorldState->m_mcResult == 1) {
					m_wmWorldState->m_flag0A = 1;
					m_wmWorldState->m_subState = 0x15;
					Sound.PlaySe(0x41, 0x40, 0x7F, 0);
				} else if (m_wmWorldState->m_mcResult == -4) {
					m_wmWorldState->m_subState = 7;
				} else {
					m_wmWorldState->m_subState = 0x14;
				}
			}
			break;
		case 0x0C:
			winState = m_menuWindowInfo->state;
			DrawMcWin(-1, 0);
			if (((winState != 1 ||
			      (DrawMcWinMess(6, 0), m_wmWorldState->m_mcResult != 0)) && winState == 2) &&
			    m_menuWindowInfo->state == 3) {
				short cRes = m_wmWorldState->m_mcResult;
				if (cRes == -1) m_wmWorldState->m_subState = 10;
				else if (cRes == -2) m_wmWorldState->m_subState = 8;
				else if (cRes == -3) m_wmWorldState->m_subState = 8;
				else if (cRes == -4) m_wmWorldState->m_subState = 7;
				else if (cRes == -999) {
					m_wmWorldState->m_nextMenuMode = -1;
					m_wmWorldState->m_delay = 1;
					m_wmTransitionCode = 2;
				} else {
					BindMcObj();
					unsigned int idx;
					for (idx = 0; idx < kMcListCount; idx++) {
						if (m_wmCharaState[idx].m_isBroken != 0) {
							break;
						}
					}
					int brokenIdx = idx;
					if (brokenIdx < 4) {
						m_wmWorldState->m_subState = 0x19;
					} else {
						m_wmWorldState->m_subState = 0x11;
					}
					m_wmWorldState->m_cardChannel = (short)m_mcCtrl.GetDno();
				}
			}
			break;
		case 0x11:
			if (m_wmWorldState->m_mcResult < 0) {
				m_wmWorldState->m_subState = 3;
			} else if (m_wmWorldState->m_state0E != 0) {
				if (m_wmWorldState->m_state0E < 0) {
					if (m_wmWorldState->m_flag0A == 0) {
						m_wmWorldState->m_subState = 2;
					} else {
						m_wmWorldState->m_nextMenuMode = -1;
						m_wmWorldState->m_delay = 10;
					}
				} else if (m_wmCharaState[m_mcCtrl.GetDno()].m_hasData == 0) {
					m_wmWorldState->m_subState = 0x13;
				} else {
					m_wmWorldState->m_subState = 0x12;
				}
			}
			break;
		}
		if ((int)subState != (int)m_wmWorldState->m_subState) {
			m_wmWorldState->m_flag09 = 0;
			m_wmWorldState->m_counter1A = 0;
			m_wmWorldState->m_state0E = 0;
		}
	} else if (state != 2) {
		m_wmWorldState->m_frameCounter++;
		int threshold;
		if (m_wmWorldState->m_mainState == 3 && m_wmWorldState->m_subState != 0) {
			threshold = 0x13;
		} else {
			threshold = 10;
		}
		if (m_wmWorldState->m_frameCounter >= threshold) {
			m_wmWorldState->m_mainState++;
			m_wmWorldState->m_frameCounter = 0;
			if (m_wmWorldState->m_mainState >= 5) {
				m_wmWorldState->m_changeRequest = m_wmWorldState->m_nextMenuMode;
				m_wmWorldState->m_nextMenuMode = 0;
			}
		}
	} else if (state == 2 && m_wmWorldState->m_delay != 0) {
		m_wmWorldState->m_delay--;
		if (m_wmWorldState->m_delay <= 0) {
			m_wmWorldState->m_mainState++;
			m_wmWorldState->m_frameCounter = 0;
			Sound.PlaySe(0x32, 0x40, 0x7F, 0);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800f98bc
 * PAL Size: 2320b
 * EN Address: 0x800F8E60
 * EN Size: 2324b
 * JP Address: 0x800F5C18
 * JP Size: 2176b
 */
void CMenuPcs::DrawCMakeMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	short state = m_wmWorldState->m_mainState;
	float frameAlpha;
	if (state == 0) {
		const double* pRate = &DOUBLE_803314E8;
		frameAlpha = static_cast<float>(*pRate * static_cast<double>(m_wmWorldState->m_frameCounter));
	} else if (state == 1) {
		const double* pRate = &DOUBLE_80331460;
		const double* pOne = &DOUBLE_80331420;
		frameAlpha = static_cast<float>(-(*pRate * static_cast<double>(m_wmWorldState->m_frameCounter) - *pOne));
	} else if (state == 2) {
		const float* pHalf = &FLOAT_80331434;
		frameAlpha = *pHalf;
	} else if (state == 3) {
		const double* pRate = &DOUBLE_80331460;
		const double* pHalf = &DOUBLE_803313F8;
		frameAlpha = static_cast<float>(*pRate * static_cast<double>(m_wmWorldState->m_frameCounter) + *pHalf);
	} else {
		const double* pRate = &DOUBLE_803314E8;
		const double* pOne = &DOUBLE_80331420;
		frameAlpha = static_cast<float>(-(*pRate * static_cast<double>(m_wmWorldState->m_frameCounter) - *pOne));
	}

	DrawWMFrame0(3, frameAlpha);

	short contentState;
	WmWorldState* const contentWS = m_wmWorldState;
	contentState = contentWS->m_mainState;
	if (contentState > 0 && contentState < 4) {
		float contentAlpha;
		if (contentState == 1) {
			const double* pRate2 = &DOUBLE_803314E8;
			contentAlpha = static_cast<float>(*pRate2 * static_cast<double>(contentWS->m_frameCounter));
		} else if (contentState == 2) {
			const float* pOne2 = &FLOAT_803313e8;
			contentAlpha = *pOne2;
		} else {
			const double* pRate2 = &DOUBLE_803314E8;
			const double* pOne2 = &DOUBLE_80331420;
			contentAlpha = static_cast<float>(-(*pRate2 * static_cast<double>(contentWS->m_frameCounter) - *pOne2));
		}

		DrawCharaBase();
		DrawChara();
		RestoreProjection();
		DrawCharaName();
		DrawCMLife();

		if (m_wmWorldState->m_menuMode == 3) {
			short winState = m_menuWindowInfo->state;
			if (winState != 3) {
				DrawMcWin(-1, 0);
				if (winState == 0 && m_menuWindowInfo->state == 1) {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				}
				if (m_menuWindowInfo->state == 1) {
					DrawMcWinMess(0x17, 1);
				}
			}
		}

		int textAlpha;
		const float* pOneCmp = &FLOAT_803313e8;
		if (contentAlpha > *pOneCmp) {
			textAlpha = 0xFF;
		} else {
			const float* p255 = &FLOAT_80331458;
			textAlpha = static_cast<int>(*p255 * contentAlpha);
		}
		DrawHelpBase(kMemoryCardBannerTexture, contentAlpha);
		if (m_wmWorldState->m_menuMode == 3) {
			if (m_wmWorldState->m_menuMode == 3) {
#ifdef VERSION_GCCJGC
			char textList[3][256] = {
				"\x83\x70\x81\x5B\x83\x65\x83\x42\x82\xCC\x83\x81\x83\x93\x83\x6F\x81\x5B\x82\xF0\x8C\x88\x82\xDF\x82\xC4\x82\xAD\x82\xBE\x82\xB3\x82\xA2",
				"\x81\x75\x82\xC8\x82\xB5\x81\x76\x82\xF0\x91\x49\x82\xD4\x82\xC6\x83\x4C\x83\x83\x83\x89\x83\x4E\x83\x5E\x81\x5B\x82\xF0\x8D\xEC\x90\xAC\x82\xB5\x82\xDC\x82\xB7",
				"\x83\x81\x83\x93\x83\x6F\x81\x5B\x82\xAA\x8C\x88\x82\xDC\x82\xC1\x82\xBD\x82\xE7\x83\x58\x83\x5E\x81\x5B\x83\x67\x83\x7B\x83\x5E\x83\x93\x82\xF0\x89\x9F\x82\xB5\x82\xC4\x82\xAD\x82\xBE\x82\xB3\x82\xA2"
			};
			const int textIndex = m_wmHelpTimer / 90;
			DrawFont(static_cast<int>(CalcCenteringPos(textList[textIndex], 22)), 391,
			         CColor(255, 255, 255, static_cast<unsigned char>(textAlpha)).color,
			         7, textList[textIndex], 1.0f, 1.0f);
#else
			int mesNo = 5;
			const int textIndex = static_cast<int>(m_wmHelpTimer / 0x4B);
			char** mes = g_strWMMenuMes[Game.m_gameWork.GetLanguage() - 1];
			char* textList[3] = {0};
			for (int i = 0; i < 3; i++) {
				textList[i] = mes[mesNo++];
			}
			const float* pY = &FLOAT_803317D0;
			DrawFont2(static_cast<int>(CalcCenteringPos2(textList[textIndex], FLOAT_80331594, FLOAT_803313e8)),
			          static_cast<int>(*pY),
			          CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(textAlpha)).color, 7,
			          textList[textIndex], FLOAT_80331594, FLOAT_803313e8, FLOAT_803313e8);
#endif
			}
		} else if (m_wmWorldState->m_menuMode == 8) {
			const int mainMode = g_pGoOutMenu->m_mainMode;
			switch (mainMode) {
			case 2:
				switch (g_pGoOutMenu->m_goOutMode) {
				case 0x0E: {
#ifdef VERSION_GCCJGC
					char text[256] = "\x83\x8D\x81\x5B\x83\x68\x82\xB7\x82\xE9\x83\x66\x81\x5B\x83\x5E\x82\xF0\x91\x49\x82\xF1\x82\xC5\x82\xAD\x82\xBE\x82\xB3\x82\xA2";
					MenuPcs.DrawFont(static_cast<int>(MenuPcs.CalcCenteringPos(text, 22)), 391,
					                 CColor(255, 255, 255, static_cast<unsigned char>(textAlpha)).color,
					                 7, text, 1.0f, 1.0f);
#else
					int mesNo = 8;
					const int languageIndex = Game.m_gameWork.GetLanguage() - 1;
					char* text = g_strWMMenuMes[languageIndex][mesNo++];
					const float* pY = &FLOAT_803317D0;
					MenuPcs.DrawFont2(static_cast<int>(MenuPcs.CalcCenteringPos2(text, FLOAT_80331594, FLOAT_803313e8)),
					                  static_cast<int>(*pY),
					                  CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(textAlpha)).color, 7, text,
					                  FLOAT_80331594, FLOAT_803313e8, FLOAT_803313e8);
#endif
					break;
				}
				case 0x0F: {
#ifdef VERSION_GCCJGC
					char text[256] = "\x88\xDA\x93\xAE\x82\xB7\x82\xE9\x83\x4C\x83\x83\x83\x89\x83\x4E\x83\x5E\x81\x5B\x82\xF0\x91\x49\x82\xF1\x82\xC5\x82\xAD\x82\xBE\x82\xB3\x82\xA2";
					MenuPcs.DrawFont(static_cast<int>(MenuPcs.CalcCenteringPos(text, 22)), 391,
					                 CColor(255, 255, 255, static_cast<unsigned char>(textAlpha)).color,
					                 7, text, 1.0f, 1.0f);
#else
					int mesNo = 9;
					const int languageIndex = Game.m_gameWork.GetLanguage() - 1;
					char* text = g_strWMMenuMes[languageIndex][mesNo++];
					const float* pY = &FLOAT_803317D0;
					MenuPcs.DrawFont2(static_cast<int>(MenuPcs.CalcCenteringPos2(text, FLOAT_80331594, FLOAT_803313e8)),
					                  static_cast<int>(*pY),
					                  CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(textAlpha)).color, 7, text,
					                  FLOAT_80331594, FLOAT_803313e8, FLOAT_803313e8);
#endif
					break;
				}
				}
				break;
			case 3:
				switch (g_pGoOutMenu->m_deleteMode) {
				case 2: {
#ifdef VERSION_GCCJGC
					char text[256] = "\x8D\xED\x8F\x9C\x82\xB7\x82\xE9\x83\x4C\x83\x83\x83\x89\x83\x4E\x83\x5E\x81\x5B\x82\xF0\x91\x49\x82\xF1\x82\xC5\x82\xAD\x82\xBE\x82\xB3\x82\xA2";
					MenuPcs.DrawFont(static_cast<int>(MenuPcs.CalcCenteringPos(text, 22)), 391,
					                 CColor(255, 255, 255, static_cast<unsigned char>(textAlpha)).color,
					                 7, text, 1.0f, 1.0f);
#else
					int mesNo = 10;
					const int languageIndex = Game.m_gameWork.GetLanguage() - 1;
					char* text = g_strWMMenuMes[languageIndex][mesNo++];
					const float* pY = &FLOAT_803317D0;
					MenuPcs.DrawFont2(static_cast<int>(MenuPcs.CalcCenteringPos2(text, FLOAT_80331594, FLOAT_803313e8)),
					                  static_cast<int>(*pY),
					                  CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(textAlpha)).color, 7, text,
					                  FLOAT_80331594, FLOAT_803313e8, FLOAT_803313e8);
#endif
					break;
				}
				}
				break;
			}
		}
	}

	if (m_wmWorldState->m_mainState != 2) {
		m_wmWorldState->m_frameCounter++;
		if (m_wmWorldState->m_frameCounter >= 10) {
			m_wmWorldState->m_mainState++;
			m_wmWorldState->m_frameCounter = 0;
			if (m_wmWorldState->m_mainState >= 5) {
				m_wmWorldState->m_changeRequest = m_wmWorldState->m_nextMenuMode;
				m_wmWorldState->m_nextMenuMode = 0;
			}
		}
	} else if (m_wmWorldState->m_mainState == 2) {
		if (m_wmWorldState->m_delay != 0) {
			m_wmWorldState->m_delay--;
			if (m_wmWorldState->m_delay <= 0) {
				m_wmWorldState->m_mainState++;
				m_wmWorldState->m_frameCounter = 0;
				Sound.PlaySe(0x31 + (m_wmWorldState->m_nextMenuMode < 0), 0x40, 0x7F, 0);
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800f9248
 * PAL Size: 1652b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawMoveMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	{
		short state = m_wmWorldState->m_mainState;
		if ((state == 0) && bytes[0x12] == 0) {
			return;
		}
		if (state > 3) {
			return;
		}
	}

	DrawFukidashi();
	short state = m_wmWorldState->m_mainState;
	float moveAlpha;
	if (state == 1) {
		moveAlpha = static_cast<float>(static_cast<double>(m_wmWorldState->m_frameCounter) / DOUBLE_803316E8);
	} else if (state == 2 && bytes[0x13] != 0) {
		moveAlpha = static_cast<float>(DOUBLE_80331420 - static_cast<double>(m_wmWorldState->m_frameCounter) / DOUBLE_803316E8);
	} else {
		moveAlpha = FLOAT_803313e8;
	}
	if (state > 0 && state < 3) {
		DrawHelpBase(0x23, moveAlpha);
	}
	DrawWMFrame();

	if (m_wmWorldState->m_mainState > 0 && m_wmWorldState->m_mainState < 3) {
		SetProjection(5);
		SetLight(0);

		{
			m_effectWork[5].m_object.m_currentAlpha = m_wm.m_handles[5]->m_model->m_lightAlpha;
			m_wm.m_handles[5]->Draw(5);
			pppFVECTOR4 color;
			const short partColorIndex = m_crystalPart;
			PartPcs.GetParColIdx(partColorIndex, color);
			color.w = m_wm.m_handles[5]->m_model->m_lightAlpha;
			PartPcs.SetParColIdx(partColorIndex, color);
			if (m_effectTimer == 0) {
				m_effectTimer = 1;
			} else {
				PartPcs.DrawMenu(m_crystalAttr);
			}
		}

		RestoreProjection();
	}

	if (m_wmWorldState->m_mainState != 2 || bytes[0x13] != 0) {
		m_wmWorldState->m_frameCounter++;
	}

	if (m_wmWorldState->m_mainState == 0 ||
	    (m_wmWorldState->m_mainState == 2 && bytes[0x13] != 0)) {
		if (static_cast<double>(m_wmWorldState->m_posX) <= DOUBLE_803314F0) {
			m_wmWorldState->m_mainState++;
			m_wm.m_frameData->m_titleFrame = 0;
			m_wm.m_frameData->m_yearFrame = 0;
			m_wmWorldState->m_frameCounter = 0;
		}
	} else if (m_wmWorldState->m_mainState == 1 && m_wmWorldState->m_frameCounter >= 10) {
		m_wmWorldState->m_mainState++;
		m_wmWorldState->m_frameCounter = 0;
		CallWorldParam(3, 0, 0);
	} else if (m_wmWorldState->m_mainState == 2 && m_wmWorldState->m_frameCounter >= 10) {
		m_wmWorldState->m_mainState++;
		m_wmWorldState->m_frameCounter = 0;
	} else if (m_wmWorldState->m_mainState == 3 && m_wmWorldState->m_frameCounter >= 10) {
		m_wmWorldState->m_mainState++;
		m_wmWorldState->m_frameCounter = 0;
		CallWorldParam(4, 0, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800F7EFC
 * PAL Size: 4940b
 * EN Address: 0x800F74A0
 * EN Size: 4940b
 * JP Address: 0x800F41D8
 * JP Size: 5064b
 */
void CMenuPcs::DrawLoadMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	McCtrl& mcCtrl = *GetMcCtrl();
	if ((signed char)m_wmWorldState->m_worldReady == 0) {
		return;
	}

	short state = m_wmWorldState->m_mainState;
	float cursorXbase;
	float cursorY0;
	float alpha;
	if (state > 0 && state < 4) {
		if (state == 1) {
			alpha = static_cast<float>(DOUBLE_803314E8 * static_cast<double>(m_wmWorldState->m_frameCounter));
		} else if (state == 2) {
			alpha = FLOAT_803313e8;
		} else {
			alpha = static_cast<float>(-(DOUBLE_803314E8 * static_cast<double>(m_wmWorldState->m_frameCounter) - DOUBLE_80331420));
		}
		if (static_cast<double>(alpha) > DOUBLE_803314F0) {
			DrawHelpBase(kMemoryCardBannerTexture, alpha);
		}
	}
	if (alpha < FLOAT_803313dc) alpha = FLOAT_803313dc;

	unsigned int uAlpha;
	if (alpha > FLOAT_803313e8) {
		uAlpha = 0xFF;
	} else {
		uAlpha = static_cast<int>(FLOAT_80331458 * alpha);
	}

	// Header text
#ifdef VERSION_GCCJGC
	switch (g_pGoOutMenu->m_goOutMode) {
	case 0x0E: {
		char text[256] = "\203\215\201\133\203\150\202\267\202\351\203\146\201\133\203\136\202\360\221\111\202\361\202\305\202\255\202\276\202\263\202\242";
		MenuPcs.DrawFont(static_cast<int>(MenuPcs.CalcCenteringPos(text, 22)), 391,
		                  CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(uAlpha)).color,
		                  7, text, 1.0f, 1.0f);
		break;
	}
	}
#else
	switch (g_pGoOutMenu->m_goOutMode) {
	case 0x0E: {
		int mesNo = 8;
		const int languageIndex = Game.m_gameWork.GetLanguage() - 1;
		char* text = g_strWMMenuMes[languageIndex][mesNo++];
		const float* pY = &FLOAT_803317D0;
		MenuPcs.DrawFont2(static_cast<int>(MenuPcs.CalcCenteringPos2(text, FLOAT_80331594, FLOAT_803313e8)),
		                  static_cast<int>(*pY),
		                  CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(uAlpha)).color, 7, text,
		                  FLOAT_80331594, FLOAT_803313e8, FLOAT_803313e8);
		break;
	}
	}
#endif

	DrawMCList();

	// Cursor / selection rendering
	state = m_wmWorldState->m_mainState;
	if (state == 2 && m_wmWorldState->m_subState >= 0x11) {
		cursorY0 = FLOAT_803314D8;
		cursorXbase = cursorY0;
		cursorY0 = static_cast<float>(static_cast<double>(cursorY0) - DOUBLE_803317D8);
		cursorXbase += FLOAT_80331410;
		int saveIdx;
		if (m_wmWorldState->m_subState == 0x11) {
			saveIdx = m_wmWorldState->m_cardChannel;
		} else {
			saveIdx = mcCtrl.m_saveIndex;
		}
		cursorXbase += DOUBLE_80331498 * static_cast<double>(saveIdx);
		DrawCursor((int)cursorY0, (int)cursorXbase, 1.0f);

		DrawMcObj();
	}

	// State machine for MC operations
	state = m_wmWorldState->m_mainState;
	if (state == 2 && m_wmWorldState->m_delay == 0) {
		short subState = m_wmWorldState->m_subState;
		short winState;
		switch ((int)subState) {
		case 0:
		case 2:
			winState = m_menuWindowInfo->state;
			DrawMcWin(-1, 0);
			if (winState == 1) {
				DrawMcWinMess(0, 0);
#ifdef VERSION_GCCJGC
				float slotX = (float)(m_menuWindowInfo->x + 28) + (float)(m_wmWorldState->m_cardChannel * 124);
				float slotY = (float)(m_menuWindowInfo->y + m_menuWindowInfo->height - 54);
#else
				float slotY = (float)((int)m_menuWindowInfo->y + m_menuWindowInfo->height - 0x3e);
				float slotX = (float)GetSlotABXPos(m_wmWorldState->m_cardChannel);
#endif
				DrawCursor((int)slotX, (int)slotY, 1.0f);
			}
			if (winState == 2 && m_menuWindowInfo->state == 3) {
				if (m_wmWorldState->m_state0E < 0) {
					m_wmWorldState->m_nextMenuMode = -1;
					m_wmWorldState->m_delay = 1;
					m_wmTransitionCode = 1;
				} else if (m_wmWorldState->m_subState == 2) {
					m_wmWorldState->m_subState = 3;
				} else {
					m_wmWorldState->m_subState = 1;
				}
			}
			break;
		case 1:
			if (m_wmWorldState->m_frameCounter >= 0x13) {
				m_wmWorldState->m_subState = 3;
			}
			m_wmWorldState->m_frameCounter++;
			break;
		case 3:
			if (m_wmWorldState->m_mcResult != 1) {
				ClrMcList();
				short mcResult = m_wmWorldState->m_mcResult;
				if (mcResult == -1) {
					m_wmWorldState->m_subState = 5;
				} else if (mcResult == -2) {
					m_wmWorldState->m_subState = 8;
				} else if (mcResult == -3) {
					m_wmWorldState->m_subState = 6;
				} else if (mcResult == -4) {
					m_wmWorldState->m_subState = 7;
				} else if (mcResult == 0) {
					m_wmWorldState->m_subState = 4;
				}
			}
			break;
		case 5:
		case 6:
		case 7:
		case 10:
		case 0x0E:
		case 0x0F:
		case 0x10:
		case 0x17:
		case 0x18:
		case 0x1B:
		case 0x1C:
			winState = m_menuWindowInfo->state;
			DrawMcWin(-1, 0);
			if (winState == 1) {
				int msgId = 0;
				int msgParam = 0;
				short ss = m_wmWorldState->m_subState;
				if (ss == 5) msgId = 1;
				else if (ss == 6) msgId = 2;
				else if (ss == 7) msgId = 3;
				else if (ss == 10) msgId = 0xB;
				else if (ss == 0x0E) msgId = 0xC;
				else if (ss == 0x0F) msgId = 0xD;
				else if (ss == 0x1C) { msgId = 0x1B; msgParam = 1; }
				else if (ss == 0x1B) { msgId = 0x1C; msgParam = 1; }
				else if (ss == 0x18) msgId = 0x10;
				else if (ss == 0x17) msgId = 0x11;
				else msgId = 0x13;
				DrawMcWinMess(msgId, msgParam);
			}
			if (winState == 2 && m_menuWindowInfo->state == 3) {
				if (m_wmWorldState->m_state0E < 0 ||
				    m_wmWorldState->m_subState == 0x1C || m_wmWorldState->m_subState == 0x1B ||
				    m_wmWorldState->m_subState == 0x17) {
					m_wmWorldState->m_subState = 3;
				} else if (subState == 0x18) {
					m_wmWorldState->m_nextMenuMode = 1;
					m_wmWorldState->m_delay = 1;
					m_wmTransitionCode = 4;
				} else if (m_wmWorldState->m_menuMode == 8 && m_goOutSaveLoadMode != 0) {
					m_wmWorldState->m_nextMenuMode = 1;
					m_wmWorldState->m_delay = 1;
					m_wmTransitionCode = 2;
				} else {
					m_wmWorldState->m_subState = 2;
				}
			}
			break;
		case 4:
			winState = m_menuWindowInfo->state;
			DrawMcWin(-1, 0);
			if (winState == 1) {
				DrawMcWinMess(6, 0);
				short cRes4 = m_wmWorldState->m_mcResult;
				if (cRes4 != 0 && cRes4 == 1) {
					m_wmWorldState->m_subState = 0xC;
				}
			} else if (winState == 2 && m_menuWindowInfo->state == 3) {
				short mcRes2 = m_wmWorldState->m_mcResult;
				if (mcRes2 == -3) {
					m_wmWorldState->m_subState = 8;
				} else if (mcRes2 == -4) {
					m_wmWorldState->m_subState = 8;
				} else if (mcRes2 == -5) {
					m_wmWorldState->m_subState = 7;
				} else if (mcRes2 == -6) {
					m_wmWorldState->m_subState = 0x10;
				} else {
					m_wmWorldState->m_subState = 10;
				}
			}
			break;
		case 8:
		case 0x0B:
		case 0x19:
			winState = m_menuWindowInfo->state;
			DrawMcWin(-1, 0);
			if (winState == 1) {
				int ymsgId = 0;
				int ymsgParam = 0;
#ifdef VERSION_GCCJGC
				float ynX;
				short ys = m_wmWorldState->m_subState;
				if (ys == 8) { ymsgId = 4; ynX = (float)(m_menuWindowInfo->x + 72); }
				else if (ys == 0x19) { ymsgId = 0x19; ymsgParam = 1; ynX = (float)(m_menuWindowInfo->x + 55); }
				else { ymsgId = 5; ynX = (float)(m_menuWindowInfo->x + 83); }
				DrawMcWinMess(ymsgId, ymsgParam);
				ynX += (float)(m_wmWorldState->m_cardChannel * 80);
				float ynY = (float)(m_menuWindowInfo->y + m_menuWindowInfo->height - 54);
#else
				short ys = m_wmWorldState->m_subState;
				if (ys == 8) ymsgId = 4;
				else if (ys == 0x19) { ymsgId = 0x19; ymsgParam = 1; }
				else ymsgId = 5;
				DrawMcWinMess(ymsgId, ymsgParam);

				// Yes/No cursor
				float ynY = (float)((int)m_menuWindowInfo->y + m_menuWindowInfo->height - 0x3e);
				float ynX = (float)GetYesNoXPos(m_wmWorldState->m_cardChannel);
#endif
				if (m_wmWorldState->m_subState != 0x19) {
					DrawCursor((int)ynX, (int)ynY, 1.0f);
				} else {
					short ynResult0 = m_wmWorldState->m_mcResult;
					if (ynResult0 < 0) {
						if (ynResult0 == -1) m_wmWorldState->m_subState = 5;
						else if (ynResult0 == -2) m_wmWorldState->m_subState = 8;
						else if (ynResult0 == -3) m_wmWorldState->m_subState = 6;
						else m_wmWorldState->m_subState = 7;
					}
				}
			}
			if (winState == 2 && m_menuWindowInfo->state == 3) {
				short ynResult = m_wmWorldState->m_mcResult;
				if (ynResult < 0) {
					if (ynResult == -1) m_wmWorldState->m_subState = 5;
					else if (ynResult == -2) m_wmWorldState->m_subState = 8;
					else if (ynResult == -3) m_wmWorldState->m_subState = 6;
					else m_wmWorldState->m_subState = 7;
				} else if (m_wmWorldState->m_state0E < 0) {
					if (m_wmWorldState->m_subState == 0x19) {
						m_wmWorldState->m_subState = 0x11;
						m_wmWorldState->m_cardChannel = (short)mcCtrl.m_saveIndex;
					} else if (m_wmWorldState->m_menuMode == 8 && m_goOutSaveLoadMode != 0) {
						m_wmWorldState->m_nextMenuMode = 1;
						m_wmWorldState->m_delay = 1;
						ClrMcList();
						m_wmTransitionCode = 1;
					} else {
						m_wmWorldState->m_subState = 2;
					}
				} else if (m_wmWorldState->m_subState == 8) {
					m_wmWorldState->m_subState = 0x0B;
				} else if (m_wmWorldState->m_subState == 0x19) {
					m_wmWorldState->m_subState = 0x1A;
				} else {
					m_wmWorldState->m_subState = 0x0D;
				}
			}
			break;
		case 0x0D:
		case 0x16:
		case 0x1A:
			winState = m_menuWindowInfo->state;
			DrawMcWin(-1, 0);
			if (winState == 1) {
				int dmsgId = 7;
				int dmsgParam = 0;
				short ds = m_wmWorldState->m_subState;
				if (ds == 0x0D) dmsgId = 7;
				else if (ds == 0x1A) { dmsgId = 0x1A; dmsgParam = 1; }
				else dmsgId = 9;
				DrawMcWinMess(dmsgId, dmsgParam);
			} else if (winState == 2 && m_menuWindowInfo->state == 3) {
				if (m_wmWorldState->m_subState == 0x0D) {
					short dRes = m_wmWorldState->m_mcResult;
					if (dRes == 1) m_wmWorldState->m_subState = 0x0E;
					else if (dRes == -2) m_wmWorldState->m_subState = 7;
					else m_wmWorldState->m_subState = 0x0F;
				} else if (subState == 0x1A) {
					short dRes = m_wmWorldState->m_mcResult;
					if (dRes == 1) m_wmWorldState->m_subState = 0x1C;
					else if (dRes == -2) m_wmWorldState->m_subState = 7;
					else m_wmWorldState->m_subState = 0x1B;
				} else {
					short dRes = m_wmWorldState->m_mcResult;
					if (dRes == 1) {
						m_wmWorldState->m_subState = 0x18;
						Sound.PlaySe(0x42, 0x40, 0x7F, 0);
					} else if (dRes == -4) m_wmWorldState->m_subState = 7;
					else m_wmWorldState->m_subState = 0x17;
				}
			}
			break;
		case 0x0C:
			winState = m_menuWindowInfo->state;
			DrawMcWin(-1, 0);
			if (winState == 1) {
				DrawMcWinMess(6, 0);
				if (m_wmWorldState->m_mcResult == 0) {
					break;
				}
			}
			if (winState == 2 && m_menuWindowInfo->state == 3) {
				short cRes = m_wmWorldState->m_mcResult;
				if (cRes == -1) m_wmWorldState->m_subState = 10;
				else if (cRes == -2) m_wmWorldState->m_subState = 8;
				else if (cRes == -3) m_wmWorldState->m_subState = 8;
				else if (cRes == -4) m_wmWorldState->m_subState = 7;
				else if (cRes == -999) {
					m_wmWorldState->m_nextMenuMode = -1;
					m_wmWorldState->m_delay = 1;
					m_wmTransitionCode = 2;
				} else {
					BindMcObj();
					int idx;
					for (idx = 0; idx < kMcListCount; idx++) {
						if (m_wmCharaState[idx].m_isBroken != 0) {
							break;
						}
					}
					if (idx < 4) {
						m_wmWorldState->m_subState = 0x19;
					} else {
						m_wmWorldState->m_subState = 0x11;
					}
				}
			}
			break;
		case 0x11:
			if (m_wmWorldState->m_mcResult < 0) {
				m_wmWorldState->m_subState = 3;
			} else if (m_wmWorldState->m_state0E != 0) {
				if (m_wmWorldState->m_state0E < 0) {
					if (m_wmWorldState->m_menuMode == 8 && m_goOutSaveLoadMode != 0) {
						m_wmWorldState->m_nextMenuMode = 1;
						m_wmWorldState->m_delay = 1;
						ClrMcList();
						m_wmTransitionCode = 1;
					} else {
						m_wmWorldState->m_subState = 2;
					}
				} else {
					m_wmWorldState->m_subState = 0x16;
				}
			}
			break;
		}
		if ((int)subState != (int)m_wmWorldState->m_subState) {
			m_wmWorldState->m_flag09 = 0;
			m_wmWorldState->m_counter1A = 0;
			m_wmWorldState->m_state0E = 0;
		}
	} else if (state != 2) {
		m_wmWorldState->m_frameCounter++;
		int threshold;
		if (m_wmWorldState->m_mainState == 3 && m_wmWorldState->m_subState != 0) {
			threshold = 0x13;
		} else {
			threshold = 10;
		}
		if (m_wmWorldState->m_frameCounter >= threshold) {
			m_wmWorldState->m_mainState++;
			m_wmWorldState->m_frameCounter = 0;
			if (m_wmWorldState->m_mainState >= 5) {
				if (m_wmWorldState->m_menuMode != 8) {
					m_wmWorldState->m_changeRequest = m_wmWorldState->m_nextMenuMode;
				}
				m_textureLocIndex = 1;
				m_wmWorldState->m_nextMenuMode = 0;
			}
		}
	} else if (m_wmWorldState->m_mainState == 2 && m_wmWorldState->m_delay != 0) {
		m_wmWorldState->m_delay--;
		if (m_wmWorldState->m_delay <= 0) {
			m_wmWorldState->m_mainState++;
			m_wmWorldState->m_frameCounter = 0;
			Sound.PlaySe(0x31 + (int)((unsigned int)(int)m_wmWorldState->m_nextMenuMode >> 31), 0x40, 0x7F, 0);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800F7044
 * PAL Size: 3768b
 * EN Address: 0x800F65E8
 * EN Size: 3768b
 * JP Address: 0x800F339C
 * JP Size: 3644b
 */
void CMenuPcs::DrawTitleMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	int state = m_wmWorldState->m_mainState;

		if (state == 0 && static_cast<signed char>(m_wmWorldState->m_worldReady) != 0) {
			if (static_cast<signed char>(m_wmThpActive) != 0) {
				THPSimpleDrawCurrentFrame(Graphic.GetRenderModeObj(), 0, 0, 0x280, 0x1C0);
				Graphic._WaitDrawDone("wm_menu.cpp", kTitleDrawLine);
			}
		short sVarE = m_wmWorldState->m_state0E;
		if (sVarE != 0 || m_wmWorldState->m_frameCounter >= kTitleMovieFrames) {
			if (sVarE != -1) {
				THPSimpleAudioStop();
				THPSimpleLoadStop();
				THPSimpleClose();
				THPSimpleQuit();
				if (m_wmWorkBuffer != 0) {
					Memory.Free(m_wmWorkBuffer);
					m_wmWorkBuffer = 0;
				}
				m_wmThpActive = 0;
			}
			m_wmWorldState->m_mainState++;
			m_wmWorldState->m_frameCounter = 0;
			m_wmWorldState->m_titleState = 0;
			m_wmWorldState->m_state0E = 0;
			m_wmWorldState->m_state12 = 0;
			CallWorldParam(9, 0, 0);
		}
	} else {
		// 3D viewport setup
		GXColor matColor;
		Mtx44 projMtx;
		C_MTXPerspective(projMtx, FLOAT_80331470, FLOAT_80331474, FLOAT_80331478, FLOAT_8033147c);
		GXSetProjection(projMtx, GX_PERSPECTIVE);
		CameraPcs.SetProjectionMatrix(projMtx);

		Vec eye;
		eye.x = FLOAT_803313dc;
		eye.y = FLOAT_803313dc;
		eye.z = FLOAT_80331768;
		Mtx lookAtMtx;
		C_MTXLookAt(lookAtMtx, &eye,
		            CVector(FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313dc),
		            CVector(FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313dc));
		CameraPcs.GetViewMatrix(m_wm.m_savedCameraMatrix);
		CameraPcs.SetViewMatrix(lookAtMtx);
		CharaPcs.InitEnv(5);
		GXSetColorUpdate(0);
		GXSetAlphaUpdate(0);
		GXSetCopyClear(CColor(0, 0, 0, 0).color, 0xFFFFFF);
		GXSetColorUpdate(1);
		GXSetAlphaUpdate(1);
		GXSetViewport(FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313e0, FLOAT_803313e4,
		              FLOAT_803313dc, FLOAT_803313e8);

		PartPcs.DrawMenuIdx(m_effectWork[23].m_partNo);
		RestoreProjection();

		// Fade-in overlay (state 1)
			state = m_wmWorldState->m_mainState;
			if (state == 1 && static_cast<signed char>(lbl_8032E8AC) == 0) {
				float fadeAlpha = static_cast<float>(-(DOUBLE_80331770 *
				                                        static_cast<double>(m_wmWorldState->m_frameCounter) -
				                                        DOUBLE_80331420));
				DrawFilter(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(static_cast<int>(FLOAT_80331458 * fadeAlpha)));
		}

		// Menu items
		MenuPcs.SetAttrFmt((FMT)0);
		MenuPcs.SetTexture((TEX)kTitleMenuTexture);

		state = m_wmWorldState->m_mainState;
		if (state >= 2) {
			float fX = kTitleSelectionX;
			fX -= FLOAT_80331414;
			float fY = FLOAT_8033177C;
			if (m_wmWorldState->m_cardChannel != 0) {
				fY += (float)(m_wmWorldState->m_cardChannel * 0x28 - 8);
			}
			fY -= FLOAT_80331780;
			float alpha;
			if (state == 2 && m_wmWorldState->m_state12 == 0) {
				int timer = (int)m_wmWorldState->m_titleState;
				fX = static_cast<float>(-(kTitleSlideDistance *
				                           (static_cast<double>(5 - timer) / DOUBLE_80331798) -
				                           static_cast<double>(fX)));
				alpha = static_cast<float>(DOUBLE_80331788 * static_cast<double>(timer) + DOUBLE_803314E8);
			} else {
				alpha = FLOAT_803313e8;
			}
			matColor.r = 0xFF;
			matColor.g = 0xFF;
			matColor.b = 0xFF;
			matColor.a = static_cast<unsigned char>(static_cast<int>(FLOAT_80331458 * alpha));
			GXSetChanMatColor(GX_COLOR0A0, matColor);
			MenuPcs.DrawRect(0, fX, fY,
			         kTitleSelectionWidth, FLOAT_80331554,
			         FLOAT_803313dc, FLOAT_803313dc,
			         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
			AlphaAdd();
			state = m_wmWorldState->m_mainState;
			float secondAlpha = alpha;
			fX = kTitleSelectionX;
			fX -= FLOAT_80331414;
			if (state == 2 && m_wmWorldState->m_state12 == 0) {
				int timer = (int)m_wmWorldState->m_titleState;
				fX = static_cast<float>(kTitleSlideDistance *
				                         (static_cast<double>(5 - timer) / DOUBLE_80331798) +
				                         static_cast<double>(fX));
			} else if ((state == 2 && m_wmWorldState->m_delay == 0) ||
			           (state == 3 && m_wmWorldState->m_state0E == 0)) {
				int pulse = abs((int)m_wmWorldState->m_titleState % 0x28 - 0x14);
				secondAlpha = static_cast<float>(-(DOUBLE_803317A0 * static_cast<double>(pulse) -
				                                  DOUBLE_80331420));
			} else {
				secondAlpha = FLOAT_803313e8;
			}
			matColor.r = 0xFF;
			matColor.g = 0xFF;
			matColor.b = 0xFF;
			matColor.a = static_cast<unsigned char>(static_cast<int>(FLOAT_80331458 * secondAlpha));
			GXSetChanMatColor(GX_COLOR0A0, matColor);
			MenuPcs.DrawRect(0, fX, fY,
			         kTitleSelectionWidth, FLOAT_80331554,
			         FLOAT_803313dc, FLOAT_80331554,
			         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
			AlphaNormal();
		}

		// Menu item labels (2 items: New Game, Continue)
		MenuPcs.SetAttrFmt((FMT)0);
		const float kColorScale = FLOAT_80331458;
		const float kZero = FLOAT_803313dc;
		unsigned int itemYOffset = 0xFFFFFFF8;
#ifdef VERSION_GCCJGC
		int itemTexX = 0;
#else
		unsigned int itemTexY = 0x70;
#endif
		for (int i = 0; i < 2; i++) {
			float labelAlpha;
			if (m_wmWorldState->m_mainState == 1) {
				labelAlpha = static_cast<float>(DOUBLE_80331770 * static_cast<double>(m_wmWorldState->m_frameCounter));
			} else {
				labelAlpha = FLOAT_803313e8;
			}
			matColor.r = 0xFF;
			matColor.g = 0xFF;
			matColor.b = 0xFF;
			matColor.a = static_cast<unsigned char>(static_cast<int>(kColorScale * labelAlpha));
			GXSetChanMatColor(GX_COLOR0A0, matColor);

			float yPos = FLOAT_8033177C;
			if (i != 0) {
				yPos = yPos + (float)((int)itemYOffset);
			}
			MenuPcs.DrawRect(0, kTitleLabelX, yPos,
			         kTitleLabelWidth, FLOAT_80331440,
#ifdef VERSION_GCCJGC
			         static_cast<float>(itemTexX), 56.0f,
#else
			         kZero, (float)((int)itemTexY),
#endif
			         FLOAT_803313e8, FLOAT_803313e8, kZero);

			// Cursor on selected item
			if (m_wmWorldState->m_flag09 == 0 &&
			    i == m_wmWorldState->m_cardChannel) {
				int timer = (int)m_wmWorldState->m_titleState;
				float cursorScale = static_cast<float>(DOUBLE_803317A8 * static_cast<double>(timer) +
				                                        static_cast<double>(FLOAT_803313e8));
				int cursorAlpha = static_cast<int>(kColorScale *
				                                   static_cast<float>(-(DOUBLE_803317B0 * static_cast<double>(timer) -
				                                                        DOUBLE_80331420)));
				matColor.r = 0xFF;
				matColor.g = 0xFF;
				matColor.b = 0xFF;
				matColor.a = static_cast<unsigned char>(cursorAlpha);
				GXSetChanMatColor(GX_COLOR0A0, matColor);
				float cursorX = static_cast<float>((FLOAT_803313e0 - kTitleLabelWidth * cursorScale) * DOUBLE_803313F8);
				float cursorY = FLOAT_8033177C - (FLOAT_80331440 * cursorScale - FLOAT_80331440);
				if (i != 0) {
					cursorY = cursorY + (float)((int)itemYOffset);
				}
				MenuPcs.DrawRect(0,
				         cursorX,
				         cursorY,
				         kTitleLabelWidth, FLOAT_80331440,
#ifdef VERSION_GCCJGC
				         static_cast<float>(itemTexX), 56.0f,
#else
				         kZero, (float)((int)itemTexY),
#endif
				         cursorScale, cursorScale, kZero);
			}
			itemYOffset += 0x28;
#ifdef VERSION_GCCJGC
			itemTexX += 120;
#else
			itemTexY += 0x28;
#endif
		}

		// Logo and copyright textures
		MenuPcs.SetAttrFmt((FMT)0);
		matColor.r = 0xFF;
		matColor.g = 0xFF;
		matColor.b = 0xFF;
		matColor.a = 0xFF;
		GXSetChanMatColor(GX_COLOR0A0, matColor);
		MenuPcs.SetTexture((TEX)kTitleLogoTexture);
		MenuPcs.DrawRect(0, FLOAT_803317B8, FLOAT_803317BC, FLOAT_803317C0, FLOAT_803315B4,
		         FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);

#ifndef VERSION_GCCJGC
		MenuPcs.SetTexture((TEX)0x44);
		float copyrightAlpha;
		if (m_wmWorldState->m_mainState == 1) {
			copyrightAlpha = static_cast<float>(DOUBLE_80331770 * static_cast<double>(m_wmWorldState->m_frameCounter));
		} else {
			copyrightAlpha = FLOAT_803313e8;
		}
		matColor.r = 0xFF;
		matColor.g = 0xFF;
		matColor.b = 0xFF;
		matColor.a = static_cast<unsigned char>(static_cast<int>(FLOAT_80331458 * copyrightAlpha));
		GXSetChanMatColor(GX_COLOR0A0, matColor);
		MenuPcs.DrawRect(0, FLOAT_803317C4, FLOAT_803317C8, FLOAT_803317CC, FLOAT_80331440,
		         FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);

#endif

		// Timer / state transitions
		state = m_wmWorldState->m_mainState;
		if (state >= 2) {
			m_wmWorldState->m_titleState++;
			if (m_wmWorldState->m_state12 == 0 &&
			    m_wmWorldState->m_titleState >= 5) {
				m_wmWorldState->m_flag09 = 1;
				m_wmWorldState->m_state12++;
				m_wmWorldState->m_titleState = 0x14;
			}
		}

		// Fade out / transition to next state
		state = m_wmWorldState->m_mainState;
		if (state == 3 || (state == 1 && static_cast<signed char>(lbl_8032E8AC) != 0)) {
			float fadeAlpha2;
			if (state == 3) {
				fadeAlpha2 = static_cast<float>(DOUBLE_803314E8 * static_cast<double>(m_wmWorldState->m_frameCounter + 1));
			} else {
				fadeAlpha2 = static_cast<float>(-(DOUBLE_80331770 * static_cast<double>(m_wmWorldState->m_frameCounter) -
				                                 DOUBLE_80331420));
			}
			if (fadeAlpha2 >= FLOAT_803313e8) fadeAlpha2 = FLOAT_803313e8;
			DrawFilter(0, 0, 0, static_cast<unsigned char>(static_cast<int>(FLOAT_80331458 * fadeAlpha2)));
		}

		// End state handling
		state = m_wmWorldState->m_mainState;
		if (state == 3 && m_wmWorldState->m_frameCounter >= 0xA) {
			PartMng.pppDeletePart(m_effectWork[23].m_partNo);
			if (m_wmWorldState->m_state0E != 0) {
				lbl_8032E8AC = 1;
				m_wmWorldState->m_changeRequest = 1;
				CallWorldParam(7, m_wmWorldState->m_cardChannel, 0);
				bytes[0x0D] = 0;
			} else {
				lbl_8032E8AC = 0;
			}
			m_wmWorldState->m_mainState = 0;
			m_wmWorldState->m_frameCounter = 0;
			m_wmWorldState->m_worldReady = 0;
		} else if (state != 2) {
			unsigned int threshold = 10;
			m_wmWorldState->m_frameCounter++;
			if (m_wmWorldState->m_mainState == 1) {
				threshold = 0x28;
			}
			if (m_wmWorldState->m_frameCounter > threshold) {
				m_wmWorldState->m_frameCounter = 0;
				m_wmWorldState->m_titleState = 0;
				m_wmWorldState->m_mainState++;
			}
		} else {
			if (state == 2 && m_wmWorldState->m_delay != 0) {
				m_wmWorldState->m_delay--;
				if (m_wmWorldState->m_delay <= 0) {
					m_wmWorldState->m_mainState++;
					m_wmWorldState->m_frameCounter = 0;
					m_wmWorldState->m_titleState = 0;
					CallWorldParam(9, 1, 0);
				}
			} else if (m_wmWorldState->m_delay == 0 && m_wmWorldState->m_frameCounter >= kTitleIdleFrames) {
				m_wmWorldState->m_state0E = 0;
				m_wmWorldState->m_mainState++;
				m_wmWorldState->m_frameCounter = 0;
				m_wmWorldState->m_titleState = 0;
				CallWorldParam(9, 1, 0);
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800F6D70
 * PAL Size: 724b
 * EN Address: 0x800F6330
 * EN Size: 696b
 * JP Address: 0x800F3118
 * JP Size: 644b
 */
void CMenuPcs::SetWorldParam(int code, int value)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	switch (code) {
	case 0: {
		bytes[5] = bytes[4];
		bytes[4] = static_cast<unsigned char>(value);
		bytes[0xA] |= WMDATA_CHG_AREA;
		break;
	}
	case 1:
		bytes[6] = static_cast<unsigned char>(value);
		break;
	case 2:
		*reinterpret_cast<unsigned short*>(bytes + 0x1A) = static_cast<unsigned short>(value) & 0x3FF;
		break;
	case 3:
		bytes[7] = static_cast<unsigned char>(value);
		break;
	case 4:
		bytes[8] = static_cast<unsigned char>(value);
		break;
	case 5:
		*reinterpret_cast<unsigned short*>(bytes + 0x1C) = static_cast<unsigned short>(value);
		break;
	case 6:
		*reinterpret_cast<unsigned short*>(bytes + 0x1E) = static_cast<unsigned short>(value);
		break;
	case 7:
		bytes[9] = static_cast<unsigned char>(value);
		break;
	case 8: {
		bytes[0xB] = bytes[0xC];
		bytes[0xC] = static_cast<unsigned char>(value);
		bytes[0xA] |= WMDATA_CHG_YEAR;
		break;
	}
	case 9:
		if (static_cast<int>(static_cast<signed char>(bytes[0xD])) != value) {
			bytes[0xD] = static_cast<unsigned char>(value);
		}
		m_wmWorldState->m_changeRequest = 2;
		break;
	case 10:
		bytes[0x10] = value ? 1 : 0;
		break;
	case 11:
		bytes[0x11] = value ? 1 : 0;
		break;
	case 12:
		bytes[0xE] = static_cast<unsigned char>(value);
		break;
	case 13:
		m_pageMarkFlags = static_cast<unsigned char>(value) & 3;
		break;
	case 14:
		bytes[0x12] = value ? 1 : 0;
		break;
	case 15:
		bytes[0x13] = value ? 1 : 0;
		break;
	case 16:
		bytes[0x17] = static_cast<unsigned char>(value);
		break;
	case 0x12: {
		McCtrl* mc = GetMcCtrl();
		mc->Init();
		mc->SetSlot(static_cast<signed char>(bytes[0x17]));
		m_mcRequest = 0x12;
		break;
	}
	case 0x13: {
		McCtrl* mc = GetMcCtrl();
		mc->Init();
		mc->SetSlot(static_cast<signed char>(bytes[0x17]));
		m_mcRequest = 0x13;
		break;
	}
	case 0x14:
		MemoryCardMan.McEnd();
		m_mcRequestLocked = 1;
		break;
	case 0x16:
		bytes[0x15] = 1;
		changeMode(static_cast<MENUMODE>(2));
		bytes[0x15] = 1;
		break;
	case 0x17: {
		const char disabled = value == 0;
		CameraPcs.m_worldMapEffect.m_paused = disabled;
#ifdef VERSION_GCCP01
		const int effectFrames = 75;
#else
		const int effectFrames = 90;
#endif
		CameraPcs.m_worldMapEffect.m_timer = effectFrames;
		CameraPcs.m_worldMapEffect.m_duration = effectFrames;
		CameraPcs.m_worldMapEffect.m_rotX = FLOAT_80331618;
		CameraPcs.m_worldMapEffect.m_rotY = FLOAT_80331760;
		CameraPcs.m_worldMapEffect.m_scale = FLOAT_80331764;
		break;
	}
	case 0x18:
		loadData();
		break;
	case 0x19:
		bytes[0x16] = 1;
		break;
#ifndef VERSION_GCCJGC
	case 0x1a: {
		int i = 0;
		do {
			GbaQue.SetRadarMode(i, 0);
			i = i + 1;
		} while (i < 4);
		break;
	}
#endif
#ifdef VERSION_GCCP01
	case 0x1b:
		GbaQue.SetControllerMode(value ? 1 : 0);
		break;
#endif
	default:
		if (static_cast<unsigned int>(System.m_execParam) >= 1) {
#ifdef VERSION_GCCJGC
			System.Printf("%s(%d): Error:function code not found(%d)\n", "wm_menu.cpp", 0x14F0, code);
#elif defined(VERSION_GCCE01)
			System.Printf("%s(%d): Error:function code not found(%d)\n", "wm_menu.cpp", 0x145B, code);
#else
			System.Printf("%s(%d): Error:function code not found(%d)\n", "wm_menu.cpp", 0x1482, code);
#endif
		}
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800f6afc
 * PAL Size: 628b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::GetWorldParam(int code)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned int result = 0;

	switch (code) {
	case 0:
		result = *reinterpret_cast<signed char*>(bytes + 4);
		break;
	case 1:
		result = *reinterpret_cast<signed char*>(bytes + 6);
		break;
	case 2:
		result = static_cast<unsigned int>(*reinterpret_cast<short*>(bytes + 0x1A));
		break;
	case 3:
		result = *reinterpret_cast<signed char*>(bytes + 7);
		break;
	case 4:
		result = *reinterpret_cast<signed char*>(bytes + 8);
		break;
	case 5:
		result = static_cast<unsigned int>(*reinterpret_cast<short*>(bytes + 0x1C));
		break;
	case 6:
		result = static_cast<unsigned int>(*reinterpret_cast<short*>(bytes + 0x1E));
		break;
	case 7:
		result = *reinterpret_cast<signed char*>(bytes + 9);
		break;
	case 8:
		result = *reinterpret_cast<signed char*>(bytes + 0xC);
		break;
	case 9:
		result = *reinterpret_cast<signed char*>(bytes + 0xD);
		break;
	case 10:
		result = bytes[0x10] ? 1 : 0;
		break;
	case 11:
		result = bytes[0x11] ? 1 : 0;
		break;
	case 12:
		result = *reinterpret_cast<signed char*>(bytes + 0xE);
		break;
	case 13:
		result = static_cast<unsigned int>(static_cast<signed char>(m_pageMarkFlags));
		break;
	case 14:
		result = bytes[0x12] ? 1 : 0;
		break;
	case 15:
		result = bytes[0x13] ? 1 : 0;
		break;
	case 16:
		result = *reinterpret_cast<signed char*>(bytes + 0x17);
		break;
	case 0x11: {
		int connectStatus;
		int retryCount = 0;
		do {
			connectStatus = MemoryCardMan.McChkConnect(0);
			if (connectStatus != 1) break;
			retryCount = retryCount + 1;
		} while (retryCount < 10);
		if (connectStatus == 0) {
			result = result | 1;
		} else if (connectStatus == 1) {
			result = result | 7;
		} else if (connectStatus != -1) {
			if (connectStatus == -2) {
				result = result | 2;
			} else if (connectStatus == -3) {
				result = result | 3;
			} else {
				result = result | 6;
			}
		}
		retryCount = 0;
		do {
			connectStatus = MemoryCardMan.McChkConnect(1);
			if (connectStatus != 1) break;
			retryCount = retryCount + 1;
		} while (retryCount < 10);
		if (connectStatus == 0) {
			result = result | 0x10;
		} else if (connectStatus == 1) {
			result = result | 0x70;
		} else if (connectStatus != -1) {
			if (connectStatus == -2) {
				result = result | 0x20;
			} else if (connectStatus == -3) {
				result = result | 0x30;
			} else {
				result = result | 0x60;
			}
		}
		break;
	}
	case 0x15:
		result = 0x16;
		break;
	case 0x16:
	case 0x17:
	case 0x18:
	case 0x19:
	case 0x1a:
	case 0x1b:
	default:
		if (static_cast<unsigned int>(System.m_execParam) >= 1) {
			System.Printf("%s(%d): Error:function code not found(%d)\n", "wm_menu.cpp", 0x1521, code);
		}
		break;
	}

	return result;
}

/*
 * --INFO--
 * PAL Address: 0x800f6ab0
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CallWorldParam(int p0, int p1, int p2)
{
	CFlatRuntime::CStack stackData[3];
	stackData[0].m_word = p0;
	stackData[1].m_word = p1;
	stackData[2].m_word = p2;

	gCFlatRuntime().SystemCall(0, 1, 4, 3, stackData, 0);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 112b
 * EN Address: 0x8010F9B8
 * EN Size: 244b
 * JP Address: TODO
 * JP Size: TODO
 */
inline float CMenuPcs::CalcSpl(CMenuPcs::SPL* prev, CMenuPcs::SPL* next, float t)
{
	float span = next->time - prev->time;
	float u = (t - prev->time) / span;
	float u2 = u * u;
	float u3 = u2 * u;
	float h00 = 2.0f * u3 - 3.0f * u2 + 1.0f;
	float h01 = -2.0f * u3 + 3.0f * u2;
	float h10 = u3 - 2.0f * u2 + u;
	float h11 = u3 - u2;

	return prev->value * h00 + next->value * h01 + span * (prev->outTangent * h10 + next->inTangent * h11);
}

/*
 * --INFO--
 * PAL Address: 0x800f69a8
 * PAL Size: 264b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
float CMenuPcs::GetFcvValue(CMenuPcs::FCV fcv, float value)
{
	SPL* cur;
	int idx;
	SPL* keys;
	float result;
	int keyCount;
	keyCount = fcv.keyCount;
	float t = value / FLOAT_803314c0;
	keys = fcv.keys;
	result = FLOAT_803313dc;

	if (t >= keys[keyCount - 1].time) {
		return keys[keyCount - 1].value;
	}

	cur = keys;
	for (idx = 0; idx < keyCount; cur++, idx++) {
		if (t <= cur->time) {
			if (idx == 0) {
				result = keys[idx].value;
			} else {
				result = CalcSpl(&fcv.keys[idx - 1], &fcv.keys[idx], t);
			}
			break;
		}
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: 0x800f67e0
 * PAL Size: 456b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetProjection(int mode)
{
	WmWorldObjInfo* const slot = &m_wm.m_worldObjData[mode];
	Mtx44 projectionMtx;
	C_MTXPerspective(projectionMtx, FLOAT_80331470, FLOAT_80331474, FLOAT_80331478, FLOAT_8033147c);
	GXSetProjection(projectionMtx, GX_PERSPECTIVE);
	CameraPcs.SetProjectionMatrix(projectionMtx);

	Mtx lookAtMtx;
	C_MTXLookAt(lookAtMtx, &slot->m_cameraPosition,
	    CVector(FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313dc),
	    CVector(FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313dc));
	CameraPcs.GetViewMatrix(m_wm.m_savedCameraMatrix);
	CameraPcs.SetViewMatrix(lookAtMtx);

	CharaPcs.InitEnv(5);
	GXSetColorUpdate(0);
	GXSetAlphaUpdate(0);
	GXSetCopyClear(CColor(0, 0, 0, 0).color, 0x00FFFFFF);
	GXSetColorUpdate(1);
	GXSetAlphaUpdate(1);

	GXSetViewport(
	    static_cast<float>(slot->m_viewportX),
	    static_cast<float>(slot->m_viewportY),
	    static_cast<float>(slot->m_viewportWidth),
	    static_cast<float>(slot->m_viewportHeight),
	    FLOAT_803313dc,
	    FLOAT_803313e8);
	GXSetScissor(
	    slot->m_scissorX,
	    slot->m_scissorY,
	    slot->m_scissorWidth,
	    slot->m_scissorHeight);
}

/*
 * --INFO--
 * PAL Address: 0x800f673c
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::RestoreProjection()
{
	CameraPcs.SetViewMatrix(m_wm.m_savedCameraMatrix);
	GXSetCopyClear(Graphic.GetCopyClearColor(), 0x00FFFFFF);
	Mtx44 projectionMtx;
	CameraPcs.GetProjectionMatrix(projectionMtx);
	GXSetProjection(projectionMtx, GX_PERSPECTIVE);
	Graphic.SetViewport();
	GXSetScissor(0, 0, 0x280, 0x1C0);
	DrawInit();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::DrawObj(int kind)
{
	if (kind == 0) {
		DrawChara();
	} else if (kind == 1) {
		DrawMcObj();
	} else {
		DrawWMFrame();
		DrawFukidashi();
	}
}

/*
 * --INFO--
 * PAL Address: 0x800f653c
 * PAL Size: 512b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcPitcher()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	short state = m_wmWorldState->m_mainState;
	if (state == 0 || state > 2) {
		return;
	}

	WmWorldObjInfo* worldObj = m_wm.m_worldObjData;

	const float one = FLOAT_803313e8;
	const float pb8 = FLOAT_803315d0;
	const float pb4 = FLOAT_80331750;
	const float pb0 = FLOAT_8033174c;
	const float pac = FLOAT_80331748;
	const float pa8 = FLOAT_803314A4;
	worldObj[5].m_active = 1;
	worldObj[5].m_viewportX = 0x140;
	worldObj[5].m_viewportY = 0xE0;
	worldObj[5].m_viewportWidth = 0x140;
	worldObj[5].m_viewportHeight = 0xE0;
	worldObj[5].m_cameraPosition.x = FLOAT_803313dc;
	worldObj[5].m_cameraPosition.y = FLOAT_803313dc;
	worldObj[5].m_cameraPosition.z = pa8;
	worldObj[5].m_transform.m_position.x = pac;
	worldObj[5].m_transform.m_position.y = pb0;
	worldObj[5].m_transform.m_position.z = pb4;
	worldObj[5].m_transform.m_rotation.x = pb8;
	worldObj[5].m_transform.m_rotation.y += FLOAT_80331754;

	Mtx scaleMtx;
	Mtx rotXMtx;
	Mtx rotYMtx;
	PSMTXScale(scaleMtx, one, one, one);
	PSMTXRotRad(rotXMtx, 'x', worldObj[5].m_transform.m_rotation.x);
	PSMTXRotRad(rotYMtx, 'y', worldObj[5].m_transform.m_rotation.y);
	PSMTXConcat(rotXMtx, rotYMtx, rotXMtx);
	rotXMtx[0][3] = worldObj[5].m_transform.m_position.x;
	rotXMtx[1][3] = worldObj[5].m_transform.m_position.y;
	rotXMtx[2][3] = worldObj[5].m_transform.m_position.z;
	PSMTXConcat(rotXMtx, scaleMtx, scaleMtx);

	short step = m_wmWorldState->m_frameCounter;
	float blendStep = static_cast<float>(DOUBLE_803314E8 * static_cast<double>(step));
	if (m_wmWorldState->m_mainState == 1 && step < 10) {
		m_wm.m_handles[5]->m_model->m_lightAlpha = blendStep;
	} else if (m_wmWorldState->m_mainState == 2 && bytes[0x13] != 0) {
		m_wm.m_handles[5]->m_model->m_lightAlpha =
			static_cast<float>(DOUBLE_80331420 - static_cast<double>(blendStep));
	} else {
		m_wm.m_handles[5]->m_model->m_lightAlpha = FLOAT_803313e8;
	}

	m_wm.m_handles[5]->m_model->SetMatrix(scaleMtx);
	m_wm.m_handles[5]->m_model->m_meshVisibleMask =
		static_cast<char>(lbl_80331380[Game.m_gameWork.m_timerA]);
	m_wm.m_handles[5]->m_model->CalcMatrix();
	m_wm.m_handles[5]->m_model->CalcSkin();
}

static inline void SetPortTownName(char* dst, const char* townName)
{
#ifdef VERSION_GCCJGC
	strcpy(dst, townName);
	strcat(dst, "\x82\xCC\x8D\x60");
#else
	static const char* s_port[] = {"Port ", "-Hafen", "Porto ", "Port ", "Puerto "};
	const int language = Game.m_gameWork.GetLanguage();
	if (language == 2) {
		strcpy(dst, townName);
		strcat(dst, s_port[language - 1]);
	} else {
		strcpy(dst, s_port[language - 1]);
		strcat(dst, townName);
	}
#endif
}

/*
 * --INFO--
 * PAL Address: 0x800F554C
 * PAL Size: 4080b
 * EN Address: 0x800F4AEC
 * EN Size: 4112b
 * JP Address: 0x800F1978
 * JP Size: 3944b
 */
void CMenuPcs::CalcFukidashi()
{
	int padIdx;
	int i;
	if (m_wmBubbleVisible != 1) {
		return;
	}
	int bitIdx;

	m_wm.m_bubbleData->m_sprites[0].m_x = m_wmBubbleX;
	float bubbleTexV = FLOAT_803313dc;
	m_wm.m_bubbleData->m_sprites[0].m_y = m_wmBubbleY;
	m_wm.m_bubbleData->m_sprites[0].m_width = 0xF0;
	m_wm.m_bubbleData->m_sprites[0].m_height = 0xC4;
	m_wm.m_bubbleData->m_sprites[0].m_v = bubbleTexV;
	if (m_wmBubbleType == 2 || m_wmBubbleType == 3) {
		m_wm.m_bubbleData->m_sprites[0].m_u = FLOAT_803313dc;
	} else {
		m_wm.m_bubbleData->m_sprites[0].m_u = FLOAT_80331704;
	}

	float panelTexU = FLOAT_80331708;
	if ((m_wmIconFlags & 0x3F0) != 0) {
		m_wm.m_bubbleData->m_sprites[1].m_width = 0x50;
		float panelTexV = FLOAT_803313dc;
		m_wm.m_bubbleData->m_sprites[1].m_height = 0x48;
		m_wm.m_bubbleData->m_sprites[1].m_u = panelTexU;
		m_wm.m_bubbleData->m_sprites[1].m_v = panelTexV;
		m_wm.m_bubbleData->m_sprites[1].m_y = m_wm.m_bubbleData->m_sprites[0].m_y + 0x1C;
		if (m_wmBubbleType == 2 || m_wmBubbleType == 3) {
			m_wm.m_bubbleData->m_sprites[1].m_y = m_wm.m_bubbleData->m_sprites[1].m_y + 0x10;
		}
		m_wm.m_bubbleData->m_sprites[1].m_x = m_wm.m_bubbleData->m_sprites[0].m_x;
		if ((m_wmIconFlags & 0xF) != 0) {
			m_wm.m_bubbleData->m_sprites[1].m_x = m_wm.m_bubbleData->m_sprites[1].m_x + 0x20;
		} else if ((m_wmIconFlags & 0x200) != 0) {
			m_wm.m_bubbleData->m_sprites[1].m_x = m_wm.m_bubbleData->m_sprites[1].m_x + 0x50;
		} else {
			m_wm.m_bubbleData->m_sprites[1].m_x = m_wm.m_bubbleData->m_sprites[1].m_x + 0x38;
		}
	}

	float iconTexUV = FLOAT_803313dc;
	if ((m_wmIconFlags & 0x1FF) != 0) {
		m_wm.m_bubbleData->m_sprites[2].m_width = 0x20;
		m_wm.m_bubbleData->m_sprites[2].m_height = 0x20;
		m_wm.m_bubbleData->m_sprites[2].m_u = iconTexUV;
		m_wm.m_bubbleData->m_sprites[2].m_v = iconTexUV;

		m_wm.m_bubbleData->m_sprites[3] = m_wm.m_bubbleData->m_sprites[2];

		short flagsF = m_wmIconFlags;
		int cnt;
		WmBubbleInfo* bubble = m_wm.m_bubbleData;
		int panelRight = bubble->m_sprites[1].m_x + bubble->m_sprites[1].m_width;
		if ((flagsF & 0xF) != 0) {
			bubble->m_sprites[3].m_x = panelRight;
			m_wm.m_bubbleData->m_sprites[2].m_x = panelRight;
			for (bitIdx = cnt = 0; bitIdx < 4; bitIdx++) {
				if ((m_wmIconFlags & (1 << bitIdx)) != 0) {
					cnt++;
				}
			}
			if (cnt == 1) {
				m_wm.m_bubbleData->m_sprites[2].m_y =
				    m_wm.m_bubbleData->m_sprites[1].m_y;
				m_wm.m_bubbleData->m_sprites[2].m_y =
				    m_wm.m_bubbleData->m_sprites[2].m_y + 0x14;
			} else {
				m_wm.m_bubbleData->m_sprites[2].m_y =
				    m_wm.m_bubbleData->m_sprites[1].m_y;
				bubble = m_wm.m_bubbleData;
				bubble->m_sprites[3].m_y =
				    bubble->m_sprites[1].m_y + bubble->m_sprites[1].m_height - 0x20;
			}
		} else {
			bubble->m_sprites[3].m_x = panelRight + 8;
			m_wm.m_bubbleData->m_sprites[2].m_x = panelRight + 8;
			m_wm.m_bubbleData->m_sprites[2].m_y =
			    m_wm.m_bubbleData->m_sprites[1].m_y;
			m_wm.m_bubbleData->m_sprites[2].m_y =
			    m_wm.m_bubbleData->m_sprites[2].m_y + 0x14;
		}
	}

	// Font name text processing
	CFont* fontFC = GetFontWorld();
	fontFC->SetMargin(FLOAT_803313e8);
	fontFC->SetShadow(0);
	fontFC->SetScale(FLOAT_803313e8);

	Mtx scaleMtx;
	char nameBuffer[64];
#ifndef VERSION_GCCJGC
	char tempBuf[64];
	char secondLine[64];
#endif
	int fieldVal = m_wmPlaceNo;
	if (fieldVal == 0x0F) {
		strcpy(nameBuffer, Game.m_gameWork.m_townName);
#ifdef VERSION_GCCJGC
		strcat(nameBuffer, "\x82\xCC\x91\xBA");
#endif
	} else if (fieldVal == 0x16) {
		SetPortTownName(nameBuffer, Game.m_gameWork.m_townName);
#ifdef VERSION_GCCJGC
	} else if (fieldVal == 5) {
		strcpy(nameBuffer, Game.GetPlaceName(fieldVal));
		*strstr(nameBuffer, "\x82\xCC\x8A\xD9") = 0;
#endif
	} else {
		strcpy(nameBuffer, Game.GetPlaceName(fieldVal));
	}
#ifndef VERSION_GCCJGC
	Game.UpperItemName(nameBuffer);

	int textWidth = m_wmIconFlags != 0 ? 0xA2 : 0xD8;
	if (ChkPlaceLength(nameBuffer, textWidth)) {
		SplitPlace(nameBuffer, tempBuf, secondLine);
		strcpy(nameBuffer, tempBuf);
	}
#endif
	float nameWidthF = fontFC->GetWidth(nameBuffer);

	int textYOffset = 0x4C;
	m_wm.m_bubbleData->m_sprites[4].m_x =
	    static_cast<short>(static_cast<int>(
	        (FLOAT_80331704 - nameWidthF) * FLOAT_80331434 +
	        static_cast<float>(static_cast<int>(m_wm.m_bubbleData->m_sprites[0].m_x))));
	float cameraZ = FLOAT_803314A4;
	float cameraXY = FLOAT_803313dc;
	unsigned short iconFlags = m_wmIconFlags;
	if ((iconFlags & 0x3F0) != 0) {
		textYOffset = 0x6C;
	}
	if (m_wmBubbleType == 2 || m_wmBubbleType == 3) {
		textYOffset = textYOffset + 0x10;
	}

	// Set text position
	m_wm.m_bubbleData->m_sprites[4].m_y =
	    m_wm.m_bubbleData->m_sprites[0].m_y + textYOffset;
#ifndef VERSION_GCCJGC
	m_wm.m_bubbleData->m_sprites[4].m_y =
	    m_wm.m_bubbleData->m_sprites[4].m_y - 4;
#endif

	// Setup model viewport slots
	int viewportX = m_wm.m_bubbleData->m_sprites[0].m_x - 0x28;
	int viewportY = m_wm.m_bubbleData->m_sprites[0].m_y - 0x0E;
	for (i = 6; i <= 16; i++) {
		WmWorldObjInfo* slot = &m_wm.m_worldObjData[i];
		slot->m_active = 0;
		slot->m_viewportX = viewportX;
		slot->m_viewportY = viewportY;
		slot->m_viewportWidth = 0x140;
		slot->m_viewportHeight = 0xE0;
		slot->m_cameraPosition.x = cameraXY;
		slot->m_cameraPosition.y = cameraXY;
		slot->m_cameraPosition.z = cameraZ;
	}

	// Setup tribe/character model slot
	float modelScale = FLOAT_8033170C;
	float modelPosZero = FLOAT_803313dc;
	short sFlags = m_wmIconFlags;
	if ((sFlags & 0x3F0) != 0) {
		int modelIdx;
		if ((sFlags & 0x200) != 0) {
			if (m_wmIconVariant == 1) {
				modelIdx = 7;
			} else {
				modelIdx = 6;
			}
		} else {
			for (bitIdx = 0; bitIdx < 5; bitIdx++) {
				if ((sFlags & (0x10 << bitIdx)) != 0) {
					break;
				}
			}
			modelIdx = bitIdx + 0x0C;
		}

		WmWorldObjInfo* worldObj = &m_wm.m_worldObjData[modelIdx];
		worldObj->m_active = 1;
		worldObj->m_transform.m_position.x = modelPosZero;
		worldObj->m_transform.m_position.y = modelPosZero;
		worldObj->m_transform.m_position.z = modelPosZero;
		worldObj->m_transform.m_scale.x = modelScale;
		worldObj->m_transform.m_scale.y = modelScale;
		worldObj->m_transform.m_scale.z = modelScale;
		if (m_wmBubbleType == 2 || m_wmBubbleType == 3) {
			worldObj->m_transform.m_position.y = FLOAT_80331710;
		}
		if ((m_wmIconFlags & 0xF) != 0) {
			worldObj->m_transform.m_position.x = FLOAT_80331714;
			worldObj->m_transform.m_position.y = static_cast<float>(
			    static_cast<double>(worldObj->m_transform.m_position.y) + DOUBLE_80331420);
		} else if ((m_wmIconFlags & 0x200) != 0) {
			worldObj->m_transform.m_position.x = FLOAT_803313dc;
			worldObj->m_transform.m_position.y = static_cast<float>(
			    static_cast<double>(worldObj->m_transform.m_position.y) + DOUBLE_80331420);
		} else {
			worldObj->m_transform.m_position.x = FLOAT_80331718;
			worldObj->m_transform.m_position.y = static_cast<float>(
			    static_cast<double>(worldObj->m_transform.m_position.y) + DOUBLE_80331720);
		}

		// Spline evaluation for Y position
		worldObj->m_transform.m_position.y =
		    worldObj->m_transform.m_position.y +
		    static_cast<float>(GetFcvValue(s_WoodTrns,
		                                   static_cast<float>(worldObj->m_frameCounter)));

		// Spline evaluation for rotation
		worldObj->m_transform.m_rotation.y =
		    FLOAT_803314bc *
		    static_cast<float>(GetFcvValue(s_WoodRot,
		                                   static_cast<float>(worldObj->m_frameCounter)));
		worldObj->m_transform.m_rotation.x = FLOAT_803315d0;

		// Matrix setup
		Mtx rotXMtx, rotYMtx;
		PSMTXScale(scaleMtx, worldObj->m_transform.m_scale.x, worldObj->m_transform.m_scale.y, worldObj->m_transform.m_scale.z);
		PSMTXRotRad(rotXMtx, 'x', worldObj->m_transform.m_rotation.x);
		PSMTXRotRad(rotYMtx, 'y', worldObj->m_transform.m_rotation.y);
		PSMTXConcat(rotXMtx, rotYMtx, rotXMtx);
		rotXMtx[0][3] = worldObj->m_transform.m_position.x;
		rotXMtx[1][3] = worldObj->m_transform.m_position.y;
		rotXMtx[2][3] = worldObj->m_transform.m_position.z;
		PSMTXConcat(rotXMtx, scaleMtx, scaleMtx);

		m_wm.m_handles[modelIdx]->m_model->SetMatrix(scaleMtx);
		m_wm.m_handles[modelIdx]->m_model->CalcMatrix();
		m_wm.m_handles[modelIdx]->m_model->CalcSkin();

		worldObj->m_frameCounter = worldObj->m_frameCounter + 1;
		if (static_cast<double>(static_cast<float>(worldObj->m_frameCounter)) >=
		    DOUBLE_803314A8 * static_cast<double>(
		        s_WoodTrns.keys[s_WoodTrns.keyCount - 1].time)) {
			worldObj->m_frameCounter = 0;
		}
	}

	// Player character model slots
	unsigned int field1a = (unsigned int)m_wmIconFlags;
	if ((field1a & 0x200) != 0 && (field1a & 0xF) != 0) {
		CMenuPcs::FCV* const yTbl = &s_WoodTrns;
		int playerCount;
		for (bitIdx = playerCount = 0; bitIdx < 4; bitIdx++) {
			if ((field1a & (1 << bitIdx)) != 0) playerCount++;
		}

		int slotIdx = 0;
		for (padIdx = 0; padIdx < 4; padIdx++) {
			if ((m_wmIconFlags & (1 << padIdx)) != 0) {
				int slot8 = padIdx + 8;
				WmWorldObjInfo* worldObj = &m_wm.m_worldObjData[slot8];
				worldObj->m_active = 1;
				worldObj->m_transform.m_position.x = FLOAT_80331728;
				if (slotIdx == 0) {
					if (playerCount == 2) {
						worldObj->m_transform.m_position.y = FLOAT_8033172C;
					} else {
						worldObj->m_transform.m_position.y = FLOAT_80331668;
					}
				} else {
					worldObj->m_transform.m_position.y = FLOAT_80331710;
				}
				if (m_wmBubbleType == 2 || m_wmBubbleType == 3) {
					if (padIdx == 0 && playerCount == 1) {
						worldObj->m_transform.m_position.y = static_cast<float>(
						    static_cast<double>(worldObj->m_transform.m_position.y) - DOUBLE_80331730);
					} else {
						worldObj->m_transform.m_position.y = static_cast<float>(
						    static_cast<double>(worldObj->m_transform.m_position.y) - DOUBLE_80331738);
					}
				}
				worldObj->m_transform.m_position.z = FLOAT_803313dc;
				float f740 = FLOAT_80331740;
				worldObj->m_transform.m_scale.x = f740;
				worldObj->m_transform.m_scale.y = f740;
				worldObj->m_transform.m_scale.z = f740;

				// Spline Y for player models
				worldObj->m_transform.m_position.y =
				    worldObj->m_transform.m_position.y +
				    static_cast<float>(GetFcvValue(s_WoodTrns,
				                                   static_cast<float>(worldObj->m_frameCounter)));

				// Spline rotation for player models
				worldObj->m_transform.m_rotation.y =
				    FLOAT_803314bc *
				    static_cast<float>(GetFcvValue(s_WoodRot,
				                                   static_cast<float>(worldObj->m_frameCounter)));
				if (playerCount == 1) {
					worldObj->m_transform.m_rotation.x = FLOAT_80331744;
				} else {
					worldObj->m_transform.m_rotation.x = FLOAT_803315d0;
				}

				Mtx rxMtx, ryMtx;
				PSMTXScale(scaleMtx, worldObj->m_transform.m_scale.x, worldObj->m_transform.m_scale.y, worldObj->m_transform.m_scale.z);
				PSMTXRotRad(rxMtx, 'x', worldObj->m_transform.m_rotation.x);
				PSMTXRotRad(ryMtx, 'y', worldObj->m_transform.m_rotation.y);
				PSMTXConcat(rxMtx, ryMtx, rxMtx);
				rxMtx[0][3] = worldObj->m_transform.m_position.x;
				rxMtx[1][3] = worldObj->m_transform.m_position.y;
				rxMtx[2][3] = worldObj->m_transform.m_position.z;
				PSMTXConcat(rxMtx, scaleMtx, scaleMtx);

				m_wm.m_handles[slot8]->m_model->SetMatrix(scaleMtx);
				m_wm.m_handles[slot8]->m_model->CalcMatrix();
				m_wm.m_handles[slot8]->m_model->CalcSkin();

				worldObj->m_frameCounter = worldObj->m_frameCounter + 1;
				if (static_cast<double>(static_cast<float>(worldObj->m_frameCounter)) >=
				    DOUBLE_803314A8 * static_cast<double>(yTbl->keys[s_WoodTrns.keyCount - 1].time)) {
					worldObj->m_frameCounter = 0;
				}
				slotIdx++;
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800F4B24
 * PAL Size: 2600b
 * EN Address: 0x800F40A4
 * EN Size: 2632b
 * JP Address: 0x800F1048
 * JP Size: 2352b
 */
void CMenuPcs::DrawFukidashi()
{
#ifdef VERSION_GCCJGC
	const int kBubbleIconTextureBase = 24;
#else
	const int kBubbleIconTextureBase = 25;
#endif
	CFont* const fontFC = GetFontWorld();
	if (m_wmBubbleVisible != 1) {
		return;
	}

	int texMode;
	if (m_wmBubbleType == 0 || m_wmBubbleType == 2) {
		texMode = 0;
	} else {
		texMode = 8;
	}

	MenuPcs.SetAttrFmt((FMT)0);
	GXColor matColor;
	matColor.r = 0xFF;
	matColor.g = 0xFF;
	matColor.b = 0xFF;
	matColor.a = 0xFF;
	GXSetChanMatColor(GX_COLOR0A0, matColor);
	MenuPcs.SetTexture((TEX)kBubbleTexture);

	Sprt* background = &m_wm.m_bubbleData->m_sprites[0];
	MenuPcs.DrawRect(texMode,
		(float)(int)background->m_x, (float)(int)background->m_y,
		(float)(int)background->m_width, (float)(int)background->m_height,
		background->m_u, background->m_v,
		FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);

	if ((m_wmIconFlags & 0x3F0) != 0) {
		WmBubbleInfo* bubble = m_wm.m_bubbleData;
		MenuPcs.DrawRect(0,
			(float)bubble->m_sprites[1].m_x, (float)bubble->m_sprites[1].m_y,
			(float)bubble->m_sprites[1].m_width, (float)bubble->m_sprites[1].m_height,
			bubble->m_sprites[1].m_u, bubble->m_sprites[1].m_v,
			FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
	}

	unsigned int iconFlags = (unsigned int)m_wmIconFlags;
	if ((iconFlags & 0x3F0) != 0 && (iconFlags & 0x1FF) != 0) {
		if ((iconFlags & 0xF) != 0) {
			int bitIndex = 0;
			int drawnIcons = 0;
			while (bitIndex < 4 && drawnIcons < 2) {
				if ((m_wmIconFlags & (1 << bitIndex)) != 0) {
					MenuPcs.SetTexture((TEX)(bitIndex + kBubbleIconTextureBase));
					Sprt* icon;
					if (drawnIcons == 0) {
						icon = &m_wm.m_bubbleData->m_sprites[2];
					} else {
						icon = &m_wm.m_bubbleData->m_sprites[3];
					}
					MenuPcs.DrawRect(0,
						(float)(int)icon->m_x, (float)(int)icon->m_y,
						(float)(int)icon->m_width, (float)(int)icon->m_height,
						icon->m_u, icon->m_v,
						FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
					drawnIcons++;
				}
				bitIndex++;
			}
		} else {
			for (int idx = 0; idx < 5; idx++) {
				if ((iconFlags & (0x10 << idx)) != 0) {
					MenuPcs.SetTexture((TEX)(idx + kBubbleIconTextureBase));
					WmBubbleInfo* bubble = m_wm.m_bubbleData;
					MenuPcs.DrawRect(0,
						(float)bubble->m_sprites[2].m_x, (float)bubble->m_sprites[2].m_y,
						(float)bubble->m_sprites[2].m_width, (float)bubble->m_sprites[2].m_height,
						bubble->m_sprites[2].m_u, bubble->m_sprites[2].m_v,
						FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
					break;
				}
			}
		}
	}

	// Name text
	char nameBuffer[68];
	int fieldVal = m_wmPlaceNo;
	if (fieldVal == 0x0F) {
		strcpy(nameBuffer, Game.m_gameWork.m_townName);
#ifdef VERSION_GCCJGC
		strcat(nameBuffer, "\x82\xCC\x91\xBA");
#endif
	} else if (fieldVal == 0x16) {
#ifndef VERSION_GCCJGC
		strcpy(nameBuffer, Game.m_gameWork.m_townName);
#endif
		SetPortTownName(nameBuffer, Game.m_gameWork.m_townName);
#ifdef VERSION_GCCJGC
	} else if (fieldVal == 5) {
		strcpy(nameBuffer, Game.GetPlaceName(fieldVal));
		*strstr(nameBuffer, "\x82\xCC\x8A\xD9") = 0;
#endif
	} else {
		strcpy(nameBuffer, Game.GetPlaceName(fieldVal));
	}
#ifndef VERSION_GCCJGC
	Game.UpperItemName(nameBuffer);

	int textW = 0xD8;
	char tempBuf[64];
	char secondLine[64];
	secondLine[0] = 0;
	CFont* const font = GetFontWorld();
	if (m_wmIconFlags != 0) {
		textW = 0xA2;
	}
	font->SetMargin(FLOAT_803313e8);
	font->SetShadow(0);
	font->SetScale(FLOAT_803313e8);
	double nameWidth = (double)font->GetWidth(nameBuffer);
	int twoLines;
	if (nameWidth > (double)(float)textW) {
		twoLines = 1;
	} else {
		twoLines = 0;
	}
	if (twoLines != 0) {
		strcpy(tempBuf, nameBuffer);
		char* spacePos = strrchr(tempBuf, 0x20);
		if (spacePos != NULL) {
			*spacePos = 0;
			strcpy(secondLine, spacePos + 1);
		} else {
			secondLine[0] = 0;
		}
		strcpy(nameBuffer, tempBuf);
	}
#endif

	fontFC->SetMargin(FLOAT_803313e8);
	fontFC->SetShadow(0);
	fontFC->SetScale(FLOAT_803313e8);
	fontFC->DrawInit();
	fontFC->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
	fontFC->SetPosX((float)m_wm.m_bubbleData->m_sprites[4].m_x);
	fontFC->SetPosY((float)m_wm.m_bubbleData->m_sprites[4].m_y);
	fontFC->Draw(nameBuffer);

#ifdef VERSION_GCCJGC
	if (m_wmPlaceNo == 5) {
		strcpy(nameBuffer, "\x82\xCC\x8A\xD9");
		float w2 = fontFC->GetWidth(nameBuffer);
		fontFC->SetPosX((FLOAT_80331704 - w2) * FLOAT_80331434 +
		                (float)m_wm.m_bubbleData->m_sprites[0].m_x);
		fontFC->SetPosY((float)(m_wm.m_bubbleData->m_sprites[4].m_y + 0x16));
		fontFC->Draw(nameBuffer);
	}
#else
	if (twoLines != 0) {
		strcpy(nameBuffer, "");
		float w2 = fontFC->GetWidth(secondLine);
		fontFC->SetPosX((FLOAT_80331704 - w2) * FLOAT_80331434 +
		                (float)m_wm.m_bubbleData->m_sprites[0].m_x);
		fontFC->SetPosY((float)(m_wm.m_bubbleData->m_sprites[4].m_y + 0x16));
		fontFC->Draw(secondLine);
	}
#endif

	DrawInit();

	// 3D viewport rendering
	int viewportSetup = 0;
	if ((m_wmIconFlags & 0x3F0) != 0) {
		for (int slot = 6; slot <= 0x10; slot++) {
			WmWorldObjInfo* view = &m_wm.m_worldObjData[slot];
			if (view->m_active != 0) {
				if (viewportSetup == 0) {
					SetProjection(slot);
					viewportSetup = 1;
				}
				SetLight(0);
				m_wm.m_handles[slot]->Draw(5);
				if (slot != 6) {
					EffectInfo* effect = &m_effectWork[slot];
					int a = effect->m_effectNo;
					int b = effect->m_slotNo;
					if (a >= 0 && b >= 0) {
						PartPcs.DrawMenu(a);
					}
				}
			}
		}
	}

	if (viewportSetup != 0) {
		RestoreProjection();
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::ChkPlaceLength(char* text, int width)
{
	CFont* font = GetFontWorld();
	font->SetMargin(1.0f);
	font->SetShadow(0);
	font->SetScale(1.0f);
	return font->GetWidth(text) > width;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 112b
 * EN Address: 0x80111588
 * EN Size: 132b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::SplitPlace(const char* text, char* left, char* right)
{
	strcpy(left, text);
	char* space = strrchr(left, ' ');
	if (space != 0) {
		*space = '\0';
		strcpy(right, space + 1);
	} else {
		right[0] = '\0';
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 188b
 * EN Address: 0x8011163C
 * EN Size: 216b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::SplitPlace2(const char* text, char* left, char* right, CFont* font, int width)
{
	char part[128];
	strcpy(left, text);
	right[0] = '\0';
	const char* searchPos = text;
	for (;;) {
		const char* space = strchr(searchPos, ' ');
		if (space == 0) {
			break;
		}
		const int firstLen = space - text;
		memcpy(part, text, firstLen);
		part[firstLen] = '\0';
		if (static_cast<int>(font->GetWidth(part)) > width) {
			break;
		}
		strcpy(left, part);
		strcpy(right, space + 1);
		searchPos = space + 1;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800F3F60
 * PAL Size: 3012b
 * EN Address: 0x800F34E0
 * EN Size: 3012b
 * JP Address: 0x800F048C
 * JP Size: 3004b
 */
void CMenuPcs::CalcWMFrame()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	short mainState = m_wmWorldState->m_mainState;
	if (mainState == 0) {
		return;
	}
	if (mainState > 2) {
		return;
	}

	if (mainState == 2 && bytes[0x13] != 0) {
		m_wm.m_frameData->m_titleFrame--;
		if (m_wm.m_frameData->m_titleFrame < 0) {
			m_wm.m_frameData->m_titleFrame = 0;
		}
	} else if ((m_wmChgFlags & WMDATA_CHG_AREA) != 0 && m_wm.m_frameData->m_titleFrame != 0) {
		m_wm.m_frameData->m_titleFrame--;
		if (m_wm.m_frameData->m_titleFrame < 0) {
			m_wm.m_frameData->m_titleFrame = 0;
		}
		if (m_wm.m_frameData->m_titleFrame == 0) {
			m_wmChgFlags &= ~WMDATA_CHG_AREA;
		}
	} else if (m_wm.m_frameData->m_titleFrame < 10) {
		m_wm.m_frameData->m_titleFrame++;
	}
	m_wm.m_frameData->m_titleSprite.m_x = 0x68;
	float titleTexU = FLOAT_803313dc;
	m_wm.m_frameData->m_titleSprite.m_y = 0x14;
	m_wm.m_frameData->m_titleSprite.m_width = kWorldTitleWidth;
	m_wm.m_frameData->m_titleSprite.m_height = 0x28;
	m_wm.m_frameData->m_titleSprite.m_u = titleTexU;

	if ((m_wmChgFlags & WMDATA_CHG_AREA) != 0) {
		WmFrameData* frameA = m_wm.m_frameData;
		int yOff = (int)frameA->m_titleSprite.m_height * m_wmPrevArea;
		frameA->m_titleSprite.m_v = (float)yOff;
	} else {
		WmFrameData* frameA = m_wm.m_frameData;
		int yOff = (int)frameA->m_titleSprite.m_height * m_wmArea;
		frameA->m_titleSprite.m_v = (float)yOff;
	}

	WmFrameData* wmFrame = m_wm.m_frameData;
	wmFrame->m_titleSprite.m_x =
	    (10 - wmFrame->m_titleFrame) * 2 + 0x68;

	if (((m_wmChgFlags & WMDATA_CHG_YEAR) != 0 ||
	     (m_wmWorldState->m_mainState == 2 && bytes[0x13] != 0))
	    && m_wm.m_frameData->m_yearFrame >= 10) {
		m_wm.m_frameData->m_yearFrame = 0;
		m_wmChgFlags &= ~WMDATA_CHG_YEAR;
	}

	unsigned int yearValue;
	if ((m_wmChgFlags & WMDATA_CHG_YEAR) != 0) {
		yearValue = Game.m_gameWork.m_scriptSysVal0 + m_wmPrevYear;
	} else {
		yearValue = Game.m_gameWork.m_scriptSysVal0 + m_wmYear;
	}
	gWmMenuScriptValueCache = (unsigned char)yearValue;
	if ((int)yearValue > 99) {
		gWmMenuScriptValueCache = 100;
	}

	int digitCount = ((int)yearValue > 9) ? 2 : 1;
	if ((int)yearValue > 99) {
		digitCount = 3;
	}

	float fE8 = FLOAT_803313e8;
	m_wm.m_frameData->m_yearSprites[0].m_scale = fE8;
	m_wm.m_frameData->m_yearSprites[1].m_scale = fE8;

	if (digitCount == 3) {
		int totalWidth = s_YearWTbl[10];
		const float fV1 = FLOAT_80331524;
		const float fV4 = FLOAT_80331528;
		m_wm.m_frameData->m_yearSprites[0].m_x = (0x2B - totalWidth) / 2 + 0x2C;
		m_wm.m_frameData->m_yearSprites[0].m_y = kWorldYearDigitY;
		m_wm.m_frameData->m_yearSprites[0].m_width = (short)totalWidth;
		m_wm.m_frameData->m_yearSprites[0].m_height = 0x20;
		m_wm.m_frameData->m_yearSprites[0].m_u = fV1;
		m_wm.m_frameData->m_yearSprites[0].m_v = fV4;
	} else {
		int digits[2];
		digits[0] = (int)yearValue % 10;
		if (1 < digitCount) {
			digits[1] = (int)yearValue / 10;
		}
		int totalWidth = s_YearWTbl[(int)yearValue % 10];
		if (1 < digitCount) {
			totalWidth = totalWidth + s_YearWTbl[(int)yearValue / 10];
		}
		int topDigitIdx = digitCount - 1;
		int digitX = (0x2B - totalWidth) / 2 + 0x2C;
		const double dV10 = DOUBLE_80331490;
		const double dV12 = DOUBLE_80331540;
		const double dV11 = DOUBLE_80331538;
		int wmDigitIdx;
		for (wmDigitIdx = topDigitIdx; wmDigitIdx >= 0; wmDigitIdx--) {
				int digit = digits[wmDigitIdx];
				m_wm.m_frameData->m_yearSprites[wmDigitIdx].m_x = (short)digitX;
				int digitW = s_YearWTbl[digit];
				m_wm.m_frameData->m_yearSprites[wmDigitIdx].m_y = kWorldYearDigitY;
				m_wm.m_frameData->m_yearSprites[wmDigitIdx].m_width = (short)digitW;
				m_wm.m_frameData->m_yearSprites[wmDigitIdx].m_height = 0x20;
				int col = digit % 5;
				int row = digit / 5;
				m_wm.m_frameData->m_yearSprites[wmDigitIdx].m_u = (float)(dV10 * (double)(float)col);
				m_wm.m_frameData->m_yearSprites[wmDigitIdx].m_v = (float)(dV12 * (double)(float)row + dV11);
				digitX = digitX + digitW;
		}
	}

	if ((m_wmChgFlags & WMDATA_CHG_YEAR) != 0 ||
	    (m_wmWorldState->m_mainState == 2 && bytes[0x13] != 0)) {
		for (int i = 0; i < digitCount; i++) {
			if (i != 0 && digitCount != 2) {
				break;
			}
			float fadeAlpha = static_cast<float>(
			    static_cast<double>(static_cast<float>(10 - m_wm.m_frameData->m_yearFrame)) / DOUBLE_803316E8);
			m_wm.m_frameData->m_yearSprites[i].m_alpha = fadeAlpha;
			m_wm.m_frameData->m_yearSprites[i].m_scale =
			    static_cast<float>(DOUBLE_803313F8 * static_cast<double>(fadeAlpha) + DOUBLE_803313F8);

			float scaledHeight = static_cast<float>(m_wm.m_frameData->m_yearSprites[i].m_height) *
			                     m_wm.m_frameData->m_yearSprites[i].m_scale;
			m_wm.m_frameData->m_yearSprites[i].m_y = static_cast<short>(
			    m_wm.m_frameData->m_yearSprites[i].m_y +
			    static_cast<int>(static_cast<float>(m_wm.m_frameData->m_yearSprites[i].m_height) - scaledHeight));

			if (i == 0 && (digitCount == 1 || digitCount == 3)) {
				float scaledWidth = static_cast<float>(m_wm.m_frameData->m_yearSprites[i].m_width) *
				                    m_wm.m_frameData->m_yearSprites[i].m_scale;
				m_wm.m_frameData->m_yearSprites[i].m_x = static_cast<short>(
				    m_wm.m_frameData->m_yearSprites[i].m_x +
				    static_cast<int>((DOUBLE_80331420 +
				                      static_cast<double>(static_cast<float>(m_wm.m_frameData->m_yearSprites[i].m_width) -
				                                          scaledWidth)) *
				                     DOUBLE_803313F8));
			} else if (i != 0) {
				float scaledWidth = static_cast<float>(m_wm.m_frameData->m_yearSprites[i].m_width) *
				                    m_wm.m_frameData->m_yearSprites[i].m_scale;
				m_wm.m_frameData->m_yearSprites[i].m_x = static_cast<short>(
				    m_wm.m_frameData->m_yearSprites[i].m_x +
				    static_cast<int>(static_cast<float>(m_wm.m_frameData->m_yearSprites[i].m_width) - scaledWidth));
			}
		}
		WmFrameData* wmEnd = m_wm.m_frameData;
		wmEnd->m_yearFrame = wmEnd->m_yearFrame + 1;
	} else {
		WmFrameData* base = m_wm.m_frameData;
		unsigned int uVar = (unsigned int)base->m_yearFrame;
		if (static_cast<float>(static_cast<int>(uVar - 5)) <
		    static_cast<float>(DOUBLE_803314A8 * static_cast<double>(s_YearTrns.keys[s_YearTrns.keyCount - 1].time))) {
			float t = static_cast<float>(static_cast<int>(uVar));
			float yTrans;
			yTrans = GetFcvValue(s_YearTrns, t);
			base->m_yearSprites[1].m_y =
			    static_cast<short>(static_cast<int>(static_cast<float>(base->m_yearSprites[1].m_y) + yTrans));

			float curveAlpha;
			curveAlpha = GetFcvValue(s_YearAlpha, t);
			m_wm.m_frameData->m_yearSprites[1].m_alpha = curveAlpha;

			if (digitCount == 2) {
				uVar -= 5;
			}
			t = static_cast<float>(static_cast<int>(uVar));
			yTrans = GetFcvValue(s_YearTrns, t);
			m_wm.m_frameData->m_yearSprites[0].m_y =
			    static_cast<short>(static_cast<int>(
			        static_cast<float>(m_wm.m_frameData->m_yearSprites[0].m_y) + yTrans));

			curveAlpha = GetFcvValue(s_YearAlpha, t);
			m_wm.m_frameData->m_yearSprites[0].m_alpha = curveAlpha;
			m_wm.m_frameData->m_yearFrame =
			    m_wm.m_frameData->m_yearFrame + 1;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800F36AC
 * PAL Size: 2228b
 * EN Address: 0x800F2C2C
 * EN Size: 2228b
 * JP Address: 0x800EFE88
 * JP Size: 1540b
 */
void CMenuPcs::DrawWMFrame()
{

	GXColor matColor;
	short sVar = m_wmWorldState->m_mainState;
	float alpha;
	if (sVar == 0) {
		const double dMin = DOUBLE_803314F0;
		m_wmWorldState->m_posX -= FLOAT_80331550;
		if (static_cast<double>(m_wmWorldState->m_posX) <= dMin) {
			m_wmWorldState->m_posX = FLOAT_803313dc;
		}
		alpha = static_cast<float>(DOUBLE_803316D8 * static_cast<double>(m_wmWorldState->m_frameCounter));
	} else if (sVar == 3) {
		const double dMax = DOUBLE_803316E0;
		m_wmWorldState->m_posX += FLOAT_80331550;
		if (static_cast<double>(m_wmWorldState->m_posX) >= dMax) {
			m_wmWorldState->m_posX = FLOAT_80331440;
		}
		alpha = static_cast<float>(-(DOUBLE_803316D8 * static_cast<double>(m_wmWorldState->m_frameCounter) -
		                             DOUBLE_80331508));
	} else {
		alpha = FLOAT_80331458;
	}

	Mtx rotMtx;
	PSMTXRotRad(rotMtx, 'z', m_wmWorldState->m_posX * FLOAT_803314bc);
	rotMtx[0][3] = FLOAT_803315B0;
	rotMtx[1][3] = FLOAT_803315B4;
	rotMtx[2][3] = FLOAT_803313dc;

	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXColor frameColor;
	matColor.r = 0xFF;
	matColor.g = 0xFF;
	matColor.b = 0xFF;
	matColor.a = static_cast<unsigned char>(static_cast<int>(alpha));
	GXSetChanMatColor(static_cast<GXChannelID>(4), matColor);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kWorldWoodTexture));

	const float baseX = FLOAT_803315B0;
	const float baseY = FLOAT_803315B4;
	for (int i = 0; i < 5; i++) {
		Sprt* const entry = &m_wm.m_frameData->m_frameSprites[i];
		MenuPcs.DrawRect2(
			0,
			static_cast<float>(entry->m_x) - baseX,
			static_cast<float>(entry->m_y) - baseY,
			(float)entry->m_width,
			(float)entry->m_height,
			entry->m_u,
			entry->m_v,
			FLOAT_803313e8,
			FLOAT_803313e8,
			rotMtx);
	}

	short mainState = m_wmWorldState->m_mainState;
	if (mainState != 0 && mainState <= 3) {
		MenuPcs.SetTexture((TEX)kMcYearTexture);
		unsigned char gaugeAlpha = static_cast<unsigned char>(static_cast<int>(
		    DOUBLE_80331508 *
		    (static_cast<float>(m_wm.m_frameData->m_titleFrame) /
		     DOUBLE_803316E8)));
		matColor.r = 0xFF;
		matColor.g = 0xFF;
		matColor.b = 0xFF;
		matColor.a = gaugeAlpha;
		GXSetChanMatColor(static_cast<GXChannelID>(4), matColor);
		const float kZeroG = FLOAT_803313dc;
		MenuPcs.DrawRect(0,
			(float)m_wm.m_frameData->m_titleSprite.m_x,
			(float)m_wm.m_frameData->m_titleSprite.m_y,
			(float)m_wm.m_frameData->m_titleSprite.m_width,
			(float)m_wm.m_frameData->m_titleSprite.m_height,
			m_wm.m_frameData->m_titleSprite.m_u,
			m_wm.m_frameData->m_titleSprite.m_v,
			FLOAT_803313e8,
			FLOAT_803313e8,
			kZeroG);

		if (m_wmWorldState->m_mainState <= 2) {
#ifdef VERSION_GCCJGC
			MenuPcs.SetAttrFmt((FMT)0);
#else
			const int language = Game.m_gameWork.GetLanguage();
			MenuPcs.SetAttrFmt((FMT)0);
				matColor.r = 0xFF;
			matColor.g = 0xFF;
			matColor.b = 0xFF;
			matColor.a = 0xFF;
			GXSetChanMatColor(static_cast<GXChannelID>(4), matColor);
			MenuPcs.SetTexture((TEX)0x21);
			const float kZeroYear = FLOAT_803313dc;
			float yearY = language != 5 ? FLOAT_803316F4 : FLOAT_803316F8;
			MenuPcs.DrawRect(0,
				FLOAT_803316F0, yearY,
				FLOAT_80331440, FLOAT_80331558,
				FLOAT_803313dc, FLOAT_803313dc,
				FLOAT_803313e8, FLOAT_803313e8,
				kZeroYear);

			MenuPcs.SetAttrFmt((FMT)0);
			MenuPcs.SetTexture((TEX)kMcYearTexture);
#endif

			unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
			int dispValue =
			    m_wmChgFlags & WMDATA_CHG_YEAR
			        ? static_cast<int>(Game.m_gameWork.m_scriptSysVal0) + m_wmPrevYear
			        : static_cast<int>(Game.m_gameWork.m_scriptSysVal0) + m_wmYear;
			int digitCnt;
			digitCnt = (dispValue > 9) + 1;
			if (dispValue > 99) {
				digitCnt = 3;
			}
#ifdef VERSION_GCCJGC
			const int languageYOffset = 0;
#else
			const int languageYOffset = language != 5 ? 0 : 0xE;
#endif

			if (digitCnt == 3) {
				int alphaInt =
				    static_cast<int>(DOUBLE_80331508 * static_cast<double>(m_wm.m_frameData->m_yearSprites[0].m_alpha));
				matColor.r = 0xFF;
				matColor.g = 0xFF;
				matColor.b = 0xFF;
				matColor.a = alphaInt;
				GXSetChanMatColor(static_cast<GXChannelID>(4), matColor);
				const float kZero3 = FLOAT_803313dc;
				MenuPcs.DrawRect(0,
					(float)m_wm.m_frameData->m_yearSprites[0].m_x,
					(float)(m_wm.m_frameData->m_yearSprites[0].m_y + languageYOffset),
					(float)m_wm.m_frameData->m_yearSprites[0].m_width,
					(float)m_wm.m_frameData->m_yearSprites[0].m_height,
					m_wm.m_frameData->m_yearSprites[0].m_u,
					m_wm.m_frameData->m_yearSprites[0].m_v,
					m_wm.m_frameData->m_yearSprites[0].m_scale,
					m_wm.m_frameData->m_yearSprites[0].m_scale,
					kZero3);
			} else {
				const double k255 = DOUBLE_80331508;
				const float kZero = FLOAT_803313dc;
				for (int i = 0; i < digitCnt; i++) {
					int alphaInt =
					    static_cast<int>(k255 * static_cast<double>(m_wm.m_frameData->m_yearSprites[i].m_alpha));
						matColor.r = 0xFF;
					matColor.g = 0xFF;
					matColor.b = 0xFF;
					matColor.a = alphaInt;
					GXSetChanMatColor(static_cast<GXChannelID>(4), matColor);
					MenuPcs.DrawRect(0,
						(float)m_wm.m_frameData->m_yearSprites[i].m_x,
						(float)(m_wm.m_frameData->m_yearSprites[i].m_y + languageYOffset),
						(float)m_wm.m_frameData->m_yearSprites[i].m_width,
						(float)m_wm.m_frameData->m_yearSprites[i].m_height,
						m_wm.m_frameData->m_yearSprites[i].m_u,
						m_wm.m_frameData->m_yearSprites[i].m_v,
						m_wm.m_frameData->m_yearSprites[i].m_scale,
						m_wm.m_frameData->m_yearSprites[i].m_scale,
						kZero);
				}
			}

#ifndef VERSION_GCCJGC
			if (digitCnt != 3 && language != 5) {
				Sprt* digit = &m_wm.m_frameData->m_yearSprites[0];
				float suffixU = FLOAT_803313dc;
				float suffixX = static_cast<float>(digit->m_width) * digit->m_scale +
				                static_cast<float>(digit->m_x);
				float suffixY = static_cast<float>(digit->m_y);
				float suffixScale = digit->m_scale;
				if (language == 1) {
					if (gWmMenuScriptValueCache / 10 == 1) {
						suffixU = FLOAT_8033151c;
					} else {
						int digit = gWmMenuScriptValueCache % 10;
						if (digit >= 1 && digit <= 3) {
							suffixU = FLOAT_803314D8 * static_cast<float>(digit - 1);
						} else {
							suffixU = FLOAT_8033151c;
						}
					}
				} else if (language == 4) {
					if (gWmMenuScriptValueCache != 1) {
						suffixU = FLOAT_803314D8;
					}
				} else if (language == 2) {
					suffixY += FLOAT_80331550;
				}
				int alphaInt =
				    static_cast<int>(DOUBLE_80331508 * static_cast<double>(digit->m_alpha));
				MenuPcs.SetAttrFmt((FMT)0);
				matColor.r = 0xFF;
				matColor.g = 0xFF;
				matColor.b = 0xFF;
				matColor.a = alphaInt;
				GXSetChanMatColor(static_cast<GXChannelID>(4), matColor);
				MenuPcs.SetTexture((TEX)0x34);
				MenuPcs.DrawRect(0,
				         suffixX,
				         suffixY,
				         FLOAT_80331410, FLOAT_803314D8,
				         FLOAT_803313dc, suffixU,
				         suffixScale, suffixScale,
				         FLOAT_803313dc);
			}
#endif
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800f3500
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcWMFrame0(int param)
{
	int value;

	m_wm.m_frameInfo->m_sprites[0].m_x = 0x10;
	m_wm.m_frameInfo->m_sprites[1].m_x = FLOAT_803313e0 - (m_wm.m_frameInfo->m_sprites[0].m_width + m_wm.m_frameInfo->m_sprites[0].m_x);

	if (param < 0) {
		float offset = static_cast<float>(static_cast<int>(m_wm.m_frameInfo->m_sprites[0].m_width) +
		                                  static_cast<int>(m_wm.m_frameInfo->m_sprites[0].m_x));
		if (param >= -10) {
			offset *= DOUBLE_803314E8 * abs(param);
			int absParam = abs(param);
			if (absParam < 0) {
				absParam = 0;
			}
			if (absParam > 10) {
				absParam = 10;
			}
			float angleScale = FLOAT_803316D4;
			offset *= sinf(FLOAT_803314bc * (static_cast<float>(absParam) * angleScale));
		}
		value = static_cast<int>(static_cast<float>(static_cast<int>(m_wm.m_frameInfo->m_sprites[0].m_x)) - offset);
		m_wm.m_frameInfo->m_sprites[0].m_x = static_cast<short>(value);
		value = static_cast<int>(static_cast<float>(static_cast<int>(m_wm.m_frameInfo->m_sprites[1].m_x)) + offset);
		m_wm.m_frameInfo->m_sprites[1].m_x = static_cast<short>(value);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800F3384
 * PAL Size: 380b
 * EN Address: 0x800F2904
 * EN Size: 380b
 * JP Address: 0x800EFB58
 * JP Size: 380b
 */
void CMenuPcs::DrawWMFrame0(int mask, float alpha)
{
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	GXColor color;
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = static_cast<unsigned char>(static_cast<int>(DOUBLE_80331508 * static_cast<double>(alpha)));
	GXSetChanMatColor(static_cast<GXChannelID>(4), color);

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kWorldFrameTexture));

	int i;
	i = 0;
	do {
		if ((static_cast<unsigned int>(mask) & (1 << i)) != 0) {
			Sprt* sprite = &m_wm.m_frameInfo->m_sprites[i];
			MenuPcs.DrawRect(sprite->m_flags, static_cast<float>(static_cast<int>(sprite->m_x)), static_cast<float>(static_cast<int>(sprite->m_y)),
			         static_cast<float>(static_cast<int>(sprite->m_width)), static_cast<float>(static_cast<int>(sprite->m_height)),
			         sprite->m_u, sprite->m_v,
			         1.0f, 1.0f, 0.0f);
		}
		i = i + 1;
	} while (i < 2);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 388b
 * EN Address: 0x801130AC
 * EN Size: 548b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::DrawMainMenuBase(float alpha)
{
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXColor color;
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = static_cast<unsigned char>(static_cast<int>(255.0 * alpha));
	GXSetChanMatColor(GX_COLOR0A0, color);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kMainMenuFrameTexture));

	float y = 40.0f;
	float x = 32.0f;
	y -= x;
	MenuPcs.DrawRect(0, x, y, 288.0f, 184.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	x += 288.0f;
	MenuPcs.DrawRect(8, x, y, 288.0f, 184.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	y += 184.0f;
	x = 32.0f;
	MenuPcs.DrawRect(4, x, y, 288.0f, 184.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	x += 288.0f;
	MenuPcs.DrawRect(12, x, y, 288.0f, 184.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 4b
 * EN Address: 0x801132D0
 * EN Size: 4b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CalcCharaBase()
{
}

/*
 * --INFO--
 * PAL Address: 0x800F31B8
 * PAL Size: 460b
 * EN Address: 0x800F2738
 * EN Size: 460b
 * JP Address: 0x800EF99C
 * JP Size: 444b
 */
void CMenuPcs::DrawCharaBase()
{
	short state;
	WmWorldState* const worldState = m_wmWorldState;
	state = worldState->m_mainState;
	if (state == 0) {
		return;
	}

	float alpha;
	if (state == 1) {
		alpha = static_cast<float>(DOUBLE_803316C0 * static_cast<double>(worldState->m_frameCounter));
	} else if (state == 2) {
		alpha = FLOAT_80331668;
	} else {
		alpha = static_cast<float>(DOUBLE_80331448 - DOUBLE_803316C0 * static_cast<double>(worldState->m_frameCounter));
	}

	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXColor color;
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = static_cast<unsigned char>(static_cast<int>(DOUBLE_80331508 * static_cast<double>(alpha)));
	GXSetChanMatColor(static_cast<GXChannelID>(4), color);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kCharacterPanelTexture));

	alpha = FLOAT_803313dc;
	int yBase;
	int row = 0;
	yBase = 0x22;
	for (; row < 2; row++) {
		for (int col = 0; col < 4; col++) {
			int yInt = yBase;
			if (row != 0) {
				yInt = yBase + 8;
			}
			const float y = static_cast<float>(yInt);
			const float x = static_cast<float>(0x1C + col * 0x90);
			MenuPcs.DrawRect(0, x, y, FLOAT_803316C8, FLOAT_803316CC, alpha, alpha, FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
		}
		yBase += 0xB8;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800f2b00
 * PAL Size: 1720b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcChara()
{
	int i;
	int player;
	WmWorldObjInfo* charaWork = &m_wm.m_worldObjData[32];
	unsigned int selectedMask = 0;

	for (i = 0; i < kWmMenuControllerCount; i++) {
		if (m_wm.m_charaSelectData[i].m_connected == 1) {
			selectedMask |= 1u << static_cast<unsigned int>(m_wm.m_charaSelectData[i].m_currentSlot);
		}
	}

	for (i = 0; i < 8; i++) {
		unsigned int effectMask = 0;
		int effectCount = 0;

		for (player = 0; player < 4; player++) {
			WmCharaSelectEntry* const entry = &m_wm.m_charaSelectData[player];
			const int currentSlot = entry->m_currentSlot;
			if ((entry->m_connected == 1) && (currentSlot >= 0) && (i == currentSlot)) {
				effectCount++;
				effectMask |= 1u << player;
			}
		}

		if (effectCount != 0) {
			float offset;
			if (effectCount == 1) {
				offset = FLOAT_803313dc;
			} else if (effectCount == 2) {
				offset = FLOAT_80331588;
			} else if (effectCount == 3) {
				offset = FLOAT_8033169C;
			} else {
				offset = FLOAT_803316A0;
			}

			for (player = 0; player < 4; player++) {
				if ((effectMask & (1u << player)) != 0) {
					Vec loc;
					const int partNo = m_effectWork[player + 32].m_partNo;
					loc.x = s_RingOrgPos.x;
					loc.y = s_RingOrgPos.y;
					loc.z = s_RingOrgPos.z;
					loc.y = static_cast<float>((double)s_RingOrgPos.y + (DOUBLE_80331420 + (double)offset));
					PartPcs.SetParLocIdx(partNo, loc);
					offset = offset - FLOAT_8033169C;
				}
			}
		}
	}

	int handleIdx = 0x20;
	for (i = 0; i < kWmMenuPlayerCount; i++, charaWork++, handleIdx++) {
		CCharaPcs::CHandle* const handle = m_wm.m_handles[handleIdx];
		if (!handle->IsModelLoaded(1)) {
			charaWork->m_active = 0;
			continue;
		}

		WmCharaModelInfo* const modelData = &m_wm.m_charaModelData[i];
		if (modelData->m_modelChanged == 1) {
			charaWork->m_transform.m_rotation.y = FLOAT_80331664;
			SetAnim(i);
			modelData->m_modelChanged = 0;
		}

		charaWork->m_active = 1;
		CCharaPcs::CHandle* const charaHandle = m_wm.m_handles[handleIdx];
		if (charaHandle->m_charaKind == 3) {
			if ((selectedMask & (1u << i)) != 0) {
				const float zero = FLOAT_803313dc;
				float normalX = FLOAT_803316A4;
				charaWork->m_transform.m_position.x = zero;
				const float scale = FLOAT_803316A8;
				charaWork->m_transform.m_position.y = normalX;
				normalX = FLOAT_803316AC;
				charaWork->m_transform.m_position.z = zero;
				charaWork->m_transform.m_scale.x = scale;
				charaWork->m_transform.m_scale.y = scale;
				charaWork->m_transform.m_scale.z = scale;
				charaWork->m_transform.m_rotation.x = normalX;
				charaWork->m_transform.m_rotation.y = zero;
			} else {
				const float zero = FLOAT_803313dc;
				const float scale = FLOAT_803313e8;
				charaWork->m_transform.m_position.x = zero;
				charaWork->m_transform.m_position.y = zero;
				charaWork->m_transform.m_position.z = zero;
				charaWork->m_transform.m_scale.x = scale;
				charaWork->m_transform.m_scale.y = scale;
				charaWork->m_transform.m_scale.z = scale;
				charaWork->m_transform.m_rotation.x = zero;
				charaWork->m_transform.m_rotation.y = zero;
			}
		} else if ((selectedMask & (1u << i)) != 0) {
			const float zero = FLOAT_803313dc;
			float normalX = FLOAT_803316B0;
			charaWork->m_transform.m_position.x = zero;
			const float scale = FLOAT_803316B4;
			charaWork->m_transform.m_position.y = normalX;
			normalX = FLOAT_803316B8;
			charaWork->m_transform.m_position.z = zero;
			charaWork->m_transform.m_scale.x = scale;
			charaWork->m_transform.m_scale.y = scale;
			charaWork->m_transform.m_scale.z = scale;
			charaWork->m_transform.m_rotation.x = normalX;
		} else {
			const float zero = FLOAT_803313dc;
			float normalX = FLOAT_803316BC;
			charaWork->m_transform.m_position.x = zero;
			const float scale = FLOAT_80331434;
			charaWork->m_transform.m_position.y = normalX;
			normalX = FLOAT_803315d0;
			charaWork->m_transform.m_position.z = zero;
			charaWork->m_transform.m_scale.x = scale;
			charaWork->m_transform.m_scale.y = scale;
			charaWork->m_transform.m_scale.z = scale;
			charaWork->m_transform.m_rotation.x = normalX;
		}

		WmWorldState* const ws = m_wmWorldState;
		float alpha = static_cast<float>(DOUBLE_803314E8 * static_cast<double>(ws->m_frameCounter));
		if (alpha > DOUBLE_80331420) {
			alpha = FLOAT_803313e8;
		}

		const int state = ws->m_mainState;
		if (state == 1) {
			m_wm.m_handles[handleIdx]->m_model->m_lightAlpha = alpha;
		} else if (state == 2) {
			m_wm.m_handles[handleIdx]->m_model->m_lightAlpha = FLOAT_803313e8;
		} else {
			m_wm.m_handles[handleIdx]->m_model->m_lightAlpha = static_cast<float>(DOUBLE_80331420 - alpha);
		}

		Mtx scaleMtx;
		Mtx rotXMtx;
		Mtx rotYMtx;
		PSMTXScale(scaleMtx, charaWork->m_transform.m_scale.x, charaWork->m_transform.m_scale.y,
		           charaWork->m_transform.m_scale.z);
		PSMTXRotRad(rotXMtx, 'x', charaWork->m_transform.m_rotation.x);
		PSMTXRotRad(rotYMtx, 'y', charaWork->m_transform.m_rotation.y);
		PSMTXConcat(rotXMtx, rotYMtx, rotXMtx);
		rotXMtx[0][3] = charaWork->m_transform.m_position.x;
		rotXMtx[1][3] = charaWork->m_transform.m_position.y;
		rotXMtx[2][3] = charaWork->m_transform.m_position.z;
		PSMTXConcat(rotXMtx, scaleMtx, scaleMtx);
		m_wm.m_handles[handleIdx]->m_model->SetMatrix(scaleMtx);
		m_wm.m_handles[handleIdx]->m_model->CalcMatrix();
		m_wm.m_handles[handleIdx]->m_model->CalcSkin();
	}

	PCAnimCtrl();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 180b
 * EN Address: TODO
 * EN Size: 244b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::GetAnimNo(int slot, int anim)
{
	int base = (static_cast<int>(static_cast<unsigned int>(GetWmCharaHandles(this)[slot]->m_charaNo) / 100) - 1) * 6;
	return base + anim;
}

/*
 * --INFO--
 * PAL Address: 0x800f26f4
 * PAL Size: 1036b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::PCAnimCtrl()
{
	WmCharaSelectEntry* const charaSelect = m_wm.m_charaSelectData;
	int isSelected;
	int i;
	unsigned int selectedMask;
	WmCharaAnimState* animState;
	CCharaPcs::CHandle* handle;

	selectedMask = 0;
	for (int j = 0; j < kWmMenuControllerCount; j++) {
		if (charaSelect[j].m_connected != 0 && charaSelect[j].m_confirmed != 0) {
			selectedMask |= 1 << charaSelect[j].m_currentSlot;
		}
	}

	animState = m_wmCharaAnimState;
	for (i = 0; i < kWmMenuPlayerCount; i++, animState++) {
		handle = GetWmCharaHandles(this)[i];
		const int blendMode = handle->GetCurrentAnimNumber() < 0 ? 0 : -1;

		CChara::CModel* const model = handle->m_model;
		if (model == 0 || model->m_texSet == 0 || handle->m_charaKind == 3) {
			continue;
		}

		animState->m_frame = model->m_time;

		if (animState->m_nextAnimIndex >= 0) {
			animState->m_animIndex = animState->m_nextAnimIndex;
			animState->m_nextAnimIndex = -1;
			handle->SetAnim(GetAnimNo(i, animState->m_animIndex), -1, -1, blendMode, 0);
			animState->m_frame = handle->m_model->GetNowFrame();
			animState->m_endFrame = handle->m_model->GetEndFrame();
			animState->m_timer = 0;
			continue;
		}

		isSelected = selectedMask & (1u << static_cast<unsigned int>(i));
		if (isSelected == 0 &&
		    m_wmWorldState->m_menuMode != 8 &&
		    animState->m_animIndex == 0 && animState->m_timer >= 3000) {
			animState->m_animIndex = 4;
			handle->SetAnim(GetAnimNo(i, animState->m_animIndex), -1, -1, blendMode, 0);
			animState->m_frame = handle->m_model->GetNowFrame();
			animState->m_endFrame = handle->m_model->GetEndFrame();
			animState->m_timer = 0;
		} else if (isSelected != 0 &&
		           m_wmWorldState->m_menuMode != 8) {
			if (animState->m_animIndex == 1 && animState->m_timer >= 12000) {
				animState->m_animIndex = 0;
				animState->m_timer = 0;
			} else if (animState->m_animIndex == 2 && animState->m_timer >= 9000) {
				animState->m_animIndex = 1;
			} else if (animState->m_animIndex == 1 && animState->m_timer >= 6000 && animState->m_timer < 9000) {
				animState->m_animIndex = 2;
			} else if (animState->m_animIndex == 0 && animState->m_timer >= 3000) {
				animState->m_animIndex = 1;
			} else {
				goto frameStep;
			}

			handle->SetAnim(GetAnimNo(i, animState->m_animIndex), -1, -1, blendMode, 0);
			animState->m_frame = handle->m_model->GetNowFrame();
			animState->m_endFrame = handle->m_model->GetEndFrame();
		} else {
		frameStep:
			const float frame = animState->m_frame;
			const float frameEnd = animState->m_endFrame;
			if (frame < frameEnd) {
				handle->m_model->AddFrame(FLOAT_80331698);
				animState->m_timer++;
			} else {
				if (animState->m_animIndex == 3 || animState->m_animIndex == 4 || animState->m_animIndex == 5) {
					animState->m_animIndex = 0;
					handle->SetAnim(GetAnimNo(i, animState->m_animIndex), -1, -1, blendMode, 0);
					animState->m_frame = handle->m_model->GetNowFrame();
					animState->m_endFrame = handle->m_model->GetEndFrame();
					if (isSelected != 0) {
						animState->m_timer = 0x834;
					} else {
						animState->m_timer = 0;
					}
				}
				handle->m_model->SetFrame(FLOAT_803313dc);
				animState->m_timer++;
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800f2034
 * PAL Size: 1728b
 * EN Address: 0x800F15B4
 * EN Size: 1728b
 * JP Address: 0x800EE7D4
 * JP Size: 1728b
 */
void CMenuPcs::DrawChara()
{
	WmWorldObjInfo* view = &m_wm.m_worldObjData[32];
	int viewSlot = 32;
	for (int i = 0; i < kWmMenuPlayerCount; i++, viewSlot++, view++) {
		if (view->m_active == 0) {
			continue;
		}

		int selectedMask = 0;
		for (int chan = 0; chan < 4; chan++) {
			WmCharaSelectEntry& entry = m_wm.m_charaSelectData[chan];
			const int slot = entry.m_currentSlot;
			if (entry.m_connected == 1 && slot >= 0 && i == slot) {
				selectedMask |= 1 << chan;
			}
		}

		CCharaPcs::CHandle* const handle = GetWmCharaHandles(this)[i];
		if (handle->m_charaKind != 3 && handle->GetCurrentAnimNumber() < 0) {
			continue;
		}

		SetProjection(viewSlot);
		SetLight(0);
		if (GetWmCharaHandles(this)[i]->m_charaKind != 3) {
			m_wm.m_handles[viewSlot]->Draw(5);
		} else {
			DrawInit();
			GXSetZMode(GX_TRUE, static_cast<GXCompare>(7), GX_TRUE);
			SetProjection(viewSlot);
			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kCharacterPlaceholderTexture));
			MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
			float alpha;
			if (m_wmWorldState->m_mainState == 2) {
				const float* pOneAl = &FLOAT_803313e8;
				alpha = *pOneAl;
			} else {
				alpha = GetWmCharaHandles(this)[i]->m_model->m_lightAlpha;
			}
			double colorScaleD;
			if (selectedMask != 0) {
				const double* pFull = &DOUBLE_80331420;
				colorScaleD = *pFull;
			} else {
				const double* pDim = &DOUBLE_80331448;
				colorScaleD = *pDim;
			}
			const float colorScale = static_cast<float>(colorScaleD);
			const double* pAScale = &DOUBLE_80331508;
			GXColor color;
			color.r = static_cast<unsigned char>(FLOAT_80331458 * colorScale);
			color.g = static_cast<unsigned char>(FLOAT_80331458 * colorScale);
			color.b = static_cast<unsigned char>(FLOAT_80331458 * colorScale);
			color.a = static_cast<unsigned char>(*pAScale * static_cast<double>(alpha));
			GXSetChanMatColor(static_cast<GXChannelID>(4), color);
			const float* pX1 = &FLOAT_8033161C;
			const float* pX2 = &FLOAT_8033168C;
			const float* pY1 = &FLOAT_803314cc;
			const float* pSc1 = &FLOAT_80331690;
			float x = *pX1 - *pX2;
			float y = *pY1;
			float scale = *pSc1;
			if (selectedMask != 0) {
				const float* pSel = &FLOAT_803315d4;
				scale *= *pSel;
				x *= *pSel;
				y *= *pSel;
			}
			MenuPcs.DrawRect3d(0, x, y, FLOAT_80331694, FLOAT_80331578, FLOAT_80331520,
			                   FLOAT_803313dc, FLOAT_803313dc, scale, scale);
			GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
		}
		if (m_wmWorldState->m_mainState == 2 && selectedMask != 0) {
			for (int chan = 3; chan >= 0; chan--) {
				if ((selectedMask & (1 << chan)) != 0) {
					PartPcs.DrawMenuIdx(m_effectWork[chan + 32].m_partNo);
				}
			}
		}
	}

	DrawInit();
}

/*
 * --INFO--
 * PAL Address: 0x800f2018
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::GetModelNo(int modelNo, int offset, int baseType)
{
	int result = modelNo * 200 + 100;
	if (baseType != 0) {
		result += 100;
	}
	result += offset;
	return result;
}

/*
 * --INFO--
 * PAL Address: 0x800f0a70
 * PAL Size: 5544b
 * EN Address: 0x800F0118
 * EN Size: 5248b
 * JP Address: 0x800ED4EC
 * JP Size: 4812b
 */
void CMenuPcs::CalcCharaSelect()
{
	int i;
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	unsigned short padRepeat[4];
	unsigned short padTrig[4];
	int requestCancel;
	int requestFinalize;
#ifndef VERSION_GCCJGC
	unsigned int confirmedSlotMask;
	unsigned int pendingMask;
#endif

	m_wmHelpTimer = static_cast<short>(m_wmHelpTimer + 1);
#ifdef VERSION_GCCJGC
	if (m_wmHelpTimer >= 270) {
#else
	if (m_wmHelpTimer >= (Game.m_gameWork.m_menuStageMode == 0 ? 3 : 2) * 0x4B) {
#endif
		m_wmHelpTimer = 0;
	}

	requestCancel = 0;
	requestFinalize = 0;
	for (i = 0; i < 4; i++) {
		WmCharaSelectEntry& entry = m_wm.m_charaSelectData[i];

		if ((i != 0) && (Game.m_gameWork.m_menuStageMode != 0)) {
			padRepeat[i] = 0;
			padTrig[i] = 0;
			entry.m_connected = 0;
			continue;
		}

		entry.m_padType = Joybus.GetPadType(i);
		if ((entry.m_padType == 0x09000000) || (entry.m_padType == -0x74F00000) ||
		    (entry.m_padType == -0x78000000)) {
			if (Game.m_gameWork.m_menuStageMode == 0) {
				entry.m_connected = 0;
			} else {
				entry.m_connected = 1;
			}
		} else {
			entry.m_connected = static_cast<unsigned char>(Joybus.GetGBAConnect(i));
		}

		if (entry.m_connected == 1 && entry.m_cmakePending == 0) {
			padRepeat[i] = Pad.GetButtonRepeat(i);
			padTrig[i] = Pad.GetButtonDown(i);
		} else {
			padRepeat[i] = 0;
			padTrig[i] = 0;
		}
	}

	if (GetWmWorldState(this)->m_mainState != 2 || GetWmWorldState(this)->m_nextMenuMode != 0) {
		return;
	}

	if (m_menuWindowInfo->state != 3) {
		unsigned short anyTrig;
		for (i = anyTrig = 0; i < 4; i++) {
			anyTrig |= padTrig[i];
		}
		if (m_menuWindowInfo->state == 1 && (anyTrig & 0x300) != 0) {
			m_menuWindowInfo->state = 2;
			for (i = 0; i < 4; i++) {
				WmCharaSelectEntry& entry = m_wm.m_charaSelectData[i];
				if (entry.m_confirmed != 0) {
					GetWmCharaAnimState(this)[entry.m_currentSlot].m_nextAnimIndex = 0;
				}
				entry.m_confirmed = 0;
				entry.m_cmakePending = 0;
				entry.m_cmakeReady = 0;
			}
			Sound.PlaySe(2, 0x40, 0x7F, 0);
		}
		return;
	}
	{
#ifdef VERSION_GCCJGC
		for (i = 0; i < 4; i++) {
			if (Game.m_gameWork.m_menuStageMode != 0) {
				break;
			}
			WmCharaSelectEntry& entry = m_wm.m_charaSelectData[i];
			if (entry.m_connected != 0 && entry.m_cmakePending == 0 && static_cast<int>(Joybus.GetMType(i)) == 1) {
				Joybus.SetMType(i, 4);
			}
		}
#else
		pendingMask = 0;
		for (i = 0; i < 4; i++) {
			if (Game.m_gameWork.m_menuStageMode != 0) {
				break;
			}
			if (m_wm.m_charaSelectData[i].m_cmakePending != 0) {
				pendingMask |= 1u << static_cast<unsigned int>(m_wm.m_charaSelectData[i].m_currentSlot);
			}
		}

		for (i = 0; i < 4; i++) {
			if (Game.m_gameWork.m_menuStageMode != 0) {
				break;
			}
			WmCharaSelectEntry& entry = m_wm.m_charaSelectData[i];

			if (entry.m_connected == 0) {
				GbaQue.ClrCmakeInfo(i);
				if (entry.m_cmakeReady == 1) {
					entry.m_cmakeReady = 0;
				} else if ((pendingMask & (1u << static_cast<unsigned int>(entry.m_currentSlot))) != 0) {
					continue;
				}

				const int slot = entry.m_currentSlot;
				const int handleIdx = slot + 0x20;
				if (Game.m_caravanWorkArr[slot].m_shopState == 0 &&
				    m_wm.m_handles[handleIdx]->IsModelLoaded(1) &&
				    m_wm.m_handles[handleIdx]->m_charaKind != 3 &&
				    entry.m_cmakeReady != 1) {
					if (static_cast<unsigned int>(System.m_execParam) >= 3) {
						System.Printf("chan = %d cur = %d\n", i,
						              static_cast<int>(entry.m_currentSlot));
					}
					ChgModel(entry.m_currentSlot, -1, -1, -1);
				}
			} else if (entry.m_cmakePending == 0 && static_cast<int>(Joybus.GetMType(i)) == 1) {
				Joybus.SetMType(i, 4);
			}
		}

		confirmedSlotMask = 0;
		for (i = 0; i < 4; i++) {
			if (m_wm.m_charaSelectData[i].m_confirmed != 0) {
				confirmedSlotMask |= 1u << static_cast<unsigned int>(m_wm.m_charaSelectData[i].m_currentSlot);
			}
		}

		for (int slot = 0; slot < 8; slot++) {
			const int handleIdx = slot + 0x20;
			if (((confirmedSlotMask & (1u << static_cast<unsigned int>(slot))) == 0) &&
			    ((pendingMask & (1u << static_cast<unsigned int>(slot))) == 0) &&
			    Game.m_caravanWorkArr[slot].m_shopState == 0 &&
			    m_wm.m_handles[handleIdx]->IsModelLoaded(1) &&
			    m_wm.m_handles[handleIdx]->m_charaKind != 3) {
				ChgModel(slot, -1, -1, -1);
			}
		}

#endif

		int connectedCount = 0;
		int locallyConfirmedCount = 0;
		int readyMask;
		for (i = readyMask = 0; i < 4; i++) {
			WmCharaSelectEntry& entry = m_wm.m_charaSelectData[i];
			if (entry.m_connected != 0) {
				CCaravanWork& work = Game.m_caravanWorkArr[entry.m_currentSlot];
				readyMask |= 1 << i;
				connectedCount++;
				if (entry.m_confirmed != 0 && work.m_caravanLocalFlags != 0) {
					locallyConfirmedCount++;
				}
			}
		}

		if (connectedCount != 0 && connectedCount == locallyConfirmedCount) {
			short windowWidth;
			short windowHeight;
			GetWinSize(0x17, &windowWidth, &windowHeight, 1);
			SetMcWinInfo(windowWidth, windowHeight);
			m_menuWindowInfo->state = 0;
			return;
		}

		unsigned short* pRep = padRepeat + 3;
		unsigned short* pTrig = padTrig + 3;
		i = 3;
		for (; i >= 0; i--, pRep--, pTrig--) {
			WmCharaSelectEntry& entry = m_wm.m_charaSelectData[i];
			if (entry.m_cmakeReady == 1) {
				entry.m_confirmed = 1;
				entry.m_cmakePending = 0;
				entry.m_cmakeReady = 0;
				SetMakeChara(i);
				Sound.PlaySe(0x33, 0x40, 0x7F, 0);
				GetWmCharaAnimState(this)[entry.m_currentSlot].m_nextAnimIndex = 3;
			}

			if (entry.m_connected == 0) {
				if (entry.m_confirmed != 0) {
					GetWmCharaAnimState(this)[entry.m_currentSlot].m_nextAnimIndex = 0;
				}
				entry.m_confirmed = 0;
				entry.m_cmakePending = 0;
				entry.m_cmakeReady = 0;
#ifdef VERSION_GCCP01
				if (entry.m_disconnectTime < 0x3C) {
					entry.m_disconnectTime++;
				}
#else
				entry.m_disconnectTime++;
#endif
				(*pRep) = 0;
				(*pTrig) = 0;
				continue;
			}

			entry.m_disconnectTime = 0;
			int currentSlot = static_cast<int>(entry.m_currentSlot);
			if (((*pRep) & 0x000C) != 0) {
				if (entry.m_confirmed != 0) {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				} else {
					if (currentSlot < 4) {
						currentSlot += 4;
					} else {
						currentSlot -= 4;
					}
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				}
			}
			if (((*pRep) & 0x0001) != 0) {
				if (entry.m_confirmed != 0) {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				} else {
					if (currentSlot > ((currentSlot >> 2) != 0 ? 4 : 0)) {
						currentSlot -= 1;
					} else {
						currentSlot += 3;
					}
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				}
			} else if (((*pRep) & 0x0002) != 0) {
				if (entry.m_confirmed != 0) {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				} else {
					const int maxSlot = (currentSlot >> 2) != 0 ? 7 : 3;
					if (currentSlot < maxSlot) {
						currentSlot += 1;
					} else {
						currentSlot -= 3;
					}
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				}
			}
			entry.m_currentSlot = static_cast<short>(currentSlot);

			if (((*pRep) & 0x006F) == 0) {
				const unsigned short trig = (*pTrig);
				CCaravanWork& work = Game.m_caravanWorkArr[entry.m_currentSlot];
				if ((trig & 0x0100) != 0 && work.m_shopBusyFlag != 0) {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				} else if ((trig & 0x0100) != 0 && entry.m_confirmed == 0) {
					const int charaId = m_wm.m_charaModelData[currentSlot].m_modelNo;
					if (charaId < 0) {
						if (Game.m_gameWork.m_menuStageMode == 0 &&
						    (entry.m_padType == 0x09000000 || entry.m_padType == -0x74F00000)) {
							Sound.PlaySe(4, 0x40, 0x7F, 0);
						} else {
							int other;
							for (other = 0; other < 4; other++) {
								if (i != other && m_wm.m_charaSelectData[other].m_cmakePending != 0 &&
								    m_wm.m_charaSelectData[other].m_currentSlot == currentSlot) {
									Sound.PlaySe(4, 0x40, 0x7F, 0);
									break;
								}
							}
							if (other >= 4) {
								if (Game.m_gameWork.m_menuStageMode != 0) {
									m_singleCmakeSlot = entry.m_currentSlot;
								} else {
									GbaQue.InitCmakeInfo(i, entry.m_currentSlot);
									entry.m_cmakePending = 1;
								}
								Sound.PlaySe(2, 0x40, 0x7F, 0);
							}
						}
					} else {
						int other;
						for (other = 0; other < 4; other++) {
							if (i != other && m_wm.m_charaSelectData[other].m_confirmed != 0 &&
							    m_wm.m_charaSelectData[other].m_currentSlot == currentSlot) {
								Sound.PlaySe(4, 0x40, 0x7F, 0);
								break;
							}
						}
						if (other >= 4) {
							if (work.m_caravanLocalFlags != 0) {
								if (Game.m_gameWork.m_menuStageMode != 0) {
									Sound.PlaySe(4, 0x40, 0x7F, 0);
								} else if (connectedCount == locallyConfirmedCount + 1) {
									Sound.PlaySe(4, 0x40, 0x7F, 0);
								} else {
									entry.m_confirmed = 1;
									locallyConfirmedCount++;
									Sound.PlaySe(0x33, 0x40, 0x7F, 0);
									GetWmCharaAnimState(this)[currentSlot].m_nextAnimIndex = 3;
								}
							} else {
								entry.m_confirmed = 1;
								Sound.PlaySe(0x33, 0x40, 0x7F, 0);
								GetWmCharaAnimState(this)[currentSlot].m_nextAnimIndex = 3;
							}
						}
					}
				} else if ((trig & 0x0100) != 0 && entry.m_confirmed != 0) {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				} else if ((trig & 0x0200) != 0) {
					if (entry.m_confirmed != 0) {
						entry.m_confirmed = 0;
						GetWmCharaAnimState(this)[currentSlot].m_nextAnimIndex = 0;
						Sound.PlaySe(0x34, 0x40, 0x7F, 0);
					} else {
						requestCancel = 1;
					}
				} else if ((trig & 0x1000) != 0) {
					requestFinalize = 1;
				}
			}
		}

		if (requestCancel) {
			int anySelected = 0;
			for (i = 0; i < 4; i++) {
				if ((m_wm.m_charaSelectData[i].m_confirmed != 0) || (m_wm.m_charaSelectData[i].m_cmakePending != 0)) {
					anySelected = 1;
					break;
				}
			}
			if (anySelected == 0) {
				GetWmWorldState(this)->m_nextMenuMode = -1;
				GetWmWorldState(this)->m_delay = 10;
				Sound.PlaySe(3, 0x40, 0x7F, 0);
			} else {
				Sound.PlaySe(4, 0x40, 0x7F, 0);
			}
		}

		if (requestFinalize) {
			int activeCount = 0;
			for (i = 0; i < 4; i++) {
				if (m_wm.m_charaSelectData[i].m_confirmed != 0) {
					activeCount++;
				}
			}
			for (i = 0; i < 4; i++) {
				if (m_wm.m_charaSelectData[i].m_cmakePending != 0) {
					activeCount = 0;
					break;
				}
			}
			if (locallyConfirmedCount >= activeCount) {
				activeCount = 0;
			}
			if (activeCount != 0) {
				Sound.PlaySe(2, 0x40, 0x7F, 0);
				GetWmWorldState(this)->m_nextMenuMode = 1;
				GetWmWorldState(this)->m_delay = 10;
			} else {
				Sound.PlaySe(4, 0x40, 0x7F, 0);
			}
		}

		int finishedMask = 0;
		for (i = 0; i < 4; i++) {
			if (m_wm.m_charaSelectData[i].m_confirmed != 0) {
				finishedMask |= 1 << i;
			}
		}
		if (Game.m_gameWork.m_menuStageMode != 0 && m_singleCmakeSlot >= 0) {
			GetWmWorldState(this)->m_nextMenuMode = 1;
			GetWmWorldState(this)->m_delay = 10;
		} else {
			for (i = 0; i < 4; i++) {
				if (m_wm.m_charaSelectData[i].m_connected == 0 && m_wm.m_charaSelectData[i].m_disconnectTime < 0x1E) {
					readyMask |= 1 << i;
				}
			}
			if (finishedMask != 0 && finishedMask == readyMask) {
				GetWmWorldState(this)->m_nextMenuMode = 1;
				GetWmWorldState(this)->m_delay = static_cast<short>(s_MaxAnimWait);
			}
		}

		if (GetWmWorldState(this)->m_nextMenuMode != 0) {
#ifndef VERSION_GCCJGC
			GbaQue.SetControllerMode(1);
#endif
			for (i = 0; i < kWmMenuControllerCount; i++) {
				WmCharaSelectEntry& entry = m_wm.m_charaSelectData[i];
				if (entry.m_cmakePending != 0) {
					entry.m_confirmed = 0;
					entry.m_cmakePending = 0;
					entry.m_cmakeReady = 0;
#ifdef VERSION_GCCJGC
					int retry;
					for (retry = 0; retry < 10; retry++) {
						if (Joybus.SetMType(i, 4) == 0) {
							break;
						}
					}
					if (retry >= 10) {
						m_wmWorldState->m_nextMenuMode = 0;
						m_wmWorldState->m_delay = 0;
						Sound.PlaySe(4, 0x40, 0x7F, 0);
					}
#endif
				}
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800f0274
 * PAL Size: 2044b
 * EN Address: 0x800EF91C
 * EN Size: 2044b
 * JP Address: 0x800ECD84
 * JP Size: 1896b
 */
void CMenuPcs::DrawCharaName()
{
#ifdef VERSION_GCCJGC
	static const char* STR_TBL[] = {"\x82\xC8\x82\xB5", "\x83\x4C\x83\x83\x83\x89\x83\x81\x83\x43\x83\x4E\x92\x86"};
#else
	static const char* STR_TBL_us[] = {"Empty", "Creating..."};
	static const char* STR_TBL_ge[] = {"Frei", "Wird kreiert"};
	static const char* STR_TBL_it[] = {"Vuoto", "Creazione..."};
	static const char* STR_TBL_fr[] = {"Vide", "Cr\351ation..."};
	static const char* STR_TBL_sp[] = {"Vac\355o", "Creando..."};
#endif

	CFont* const font = GetWmFont(this);
	WmCharaSelectEntry* const selectEntries = m_wm.m_charaSelectData;
	unsigned char nameBuf[0x20];

#ifndef VERSION_GCCJGC
	const char** emptyText;
	switch (Game.m_gameWork.GetLanguage()) {
	case 2:
		emptyText = STR_TBL_ge;
		break;
	case 3:
		emptyText = STR_TBL_it;
		break;
	case 4:
		emptyText = STR_TBL_fr;
		break;
	case 5:
		emptyText = STR_TBL_sp;
		break;
	case 1:
	default:
		emptyText = STR_TBL_us;
		break;
	}
#endif

	float fade;
	if (m_wmWorldState->m_mainState == 1) {
		fade = static_cast<float>(DOUBLE_803314E8 * static_cast<double>(m_wmWorldState->m_frameCounter));
	} else if (m_wmWorldState->m_mainState == 2) {
		fade = FLOAT_803313e8;
	} else {
		fade = static_cast<float>(-(DOUBLE_803314E8 * static_cast<double>(m_wmWorldState->m_frameCounter) - DOUBLE_80331420));
	}
	unsigned int activeMask = 0;
	unsigned int confirmedMask = 0;
	unsigned int pendingMask = 0;
	const WmCharaSelectEntry* entry = selectEntries;
	for (int i = 0; i < 4; i++) {
		if (entry->m_connected != 0) {
			const unsigned int bit = 1u << entry->m_currentSlot;
			activeMask |= bit;
			if (entry->m_confirmed != 0) {
				confirmedMask |= bit;
			}
			if (entry->m_cmakePending != 0 || entry->m_cmakeReady != 0) {
				pendingMask |= bit;
			}
		}
		entry++;
	}

	font->SetMargin(FLOAT_803313e8);
	font->SetShadow(0);
	font->SetScale(FLOAT_8033158C);
	font->DrawInit();
	DrawInit();

	const float alphaF = FLOAT_80331458 * fade;
	GXColor shade;
	shade.r = 0xFF;
	shade.g = 0xFF;
	shade.b = 0xFF;
	shade.a = static_cast<unsigned char>(static_cast<int>(alphaF));
	GXSetChanMatColor(GX_COLOR0A0, shade);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kCharacterNamePlateTexture));
	float plateW = 64.0f;
	const double xOffsetDefault =
	    -(DOUBLE_80331418 * static_cast<double>(plateW) - DOUBLE_80331678);
	for (int row = 0; row < 2; row++) {
		float y = FLOAT_80331478 + static_cast<float>(row * 0xB8);
		y += FLOAT_80331684;
		if (row != 0) {
			y += FLOAT_80331548;
		}
		for (int col = 0; col < 4; col++) {
			const int slot = row * 4 + col;
			if ((confirmedMask & (1u << slot)) != 0) {
				const char* const text = reinterpret_cast<const char*>(
				    Game.m_caravanWorkArr[slot].m_name);
				float xBase = FLOAT_80331410 + static_cast<float>(col * 0x90);
				const float width = font->GetWidth(text);
				float scale = FLOAT_803313e8;
				if (width / 2.0 > plateW) {
					const float widthPlus = static_cast<float>(width + DOUBLE_80331510);
					scale = static_cast<float>(widthPlus / 2.0 / plateW);
					xBase = static_cast<float>((FLOAT_8033155C - widthPlus) / 2.0 + xBase);
				} else {
					xBase = static_cast<float>(xOffsetDefault / 2.0 + xBase);
				}
				MenuPcs.DrawRect(
				    0, xBase, y, FLOAT_80331680, FLOAT_80331410,
				                                FLOAT_803313dc, FLOAT_803313dc, scale, FLOAT_803313e8, FLOAT_803313dc);
				MenuPcs.DrawRect(
				    8, FLOAT_80331680 * scale + xBase, y,
				                                FLOAT_80331680, FLOAT_80331410, FLOAT_803313dc, FLOAT_803313dc,
				                                scale, FLOAT_803313e8, FLOAT_803313dc);
			}
		}
	}

	DrawInit();
	font->SetMargin(FLOAT_803313e8);
	font->SetShadow(1);
	font->SetScale(FLOAT_8033158C);
	font->DrawInit();
	font->SetColor(CColor(0xFF, 0xFF, 0xFF, alphaF).color);

	CSystem* const sys = &System;
	for (int row2 = 0; row2 < 2; row2++) {
		float y = FLOAT_80331478 + static_cast<float>(row2 * 0xB8);
		y += FLOAT_80331688;
		if (row2 != 0) {
			y += FLOAT_80331548;
		}
#ifndef VERSION_GCCJGC
		y -= FLOAT_80331550;
#endif
		for (int col = 0; col < 4; col++) {
			const int slot = row2 * 4 + col;
			int restoreColor;
			restoreColor = 0;
			const char* text;

			float xBase = FLOAT_80331410 + static_cast<float>(col * 0x90);

			const int menuMode = this->m_wmWorldState->m_menuMode;
			bool hasName;
			if (menuMode == 8 && this->m_cmakeWork != 0) {
				hasName = m_cmakeWork->m_characters[slot].m_exists != 0;
			} else {
				hasName = Game.m_caravanWorkArr[slot].m_shopState != 0;
			}

			if (hasName) {
				if (menuMode == 8 && this->m_cmakeWorkActive == 1 && this->m_cmakeWork != 0) {
					memset(nameBuf, 0, 0x20);
					memcpy(nameBuf, m_cmakeWork->m_characters[slot].m_name, sizeof(m_cmakeWork->m_characters[slot].m_name));
					text = reinterpret_cast<const char*>(nameBuf);
				} else {
					text = reinterpret_cast<const char*>(Game.m_caravanWorkArr[slot].m_name);
				}
				if ((activeMask & (1u << slot)) != 0) {
					font->SetTlut(6);
				} else {
					font->SetTlut(8);
				}
			} else if ((pendingMask & (1u << slot)) != 0) {
				font->SetTlut(0x10);
#ifdef VERSION_GCCJGC
				text = STR_TBL[1];
#else
				text = emptyText[1];
#endif
				const int phase = static_cast<int>(sys->m_frameCounter) % 20 - 10;
				if (this->m_wmWorldState->m_mainState == 2) {
					const int absPhase = abs(phase);
					fade = static_cast<float>(-(DOUBLE_80331460 * static_cast<double>(absPhase) - DOUBLE_80331420));
					restoreColor = 1;
				}
				font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<int>(FLOAT_80331458 * fade)).color);
			} else {
				if ((activeMask & (1u << slot)) != 0) {
					font->SetTlut(7);
				} else {
					font->SetTlut(8);
				}
#ifdef VERSION_GCCJGC
				text = STR_TBL[0];
#else
				text = emptyText[0];
#endif
			}

			const float widthDiff = FLOAT_8033155C - font->GetWidth(text);
			xBase += widthDiff / 2.0;
			font->SetPosX(xBase);
			font->SetPosY(y);
			font->Draw(text);
			if (restoreColor) {
				font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
			}
		}
	}

	DrawInit();
}

/*
 * --INFO--
 * PAL Address: 0x800efc38
 * PAL Size: 1596b
 * EN Address: 0x800EF2E0
 * EN Size: 1596b
 * JP Address: 0x800EC784
 * JP Size: 1536b
 */
void CMenuPcs::DrawCMLife()
{
	static CMenuPcs::SPL s_LifeY[] = {
		{0.0f, 0.0f, 65.0f, 65.0f},
		{0.1166666f, 6.0f, 0.0f, 0.0f},
		{0.25f, 0.0f, -65.0f, -65.0f},
	};
	static FCV s_LifePos = {3, s_LifeY};
#define worldState GetWmWorldState(this)
#define selectEntries m_wm.m_charaSelectData

	float fade;
	if (worldState->m_mainState == 1) {
		fade = static_cast<float>(DOUBLE_803314E8 * static_cast<double>(worldState->m_frameCounter));
	} else if (worldState->m_mainState == 2) {
		fade = FLOAT_803313e8;
	} else {
		fade = static_cast<float>(-(DOUBLE_803314E8 * static_cast<double>(worldState->m_frameCounter) -
		                            FLOAT_803313e8));
	}
	int slot;
	unsigned int readyMask = 0;
	for (slot = 0; slot < 4; slot++) {
		const WmCharaSelectEntry& entry = selectEntries[slot];
		if (entry.m_connected != 0 && entry.m_cmakePending == 0 && entry.m_cmakeReady == 0) {
			readyMask |= 1u << entry.m_currentSlot;
		}
	}
	const double alphaF = FLOAT_80331458 * fade;

	for (slot = 0; slot < 8; slot++) {
		int i;
		int row;
		int col;
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kCharacterLifeTexture));

		int count;
		if (worldState->m_menuMode == 8 && m_cmakeWorkActive == 1 && m_cmakeWork != 0) {
			if (m_cmakeWork->m_characters[slot].m_exists == 0) {
				continue;
			}
#ifdef VERSION_GCCJGC
			count = static_cast<int>(m_cmakeWork->m_characters[slot].m_hp) >> 1;
#else
			count = static_cast<int>(m_cmakeWork->m_characters[slot].m_maxHp) >> 1;
#endif
		} else {
			CCaravanWork& caravan = Game.m_caravanWorkArr[slot];
			if (caravan.m_shopState == 0) {
				continue;
			}
			count = static_cast<int>(caravan.m_maxHp) >> 1;
		}
		float red;
		float green;
		float blue;
		if ((readyMask & (1u << slot)) != 0) {
			red = FLOAT_803313e8;
			green = red;
			blue = red;
		} else {
			red = FLOAT_80331434;
			green = FLOAT_80331668;
			blue = green;
		}

		GXColor color;
		color.r = static_cast<unsigned char>(static_cast<int>(FLOAT_80331458 * red));
		color.g = static_cast<unsigned char>(static_cast<int>(FLOAT_80331458 * green));
		color.b = static_cast<unsigned char>(static_cast<int>(FLOAT_80331458 * blue));
		color.a = static_cast<unsigned char>(static_cast<int>(alphaF));
		GXSetChanMatColor(GX_COLOR0A0, color);

		row = slot / 4;
		col = slot % 4;
		float xBase;
		float y;
		float x;
		xBase = FLOAT_80331410 + static_cast<float>(col * 0x90);
		y = FLOAT_80331478 + static_cast<float>(row * 0xB8);
		float yTmp = y;
		if (row != 0) {
			float rowAdd = FLOAT_80331548;
			yTmp = y + rowAdd;
		}
		float yAdjust = FLOAT_8033166C;
		yTmp = yTmp + yAdjust;
		x = static_cast<float>((0x90 - count * 0x10) / 2.0 + xBase);
		float step = static_cast<float>((8 - count) / 2.0);

		const float* pRectSize = &FLOAT_80331558;
		float kRectSize;
		kRectSize = *pRectSize;

		for (i = 0; i < count; i++) {
			float yAdd = GetFcvValue(s_LifePos, step);

			MenuPcs.DrawRect(
			    0, x, yTmp + yAdd, FLOAT_80331558, FLOAT_80331558,
			                                FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
			step += 1.0;
			x += kRectSize;
		}

		unsigned char flagA;
		unsigned char flagB;
		if (m_cmakeWorkActive == 1 && m_cmakeWork != 0) {
			flagA = m_cmakeWork->m_characters[slot].m_isAway;
			flagB = m_cmakeWork->m_characters[slot].m_isGuest;
		} else {
			flagA = Game.m_caravanWorkArr[slot].m_shopBusyFlag;
			flagB = Game.m_caravanWorkArr[slot].m_caravanLocalFlags;
		}
		if (flagA != 0 || flagB != 0) {
			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kCharacterAwayTexture));
			float texV;
			if (flagA != 0) {
				texV = FLOAT_803313dc;
			} else {
				texV = FLOAT_80331440;
			}
			if (row != 0) {
				y += FLOAT_80331548;
			}
			y += DOUBLE_803315C0;
			MenuPcs.DrawRect(
			    0, static_cast<float>(xBase + DOUBLE_80331670),
			                                y, FLOAT_80331524,
			                                FLOAT_80331440, FLOAT_803313dc,
			                                texV,
			                                FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
		}
	}
#undef worldState
#undef selectEntries
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 32b
 * EN Address: 0x80116144
 * EN Size: 40b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::WMSubMenuInit()
{
	m_effectTimer = 0;
	m_wmMenuRotation = 0.0f;
	m_wmMenuTargetRotation = 0.0f;
	m_wmHelpTimer = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800eeea0
 * PAL Size: 3480b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::WMChgMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	if (m_wmWorldState->m_changeRequest == 0) {
		return;
	}

	int prevMenuMode = m_wmWorldState->m_menuMode;
	lbl_8032EE1C = 1;

	short changeRequest = m_wmWorldState->m_changeRequest;

	if (changeRequest == 2) {
		char requestKind = bytes[0xD];
		if (requestKind == 1) {
			m_wmWorldState->m_menuMode = 0;
		} else if (requestKind == 2) {
			m_wmWorldState->m_menuMode = 5;
		} else if (requestKind == 3) {
			lbl_8032EE1C = 1;
			if (prevMenuMode == 6) {
				m_wmWorldState->m_changeRequest = 0;
				return;
			}
			m_wmWorldState->m_menuMode = 6;
		} else if (requestKind == 4) {
			m_wmWorldState->m_menuMode = 4;
		} else {
			m_wmWorldState->m_menuMode = 1;
		}
	} else if (prevMenuMode == 0) {
		if (changeRequest == 1) {
			short menuCursor = m_wmWorldState->m_cardChannel;
			if (menuCursor == 0) {
				m_wmWorldState->m_menuMode = 3;
			} else if (menuCursor == 1) {
				m_wmWorldState->m_menuMode = 1;
				memset(m_wmWorldParams, 0, 0x10);
			} else if (menuCursor == 2) {
				m_wmWorldState->m_menuMode = 8;
			} else if (menuCursor == 3) {
				m_wmWorldState->m_menuMode = 7;
			} else {
				m_wmWorldState->m_menuMode = 2;
			}
		} else {
			m_wmWorldState->m_menuMode = 4;
		}
	} else if (prevMenuMode == 1) {
		m_wmWorldState->m_menuMode = 0;
		m_wmWorldState->m_cardChannel = 1;
	} else if (prevMenuMode == 8) {
		m_wmWorldState->m_menuMode = 0;
		m_wmWorldState->m_cardChannel = 2;
	} else if (prevMenuMode == 7) {
		m_wmWorldState->m_menuMode = 0;
		m_wmWorldState->m_cardChannel = 3;
	} else if (prevMenuMode == 2) {
		m_wmWorldState->m_menuMode = 0;
		m_wmWorldState->m_cardChannel = 4;
	} else if (prevMenuMode == 5) {
		if (changeRequest == 1) {
			m_wmWorldState->m_menuMode = 0;
			bytes[0xD] = 0;
			m_wmWorldState->m_cardChannel = 0;
			CallWorldParam(1, 1, 0);
		} else if (changeRequest == -1) {
			lbl_8032EE1C = 1;
			m_wmWorldState->m_menuMode = 6;
			CallWorldParam(1, 0, 0);
		}
	} else if (prevMenuMode == 6) {
		m_wmWorldState->m_menuMode = 0;
	} else if (changeRequest == 1) {
		if (m_wmWorldState->m_menuMode >= 8) {
			bytes[0xD] = 0;
		} else {
			m_wmWorldState->m_menuMode++;
		}
	} else if (changeRequest == -1) {
		short curMode = m_wmWorldState->m_menuMode;
		if (curMode <= 0) {
			bytes[0xD] = 0;
		} else if (curMode == 3) {
			m_wmWorldState->m_menuMode = 0;
			m_wmWorldState->m_cardChannel = 0;
		} else {
			m_wmWorldState->m_menuMode = curMode - 1;
		}
	}

	if (m_wmWorldState->m_menuMode != 0) {
		m_wmWorldState->m_cardChannel = 0;
	}

	m_wmWorldState->m_frameCounter = 0;
	m_wmWorldState->m_titleState = 0;
	m_wmWorldState->m_worldReady = 0;
	m_wmWorldState->m_flag09 = 0;
	m_wmWorldState->m_flag0A = 0;
	m_wmWorldState->m_state0E = 0;
	m_wmWorldState->m_mainState = 0;
	m_wmWorldState->m_state12 = 0;
	m_wmWorldState->m_subState = 0;
	m_wmWorldState->m_delay = 0;
	m_wmWorldState->m_counter1A = 0;
	m_wmWorldState->m_posY = FLOAT_803313e8;
	m_wmWorldState->m_posX = FLOAT_803313dc;
	m_wmWorldState->m_mcResult = 0;
	m_wmWorldState->m_flag0B = 0;
	m_wmWorldState->m_modelFlagsInitialized = 0;

	SetMcWinInfo(0, 0);
	m_textureLocIndex = 0;

	InitFrame0Info();

	if (prevMenuMode == 3 && Game.m_gameWork.m_menuStageMode != 0
	    && m_singleCmakeSlot >= 0
	    && m_singleCmakeSlot < 8) {
		m_singleCmakeMode = 1;
		m_wmWorldState->m_menuMode = 3;
	} else if (prevMenuMode == 3 && Game.m_gameWork.m_menuStageMode != 0
	           && m_singleCmakeSlot >= 8) {
		m_singleCmakeMode = 0;
		m_singleCmakeSlot = (short)0xFFFF;
		m_wmWorldState->m_menuMode = 3;
	} else {
		m_singleCmakeMode = 0;
		m_singleCmakeSlot = (short)0xFFFF;
	}

	m_wmTransitionCode = 0;

	short newMenuMode = m_wmWorldState->m_menuMode;
	switch (newMenuMode) {
	case 0: {
			ChkSelectParty();

			const float scrollStep = FLOAT_8033151c;
			m_wmMenuTargetRotation = -(scrollStep * (float)(int)m_wmWorldState->m_cardChannel);
			m_wmMenuRotation = -(scrollStep * (float)(int)m_wmWorldState->m_cardChannel);
			m_effectTimer = 0;
		break;
	}
	case 3: {
			float initialRotY = FLOAT_80331664;
			int slot = 0;
			WmWorldObjInfo* worldObj = &m_wm.m_worldObjData[32];
			do {
				const int handleIdx = slot + 0x20;
				m_wm.m_charaModelData[slot].m_modelChanged = 1;
				worldObj->m_transform.m_rotation.y = initialRotY;
				WmCharaSelectEntry* const selectData = &m_wm.m_charaSelectData[slot];
				selectData->m_displaySlot = selectData->m_currentSlot;
				if (m_wm.m_handles[handleIdx]->IsModelLoaded(1)) {
					Mtx mtx;
					PSMTXIdentity(mtx);
					m_wm.m_handles[handleIdx]->m_model->SetMatrix(mtx);
					m_wm.m_handles[handleIdx]->m_model->CalcMatrix();
					m_wm.m_handles[handleIdx]->m_model->CalcSkin();
				}
				slot = slot + 1;
				worldObj++;
			} while (slot < 8);

			for (int channel = 0; channel < 4; channel++) {
				GbaQue.ClrCmakeInfo(channel);
			}
		break;
	}
	case 4:
		m_wmWorldState->m_posX = FLOAT_80331440;
		break;
	case 7:
		GetOptionData();
		break;
	}

	switch (prevMenuMode) {
	case 0: {
		if (m_wmWorldState->m_menuMode == 4) {
			for (int i = 0; i < kWmMenuControllerCount; i++) {
				Game.m_gameWork.m_wmBackupParams[i] = m_wmWorldState->m_backupParams[i];
			}
			bytes[0x10] = 1;
			bytes[0x12] = 0;
			bytes[0x13] = 0;
		} else {
			InitCharaSelectInfo();
		}
		break;
	}
	case 1:
		memset(m_wmWorldParams, 0, 0x10);
		bytes[0x11] = 0;
		break;
	case 3: {
		if (m_wmWorldState->m_menuMode == 4) {
			SetParty();

			bytes[0x10] = 1;
			bytes[0x12] = 0;
			bytes[0x13] = 0;
		}
		break;
	}
	case 4: {
		Sound.PlaySe(0x31, 0x40, 0x7F, 0);
		bytes[0x10] = 0;
		InitCharaSelectInfo();
		break;
	}
	case 7:
		break;
	}

	if (m_wmWorldState->m_changeRequest == 2
	    && m_wmWorldState->m_menuMode == 4) {
		bytes[0x10] = 1;
		bytes[0x12] = 0;
		bytes[0x13] = 0;
	}

	m_wmWorldState->m_changeRequest = 0;
	m_wmWorldState->m_nextMenuMode = 0;
	m_wmWorldState->m_delay = 0;

	newMenuMode = m_wmWorldState->m_menuMode;
	if (newMenuMode == 6) {
		MapMng.SetDraw(0);
	} else if (prevMenuMode == 6 && newMenuMode != 6) {
		MapMng.SetDraw(1);
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 184b
 * EN Address: 0x801169D4
 * EN Size: 132b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::SetParty()
{
	for (int i = 0; i < kWmMenuControllerCount; i++) {
		const int slot = m_wm.m_charaSelectData[i].m_confirmed != 0
		    ? m_wm.m_charaSelectData[i].m_currentSlot : -1;
		Game.m_gameWork.m_wmBackupParams[i] = slot;
		m_wmWorldState->m_backupParams[i] = static_cast<short>(slot);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800eee34
 * PAL Size: 108b
 * EN Address: 0x800EE530
 * EN Size: 24b
 * JP Address: 0x800EBA08
 * JP Size: 24b
 */
void CMenuPcs::SetCMakeEnd(int channel)
{
	m_wm.m_charaSelectData[channel].m_cmakeReady = 1;
#ifdef VERSION_GCCP01
	if ((unsigned int)System.m_execParam >= 3) {
		System.Printf("SetCMakeEnd : chan = %d  cur = %d\n", channel,
		               (int)m_wm.m_charaSelectData[channel].m_currentSlot);
	}
#endif
}

/*
 * --INFO--
 * PAL Address: 0x800eed84
 * PAL Size: 176b
 * EN Address: 0x800EE4C8
 * EN Size: 104b
 * JP Address: 0x800EB9A0
 * JP Size: 104b
 */
void CMenuPcs::ClrCMakeFlg(int channel)
{
	m_wm.m_charaSelectData[channel].m_cmakePending = 0;
	const int current = m_wm.m_charaSelectData[channel].m_currentSlot;
#ifdef VERSION_GCCP01
	if ((unsigned int)System.m_execParam >= 3) {
		System.Printf("ClrCMakeFlg : chan = %d  cur = %d\n", channel, current);
	}
#endif
	WmCharaModelInfo* modelData = &m_wm.m_charaModelData[current];
	modelData->m_modelChanged = 0;
	GetWmCharaHandles(this)[current]->LoadModelASync(3, 0x43, 0);
}

/*
 * --INFO--
 * PAL Address: 0x800eec84
 * PAL Size: 256b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ChgAllModel()
{
	for (int i = 0; i < kWmMenuPlayerCount; i++) {
		WmCharaModelInfo* modelData = &m_wm.m_charaModelData[i];
		CCaravanWork* const caravan = &Game.m_caravanWorkArr[i];
		int tribe;
		int appearance;
		int isFemale;
		int modelId;

		if (Game.m_caravanWorkArr[i].m_shopState != 0) {
			tribe = caravan->m_tribeId;
			isFemale = caravan->m_genderFlag;
			appearance = caravan->m_appearanceVariant;
			modelId = GetModelNo(tribe, appearance, isFemale);
			modelData->m_modelNo = modelId;
		} else {
			tribe = -1;
			modelData->m_modelNo = -1;
			appearance = -1;
			isFemale = -1;
		}

		ChgModel(i, tribe, appearance, isFemale);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800eeb9c
 * PAL Size: 232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ChgAllModel2()
{
	for (int i = 0; i < kWmMenuPlayerCount; i++) {
		WmCharaModelInfo* modelData = &m_wm.m_charaModelData[i];
		const Mc::CharaDat& character = m_cmakeWork->m_characters[i];
		int tribe;
		int isFemale;
		int appearance;

		if (character.m_exists != 0) {
			isFemale = character.m_genderFlag;
			appearance = character.m_appearanceVariant;
			tribe = character.m_tribeId;
		} else {
			tribe = -1;
			modelData->m_modelNo = -1;
			appearance = -1;
			isFemale = -1;
		}

		ChgModel(i, tribe, appearance, isFemale);
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 660b
 * EN Address: 0x80116C58
 * EN Size: 576b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::SetMakeChara(int channel)
{
	GbaCMakeInfo info;
	GbaQue.GetCMakeInfo(channel, &info);

	const int caravanSlot = static_cast<int>(static_cast<signed char>(info.m_playerSlot));
	const int gender = (info.m_charaType >> 7) ? 1 : 0;
	int modelNo = GetModelNo(info.m_charaType & 3, (info.m_charaType >> 2) & 3, gender);

	m_wm.m_charaModelData[caravanSlot].m_modelNo = modelNo;

	CCaravanWork& caravanWork = Game.m_caravanWorkArr[caravanSlot];
	caravanWork.LoadInit();
	caravanWork.m_shopState = 1;
	caravanWork.unk_0x3a8 =
	    (static_cast<unsigned int>(info.m_birthDate[0]) << 8) | static_cast<unsigned int>(info.m_birthDate[1]);
	caravanWork.m_jobType = static_cast<int>(info.m_jobType);
	memset(caravanWork.m_name, 0, 0x11);
	strcpy(reinterpret_cast<char*>(caravanWork.m_name), info.m_name);
	caravanWork.m_tribeId = static_cast<unsigned short>(info.m_charaType & 3);
	caravanWork.m_appearanceVariant = static_cast<unsigned short>((info.m_charaType >> 2) & 3);
	caravanWork.m_genderFlag = static_cast<unsigned short>((info.m_charaType >> 7) != 0);
	caravanWork.m_id = static_cast<unsigned short>(
	    GetModelNo(info.m_charaType & 3, (info.m_charaType >> 2) & 3, (info.m_charaType >> 7) ? 1 : 0));
	for (int favorite = 0; favorite < 8; favorite++) {
		unsigned char nibble = info.m_favorite[favorite >> 1];
		int v;
		if ((favorite & 1) != 0) {
			v = (nibble >> 4) & 0x0F;
		} else {
			v = nibble & 0x0F;
		}
		caravanWork.m_letterMeta[favorite] = static_cast<unsigned short>((10 - v) * 10 - 5);
	}

	const int baseDataIndex =
	    static_cast<int>(caravanWork.m_genderFlag) + static_cast<int>(caravanWork.m_tribeId) * 2;
	caravanWork.Init(baseDataIndex,
	                 reinterpret_cast<CRomWork*>(Game.unkCFlatData0[0]) + baseDataIndex,
	                 static_cast<int>(caravanWork.m_appearanceVariant));
	caravanWork.LoadFinished();

	CallWorldParam(0, caravanSlot, 0);
}

/*
 * --INFO--
 * PAL Address: 0x800eeb1c
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ChgModel(int slot, int tribe, int job, int isFemale)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	WmCharaModelInfo* modelData = &m_wm.m_charaModelData[slot];
	int modelNo;
	int charaKind;

	if (tribe >= 0) {
		charaKind = 0;
		modelNo = GetModelNo(tribe, job, isFemale);
		modelData->m_modelChanged = 1;
	} else {
		charaKind = 3;
		modelData->m_modelChanged = 0;
		modelNo = 0x43;
	}

	GetWmCharaHandles(this)[slot]->LoadModelASync(charaKind, static_cast<unsigned long>(modelNo), 0);
}

/*
 * --INFO--
 * PAL Address: 0x800ee928
 * PAL Size: 500b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetAnim(int anim)
{
	const int handleIdx = anim + 0x20;
	if (m_wm.m_handles[handleIdx]->m_charaKind == 3) {
		return;
	}

	const unsigned int charaNo = m_wm.m_handles[handleIdx]->m_charaNo;
	int animBase = static_cast<int>(charaNo / 100) - 1;
	animBase *= 6;
	const int modelBase = static_cast<int>(charaNo / 100) * 100;

	m_wm.m_handles[handleIdx]->LoadAnim(const_cast<char*>(s_wmCharaAnimStand), animBase++, 1, 0, modelBase, -1, 0);
	m_wm.m_handles[handleIdx]->LoadAnim(const_cast<char*>(s_wmCharaAnimWalk), animBase++, 1, 0, modelBase, -1, 0);
	m_wm.m_handles[handleIdx]->LoadAnim(const_cast<char*>(s_wmCharaAnimRun), animBase++, 1, 0, modelBase, -1, 0);
	m_wm.m_handles[handleIdx]->LoadAnim(const_cast<char*>(s_wmCharaAnimGlad), animBase++, 3, 0, modelBase, -1, 0);
	m_wm.m_handles[handleIdx]->LoadAnim(const_cast<char*>(s_wmCharaAnimSleep), animBase++, 1, 0, modelBase, -1, 0);
	m_wm.m_handles[handleIdx]->LoadAnim(const_cast<char*>(s_wmCharaAnimAngry), animBase, 1, 0, modelBase, -1, 0);

	m_wmCharaAnimState[anim].m_animIndex = 0;
	m_wmCharaAnimState[anim].m_nextAnimIndex = -1;
	m_wmCharaAnimState[anim].m_timer = rand() % 250;

	m_wm.m_handles[handleIdx]->SetAnim(animBase - 5, -1, -1,
	    m_wm.m_handles[handleIdx]->GetCurrentAnimNumber() < 0 ? 0 : -1, 1);

	m_wmCharaAnimState[anim].m_frame = m_wm.m_handles[handleIdx]->m_model->GetNowFrame();
	m_wmCharaAnimState[anim].m_endFrame = m_wm.m_handles[handleIdx]->m_model->GetEndFrame();
}

/*
 * --INFO--
 * PAL Address: 0x800ee828
 * PAL Size: 256b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawCursor(int x, int y, float scale)
{
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	unsigned char alpha = static_cast<unsigned char>(static_cast<int>(FLOAT_80331458 * scale));
	GXColor color;
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = alpha;
	GXSetChanMatColor(static_cast<GXChannelID>(4), color);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0));
	MenuPcs.DrawRect(0, static_cast<float>(x), static_cast<float>(y), FLOAT_80331410, FLOAT_80331410, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
}

/*
 * --INFO--
 * PAL Address: 0x800ed94c
 * PAL Size: 3804b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcMainMenuSub()
{
	int i;
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	const unsigned short btn = Pad.GetButtonDown(0);

	if (((m_wmWorldState->m_mainState > 0) && (m_wmWorldState->m_mainState < 4)) || m_wmWorldState->m_cardChannel == 1) {
		if (m_wmWorldState->m_mainState == 2 && m_wmWorldState->m_delay == 0) {
			if ((btn & 1) != 0) {
				float zero = FLOAT_803313dc;
				m_wmMenuTargetRotation -= FLOAT_8033151c;
				if (m_wmMenuTargetRotation < zero) {
					float wrap = FLOAT_80331528;
					m_wmMenuTargetRotation += wrap;
					m_wmMenuRotation += wrap;
				}
				m_wmWorldState->m_frameCounter = 0xE;
				if (m_wmWorldState->m_cardChannel >= 4) {
					m_wmWorldState->m_cardChannel = 0;
				} else {
					m_wmWorldState->m_cardChannel++;
				}
				Sound.PlaySe(0x37, 0x40, 0x7F, 0);
			} else if ((btn & 2) != 0) {
				float wrap2 = FLOAT_80331528;
				m_wmMenuTargetRotation += FLOAT_8033151c;
				if (m_wmMenuTargetRotation > wrap2) {
					m_wmMenuTargetRotation -= wrap2;
					m_wmMenuRotation -= wrap2;
				}
				m_wmWorldState->m_frameCounter = 0xE;
				if (m_wmWorldState->m_cardChannel <= 0) {
					m_wmWorldState->m_cardChannel = 4;
				} else {
					m_wmWorldState->m_cardChannel--;
				}
				Sound.PlaySe(0x37, 0x40, 0x7F, 0);
			}

			const float selA = m_wmMenuTargetRotation;
			const float selB = m_wmMenuRotation;
			const float hi = (selB < selA) ? selA : selB;
			const float lo = (selB < selA) ? selB : selA;
			const float delta = FLOAT_803315cc * (hi - lo);
			if (selB <= selA) {
				m_wmMenuRotation += delta;
			} else {
				m_wmMenuRotation -= delta;
			}

			if (m_wmWorldState->m_frameCounter > 0) {
				m_wmWorldState->m_frameCounter--;
			}

			if (m_wmWorldState->m_frameCounter == 0 && (btn & 3) == 0) {
				if ((btn & 0x100) != 0) {
					m_wmMenuRotation = m_wmMenuTargetRotation;
					m_wmWorldState->m_delay = 0x14;
					m_wmWorldState->m_nextMenuMode = 1;
					Sound.PlaySe(2, 0x40, 0x7F, 0);
				} else if ((btn & 0x200) != 0) {
					int valid;
					m_wmMenuRotation = m_wmMenuTargetRotation;
					for (i = valid = 0; i < 4; i++) {
						if (Game.m_gameWork.m_menuStageMode != 0 && i != 0) {
							break;
						}
						if (m_wmWorldState->m_backupParams[i] >= 0) {
							valid++;
						}
					}
					if (valid == 0) {
						Sound.PlaySe(4, 0x40, 0x7F, 0);
					} else {
						m_wmWorldState->m_delay = 1;
						m_wmWorldState->m_nextMenuMode = -1;
						Sound.PlaySe(3, 0x40, 0x7F, 0);
					}
				}
			}
		}

		WmWorldObjInfo* const worldObj = m_wm.m_worldObjData;
		Mtx baseMtx;
		Mtx workMtx;
		Mtx modelMtx;
		Vec modelPos;

		PSMTXRotRad(baseMtx, 'x', FLOAT_803315d0);
		Math.MTXRotRadApply(baseMtx, baseMtx, 'y', FLOAT_803314bc * -m_wmMenuRotation);

		float selectedRotY = GetFcvValue(s_MenuObjYRot,
		                                 static_cast<float>(m_wmWorldState->m_titleState));
		float selectedRotZ = GetFcvValue(s_MenuObjZRot,
		                                 static_cast<float>(m_wmWorldState->m_titleState));
		float selectedYOffset = GetFcvValue(s_MenuObjYTrs,
		                                    static_cast<float>(m_wmWorldState->m_titleState));

		float openScale;
		if (m_wmWorldState->m_nextMenuMode != -1) {
			openScale = GetFcvValue(s_MenuObjScl,
			                        static_cast<float>(0x14 - m_wmWorldState->m_delay));
		} else {
			openScale = FLOAT_803313dc;
		}

		if (m_wmWorldState->m_mainState == 2 && m_wmWorldState->m_delay == 0) {
			m_wmWorldState->m_titleState++;
			if (m_wmWorldState->m_titleState >= 100) {
				m_wmWorldState->m_titleState = 0;
			}
		} else {
			m_wmWorldState->m_titleState = 0;
		}

		const float rotZSel = FLOAT_803314bc * selectedRotZ;
		const float rotYSel = FLOAT_803314bc * selectedRotY;
		for (i = 0; i < 5; i++) {
			if (!(((m_wmWorldState->m_mainState > 0) && (m_wmWorldState->m_mainState < 4)) || i == 1)) {
				continue;
			}

			WmWorldObjInfo* const panel = &worldObj[i];
			panel->m_active = 1;
			int frame = 0;
			float modelScale = FLOAT_803315d4;
			if (i == 0) {
				modelScale *= DOUBLE_803315D8;
			}

			panel->m_transform.m_scale.x = modelScale;
			float zero = FLOAT_803313dc;
			panel->m_transform.m_scale.y = modelScale;
			panel->m_transform.m_scale.z = modelScale;
			panel->m_transform.m_position.x = zero;
			panel->m_transform.m_position.y = zero;
			panel->m_transform.m_position.z = FLOAT_803315E0;
			panel->m_transform.m_rotation.x = zero;
			panel->m_transform.m_rotation.y = FLOAT_803315E4 * static_cast<float>(i);
			panel->m_transform.m_rotation.z = zero;

			PSMTXRotRad(workMtx, 'y', FLOAT_803314bc * panel->m_transform.m_rotation.y);
			PSMTXMultVecSR(workMtx, &panel->m_transform.m_position, &modelPos);
			PSMTXTransApply(workMtx, modelMtx, modelPos.x, modelPos.y, modelPos.z);
			PSMTXConcat(baseMtx, modelMtx, workMtx);
			{
				Vec* const mpp = &modelPos;
				mpp->x = workMtx[0][3];
				mpp->y = workMtx[1][3];
				mpp->z = workMtx[2][3];
			}
			PSMTXIdentity(workMtx);

			if (i == 1) {
				const int ms = m_wmWorldState->m_mainState;
				if (ms != 2) {
					if (ms < 2) {
						frame = 0x13 - (ms * 10 + m_wmWorldState->m_frameCounter);
						if (static_cast<int>(frame) < 0) {
							frame = 0;
						}
					} else {
						frame = m_wmWorldState->m_frameCounter + (ms - 3) * 10;
					}
				}
			}

			if (i == 0) {
				PSMTXRotRad(modelMtx, 'y', FLOAT_803315E8);
				Math.MTXRotRadApply(modelMtx, modelMtx, 'x', FLOAT_803315d0);
			} else if (i == 1) {
				if (m_wmWorldState->m_nextMenuMode != -1 && m_wmWorldState->m_cardChannel == 1 &&
				    m_wmWorldState->m_mainState != 2) {
					float inner = static_cast<float>(DOUBLE_80331600 *
					    (static_cast<double>(static_cast<float>(frame)) / DOUBLE_80331608));
					float rot = static_cast<float>(
					    DOUBLE_803315F0 * (DOUBLE_803315F8 + inner));
					PSMTXRotRad(modelMtx, 'x', rot);
				} else {
					PSMTXRotRad(modelMtx, 'x', FLOAT_80331610);
				}
			} else if (i == 2 || i == 3 || i == 4) {
				PSMTXRotRad(modelMtx, 'x', FLOAT_80331614);
			}

			if (m_wmWorldState->m_cardChannel == i) {
				PSMTXRotRad(workMtx, 'z', rotZSel);
				Math.MTXRotRadApply(workMtx, workMtx, 'y', rotYSel);
				PSMTXConcat(workMtx, modelMtx, modelMtx);
			}

			s_MMenuPos[i].x = modelPos.x;
			s_MMenuPos[i].y = static_cast<float>(static_cast<double>(modelPos.y) + DOUBLE_80331418);
			s_MMenuPos[i].z = modelPos.z;
			PSMTXTransApply(modelMtx, workMtx, FLOAT_803313dc, FLOAT_803313dc, modelPos.z);
			PSMTXScaleApply(workMtx, modelMtx, panel->m_transform.m_scale.x,
			                panel->m_transform.m_scale.y, panel->m_transform.m_scale.z);
			if (i == 0) {
				PSMTXTransApply(modelMtx, modelMtx, FLOAT_80331618, FLOAT_8033161C, FLOAT_803313dc);
			} else if (i == 1) {
				PSMTXTransApply(modelMtx, modelMtx, FLOAT_80331620, FLOAT_803313dc, FLOAT_803313dc);
			}
			if (m_wmWorldState->m_cardChannel == i) {
				modelMtx[1][3] = modelMtx[1][3] + selectedYOffset;
			}

			if (m_wmWorldState->m_nextMenuMode != -1 && i == 1 &&
			    m_wmWorldState->m_cardChannel == 1 && m_wmWorldState->m_mainState != 2) {
				double u = static_cast<double>(frame) / DOUBLE_80331608;
				float m00 = modelMtx[0][3];
				float m10 = modelMtx[1][3];
				float m20 = modelMtx[2][3];
				modelMtx[0][3] = m00 + static_cast<float>(static_cast<float>(-m00 * u) * u);
				modelMtx[1][3] = m10 + static_cast<float>(static_cast<float>(DOUBLE_80331628 - m10 * u) * u);
				modelMtx[2][3] = m20 + static_cast<float>(static_cast<float>(DOUBLE_80331630 - m20) * u);
			}

			if (m_wmWorldState->m_nextMenuMode != -1 && m_wmWorldState->m_cardChannel == i &&
			    m_wmWorldState->m_delay != 0) {
				PSMTXScale(workMtx, openScale, openScale, openScale);
				PSMTXConcat(workMtx, modelMtx, modelMtx);
			}

			if (m_wmWorldState->m_nextMenuMode != -1 && i == 1 &&
			    m_wmWorldState->m_cardChannel == 1 && m_wmWorldState->m_mainState != 2) {
				float openScale2 = static_cast<float>(
				    static_cast<float>(DOUBLE_803313F8 * (static_cast<double>(frame) / DOUBLE_80331608)) +
				    DOUBLE_80331420);
				PSMTXScale(workMtx, openScale2, openScale2, openScale2);
				PSMTXConcat(workMtx, modelMtx, modelMtx);
			}

			if (m_wmWorldState->m_mainState == 1) {
				GetWmWorldHandles(this)[i]->m_model->m_lightAlpha =
				    static_cast<float>(DOUBLE_803314E8 * static_cast<double>(m_wmWorldState->m_frameCounter));
			} else if (m_wmWorldState->m_mainState == 2) {
				GetWmWorldHandles(this)[i]->m_model->m_lightAlpha = FLOAT_803313e8;
			} else if (m_wmWorldState->m_mainState == 3) {
				GetWmWorldHandles(this)[i]->m_model->m_lightAlpha =
				    static_cast<float>(-(DOUBLE_803314E8 * static_cast<double>(m_wmWorldState->m_frameCounter) -
				                         DOUBLE_80331420));
			} else {
				GetWmWorldHandles(this)[i]->m_model->m_lightAlpha = FLOAT_803313dc;
			}
			if (m_wmWorldState->m_nextMenuMode != -1 && m_wmWorldState->m_cardChannel == 1 &&
			    i == 1) {
				GetWmWorldHandles(this)[i]->m_model->m_lightAlpha = FLOAT_803313e8;
			}
			GetWmWorldHandles(this)[i]->m_model->SetMatrix(modelMtx);
			GetWmWorldHandles(this)[i]->m_model->CalcMatrix();
			GetWmWorldHandles(this)[i]->m_model->CalcSkin();
		}
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 172b
 * EN Address: 0x80118104
 * EN Size: 300b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::ChkSelectParty()
{
	for (int i = 0; i < kWmMenuControllerCount; i++) {
		if (Game.m_caravanWorkArr[m_wmWorldState->m_originalBackupParams[i]].m_shopState == 0) {
			m_wmWorldState->m_originalBackupParams[i] = -1;
		}
		if (Game.m_caravanWorkArr[m_wmWorldState->m_backupParams[i]].m_shopState == 0) {
			m_wmWorldState->m_backupParams[i] = -1;
		}
		const int slot = Game.m_gameWork.m_wmBackupParams[i];
		if (Game.m_caravanWorkArr[slot].m_shopState == 0) {
			Game.m_gameWork.m_wmBackupParams[i] = -1;
		}
		if (Game.m_caravanWorkArr[slot].m_shopBusyFlag != 0) {
			Game.m_gameWork.m_wmBackupParams[i] = -1;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800ECFF0
 * PAL Size: 2396b
 * EN Address: 0x800EC734
 * EN Size: 2396b
 * JP Address: 0x800E9C64
 * JP Size: 2296b
 */
void CMenuPcs::DrawMainMenuSub()
{
	int orderIndex;
	int j;
	int i;
	static const float s_sprt_w[] = {264.0f, 264.0f, 264.0f, 264.0f, 264.0f};
	Mtx modelMtx;
	Mtx44 screenMtx;
	GXColor white;
	unsigned int drawOrder[5];
	float depthValues[5];

	SetProjection(23);
	CameraPcs.GetProjectionMatrix(screenMtx);

	for (i = 0; i < 5; i++) {
		Vec viewPos;
		Vec4d clipPos;
		viewPos.x = s_MMenuPos[i].x;
		viewPos.z = s_MMenuPos[i].z;
		viewPos.y = s_MMenuPos[i].y;
		viewPos.z = viewPos.z - FLOAT_80331598;
		Math.MTX44MultVec4(screenMtx, &viewPos, &clipPos);

		clipPos.x = clipPos.x / clipPos.w;
		clipPos.y = clipPos.y / clipPos.w;
		clipPos.x = 320.0 * (clipPos.x + 1.0);
		clipPos.y = 224.0 * (-clipPos.y + 1.0);
		m_wm.m_worldObjData[i].m_viewportX =
		    static_cast<short>(static_cast<int>(clipPos.x - FLOAT_803315B0));
		m_wm.m_worldObjData[i].m_viewportY =
		    static_cast<short>(static_cast<int>(clipPos.y - FLOAT_803315B4));
		m_wm.m_worldObjData[i].m_viewportWidth = 0x280;
		m_wm.m_worldObjData[i].m_viewportHeight = 0x1C0;
		m_wm.m_worldObjData[i].m_cameraPosition.y = m_wm.m_worldObjData[i].m_cameraPosition.x = FLOAT_803313dc;
		m_wm.m_worldObjData[i].m_cameraPosition.z = FLOAT_80331598;
	}

	for (i = 0; i < 5; i++) {
		m_wm.m_handles[i]->m_model->GetMatrix(modelMtx);
		depthValues[i] = modelMtx[2][3];
		drawOrder[i] = i;
	}

	for (i = 0; i < 5; i++) {
		for (j = i + 1; j < 5; j++) {
			if (depthValues[i] > depthValues[j]) {
				float depth = depthValues[i];
				unsigned int index = drawOrder[i];
				depthValues[i] = depthValues[j];
				drawOrder[i] = drawOrder[j];
				depthValues[j] = depth;
				drawOrder[j] = index;
			}
		}
	}

	white.r = 0xFF;
	white.g = 0xFF;
	white.b = 0xFF;
	white.a = 0xFF;
	for (orderIndex = 0; orderIndex < 5; orderIndex++) {
		short state = m_wmWorldState->m_mainState;
		if (state < 1 || state > 3) {
			if (m_wmWorldState->m_cardChannel != 1 || orderIndex != 1) {
				continue;
			}
			drawOrder[orderIndex] = 1;
		}

		SetProjection(drawOrder[orderIndex]);
		SetLight(0);
		m_wm.m_handles[drawOrder[orderIndex]]->Draw(5);
		DrawInit();

		GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
		SetProjection(drawOrder[orderIndex]);

		if (m_wmWorldState->m_mainState == 2) {
			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kWorldFrameTexture));
			MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
			GXSetChanMatColor(static_cast<GXChannelID>(4), white);
			unsigned int idx = drawOrder[orderIndex];
			float frameWidth = s_sprt_w[idx];
			float frameX = FLOAT_803313dc;
			frameX -= FLOAT_80331414 * (frameWidth / FLOAT_803315B8);
			MenuPcs.DrawRect3d(0, frameX, FLOAT_803315BC,
			           static_cast<float>(DOUBLE_80331418 + static_cast<double>(s_MMenuPos[idx].z) - DOUBLE_803315C0),
			           frameWidth, FLOAT_80331554, FLOAT_803313dc,
			           FLOAT_80331554 * static_cast<float>(static_cast<int>(idx)) + FLOAT_80331528,
			           FLOAT_803315C8, FLOAT_803315C8);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800ecfd0
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetMcAccessPos(int* x, int* y)
{
	*x = gWmMenuCursorX[0];
	*y = gWmMenuCursorX[1];
}

/*
 * --INFO--
 * PAL Address: 0x800ecfb0
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetMcOdekakePos(int* x, int* y)
{
	*x = gWmMenuCursorY[0];
	*y = gWmMenuCursorY[1];
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 76b
 * EN Address: 0x80118790
 * EN Size: 108b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::ChkMcDataCnt()
{
	int count;
	int i;
	for (i = count = 0; i < kMcListCount; i++) {
		const McListInfo& entry = m_wmCharaState[i];
		if (entry.m_isBroken == 0 && static_cast<int>(entry.m_scriptSysVal0) > 0) {
			count++;
		}
	}
	return count;
}

/*
 * --INFO--
 * PAL Address: 0x800EB6F8
 * PAL Size: 6328b
 * EN Address: 0x800EADFC
 * EN Size: 6392b
 * JP Address: 0x800E875C
 * JP Size: 5320b
 */
void CMenuPcs::DrawMCList()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	static const int s_TimeWTbl[] = {17, 10, 16, 16, 19, 17, 16, 16, 16, 15, 8};
	static const unsigned char s_LocTex[][4] = {
		{1, 1, 0, 0},
		{1, 2, 0, 0},
		{1, 3, 0, 0},
		{1, 0, 1, 0},
		{1, 2, 1, 0},
		{1, 3, 1, 0},
		{1, 2, 3, 0},
		{1, 3, 2, 0},
		{2, 0, 1, 0},
		{1, 1, 2, 0},
		{2, 3, 0, 0},
		{1, 1, 3, 0},
		{1, 0, 3, 0},
		{2, 2, 0, 0},
		{2, 2, 0, 0},
		{1, 0, 0, 0},
		{1, 1, 1, 0},
		{1, 0, 2, 0},
		{1, 2, 2, 0},
		{2, 2, 1, 0},
		{2, 0, 0, 0},
		{1, 2, 3, 0},
		{1, 2, 3, 0},
		{1, 3, 3, 0},
		{2, 1, 0, 0},
	};
	CFont* fontF8 = GetFont22();
	GXColor colors[4];
	int slot;
	int slotOff;
#define worldState GetWmWorldState(this)
	short state = worldState->m_mainState;

	if ((state == 2 || state == 3) && worldState->m_subState != 0) {
		slotOff = 0;
		slot = 0;
		do {
			float yPos;
			float alpha;
			short sub = worldState->m_subState;
			if (sub == 1 || worldState->m_mainState == 3) {
				int animFrames;
				if (worldState->m_mainState == 2) {
					animFrames = (int)worldState->m_frameCounter - slotOff;
				} else {
					animFrames = 10 - ((int)worldState->m_frameCounter - (3 - slot) * 3);
				}
				if (animFrames < 0) {
					goto nextListEntry;
				}
				if (animFrames > 10) {
					yPos = FLOAT_803314D8;
					alpha = FLOAT_803313e8;
				} else {
					yPos = FLOAT_803314DC + static_cast<float>(animFrames) * FLOAT_803314E0;
					alpha = static_cast<float>(DOUBLE_803314E8 * static_cast<double>(animFrames));
				}
			} else {
				yPos = FLOAT_803314D8;
				alpha = FLOAT_803313e8;
			}
			if (!(alpha <= DOUBLE_803314F0)) {
				float slotY = static_cast<float>(DOUBLE_80331498 * static_cast<double>(slot) + DOUBLE_80331490);
				MenuPcs.SetAttrFmt((FMT)0);
				alpha = FLOAT_80331458 * alpha;
				colors[0].r = 0xFF;
				colors[0].g = 0xFF;
				colors[0].b = 0xFF;
				colors[0].a = static_cast<unsigned char>(static_cast<int>(alpha));
				GXSetChanMatColor(GX_COLOR0A0, colors[0]);

				// Draw slot background
				MenuPcs.SetTexture((TEX)kMcSlotLeftTexture);
				MenuPcs.DrawRect(0, yPos, slotY, FLOAT_80331468, FLOAT_803314F8,
				         FLOAT_803313dc, FLOAT_803313dc,
				         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
				MenuPcs.SetTexture((TEX)kMcSlotMiddleTexture);
				yPos += FLOAT_80331468;
				MenuPcs.DrawRect(0, yPos, slotY, FLOAT_803314FC, FLOAT_803314F8,
				         FLOAT_803313dc, FLOAT_803313dc,
				         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
				yPos += FLOAT_803314FC;

				// Draw slot content area
				MenuPcs.SetAttrFmt((FMT)1);
				colors[0].r = 0xFF;
				colors[0].g = 0xFF;
				colors[0].b = 0xFF;
				const float alpha2 = alpha;
				const float alpha3 = alpha;
				colors[0].a = static_cast<unsigned char>(static_cast<int>(alpha3));
				colors[1].r = 0xFF;
				colors[1].g = 0xFF;
				colors[1].b = 0xFF;
				colors[1].a = 0;
				colors[2].r = 0xFF;
				colors[2].g = 0xFF;
				colors[2].b = 0xFF;
				colors[2].a = static_cast<unsigned char>(static_cast<int>(static_cast<float>(alpha2)));
				colors[3].r = 0xFF;
				colors[3].g = 0xFF;
				colors[3].b = 0xFF;
				colors[3].a = 0;
				MenuPcs.DrawRect(0, yPos, slotY, FLOAT_80331500, FLOAT_803314F8,
				         FLOAT_803313dc, FLOAT_803313dc, colors,
				         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
			}
nextListEntry:
			slot++;
			slotOff += 3;
		} while (slot < 4);
	}

	float frameAlpha;
	state = worldState->m_mainState;
	if (state == 0) {
		frameAlpha = static_cast<float>(DOUBLE_803314E8 * static_cast<double>(static_cast<int>(worldState->m_frameCounter)));
	} else if (state > 0 && state < 4) {
		frameAlpha = FLOAT_803313e8;
	} else {
		frameAlpha = static_cast<float>(-(DOUBLE_803314E8 * static_cast<double>(static_cast<int>(worldState->m_frameCounter)) - DOUBLE_80331420));
	}
	DrawWMFrame0(2, frameAlpha);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	colors[0].r = 0xFF;
	colors[0].g = 0xFF;
	colors[0].b = 0xFF;
	colors[0].a = 0xFF;
	GXSetChanMatColor(static_cast<GXChannelID>(4), colors[0]);
	short separatorSub = worldState->m_subState;
	if (separatorSub != 0 && separatorSub > 1 &&
	    worldState->m_mainState == 2) {
		const float* psZ = &FLOAT_803313dc;
		double psSl = DOUBLE_80331498;
		double sepOff;
		double sepBase;
		double sepSlope;
		float sepZero;
		sepZero = *psZ;
		sepSlope = psSl;
		sepBase = DOUBLE_80331490;
		sepOff = DOUBLE_80331510;
		for (int slot = 0; slot < kMcListCount; slot++) {
			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kWorldFrameTexture));
			MenuPcs.DrawRect(0, FLOAT_803314D8,
			         static_cast<float>(static_cast<float>(sepSlope * static_cast<double>(slot) + sepBase) -
			                            sepOff),
			         FLOAT_803314D8, FLOAT_803314D8,
			         static_cast<float>(sepBase * static_cast<double>(slot)), FLOAT_803313e0,
			         FLOAT_803313e8, FLOAT_803313e8, sepZero);
		}
	}

	if (worldState->m_subState >= 0x11 &&
	    worldState->m_mainState < 3) {
		double pSl2 = DOUBLE_80331498;
		float p518a = FLOAT_80331518;
		double rowBaseD;
		float slotY;
		double mapX;
		double rowSlopeD;
		mapX = DOUBLE_80331510 + static_cast<double>(p518a);
#ifndef VERSION_GCCJGC
		const int language = Game.m_gameWork.GetLanguage();
#endif
		const int* digitWidths = s_YearWTbl;
		const int* playWidths = s_TimeWTbl;
		rowSlopeD = pSl2;
		rowBaseD = DOUBLE_80331490;
		for (slot = 0; slot < kMcListCount; slot++) {
			const McListInfo* const slotData = &m_wmCharaState[slot];
			slotY = static_cast<float>(rowSlopeD * static_cast<double>(slot) + rowBaseD);
			if (slotData->m_isBroken == 0 && slotData->m_hasData != 0) {
				float digitX;
				float rowY = FLOAT_80331440 + slotY;
				float capX = FLOAT_80331468;
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kMcCharacterFrameTexture));
				MenuPcs.DrawRect(0, FLOAT_80331468, rowY, FLOAT_803314D8, FLOAT_80331440,
				         FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);

				int totalWidth = 0;
				if (slotData->m_characterIds[0] >= 0) {
					totalWidth = 1;
				}
				if (slotData->m_characterIds[1] >= 0) {
					totalWidth++;
				}
				if (slotData->m_characterIds[2] >= 0) {
					totalWidth++;
				}
				if (slotData->m_characterIds[3] >= 0) {
					totalWidth++;
				}
				const int panelWidth = totalWidth * 0x30 + 0x40;
				const float* pD8c2 = &FLOAT_803314D8;
				capX += *pD8c2 + static_cast<float>(panelWidth);
				const float* pD8c3 = &FLOAT_803314D8;
				MenuPcs.DrawRect(8, capX, rowY, *pD8c3, FLOAT_80331440,
				         FLOAT_803313dc, FLOAT_803313dc,
				         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kMcCharacterFillTexture));
				MenuPcs.DrawRect(0, FLOAT_8033151c, rowY, static_cast<float>(panelWidth), FLOAT_80331440,
				         FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);

				digitX = FLOAT_80331520;
#ifdef VERSION_GCCJGC
				rowY = FLOAT_803314D8 + slotY;
#else
				if (language != 5) {
					rowY = FLOAT_803314D8 + slotY;
				}
#endif
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kMcYearTexture));
				int digitCount = (static_cast<int>(slotData->m_scriptSysVal0) > 9) + 1;
				if (static_cast<int>(slotData->m_scriptSysVal0) > 99) {
					digitCount = 3;
				}
				if (digitCount == 3) {
					const int dw10 = digitWidths[10];
					MenuPcs.DrawRect(0, FLOAT_80331520, rowY, static_cast<float>(dw10), FLOAT_80331410,
					         FLOAT_80331524, FLOAT_80331528, FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
				} else {
					for (int di = 0; di < digitCount; di++) {
						if (digitCount == 1) {
							totalWidth = digitWidths[static_cast<int>(slotData->m_scriptSysVal0) % 10];
						} else if (di == 0) {
							totalWidth = digitWidths[static_cast<int>(slotData->m_scriptSysVal0) / 10];
						} else {
							totalWidth += digitWidths[static_cast<int>(slotData->m_scriptSysVal0) % 10];
						}
					}
#ifdef VERSION_GCCJGC
					digitX += (float)((32 - totalWidth) / 2);
#else
					double digitScaleD;
					if (language != 5) {
						digitScaleD = DOUBLE_80331530;
					} else {
						digitScaleD = DOUBLE_80331420;
					}
					float digitScale = static_cast<float>(digitScaleD);
					if (language == 2) {
						totalWidth += 8;
					} else if (language == 3) {
						totalWidth += 0xB;
					} else if (language != 5) {
						totalWidth += 0x20;
					}
					digitX += static_cast<float>((0x20 - static_cast<int>(static_cast<float>(totalWidth) * digitScale)) / 2);
#endif
					const float* pZd1 = &FLOAT_803313dc;
					const double* pCs1 = &DOUBLE_80331490;
					const double* pRs1 = &DOUBLE_80331540;
					const double* pRb1 = &DOUBLE_80331538;
					double rowBase;
					double rowSlope;
					double colSlope;
					float zeroF;
					zeroF = *pZd1;
					colSlope = *pCs1;
					rowSlope = *pRs1;
					rowBase = *pRb1;
					const int* const dw = s_YearWTbl;
					for (int digitIdx = 0; digitIdx < digitCount; digitIdx++) {
						int digit;
						if (digitCount == 1) {
							digit = static_cast<int>(slotData->m_scriptSysVal0) % 10;
						} else if (digitIdx == 0) {
							digit = static_cast<int>(slotData->m_scriptSysVal0) / 10;
						} else {
							digit = static_cast<int>(slotData->m_scriptSysVal0) % 10;
						}
						const int digitWidth = dw[digit];
						const float digitWidthF = static_cast<float>(digitWidth);
						MenuPcs.DrawRect(0, digitX, rowY, digitWidthF, FLOAT_80331410,
						         static_cast<float>(colSlope * static_cast<float>(digit % 5)),
						         static_cast<float>(rowSlope * static_cast<float>(digit / 5) + rowBase),
#ifdef VERSION_GCCJGC
						         FLOAT_803313e8, FLOAT_803313e8, zeroF);
						digitX += digitWidthF;
#else
						         digitScale, FLOAT_803313e8, zeroF);
						digitX += digitWidthF * digitScale;
#endif
					}
#ifndef VERSION_GCCJGC
					float suffixU;
					float suffixWidth;
					if (language == 2) {
						suffixWidth = FLOAT_80331548;
					} else if (language == 3) {
						suffixWidth = FLOAT_8033154C;
					} else {
						suffixWidth = FLOAT_80331410;
					}
					suffixU = FLOAT_803313dc;
					unsigned char wideLang = (language == 1 || language == 4);
					double suffixScaleD;
					if (wideLang) {
						suffixScaleD = DOUBLE_80331530;
					} else {
						suffixScaleD = DOUBLE_80331420;
					}
					float suffixScale = static_cast<float>(suffixScaleD);
					if (language == 1) {
						if (static_cast<int>(slotData->m_scriptSysVal0) / 10 == 1) {
							suffixU = FLOAT_8033151c;
						} else {
							const int ones = static_cast<int>(slotData->m_scriptSysVal0) % 10;
							if (ones >= 1 && ones <= 3) {
								suffixU = FLOAT_803314D8 * static_cast<float>(ones - 1);
							} else {
								suffixU = FLOAT_8033151c;
							}
						}
					} else if (language == 4) {
						if (static_cast<int>(slotData->m_scriptSysVal0) != 1) {
							suffixU = FLOAT_803314D8;
						}
					} else if (language == 2) {
						rowY += FLOAT_80331550;
					}
					if (language != 5) {
						MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x34));
						MenuPcs.DrawRect(0, digitX, rowY, suffixWidth, FLOAT_803314D8,
						         FLOAT_803313dc, suffixU, suffixScale, FLOAT_803313e8, FLOAT_803313dc);
					}
#endif
				}

				float labelX = FLOAT_80331520;
#ifdef VERSION_GCCJGC
				float dateLabelY = FLOAT_80331554 + slotY;
#else
				float dateLabelY;
				if (language != 5) {
					dateLabelY = FLOAT_80331554 + slotY;
				} else {
					dateLabelY = FLOAT_803314c8 + (FLOAT_803314D8 + slotY);
				}
				labelX -= FLOAT_80331550;
#endif
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kMcYearLabelTexture));
				MenuPcs.DrawRect(0, labelX, dateLabelY,
#ifdef VERSION_GCCJGC
				         32.0f, FLOAT_80331558, FLOAT_803313dc, FLOAT_803313dc,
#else
				         FLOAT_80331440, FLOAT_80331558, FLOAT_803313dc, FLOAT_803313dc,
#endif
				         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);

				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kMcFaceTexture));
				float iconX = FLOAT_8033155C;
				const float iconY = FLOAT_803314D8 + slotY;
				const int* memberPtr = slotData->m_characterIds;
				for (int member = 0; member < 4; member++, memberPtr++) {
					const int modelNo = *memberPtr;
					if (modelNo >= 0) {
						const int faceNo = modelNo - 100;
						float texU;
						if ((faceNo / 100 & 1) != 0) {
							texU = FLOAT_80331560;
						} else {
							double pHf1 = DOUBLE_803314F0;
							texU = static_cast<float>(pHf1);
						}
						const float du = static_cast<float>(faceNo % 100) * FLOAT_80331468;
						texU += du;
						const float* pW68f = &FLOAT_80331468;
						MenuPcs.DrawRect(0, iconX, iconY, *pW68f, *pW68f,
						         texU,
						         static_cast<float>(faceNo / 100 / 2) * *pW68f,
						         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
						iconX += FLOAT_80331468;
					}
				}
				rowY = FLOAT_80331468 + slotY;
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kMcTimeTexture));
				MenuPcs.DrawRect(0, FLOAT_80331564, rowY,
				         FLOAT_80331554, FLOAT_803314D8, FLOAT_803313dc, FLOAT_803313dc,
				         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);

				int playHours;
				int playMinutes;
				MemoryCardMan.CnvPlayTime(slotData->m_frameCounter, &playHours, &playMinutes);
				int playDigits[5];
				float playWidth = FLOAT_803313dc;
				const int hundreds = playHours / 100;
				if (hundreds != 0) {
					playDigits[0] = hundreds;
					playWidth += static_cast<float>(playWidths[hundreds]);
				} else {
					playDigits[0] = -1;
				}
				const int hourRemainder = playHours % 100;
				const int tens = hourRemainder / 10;
				if (tens != 0 || playDigits[0] > 0) {
					playDigits[1] = tens;
					playWidth += static_cast<float>(playWidths[tens]);
				} else {
					playDigits[1] = -1;
				}
				playDigits[2] = hourRemainder % 10;
				playDigits[3] = playMinutes / 10;
				playDigits[4] = playMinutes % 10;
				playWidth += static_cast<float>(playWidths[playDigits[2]]);
				playWidth += static_cast<float>(playWidths[10]);
				playWidth += static_cast<float>(playWidths[playDigits[3]]);
				playWidth += static_cast<float>(playWidths[playDigits[4]]);
				float playX = FLOAT_80331518 - playWidth;
				for (int digitIdx = 0; digitIdx < 5; digitIdx++) {
					if (playDigits[digitIdx] >= 0) {
						if (digitIdx == 3) {
							const float colonW = static_cast<float>(playWidths[10]);
							const float* pOe5 = &FLOAT_803313e8;
							MenuPcs.DrawRect(0, playX, rowY, colonW, FLOAT_803314D8,
							         FLOAT_80331568, FLOAT_803313dc, *pOe5, *pOe5, FLOAT_803313dc);
							playX += colonW;
						}
						const float digitW = static_cast<float>(playWidths[playDigits[digitIdx]]);
						const float* pOe6 = &FLOAT_803313e8;
						MenuPcs.DrawRect(0, playX, rowY, digitW, FLOAT_803314D8,
						         static_cast<float>(DOUBLE_80331490 * static_cast<double>(playDigits[digitIdx]) + DOUBLE_80331570),
						         FLOAT_803313dc, *pOe6, *pOe6, FLOAT_803313dc);
						playX += digitW;
					}
				}

				const unsigned char* mapInfo = s_LocTex[slotData->m_scriptGlobalTime];
				SetTextureLoc(mapInfo[0]);
				MenuPcs.DrawRect(0,
				         static_cast<float>(mapX),
				         static_cast<float>(DOUBLE_80331510 + static_cast<double>(slotY)),
				         FLOAT_80331578, FLOAT_80331578,
				         static_cast<float>(static_cast<int>(static_cast<char>(mapInfo[1])) << 7),
				         static_cast<float>(static_cast<int>(static_cast<char>(mapInfo[2])) << 7),
				         FLOAT_80331434, FLOAT_80331434, FLOAT_803313dc);
			}
		}

		// Draw text info for each save slot
		const double tSlope = DOUBLE_80331498;
		const double tBase = DOUBLE_80331490;
		for (slot = 0; slot < kMcListCount; slot++) {
			char locationStr[64];
			char line1[64];
			char line2[64];
			const McListInfo* const slotData = &m_wmCharaState[slot];
			const float slotY = static_cast<float>(tSlope * static_cast<double>(slot) + tBase);
			if (slotData->m_isBroken != 0 || static_cast<int>(slotData->m_scriptSysVal0) <= 0) {
				fontF8->SetMargin(FLOAT_803313e8);
				fontF8->SetShadow(1);
				fontF8->SetScale(FLOAT_803313e8);
				fontF8->DrawInit();
				fontF8->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
				fontF8->SetTlut(0x19);
				const unsigned int msgId =
					slotData->m_isBroken == 0;
				const int width = static_cast<int>(fontF8->GetWidth(const_cast<char*>(GetMcStr(msgId))));
				double pHd1 = DOUBLE_803313F8;
				float pD8f1 = FLOAT_803314D8;
				fontF8->SetPosX(static_cast<float>(static_cast<float>(0x238 - width) * pHd1 + pD8f1));
				fontF8->SetPosY(static_cast<float>(DOUBLE_80331580 + static_cast<double>(slotY)));
				fontF8->Draw(const_cast<char*>(GetMcStr(msgId)));
			} else {
				fontF8->SetMargin(FLOAT_803313e8);
				fontF8->SetShadow(0);
				fontF8->SetScale(FLOAT_80331588);
				fontF8->DrawInit();
				fontF8->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
				fontF8->SetTlut(0x2C);
				fontF8->SetPosX(FLOAT_80331520);
				fontF8->SetPosY(static_cast<float>(static_cast<double>(slotY) - DOUBLE_80331510));
#ifdef VERSION_GCCJGC
				fontF8->Draw(const_cast<char*>(slotData->m_townName));
#else
				strcpy(locationStr, slotData->m_townName);
				Game.UpperItemName(locationStr);
				fontF8->Draw(locationStr);
#endif

				fontF8->SetMargin(FLOAT_803313e8);
				fontF8->SetShadow(1);
				fontF8->SetScale(FLOAT_8033158C);
				fontF8->DrawInit();
				fontF8->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
				fontF8->SetTlut(7);
				const int locationIndex = slotData->m_scriptGlobalTime;
				if (locationIndex == 0x0F) {
					strcpy(locationStr, slotData->m_townName);
				} else if (locationIndex == 0x16) {
#ifdef VERSION_GCCJGC
					strcpy(locationStr, slotData->m_townName);
					strcpy(locationStr + strlen(locationStr) - 4, "\x82\xCC\x8D\x60");
#else
					SetPortTownName(locationStr, slotData->m_townName);
#endif
				} else {
					strcpy(locationStr, Game.GetPlaceName(locationIndex));
				}
#ifdef VERSION_GCCJGC
				fontF8->SetPosX(FLOAT_80331518 - fontF8->GetWidth(locationStr));
				fontF8->SetPosY(FLOAT_80331558 + slotY);
				fontF8->Draw(locationStr);
#else
				Game.UpperItemName(locationStr);
				const float locationWidth = fontF8->GetWidth(locationStr);
				float locationY = FLOAT_80331558 + slotY;
				if (locationWidth <= FLOAT_8033155C) {
					fontF8->SetPosX(FLOAT_80331518 - locationWidth);
					fontF8->SetPosY(locationY);
					fontF8->Draw(locationStr);
				} else {
					locationY = locationY + FLOAT_80331550;
					SplitPlace2(locationStr, line1, line2, fontF8, 0x90);
					const float w1 = fontF8->GetWidth(line1);
					fontF8->SetPosX(FLOAT_80331518 - w1);
					fontF8->SetPosY(locationY - FLOAT_80331590);
					fontF8->Draw(line1);
					const float w2 = fontF8->GetWidth(line2);
					fontF8->SetPosX(FLOAT_80331518 - w2);
					fontF8->SetPosY(locationY);
					fontF8->Draw(line2);
				}
#endif
			}
		}
	}
	if (worldState->m_subState == 0x11) {
		short mode = worldState->m_menuMode;
		if (mode == 5) {
#ifdef VERSION_GCCJGC
			char text[256] = "\x83\x8D\x81\x5B\x83\x68\x82\xB7\x82\xE9\x83\x66\x81\x5B\x83\x5E\x82\xF0\x91\x49\x82\xF1\x82\xC5\x82\xAD\x82\xBE\x82\xB3\x82\xA2";
			DrawFont((int)CalcCenteringPos(text, 22), 391,
			         CColor(255, 255, 255, 255).color, 7, text, 1.0f, 1.0f);
#else
			DrawFont2(static_cast<int>(CalcCenteringPos2(const_cast<char*>(GetMcStr(2)), FLOAT_80331594, FLOAT_803313e8)), 0x187,
			          CColor(0xFF, 0xFF, 0xFF, 0xFF).color, 7, const_cast<char*>(GetMcStr(2)), FLOAT_80331594, FLOAT_803313e8, FLOAT_803313e8);
#endif
		} else if (mode == 2) {
#ifdef VERSION_GCCJGC
			char text[256] = "\x83\x66\x81\x5B\x83\x5E\x82\xF0\x82\xC7\x82\xB1\x82\xC9\x83\x5A\x81\x5B\x83\x75\x82\xB5\x82\xDC\x82\xB7\x82\xA9\x81\x48";
			DrawFont((int)CalcCenteringPos(text, 22), 391,
			         CColor(255, 255, 255, 255).color, 7, text, 1.0f, 1.0f);
#else
			DrawFont2(static_cast<int>(CalcCenteringPos2(const_cast<char*>(GetMcStr(3)), FLOAT_80331594, FLOAT_803313e8)), 0x187,
			          CColor(0xFF, 0xFF, 0xFF, 0xFF).color, 7, const_cast<char*>(GetMcStr(3)), FLOAT_80331594, FLOAT_803313e8, FLOAT_803313e8);
#endif
		}
#ifdef VERSION_GCCJGC
		DrawInit();
#endif
	}
#ifndef VERSION_GCCJGC
	DrawInit();
#endif
#undef worldState
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 248b
 * EN Address: 0x8011A1BC
 * EN Size: 372b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::DrawHelpBase(int texture, float alpha)
{
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXColor color;
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = static_cast<unsigned char>(255.0f * alpha);
	GXSetChanMatColor(GX_COLOR0A0, color);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(texture));
	float height = 40.0f;
	MenuPcs.DrawRect(0, 0.0f, static_cast<float>(424.0 - height), 640.0f, height, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
}

/*
 * --INFO--
 * PAL Address: 0x800EB1D8
 * PAL Size: 1312b
 * EN Address: 0x800EA8DC
 * EN Size: 1312b
 * JP Address: 0x800E82B8
 * JP Size: 1188b
 */
void CMenuPcs::CalcMcObj()
{
	WmWorldObjInfo* const worldObj = m_wm.m_worldObjData;

	float panelStateFloat = FLOAT_80331480;
	int i;
	int viewSlot = 17;
	WmWorldObjInfo* panelState = &worldObj[17];
	for (i = 0; i < 4; i++, panelState++, viewSlot++) {
		panelState->m_viewportX = static_cast<short>(panelStateFloat);

		const int y = static_cast<int>(
		    static_cast<float>(DOUBLE_80331488 + (DOUBLE_80331498 * static_cast<double>(i) + DOUBLE_80331490)) -
		    FLOAT_803314A0);
		panelState->m_viewportY = static_cast<short>(y);
		panelState->m_viewportWidth = 0x140;
		panelState->m_viewportHeight = 0xE0;
		panelState->m_cameraPosition.x = FLOAT_803313dc;
		panelState->m_cameraPosition.y = FLOAT_803313dc;
		panelState->m_cameraPosition.z = FLOAT_803314A4;

		const McListInfo* const charaState = &m_wmCharaState[i];
		CMenuPcs::FCV* const yTbl = &s_WoodTrns;
		panelState->m_frameCounter++;
		if (static_cast<float>(static_cast<int>(panelState->m_frameCounter)) >=
		    DOUBLE_803314A8 * static_cast<double>(yTbl->keys[s_WoodTrns.keyCount - 1].time)) {
			panelState->m_frameCounter = 0;
		}

		if (static_cast<int>(charaState->m_scriptSysVal0) <= 0) {
			panelState->m_active = 0;
		} else {
			Mtx scaleMtx;
			Mtx rotXMtx;
			Mtx rotYMtx;

			panelState->m_active = 1;
			panelState->m_transform.m_position.x = FLOAT_803314B0;
			panelState->m_transform.m_position.y = FLOAT_803314B4;
			panelState->m_transform.m_position.z = FLOAT_803313dc;
			panelState->m_transform.m_scale.x = FLOAT_80331434;
			panelState->m_transform.m_scale.y = FLOAT_80331434;
			panelState->m_transform.m_scale.z = FLOAT_80331434;
			panelState->m_transform.m_rotation.x = FLOAT_803314B8;
			panelState->m_transform.m_rotation.y += FLOAT_803314bc;

			panelState->m_transform.m_position.y =
			    panelState->m_transform.m_position.y +
			    static_cast<float>(GetFcvValue(s_WoodTrns,
			                                   static_cast<float>(static_cast<int>(panelState->m_frameCounter))));

			const float rotVal =
			    static_cast<float>(GetFcvValue(s_WoodRot,
			                                   static_cast<float>(static_cast<int>(panelState->m_frameCounter))));

			panelState->m_transform.m_rotation.y = FLOAT_803314bc * rotVal;
			PSMTXScale(scaleMtx, panelState->m_transform.m_scale.x, panelState->m_transform.m_scale.y,
			           panelState->m_transform.m_scale.z);
			PSMTXRotRad(rotXMtx, 'x', panelState->m_transform.m_rotation.x);
			PSMTXRotRad(rotYMtx, 'y', panelState->m_transform.m_rotation.y);
			PSMTXConcat(rotXMtx, rotYMtx, rotXMtx);
			rotXMtx[0][3] = panelState->m_transform.m_position.x;
			rotXMtx[1][3] = panelState->m_transform.m_position.y;
			rotXMtx[2][3] = panelState->m_transform.m_position.z;
			PSMTXConcat(rotXMtx, scaleMtx, scaleMtx);

			m_wm.m_handles[viewSlot]->m_model->SetMatrix(scaleMtx);
			m_wm.m_handles[viewSlot]->m_model->CalcMatrix();
			m_wm.m_handles[viewSlot]->m_model->CalcSkin();
		}
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 804b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::DrawMcObj()
{
	WmWorldObjInfo* view = &m_wm.m_worldObjData[17];
	int viewSlot = 17;
	for (int i = 0; i < 4; i++, viewSlot++, view++) {
		if (view->m_active != 0) {
			SetProjection(viewSlot);
			SetLight(0);
			m_wm.m_handles[viewSlot]->Draw(5);
			int partA = m_effectWork[i + 17].m_partNo;
			if (partA >= 0) {
				PartPcs.DrawMenuIdx(partA);
			}
			int partB = m_effectWork[i + 21].m_partNo;
			if (partB >= 0) {
				PartPcs.DrawMenuIdx(partB);
			}
		}
	}
	DrawInit();
	RestoreProjection();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 188b
 * EN Address: 0x8011A738
 * EN Size: 72b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::SetMcList(int index, McListInfo* info)
{
	m_wmCharaState[index] = *info;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 44b
 * EN Address: 0x8011A838
 * EN Size: 56b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::ClrMcList()
{
	memset(m_wmCharaState, 0, sizeof(McListInfo) * kMcListCount);
}

/*
 * --INFO--
 * PAL Address: 0x800eb088
 * PAL Size: 336b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::BindEffect(int slot, int effectNo, int cameraSlot)
{
	PPPCREATEPARAM createParam;
	CGObject* object;
	EffectInfo* effect;

	if (cameraSlot < 0) {
		cameraSlot = slot;
	}

	effect = &m_effectWork[slot];
	if (slot == 5 && effectNo < 0x13) {
		effect++;
	} else if (slot >= 0x11 && slot <= 0x14 && effectNo > 0x19) {
		effect += 4;
	}

	object = &effect->m_object;
	const bool group = (effect->m_effectNo = effectNo) > 100;
	effect->m_slotNo = slot;
	object->Create();
	object->m_charaModelHandle = m_wm.m_handles[cameraSlot];

	createParam.m_lookTargetPtr = object;
	createParam.m_bindObject = object;

	const unsigned int partId = PartMng.pppCreate(group, effectNo, &createParam, 1);
	effect->m_partNo = partId;
	return effect->m_partNo;
}

/*
 * --INFO--
 * PAL Address: 0x800eafa0
 * PAL Size: 232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetLight(int mode)
{
	Graphic.SetFog(1, 0);

	LightPcs.SetAmbient(s_Light[mode].m_ambient);
	LightPcs.SetNumDiffuse(static_cast<unsigned long>(s_Light[mode].m_diffuseCount));

	for (int i = 0; i < s_Light[mode].m_diffuseCount; i++) {
		LightPcs.SetDiffuse(
			static_cast<unsigned long>(i), s_Light[mode].m_diffuseColors[i],
			&s_Light[mode].m_diffuseDirs[i], 0);
	}

	LightPcs.SetPosition(static_cast<CLightPcs::TARGET>(0), 0, 0xFFFFFFFF);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 524b
 * EN Address: 0x8011AACC
 * EN Size: 680b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::DrawPageMark()
{
#ifdef VERSION_GCCJGC
	const int kPageMarkTexture = 42;
#else
	const int kPageMarkTexture = 43;
#endif
	const int phase = abs(static_cast<int>(System.m_frameCounter) % 20 - 10);
	const float scale = static_cast<float>(0.03 * phase + 0.7);
	float x = 220.0f;
	x -= 40.0;
	float y = 369.0f;
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXColor color;
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = static_cast<unsigned char>(static_cast<int>(
	    255.0f * static_cast<float>(0.05 * phase + 0.5)));
	GXSetChanMatColor(GX_COLOR0A0, color);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kPageMarkTexture));

	x = static_cast<float>((48.0f - 48.0f * scale) * 0.5 + x);
	y = static_cast<float>((40.0f - 40.0f * scale) * 0.5 + y);
	if ((m_pageMarkFlags & 2) != 0) {
		MenuPcs.DrawRect(8, x, y, 48.0f, 40.0f, 0.0f, 0.0f, scale, scale, 0.0f);
	}
	x += 248.0f;
	if ((m_pageMarkFlags & 1) != 0) {
		MenuPcs.DrawRect(0, x, y, 48.0f, 40.0f, 0.0f, 0.0f, scale, scale, 0.0f);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800ead94
 * PAL Size: 524b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawRect2(unsigned long flags, float x, float y, float w, float h, float tx, float ty, float scaleX, float scaleY, float (*mtx)[4])
{
	if (w <= 0.0f || h <= 0.0f) {
		return;
	}

#define halfTexel FLOAT_80331434
	float u0;
	float v0;
	float u1;
	float v1;

	if ((flags & 8) != 0) {
		u1 = tx + halfTexel;
		u0 = (tx + w) - halfTexel;
	} else {
		u1 = (tx + w) - halfTexel;
		u0 = tx + halfTexel;
	}

	if ((flags & 4) != 0) {
		v1 = ty + halfTexel;
		v0 = (v1 + h) - halfTexel;
	} else {
		v1 = (ty + h) - halfTexel;
		v0 = ty + halfTexel;
	}

	float wS = w * scaleX;
	float hS = h * scaleY;

	if ((flags & 1) != 0) {
		x = x - halfTexel * wS;
	}
	if ((flags & 2) != 0) {
		y = y - halfTexel * hS;
	}
#undef halfTexel

	Vec in[4];
	Vec out[4];

	in[0].x = x;
	in[0].y = y;
	in[0].z = 0.0f;

	in[1].x = x + wS;
	in[1].y = y;
	in[1].z = 0.0f;

	in[2].x = x;
	in[2].y = y + hS;
	in[2].z = 0.0f;

	in[3].x = x + wS;
	in[3].y = y + hS;
	in[3].z = 0.0f;

	PSMTXMultVecArray(reinterpret_cast<MtxPtr>(mtx), in, out, 4);

	GXBegin(static_cast<GXPrimitive>(0x98), static_cast<GXVtxFmt>(0), 4);

	float z = 0.0f;
	for (int i = 0; i < 4; i++) {
		GXPosition3f32(out[i].x, out[i].y, z);
		float uu;
		if ((i & 1) != 0) {
			uu = u1;
		} else {
			uu = u0;
		}
		float vv;
		if (i < 2) {
			vv = v0;
		} else {
			vv = v1;
		}
		GXTexCoord2f32(uu, vv);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800eab98
 * PAL Size: 508b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawRect3d(unsigned long flags, float x, float y, float z, float w, float h, float tx, float ty, float scaleX, float scaleY)
{
	if (w <= 0.0f || h <= 0.0f) {
		return;
	}

#define halfTexel FLOAT_80331434
	float u1;
	float v1;
	float u0;
	float v0;

	if ((flags & 8) != 0) {
		u1 = tx + halfTexel;
		u0 = (tx + w) - halfTexel;
	} else {
		u1 = (tx + w) - halfTexel;
		u0 = tx + halfTexel;
	}

	if ((flags & 4) != 0) {
		v1 = ty + halfTexel;
		v0 = (v1 + h) - halfTexel;
	} else {
		v1 = (ty + h) - halfTexel;
		v0 = ty + halfTexel;
	}

	float wS = w * scaleX;
	h = h * scaleY;
	if ((flags & 1) != 0) {
		x = x - halfTexel * wS;
	}
	if ((flags & 2) != 0) {
		y = y - halfTexel * h;
	}
#undef halfTexel

	Vec out[4];

	out[0].x = x;
	out[0].y = y;
	out[0].z = z;

	out[1].x = x + wS;
	out[1].y = y;
	out[1].z = z;

	out[2].x = x;
	out[2].y = y + h;
	out[2].z = z;

	out[3].x = x + wS;
	out[3].y = y + h;
	out[3].z = z;

	GXBegin(static_cast<GXPrimitive>(0x98), static_cast<GXVtxFmt>(0), 4);

	for (int i = 0; i < 4; i++) {
		GXPosition3f32(out[i].x, out[i].y, out[i].z);
		float uu;
		if ((i & 1) != 0) {
			uu = u1;
		} else {
			uu = u0;
		}
		float vv;
		if (i < 2) {
			vv = v0;
		} else {
			vv = v1;
		}
		GXTexCoord2f32(uu, vv);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800eaaec
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetMcWinInfo(int x, int y)
{
    float fy = FLOAT_80331430 - y;
    float fx = static_cast<float>(0x280 - x) / 2.0;
    m_menuWindowInfo->x = static_cast<short>(fx);
    m_menuWindowInfo->y = static_cast<short>(static_cast<float>(fy / 2.0));
    m_menuWindowInfo->width = static_cast<short>(x);
    m_menuWindowInfo->height = static_cast<short>(y);
    m_menuWindowInfo->frame = 0;
    m_menuWindowInfo->state = 3;
}

/*
 * --INFO--
 * PAL Address: 0x800EA4F4
 * PAL Size: 1528b
 * EN Address: 0x800E9BF8
 * EN Size: 1528b
 * JP Address: 0x800E75D4
 * JP Size: 1516b
 */
void CMenuPcs::DrawMcWin(short state, short kind)
{
	if (state >= 0 && m_menuWindowInfo->state != state) {
		m_menuWindowInfo->state = state;
	}

	if (m_menuWindowInfo->state == 3) {
		return;
	}

	const float centerX = static_cast<float>(m_menuWindowInfo->x) + static_cast<float>(m_menuWindowInfo->width / 2.0);
	const float centerY = static_cast<float>(m_menuWindowInfo->y) + static_cast<float>(m_menuWindowInfo->height / 2.0);

	float right;
	float sw;
	float sy;
	float sh;
	float sx;
	float bottom;
	if (m_menuWindowInfo->state != 1) {
		sx = centerX - FLOAT_80331410;
		sy = centerY - FLOAT_80331410;
		const float xAdd = (((centerX - static_cast<float>(m_menuWindowInfo->x)) - FLOAT_80331410) / static_cast<float>(kMcWindowFrames)) * static_cast<float>(m_menuWindowInfo->frame);
		const float yAdd = (((centerY - static_cast<float>(m_menuWindowInfo->y)) - FLOAT_80331410) / static_cast<float>(kMcWindowFrames)) * static_cast<float>(m_menuWindowInfo->frame);
		sx -= xAdd;
		sy -= yAdd;
		sw = static_cast<float>(DOUBLE_80331418 * static_cast<double>(FLOAT_80331410 + xAdd));
		sh = static_cast<float>(DOUBLE_80331418 * static_cast<double>(FLOAT_80331410 + yAdd));
	} else {
		sx = static_cast<float>(m_menuWindowInfo->x);
		sy = static_cast<float>(m_menuWindowInfo->y);
		sw = static_cast<float>(m_menuWindowInfo->width);
		sh = static_cast<float>(m_menuWindowInfo->height);
	}

	sx = static_cast<float>(static_cast<int>(static_cast<double>(sx) - DOUBLE_803313F8));
	sw = static_cast<float>(static_cast<int>(static_cast<double>(sw) - DOUBLE_80331420));
	sy = static_cast<float>(static_cast<int>(static_cast<double>(sy) - DOUBLE_803313F8));
	sh = static_cast<float>(static_cast<int>(static_cast<double>(sh) - DOUBLE_80331420));

	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXColor color;
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = 0xFF;
	GXSetChanMatColor(static_cast<GXChannelID>(4), color);

	int rectIdx;
	unsigned long flags;

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((kind != 0) ? kAltWindowTextureBase : kMcWindowTextureBase));
	right = (sx + sw) - FLOAT_80331410;
	bottom = (sy + sh) - FLOAT_80331410;
	const float* pZw1 = &FLOAT_803313dc;
	const float uv0 = *pZw1;
	for (rectIdx = 0; rectIdx < 4; rectIdx++) {
		float x;
		float y;
		flags = 0;
		if (rectIdx & 1) {
			x = right;
			flags |= 8;
		} else {
			x = sx;
		}
		if (rectIdx & 2) {
			y = bottom;
			flags |= 4;
		} else {
			y = sy;
		}
		MenuPcs.DrawRect(flags, x, y, FLOAT_80331410, FLOAT_80331410, uv0, uv0, FLOAT_803313e8, FLOAT_803313e8, uv0);
	}

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((kind != 0) ? kAltWindowTextureBase + 2 : kMcWindowTextureBase + 1));
	const double innerWidthD = static_cast<double>(sw) - DOUBLE_80331428;
	const float innerX = FLOAT_80331410 + sx;
	const float innerWidthF = static_cast<float>(innerWidthD);
	float y = sy;
	for (rectIdx = 0; rectIdx < 2; rectIdx++) {
		flags = 0;
		if (rectIdx != 0) {
			y = bottom;
			flags |= 4;
		}
		MenuPcs.DrawRect(flags, innerX, y, innerWidthF, FLOAT_80331410, FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
	}

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((kind != 0) ? kAltWindowTextureBase + 1 : kMcWindowTextureBase + 2));
	const double innerHeightD = static_cast<double>(sh) - DOUBLE_80331428;
	const float innerY = FLOAT_80331410 + sy;
	const float innerHeightF = static_cast<float>(innerHeightD);
	float x = sx;
	for (rectIdx = 0; rectIdx < 2; rectIdx++) {
		flags = 0;
		if (rectIdx != 0) {
			x = right;
			flags |= 8;
		}
		MenuPcs.DrawRect(flags, x, innerY, FLOAT_80331410, innerHeightF, FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
	}

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((kind != 0) ? kAltWindowTextureBase + 3 : kMcWindowTextureBase + 3));
	MenuPcs.DrawRect(flags, innerX, innerY, static_cast<float>(innerWidthD), static_cast<float>(innerHeightD), FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);

	if (m_menuWindowInfo->state == 0) {
		m_menuWindowInfo->frame++;
		if (m_menuWindowInfo->frame >= kMcWindowFrames) {
			m_menuWindowInfo->frame = kMcWindowFrames;
			m_menuWindowInfo->state = 1;
		}
	} else if (m_menuWindowInfo->state == 1) {
		if (m_menuWindowInfo->frame != kMcWindowFrames) {
			m_menuWindowInfo->frame = kMcWindowFrames;
		}
	} else if (m_menuWindowInfo->state == 2) {
		m_menuWindowInfo->frame--;
		if (m_menuWindowInfo->frame <= 0) {
			m_menuWindowInfo->frame = 0;
			m_menuWindowInfo->state = 3;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800EA150
 * PAL Size: 932b
 * EN Address: 0x800E9854
 * EN Size: 932b
 * JP Address: 0x800E7288
 * JP Size: 844b
 */
void CMenuPcs::DrawMcWinMess(int winType, int messType)
{
	CFont* font;
	const char* const* msgTable;
	int maxWidth;
	int i;
	const WinMessEntry* winMess;
#ifdef VERSION_GCCJGC
	int msgId;
#endif
#ifndef VERSION_GCCJGC
	static const char* s_SlotStr[] = {"Slot A", "Steckplatz A", "Slot A", "Slot A", "Ranura A"};
	static const char* s_DataStr[] = {"Data 1", "Datenblock 1", "Salvataggio 1", "sauvegarde 1", "Archivo 1"};
#endif

	font = GetFont22();

	float one = FLOAT_803313e8;
	font->SetMargin(one);
	font->SetShadow(0);
	font->SetScale(one);
	font->DrawInit();

	font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
	font->SetTlut(0x23);

	msgTable = GetMcWinMessBuff(messType);
#ifndef VERSION_GCCJGC
	const int languageIndex = Game.m_gameWork.GetLanguage() - 1;
	winMess = GetWinMess(winType);

	float lineHeight;
#endif
	float posX;
	if (winType != 0) {
#ifdef VERSION_GCCJGC
		winMess = GetWinMess(winType);
#endif
		maxWidth = 0;
#ifdef VERSION_GCCJGC
		for (i = 0; i < winMess->m_lineCount; i++) {
#else
		for (i = 0; i < winMess->m_lineCount; i++) {
#endif
			const short msgId = winMess->m_messageIds[i];
			const char* text = msgTable[msgId];
#ifndef VERSION_GCCJGC
			if (text != 0) {
				if (text[0] == '$') {
					text++;
				}
#endif
				const int width = font->GetWidth(const_cast<char*>(text));
				if (width > maxWidth) {
					maxWidth = width;
				}
#ifndef VERSION_GCCJGC
			}
#endif
		}
		posX = static_cast<float>((m_menuWindowInfo->width - maxWidth) / 2.0 + m_menuWindowInfo->x);
	}

	float y = static_cast<float>(m_menuWindowInfo->y + 0x20);
#ifdef VERSION_GCCJGC
	winMess = GetWinMess(winType);
#else
	lineHeight = FLOAT_80331404;
#endif

	char textBuf[128];
#ifdef VERSION_GCCJGC
	for (i = 0; i < winMess->m_lineCount; i++) {
#else
	for (i = 0; i < winMess->m_lineCount; i++) {
#endif
#ifdef VERSION_GCCJGC
		msgId = winMess->m_messageIds[i];
#else
		const short msgId = winMess->m_messageIds[i];
#endif
#ifndef VERSION_GCCJGC
		int isDollar = 0;
#endif
		if ((int)strlen(msgTable[msgId]) != 0) {
#ifdef VERSION_GCCJGC
			strcpy(textBuf, msgTable[msgId]);
			if (winType == 0 || msgId == 11) {
#else
			if (msgTable[msgId][0] == '$') {
				strcpy(textBuf, msgTable[msgId] + 1);
				isDollar = 1;
			} else {
				strcpy(textBuf, msgTable[msgId]);
			}

			if (winType == 0 || isDollar != 0) {
#endif
				const int textWidth = font->GetWidth(textBuf);
				posX = static_cast<float>((m_menuWindowInfo->width - textWidth) / 2.0 + m_menuWindowInfo->x);
			}
			font->SetPosX(posX);
			font->SetPosY(y);
#ifdef VERSION_GCCJGC
			if (messType == 0) {
				if (msgId == 3 || msgId == 5 || msgId == 7 || msgId == 15 ||
				    msgId == 19 || msgId == 22 || msgId == 32) {
					textBuf[9] += GetMcCtrl()->m_cardChannel;
				} else if (msgId == 27) {
					textBuf[1] += 2;
					textBuf[3] += 2;
				}
			} else if (memcmp(textBuf, "\x83\x66\x81\x5B\x83\x5E\x82\x50", 8) == 0) {
				textBuf[7] += GetMcCtrl()->m_saveIndex;
			}
#else
			if (messType == 0) {
				char* slotText;
				if (winType != 0 && (slotText = strstr(textBuf, s_SlotStr[languageIndex])) != 0) {
					int len = strlen(s_SlotStr[languageIndex]);
					slotText[len - 1] += GetMcCtrl()->m_cardChannel;
				} else {
					char* marker = strstr(textBuf, lbl_80331400);
					if (marker != 0) {
						marker[0] += 2;
						marker[1] += 2;
					}
				}
			} else {
				char* dataText = strstr(textBuf, s_DataStr[languageIndex]);
				if (dataText != 0) {
					int len = strlen(s_DataStr[languageIndex]);
					dataText[len - 1] += GetMcCtrl()->m_saveIndex;
				}
			}
#endif
			font->Draw(textBuf);
		}
#ifdef VERSION_GCCJGC
		y += 22.0f;
#else
		y += lineHeight;
#endif
	}

	DrawInit();
}

/*
 * --INFO--
 * PAL Address: 0x800EA014
 * PAL Size: 316b
 * EN Address: 0x800E9718
 * EN Size: 316b
 * JP Address: 0x800E7160
 * JP Size: 296b
 */
void CMenuPcs::GetWinSize(int winType, short* w, short* h, int messType)
{
	CFont* font;
	const char* const* msgTable;
	int maxWidth;
	const WinMessEntry* winMess;

	font = GetFont22();
	font->SetMargin(FLOAT_803313e8);
	font->SetShadow(0);
	font->SetScale(FLOAT_803313e8);

	msgTable = GetMcWinMessBuff(messType);
	maxWidth = 0;
	winMess = GetWinMess(winType);

	for (int i = 0; i < winMess->m_lineCount; i++) {
		const short msgId = winMess->m_messageIds[i];
		const char* text = msgTable[msgId];
#ifndef VERSION_GCCJGC
		if (text != 0) {
			if (text[0] == '$') {
				text++;
			}
#endif
			const int textWidth = font->GetWidth(text);
			if (textWidth > maxWidth) {
				maxWidth = textWidth;
			}
#ifndef VERSION_GCCJGC
		}
#endif
	}

	int cols = maxWidth / 0x16;
	if ((maxWidth % 0x16) != 0) {
		cols++;
	}

	*w = static_cast<short>((cols + 2) * 0x16 + 0x40);
#ifdef VERSION_GCCJGC
	*h = static_cast<short>(winMess->m_lineCount * 0x16 + 0x40);
#else
	*h = static_cast<short>(winMess->m_lineCount * 0x1E + 0x40);
#endif
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 204b
 * EN Address: 0x8011C2E8
 * EN Size: 316b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::SetTextureLoc(int materialId)
{
	CMaterial* material = MapMng.GetMaterialID(materialId);
	CTexture* texture = material->GetTexture(0);
	TextureMan.SetTexture(GX_TEXMAP0, texture);

	Mtx texMtx;
	PSMTXScale(texMtx, 1.0f / texture->m_width, 1.0f / texture->m_height, 1.0f);
	GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);
	GXSetNumTexGens(1);
	GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0);
	TextureMan.SetTextureTev(texture);
}

/*
 * --INFO--
 * PAL Address: 0x800ea00c
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
float CMenuPcs::GetMaxAnimWait()
{
	return s_MaxAnimWait;
}

/*
 * --INFO--
 * PAL Address: 0x800E9C8C
 * PAL Size: 896b
 * EN Address: 0x800E9390
 * EN Size: 896b
 * JP Address: 0x800E6DE8
 * JP Size: 880b
 */
void CMenuPcs::BindMcObj()
{
	int i;

	for (i = 0; i < 4; i++) {
		EffectInfo* const effectA = &m_effectWork[i + 0x11];
		if (effectA->m_partNo >= 0) {
			PartMng.pppDeletePart(effectA->m_partNo);
			effectA->m_partNo = -1;
			effectA->m_slotNo = -1;
			effectA->m_effectNo = -1;
		}

		EffectInfo* const effectB = effectA + 4;
		if (effectB->m_partNo >= 0) {
			PartMng.pppDeletePart(effectB->m_partNo);
			effectB->m_partNo = -1;
			effectB->m_slotNo = -1;
			effectB->m_effectNo = -1;
		}
	}

	for (i = 0; i < 4; i++) {
		int modelNo;
		const McListInfo& charaState = m_wmCharaState[i];
		modelNo = charaState.m_timerA;

		if (modelNo != 0) {
			BindEffect(i + 0x11, modelNo + 0x16, -1);
		}

		const unsigned int flags = charaState.m_chaliceElement;
		if ((flags & 1) != 0) {
			modelNo = 0;
		} else if ((flags & 2) != 0) {
			modelNo = 1;
		} else if ((flags & 4) != 0) {
			modelNo = 2;
		} else if ((flags & 8) != 0) {
			modelNo = 3;
		} else if ((flags & 0x10) != 0) {
			modelNo = 4;
		}

		BindEffect(i + 0x11, modelNo + 0x1A, -1);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800e9ba0
 * PAL Size: 236b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawFilter(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	SetAttrFmt(static_cast<CMenuPcs::FMT>(2));

	GXColor color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	GXSetChanMatColor(static_cast<GXChannelID>(4), color);

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(-1));
	AlphaNormal();

	GXBegin(GX_QUADS, GX_VTXFMT0, 4);
	float tall = 448.0f;
	float wide = 640.0f;
	float zero = 0.0f;
	GXPosition3f32(zero, zero, zero);
	GXPosition3f32(wide, zero, zero);
	GXPosition3f32(wide, tall, zero);
	GXPosition3f32(zero, tall, zero);
}

/*
 * --INFO--
 * PAL Address: 0x800e9b2c
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CopyNowCaravanDat(Mc::SaveDat* outSave)
{
	MemoryCardMan.CreateMcBuff();
	MemoryCardMan.MakeSaveData();
	MemoryCardMan.DecodeData();
	memcpy(outSave, MemoryCardMan.GetMcBuffer(), 0x8BD0);
	MemoryCardMan.DestroyMcBuff();
}

/*
 * --INFO--
 * PAL Address: 0x800e9aac
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetCaravanWork(Mc::SaveDat* saveDat)
{
	MemoryCardMan.CreateMcBuff();
	memcpy(MemoryCardMan.GetMcBuffer(), saveDat, 0x8BD0);
	Game.LoadInit();
	MemoryCardMan.SetLoadData();
	Game.LoadFinished();
	MemoryCardMan.DestroyMcBuff();
}

/*
 * --INFO--
 * PAL Address: 0x800e9904
 * PAL Size: 424b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::GetSameCharaData(Mc::SaveDat* source, Mc::SaveDat* target, int memberIndex, int strictMode)
{
	if (strictMode == 0) {
		if (source->m_mcSerial != target->m_characters[memberIndex].m_originSerial ||
		    source->m_mcRandom != target->m_characters[memberIndex].m_originRandom) {
			return -2;
		}
	}

	int result;
	for (result = 0; result < 8; result++) {
		const Mc::CharaDat& character = source->m_characters[result];
		if (character.m_exists != 0) {
			if (strictMode == 0) {
				if (character.m_isAway != 0 &&
				    character.m_characterId == target->m_characters[memberIndex].m_characterId) {
					break;
				}
			} else if (character.m_isGuest != 0 &&
			           character.m_characterId == target->m_characters[memberIndex].m_characterId) {
				if (character.m_originSerial == target->m_mcSerial &&
				    character.m_originRandom == target->m_mcRandom) {
					break;
				}
			}
		}
	}

	if (strictMode == 0) {
		if (result < 8) {
			return result;
		}
		return -1;
	}

	return result < 8 ? -3 : -4;
}

/*
 * --INFO--
 * PAL Address: 0x800e98c4
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::CheckSameMcFormatID(Mc::SaveDat* lhs, Mc::SaveDat* rhs)
{
	if (lhs->m_mcSerial == rhs->m_mcSerial && lhs->m_mcRandom == rhs->m_mcRandom) {
		return 1;
	}
	return 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 520b
 * EN Address: 0x8011CA28
 * EN Size: 340b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::IsAsyncCharaLoadFinish()
{
	int i;
	int loadedCount;
	int validCount;
	validCount = 0;
	if (m_cmakeWorkActive == 1) {
		for (i = 0; i < kWmMenuPlayerCount; i++) {
			if (m_cmakeWork->m_characters[i].m_exists != 0) {
				validCount++;
			}
		}
	} else {
		for (i = 0; i < kWmMenuPlayerCount; i++) {
			if (Game.m_caravanWorkArr[i].m_shopState != 0) {
				validCount++;
			}
		}
	}

	loadedCount = 0;
	for (i = 0; i < kWmMenuPlayerCount; i++) {
		const int handleIdx = i + 0x20;
		CCharaPcs::CHandle* const handle = m_wm.m_handles[handleIdx];
		if (handle->m_charaKind != 3 && handle->IsLoadModelASyncCompleted() != 0) {
			loadedCount++;
		}
	}

	return loadedCount == validCount;
}

/*
 * --INFO--
 * PAL Address: 0x800E9348
 * PAL Size: 1404b
 * EN Address: 0x800E8A60
 * EN Size: 1384b
 * JP Address: 0x800E64C4
 * JP Size: 1336b
 */
int McCtrl::LoadMcList()
{
	if (m_state < 0) {
		return -1;
	}

	m_previousState = m_state;

	switch (m_state) {
	case 0:
		MenuPcs.ClrMcList();
		MemoryCardMan.McMount(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 1;
		m_iteration = 0;
		break;

	case 1:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
#if defined(VERSION_GCCP01)
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
#endif
				if (m_lastResult == -6) {
					m_state = 2;
				} else if (m_lastResult == -0x0D) {
					m_state = -1;
					return -2;
				}
				if (m_lastResult == -5) {
					m_state = -1;
					return -4;
				}
				m_state = -1;
			} else {
				m_state = 4;
			}
		}
		break;

	case 2:
		MemoryCardMan.McCheck(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 3;
		break;

	case 3:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult != 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = -1;
				return (m_lastResult == -5) ? -4 : -3;
			}
			m_state = 4;
		}
		break;

	case 4:
		m_lastResult = MemoryCardMan.McOpen(m_cardChannel);
		if (m_lastResult < 0) {
			if (m_lastResult == -4) {
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = 7;
				if (m_lastResult == -5) {
					return -4;
				}
			} else {
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = -1;
			}
		} else if (MemoryCardMan.IsBrokenFile()) {
			const int closeResult = MemoryCardMan.McClose();
#if !defined(VERSION_GCCJGC)
			if (closeResult != 0) {
				m_lastResult = closeResult;
				m_state = -1;
			} else
#endif
			{
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				SetBrokenFile(1);
				m_state = 7;
			}
		} else {
			m_state = 5;
		}
		break;

	case 5: {
		unsigned long long serial;
		if (CARDGetSerialNo(m_cardChannel, &serial) == 0) {
			m_serial = serial;
		} else {
			MemoryCardMan.McClose();
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			m_state = -1;
			return -1;
		}
		MemoryCardMan.CreateMcBuff();
		MemoryCardMan.McRead(0, 0xA000, m_iteration * 0xA000 + 0x4000);
		m_state = 6;
		break;
	}

	case 6:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.McClose();
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = -1;
				if (m_lastResult == -5) {
					return -4;
				}
			} else {
				MemoryCardMan.DecodeData();
				const int iteration = m_iteration;
				m_iteration = iteration + 1;
				SetListDat(iteration, 0);
				if (m_iteration < 4) {
					m_state = 5;
				} else {
					const int closeResult = MemoryCardMan.McClose();
#if !defined(VERSION_GCCJGC)
					if (closeResult != 0) {
						m_lastResult = closeResult;
						m_state = -1;
					} else
#endif
					{
						MemoryCardMan.McUnmount(m_cardChannel);
						MemoryCardMan.DestroyMcBuff();
						m_state = 7;
					}
				}
			}
		}
		break;

	case 7:
		break;
	}

	int result;
	if (m_state == -1) {
		result = -1;
	} else if (m_state == 7) {
		result = 1;
	} else {
		result = 0;
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: 0x800E902C
 * PAL Size: 796b
 * EN Address: 0x800E8744
 * EN Size: 796b
 * JP Address: 0x800E6198
 * JP Size: 812b
 */
void McCtrl::SetListDat(int slot, int clearScriptSysVal0)
{
	McListInfo entry;
	Mc::SaveDat* const save = reinterpret_cast<Mc::SaveDat*>(MemoryCardMan.GetMcBuffer());
	memset(&entry, 0, sizeof(entry));

	if (save->m_townName[0] != 0) {
		const int formatMatch = memcmp(save->m_version, CardConst::MCDAT_VERSION, 4);
		const unsigned char crcOk = MemoryCardMan.ChkCrc(0);
		if (crcOk == 1 && formatMatch == 0) {
			if (clearScriptSysVal0 == 0) {
				entry.m_scriptSysVal0 = save->m_scriptSysVal0;
			} else {
				entry.m_scriptSysVal0 = 0;
			}
			memcpy(&entry.m_saveTime, &save->m_saveTime, sizeof(entry.m_saveTime));
			entry.m_timerA = save->m_timerA;
			entry.m_scriptGlobalTime = save->m_scriptGlobalTime;
			entry.m_frameCounter = save->m_frameCounter;

			ChkParty(reinterpret_cast<char*>(save));

			for (int i = 0; i < 4; i++) {
				if (save->m_partySlots[i] >= 0) {
					entry.m_characterIds[i] = save->m_characters[save->m_partySlots[i]].m_id;
				} else {
					entry.m_characterIds[i] = -1;
				}
			}
			entry.m_chaliceElement = save->m_chaliceElement;
			memcpy(entry.m_townName, save->m_townName, sizeof(save->m_townName));
#if defined(VERSION_GCCJGC)
			strcat(entry.m_townName, "\x82\xCC\x91\xBA");
#endif
			entry.m_hasData = 1;
		} else {
			entry.m_isBroken = 1;
		}
	} else {
		entry.m_isBroken = 0;
		entry.m_hasData = 0;
	}

	MenuPcs.SetMcList(slot, &entry);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 232b
 * EN Address: 0x8011D25C
 * EN Size: 108b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void McCtrl::SetBrokenFile(int isBroken)
{
	McListInfo entry;
	memset(&entry, 0, sizeof(entry));
	entry.m_isBroken = isBroken;
	for (int i = 0; i < kMcListCount; i++) {
		MenuPcs.SetMcList(i, &entry);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800E8738
 * PAL Size: 2292b
 * EN Address: 0x800E7E5C
 * EN Size: 2280b
 * JP Address: 0x800E58C8
 * JP Size: 2256b
 */
int McCtrl::SaveDat()
{
	if (m_state < 0) {
		return -1;
	}

	m_previousState = m_state;

	switch (m_state) {
	case 0:
		MemoryCardMan.McMount(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 1;
		m_iteration = 0;
		break;

	case 1:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
#if defined(VERSION_GCCP01)
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
#endif
				if (m_lastResult == -6) {
					m_state = 2;
				} else if (m_lastResult == -0x0D) {
					m_state = -1;
					return -2;
				} else if (m_lastResult == -5) {
					m_state = -1;
					return -4;
				} else {
					m_state = -1;
				}
			} else {
				m_state = 7;
			}
		}
		break;

	case 2:
		MemoryCardMan.McCheck(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 3;
		break;

	case 3:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult != 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				m_state = -1;
				if (m_lastResult == -5) {
					return -4;
				}
				return -3;
			}
			m_state = 7;
		}
		break;

	case 7:
		m_lastResult = MemoryCardMan.McOpen(m_cardChannel);
		if (m_lastResult == -4) {
			m_state = 10;
		} else if (m_lastResult == -5) {
			m_state = -1;
			MemoryCardMan.McUnmount(m_cardChannel);
			return -4;
		} else if (MemoryCardMan.IsBrokenFile()) {
			m_state = 8;
		} else {
			MemoryCardMan.CreateMcBuff();
			m_state = 0x0C;
		}
		break;

	case 8:
		MemoryCardMan.McDelFile(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 9;
		break;

	case 9:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				if (m_lastResult == -6) {
					m_state = 2;
				} else if (m_lastResult == -0x0D) {
					m_state = -1;
					return -2;
				} else if (m_lastResult == -5) {
					m_state = -1;
					return -4;
				} else {
					m_state = -1;
				}
			} else {
				SetBrokenFile(0);
				m_state = 10;
			}
		}
		break;

	case 10:
		m_createFlag = 1;
		MemoryCardMan.McCreate(m_cardChannel);
		m_state = 0x0B;
		break;

	case 0x0B:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				m_state = -1;
				if (m_lastResult == -5) {
					return -4;
				}
			} else {
				m_state = 0x10;
			}
		}
		break;

	case 0x0C:
		m_lastResult = MemoryCardMan.McGetStat(m_cardChannel);
		if (m_lastResult != 0) {
			MemoryCardMan.McUnmount(m_cardChannel);
			m_state = -1;
			if (m_lastResult == -5) {
				return -4;
			}
		} else {
			m_state = 0x0D;
		}
		break;

	case 0x0D:
		MemoryCardMan.CreateMcBuff();
		MemoryCardMan.SetMcIconImage();
		MemoryCardMan.McWrite(0, 0x4000, 0);
		m_state = 0x0E;
		break;

	case 0x0E:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = -1;
				if (m_lastResult == -5) {
					return -4;
				}
			} else {
				m_state = 0x0F;
			}
		}
		break;

	case 0x0F:
		m_lastResult = MemoryCardMan.McSetStat(m_cardChannel);
		if (m_lastResult != 0) {
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			m_state = -1;
			if (m_lastResult == -5) {
				return -4;
			}
		} else {
			m_state = 0x12;
		}
		break;

	case 0x10:
		MemoryCardMan.CreateMcBuff();
		MemoryCardMan.McWrite(0, 0xA000, m_iteration * 0xA000 + 0x4000);
		m_state = 0x11;
		break;

	case 0x11:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_iteration = m_iteration + 1;
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.McClose();
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = -1;
				if (m_lastResult == -5) {
					return -4;
				}
			} else if (m_iteration < 4) {
				m_state = 0x10;
			} else {
				m_state = 0x0C;
			}
		}
		break;

	case 0x12: {
		unsigned long long serial;
		if (CARDGetSerialNo(m_cardChannel, &serial) == 0) {
			if (static_cast<signed char>(Game.m_gameWork.m_mcHasSerial) == 0) {
				Game.m_gameWork.m_mcSerial = serial;
				Game.m_gameWork.m_mcRandom = Math.Rand(0x7FFFFFFF);
				Game.m_gameWork.m_mcHasSerial = 1;
			} else {
				m_serial = serial;
			}
		} else {
			MemoryCardMan.McClose();
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			m_state = -1;
			return -1;
		}
		MemoryCardMan.CreateMcBuff();
		if (m_userBuffer != 0) {
			memcpy(MemoryCardMan.GetMcBuffer(), m_userBuffer, 0x8BD0);
		} else {
			MemoryCardMan.MakeSaveData();
		}
		MemoryCardMan.McWrite(0, 0xA000, m_saveIndex * 0xA000 + 0x4000);
		m_state = 0x13;
		break;
	}

	case 0x13:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				m_state = -1;
				if (m_lastResult == -5) {
					MemoryCardMan.McClose();
					MemoryCardMan.McUnmount(m_cardChannel);
					MemoryCardMan.DestroyMcBuff();
					return -4;
				}
			} else {
				MemoryCardMan.DecodeData();
				SetListDat(m_saveIndex, 1);
				MenuPcs.BindMcObj(m_saveIndex);
				m_state = 0x14;
			}

			const int closeResult = MemoryCardMan.McClose();
#if !defined(VERSION_GCCJGC)
			if (closeResult != 0) {
				m_lastResult = closeResult;
				m_state = -1;
			} else
#endif
			{
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
			}
		}
		break;

	case 0x14:
		break;
	}

	int result;
	if (m_state == -1) {
		result = -1;
	} else if (m_state == 0x14) {
		result = 1;
	} else {
		result = 0;
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: 0x800e8300
 * PAL Size: 1080b
 * EN Address: 0x800E7A30
 * EN Size: 1068b
 * JP Address: 0x800E54AC
 * JP Size: 1052b
 */
int McCtrl::LoadDat()
{
	if (m_state < 0) {
		return -1;
	}

	m_previousState = m_state;

	switch (m_state) {
	case 0:
		MemoryCardMan.McMount(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 1;
		m_iteration = 0;
		break;

	case 1:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
#if defined(VERSION_GCCP01)
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
#endif
				if (m_lastResult == -6) {
					m_state = 2;
				} else if (m_lastResult == -0x0D) {
					m_state = -1;
					return -2;
				} else if (m_lastResult == -5) {
					m_state = -1;
					return -4;
				} else {
					m_state = -1;
				}
			} else {
				m_state = 4;
			}
		}
		break;

	case 2:
		MemoryCardMan.McCheck(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 3;
		break;

	case 3:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult != 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = 7;
				if (m_lastResult == -5) {
					return -4;
				}
				return -3;
			}
			m_state = 4;
		}
		break;

	case 4:
		m_lastResult = MemoryCardMan.McOpen(m_cardChannel);
		if (m_lastResult < 0) {
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			if (m_lastResult == -4) {
				m_state = 7;
			} else if (m_lastResult == -5) {
				m_state = -1;
				return -4;
			} else {
				m_state = -1;
			}
		} else {
			m_state = 5;
		}
		break;

	case 5: {
		unsigned long long serial;
		if (CARDGetSerialNo(m_cardChannel, &serial) == 0) {
			m_serial = serial;
		} else {
			MemoryCardMan.McClose();
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			m_state = -1;
			return -1;
		}

		MemoryCardMan.CreateMcBuff();
		MemoryCardMan.McRead(0, 0xA000, m_saveIndex * 0xA000 + 0x4000);
		m_state = 6;
		break;
	}

	case 6:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.McClose();
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = -1;
				if (m_lastResult == -5) {
					return -4;
				}
			} else {
				MemoryCardMan.DecodeData();
				MemoryCardMan.McClose();
				MemoryCardMan.McUnmount(m_cardChannel);
				if (!(m_userBuffer == 0)) {
					memcpy(m_userBuffer, MemoryCardMan.GetMcBuffer(), 0x8BD0);
#if !defined(VERSION_GCCJGC)
					MemoryCardMan.CalcSaveDatHpMax(reinterpret_cast<Mc::SaveDat*>(m_userBuffer));
#endif
				} else {
					Game.LoadInit();
					MemoryCardMan.SetLoadData();
					Game.LoadFinished();
				}
				MemoryCardMan.DestroyMcBuff();
				m_state = 7;
			}
		}
		break;

	case 7:
		break;
	}

	int result;
	if (m_state == -1) {
		result = -1;
	} else if (m_state == 7) {
		result = 1;
	} else {
		result = 0;
	}

	return result;
}

/*
 * --INFO--
 * PAL Address: 0x800E80F0
 * PAL Size: 528b
 * EN Address: 0x800E7848
 * EN Size: 488b
 * JP Address: 0x800E52C4
 * JP Size: 488b
 */
int McCtrl::Format(int unmountAfter)
{
	if (m_state < 0) {
		return -1;
	}

	m_previousState = m_state;

	switch (m_state) {
	case 0:
		MemoryCardMan.McMount(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 1;
		m_iteration = 0;
		break;
	case 1:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult == -6 || m_lastResult == -0xD || m_lastResult == 0) {
				m_state = 2;
			} else {
				if (m_lastResult == -5) {
#if defined(VERSION_GCCP01)
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
#endif
					m_state = -1;
					return -2;
				}
#if defined(VERSION_GCCP01)
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
#endif
				m_state = -1;
			}
		}
		break;
	case 2:
		MemoryCardMan.McFormat(m_cardChannel);
		m_state = 3;
		break;
	case 3:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				m_state = -1;
				if (m_lastResult == -5) {
					return -2;
				}
			} else {
				if (unmountAfter != 0) {
					MemoryCardMan.McUnmount(m_cardChannel);
				}
				m_state = 4;
			}
		}
		break;
	case 4:
		break;
	}

	int result;
	if (m_state == -1) {
		result = -1;
	} else if (m_state == 4) {
		result = 1;
	} else {
		result = 0;
	}

	return result;
}

/*
 * --INFO--
 * PAL Address: 0x800E7DC8
 * PAL Size: 808b
 * EN Address: 0x800E7570
 * EN Size: 728b
 * JP Address: 0x800E4FEC
 * JP Size: 728b
 */
int McCtrl::ChkEmpty(int requireFile)
{
	int filesFree;
	int bytesFree[3];

	if (m_state < 0)
	{
		return -1;
	}

	m_previousState = m_state;

	int state = m_state;

	switch (state)
	{
	case 0:
		MemoryCardMan.McMount(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 1;
		m_iteration = 0;
		break;
	case 1:
		if (MemoryCardMan.AsyncFinished() == 1)
		{
			m_lastResult = MemoryCardMan.GetResult();

			if (m_lastResult == 0)
			{
				m_state = 2;
			}
			else
			{
				if (m_lastResult == -0x0D)
				{
#if defined(VERSION_GCCP01)
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
#endif
					m_state = -1;
					return -3;
				}

				if (m_lastResult == -6)
				{
#if defined(VERSION_GCCP01)
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
#endif
					m_state = -1;
					return -4;
				}

				if (m_lastResult == -5)
				{
#if defined(VERSION_GCCP01)
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
#endif
					m_state = -1;
					return -5;
				}

#if defined(VERSION_GCCP01)
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = 0xFF;
#endif
				m_state = -1;
			}
		}
		break;
	case 2:
	{
		m_lastResult = MemoryCardMan.McOpen(m_cardChannel);

		if (m_lastResult < 0)
		{
			if (m_lastResult == -4)
			{
				if (requireFile == 0)
				{
					m_state = 3;
				}
				else
				{
					MemoryCardMan.McUnmount(m_cardChannel);
					m_state = -1;
					return -6;
				}
			}
			else
			{
				if (m_lastResult == -5)
				{
					MemoryCardMan.McUnmount(m_cardChannel);
					m_state = -1;
					return -5;
				}

				MemoryCardMan.McUnmount(m_cardChannel);
				m_state = -1;
			}
		}
		else
		{
			MemoryCardMan.McClose();
			MemoryCardMan.McUnmount(m_cardChannel);
			m_state = 4;
		}
		break;
	}
	case 3:
		{
			m_lastResult = MemoryCardMan.McFreeBlocks(m_cardChannel, bytesFree, &filesFree);
			MemoryCardMan.McUnmount(m_cardChannel);

			if (m_lastResult < 0)
			{
				if (m_lastResult == -5)
				{
					m_state = -1;
					return -5;
				}

				m_state = -1;
			}
			else
			{
				if (filesFree == 0)
				{
					m_state = -1;
					return -2;
				}

				if (bytesFree[0] < 0x2C000)
				{
					m_state = -1;
					return -2;
				}

				m_state = 4;
			}
		}
		break;
	case 4:
		break;
	}

	int result;
	if (m_state == -1)
	{
		result = -1;
	}
	else if (m_state == 4)
	{
		result = 1;
	}
	else
	{
		result = 0;
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: 0x800e7d4c
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int McCtrl::ChkConnect(int chan)
{
	int result = MemoryCardMan.McChkConnect(chan);

	if (result == 0)
	{
		result = 1;
	}
	else if (result == -1)
	{
		result = -3;
	}
	else if (result == -2)
	{
		result = -6;
	}
	else if (result == -3)
	{
		result = -2;
	}
	else if (result == -4)
	{
		result = -5;
	}
	else
	{
		result = -1;
	}

	return result;
}

/*
 * --INFO--
 * PAL Address: 0x800E78F8
 * PAL Size: 1108b
 * EN Address: 0x800E70AC
 * EN Size: 1096b
 * JP Address: 0x800E4B40
 * JP Size: 1072b
 */
int McCtrl::ChkNowData()
{
	unsigned long long serial;

	if (m_state < 0)
	{
		return -999;
	}

	m_previousState = m_state;

	switch (m_state)
	{
	case 0:
		MemoryCardMan.McMount(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 1;
		m_iteration = 0;
		break;

	case 1:
		if (MemoryCardMan.AsyncFinished() == 1)
		{
			m_lastResult = MemoryCardMan.GetResult();
			int mountResult = m_lastResult;

			if (mountResult < 0)
			{
#if defined(VERSION_GCCP01)
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = 0xFF;
#endif

				if (mountResult == -6)
				{
					m_state = 2;
				}
				else
				{
					if (mountResult == -0x0D)
					{
						m_state = -1;
						return -0x0D;
					}

					if (mountResult == -5)
					{
						m_state = -1;
						return -5;
					}

					m_state = -1;
				}
			}
			else
			{
				m_state = 4;
			}
		}
		break;

	case 2:
		MemoryCardMan.McCheck(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 3;
		break;

	case 3:
		if (MemoryCardMan.AsyncFinished() == 1)
		{
			m_lastResult = MemoryCardMan.GetResult();

			if (m_lastResult != 0)
			{
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = 7;

				return m_lastResult == -5 ? -5 : -6;
			}

			m_state = 4;
		}
		break;

	case 4:
		m_lastResult = MemoryCardMan.McOpen(m_cardChannel);

		if (m_lastResult < 0)
		{
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();

			if (m_lastResult == -4)
			{
				m_state = -1;
				return -4;
			}

			if (m_lastResult == -5)
			{
				m_state = -1;
				return -5;
			}

			m_state = -1;
		}
		else
		{
			m_state = 5;
		}
		break;

	case 5:
		if (CARDGetSerialNo(m_cardChannel, &serial) == 0) {
			m_serial = serial;
		} else {
			MemoryCardMan.McClose();
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			m_state = -1;
			return -999;
		}

		MemoryCardMan.CreateMcBuff();
		MemoryCardMan.McRead(0, 0xA000, m_saveIndex * 0xA000 + 0x4000);
		m_state = 6;
		break;

	case 6:
		if (MemoryCardMan.AsyncFinished() == 1)
		{
			m_lastResult = MemoryCardMan.GetResult();

			if (m_lastResult < 0)
			{
				MemoryCardMan.McClose();
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = -1;

				if (m_lastResult == -5)
				{
					return -5;
				}
			}
			else
			{
				MemoryCardMan.DecodeData();

				int r = MemoryCardMan.McClose();
#if !defined(VERSION_GCCJGC)
				if (r != 0)
				{
					m_lastResult = r;
					m_state = -1;
				}
				else
#endif
				{
					MemoryCardMan.McUnmount(m_cardChannel);

					Mc::SaveDat* saveDat = reinterpret_cast<Mc::SaveDat*>(MemoryCardMan.GetMcBuffer());
					if (saveDat->m_mcSerial == Game.m_gameWork.m_mcSerial &&
					    saveDat->m_mcRandom == Game.m_gameWork.m_mcRandom)
					{
						r = 1;
					}
					else
					{
						r = -1000;
					}

					MemoryCardMan.DestroyMcBuff();
					m_state = 7;
					return r;
				}
			}
		}
		break;

	case 7:
		break;
	}

	int result;
	if (m_state == -1)
	{
		result = -999;
	}
	else if (m_state == 7)
	{
		result = 1;
	}
	else
	{
		result = 0;
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: 0x800E7430
 * PAL Size: 1224b
 * EN Address: 0x800E6BF0
 * EN Size: 1212b
 * JP Address: 0x800E469C
 * JP Size: 1188b
 */
int McCtrl::SaveDataBuffer(char* buffer)
{
	if (m_state < 0) {
		return -1000;
	}

	m_previousState = m_state;

	switch (m_state) {
	case 0:
		MemoryCardMan.McMount(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 1;
		m_iteration = 0;
		break;

	case 1:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
#if defined(VERSION_GCCP01)
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
#endif
				if (m_lastResult == -6) {
					m_state = 2;
				} else if (m_lastResult == -0xD) {
					m_state = -1;
					return -13;
				} else if (m_lastResult == -5) {
					m_state = -1;
					return -5;
				} else {
					m_state = -1;
				}
			} else {
				m_state = 7;
			}
		}
		break;

	case 2:
		MemoryCardMan.McCheck(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 3;
		break;

	case 3:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult != 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				m_state = -1;
				return (m_lastResult == -5) ? -5 : -6;
			}
			m_state = 7;
		}
		break;

	case 7:
		m_lastResult = MemoryCardMan.McOpen(m_cardChannel);
		if (m_lastResult == -4) {
			m_state = -1;
			MemoryCardMan.McUnmount(m_cardChannel);
			return -4;
		} else if (m_lastResult == -5) {
			m_state = -1;
			MemoryCardMan.McUnmount(m_cardChannel);
			return -5;
		} else {
			MemoryCardMan.CreateMcBuff();
			m_state = 0x10;
		}
		break;

	case 0x10: {
		unsigned long long serial;
		if (CARDGetSerialNo(m_cardChannel, &serial) == 0) {
			m_serial = serial;
		} else {
			MemoryCardMan.McClose();
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			m_state = -1;
			return -999;
		}

		Mc::SaveDat* const save = reinterpret_cast<Mc::SaveDat*>(MemoryCardMan.GetMcBuffer());
		memcpy(save, buffer, sizeof(*save));

		ChkParty(reinterpret_cast<char*>(save));
		MemoryCardMan.EncodeData();
		MemoryCardMan.McWrite(0, 0xA000, m_saveIndex * 0xA000 + 0x4000);
		m_state = 0x11;
		break;
	}

	case 0x11:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				m_state = -1;
				if (m_lastResult == -5) {
					MemoryCardMan.McClose();
					MemoryCardMan.McUnmount(m_cardChannel);
					MemoryCardMan.DestroyMcBuff();
					return -5;
				}
			} else {
				m_state = 0x12;
			}

			const int closeResult = MemoryCardMan.McClose();
#if !defined(VERSION_GCCJGC)
			if (!(closeResult == 0)) {
				m_lastResult = closeResult;
				m_state = -1;
			} else
#endif
			{
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
			}
		}
		break;

	case 0x12:
		break;
	}

	int result;
	if (m_state == -1) {
		result = -999;
	} else if (m_state == 0x12) {
		result = 1;
	} else {
		result = 0;
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 244b
 * EN Address: 0x8011F050
 * EN Size: 184b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void McCtrl::ChkParty(char* buffer)
{
	Mc::SaveDat* const save = reinterpret_cast<Mc::SaveDat*>(buffer);
	for (int i = 0; i < 4; i++) {
		const int partySlot = save->m_partySlots[i];
		if (save->m_characters[partySlot].m_exists == 0) {
			save->m_partySlots[i] = -1;
		}
		if (save->m_characters[partySlot].m_isAway != 0) {
			save->m_partySlots[i] = -1;
		}
	}
	save->m_crc = MemoryCardMan.CalcCrc(save);
}

/*
 * --INFO--
 * PAL Address: 0x800E6B98
 * PAL Size: 2200b
 * EN Address: 0x800E6364
 * EN Size: 2188b
 * JP Address: 0x800E3E28
 * JP Size: 2164b
 */
int McCtrl::EraseDat()
{
	if (m_state < 0) {
		return -1;
	}

	m_previousState = m_state;

	switch (m_state) {
	case 0:
		MemoryCardMan.McMount(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 1;
		m_iteration = 0;
		break;

	case 1:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
#if defined(VERSION_GCCP01)
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
#endif
				if (m_lastResult == -6) {
					m_state = 2;
				} else if (m_lastResult == -0x0D) {
					m_state = -1;
					return -2;
				} else if (m_lastResult == -5) {
					m_state = -1;
					return -4;
				} else {
					m_state = -1;
				}
			} else {
				m_state = 7;
			}
		}
		break;

	case 2:
		MemoryCardMan.McCheck(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 3;
		break;

	case 3:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult != 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				m_state = -1;
				if (m_lastResult == -5) {
					return -4;
				}
				return -3;
			}
			m_state = 7;
		}
		break;

	case 7:
		m_lastResult = MemoryCardMan.McOpen(m_cardChannel);
		if (m_lastResult == -4) {
			m_state = 10;
		} else if (m_lastResult == -5) {
			m_state = -1;
			MemoryCardMan.McUnmount(m_cardChannel);
			return -4;
		} else if (MemoryCardMan.IsBrokenFile()) {
			m_state = 8;
		} else {
			MemoryCardMan.CreateMcBuff();
			m_state = 0x0C;
		}
		break;

	case 8:
		MemoryCardMan.McDelFile(m_cardChannel);
		m_lastResult = MemoryCardMan.GetResult();
		m_state = 9;
		break;

	case 9:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				if (m_lastResult == -6) {
					m_state = 2;
				} else if (m_lastResult == -0x0D) {
					m_state = -1;
					return -2;
				} else if (m_lastResult == -5) {
					m_state = -1;
					return -4;
				} else {
					m_state = -1;
				}
			} else {
				SetBrokenFile(0);
				m_state = 10;
			}
		}
		break;

	case 10:
		m_createFlag = 1;
		MemoryCardMan.McCreate(m_cardChannel);
		m_state = 0x0B;
		break;

	case 0x0B:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				m_state = -1;
				if (m_lastResult == -5) {
					return -4;
				}
			} else {
				m_state = 0x10;
			}
		}
		break;

	case 0x0C:
		m_lastResult = MemoryCardMan.McGetStat(m_cardChannel);
		if (m_lastResult != 0) {
			MemoryCardMan.McUnmount(m_cardChannel);
			m_state = -1;
			if (m_lastResult == -5) {
				return -4;
			}
		} else {
			m_state = 0x0D;
		}
		break;

	case 0x0D:
		MemoryCardMan.CreateMcBuff();
		MemoryCardMan.SetMcIconImage();
		MemoryCardMan.McWrite(0, 0x4000, 0);
		m_state = 0x0E;
		break;

	case 0x0E:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = -1;
				if (m_lastResult == -5) {
					return -4;
				}
			} else {
				m_state = 0x0F;
			}
		}
		break;

	case 0x0F:
		m_lastResult = MemoryCardMan.McSetStat(m_cardChannel);
		if (m_lastResult != 0) {
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			m_state = -1;
			if (m_lastResult == -5) {
				return -4;
			}
		} else {
			m_state = 0x12;
		}
		break;

	case 0x10:
		MemoryCardMan.CreateMcBuff();
		MemoryCardMan.McWrite(0, 0xA000, m_iteration * 0xA000 + 0x4000);
		m_state = 0x11;
		break;

	case 0x11:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_iteration = m_iteration + 1;
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				MemoryCardMan.McClose();
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
				m_state = -1;
				if (m_lastResult == -5) {
					return -4;
				}
			} else {
				const int finishedSlot = m_iteration - 1;
				SetListDat(finishedSlot, 1);
				MenuPcs.BindMcObj(m_iteration - 1);
				if (m_iteration < 4) {
					m_state = 0x10;
				} else {
					m_state = 0x0C;
				}
			}
		}
		break;

	case 0x12: {
		unsigned long long serial;
		if (CARDGetSerialNo(m_cardChannel, &serial) == 0) {
			m_serial = serial;
		} else {
			MemoryCardMan.McClose();
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			m_state = -1;
			return -1;
		}
		MemoryCardMan.CreateMcBuff();
		MemoryCardMan.McWrite(0, 0xA000, m_saveIndex * 0xA000 + 0x4000);
		m_state = 0x13;
		break;
	}

	case 0x13:
		if (MemoryCardMan.AsyncFinished() == 1) {
			m_lastResult = MemoryCardMan.GetResult();
			if (m_lastResult < 0) {
				m_state = -1;
				if (m_lastResult == -5) {
					MemoryCardMan.McClose();
					MemoryCardMan.McUnmount(m_cardChannel);
					MemoryCardMan.DestroyMcBuff();
					return -4;
				}
			} else {
				MemoryCardMan.DecodeData();
				SetListDat(m_saveIndex, 1);
				MenuPcs.BindMcObj(m_saveIndex);
				m_state = 0x14;
			}

			const int closeResult = MemoryCardMan.McClose();
#if !defined(VERSION_GCCJGC)
			if (closeResult != 0) {
				m_lastResult = closeResult;
				m_state = -1;
			} else
#endif
			{
				MemoryCardMan.McUnmount(m_cardChannel);
				MemoryCardMan.DestroyMcBuff();
			}
		}
		break;

		case 0x14:
		break;
	}

	int result;
	if (m_state == -1) {
		result = -1;
	} else if (m_state == 0x14) {
		result = 1;
	} else {
		result = 0;
	}
	return result;
}

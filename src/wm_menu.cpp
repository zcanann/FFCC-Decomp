#include "ffcc/ptrarray.h"
#include "ffcc/wm_menu.h"

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
#include "ffcc/strcase.h"
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

extern const char lbl_80331208[5];

char* DAT_8032E8A8 = const_cast<char*>(lbl_80331208);
unsigned char lbl_8032E8AC = 1;
struct WmMenuLightTable
{
	int m_diffuseCount;
	_GXColor m_ambient;
	_GXColor m_diffuseColors[3];
	Vec m_diffuseDirs[3];
};

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
extern int DAT_8032ef08;
extern int DAT_80238028;
extern char cRam8032ee21;
static const char* s_port[] = {"Port ", "-Hafen", "Porto ", "Port ", "Puerto "};

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

extern const char lbl_80331208[5] = "1.00";
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
extern const double DOUBLE_803314A8 = 25.0;
extern const float FLOAT_803314B0 = 0.6000000238418579f;
extern const float FLOAT_803314B4 = -1.399999976158142f;
extern const float FLOAT_803314B8 = 0.1745329201221466f;
extern const float FLOAT_803314bc = 0.01745329238474369f;
extern const float FLOAT_803314c0 = 25.0f;
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
extern const unsigned int s_wmWorldParamPrimaryDirtyMask = 0x00000001;
extern const unsigned int s_wmWorldParamSecondaryDirtyMask = 0x00000002;
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
static Vec s_RingOrgPos;
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
 * PAL Address: 0x80102ed8
 * PAL Size: 220b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::WmInit()
{
	const float* pInit = &FLOAT_803313dc;
	float initValue = *pInit;
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
	s_MaxAnimWait = initValue;
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
	int scriptValue = static_cast<int>(Game.m_gameWork.m_scriptSysVal0);
	gWmMenuScriptValueCache = scriptValue;
	if (scriptValue > 99) {
		gWmMenuScriptValueCache = 100;
	}
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
	const int modelBase =  (s32)(static_cast<int>(charaNo / 100) * 100);

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
	    m_wm.m_handles[handleIdx]->m_currentAnimIndex < 0 ? 0 : -1, 1);

	m_wmCharaAnimState[anim].m_frame = m_wm.m_handles[handleIdx]->m_model->m_time;
	m_wmCharaAnimState[anim].m_endFrame = m_wm.m_handles[handleIdx]->m_model->m_animEnd;
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
 * PAL Address: 0x8010172c
 * PAL Size: 6000b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::loadData()
{
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
		{2, "world50"},
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
		{3, "world51"},
		{4, "cc_logo01"},
		{4, "cc_logo02"},
		{4, "cc_logo03"},
	};

	loadTexture(tName, 2, 3, tTmp, 0x16, 0x2F, 0);

	m_wm.m_handles[0x00] = 0;
	m_wm.m_handles[0x01] = 0;
	m_wm.m_handles[0x02] = 0;
	m_wm.m_handles[0x03] = 0;
	m_wm.m_handles[0x04] = 0;
	m_wm.m_handles[0x05] = 0;
	m_wm.m_handles[0x06] = 0;
	m_wm.m_handles[0x07] = 0;
	m_wm.m_handles[0x08] = 0;
	m_wm.m_handles[0x09] = 0;
	m_wm.m_handles[0x0A] = 0;
	m_wm.m_handles[0x0B] = 0;
	m_wm.m_handles[0x0C] = 0;
	m_wm.m_handles[0x0D] = 0;
	m_wm.m_handles[0x0E] = 0;
	m_wm.m_handles[0x0F] = 0;
	m_wm.m_handles[0x10] = 0;
	m_wm.m_handles[0x11] = 0;
	m_wm.m_handles[0x12] = 0;
	m_wm.m_handles[0x13] = 0;
	m_wm.m_handles[0x14] = 0;
	m_wm.m_handles[0x15] = 0;
	m_wm.m_handles[0x16] = 0;
	m_wm.m_handles[0x17] = 0;
	m_wm.m_handles[0x18] = 0;
	m_wm.m_handles[0x19] = 0;
	m_wm.m_handles[0x1A] = 0;
	m_wm.m_handles[0x1B] = 0;
	m_wm.m_handles[0x1C] = 0;
	m_wm.m_handles[0x1D] = 0;
	m_wm.m_handles[0x1E] = 0;
	m_wm.m_handles[0x1F] = 0;
	m_wm.m_handles[0x20] = 0;
	m_wm.m_handles[0x21] = 0;
	m_wm.m_handles[0x22] = 0;
	m_wm.m_handles[0x23] = 0;
	m_wm.m_handles[0x24] = 0;
	m_wm.m_handles[0x25] = 0;
	m_wm.m_handles[0x26] = 0;
	m_wm.m_handles[0x27] = 0;

	static const short s_objtbl[] = {
		110, 52, 127, 67, 66, 73, 42, 37,
		85, 87, 86, 88, 89, 36, 90, 92,
		93, 100, 100, 100, 100, 67, 18, 19,
		20, 21, 22, 23, 24, 25, 26, 100,
		300, 500, 700, 200, 400, 600, 800, 0,
	};
	const short* charaNoTable = s_objtbl;
	const short* const charaNoDefault = charaNoTable + 21;
	for (int i = 0; i < 0x28; i++, charaNoTable++) {
		m_wm.m_handles[i] = new (MenuPcs.m_menuStage, "wm_menu.cpp", 0x1F4) CCharaPcs::CHandle;
		m_wm.m_handles[i]->Add();

		int charaKind;
		unsigned long charaNo;
		if (i < 0x20) {
			CharaPcs.m_charaAllocStage = 1;
			charaKind = 3;
			charaNo = *charaNoTable;
		} else {
			CCaravanWork& caravan = Game.m_caravanWorkArr[i - 0x20];
			CharaPcs.m_charaAllocStage = 0;
			if (caravan.m_shopState != 0) {
				charaKind = 0;
				charaNo = caravan.m_tribeId * 200 + 100;
				unsigned short variant = caravan.m_appearanceVariant;
				int gender = caravan.m_genderFlag;
				if (gender != 0) {
					charaNo += 100;
				}
				charaNo += variant;
			} else {
				charaKind = 3;
				charaNo = *charaNoDefault;
			}
		}

		m_wm.m_handles[i]->LoadModel(charaKind, charaNo, 0, 0, -1, 0, 0);
		m_wm.m_handles[i]->m_flags |= 0x141;
	}
	CharaPcs.m_charaAllocStage = 0;
	m_wm.m_handles[6]->m_model->m_lightAlpha = FLOAT_803314B0;

	m_wm.m_worldObjData = new (MenuPcs.m_menuStage, "wm_menu.cpp", 0x214) WmWorldObjInfo[40];
	{
		const float bigF = FLOAT_80331598;
		const float zeroF = FLOAT_803313dc;
		for (int i = 0; i < 0x28; i++) {
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
	    new (MenuPcs.m_menuStage, "wm_menu.cpp", 0x227) WmBubbleInfo;
	memset(m_wm.m_bubbleData, 0, sizeof(WmBubbleInfo));

	m_wm.m_frameData =
	    new (MenuPcs.m_menuStage, "wm_menu.cpp", 0x22B) WmFrameData;
	memset(m_wm.m_frameData, 0, sizeof(WmFrameData));
	InitFrameInfo();

	m_wm.m_frameInfo =
	    new (MenuPcs.m_menuStage, "wm_menu.cpp", 0x231) WmFrameInfo;
	memset(m_wm.m_frameInfo, 0, sizeof(WmFrameInfo));
	InitFrame0Info();

	m_wm.m_charaModelData =
	    new (MenuPcs.m_menuStage, "wm_menu.cpp", 0x237) WmCharaModelInfo[kWmMenuPlayerCount];
	{
		for (int i = 0; i < kWmMenuPlayerCount; i++) {
			m_wm.m_charaModelData[i].m_unknown00 = 0;
			m_wm.m_charaModelData[i].m_unknown04 = 0;
			m_wm.m_charaModelData[i].m_modelNo = 0;
			m_wm.m_charaModelData[i].m_modelChanged = 0;
			m_wm.m_charaModelData[i].m_transform.Identity();
		}
	}

	InitCharaInfo();

	m_wm.m_charaSelectData =
	    new (MenuPcs.m_menuStage, "wm_menu.cpp", 0x243) WmCharaSelectEntry[kWmCharaSelectCount];

	m_wmWorldState =
	    static_cast<WmWorldState*>(operator new(sizeof(WmWorldState), MenuPcs.m_menuStage, "wm_menu.cpp", 0x246));
	memset(m_wmWorldState, 0, sizeof(WmWorldState));

	m_wmCharaState =
	    new (MenuPcs.m_menuStage, "wm_menu.cpp", 0x24A) McListInfo[kMcListCount];
	ClrMcList();

	m_wmWorldParams =
	    static_cast<unsigned char*>(operator new(0x10, MenuPcs.m_menuStage, "wm_menu.cpp", 0x24E));
	memset(m_wmWorldParams, 0, 0x10);

	m_effectWork = new (MenuPcs.m_menuStage, "wm_menu.cpp", 0x252) EffectInfo[0x28];
	for (int i = 0; i < 0x28; i++) {
		m_effectWork[i].m_effectNo = -1;
		m_effectWork[i].m_partNo = -1;
		m_effectWork[i].m_slotNo = -1;
	}

	m_wmCharaAnimState =
	    new (MenuPcs.m_menuStage, "wm_menu.cpp", 0x25A) WmCharaAnimState[8];
	memset(m_wmCharaAnimState, 0, sizeof(WmCharaAnimState) * 8);

	m_menuWindowInfo = new (MenuPcs.m_menuStage, "wm_menu.cpp", 0x25E) MenuWindowInfo;
	memset(m_menuWindowInfo, 0, sizeof(MenuWindowInfo));

	// Re-initialize the effect work entries.
	for (int i = 0; i < 0x28; i++) {
		m_effectWork[i].m_partNo = -1;
		m_effectWork[i].m_slotNo = -1;
		m_effectWork[i].m_effectNo = -1;
	}

	bytes[0x86E] = 0;
	bytes[0x858] = 0;
	*reinterpret_cast<int*>(bytes + 0x854) = 0;
	InitCharaSelectInfo();

	SetManaWaterEffect();
	m_crystalPart = -1;
	m_crystalAttr = -1;
	SetCrystalCageAttr();

	// Crystal cage effect (effect slot 7, effect no 9).
	{
		PPPCREATEPARAM titleParam;
		EffectInfo* const effect = &m_effectWork[7];
		effect->m_effectNo = 9;
		CGObject* const titleObject = &effect->m_object;
		effect->m_slotNo = 7;
		titleObject->Create();
		titleObject->m_charaModelHandle =
		    m_wm.m_handles[7];
		titleParam.m_paramB = reinterpret_cast<unsigned int>(titleObject);
		titleParam.m_lookTargetPtr = titleObject;
		effect->m_partNo =
		    PartMng.pppCreate(0, 9, &titleParam, 1);
	}

	for (int i = 0; i < 4; i++) {
		PPPCREATEPARAM param;
		const int slot = i + 8;
		EffectInfo* effect = &m_effectWork[slot];
		if (slot == 5 && i + 5 < 0x13) {
			effect++;
		} else if (i + 8 >= 0x11 && i + 8 <= 0x14 && i + 5 > 0x19) {
			effect += 4;
		}
		const bool group = (effect->m_effectNo = i + 5) > 100;
		CGObject* const object = &effect->m_object;
		effect->m_slotNo = slot;
		object->Create();
		object->m_charaModelHandle = m_wm.m_handles[slot];
		param.m_paramB = reinterpret_cast<unsigned int>(object);
		param.m_lookTargetPtr = object;
		effect->m_partNo = PartMng.pppCreate(group, i + 5, &param, 1);
	}

	for (int i = 0; i < 5; i++) {
		PPPCREATEPARAM param;
		const int slot = i + 0xC;
		EffectInfo* effect = &m_effectWork[slot];
		if (slot == 5 && i < 0x13) {
			effect++;
		} else if (i + 0xC >= 0x11 && i + 0xC <= 0x14 && i > 0x19) {
			effect += 4;
		}
		const bool group = (effect->m_effectNo = i) > 100;
		CGObject* const object = &effect->m_object;
		effect->m_slotNo = slot;
		object->Create();
		object->m_charaModelHandle = m_wm.m_handles[slot];
		param.m_paramB = reinterpret_cast<unsigned int>(object);
		param.m_lookTargetPtr = object;
		effect->m_partNo = PartMng.pppCreate(group, i, &param, 1);
	}

	for (int i = 0; i < 4; i++) {
		PPPCREATEPARAM param;
		const int slot = i + 0x20;
		EffectInfo* effect = &m_effectWork[slot];
		if (slot == 5 && i + 0xA < 0x13) {
			effect++;
		} else if (i + 0x20 >= 0x11 && i + 0x20 <= 0x14 && i + 0xA > 0x19) {
			effect += 4;
		}
		const bool group = (effect->m_effectNo = i + 0xA) > 100;
		CGObject* const object = &effect->m_object;
		effect->m_slotNo = slot;
		object->Create();
		object->m_charaModelHandle = m_wm.m_handles[slot];
		param.m_paramB = reinterpret_cast<unsigned int>(object);
		param.m_lookTargetPtr = object;
		effect->m_partNo = PartMng.pppCreate(group, i + 0xA, &param, 1);
		if (i == 0) {
			PartPcs.GetParLocIdx(effect->m_partNo, s_RingOrgPos);
		}
	}

	s_MaxAnimWait = FLOAT_803317FC;
	for (int i = 0; i < 8; i++) {
		const int modelNo = (i + 1) * 100;
		CharaPcs.LoadAnim(0, modelNo, const_cast<char*>(s_wmCharaAnimStand), 1, 0, 0);
		CharaPcs.LoadAnim(0, modelNo, const_cast<char*>(s_wmCharaAnimWalk), 1, 0, 0);
		CharaPcs.LoadAnim(0, modelNo, const_cast<char*>(s_wmCharaAnimRun), 1, 0, 0);
		CharaPcs.LoadAnim(0, modelNo, const_cast<char*>(s_wmCharaAnimGlad), 3, 0, 0);
		CharaPcs.LoadAnim(0, modelNo, const_cast<char*>(s_wmCharaAnimSleep), 1, 0, 0);
	}

	{
		for (int i = 0; i < 8; i++) {
			if (m_wm.m_handles[i + 0x20]->m_charaKind != 3) {
				const unsigned int charaBase =
				    static_cast<unsigned int>(m_wm.m_handles[i + 0x20]->m_charaNo) /
				    100;
				const int modelNo = charaBase * 100;
				int anim = (charaBase - 1) * 6;
				m_wm.m_handles[i + 0x20]->LoadAnim(
				    const_cast<char*>(s_wmCharaAnimStand), anim++, 1, 0, modelNo, -1, 0);
				m_wm.m_handles[i + 0x20]->LoadAnim(
				    const_cast<char*>(s_wmCharaAnimWalk), anim++, 1, 0, modelNo, -1, 0);
				m_wm.m_handles[i + 0x20]->LoadAnim(
				    const_cast<char*>(s_wmCharaAnimRun), anim++, 1, 0, modelNo, -1, 0);
				m_wm.m_handles[i + 0x20]->LoadAnim(
				    const_cast<char*>(s_wmCharaAnimGlad), anim++, 3, 0, modelNo, -1, 0);
				m_wm.m_handles[i + 0x20]->LoadAnim(
				    const_cast<char*>(s_wmCharaAnimSleep), anim++, 1, 0, modelNo, -1, 0);
				m_wm.m_handles[i + 0x20]->LoadAnim(
				    const_cast<char*>(s_wmCharaAnimAngry), anim++, 1, 0, modelNo, -1, 0);
				m_wmCharaAnimState[i].m_animIndex = 0;
				m_wmCharaAnimState[i].m_nextAnimIndex = -1;
				m_wmCharaAnimState[i].m_timer = rand() % 250;
				m_wm.m_handles[i + 0x20]->SetAnim(anim - 6, -1, -1, 0, 0);
				m_wmCharaAnimState[i].m_frame = m_wm.m_handles[i + 0x20]->m_model->m_time;
				m_wmCharaAnimState[i].m_endFrame = m_wm.m_handles[i + 0x20]->m_model->m_animEnd;
				float maxWait = static_cast<float>(
				    m_wm.m_handles[i + 0x20]->m_animSlot[anim - 1]->m_anim->m_frameCount);
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

	{
#define worldState (reinterpret_cast<unsigned char*>(m_wmWorldState))
		*reinterpret_cast<short*>(worldState + 0x1C) = 0;
		*reinterpret_cast<short*>(worldState + 0x36) = static_cast<short>(Game.m_gameWork.m_wmBackupParams[0]);
		*reinterpret_cast<short*>(worldState + 0x3E) = static_cast<short>(Game.m_gameWork.m_wmBackupParams[0]);
		*reinterpret_cast<short*>(worldState + 0x38) = static_cast<short>(Game.m_gameWork.m_wmBackupParams[1]);
		*reinterpret_cast<short*>(worldState + 0x40) = static_cast<short>(Game.m_gameWork.m_wmBackupParams[1]);
		*reinterpret_cast<short*>(worldState + 0x3A) = static_cast<short>(Game.m_gameWork.m_wmBackupParams[2]);
		*reinterpret_cast<short*>(worldState + 0x42) = static_cast<short>(Game.m_gameWork.m_wmBackupParams[2]);
		*reinterpret_cast<short*>(worldState + 0x3C) = static_cast<short>(Game.m_gameWork.m_wmBackupParams[3]);
		*reinterpret_cast<short*>(worldState + 0x44) = static_cast<short>(Game.m_gameWork.m_wmBackupParams[3]);
#undef worldState
	}

	char fontPath[128];
	sprintf(fontPath, "dvd/%smenu/subfont.fnt", Game.GetLangString());
	loadFont(0, fontPath, 1, -1);

	bytes[0xD] = 0;
	{
		unsigned char* const worldState = reinterpret_cast<unsigned char*>(m_wmWorldState);
		bytes[0x10] = 0;
		bytes[0x12] = 0;
		bytes[0x13] = 0;
		*reinterpret_cast<short*>(worldState + 0x20) = 0;
		*reinterpret_cast<short*>(worldState + 0x1E) = 0;
		*reinterpret_cast<short*>(worldState + 0x18) = 0;
	}
	lbl_8032EE1C = 1;
	lbl_8032E8AC = 1;

	for (int i = 4; i < 6; i++) {
		m_battleMesMenus[i] = new (MenuPcs.m_menuStage, "wm_menu.cpp", 0x2EA) CMesMenu;
		CMesMenu* const cur = m_battleMesMenus[i];
		cur->SetBattleIndex(i);
		cur->Create();
	}

	char optionPath[256];
	sprintf(optionPath, "dvd/%smenu/option.tex", Game.GetLangString());
	CFile::CHandle* const fileHandle = File.Open(optionPath, 0, CFile::PRI_LOW);
	if (fileHandle != 0) {
		File.Read(fileHandle);
		File.SyncCompleted(fileHandle);
		CTextureSet* texSet =
		    new (MenuPcs.m_menuStage, "wm_menu.cpp", 0x300) CTextureSet;
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
	return result + offset;
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

	freeTexture(2, 3, 0x16, 0x2F);

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

	GXSetCopyClear(Graphic.m_defaultCopyClearColor, 0x00FFFFFF);
	GbaQue.SetControllerMode(0);
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
	int frameSum = static_cast<int>(m_wm.m_frameInfo->m_sprites[0].m_width) +
	               static_cast<int>(m_wm.m_frameInfo->m_sprites[0].m_x);
	value = static_cast<int>(FLOAT_803313e0 - static_cast<float>(frameSum));
	m_wm.m_frameInfo->m_sprites[1].m_x = static_cast<short>(value);

	if (param < 0) {
		float offset = static_cast<float>(static_cast<int>(m_wm.m_frameInfo->m_sprites[0].m_width) +
		                                  static_cast<int>(m_wm.m_frameInfo->m_sprites[0].m_x));
		if (param >= -10) {
			int absRaw = abs(param);
			offset = static_cast<float>(static_cast<double>(offset) * (DOUBLE_803314E8 * static_cast<double>(absRaw)));
			int absParam = abs(param);
			if (absParam < 0) {
				absParam = 0;
			}
			if (absParam > 10) {
				absParam = 10;
			}
			offset *= static_cast<float>(sin(static_cast<double>(FLOAT_803314bc * (static_cast<float>(absParam) * FLOAT_803316D4))));
		}
		value = static_cast<int>(static_cast<float>(static_cast<int>(m_wm.m_frameInfo->m_sprites[0].m_x)) - offset);
		m_wm.m_frameInfo->m_sprites[0].m_x = static_cast<short>(value);
		value = static_cast<int>(static_cast<float>(static_cast<int>(m_wm.m_frameInfo->m_sprites[1].m_x)) + offset);
		m_wm.m_frameInfo->m_sprites[1].m_x = static_cast<short>(value);
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
 * PAL Address: 0x80100b00
 * PAL Size: 1616b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcDiaryMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	static bool s_wmMenuLastMountState = false;

	const bool mounted = MemoryCardMan.m_currentSlot != -1;
	if (mounted != s_wmMenuLastMountState) {
		if (static_cast<unsigned int>(System.m_execParam) >= 3) {
			const char* text = "FALSE";
			if (mounted != 0) {
				text = "TRUE";
			}
			System.Printf("mount = %s\n", text);
		}
		s_wmMenuLastMountState = mounted;
	}

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

	switch (m_wmWorldState->m_menuMode) {
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
			System.Printf("%s(%d): Error:WM menu no error(%d)\n", "wm_menu.cpp", 0x4c0);
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
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
#define worldParams m_wmWorldParams

	reinterpret_cast<unsigned int*>(worldParams + 4)[0] = reinterpret_cast<unsigned int*>(worldParams + 8)[0];

	if (m_wmWorldState->m_worldReady == 0) {
		Sound.PlaySe(0x138B, 0x40, 0x7F, 0);
		GetWmWorldHandles(this)[1]->SetAnim(0, -1, -1, -1, 0);
		reinterpret_cast<unsigned int*>(worldParams + 8)[0] = 0;
		m_wmWorldState->m_worldReady = 1;
		m_wmWorldState->m_mainState = 1;
	}

#define handle GetWmWorldHandles(this)[1]
#define model handle->m_model
	const int animState = m_wmWorldState->m_mainState;
	const float animTime = reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(model) + 0xB4)[0];
	const float animEnd = reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(model) + 0xC0)[0];

	if (animState == 1) {
		if (animTime < animEnd) {
			model->AddFrame(FLOAT_80331698);
			m_wmWorldState->m_frameCounter = 0;
		} else {
			if (m_wmWorldState->m_frameCounter >= 10) {
				CFlatRuntime::CStack stackData[3];

				handle->SetAnim(1, -1, -1, -1, 0);
				reinterpret_cast<unsigned int*>(worldParams + 8)[0] = 1;
				stackData[0].m_word = 2;
				stackData[1].m_word = 0;
				stackData[2].m_word = 0;
				gCFlatRuntime().SystemCall(0, 1, 4, 3, stackData, 0);
				m_wmWorldState->m_mainState = 2;
				m_wmWorldState->m_frameCounter = 0;
			}
		}
	} else if (animState == 2) {
		int nextAnim = static_cast<signed char>(bytes[0xE]);

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

			if (nextAnim != reinterpret_cast<int*>(worldParams + 8)[0]) {
				handle->SetAnim(nextAnim, -1, -1, -1, 0);
				reinterpret_cast<int*>(worldParams + 8)[0] = nextAnim;

				if (nextAnim == 0) {
					model->SetFrame(animEnd);
				}
			}
			bytes[0xE] = 0;
		} else {
			if (animTime < animEnd) {
				model->AddFrame(FLOAT_80331698);
			} else {
				handle->SetAnim(1, -1, -1, -1, 0);
				reinterpret_cast<unsigned int*>(worldParams + 8)[0] = 1;
			}
		}
	} else if (animState == 3 && m_wmWorldState->m_frameCounter >= 10) {
		if (animTime < animEnd) {
			model->AddFrame(FLOAT_80331698);
		} else {
			handle->SetAnim(0, -1, -1, -1, 0);
			reinterpret_cast<unsigned int*>(worldParams + 8)[0] = 0;
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
	const float fVar1 = FLOAT_803313dc;
	worldObj[1].m_viewportY = 0;
	float fVar3 = FLOAT_80331598;
	worldObj[1].m_viewportWidth = 0x280;
	const float fVar4 = FLOAT_803315d4;
	worldObj[1].m_viewportHeight = 0x1C0;
	const float fVar5 = FLOAT_803317e0;
	worldObj[1].m_cameraPosition.x = fVar1;
	const float fVar6 = FLOAT_803317e4;
	worldObj[1].m_cameraPosition.y = fVar1;
	const float fVar7 = FLOAT_803317e8;
	worldObj[1].m_cameraPosition.z = fVar3;
	fVar3 = FLOAT_803314bc;
	worldObj[1].m_active = 1;
	worldObj[1].m_transform.m_scale.x = fVar4;
	worldObj[1].m_transform.m_scale.y = fVar4;
	worldObj[1].m_transform.m_scale.z = fVar4;
	worldObj[1].m_transform.m_position.x = fVar1;
	worldObj[1].m_transform.m_position.y = fVar5;
	worldObj[1].m_transform.m_position.z = fVar6;
	worldObj[1].m_transform.m_rotation.x = fVar7;
	worldObj[1].m_transform.m_rotation.y = fVar1;
	worldObj[1].m_transform.m_rotation.z = fVar1;

	Mtx matrix;
	PSMTXRotRad(matrix, 'x', fVar3 * worldObj[1].m_transform.m_rotation.x);
	matrix[0][3] = worldObj[1].m_transform.m_position.x;
	matrix[1][3] = worldObj[1].m_transform.m_position.y;
	matrix[2][3] = worldObj[1].m_transform.m_position.z;
	PSMTXScaleApply(matrix, matrix, worldObj[1].m_transform.m_scale.x, worldObj[1].m_transform.m_scale.y,
	                worldObj[1].m_transform.m_scale.z);

	model->SetMatrix(matrix);
	model->CalcMatrix();
	model->CalcSkin();

	const int updatedAnimState = m_wmWorldState->m_mainState;

	if (updatedAnimState == 1 && animTime >= animEnd) {
		if (m_wmWorldState->m_frameCounter < 10) {
			m_wmWorldState->m_frameCounter++;
		}
	} else if (updatedAnimState == 3 && m_wmWorldState->m_frameCounter < 10) {
		m_wmWorldState->m_frameCounter++;
	}
#undef worldParams
#undef model
#undef handle
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
	int count = 0;
	for (int i = 0; i < kMcListCount; i++) {
		const McListInfo& entry = m_wmCharaState[i];
		if (entry.m_isBroken == 0 && static_cast<int>(entry.m_scriptSysVal0) > 0) {
			count++;
		}
	}
	return count;
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
    const short newX = static_cast<short>(static_cast<int>(static_cast<float>(static_cast<float>(0x280 - x) * DOUBLE_803313F8)));
    const short newY = static_cast<short>(static_cast<int>(static_cast<float>((FLOAT_80331430 - static_cast<float>(y)) * DOUBLE_803313F8)));
    m_menuWindowInfo->x = newX;
    m_menuWindowInfo->y = newY;
    m_menuWindowInfo->width = static_cast<short>(x);
    m_menuWindowInfo->height = static_cast<short>(y);
    m_menuWindowInfo->frame = 0;
    m_menuWindowInfo->state = 3;
}

/*
 * --INFO--
 * PAL Address: 0x800ea014
 * PAL Size: 316b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetWinSize(int winType, short* w, short* h, int messType)
{
	CFont* const font = m_fonts[0];

	font->SetMargin(FLOAT_803313e8);
	font->SetShadow(0);
	font->SetScale(FLOAT_803313e8);

	const char* const* msgTable = GetMcWinMessBuff(messType);
	int maxWidth = 0;
	const WinMessEntry* const winMess = GetWinMess(winType);

	for (int i = 0; i < winMess->m_lineCount; i++) {
		const short msgId = winMess->m_messageIds[i];
		const char* text = msgTable[msgId];
		if (text != 0) {
			if (text[0] == '$') {
				text++;
			}
			const int textWidth = font->GetWidth(text);
			if (textWidth > maxWidth) {
				maxWidth = textWidth;
			}
		}
	}

	int cols = maxWidth / 0x16;
	if ((maxWidth % 0x16) != 0) {
		cols++;
	}

	*w = static_cast<short>((cols + 2) * 0x16 + 0x40);
	*h = static_cast<short>(winMess->m_lineCount * 0x1E + 0x40);
}

/*
 * --INFO--
 * PAL Address: 0x800fec40
 * PAL Size: 6552b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcMCardMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	bool bVar1 = false;
	unsigned int uVar3 = Pad.GetButtonDown(0);
	unsigned short uVar6 = GetButtonRepeat(0);

	if ((signed char)m_wmWorldState->m_worldReady == 0) {
		m_mcCtrl.m_previousState = 0;
		m_mcCtrl.m_state = 0;
		m_mcCtrl.m_lastResult = 0;
		m_mcCtrl.m_iteration = 0;
		m_mcCtrl.m_userBuffer = 0;
		m_mcCtrl.m_createFlag = 0;
		if (gWmMenuCursorX[0] >= 0 && gWmMenuCursorX[0] < 2) {
			m_mcCtrl.m_cardChannel = (int)gWmMenuCursorX[0];
		} else {
			m_mcCtrl.m_cardChannel = 0;
		}
		if (gWmMenuCursorX[1] >= 0 && gWmMenuCursorX[1] < 4) {
			m_mcCtrl.m_saveIndex = (int)gWmMenuCursorX[1];
		} else {
			m_mcCtrl.m_saveIndex = 0;
		}
		ClrMcList();
		for (int i = 0; i < kWmMenuControllerCount; i++) {
			Game.m_gameWork.m_wmBackupParams[i] = m_wmWorldState->m_originalBackupParams[i];
		}
		m_wmWorldState->m_flag0A = 0;
		m_wmWorldState->m_worldReady = 1;
	}

	int iVar14;
	int iVar12;
	short sVar7 = m_wmWorldState->m_mainState;
	unsigned int uVar15;
	if (sVar7 == 0) {
		uVar15 = static_cast<int>(m_wmWorldState->m_frameCounter) - 10;
	} else if (sVar7 > 0 && sVar7 < 4) {
		uVar15 = 0;
	} else {
		uVar15 = -static_cast<int>(m_wmWorldState->m_frameCounter);
	}

	CalcWMFrame0(static_cast<int>(uVar15));

	if (m_wmWorldState->m_mainState != 2) {
		return;
	}

	iVar12 = m_wmWorldState->m_subState;
	switch (iVar12) {
	case 0:
	case 2:
		if ((signed char)m_wmWorldState->m_flag09 == 0) {
			m_wmWorldState->m_cardChannel = static_cast<short>(m_mcCtrl.m_cardChannel);
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
				if ((uVar6 & 3) != 0) {
					m_wmWorldState->m_cardChannel ^= 1;
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				} else {
					if ((uVar3 & 0x100) != 0) {
						m_wmWorldState->m_state0E = 1;
						m_mcCtrl.m_cardChannel = m_wmWorldState->m_cardChannel;
						if (m_wmWorldState->m_cardChannel == static_cast<signed char>(gWmMenuCursorX[0])) {
							m_mcCtrl.m_saveIndex = (int)gWmMenuCursorX[1];
						}
						m_wmWorldState->m_counter1A = 10;
						Sound.PlaySe(2, 0x40, 0x7F, 0);
					} else {
						if ((uVar3 & 0x200) != 0) {
							m_wmWorldState->m_state0E = -1;
							m_wmWorldState->m_counter1A = 1;
							Sound.PlaySe(3, 0x40, 0x7F, 0);
						}
					}
				}
			}
		}
		if (m_menuWindowInfo->state == 1) {
			sVar7 = m_wmWorldState->m_counter1A;
			if (sVar7 != 0) {
				m_wmWorldState->m_counter1A = sVar7 - 1;
				if (m_wmWorldState->m_counter1A == 0) {
					m_menuWindowInfo->state = 2;
				}
			}
		}
		break;
	case 3:
		m_wmWorldState->m_mcResult = static_cast<short>(MemoryCardMan.McChkConnect(m_mcCtrl.GetDno()));
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
			bVar1 = true;
			int uVar17;
			int uVar20 = 0;
			if (iVar12 == 5) { uVar17 = 1; }
			else if (iVar12 == 6) { uVar17 = 2; }
			else if (iVar12 == 7) { uVar17 = 3; }
			else if (iVar12 == 9) { uVar17 = 10; }
			else if (iVar12 == 10) { uVar17 = 0xB; }
			else if (iVar12 == 0xE) { uVar17 = 0xC; }
			else if (iVar12 == 0xF) { uVar17 = 0xD; }
			else if (iVar12 == 0x1C) { uVar20 = 1; uVar17 = 0x1B; }
			else if (iVar12 == 0x1B) { uVar20 = 1; uVar17 = 0x1C; }
			else if (iVar12 == 0x15) { bVar1 = false; uVar17 = 0xE; }
			else { uVar17 = 0xF; }
			short windowWidth;
			short windowHeight;
			GetWinSize(uVar17, &windowWidth, &windowHeight, uVar20);
			SetMcWinInfo(windowWidth, windowHeight);
			m_menuWindowInfo->state = 0;
			m_wmWorldState->m_flag09 = 1;
			m_wmWorldState->m_counter1A = 0;
			if (bVar1) {
				Sound.PlaySe(4, 0x40, 0x7F, 0);
			}
		}
		if (m_menuWindowInfo->state == 1
		    && m_wmWorldState->m_counter1A == 0) {
			sVar7 = m_wmWorldState->m_subState;
			if (sVar7 == 0xE || sVar7 == 0x15) {
				m_wmWorldState->m_mcResult = (short)MemoryCardMan.McChkConnect(m_mcCtrl.GetDno());
				if (m_wmWorldState->m_mcResult < 0) goto LAB_chk;
			} else if (sVar7 == 5) {
				m_wmWorldState->m_mcResult = (short)MemoryCardMan.McChkConnect(m_mcCtrl.GetDno());
			LAB_chk:
				sVar7 = m_wmWorldState->m_subState;
				short sVar16;
				if (sVar7 == 5) { sVar16 = -1; }
				else if (sVar7 == 6) { sVar16 = -3; }
				else if (sVar7 == 7) { sVar16 = -4; }
				else { sVar16 = 0; }
				if (sVar7 != 7) {
					if (sVar16 != m_wmWorldState->m_mcResult && m_wmWorldState->m_mcResult != 1) {
						m_wmWorldState->m_state0E = -1;
						m_wmWorldState->m_counter1A = 1;
						break;
					}
				} else {
					short chk = m_wmWorldState->m_mcResult;
					if (chk != 0 && chk != sVar16 && chk != 1) {
						m_wmWorldState->m_state0E = -1;
						m_wmWorldState->m_counter1A = 1;
						break;
					}
				}
			}
			if ((uVar3 & 0x300) != 0) {
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
			sVar7 = m_wmWorldState->m_counter1A;
			if (sVar7 != 0) {
				m_wmWorldState->m_counter1A = sVar7 - 1;
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
			m_mcCtrl.m_previousState = 0;
			m_mcCtrl.m_state = 0;
			m_mcCtrl.m_lastResult = 0;
			m_mcCtrl.m_iteration = 0;
			m_mcCtrl.m_userBuffer = 0;
			m_mcCtrl.m_createFlag = 0;
			m_wmWorldState->m_flag09 = 1;
		} else if (m_menuWindowInfo->state == 1
		           && m_wmWorldState->m_counter1A == 0) {
			short chkResult = (short)GetMcCtrl()->ChkEmpty(0);
			int __p12 = chkResult;
			m_wmWorldState->m_mcResult = __p12;
			if (m_wmWorldState->m_mcResult < 0) {
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = 0xFF;
				m_wmWorldState->m_state0E = -1;
				m_wmWorldState->m_counter1A = 10;
			}
		}
		if (m_menuWindowInfo->state == 1) {
			sVar7 = m_wmWorldState->m_counter1A;
			if (sVar7 != 0) {
				m_wmWorldState->m_counter1A = sVar7 - 1;
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
			int uVar20 =  (int)(long)(0);
			int uVar17;
			if (iVar12 == 8) {
				m_wmWorldState->m_cardChannel = 0;
				uVar17 = 4;
			} else if (iVar12 == 0xB) {
				uVar17 = 5;
				m_wmWorldState->m_cardChannel = 1;
			} else if (iVar12 == 0x19) {
				uVar17 = 0x19;
				uVar20 = 1;
				m_wmWorldState->m_cardChannel = 1;
			} else {
				uVar17 = 0x12;
				m_wmWorldState->m_cardChannel = 1;
			}
			short windowWidth;
			short windowHeight;
			GetWinSize(uVar17, &windowWidth, &windowHeight, uVar20);
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
				int chkRes = MemoryCardMan.McChkConnect(m_mcCtrl.GetDno());
				m_wmWorldState->m_mcResult = (short)chkRes;
				if (m_wmWorldState->m_mcResult != 0) {
					m_wmWorldState->m_state0E = -1;
					m_wmWorldState->m_counter1A = 10;
				} else {
					if ((uVar6 & 3) != 0) {
						m_wmWorldState->m_cardChannel ^= 1;
						Sound.PlaySe(1, 0x40, 0x7F, 0);
					} else {
						if ((uVar3 & 0x100) != 0) {
							if (m_wmWorldState->m_cardChannel == 0) {
								m_wmWorldState->m_state0E = 1;
							} else {
								m_wmWorldState->m_state0E = -1;
							}
							m_wmWorldState->m_counter1A = 10;
							Sound.PlaySe(2, 0x40, 0x7F, 0);
						} else {
							if ((uVar3 & 0x200) != 0) {
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
				m_wmWorldState->m_mcResult = (short)MemoryCardMan.McChkConnect(m_mcCtrl.GetDno());
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
			int uVar20;
			uVar20 = 0;
			int uVar17;
			if (iVar12 == 0xD) { uVar17 = 7; }
			else if (iVar12 == 0x1A) { uVar17 = 0x1A; uVar20 = 1; }
			else { uVar17 = 8; }
			short windowWidth;
			short windowHeight;
			GetWinSize(uVar17, &windowWidth, &windowHeight, uVar20);
			SetMcWinInfo(windowWidth, windowHeight);
			m_menuWindowInfo->state = 0;
			m_mcCtrl.m_previousState = 0;
			m_mcCtrl.m_state = 0;
			m_mcCtrl.m_lastResult = 0;
			m_mcCtrl.m_iteration = 0;
			m_mcCtrl.m_userBuffer = 0;
			m_mcCtrl.m_createFlag = 0;
			if (m_wmWorldState->m_menuMode == 8
			    && m_cmakeWork != 0) {
				m_mcCtrl.m_userBuffer = m_cmakeWork;
			} else {
				m_mcCtrl.m_userBuffer = 0;
			}
			m_wmWorldState->m_flag09 = 1;
		} else if (m_menuWindowInfo->state == 1
		           && m_wmWorldState->m_counter1A == 0) {
			if (iVar12 == 0xD) {
				GetMcCtrl()->Format(1);
				m_wmWorldState->m_mcResult = (short)m_mcCtrl.m_lastResult;
				if (m_wmWorldState->m_mcResult < 0) {
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
				}
			} else if (iVar12 == 0x1A) {
				m_wmWorldState->m_mcResult = (short)GetMcCtrl()->EraseDat();
				if (m_wmWorldState->m_mcResult < 0) {
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
				}
			} else {
				m_wmWorldState->m_mcResult = (short)GetMcCtrl()->SaveDat();
				if (m_wmWorldState->m_mcResult < 0) {
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
				}
			}
			if (m_wmWorldState->m_mcResult == 0) break;
			if (m_wmWorldState->m_subState == 0x13) {
				if (m_wmWorldState->m_menuMode != 8) {
					s_Serial = m_mcCtrl.GetSerial();
					gWmMenuCursorX[0] = (unsigned char)m_mcCtrl.m_cardChannel;
					gWmMenuCursorX[1] = (unsigned char)m_mcCtrl.m_saveIndex;
				}
				m_wmCharaState[m_mcCtrl.m_saveIndex].m_scriptSysVal0 = Game.m_gameWork.m_scriptSysVal0;
			}
			m_wmWorldState->m_state0E = 1;
			m_wmWorldState->m_counter1A = 10;
		}
		if (m_menuWindowInfo->state == 1) {
			sVar7 = m_wmWorldState->m_counter1A;
			if (sVar7 != 0) {
				m_wmWorldState->m_counter1A = sVar7 - 1;
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
			m_mcCtrl.m_previousState = 0;
			m_mcCtrl.m_state = 0;
			m_mcCtrl.m_lastResult = 0;
			m_mcCtrl.m_iteration = 0;
			m_mcCtrl.m_userBuffer = 0;
			m_mcCtrl.m_createFlag = 0;
		}
		if (m_menuWindowInfo->state == 1
		    && m_wmWorldState->m_counter1A == 0) {
			short listRes = (short)GetMcCtrl()->LoadMcList();
			int __p9 = listRes;
			m_wmWorldState->m_mcResult = __p9;
			if (m_wmWorldState->m_mcResult == 0) {
				if (m_wmWorldState->m_mcResult < 0) {
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
				}
				break;
			}
			if (m_wmWorldState->m_menuMode == 8) {
				const int iVar21 = ChkMcDataCnt();
				if (iVar21 == 0) {
					m_wmWorldState->m_mcResult = (short)0xFC19;
				}
			}
			if (!(gWmMenuCursorX[1] >= 0 && (int)gWmMenuCursorX[0] == m_mcCtrl.m_cardChannel)) {
			LAB_saveIdx:
				int sel;
				for (sel = 0; sel < kMcListCount; sel++) {
					if (m_wmCharaState[sel].m_isBroken != 0 ||
					    static_cast<int>(m_wmCharaState[sel].m_scriptSysVal0) <= 0) {
						break;
					}
				}
				m_mcCtrl.m_saveIndex = sel < kMcListCount ? sel : 0;
				m_wmWorldState->m_cardChannel = (short)m_mcCtrl.m_saveIndex;
			} else {
				if (s_Serial != m_mcCtrl.GetSerial()) goto LAB_saveIdx;
				m_mcCtrl.m_saveIndex = (int)gWmMenuCursorX[1];
				m_wmWorldState->m_cardChannel = (short)m_mcCtrl.m_saveIndex;
			}
			iVar12 = 0;
			for (int iVar21 = 4; iVar21 != 0; iVar21--) {
				if (m_wmCharaState[iVar12].m_isBroken != 0) {
					m_mcCtrl.m_saveIndex = iVar12;
					m_wmWorldState->m_cardChannel = (short)iVar12;
					break;
				}
				iVar12++;
			}
			m_wmWorldState->m_state0E = 1;
			m_wmWorldState->m_counter1A = 10;
		}
		if (m_menuWindowInfo->state == 1) {
			sVar7 = m_wmWorldState->m_counter1A;
			if (sVar7 != 0) {
				m_wmWorldState->m_counter1A = sVar7 - 1;
				if (m_wmWorldState->m_counter1A == 0) {
					m_menuWindowInfo->state = 2;
				}
			}
		}
		break;
	}
	case 0x11:
		m_wmWorldState->m_mcResult = (short)MemoryCardMan.McChkConnect(m_mcCtrl.GetDno());
		if (m_wmWorldState->m_mcResult == 0 && uVar6 != 0) {
			if ((uVar6 & 8) != 0) {
				if (m_wmWorldState->m_cardChannel < 1) {
					m_wmWorldState->m_cardChannel = 3;
				} else {
					m_wmWorldState->m_cardChannel--;
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			} else {
				if ((uVar6 & 4) != 0) {
					if (!(m_wmWorldState->m_cardChannel < 3)) {
						m_wmWorldState->m_cardChannel = 0;
					} else {
						m_wmWorldState->m_cardChannel++;
					}
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				}
			}
			if ((uVar6 & 0xC) == 0) {
				if ((uVar3 & 0x100) != 0) {
					sVar7 = m_wmWorldState->m_state0E;
					if (sVar7 != -1 && sVar7 != 1) {
						m_mcCtrl.m_saveIndex = (int)m_wmWorldState->m_cardChannel;
						m_wmWorldState->m_state0E = 1;
						Sound.PlaySe(2, 0x40, 0x7F, 0);
					}
				}
				if ((uVar3 & 0x200) != 0) {
					sVar7 = m_wmWorldState->m_state0E;
					if (sVar7 != -1 && sVar7 != 1) {
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
 * PAL Address: 0x800fcfb4
 * PAL Size: 7148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcLoadMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	unsigned char bVar1 = 0;
	m_textureLocIndex = 0;

	unsigned int uVar4 = Pad.GetButtonDown(0);
	unsigned short uVar7 = GetButtonRepeat(0);

	if (m_wmWorldState->m_worldReady == 0) {
		InitFrame0Info();

		m_mcCtrl.Init();
		ClrMcList();

		for (int i = 0; i < kWmMenuControllerCount; i++) {
			Game.m_gameWork.m_wmBackupParams[i] = m_wmWorldState->m_originalBackupParams[i];
		}
		if (m_wmWorldState->m_menuMode == 8 && m_cmakeWorkCardChannel != 0) {
			m_mcCtrl.m_cardChannel = (int)m_cmakeWorkCardChannel - 1;
			m_wmWorldState->m_subState = 3;
			m_wmWorldState->m_flag09 = 1;
		}
		m_wmWorldState->m_flag0A = 0;
		m_wmWorldState->m_worldReady = 1;
	}

	int iVar14;
	short sVar8 = m_wmWorldState->m_mainState;
	unsigned int uVar15;
	if (sVar8 == 0) {
		uVar15 = static_cast<int>(m_wmWorldState->m_frameCounter) - 10;
	} else if (sVar8 > 0 && sVar8 < 4) {
		uVar15 = 0;
	} else {
		uVar15 = -static_cast<int>(m_wmWorldState->m_frameCounter);
	}

	CalcWMFrame0(static_cast<int>(uVar15));
	int iVar10;

	if (m_wmWorldState->m_mainState != 2) {
		return;
	}

	iVar10 = m_wmWorldState->m_subState;
	switch (iVar10) {
	case 0:
	case 2:
		if ((signed char)m_wmWorldState->m_flag09 == 0) {
			m_wmWorldState->m_cardChannel = (short)m_mcCtrl.m_cardChannel;
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
				if ((uVar7 & 3) != 0) {
					m_wmWorldState->m_cardChannel ^= 1;
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				} else {
					if ((uVar4 & 0x100) != 0) {
						m_wmWorldState->m_state0E = 1;
						m_mcCtrl.m_cardChannel = (int)m_wmWorldState->m_cardChannel;
						m_wmWorldState->m_counter1A = 10;
						Sound.PlaySe(2, 0x40, 0x7F, 0);
					} else {
						if ((uVar4 & 0x200) != 0) {
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
		m_wmWorldState->m_mcResult = (short)MemoryCardMan.McChkConnect(m_mcCtrl.GetDno());
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
			bVar1 = true;
			int uVar22 = 0;
			int uVar19;
			if (iVar10 == 5) { uVar19 = 1; }
			else if (iVar10 == 6) { uVar19 = 2; }
			else if (iVar10 == 7) { uVar19 = 3; }
			else if (iVar10 == 10) { uVar19 = 0xB; }
			else if (iVar10 == 0xE) { uVar19 = 0xC; }
			else if (iVar10 == 0xF) { uVar19 = 0xD; }
			else if (iVar10 == 0x1C) { uVar19 = 0x1B; uVar22 = 1; }
			else if (iVar10 == 0x1B) { uVar19 = 0x1C; uVar22 = 1; }
			else if (iVar10 == 0x18) { bVar1 = false; uVar19 = 0x10; }
			else if (iVar10 == 0x17) { uVar19 = 0x11; }
			else { uVar19 = 0x13; }
			if (bVar1) {
				Sound.PlaySe(4, 0x40, 0x7F, 0);
			}
			short windowWidth;
			short windowHeight;
			GetWinSize(uVar19, &windowWidth, &windowHeight, uVar22);
			SetMcWinInfo(windowWidth, windowHeight);
			m_menuWindowInfo->state = 0;
			m_wmWorldState->m_flag09 = 1;
			m_wmWorldState->m_counter1A = 0;
		}
		if (m_menuWindowInfo->state == 1
		    && m_wmWorldState->m_counter1A == 0) {
			if (m_wmWorldState->m_subState == 0xE) {
				m_wmWorldState->m_mcResult = (short)MemoryCardMan.McChkConnect(m_mcCtrl.GetDno());
				if (m_wmWorldState->m_mcResult < 0) goto LAB_chkLoad;
			} else if (m_wmWorldState->m_subState == 5) {
				m_wmWorldState->m_mcResult = (short)MemoryCardMan.McChkConnect(m_mcCtrl.GetDno());
			LAB_chkLoad:
				sVar8 = m_wmWorldState->m_subState;
				short sVar18;
				if (sVar8 == 5) { sVar18 = -1; }
				else if (sVar8 == 6) { sVar18 = -3; }
				else if (sVar8 == 7) { sVar18 = -4; } else { sVar18 = 0; }
				if (sVar8 != 7) {
					if (m_wmWorldState->m_mcResult != 0 && m_wmWorldState->m_mcResult != sVar18 && m_wmWorldState->m_mcResult != 1) {
						m_wmWorldState->m_state0E = -1;
						m_wmWorldState->m_counter1A = 1;
						break;
					}
				} else {
					short chk = m_wmWorldState->m_mcResult;
					if (chk != 0 && chk != sVar18 && chk != 1) {
						m_wmWorldState->m_state0E = -1;
						m_wmWorldState->m_counter1A = 1;
						break;
					}
				}
			}
			if ((uVar4 & 0x300) != 0) {
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
			m_mcCtrl.m_previousState = 0;
			m_mcCtrl.m_state = 0;
			m_mcCtrl.m_lastResult = 0;
			m_mcCtrl.m_iteration = 0;
			m_mcCtrl.m_userBuffer = 0;
			m_mcCtrl.m_createFlag = 0;
			m_wmWorldState->m_flag09 = 1;
		} else if (m_menuWindowInfo->state == 1
		           && m_wmWorldState->m_counter1A == 0) {
			short chkResult = (short)GetMcCtrl()->ChkEmpty(1);
			m_wmWorldState->m_mcResult = chkResult;
			if (m_wmWorldState->m_mcResult < 0) {
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = 0xFF;
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
			int uVar22 = 0;
			int uVar19;
			if (iVar10 == 8) {
				m_wmWorldState->m_cardChannel = 0;
				uVar19 = 4;
			} else if (iVar10 == 0x19) {
				uVar22 = 1;
				uVar19 = 0x19;
				m_wmWorldState->m_cardChannel = 1;
			} else {
				uVar19 = 5;
				m_wmWorldState->m_cardChannel = 1;
			}
			short windowWidth;
			short windowHeight;
			GetWinSize(uVar19, &windowWidth, &windowHeight, uVar22);
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
				int chkRes = MemoryCardMan.McChkConnect(m_mcCtrl.GetDno());
				m_wmWorldState->m_mcResult = (short)chkRes;
				if (m_wmWorldState->m_mcResult != 0) {
					m_wmWorldState->m_state0E = -1;
					m_wmWorldState->m_counter1A = 10;
				} else {
					if ((uVar7 & 3) != 0) {
						m_wmWorldState->m_cardChannel ^= 1;
						Sound.PlaySe(1, 0x40, 0x7F, 0);
					} else {
						if ((uVar4 & 0x100) != 0) {
							if (m_wmWorldState->m_cardChannel == 0) {
								m_wmWorldState->m_state0E = 1;
							} else {
								m_wmWorldState->m_state0E = -1;
							}
							m_wmWorldState->m_counter1A = 10;
							Sound.PlaySe(2, 0x40, 0x7F, 0);
						} else {
							if ((uVar4 & 0x200) != 0) {
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
				int chkRes = MemoryCardMan.McChkConnect(m_mcCtrl.GetDno());
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
			int uVar22 = 0;
			int uVar19;
			if (iVar10 == 0xD) { uVar19 = 7; }
			else if (iVar10 == 0x1A) { uVar19 = 0x1A; uVar22 = 1; }
			else { uVar19 = 9; }
			short windowWidth;
			short windowHeight;
			GetWinSize(uVar19, &windowWidth, &windowHeight, uVar22);
			SetMcWinInfo(windowWidth, windowHeight);
			m_menuWindowInfo->state = 0;
			m_mcCtrl.m_previousState = 0;
			m_mcCtrl.m_state = 0;
			m_mcCtrl.m_lastResult = 0;
			m_mcCtrl.m_iteration = 0;
			m_mcCtrl.m_userBuffer = 0;
			m_mcCtrl.m_createFlag = 0;
			if (m_wmWorldState->m_menuMode == 8
			    && m_cmakeWork != 0) {
				m_mcCtrl.m_userBuffer = m_cmakeWork;
			} else {
				m_mcCtrl.m_userBuffer = 0;
			}
			m_wmWorldState->m_flag09 = 1;
		} else if (m_menuWindowInfo->state == 1
		           && m_wmWorldState->m_counter1A == 0) {
			iVar10 = (int)m_wmWorldState->m_subState;
			if (iVar10 == 0xD) {
				short fmtRes = (short)GetMcCtrl()->Format(1);
				m_wmWorldState->m_mcResult = fmtRes;
				if (m_wmWorldState->m_mcResult < 0) {
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
				}
			} else if (iVar10 == 0x1A) {
				short erRes = (short)GetMcCtrl()->EraseDat();
				m_wmWorldState->m_mcResult = erRes;
				if (m_wmWorldState->m_mcResult < 0) {
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
				}
			} else {
				m_wmWorldState->m_mcResult = (short)GetMcCtrl()->LoadDat();
			}

			if (m_wmWorldState->m_mcResult != 0) {
				if (m_wmWorldState->m_mcResult < 0) {
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
				}
				if (m_wmWorldState->m_subState == 0x16) {
					if (m_wmWorldState->m_menuMode != 8 && m_wmWorldState->m_mcResult == 1) {
						s_Serial = m_mcCtrl.GetSerial();
						gWmMenuCursorX[0] = (unsigned char)m_mcCtrl.m_cardChannel;
						gWmMenuCursorX[1] = (unsigned char)m_mcCtrl.m_saveIndex;
					} else {
						gWmMenuCursorY[0] = (unsigned char)m_mcCtrl.m_cardChannel;
						gWmMenuCursorY[1] = (unsigned char)m_mcCtrl.m_saveIndex;
					}
					for (iVar14 = 0; iVar14 < kWmMenuPlayerCount; iVar14++) {
						WmCharaModelInfo* modelInfo = &m_wm.m_charaModelData[iVar14];
						if (m_wmWorldState->m_menuMode == 8
						    && m_cmakeWork != 0) {
							const Mc::CharaDat& character = m_cmakeWork->m_characters[iVar14];
							if (character.m_exists != 0) {
								unsigned int tribe = character.m_tribeId;
								unsigned int gender = character.m_genderFlag;
								unsigned int appearance = character.m_appearanceVariant;
								modelInfo->m_modelNo = GetModelNo(tribe, appearance, gender);
							} else {
								modelInfo->m_modelNo = -1;
							}
						} else if (Game.m_caravanWorkArr[iVar14].m_shopState != 0) {
							unsigned int tribe = Game.m_caravanWorkArr[iVar14].m_tribeId;
							unsigned int gender = Game.m_caravanWorkArr[iVar14].m_genderFlag;
							unsigned int appearance = Game.m_caravanWorkArr[iVar14].m_appearanceVariant;
							modelInfo->m_modelNo = GetModelNo(tribe, appearance, gender);
						} else {
							modelInfo->m_modelNo = -1;
						}
						modelInfo = &m_wm.m_charaModelData[iVar14];
						int charaId = modelInfo->m_modelNo;
						int uVar22;
						if (charaId < 0) {
							uVar22 = 3;
							modelInfo->m_modelChanged = 0;
							charaId = 0x43;
						} else {
							uVar22 = 0;
							modelInfo->m_modelChanged = 1;
						}
						GetWmCharaHandles(this)[iVar14]->LoadModelASync(uVar22, charaId, 0);
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
			m_mcCtrl.m_previousState = 0;
			m_mcCtrl.m_state = 0;
			m_mcCtrl.m_lastResult = 0;
			m_mcCtrl.m_iteration = 0;
			m_mcCtrl.m_userBuffer = 0;
			m_mcCtrl.m_createFlag = 0;
		}
		if (m_menuWindowInfo->state == 1
		    && m_wmWorldState->m_counter1A == 0) {
			short listRes = (short)GetMcCtrl()->LoadMcList();
			m_wmWorldState->m_mcResult = listRes;
			sVar8 = m_wmWorldState->m_mcResult;
			if (sVar8 == 0) {
				if (sVar8 < 0) {
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
				}
			} else {
				int iVar23 = 0;
				if (m_wmWorldState->m_menuMode == 8) {
					iVar23 = ChkMcDataCnt();
					if (iVar23 == 0) {
						m_wmWorldState->m_mcResult = (short)0xFC19;
					}
				}
				OSCalendarTime saveTimes[kMcListCount];
				OSCalendarTime* currentTime = saveTimes;
				iVar10 = 0;
				do {
					OSTicksToCalendarTime(m_wmCharaState[iVar10].m_saveTime,
					                      &currentTime[iVar10]);
					iVar10++;
				} while (iVar10 < 4);

				iVar23 = 0;
				int bestIdx = -1;
				for (; iVar23 < 4; iVar23++) {
					const McListInfo& entry = m_wmCharaState[iVar23];
					if (entry.m_isBroken == 0
					    && static_cast<int>(entry.m_scriptSysVal0) > 0) {
						if (bestIdx < 0) {
							bestIdx = iVar23;
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
							bestIdx = iVar23;
						}
					}
					currentTime++;
				}
				if (bestIdx < 0) bestIdx = 0;

				m_wmWorldState->m_cardChannel = (short)bestIdx;
				for (iVar10 = 0; iVar10 < 4; iVar10++) {
					const McListInfo& entry = m_wmCharaState[iVar10];
					if (entry.m_isBroken != 0) {
						m_mcCtrl.m_saveIndex = iVar10;
						m_wmWorldState->m_cardChannel = (short)iVar10;
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
		int chkRes = MemoryCardMan.McChkConnect(m_mcCtrl.GetDno());
		m_wmWorldState->m_mcResult = (short)chkRes;
		if (m_wmWorldState->m_mcResult == 0 && uVar7 != 0) {
			if ((uVar7 & 8) != 0) {
				if (m_wmWorldState->m_cardChannel <= 0) {
					m_wmWorldState->m_cardChannel = 3;
				} else {
					m_wmWorldState->m_cardChannel--;
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			} else {
				if ((uVar7 & 4) != 0) {
					if (m_wmWorldState->m_cardChannel >= 3) {
						m_wmWorldState->m_cardChannel = 0;
					} else {
						m_wmWorldState->m_cardChannel++;
					}
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				}
			}
			if ((uVar7 & 0xC) == 0) {
				if ((uVar4 & 0x100) != 0) {
					sVar8 = m_wmWorldState->m_state0E;
					if (sVar8 != -1 && sVar8 != 1) {
						iVar14 = (int)m_wmWorldState->m_cardChannel;
						const McListInfo& entry = m_wmCharaState[iVar14];
						if (entry.m_hasData == 0 || entry.m_isBroken != 0) {
							Sound.PlaySe(4, 0x40, 0x7F, 0);
						} else {
							m_mcCtrl.m_saveIndex = iVar14;
							m_wmWorldState->m_state0E = 1;
							Sound.PlaySe(2, 0x40, 0x7F, 0);
						}
					}
				}
				if ((uVar4 & 0x200) != 0) {
					sVar8 = m_wmWorldState->m_state0E;
					if (sVar8 != -1 && sVar8 != 1) {
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
 * PAL Address: 0x800fca2c
 * PAL Size: 1416b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcTitleMenu()
{

	static char* OPMOVIE_FNAME = "dvd/movie/ffcc_op.thp";

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
				param.m_paramB = reinterpret_cast<unsigned int>(titleObject);
				titleEffect->m_partNo = PartMng.pppCreate(0, 0x1F, &param, 1);
				m_wmWorldState->m_delay = 0;
				m_wmWorldState->m_worldReady = 1;
				m_wmWorldState->m_flag09 = 1;
				m_wmThpActive = 0;
				m_wmWorldState->m_titleState = 0;
				m_wmWorldState->m_state0E = -1;
				m_wmWorldState->m_state12 = 0;
				CFlatRuntime::CStack flatArgs[3];
				flatArgs[0].m_word = 9;
				flatArgs[1].m_word = 0;
				flatArgs[2].m_word = 0;
				gCFlatRuntime().SystemCall(0, 1, 4, 3, flatArgs, 0);
				m_wmWorldState->m_cardChannel = 0;
				lbl_8032EE1C = 0;
				return;
			}
			lbl_8032E8AC = 0;
			THPSimpleInit(1);
			THPSimpleOpen(OPMOVIE_FNAME);
			int thpMemory = THPSimpleCalcNeedMemory();
			m_wmWorkBuffer =
			    static_cast<unsigned char*>(Memory._Alloc(thpMemory, CharaPcs.m_loadStages[CCharaPcs::LOAD_STAGE_ANIM], "wm_menu.cpp", 0xABA, 0));
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
			param.m_paramB = reinterpret_cast<unsigned int>(titleObject);
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
 * PAL Address: UNUSED
 * PAL Size: 520b
 * EN Address: 0x8011CA28
 * EN Size: 340b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::IsAsyncCharaLoadFinish()
{
	int validCount = 0;
	if (m_cmakeWorkActive == 1) {
		for (int ci = 0; ci < kWmMenuPlayerCount; ci++) {
			if (m_cmakeWork->m_characters[ci].m_exists != 0) {
				validCount++;
			}
		}
	} else {
		for (int ci = 0; ci < kWmMenuPlayerCount; ci++) {
			if (Game.m_caravanWorkArr[ci].m_shopState != 0) {
				validCount++;
			}
		}
	}

	int loadedCount = 0;
	for (int i = 0; i < kWmMenuPlayerCount; i++) {
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

	const short menuAnim = m_wmWorldState->m_mainState;
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
				System.Printf("%s(%d): Error:WM menu no error(%d)\n", "wm_menu.cpp", 0xC59);
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
 * PAL Address: 0x800f673c
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::RestoreProjection()
{
	PSMTXCopy(m_wm.m_savedCameraMatrix, CameraPcs.m_cameraMatrix);
	GXSetCopyClear(Graphic.m_defaultCopyClearColor, 0x00FFFFFF);
	Mtx44 projectionMtx;
	PSMTX44Copy(CameraPcs.m_screenMatrix, projectionMtx);
	GXSetProjection(projectionMtx, GX_PERSPECTIVE);
	Graphic.SetViewport();
	GXSetScissor(0, 0, 0x280, 0x1C0);
	DrawInit();
}

/*
 * --INFO--
 * PAL Address: 0x800f3384
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1E));

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
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x33));

	float x = 32.0f;
	float y = 40.0f - x;
	MenuPcs.DrawRect(0, x, y, 288.0f, 184.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	MenuPcs.DrawRect(8, x + 288.0f, y, 288.0f, 184.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	y += 184.0f;
	x = 32.0f;
	MenuPcs.DrawRect(4, x, y, 288.0f, 184.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	x += 288.0f;
	MenuPcs.DrawRect(12, x, y, 288.0f, 184.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
}

/*
 * --INFO--
 * PAL Address: 0x800fb910
 * PAL Size: 1952b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
		const double* pHmm1 = &DOUBLE_803313F8;
		tileAlpha = static_cast<float>(static_cast<double>(tileAlpha) * *pHmm1);
		DrawMainMenuBase(tileAlpha);
	}

	DrawMainMenuSub();
	RestoreProjection();

	if (m_wmWorldState->m_mainState > 0 && m_wmWorldState->m_mainState < 4) {
		const int helpState = m_wmWorldState->m_mainState;
		double helpColorAlpha;
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
			MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
			const float* p255mm = &FLOAT_80331458;
			helpColorAlpha = static_cast<double>(*p255mm * helpAlpha);
			GXColor helpColor;
			helpColor.r = 0xFF;
			helpColor.g = 0xFF;
			helpColor.b = 0xFF;
			helpColor.a = static_cast<unsigned char>(static_cast<int>(helpColorAlpha));
			GXSetChanMatColor(static_cast<GXChannelID>(4), helpColor);
			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1F));
			const float* pZmm6 = &FLOAT_803313dc;
			const float* pOmm9 = &FLOAT_803313e8;
			const float* pWmm6 = &FLOAT_803313e0;
			const float* p440mm = &FLOAT_80331440;
			const double* pBmm1 = &DOUBLE_803314D0;
			MenuPcs.DrawRect(0, *pZmm6, static_cast<float>(*pBmm1 - static_cast<double>(*p440mm)),
			                 *pWmm6, *p440mm, *pZmm6, *pZmm6, *pOmm9, *pOmm9, *pZmm6);

			char* textList[5] = {0};
			const int languageIndex = Game.m_gameWork.m_languageId - 1;
			char** const langText = g_strWMMenuMes[languageIndex];
			for (int i = 0; i < 5; i++) {
				textList[i] = langText[i];
			}
			unsigned int textAlpha;
			if (helpAlpha > FLOAT_803313e8) {
				textAlpha = 0xFF;
			} else {
				textAlpha = static_cast<unsigned int>(static_cast<int>(helpColorAlpha));
			}
			CColor textColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(textAlpha & 0xFF));
			char* const text = textList[m_wmWorldState->m_cardChannel];
			const float* pWt1 = &FLOAT_80331594;
			const float* pHt1 = &FLOAT_803313e8;
			const int x = static_cast<int>(CalcCenteringPos2(text, *pWt1, *pHt1));
			const float* pYt1 = &FLOAT_803317D0;
			const float* pWt2 = &FLOAT_80331594;
			const float* pHt2 = &FLOAT_803313e8;
			DrawFont2(x, static_cast<int>(*pYt1), textColor.color, 7, text,
			          *pWt2, *pHt2, *pHt2);
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
	PSMTX44Copy(projectionMtx, CameraPcs.m_screenMatrix);

	Mtx lookAtMtx;
	C_MTXLookAt(lookAtMtx, &slot->m_cameraPosition,
	    CVector(FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313dc),
	    CVector(FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313dc));
	PSMTXCopy(CameraPcs.m_cameraMatrix, m_wm.m_savedCameraMatrix);
	PSMTXCopy(lookAtMtx, CameraPcs.m_cameraMatrix);

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
 * PAL Address: UNUSED
 * PAL Size: 524b
 * EN Address: 0x8011AACC
 * EN Size: 680b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::DrawPageMark()
{
	const int phase = abs(static_cast<int>(System.m_frameCounter) % 20 - 10);
	const float scale = static_cast<float>(0.03 * phase + 0.7);
	float x = 220.0 - 40.0f;
	float y = 369.0f;
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXColor color;
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = static_cast<unsigned char>(static_cast<int>(
	    255.0f * static_cast<float>(0.05 * phase + 0.5)));
	GXSetChanMatColor(GX_COLOR0A0, color);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x2B));

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
 * PAL Address: 0x800fb440
 * PAL Size: 1232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawDiaryMenu()
{
	GetWmWorldHandles(this)[1]->m_model->m_lightAlpha = FLOAT_803313e8;
	{
		SetProjection(1);
		GetWmWorldHandles(this)[1]->Draw(5);
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
 * PAL Size: 804b
 * EN Address: 0x8011A654
 * EN Size: 228b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::DrawMcObj()
{
	WmWorldObjInfo* view = &m_wm.m_worldObjData[17];
	for (int i = 0; i < 4; i++, view++) {
		if (view->m_active != 0) {
			SetProjection(i + 17);
			SetLight(0);
			m_wm.m_handles[i + 17]->Draw(5);
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
 * PAL Address: 0x800fa1cc
 * PAL Size: 4724b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
			const float* p255 = &FLOAT_80331458;
			MenuPcs.SetAttrFmt((FMT)0);
			_GXColor bgColor;
			bgColor.r = 0xFF;
			bgColor.g = 0xFF;
			bgColor.b = 0xFF;
			bgColor.a = (unsigned char)(int)(*p255 * alpha);
			GXSetChanMatColor(GX_COLOR0A0, bgColor);
			MenuPcs.SetTexture((TEX)0x1F);
			const float* pZeroBg = &FLOAT_803313dc;
			const float* pOneBg = &FLOAT_803313e8;
			const float* pWideBg = &FLOAT_803313e0;
			const float* p40Bg = &FLOAT_80331440;
			const double* pBottomBg = &DOUBLE_803314D0;
			MenuPcs.DrawRect(0, *pZeroBg,
			         (float)(*pBottomBg - (double)*p40Bg),
			         *pWideBg, *p40Bg,
			         *pZeroBg, *pZeroBg,
			         *pOneBg, *pOneBg, *pZeroBg);
		}
	}

	DrawMCList();

	if (m_wmWorldState->m_mainState == 2 && m_wmWorldState->m_subState >= 0x11) {
		const float* pD8 = &FLOAT_803314D8;
		const double* pCursOff = &DOUBLE_803317D8;
		const float* p32c = &FLOAT_80331410;
		cursorY = (float)((double)*pD8 - *pCursOff);
		float cursorXbase = *pD8 + *p32c;
		unsigned int saveIdx;
		if (m_wmWorldState->m_subState == 0x11) {
			saveIdx = (unsigned int)m_wmWorldState->m_cardChannel;
		} else {
			saveIdx = (unsigned int)m_mcCtrl.GetSlot();
		}
		const double* pStride = &DOUBLE_80331498;
		cursorX = (float)(*pStride * (double)(int)saveIdx + (double)cursorXbase);
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
				float rectY = (float)((int)m_menuWindowInfo->y + m_menuWindowInfo->height - 0x3e);
				float rectX = (float)GetSlotABXPos((int)m_wmWorldState->m_cardChannel);
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
					m_wmWorldState->m_cardChannel = (short)m_mcCtrl.m_saveIndex;
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
				int msgId;
				short ss = m_wmWorldState->m_subState;
				if (ss == 8) msgId = 4;
				else if (ss == 0x0B) msgId = 5;
				else if (ss == 0x19) { msgId = 0x19; msgParam = 1; }
				else msgId = 0x12;
				DrawMcWinMess(msgId, msgParam);
				float rectY = (float)((int)m_menuWindowInfo->y + m_menuWindowInfo->height - 0x3e);
				float rectX = (float)GetYesNoXPos((int)m_wmWorldState->m_cardChannel);
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
						m_wmWorldState->m_cardChannel = (short)m_mcCtrl.m_saveIndex;
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
							m_wmWorldState->m_cardChannel = (short)m_mcCtrl.m_saveIndex;
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
					int __p7 = idx;
					if (__p7 < 4) {
						m_wmWorldState->m_subState = 0x19;
					} else {
						m_wmWorldState->m_subState = 0x11;
					}
					m_wmWorldState->m_cardChannel = (short)m_mcCtrl.m_saveIndex;
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
				} else if (m_wmCharaState[m_mcCtrl.m_saveIndex].m_hasData == 0) {
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
	} else if (m_wmWorldState->m_delay != 0) {
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
		MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
		GXColor helpColor;
		helpColor.r = 0xFF;
		helpColor.g = 0xFF;
		helpColor.b = 0xFF;
		const float* p255b = &FLOAT_80331458;
		helpColor.a = static_cast<unsigned char>(static_cast<int>(*p255b * contentAlpha));
		GXSetChanMatColor(static_cast<GXChannelID>(4), helpColor);
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1F));
		const float* pZeroR = &FLOAT_803313dc;
		const float* pOneR = &FLOAT_803313e8;
		const float* pWideR = &FLOAT_803313e0;
		const float* pFortyR = &FLOAT_80331440;
		const double* pBottomR = &DOUBLE_803314D0;
		MenuPcs.DrawRect(0, *pZeroR, static_cast<float>(*pBottomR - static_cast<double>(*pFortyR)),
		         *pWideR, *pFortyR, *pZeroR, *pZeroR, *pOneR, *pOneR, *pZeroR);
		if (m_wmWorldState->m_menuMode == 3) {
			if (m_wmWorldState->m_menuMode == 3) {
			const int textIndex = static_cast<int>(m_wmHelpTimer / 0x4B);
			char* textList[3] = {0};
			char** const langText = g_strWMMenuMes[Game.m_gameWork.m_languageId - 1];
			for (int i = 0; i < 3; i++) {
				textList[i] = langText[i + 5];
			}
			const _GXColor textColor = CColor(0xFF, 0xFF, 0xFF, static_cast<signed char>(textAlpha & 0xFF)).color;
			char* const text = textList[textIndex];
			const float* pW1 = &FLOAT_80331594;
			const float* pH1 = &FLOAT_803313e8;
			const int x = static_cast<int>(CalcCenteringPos2(text, *pW1, *pH1));
			const float* pY1 = &FLOAT_803317D0;
			const float* pW1b = &FLOAT_80331594;
			const float* pH1b = &FLOAT_803313e8;
			DrawFont2(x, static_cast<int>(*pY1), textColor, 7, text,
			          *pW1b, *pH1b, *pH1b);
			}
		} else if (m_wmWorldState->m_menuMode == 8) {
			const int mainMode = g_pGoOutMenu->m_mainMode;
			switch (mainMode) {
			case 2:
				switch (g_pGoOutMenu->m_goOutMode) {
				case 0x0E: {
					char** const caseText = g_strWMMenuMes[Game.m_gameWork.m_languageId - 1];
				unsigned int ci = 8;
				char* const text = caseText[ci];
					_GXColor textColor = CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(textAlpha & 0xFF)).color;
					const float* pWc = &FLOAT_80331594;
					const float* pHc = &FLOAT_803313e8;
					const int x = static_cast<int>(MenuPcs.CalcCenteringPos2(text, *pWc, *pHc));
					const float* pYc = &FLOAT_803317D0;
					const float* pWc2 = &FLOAT_80331594;
					const float* pHc2 = &FLOAT_803313e8;
					MenuPcs.DrawFont2(x, static_cast<int>(*pYc), textColor, 7, text,
					                  *pWc2, *pHc2, *pHc2);
					break;
				}
				case 0x0F: {
					char** const caseText = g_strWMMenuMes[Game.m_gameWork.m_languageId - 1];
				unsigned int ci = 9;
				char* const text = caseText[ci];
					_GXColor textColor = CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(textAlpha & 0xFF)).color;
					const float* pWc = &FLOAT_80331594;
					const float* pHc = &FLOAT_803313e8;
					const int x = static_cast<int>(MenuPcs.CalcCenteringPos2(text, *pWc, *pHc));
					const float* pYc = &FLOAT_803317D0;
					const float* pWc2 = &FLOAT_80331594;
					const float* pHc2 = &FLOAT_803313e8;
					MenuPcs.DrawFont2(x, static_cast<int>(*pYc), textColor, 7, text,
					                  *pWc2, *pHc2, *pHc2);
					break;
				}
				}
				break;
			case 3:
				switch (g_pGoOutMenu->m_deleteMode) {
				case 2: {
					char** const caseText = g_strWMMenuMes[Game.m_gameWork.m_languageId - 1];
				unsigned int ci = 10;
				char* const text = caseText[ci];
					_GXColor textColor = CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(textAlpha & 0xFF)).color;
					const float* pWc = &FLOAT_80331594;
					const float* pHc = &FLOAT_803313e8;
					const int x = static_cast<int>(MenuPcs.CalcCenteringPos2(text, *pWc, *pHc));
					const float* pYc = &FLOAT_803317D0;
					const float* pWc2 = &FLOAT_80331594;
					const float* pHc2 = &FLOAT_803313e8;
					MenuPcs.DrawFont2(x, static_cast<int>(*pYc), textColor, 7, text,
					                  *pWc2, *pHc2, *pHc2);
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
				Sound.PlaySe(0x31 + (static_cast<int>(m_wmWorldState->m_nextMenuMode) >> 31), 0x40, 0x7F, 0);
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
		MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
		GXColor helpColor;
		helpColor.r = 0xFF;
		helpColor.g = 0xFF;
		helpColor.b = 0xFF;
		helpColor.a = static_cast<unsigned char>(static_cast<int>(FLOAT_80331458 * moveAlpha));
		GXSetChanMatColor(static_cast<GXChannelID>(4), helpColor);
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x23));
		MenuPcs.DrawRect(0, FLOAT_803313dc, static_cast<float>(DOUBLE_803314D0 - static_cast<double>(FLOAT_80331440)),
		         FLOAT_803313e0, FLOAT_80331440, FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
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
		CFlatRuntime::CStack stackData[3];
		stackData[0].m_word = 3;
		stackData[1].m_word = 0;
		stackData[2].m_word = 0;
		gCFlatRuntime().SystemCall(0, 1, 4, 3, stackData, 0);
	} else if (m_wmWorldState->m_mainState == 2 && m_wmWorldState->m_frameCounter >= 10) {
		m_wmWorldState->m_mainState++;
		m_wmWorldState->m_frameCounter = 0;
	} else if (m_wmWorldState->m_mainState == 3 && m_wmWorldState->m_frameCounter >= 10) {
		m_wmWorldState->m_mainState++;
		m_wmWorldState->m_frameCounter = 0;
		CFlatRuntime::CStack stackData[3];
		stackData[0].m_word = 4;
		stackData[1].m_word = 0;
		stackData[2].m_word = 0;
		gCFlatRuntime().SystemCall(0, 1, 4, 3, stackData, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800f7efc
 * PAL Size: 4940b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
			MenuPcs.SetAttrFmt((FMT)0);
			_GXColor bgColor;
			bgColor.r = 0xFF;
			bgColor.g = 0xFF;
			bgColor.b = 0xFF;
			bgColor.a = static_cast<unsigned char>(static_cast<int>(FLOAT_80331458 * alpha));
			GXSetChanMatColor(GX_COLOR0A0, bgColor);
			MenuPcs.SetTexture((TEX)0x1F);
			MenuPcs.DrawRect(0, FLOAT_803313dc, static_cast<float>(DOUBLE_803314D0 - static_cast<double>(FLOAT_80331440)),
			         FLOAT_803313e0, FLOAT_80331440,
			         FLOAT_803313dc, FLOAT_803313dc,
			         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
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
	if (*reinterpret_cast<char*>(reinterpret_cast<int>(g_pGoOutMenu) + 0x18) == 0x0E) {
		const int languageIndex = Game.m_gameWork.m_languageId - 1;
		char* text = g_strWMMenuMes[languageIndex][8];
		_GXColor color = CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(uAlpha)).color;
		const int x = static_cast<int>(MenuPcs.CalcCenteringPos2(text, FLOAT_80331594, FLOAT_803313e8));
		MenuPcs.DrawFont2(x, static_cast<int>(FLOAT_803317D0), color, 7, text,
		                  FLOAT_80331594, FLOAT_803313e8, FLOAT_803313e8);
	}

	DrawMCList();

	// Cursor / selection rendering
	state = m_wmWorldState->m_mainState;
	if (state == 2 && m_wmWorldState->m_subState >= 0x11) {
		float cursorY0;
		cursorY0 = FLOAT_803314D8;
		cursorXbase = cursorY0;
		cursorY0 = static_cast<float>(static_cast<double>(cursorY0) - DOUBLE_803317D8);
		cursorXbase = cursorXbase + FLOAT_80331410;
		unsigned int saveIdx;
		if (m_wmWorldState->m_subState == 0x11) {
			saveIdx = static_cast<unsigned int>(m_wmWorldState->m_cardChannel);
		} else {
			saveIdx = static_cast<unsigned int>(mcCtrl.m_saveIndex);
		}
		double rawIdx;
		reinterpret_cast<int*>(&rawIdx)[0] = 0x43300000;
		reinterpret_cast<int*>(&rawIdx)[1] = saveIdx ^ 0x80000000;
		cursorXbase = static_cast<float>(DOUBLE_80331498 * (rawIdx - DOUBLE_80331408) + static_cast<double>(cursorXbase));
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
				float slotY = (float)((int)m_menuWindowInfo->y + m_menuWindowInfo->height - 0x3e);
				float slotX = (float)GetSlotABXPos(m_wmWorldState->m_cardChannel);
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
				short ys = m_wmWorldState->m_subState;
				if (ys == 8) ymsgId = 4;
				else if (ys == 0x19) { ymsgId = 0x19; ymsgParam = 1; }
				else ymsgId = 5;
				DrawMcWinMess(ymsgId, ymsgParam);

				// Yes/No cursor
				float ynY = (float)((int)m_menuWindowInfo->y + m_menuWindowInfo->height - 0x3e);
				float ynX = (float)GetYesNoXPos(m_wmWorldState->m_cardChannel);
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
 * PAL Address: 0x800f7044
 * PAL Size: 3768b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawTitleMenu()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	int state = m_wmWorldState->m_mainState;

		if (state == 0 && static_cast<signed char>(m_wmWorldState->m_worldReady) != 0) {
			if (static_cast<signed char>(m_wmThpActive) != 0) {
				THPSimpleDrawCurrentFrame((_GXRenderModeObj*)Graphic.m_renderMode, 0, 0, 0x280, 0x1C0);
				Graphic._WaitDrawDone("wm_menu.cpp", 0x12A2);
			}
		short sVarE = m_wmWorldState->m_state0E;
		if (sVarE != 0 || m_wmWorldState->m_frameCounter >= 0xB43) {
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
			CFlatRuntime::CStack flatArgs[3];
			flatArgs[0].m_word = 9;
			flatArgs[1].m_word = 0;
			flatArgs[2].m_word = 0;
			gCFlatRuntime().SystemCall(0, 1, 4, 3, flatArgs, 0);
		}
	} else {
		// 3D viewport setup
		GXColor matColor;
		Mtx44 projMtx;
		C_MTXPerspective(projMtx, FLOAT_80331470, FLOAT_80331474, FLOAT_80331478, FLOAT_8033147c);
		GXSetProjection(projMtx, GX_PERSPECTIVE);
		PSMTX44Copy(projMtx, CameraPcs.m_screenMatrix);

		Vec eye;
		eye.x = FLOAT_803313dc;
		eye.y = FLOAT_803313dc;
		eye.z = FLOAT_80331768;
		Mtx lookAtMtx;
		C_MTXLookAt(lookAtMtx, &eye,
		            CVector(FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313dc),
		            CVector(FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313dc));
		PSMTXCopy(CameraPcs.m_cameraMatrix, m_wm.m_savedCameraMatrix);
		PSMTXCopy(lookAtMtx, CameraPcs.m_cameraMatrix);
		CharaPcs.InitEnv(5);
		GXSetColorUpdate(0);
		GXSetAlphaUpdate(0);
		_GXColor clearGxColor = CColor(0, 0, 0, 0).color;
		GXSetCopyClear(clearGxColor, 0xFFFFFF);
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
				SetAttrFmt((FMT)2);
			matColor.r = 0xFF;
			matColor.g = 0xFF;
			matColor.b = 0xFF;
			matColor.a = static_cast<unsigned char>(static_cast<int>(FLOAT_80331458 * fadeAlpha));
			GXSetChanMatColor(GX_COLOR0A0, matColor);
			MenuPcs.SetTexture((TEX)0xFFFFFFFF);
			_GXSetBlendMode(static_cast<_GXBlendMode>(1), static_cast<_GXBlendFactor>(4), static_cast<_GXBlendFactor>(5), static_cast<_GXLogicOp>(1));
			GXBegin(GX_QUADS, GX_VTXFMT0, 4);
			GXPosition3f32(FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313dc);
			GXPosition3f32(FLOAT_803313e0, FLOAT_803313dc, FLOAT_803313dc);
			GXPosition3f32(FLOAT_803313e0, FLOAT_803313e4, FLOAT_803313dc);
			GXPosition3f32(FLOAT_803313dc, FLOAT_803313e4, FLOAT_803313dc);
		}

		// Menu items
		MenuPcs.SetAttrFmt((FMT)0);
		MenuPcs.SetTexture((TEX)0x43);

		state = m_wmWorldState->m_mainState;
		if (state >= 2) {
			float fX = FLOAT_80331778 - FLOAT_80331414;
			float fY = FLOAT_8033177C;
			if (m_wmWorldState->m_cardChannel != 0) {
				fY = FLOAT_8033177C + (float)(m_wmWorldState->m_cardChannel * 0x28 - 8);
			}
			float fYRect = fY - FLOAT_80331780;
			float alpha;
			if (state == 2 && m_wmWorldState->m_state12 == 0) {
				int timer = (int)m_wmWorldState->m_titleState;
				fX = static_cast<float>(-(DOUBLE_80331790 *
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
			MenuPcs.DrawRect(0, fX, fYRect,
			         FLOAT_80331568, FLOAT_80331554,
			         FLOAT_803313dc, FLOAT_803313dc,
			         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
			_GXSetBlendMode(static_cast<_GXBlendMode>(1), static_cast<_GXBlendFactor>(4), static_cast<_GXBlendFactor>(1), static_cast<_GXLogicOp>(5));
			state = m_wmWorldState->m_mainState;
			float secondAlpha = alpha;
			fX = FLOAT_80331778 - FLOAT_80331414;
			if (state == 2 && m_wmWorldState->m_state12 == 0) {
				int timer = (int)m_wmWorldState->m_titleState;
				fX = static_cast<float>(DOUBLE_80331790 *
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
			MenuPcs.DrawRect(0, fX, fYRect,
			         FLOAT_80331568, FLOAT_80331554,
			         FLOAT_803313dc, FLOAT_80331554,
			         FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
			_GXSetBlendMode(static_cast<_GXBlendMode>(1), static_cast<_GXBlendFactor>(4), static_cast<_GXBlendFactor>(5), static_cast<_GXLogicOp>(1));
		}

		// Menu item labels (2 items: New Game, Continue)
		MenuPcs.SetAttrFmt((FMT)0);
		const float kColorScale = FLOAT_80331458;
		const float kZero = FLOAT_803313dc;
		unsigned int uVar7 = 0xFFFFFFF8;
		unsigned int uVar6 = 0x70;
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
				yPos = yPos + (float)((int)uVar7);
			}
			MenuPcs.DrawRect(0, FLOAT_80331778, yPos,
			         FLOAT_80331568, FLOAT_80331440,
			         kZero, (float)((int)uVar6),
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
				float cursorX = static_cast<float>((FLOAT_803313e0 - FLOAT_80331568 * cursorScale) * DOUBLE_803313F8);
				float cursorY = FLOAT_8033177C - (FLOAT_80331440 * cursorScale - FLOAT_80331440);
				if (i != 0) {
					cursorY = cursorY + (float)((int)uVar7);
				}
				MenuPcs.DrawRect(0,
				         cursorX,
				         cursorY,
				         FLOAT_80331568, FLOAT_80331440,
				         kZero, (float)((int)uVar6),
				         cursorScale, cursorScale, kZero);
			}
			uVar7 += 0x28;
			uVar6 += 0x28;
		}

		// Logo and copyright textures
		MenuPcs.SetAttrFmt((FMT)0);
		matColor.r = 0xFF;
		matColor.g = 0xFF;
		matColor.b = 0xFF;
		matColor.a = 0xFF;
		GXSetChanMatColor(GX_COLOR0A0, matColor);
		MenuPcs.SetTexture((TEX)0x42);
		MenuPcs.DrawRect(0, FLOAT_803317B8, FLOAT_803317BC, FLOAT_803317C0, FLOAT_803315B4,
		         FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);

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
			SetAttrFmt((FMT)2);
			matColor.r = 0;
			matColor.g = 0;
			matColor.b = 0;
			matColor.a = static_cast<unsigned char>(static_cast<int>(FLOAT_80331458 * fadeAlpha2));
			GXSetChanMatColor(GX_COLOR0A0, matColor);
			MenuPcs.SetTexture((TEX)0xFFFFFFFF);
			_GXSetBlendMode(static_cast<_GXBlendMode>(1), static_cast<_GXBlendFactor>(4), static_cast<_GXBlendFactor>(5), static_cast<_GXLogicOp>(1));
			GXBegin(GX_QUADS, GX_VTXFMT0, 4);
			GXPosition3f32(FLOAT_803313dc, FLOAT_803313dc, FLOAT_803313dc);
			GXPosition3f32(FLOAT_803313e0, FLOAT_803313dc, FLOAT_803313dc);
			GXPosition3f32(FLOAT_803313e0, FLOAT_803313e4, FLOAT_803313dc);
			GXPosition3f32(FLOAT_803313dc, FLOAT_803313e4, FLOAT_803313dc);
		}

		// End state handling
		state = m_wmWorldState->m_mainState;
		if (state == 3 && m_wmWorldState->m_frameCounter >= 0xA) {
			PartMng.pppDeletePart(m_effectWork[23].m_partNo);
			if (m_wmWorldState->m_state0E != 0) {
				lbl_8032E8AC = 1;
				m_wmWorldState->m_changeRequest = 1;
				CFlatRuntime::CStack flatArgs2[3];
				flatArgs2[0].m_word = 7;
				flatArgs2[1].m_word = static_cast<int>(m_wmWorldState->m_cardChannel);
				flatArgs2[2].m_word = 0;
				gCFlatRuntime().SystemCall(0, 1, 4, 3, flatArgs2, 0);
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
					CFlatRuntime::CStack flatArgs3[3];
					flatArgs3[0].m_word = 9;
					flatArgs3[1].m_word = 1;
					flatArgs3[2].m_word = 0;
					gCFlatRuntime().SystemCall(0, 1, 4, 3, flatArgs3, 0);
				}
			} else if (m_wmWorldState->m_delay == 0 && m_wmWorldState->m_frameCounter >= 0x992) {
				m_wmWorldState->m_state0E = 0;
				m_wmWorldState->m_mainState++;
				m_wmWorldState->m_frameCounter = 0;
				m_wmWorldState->m_titleState = 0;
				CFlatRuntime::CStack flatArgs4[3];
				flatArgs4[0].m_word = 9;
				flatArgs4[1].m_word = 1;
				flatArgs4[2].m_word = 0;
				gCFlatRuntime().SystemCall(0, 1, 4, 3, flatArgs4, 0);
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800f6d70
 * PAL Size: 724b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetWorldParam(int code, int value)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	switch (code) {
	case 0: {
		bytes[5] = bytes[4];
		bytes[4] = static_cast<unsigned char>(value);
		bytes[0xA] = 1 | bytes[0xA];
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
		bytes[0xA] = 2 | bytes[0xA];
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
		mc->m_previousState = 0;
		mc->m_state = 0;
		mc->m_lastResult = 0;
		mc->m_iteration = 0;
		mc->m_userBuffer = 0;
		mc->m_createFlag = 0;
		mc->m_cardChannel = static_cast<int>(static_cast<signed char>(bytes[0x17]));
		bytes[0x18] = 0x12;
		break;
	}
	case 0x13: {
		McCtrl* mc = GetMcCtrl();
		mc->m_previousState = 0;
		mc->m_state = 0;
		mc->m_lastResult = 0;
		mc->m_iteration = 0;
		mc->m_userBuffer = 0;
		mc->m_createFlag = 0;
		mc->m_cardChannel = static_cast<int>(static_cast<signed char>(bytes[0x17]));
		bytes[0x18] = 0x13;
		break;
	}
	case 0x14:
		MemoryCardMan.McEnd();
		bytes[0x14] = 1;
		break;
	case 0x16:
		bytes[0x15] = 1;
		changeMode(static_cast<MENUMODE>(2));
		bytes[0x15] = 1;
		break;
	case 0x17: {
		const unsigned int disabled = value == 0;
		CameraPcs.m_worldMapEffect.m_flags =
		    static_cast<unsigned char>(disabled << 7) |
		    (CameraPcs.m_worldMapEffect.m_flags & 0x7F);
		CameraPcs.m_worldMapEffect.m_timer = 0x4B;
		CameraPcs.m_worldMapEffect.m_duration = 0x4B;
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
	case 0x1a: {
		int i = 0;
		do {
			GbaQue.SetRadarMode(i, 0);
			i = i + 1;
		} while (i < 4);
		break;
	}
	case 0x1b:
		GbaQue.SetControllerMode(value ? 1 : 0);
		break;
	default:
		if (static_cast<unsigned int>(System.m_execParam) >= 1) {
			System.Printf("%s(%d): Error:function code not found(%d)\n", "wm_menu.cpp", 0x1482, code);
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
		int iVar1;
		int iVar3 = 0;
		do {
			iVar1 = MemoryCardMan.McChkConnect(0);
			if (iVar1 != 1) break;
			iVar3 = iVar3 + 1;
		} while (iVar3 < 10);
		if (iVar1 == 0) {
			result = result | 1;
		} else if (iVar1 == 1) {
			result = result | 7;
		} else if (iVar1 != -1) {
			if (iVar1 == -2) {
				result = result | 2;
			} else if (iVar1 == -3) {
				result = result | 3;
			} else {
				result = result | 6;
			}
		}
		iVar3 = 0;
		do {
			iVar1 = MemoryCardMan.McChkConnect(1);
			if (iVar1 != 1) break;
			iVar3 = iVar3 + 1;
		} while (iVar3 < 10);
		if (iVar1 == 0) {
			result = result | 0x10;
		} else if (iVar1 == 1) {
			result = result | 0x70;
		} else if (iVar1 != -1) {
			if (iVar1 == -2) {
				result = result | 0x20;
			} else if (iVar1 == -3) {
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
	float threeU2 = FLOAT_803314c4 * u2;
	float negTerm = -(FLOAT_803314c8 * u2 - u3);

	return span * (prev->outTangent * (u + negTerm) + next->inTangent * (u3 - u2)) +
	       (prev->value * (FLOAT_803313e8 + (FLOAT_803314c8 * u3 - threeU2)) +
	           next->value * (FLOAT_803314cc * u3 + threeU2));
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
				result = CalcSpl(&keys[idx - 1], &keys[idx], t);
			}
			break;
		}
	}
	return result;
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
 * PAL Address: 0x800f554c
 * PAL Size: 4080b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcFukidashi()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	if ((char)bytes[0x09] != 1) {
		return;
	}
	int bitIdx;

	m_wm.m_bubbleData->m_sprites[0].m_x = *reinterpret_cast<short*>(bytes + 0x1C);
	float fVar1 = FLOAT_803313dc;
	m_wm.m_bubbleData->m_sprites[0].m_y = *reinterpret_cast<short*>(bytes + 0x1E);
	m_wm.m_bubbleData->m_sprites[0].m_width = 0xF0;
	m_wm.m_bubbleData->m_sprites[0].m_height = 0xC4;
	m_wm.m_bubbleData->m_sprites[0].m_v = fVar1;
	if ((char)bytes[0x08] == 2 || (char)bytes[0x08] == 3) {
		m_wm.m_bubbleData->m_sprites[0].m_u = FLOAT_803313dc;
	} else {
		m_wm.m_bubbleData->m_sprites[0].m_u = FLOAT_80331704;
	}

	fVar1 = FLOAT_80331708;
	if ((*reinterpret_cast<short*>(bytes + 0x1A) & 0x3F0) != 0) {
		m_wm.m_bubbleData->m_sprites[1].m_width = 0x50;
		float fVar2 = FLOAT_803313dc;
		m_wm.m_bubbleData->m_sprites[1].m_height = 0x48;
		m_wm.m_bubbleData->m_sprites[1].m_u = fVar1;
		m_wm.m_bubbleData->m_sprites[1].m_v = fVar2;
		m_wm.m_bubbleData->m_sprites[1].m_y = m_wm.m_bubbleData->m_sprites[0].m_y + 0x1C;
		if ((char)bytes[0x08] == 2 || (char)bytes[0x08] == 3) {
			m_wm.m_bubbleData->m_sprites[1].m_y = m_wm.m_bubbleData->m_sprites[1].m_y + 0x10;
		}
		m_wm.m_bubbleData->m_sprites[1].m_x = m_wm.m_bubbleData->m_sprites[0].m_x;
		if ((*reinterpret_cast<short*>(bytes + 0x1A) & 0xF) != 0) {
			m_wm.m_bubbleData->m_sprites[1].m_x = m_wm.m_bubbleData->m_sprites[1].m_x + 0x20;
		} else if ((*reinterpret_cast<short*>(bytes + 0x1A) & 0x200) != 0) {
			m_wm.m_bubbleData->m_sprites[1].m_x = m_wm.m_bubbleData->m_sprites[1].m_x + 0x50;
		} else {
			m_wm.m_bubbleData->m_sprites[1].m_x = m_wm.m_bubbleData->m_sprites[1].m_x + 0x38;
		}
	}

	fVar1 = FLOAT_803313dc;
	if ((*reinterpret_cast<short*>(bytes + 0x1A) & 0x1FF) != 0) {
		m_wm.m_bubbleData->m_sprites[2].m_width = 0x20;
		m_wm.m_bubbleData->m_sprites[2].m_height = 0x20;
		m_wm.m_bubbleData->m_sprites[2].m_u = fVar1;
		m_wm.m_bubbleData->m_sprites[2].m_v = fVar1;

		m_wm.m_bubbleData->m_sprites[3] = m_wm.m_bubbleData->m_sprites[2];

		short flagsF = *reinterpret_cast<short*>(bytes + 0x1A);
		int cnt = 0;
		WmBubbleInfo* bubble = m_wm.m_bubbleData;
		int sVar15 = bubble->m_sprites[1].m_x + bubble->m_sprites[1].m_width;
		if ((flagsF & 0xF) != 0) {
			bubble->m_sprites[3].m_x = sVar15;
			m_wm.m_bubbleData->m_sprites[2].m_x = sVar15;
			for (bitIdx = 0; bitIdx < 4; bitIdx++) {
				if (((int)*reinterpret_cast<short*>(bytes + 0x1A) & (1 << bitIdx)) != 0) {
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
			bubble->m_sprites[3].m_x = sVar15 + 8;
			m_wm.m_bubbleData->m_sprites[2].m_x = sVar15 + 8;
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
	char tempBuf[64];
	char secondLine[64];
	int fieldVal = (int)(char)bytes[0x07];
	if (fieldVal == 0x0F) {
		strcpy(nameBuffer, Game.m_gameWork.m_townName);
	} else if (fieldVal == 0x16) {
		int languageId = Game.m_gameWork.m_languageId;
		if (languageId == 2) {
			strcpy(nameBuffer, Game.m_gameWork.m_townName);
			strcat(nameBuffer, s_port[languageId - 1]);
		} else {
			strcpy(nameBuffer, s_port[languageId - 1]);
			strcat(nameBuffer, Game.m_gameWork.m_townName);
		}
	} else {
		strcpy(nameBuffer, Game.m_cFlatDataArr[1].TableStrings(3)[fieldVal]);
	}
	if (nameBuffer[0] != '\0') {
		nameBuffer[0] = static_cast<char>(toupperLatin1(static_cast<unsigned char>(nameBuffer[0])));
	}

	int textWidth = 0xD8;
	if (*reinterpret_cast<short*>(bytes + 0x1A) != 0) {
		textWidth = 0xA2;
	}
	if (ChkPlaceLength(nameBuffer, textWidth)) {
		SplitPlace(nameBuffer, tempBuf, secondLine);
		strcpy(nameBuffer, tempBuf);
	}
	float nameWidthF = fontFC->GetWidth(nameBuffer);

	int sVar15 = 0x4C;
	m_wm.m_bubbleData->m_sprites[4].m_x =
	    static_cast<short>(static_cast<int>(
	        (FLOAT_80331704 - nameWidthF) * FLOAT_80331434 +
	        static_cast<float>(static_cast<int>(m_wm.m_bubbleData->m_sprites[0].m_x))));
	float fVar2 = FLOAT_803314A4;
	fVar1 = FLOAT_803313dc;
	unsigned short uVar3 = *reinterpret_cast<short*>(bytes + 0x1A);
	if ((uVar3 & 0x3F0) != 0) {
		sVar15 = 0x6C;
	}
	if ((char)bytes[0x08] == 2 || (char)bytes[0x08] == 3) {
		sVar15 = sVar15 + 0x10;
	}

	// Set text position
	m_wm.m_bubbleData->m_sprites[4].m_y =
	    m_wm.m_bubbleData->m_sprites[0].m_y + sVar15;
	m_wm.m_bubbleData->m_sprites[4].m_y =
	    m_wm.m_bubbleData->m_sprites[4].m_y - 4;

	// Setup model viewport slots
	int sVar15b = m_wm.m_bubbleData->m_sprites[0].m_x - 0x28;
	int sVar22 = m_wm.m_bubbleData->m_sprites[0].m_y - 0x0E;
	for (int i = 6; i <= 16; i++) {
		WmWorldObjInfo* slot = &m_wm.m_worldObjData[i];
		slot->m_active = 0;
		slot->m_viewportX = sVar15b;
		slot->m_viewportY = sVar22;
		slot->m_viewportWidth = 0x140;
		slot->m_viewportHeight = 0xE0;
		slot->m_cameraPosition.x = fVar1;
		slot->m_cameraPosition.y = fVar1;
		slot->m_cameraPosition.z = fVar2;
	}

	// Setup tribe/character model slot
	fVar2 = FLOAT_8033170C;
	fVar1 = FLOAT_803313dc;
	short sFlags = *reinterpret_cast<short*>(bytes + 0x1A);
	if ((sFlags & 0x3F0) != 0) {
		int modelIdx;
		if ((sFlags & 0x200) != 0) {
			if ((char)bytes[0x06] == 1) {
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
		worldObj->m_transform.m_position.x = fVar1;
		worldObj->m_transform.m_position.y = fVar1;
		worldObj->m_transform.m_position.z = fVar1;
		worldObj->m_transform.m_scale.x = fVar2;
		worldObj->m_transform.m_scale.y = fVar2;
		worldObj->m_transform.m_scale.z = fVar2;
		if ((char)bytes[0x08] == 2 || (char)bytes[0x08] == 3) {
			worldObj->m_transform.m_position.y = FLOAT_80331710;
		}
		if ((*reinterpret_cast<short*>(bytes + 0x1A) & 0xF) != 0) {
			worldObj->m_transform.m_position.x = FLOAT_80331714;
			worldObj->m_transform.m_position.y = static_cast<float>(
			    static_cast<double>(worldObj->m_transform.m_position.y) + DOUBLE_80331420);
		} else if ((*reinterpret_cast<short*>(bytes + 0x1A) & 0x200) != 0) {
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
	unsigned int field1a = (unsigned int)*reinterpret_cast<short*>(bytes + 0x1A);
	if ((field1a & 0x200) != 0 && (field1a & 0xF) != 0) {
		CMenuPcs::FCV* const yTbl = &s_WoodTrns;
		int playerCount = 0;
		for (bitIdx = 0; bitIdx < 4; bitIdx++) {
			if ((field1a & (1 << bitIdx)) != 0) playerCount++;
		}

		int slotIdx = 0;
		for (int padIdx = 0; padIdx < 4; padIdx++) {
			if (((int)*reinterpret_cast<short*>(bytes + 0x1A) & (1 << padIdx)) != 0) {
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
				if ((char)bytes[0x08] == 2 || (char)bytes[0x08] == 3) {
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
 * PAL Address: 0x800f4b24
 * PAL Size: 2600b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawFukidashi()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	CFont* const fontFC = GetFontWorld();
	if (static_cast<signed char>(bytes[0x09]) != 1) {
		return;
	}

	int texMode;
	if (static_cast<signed char>(bytes[0x08]) == 0 || static_cast<signed char>(bytes[0x08]) == 2) {
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
	MenuPcs.SetTexture((TEX)0x18);

	Sprt* background = &m_wm.m_bubbleData->m_sprites[0];
	MenuPcs.DrawRect(texMode,
		(float)(int)background->m_x, (float)(int)background->m_y,
		(float)(int)background->m_width, (float)(int)background->m_height,
		background->m_u, background->m_v,
		FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);

	if ((*reinterpret_cast<short*>(bytes + 0x1A) & 0x3F0) != 0) {
		WmBubbleInfo* bubble = m_wm.m_bubbleData;
		MenuPcs.DrawRect(0,
			(float)bubble->m_sprites[1].m_x, (float)bubble->m_sprites[1].m_y,
			(float)bubble->m_sprites[1].m_width, (float)bubble->m_sprites[1].m_height,
			bubble->m_sprites[1].m_u, bubble->m_sprites[1].m_v,
			FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
	}

	unsigned int uVar3 = (unsigned int)*reinterpret_cast<short*>(bytes + 0x1A);
	if ((uVar3 & 0x3F0) != 0 && (uVar3 & 0x1FF) != 0) {
		if ((uVar3 & 0xF) != 0) {
			int iVar5 = 0;
			int iVar9 = 0;
			while (iVar5 < 4 && iVar9 < 2) {
				if (((int)*reinterpret_cast<short*>(bytes + 0x1A) & (1 << iVar5)) != 0) {
					MenuPcs.SetTexture((TEX)(iVar5 + 0x19));
					Sprt* icon;
					if (iVar9 == 0) {
						icon = &m_wm.m_bubbleData->m_sprites[2];
					} else {
						icon = &m_wm.m_bubbleData->m_sprites[3];
					}
					MenuPcs.DrawRect(0,
						(float)(int)icon->m_x, (float)(int)icon->m_y,
						(float)(int)icon->m_width, (float)(int)icon->m_height,
						icon->m_u, icon->m_v,
						FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
					iVar9++;
				}
				iVar5++;
			}
		} else {
			for (int idx = 0; idx < 5; idx++) {
				if ((uVar3 & (0x10 << idx)) != 0) {
					MenuPcs.SetTexture((TEX)(idx + 0x19));
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
	int fieldVal = (int)(char)bytes[0x07];
	if (fieldVal == 0x0F) {
		strcpy(nameBuffer, Game.m_gameWork.m_townName);
	} else if (fieldVal == 0x16) {
		strcpy(nameBuffer, Game.m_gameWork.m_townName);
		const int language = Game.m_gameWork.m_languageId;
		if (language == 2) {
			strcpy(nameBuffer, Game.m_gameWork.m_townName);
			strcat(nameBuffer, s_port[language - 1]);
		} else {
			strcpy(nameBuffer, s_port[language - 1]);
			strcat(nameBuffer, Game.m_gameWork.m_townName);
		}
	} else {
		strcpy(nameBuffer, Game.m_cFlatDataArr[1].TableStrings(3)[fieldVal]);
	}
	if (nameBuffer[0] != 0) {
		nameBuffer[0] = static_cast<char>(toupperLatin1(static_cast<unsigned char>(nameBuffer[0])));
	}

	int textW = 0xD8;
	char tempBuf[64];
	char secondLine[64];
	secondLine[0] = 0;
	CFont* const font = GetFontWorld();
	if (*reinterpret_cast<short*>(bytes + 0x1A) != 0) {
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

	fontFC->SetMargin(FLOAT_803313e8);
	fontFC->SetShadow(0);
	fontFC->SetScale(FLOAT_803313e8);
	fontFC->DrawInit();
	fontFC->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
	fontFC->SetPosX((float)m_wm.m_bubbleData->m_sprites[4].m_x);
	fontFC->SetPosY((float)m_wm.m_bubbleData->m_sprites[4].m_y);
	fontFC->Draw(nameBuffer);

	if (twoLines != 0) {
		strcpy(nameBuffer, "");
		float w2 = fontFC->GetWidth(secondLine);
		fontFC->SetPosX((FLOAT_80331704 - w2) * FLOAT_80331434 +
		                (float)m_wm.m_bubbleData->m_sprites[0].m_x);
		fontFC->SetPosY((float)(m_wm.m_bubbleData->m_sprites[4].m_y + 0x16));
		fontFC->Draw(secondLine);
	}

	DrawInit();

	// 3D viewport rendering
	int viewportSetup = 0;
	if ((*reinterpret_cast<short*>(bytes + 0x1A) & 0x3F0) != 0) {
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
 * PAL Size: 188b
 * EN Address: 0x8011163C
 * EN Size: 216b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::SplitPlace2(const char* text, char* left, char* right, CFont* font, int width)
{
	char part[64];
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
 * PAL Address: 0x800f3f60
 * PAL Size: 3012b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcWMFrame()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
#define worldState m_wmWorldState
	short sVar3 = worldState->m_mainState;
	if (sVar3 == 0) {
		return;
	}
	if (sVar3 > 2) {
		return;
	}

	if (sVar3 == 2 && bytes[0x13] != 0) {
		m_wm.m_frameData->m_titleFrame--;
		if (m_wm.m_frameData->m_titleFrame < 0) {
			m_wm.m_frameData->m_titleFrame = 0;
		}
	} else if ((bytes[0x0A] & 1) != 0 && m_wm.m_frameData->m_titleFrame != 0) {
		m_wm.m_frameData->m_titleFrame--;
		if (m_wm.m_frameData->m_titleFrame < 0) {
			m_wm.m_frameData->m_titleFrame = 0;
		}
		if (m_wm.m_frameData->m_titleFrame == 0) {
			bytes[0x0A] &= ~1;
		}
	} else if (m_wm.m_frameData->m_titleFrame < 10) {
		m_wm.m_frameData->m_titleFrame++;
	}
	m_wm.m_frameData->m_titleSprite.m_x = 0x68;
	float fVar1 = FLOAT_803313dc;
	m_wm.m_frameData->m_titleSprite.m_y = 0x14;
	m_wm.m_frameData->m_titleSprite.m_width = 200;
	m_wm.m_frameData->m_titleSprite.m_height = 0x28;
	m_wm.m_frameData->m_titleSprite.m_u = fVar1;

	if ((bytes[0x0A] & 1) != 0) {
		WmFrameData* frameA = m_wm.m_frameData;
		int yOff = (int)frameA->m_titleSprite.m_height * (int)(char)bytes[0x05];
		frameA->m_titleSprite.m_v = (float)yOff;
	} else {
		WmFrameData* frameA = m_wm.m_frameData;
		int yOff = (int)frameA->m_titleSprite.m_height * (int)(char)bytes[0x04];
		frameA->m_titleSprite.m_v = (float)yOff;
	}

	WmFrameData* wmFrame = m_wm.m_frameData;
	wmFrame->m_titleSprite.m_x =
	    (10 - wmFrame->m_titleFrame) * 2 + 0x68;

	if (((bytes[0x0A] & 2) != 0 ||
	     (m_wmWorldState->m_mainState == 2 && bytes[0x13] != 0))
	    && m_wm.m_frameData->m_yearFrame >= 10) {
		m_wm.m_frameData->m_yearFrame = 0;
		bytes[0x0A] = bytes[0x0A] & ~2;
	}

	unsigned int uVar13;
	if ((bytes[0x0A] & 2) != 0) {
		uVar13 = *reinterpret_cast<int*>(reinterpret_cast<char*>(&Game.m_gameWork) + 8) + (int)(char)bytes[0x0B];
	} else {
		uVar13 = *reinterpret_cast<int*>(reinterpret_cast<char*>(&Game.m_gameWork) + 8) + (int)(char)bytes[0x0C];
	}
	gWmMenuScriptValueCache = (unsigned char)uVar13;
	if ((int)uVar13 > 99) {
		gWmMenuScriptValueCache = 100;
	}

	int uVar14 = ((int)uVar13 > 9) + 1;
	if ((int)uVar13 > 99) {
		uVar14 = 3;
	}

	float fE8 = FLOAT_803313e8;
	m_wm.m_frameData->m_yearSprites[0].m_scale = fE8;
	m_wm.m_frameData->m_yearSprites[1].m_scale = fE8;

	if (uVar14 == 3) {
		int iVar16 = s_YearWTbl[10];
		const float fV1 = FLOAT_80331524;
		const float fV4 = FLOAT_80331528;
		m_wm.m_frameData->m_yearSprites[0].m_x = (0x2B - iVar16) / 2 + 0x2C;
		m_wm.m_frameData->m_yearSprites[0].m_y = 0x43;
		m_wm.m_frameData->m_yearSprites[0].m_width = (short)iVar16;
		m_wm.m_frameData->m_yearSprites[0].m_height = 0x20;
		m_wm.m_frameData->m_yearSprites[0].m_u = fV1;
		m_wm.m_frameData->m_yearSprites[0].m_v = fV4;
	} else {
		int digits[2];
		digits[0] = (int)uVar13 % 10;
		if (1 < uVar14) {
			digits[1] = (int)uVar13 / 10;
		}
		int iVar16 = s_YearWTbl[(int)uVar13 % 10];
		if (1 < uVar14) {
			iVar16 = iVar16 + s_YearWTbl[(int)uVar13 / 10];
		}
		int iVar19 = uVar14 - 1;
		int iVar15 = (0x2B - iVar16) / 2 + 0x2C;
		const double dV10 = DOUBLE_80331490;
		const double dV12 = DOUBLE_80331540;
		const double dV11 = DOUBLE_80331538;
		int wmDigitIdx;
		for (wmDigitIdx = iVar19; wmDigitIdx >= 0; wmDigitIdx--) {
				int digit = digits[wmDigitIdx];
				m_wm.m_frameData->m_yearSprites[wmDigitIdx].m_x = (short)iVar15;
				int digitW = s_YearWTbl[digit];
				m_wm.m_frameData->m_yearSprites[wmDigitIdx].m_y = 0x43;
				m_wm.m_frameData->m_yearSprites[wmDigitIdx].m_width = (short)digitW;
				m_wm.m_frameData->m_yearSprites[wmDigitIdx].m_height = 0x20;
				int col = digit % 5;
				int row = digit / 5;
				m_wm.m_frameData->m_yearSprites[wmDigitIdx].m_u = (float)(dV10 * (double)(float)col);
				m_wm.m_frameData->m_yearSprites[wmDigitIdx].m_v = (float)(dV12 * (double)(float)row + dV11);
				iVar15 = iVar15 + digitW;
		}
	}

	if ((bytes[0x0A] & 2) != 0 ||
	    (worldState->m_mainState == 2 && bytes[0x13] != 0)) {
		const double dE8 = DOUBLE_803316E8;
		const double dF8 = DOUBLE_803313F8;
		for (int i = 0; i < uVar14; i++) {
			if (i != 0 && uVar14 != 2) {
				break;
			}
			float fVar1 = static_cast<float>(
			    static_cast<double>(static_cast<float>(10 - m_wm.m_frameData->m_yearFrame)) / dE8);
			m_wm.m_frameData->m_yearSprites[i].m_alpha = fVar1;
			m_wm.m_frameData->m_yearSprites[i].m_scale =
			    static_cast<float>(dF8 * static_cast<double>(fVar1) + dF8);

			Sprt* entry = &m_wm.m_frameData->m_yearSprites[i];
			float prodBA = static_cast<float>(entry->m_height) *
			               entry->m_scale;
			entry->m_y =
			    static_cast<short>(entry->m_y +
			                       static_cast<int>(
			                           static_cast<float>(entry->m_height) -
			                           prodBA));

			if (i == 0 && (uVar14 == 1 || uVar14 == 3)) {
				entry = &m_wm.m_frameData->m_yearSprites[i];
				float prodB8a = static_cast<float>(entry->m_width) *
				               entry->m_scale;
				entry->m_x =
				    static_cast<short>(entry->m_x +
				                       static_cast<int>(
				                           (DOUBLE_80331420 +
				                            static_cast<double>(
				                                static_cast<float>(entry->m_width) -
				                                prodB8a)) *
				                           DOUBLE_803313F8));
			} else if (i != 0) {
				entry = &m_wm.m_frameData->m_yearSprites[i];
				float prodB8b = static_cast<float>(entry->m_width) *
				               entry->m_scale;
				entry->m_x =
				    static_cast<short>(entry->m_x +
				                       static_cast<int>(
				                           static_cast<float>(entry->m_width) -
				                           prodB8b));
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
			float fVar5;
			fVar5 = GetFcvValue(s_YearTrns, t);
			base->m_yearSprites[1].m_y =
			    static_cast<short>(static_cast<int>(static_cast<float>(base->m_yearSprites[1].m_y) + fVar5));

			float fVar1;
			fVar1 = GetFcvValue(s_YearAlpha, t);
			m_wm.m_frameData->m_yearSprites[1].m_alpha = fVar1;

			if (uVar14 == 2) {
				uVar -= 5;
			}
			t = static_cast<float>(static_cast<int>(uVar));
			fVar5 = GetFcvValue(s_YearTrns, t);
			m_wm.m_frameData->m_yearSprites[0].m_y =
			    static_cast<short>(static_cast<int>(
			        static_cast<float>(m_wm.m_frameData->m_yearSprites[0].m_y) + fVar5));

			fVar1 = GetFcvValue(s_YearAlpha, t);
			m_wm.m_frameData->m_yearSprites[0].m_alpha = fVar1;
			m_wm.m_frameData->m_yearFrame =
			    m_wm.m_frameData->m_yearFrame + 1;
		}
	}
#undef worldState
}

/*
 * --INFO--
 * PAL Address: 0x800f36ac
 * PAL Size: 2228b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x16));

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

	short sVar2 = m_wmWorldState->m_mainState;
	if (sVar2 != 0 && sVar2 <= 3) {
		MenuPcs.SetTexture((TEX)0x17);
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
			const int language = Game.m_gameWork.m_languageId;
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
			MenuPcs.SetTexture((TEX)0x17);

			unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
			int dispValue =
			    bytes[0xA] & 2
			        ? static_cast<int>(Game.m_gameWork.m_scriptSysVal0) + static_cast<signed char>(bytes[0xB])
			        : static_cast<int>(Game.m_gameWork.m_scriptSysVal0) + static_cast<signed char>(bytes[0xC]);
			int digitCnt;
			digitCnt = (dispValue > 9) + 1;
			if (dispValue > 99) {
				digitCnt = 3;
			}
			const int languageYOffset = language != 5 ? 0 : 0xE;

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
					Sprt* digit = &m_wm.m_frameData->m_yearSprites[i];
					MenuPcs.DrawRect(0,
						(float)digit->m_x,
						(float)(digit->m_y + languageYOffset),
						(float)digit->m_width,
						(float)digit->m_height,
						digit->m_u,
						digit->m_v,
						digit->m_scale,
						digit->m_scale,
						kZero);
				}
			}

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
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800f31b8
 * PAL Size: 460b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x29));

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
	WmWorldObjInfo* charaWork = &m_wm.m_worldObjData[32];
	unsigned int selectedMask = 0;

	for (int i = 0; i < kWmMenuControllerCount; i++) {
		if (m_wm.m_charaSelectData[i].m_connected == 1) {
			selectedMask |= 1u << static_cast<unsigned int>(m_wm.m_charaSelectData[i].m_currentSlot);
		}
	}

	for (int slot = 0; slot < 8; slot++) {
		unsigned int effectMask = 0;
		int effectCount = 0;

		for (int player = 0; player < 4; player++) {
			WmCharaSelectEntry* const entry = &m_wm.m_charaSelectData[player];
			const int currentSlot = entry->m_currentSlot;
			if ((entry->m_connected == 1) && (currentSlot >= 0) && (slot == currentSlot)) {
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

			for (int player = 0; player < 4; player++) {
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

	for (int i = 0; i < kWmMenuPlayerCount; i++, charaWork++) {
		CCharaPcs::CHandle* const handle = GetWmCharaHandles(this)[i];
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
		CCharaPcs::CHandle* const charaHandle = GetWmCharaHandles(this)[i];
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
			GetWmCharaHandles(this)[i]->m_model->m_lightAlpha = alpha;
		} else if (state == 2) {
			GetWmCharaHandles(this)[i]->m_model->m_lightAlpha = FLOAT_803313e8;
		} else {
			GetWmCharaHandles(this)[i]->m_model->m_lightAlpha = static_cast<float>(DOUBLE_80331420 - alpha);
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
		GetWmCharaHandles(this)[i]->m_model->SetMatrix(scaleMtx);
		GetWmCharaHandles(this)[i]->m_model->CalcMatrix();
		GetWmCharaHandles(this)[i]->m_model->CalcSkin();
	}

	PCAnimCtrl();
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
	unsigned int selectedMask = 0;

	for (int i = 0; i < kWmMenuControllerCount; i++) {
		if (charaSelect[i].m_connected != 0 && charaSelect[i].m_confirmed != 0) {
			selectedMask |= 1 << charaSelect[i].m_currentSlot;
		}
	}

	WmCharaAnimState* animState = m_wmCharaAnimState;
	for (int i = 0; i < kWmMenuPlayerCount; i++, animState++) {
		CCharaPcs::CHandle* const handle = GetWmCharaHandles(this)[i];
		const int blendMode = handle->m_currentAnimIndex < 0 ? 0 : -1;

		CChara::CModel* const model = handle->m_model;
		if (model == 0 || model->m_texSet == 0 || handle->m_charaKind == 3) {
			continue;
		}

		animState->m_frame = model->m_time;

		if (animState->m_nextAnimIndex >= 0) {
			animState->m_animIndex = animState->m_nextAnimIndex;
			animState->m_nextAnimIndex = -1;
			handle->SetAnim((static_cast<int>(static_cast<unsigned int>(GetWmCharaHandles(this)[i]->m_charaNo) / 100) - 1) * 6 + animState->m_animIndex, -1, -1, blendMode, 0);
			animState->m_frame = handle->m_model->m_time;
			animState->m_endFrame = handle->m_model->m_animEnd;
			animState->m_timer = 0;
			continue;
		}

		const int isSelected = selectedMask & (1u << static_cast<unsigned int>(i));
		if (isSelected == 0 &&
		    m_wmWorldState->m_menuMode != 8 &&
		    animState->m_animIndex == 0 && animState->m_timer >= 3000) {
			animState->m_animIndex = 4;
			handle->SetAnim((static_cast<int>(static_cast<unsigned int>(GetWmCharaHandles(this)[i]->m_charaNo) / 100) - 1) * 6 + animState->m_animIndex, -1, -1, blendMode, 0);
			animState->m_frame = handle->m_model->m_time;
			animState->m_endFrame = handle->m_model->m_animEnd;
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

			handle->SetAnim((static_cast<int>(static_cast<unsigned int>(GetWmCharaHandles(this)[i]->m_charaNo) / 100) - 1) * 6 + animState->m_animIndex, -1, -1, blendMode, 0);
			animState->m_frame = handle->m_model->m_time;
			animState->m_endFrame = handle->m_model->m_animEnd;
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
					handle->SetAnim((static_cast<int>(static_cast<unsigned int>(GetWmCharaHandles(this)[i]->m_charaNo) / 100) - 1) * 6 + animState->m_animIndex, -1, -1, blendMode, 0);
					animState->m_frame = handle->m_model->m_time;
					animState->m_endFrame = handle->m_model->m_animEnd;
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawChara()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	for (int i = 0; i < kWmMenuPlayerCount; i++) {
		WmWorldObjInfo* const view = &m_wm.m_worldObjData[32 + i];
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
		if (handle->m_charaKind != 3 && handle->m_currentAnimIndex < 0) {
			continue;
		}

		SetProjection(i + 32);
		SetLight(0);
		if (GetWmCharaHandles(this)[i]->m_charaKind != 3) {
			GetWmCharaHandles(this)[i]->Draw(5);
		} else {
			DrawInit();
			GXSetZMode(GX_TRUE, static_cast<GXCompare>(7), GX_TRUE);
			SetProjection(i + 32);
			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x32));
			MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
			float alpha;
			if (m_wmWorldState->m_mainState == 2) {
				const float* pOneAl = &FLOAT_803313e8;
				alpha = *pOneAl;
			} else {
				alpha = handle->m_model->m_lightAlpha;
			}
			const float* pRgbMul = &FLOAT_80331458;
			const float rgbMul = *pRgbMul;
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
			color.r = static_cast<unsigned char>(static_cast<int>(rgbMul * colorScale));
			color.g = static_cast<unsigned char>(static_cast<int>(rgbMul * colorScale));
			color.b = static_cast<unsigned char>(static_cast<int>(rgbMul * colorScale));
			color.a = static_cast<unsigned char>(static_cast<int>(*pAScale * static_cast<double>(alpha)));
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
				x *= *pSel;
				y *= *pSel;
				scale *= *pSel;
			}
			const float* pR1 = &FLOAT_80331694;
			const float* pR2 = &FLOAT_80331578;
			const float* pR3 = &FLOAT_80331520;
			const float* pZeroR3 = &FLOAT_803313dc;
			MenuPcs.DrawRect3d(0, x, y, *pR1, *pR2, *pR3,
			                   *pZeroR3, *pZeroR3, scale, scale);
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
	const int gender = (info.m_charaType >> 7) != 0;
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
	{
		int modelNo2 = static_cast<int>(info.m_charaType & 3) * 200 + 100;
		if ((info.m_charaType >> 7) != 0) {
			modelNo2 += 100;
		}
		caravanWork.m_id = static_cast<unsigned short>(modelNo2 + ((info.m_charaType >> 2) & 3));
	}
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

	CFlatRuntime::CStack stackArgs[3];
	stackArgs[0].m_word = 0;
	stackArgs[1].m_word = caravanSlot;
	stackArgs[2].m_word = 0;
	gCFlatRuntime().SystemCall(0, 1, 4, 3, stackArgs, 0);
}

/*
 * --INFO--
 * PAL Address: 0x800f0a70
 * PAL Size: 5544b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcCharaSelect()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	unsigned short padRepeat[4];
	unsigned short padTrig[4];
	int requestCancel;
	int requestFinalize;

	m_wmHelpTimer = static_cast<short>(m_wmHelpTimer + 1);
	const unsigned int modeIsZero = Game.m_gameWork.m_menuStageMode == 0;
	if (static_cast<int>(m_wmHelpTimer) >= static_cast<int>((modeIsZero + 2) * 0x4B)) {
		m_wmHelpTimer = 0;
	}

	requestCancel = 0;
	requestFinalize = 0;
	for (int i = 0; i < 4; i++) {
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

	const short winState = m_menuWindowInfo->state;
	if (winState != 3) {
		unsigned short anyTrig = static_cast<unsigned short>(requestCancel);
		for (int i = anyTrig; i < 4; i++) {
			anyTrig |= padTrig[i];
		}
		int __p3 =  (anyTrig + 0);
		if (winState == 1 && (__p3 & 0x0300) != 0) {
			m_menuWindowInfo->state = 2;
			for (int i = 0; i < 4; i++) {
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
		unsigned int pendingMask = 0;
		for (int i = 0; i < 4; i++) {
			if (Game.m_gameWork.m_menuStageMode != 0) {
				break;
			}
			if (m_wm.m_charaSelectData[i].m_cmakePending != 0) {
				pendingMask |= 1u << static_cast<unsigned int>(m_wm.m_charaSelectData[i].m_currentSlot);
			}
		}

		for (int i = 0; i < 4; i++) {
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
				const int hOff = (slot + 0x20) * 4 + 0x774;
				if (Game.m_caravanWorkArr[slot].m_shopState == 0 &&
				    (*reinterpret_cast<CCharaPcs::CHandle**>(bytes + hOff))->IsModelLoaded(1) &&
				    (*reinterpret_cast<CCharaPcs::CHandle**>(bytes + hOff))->m_charaKind != 3 &&
				    entry.m_cmakeReady != 1) {
					if (static_cast<unsigned int>(System.m_execParam) >= 3) {
						System.Printf("chan = %d cur = %d\n", i,
						              static_cast<int>(entry.m_currentSlot));
					}
					const int loadSlot =  (s32)(static_cast<int>(entry.m_currentSlot));
					m_wm.m_charaModelData[loadSlot].m_modelChanged = 0;
					GetWmCharaHandles(this)[loadSlot]->LoadModelASync(3, 0x43, 0);
				}
			} else if (entry.m_cmakePending == 0 && static_cast<int>(Joybus.GetMType(i)) == 1) {
				Joybus.SetMType(i, 4);
			}
		}

		unsigned int confirmedSlotMask = 0;
		for (int i = 0; i < 4; i++) {
			if (m_wm.m_charaSelectData[i].m_confirmed != 0) {
				confirmedSlotMask |= 1u << static_cast<unsigned int>(m_wm.m_charaSelectData[i].m_currentSlot);
			}
		}

		for (int slot = 0; slot < 8; slot++) {
			if (((confirmedSlotMask & (1u << static_cast<unsigned int>(slot))) == 0) &&
			    ((pendingMask & (1u << static_cast<unsigned int>(slot))) == 0) &&
			    Game.m_caravanWorkArr[slot].m_shopState == 0 &&
			    GetWmCharaHandles(this)[slot]->IsModelLoaded(1) &&
			    GetWmCharaHandles(this)[slot]->m_charaKind != 3) {
				m_wm.m_charaModelData[slot].m_modelChanged = 0;
				GetWmCharaHandles(this)[slot]->LoadModelASync(3, 0x43, 0);
			}
		}

		int connectedCount = 0;
		int locallyConfirmedCount = 0;
		int readyMask = 0;
		for (int i = 0; i < 4; i++) {
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
		int i = 3;
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
				if (entry.m_disconnectTime < 0x3C) {
					entry.m_disconnectTime++;
				}
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
			for (int i = 0; i < 4; i++) {
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
			for (int i = 0; i < 4; i++) {
				if (m_wm.m_charaSelectData[i].m_confirmed != 0) {
					activeCount++;
				}
			}
			for (int i = 0; i < 4; i++) {
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
		for (int i = 0; i < 4; i++) {
			if (m_wm.m_charaSelectData[i].m_confirmed != 0) {
				finishedMask |= 1 << i;
			}
		}
		if (Game.m_gameWork.m_menuStageMode != 0 && m_singleCmakeSlot >= 0) {
			GetWmWorldState(this)->m_nextMenuMode = 1;
			GetWmWorldState(this)->m_delay = 10;
		} else {
			for (int i = 0; i < 4; i++) {
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
			GbaQue.SetControllerMode(1);
			for (int i = 0; i < kWmMenuControllerCount; i++) {
				WmCharaSelectEntry& entry = m_wm.m_charaSelectData[i];
				if (entry.m_cmakePending != 0) {
					entry.m_confirmed = 0;
					entry.m_cmakePending = 0;
					entry.m_cmakeReady = 0;
				}
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x800f0274
 * PAL Size: 2044b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawCharaName()
{
	static const char* STR_TBL_us[] = {"Empty", "Creating..."};
	static const char* STR_TBL_ge[] = {"Frei", "Wird kreiert"};
	static const char* STR_TBL_it[] = {"Vuoto", "Creazione..."};
	static const char* STR_TBL_fr[] = {"Vide", "Cr\351ation..."};
	static const char* STR_TBL_sp[] = {"Vac\355o", "Creando..."};

	CFont* const font = GetWmFont(this);
	WmCharaSelectEntry* const selectEntries = m_wm.m_charaSelectData;
	unsigned char nameBuf[0x20];

	const char** emptyText;
	switch (Game.m_gameWork.m_languageId) {
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
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x28));
	const float yBase1 = FLOAT_80331478;
	const double xOffsetDefault =
	    -(DOUBLE_80331418 * static_cast<double>(FLOAT_80331680) - DOUBLE_80331678);
	const float yExtra1 = FLOAT_80331684;
	int row = 0;
	int yCounter = row;
	int slotBase = row;
	for (; row < 2; row++) {
		float y = yBase1 + static_cast<float>(yCounter);
		y += yExtra1;
		if (row != 0) {
			y += FLOAT_80331548;
		}
		int xCounter = 0;
		int slot = slotBase;
		for (int col = 0; col < 4; col++) {
			if ((confirmedMask & (1u << slot)) != 0) {
				const char* const text = reinterpret_cast<const char*>(
				    Game.m_caravanWorkArr[slot].m_name);
				float xBase = FLOAT_80331410 + static_cast<float>(xCounter);
				const float width = font->GetWidth(text);
				float scale = FLOAT_803313e8;
				if (static_cast<double>(width) * DOUBLE_803313F8 > static_cast<double>(FLOAT_80331680)) {
					const float widthPlus = static_cast<float>(static_cast<double>(width) + DOUBLE_80331510);
					scale = static_cast<float>(widthPlus * DOUBLE_803313F8 / static_cast<double>(FLOAT_80331680));
					const double xOffsetW = FLOAT_8033155C - widthPlus;
					xBase = static_cast<float>(xOffsetW * DOUBLE_803313F8 + xBase);
				} else {
					xBase = static_cast<float>(xOffsetDefault * DOUBLE_803313F8 + xBase);
				}
				MenuPcs.DrawRect(
				    0, xBase, y, FLOAT_80331680, FLOAT_80331410,
				                                FLOAT_803313dc, FLOAT_803313dc, scale, FLOAT_803313e8, FLOAT_803313dc);
				MenuPcs.DrawRect(
				    8, FLOAT_80331680 * scale + xBase, y,
				                                FLOAT_80331680, FLOAT_80331410, FLOAT_803313dc, FLOAT_803313dc,
				                                scale, FLOAT_803313e8, FLOAT_803313dc);
			}
			xCounter += 0x90;
			slot++;
		}
		yCounter += 0xB8;
		slotBase += 4;
	}

	DrawInit();
	font->SetMargin(FLOAT_803313e8);
	font->SetShadow(1);
	font->SetScale(FLOAT_8033158C);
	font->DrawInit();
	font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<long>(alphaF)).color);

	CSystem* const sys = &System;
	const float xBase2 = FLOAT_80331410;
	const float xMax2 = FLOAT_8033155C;
	const float yBase2 = FLOAT_80331478;
	const float yExtra2 = FLOAT_80331688;
	const float ySub2 = FLOAT_80331550;
	const double k3f8_2 = DOUBLE_803313F8;
	int row2 = 0;
	int slotBase2;
	int yCounter2 = row2;
	slotBase2 = row2;
	for (; row2 < 2; row2++) {
		float y = yBase2 + static_cast<float>(yCounter2);
		y += yExtra2;
		if (row2 != 0) {
			y += FLOAT_80331548;
		}
		y = static_cast<float>(y - ySub2);
		int col = 0;
		int slot = slotBase2;
		int xCounter2 = col;
		for (; col < 4; col++) {
			int restoreColor;
			restoreColor = 0;
			const char* text;

			float xBase = xBase2 + static_cast<float>(xCounter2);

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
				text = emptyText[1];
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
				text = emptyText[0];
			}

			const float widthDiff = xMax2 - font->GetWidth(text);
			xBase = static_cast<float>(widthDiff * k3f8_2 + xBase);
			font->SetPosX(xBase);
			font->SetPosY(y);
			font->Draw(text);
			if (restoreColor) {
				font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
			}
			xCounter2 += 0x90;
			slot++;
		}
		slotBase2 += 4;
		yCounter2 += 0xB8;
	}

	DrawInit();
}

/*
 * --INFO--
 * PAL Address: 0x800efc38
 * PAL Size: 1596b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
		const double* pRate = &DOUBLE_803314E8;
		fade = static_cast<float>(*pRate * static_cast<double>(worldState->m_frameCounter));
	} else if (worldState->m_mainState == 2) {
		const float* pOne = &FLOAT_803313e8;
		fade = *pOne;
	} else {
		const double* pRate = &DOUBLE_803314E8;
		const double* pOne = &DOUBLE_80331420;
		fade = static_cast<float>(-(*pRate * static_cast<double>(worldState->m_frameCounter) -
		                            *pOne));
	}
	unsigned int readyMask = 0;
	for (int i = 0; i < 4; i++) {
		const WmCharaSelectEntry& entry = selectEntries[i];
		if (entry.m_connected != 0 && entry.m_cmakePending == 0 && entry.m_cmakeReady == 0) {
			readyMask |= 1u << entry.m_currentSlot;
		}
	}
	const float* p255A = &FLOAT_80331458;
	const double alphaF = *p255A * fade;

	for (int slot = 0; slot < 8; slot++) {
		int i;
		int row;
		int col;
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x27));

		int count;
		if (worldState->m_menuMode == 8 && m_cmakeWorkActive == 1 && m_cmakeWork != 0 &&
		    m_cmakeWork->m_characters[slot].m_exists != 0) {
			count = static_cast<int>(m_cmakeWork->m_characters[slot].m_maxHp) >> 1;
		} else if (Game.m_caravanWorkArr[slot].m_shopState != 0) {
			count = static_cast<int>(Game.m_caravanWorkArr[slot].m_maxHp) >> 1;
		} else {
			continue;
		}
		float red;
		float green;
		float blue;
		if ((readyMask & (1u << slot)) != 0) {
			const float* pOneC = &FLOAT_803313e8;
			red = *pOneC;
			green = red;
			blue = red;
		} else {
			const float* pHalfC = &FLOAT_80331434;
			const float* pDimC = &FLOAT_80331668;
			red = *pHalfC;
			green = *pDimC;
			blue = green;
		}

		const float* p255C = &FLOAT_80331458;
		GXColor color;
		color.a = static_cast<unsigned char>(static_cast<int>(alphaF));
		color.b = static_cast<unsigned char>(static_cast<int>(*p255C * blue));
		color.r = static_cast<unsigned char>(static_cast<int>(*p255C * red));
		color.g = static_cast<unsigned char>(static_cast<int>(*p255C * green));
		GXSetChanMatColor(GX_COLOR0A0, color);

		row = slot / 4;
		col = slot % 4;
		const float* pYOrg = &FLOAT_80331478;
		const float* pXOrg = &FLOAT_80331410;
		float xBase;
		float y;
		float x;
		xBase = *pXOrg + static_cast<float>(col * 0x90);
		y = *pYOrg + static_cast<float>(row * 0xB8);
		float yTmp = y;
		if (row != 0) {
			const float* pRowAdd = &FLOAT_80331548;
			yTmp = y + *pRowAdd;
		}
		const float* pYAdj = &FLOAT_8033166C;
		yTmp = yTmp + *pYAdj;
		const double* pHalfD = &DOUBLE_803313F8;
		x = static_cast<float>(static_cast<double>(0x90 - count * 0x10) * *pHalfD + static_cast<double>(xBase));
		float step = static_cast<float>(static_cast<double>(8 - count) * *pHalfD);

		const float* pZeroK = &FLOAT_803313dc;
		const float* pRectSize = &FLOAT_80331558;
		const double* pStepDelta = &DOUBLE_80331420;
		double kStepDelta;
		float kRectSize;
		const float kZero = *pZeroK;
		kStepDelta = *pStepDelta;
		kRectSize = *pRectSize;

		for (i = 0; i < count; i++) {
			float yAdd = GetFcvValue(s_LifePos, step);

			MenuPcs.DrawRect(
			    0, x, yTmp + yAdd, FLOAT_80331558, FLOAT_80331558,
			                                kZero, kZero, FLOAT_803313e8, FLOAT_803313e8, kZero);
			step = static_cast<float>(step + kStepDelta);
			x += kRectSize;
		}

		unsigned char flagA;
		unsigned char flagB;
		if (m_cmakeWorkActive == 1 && m_cmakeWork != 0) {
			flagB = m_cmakeWork->m_characters[slot].m_isGuest;
			flagA = m_cmakeWork->m_characters[slot].m_isAway;
		} else {
			flagB = Game.m_caravanWorkArr[slot].m_caravanLocalFlags;
			flagA = Game.m_caravanWorkArr[slot].m_shopBusyFlag;
		}
		if (flagA != 0 || flagB != 0) {
			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x38));
			MenuPcs.DrawRect(
			    0, static_cast<float>(xBase + DOUBLE_80331670),
			                                static_cast<float>((row != 0 ? y + FLOAT_80331548 : y) + DOUBLE_803315C0), FLOAT_80331524,
			                                FLOAT_80331440, FLOAT_803313dc,
			                                flagA != 0 ? FLOAT_803313dc : FLOAT_80331440,
			                                FLOAT_803313e8, FLOAT_803313e8, FLOAT_803313dc);
		}
	}
#undef worldState
#undef selectEntries
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

	int iVar14 = m_wmWorldState->m_menuMode;
	lbl_8032EE1C = 1;

	short sVar2 = m_wmWorldState->m_changeRequest;

	if (sVar2 == 2) {
		char cVar1 = bytes[0xD];
		if (cVar1 == 1) {
			m_wmWorldState->m_menuMode = 0;
		} else if (cVar1 == 2) {
			m_wmWorldState->m_menuMode = 5;
		} else if (cVar1 == 3) {
			lbl_8032EE1C = 1;
			if (iVar14 == 6) {
				m_wmWorldState->m_changeRequest = 0;
				return;
			}
			m_wmWorldState->m_menuMode = 6;
		} else if (cVar1 == 4) {
			m_wmWorldState->m_menuMode = 4;
		} else {
			m_wmWorldState->m_menuMode = 1;
		}
	} else if (iVar14 == 0) {
		if (sVar2 == 1) {
			short sVar2b = m_wmWorldState->m_cardChannel;
			if (sVar2b == 0) {
				m_wmWorldState->m_menuMode = 3;
			} else if (sVar2b == 1) {
				m_wmWorldState->m_menuMode = 1;
				memset(m_wmWorldParams, 0, 0x10);
			} else if (sVar2b == 2) {
				m_wmWorldState->m_menuMode = 8;
			} else if (sVar2b == 3) {
				m_wmWorldState->m_menuMode = 7;
			} else {
				m_wmWorldState->m_menuMode = 2;
			}
		} else {
			m_wmWorldState->m_menuMode = 4;
		}
	} else if (iVar14 == 1) {
		m_wmWorldState->m_menuMode = 0;
		m_wmWorldState->m_cardChannel = 1;
	} else if (iVar14 == 8) {
		m_wmWorldState->m_menuMode = 0;
		m_wmWorldState->m_cardChannel = 2;
	} else if (iVar14 == 7) {
		m_wmWorldState->m_menuMode = 0;
		m_wmWorldState->m_cardChannel = 3;
	} else if (iVar14 == 2) {
		m_wmWorldState->m_menuMode = 0;
		m_wmWorldState->m_cardChannel = 4;
	} else if (iVar14 == 5) {
		if (sVar2 == 1) {
			m_wmWorldState->m_menuMode = 0;
			bytes[0xD] = 0;
			m_wmWorldState->m_cardChannel = 0;
			CFlatRuntime::CStack stackA[3];
			stackA[0].m_word = 1;
			stackA[1].m_word = 1;
			stackA[2].m_word = 0;
			gCFlatRuntime().SystemCall(0, 1, 4, 3, stackA, 0);
		} else if (sVar2 == -1) {
			lbl_8032EE1C = 1;
			m_wmWorldState->m_menuMode = 6;
			CFlatRuntime::CStack stackB[3];
			stackB[0].m_word = 1;
			stackB[1].m_word = 0;
			stackB[2].m_word = 0;
			gCFlatRuntime().SystemCall(0, 1, 4, 3, stackB, 0);
		}
	} else if (iVar14 == 6) {
		m_wmWorldState->m_menuMode = 0;
	} else if (sVar2 == 1) {
		if (m_wmWorldState->m_menuMode >= 8) {
			bytes[0xD] = 0;
		} else {
			m_wmWorldState->m_menuMode++;
		}
	} else if (sVar2 == -1) {
		short sVar2c = m_wmWorldState->m_menuMode;
		if (sVar2c <= 0) {
			bytes[0xD] = 0;
		} else if (sVar2c == 3) {
			m_wmWorldState->m_menuMode = 0;
			m_wmWorldState->m_cardChannel = 0;
		} else {
			m_wmWorldState->m_menuMode = sVar2c - 1;
		}
	}

	if (m_wmWorldState->m_menuMode != 0) {
		m_wmWorldState->m_cardChannel = 0;
	}

	float fVar6 = FLOAT_803315B0;
	m_wmWorldState->m_frameCounter = 0;
	double dVar15 = (double)FLOAT_80331430;
	int xInt = (int)fVar6;
	m_wmWorldState->m_titleState = 0;
	float fVar4 = FLOAT_803313dc;
	float fVar5 = FLOAT_803313e8;
	double dVar16 = DOUBLE_803313F8;
	m_wmWorldState->m_worldReady = 0;
	m_wmWorldState->m_flag09 = 0;
	int yInt = (int)(float)(dVar15 * dVar16);
	m_wmWorldState->m_flag0A = 0;
	m_wmWorldState->m_state0E = 0;
	m_wmWorldState->m_mainState = 0;
	m_wmWorldState->m_state12 = 0;
	m_wmWorldState->m_subState = 0;
	m_wmWorldState->m_delay = 0;
	m_wmWorldState->m_counter1A = 0;
	m_wmWorldState->m_posY = fVar5;
	m_wmWorldState->m_posX = fVar4;
	m_wmWorldState->m_mcResult = 0;
	m_wmWorldState->m_flag0B = 0;
	m_wmWorldState->m_modelFlagsInitialized = 0;

	m_menuWindowInfo->x = (short)xInt;
	m_menuWindowInfo->y = (short)yInt;
	m_menuWindowInfo->width = 0;
	m_menuWindowInfo->height = 0;
	m_menuWindowInfo->frame = 0;
	m_menuWindowInfo->state = 3;
	m_textureLocIndex = 0;

	InitFrame0Info();

	if (iVar14 == 3 && Game.m_gameWork.m_menuStageMode != 0
	    && m_singleCmakeSlot >= 0
	    && m_singleCmakeSlot < 8) {
		m_singleCmakeMode = 1;
		m_wmWorldState->m_menuMode = 3;
	} else if (iVar14 == 3 && Game.m_gameWork.m_menuStageMode != 0
	           && m_singleCmakeSlot >= 8) {
		m_singleCmakeMode = 0;
		m_singleCmakeSlot = (short)0xFFFF;
		m_wmWorldState->m_menuMode = 3;
	} else {
		m_singleCmakeMode = 0;
		m_singleCmakeSlot = (short)0xFFFF;
	}

	int iVar8 = 0;
	m_wmTransitionCode = 0;

	sVar2 = m_wmWorldState->m_menuMode;
	switch (sVar2) {
	case 0: {
			ChkSelectParty();

			const float scrollStep = FLOAT_8033151c;
			m_wmMenuTargetRotation = -(scrollStep * (float)(int)m_wmWorldState->m_cardChannel);
			m_wmMenuRotation = -(scrollStep * (float)(int)m_wmWorldState->m_cardChannel);
			m_effectTimer = 0;
		break;
	}
	case 3: {
			double dVar16b = (double)FLOAT_80331664;
			int iVar12 = 0;
			WmWorldObjInfo* worldObj = &m_wm.m_worldObjData[32];
			do {
				const int handleIdx = iVar12 + 0x20;
				m_wm.m_charaModelData[iVar12].m_modelChanged = 1;
				worldObj->m_transform.m_rotation.y = (float)dVar16b;
				WmCharaSelectEntry* const selectData = &m_wm.m_charaSelectData[iVar12];
				selectData->m_displaySlot = selectData->m_currentSlot;
				if (m_wm.m_handles[handleIdx]->IsModelLoaded(1)) {
					Mtx mtx;
					PSMTXIdentity(mtx);
					m_wm.m_handles[handleIdx]->m_model->SetMatrix(mtx);
					m_wm.m_handles[handleIdx]->m_model->CalcMatrix();
					m_wm.m_handles[handleIdx]->m_model->CalcSkin();
				}
				iVar12 = iVar12 + 1;
				worldObj++;
			} while (iVar12 < 8);

			iVar8 = 0;
			do {
				GbaQue.ClrCmakeInfo(iVar8);
				iVar8 = iVar8 + 1;
			} while (iVar8 < 4);
		break;
	}
	case 4:
		m_wmWorldState->m_posX = FLOAT_80331440;
		break;
	case 7:
		GetOptionData();
		break;
	}

	switch (iVar14) {
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

	sVar2 = m_wmWorldState->m_menuMode;
	if (sVar2 == 6) {
		MapMng.GetMapIdGrpArray()[0xF7].m_primaryColor.a = 0;
	} else if (iVar14 == 6 && sVar2 != 6) {
		MapMng.GetMapIdGrpArray()[0xF7].m_primaryColor.a = 1;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800eee34
 * PAL Size: 108b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetCMakeEnd(int channel)
{
	m_wm.m_charaSelectData[channel].m_cmakeReady = 1;
	if ((unsigned int)System.m_execParam >= 3) {
		System.Printf("SetCMakeEnd : chan = %d  cur = %d\n", channel,
		               (int)m_wm.m_charaSelectData[channel].m_currentSlot);
	}
}

/*
 * --INFO--
 * PAL Address: 0x800eed84
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ClrCMakeFlg(int channel)
{
	m_wm.m_charaSelectData[channel].m_cmakePending = 0;
	const int current = m_wm.m_charaSelectData[channel].m_currentSlot;
	if ((unsigned int)System.m_execParam >= 3) {
		System.Printf("ClrCMakeFlg : chan = %d  cur = %d\n", channel, current);
	}
	WmCharaModelInfo* modelData = &m_wm.m_charaModelData[current];
	modelData->m_modelChanged = 0;
	GetWmCharaHandles(this)[current]->LoadModelASync(3, 0x43, 0);
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
		int tribe;
		int appearance;
		int isFemale;
		int modelId;

		if (Game.m_caravanWorkArr[i].m_shopState != 0) {
			CCaravanWork* const caravan = &Game.m_caravanWorkArr[i];
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
		const Mc::CharaDat& character = m_cmakeWork->m_characters[i];
		WmCharaModelInfo* modelData = &m_wm.m_charaModelData[i];
		int tribe;
		int isFemale;
		int appearance;

		if (character.m_exists != 0) {
			tribe = character.m_tribeId;
			appearance = character.m_appearanceVariant;
			isFemale = character.m_genderFlag;
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
 * PAL Address: 0x800ed94c
 * PAL Size: 3804b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcMainMenuSub()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	const unsigned short btn = Pad.GetButtonDown(0);
	const short state = m_wmWorldState->m_mainState;

	if (((state > 0) && (state < 4)) || m_wmWorldState->m_cardChannel == 1) {
		if (state == 2 && m_wmWorldState->m_delay == 0) {
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
					int valid = 0;
					m_wmMenuRotation = m_wmMenuTargetRotation;
					const unsigned char stageMode = Game.m_gameWork.m_menuStageMode;
					int i = 0;
					do {
						if (stageMode != 0 && i != 0) {
							break;
						}
						if (m_wmWorldState->m_backupParams[i] >= 0) {
							valid++;
						}
						i++;
					} while (i < 4);
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
		Mtx rotMtx;
		Mtx scaleMtx;
		Mtx selScaleMtx;
		Vec modelPos;

		PSMTXRotRad(baseMtx, 'x', FLOAT_803315d0);
		PSMTXRotRad(rotMtx, 'y', FLOAT_803314bc * -m_wmMenuRotation);
		PSMTXConcat(baseMtx, rotMtx, baseMtx);

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
		for (int i = 0; i < 5; i++) {
			const short curState = m_wmWorldState->m_mainState;
			if (!(((curState > 0) && (curState < 4)) || i == 1)) {
				continue;
			}

			WmWorldObjInfo* const panel = &worldObj[i];
			panel->m_active = 1;
			int frame = 0;
			float modelScale = FLOAT_803315d4;
			if (i == 0) {
				modelScale = static_cast<float>(static_cast<double>(modelScale) * DOUBLE_803315D8);
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
				PSMTXRotRad(scaleMtx, 'x', FLOAT_803315d0);
				PSMTXConcat(modelMtx, scaleMtx, modelMtx);
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
				PSMTXRotRad(selScaleMtx, 'y', rotYSel);
				PSMTXConcat(workMtx, selScaleMtx, workMtx);
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
				PSMTXScale(scaleMtx, openScale, openScale, openScale);
				PSMTXConcat(scaleMtx, modelMtx, modelMtx);
			}

			if (m_wmWorldState->m_nextMenuMode != -1 && i == 1 &&
			    m_wmWorldState->m_cardChannel == 1 && m_wmWorldState->m_mainState != 2) {
				float openScale2 = static_cast<float>(
				    static_cast<float>(DOUBLE_803313F8 * (static_cast<double>(frame) / DOUBLE_80331608)) +
				    DOUBLE_80331420);
				PSMTXScale(scaleMtx, openScale2, openScale2, openScale2);
				PSMTXConcat(scaleMtx, modelMtx, modelMtx);
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
 * PAL Address: 0x800ecff0
 * PAL Size: 2396b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawMainMenuSub()
{
	static const float s_sprt_w[] = {264.0f, 264.0f, 264.0f, 264.0f, 264.0f};
	Mtx modelMtx;
	Mtx44 screenMtx;
	GXColor white;
	float depthValues[5];
	unsigned int drawOrder[5];

	SetProjection(23);
	PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);

	const float zSub = FLOAT_80331598;
	const Vec* posPtr = s_MMenuPos;
	const double scaleX = DOUBLE_803315A0;
	const double one = DOUBLE_80331420;
	const double scaleY = DOUBLE_803315A8;
	const float subX = FLOAT_803315B0;
	const float subY = FLOAT_803315B4;
	const float zero = FLOAT_803313dc;
	for (int i = 0; i < 5; i++) {
		Vec viewPos;
		Vec4d clipPos;
		viewPos.x = posPtr->x;
		viewPos.z = posPtr->z;
		viewPos.y = posPtr->y;
		viewPos.z = viewPos.z - zSub;
		Math.MTX44MultVec4(screenMtx, &viewPos, &clipPos);
		posPtr++;

		clipPos.x = clipPos.x / clipPos.w;
		clipPos.y = clipPos.y / clipPos.w;
		double negY = -static_cast<double>(clipPos.y);
		clipPos.x = static_cast<float>(scaleX * (one + static_cast<double>(clipPos.x)));
		clipPos.y = static_cast<float>(scaleY * (one + negY));
		m_wm.m_worldObjData[i].m_viewportX =
		    static_cast<short>(static_cast<int>(clipPos.x - subX));
		m_wm.m_worldObjData[i].m_viewportY =
		    static_cast<short>(static_cast<int>(clipPos.y - subY));
		m_wm.m_worldObjData[i].m_viewportWidth = 0x280;
		m_wm.m_worldObjData[i].m_viewportHeight = 0x1C0;
		m_wm.m_worldObjData[i].m_cameraPosition.x = zero;
		m_wm.m_worldObjData[i].m_cameraPosition.y = zero;
		m_wm.m_worldObjData[i].m_cameraPosition.z = zSub;
	}

	float* depthPtr = depthValues;
	unsigned int* orderPtr = drawOrder;
	for (unsigned int i = 0; static_cast<int>(i) < 5; i++) {
		PSMTXCopy(m_wm.m_handles[i]->m_model->m_matrix, modelMtx);
		*orderPtr = i;
		orderPtr++;
		*depthPtr = modelMtx[2][3];
		depthPtr++;
	}

	{
		float* fp = depthValues;
		unsigned int* op = drawOrder;
		for (int i = 0; i < 5; i++) {
			int next = i + 1;
			float* fpInner = depthValues + next;
			unsigned int* opInner = drawOrder + next;
			for (int j = next; j < 5; j++) {
				float depth = *fp;
				if (*fp > *fpInner) {
					unsigned int idx = *op;
					unsigned int idxInner = *opInner;
					*fp = *fpInner;
					*op = idxInner;
					*fpInner = depth;
					*opInner = idx;
				}
				fpInner++;
				opInner++;
			}
			op++;
			fp++;
		}
	}

	white.r = 0xFF;
	white.g = 0xFF;
	white.b = 0xFF;
	white.a = 0xFF;
	for (int orderIndex = 0; orderIndex < 5; orderIndex++) {
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
			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1E));
			MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
			GXSetChanMatColor(static_cast<GXChannelID>(4), white);
			unsigned int idx = drawOrder[orderIndex];
			float frameWidth = s_sprt_w[idx];
			MenuPcs.DrawRect3d(0, -(FLOAT_80331414 * (frameWidth / FLOAT_803315B8) - FLOAT_803313dc), FLOAT_803315BC,
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
 * PAL Address: 0x800eb6f8
 * PAL Size: 6328b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
	CFont* fontF8 = m_fonts[0];
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
					goto LAB_next;
				}
				if (animFrames > 10) {
					const float* pD8a = &FLOAT_803314D8;
					yPos = *pD8a;
					const float* pOneA = &FLOAT_803313e8;
					alpha = *pOneA;
				} else {
					const float* pDCa = &FLOAT_803314DC;
					const float* pE0a = &FLOAT_803314E0;
					yPos = *pDCa + static_cast<float>(animFrames) * *pE0a;
					const double* pRateA = &DOUBLE_803314E8;
					alpha = static_cast<float>(*pRateA * static_cast<double>(animFrames));
				}
			} else {
				const float* pD8b = &FLOAT_803314D8;
				yPos = *pD8b;
				const float* pOneB = &FLOAT_803313e8;
				alpha = *pOneB;
			}
			const double* pHalfA = &DOUBLE_803314F0;
			if (!(alpha <= *pHalfA)) {
				const double* pSlopeA = &DOUBLE_80331498;
				const double* pBaseA = &DOUBLE_80331490;
				float slotY = static_cast<float>(*pSlopeA * static_cast<double>(slot) + *pBaseA);
				MenuPcs.SetAttrFmt((FMT)0);
				const float* p255A = &FLOAT_80331458;
				alpha = *p255A * alpha;
				GXColor slotColor;
				slotColor.r = 0xFF;
				slotColor.g = 0xFF;
				slotColor.b = 0xFF;
				slotColor.a = static_cast<unsigned char>(static_cast<int>(alpha));
				GXSetChanMatColor(GX_COLOR0A0, slotColor);

				// Draw slot background
				MenuPcs.SetTexture((TEX)0x24);
				const float* pZb1 = &FLOAT_803313dc;
				const float* pOb1 = &FLOAT_803313e8;
				const float* pW68a = &FLOAT_80331468;
				const float* pHF8a = &FLOAT_803314F8;
				MenuPcs.DrawRect(0, yPos, slotY, *pW68a, *pHF8a,
				         *pZb1, *pZb1,
				         *pOb1, *pOb1, *pZb1);
				MenuPcs.SetTexture((TEX)0x25);
				const float* pW68b = &FLOAT_80331468;
				yPos += *pW68b;
				const float* pZb2 = &FLOAT_803313dc;
				const float* pOb2 = &FLOAT_803313e8;
				const float* pWFCa = &FLOAT_803314FC;
				const float* pHF8b = &FLOAT_803314F8;
				MenuPcs.DrawRect(0, yPos, slotY, *pWFCa, *pHF8b,
				         *pZb2, *pZb2,
				         *pOb2, *pOb2, *pZb2);
				const float* pWFCb = &FLOAT_803314FC;
				yPos += *pWFCb;

				// Draw slot content area
				MenuPcs.SetAttrFmt((FMT)1);
				GXColor contentColors[4];
				contentColors[0].r = 0xFF;
				contentColors[0].g = 0xFF;
				contentColors[0].b = 0xFF;
				const float alpha2 = alpha;
				const float alpha3 = alpha;
				contentColors[0].a = static_cast<unsigned char>(static_cast<int>(alpha3));
				contentColors[1].r = 0xFF;
				contentColors[1].g = 0xFF;
				contentColors[1].b = 0xFF;
				contentColors[1].a = 0;
				contentColors[2].r = 0xFF;
				contentColors[2].g = 0xFF;
				contentColors[2].b = 0xFF;
				contentColors[2].a = static_cast<unsigned char>(static_cast<int>(static_cast<float>(alpha2)));
				contentColors[3].r = 0xFF;
				contentColors[3].g = 0xFF;
				contentColors[3].b = 0xFF;
				contentColors[3].a = 0;
				const float* pOb3 = &FLOAT_803313e8;
				const float* pZb3 = &FLOAT_803313dc;
				const float* pW500 = &FLOAT_80331500;
				const float* pHF8c = &FLOAT_803314F8;
				MenuPcs.DrawRect(0, yPos, slotY, *pW500, *pHF8c,
				         *pZb3, *pZb3, contentColors,
				         *pOb3, *pOb3, *pZb3);
			}
LAB_next:
			slot++;
			slotOff += 3;
		} while (slot < 4);
	}

	float frameAlpha;
	state = worldState->m_mainState;
	if (state == 0) {
		const double* pRateB = &DOUBLE_803314E8;
		frameAlpha = static_cast<float>(*pRateB * static_cast<double>(static_cast<int>(worldState->m_frameCounter)));
	} else if (state > 0 && state < 4) {
		const float* pOneC = &FLOAT_803313e8;
		frameAlpha = *pOneC;
	} else {
		const double* pRateC = &DOUBLE_803314E8;
		const double* pOneD = &DOUBLE_80331420;
		frameAlpha = static_cast<float>(-(*pRateC * static_cast<double>(static_cast<int>(worldState->m_frameCounter)) - *pOneD));
	}
	DrawWMFrame0(2, frameAlpha);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXColor white;
	white.r = 0xFF;
	white.g = 0xFF;
	white.b = 0xFF;
	white.a = 0xFF;
	GXSetChanMatColor(static_cast<GXChannelID>(4), white);
	short separatorSub = worldState->m_subState;
	if (separatorSub != 0 && separatorSub > 1 &&
	    worldState->m_mainState == 2) {
		const float* psZ = &FLOAT_803313dc;
		const double* psSl = &DOUBLE_80331498;
		const double* psBa = &DOUBLE_80331490;
		const double* psOf = &DOUBLE_80331510;
		double sepOff;
		double sepBase;
		double sepSlope;
		float sepZero;
		sepZero = *psZ;
		sepSlope = *psSl;
		sepBase = *psBa;
		sepOff = *psOf;
		for (int slot = 0; slot < kMcListCount; slot++) {
			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1E));
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
		const double* pSl2 = &DOUBLE_80331498;
		const double* pBa2 = &DOUBLE_80331490;
		const double* pOff2 = &DOUBLE_80331510;
		const float* p518a = &FLOAT_80331518;
		double rowBaseD;
		float slotY;
		double mapX;
		double rowSlopeD;
		mapX = *pOff2 + static_cast<double>(*p518a);
		const int language = Game.m_gameWork.m_languageId;
		const int* digitWidths = s_YearWTbl;
		const int* playWidths = s_TimeWTbl;
		rowSlopeD = *pSl2;
		rowBaseD = *pBa2;
		for (slot = 0; slot < kMcListCount; slot++) {
			const McListInfo* const slotData = &m_wmCharaState[slot];
			slotY = static_cast<float>(rowSlopeD * static_cast<double>(slot) + rowBaseD);
			if (slotData->m_isBroken == 0 && slotData->m_hasData != 0) {
				const float* pH40a = &FLOAT_80331440;
				float digitX;
				float rowY = *pH40a + slotY;
				const float* pW68c = &FLOAT_80331468;
				float capX = *pW68c;
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x26));
				const float* pZc1 = &FLOAT_803313dc;
				const float* pOc1 = &FLOAT_803313e8;
				const float* pW68d = &FLOAT_80331468;
				const float* pD8c1 = &FLOAT_803314D8;
				const float* pH40b = &FLOAT_80331440;
				MenuPcs.DrawRect(0, *pW68d, rowY, *pD8c1, *pH40b,
				         *pZc1, *pZc1, *pOc1, *pOc1, *pZc1);

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
				const float* pZc2 = &FLOAT_803313dc;
				const float* pOc2 = &FLOAT_803313e8;
				const float* pD8c3 = &FLOAT_803314D8;
				const float* pH40c = &FLOAT_80331440;
				MenuPcs.DrawRect(8, capX, rowY, *pD8c3, *pH40c,
				         *pZc2, *pZc2,
				         *pOc2, *pOc2, *pZc2);
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x2A));
				const float* pZc3 = &FLOAT_803313dc;
				const float* pOc3 = &FLOAT_803313e8;
				const float* p51ca = &FLOAT_8033151c;
				const float* pH40d = &FLOAT_80331440;
				MenuPcs.DrawRect(0, *p51ca, rowY, static_cast<float>(panelWidth), *pH40d,
				         *pZc3, *pZc3, *pOc3, *pOc3, *pZc3);

				const float* p520a = &FLOAT_80331520;
				digitX = *p520a;
				if (language != 5) {
					const float* pD8c4 = &FLOAT_803314D8;
					rowY = *pD8c4 + slotY;
				}
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x17));
				int digitCount = (static_cast<int>(slotData->m_scriptSysVal0) > 9) + 1;
				if (static_cast<int>(slotData->m_scriptSysVal0) > 99) {
					digitCount = 3;
				}
				if (digitCount == 3) {
					const int dw10 = digitWidths[10];
					const float* pZc4 = &FLOAT_803313dc;
					const float* pOc4 = &FLOAT_803313e8;
					const float* p520b = &FLOAT_80331520;
					const float* p410a = &FLOAT_80331410;
					const float* p524a = &FLOAT_80331524;
					const float* p528a = &FLOAT_80331528;
					MenuPcs.DrawRect(0, *p520b, rowY, static_cast<float>(dw10), *p410a,
					         *p524a, *p528a, *pOc4, *pOc4, *pZc4);
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
					double digitScaleD;
					if (language != 5) {
						const double* pSc530a = &DOUBLE_80331530;
						digitScaleD = *pSc530a;
					} else {
						const double* pSc420a = &DOUBLE_80331420;
						digitScaleD = *pSc420a;
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
						const float* p410b = &FLOAT_80331410;
						const float* pOd1 = &FLOAT_803313e8;
						MenuPcs.DrawRect(0, digitX, rowY, digitWidthF, *p410b,
						         static_cast<float>(colSlope * static_cast<float>(digit % 5)),
						         static_cast<float>(rowSlope * static_cast<float>(digit / 5) + rowBase),
						         digitScale, *pOd1, zeroF);
						digitX += digitWidthF * digitScale;
					}
					float suffixU;
					float suffixWidth;
					if (language == 2) {
						const float* pSw548 = &FLOAT_80331548;
						suffixWidth = *pSw548;
					} else if (language == 3) {
						const float* pSw54C = &FLOAT_8033154C;
						suffixWidth = *pSw54C;
					} else {
						const float* pSw410 = &FLOAT_80331410;
						suffixWidth = *pSw410;
					}
					const float* pZd2 = &FLOAT_803313dc;
					suffixU = *pZd2;
					unsigned char wideLang = (language == 1 || language == 4);
					double suffixScaleD;
					if (wideLang) {
						const double* pSc530b = &DOUBLE_80331530;
						suffixScaleD = *pSc530b;
					} else {
						const double* pSc420b = &DOUBLE_80331420;
						suffixScaleD = *pSc420b;
					}
					float suffixScale = static_cast<float>(suffixScaleD);
					if (language == 1) {
						if (static_cast<int>(slotData->m_scriptSysVal0) / 10 == 1) {
							const float* pSu51c1 = &FLOAT_8033151c;
							suffixU = *pSu51c1;
						} else {
							const int ones = static_cast<int>(slotData->m_scriptSysVal0) % 10;
							if (ones >= 1 && ones <= 3) {
								const float* pSuD8 = &FLOAT_803314D8;
								suffixU = *pSuD8 * static_cast<float>(ones - 1);
							} else {
								const float* pSu51c2 = &FLOAT_8033151c;
								suffixU = *pSu51c2;
							}
						}
					} else if (language == 4) {
						if (static_cast<int>(slotData->m_scriptSysVal0) != 1) {
							const float* pSuD8b = &FLOAT_803314D8;
							suffixU = *pSuD8b;
						}
					} else if (language == 2) {
						const float* pRy550 = &FLOAT_80331550;
						rowY += *pRy550;
					}
					if (language != 5) {
						MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x34));
						const float* pZd3 = &FLOAT_803313dc;
						const float* pOd2 = &FLOAT_803313e8;
						const float* pD8d1 = &FLOAT_803314D8;
						MenuPcs.DrawRect(0, digitX, rowY, suffixWidth, *pD8d1,
						         *pZd3, suffixU, suffixScale, *pOd2, *pZd3);
					}
				}

				const float* pLx520 = &FLOAT_80331520;
				float labelX = *pLx520;
				float dateLabelY;
				if (language != 5) {
					const float* pDl554 = &FLOAT_80331554;
					dateLabelY = *pDl554 + slotY;
				} else {
					const float* pDlc8 = &FLOAT_803314c8;
					const float* pDlD8 = &FLOAT_803314D8;
					dateLabelY = *pDlc8 + (*pDlD8 + slotY);
				}
				const float* pLx550 = &FLOAT_80331550;
				labelX -= *pLx550;
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x21));
				const float* pZe1 = &FLOAT_803313dc;
				const float* pOe1 = &FLOAT_803313e8;
				const float* pH40e = &FLOAT_80331440;
				const float* p558a = &FLOAT_80331558;
				MenuPcs.DrawRect(0, labelX, dateLabelY,
				         *pH40e, *p558a, *pZe1, *pZe1,
				         *pOe1, *pOe1, *pZe1);

				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x37));
				const float* p55Ca = &FLOAT_8033155C;
				float iconX = *p55Ca;
				const float* pD8e1 = &FLOAT_803314D8;
				const float iconY = *pD8e1 + slotY;
				const int* memberPtr = slotData->m_characterIds;
				for (int member = 0; member < 4; member++, memberPtr++) {
					const int modelNo = *memberPtr;
					if (modelNo >= 0) {
						const int faceNo = modelNo - 100;
						float texU;
						if ((faceNo / 100 & 1) != 0) {
							const float* p560a = &FLOAT_80331560;
							texU = *p560a;
						} else {
							const double* pHf1 = &DOUBLE_803314F0;
							texU = static_cast<float>(*pHf1);
						}
						const float* pW68e = &FLOAT_80331468;
						const float du = static_cast<float>(faceNo % 100) * *pW68e;
						texU += du;
						const float* pZe2 = &FLOAT_803313dc;
						const float* pOe2 = &FLOAT_803313e8;
						const float* pW68f = &FLOAT_80331468;
						MenuPcs.DrawRect(0, iconX, iconY, *pW68f, *pW68f,
						         texU,
						         static_cast<float>(faceNo / 100 / 2) * *pW68f,
						         *pOe2, *pOe2, *pZe2);
						const float* pW68g = &FLOAT_80331468;
						iconX += *pW68g;
					}
				}
				const float* pW68h = &FLOAT_80331468;
				rowY = *pW68h + slotY;
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x20));
				const float* pZe3 = &FLOAT_803313dc;
				const float* pOe3 = &FLOAT_803313e8;
				const float* p564a = &FLOAT_80331564;
				const float* p554a = &FLOAT_80331554;
				const float* pD8e2 = &FLOAT_803314D8;
				MenuPcs.DrawRect(0, *p564a, rowY,
				         *p554a, *pD8e2, *pZe3, *pZe3,
				         *pOe3, *pOe3, *pZe3);

				int playHours;
				int playMinutes;
				MemoryCardMan.CnvPlayTime(slotData->m_frameCounter, &playHours, &playMinutes);
				int playDigits[5];
				const float* pZe4 = &FLOAT_803313dc;
				float playWidth = *pZe4;
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
				const float* p518b = &FLOAT_80331518;
				float playX = *p518b - playWidth;
				for (int digitIdx = 0; digitIdx < 5; digitIdx++) {
					if (playDigits[digitIdx] >= 0) {
						if (digitIdx == 3) {
							const float colonW = static_cast<float>(playWidths[10]);
							const float* pZe5 = &FLOAT_803313dc;
							const float* pOe5 = &FLOAT_803313e8;
							const float* p568a = &FLOAT_80331568;
							const float* pD8e3 = &FLOAT_803314D8;
							MenuPcs.DrawRect(0, playX, rowY, colonW, *pD8e3,
							         *p568a, *pZe5, *pOe5, *pOe5, *pZe5);
							playX += colonW;
						}
						const float digitW = static_cast<float>(playWidths[playDigits[digitIdx]]);
						const float* pZe6 = &FLOAT_803313dc;
						const float* pOe6 = &FLOAT_803313e8;
						const float* pD8e4 = &FLOAT_803314D8;
						const double* pCs2 = &DOUBLE_80331490;
						const double* p570a = &DOUBLE_80331570;
						MenuPcs.DrawRect(0, playX, rowY, digitW, *pD8e4,
						         static_cast<float>(*pCs2 * static_cast<double>(playDigits[digitIdx]) + *p570a),
						         *pZe6, *pOe6, *pOe6, *pZe6);
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
		const double* pSl3 = &DOUBLE_80331498;
		const double tSlope = *pSl3;
		const double* pBa3 = &DOUBLE_80331490;
		const double tBase = *pBa3;
		for (slot = 0; slot < kMcListCount; slot++) {
			char locationStr[64];
			char line1[64];
			char line2[64];
			const McListInfo* const slotData = &m_wmCharaState[slot];
			const float slotY = static_cast<float>(tSlope * static_cast<double>(slot) + tBase);
			if (slotData->m_isBroken != 0 || static_cast<int>(slotData->m_scriptSysVal0) <= 0) {
				const float* pMa1 = &FLOAT_803313e8;
				fontF8->SetMargin(*pMa1);
				fontF8->SetShadow(1);
				const float* pSa1 = &FLOAT_803313e8;
				fontF8->SetScale(*pSa1);
				fontF8->DrawInit();
				fontF8->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
				fontF8->SetTlut(0x19);
				const unsigned int msgId =
					slotData->m_isBroken == 0;
				const int width = static_cast<int>(fontF8->GetWidth(const_cast<char*>(GetMcStr(msgId))));
				const double* pHd1 = &DOUBLE_803313F8;
				const float* pD8f1 = &FLOAT_803314D8;
				fontF8->SetPosX(static_cast<float>(static_cast<float>(0x238 - width) * *pHd1 + *pD8f1));
				const double* p580a = &DOUBLE_80331580;
				fontF8->SetPosY(static_cast<float>(*p580a + static_cast<double>(slotY)));
				fontF8->Draw(const_cast<char*>(GetMcStr(msgId)));
			} else {
				const float* pMa2 = &FLOAT_803313e8;
				fontF8->SetMargin(*pMa2);
				fontF8->SetShadow(0);
				const float* pSa2 = &FLOAT_80331588;
				fontF8->SetScale(*pSa2);
				fontF8->DrawInit();
				fontF8->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
				fontF8->SetTlut(0x2C);
				const float* pPx520 = &FLOAT_80331520;
				fontF8->SetPosX(*pPx520);
				const double* pOff4 = &DOUBLE_80331510;
				fontF8->SetPosY(static_cast<float>(static_cast<double>(slotY) - *pOff4));
				strcpy(locationStr, slotData->m_townName);
				if (locationStr[0] != 0) {
					locationStr[0] = static_cast<char>(toupperLatin1(static_cast<unsigned char>(locationStr[0])));
				}
				fontF8->Draw(locationStr);

				const float* pMa3 = &FLOAT_803313e8;
				fontF8->SetMargin(*pMa3);
				fontF8->SetShadow(1);
				const float* pSa3 = &FLOAT_8033158C;
				fontF8->SetScale(*pSa3);
				fontF8->DrawInit();
				fontF8->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
				fontF8->SetTlut(7);
				const int locationIndex = slotData->m_scriptGlobalTime;
				if (locationIndex == 0x0F) {
					strcpy(locationStr, slotData->m_townName);
				} else if (locationIndex == 0x16) {
					const int lang2 = Game.m_gameWork.m_languageId;
					if (lang2 == 2) {
						strcpy(locationStr, slotData->m_townName);
						strcat(locationStr, s_port[lang2 - 1]);
					} else {
						strcpy(locationStr, s_port[lang2 - 1]);
						strcat(locationStr, slotData->m_townName);
					}
				} else {
					strcpy(locationStr, Game.m_cFlatDataArr[1].TableStrings(3)[locationIndex]);
				}
				if (locationStr[0] != 0) {
					locationStr[0] = static_cast<char>(toupperLatin1(static_cast<unsigned char>(locationStr[0])));
				}
				const float locationWidth = fontF8->GetWidth(locationStr);
				const float* p558b = &FLOAT_80331558;
				float locationY = *p558b + slotY;
				const float* p55Cb = &FLOAT_8033155C;
				if (locationWidth <= *p55Cb) {
					const float* p518c = &FLOAT_80331518;
					fontF8->SetPosX(*p518c - locationWidth);
					fontF8->SetPosY(locationY);
					fontF8->Draw(locationStr);
				} else {
					const float* p550a = &FLOAT_80331550;
					locationY = locationY + *p550a;
					SplitPlace2(locationStr, line1, line2, fontF8, 0x90);
					const float w1 = fontF8->GetWidth(line1);
					const float* p518d = &FLOAT_80331518;
					fontF8->SetPosX(*p518d - w1);
					const float* p590a = &FLOAT_80331590;
					fontF8->SetPosY(locationY - *p590a);
					fontF8->Draw(line1);
					const float w2 = fontF8->GetWidth(line2);
					const float* p518e = &FLOAT_80331518;
					fontF8->SetPosX(*p518e - w2);
					fontF8->SetPosY(locationY);
					fontF8->Draw(line2);
				}
			}
		}
	}
	if (worldState->m_subState == 0x11) {
		short mode = worldState->m_menuMode;
		if (mode == 5) {
			GXColor color = CColor(0xFF, 0xFF, 0xFF, 0xFF).color;
			char* text = const_cast<char*>(GetMcStr(2));
			char* text2 = const_cast<char*>(GetMcStr(2));
			const float* pWf1 = &FLOAT_80331594;
			const float* pHf3 = &FLOAT_803313e8;
			const int x = static_cast<int>(CalcCenteringPos2(text2, *pWf1, *pHf3));
			const float* pWf2 = &FLOAT_80331594;
			const float* pHf4 = &FLOAT_803313e8;
			DrawFont2(x, 0x187, color, 7, text, *pWf2, *pHf4, *pHf4);
		} else if (mode == 2) {
			GXColor color = CColor(0xFF, 0xFF, 0xFF, 0xFF).color;
			char* text = const_cast<char*>(GetMcStr(3));
			char* text2 = const_cast<char*>(GetMcStr(3));
			const float* pWf3 = &FLOAT_80331594;
			const float* pHf5 = &FLOAT_803313e8;
			const int x = static_cast<int>(CalcCenteringPos2(text2, *pWf3, *pHf5));
			const float* pWf4 = &FLOAT_80331594;
			const float* pHf6 = &FLOAT_803313e8;
			DrawFont2(x, 0x187, color, 7, text, *pWf4, *pHf6, *pHf6);
		}
	}
	DrawInit();
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
inline void CMenuPcs::DrawHelpBase(int kind, float baseAlpha)
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);
	WmWorldState* const worldState = m_wmWorldState;
	float alpha = baseAlpha;

	if (alpha <= 0.0f) {
		alpha = 1.0f;
	}

	if (worldState != 0) {
		const short state = worldState->m_mainState;
		if (state == 0) {
			alpha *= static_cast<float>(worldState->m_frameCounter) * 0.1f;
		} else if (state >= 3) {
			alpha *= 1.0f - static_cast<float>(worldState->m_frameCounter) * 0.1f;
		}
	}
	if (alpha < 0.0f) {
		alpha = 0.0f;
	} else if (alpha > 1.0f) {
		alpha = 1.0f;
	}

	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXColor color = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * alpha)};
	GXSetChanMatColor(static_cast<GXChannelID>(4), color);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kind == 0 ? 0x1F : 0x20));
	MenuPcs.DrawRect(0xFFFFFFFF, 0.0f, 0x1A8, 0x280, 0x18, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
}

/*
 * --INFO--
 * PAL Address: 0x800eb1d8
 * PAL Size: 1312b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcMcObj()
{
	WmWorldObjInfo* const worldObj = m_wm.m_worldObjData;

	const float* pPanelF = &FLOAT_80331480;
	const float panelStateFloat = *pPanelF;

	const double* pY48 = &DOUBLE_80331488;
	const double* pY88 = &DOUBLE_80331498;
	const double* pY24 = &DOUBLE_80331490;
	const float* pY112 = &FLOAT_803314A0;
	const float* pZeroP = &FLOAT_803313dc;
	const float* p50 = &FLOAT_803314A4;
	const double* p25 = &DOUBLE_803314A8;

	int i;
	WmWorldObjInfo* panelState = &worldObj[17];
	for (i = 0; i < 4; i++, panelState++) {
		panelState->m_viewportX = static_cast<short>(panelStateFloat);

		const int y = static_cast<int>(
		    static_cast<float>(*pY48 + (*pY88 * static_cast<double>(i) + *pY24)) -
		    *pY112);
		panelState->m_viewportY = static_cast<short>(y);
		panelState->m_viewportWidth = 0x140;
		panelState->m_viewportHeight = 0xE0;
		panelState->m_cameraPosition.x = *pZeroP;
		panelState->m_cameraPosition.y = *pZeroP;
		panelState->m_cameraPosition.z = *p50;

		const McListInfo* const charaState = &m_wmCharaState[i];
		CMenuPcs::FCV* const yTbl = &s_WoodTrns;
		panelState->m_frameCounter++;
		if (static_cast<float>(static_cast<int>(panelState->m_frameCounter)) >=
		    *p25 * static_cast<double>(yTbl->keys[s_WoodTrns.keyCount - 1].time)) {
			panelState->m_frameCounter = 0;
		}

		if (static_cast<int>(charaState->m_scriptSysVal0) <= 0) {
			panelState->m_active = 0;
		} else {
			Mtx scaleMtx;
			Mtx rotXMtx;
			Mtx rotYMtx;

			const float* pB0 = &FLOAT_803314B0;
			const float* pB4 = &FLOAT_803314B4;
			const float* pZeroB = &FLOAT_803313dc;
			const float* pHalfB = &FLOAT_80331434;
			const float* pB8 = &FLOAT_803314B8;
			const float* pBC = &FLOAT_803314bc;
			panelState->m_active = 1;
			panelState->m_transform.m_position.x = *pB0;
			panelState->m_transform.m_position.y = *pB4;
			panelState->m_transform.m_position.z = *pZeroB;
			panelState->m_transform.m_scale.x = *pHalfB;
			panelState->m_transform.m_scale.y = *pHalfB;
			panelState->m_transform.m_scale.z = *pHalfB;
			panelState->m_transform.m_rotation.x = *pB8;
			panelState->m_transform.m_rotation.y = panelState->m_transform.m_rotation.y + *pBC;

			panelState->m_transform.m_position.y =
			    panelState->m_transform.m_position.y +
			    static_cast<float>(GetFcvValue(s_WoodTrns,
			                                   static_cast<float>(static_cast<int>(panelState->m_frameCounter))));

			const float rotVal =
			    static_cast<float>(GetFcvValue(s_WoodRot,
			                                   static_cast<float>(static_cast<int>(panelState->m_frameCounter))));
			const float* pBC2 = &FLOAT_803314bc;
			panelState->m_transform.m_rotation.y = *pBC2 * rotVal;
			PSMTXScale(scaleMtx, panelState->m_transform.m_scale.x, panelState->m_transform.m_scale.y,
			           panelState->m_transform.m_scale.z);
			PSMTXRotRad(rotXMtx, 'x', panelState->m_transform.m_rotation.x);
			PSMTXRotRad(rotYMtx, 'y', panelState->m_transform.m_rotation.y);
			PSMTXConcat(rotXMtx, rotYMtx, rotXMtx);
			rotXMtx[0][3] = panelState->m_transform.m_position.x;
			rotXMtx[1][3] = panelState->m_transform.m_position.y;
			rotXMtx[2][3] = panelState->m_transform.m_position.z;
			PSMTXConcat(rotXMtx, scaleMtx, scaleMtx);

			m_wm.m_handles[i + 17]->m_model->SetMatrix(scaleMtx);
			m_wm.m_handles[i + 17]->m_model->CalcMatrix();
			m_wm.m_handles[i + 17]->m_model->CalcSkin();
		}
	}
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

	if (cameraSlot < 0) {
		cameraSlot = slot;
	}

	EffectInfo* effect = &m_effectWork[slot];
	if (slot == 5 && effectNo < 0x13) {
		effect++;
	} else if (slot >= 0x11 && slot <= 0x14 && effectNo > 0x19) {
		effect += 4;
	}

	const bool group = (effect->m_effectNo = effectNo) > 100;
	CGObject* const object = &effect->m_object;
	effect->m_slotNo = slot;
	object->Create();
	object->m_charaModelHandle = m_wm.m_handles[cameraSlot];

	createParam.m_lookTargetPtr = object;
	createParam.m_paramB = reinterpret_cast<unsigned int>(object);

	const unsigned int partId = PartMng.pppCreate(group, effectNo, &createParam, 1);
	effect->m_partNo = partId;
	return effect->m_partNo;
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
		u0 = tx + halfTexel;
		u1 = (tx + w) - halfTexel;
	}

	if ((flags & 4) != 0) {
		v1 = ty + halfTexel;
		v0 = (v1 + h) - halfTexel;
	} else {
		v0 = ty + halfTexel;
		v1 = (ty + h) - halfTexel;
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
	float u0;
	float v1;
	float v0;

	if ((flags & 8) != 0) {
		u1 = tx + halfTexel;
		u0 = (tx + w) - halfTexel;
	} else {
		u0 = tx + halfTexel;
		u1 = (tx + w) - halfTexel;
	}

	if ((flags & 4) != 0) {
		v1 = ty + halfTexel;
		v0 = (ty + h) - halfTexel;
	} else {
		v0 = ty + halfTexel;
		v1 = (ty + h) - halfTexel;
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
 * PAL Address: 0x800ea4f4
 * PAL Size: 1528b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawMcWin(short state, short kind)
{
	if (state >= 0 && m_menuWindowInfo->state != state) {
		m_menuWindowInfo->state = state;
	}

	if (m_menuWindowInfo->state == 3) {
		return;
	}

	const float centerX = static_cast<float>(m_menuWindowInfo->x) + static_cast<float>(static_cast<double>(m_menuWindowInfo->width) * DOUBLE_803313F8);
	const float centerY = static_cast<float>(m_menuWindowInfo->y) + static_cast<float>(static_cast<double>(m_menuWindowInfo->height) * DOUBLE_803313F8);

	float right;
	float sw;
	float sy;
	float sh;
	float sx;
	float bottom;
	if (m_menuWindowInfo->state != 1) {
		const float xAdd = (((centerX - static_cast<float>(m_menuWindowInfo->x)) - FLOAT_80331410) / FLOAT_80331414) * static_cast<float>(m_menuWindowInfo->frame);
		const float yAdd = (((centerY - static_cast<float>(m_menuWindowInfo->y)) - FLOAT_80331410) / FLOAT_80331414) * static_cast<float>(m_menuWindowInfo->frame);
		sx = (centerX - FLOAT_80331410) - xAdd;
		sy = (centerY - FLOAT_80331410) - yAdd;
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

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((kind != 0) ? 0x24 : 0x2C));
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

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((kind != 0) ? 0x26 : 0x2D));
	const double innerWidthD = static_cast<double>(sw) - DOUBLE_80331428;
	const float innerX = FLOAT_80331410 + sx;
	const float* pZw2 = &FLOAT_803313dc;
	const float uv1 = *pZw2;
	const float innerWidthF = static_cast<float>(innerWidthD);
	float y = sy;
	for (rectIdx = 0; rectIdx < 2; rectIdx++) {
		flags = 0;
		if (rectIdx != 0) {
			y = bottom;
			flags |= 4;
		}
		MenuPcs.DrawRect(flags, innerX, y, innerWidthF, FLOAT_80331410, uv1, uv1, FLOAT_803313e8, FLOAT_803313e8, uv1);
	}

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((kind != 0) ? 0x25 : 0x2E));
	const double innerHeightD = static_cast<double>(sh) - DOUBLE_80331428;
	const float innerY = FLOAT_80331410 + sy;
	const float* pZw3 = &FLOAT_803313dc;
	const float uv2 = *pZw3;
	const float innerHeightF = static_cast<float>(innerHeightD);
	float x = sx;
	for (rectIdx = 0; rectIdx < 2; rectIdx++) {
		flags = 0;
		if (rectIdx != 0) {
			x = right;
			flags |= 8;
		}
		MenuPcs.DrawRect(flags, x, innerY, FLOAT_80331410, innerHeightF, uv2, uv2, FLOAT_803313e8, FLOAT_803313e8, uv2);
	}

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((kind != 0) ? 0x27 : 0x2F));
	const float* pZw4 = &FLOAT_803313dc;
	const float uv3 = *pZw4;
	MenuPcs.DrawRect(flags, innerX, innerY, static_cast<float>(innerWidthD), static_cast<float>(innerHeightD), uv3, uv3, FLOAT_803313e8, FLOAT_803313e8, uv3);

	if (m_menuWindowInfo->state == 0) {
		m_menuWindowInfo->frame++;
		if (m_menuWindowInfo->frame >= 6) {
			m_menuWindowInfo->frame = 6;
			m_menuWindowInfo->state = 1;
		}
	} else if (m_menuWindowInfo->state == 1) {
		if (m_menuWindowInfo->frame != 6) {
			m_menuWindowInfo->frame = 6;
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
 * PAL Address: 0x800ea150
 * PAL Size: 932b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawMcWinMess(int winType, int messType)
{
	static const char* s_SlotStr[] = {"Slot A", "Steckplatz A", "Slot A", "Slot A", "Ranura A"};
	static const char* s_DataStr[] = {"Data 1", "Datenblock 1", "Salvataggio 1", "sauvegarde 1", "Archivo 1"};

	CFont* const font = m_fonts[0];

	const float* pOneM = &FLOAT_803313e8;
	font->SetMargin(*pOneM);
	font->SetShadow(0);
	font->SetScale(*pOneM);
	font->DrawInit();

	font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
	font->SetTlut(0x23);

	const char* const* msgTable = GetMcWinMessBuff(messType);
	const int languageIndex = Game.m_gameWork.m_languageId - 1;
	const WinMessEntry* const winMess = GetWinMess(winType);

	float lineHeight;
	float posX;
	if (winType != 0) {
		int maxWidth = 0;
		for (int i = 0; i < winMess->m_lineCount; i++) {
			const short msgId = winMess->m_messageIds[i];
			const char* text = msgTable[msgId];
			if (text != 0) {
				if (text[0] == '$') {
					text++;
				}
				const int width = font->GetWidth(const_cast<char*>(text));
				if (width > maxWidth) {
					maxWidth = width;
				}
			}
		}
		const double* pHalfW = &DOUBLE_803313F8;
		posX = static_cast<float>(static_cast<double>(m_menuWindowInfo->width - maxWidth) * *pHalfW +
		                          static_cast<double>(static_cast<int>(m_menuWindowInfo->x)));
	}

	float y = static_cast<float>(m_menuWindowInfo->y + 0x20);
	const float* pLineH = &FLOAT_80331404;
	lineHeight = *pLineH;

	char textBuf[128];
	for (int i = 0; i < winMess->m_lineCount; i++) {
		const short msgId = winMess->m_messageIds[i];
		int isDollar = 0;
		if ((int)strlen(msgTable[msgId]) != 0) {
			if (msgTable[msgId][0] == '$') {
				strcpy(textBuf, msgTable[msgId] + 1);
				isDollar = 1;
			} else {
				strcpy(textBuf, msgTable[msgId]);
			}

			if (winType == 0 || isDollar != 0) {
				const double* pHalfW2 = &DOUBLE_803313F8;
				const int textWidth = font->GetWidth(textBuf);
				posX = static_cast<float>(static_cast<double>(m_menuWindowInfo->width - textWidth) * *pHalfW2 +
				                          static_cast<double>(static_cast<int>(m_menuWindowInfo->x)));
			}
			font->SetPosX(posX);
			font->SetPosY(y);
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
			font->Draw(textBuf);
		}
		y += lineHeight;
	}

	DrawInit();
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
 * PAL Address: 0x800e9c8c
 * PAL Size: 896b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::BindMcObj()
{
	unsigned char* const bytes = reinterpret_cast<unsigned char*>(this);

	for (int i = 0; i < 4; i++) {
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

	for (int i = 0; i < 4; i++) {
		const McListInfo& charaState = m_wmCharaState[i];
		const int modelNo = charaState.m_timerA;

		if (modelNo != 0) {
			PPPCREATEPARAM createParam;

			const int slot = i + 0x11;
			EffectInfo* effect = &m_effectWork[slot];
			if (slot == 5 && modelNo + 0x16 < 0x13) {
				effect++;
			} else if (i + 0x11 >= 0x11 && i + 0x11 <= 0x14 && modelNo + 0x16 > 0x19) {
				effect += 4;
			}

			const bool group = (effect->m_effectNo = modelNo + 0x16) > 100;
			CGObject* const object = &effect->m_object;
			effect->m_slotNo = i + 0x11;
			object->Create();
			object->m_charaModelHandle = m_wm.m_handles[slot];
			createParam.m_lookTargetPtr = object;
			createParam.m_paramB = reinterpret_cast<unsigned int>(object);
			effect->m_partNo =
			    PartMng.pppCreate(group, modelNo + 0x16, &createParam, 1);
		}

		const unsigned int flags = charaState.m_chaliceElement;
		int weaponModel;
		if ((flags & 1) != 0) {
			weaponModel = 0;
		} else if ((flags & 2) != 0) {
			weaponModel = 1;
		} else if ((flags & 4) != 0) {
			weaponModel = 2;
		} else if ((flags & 8) != 0) {
			weaponModel = 3;
		} else if ((flags & 0x10) != 0) {
			weaponModel = 4;
		}

		PPPCREATEPARAM createParam;

		const int slot = i + 0x11;
		EffectInfo* effect = &m_effectWork[slot];
		if (slot == 5 && weaponModel + 0x1A < 0x13) {
			effect++;
		} else if (i + 0x11 >= 0x11 && i + 0x11 <= 0x14 && weaponModel + 0x1A > 0x19) {
			effect += 4;
		}

		const bool group = (effect->m_effectNo = weaponModel + 0x1A) > 100;
		CGObject* const object = &effect->m_object;
		effect->m_slotNo = i + 0x11;
		object->Create();
		object->m_charaModelHandle = m_wm.m_handles[slot];
		createParam.m_lookTargetPtr = object;
		createParam.m_paramB = reinterpret_cast<unsigned int>(object);
		effect->m_partNo =
		    PartMng.pppCreate(group, weaponModel + 0x1A, &createParam, 1);
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
	_GXSetBlendMode(static_cast<_GXBlendMode>(1), static_cast<_GXBlendFactor>(4), static_cast<_GXBlendFactor>(5), static_cast<_GXLogicOp>(1));

	GXBegin(GX_QUADS, GX_VTXFMT0, 4);
	const float* pTall = &FLOAT_803313e4;
	const float* pWide = &FLOAT_803313e0;
	const float* pZero = &FLOAT_803313dc;
	float tall = *pTall;
	float wide = *pWide;
	float zero = *pZero;
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
	memcpy(outSave, MemoryCardMan.m_saveBuffer, 0x8BD0);
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
	memcpy(MemoryCardMan.m_saveBuffer, saveDat, 0x8BD0);
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
 * PAL Address: 0x800e9348
 * PAL Size: 1404b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
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
			if (closeResult != 0) {
				m_lastResult = closeResult;
				m_state = -1;
			} else {
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
					if (closeResult != 0) {
						m_lastResult = closeResult;
						m_state = -1;
					} else {
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
 * PAL Address: 0x800e902c
 * PAL Size: 796b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::SetListDat(int slot, int clearScriptSysVal0)
{
	McListInfo entry;
	Mc::SaveDat* const save = reinterpret_cast<Mc::SaveDat*>(MemoryCardMan.m_saveBuffer);
	memset(&entry, 0, sizeof(entry));

	if (save->m_townName[0] != 0) {
		const int formatMatch = memcmp(save->m_version, DAT_8032E8A8, 4);
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
 * PAL Address: 0x800e8738
 * PAL Size: 2292b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
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
			if (Game.m_gameWork.m_mcHasSerial == 0) {
				Game.m_gameWork.m_mcSerial = serial;
				Game.m_gameWork.m_mcRandom = Math.Rand(0x7FFFFFFF);
				Game.m_gameWork.m_mcHasSerial = 1;
			}
			m_serial = serial;
			MemoryCardMan.CreateMcBuff();
			if (m_userBuffer == 0) {
				MemoryCardMan.MakeSaveData();
			} else {
				memcpy(MemoryCardMan.m_saveBuffer, m_userBuffer, 0x8BD0);
			}
			MemoryCardMan.McWrite(0, 0xA000, m_saveIndex * 0xA000 + 0x4000);
			m_state = 0x13;
		} else {
			MemoryCardMan.McClose();
			MemoryCardMan.McUnmount(m_cardChannel);
			MemoryCardMan.DestroyMcBuff();
			m_state = -1;
			return -1;
		}
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
			if (closeResult != 0) {
				m_lastResult = closeResult;
				m_state = -1;
			} else {
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
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
					memcpy(m_userBuffer, MemoryCardMan.m_saveBuffer, 0x8BD0);
					MemoryCardMan.CalcSaveDatHpMax(reinterpret_cast<Mc::SaveDat*>(m_userBuffer));
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
 * PAL Address: 0x800e80f0
 * PAL Size: 528b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
					m_state = -1;
					return -2;
				}
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
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
 * PAL Address: 0x800e7dc8
 * PAL Size: 808b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int McCtrl::ChkEmpty(int param_2)
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
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
					m_state = -1;
					return -3;
				}

				if (m_lastResult == -6)
				{
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
					m_state = -1;
					return -4;
				}

				if (m_lastResult == -5)
				{
					MemoryCardMan.m_opDoneFlag = 1;
					MemoryCardMan.m_currentSlot = 0xFF;
					m_state = -1;
					return -5;
				}

				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = 0xFF;
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
				if (param_2 == 0)
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
 * PAL Address: 0x800e78f8
 * PAL Size: 1108b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
			int iVar3 = m_lastResult;

			if (iVar3 < 0)
			{
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = 0xFF;

				if (iVar3 == -6)
				{
					m_state = 2;
				}
				else
				{
					if (iVar3 == -0x0D)
					{
						m_state = -1;
						return -0x0D;
					}

					if (iVar3 == -5)
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
				if (r != 0)
				{
					m_lastResult = r;
					m_state = -1;
				}
				else
				{
					MemoryCardMan.McUnmount(m_cardChannel);

					Mc::SaveDat* saveDat = reinterpret_cast<Mc::SaveDat*>(MemoryCardMan.m_saveBuffer);
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
 * PAL Address: 0x800e7430
 * PAL Size: 1224b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
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

		Mc::SaveDat* const save = reinterpret_cast<Mc::SaveDat*>(MemoryCardMan.m_saveBuffer);
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
			if (!(closeResult == 0)) {
				m_lastResult = closeResult;
				m_state = -1;
			} else {
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
 * PAL Address: 0x800e6b98
 * PAL Size: 2200b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
				MemoryCardMan.m_opDoneFlag = 1;
				MemoryCardMan.m_currentSlot = static_cast<char>(0xFF);
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
			if (closeResult != 0) {
				m_lastResult = closeResult;
				m_state = -1;
			} else {
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
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::SetDataBuff(char* buffer)
{
	m_userBuffer = buffer;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::SetDno(int channel)
{
	m_cardChannel = channel;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void McCtrl::SetSlot(int slot)
{
	m_saveIndex = slot;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::AlphaNormal()
{
	s_MaxAnimWait = FLOAT_803313dc;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::AlphaAdd()
{
	s_MaxAnimWait = FLOAT_803315d4;
}

#include "ffcc/MenuUtil.h"
#include "ffcc/partMng.h"
#include "ffcc/game.h"
#include "ffcc/gobjwork.h"
#include "ffcc/memory.h"
#include "ffcc/menu_arti.h"
#include "ffcc/mes.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include "ffcc/fontman.h"
#include "ffcc/strcase.h"
#include "ffcc/util.h"
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/string.h>
#include <math.h>

struct MenuOptionEstandarData {
	char m_text[0x0C];
	int m_helpLineBaseY[7];
	f32 m_layout[68];
};

// Disc-path constants for CGame::SetGbaSP().  The method is dead-stripped from
// this build's .text, but its string constants are still emitted into
// MenuUtil.o's .rodata.  Being the first constants in the translation unit they
// anchor the rodata pool base register used by the option-menu draw routines.
__declspec(section ".rodata") static const char s_dvd_gba_801E3058[] = "dvd/gba/";
__declspec(section ".rodata") static const char s_ffcc_cli_bin_801E3060[] = "ffcc_cli.bin";
__declspec(section ".rodata") static const char s_objdat_spt_801E3070[] = "objdat.spt";
__declspec(section ".rodata") static const char s_icon_dat_801E307C[] = "icon.dat";
static const char s_FF_Crystal_Chronicles_801E3088[] = "FF Crystal Chronicles";

extern "C" const char s_MenuOptionMusic[] = "Music";
extern "C" const char s_MenuOptionOn[] = "On";
extern "C" const char s_MenuOptionOff[] = "Off";
extern "C" const char s_MenuOptionStereo[] = "Stereo";
extern "C" const char s_MenuOptionMin[] = "Min";
extern "C" const char s_MenuOptionMax[] = "Max";
extern "C" const char s_MenuOptionStrengthDe[] = {'S', 't', '\xe4', 'r', 'k', 'e', '\0', '\0'};
extern "C" const char s_MenuOptionDefenceDe[] = "Abwehr";
extern "C" const char s_MenuOptionMusicDe[] = "Musik";
extern "C" const char s_MenuOptionOnDe[] = "AN";
extern "C" const char s_MenuOptionOffDe[] = "AUS";
extern "C" const char s_MenuOptionStereoDe[] = "STEREO";
extern "C" const char s_MenuOptionMonoUpper[] = "MONO";
extern "C" const char s_MenuOptionNormalIt[] = "Normal";
extern "C" const char s_MenuOptionForza[] = "Forza";
extern "C" const char s_MenuOptionDifesa[] = "Difesa";
extern "C" const char s_MenuOptionSonoro[] = "Sonoro";
extern "C" const char s_MenuOptionMusicaIt[] = "Musica";
extern "C" const char s_MenuOptionMonoIt[] = "Mono";
extern "C" const char s_MenuOptionContr[] = "Contr.";
extern "C" const char s_MenuOptionNorm[] = "Norm.";
extern "C" const char s_MenuOptionForceFr[] = "Force";
extern "C" const char s_MenuOptionMusiqueFr[] = "Musique";
extern "C" const char s_MenuOptionActiveFr[8] = "Activ\351";
extern "C" const char s_MenuOptionStereoFr[8] = "St\351r\351o";
extern "C" const char s_MenuOptionFuerzaEs[] = "Fuerza";
extern "C" const char s_MenuOptionDefensaEs[] = "Defensa";
extern "C" const char s_MenuOptionMusicaEs[8] = "M\372sica";
extern "C" const char s_MenuOptionApagadoEs[] = "Apagado";
extern "C" const char s_MenuOptionEstereoEs[8] = "Est\351reo";
extern "C" const char s_MenuOptionMinEs[8] = "M\355n.";
extern "C" const char s_MenuOptionMaxEs[8] = "M\341x.";
// .sdata2 float/double pool, emitted in the target's first-use order.
extern const float kOptionMenuFontScale = 0.88f;
extern const float kOptionAnimMin = 0.0f;
extern const float kOptionMenuAlphaMax = 255.0f;
extern const float kOptionBannerCenterY = 224.0f;
extern const float kMenuCenteringHalfWidth = 0.5f;
extern const float kOptionBannerYOffset = 14.0f;
extern const float kOptionScreenWidth = 640.0f;
extern const float kOptionPanelLeft = 336.0f;
extern const float kOptionPanelTop = 88.0f;
extern const float kOptionAnimMax = 1.0f;
extern const float kOptionCursorSize = 32.0f;
extern const float kOptionMarkerLeft = 64.0f;
extern const float kOptionListTextScaleX = 0.8f;
extern const float kOptionRowLeft = 56.0f;
extern const float kOptionTextYOffset = -4.0f;
extern const float kOptionHelpBarTop = 384.0f;
extern const float kOptionLargeIconSize = 40.0f;
extern const float kMenuCenteringOffset = 320.0f;
extern const float kOptionHelpTextY = 387.0f;
extern const float kOptionDegToRad = 0.017453292f;
extern const float kOptionRowAnimStep = 0.125f;
extern const float kOptionRowAngleStep = 11.25f;
extern const float kOptionTextNudge = 2.0f;
extern const float kOptionSelectorTextY = 185.0f;
extern const float kOptionIconWaveTargetX = 472.0f;
extern const float kOptionGameInitTextOffset = 96.0f;
extern const float kOptionSelectorWidth = 120.0f;
extern const float kOptionSelectorHeight = 48.0f;
extern const double kOptionAltLanguageTextScale = 0.8;
extern const double kOptionDefaultTextScale = 1.0;
extern const double kOptionSelectorBaseX64 = 368.0;
extern const double kOptionHalf64 = 0.5;
extern const double kOptionSelectorRightX64 = 464.0;
extern const float kOptionStereoTextOffset = 112.0f;
extern const double kOptionStereoSelectorX64 = 360.0;
extern const double kOptionIconWaveTargetX64 = 472.0;
extern const float kOptionIconWaveOriginX = 348.0f;
extern const float kOptionLeftIconBaseY = 192.0f;
extern const float kOptionRightIconBaseX = 556.0f;
extern const float kOptionRightIconBaseY = 184.0f;
extern "C" const float kOptionMeterArrowY = 190.0f;
extern "C" const float kOptionMeterRightArrowX = 587.0f;
extern "C" const float kOptionMeterBarBaseX = 372.0f;
extern "C" const float kOptionMeterAnchor196 = 196.0f;
extern "C" const float kOptionMeterLabelY = 168.0f;
extern "C" const float kOptionSmallIconSize = 24.0f;
extern "C" const float kOptionUiTwenty = 20.0f;
extern "C" const float kOptionMeterSegmentSize = 16.0f;
extern "C" const float kOptionMeterMaxLabelRight = 564.0f;
extern "C" const float kOptionSpecialRowFrameStep = 0.07692308f;
extern "C" const float kOptionSpecialRowAngleStep = 6.923077f;
extern "C" const float kOptionModeTextYOffset = 4.0f;
extern "C" const unsigned int kMenuUtilUnsignedIntToDoubleBiasBits[2] = {0x43300000, 0x00000000};
extern "C" const unsigned int kMenuUtilSignedIntToDoubleBiasBits[2] = {0x43300000, 0x80000000};
extern "C" const float kOptionOpenAnimStep = 0.04f;
extern "C" const float kOptionColumnAnimStep = 0.2f;
extern "C" const float kOptionVolumeScale = 10.583333f;
extern "C" const float kHelpMessageLineStep = 25.0f;
extern const char sMenuUtilEmptyText[4] = "";
extern const char sMenuUtilStringFormat[] = "%s";
extern const char sMenuUtilPlusOneText[] = "+1";
extern const char sMenuUtilSignedValueFormat[] = "%c%d";
extern const char sMenuUtilSpaceText[] = " ";
extern const char sMenuUtilValueSuffixFormat[] = " %d";
extern const char sMenuUtilSignedDeltaFormat[] = " %+d";
extern const char sMenuUtilAttrBonusFormat[] = " %s";
__declspec(section ".rodata") static const char s_Strength[] = "Strength:";
__declspec(section ".rodata") static const char s_Defence[] = "Defence:";
__declspec(section ".rodata") static const char s_Position_Markers[] = "Position Markers";
__declspec(section ".rodata") static const char s_Sound_Mode[] = "Sound Mode";
__declspec(section ".rodata") static const char s_Sound_Effects[] = "Sound Effects";
static const char s_GBA_Colour_Balance[] = "GBA Colour Balance";
static const char s_Show_or_hide_position_marker_under_each_character_s_feet[] = "Show or hide position marker under each character's feet.";
static const char s_Select_stereo_or_monaural_sound[] = "Select stereo or monaural sound.";
static const char s_Adjust_volume_of_background_music[] = "Adjust volume of background music.";
static const char s_Adjust_volume_of_sound_effects[] = "Adjust volume of sound effects.";
static const char s_Adjust_colour_balance_of_Game_Boy_Advance[] = "Adjust colour balance of Game Boy Advance.";
__declspec(section ".rodata") static const char s_Monaural[] = "Monaural";
__declspec(section ".rodata") static const char s_Enhanced[] = "Enhanced";
__declspec(section ".rodata") static const char s_Standard[] = "Standard";
static const char s_Erkennungskreisel[] = "Erkennungskreisel";
__declspec(section ".rodata") static const char s_Tonausgabe[] = "Tonausgabe";
__declspec(section ".rodata") static const char s_MenuOptionSoundEffectsDe[] = "Ger\344uscheffekte";
__declspec(section ".rodata") static const char s_Farbeinstellung[] = "Farbeinstellung";
static const char s_Erkennungskreisel_des_Charakters_AN_AUS_schalten[] = "Erkennungskreisel des Charakters AN/AUS schalten.";
static const char s_Tonausgabe_auf_Stereo_oder_Mono_schalten[] = "Tonausgabe auf Stereo oder Mono schalten.";
static const char s_Lautstaerke_der_Musik_aendern[] = "Lautst\344rke der Musik \344ndern.";
static const char s_Lautstaerke_der_Geraeuscheffekte_aendern[] = "Lautst\344rke der Ger\344uscheffekte \344ndern.";
static const char s_Farbeinstellung_des_Game_Boy_Advance_aendern[] = "Farbeinstellung des Game Boy Advance \344ndern.";
__declspec(section ".rodata") static const char s_Erweitert[] = "Erweitert";
static const char s_Indicatori_di_posizione[] = "Indicatori di posizione";
__declspec(section ".rodata") static const char s_Effetti_sonori[] = "Effetti sonori";
static const char s_Bilanc_colore_GBA[] = "Bilanc. colore GBA";
static const char s_Attiva_o_disattiva_l_indicatore_ai_piedi_dei_personaggi[] = "Attiva o disattiva l'indicatore ai piedi dei personaggi.";
static const char s_Scegli_tra_sonoro_mono_o_stereo[] = "Scegli tra sonoro mono o stereo.";
static const char s_Regola_il_volume_della_musica[] = "Regola il volume della musica";
static const char s_Regola_il_volume_degli_effetti_sonori[] = "Regola il volume degli effetti sonori";
static const char s_Regola_il_colore_sul_Game_Boy_Advance[] = "Regola il colore sul Game Boy Advance.";
__declspec(section ".rodata") static const char s_ResistanceFr[] = "R\351sistance";
static const char s_Sceau_de_position[] = "Sceau de position";
__declspec(section ".rodata") static const char s_Signal_sonore[] = "Signal sonore";
__declspec(section ".rodata") static const char s_Effets_sonores[] = "Effets sonores";
static const char s_Affichage_du_GBA[] = "Affichage du GBA";
static const char s_Affichage_du_sceau_de_position_aux_pieds_des_personnages[] = "Affichage du sceau de position aux pieds des personnages";
static const char s_Choisissez_le_signal_sonore_stereo_ou_mono[] = "Choisissez le signal sonore st\351r\351o ou mono";
static const char s_Reglez_le_volume_de_la_musique[] = "R\351glez le volume de la musique";
static const char s_Reglez_le_volume_des_effets_sonores[] = "R\351glez le volume des effets sonores";
static const char s_Reglez_le_contraste_des_couleurs_du_Game_Boy_Advance[] = "R\351glez le contraste des couleurs du Game Boy Advance";
__declspec(section ".rodata") static const char s_MenuOptionDesactiveFr[] = "D\351sactiv\351";
__declspec(section ".rodata") static const char s_MenuOptionAmelioreFr[] = "Am\351lior\351";
__declspec(section ".rodata") static const char s_Aro_de_posicion[] = "Aro de posici\363n";
__declspec(section ".rodata") static const char s_Tipo_de_sonido[] = "Tipo de sonido";
static const char s_Efectos_de_sonido[] = "Efectos de sonido";
__declspec(section ".rodata") static const char s_Color_de_la_GBA[] = "Color de la GBA";
static const char s_Senala_la_posicion_bajo_los_pies_de_cada_personaje[] = "Se\361ala la posici\363n bajo los pies de cada personaje.";
static const char s_Selecciona_sonido_estereo_o_monoaural[] = "Selecciona sonido est\351reo o monoaural.";
static const char s_Ajusta_el_volumen_de_la_musica_de_fondo[] = "Ajusta el volumen de la m\372sica de fondo.";
static const char s_Ajusta_el_volumen_de_los_efectos_de_sonido[] = "Ajusta el volumen de los efectos de sonido.";
static const char s_Ajusta_el_balance_del_color_de_la_Game_Boy_Advance[] = "Ajusta el balance del color de la Game Boy Advance.";
__declspec(section ".rodata") static const char s_Encendido[] = "Encendido";
__declspec(section ".rodata") static const char s_Monoaural[] = "Monoaural";
__declspec(section ".rodata") static const char s_Mejorado[] = "Mejorado";

static const MenuOptionEstandarData s_MenuOptionEstandarEs = {
	"Est\341ndar",
	{ 0x160, 0x14E, 0x142, 0x13E, 0x160, 0x154, 0x146 },
	{
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		328.0f, 172.0f, 544.0f, 186.0f, 368.0f, 176.0f, 400.0f, 0.0f, 496.0f, 0.0f,
		328.0f, 172.0f, 552.0f, 186.0f, 360.0f, 176.0f, 376.0f, 0.0f, 488.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 508.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 508.0f, 0.0f, 326.0f, 128.0f,
		300.0f, 160.0f, 330.0f, 138.0f, 372.0f, 132.0f, 492.0f, 132.0f,
	},
};

__declspec(section ".rodata") static const char s_MenuUtil_cpp_801e37fc[] = "MenuUtil.cpp";
__declspec(section ".rodata") static const char s_MenuUtilAllocErrorFmt[] = "%s(%d): Error: memory allocation error\n";

// DrawHelpMessageUS anchors on the start of this TU's .rodata island
// (lbl_801E3058) and reaches the help-line table and the alloc-error strings
// via fixed offsets, matching the target's pooled-base addressing.
extern "C" char lbl_801E3058[];

extern const char s_MenuOptionMusic[];
extern const char s_MenuOptionOn[];
extern const char s_MenuOptionOff[];
extern const char s_MenuOptionStereo[];
extern const char s_MenuOptionMin[];
extern const char s_MenuOptionMax[];
extern const char s_MenuOptionStrengthDe[];
extern const char s_MenuOptionDefenceDe[];
extern const char s_MenuOptionMusicDe[];
extern const char s_MenuOptionOnDe[];
extern const char s_MenuOptionOffDe[];
extern const char s_MenuOptionStereoDe[];
extern const char s_MenuOptionMonoUpper[];
extern const char s_MenuOptionNormalIt[];
extern const char s_MenuOptionForza[];
extern const char s_MenuOptionDifesa[];
extern const char s_MenuOptionSonoro[];
extern const char s_MenuOptionMusicaIt[];
extern const char s_MenuOptionMonoIt[];
extern const char s_MenuOptionContr[];
extern const char s_MenuOptionNorm[];
extern const char s_MenuOptionForceFr[];
extern const char s_MenuOptionMusiqueFr[];
extern const char s_MenuOptionActiveFr[];
extern const char s_MenuOptionStereoFr[];
extern const char s_MenuOptionFuerzaEs[];
extern const char s_MenuOptionDefensaEs[];
extern const char s_MenuOptionMusicaEs[];
extern const char s_MenuOptionApagadoEs[];
extern const char s_MenuOptionEstereoEs[];
extern const char s_MenuOptionMinEs[];
extern const char s_MenuOptionMaxEs[];
char* g_strMenuUtilMes[] = {
	const_cast<char*>(s_Strength), const_cast<char*>(s_Defence), const_cast<char*>(s_Position_Markers), const_cast<char*>(s_Sound_Mode),
	const_cast<char*>(s_MenuOptionMusic), const_cast<char*>(s_Sound_Effects), const_cast<char*>(s_GBA_Colour_Balance),
	const_cast<char*>(s_Show_or_hide_position_marker_under_each_character_s_feet),
	const_cast<char*>(s_Select_stereo_or_monaural_sound), const_cast<char*>(s_Adjust_volume_of_background_music),
	const_cast<char*>(s_Adjust_volume_of_sound_effects), const_cast<char*>(s_Adjust_colour_balance_of_Game_Boy_Advance),
	const_cast<char*>(s_MenuOptionOn), const_cast<char*>(s_MenuOptionOff), const_cast<char*>(s_MenuOptionStereo), const_cast<char*>(s_Monaural),
	const_cast<char*>(s_MenuOptionMin), const_cast<char*>(s_MenuOptionMax), const_cast<char*>(s_Enhanced), const_cast<char*>(s_Standard),
	const_cast<char*>(s_MenuOptionStrengthDe), const_cast<char*>(s_MenuOptionDefenceDe), const_cast<char*>(s_Erkennungskreisel), const_cast<char*>(s_Tonausgabe),
	const_cast<char*>(s_MenuOptionMusicDe), const_cast<char*>(s_MenuOptionSoundEffectsDe), const_cast<char*>(s_Farbeinstellung),
	const_cast<char*>(s_Erkennungskreisel_des_Charakters_AN_AUS_schalten),
	const_cast<char*>(s_Tonausgabe_auf_Stereo_oder_Mono_schalten), const_cast<char*>(s_Lautstaerke_der_Musik_aendern), const_cast<char*>(s_Lautstaerke_der_Geraeuscheffekte_aendern),
	const_cast<char*>(s_Farbeinstellung_des_Game_Boy_Advance_aendern), const_cast<char*>(s_MenuOptionOnDe), const_cast<char*>(s_MenuOptionOffDe), const_cast<char*>(s_MenuOptionStereoDe), const_cast<char*>(s_MenuOptionMonoUpper),
	const_cast<char*>(s_MenuOptionMin), const_cast<char*>(s_MenuOptionMax), const_cast<char*>(s_Erweitert), const_cast<char*>(s_MenuOptionNormalIt),
	const_cast<char*>(s_MenuOptionForza), const_cast<char*>(s_MenuOptionDifesa), const_cast<char*>(s_Indicatori_di_posizione), const_cast<char*>(s_MenuOptionSonoro),
	const_cast<char*>(s_MenuOptionMusicaIt), const_cast<char*>(s_Effetti_sonori), const_cast<char*>(s_Bilanc_colore_GBA),
	const_cast<char*>(s_Attiva_o_disattiva_l_indicatore_ai_piedi_dei_personaggi),
	const_cast<char*>(s_Scegli_tra_sonoro_mono_o_stereo), const_cast<char*>(s_Regola_il_volume_della_musica),
	const_cast<char*>(s_Regola_il_volume_degli_effetti_sonori), const_cast<char*>(s_Regola_il_colore_sul_Game_Boy_Advance),
	const_cast<char*>(s_MenuOptionOn), const_cast<char*>(s_MenuOptionOff), const_cast<char*>(s_MenuOptionStereo), const_cast<char*>(s_MenuOptionMonoIt), const_cast<char*>(s_MenuOptionMin), const_cast<char*>(s_MenuOptionMax),
	const_cast<char*>(s_MenuOptionContr), const_cast<char*>(s_MenuOptionNorm),
	const_cast<char*>(s_MenuOptionForceFr), const_cast<char*>(s_ResistanceFr), const_cast<char*>(s_Sceau_de_position), const_cast<char*>(s_Signal_sonore),
	const_cast<char*>(s_MenuOptionMusiqueFr), const_cast<char*>(s_Effets_sonores), const_cast<char*>(s_Affichage_du_GBA),
	const_cast<char*>(s_Affichage_du_sceau_de_position_aux_pieds_des_personnages),
	const_cast<char*>(s_Choisissez_le_signal_sonore_stereo_ou_mono), const_cast<char*>(s_Reglez_le_volume_de_la_musique), const_cast<char*>(s_Reglez_le_volume_des_effets_sonores), const_cast<char*>(s_Reglez_le_contraste_des_couleurs_du_Game_Boy_Advance), const_cast<char*>(s_MenuOptionActiveFr),
	const_cast<char*>(s_MenuOptionDesactiveFr), const_cast<char*>(s_MenuOptionStereoFr), const_cast<char*>(s_MenuOptionMonoIt), const_cast<char*>(s_MenuOptionMin), const_cast<char*>(s_MenuOptionMax),
	const_cast<char*>(s_MenuOptionAmelioreFr), const_cast<char*>(s_Standard),
	const_cast<char*>(s_MenuOptionFuerzaEs), const_cast<char*>(s_MenuOptionDefensaEs), const_cast<char*>(s_Aro_de_posicion), const_cast<char*>(s_Tipo_de_sonido),
	const_cast<char*>(s_MenuOptionMusicaEs), const_cast<char*>(s_Efectos_de_sonido), const_cast<char*>(s_Color_de_la_GBA),
	const_cast<char*>(s_Senala_la_posicion_bajo_los_pies_de_cada_personaje), const_cast<char*>(s_Selecciona_sonido_estereo_o_monoaural), const_cast<char*>(s_Ajusta_el_volumen_de_la_musica_de_fondo), const_cast<char*>(s_Ajusta_el_volumen_de_los_efectos_de_sonido),
	const_cast<char*>(s_Ajusta_el_balance_del_color_de_la_Game_Boy_Advance), const_cast<char*>(s_Encendido),
	const_cast<char*>(s_MenuOptionApagadoEs), const_cast<char*>(s_MenuOptionEstereoEs), const_cast<char*>(s_Monoaural), const_cast<char*>(s_MenuOptionMinEs), const_cast<char*>(s_MenuOptionMaxEs),
	const_cast<char*>(s_Mejorado), const_cast<char*>(s_MenuOptionEstandarEs.m_text),
};

#define PTR_s_Strength__80215a48 g_strMenuUtilMes
#define PTR_s_Defence__80215a4c (g_strMenuUtilMes + 1)

namespace {
static inline char** GetMenuHelpMsgTable()
{
	return reinterpret_cast<char**>(Game.m_cFlatDataArr[1].TableStrings(6));
}

static inline CTexture* GetMenuTexture(CMenuPcs* menu, int offset)
{
	return *reinterpret_cast<CTexture**>(reinterpret_cast<unsigned char*>(menu) + offset);
}

static inline CTextureSet* GetMenuTextureSet(CMenuPcs* menu, int offset)
{
	return *reinterpret_cast<CTextureSet**>(reinterpret_cast<unsigned char*>(menu) + offset);
}

static inline CTexture* GetTextureSetTexture(CTextureSet* set, int index)
{
	return set->GetTexture(index);
}

static inline void SetUv(Vec2d& uv, float u, float v)
{
	uv.x = u;
	uv.y = v;
}
}

static inline unsigned short GetMenuPress()
{
	bool activeInput = false;

	if ((Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1)) {
		activeInput = true;
	}

	if (activeInput) {
		return 0;
	}

	int padIndex = 0;
	padIndex &= ~-((__cntlzw(static_cast<unsigned int>(Pad.m_debugPadPort)) & 0x20) >> 5);
	return Pad.GetPadInputs()[padIndex].buttonDown[0];
}

static inline unsigned short GetMenuPressLock(int lock)
{
	bool activeInput = false;

	if ((lock != 0) || (Pad.m_debugPadPort != -1)) {
		activeInput = true;
	}

	if (activeInput) {
		return 0;
	}

	int padIndex = 0;
	padIndex &= ~-((__cntlzw(static_cast<unsigned int>(Pad.m_debugPadPort)) & 0x20) >> 5);
	return Pad.GetPadInputs()[padIndex].buttonDown[0];
}

/*
 * --INFO--
 * PAL Address: 0x8017683c
 * PAL Size: 336b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::BindMcObj(int slotNo)
{
	int slot;
	EffectInfo* obj;

	for (slot = 0; slot < 4; slot++) {
		if (slotNo == slot) {
			obj = &m_effectWork[slot + 0x11];

			if (obj->m_partNo >= 0) {
				PartMng.pppDeletePart(obj->m_partNo);
				obj->m_partNo = -1;
				obj->m_slotNo = -1;
				obj->m_effectNo = -1;
			}

			obj += 4;
			if (obj->m_partNo >= 0) {
				PartMng.pppDeletePart(obj->m_partNo);
				obj->m_partNo = -1;
				obj->m_slotNo = -1;
				obj->m_effectNo = -1;
			}
		}
	}

	for (slot = 0; slot < 4; slot++) {
		if (slotNo == slot) {
			int iconType;
			EffectEntry* entry = &m_effectEntries[slot];
			iconType = entry->m_iconType;

			if (iconType != 0) {
				BindEffect(slot + 0x11, iconType + 0x16, -1);
			}

			unsigned int flags = entry->m_flags;

			if ((flags & 1) != 0) {
				iconType = 0;
			} else if ((flags & 2) != 0) {
				iconType = 1;
			} else if ((flags & 4) != 0) {
				iconType = 2;
			} else if ((flags & 8) != 0) {
				iconType = 3;
			} else if ((flags & 0x10) != 0) {
				iconType = 4;
			}

			BindEffect(slot + 0x11, iconType + 0x1A, -1);
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
struct MenuOptLayout10 {
	f32 f0, f1, f2, f3, f4, f5, f6, f7, f8, f9;
};
struct MenuOptLayout14 {
	f32 f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13;
};
struct MenuOptPair {
	f32 x, y;
};
struct MenuOptText5 {
	char* p0;
	char* p1;
	char* p2;
	char* p3;
	char* p4;
};
struct MenuOptLayoutPairs {
	MenuOptPair p[5];
};

#define OPT_MES(n) g_strMenuUtilMes[langRow * 20 + (n)]

void CMenuPcs::DrawOptionMenu()
{
	const f32* layoutBase = reinterpret_cast<const f32*>(lbl_801E3058 + 0x694);
	CFont* font = m_fonts[0];
	int langRow = Game.m_gameWork.m_languageId - 1;
	f32 rowWidth;
	_GXColor color;
	Vec2d uv0;
	Vec2d uv1;

	font->SetScale(*(const volatile float*)&kOptionMenuFontScale);
	font->SetMargin(kOptionAnimMin);

	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = static_cast<unsigned char>(static_cast<int>(*(const volatile float*)&kOptionMenuAlphaMax * m_optionOpenAnim));

	char* optionText[5];
	char* helpText[5];
	char** mes = &g_strMenuUtilMes[langRow * 20];
	int idx = 2;
	*reinterpret_cast<MenuOptText5*>(optionText) = *reinterpret_cast<const MenuOptText5*>(&layoutBase[0]);
	for (int n = 0; n < 5; n++) {
		optionText[n] = mes[idx++];
	}
	*reinterpret_cast<MenuOptText5*>(helpText) = *reinterpret_cast<const MenuOptText5*>(&layoutBase[5]);
	for (int n = 0; n < 5; n++) {
		helpText[n] = mes[idx++];
	}

	CTexture* banner = GetMenuTexture(this, 0xD4);
	float bannerWidth = static_cast<float>(banner->m_width);
	float bannerHeight = static_cast<float>(banner->m_height);
	gUtil.CalcUV(uv0.x, uv0.y, 0, 0, static_cast<unsigned int>(bannerWidth), static_cast<unsigned int>(bannerHeight));
	gUtil.CalcUV(uv1.x, uv1.y, 0x280, static_cast<unsigned int>(bannerHeight),
	             static_cast<unsigned int>(bannerWidth), static_cast<unsigned int>(bannerHeight));
	gUtil.RenderTextureQuad(kOptionAnimMin,
	                        -(bannerHeight * kMenuCenteringHalfWidth - *(const volatile float*)&kOptionBannerCenterY) - kOptionBannerYOffset,
	                        kOptionScreenWidth, bannerHeight, GetMenuTexture(this, 0xD4), &uv0, &uv1, &color, GX_BL_SRCALPHA,
	                        GX_BL_INVSRCALPHA);

	CTexture* panel = GetMenuTexture(this, 0xE8);
	float panelWidth = static_cast<float>(panel->m_width);
	float panelHeight = static_cast<float>(panel->m_height);
	gUtil.RenderTextureQuad(*(const volatile float*)&kOptionPanelLeft, kOptionPanelTop, panelWidth, panelHeight, panel, 0, 0, &color,
	                        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
	float panelBottom = kOptionPanelTop + panelHeight;
	uv0.x = kOptionAnimMin;
	uv0.y = kOptionAnimMax;
	uv1.x = kOptionAnimMax;
	uv1.y = kOptionAnimMin;
	gUtil.RenderTextureQuad(*(const volatile float*)&kOptionPanelLeft, panelBottom, panelWidth, panelHeight, GetMenuTexture(this, 0xE8), &uv0, &uv1, &color,
	                        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
	float panelRight = *(const volatile float*)&kOptionPanelLeft + panelWidth;
	uv0.x = kOptionAnimMax;
	uv0.y = kOptionAnimMin;
	uv1.x = kOptionAnimMin;
	uv1.y = kOptionAnimMax;
	gUtil.RenderTextureQuad(panelRight, kOptionPanelTop, panelWidth, panelHeight, GetMenuTexture(this, 0xE8), &uv0, &uv1, &color,
	                        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
	uv0.x = kOptionAnimMax;
	uv0.y = kOptionAnimMax;
	uv1.x = kOptionAnimMin;
	uv1.y = kOptionAnimMin;
	gUtil.RenderTextureQuad(panelRight, panelBottom, panelWidth, panelHeight, GetMenuTexture(this, 0xE8), &uv0, &uv1, &color,
	                        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

	CTexture* cursor = GetMenuTexture(this, 0x18C);
	float cursorWidth = static_cast<float>(cursor->m_width);
	float cursorHeight = static_cast<float>(cursor->m_height);
	gUtil.CalcUV(uv0.x, uv0.y, 0, 0, static_cast<unsigned int>(cursorWidth),
	             static_cast<unsigned int>(cursorHeight));
	gUtil.CalcUV(uv1.x, uv1.y, 0x20, 0x20, static_cast<unsigned int>(cursorWidth),
	             static_cast<unsigned int>(cursorHeight));
	gUtil.RenderTextureQuad(static_cast<float>(static_cast<int>(System.m_frameCounter) % 8 + 0x1C),
	                        static_cast<float>(m_optionIndex * 0x28 + 0x70), kOptionCursorSize,
	                        kOptionCursorSize, GetMenuTexture(this, 0x18C), &uv0, &uv1, &color, GX_BL_SRCALPHA,
	                        GX_BL_INVSRCALPHA);

	CTexture* marker = GetMenuTexture(this, 0xC8);
	rowWidth = static_cast<float>(marker->m_width);
	gUtil.RenderTextureQuad(*(const volatile float*)&kOptionMarkerLeft, static_cast<float>(m_optionIndex * 0x28 + 0x70),
	                        rowWidth, static_cast<float>(marker->m_height), marker, 0, 0,
	                        &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

	font->SetScaleX(*(const volatile float*)&kOptionListTextScaleX);
	char** option = optionText;
	int i = 0;
	int rowY = 0x70;
	int selectedY = 0x73;
	int normalY = 0x75;
	for (; i < 5; i++, rowY += 0x28, selectedY += 0x28, normalY += 0x28, option++) {
		CTexture* row = GetMenuTexture(this, 0xC0);
		rowWidth = static_cast<float>(row->m_width);
		float rowHeight = static_cast<float>(row->m_height);
		uv0.x = (i == m_optionIndex) ? kOptionAnimMin : kMenuCenteringHalfWidth;
		uv0.y = kOptionAnimMin;
		uv1.x = (i == m_optionIndex) ? kMenuCenteringHalfWidth : kOptionAnimMax;
		uv1.y = kOptionAnimMax;
		gUtil.RenderTextureQuad(*(const volatile float*)&kOptionRowLeft, static_cast<float>(rowY),
		                        rowWidth * kMenuCenteringHalfWidth, rowHeight, GetMenuTexture(this, 0xC0), &uv0,
		                        &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		if (i == m_optionIndex) {
			DrawFont(0x5E, static_cast<int>(*(const volatile float*)&kOptionTextYOffset + static_cast<float>(selectedY)), color, 0x16,
			         *option, kOptionAnimMax, kOptionAnimMax);
		} else {
			DrawFont(0x60, static_cast<int>(*(const volatile float*)&kOptionTextYOffset + static_cast<float>(normalY)), color, 6,
			         *option, kOptionAnimMax, kOptionAnimMax);
		}
	}

	font->SetScaleX(kOptionAnimMax);
	gUtil.RenderTextureQuad(kOptionAnimMin, *(const volatile float*)&kOptionHelpBarTop, kOptionScreenWidth, kOptionLargeIconSize,
	                        GetMenuTexture(this, 0x208), 0, 0, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

	{
		float helpTextY = kOptionHelpTextY;
		char* help = helpText[m_optionIndex];
		CFont* fnt = m_fonts[0];
		fnt->SetShadow(1);
		fnt->SetMargin(kOptionAnimMax);
		fnt->SetScaleX(*(const volatile float*)&kOptionListTextScaleX);
		fnt->SetScaleY(kOptionAnimMax);
		DrawFont2(static_cast<int>(-(fnt->GetWidth(help) * kMenuCenteringHalfWidth -
		                            *(const volatile float*)&kMenuCenteringOffset)),
		          static_cast<int>(helpTextY), color, 7, helpText[m_optionIndex], *(const volatile float*)&kOptionListTextScaleX,
		          kOptionAnimMax, kOptionAnimMax);
	}

	int leftHintOn = 0;
	int rightHintOn = 0;
	if (m_leftHintTimer != 0) {
		leftHintOn = 1;
	}
	if (m_rightHintTimer != 0) {
		rightHintOn = 1;
	}

	int rowAnimStep = static_cast<int>(m_optionRowAnim / kOptionRowAnimStep);
	color.a = static_cast<unsigned char>(static_cast<int>(*(const volatile float*)&kOptionMenuAlphaMax * m_optionRowAnim));
	int __p13 = rowAnimStep;
	float rowAngle = static_cast<float>(__p13) * kOptionRowAngleStep;
	float rowSin = static_cast<float>(sin(static_cast<double>(*(const volatile float*)&kOptionDegToRad * (kOptionTextNudge * rowAngle))));
	float rowCos = static_cast<float>(cos(static_cast<double>(*(const volatile float*)&kOptionDegToRad * rowAngle)));

	switch (m_optionIndex) {
	case 0: {
		MenuOptLayout10 row = *reinterpret_cast<const MenuOptLayout10*>(&layoutBase[10]);
		int leftXi = static_cast<int>(kOptionIconWaveTargetX - row.f0);
		int rightXi = static_cast<int>(rowWidth * kMenuCenteringHalfWidth + row.f2 - kOptionIconWaveTargetX);
		row.f7 = kOptionSelectorTextY;
		row.f9 = kOptionSelectorTextY;
		CTexture* sideTexture = GetTextureSetTexture(GetMenuTextureSet(this, 0xBC), 1);
		unsigned int sideWidth = sideTexture->m_width;
		unsigned int sideHeight = sideTexture->m_height;

		SetUv(uv0, kOptionAnimMin, kOptionAnimMin);
		SetUv(uv1, kMenuCenteringHalfWidth, kOptionAnimMax);
		float sideW = static_cast<float>(sideWidth) * kMenuCenteringHalfWidth;
		float sideH = static_cast<float>(sideHeight);
		gUtil.RenderTextureQuad(static_cast<float>(static_cast<int>(static_cast<float>(leftXi) * rowCos + row.f0)),
		                        row.f1, sideW, sideH, sideTexture, &uv0, &uv1, &color,
		                        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
		SetUv(uv0, kMenuCenteringHalfWidth, kOptionAnimMin);
		SetUv(uv1, kOptionAnimMax, kOptionAnimMax);
		gUtil.RenderTextureQuad(static_cast<float>(static_cast<int>(-(static_cast<float>(rightXi) * rowCos - row.f2))),
		                        row.f3, sideW, sideH, sideTexture, &uv0, &uv1, &color,
		                        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		color.a = static_cast<unsigned char>(static_cast<int>(*(const volatile float*)&kOptionMenuAlphaMax * m_optionColumnAnim));
		CTexture* selectorTexture = GetTextureSetTexture(GetMenuTextureSet(this, 0xBC), 4);
		unsigned int selectorHeight = static_cast<unsigned int>(static_cast<float>(selectorTexture->m_height));
		unsigned int selectorWidth = static_cast<unsigned int>(static_cast<float>(selectorTexture->m_width));
		gUtil.CalcUV(uv0.x, uv0.y, 0, 0, selectorWidth, selectorHeight);
		gUtil.CalcUV(uv1.x, uv1.y, 0x78, 0x30, selectorWidth, selectorHeight);
		gUtil.RenderTextureQuad((m_gameInitMode == 0) ? row.f4 : kOptionGameInitTextOffset + row.f4, row.f5,
		                        kOptionSelectorWidth, kOptionSelectorHeight, selectorTexture, &uv0, &uv1, &color,
		                        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		unsigned char isAlt = (langRow + 1 == 4) || (langRow + 1 == 5);
		float scale = isAlt ? kOptionAltLanguageTextScale : kOptionDefaultTextScale;

		if (m_gameInitMode == 0) {
			{
				CFont* fnt = m_fonts[0];
				char* txt = OPT_MES(12);
				fnt->SetMargin(kOptionAnimMax);
				fnt->SetShadow(1);
				float oneF = kOptionAnimMax;
				float firstScale = oneF * scale;
				fnt->SetScale(firstScale);
				DrawFont2(static_cast<int>(static_cast<float>((kOptionSelectorWidth - fnt->GetWidth(txt)) *
				                           kOptionHalf64 + kOptionSelectorBaseX64)),
				          static_cast<int>(row.f7 - kOptionTextNudge), color, 0x17, txt, firstScale,
				          kOptionAnimMax, kOptionAnimMax);
			}
			{
				CFont* fnt = m_fonts[0];
				char* txt = OPT_MES(13);
				fnt->SetMargin(kOptionAnimMax);
				fnt->SetShadow(1);
				fnt->SetScale(scale);
				DrawFont2(static_cast<int>(static_cast<float>((kOptionSelectorWidth - fnt->GetWidth(txt)) *
				                           kOptionHalf64 + kOptionSelectorRightX64)),
				          static_cast<int>(row.f9), color, 6, txt, scale, kOptionAnimMax,
				          kOptionAnimMax);
			}
		} else {
			{
				CFont* fnt = m_fonts[0];
				char* txt = OPT_MES(12);
				fnt->SetMargin(kOptionAnimMax);
				fnt->SetShadow(1);
				fnt->SetScale(scale);
				DrawFont2(static_cast<int>(static_cast<float>((kOptionSelectorWidth - fnt->GetWidth(txt)) *
				                           kOptionHalf64 + kOptionSelectorBaseX64)),
				          static_cast<int>(row.f7), color, 6, txt, scale, kOptionAnimMax,
				          kOptionAnimMax);
			}
			{
				CFont* fnt = m_fonts[0];
				char* txt = OPT_MES(13);
				fnt->SetMargin(kOptionAnimMax);
				fnt->SetShadow(1);
				float oneF = kOptionAnimMax;
				scale = oneF * scale;
				fnt->SetScale(scale);
				DrawFont2(static_cast<int>(static_cast<float>((kOptionSelectorWidth - fnt->GetWidth(txt)) *
				                           kOptionHalf64 + kOptionSelectorRightX64)),
				          static_cast<int>(row.f9 - kOptionTextNudge), color, 0x17, txt, scale,
				          kOptionAnimMax, kOptionAnimMax);
			}
		}
		break;
	}
	case 1: {
		MenuOptLayout10 row = *reinterpret_cast<const MenuOptLayout10*>(&layoutBase[20]);
		int leftXi = static_cast<int>(kOptionIconWaveTargetX - row.f0);
		int rightXi = static_cast<int>(rowWidth * kMenuCenteringHalfWidth + row.f2 - kOptionIconWaveTargetX);
		row.f7 = kOptionSelectorTextY;
		row.f9 = kOptionSelectorTextY;
		CTexture* sideTexture = GetTextureSetTexture(GetMenuTextureSet(this, 0xBC), 1);
		unsigned int sideWidth = sideTexture->m_width;
		unsigned int sideHeight = sideTexture->m_height;

		SetUv(uv0, kOptionAnimMin, kOptionAnimMin);
		SetUv(uv1, kMenuCenteringHalfWidth, kOptionAnimMax);
		float sideW = static_cast<float>(sideWidth) * kMenuCenteringHalfWidth;
		float sideH = static_cast<float>(sideHeight);
		gUtil.RenderTextureQuad(static_cast<float>(static_cast<int>(static_cast<float>(leftXi) * rowCos + row.f0)),
		                        row.f1, sideW, sideH, sideTexture, &uv0, &uv1, &color,
		                        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
		SetUv(uv0, kMenuCenteringHalfWidth, kOptionAnimMin);
		SetUv(uv1, kOptionAnimMax, kOptionAnimMax);
		gUtil.RenderTextureQuad(static_cast<float>(static_cast<int>(-(static_cast<float>(rightXi) * rowCos - row.f2))),
		                        row.f3, sideW, sideH, sideTexture, &uv0, &uv1, &color,
		                        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		color.a = static_cast<unsigned char>(static_cast<int>(*(const volatile float*)&kOptionMenuAlphaMax * m_optionColumnAnim));
		CTexture* selectorTexture = GetTextureSetTexture(GetMenuTextureSet(this, 0xBC), 4);
		unsigned int selectorHeight = static_cast<unsigned int>(static_cast<float>(selectorTexture->m_height));
		unsigned int selectorWidth = static_cast<unsigned int>(static_cast<float>(selectorTexture->m_width));
		gUtil.CalcUV(uv0.x, uv0.y, 0, 0, selectorWidth, selectorHeight);
		gUtil.CalcUV(uv1.x, uv1.y, 0x78, 0x30, selectorWidth, selectorHeight);
		gUtil.RenderTextureQuad((m_stereoMode == 0) ? row.f4 : kOptionStereoTextOffset + row.f4, row.f5,
		                        kOptionSelectorWidth, kOptionSelectorHeight, selectorTexture, &uv0, &uv1, &color,
		                        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		double stereoScale = kOptionAltLanguageTextScale;
		if (m_stereoMode == 0) {
			{
				CFont* fnt = m_fonts[0];
				char* txt = OPT_MES(14);
				fnt->SetMargin(kOptionAnimMax);
				fnt->SetShadow(1);
				float oneF = kOptionAnimMax;
				fnt->SetScale(stereoScale * oneF);
				DrawFont2(static_cast<int>(static_cast<float>((kOptionSelectorWidth - fnt->GetWidth(txt)) *
				                           kOptionHalf64 + kOptionStereoSelectorX64)),
				          static_cast<int>(row.f7 - kOptionTextNudge), color, 0x17, txt,
				          stereoScale * oneF, kOptionAnimMax, kOptionAnimMax);
			}
			{
				CFont* fnt = m_fonts[0];
				char* txt = OPT_MES(15);
				fnt->SetMargin(kOptionAnimMax);
				fnt->SetShadow(1);
				fnt->SetScale(*(const volatile float*)&kOptionListTextScaleX);
				DrawFont2(static_cast<int>(static_cast<float>((kOptionSelectorWidth - fnt->GetWidth(txt)) *
				                           kOptionHalf64 + kOptionIconWaveTargetX64)),
				          static_cast<int>(row.f9), color, 6, txt, *(const volatile float*)&kOptionListTextScaleX, kOptionAnimMax,
				          kOptionAnimMax);
			}
		} else {
			{
				CFont* fnt = m_fonts[0];
				char* txt = OPT_MES(14);
				fnt->SetMargin(kOptionAnimMax);
				fnt->SetShadow(1);
				fnt->SetScale(*(const volatile float*)&kOptionListTextScaleX);
				DrawFont2(static_cast<int>(static_cast<float>((kOptionSelectorWidth - fnt->GetWidth(txt)) *
				                           kOptionHalf64 + kOptionStereoSelectorX64)),
				          static_cast<int>(row.f7), color, 6, txt, *(const volatile float*)&kOptionListTextScaleX, kOptionAnimMax,
				          kOptionAnimMax);
			}
			{
				CFont* fnt = m_fonts[0];
				char* txt = OPT_MES(15);
				fnt->SetMargin(kOptionAnimMax);
				fnt->SetShadow(1);
				float oneF = kOptionAnimMax;
				fnt->SetScale(stereoScale * oneF);
				DrawFont2(static_cast<int>(static_cast<float>((kOptionSelectorWidth - fnt->GetWidth(txt)) *
				                           kOptionHalf64 + kOptionIconWaveTargetX64)),
				          static_cast<int>(row.f9 - kOptionTextNudge), color, 0x17, txt,
				          stereoScale * oneF, kOptionAnimMax, kOptionAnimMax);
			}
		}
		break;
	}
	case 2: {
		MenuOptLayout14 pos = *reinterpret_cast<const MenuOptLayout14*>(&layoutBase[30]);
		f32* posp = &pos.f0;
		posp[0] = kOptionIconWaveOriginX;
		posp[1] = kOptionLeftIconBaseY;
		posp[2] = kOptionRightIconBaseX;
		posp[3] = kOptionRightIconBaseY;
		posp[4] = *(const volatile float*)&kOptionPanelLeft;
		posp[5] = kOptionMeterArrowY;
		posp[6] = kOptionMeterRightArrowX;
		posp[7] = kOptionMeterArrowY;
		posp[8] = kOptionMeterBarBaseX;
		posp[9] = kOptionMeterAnchor196;
		posp[10] = kOptionMeterBarBaseX;
		posp[11] = kOptionMeterLabelY;
		posp[13] = kOptionMeterLabelY;
		CTexture* meterTexture = GetTextureSetTexture(GetMenuTextureSet(this, 0xBC), 3);
		int leftXi = static_cast<int>(kOptionIconWaveTargetX - pos.f0);
		int rightXi = static_cast<int>((kOptionSmallIconSize + pos.f2) - kOptionIconWaveTargetX);
		unsigned int meterHeight = static_cast<unsigned int>(static_cast<float>(meterTexture->m_height));
		unsigned int meterWidth = static_cast<unsigned int>(static_cast<float>(meterTexture->m_width));

		gUtil.CalcUV(uv0.x, uv0.y, 0, 0x28, meterWidth, meterHeight);
		gUtil.CalcUV(uv1.x, uv1.y, 0x18, 0x40, meterWidth, meterHeight);
		float iconWave = *(const volatile float*)&kOptionUiTwenty * rowSin;
		gUtil.RenderTextureQuad(static_cast<float>(static_cast<int>(static_cast<float>(leftXi) * rowCos + pos.f0)),
		                        posp[1] - iconWave, kOptionSmallIconSize, kOptionSmallIconSize, meterTexture, &uv0, &uv1,
		                        &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		gUtil.CalcUV(uv0.x, uv0.y, 0, 0, meterWidth, meterHeight);
		gUtil.CalcUV(uv1.x, uv1.y, 0x28, 0x28, meterWidth, meterHeight);
		gUtil.RenderTextureQuad(static_cast<float>(static_cast<int>(-(static_cast<float>(rightXi) * rowCos - pos.f2))),
		                        posp[3] + iconWave, kOptionLargeIconSize, kOptionLargeIconSize, meterTexture, &uv0, &uv1,
		                        &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		color.a = static_cast<unsigned char>(static_cast<int>(*(const volatile float*)&kOptionMenuAlphaMax * m_optionColumnAnim));
		if (leftHintOn != 0) {
			gUtil.CalcUV(uv0.x, uv0.y, 0x18, 0x58, meterWidth, meterHeight);
			gUtil.CalcUV(uv1.x, uv1.y, 0x28, 0x70, meterWidth, meterHeight);
		} else {
			gUtil.CalcUV(uv0.x, uv0.y, 0, 0x58, meterWidth, meterHeight);
			gUtil.CalcUV(uv1.x, uv1.y, 0x10, 0x70, meterWidth, meterHeight);
		}
		gUtil.RenderTextureQuad(posp[4], posp[5], kOptionMeterSegmentSize, kOptionSmallIconSize, meterTexture, &uv0,
		                        &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		if (rightHintOn != 0) {
			gUtil.CalcUV(uv0.x, uv0.y, 0x60, 0x5C, meterWidth, meterHeight);
			gUtil.CalcUV(uv1.x, uv1.y, 0x48, 0x7C, meterWidth, meterHeight);
		} else {
			gUtil.CalcUV(uv0.x, uv0.y, 0x48, 0x5C, meterWidth, meterHeight);
			gUtil.CalcUV(uv1.x, uv1.y, 0x30, 0x7C, meterWidth, meterHeight);
		}
		gUtil.RenderTextureQuad(posp[6], posp[7], kOptionSmallIconSize, kOptionCursorSize, meterTexture, &uv0,
		                        &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		gUtil.CalcUV(uv0.x, uv0.y, 0x40, 0x28, meterWidth, meterHeight);
		gUtil.CalcUV(uv1.x, uv1.y, 0x50, 0x38, meterWidth, meterHeight);
		float barBaseX = pos.f8;
		for (int i = 0, x = 0; i < 12; i++, x += 0x10) {
			gUtil.RenderTextureQuad(barBaseX + static_cast<float>(x), posp[9], kOptionMeterSegmentSize, kOptionMeterSegmentSize, meterTexture, &uv0,
			                        &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
			if ((m_optionMenuState != 2) && (i + 1 <= m_bgmVolume)) {
				gUtil.RenderTextureQuad(posp[8] + static_cast<float>(x), posp[9], kOptionMeterSegmentSize, kOptionMeterSegmentSize, meterTexture, &uv0,
				                        &uv1, &color, GX_BL_ONE, GX_BL_ONE);
			}
		}

		DrawFont(static_cast<int>(posp[10]), static_cast<int>(posp[11]), color, 7,
		         OPT_MES(16), kOptionAnimMax, kOptionAnimMax);
		posp[12] = *(const volatile float*)&kOptionMeterMaxLabelRight - font->GetWidth(OPT_MES(17));
		DrawFont(static_cast<int>(posp[12]), static_cast<int>(posp[13]), color, 7, OPT_MES(17), kOptionAnimMax,
		         kOptionAnimMax);
		break;
	}
	case 3: {
		MenuOptLayout14 pos = *reinterpret_cast<const MenuOptLayout14*>(&layoutBase[44]);
		f32* posp = &pos.f0;
		posp[0] = kOptionIconWaveOriginX;
		posp[1] = kOptionLeftIconBaseY;
		posp[2] = kOptionRightIconBaseX;
		posp[3] = kOptionRightIconBaseY;
		posp[4] = *(const volatile float*)&kOptionPanelLeft;
		posp[5] = kOptionMeterArrowY;
		posp[6] = kOptionMeterRightArrowX;
		posp[7] = kOptionMeterArrowY;
		posp[8] = kOptionMeterBarBaseX;
		posp[9] = kOptionMeterAnchor196;
		posp[10] = kOptionMeterBarBaseX;
		posp[11] = kOptionMeterLabelY;
		posp[13] = kOptionMeterLabelY;
		CTexture* meterTexture = GetTextureSetTexture(GetMenuTextureSet(this, 0xBC), 3);
		int leftXi = static_cast<int>(kOptionIconWaveTargetX - pos.f0);
		int rightXi = static_cast<int>((kOptionSmallIconSize + pos.f2) - kOptionIconWaveTargetX);
		unsigned int meterHeight = static_cast<unsigned int>(static_cast<float>(meterTexture->m_height));
		unsigned int meterWidth = static_cast<unsigned int>(static_cast<float>(meterTexture->m_width));

		gUtil.CalcUV(uv0.x, uv0.y, 0x18, 0x28, meterWidth, meterHeight);
		gUtil.CalcUV(uv1.x, uv1.y, 0x30, 0x40, meterWidth, meterHeight);
		float iconWave = *(const volatile float*)&kOptionUiTwenty * rowSin;
		gUtil.RenderTextureQuad(static_cast<float>(static_cast<int>(static_cast<float>(leftXi) * rowCos + pos.f0)),
		                        posp[1] + iconWave, kOptionSmallIconSize, kOptionSmallIconSize, meterTexture, &uv0, &uv1,
		                        &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		gUtil.CalcUV(uv0.x, uv0.y, 0x28, 0, meterWidth, meterHeight);
		gUtil.CalcUV(uv1.x, uv1.y, 0x50, 0x28, meterWidth, meterHeight);
		gUtil.RenderTextureQuad(static_cast<float>(static_cast<int>(-(static_cast<float>(rightXi) * rowCos - pos.f2))),
		                        posp[3] - iconWave, kOptionLargeIconSize, kOptionLargeIconSize, meterTexture, &uv0, &uv1,
		                        &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		color.a = static_cast<unsigned char>(static_cast<int>(*(const volatile float*)&kOptionMenuAlphaMax * m_optionColumnAnim));
		if (leftHintOn != 0) {
			gUtil.CalcUV(uv0.x, uv0.y, 0x18, 0x40, meterWidth, meterHeight);
			gUtil.CalcUV(uv1.x, uv1.y, 0x28, 0x58, meterWidth, meterHeight);
		} else {
			gUtil.CalcUV(uv0.x, uv0.y, 0, 0x40, meterWidth, meterHeight);
			gUtil.CalcUV(uv1.x, uv1.y, 0x10, 0x58, meterWidth, meterHeight);
		}
		gUtil.RenderTextureQuad(posp[4], posp[5], kOptionMeterSegmentSize, kOptionSmallIconSize, meterTexture, &uv0,
		                        &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		if (rightHintOn != 0) {
			gUtil.CalcUV(uv0.x, uv0.y, 0x60, 0x3C, meterWidth, meterHeight);
			gUtil.CalcUV(uv1.x, uv1.y, 0x48, 0x5C, meterWidth, meterHeight);
		} else {
			gUtil.CalcUV(uv0.x, uv0.y, 0x48, 0x3C, meterWidth, meterHeight);
			gUtil.CalcUV(uv1.x, uv1.y, 0x30, 0x5C, meterWidth, meterHeight);
		}
		gUtil.RenderTextureQuad(posp[6], posp[7], kOptionSmallIconSize, kOptionCursorSize, meterTexture, &uv0,
		                        &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		gUtil.CalcUV(uv0.x, uv0.y, 0x30, 0x28, meterWidth, meterHeight);
		gUtil.CalcUV(uv1.x, uv1.y, 0x40, 0x38, meterWidth, meterHeight);
		float barBaseX = pos.f8;
		for (int i = 0, x = 0; i < 12; i++, x += 0x10) {
			gUtil.RenderTextureQuad(barBaseX + static_cast<float>(x), posp[9], kOptionMeterSegmentSize, kOptionMeterSegmentSize, meterTexture, &uv0,
			                        &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
			if ((m_optionMenuState != 2) && (i + 1 <= m_seVolume)) {
				gUtil.RenderTextureQuad(posp[8] + static_cast<float>(x), posp[9], kOptionMeterSegmentSize, kOptionMeterSegmentSize, meterTexture, &uv0,
				                        &uv1, &color, GX_BL_ONE, GX_BL_ONE);
			}
		}

		DrawFont(static_cast<int>(posp[10]), static_cast<int>(posp[11]), color, 7,
		         OPT_MES(16), kOptionAnimMax, kOptionAnimMax);
		posp[12] = *(const volatile float*)&kOptionMeterMaxLabelRight - font->GetWidth(OPT_MES(17));
		DrawFont(static_cast<int>(posp[12]), static_cast<int>(posp[13]), color, 7, OPT_MES(17), kOptionAnimMax,
		         kOptionAnimMax);
		break;
	}
	case 4: {
		MenuOptLayoutPairs pts = *reinterpret_cast<const MenuOptLayoutPairs*>(&layoutBase[58]);
		int rowAnimFrame;
		if (static_cast<double>(m_optionRowAnim) < kOptionDefaultTextScale) {
			rowAnimFrame = static_cast<int>(m_optionRowAnim / *(const volatile float*)&kOptionSpecialRowFrameStep);
		} else {
			rowAnimFrame = 0xD;
		}
		const float specialRowCos = static_cast<float>(
			cos(static_cast<double>(*(const volatile float*)&kOptionDegToRad * (static_cast<float>(rowAnimFrame) * kOptionSpecialRowAngleStep))));

		int k = 0;
		int y = k;
		int uvY =  (k | 0);
		int uvY2 = 0x18;
		int modeU = 0x280;
		for (int i = 0; i < 4; i++, y += 0x28, uvY += 0x20, uvY2 += 0x20, modeU += 0x40, k = 0) {
			CTexture* cursorPanel = GetTextureSetTexture(GetMenuTextureSet(this, 0xBC), 4);
			float cursorWidth = static_cast<float>(cursorPanel->m_width);
			float cursorHeight = static_cast<float>(cursorPanel->m_height);
			if ((m_specialModeEdit != 0) && (m_specialModeCursor == i)) {
				gUtil.CalcUV(uv0.x, uv0.y, static_cast<unsigned int>(cursorWidth - kOptionSelectorHeight), 0,
				             static_cast<unsigned int>(cursorWidth), static_cast<unsigned int>(cursorHeight));
				gUtil.CalcUV(uv1.x, uv1.y, static_cast<unsigned int>(cursorWidth), 0x28,
				             static_cast<unsigned int>(cursorWidth), static_cast<unsigned int>(cursorHeight));
				const MenuOptPair* pp = &pts.p[k];
				gUtil.RenderTextureQuad(pp->x, pp->y + static_cast<float>(y), kOptionSelectorHeight,
				                        kOptionLargeIconSize, cursorPanel, &uv0, &uv1, &color, GX_BL_SRCALPHA,
				                        GX_BL_INVSRCALPHA);
			}

			if ((m_specialModeEdit != 0) && (m_specialModeCursor == i)) {
				gUtil.CalcUV(uv0.x, uv0.y, 0, 0x30, static_cast<unsigned int>(cursorWidth),
				             static_cast<unsigned int>(cursorHeight));
				gUtil.CalcUV(uv1.x, uv1.y, static_cast<unsigned int>(cursorWidth), static_cast<unsigned int>(cursorHeight),
				             static_cast<unsigned int>(cursorWidth), static_cast<unsigned int>(cursorHeight));
				const MenuOptPair* pp1 = &pts.p[k + 1];
				gUtil.RenderTextureQuad(pp1->x, pp1->y + static_cast<float>(y),
				                        cursorWidth, kOptionMeterSegmentSize, cursorPanel,
				                        &uv0, &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

				gUtil.CalcUV(uv0.x, uv0.y, static_cast<unsigned int>(cursorWidth), 0x30,
				             static_cast<unsigned int>(cursorWidth), static_cast<unsigned int>(cursorHeight));
				gUtil.CalcUV(uv1.x, uv1.y, 0, static_cast<unsigned int>(cursorHeight),
				             static_cast<unsigned int>(cursorWidth), static_cast<unsigned int>(cursorHeight));
				gUtil.RenderTextureQuad(cursorWidth + pp1->x, pp1->y + static_cast<float>(y),
				                        cursorWidth, kOptionMeterSegmentSize, cursorPanel,
				                        &uv0, &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
			}

			CTexture* modePanel = GetTextureSetTexture(GetMenuTextureSet(this, 0xBC), 7);
			float modeW = static_cast<float>(modePanel->m_width);
			float modeH = static_cast<float>(modePanel->m_height);
			unsigned int modeHeight = static_cast<unsigned int>(modeH);
			unsigned int modeWidth = static_cast<unsigned int>(modeW);
			gUtil.CalcUV(uv0.x, uv0.y, static_cast<unsigned int>(modeW - kOptionSelectorHeight),
			             uvY, modeWidth, modeHeight);
			gUtil.CalcUV(uv1.x, uv1.y, modeWidth, uvY2, modeWidth, modeHeight);
			const MenuOptPair* pp2 = &pts.p[k + 2];
			int modeXi = static_cast<int>(static_cast<float>(modeU) - pp2->x);
			gUtil.RenderTextureQuad(static_cast<float>(static_cast<int>(static_cast<float>(modeXi) *
			                                           specialRowCos + pp2->x)),
			                        pp2->y + static_cast<float>(y), kOptionLargeIconSize, kOptionSmallIconSize,
			                        modePanel, &uv0, &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

			const MenuOptPair* pp3 = &pts.p[k + 3];
			int step1 = static_cast<int>(kOptionSmallIconSize + (static_cast<float>(modeU) - pp3->x));
			int textXi = static_cast<int>(pp3->x + static_cast<float>(step1) * specialRowCos);
			if (m_specialModeFlags[i] == 0) {
				gUtil.CalcUV(uv0.x, uv0.y, 0, uvY, modeWidth, modeHeight);
				gUtil.CalcUV(uv1.x, uv1.y, 0x78, (i + 1) * 0x20, modeWidth, modeHeight);
				gUtil.RenderTextureQuad(static_cast<float>(textXi), pp3->y + static_cast<float>(y),
				                        kOptionSelectorWidth, kOptionCursorSize,
				                        modePanel, &uv0, &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
				CFont* fnt = m_fonts[0];
				char* txt = OPT_MES(18);
				const MenuOptPair* pp4 = &pts.p[k + 4];
				int textXi2 = static_cast<int>(pp4->x + static_cast<float>(step1) * specialRowCos);
				fnt->SetMargin(kOptionAnimMax);
				fnt->SetShadow(1);
				fnt->SetScale(kOptionAnimMax);
				DrawFont(static_cast<int>(static_cast<float>((kOptionSelectorWidth - fnt->GetWidth(txt)) *
				                          kOptionHalf64 + textXi2)),
				         static_cast<int>(*(const volatile float*)&kOptionTextYOffset + (kOptionModeTextYOffset +
				                          (pp4->y + static_cast<float>(y)))), color, 7,
				         txt, kOptionAnimMax, kOptionAnimMax);
			} else {
				CFont* fnt = m_fonts[0];
				char* txt = OPT_MES(19);
				fnt->SetMargin(kOptionAnimMax);
				fnt->SetShadow(1);
				fnt->SetScale(kOptionAnimMax);
				DrawFont(static_cast<int>(static_cast<float>((kOptionSelectorWidth - fnt->GetWidth(txt)) *
				                          kOptionHalf64 + textXi)),
				         static_cast<int>(*(const volatile float*)&kOptionTextYOffset + (kOptionModeTextYOffset +
				                          (pp3->y + static_cast<float>(y)))), color, 7,
				         txt, kOptionAnimMax, kOptionAnimMax);
				const MenuOptPair* pp4e = &pts.p[k + 4];
				int panelXi = static_cast<int>(pp4e->x + static_cast<float>(step1) * specialRowCos);
				gUtil.CalcUV(uv0.x, uv0.y, 0x78, uvY, modeWidth, modeHeight);
				gUtil.CalcUV(uv1.x, uv1.y, 0xE0, (i + 1) * 0x20, modeWidth, modeHeight);
				gUtil.RenderTextureQuad(static_cast<float>(panelXi),
				                        pp4e->y + static_cast<float>(y), kOptionStereoTextOffset, kOptionCursorSize,
				                        modePanel, &uv0, &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
			}
		}
		break;
	}
	}
}

/*
 * --INFO--
 * PAL Address: 0x80179328
 * PAL Size: 2560b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcOptionMenu()
{
	unsigned short press = static_cast<unsigned short>(GetMenuPress());
	int optionChanged = 0;

	if (m_optionMenuState == 0) {
		m_optionOpenAnim += kOptionOpenAnimStep;
		if (!(m_optionOpenAnim >= kOptionAnimMax)) {
			return;
		}

		m_optionMenuState = 1;
		m_optionOpenAnim = kOptionAnimMax;
		return;
	}

	if (m_optionMenuState == 2) {
		m_optionOpenAnim -= kOptionOpenAnimStep;
		m_optionRowAnim -= kOptionRowAnimStep;
		m_optionColumnAnim -= kOptionColumnAnimStep;

		if (m_optionRowAnim <= kOptionAnimMin) {
			m_optionRowAnim = kOptionAnimMin;
		}
		if (m_optionColumnAnim <= kOptionAnimMin) {
			m_optionColumnAnim = kOptionAnimMin;
		}
		{
			const float& divStep = kOptionOpenAnimStep;
			if (static_cast<int>(m_optionOpenAnim / divStep) == 5) {
				Sound.PlaySe(0x32, 0x40, 0x7F, 0);
			}
		}
		if (!(m_optionOpenAnim <= kOptionAnimMin)) {
			return;
		}

		m_artiState->optionCloseReady = 1;
		m_optionIndex = 0;
		m_optionMenuState = 0;
		m_optionOpenAnim = kOptionAnimMin;
		m_optionRowAnim = kOptionAnimMin;
		m_optionColumnAnim = kOptionAnimMin;
		m_optionAnimCounter = 0;
		m_optionAnimPhase = 0;
		return;
	}

	if (m_optionMenuState == 3) {
		return;
	}

	if (m_optionAnimPhase == 0) {
		m_optionRowAnim += kOptionRowAnimStep;
		m_optionAnimCounter++;
		if (m_optionRowAnim >= kOptionAnimMax) {
			m_optionAnimPhase = 1;
			m_optionRowAnim = kOptionAnimMax;
		}
	} else if (m_optionAnimPhase == 1) {
		m_optionColumnAnim += kOptionColumnAnimStep;
		if (m_optionColumnAnim >= kOptionAnimMax) {
			m_optionAnimPhase = 2;
			m_optionColumnAnim = kOptionAnimMax;
		}
	}

	if (m_leftHintTimer > 0) {
		m_leftHintTimer--;
	}
	if (m_rightHintTimer > 0) {
		m_rightHintTimer--;
	}

	if ((m_specialModeEdit == 0) && ((press & 8) != 0)) {
		m_leftHintTimer = 0;
		m_rightHintTimer = 0;
		m_optionIndex--;
		if (m_optionIndex < 0) {
			m_optionIndex = 4;
		}
		{
			const float& leftMin = kOptionAnimMin;
			m_optionRowAnim = leftMin;
			m_optionColumnAnim = leftMin;
		}
		m_optionAnimCounter = 0;
		m_optionAnimPhase = 0;
		Sound.PlaySe(1, 0x40, 0x7F, 0);
	} else if ((m_specialModeEdit == 0) && ((press & 4) != 0)) {
		m_leftHintTimer = 0;
		m_rightHintTimer = 0;
		m_optionIndex++;
		if (m_optionIndex > 4) {
			m_optionIndex = 0;
		}
		{
			const float& rightMin = kOptionAnimMin;
			m_optionRowAnim = rightMin;
			m_optionColumnAnim = rightMin;
		}
		m_optionAnimCounter = 0;
		m_optionAnimPhase = 0;
		Sound.PlaySe(1, 0x40, 0x7F, 0);
	}

	int specialModeEdit = m_specialModeEdit;
	if (specialModeEdit == 0) {
		unsigned short press2;
		press2 = GetMenuPress();

		if ((press2 & 0x200) != 0) {
			m_optionMenuState = 2;
			Sound.PlaySe(3, 0x40, 0x7F, 0);
			return;
		}
	}

	if (m_optionAnimPhase != 0) {
		if (m_optionAnimPhase == 1) {
			return;
		}
	} else {
		return;
	}

	if ((press & 1) != 0) {
		switch (m_optionIndex) {
		case 0:
			m_gameInitMode--;
			if (m_gameInitMode < 0) {
				m_gameInitMode = 1;
			}
			break;
		case 1:
			m_stereoMode--;
			if (m_stereoMode < 0) {
				m_stereoMode = 1;
			}
			break;
		case 2:
			m_leftHintTimer = 3;
			m_rightHintTimer = 0;
			m_bgmVolume--;
			if (m_bgmVolume < 0) {
				m_bgmVolume = 0;
			}
			break;
		case 3:
			m_leftHintTimer = 3;
			m_rightHintTimer = 0;
			m_seVolume--;
			if (m_seVolume < 0) {
				m_seVolume = 0;
			}
			break;
		case 4:
			if (specialModeEdit != 0) {
				m_specialModeFlags[static_cast<signed char>(m_specialModeCursor)]--;
				if (m_specialModeFlags[static_cast<signed char>(m_specialModeCursor)] < 0) {
					m_specialModeFlags[static_cast<signed char>(m_specialModeCursor)] = 1;
				}
			}
			break;
		}

		Sound.PlaySe(1, 0x40, 0x7F, 0);
		optionChanged = 1;
	} else if ((press & 2) != 0) {
		switch (m_optionIndex) {
		case 0:
			m_gameInitMode++;
			if (m_gameInitMode > 1) {
				m_gameInitMode = 0;
			}
			break;
		case 1:
			m_stereoMode++;
			if (m_stereoMode > 1) {
				m_stereoMode = 0;
			}
			break;
		case 2:
			m_rightHintTimer = 3;
			m_leftHintTimer = 0;
			m_bgmVolume++;
			if (m_bgmVolume > 0xC) {
				m_bgmVolume = 0xC;
			}
			break;
		case 3:
			m_rightHintTimer = 3;
			m_leftHintTimer = 0;
			m_seVolume++;
			if (m_seVolume > 0xC) {
				m_seVolume = 0xC;
			}
			break;
		case 4:
			if (specialModeEdit != 0) {
				m_specialModeFlags[static_cast<signed char>(m_specialModeCursor)]++;
				if (m_specialModeFlags[static_cast<signed char>(m_specialModeCursor)] > 1) {
					m_specialModeFlags[static_cast<signed char>(m_specialModeCursor)] = 0;
				}
			}
			break;
		}

		Sound.PlaySe(1, 0x40, 0x7F, 0);
		optionChanged = 1;
	}

	if (m_optionIndex == 4) {
		int lock = Pad.m_debugPadLock;
		unsigned short press3;
		press3 = GetMenuPressLock(lock);

		if ((press3 & 0x100) != 0) {
			if (m_specialModeEdit == 0) {
				m_specialModeCursor = 0;
				m_specialModeEdit = 1;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
			}
		} else if ((m_specialModeEdit != 0) && ((GetMenuPressLock(lock) & 0x200) != 0)) {
			m_specialModeCursor = 0;
			m_specialModeEdit = 0;
			Sound.PlaySe(3, 0x40, 0x7F, 0);

			Game.m_gameWork.m_spModeFlags[0] =
			    static_cast<unsigned char>(static_cast<unsigned int>(__cntlzw(1 - m_specialModeFlags[0])) >> 5);
			Game.m_gameWork.m_spModeFlags[1] =
			    static_cast<unsigned char>(static_cast<unsigned int>(__cntlzw(1 - m_specialModeFlags[1])) >> 5);
			Game.m_gameWork.m_spModeFlags[2] =
			    static_cast<unsigned char>(static_cast<unsigned int>(__cntlzw(1 - m_specialModeFlags[2])) >> 5);
			Game.m_gameWork.m_spModeFlags[3] =
			    static_cast<unsigned char>(static_cast<unsigned int>(__cntlzw(1 - m_specialModeFlags[3])) >> 5);
		} else if ((m_specialModeEdit != 0) && ((press & 8) != 0)) {
			m_specialModeCursor--;
			if (m_specialModeCursor < 0) {
				m_specialModeCursor = 3;
			}
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		} else if ((m_specialModeEdit != 0) && ((press & 4) != 0)) {
			m_specialModeCursor++;
			if (m_specialModeCursor > 3) {
				m_specialModeCursor = 0;
			}
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		}
	}

	if (optionChanged) {
		Game.m_gameWork.m_gameInitFlag =
		    static_cast<unsigned char>(static_cast<unsigned int>(__cntlzw(static_cast<int>(m_gameInitMode))) >> 5);
		Sound.SetStereo(static_cast<unsigned int>(__cntlzw(static_cast<int>(m_stereoMode))) >> 5);
		{
			const float& seScale = kOptionVolumeScale;
			Sound.SetSeMasterVolume(static_cast<int>(seScale * static_cast<float>(m_seVolume)));
		}
		{
			const float& bgmScale = kOptionVolumeScale;
			Sound.SetBgmMasterVolume(static_cast<int>(bgmScale * static_cast<float>(m_bgmVolume)));
		}
	}
}

#pragma push
#pragma optimization_level 4
/*
 * --INFO--
 * PAL Address: 0x80179d28
 * PAL Size: 256b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetOptionData()
{
	signed char& gameInitMode = m_gameInitMode;
	signed char& stereoMode = m_stereoMode;
	signed char& bgmVolume = m_bgmVolume;
	signed char& seVolume = m_seVolume;

	gameInitMode =
	    static_cast<signed char>(static_cast<unsigned int>(__cntlzw(static_cast<unsigned int>(Game.m_gameWork.m_gameInitFlag))) >> 5);

	unsigned int soundMode = Sound.GetSoundMode();
	unsigned int soundModeClz = static_cast<unsigned int>(__cntlzw(soundMode));
	stereoMode = static_cast<signed char>(static_cast<unsigned int>(__cntlzw(soundModeClz >> 5)) >> 5);

	int value = Sound.GetBgmMasterVolume();
	bgmVolume = static_cast<signed char>(value / 10);

	value = Sound.GetSeMasterVolume();
	seVolume = static_cast<signed char>(value / 10);

	unsigned int flag = Game.m_gameWork.m_spModeFlags[0];
	m_specialModeFlags[0] = static_cast<signed char>((-flag | flag) >> 31);
	flag = Game.m_gameWork.m_spModeFlags[1];
	m_specialModeFlags[1] = static_cast<signed char>((-flag | flag) >> 31);
	flag = Game.m_gameWork.m_spModeFlags[2];
	m_specialModeFlags[2] = static_cast<signed char>((-flag | flag) >> 31);
	flag = Game.m_gameWork.m_spModeFlags[3];
	m_specialModeFlags[3] = static_cast<signed char>((-flag | flag) >> 31);
}
#pragma pop

/*
 * --INFO--
 * PAL Address: 0x80179e28
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetManaWaterEffect()
{
	int partNo = m_effectWork[5].m_partNo;

	if (partNo != -1) {
		PartMng.pppDeletePart(partNo);
	}

	BindEffect(5, Game.m_gameWork.m_timerA + 0x13, -1);
	m_manaWaterTimerA = Game.m_gameWork.m_timerA;
}

/*
 * --INFO--
 * PAL Address: 0x80179e9c
 * PAL Size: 244b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetCrystalCageAttr()
{
	if (m_crystalPart != -1) {
		PartMng.pppDeletePart(m_crystalPart);
	}

	unsigned int chaliceElement = Game.m_gameWork.m_chaliceElement;
	if ((chaliceElement & 1U) != 0) {
		m_crystalAttr = 0xE;
		m_crystalElem = 1;
	} else if ((chaliceElement & 2U) != 0) {
		m_crystalAttr = 0xF;
		m_crystalElem = 2;
	} else if ((chaliceElement & 4U) != 0) {
		m_crystalAttr = 0x10;
		m_crystalElem = 4;
	} else if ((chaliceElement & 8U) != 0) {
		m_crystalAttr = 0x11;
		m_crystalElem = 8;
	} else if ((chaliceElement & 0x10U) != 0) {
		m_crystalAttr = 0x12;
		m_crystalElem = 0x10;
	}

	m_crystalPart = BindEffect(5, m_crystalAttr, -1);
	m_effectTimer = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
#pragma dont_inline on
void CMenuPcs::DrawHelpMessage(int msgNo, CFont* font, int posX, int posY, _GXColor color, int tlut, float margin, float scaleY)
{
	if (msgNo >= 0) {
		DrawHelpMessageUS(msgNo, font, posX, posY, color, tlut, margin, scaleY);
	}
}
#pragma dont_inline reset

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
#pragma push
#pragma optimization_level 4
#pragma opt_propagation off
void CMenuPcs::DrawHelpMessageUS(int msgNo, CFont* font, int, int, _GXColor color, int tlut, float margin, float scale)
{
	unsigned char* const self = reinterpret_cast<unsigned char*>(this);
	char* anchor = lbl_801E3058;
	const CCaravanWork* const caravanWork = reinterpret_cast<const CCaravanWork*>(Game.m_scriptFoodBase[0]);
	u32 lineBaseY[4];
	const int* lineBaseData = reinterpret_cast<const int*>(anchor + 0x678);
	lineBaseY[0] = lineBaseData[0];
	lineBaseY[1] = lineBaseData[1];
	lineBaseY[2] = lineBaseData[2];
	lineBaseY[3] = lineBaseData[3];

	int languageIndex = Game.m_gameWork.m_languageId - 1;
	int drawPrefix = 1;
	float lineStep = *(const volatile float*)&kHelpMessageLineStep;
	const char* suffix = 0;
	char itemName[260];
	char scratch[0x100];

	font->SetMargin(kOptionTextNudge);
	font->SetShadow(1);
	font->SetScale(margin);
	font->DrawInit();
	font->SetTlut(tlut);
	font->SetColor(color);
	font->SetScale(*(const volatile float*)&kOptionMenuFontScale);

	int maxWidth;
	int firstLine = 500;
	int lineMax;
	if ((0 <= msgNo) && (msgNo <= 0x268)) {
		firstLine = msgNo * 3 + 0x1F5;
		lineMax = 3;
	}
	maxWidth = -1;

	CMemory::CStage* stage;
	if (Game.m_gameWork.m_menuStageMode != 0) {
		stage = MenuPcs.m_stageF4;
	} else {
		stage = MenuPcs.m_menuStage;
	}

	char* temp = new (stage, anchor + 0x7A4, 0x8C) char[0x200];
	if ((temp == nullptr) && (static_cast<unsigned int>(System.m_execParam) >= 1)) {
		System.Printf(anchor + 0x7B4, anchor + 0x7A4, 0x8E);
	}
	for (int line = firstLine; line < firstLine + 3; line++) {
		char* msg = GetMenuHelpMsgTable()[line];
		memset(temp, 0, 0x200);
		CMes::MakeAgbString(temp, msg, 0, 1);
		if (strlen(temp) != 0) {
			int width = static_cast<int>(CMes::drawTagString(font, msg, 0, 0, 0));
			if (width < maxWidth) {
				width = maxWidth;
			}
			maxWidth = width;
		}
	}
	delete[] temp;

	if ((msgNo >= 0x259) && (msgNo <= 0x268)) {
		drawPrefix = 0;
	} else {
		if (msgNo == 0x209) {
			suffix = GetSkillStr(0);
		} else if (msgNo == 0x20D) {
			suffix = GetSkillStr(1);
		} else if (msgNo == 0x211) {
			suffix = GetSkillStr(2);
		} else {
			suffix = sMenuUtilEmptyText;
		}

		if ((msgNo == 0x209) || (msgNo == 0x20D) || (msgNo == 0x211)) {
			itemName[0] = '\0';
		} else {
			Game.MakeArtItemName(itemName, msgNo, 1);
			if ((strlen(itemName) != 0) && (static_cast<signed char>(itemName[0]) != 0)) {
				itemName[0] = static_cast<char>(toupperLatin1(static_cast<unsigned char>(itemName[0])));
			}
		}

		int four = drawPrefix + 3;
		if (four == 4) {
			lineStep = *(const volatile float*)&kOptionUiTwenty;
		}
	}

	int rangeKind;
	if ((1 <= msgNo) && (msgNo < 0x45)) {
		rangeKind = 1;
	} else if ((0x45 <= msgNo) && (msgNo < 0x7F)) {
		rangeKind = 0x45;
	} else if ((0x7F <= msgNo) && (msgNo < 0x9F)) {
		rangeKind = 0x7F;
	} else {
		rangeKind = 0;
	}

	if (rangeKind != 0) {
		int baseIndex = drawPrefix + 2;
		u32 baseY = lineBaseY[baseIndex];
		int y = baseY;
		if (drawPrefix != 0) {
			font->SetPosX(*(const volatile float*)&kOptionRowLeft);
			font->SetPosY(static_cast<float>(static_cast<int>(y)));
			font->Draw(itemName);
			font->Draw(suffix);
			y = static_cast<int>(static_cast<float>(static_cast<int>(y)) + lineStep);
		}

		for (int i = 0; i < lineMax; i++) {
			char* msg = GetMenuHelpMsgTable()[firstLine + i];
			font->SetPosX(static_cast<float>(0x140 - maxWidth / 2));
			font->SetPosY(static_cast<float>(static_cast<int>(y)));
			CMes::drawTagString(font, msg, 1, 0, 0);
			y = static_cast<int>(static_cast<float>(static_cast<int>(y)) + lineStep);
		}

	int itemBase = Game.unkCFlatData0[2] + msgNo * 0x48;
	u16 flags = *reinterpret_cast<u16*>(itemBase + 4);
	if ((flags & 0x100) != 0) {
		strcpy(scratch, PTR_s_Strength__80215a48[languageIndex * 20]);
	} else if ((flags & 0x200) != 0) {
		strcpy(scratch, PTR_s_Defence__80215a4c[languageIndex * 20]);
	} else if ((flags & 0x400) != 0) {
		strcpy(scratch, PTR_s_Defence__80215a4c[languageIndex * 20]);
	} else if ((flags & 0x800) != 0) {
		strcpy(scratch, PTR_s_Defence__80215a4c[languageIndex * 20]);
	} else if ((flags & 0x1000) != 0) {
		strcpy(scratch, sMenuUtilEmptyText);
	} else if ((flags & 0x2000) != 0) {
		strcpy(scratch, sMenuUtilEmptyText);
	}

	int x = 0x38;
	font->SetPosX(*(const volatile float*)&kOptionRowLeft);
	int detailY = static_cast<int>(lineStep + static_cast<float>(static_cast<int>(baseY)));
	font->SetPosY(static_cast<float>(detailY));

		if ((*reinterpret_cast<u16*>(itemBase + 4) & 0x1000) != 0) {
			if (*reinterpret_cast<u16*>(itemBase + 8) >= 1) {
				if (*reinterpret_cast<u16*>(itemBase + 8) > 0x13) {
					return;
				} else {
					strcpy(scratch, GetAttrStr(*reinterpret_cast<u16*>(itemBase + 8)));
					font->SetTlut(4);
					font->Draw(scratch);
					x = static_cast<int>(static_cast<float>(x) + (*(const volatile float*)&kOptionTextNudge + font->GetWidth(scratch)));
					font->SetPosX(static_cast<float>(x));
					font->SetTlut(9);

					unsigned int attr = *reinterpret_cast<u16*>(itemBase + 8);
					if ((attr >= 1) && (attr <= 8)) {
						sprintf(scratch, sMenuUtilStringFormat, sMenuUtilPlusOneText);
					} else if ((attr == 0xB) || (attr == 0x11) || (attr == 0x12)) {
						sprintf(scratch, sMenuUtilSignedValueFormat, 0x2B, *reinterpret_cast<u16*>(itemBase + 6));
					} else if ((static_cast<unsigned short>(attr - 9) <= 1) || (attr == 0xC)) {
						sprintf(scratch, sMenuUtilSignedValueFormat, 0x2D, *reinterpret_cast<u16*>(itemBase + 6));
						font->SetTlut(3);
					} else {
						return;
					}

					font->Draw(scratch);
				}
			}
		} else {
			strcat(scratch, sMenuUtilSpaceText);
			font->Draw(scratch);

			x = static_cast<int>(static_cast<float>(x) + (*(const volatile float*)&kOptionTextNudge + font->GetWidth(scratch)));
			font->SetTlut(1);
			font->SetPosX(static_cast<float>(x));
			sprintf(scratch, sMenuUtilValueSuffixFormat, *reinterpret_cast<u16*>(itemBase + 6));
			font->Draw(scratch);

			int sel = m_artiState->currentSelection;
			if ((static_cast<int>(m_battleStateFlag) == 2) && (sel == 1)) {
				u16 effectFlags = *reinterpret_cast<u16*>(itemBase + 4);

				if ((effectFlags & 0x1000) == 0) {
					int currentItem = -1;
					if ((effectFlags & 0x100) != 0) {
						currentItem = 0;
					} else if ((effectFlags & 0x400) != 0) {
						currentItem = 1;
					} else if ((effectFlags & 0x800) != 0) {
						currentItem = 2;
					} else if ((effectFlags & 0x200) != 0) {
						currentItem = 2;
					} else if ((effectFlags & 0x1000) != 0) {
						currentItem = 3;
					} else if ((effectFlags & 0x2000) != 0) {
						currentItem = 3;
					}

					unsigned int equipmentSlot = caravanWork->m_equipment[currentItem];
					currentItem = (equipmentSlot >= 0) ? caravanWork->m_inventoryItems[equipmentSlot] : -1;

					if (static_cast<unsigned char>(ChkEquipActive(static_cast<int>(m_artiState->selections[sel]) +
					                                              static_cast<int>(m_artiState->scrollOffset))) != 0) {
						int currentItemBase = Game.unkCFlatData0[2] + currentItem * 0x48;
						unsigned int currentValue;
						if (currentItem == -1) {
							currentValue = 0;
						} else {
							currentValue = *reinterpret_cast<u16*>(currentItemBase + 6);
						}

						int delta = static_cast<int>(*reinterpret_cast<u16*>(itemBase + 6)) - static_cast<int>(currentValue);
						int deltaX = static_cast<int>(static_cast<float>(x) + (*(const volatile float*)&kOptionTextNudge + font->GetWidth(scratch)));
						font->SetPosX(static_cast<float>(deltaX));
						if (delta >= 0) {
							font->SetTlut(9);
						} else {
							font->SetTlut(3);
						}
						sprintf(scratch, sMenuUtilSignedDeltaFormat, delta);
						if (delta != 0) {
							font->Draw(scratch);
						}
					}
				}
			}

			float attrPosX = font->posX;
			int attrX = static_cast<int>(attrPosX + font->GetWidth(sMenuUtilSpaceText));
			font->SetPosX(static_cast<float>(attrX));

			if ((*reinterpret_cast<u16*>(itemBase + 4) & 0x1000) == 0) {
				if ((*reinterpret_cast<u16*>(itemBase + 8) >= 1) && (*reinterpret_cast<u16*>(itemBase + 8) <= 0x13)) {
					font->SetTlut(4);
					strcpy(scratch, GetAttrStr(*reinterpret_cast<u16*>(itemBase + 8)));
					font->Draw(scratch);
					font->SetTlut(9);
					unsigned int attr = *reinterpret_cast<u16*>(itemBase + 8);
					if ((attr >= 1) && (attr <= 8)) {
						sprintf(scratch, sMenuUtilAttrBonusFormat, sMenuUtilPlusOneText);
					} else {
						return;
					}
					font->Draw(scratch);
				}
			}
		}
		} else {
		int lineCount = 3;
		int firstNonEmptyLine = firstLine;
		temp = new ((Game.m_gameWork.m_menuStageMode != 0) ? MenuPcs.m_stageF4 : MenuPcs.m_menuStage,
		            anchor + 0x7A4, 0x23D) char[0x200];
		if ((temp == nullptr) && (static_cast<int>(System.m_execParam) >= 1)) {
			System.Printf(anchor + 0x7B4, anchor + 0x7A4, 0x23F);
		}
		for (int i = 0; i < lineMax; i++) {
			char* msg = GetMenuHelpMsgTable()[firstLine + i];
			memset(temp, 0, 0x200);
			CMes::MakeAgbString(temp, msg, 0, 1);
			if (strlen(temp) == 0) {
				lineCount--;
				if (firstNonEmptyLine == firstLine + i) {
					firstNonEmptyLine++;
				}
			}
		}
		delete[] temp;

		int idx = lineCount + drawPrefix - 1;
		int y = lineBaseY[idx];
		if (drawPrefix != 0) {
			font->SetPosX(*(const volatile float*)&kOptionRowLeft);
			font->SetPosY(static_cast<float>(static_cast<int>(y)));
			font->Draw(itemName);
			font->Draw(suffix);
			y = static_cast<int>(static_cast<float>(y) + lineStep);
		}

		for (int i = 0; i < lineCount; i++) {
			char* msg = GetMenuHelpMsgTable()[firstNonEmptyLine + i];
			font->SetPosX(static_cast<float>(0x140 - maxWidth / 2));
			font->SetPosY(static_cast<float>(static_cast<int>(y)));
			CMes::drawTagString(font, msg, 1, 0, 0);
			y = static_cast<int>(static_cast<float>(static_cast<int>(y)) + lineStep);
		}
	}
}
#pragma pop

/*
 * --INFO--
 * PAL Address: 0x8017ac40
 * PAL Size: 272b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma dont_inline on
void CMenuPcs::DrawFont2(int posX, int posY, _GXColor color, int tlut, char* text, float scaleX, float scaleY, float margin)
{
	CFont* font = m_fonts[0];

	font->SetMargin(margin);
	font->SetShadow(1);
	font->SetScaleX(scaleX);
	font->SetScaleY(scaleY);
	font->DrawInit();
	font->SetTlut(tlut);
	font->SetColor(color);
	font->SetPosX((float)posX);
	font->SetPosY((float)posY);
	font->Draw(text);
}
#pragma dont_inline reset

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
#pragma dont_inline on
void CMenuPcs::DrawFont(int posX, int posY, _GXColor color, int tlut, char* text, float scale, float margin)
{
	CFont* font = m_fonts[0];

	font->SetMargin(margin);
	font->SetShadow(1);
	font->SetScale(scale);
	font->DrawInit();
	font->SetTlut(tlut);
	font->SetColor(color);
	font->SetPosX((float)posX);
	font->SetPosY((float)posY);
	font->Draw(text);
}
#pragma dont_inline reset

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
float CMenuPcs::CalcCenteringPos(char* text, CFont* font)
{
    const float& halfWidth = kMenuCenteringHalfWidth;
    const float& offset = kMenuCenteringOffset;
    float width = font->GetWidth(text);
    return offset - width * halfWidth;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
float CMenuPcs::CalcCenteringPos2(char* text, float scale, float margin)
{
	CFont* font = m_fonts[0];
	float width;
	const float& scaleY = kOptionAnimMax;
	const float& halfWidth = kMenuCenteringHalfWidth;
	const float& offset = kMenuCenteringOffset;

	font->SetShadow(1);
	font->SetMargin(margin);
	font->SetScaleX(scale);
	font->SetScaleY(scaleY);
	width = font->GetWidth(text);
	return offset - width * halfWidth;
}

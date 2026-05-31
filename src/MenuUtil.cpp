#include "ffcc/MenuUtil.h"
#include "ffcc/partMng.h"
#include "ffcc/game.h"
#include "ffcc/memory.h"
#include "ffcc/mes.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include "ffcc/RedSound/RedSound.h"
#include "ffcc/fontman.h"
#include "ffcc/strcase.h"
#include "ffcc/util.h"
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/string.h>

struct Vec2d {
	float x;
	float y;
};

extern "C" char s_MenuUtil_cpp_801e37fc[];
extern char lbl_801E3058[];
extern "C" const float FLOAT_80333614 = 196.0f;
extern "C" const float FLOAT_80333618 = 168.0f;
extern "C" const float FLOAT_8033361C = 24.0f;
extern "C" const float FLOAT_80333620 = 20.0f;
extern "C" const float FLOAT_80333624 = 16.0f;
extern "C" const float FLOAT_80333628 = 564.0f;
extern "C" const float FLOAT_8033362C = 0.07692308f;
extern "C" const float FLOAT_80333630 = 6.923077f;
extern "C" const float FLOAT_80333634 = 4.0f;
extern "C" const unsigned int DOUBLE_80333638[2] = {0x43300000, 0x00000000};
extern "C" const unsigned int DOUBLE_80333640[2] = {0x43300000, 0x80000000};
extern "C" const float FLOAT_80333608 = 190.0f;
extern "C" const float FLOAT_8033360C = 587.0f;
extern "C" const float FLOAT_80333610 = 372.0f;
extern "C" const float kOptionOpenAnimStep = 0.04f;
extern "C" const float kOptionColumnAnimStep = 0.2f;
extern "C" const float kOptionVolumeScale = 10.583333f;
extern "C" const float FLOAT_80333654 = 25.0f;
extern float FLOAT_80333548;
extern float FLOAT_80333550;
extern float FLOAT_80333554;
extern float FLOAT_8033355C;
extern float FLOAT_80333560;
extern float FLOAT_80333564;
extern float FLOAT_80333568;
extern float FLOAT_80333570;
extern float FLOAT_80333574;
extern float FLOAT_80333578;
extern float FLOAT_8033357c;
extern float FLOAT_80333580;
extern float FLOAT_80333584;
extern float FLOAT_80333588;
extern float FLOAT_80333590;
extern float FLOAT_803335a0;
extern float FLOAT_803335B0;
extern float FLOAT_803335B4;
extern const char sMenuUtilEmptyText[4] = "";
extern const char sMenuUtilStringFormat[] = "%s";
extern const char sMenuUtilPlusOneText[] = "+1";
extern const char sMenuUtilSignedValueFormat[] = "%c%d";
extern const char sMenuUtilSpaceText[] = " ";
extern const char sMenuUtilValueSuffixFormat[] = " %d";
extern const char sMenuUtilSignedDeltaFormat[] = " %+d";
extern const char sMenuUtilAttrBonusFormat[] = " %s";
extern "C" char s_Force_803334F0[] = "Force";
extern "C" char s_Musique_803334F8[] = "Musique";
extern "C" char s_Active_80333500[8] = "Activ\351";
extern "C" char s_Stereo_80333508[8] = "St\351r\351o";
extern "C" char s_Fuerza_80333510[] = "Fuerza";
extern "C" char s_Defensa_80333518[] = "Defensa";
extern "C" char s_Musica_80333520[8] = "M\372sica";
extern "C" char s_Apagado_80333528[] = "Apagado";
extern char s_Strength_801E30A4[];
extern char s_Defence_801E30B0[];
extern char s_Position_Markers_801E30BC[];
extern char s_Sound_Mode_801E30D0[];
extern char s_Sound_Effects_801E30DC[];
extern char s_GBA_Colour_Balance_801E30EC[];
extern char s_Show_or_hide_position_marker_under_each_character_s_feet_801E3100[];
extern char s_Select_stereo_or_monaural_sound_801E313C[];
extern char s_Adjust_volume_of_background_music_801E3160[];
extern char s_Adjust_volume_of_sound_effects_801E3184[];
extern char s_Adjust_colour_balance_of_Game_Boy_Advance_801E31A4[];
extern char s_Monaural_801E31D0[];
extern char s_Enhanced_801E31DC[];
extern char s_Standard_801E31E8[];
extern char s_Erkennungskreisel_801E31F4[];
extern char s_Tonausgabe_801E3208[];
extern char s_MenuOptionSoundEffectsDe_801E3214[];
extern char s_Farbeinstellung_801E3224[];
extern char s_Erkennungskreisel_des_Charakters_AN_AUS_schalten_801E3234[];
extern char s_Tonausgabe_auf_Stereo_oder_Mono_schalten_801E3268[];
extern char s_Lautstaerke_der_Musik_aendern_801E3294[];
extern char s_Lautstaerke_der_Geraeuscheffekte_aendern_801E32B4[];
extern char s_Farbeinstellung_des_Game_Boy_Advance_aendern_801E32DC[];
extern char s_Erweitert_801E330C[];
extern char s_Indicatori_di_posizione_801E3318[];
extern char s_Effetti_sonori_801E3330[];
extern char s_Bilanc_colore_GBA_801E3340[];
extern char s_Attiva_o_disattiva_l_indicatore_ai_piedi_dei_personaggi_801E3354[];
extern char s_Scegli_tra_sonoro_mono_o_stereo_801E3390[];
extern char s_Regola_il_volume_della_musica_801E33B4[];
extern char s_Regola_il_volume_degli_effetti_sonori_801E33D4[];
extern char s_Regola_il_colore_sul_Game_Boy_Advance_801E33FC[];
extern char s_ResistanceFr_801E3424[];
extern char s_Sceau_de_position_801E3430[];
extern char s_Signal_sonore_801E3444[];
extern char s_Effets_sonores_801E3454[];
extern char s_Affichage_du_GBA_801E3464[];
extern char s_Affichage_du_sceau_de_position_aux_pieds_des_personnages_801E3478[];
extern char s_Choisissez_le_signal_sonore_stereo_ou_mono_801E34B4[];
extern char s_Reglez_le_volume_de_la_musique_801E34E0[];
extern char s_Reglez_le_volume_des_effets_sonores_801E3500[];
extern char s_Reglez_le_contraste_des_couleurs_du_Game_Boy_Advance_801E3524[];
extern char s_MenuOptionDesactive_801E355C[];
extern char s_MenuOptionAmeliore_801E3568[];
extern char s_Aro_de_posicion_801E3574[];
extern char s_Tipo_de_sonido_801E3584[];
extern char s_Efectos_de_sonido_801E3594[];
extern char s_Color_de_la_GBA_801E35A8[];
extern char s_Senala_la_posicion_bajo_los_pies_de_cada_personaje_801E35B8[];
extern char s_Selecciona_sonido_estereo_o_monoaural_801E35EC[];
extern char s_Ajusta_el_volumen_de_la_musica_de_fondo_801E3614[];
extern char s_Ajusta_el_volumen_de_los_efectos_de_sonido_801E3640[];
extern char s_Ajusta_el_balance_del_color_de_la_Game_Boy_Advance_801E366C[];
extern char s_Encendido_801E36A0[];
extern char s_Monoaural_801E36AC[];
extern char s_Mejorado_801E36B8[];
extern char s_MenuOptionEstandar_801E36C4[];
extern char s_MenuOptionMusic[];
extern char s_MenuOptionOn[];
extern char s_MenuOptionOff[];
extern char s_MenuOptionStereo[];
extern char s_MenuOptionMin[];
extern char s_MenuOptionMax[];
extern char s_MenuOptionStrengthDe[];
extern char s_MenuOptionDefenceDe[];
extern char s_MenuOptionMusicDe[];
extern char s_MenuOptionOnDe[];
extern char s_MenuOptionOffDe[];
extern char s_MenuOptionStereoDe[];
extern char s_MenuOptionMonoUpper_803334A8[];
extern char s_MenuOptionNormalIt_803334B0[];
extern char s_MenuOptionForza_803334B8[];
extern char s_MenuOptionDifesa_803334C0[];
extern char s_MenuOptionSonoro_803334C8[];
extern char s_MenuOptionMusica_803334D0[];
extern char s_MenuOptionMonoIt_803334D8[];
extern char s_MenuOptionContr_803334E0[];
extern char s_MenuOptionNorm_803334E8[];
extern char s_Force_803334F0[];
extern char s_Musique_803334F8[];
extern char s_Active_80333500[];
extern char s_Stereo_80333508[];
extern char s_Fuerza_80333510[];
extern char s_Defensa_80333518[];
extern char s_Musica_80333520[];
extern char s_Apagado_80333528[];
extern char s_MenuOptionEstereo_80333530[];
extern char s_MenuOptionMinEs_80333538[];
extern char s_MenuOptionMaxEs_80333540[];
extern "C" char* g_strMenuUtilMes[] = {
	s_Strength_801E30A4, s_Defence_801E30B0, s_Position_Markers_801E30BC, s_Sound_Mode_801E30D0,
	s_MenuOptionMusic, s_Sound_Effects_801E30DC, s_GBA_Colour_Balance_801E30EC,
	s_Show_or_hide_position_marker_under_each_character_s_feet_801E3100,
	s_Select_stereo_or_monaural_sound_801E313C, s_Adjust_volume_of_background_music_801E3160,
	s_Adjust_volume_of_sound_effects_801E3184, s_Adjust_colour_balance_of_Game_Boy_Advance_801E31A4,
	s_MenuOptionOn, s_MenuOptionOff, s_MenuOptionStereo, s_Monaural_801E31D0,
	s_MenuOptionMin, s_MenuOptionMax, s_Enhanced_801E31DC, s_Standard_801E31E8,
	s_MenuOptionStrengthDe, s_MenuOptionDefenceDe, s_Erkennungskreisel_801E31F4, s_Tonausgabe_801E3208,
	s_MenuOptionMusicDe, s_MenuOptionSoundEffectsDe_801E3214, s_Farbeinstellung_801E3224,
	s_Erkennungskreisel_des_Charakters_AN_AUS_schalten_801E3234,
	s_Tonausgabe_auf_Stereo_oder_Mono_schalten_801E3268, s_Lautstaerke_der_Musik_aendern_801E3294, s_Lautstaerke_der_Geraeuscheffekte_aendern_801E32B4,
	s_Farbeinstellung_des_Game_Boy_Advance_aendern_801E32DC, s_MenuOptionOnDe, s_MenuOptionOffDe, s_MenuOptionStereoDe, s_MenuOptionMonoUpper_803334A8,
	s_MenuOptionMin, s_MenuOptionMax, s_Erweitert_801E330C, s_MenuOptionNormalIt_803334B0,
	s_MenuOptionForza_803334B8, s_MenuOptionDifesa_803334C0, s_Indicatori_di_posizione_801E3318, s_MenuOptionSonoro_803334C8,
	s_MenuOptionMusica_803334D0, s_Effetti_sonori_801E3330, s_Bilanc_colore_GBA_801E3340,
	s_Attiva_o_disattiva_l_indicatore_ai_piedi_dei_personaggi_801E3354,
	s_Scegli_tra_sonoro_mono_o_stereo_801E3390, s_Regola_il_volume_della_musica_801E33B4,
	s_Regola_il_volume_degli_effetti_sonori_801E33D4, s_Regola_il_colore_sul_Game_Boy_Advance_801E33FC,
	s_MenuOptionOn, s_MenuOptionOff, s_MenuOptionStereo, s_MenuOptionMonoIt_803334D8, s_MenuOptionMin, s_MenuOptionMax,
	s_MenuOptionContr_803334E0, s_MenuOptionNorm_803334E8,
	s_Force_803334F0, s_ResistanceFr_801E3424, s_Sceau_de_position_801E3430, s_Signal_sonore_801E3444,
	s_Musique_803334F8, s_Effets_sonores_801E3454, s_Affichage_du_GBA_801E3464,
	s_Affichage_du_sceau_de_position_aux_pieds_des_personnages_801E3478,
	s_Choisissez_le_signal_sonore_stereo_ou_mono_801E34B4, s_Reglez_le_volume_de_la_musique_801E34E0, s_Reglez_le_volume_des_effets_sonores_801E3500, s_Reglez_le_contraste_des_couleurs_du_Game_Boy_Advance_801E3524, s_Active_80333500,
	s_MenuOptionDesactive_801E355C, s_Stereo_80333508, s_MenuOptionMonoIt_803334D8, s_MenuOptionMin, s_MenuOptionMax,
	s_MenuOptionAmeliore_801E3568, s_Standard_801E31E8,
	s_Fuerza_80333510, s_Defensa_80333518, s_Aro_de_posicion_801E3574, s_Tipo_de_sonido_801E3584,
	s_Musica_80333520, s_Efectos_de_sonido_801E3594, s_Color_de_la_GBA_801E35A8,
	s_Senala_la_posicion_bajo_los_pies_de_cada_personaje_801E35B8, s_Selecciona_sonido_estereo_o_monoaural_801E35EC, s_Ajusta_el_volumen_de_la_musica_de_fondo_801E3614, s_Ajusta_el_volumen_de_los_efectos_de_sonido_801E3640,
	s_Ajusta_el_balance_del_color_de_la_Game_Boy_Advance_801E366C, s_Encendido_801E36A0,
	s_Apagado_80333528, s_MenuOptionEstereo_80333530, s_Monoaural_801E36AC, s_MenuOptionMinEs_80333538, s_MenuOptionMaxEs_80333540,
	s_Mejorado_801E36B8, s_MenuOptionEstandar_801E36C4,
};

#define PTR_s_Strength__80215a48 g_strMenuUtilMes
#define PTR_s_Defence__80215a4c (g_strMenuUtilMes + 1)

// Constants defined externally, placed in .sdata2 by the linker.
extern const float kMenuCenteringHalfWidth;
extern const float kOptionAnimMin;
extern const float kOptionAnimMax;
extern const float kMenuCenteringOffset;
extern const float kOptionRowAnimStep;
extern const float kOptionOpenAnimStep;
extern const float kOptionColumnAnimStep;
extern const float kOptionVolumeScale;

namespace {
struct MenuUtilFlatTableEntry {
	int count;
	const char** index;
	char* buffer;
};

struct MenuUtilFlatData {
	char pad[0x6C];
	MenuUtilFlatTableEntry table[8];
};

static inline int* GetMenuHelpMsgTable()
{
	return reinterpret_cast<int*>(reinterpret_cast<MenuUtilFlatData*>(&Game.m_cFlatDataArr[1])->table[6].index);
}

static inline CRedSound* GetRedSoundGlobal()
{
	return reinterpret_cast<CRedSound*>(reinterpret_cast<unsigned char*>(&Sound) + 8);
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
	unsigned char* ptrArray = reinterpret_cast<unsigned char*>(set) + 8;
	CTexture** textures = *reinterpret_cast<CTexture***>(ptrArray + 0x10);
	return textures[index];
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

	if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
		activeInput = true;
	}

	if (activeInput) {
		return 0;
	}

	int padIndex = 0;
	padIndex &= ~-((__cntlzw(static_cast<unsigned int>(Pad._448_4_)) & 0x20) >> 5);
	return *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(&Pad) + padIndex * 0x54 + 8);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
float CMenuPcs::CalcCenteringPos2(char* text, float scale, float margin)
{
	CFont* font = menuFont;
	float width;

	font->SetShadow(1);
	font->SetMargin(margin);
	font->SetScaleX(scale);
	font->SetScaleY(kOptionAnimMax);
	width = font->GetWidth(text);
	return kMenuCenteringOffset - width * kMenuCenteringHalfWidth;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
float CMenuPcs::CalcCenteringPos(char* text, CFont* font)
{
    float width = font->GetWidth(text);
    return -(width * kMenuCenteringHalfWidth - kMenuCenteringOffset);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawFont(int posX, int posY, _GXColor color, int tlut, char* text, float scale, float margin)
{
	CFont* font = menuFont;

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

/*
 * --INFO--
 * PAL Address: 0x8017ac40
 * PAL Size: 272b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawFont2(int posX, int posY, _GXColor color, int tlut, char* text, float scaleX, float scaleY, float margin)
{
	CFont* font = menuFont;

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

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawHelpMessageUS(int msgNo, CFont* font, int, int, _GXColor color, int tlut, float margin, float scale)
{
	unsigned char* const self = reinterpret_cast<unsigned char*>(this);
	unsigned char* const menuPcsGlobal = reinterpret_cast<unsigned char*>(&MenuPcs);
	u32 foodBase = Game.m_scriptFoodBase[0];
	u32 lineBaseY[4];
	const u32* lineBaseData = reinterpret_cast<const u32*>(lbl_801E3058 + 0x678);
	lineBaseY[0] = lineBaseData[0];
	lineBaseY[1] = lineBaseData[1];
	lineBaseY[2] = lineBaseData[2];
	lineBaseY[3] = lineBaseData[3];

	int languageIndex = Game.m_gameWork.m_languageId - 1;
	int drawPrefix = 1;
	int firstLine = 500;
	int maxWidth = -1;
	float lineStep = FLOAT_80333654;
	const char* suffix = 0;
	char itemName[260];
	char scratch[0x100];
	itemName[0] = '\0';

	font->SetMargin(FLOAT_803335a0);
	font->SetShadow(1);
	font->SetScale(margin);
	font->DrawInit();
	font->SetTlut(tlut);
	font->SetColor(color);
	font->SetScale(FLOAT_80333548);

	if ((0 <= msgNo) && (msgNo <= 0x268)) {
		firstLine = msgNo * 3 + 0x1F5;
	}

	CMemory::CStage* stage = *reinterpret_cast<CMemory::CStage**>(menuPcsGlobal + 0xEC);
	if (Game.m_gameWork.m_menuStageMode != 0) {
		stage = *reinterpret_cast<CMemory::CStage**>(menuPcsGlobal + 0xF4);
	}

	char* temp = new (stage, s_MenuUtil_cpp_801e37fc, 0x8C) char[0x200];
	if ((temp == nullptr) && (System.m_execParam != 0)) {
		System.Printf(s_MenuUtil_cpp_801e37fc + 0x10, s_MenuUtil_cpp_801e37fc, 0x8E);
	}
	for (int line = firstLine; line < firstLine + 3; line++) {
		int msgId = GetMenuHelpMsgTable()[line];
		memset(temp, 0, 0x200);
		CMes::MakeAgbString(temp, reinterpret_cast<char*>(msgId), 0, 1);
		if (strlen(temp) != 0) {
			int width = static_cast<int>(CMes::drawTagString(font, reinterpret_cast<char*>(msgId), 0, 0, 0));
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
			if ((strlen(itemName) != 0) && (itemName[0] != '\0')) {
				itemName[0] = static_cast<char>(toupperLatin1(static_cast<unsigned char>(itemName[0])));
			}
		}
	}
	if (drawPrefix == 1) {
		lineStep = FLOAT_80333620;
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
			font->SetPosX(FLOAT_8033357c);
			font->SetPosY(static_cast<float>(static_cast<int>(y)));
			font->Draw(itemName);
			font->Draw(suffix);
			y = static_cast<int>(static_cast<float>(static_cast<int>(y)) + lineStep);
		}

		for (int i = 0; i < 3; i++) {
			int msgId = GetMenuHelpMsgTable()[firstLine + i];
			font->SetPosX(static_cast<float>(0x140 - maxWidth / 2));
			font->SetPosY(static_cast<float>(static_cast<int>(y)));
			CMes::drawTagString(font, reinterpret_cast<char*>(msgId), 1, 0, 0);
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

	font->SetPosX(FLOAT_8033357c);
	int detailY = static_cast<int>(lineStep + static_cast<float>(static_cast<int>(baseY)));
	font->SetPosY(static_cast<float>(detailY));

		if ((*reinterpret_cast<u16*>(itemBase + 4) & 0x1000) != 0) {
			unsigned int attr = *reinterpret_cast<u16*>(itemBase + 8);
			if ((attr >= 1) && (attr <= 0x13)) {
				strcpy(scratch, GetAttrStr(attr));
				font->SetTlut(4);
				font->Draw(scratch);
				int valueX = static_cast<int>(FLOAT_8033357c + (FLOAT_803335a0 + font->GetWidth(scratch)));
				font->SetPosX(static_cast<float>(valueX));
				font->SetTlut(9);

				if ((attr >= 1) && (attr <= 8)) {
					sprintf(scratch, sMenuUtilStringFormat, sMenuUtilPlusOneText);
				} else {
					if ((attr == 0xB) || (attr == 0x11) || (attr == 0x12)) {
						sprintf(scratch, sMenuUtilSignedValueFormat, 0x2B, *reinterpret_cast<u16*>(itemBase + 6));
					} else {
						if (((attr - 9) > 1) && (attr != 0xC)) {
							return;
						}
						sprintf(scratch, sMenuUtilSignedValueFormat, 0x2D, *reinterpret_cast<u16*>(itemBase + 6));
						font->SetTlut(3);
					}
				}

				font->Draw(scratch);
			}
		} else {
			strcat(scratch, sMenuUtilSpaceText);
			font->Draw(scratch);

			int valueX = static_cast<int>(FLOAT_8033357c + (FLOAT_803335a0 + font->GetWidth(scratch)));
			font->SetTlut(1);
			font->SetPosX(static_cast<float>(valueX));
			sprintf(scratch, sMenuUtilValueSuffixFormat, *reinterpret_cast<u16*>(itemBase + 6));
			font->Draw(scratch);

			if ((*reinterpret_cast<short*>(self + 0x864) == 2) &&
			    (*reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x82C) + 0x30) == 1)) {
				int menuState = *reinterpret_cast<int*>(self + 0x82C);
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

					currentItem = *reinterpret_cast<short*>(
					    foodBase +
					    static_cast<int>(*reinterpret_cast<short*>(foodBase + currentItem * 2 + 0xAC)) * 2 +
					    0xB6);

					if (static_cast<unsigned char>(ChkEquipActive(static_cast<int>(*reinterpret_cast<short*>(menuState + 0x28)) +
					                                              static_cast<int>(*reinterpret_cast<short*>(menuState + 0x34)))) != 0) {
						unsigned int currentValue = 0;
						if (currentItem != -1) {
							currentValue = *reinterpret_cast<u16*>(Game.unkCFlatData0[2] + currentItem * 0x48 + 6);
						}

						int delta = static_cast<int>(*reinterpret_cast<u16*>(itemBase + 6)) - static_cast<int>(currentValue);
						int deltaX = static_cast<int>(static_cast<float>(valueX) + (FLOAT_803335a0 + font->GetWidth(scratch)));
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

			int attrX = static_cast<int>(font->posX + font->GetWidth(sMenuUtilSpaceText));
			font->SetPosX(static_cast<float>(attrX));

			unsigned int attr = *reinterpret_cast<u16*>(itemBase + 8);
			if ((attr >= 1) && (attr <= 0x13)) {
				font->SetTlut(4);
				strcpy(scratch, GetAttrStr(attr));
				font->Draw(scratch);
				font->SetTlut(9);
				if ((attr >= 1) && (attr <= 8)) {
					sprintf(scratch, sMenuUtilAttrBonusFormat, sMenuUtilPlusOneText);
					font->Draw(scratch);
				}
			}
		}
		} else {
		int lineCount = 3;
		int firstNonEmptyLine = firstLine;
		stage = *reinterpret_cast<CMemory::CStage**>(menuPcsGlobal + 0xEC);
		if (Game.m_gameWork.m_menuStageMode != 0) {
			stage = *reinterpret_cast<CMemory::CStage**>(menuPcsGlobal + 0xF4);
		}

		temp = new (stage, s_MenuUtil_cpp_801e37fc, 0x23D) char[0x200];
		if ((temp == nullptr) && (System.m_execParam != 0)) {
			System.Printf(s_MenuUtil_cpp_801e37fc + 0x10, s_MenuUtil_cpp_801e37fc, 0x23F);
		}
		for (int i = 0; i < 3; i++) {
			int msgId = GetMenuHelpMsgTable()[firstLine + i];
			memset(temp, 0, 0x200);
			CMes::MakeAgbString(temp, reinterpret_cast<char*>(msgId), 0, 1);
			if (strlen(temp) == 0) {
				lineCount--;
				if (firstNonEmptyLine == firstLine + i) {
					firstNonEmptyLine++;
				}
			}
		}
		delete[] temp;

		int y = lineBaseY[lineCount + drawPrefix - 1];
		if (drawPrefix != 0) {
			font->SetPosX(FLOAT_8033357c);
			font->SetPosY(static_cast<float>(static_cast<int>(y)));
			font->Draw(itemName);
			font->Draw(suffix);
			y = static_cast<int>(static_cast<float>(static_cast<int>(y)) + lineStep);
		}

		for (int i = 0; i < lineCount; i++) {
			int msgId = GetMenuHelpMsgTable()[firstNonEmptyLine + i];
			font->SetPosX(static_cast<float>(0x140 - maxWidth / 2));
			font->SetPosY(static_cast<float>(static_cast<int>(y)));
			CMes::drawTagString(font, reinterpret_cast<char*>(msgId), 1, 0, 0);
			y = static_cast<int>(static_cast<float>(static_cast<int>(y)) + lineStep);
		}
	}
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
 * PAL Address: 0x80179e9c
 * PAL Size: 244b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetCrystalCageAttr()
{
	struct CrystalState {
		unsigned char _pad0[0x80];
		unsigned char m_effectTimer;
		unsigned char _pad1[3];
		int m_crystalElem;
		short m_crystalPart;
		short m_crystalAttr;
	};

	CrystalState* state = reinterpret_cast<CrystalState*>(this);

	if (state->m_crystalPart != -1) {
		PartMng.pppDeletePart(state->m_crystalPart);
	}

	unsigned int chaliceElement = Game.m_gameWork.m_chaliceElement;
	if ((chaliceElement & 1U) != 0) {
		state->m_crystalAttr = 0xE;
		state->m_crystalElem = 1;
	} else if ((chaliceElement & 2U) != 0) {
		state->m_crystalAttr = 0xF;
		state->m_crystalElem = 2;
	} else if ((chaliceElement & 4U) != 0) {
		state->m_crystalAttr = 0x10;
		state->m_crystalElem = 4;
	} else if ((chaliceElement & 8U) != 0) {
		state->m_crystalAttr = 0x11;
		state->m_crystalElem = 8;
	} else if ((chaliceElement & 0x10U) != 0) {
		state->m_crystalAttr = 0x12;
		state->m_crystalElem = 0x10;
	}

	state->m_crystalPart = BindEffect(5, state->m_crystalAttr, -1);
	state->m_effectTimer = 0;
}

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
	unsigned char* const self = reinterpret_cast<unsigned char*>(this);
	int partNo = *reinterpret_cast<int*>(*reinterpret_cast<int*>(self + 0x840) + 0x19B8);

	if (partNo != -1) {
		PartMng.pppDeletePart(partNo);
	}

	BindEffect(5, Game.m_gameWork.m_timerA + 0x13, -1);
	*reinterpret_cast<int*>(self + 0x70) = Game.m_gameWork.m_timerA;
}

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
	unsigned char* const self = reinterpret_cast<unsigned char*>(this);
	signed char& gameInitMode = *reinterpret_cast<signed char*>(self + 0x8F);
	signed char& stereoMode = *reinterpret_cast<signed char*>(self + 0x90);
	signed char& bgmVolume = *reinterpret_cast<signed char*>(self + 0x91);
	signed char& seVolume = *reinterpret_cast<signed char*>(self + 0x92);

	gameInitMode =
	    static_cast<signed char>(static_cast<unsigned int>(__cntlzw(static_cast<unsigned int>(Game.m_gameWork.m_gameInitFlag))) >> 5);

	unsigned int soundMode = GetRedSoundGlobal()->GetSoundMode();
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
	unsigned char* const self = reinterpret_cast<unsigned char*>(this);
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
		if (static_cast<int>(m_optionOpenAnim / kOptionOpenAnimStep) == 5) {
			Sound.PlaySe(0x32, 0x40, 0x7F, 0);
		}
		if (!(m_optionOpenAnim <= kOptionAnimMin)) {
			return;
		}

		*reinterpret_cast<unsigned short*>(*reinterpret_cast<int*>(self + 0x82C) + 0x20) = 1;
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
		m_optionRowAnim = kOptionAnimMin;
		m_optionColumnAnim = kOptionAnimMin;
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
		m_optionRowAnim = kOptionAnimMin;
		m_optionColumnAnim = kOptionAnimMin;
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
		unsigned short press3;
		press3 = GetMenuPress();

		if ((press3 & 0x100) != 0) {
			if (m_specialModeEdit == 0) {
				m_specialModeCursor = 0;
				m_specialModeEdit = 1;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
			}
		} else if (m_specialModeEdit != 0) {
			unsigned short press4;
			press4 = GetMenuPress();

			if ((press4 & 0x200) != 0) {
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
	}

	if (optionChanged) {
		Game.m_gameWork.m_gameInitFlag =
		    static_cast<unsigned char>(static_cast<unsigned int>(__cntlzw(static_cast<int>(m_gameInitMode))) >> 5);
		Sound.SetStereo(static_cast<unsigned int>(__cntlzw(static_cast<int>(m_stereoMode))) >> 5);
		Sound.SetSeMasterVolume(static_cast<int>(kOptionVolumeScale * static_cast<float>(m_seVolume)));
		Sound.SetBgmMasterVolume(static_cast<int>(kOptionVolumeScale * static_cast<float>(m_bgmVolume)));
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawOptionMenu()
{
	CFont* font = menuFont;
	int languageBase = (Game.m_gameWork.m_languageId - 1) * 20;
	_GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
	Vec2d uv0;
	Vec2d uv1;

	char* optionText[5] = {
	    g_strMenuUtilMes[languageBase + 2],
	    g_strMenuUtilMes[languageBase + 3],
	    g_strMenuUtilMes[languageBase + 4],
	    g_strMenuUtilMes[languageBase + 5],
	    g_strMenuUtilMes[languageBase + 6],
	};
	char* helpText[5] = {
	    g_strMenuUtilMes[languageBase + 7],
	    g_strMenuUtilMes[languageBase + 8],
	    g_strMenuUtilMes[languageBase + 9],
	    g_strMenuUtilMes[languageBase + 10],
	    g_strMenuUtilMes[languageBase + 11],
	};
	color.a = static_cast<unsigned char>(static_cast<int>(FLOAT_80333550 * m_optionOpenAnim));

	font->SetScale(FLOAT_80333548);
	font->SetMargin(kOptionAnimMin);

	CTexture* banner = GetMenuTexture(this, 0xD4);
	float bannerHeight = static_cast<float>(banner->m_height);
	gUtil.CalcUV(uv0.x, uv0.y, 0, 0, banner->m_width, banner->m_height);
	gUtil.CalcUV(uv1.x, uv1.y, 0x280, banner->m_height, banner->m_width, banner->m_height);
	gUtil.RenderTextureQuad(kOptionAnimMin,
	                        -(bannerHeight * kMenuCenteringHalfWidth - FLOAT_80333554) - FLOAT_8033355C,
	                        FLOAT_80333560, bannerHeight, banner, &uv0, &uv1, &color, GX_BL_SRCALPHA,
	                        GX_BL_INVSRCALPHA);

	CTexture* panel = GetMenuTexture(this, 0xE8);
	float panelWidth = static_cast<float>(panel->m_width);
	float panelHeight = static_cast<float>(panel->m_height);
	float panelRight = FLOAT_80333564 + panelWidth;
	float panelBottom = FLOAT_80333568 + panelHeight;
	gUtil.RenderTextureQuad(FLOAT_80333564, FLOAT_80333568, panelWidth, panelHeight, panel, 0, 0, &color,
	                        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
	uv0.x = kOptionAnimMin;
	uv0.y = kOptionAnimMax;
	uv1.x = kOptionAnimMax;
	uv1.y = kOptionAnimMin;
	gUtil.RenderTextureQuad(FLOAT_80333564, panelBottom, panelWidth, panelHeight, panel, &uv0, &uv1, &color,
	                        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
	uv0.x = kOptionAnimMax;
	uv0.y = kOptionAnimMin;
	uv1.x = kOptionAnimMin;
	uv1.y = kOptionAnimMax;
	gUtil.RenderTextureQuad(panelRight, FLOAT_80333568, panelWidth, panelHeight, panel, &uv0, &uv1, &color,
	                        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
	uv0.x = kOptionAnimMax;
	uv0.y = kOptionAnimMax;
	uv1.x = kOptionAnimMin;
	uv1.y = kOptionAnimMin;
	gUtil.RenderTextureQuad(panelRight, panelBottom, panelWidth, panelHeight, panel, &uv0, &uv1, &color,
	                        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

	CTexture* cursor = GetMenuTexture(this, 0x18C);
	gUtil.CalcUV(uv0.x, uv0.y, 0, 0, cursor->m_width, cursor->m_height);
	gUtil.CalcUV(uv1.x, uv1.y, 0x20, 0x20, cursor->m_width, cursor->m_height);
	gUtil.RenderTextureQuad(static_cast<float>((System.m_frameCounter & 7) + 0x1C),
	                        static_cast<float>(m_optionIndex * 0x28 + 0x70), FLOAT_80333570,
	                        FLOAT_80333570, cursor, &uv0, &uv1, &color, GX_BL_SRCALPHA,
	                        GX_BL_INVSRCALPHA);

	CTexture* marker = GetMenuTexture(this, 0xC8);
	gUtil.RenderTextureQuad(FLOAT_80333574, static_cast<float>(m_optionIndex * 0x28 + 0x70),
	                        static_cast<float>(marker->m_width), static_cast<float>(marker->m_height), marker, 0, 0,
	                        &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

	font->SetScaleX(FLOAT_80333578);
	char** option = optionText;
	int rowY = 0x70;
	unsigned int selectedY = 0x73;
	unsigned int normalY = 0x75;
	for (int i = 0; i < 5; i++, rowY += 0x28, selectedY += 0x28, normalY += 0x28, option++) {
		CTexture* row = GetMenuTexture(this, 0xC0);
		uv0.x = (i == m_optionIndex) ? kOptionAnimMin : kMenuCenteringHalfWidth;
		uv0.y = kOptionAnimMin;
		uv1.x = (i == m_optionIndex) ? kMenuCenteringHalfWidth : kOptionAnimMax;
		uv1.y = kOptionAnimMax;
		gUtil.RenderTextureQuad(FLOAT_8033357c, static_cast<float>(rowY),
		                        static_cast<float>(row->m_width) * kMenuCenteringHalfWidth,
		                        static_cast<float>(row->m_height), row, &uv0, &uv1, &color, GX_BL_SRCALPHA,
		                        GX_BL_INVSRCALPHA);

		if (i == m_optionIndex) {
			DrawFont(0x5E, static_cast<int>(FLOAT_80333580 + static_cast<float>(selectedY)), color, 0x16,
			         *option, kOptionAnimMax, kOptionAnimMax);
		} else {
			DrawFont(0x60, static_cast<int>(FLOAT_80333580 + static_cast<float>(normalY)), color, 6,
			         *option, kOptionAnimMax, kOptionAnimMax);
		}
	}

	font->SetScaleX(kOptionAnimMax);
	gUtil.RenderTextureQuad(kOptionAnimMin, FLOAT_80333584, FLOAT_80333560, FLOAT_80333588,
	                        GetMenuTexture(this, 0x208), 0, 0, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

	font->SetShadow(1);
	font->SetMargin(kOptionAnimMax);
	font->SetScaleX(FLOAT_80333578);
	font->SetScaleY(kOptionAnimMax);
	char* help = helpText[m_optionIndex];
	DrawFont2(static_cast<int>(-(font->GetWidth(help) * kMenuCenteringHalfWidth -
	                            kMenuCenteringOffset)),
	          static_cast<int>(FLOAT_80333590), color, 7, help, FLOAT_80333578,
	          kOptionAnimMax, kOptionAnimMax);

	if (m_optionIndex <= 1) {
		CTextureSet* textureSet = GetMenuTextureSet(this, 0xBC);
		CTexture* sideTexture = GetTextureSetTexture(textureSet, 1);
		CTexture* selectorTexture = GetTextureSetTexture(textureSet, 4);
		int secondValue = (m_optionIndex == 0) ? (m_gameInitMode != 0) : (m_stereoMode != 0);
		char* firstText = g_strMenuUtilMes[languageBase + ((m_optionIndex == 0) ? 12 : 14)];
		char* secondText = g_strMenuUtilMes[languageBase + ((m_optionIndex == 0) ? 13 : 15)];
		float leftX = 328.0f;
		float rightX = (m_optionIndex == 0) ? 544.0f : 552.0f;
		float selectorX = (m_optionIndex == 0) ? 368.0f : 360.0f;
		float secondOffset = (m_optionIndex == 0) ? 96.0f : 112.0f;

		SetUv(uv0, kOptionAnimMin, kOptionAnimMin);
		SetUv(uv1, kMenuCenteringHalfWidth, kOptionAnimMax);
		gUtil.RenderTextureQuad(leftX, 172.0f, static_cast<float>(sideTexture->m_width) * kMenuCenteringHalfWidth,
		                        static_cast<float>(sideTexture->m_height), sideTexture, &uv0, &uv1, &color,
		                        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
		SetUv(uv0, kMenuCenteringHalfWidth, kOptionAnimMin);
		SetUv(uv1, kOptionAnimMax, kOptionAnimMax);
		gUtil.RenderTextureQuad(rightX, 186.0f, static_cast<float>(sideTexture->m_width) * kMenuCenteringHalfWidth,
		                        static_cast<float>(sideTexture->m_height), sideTexture, &uv0, &uv1, &color,
		                        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		color.a = static_cast<unsigned char>(static_cast<int>(FLOAT_80333550 * m_optionColumnAnim));
		gUtil.CalcUV(uv0.x, uv0.y, 0, 0, selectorTexture->m_width, selectorTexture->m_height);
		gUtil.CalcUV(uv1.x, uv1.y, 0x78, 0x30, selectorTexture->m_width, selectorTexture->m_height);
		gUtil.RenderTextureQuad(selectorX + (secondValue ? secondOffset : kOptionAnimMin), 176.0f,
		                        FLOAT_803335B0, FLOAT_803335B4, selectorTexture, &uv0, &uv1, &color,
		                        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		float firstScale = secondValue ? 0.8f : 1.46f;
		float secondScale = secondValue ? 1.46f : 0.8f;
		float firstY = secondValue ? 185.0f : 183.0f;
		float secondY = secondValue ? 183.0f : 185.0f;
		int firstTlut = secondValue ? 6 : 0x17;
		int secondTlut = secondValue ? 0x17 : 6;

		font->SetScale(firstScale);
		DrawFont2(static_cast<int>(selectorX + (FLOAT_803335B0 - font->GetWidth(firstText)) * kMenuCenteringHalfWidth),
		          static_cast<int>(firstY), color, firstTlut, firstText, firstScale, kOptionAnimMax,
		          kOptionAnimMax);
		font->SetScale(secondScale);
		DrawFont2(static_cast<int>(selectorX + secondOffset + (FLOAT_803335B0 - font->GetWidth(secondText)) *
		                                                  kMenuCenteringHalfWidth),
		          static_cast<int>(secondY), color, secondTlut, secondText, secondScale, kOptionAnimMax,
		          kOptionAnimMax);
	} else if (m_optionIndex < 4) {
		CTexture* meterTexture = GetTextureSetTexture(GetMenuTextureSet(this, 0xBC), 3);
		signed char volume = (m_optionIndex <= 2) ? m_bgmVolume : m_seVolume;
		unsigned long iconLeftU = (m_optionIndex <= 2) ? 0 : 0x18;
		unsigned long iconRightU = (m_optionIndex <= 2) ? 0 : 0x28;
		unsigned long leftArrowY = (m_optionIndex <= 2) ? 0x58 : 0x40;
		unsigned long rightArrowY = (m_optionIndex <= 2) ? 0x5C : 0x3C;
		unsigned long barU = (m_optionIndex <= 2) ? 0x40 : 0x30;

		gUtil.CalcUV(uv0.x, uv0.y, iconLeftU, 0x28, meterTexture->m_width, meterTexture->m_height);
		gUtil.CalcUV(uv1.x, uv1.y, iconLeftU + 0x18, 0x40, meterTexture->m_width, meterTexture->m_height);
		gUtil.RenderTextureQuad(348.0f, 192.0f, FLOAT_8033361C, FLOAT_8033361C, meterTexture, &uv0, &uv1,
		                        &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		gUtil.CalcUV(uv0.x, uv0.y, iconRightU, 0, meterTexture->m_width, meterTexture->m_height);
		gUtil.CalcUV(uv1.x, uv1.y, iconRightU + 0x28, 0x28, meterTexture->m_width, meterTexture->m_height);
		gUtil.RenderTextureQuad(556.0f, 184.0f, FLOAT_80333588, FLOAT_80333588, meterTexture, &uv0, &uv1,
		                        &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		color.a = static_cast<unsigned char>(static_cast<int>(FLOAT_80333550 * m_optionColumnAnim));
		if (m_leftHintTimer == 0) {
			gUtil.CalcUV(uv0.x, uv0.y, 0, leftArrowY, meterTexture->m_width, meterTexture->m_height);
			gUtil.CalcUV(uv1.x, uv1.y, 0x10, leftArrowY + 0x18, meterTexture->m_width, meterTexture->m_height);
		} else {
			gUtil.CalcUV(uv0.x, uv0.y, 0x18, leftArrowY, meterTexture->m_width, meterTexture->m_height);
			gUtil.CalcUV(uv1.x, uv1.y, 0x28, leftArrowY + 0x18, meterTexture->m_width, meterTexture->m_height);
		}
		gUtil.RenderTextureQuad(FLOAT_80333564, FLOAT_80333608, FLOAT_80333624, FLOAT_8033361C, meterTexture, &uv0,
		                        &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		if (m_rightHintTimer == 0) {
			gUtil.CalcUV(uv0.x, uv0.y, 0x48, rightArrowY, meterTexture->m_width, meterTexture->m_height);
			gUtil.CalcUV(uv1.x, uv1.y, 0x30, rightArrowY + 0x20, meterTexture->m_width, meterTexture->m_height);
		} else {
			gUtil.CalcUV(uv0.x, uv0.y, 0x60, rightArrowY, meterTexture->m_width, meterTexture->m_height);
			gUtil.CalcUV(uv1.x, uv1.y, 0x48, rightArrowY + 0x20, meterTexture->m_width, meterTexture->m_height);
		}
		gUtil.RenderTextureQuad(FLOAT_8033360C, FLOAT_80333608, FLOAT_8033361C, FLOAT_80333570, meterTexture, &uv0,
		                        &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		gUtil.CalcUV(uv0.x, uv0.y, barU, 0x28, meterTexture->m_width, meterTexture->m_height);
		gUtil.CalcUV(uv1.x, uv1.y, barU + 0x10, 0x38, meterTexture->m_width, meterTexture->m_height);
		for (int i = 0, x = 0; i < 12; i++, x += 0x10) {
			float barX = FLOAT_80333610 + static_cast<float>(x);
			gUtil.RenderTextureQuad(barX, FLOAT_80333614, FLOAT_80333624, FLOAT_80333624, meterTexture, &uv0,
			                        &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
			if ((m_optionMenuState != 2) && (i < volume)) {
				gUtil.RenderTextureQuad(barX, FLOAT_80333614, FLOAT_80333624, FLOAT_80333624, meterTexture, &uv0,
				                        &uv1, &color, GX_BL_ONE, GX_BL_ONE);
			}
		}

		char* maxText = g_strMenuUtilMes[languageBase + 17];
		DrawFont(static_cast<int>(FLOAT_80333614), static_cast<int>(FLOAT_80333618), color, 7,
		         g_strMenuUtilMes[languageBase + 16], kOptionAnimMax, kOptionAnimMax);
		float maxX = FLOAT_80333628 - font->GetWidth(maxText);
		DrawFont(static_cast<int>(maxX), static_cast<int>(FLOAT_80333618), color, 7, maxText, kOptionAnimMax,
		         kOptionAnimMax);
	} else if (m_optionIndex == 4) {
		CTextureSet* textureSet = GetMenuTextureSet(this, 0xBC);
		CTexture* cursorPanel = GetTextureSetTexture(textureSet, 4);
		CTexture* modePanel = GetTextureSetTexture(textureSet, 7);
		color.a = static_cast<unsigned char>(static_cast<int>(FLOAT_80333550 * m_optionColumnAnim));

		int y = 0;
		unsigned int uvY = 0;
		unsigned int modeU = 0x280;
		for (int i = 0; i < 4; i++, y += 0x28, uvY += 0x20, modeU += 0x40) {
			if ((m_specialModeEdit != 0) && (m_specialModeCursor == i)) {
				gUtil.CalcUV(uv0.x, uv0.y, cursorPanel->m_width - 0x30, 0, cursorPanel->m_width,
				             cursorPanel->m_height);
				gUtil.CalcUV(uv1.x, uv1.y, cursorPanel->m_width, 0x28, cursorPanel->m_width,
				             cursorPanel->m_height);
				gUtil.RenderTextureQuad(326.0f, 128.0f + static_cast<float>(y), 48.0f, FLOAT_80333588,
				                        cursorPanel, &uv0, &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

				gUtil.CalcUV(uv0.x, uv0.y, 0, 0x30, cursorPanel->m_width, cursorPanel->m_height);
				gUtil.CalcUV(uv1.x, uv1.y, cursorPanel->m_width, cursorPanel->m_height, cursorPanel->m_width,
				             cursorPanel->m_height);
				gUtil.RenderTextureQuad(300.0f, 160.0f + static_cast<float>(y),
				                        static_cast<float>(cursorPanel->m_width), FLOAT_80333624, cursorPanel,
				                        &uv0, &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
			}

			gUtil.CalcUV(uv0.x, uv0.y, modePanel->m_width - 0x30, uvY, modePanel->m_width, modePanel->m_height);
			gUtil.CalcUV(uv1.x, uv1.y, modePanel->m_width, uvY + 0x18, modePanel->m_width, modePanel->m_height);
			gUtil.RenderTextureQuad(330.0f, 138.0f + static_cast<float>(y), FLOAT_80333588, FLOAT_8033361C,
			                        modePanel, &uv0, &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

			char* modeText = g_strMenuUtilMes[languageBase + 18];
			float textPanelX = 492.0f;
			float textY = 132.0f;
			float textPanelWidth = 112.0f;
			if (m_specialModeFlags[i] == 0) {
				modeText = g_strMenuUtilMes[languageBase + 19];
				textPanelX = 372.0f;
				textY = 136.0f;
				textPanelWidth = 120.0f;
				gUtil.CalcUV(uv0.x, uv0.y, 0, uvY, modePanel->m_width, modePanel->m_height);
				gUtil.CalcUV(uv1.x, uv1.y, 0x78, uvY + 0x20, modePanel->m_width, modePanel->m_height);
			} else {
				gUtil.CalcUV(uv0.x, uv0.y, 0x78, uvY, modePanel->m_width, modePanel->m_height);
				gUtil.CalcUV(uv1.x, uv1.y, 0xE0, uvY + 0x20, modePanel->m_width, modePanel->m_height);
			}

			gUtil.RenderTextureQuad(textPanelX, textY + static_cast<float>(y), textPanelWidth, FLOAT_80333570,
			                        modePanel, &uv0, &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
			DrawFont(static_cast<int>(textPanelX + (textPanelWidth - font->GetWidth(modeText)) *
			                                         kMenuCenteringHalfWidth),
			         static_cast<int>(textY + FLOAT_80333580 + FLOAT_80333634 + static_cast<float>(y)), color, 7,
			         modeText, kOptionAnimMax, kOptionAnimMax);
		}
	}
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
	unsigned char* const self = reinterpret_cast<unsigned char*>(this);

	for (int slot = 0; slot < 4; slot++) {
		if (slotNo == slot) {
			int* obj = reinterpret_cast<int*>(
				*reinterpret_cast<unsigned char**>(self + 0x840) + (slot + 0x11) * 0x524);

			if (obj[1] >= 0) {
				PartMng.pppDeletePart(obj[1]);
				obj[1] = -1;
				obj[2] = -1;
				obj[0] = -1;
			}

			if (obj[0x525] >= 0) {
				PartMng.pppDeletePart(obj[0x525]);
				obj[0x525] = -1;
				obj[0x526] = -1;
				obj[0x524] = -1;
			}
		}
	}

	for (int slot = 0, entryOffset = 0; slot < 4; slot++, entryOffset += 0x48) {
		if (slotNo == slot) {
			unsigned char* entry = *reinterpret_cast<unsigned char**>(self + 0x838) + entryOffset;
			int iconType = *reinterpret_cast<int*>(entry + 0xC);

			if (iconType != 0) {
				BindEffect(slot + 0x11, iconType + 0x16, -1);
			}

			unsigned int flags = *reinterpret_cast<unsigned int*>(entry + 0x28);

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

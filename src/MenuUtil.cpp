#include "ffcc/MenuUtil.h"
#include "ffcc/partMng.h"
#include "ffcc/game.h"
#include "ffcc/memory.h"
#include "ffcc/mes.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include "ffcc/RedSound/RedSound.h"
#include <string.h>
#include "ffcc/fontman.h"
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

extern "C" char* strcat(char*, const char*);
extern "C" int toupper(int);
extern "C" char s_MenuUtil_cpp_801e37fc[];
extern u32 DAT_801e36d0;
extern u32 DAT_801e36d4;
extern u32 DAT_801e36d8;
extern u32 DAT_801e36dc;
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
extern "C" const float kOptionOpenAnimStep = 0.04f;
extern "C" const float kOptionColumnAnimStep = 0.2f;
extern "C" const float kOptionVolumeScale = 10.583333f;
extern "C" const float FLOAT_80333654 = 25.0f;
extern float FLOAT_8033357c;
extern float FLOAT_803335a0;
extern const char s_MenuUtilEmptyText_80333658[4] = "";
extern const char s_MenuUtilStringFormat_8033365c[] = "%s";
extern const char s_MenuUtilPlusOneText_80333660[] = "+1";
extern const char s_MenuUtilSignedValueFormat_80333664[] = "%c%d";
extern const char s_MenuUtilSpaceText_8033366c[] = " ";
extern const char s_MenuUtilValueSuffixFormat_80333670[] = " %d";
extern const char s_MenuUtilSignedDeltaFormat_80333674[] = " %+d";
extern const char s_MenuUtilAttrBonusFormat_8033367C[] = " %s";
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

	int padIndex = activeInput;
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
	u32 lineBaseY[4];
	lineBaseY[0] = DAT_801e36d0;
	lineBaseY[1] = DAT_801e36d4;
	lineBaseY[2] = DAT_801e36d8;
	lineBaseY[3] = DAT_801e36dc;

	int languageIndex = (Game.m_gameWork.m_languageId - 1) * 20;
	int drawPrefix = 1;
	int firstLine = 500;
	int maxWidth = -1;
	float lineStep = FLOAT_80333654;
	const char* suffix = 0;
	char itemName[260];
	char scratch[0x100];
	itemName[0] = '\0';

	font->SetMargin(margin);
	font->SetShadow(1);
	font->SetScale(scale);
	font->DrawInit();
	font->SetTlut(tlut);
	font->SetColor(color);
	font->SetScale(kOptionAnimMax);

	if ((0 <= msgNo) && (msgNo < 0x269)) {
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
	for (int i = 0; i < 3; i++) {
		int msgId = GetMenuHelpMsgTable()[firstLine + i];
		memset(temp, 0, 0x200);
		CMes::MakeAgbString(temp, reinterpret_cast<char*>(msgId), 0, 1);
		if (strlen(temp) != 0) {
			int width = static_cast<int>(CMes::drawTagString(font, reinterpret_cast<char*>(msgId), 0, 0, 0));
			if (width > maxWidth) {
				maxWidth = width;
			}
		}
	}
	delete[] temp;

	if ((msgNo < 0x259) || (0x268 < msgNo)) {
		if (msgNo == 0x209) {
			suffix = GetSkillStr(0);
		} else if (msgNo == 0x20D) {
			suffix = GetSkillStr(1);
		} else if (msgNo == 0x211) {
			suffix = GetSkillStr(2);
		} else {
			suffix = s_MenuUtilEmptyText_80333658;
		}

		if ((msgNo == 0x209) || (msgNo == 0x20D) || (msgNo == 0x211)) {
			itemName[0] = '\0';
		} else {
			Game.MakeArtItemName(itemName, msgNo, 1);
			if ((strlen(itemName) != 0) && (itemName[0] != '\0')) {
				itemName[0] = static_cast<char>(toupper(static_cast<unsigned char>(itemName[0])));
			}
		}
		lineStep = FLOAT_80333620;
	} else {
		drawPrefix = 0;
	}

	int rangeKind = 0;
	if ((1 <= msgNo) && (msgNo <= 0x44)) {
		rangeKind = 1;
	} else if ((0x45 <= msgNo) && (msgNo <= 0x7E)) {
		rangeKind = 0x45;
	} else if ((0x7F <= msgNo) && (msgNo <= 0x9E)) {
		rangeKind = 0x7F;
	}

	if (rangeKind == 0) {
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

		u32 y = lineBaseY[lineCount + drawPrefix - 1];
		if (drawPrefix != 0) {
			font->SetPosX(FLOAT_8033357c);
			font->SetPosY(static_cast<float>(y));
			font->Draw(itemName);
			font->Draw(suffix);
			y = static_cast<u32>(static_cast<float>(y) + lineStep);
		}

		for (int i = 0; i < lineCount; i++) {
			int msgId = GetMenuHelpMsgTable()[firstNonEmptyLine + i];
			font->SetPosX(static_cast<float>(0x140 - maxWidth / 2));
			font->SetPosY(static_cast<float>(y));
			CMes::drawTagString(font, reinterpret_cast<char*>(msgId), 1, 0, 0);
			y = static_cast<u32>(static_cast<float>(y) + lineStep);
		}
		return;
	}

	u32 y = lineBaseY[drawPrefix + 2];
	if (drawPrefix != 0) {
		font->SetPosX(FLOAT_8033357c);
		font->SetPosY(static_cast<float>(y));
		font->Draw(itemName);
		font->Draw(suffix);
		y = static_cast<u32>(static_cast<float>(y) + lineStep);
	}

	for (int i = 0; i < 3; i++) {
		int msgId = GetMenuHelpMsgTable()[firstLine + i];
		font->SetPosX(static_cast<float>(0x140 - maxWidth / 2));
		font->SetPosY(static_cast<float>(y));
		CMes::drawTagString(font, reinterpret_cast<char*>(msgId), 1, 0, 0);
		y = static_cast<u32>(static_cast<float>(y) + lineStep);
	}

	int itemBase = Game.unkCFlatData0[2] + msgNo * 0x48;
	u16 flags = *reinterpret_cast<u16*>(itemBase + 4);
	if ((flags & 0x100) != 0) {
		strcpy(scratch, PTR_s_Strength__80215a48[languageIndex]);
	} else if ((flags & 0x200) != 0) {
		strcpy(scratch, PTR_s_Defence__80215a4c[languageIndex]);
	} else if ((flags & 0x400) != 0) {
		strcpy(scratch, PTR_s_Defence__80215a4c[languageIndex]);
	} else if ((flags & 0x800) != 0) {
		strcpy(scratch, PTR_s_Defence__80215a4c[languageIndex]);
	} else if ((flags & 0x1000) != 0) {
		strcpy(scratch, s_MenuUtilEmptyText_80333658);
	} else if ((flags & 0x2000) != 0) {
		strcpy(scratch, s_MenuUtilEmptyText_80333658);
	}

	font->SetPosX(FLOAT_8033357c);
	font->SetPosY(static_cast<float>(y));

	if ((flags & 0x1000) == 0) {
		strcat(scratch, s_MenuUtilSpaceText_8033366c);
		font->Draw(scratch);

		float valueX = FLOAT_8033357c + font->GetWidth(scratch) + FLOAT_803335a0;
		font->SetTlut(1);
		font->SetPosX(valueX);
		sprintf(scratch, s_MenuUtilValueSuffixFormat_80333670, *reinterpret_cast<u16*>(itemBase + 6));
		font->Draw(scratch);

		if ((*reinterpret_cast<short*>(self + 0x864) == 2) &&
		    (*reinterpret_cast<short*>(*reinterpret_cast<int*>(self + 0x82C) + 0x30) == 1)) {
			int currentItem = -1;
			int menuState = *reinterpret_cast<int*>(self + 0x82C);
			u16 effectFlags = *reinterpret_cast<u16*>(itemBase + 4);

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

			currentItem = static_cast<int>(*reinterpret_cast<short*>(
			    Game.m_scriptFoodBase[0] +
			    static_cast<int>(*reinterpret_cast<short*>(Game.m_scriptFoodBase[0] + currentItem * 2 + 0xAC)) * 2 +
			    0xB6));

			if (ChkEquipActive(static_cast<int>(*reinterpret_cast<short*>(menuState + 0x28)) +
			                   static_cast<int>(*reinterpret_cast<short*>(menuState + 0x34))) != 0) {
				u16 currentValue = 0;
				if (currentItem != -1) {
					currentValue = *reinterpret_cast<u16*>(Game.unkCFlatData0[2] + currentItem * 0x48 + 6);
				}

				int delta = static_cast<int>(*reinterpret_cast<u16*>(itemBase + 6)) - static_cast<int>(currentValue);
				float deltaX = valueX + font->GetWidth(scratch) + FLOAT_803335a0;
				font->SetPosX(deltaX);
				if (delta < 0) {
					font->SetTlut(3);
				} else {
					font->SetTlut(9);
				}
				sprintf(scratch, s_MenuUtilSignedDeltaFormat_80333674, delta);
				if (delta != 0) {
					font->Draw(scratch);
				}
			}
		}

		float attrX = font->posX + font->GetWidth(s_MenuUtilSpaceText_8033366c);
		font->SetPosX(attrX);

		u16 attr = *reinterpret_cast<u16*>(itemBase + 8);
		if (((flags & 0x1000) == 0) && (attr != 0) && (attr < 0x14)) {
			font->SetTlut(4);
			strcpy(scratch, GetAttrStr(attr));
			font->Draw(scratch);
			font->SetTlut(9);
			if ((attr != 0) && (attr < 9)) {
				sprintf(scratch, s_MenuUtilAttrBonusFormat_8033367C, s_MenuUtilPlusOneText_80333660);
				font->Draw(scratch);
			}
		}
	} else {
		u16 attr = *reinterpret_cast<u16*>(itemBase + 8);
		if ((attr != 0) && (attr < 0x14)) {
			strcpy(scratch, GetAttrStr(attr));
			font->SetTlut(4);
			font->Draw(scratch);
			font->SetPosX(FLOAT_803335a0 + font->GetWidth(scratch));
			font->SetTlut(9);

			if ((attr == 0) || (8 < attr)) {
				if ((attr == 0xB) || (attr == 0x11) || (attr == 0x12)) {
					sprintf(scratch, s_MenuUtilSignedValueFormat_80333664, 0x2B, *reinterpret_cast<u16*>(itemBase + 6));
				} else {
					if (((attr - 9) > 1) && (attr != 0xC)) {
						return;
					}
					sprintf(scratch, s_MenuUtilSignedValueFormat_80333664, 0x2D, *reinterpret_cast<u16*>(itemBase + 6));
					font->SetTlut(3);
				}
			} else {
				sprintf(scratch, s_MenuUtilStringFormat_8033365c, s_MenuUtilPlusOneText_80333660);
			}

			font->Draw(scratch);
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

	int value = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&Sound) + 0x22B0);
	bgmVolume = static_cast<signed char>(value / 10);

	value = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&Sound) + 0x22B4);
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
	unsigned short press;
	bool optionChanged = false;

	press = GetMenuPress();

	signed char& menuState = *reinterpret_cast<signed char*>(self + 0x9C);
	float& openAnim = *reinterpret_cast<float*>(self + 0x98);
	float& rowAnim = *reinterpret_cast<float*>(self + 0xA0);
	float& colAnim = *reinterpret_cast<float*>(self + 0xA8);
	signed char& animPhase = *reinterpret_cast<signed char*>(self + 0xA4);
	signed char& animCounter = *reinterpret_cast<signed char*>(self + 0xAC);
	signed char& optionIndex = *reinterpret_cast<signed char*>(self + 0x8E);
	signed char& gameInitMode = *reinterpret_cast<signed char*>(self + 0x8F);
	signed char& stereoMode = *reinterpret_cast<signed char*>(self + 0x90);
	signed char& bgmVolume = *reinterpret_cast<signed char*>(self + 0x91);
	signed char& seVolume = *reinterpret_cast<signed char*>(self + 0x92);
	signed char& leftHintTimer = *reinterpret_cast<signed char*>(self + 0x93);
	signed char& rightHintTimer = *reinterpret_cast<signed char*>(self + 0x94);
	int& specialModeEdit = *reinterpret_cast<int*>(self + 0xB0);
	signed char& specialModeCursor = *reinterpret_cast<signed char*>(self + 0xB4);

	if (menuState == 0) {
		openAnim += kOptionOpenAnimStep;
		if (!(openAnim >= kOptionAnimMax)) {
			return;
		}

		menuState = 1;
		openAnim = kOptionAnimMax;
		return;
	}

	if (menuState == 2) {
		openAnim -= kOptionOpenAnimStep;
		rowAnim -= kOptionRowAnimStep;
		colAnim -= kOptionColumnAnimStep;

		if (rowAnim <= kOptionAnimMin) {
			rowAnim = kOptionAnimMin;
		}
		if (colAnim <= kOptionAnimMin) {
			colAnim = kOptionAnimMin;
		}
		if (static_cast<int>(openAnim / kOptionOpenAnimStep) == 5) {
			Sound.PlaySe(0x32, 0x40, 0x7F, 0);
		}
		if (!(openAnim <= kOptionAnimMin)) {
			return;
		}

		*reinterpret_cast<unsigned short*>(*reinterpret_cast<int*>(self + 0x82C) + 0x20) = 1;
		optionIndex = 0;
		menuState = 0;
		openAnim = kOptionAnimMin;
		rowAnim = kOptionAnimMin;
		colAnim = kOptionAnimMin;
		animCounter = 0;
		animPhase = 0;
		return;
	}

	if (menuState == 3) {
		return;
	}

	if (animPhase == 0) {
		rowAnim += kOptionRowAnimStep;
		animCounter++;
		if (rowAnim >= kOptionAnimMax) {
			animPhase = 1;
			rowAnim = kOptionAnimMax;
		}
	} else if (animPhase == 1) {
		colAnim += kOptionColumnAnimStep;
		if (colAnim >= kOptionAnimMax) {
			animPhase = 2;
			colAnim = kOptionAnimMax;
		}
	}

	if (leftHintTimer > 0) {
		leftHintTimer--;
	}
	if (rightHintTimer > 0) {
		rightHintTimer--;
	}

	if ((specialModeEdit == 0) && ((press & 8) != 0)) {
		leftHintTimer = 0;
		rightHintTimer = 0;
		optionIndex--;
		if (optionIndex < 0) {
			optionIndex = 4;
		}
		rowAnim = kOptionAnimMin;
		colAnim = kOptionAnimMin;
		animCounter = 0;
		animPhase = 0;
		Sound.PlaySe(1, 0x40, 0x7F, 0);
	} else if ((specialModeEdit == 0) && ((press & 4) != 0)) {
		leftHintTimer = 0;
		rightHintTimer = 0;
		optionIndex++;
		if (optionIndex > 4) {
			optionIndex = 0;
		}
		rowAnim = kOptionAnimMin;
		colAnim = kOptionAnimMin;
		animCounter = 0;
		animPhase = 0;
		Sound.PlaySe(1, 0x40, 0x7F, 0);
	}

	if (specialModeEdit == 0) {
		unsigned short press2;
		press2 = GetMenuPress();

		if ((press2 & 0x200) != 0) {
			menuState = 2;
			Sound.PlaySe(3, 0x40, 0x7F, 0);
			return;
		}
	}

	if ((animPhase == 0) || (animPhase == 1)) {
		return;
	}

	if ((press & 1) != 0) {
		if (optionIndex == 2) {
			leftHintTimer = 3;
			rightHintTimer = 0;
			bgmVolume--;
			if (bgmVolume < 0) {
				bgmVolume = 0;
			}
		} else if (optionIndex < 2) {
			if (optionIndex == 0) {
				gameInitMode--;
				if (gameInitMode < 0) {
					gameInitMode = 1;
				}
			} else if (optionIndex == 1) {
				stereoMode--;
				if (stereoMode < 0) {
					stereoMode = 1;
				}
			}
		} else if (optionIndex == 4) {
			if (specialModeEdit != 0) {
				m_specialModeFlags[static_cast<signed char>(specialModeCursor)]--;
				if (m_specialModeFlags[static_cast<signed char>(specialModeCursor)] < 0) {
					m_specialModeFlags[static_cast<signed char>(specialModeCursor)] = 1;
				}
			}
		} else if (optionIndex == 3) {
			leftHintTimer = 3;
			rightHintTimer = 0;
			seVolume--;
			if (seVolume < 0) {
				seVolume = 0;
			}
		}

		Sound.PlaySe(1, 0x40, 0x7F, 0);
		optionChanged = true;
	} else if ((press & 2) != 0) {
		if (optionIndex == 2) {
			rightHintTimer = 3;
			leftHintTimer = 0;
			bgmVolume++;
			if (bgmVolume > 0xC) {
				bgmVolume = 0xC;
			}
		} else if (optionIndex < 2) {
			if (optionIndex == 0) {
				gameInitMode++;
				if (gameInitMode > 1) {
					gameInitMode = 0;
				}
			} else if (optionIndex == 1) {
				stereoMode++;
				if (stereoMode > 1) {
					stereoMode = 0;
				}
			}
		} else if (optionIndex == 4) {
			if (specialModeEdit != 0) {
				m_specialModeFlags[static_cast<signed char>(specialModeCursor)]++;
				if (m_specialModeFlags[static_cast<signed char>(specialModeCursor)] > 1) {
					m_specialModeFlags[static_cast<signed char>(specialModeCursor)] = 0;
				}
			}
		} else if (optionIndex == 3) {
			rightHintTimer = 3;
			leftHintTimer = 0;
			seVolume++;
			if (seVolume > 0xC) {
				seVolume = 0xC;
			}
		}

		Sound.PlaySe(1, 0x40, 0x7F, 0);
		optionChanged = true;
	}

	if (optionIndex == 4) {
		unsigned short press3;
		press3 = GetMenuPress();

		if ((press3 & 0x100) != 0) {
			if (specialModeEdit == 0) {
				specialModeCursor = 0;
				specialModeEdit = 1;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
			}
		} else if (specialModeEdit != 0) {
			unsigned short press4;
			press4 = GetMenuPress();

			if ((press4 & 0x200) != 0) {
				specialModeCursor = 0;
				specialModeEdit = 0;
				Sound.PlaySe(3, 0x40, 0x7F, 0);

				Game.m_gameWork.m_spModeFlags[0] =
				    static_cast<unsigned char>(static_cast<unsigned int>(__cntlzw(1 - m_specialModeFlags[0])) >> 5);
				Game.m_gameWork.m_spModeFlags[1] =
				    static_cast<unsigned char>(static_cast<unsigned int>(__cntlzw(1 - m_specialModeFlags[1])) >> 5);
				Game.m_gameWork.m_spModeFlags[2] =
				    static_cast<unsigned char>(static_cast<unsigned int>(__cntlzw(1 - m_specialModeFlags[2])) >> 5);
				Game.m_gameWork.m_spModeFlags[3] =
				    static_cast<unsigned char>(static_cast<unsigned int>(__cntlzw(1 - m_specialModeFlags[3])) >> 5);
			} else if ((press & 8) != 0) {
				specialModeCursor--;
				if (specialModeCursor < 0) {
					specialModeCursor = 3;
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			} else if ((press & 4) != 0) {
				specialModeCursor++;
				if (specialModeCursor > 3) {
					specialModeCursor = 0;
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			}
		}
	}

	if (optionChanged) {
		Game.m_gameWork.m_gameInitFlag =
		    static_cast<unsigned char>(static_cast<unsigned int>(__cntlzw(static_cast<int>(gameInitMode))) >> 5);
		Sound.SetStereo(static_cast<unsigned int>(__cntlzw(static_cast<int>(stereoMode))) >> 5);
		Sound.SetSeMasterVolume(static_cast<int>(kOptionVolumeScale * static_cast<float>(seVolume)));
		Sound.SetBgmMasterVolume(static_cast<int>(kOptionVolumeScale * static_cast<float>(bgmVolume)));
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawOptionMenu()
{
	// TODO
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

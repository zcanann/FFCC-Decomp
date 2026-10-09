#include "ffcc/MenuUtil.h"
#include "ffcc/partMng.h"
#include "ffcc/game.h"
#include "ffcc/gobjwork.h"
#include "ffcc/itemobj.h"
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

// Disc-path constants for the dead-stripped CGame::SetGbaSP method.
static const char s_dvd_gba_801E3058[] = "dvd/gba/";
static const char s_ffcc_cli_bin_801E3060[] = "ffcc_cli.bin";
static const char s_objdat_spt_801E3070[] = "objdat.spt";
#ifdef VERSION_GCCJGC
static const char s_icon_dat_801E307C[] = "dvd/menu/icon.dat";
static const char s_FF_Crystal_Chronicles_801E3088[] =
	"\314\247\262\305\331\314\247\335\300\274\336\260\245\270\330\275\300\331\270\333\306\270\331";
#else
static const char s_icon_dat_801E307C[] = "icon.dat";
static const char s_FF_Crystal_Chronicles_801E3088[] = "FF Crystal Chronicles";
#endif

#ifndef VERSION_GCCJGC
char* g_strMenuUtilMes[] = {
#ifdef VERSION_GCCE01
	"Strength",
	"Defense",
	"Position Markers",
	"Sound Mode",
	"Music",
	"Sound Effects",
	"GBA Color Balance",
	"Show or hide position marker under each character's feet.",
	"Select stereo or monaural sound.",
	"Adjust volume of background music.",
	"Adjust volume of sound effects.",
	"Adjust color balance of Game Boy Advance.",
	"On",
	"Off",
	"Stereo",
	"Monaural",
	"Min",
	"Max",
	"Enhanced",
	"Standard",

	"St\344rke",
	"Abwehr",
	"Erkennungskreisel",
	"Tonausgabe",
	"Musik",
	"Ger\344uscheffekte",
	"Farbeinstellung",
	"Erkennungskreisel des Charakters AN/AUS schalten.",
	"Tonausgabe auf Stereo oder Mono schalten.",
	"Lautst\344rke der Musik \344ndern.",
	"Lautst\344rke der Ger\344uscheffekte \344ndern.",
	"Farbeinstellung des GBA \344ndern.",
	"AN",
	"AUS",
	"STEREO",
	"MONO",
	"Min",
	"Max",
	"Erweitert",
	"Normal",

	"Forza",
	"Difesa",
	"Indicatori di posizione",
	"Sonoro",
	"Musica",
	"Effetti sonori",
	"Bilanc. colore GBA",
	"Attiva o disattiva l'indicatore ai piedi dei personaggi.",
	"Scelta tra sonoro mono o stereo.",
	"Regola il volume della musica",
	"Regola il volume degli effetti sonori",
	"Regola il colore del Game Boy Advance.",
	"On",
	"Off",
	"Stereo",
	"Mono",
	"Min",
	"Max",
	"Contr.",
	"Norm.",

	"Force",
	"R\351sistance",
	"Sceau de position",
	"Signal sonore",
	"Musique",
	"Effets sonores",
	"Affichage du GBA",
	"Affichage du sceau de position aux pieds des personnages",
	"Choisissez le signal sonore st\351r\351o ou mono",
	"R\351glez le volume de la musique",
	"R\351glez le volume des effets sonores",
	"R\351glez le contraste des couleurs du Game Boy Advance",
	"Activ\351",
	"D\351sactiv\351",
	"St\351r\351o",
	"Mono",
	"Min",
	"Max",
	"Am\351lior\351",
	"Standard",

	"Fuerza",
	"Defensa",
	"Indicadores de posici\363n",
	"Se\361al de sonido",
	"M\372sica",
	"Efectos de sonido",
	"Ajuste del color del GBA",
	"Mostrar o esconder el indicador de posici\363n bajo los pies de cada personaje.",
	"Seleccionar sonido est\351reo o monoaural.",
	"Ajustar el volumen de la m\372sica de fondo.",
	"Ajustar el volumen de los efectos de sonido.",
	"Ajustar el balance de color del Game Boy Advance.",
	"Desactivado",
	"Activado",
	"Est\351reo",
	"Monoaural",
	"Min.",
	"M\341x.",
	"Mejorado",
	"Est\341ndar",
#else
	"Strength:",
	"Defence:",
	"Position Markers",
	"Sound Mode",
	"Music",
	"Sound Effects",
	"GBA Colour Balance",
	"Show or hide position marker under each character's feet.",
	"Select stereo or monaural sound.",
	"Adjust volume of background music.",
	"Adjust volume of sound effects.",
	"Adjust colour balance of Game Boy Advance.",
	"On",
	"Off",
	"Stereo",
	"Monaural",
	"Min",
	"Max",
	"Enhanced",
	"Standard",

	"St\344rke",
	"Abwehr",
	"Erkennungskreisel",
	"Tonausgabe",
	"Musik",
	"Ger\344uscheffekte",
	"Farbeinstellung",
	"Erkennungskreisel des Charakters AN/AUS schalten.",
	"Tonausgabe auf Stereo oder Mono schalten.",
	"Lautst\344rke der Musik \344ndern.",
	"Lautst\344rke der Ger\344uscheffekte \344ndern.",
	"Farbeinstellung des Game Boy Advance \344ndern.",
	"AN",
	"AUS",
	"STEREO",
	"MONO",
	"Min",
	"Max",
	"Erweitert",
	"Normal",

	"Forza",
	"Difesa",
	"Indicatori di posizione",
	"Sonoro",
	"Musica",
	"Effetti sonori",
	"Bilanc. colore GBA",
	"Attiva o disattiva l'indicatore ai piedi dei personaggi.",
	"Scegli tra sonoro mono o stereo.",
	"Regola il volume della musica",
	"Regola il volume degli effetti sonori",
	"Regola il colore sul Game Boy Advance.",
	"On",
	"Off",
	"Stereo",
	"Mono",
	"Min",
	"Max",
	"Contr.",
	"Norm.",

	"Force",
	"R\351sistance",
	"Sceau de position",
	"Signal sonore",
	"Musique",
	"Effets sonores",
	"Affichage du GBA",
	"Affichage du sceau de position aux pieds des personnages",
	"Choisissez le signal sonore st\351r\351o ou mono",
	"R\351glez le volume de la musique",
	"R\351glez le volume des effets sonores",
	"R\351glez le contraste des couleurs du Game Boy Advance",
	"Activ\351",
	"D\351sactiv\351",
	"St\351r\351o",
	"Mono",
	"Min",
	"Max",
	"Am\351lior\351",
	"Standard",

	"Fuerza",
	"Defensa",
	"Aro de posici\363n",
	"Tipo de sonido",
	"M\372sica",
	"Efectos de sonido",
	"Color de la GBA",
	"Se\361ala la posici\363n bajo los pies de cada personaje.",
	"Selecciona sonido est\351reo o monoaural.",
	"Ajusta el volumen de la m\372sica de fondo.",
	"Ajusta el volumen de los efectos de sonido.",
	"Ajusta el balance del color de la Game Boy Advance.",
	"Encendido",
	"Apagado",
	"Est\351reo",
	"Monoaural",
	"M\355n.",
	"M\341x.",
	"Mejorado",
	"Est\341ndar",
#endif
};
#endif


namespace {
static inline void SetUv(Vec2d& uv, float u, float v)
{
	uv.x = u;
	uv.y = v;
}

static inline int GetOptionHelpX(char* text, CFont* font)
{
	font->SetShadow(1);
	font->SetMargin(1.0f);
	font->SetScaleX(0.8f);
	font->SetScaleY(1.0f);
	return static_cast<int>(-(font->GetWidth(text) / 2.0f - 320.0f));
}
}

struct MenuOptionChoiceLayout {
	Vec2d leftIcon;
	Vec2d rightIcon;
	Vec2d selector;
	Vec2d leftText;
	Vec2d rightText;
};
struct MenuOptionMeterLayout {
	Vec2d leftIcon;
	Vec2d rightIcon;
	Vec2d leftArrow;
	Vec2d rightArrow;
	Vec2d bar;
	Vec2d minLabel;
	Vec2d maxLabel;
};

#define OPT_MES(n) g_strMenuUtilMes[langRow * 20 + (n)]

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 64b
 * EN Address: 0x80199d18
 * EN Size: 64b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CalcHelpLine(int msgNo, int& firstLine, int& lineMax)
{
	firstLine = 500;
	if ((0 <= msgNo) && (msgNo <= 0x268)) {
		firstLine = msgNo * 3 + 0x1F5;
		lineMax = 3;
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 348b
 * EN Address: 0x80199d58
 * EN Size: 376b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::GetLongHelpString(CFont* font, int firstLine, int lineMax)
{
	int maxWidth = -1;
	CMemory::CStage* stage;
	if (Game.m_gameWork.m_menuStageMode != 0) {
		stage = MenuPcs.m_stageF4;
	} else {
		stage = MenuPcs.m_menuStage;
	}

	char* temp = new (stage, "MenuUtil.cpp", 0x8C) char[0x200];
	if ((temp == nullptr) && (static_cast<unsigned int>(System.m_execParam) >= 1)) {
		System.Printf("%s(%d): Error: memory allocation error\n", "MenuUtil.cpp", 0x8E);
	}
	for (int line = firstLine; line < firstLine + lineMax; line++) {
		char* msg = Game.GetHelpName(line);
		memset(temp, 0, 0x200);
#ifdef VERSION_GCCJGC
		CMes::MakeAgbString(temp, msg);
#else
		CMes::MakeAgbString(temp, msg, 0, 1);
#endif
		if (strlen(temp) != 0) {
			int width = static_cast<int>(CMes::GetTagStringWidth(font, msg));
			if (width < maxWidth) {
				width = maxWidth;
			}
			maxWidth = width;
		}
	}
	delete[] temp;
	return maxWidth;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 124b
 * EN Address: UNUSED
 * EN Size: 152b
 * JP Address: 0x80175A20
 * JP Size: 112b
 */
#ifdef VERSION_GCCJGC
float CMenuPcs::CalcCenteringPos(char* text, int fontSize)
{
	int length = strlen(text);
	CFont* font = m_fonts[0];
	float halfWidth = 0.5f;
	float offset = 320.0f;
	font->SetMargin(1.0f);
	font->SetScale(1.0f);
	float width = font->GetWidth(text);
	return offset - width * halfWidth;
}
#else
/*
 * --INFO--
 * PAL Address: 0x8017AE70
 * PAL Size: 164b
 * EN Address: 0x80179DC0
 * EN Size: 164b
 * JP Address: UNUSED
 * JP Size: TODO
 */
float CMenuPcs::CalcCenteringPos2(char* text, float scale, float margin)
{
	CFont* font = m_fonts[0];
	float width;
	float scaleY = 1.0f;
	float halfWidth = 0.5f;
	float offset = 320.0f;

	font->SetShadow(1);
	font->SetMargin(margin);
	font->SetScaleX(scale);
	font->SetScaleY(scaleY);
	width = font->GetWidth(text);
	return offset - width * halfWidth;
}
#endif

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
float CMenuPcs::CalcCenteringPos(char* text, CFont* font)
{
    float halfWidth = 0.5f;
    float offset = 320.0f;
    float width = font->GetWidth(text);
    return offset - width * halfWidth;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
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

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 112b
 * EN Address: 0x8019a0dc
 * EN Size: 112b
 * JP Address: TODO
 * JP Size: TODO
 */
inline float CMenuPcs::GetFontWidth(char* text, float scale, float margin)
{
	CFont* font = m_fonts[0];

	font->SetMargin(margin);
	font->SetShadow(1);
	font->SetScale(scale);
	return font->GetWidth(text);
}

#ifndef VERSION_GCCJGC
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

/*
 * --INFO--
 * PAL Address: 0x80179FC4
 * PAL Size: 3196b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawHelpMessageUS(int msgNo, CFont* font, int, int, _GXColor color, int tlut, float margin, float scale)
{
	const CCaravanWork* const caravanWork = Game.m_scriptFoodBase[0];
	u32 lineBaseY[4] = { 0x160, 0x14E, 0x142, 0x13E };

	int languageIndex = Game.m_gameWork.m_languageId - 1;
	int drawPrefix = 1;
	float lineStep = 25.0f;
	const char* suffix = 0;
	char itemName[260];
	char scratch[0x100];

	font->SetMargin(2.0f);
	font->SetShadow(1);
	font->SetScale(margin);
	font->DrawInit();
	font->SetTlut(tlut);
	font->SetColor(color);
	font->SetScale(0.88f);

	int firstLine;
	int lineMax;
	CalcHelpLine(msgNo, firstLine, lineMax);
	int maxWidth = GetLongHelpString(font, firstLine, lineMax);

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
			suffix = "";
		}

		if ((msgNo == 0x209) || (msgNo == 0x20D) || (msgNo == 0x211)) {
			itemName[0] = '\0';
		} else {
			Game.MakeArtItemName(itemName, msgNo, 1);
			if (strlen(itemName) != 0) {
				Game.UpperItemName(itemName);
			}
		}

		if (lineMax + drawPrefix == 4) {
			lineStep = 20.0f;
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
		int i;
		int baseIndex = drawPrefix + 2;
		u32 baseY = lineBaseY[baseIndex];
		int y = baseY;
		if (drawPrefix != 0) {
			font->SetPosX(56.0f);
			font->SetPosY(static_cast<float>(static_cast<int>(y)));
			font->Draw(itemName);
			font->Draw(suffix);
			y = static_cast<int>(static_cast<float>(static_cast<int>(y)) + lineStep);
		}

		for (i = 0; i < lineMax; i++) {
			char* msg = Game.GetHelpName(firstLine + i);
			font->SetPosX(static_cast<float>(0x140 - maxWidth / 2));
			font->SetPosY(static_cast<float>(static_cast<int>(y)));
			CMes::drawTagString(font, msg, 1, 0, 0);
			y = static_cast<int>(static_cast<float>(static_cast<int>(y)) + lineStep);
		}

	const SItemFlatRow* item = reinterpret_cast<const SItemFlatRow*>(Game.unkCFlatData0[2]) + msgNo;
	u16 flags = item->m_equipFlags;
	if ((flags & 0x100) != 0) {
		strcpy(scratch, g_strMenuUtilMes[languageIndex * 20]);
	} else if ((flags & 0x200) != 0) {
		strcpy(scratch, g_strMenuUtilMes[languageIndex * 20 + 1]);
	} else if ((flags & 0x400) != 0) {
		strcpy(scratch, g_strMenuUtilMes[languageIndex * 20 + 1]);
	} else if ((flags & 0x800) != 0) {
		strcpy(scratch, g_strMenuUtilMes[languageIndex * 20 + 1]);
	} else if ((flags & 0x1000) != 0) {
		strcpy(scratch, "");
	} else if ((flags & 0x2000) != 0) {
		strcpy(scratch, "");
	}

	int x = 0x38;
	font->SetPosX(56.0f);
	int detailY = static_cast<int>(lineStep + static_cast<float>(static_cast<int>(baseY)));
	font->SetPosY(static_cast<float>(detailY));

		if ((item->m_equipFlags & 0x1000) != 0) {
			if ((item->m_attribute < 1) || (item->m_attribute > 0x13)) {
				return;
			}

			strcpy(scratch, GetAttrStr(item->m_attribute));
			font->SetTlut(4);
			font->Draw(scratch);
			x += 2.0f + font->GetWidth(scratch);
			font->SetPosX(static_cast<float>(x));
			font->SetTlut(9);

			unsigned int attr = item->m_attribute;
			if ((attr >= 1) && (attr <= 8)) {
				sprintf(scratch, "%s", "+1");
			} else if ((attr == 0xB) || (attr == 0x11) || (attr == 0x12)) {
				sprintf(scratch, "%c%d", 0x2B, item->m_value);
			} else if ((static_cast<unsigned short>(attr - 9) <= 1) || (attr == 0xC)) {
				sprintf(scratch, "%c%d", 0x2D, item->m_value);
				font->SetTlut(3);
			} else {
				return;
			}

			font->Draw(scratch);
		} else {
			strcat(scratch, " ");
			font->Draw(scratch);

			x += 2.0f + font->GetWidth(scratch);
			font->SetTlut(1);
			font->SetPosX(static_cast<float>(x));
			sprintf(scratch, " %d", item->m_value);
#ifdef VERSION_GCCE01
			strcat(scratch, " ");
#endif
			font->Draw(scratch);

			if (m_battleStateFlag == 2) {
				int sel = m_artiState->currentSelection;
				if (sel == 1) {
					u16 effectFlags = item->m_equipFlags;

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

						int equipmentSlot = caravanWork->m_equipment[currentItem];
						currentItem = caravanWork->m_inventoryItems[equipmentSlot];

						if (ChkEquipActive(static_cast<int>(m_artiState->selections[sel]) +
						                   static_cast<int>(m_artiState->scrollOffset))) {
							const SItemFlatRow* current = reinterpret_cast<const SItemFlatRow*>(Game.unkCFlatData0[2]) + currentItem;
							unsigned int currentValue;
							if (currentItem == -1) {
								currentValue = 0;
							} else {
								currentValue = current->m_value;
							}

							int delta = static_cast<int>(item->m_value) - static_cast<int>(currentValue);
							x += 2.0f + font->GetWidth(scratch);
							font->SetPosX(static_cast<float>(x));
#ifdef VERSION_GCCE01
							if (delta >= 0) {
								font->SetTlut(9);
								sprintf(scratch, " %c%d ", '+', delta);
							} else {
								font->SetTlut(3);
								sprintf(scratch, " %d ", delta);
							}
							font->Draw(scratch);
#else
							if (delta >= 0) {
								font->SetTlut(9);
							} else {
								font->SetTlut(3);
							}
							sprintf(scratch, " %+d", delta);
							if (delta != 0) {
								font->Draw(scratch);
							}
#endif
						}
					}
				}
			}

#ifdef VERSION_GCCE01
			if ((item->m_equipFlags & 0x1000) == 0) {
				if ((item->m_attribute >= 1) && (item->m_attribute <= 0x13)) {
					x += 2.0f + font->GetWidth(scratch);
					font->SetPosX(static_cast<float>(x));
					font->SetTlut(4);
					strcpy(scratch, GetAttrStr(item->m_attribute));
					font->Draw(scratch);
					x += 2.0f + font->GetWidth(scratch);
					font->SetPosX(static_cast<float>(x));
					font->SetTlut(9);
					unsigned int attr = item->m_attribute;
					if ((attr >= 1) && (attr <= 8)) {
						sprintf(scratch, "%s", "+1");
					} else {
						return;
					}
					font->Draw(scratch);
				}
			}
#else
			float attrPosX = font->posX;
			int attrX = static_cast<int>(attrPosX + font->GetWidth(" "));
			font->SetPosX(static_cast<float>(attrX));

			if ((item->m_equipFlags & 0x1000) == 0) {
				if ((item->m_attribute >= 1) && (item->m_attribute <= 0x13)) {
					font->SetTlut(4);
					strcpy(scratch, GetAttrStr(item->m_attribute));
					font->Draw(scratch);
					font->SetTlut(9);
					unsigned int attr = item->m_attribute;
					if ((attr >= 1) && (attr <= 8)) {
						sprintf(scratch, " %s", "+1");
					} else {
						return;
					}
					font->Draw(scratch);
				}
			}
#endif
		}
		} else {
		char* temp;
		int firstNonEmptyLine = firstLine;
		int lineCount = 3;
#ifdef VERSION_GCCE01
		temp = new ((Game.m_gameWork.m_menuStageMode != 0) ? MenuPcs.m_stageF4 : MenuPcs.m_menuStage,
		            "MenuUtil.cpp", 0x231) char[0x200];
		if ((temp == nullptr) && (static_cast<unsigned int>(System.m_execParam) >= 1)) {
			System.Printf("%s(%d): Error: memory allocation error\n", "MenuUtil.cpp", 0x233);
		}
#else
		temp = new ((Game.m_gameWork.m_menuStageMode != 0) ? MenuPcs.m_stageF4 : MenuPcs.m_menuStage,
		            "MenuUtil.cpp", 0x23D) char[0x200];
		if ((temp == nullptr) && (static_cast<unsigned int>(System.m_execParam) >= 1)) {
			System.Printf("%s(%d): Error: memory allocation error\n", "MenuUtil.cpp", 0x23F);
		}
#endif
		for (int i = 0; i < lineMax; i++) {
			char* msg = Game.GetHelpName(firstLine + i);
			memset(temp, 0, 0x200);
#ifdef VERSION_GCCJGC
			CMes::MakeAgbString(temp, msg);
#else
			CMes::MakeAgbString(temp, msg, 0, 1);
#endif
			if (strlen(temp) == 0) {
				lineCount--;
				if (firstNonEmptyLine == firstLine + i) {
					firstNonEmptyLine++;
				}
			}
		}
		delete[] temp;

		int idx = lineCount - 1 + drawPrefix;
		int y = lineBaseY[idx];
		if (drawPrefix != 0) {
			font->SetPosX(56.0f);
			font->SetPosY(static_cast<float>(static_cast<int>(y)));
			font->Draw(itemName);
			font->Draw(suffix);
			y = static_cast<int>(static_cast<float>(y) + lineStep);
		}

		for (int i = 0; i < lineCount; i++) {
			char* msg = Game.GetHelpName(firstNonEmptyLine + i);
			font->SetPosX(static_cast<float>(0x140 - maxWidth / 2));
			font->SetPosY(static_cast<float>(static_cast<int>(y)));
			CMes::DrawTagString(font, msg);
			y = static_cast<int>(static_cast<float>(static_cast<int>(y)) + lineStep);
		}
	}
}
#endif

#ifdef VERSION_GCCJGC
#include "src/MenuUtil_jp.inc"
#else
/*
 * --INFO--
 * PAL Address: 0x80179F90
 * PAL Size: 52b
 * EN Address: 0x80178E30
 * EN Size: 52b
 * JP Address: 0x80174F08
 * JP Size: 2552b
 */
void CMenuPcs::DrawHelpMessage(int msgNo, CFont* font, int posX, int posY, _GXColor color, int tlut, float margin, float scaleY)
{
	int lineBaseY[3] = { 0x160, 0x154, 0x146 };

	if (msgNo >= 0) {
		DrawHelpMessageUS(msgNo, font, posX, posY, color, tlut, margin, scaleY);
	}
}

#endif

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

#ifdef VERSION_GCCP01
#define OPTION_OPEN_STEP 0.04f
#define OPTION_ROW_STEP 0.125f
#define OPTION_COLUMN_STEP 0.2f
#define OPTION_ROW_ANGLE_STEP 11.25f
#else
#define OPTION_OPEN_STEP (1.0f / 30.0f)
#define OPTION_ROW_STEP 0.1f
#define OPTION_COLUMN_STEP (1.0f / 6.0f)
#define OPTION_ROW_ANGLE_STEP 9.0f
#endif

/*
 * --INFO--
 * PAL Address: 0x80179d28
 * PAL Size: 256b
 * EN Address: 0x8019B444
 * EN Size: 284b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetOptionData()
{
	m_gameInitMode = Game.GetMark() == 0;
	m_stereoMode = !Sound.IsStereo();
	m_bgmVolume = Sound.GetBgmMasterVolume() / 10;
	m_seVolume = Sound.GetSeMasterVolume() / 10;

	for (int i = 0; i < 4; i++) {
		m_specialModeFlags[i] = Game.GetGbaSP(i) ? 1 : 0;
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
	unsigned short press;
	int optionChanged;
	press = Pad.GetButtonDown(0);
	optionChanged = 0;

	if (m_optionMenuState == 0) {
		m_optionOpenAnim += OPTION_OPEN_STEP;
		if (!(m_optionOpenAnim >= 1.0f)) {
			return;
		}

		m_optionMenuState = 1;
		m_optionOpenAnim = 1.0f;
		return;
	}

	if (m_optionMenuState == 2) {
		m_optionOpenAnim -= OPTION_OPEN_STEP;
		m_optionRowAnim -= OPTION_ROW_STEP;
		m_optionColumnAnim -= OPTION_COLUMN_STEP;

		if (m_optionRowAnim <= 0.0f) {
			m_optionRowAnim = 0.0f;
		}
		if (m_optionColumnAnim <= 0.0f) {
			m_optionColumnAnim = 0.0f;
		}
		{
			float divStep = OPTION_OPEN_STEP;
			if (static_cast<int>(m_optionOpenAnim / divStep) == 5) {
				Sound.PlaySe(0x32, 0x40, 0x7F, 0);
			}
		}
		if (!(m_optionOpenAnim <= 0.0f)) {
			return;
		}

		m_artiState->optionCloseReady = 1;
		m_optionIndex = 0;
		m_optionMenuState = 0;
		m_optionOpenAnim = 0.0f;
		m_optionRowAnim = 0.0f;
		m_optionColumnAnim = 0.0f;
		m_optionAnimCounter = 0;
		m_optionAnimPhase = 0;
		return;
	}

	if (m_optionMenuState == 3) {
		return;
	}

	if (m_optionAnimPhase == 0) {
		m_optionRowAnim += OPTION_ROW_STEP;
		m_optionAnimCounter++;
		if (m_optionRowAnim >= 1.0f) {
			m_optionAnimPhase = 1;
			m_optionRowAnim = 1.0f;
		}
	} else if (m_optionAnimPhase == 1) {
		m_optionColumnAnim += OPTION_COLUMN_STEP;
		if (m_optionColumnAnim >= 1.0f) {
			m_optionAnimPhase = 2;
			m_optionColumnAnim = 1.0f;
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
			float leftMin = 0.0f;
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
			float rightMin = 0.0f;
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
		press2 = Pad.GetButtonDown(0);

		if ((press2 & 0x200) != 0) {
			m_optionMenuState = 2;
			Sound.PlaySe(3, 0x40, 0x7F, 0);
			return;
		}
	}

	if (m_optionAnimPhase == 0 || m_optionAnimPhase == 1) {
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
		press3 = Pad.GetButtonDown(0);

		if ((press3 & 0x100) != 0) {
			if (m_specialModeEdit == 0) {
				m_specialModeCursor = 0;
				m_specialModeEdit = 1;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
			}
		} else if ((m_specialModeEdit != 0) && ((Pad.GetButtonDown(0) & 0x200) != 0)) {
			m_specialModeCursor = 0;
			m_specialModeEdit = 0;
			Sound.PlaySe(3, 0x40, 0x7F, 0);

			for (int i = 0; i < 4; i++) {
				Game.SetGbaSP(i, m_specialModeFlags[i] == 1);
			}
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
		Game.SetMark(m_gameInitMode == 0);
		Sound.SetStereo(static_cast<unsigned int>(__cntlzw(static_cast<int>(m_stereoMode))) >> 5);
		{
			float seScale = 10.583333f;
			Sound.SetSeMasterVolume(static_cast<int>(seScale * static_cast<float>(m_seVolume)));
		}
		{
			float bgmScale = 10.583333f;
			Sound.SetBgmMasterVolume(static_cast<int>(bgmScale * static_cast<float>(m_bgmVolume)));
		}
	}
}

#ifdef VERSION_GCCJGC
static inline void DrawOptionLabel(CFont* font, int x, int y, _GXColor color,
                                   int tlut, char* text, float scale)
{
	font->SetMargin(1.0f);
	font->SetShadow(1);
	font->SetScale(scale);
	font->DrawInit();
	font->SetTlut(tlut);
	font->SetColor(color);
	font->SetPosX(static_cast<float>(x));
	font->SetPosY(static_cast<float>(y));
	font->Draw(text);
}
#endif

/*
 * --INFO--
 * PAL Address: 0x8017698C
 * PAL Size: 10652b
 * EN Address: 0x80175908
 * EN Size: 10432b
 * JP Address: 0x80171684
 * JP Size: 11260b
 */
void CMenuPcs::DrawOptionMenu()
{
	CFont* font = m_fonts[0];
	int langRow = Game.m_gameWork.m_languageId - 1;
	float w;
	float h;
	int leftXi;
	int rightXi;
	_GXColor color;
	Vec2d uv0;
	Vec2d uv1;

#ifndef VERSION_GCCJGC
	font->SetScale(0.88f);
	font->SetMargin(0.0f);
#endif

	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = static_cast<unsigned char>(static_cast<int>(255.0f * m_optionOpenAnim));

#ifdef VERSION_GCCJGC
	char optionText[5][256] = {
		"\x83\x7C\x83\x57\x83\x56\x83\x87\x83\x93\x83\x7D\x81\x5B\x83\x4E",
		"\x83\x54\x83\x45\x83\x93\x83\x68\x8F\x6F\x97\xCD",
		"\x82\x61\x82\x66\x82\x6C\x83\x7B\x83\x8A\x83\x85\x81\x5B\x83\x80",
		"\x82\x72\x82\x64\x83\x7B\x83\x8A\x83\x85\x81\x5B\x83\x80",
		"\x82\x66\x82\x61\x82\x60\x83\x4A\x83\x89\x81\x5B\x83\x6F\x83\x89\x83\x93\x83\x58"
	};
	char helpText[5][256] = {
		"\x83\x76\x83\x8C\x83\x43\x83\x84\x81\x5B\x82\xCC\x91\xAB\x8C\xB3\x82\xC9\x8F\x6F\x82\xE9\x83\x7D\x81\x5B\x83\x4A\x81\x5B\x82\xCC\x82\x6E\x82\x6D\x81\x5E\x82\x6E\x82\x65\x82\x65\x82\xC5\x82\xB7",
		"\x83\x54\x83\x45\x83\x93\x83\x68\x82\xCC\x8F\x6F\x97\xCD\x82\xF0\x83\x58\x83\x65\x83\x8C\x83\x49\x82\xA9\x83\x82\x83\x6D\x83\x89\x83\x8B\x82\xC9\x82\xB5\x82\xDC\x82\xB7",
		"\x82\x61\x82\x66\x82\x6C\x82\xCC\x83\x7B\x83\x8A\x83\x85\x81\x5B\x83\x80\x82\xCC\x91\xE5\x82\xAB\x82\xB3\x82\xF0\x95\xCF\x8D\x58\x82\xB5\x82\xDC\x82\xB7",
		"\x8C\xF8\x89\xCA\x89\xB9\x82\xCC\x83\x7B\x83\x8A\x83\x85\x81\x5B\x83\x80\x82\xCC\x91\xE5\x82\xAB\x82\xB3\x82\xF0\x95\xCF\x8D\x58\x82\xB5\x82\xDC\x82\xB7",
		"\x82\x66\x82\x61\x82\x60\x82\xCC\x83\x4A\x83\x89\x81\x5B\x83\x6F\x83\x89\x83\x93\x83\x58\x82\xF0\x95\xCF\x8D\x58\x82\xB5\x82\xDC\x82\xB7"
	};
#else
	char* optionText[5] = { 0, 0, 0, 0, 0 };
	char** mes = &g_strMenuUtilMes[langRow * 20];
	int idx = 2;
	for (int n = 0; n < 5; n++) {
		optionText[n] = mes[idx++];
	}
	char* helpText[5] = { 0, 0, 0, 0, 0 };
	for (int n = 0; n < 5; n++) {
		helpText[n] = mes[idx++];
	}

#endif

	CTexture* banner = m_wmOptionTextures[5];
	w = static_cast<float>(banner->m_width);
	h = static_cast<float>(banner->m_height);
	gUtil.CalcUV(uv0.x, uv0.y, 0, 0, static_cast<unsigned int>(w), static_cast<unsigned int>(h));
	gUtil.CalcUV(uv1.x, uv1.y, 0x280, static_cast<unsigned int>(h),
	             static_cast<unsigned int>(w), static_cast<unsigned int>(h));
	gUtil.RenderTextureQuad(0.0f,
	                        224.0f - h / 2.0f - 14.0f,
	                        640.0f, h, m_wmOptionTextures[5], &uv0, &uv1, &color, GX_BL_SRCALPHA,
	                        GX_BL_INVSRCALPHA);

	CTexture* panel = m_wmOptionTextures[10];
	w = static_cast<float>(panel->m_width);
	h = static_cast<float>(panel->m_height);
	gUtil.RenderTextureQuad(336.0f, 88.0f, w, h, panel, 0, 0, &color,
	                        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
	uv0.x = 0.0f;
	uv0.y = 1.0f;
	uv1.x = 1.0f;
	uv1.y = 0.0f;
	gUtil.RenderTextureQuad(336.0f, 88.0f + h, w, h, m_wmOptionTextures[10], &uv0, &uv1, &color,
	                        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
	uv0.x = 1.0f;
	uv0.y = 0.0f;
	uv1.x = 0.0f;
	uv1.y = 1.0f;
	gUtil.RenderTextureQuad(336.0f + w, 88.0f, w, h, m_wmOptionTextures[10], &uv0, &uv1, &color,
	                        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
	uv0.x = 1.0f;
	uv0.y = 1.0f;
	uv1.x = 0.0f;
	uv1.y = 0.0f;
	gUtil.RenderTextureQuad(336.0f + w, 88.0f + h, w, h, m_wmOptionTextures[10], &uv0, &uv1, &color,
	                        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

	CTexture* cursor = m_textures[0];
	w = static_cast<float>(cursor->m_width);
	h = static_cast<float>(cursor->m_height);
	gUtil.CalcUV(uv0.x, uv0.y, 0, 0, static_cast<unsigned int>(w),
	             static_cast<unsigned int>(h));
	gUtil.CalcUV(uv1.x, uv1.y, 0x20, 0x20, static_cast<unsigned int>(w),
	             static_cast<unsigned int>(h));
	gUtil.RenderTextureQuad(static_cast<float>(static_cast<int>(System.m_frameCounter) % 8 + 0x1C),
	                        static_cast<float>(m_optionIndex * 0x28 + 0x70), 32.0f,
	                        32.0f, m_textures[0], &uv0, &uv1, &color, GX_BL_SRCALPHA,
	                        GX_BL_INVSRCALPHA);

	CTexture* marker = m_wmOptionTextures[2];
	w = static_cast<float>(marker->m_width);
	gUtil.RenderTextureQuad(64.0f, static_cast<float>(m_optionIndex * 0x28 + 0x70),
	                        w, static_cast<float>(marker->m_height), marker, 0, 0,
	                        &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

#ifdef VERSION_GCCJGC
	char (*option)[256] = optionText;
#else
	font->SetScaleX(0.8f);
	char** option = optionText;
#endif
	for (int i = 0; i < 5; i++) {
		CTexture* row = m_wmOptionTextures[0];
		w = static_cast<float>(row->m_width);
		h = static_cast<float>(row->m_height);
		uv0.x = (i == m_optionIndex) ? 0.0f : 0.5f;
		uv0.y = 0.0f;
		uv1.x = (i == m_optionIndex) ? 0.5f : 1.0f;
		uv1.y = 1.0f;
		gUtil.RenderTextureQuad(56.0f, static_cast<float>(i * 0x28 + 0x70),
		                        w / 2.0f, h, m_wmOptionTextures[0], &uv0,
		                        &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

#ifdef VERSION_GCCJGC
		if (i == m_optionIndex) {
			DrawOptionLabel(m_fonts[0], 94, i * 0x28 + 0x73, color, 0x16, option[i], 1.2f);
		} else {
			DrawOptionLabel(m_fonts[0], 96, i * 0x28 + 0x75, color, 6, option[i], 1.0f);
		}
#else
		if (i == m_optionIndex) {
			DrawFont(0x5E, static_cast<int>(-4.0f + static_cast<float>(i * 0x28 + 0x73)), color, 0x16,
			         option[i], 1.0f, 1.0f);
		} else {
			DrawFont(0x60, static_cast<int>(-4.0f + static_cast<float>(i * 0x28 + 0x75)), color, 6,
			         option[i], 1.0f, 1.0f);
		}
#endif
	}

#ifndef VERSION_GCCJGC
	font->SetScaleX(1.0f);
#endif
	gUtil.RenderTextureQuad(0.0f, 384.0f, 640.0f, 40.0f,
#ifdef VERSION_GCCJGC
	                        m_textures[30], 0, 0, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
#else
	                        m_textures[31], 0, 0, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
#endif

#ifdef VERSION_GCCJGC
	{
		char* help = helpText[m_optionIndex];
		strlen(help);
		CFont* helpFont = m_fonts[0];
		helpFont->SetMargin(1.0f);
		helpFont->SetScale(1.0f);
		float width = helpFont->GetWidth(help);
		DrawOptionLabel(m_fonts[0], static_cast<int>(320.0f - width * 0.5f),
		                391, color, 7, help, 1.0f);
	}
#else
	{
		float helpTextY = 387.0f;
		DrawFont2(GetOptionHelpX(helpText[m_optionIndex], m_fonts[0]),
		          static_cast<int>(helpTextY), color, 7, helpText[m_optionIndex], 0.8f,
		          1.0f, 1.0f);
	}

#endif

	int leftHintOn = 0;
	int rightHintOn = 0;
	if (m_leftHintTimer != 0) {
		leftHintOn = 1;
	}
	if (m_rightHintTimer != 0) {
		rightHintOn = 1;
	}

	color.a = static_cast<unsigned char>(static_cast<int>(255.0f * m_optionRowAnim));
	int rowAnimStep = static_cast<int>(m_optionRowAnim / OPTION_ROW_STEP);
	float rowAngle = static_cast<float>(rowAnimStep) * OPTION_ROW_ANGLE_STEP;
	float rowRad = 0.017453292f * rowAngle;
	rowAngle = 2.0f * rowAngle;
	float rowSin = static_cast<float>(sin(0.017453292f * rowAngle));
	float rowCos = static_cast<float>(cos(rowRad));

	switch (m_optionIndex) {
	case 0: {
#ifdef VERSION_GCCJGC
		MenuOptionChoiceLayout row = { { 328.0f, 172.0f }, { 544.0f, 186.0f }, { 368.0f, 176.0f }, { 400.0f, 189.0f }, { 496.0f, 189.0f } };
#else
		MenuOptionChoiceLayout row = { { 328.0f, 172.0f }, { 544.0f, 186.0f }, { 368.0f, 176.0f }, { 400.0f, 0.0f }, { 496.0f, 0.0f } };
#endif
		leftXi = static_cast<int>(472.0f - row.leftIcon.x);
		rightXi = static_cast<int>(w / 2.0f + row.rightIcon.x - 472.0f);
#ifndef VERSION_GCCJGC
		row.leftText.y = 185.0f;
		row.rightText.y = 185.0f;
#endif
		CTexture* sideTexture = m_wmOptionTextureSet->GetTexture(1);
		unsigned int sideWidth = sideTexture->m_width;
		unsigned int sideHeight = sideTexture->m_height;

		SetUv(uv0, 0.0f, 0.0f);
		SetUv(uv1, 0.5f, 1.0f);
		float sideW = static_cast<float>(sideWidth) / 2.0f;
		float sideH = static_cast<float>(sideHeight);
		gUtil.RenderTextureQuad(static_cast<float>(static_cast<int>(static_cast<float>(leftXi) * rowCos + row.leftIcon.x)),
		                        row.leftIcon.y, sideW, sideH, sideTexture, &uv0, &uv1, &color,
		                        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
		SetUv(uv0, 0.5f, 0.0f);
		SetUv(uv1, 1.0f, 1.0f);
		gUtil.RenderTextureQuad(static_cast<float>(static_cast<int>(-(static_cast<float>(rightXi) * rowCos - row.rightIcon.x))),
		                        row.rightIcon.y, sideW, sideH, sideTexture, &uv0, &uv1, &color,
		                        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		color.a = static_cast<unsigned char>(static_cast<int>(255.0f * m_optionColumnAnim));
		CTexture* selectorTexture = m_wmOptionTextureSet->GetTexture(4);
		unsigned int selectorHeight = static_cast<unsigned int>(static_cast<float>(selectorTexture->m_height));
		unsigned int selectorWidth = static_cast<unsigned int>(static_cast<float>(selectorTexture->m_width));
		gUtil.CalcUV(uv0.x, uv0.y, 0, 0, selectorWidth, selectorHeight);
		gUtil.CalcUV(uv1.x, uv1.y, 0x78, 0x30, selectorWidth, selectorHeight);
		gUtil.RenderTextureQuad((m_gameInitMode == 0) ? row.selector.x : 96.0f + row.selector.x, row.selector.y,
		                        120.0f, 48.0f, selectorTexture, &uv0, &uv1, &color,
		                        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

#ifdef VERSION_GCCJGC
		if (m_gameInitMode == 0) {
			DrawOptionLabel(m_fonts[0], static_cast<int>(row.leftText.x - 2.0f),
			                static_cast<int>(row.leftText.y - 2.0f), color, 0x17,
			                "\202\156\202\155", 1.2f);
			DrawOptionLabel(m_fonts[0], static_cast<int>(row.rightText.x),
			                static_cast<int>(row.rightText.y), color, 6,
			                "\202\156\202\145\202\145", 1.0f);
		} else {
			DrawOptionLabel(m_fonts[0], static_cast<int>(row.leftText.x),
			                static_cast<int>(row.leftText.y), color, 6,
			                "\202\156\202\155", 1.0f);
			DrawOptionLabel(m_fonts[0], static_cast<int>(row.rightText.x - 2.0f),
			                static_cast<int>(row.rightText.y - 2.0f), color, 0x17,
			                "\202\156\202\145\202\145", 1.2f);
		}
#else
		unsigned char isAlt = (langRow + 1 == 4) || (langRow + 1 == 5);
		float scale = isAlt ? 0.8 : 1.0;

		if (m_gameInitMode == 0) {
			{
				CFont* fnt = m_fonts[0];
				char* txt = OPT_MES(12);
				fnt->SetMargin(1.0f);
				fnt->SetShadow(1);
				float oneF = 1.0f;
				float firstScale = oneF * scale;
				fnt->SetScale(firstScale);
				float tw = fnt->GetWidth(txt);
				DrawFont2(static_cast<int>(static_cast<float>((120.0f - tw) *
				                           0.5 + 368.0)),
				          static_cast<int>(row.leftText.y - 2.0f), color, 0x17, txt, firstScale,
				          1.0f, 1.0f);
			}
			{
				CFont* fnt = m_fonts[0];
				char* txt = OPT_MES(13);
				fnt->SetMargin(1.0f);
				fnt->SetShadow(1);
				fnt->SetScale(scale);
				float tw = fnt->GetWidth(txt);
				DrawFont2(static_cast<int>(static_cast<float>((120.0f - tw) *
				                           0.5 + 464.0)),
				          static_cast<int>(row.rightText.y), color, 6, txt, scale, 1.0f,
				          1.0f);
			}
		} else {
			{
				CFont* fnt = m_fonts[0];
				char* txt = OPT_MES(12);
				fnt->SetMargin(1.0f);
				fnt->SetShadow(1);
				fnt->SetScale(scale);
				float tw = fnt->GetWidth(txt);
				DrawFont2(static_cast<int>(static_cast<float>((120.0f - tw) *
				                           0.5 + 368.0)),
				          static_cast<int>(row.leftText.y), color, 6, txt, scale, 1.0f,
				          1.0f);
			}
			{
				CFont* fnt = m_fonts[0];
				char* txt = OPT_MES(13);
				fnt->SetMargin(1.0f);
				fnt->SetShadow(1);
				float oneF = 1.0f;
				scale = oneF * scale;
				fnt->SetScale(scale);
				float tw = fnt->GetWidth(txt);
				DrawFont2(static_cast<int>(static_cast<float>((120.0f - tw) *
				                           0.5 + 464.0)),
				          static_cast<int>(row.rightText.y - 2.0f), color, 0x17, txt, scale,
				          1.0f, 1.0f);
			}
		}
#endif
		break;
	}
	case 1: {
#ifdef VERSION_GCCJGC
		MenuOptionChoiceLayout row = { { 328.0f, 172.0f }, { 552.0f, 186.0f }, { 360.0f, 176.0f }, { 376.0f, 189.0f }, { 488.0f, 189.0f } };
#else
		MenuOptionChoiceLayout row = { { 328.0f, 172.0f }, { 552.0f, 186.0f }, { 360.0f, 176.0f }, { 376.0f, 0.0f }, { 488.0f, 0.0f } };
#endif
		leftXi = static_cast<int>(472.0f - row.leftIcon.x);
		rightXi = static_cast<int>(w / 2.0f + row.rightIcon.x - 472.0f);
#ifndef VERSION_GCCJGC
		row.leftText.y = 185.0f;
		row.rightText.y = 185.0f;
#endif
		CTexture* sideTexture = m_wmOptionTextureSet->GetTexture(1);
		unsigned int sideWidth = sideTexture->m_width;
		unsigned int sideHeight = sideTexture->m_height;

		SetUv(uv0, 0.0f, 0.0f);
		SetUv(uv1, 0.5f, 1.0f);
		float sideW = static_cast<float>(sideWidth) / 2.0f;
		float sideH = static_cast<float>(sideHeight);
		gUtil.RenderTextureQuad(static_cast<float>(static_cast<int>(static_cast<float>(leftXi) * rowCos + row.leftIcon.x)),
		                        row.leftIcon.y, sideW, sideH, sideTexture, &uv0, &uv1, &color,
		                        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
		SetUv(uv0, 0.5f, 0.0f);
		SetUv(uv1, 1.0f, 1.0f);
		gUtil.RenderTextureQuad(static_cast<float>(static_cast<int>(-(static_cast<float>(rightXi) * rowCos - row.rightIcon.x))),
		                        row.rightIcon.y, sideW, sideH, sideTexture, &uv0, &uv1, &color,
		                        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		color.a = static_cast<unsigned char>(static_cast<int>(255.0f * m_optionColumnAnim));
		CTexture* selectorTexture = m_wmOptionTextureSet->GetTexture(4);
		unsigned int selectorHeight = static_cast<unsigned int>(static_cast<float>(selectorTexture->m_height));
		unsigned int selectorWidth = static_cast<unsigned int>(static_cast<float>(selectorTexture->m_width));
		gUtil.CalcUV(uv0.x, uv0.y, 0, 0, selectorWidth, selectorHeight);
		gUtil.CalcUV(uv1.x, uv1.y, 0x78, 0x30, selectorWidth, selectorHeight);
		gUtil.RenderTextureQuad((m_stereoMode == 0) ? row.selector.x : 112.0f + row.selector.x, row.selector.y,
		                        120.0f, 48.0f, selectorTexture, &uv0, &uv1, &color,
		                        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

#ifdef VERSION_GCCJGC
		if (m_stereoMode == 0) {
			DrawOptionLabel(m_fonts[0], static_cast<int>(row.leftText.x - 2.0f),
			                static_cast<int>(row.leftText.y - 2.0f), color, 0x17,
			                "\203\130\203\145\203\214\203\111", 1.2f);
			DrawOptionLabel(m_fonts[0], static_cast<int>(row.rightText.x),
			                static_cast<int>(row.rightText.y), color, 6,
			                "\203\202\203\155\203\211\203\213", 1.0f);
		} else {
			DrawOptionLabel(m_fonts[0], static_cast<int>(row.leftText.x),
			                static_cast<int>(row.leftText.y), color, 6,
			                "\203\130\203\145\203\214\203\111", 1.0f);
			DrawOptionLabel(m_fonts[0], static_cast<int>(row.rightText.x - 2.0f),
			                static_cast<int>(row.rightText.y - 2.0f), color, 0x17,
			                "\203\202\203\155\203\211\203\213", 1.2f);
		}
#else
		double stereoScale = 0.8;
		if (m_stereoMode == 0) {
			{
				CFont* fnt = m_fonts[0];
				char* txt = OPT_MES(14);
				fnt->SetMargin(1.0f);
				fnt->SetShadow(1);
				float oneF = 1.0f;
				fnt->SetScale(stereoScale * oneF);
				float tw = fnt->GetWidth(txt);
				DrawFont2(static_cast<int>(static_cast<float>((120.0f - tw) *
				                           0.5 + 360.0)),
				          static_cast<int>(row.leftText.y - 2.0f), color, 0x17, txt,
				          stereoScale * oneF, 1.0f, 1.0f);
			}
			{
				CFont* fnt = m_fonts[0];
				char* txt = OPT_MES(15);
				fnt->SetMargin(1.0f);
				fnt->SetShadow(1);
				fnt->SetScale(0.8f);
				float tw = fnt->GetWidth(txt);
				DrawFont2(static_cast<int>(static_cast<float>((120.0f - tw) *
				                           0.5 + 472.0)),
				          static_cast<int>(row.rightText.y), color, 6, txt, 0.8f, 1.0f,
				          1.0f);
			}
		} else {
			{
				CFont* fnt = m_fonts[0];
				char* txt = OPT_MES(14);
				fnt->SetMargin(1.0f);
				fnt->SetShadow(1);
				fnt->SetScale(0.8f);
				float tw = fnt->GetWidth(txt);
				DrawFont2(static_cast<int>(static_cast<float>((120.0f - tw) *
				                           0.5 + 360.0)),
				          static_cast<int>(row.leftText.y), color, 6, txt, 0.8f, 1.0f,
				          1.0f);
			}
			{
				CFont* fnt = m_fonts[0];
				char* txt = OPT_MES(15);
				fnt->SetMargin(1.0f);
				fnt->SetShadow(1);
				float oneF = 1.0f;
				fnt->SetScale(stereoScale * oneF);
				float tw = fnt->GetWidth(txt);
				DrawFont2(static_cast<int>(static_cast<float>((120.0f - tw) *
				                           0.5 + 472.0)),
				          static_cast<int>(row.rightText.y - 2.0f), color, 0x17, txt,
				          stereoScale * oneF, 1.0f, 1.0f);
			}
		}
#endif
		break;
	}
	case 2: {
		MenuOptionMeterLayout pos = { { 0.0f, 0.0f }, { 0.0f, 0.0f },
		                             { 0.0f, 0.0f }, { 0.0f, 0.0f },
		                             { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 508.0f, 0.0f } };
		pos.leftIcon.x = 348.0f;
		pos.leftIcon.y = 192.0f;
		pos.rightIcon.x = 556.0f;
		pos.rightIcon.y = 184.0f;
		pos.leftArrow.x = 336.0f;
		pos.leftArrow.y = 190.0f;
		pos.rightArrow.x = 587.0f;
		pos.rightArrow.y = 190.0f;
		pos.bar.x = 372.0f;
		pos.bar.y = 196.0f;
		pos.minLabel.x = 372.0f;
#ifdef VERSION_GCCJGC
		pos.minLabel.y = 172.0f;
		pos.maxLabel.y = 172.0f;
#else
		pos.minLabel.y = 168.0f;
		pos.maxLabel.y = 168.0f;
#endif
		CTexture* meterTexture = m_wmOptionTextureSet->GetTexture(3);
		leftXi = static_cast<int>(472.0f - pos.leftIcon.x);
		rightXi = static_cast<int>((24.0f + pos.rightIcon.x) - 472.0f);
		unsigned int meterHeight = static_cast<unsigned int>(static_cast<float>(meterTexture->m_height));
		unsigned int meterWidth = static_cast<unsigned int>(static_cast<float>(meterTexture->m_width));

		gUtil.CalcUV(uv0.x, uv0.y, 0, 0x28, meterWidth, meterHeight);
		gUtil.CalcUV(uv1.x, uv1.y, 0x18, 0x40, meterWidth, meterHeight);
		float iconWave = 20.0f * rowSin;
		gUtil.RenderTextureQuad(static_cast<float>(static_cast<int>(static_cast<float>(leftXi) * rowCos + pos.leftIcon.x)),
		                        pos.leftIcon.y - iconWave, 24.0f, 24.0f, meterTexture, &uv0, &uv1,
		                        &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		gUtil.CalcUV(uv0.x, uv0.y, 0, 0, meterWidth, meterHeight);
		gUtil.CalcUV(uv1.x, uv1.y, 0x28, 0x28, meterWidth, meterHeight);
		gUtil.RenderTextureQuad(static_cast<float>(static_cast<int>(-(static_cast<float>(rightXi) * rowCos - pos.rightIcon.x))),
		                        pos.rightIcon.y + iconWave, 40.0f, 40.0f, meterTexture, &uv0, &uv1,
		                        &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		color.a = static_cast<unsigned char>(static_cast<int>(255.0f * m_optionColumnAnim));
		if (leftHintOn != 0) {
			gUtil.CalcUV(uv0.x, uv0.y, 0x18, 0x58, meterWidth, meterHeight);
			gUtil.CalcUV(uv1.x, uv1.y, 0x28, 0x70, meterWidth, meterHeight);
		} else {
			gUtil.CalcUV(uv0.x, uv0.y, 0, 0x58, meterWidth, meterHeight);
			gUtil.CalcUV(uv1.x, uv1.y, 0x10, 0x70, meterWidth, meterHeight);
		}
		gUtil.RenderTextureQuad(pos.leftArrow.x, pos.leftArrow.y, 16.0f, 24.0f, meterTexture, &uv0,
		                        &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		if (rightHintOn != 0) {
			gUtil.CalcUV(uv0.x, uv0.y, 0x60, 0x5C, meterWidth, meterHeight);
			gUtil.CalcUV(uv1.x, uv1.y, 0x48, 0x7C, meterWidth, meterHeight);
		} else {
			gUtil.CalcUV(uv0.x, uv0.y, 0x48, 0x5C, meterWidth, meterHeight);
			gUtil.CalcUV(uv1.x, uv1.y, 0x30, 0x7C, meterWidth, meterHeight);
		}
		gUtil.RenderTextureQuad(pos.rightArrow.x, pos.rightArrow.y, 24.0f, 32.0f, meterTexture, &uv0,
		                        &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		gUtil.CalcUV(uv0.x, uv0.y, 0x40, 0x28, meterWidth, meterHeight);
		gUtil.CalcUV(uv1.x, uv1.y, 0x50, 0x38, meterWidth, meterHeight);
		Vec2d* bar = &pos.bar;
		float barBaseX = bar->x;
		for (int i = 0, x = 0; i < 12; i++, x += 0x10) {
			gUtil.RenderTextureQuad(barBaseX + static_cast<float>(x), bar->y, 16.0f, 16.0f, meterTexture, &uv0,
			                        &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
			if ((m_optionMenuState != 2) && (i + 1 <= m_bgmVolume)) {
				gUtil.RenderTextureQuad(bar->x + static_cast<float>(x), bar->y, 16.0f, 16.0f, meterTexture, &uv0,
				                        &uv1, &color, GX_BL_ONE, GX_BL_ONE);
			}
		}

#ifdef VERSION_GCCJGC
		DrawOptionLabel(m_fonts[0], static_cast<int>(pos.minLabel.x),
		                static_cast<int>(pos.minLabel.y), color, 7,
		                "\202\215\202\211\202\216", 1.0f);
		DrawOptionLabel(m_fonts[0], static_cast<int>(pos.maxLabel.x),
		                static_cast<int>(pos.maxLabel.y), color, 7,
		                "\202\215\202\201\202\230", 1.0f);
#else
		DrawFont(static_cast<int>(pos.minLabel.x), static_cast<int>(pos.minLabel.y), color, 7,
		         OPT_MES(16), 1.0f, 1.0f);
		pos.maxLabel.x = 564.0f - font->GetWidth(OPT_MES(17));
		DrawFont(static_cast<int>(pos.maxLabel.x), static_cast<int>(pos.maxLabel.y), color, 7, OPT_MES(17), 1.0f,
		         1.0f);
#endif
		break;
	}
	case 3: {
		MenuOptionMeterLayout pos = { { 0.0f, 0.0f }, { 0.0f, 0.0f },
		                             { 0.0f, 0.0f }, { 0.0f, 0.0f },
		                             { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 508.0f, 0.0f } };
		pos.leftIcon.x = 348.0f;
		pos.leftIcon.y = 192.0f;
		pos.rightIcon.x = 556.0f;
		pos.rightIcon.y = 184.0f;
		pos.leftArrow.x = 336.0f;
		pos.leftArrow.y = 190.0f;
		pos.rightArrow.x = 587.0f;
		pos.rightArrow.y = 190.0f;
		pos.bar.x = 372.0f;
		pos.bar.y = 196.0f;
		pos.minLabel.x = 372.0f;
#ifdef VERSION_GCCJGC
		pos.minLabel.y = 172.0f;
		pos.maxLabel.y = 172.0f;
#else
		pos.minLabel.y = 168.0f;
		pos.maxLabel.y = 168.0f;
#endif
		CTexture* meterTexture = m_wmOptionTextureSet->GetTexture(3);
		leftXi = static_cast<int>(472.0f - pos.leftIcon.x);
		rightXi = static_cast<int>((24.0f + pos.rightIcon.x) - 472.0f);
		unsigned int meterHeight = static_cast<unsigned int>(static_cast<float>(meterTexture->m_height));
		unsigned int meterWidth = static_cast<unsigned int>(static_cast<float>(meterTexture->m_width));

		gUtil.CalcUV(uv0.x, uv0.y, 0x18, 0x28, meterWidth, meterHeight);
		gUtil.CalcUV(uv1.x, uv1.y, 0x30, 0x40, meterWidth, meterHeight);
		float iconWave = 20.0f * rowSin;
		gUtil.RenderTextureQuad(static_cast<float>(static_cast<int>(static_cast<float>(leftXi) * rowCos + pos.leftIcon.x)),
		                        pos.leftIcon.y + iconWave, 24.0f, 24.0f, meterTexture, &uv0, &uv1,
		                        &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		gUtil.CalcUV(uv0.x, uv0.y, 0x28, 0, meterWidth, meterHeight);
		gUtil.CalcUV(uv1.x, uv1.y, 0x50, 0x28, meterWidth, meterHeight);
		gUtil.RenderTextureQuad(static_cast<float>(static_cast<int>(-(static_cast<float>(rightXi) * rowCos - pos.rightIcon.x))),
		                        pos.rightIcon.y - iconWave, 40.0f, 40.0f, meterTexture, &uv0, &uv1,
		                        &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		color.a = static_cast<unsigned char>(static_cast<int>(255.0f * m_optionColumnAnim));
		if (leftHintOn != 0) {
			gUtil.CalcUV(uv0.x, uv0.y, 0x18, 0x40, meterWidth, meterHeight);
			gUtil.CalcUV(uv1.x, uv1.y, 0x28, 0x58, meterWidth, meterHeight);
		} else {
			gUtil.CalcUV(uv0.x, uv0.y, 0, 0x40, meterWidth, meterHeight);
			gUtil.CalcUV(uv1.x, uv1.y, 0x10, 0x58, meterWidth, meterHeight);
		}
		gUtil.RenderTextureQuad(pos.leftArrow.x, pos.leftArrow.y, 16.0f, 24.0f, meterTexture, &uv0,
		                        &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		if (rightHintOn != 0) {
			gUtil.CalcUV(uv0.x, uv0.y, 0x60, 0x3C, meterWidth, meterHeight);
			gUtil.CalcUV(uv1.x, uv1.y, 0x48, 0x5C, meterWidth, meterHeight);
		} else {
			gUtil.CalcUV(uv0.x, uv0.y, 0x48, 0x3C, meterWidth, meterHeight);
			gUtil.CalcUV(uv1.x, uv1.y, 0x30, 0x5C, meterWidth, meterHeight);
		}
		gUtil.RenderTextureQuad(pos.rightArrow.x, pos.rightArrow.y, 24.0f, 32.0f, meterTexture, &uv0,
		                        &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

		gUtil.CalcUV(uv0.x, uv0.y, 0x30, 0x28, meterWidth, meterHeight);
		gUtil.CalcUV(uv1.x, uv1.y, 0x40, 0x38, meterWidth, meterHeight);
		Vec2d* bar = &pos.bar;
		float barBaseX = bar->x;
		for (int i = 0, x = 0; i < 12; i++, x += 0x10) {
			gUtil.RenderTextureQuad(barBaseX + static_cast<float>(x), bar->y, 16.0f, 16.0f, meterTexture, &uv0,
			                        &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
			if ((m_optionMenuState != 2) && (i + 1 <= m_seVolume)) {
				gUtil.RenderTextureQuad(bar->x + static_cast<float>(x), bar->y, 16.0f, 16.0f, meterTexture, &uv0,
				                        &uv1, &color, GX_BL_ONE, GX_BL_ONE);
			}
		}

#ifdef VERSION_GCCJGC
		DrawOptionLabel(m_fonts[0], static_cast<int>(pos.minLabel.x),
		                static_cast<int>(pos.minLabel.y), color, 7,
		                "\202\215\202\211\202\216", 1.0f);
		DrawOptionLabel(m_fonts[0], static_cast<int>(pos.maxLabel.x),
		                static_cast<int>(pos.maxLabel.y), color, 7,
		                "\202\215\202\201\202\230", 1.0f);
#else
		DrawFont(static_cast<int>(pos.minLabel.x), static_cast<int>(pos.minLabel.y), color, 7,
		         OPT_MES(16), 1.0f, 1.0f);
		pos.maxLabel.x = 564.0f - font->GetWidth(OPT_MES(17));
		DrawFont(static_cast<int>(pos.maxLabel.x), static_cast<int>(pos.maxLabel.y), color, 7, OPT_MES(17), 1.0f,
		         1.0f);
#endif
		break;
	}
	case 4: {
		Vec2d pts[5] = { { 326.0f, 128.0f }, { 300.0f, 160.0f },
		                       { 330.0f, 138.0f }, { 372.0f, 132.0f }, { 492.0f, 132.0f } };
		int rowAnimFrame;
#ifdef VERSION_GCCJGC
		rowAnimFrame = static_cast<int>(m_optionRowAnim / 0.0625f);
		const float specialRowCos = static_cast<float>(
			cos(static_cast<double>(0.017453292f * (static_cast<float>(rowAnimFrame) * 5.625f))));
#elif defined(VERSION_GCCE01)
		if (static_cast<double>(m_optionRowAnim) < 1.0) {
			rowAnimFrame = static_cast<int>(m_optionRowAnim / 0.0625f);
		} else {
			rowAnimFrame = 0x10;
		}
		const float specialRowCos = static_cast<float>(
			cos(static_cast<double>(0.017453292f * (static_cast<float>(rowAnimFrame) * 5.625f))));
#else
		if (static_cast<double>(m_optionRowAnim) < 1.0) {
			rowAnimFrame = static_cast<int>(m_optionRowAnim / 0.07692308f);
		} else {
			rowAnimFrame = 0xD;
		}
		const float specialRowCos = static_cast<float>(
			cos(static_cast<double>(0.017453292f * (static_cast<float>(rowAnimFrame) * 6.923077f))));
#endif

		int modeU = 0x280;
		int y = 0;
		int uvY2 = 0x18;
		int k = 0;
		int uvY = 0;
		for (int i = 0; i < 4; i++, y += 0x28, uvY += 0x20, uvY2 += 0x20, modeU += 0x40, k = 0) {
			CTexture* cursorPanel = m_wmOptionTextureSet->GetTexture(4);
			float cursorWidth = static_cast<float>(cursorPanel->m_width);
			float cursorHeight = static_cast<float>(cursorPanel->m_height);
			if ((m_specialModeEdit != 0) && (m_specialModeCursor == i)) {
				gUtil.CalcUV(uv0.x, uv0.y, static_cast<unsigned int>(cursorWidth - 48.0f), 0,
				             static_cast<unsigned int>(cursorWidth), static_cast<unsigned int>(cursorHeight));
				gUtil.CalcUV(uv1.x, uv1.y, static_cast<unsigned int>(cursorWidth), 0x28,
				             static_cast<unsigned int>(cursorWidth), static_cast<unsigned int>(cursorHeight));
				const Vec2d* pp = &pts[k];
				gUtil.RenderTextureQuad(pp->x, pp->y + static_cast<float>(y), 48.0f,
				                        40.0f, cursorPanel, &uv0, &uv1, &color, GX_BL_SRCALPHA,
				                        GX_BL_INVSRCALPHA);
			}

			if ((m_specialModeEdit != 0) && (m_specialModeCursor == i)) {
				gUtil.CalcUV(uv0.x, uv0.y, 0, 0x30, static_cast<unsigned int>(cursorWidth),
				             static_cast<unsigned int>(cursorHeight));
				gUtil.CalcUV(uv1.x, uv1.y, static_cast<unsigned int>(cursorWidth), static_cast<unsigned int>(cursorHeight),
				             static_cast<unsigned int>(cursorWidth), static_cast<unsigned int>(cursorHeight));
				const Vec2d* pp1 = &pts[k + 1];
				gUtil.RenderTextureQuad(pp1->x, pp1->y + static_cast<float>(y),
				                        cursorWidth, 16.0f, cursorPanel,
				                        &uv0, &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

				gUtil.CalcUV(uv0.x, uv0.y, static_cast<unsigned int>(cursorWidth), 0x30,
				             static_cast<unsigned int>(cursorWidth), static_cast<unsigned int>(cursorHeight));
				gUtil.CalcUV(uv1.x, uv1.y, 0, static_cast<unsigned int>(cursorHeight),
				             static_cast<unsigned int>(cursorWidth), static_cast<unsigned int>(cursorHeight));
				gUtil.RenderTextureQuad(cursorWidth + pp1->x, pp1->y + static_cast<float>(y),
				                        cursorWidth, 16.0f, cursorPanel,
				                        &uv0, &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
			}

			CTexture* modePanel = m_wmOptionTextureSet->GetTexture(7);
			float modeW = static_cast<float>(modePanel->m_width);
			float modeH = static_cast<float>(modePanel->m_height);
			unsigned int modeHeight = static_cast<unsigned int>(modeH);
			unsigned int modeWidth = static_cast<unsigned int>(modeW);
			gUtil.CalcUV(uv0.x, uv0.y, static_cast<unsigned int>(modeW - 48.0f),
			             uvY, modeWidth, modeHeight);
			gUtil.CalcUV(uv1.x, uv1.y, modeWidth, uvY2, modeWidth, modeHeight);
			const Vec2d* pp2 = &pts[k + 2];
			int modeXi = static_cast<int>(static_cast<float>(modeU) - pp2->x);
			gUtil.RenderTextureQuad(static_cast<float>(static_cast<int>(static_cast<float>(modeXi) *
			                                           specialRowCos + pp2->x)),
			                        pp2->y + static_cast<float>(y), 40.0f, 24.0f,
			                        modePanel, &uv0, &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

			const Vec2d* pp3 = &pts[k + 3];
			int step1 = static_cast<int>(24.0f + (static_cast<float>(modeU) - pp3->x));
			int textXi = static_cast<int>(pp3->x + static_cast<float>(step1) * specialRowCos);
			if (m_specialModeFlags[i] == 0) {
				gUtil.CalcUV(uv0.x, uv0.y, 0, uvY, modeWidth, modeHeight);
				gUtil.CalcUV(uv1.x, uv1.y, 0x78, (i + 1) * 0x20, modeWidth, modeHeight);
				gUtil.RenderTextureQuad(static_cast<float>(textXi), pp3->y + static_cast<float>(y),
				                        120.0f, 32.0f,
				                        modePanel, &uv0, &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
#ifdef VERSION_GCCJGC
				const Vec2d* pp4 = &pts[k + 4];
				int textXi2 = static_cast<int>(pp4->x + static_cast<float>(step1) * specialRowCos);
				DrawOptionLabel(m_fonts[0], textXi2 + 8,
				                static_cast<int>(4.0f + (pp4->y + static_cast<float>(y))), color, 7,
				                "\203\211\203\103\203\147\202\156\202\155", 1.0f);
#elif defined(VERSION_GCCE01)
				const Vec2d* pp4 = &pts[k + 4];
				int textXi2 = static_cast<int>(pp4->x + static_cast<float>(step1) * specialRowCos);
				DrawFont(textXi2 + 8, static_cast<int>(-4.0f + (4.0f + (pp4->y + static_cast<float>(y)))),
				         color, 7, OPT_MES(18), 1.0f, 1.0f);
#else
				CFont* fnt = m_fonts[0];
				char* txt = OPT_MES(18);
				const Vec2d* pp4 = &pts[k + 4];
				int textXi2 = static_cast<int>(pp4->x + static_cast<float>(step1) * specialRowCos);
				fnt->SetMargin(1.0f);
				fnt->SetShadow(1);
				fnt->SetScale(1.0f);
				float tw = fnt->GetWidth(txt);
				DrawFont(static_cast<int>(static_cast<float>((120.0f - tw) *
				                          0.5 + textXi2)),
				         static_cast<int>(-4.0f + (4.0f +
				                          (pp4->y + static_cast<float>(y)))), color, 7,
				         txt, 1.0f, 1.0f);
#endif
			} else {
#ifdef VERSION_GCCJGC
				DrawOptionLabel(m_fonts[0], textXi + 8,
				                static_cast<int>(4.0f + (pp3->y + static_cast<float>(y))), color, 7,
				                "\203\211\203\103\203\147\202\156\202\145\202\145", 1.0f);
#elif defined(VERSION_GCCE01)
				DrawFont(textXi + 8, static_cast<int>(-4.0f + (4.0f + (pp3->y + static_cast<float>(y)))),
				         color, 7, OPT_MES(19), 1.0f, 1.0f);
#else
				CFont* fnt = m_fonts[0];
				char* txt = OPT_MES(19);
				fnt->SetMargin(1.0f);
				fnt->SetShadow(1);
				fnt->SetScale(1.0f);
				float tw = fnt->GetWidth(txt);
				DrawFont(static_cast<int>(static_cast<float>((120.0f - tw) *
				                          0.5 + textXi)),
				         static_cast<int>(-4.0f + (4.0f +
				                          (pp3->y + static_cast<float>(y)))), color, 7,
				         txt, 1.0f, 1.0f);
#endif
				const Vec2d* pp4e = &pts[k + 4];
				int panelXi = static_cast<int>(pp4e->x + static_cast<float>(step1) * specialRowCos);
				gUtil.CalcUV(uv0.x, uv0.y, 0x78, uvY, modeWidth, modeHeight);
				gUtil.CalcUV(uv1.x, uv1.y, 0xE0, (i + 1) * 0x20, modeWidth, modeHeight);
				gUtil.RenderTextureQuad(static_cast<float>(panelXi),
				                        pp4e->y + static_cast<float>(y), 112.0f, 32.0f,
				                        modePanel, &uv0, &uv1, &color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
			}
		}
		break;
	}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8017683C
 * PAL Size: 336b
 * EN Address: 0x801757B8
 * EN Size: 336b
 * JP Address: 0x80171534
 * JP Size: 336b
 */
void CMenuPcs::BindMcObj(int slotNo)
{
	int slot;
	int iconType;
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


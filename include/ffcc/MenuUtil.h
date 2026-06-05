#ifndef _FFCC_MENU_UTIL_H_
#define _FFCC_MENU_UTIL_H_

#include "ffcc/gobject.h"
#include "ffcc/memory.h"

#include <dolphin/gx.h>

class CFont;
struct ArtiState;

class CMenuPcs
{
public:
    void CalcHelpLine(int, int&, int&);
    void GetLongHelpString(CFont*, int, int);
    float CalcCenteringPos2(char*, float, float);
    float CalcCenteringPos(char*, CFont*);
    void DrawFont(int, int, _GXColor, int, char*, float, float);
    void GetFontWidth(char*, float, float);
    void DrawFont2(int, int, _GXColor, int, char*, float, float, float);
    void DrawHelpMessageUS(int, CFont*, int, int, _GXColor, int, float, float);
    void DrawHelpMessage(int, CFont*, int, int, _GXColor, int, float, float);
    void IsItemEquip(int);
    void SetCrystalCageAttr();
    void SetManaWaterEffect();
    const char* GetSkillStr(int);
    char* GetAttrStr(int);
    int ChkEquipActive(int);
    void GetOptionData();
    void InitOptionMenuParam();
    void CalcOptionMenu();
    void DrawOptionMenu();
    void BindMcObj(int);
    unsigned int BindEffect(int, int, int);

    struct EffectInfo
    {
        int m_effectNo;
        int m_partNo;
        int m_slotNo;
        CGObject m_object;
    };

    char pad_00[0x70];
    int m_manaWaterTimerA;            // 0x70
    char pad_74[0x80 - 0x74];
    unsigned char m_effectTimer;      // 0x80
    char pad_81[0x84 - 0x81];
    int m_crystalElem;                // 0x84
    short m_crystalPart;              // 0x88
    short m_crystalAttr;              // 0x8A
    char pad_8C[0x8E - 0x8C];
    signed char m_optionIndex;          // 0x8E
    signed char m_gameInitMode;         // 0x8F
    signed char m_stereoMode;           // 0x90
    signed char m_bgmVolume;            // 0x91
    signed char m_seVolume;             // 0x92
    signed char m_leftHintTimer;        // 0x93
    signed char m_rightHintTimer;       // 0x94
    char pad_95[0x98 - 0x95];
    float m_optionOpenAnim;             // 0x98
    signed char m_optionMenuState;      // 0x9C
    char pad_9D[0xA0 - 0x9D];
    float m_optionRowAnim;              // 0xA0
    signed char m_optionAnimPhase;      // 0xA4
    char pad_A5[0xA8 - 0xA5];
    float m_optionColumnAnim;           // 0xA8
    signed char m_optionAnimCounter;    // 0xAC
    char pad_AD[0xB0 - 0xAD];
    int m_specialModeEdit;              // 0xB0
    signed char m_specialModeCursor;    // 0xB4
    signed char m_specialModeFlags[4];  // 0xB5
    char pad_B9[0xEC - 0xB9];
    CMemory::CStage* m_menuStage;       // 0xEC
    CMemory::CStage* m_stageF0;         // 0xF0
    CMemory::CStage* m_stageF4;         // 0xF4
    CFont* menuFont;
    char pad_FC[0x82C - 0xFC];
    ArtiState* m_artiState;             // 0x82C
    char pad_830[0x838 - 0x830];
    unsigned char* m_effectEntries;     // 0x838
    EffectInfo* m_effectWork;           // 0x840
    char pad_844[0x864 - 0x844];
    unsigned short m_battleStateFlag;   // 0x864
};

extern CMenuPcs MenuPcs;

#endif // _FFCC_MENU_UTIL_H_

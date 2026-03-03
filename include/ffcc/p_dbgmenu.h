#ifndef _FFCC_P_DBGMENU_H_
#define _FFCC_P_DBGMENU_H_

#include "ffcc/system.h"

class CDbgMenuPcs : public CProcess
{
public:
    struct CDM
    {
        s32 m_type;                             // 0x00
        u32 m_flags;                            // 0x04
        s32 m_x;                                // 0x08
        s32 m_y;                                // 0x0C
        s32 m_width;                            // 0x10
        s32 m_height;                           // 0x14
        s32 m_unk18;                            // 0x18
        s32 m_unk1C;                            // 0x1C
        s32 m_unk20;                            // 0x20
        char* m_text;                           // 0x24
        u32 m_unk28;                            // 0x28
        u32 m_unk2C;                            // 0x2C
        s32 m_state;                            // 0x30
        u8 m_status;                            // 0x34
        u8 m_pad35[3];                          // 0x35
        s32 m_id;                               // 0x38
        s32 m_drawX;                            // 0x3C
        s32 m_drawY;                            // 0x40
        CDM* m_prev;                            // 0x44
        CDM* m_next;                            // 0x48
        CDM* m_parent;                          // 0x4C
        CDM* m_firstChild;                      // 0x50

        CDM();

        void Clear();
    };

    struct CDMParam
    {
        s32 m_type;                             // 0x00
        u32 m_flags;                            // 0x04
        s32 m_x;                                // 0x08
        s32 m_y;                                // 0x0C
        s32 m_width;                            // 0x10
        s32 m_height;                           // 0x14
        s32 m_unk18;                            // 0x18
        s32 m_unk1C;                            // 0x1C
        s32 m_unk20;                            // 0x20
        char* m_text;                           // 0x24
        u32 m_unk28;                            // 0x28
        u32 m_unk2C;                            // 0x2C
        u32 m_unk30;                            // 0x30

        CDMParam();
        CDMParam(int, int, int, int, int, int, void*, void (*)(CDM&, void*), void (*)(CDM&, void*));
        
        void Clear();
        void operator=(const CDMParam&);
    };

    CDbgMenuPcs();
	
    void Init();
    void Quit();
    int GetTable(unsigned long);
    void create();
    void destroy();
    void selectNext();
    void selectPrev();
    void calc();
    void draw();
    void calcMenu(CDM*);
    void drawMenu(CDM*);
    void changeVtxFmt(int);
    void drawWindow(int, int, int, int, int, char*);
    void drawFont(int, int, int, char*);
    void searchFreeCDM();
    int searchID(int, CDM&);
    void Add();
    void Add(int, int, CDMParam&);
    void Delete(int);
    int GetDbgFlag();

private:
    u8 m_pad54[0x4];                            // 0x54
    CDM* m_rootMenu;                            // 0x58
    CDM m_menuPool[0x80];                       // 0x5C
    CDM* m_currentMenu;                         // 0x2A5C
    CDM* m_defaultMenu;                         // 0x2A60
    CDM* m_selectedMenu;                        // 0x2A64
    s32 m_currentVtxFmt;                        // 0x2A68
};

extern CDbgMenuPcs DbgMenuPcs;

#endif // _FFCC_P_DBGMENU_H_

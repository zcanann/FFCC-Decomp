#ifndef _FFCC_P_DBGMENU_H_
#define _FFCC_P_DBGMENU_H_

#include "ffcc/system.h"

extern u32 m_table__11CDbgMenuPcs[];
extern u32 m_table_desc0__11CDbgMenuPcs[];
extern u32 m_table_desc1__11CDbgMenuPcs[];
extern u32 m_table_desc2__11CDbgMenuPcs[];
extern u32 m_table_desc3__11CDbgMenuPcs[];

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
    };

    CDbgMenuPcs()
    {
        u32* table = reinterpret_cast<u32*>(m_table__11CDbgMenuPcs);
        const u32* desc0 = m_table_desc0__11CDbgMenuPcs;
        const u32* desc1 = m_table_desc1__11CDbgMenuPcs;
        const u32* desc2 = m_table_desc2__11CDbgMenuPcs;
        const u32* desc3 = m_table_desc3__11CDbgMenuPcs;

        table[1] = desc0[0];
        table[2] = desc0[1];
        table[3] = desc0[2];
        table[4] = desc1[0];
        table[5] = desc1[1];
        table[6] = desc1[2];
        table[7] = desc2[0];
        table[8] = desc2[1];
        table[9] = desc2[2];
        table[12] = desc3[0];
        table[13] = desc3[1];
        table[14] = desc3[2];
    }
	
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
    inline u32 GetDbgFlagsRaw() const { return m_dbgFlags; }

private:
    u32 m_dbgFlags;                             // 0x04
    CDM m_rootMenuNode;                         // 0x08
    CDM m_menuPool[0x80];                       // 0x5C
    CDM* m_currentMenu;                         // 0x2A5C
    CDM* m_defaultMenu;                         // 0x2A60
    CDM* m_selectedMenu;                        // 0x2A64
    s32 m_currentVtxFmt;                        // 0x2A68
};

extern CDbgMenuPcs DbgMenuPcs;

#endif // _FFCC_P_DBGMENU_H_

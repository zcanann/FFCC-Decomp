#ifndef _FFCC_P_DBGMENU_H_
#define _FFCC_P_DBGMENU_H_

class CDbgMenuPcs
{
public:
    struct CDM
    {
        CDM();

        void Clear();
    };

    struct CDMParam
    {
        CDMParam();
        CDMParam(int, int, int, int, int, int, void *, void (*)(CDM &, void *), void (*)(CDM &, void *));
        
        void Clear();
        void operator=(const CDMParam &);
    };

    CDbgMenuPcs();
	
    void Init();
    void Quit();
    void GetTable(unsigned long);
    void create();
    void destroy();
    void selectNext();
    void selectPrev();
    void calc();
    void draw();
    void calcMenu(CDM *);
    void drawMenu(CDM *);
    void changeVtxFmt(int);
    void drawWindow(int, int, int, int, int, char *);
    void drawFont(int, int, int, char *);
    void searchFreeCDM();
    void searchID(int, CDM &);
    void Add();
    void Add(int, int, CDMParam &);
    void Delete(int);
};

#endif // _FFCC_P_DBGMENU_H_

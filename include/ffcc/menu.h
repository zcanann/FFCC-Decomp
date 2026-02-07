#ifndef _FFCC_MENU_H_
#define _FFCC_MENU_H_

#include "ffcc/ref.h"

class CMenu : public CRef
{
public:
    CMenu();
    ~CMenu();
	
    void Create();
    void Destroy();
    void Calc();
    void Draw();
    void ScriptChanging(char*);
    virtual void onCalc();
    virtual void onDraw();
    virtual void onScriptChanging(char*);
    virtual void onScriptChanged(char*, int);
};

#endif // _FFCC_MENU_H_

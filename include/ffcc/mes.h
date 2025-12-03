#ifndef _FFCC_MES_H_
#define _FFCC_MES_H_

class CFont;
class CMenuPcs;
class CGame;

class CMes
{
public:
    class CFlag
    {
    public:
        void operator=(const CFlag&);
    };
	
    CMes();
    ~CMes();

    void Set(char*, int);
    void Next();
    void getFont(int, int);
    void addString(char**, int);
    void GET_2(char**);
    void GET_1(char**);
    void GetWait();
    void Calc();
    void Draw();
    void SetPosition(float, float);
    void useFlag(int, int);
    void addFlag(class CFlag&);
    void MakeAgbString(char*, char*, int, int);
    void drawTagString(CFont*, char*, int, int, int);
};

#endif // _FFCC_MES_H_

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

private:
    char* mText;
    int mCounter;
    int mFlags;
    
    // Large data structure to account for high memory offsets seen in objdiff
    char mData[0x3D50];  // Provides space up to offset 0x3D50
};

#endif // _FFCC_MES_H_

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
        unsigned char m_type;   // 0x00
        unsigned char m_pad01;  // 0x01
        unsigned char m_index;  // 0x02
        unsigned char m_pad03;  // 0x03
        short m_value;          // 0x04
    };
	
    CMes();
    ~CMes();

    void Set(char*, int);
    void Next();
    void getFont(int, int);
    void addString(char**, int);
    void GET_2(char**);
    void GET_1(char**);
    int GetWait();
    void SetPlayerIndex(int index) { m_playerIndex = index; }
    float GetMaxWidth() const { return mMaxWidth; }
    float GetMaxHeight() const { return mMaxHeight; }
    void SetTlutBase(int tlutBase) { mTlutBase = tlutBase; }
    void SetShadow(int shadow) { mShadow = shadow; }
    void Calc();
    void Draw();
    void SetPosition(float, float);
    int useFlag(int, int);
    void addFlag(class CFlag&);
    static void MakeAgbString(char*, char*, int, int);
    static unsigned long drawTagString(CFont*, char*, int, int, int);
    static void SetTempValue(int, int);
    static int m_tempVar[0x14];

private:
    void advanceLine(CFont* font);
    void addFlagEntry(unsigned char type, unsigned char index, short value);

    int m_playerIndex;
    char* mText;
    int mCounter;
    int mFlags;

    char mData[0x3BFC];
    int mFlagCount;             // 0x3C0C
    int mFlagCursor;            // 0x3C10
    CFlag mFlagEntries[0x10];   // 0x3C14
    int mWaitActive;            // 0x3C74
    int mWaitFrames;            // 0x3C78
    int mRevealCursor;          // 0x3C7C
    int mDrawCursor;            // 0x3C80
    float mCurrentX;            // 0x3C84
    float mCurrentY;            // 0x3C88
    float mLineWidth;           // 0x3C8C
    float mLineHeight;          // 0x3C90
    char mPad3C94[8];
    float mBaseX;               // 0x3C9C
    float mBaseY;               // 0x3CA0
    float mMaxWidth;            // 0x3CA4
    float mMaxHeight;           // 0x3CA8
    int mFadeEnabled;           // 0x3CAC
    int mAdvanceStep;           // 0x3CB0
    int mTextAlign;             // 0x3CB4
    int mFadeFrames;            // 0x3CB8
    int mFadeCursor;            // 0x3CBC
    int mFlagVars[0x14];        // 0x3CC0
    int mRubyEnabled;           // 0x3D10
    int mRubyLine;              // 0x3D14
    int mRubyHeight;            // 0x3D18
    int mRubyOffset;            // 0x3D1C
    float mRubyY;               // 0x3D20
    int mRubySpacing;           // 0x3D24
    int mColor;                 // 0x3D28
    int mFontAlign;             // 0x3D2C
    int mFontCount;             // 0x3D30
    int mTlutBase;              // 0x3D34
    int mShadow;                // 0x3D38
    float mLineSpacing;         // 0x3D3C
    int mFontIndex;             // 0x3D40
    float mScaleX;              // 0x3D44
    float mScaleY;              // 0x3D48
    int mAdvanceEnabled;        // 0x3D4C
};

#endif // _FFCC_MES_H_

#ifndef _FFCC_MES_H_
#define _FFCC_MES_H_

class CFont;
class CMenuPcs;
class CGame;

#ifdef VERSION_GCCJGC
struct CMesCharCell
{
    float m_x;
    float m_y;
    float m_width;
    float m_scale;
    unsigned short m_char;
    unsigned short m_reveal;
    unsigned char m_fontAlign;
    unsigned char m_fadeFrames;
    unsigned char m_color;
    unsigned char m_fontIndex;
    unsigned char m_fadeCursor;
    unsigned char m_flagCount;
};

typedef char CMesCharCell_size_check[(sizeof(CMesCharCell) == 0x1C) ? 1 : -1];
#else
struct CMesCharCell
{
	float m_x;                      // 0x00
	float m_width;                  // 0x04
	short m_y;                      // 0x08
	unsigned char m_scaleX;         // 0x0A
	char m_pad0B;                   // 0x0B
	unsigned short m_reveal;        // 0x0C
	unsigned char m_fontAlign : 4;  // 0x0E hi
	unsigned char m_fontIndex : 4;  // 0x0E lo
	unsigned char m_fadeFrames : 4; // 0x0F hi
	unsigned char m_fadeCursor : 4; // 0x0F lo
	unsigned char m_char;           // 0x10
	unsigned char m_scaleY;         // 0x11
	unsigned char m_color;          // 0x12
	unsigned char m_flagCount;      // 0x13
};

typedef char CMesCharCell_size_check[(sizeof(CMesCharCell) == 0x14) ? 1 : -1];
#endif

class CMes
{
    friend class CMesMenu;

public:
    class CFlag
    {
    public:
        class CParam
        {
        public:
            unsigned char m_index;  // 0x00
            short m_value;          // 0x02
        };

        unsigned char m_type;   // 0x00
        CParam m_param;         // 0x02
    };
	
    CMes();
    ~CMes();

    void Set(char*, int);
    void Next();
    CFont* getFont(int, int);
    void addString(char**, int);
    int GET_2(char**);
    char GET_1(char**);
    int GetWait();
#ifndef VERSION_GCCJGC
    void SetPlayerIndex(int index) { m_playerIndex = index; }
#endif
    float GetWidth() { return mMaxWidth; }
    float GetHeight() { return mMaxHeight; }
    float GetPosX() { return mBaseX; }
    float GetPosY() { return mBaseY; }
    void SetTlut(int tlutBase, int shadow)
    {
        mTlutBase = tlutBase;
        mShadow = shadow;
    }
    int GetIdxSelect() { return mRubyHeight; }
    void SetIdxSelect(int index) { mRubyHeight = index; }
    int GetNumSelect() { return mRubyLine; }
    int GetDefaultSelect() { return mRubyOffset; }
    float GetYSelect() { return mRubyY; }
    float GetHSelect() { return mRubySpacing; }
    void SetValue(int index, int value) { mFlagVars[index] = value; }
    int IsEnd() { return mWaitActive; }
    int IsFadeOut() { return mFadeEnabled; }
    void FadeOut()
    {
        mFadeEnabled = 1;
        mFadeCursor = 0;
    }
    bool IsFadeOutCompleted() { return (mFadeEnabled != 0) && (mFadeCursor == mFadeFrames); }
    void Skip()
    {
        mDrawCursor = mRevealCursor + 1000;
        useFlag(mFlagCount, 1);
    }
    void Calc();
    void Draw();
    void SetPosition(float, float);
    int useFlag(int, int);
    void addFlag(class CFlag&);
#ifdef VERSION_GCCJGC
    static void MakeAgbString(char*, char*);
#else
    static void MakeAgbString(char*, char*, int, int);
#endif
    static unsigned long drawTagString(CFont*, char*, int, int, int);
    static unsigned long GetTagStringWidth(CFont* font, char* text) { return drawTagString(font, text, 0, 0, 0); }
    static unsigned long DrawTagString(CFont* font, char* text) { return drawTagString(font, text, 1, 0, 0); }
    static void SetTempValue(int index, int value) { m_tempVar[index] = value; }
    static int m_tempVar[0x14];

private:
    void advanceLine(CFont* font);
    void addFlagEntry(unsigned char type, unsigned char index, short value);

#ifndef VERSION_GCCJGC
    int m_playerIndex;
#endif
    char* mText;
    int mCounter;
#ifdef VERSION_GCCJGC
    CMesCharCell m_chars[256];
#else
    CMesCharCell m_chars[768];
#endif
    // Offset comments below describe the PAL/USA layout.
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
#ifdef VERSION_GCCJGC
    int mFlagVars[0x10];
#else
    int mFlagVars[0x14];        // 0x3CC0
#endif
    int mRubyEnabled;           // 0x3D10
    int mRubyLine;              // 0x3D14
    int mRubyHeight;            // 0x3D18
    int mRubyOffset;            // 0x3D1C
    float mRubyY;               // 0x3D20
    float mRubySpacing;         // 0x3D24
    int mColor;                 // 0x3D28
    int mFontAlign;             // 0x3D2C
    int mFontCount;             // 0x3D30
    int mTlutBase;              // 0x3D34
    int mShadow;                // 0x3D38
    float mLineSpacing;         // 0x3D3C
    int mFontIndex;             // 0x3D40
    float mScaleX;              // 0x3D44
#ifndef VERSION_GCCJGC
    float mScaleY;              // 0x3D48
    int mAdvanceEnabled;        // 0x3D4C
#endif
};

#ifdef VERSION_GCCJGC
typedef char CMes_size_check[(sizeof(CMes) == 0x1D34) ? 1 : -1];
#endif

#endif // _FFCC_MES_H_

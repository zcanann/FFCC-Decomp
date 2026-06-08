#ifndef _FFCC_MAPKEYFRAME_H_
#define _FFCC_MAPKEYFRAME_H_

class CChunkFile;

class CMapKeyFrame
{
public:
    CMapKeyFrame()
    {
        m_junTable = 0;
        m_keyFrame = 0;
        m_keyValue = 0;
        m_splineTable = 0;
        m_loop = 1;
        m_isRun = 0;
    }
#ifndef FFCC_MAPKEYFRAME_NO_DESTRUCTOR
    ~CMapKeyFrame()
    {
        Destroy();
    }
#endif

    void Destroy()
    {
        if (m_junTable != 0) {
            delete m_junTable;
            m_junTable = 0;
        }
        if (m_keyFrame != 0) {
            delete m_keyFrame;
            m_keyFrame = 0;
        }
        if (m_keyValue != 0) {
            delete m_keyValue;
            m_keyValue = 0;
        }
        if (m_splineTable != 0) {
            delete m_splineTable;
            m_splineTable = 0;
        }
    }

    float Get();
    int Get(int&, int&, float&);
    void Calc();
    int IsRun();
    void ReadJun(CChunkFile&, int);
    void ReadFrame(CChunkFile&, int);
    void ReadKey(CChunkFile&, int);

    unsigned char m_mode;      // 0x00
    unsigned char m_junCount;  // 0x01
    unsigned char m_keyCount;  // 0x02
    unsigned char m_loop;      // 0x03
    unsigned char m_isRun;     // 0x04
    unsigned char m_pad05[3];  // 0x05
    int m_currentFrame;        // 0x08
    int m_startFrame;          // 0x0C
    int m_endFrame;            // 0x10
    int m_frameCount;          // 0x14
    unsigned char* m_junTable; // 0x18
    float* m_keyFrame;         // 0x1C
    float* m_keyValue;         // 0x20
    float* m_splineTable;      // 0x24
};

typedef char CMapKeyFrame_size_check[(sizeof(CMapKeyFrame) == 0x28) ? 1 : -1];

#endif // _FFCC_MAPKEYFRAME_H_

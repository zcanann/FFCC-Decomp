#ifndef _FFCC_PPP_PRGOBJ_H_
#define _FFCC_PPP_PRGOBJ_H_

#include "ffcc/gobject.h"

struct Vec;
class CGObject;

class CGPrgObj : public CGObject
{
public:
    void onCreate();
    void onDestroy();
    void onFrame();
    virtual void ClassControl(int, int);
    virtual int GetClassControl(int);
    virtual void bonus(int, int, CGPrgObj*);
    virtual int getReplaceStat(int);
    virtual void onCancelStat(int);
    virtual void onChangeStat(int);
    virtual void onFramePreCalc();
    virtual void onFramePostCalc();
    virtual void onFrameStat();
    virtual void onFrameAlways();
    virtual void onFrameAlwaysAfter();
    virtual void onChangePrg(int);
    virtual void onDamaged(CGPrgObj*);
    virtual void onAttacked(CGPrgObj*);
    void changeStat(int, int, int);
    void changeSubStat(int subState);
    void addSubStat();
    void reqAnim(int, int, int);
    int isLoopAnim();
    int isLoopAnimDirect();
    int playSe3D(int, int, int, int, Vec*);
    void putParticle(int, int, Vec*, float, int);
    void putParticle(int, int, CGObject*, float, int);
    void putParticleTrace(int, int, CGObject*, float, int);
    void putParticleBindTrace(int, int, CGObject*, float, int);
    float getTargetRot(CGPrgObj*);
    void rotTarget(CGPrgObj*);
    void dstTargetRot(CGPrgObj*);
    int GetCID();

    int m_stateFrameGate;      // 0x518
    int m_subFrameGate;        // 0x51C
    int m_lastStateId;         // 0x520
    int m_stateArg;            // 0x524
    int m_stateFrame;          // 0x528
    int m_subState;            // 0x52C
    int m_subFrame;            // 0x530
    char unk_534[16];          // 0x534
    union AnimFlags {
        unsigned char m_animFlags; // 0x544-0x548
        struct Bits {
            signed char m_animRequested : 1;
            signed char m_animLoop : 1;
            signed char m_animDirect : 1;
            signed char m_animFlagsUnused : 5;
        } bits;
    } m_animFlagBits;
    int m_reqAnimId;       // 0x548
    union Flags {
        unsigned char m_flags;
        struct Bits {
            unsigned char unk0 : 1;
            unsigned char unk1 : 1;
            unsigned char unk2 : 1;
            unsigned char unk3 : 1;
            unsigned char unk4 : 1;
            unsigned char unk5 : 1;
            unsigned char unk6 : 1;
            unsigned char unk7 : 1;
        } bits;
    } m_flagBits;          // 0x54C
};

#endif // _FFCC_PPP_PRGOBJ_H_

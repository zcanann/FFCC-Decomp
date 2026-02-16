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
    void bonus(int, int, CGPrgObj*);
    void onFrameAlways();
    void onFrameAlwaysAfter();
    void onDamaged(CGPrgObj*);
    void onAttacked(CGPrgObj*);
    virtual void onCancelStat(int);
    virtual void onChangeStat(int);
    virtual void onFramePreCalc();
    virtual void onFramePostCalc();
    virtual void onFrameStat();
    virtual void onChangePrg(int);
    void changeStat(int, int, int);
    void changeSubStat(int subState);
    void addSubStat();
    void reqAnim(int, int, int);
    int isLoopAnim();
    int isLoopAnimDirect();
    int playSe3D(int, int, int, int, Vec*);
    void changePrg(int);
    void putParticle(int, int, Vec*, float, int);
    void putParticle(int, int, CGObject*, float, int);
    void putParticleTrace(int, int, CGObject*, float, int);
    void putParticleBindTrace(int, int, CGObject*, float, int);
    virtual int getReplaceStat(int);
    float getTargetRot(CGPrgObj*);
    void rotTarget(CGPrgObj*);
    void dstTargetRot(CGPrgObj*);
    void ClassControl(int, int);
    int GetClassControl(int);
    int GetCID();

    int m_stateFrameGate;      // 0x518
    int m_subFrameGate;        // 0x51C
    int m_lastStateId;         // 0x520
    int m_stateArg;            // 0x524
    int m_stateFrame;          // 0x528
    int m_subState;            // 0x52C
    int m_subFrame;            // 0x530
    char unk_534[16];          // 0x534
    unsigned char m_animFlags; // 0x544-0x548
    int m_reqAnimId;           // 0x548
    unsigned char m_flags;     // 0x54D-0x550
};

#endif // _FFCC_PPP_PRGOBJ_H_

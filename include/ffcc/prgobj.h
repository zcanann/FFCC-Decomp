#ifndef _FFCC_PPP_PRGOBJ_H_
#define _FFCC_PPP_PRGOBJ_H_

struct Vec;
class CGObject;

class CGPrgObj
{
public:
    void onCreate();
    void onDestroy();
    void onFrame();
    void changeStat(int, int, int);
    void changeSubStat(int);
    void addSubStat();
    void reqAnim(int, int, int);
    void isLoopAnim();
    void isLoopAnimDirect();
    void playSe3D(int, int, int, int, Vec *);
    void changePrg(int);
    void putParticle(int, int, Vec *, float, int);
    void putParticle(int, int, CGObject *, float, int);
    void putParticleTrace(int, int, CGObject *, float, int);
    void putParticleBindTrace(int, int, CGObject *, float, int);
    void getTargetRot(CGPrgObj *);
    void rotTarget(CGPrgObj *);
    void dstTargetRot(CGPrgObj *);
    void ClassControl(int, int);
    void GetClassControl(int);
    void GetCID();
};

#endif // _FFCC_PPP_PRGOBJ_H_

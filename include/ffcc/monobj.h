#ifndef _FFCC_MONOBJ_H_
#define _FFCC_MONOBJ_H_

class CFont;
class CGPrgObj;
class CGPartyObj;
class CGCharaObj;
struct Vec;
class CVector;
class CMapPcs;

class CGMonObj
{
public:
    class CMoveWork
    {
    public:
        void Clear();
    };
	
    void onCreate();
    void onDestroy();
    void resetWork();
    void onFramePreCalc();
    void flyDown();
    void flyUp();
    void undeadOff();
    void undeadOn();
    void rotTarget(int, float);
    void onStatAttack(int);
    void setAttackAfter(int);
    void getNearParty(int, int, float, float, int);
    void onChangeStat(int);
    void setActionParam(int);
    void onCancelStat(int);
    void isValidTarget();
    void seKiduki();
    void onFrameStat();
    void onStatMagic();
    void onAnimPoint(int, int);
    void enableAttackCol(int, int, int);
    void enableDamageCol(int);
    void getReplaceStat(int);
    void onStatShield();
    void onStatDie();
    void onDrawDebug(CFont*, float, float&, float);
    void onAttacked(CGPrgObj*);
    void onDamaged(CGPrgObj*);
    void link(CGPartyObj*, CGMonObj*);
    void aiTarget();
    void aiTargetAttackRomMon(int);
    void checkCol(int, float, float, float*, int*);
    void mlSet(int);
    void mlWaitingCheck();
    void mlAway();
    void mlHide();
    void mlWaiting();
    void mlEscapeCheck();
    void mlEscape();
    void moveCancel();
    void moveChase(CGCharaObj*);
    void moveEscape();
    void moveAway(CGCharaObj*, int, int, int, int);
    void moveChaseAndStat(CGCharaObj*, int, float, int, int);
    void mlMove();
    void mlAttackCheck(int);
    void mlAttack();
    void aiAddDefault(int&);
    void aiSeq(int, int, int, int, int, int);
    void statWatch();
    void statAround();
    void statAway();
    void setAI(int, int, int);
    void onFrameAlways();
    void InitFinished();
    void initFinishedFuncDefault();
    void setIceJEffect(int);
    void setFlyEffect(int, int);
    void setUndeadEffect(int, int);
    void IsDispRader();
    void setRepop(int);
    void statMove();
    void moveAStar(int, int, Vec&);
    void moveFrame();
    void logicFuncDefault();
    void calcBranchFuncDefault(int);
    void sysControl(int);
    void onChangePrg(int);
    void footSe();
    void GetCID();
};

#endif // _FFCC_MONOBJ_H_

#ifndef _FFCC_MONOBJ_H_
#define _FFCC_MONOBJ_H_

#include "ffcc/charaobj.h"

class CFont;
class CGPrgObj;
class CGPartyObj;
class CGObject;
struct Vec;
class CVector;
class CMapPcs;
struct MonAiFuncTable;

extern "C" u8 m_aiWork__8CGMonObj[0xC];
extern "C" u8 m_boss__8CGMonObj[0x8C];

class CGMonObj : public CGCharaObj
{
public:
    CGMonObj();

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
    int getNearParty(int, int, float, float, int);
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
    int getReplaceStat(int);
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
    int aiSeq(int, int, int, int, int, int);
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
    unsigned int IsDispRader();
    void setRepop(int);
    void statMove();
    void moveAStar(int, int, Vec&);
    void moveFrame();
    void logicFuncDefault();
    int calcBranchFuncDefault(int);
    void sysControl(int);
    void onChangePrg(int);
    void footSe();
    int GetCID();

    void alwaysFuncDefault();
    void alwaysFuncMeteoParasite();
    void alwaysFuncOrcKing();
    int attackCheckFuncLKShooter(int);
    int attackCheckFuncMeteoParasite(int);
    int attackCheckFuncMeteoParasiteC(int);
    void attackedFuncSaw();
    void aiAddDuct(int&);

    void cancelStatFuncDefault();
    void cancelStatFuncGiantCrab();
    void cancelStatFuncOrcKing();
    void cancelStatFuncGolem();
    void cancelStatFuncArmstrong();
    void cancelStatFuncGoblinKing();
    void cancelStatFuncMolbol();
    void cancelStatFuncLizardmanKing();
    void cancelStatFuncCaveWorm();
    void cancelStatFuncGigasLoad();
    void cancelStatFuncMeteoParasite();
    void cancelStatFuncMeteoParasiteC();
    void cancelStatFuncDuct();
    void cancelStatFuncDragonZombie();
    void cancelStatFuncAntrion();
    void cancelStatFuncTetsukyojin();
    void cancelStatFuncLich();
    void cancelStatFuncSaw();
    void cancelStatFuncRamoe();
    void cancelStatFuncLastBoss();

    int calcBranchFuncDragonZombie(int);
    int calcBranchFuncGiantCrab(int);
    int calcBranchFuncGigasLoad(int);
    int calcBranchFuncGoblinKing(int);
    int calcBranchFuncGolem(int);
    int calcBranchFuncLastBoss(int);
    int calcBranchFuncLich(int);
    int calcBranchFuncMeteoParasiteC(int);
    int calcBranchFuncOrcKing(int);
    int calcBranchFuncTetsukyojin(int);

    void changeStatFuncDefault(int);
    void changeStatFuncGiantCrab(int);
    void changeStatFuncOrcKing(int);
    void changeStatFuncGolem(int);
    void changeStatFuncArmstrong(int);
    void changeStatFuncGoblinKing(int);
    void changeStatFuncMolbol(int);
    void changeStatFuncLizardmanKing(int);
    void changeStatFuncCaveWorm(int);
    void changeStatFuncGigasLoad(int);
    void changeStatFuncMeteoParasite(int);
    void changeStatFuncMeteoParasiteC(int);
    void changeStatFuncDuct(int);
    void changeStatFuncDragonZombie(int);
    void changeStatFuncAntrion(int);
    void changeStatFuncTetsukyojin(int);
    void changeStatFuncLich(int);
    void changeStatFuncRamoe(int);
    void changeStatFuncLastBoss(int);

    void damagedFuncGiantCrab();
    void damagedFuncGolem();
    void damagedFuncGigasLoad();
    void damagedFuncMeteoParasiteC();
    void damagedFuncDuct();
    void damagedFuncLastBoss();
    void damagedFuncWifeLamia();

    void frameStatFuncDefault();
    void frameStatFuncGiantCrab();
    void frameStatFuncOrcKing();
    void frameStatFuncGolem();
    void frameStatFuncArmstrong();
    void frameStatFuncGoblinKing();
    void frameStatFuncMolbol();
    void frameStatFuncLizardmanKing();
    void frameStatFuncCaveWorm();
    void frameStatFuncGigasLoad();
    void frameStatFuncMeteoParasite();
    void frameStatFuncMeteoParasiteC();
    void frameStatFuncDuct();
    void frameStatFuncDragonZombie();
    void frameStatFuncAntrion();
    void frameStatFuncTetsukyojin();
    void frameStatFuncLich();
    void frameStatFuncSaw();
    void frameStatFuncRamoe();
    void frameStatFuncLastBoss();
    void frameStatFuncWifeLamia();
    void frameStatFuncLKShooter();

    void initFinishedFuncMeteoParasite();
    void initFinishedFuncMeteoParasiteC();
    void initFinishedFuncDuct();
    void initFinishedFuncLastBoss();

    void logicFuncGiantCrab();
    void logicFuncSaw();
    void logicFuncMeteoParasite();
    void logicFuncMeteoParasiteC();
    void logicFuncRamoe();
    void logicFuncLastBoss();

    void moveCancelFuncDefault();
    void moveCancelFuncGiantCrab();
    void moveCancelFuncOrcKing();
    void moveCancelFuncGolem();
    void moveCancelFuncArmstrong();
    void moveCancelFuncGoblinKing();
    void moveCancelFuncMolbol();
    void moveCancelFuncLizardmanKing();
    void moveCancelFuncCaveWorm();
    void moveCancelFuncGigasLoad();
    void moveCancelFuncMeteoParasite();
    void moveCancelFuncMeteoParasiteC();
    void moveCancelFuncDuct();
    void moveCancelFuncDragonZombie();
    void moveCancelFuncAntrion();
    void moveCancelFuncTetsukyojin();
    void moveCancelFuncLich();
    void moveCancelFuncRamoe();
    void moveCancelFuncLastBoss();

    void moveFrameFuncDefault();
    void moveFrameFuncGiantCrab();
    void moveFrameFuncOrcKing();
    void moveFrameFuncGolem();
    void moveFrameFuncArmstrong();
    void moveFrameFuncGoblinKing();
    void moveFrameFuncMolbol();
    void moveFrameFuncLizardmanKing();
    void moveFrameFuncCaveWorm();
    void moveFrameFuncGigasLoad();
    void moveFrameFuncMeteoParasite();
    void moveFrameFuncMeteoParasiteC();
    void moveFrameFuncDuct();
    void moveFrameFuncDragonZombie();
    void moveFrameFuncAntrion();
    void moveFrameFuncTetsukyojin();
    void moveFrameFuncLich();
    void moveFrameFuncSaw();
    void moveFrameFuncRamoe();
    void moveFrameFuncLastBoss();

    void teleport(int, int, int, int, int, int, int, int, int, Vec*, int&, Vec&);
    void suikomiSub(CGObject*, float);
    void suikomi(int, float);
    int tgtFuncGigasLoad(int);

    unsigned char m_unk6B8[0x50]; // 0x6B8
    MonAiFuncTable* m_funcs;      // 0x708
};

#endif // _FFCC_MONOBJ_H_

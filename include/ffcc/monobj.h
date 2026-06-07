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

class CGMonObj : public CGCharaObj
{
public:
    static u8 m_aiWork[0xC];
    static u8 m_boss[0x8C];

    CGMonObj();

    class CMoveWork
    {
    public:
        void Clear();

        unsigned int m_flags;       // 0x00
        unsigned int m_stateFlags;  // 0x04
        CGCharaObj* m_target;       // 0x08
        Vec m_targetPos;            // 0x0C
        float m_speed;              // 0x18
        float m_range;              // 0x1C
        unsigned int m_limitFrame;  // 0x20
        int m_frame;                // 0x24
        int m_mode;                 // 0x28
        int m_changeStat;           // 0x2C
        short m_routeFrom;          // 0x30
        short m_routePrev;          // 0x32
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
    int mlAttackCheck(int);
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
    void statMove(int*);
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
    inline void suikomiSub(CGObject*, float);
    void suikomi(int, float);
    int tgtFuncGigasLoad(int);

    unsigned char m_unk6B8;       // 0x6B8
    unsigned char m_unk6B9;       // 0x6B9
    unsigned char m_unk6BA;       // 0x6BA
    unsigned char m_chaseDirty;   // 0x6BB
    unsigned char m_unk6BC;       // 0x6BC
    unsigned char m_unk6BD;       // 0x6BD
    unsigned char m_unk6BE;       // 0x6BE
    unsigned char m_unk6BF;       // 0x6BF
    unsigned char m_unk6C0;       // 0x6C0
    unsigned char m_unk6C1;       // 0x6C1
    unsigned char m_unk6C2;       // 0x6C2
    unsigned char m_unk6C3;       // 0x6C3
    int m_targetPartyIndex;       // 0x6C4
    int m_unk6C8;                 // 0x6C8
    int m_unk6CC;                 // 0x6CC
    int m_actionBranch;           // 0x6D0
    union {
        unsigned int m_unk6D4Word;      // 0x6D4
        unsigned short m_groupTag;      // 0x6D4
        struct {
            unsigned short groupTag;    // 0x6D4
            unsigned short delay;       // 0x6D6
        } m_repop;
        unsigned char m_unk6D4[4];      // 0x6D4
    };
    int m_chaseState;             // 0x6D8
    int m_chaseTimer;             // 0x6DC
    union {
        int m_unk6E0;             // 0x6E0
        unsigned char* m_bind;    // 0x6E0
    };
    short m_aiState;              // 0x6E4
    short m_aiStatePrev;          // 0x6E6
    int m_forcedAction;           // 0x6E8
    unsigned int m_controlMask;   // 0x6EC
    int m_attackDelay;            // 0x6F0
    int m_aliveFrames;            // 0x6F4
    Vec m_homePosition;           // 0x6F8
    int m_stepSeHandle;           // 0x704
    MonAiFuncTable* m_funcs;      // 0x708
    CMoveWork m_moveWork;         // 0x70C
};

STATIC_ASSERT(sizeof(CGMonObj::CMoveWork) == 0x34);
STATIC_ASSERT(offsetof(CGMonObj, m_targetPartyIndex) == 0x6C4);
STATIC_ASSERT(offsetof(CGMonObj, m_actionBranch) == 0x6D0);
STATIC_ASSERT(offsetof(CGMonObj, m_repop.delay) == 0x6D6);
STATIC_ASSERT(offsetof(CGMonObj, m_chaseState) == 0x6D8);
STATIC_ASSERT(offsetof(CGMonObj, m_chaseTimer) == 0x6DC);
STATIC_ASSERT(offsetof(CGMonObj, m_bind) == 0x6E0);
STATIC_ASSERT(offsetof(CGMonObj, m_aiState) == 0x6E4);
STATIC_ASSERT(offsetof(CGMonObj, m_forcedAction) == 0x6E8);
STATIC_ASSERT(offsetof(CGMonObj, m_controlMask) == 0x6EC);
STATIC_ASSERT(offsetof(CGMonObj, m_attackDelay) == 0x6F0);
STATIC_ASSERT(offsetof(CGMonObj, m_homePosition) == 0x6F8);
STATIC_ASSERT(offsetof(CGMonObj, m_stepSeHandle) == 0x704);
STATIC_ASSERT(offsetof(CGMonObj, m_funcs) == 0x708);
STATIC_ASSERT(offsetof(CGMonObj, m_moveWork) == 0x70C);
STATIC_ASSERT(sizeof(CGMonObj) == 0x740);

#endif // _FFCC_MONOBJ_H_

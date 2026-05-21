#ifndef _FFCC_PARTYOBJ_H_
#define _FFCC_PARTYOBJ_H_

#include "ffcc/charaobj.h"
#include <dolphin/mtx.h>

class CGObject;
class CGBaseObj;
class CGPrgObj;
class CFont;
class CCaravanWork;
class CGame;
class CATEGOLY2TYPE;
class CVector;
struct Vec;

void stageWeather();
void magicReady();
void chooseMagic();
void decMagic(int);
void calcWeightMax();

struct GhostPartyWork {
	unsigned char _pad0[0x20];
	int mood;
	int thresholdA;
	int thresholdB;
	int thresholdC;
	int slotSel;
	float carrySpeed;
	int pressure;
	int settleTimer;
	int activeTrailCount;
	int trailIndex;
	Vec trail[5];
	Vec leaderTrail[5];
	Vec carryDir;
	int auraParticle;
};

class CGPartyObj : public CGCharaObj
{
public:
	static unsigned char m_ghostWork[0x90];

    void onCreate();
    void onDestroy();

    void onChangeStat(int);
    void onCancelStat(int);

    void menu();
    void onFrameAlways();
    static void CheckMenu();

    void onFramePreCalc();
    void onFramePostCalc();

    void command();
    void callCommandScript(int, CGObject*);

    void shouki();
    void onFrameStat();
    void onAnimPoint(int, int);

    void enableAttackCol(int, int, int);
    void enableDamageCol(int);

    int getReplaceStat(int);

    void statCharge();
    void statAttackSel();

    CGPrgObj* getBestAngleObject(float, float);

    void onStatAttack(int);
    void onStatShield();

    void putComboParticle();
    void putTargetParticle(int, int);
    void endTargetParticle();

    int isDispTarget();
    int isRideTarget();
    void checkTargetParticle();
    void moveCenterTargetParticle();

    void onStatMagic();
    void onStatDie();
    void statAlive();

    void onPush(CGBaseObj*, int);
    void onTalk(CGBaseObj*, int);

    void commandFinished();

    void carry(int, CGObject*, int);
    void statCarry();
    void statPut();
    void statPickup();

    void bonus(int, int, CGPrgObj*);
    int canPlayerUseItem();
    void canPlayerGoMenu();
    void useItem(int);

    int canPlayerPutItem();
    void putItem(int);
    void putGil(int);

    void statRebound();
    void statKorobi();
    void statHide();
    void statJump();

    void statWeaponChange();
    void changeWeapon(int, int, int);

    void CheckGameOver();
    static void SetBonusCondition(int, int, int, int, int);

    void InitFinished();
    unsigned int IsDispRader();

    void ChangeCommandMode(int);
    void checkAndSetWeapon();
    void changeMotionMode(int);
    void setIdleMotion();

    void setAlive(int, int);

    void PutMemoryCapsule(int, int, int, int, char*);
    void onDamaged(CGPrgObj*);
    void onAttacked(CGPrgObj*);

    void gpmCalcDist(Vec*, float&);
    void gpmCol();
    void ghostPartyMog();
    void gpmMove();

    void sysControl(int, int);

    void onDrawDebug(CFont*, float, float&, float);
    void onDraw();

    int GetCID();
};

#endif

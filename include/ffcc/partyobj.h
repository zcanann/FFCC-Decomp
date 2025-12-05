#ifndef _FFCC_PARTYOBJ_H_
#define _FFCC_PARTYOBJ_H_

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

class CGPartyObj
{
public:
    void onCreate();
    void onDestroy();

    void onChangeStat(int);
    void onCancelStat(int);

    void menu();
    void onFrameAlways();
    void CheckMenu();

    void onFramePreCalc();
    void onFramePostCalc();

    void command();
    void callCommandScript(int, CGObject*);

    void shouki();
    void onFrameStat();
    void onAnimPoint(int, int);

    void enableAttackCol(int, int, int);
    void enableDamageCol(int);

    void getReplaceStat(int);

    void statCharge();
    void statAttackSel();

    void getBestAngleObject(float, float);

    void onStatAttack(int);
    void onStatShield();

    void putComboParticle();
    void putTargetParticle(int, int);
    void endTargetParticle();

    void isDispTarget();
    void isRideTarget();
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
    void canPlayerUseItem();
    void canPlayerGoMenu();
    void useItem(int);

    void canPlayerPutItem();
    void putItem(int);
    void putGil(int);

    void statRebound();
    void statKorobi();
    void statHide();
    void statJump();

    void statWeaponChange();
    void changeWeapon(int, int, int);

    void CheckGameOver();
    void SetBonusCondition(int, int, int, int, int);

    void InitFinished();
    void IsDispRader();

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

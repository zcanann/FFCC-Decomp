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

struct PartyObjFlags {
    unsigned char commandActive : 1;
    unsigned char flag40 : 1;
    unsigned char flag20 : 1;
    unsigned char flag10 : 1;
    signed char flag08 : 1;
    signed char flag04 : 1;
    signed char flag02 : 1;
    unsigned char flag01 : 1;
};

struct PartyObjOverlay {
    union {
        unsigned char partyFlags; // 0x6B8
        PartyObjFlags flags;
    };
    unsigned char _pad6B9[3];
    int unk6BC;
    int unk6C0;
    unsigned char commandFlags;
    unsigned char _pad6C5[3];
    int attackSel;
    int unk6CC;
    int unk6D0;
    unsigned short unk6D2;
    unsigned short _pad6D4;
    int weaponRef;
    int weaponItem;
    int pendingWeaponItem;
    union {
        CGObject* target;
        CGBaseObj* carryTarget;
    };
    union {
        CGObject* targetOverride;
        CGBaseObj* secondaryTarget;
    };
    union {
        int unk6EC;
        float unk6ECFloat;
        float targetSearchDistance;
    };
    CGObject* carryObject;
    short commandMode;
    unsigned short _pad6F6;
};

STATIC_ASSERT(offsetof(PartyObjOverlay, unk6BC) == 0x04);
STATIC_ASSERT(offsetof(PartyObjOverlay, unk6C0) == 0x08);
STATIC_ASSERT(offsetof(PartyObjOverlay, commandFlags) == 0x0C);
STATIC_ASSERT(offsetof(PartyObjOverlay, attackSel) == 0x10);
STATIC_ASSERT(offsetof(PartyObjOverlay, weaponRef) == 0x20);
STATIC_ASSERT(offsetof(PartyObjOverlay, weaponItem) == 0x24);
STATIC_ASSERT(offsetof(PartyObjOverlay, pendingWeaponItem) == 0x28);
STATIC_ASSERT(offsetof(PartyObjOverlay, target) == 0x2C);
STATIC_ASSERT(offsetof(PartyObjOverlay, targetOverride) == 0x30);
STATIC_ASSERT(offsetof(PartyObjOverlay, unk6EC) == 0x34);
STATIC_ASSERT(offsetof(PartyObjOverlay, carryObject) == 0x38);
STATIC_ASSERT(offsetof(PartyObjOverlay, commandMode) == 0x3C);

STATIC_ASSERT(sizeof(PartyObjOverlay) == 0x40);

struct GhostPartyWorkFlags {
	unsigned char flag80 : 1;
	unsigned char flag40 : 1;
	unsigned char flag20 : 1;
	unsigned char flag10 : 1;
	unsigned char flag08 : 1;
	unsigned char flag04 : 1;
	unsigned char flag02 : 1;
	unsigned char flag01 : 1;
};

struct GhostPartyWork {
	union {
		unsigned char flags;   // 0x00
		GhostPartyWorkFlags flagBits;
	};
	unsigned char _pad0[3];
	int field04;               // 0x04
	int field08;               // 0x08
	Vec carryDir;              // 0x0C
	int gauge;                 // 0x18
	int state;                 // 0x1C
	int field20;               // 0x20
	int thresholdA;            // 0x24
	int thresholdB;            // 0x28
	int thresholdC;            // 0x2C
	int slotSel;               // 0x30
	float carrySpeed;          // 0x34
	int pressure;              // 0x38
	int settleTimer;           // 0x3C
	int activeTrailCount;      // 0x40
	unsigned char _pad44[0x90 - 0x44];
};
STATIC_ASSERT(offsetof(GhostPartyWork, carryDir) == 0x0C);
STATIC_ASSERT(offsetof(GhostPartyWork, gauge) == 0x18);
STATIC_ASSERT(offsetof(GhostPartyWork, thresholdA) == 0x24);
STATIC_ASSERT(offsetof(GhostPartyWork, slotSel) == 0x30);
STATIC_ASSERT(offsetof(GhostPartyWork, carrySpeed) == 0x34);
STATIC_ASSERT(offsetof(GhostPartyWork, pressure) == 0x38);
STATIC_ASSERT(offsetof(GhostPartyWork, settleTimer) == 0x3C);
STATIC_ASSERT(offsetof(GhostPartyWork, activeTrailCount) == 0x40);
STATIC_ASSERT(sizeof(GhostPartyWork) == 0x90);

class CGPartyObj : public CGCharaObj
{
public:
    CGPartyObj();

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
    int useItem(int);

    int canPlayerPutItem();
    int putItem(int);
    int putGil(int);

    void statRebound();
    void statKorobi();
    void statHide();
    void statJump();

    void statWeaponChange();
    void changeWeapon(int, int, int);

    static void CheckGameOver();
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

    PartyObjOverlay m_partyData; // 0x6B8
};

STATIC_ASSERT(offsetof(CGPartyObj, m_partyData) == 0x6B8);
STATIC_ASSERT(sizeof(CGPartyObj) == 0x6F8);

#endif

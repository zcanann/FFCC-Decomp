#ifndef _FFCC_MONOBJ_TABLE_H_
#define _FFCC_MONOBJ_TABLE_H_

#include "ffcc/monobj.h"

typedef void (CGMonObj::*MonVoidFunc)();
typedef void (CGMonObj::*MonStateFunc)(int);
typedef int (CGMonObj::*MonTargetFunc)(int);
typedef int (CGMonObj::*MonCalcFunc)(int);

struct MonAiFuncTable {
    MonVoidFunc initFinished;
    MonVoidFunc moveFrame;
    MonVoidFunc moveCancel;
    MonStateFunc changeStat;
    MonVoidFunc cancelStat;
    MonVoidFunc frameStat;
    MonVoidFunc logic;
    MonTargetFunc target;
    MonCalcFunc calcBranch;
    MonVoidFunc damaged;
    MonVoidFunc attacked;
    MonCalcFunc attackCheck;
    MonVoidFunc always;
};

extern "C" {
extern MonAiFuncTable funcsDefault;
extern MonAiFuncTable funcsGiantCrab;
extern MonAiFuncTable funcsOrcKing;
extern MonAiFuncTable funcsGolem;
extern MonAiFuncTable funcsArmstrong;
extern MonAiFuncTable funcsGoblinKing;
extern MonAiFuncTable funcsMolbol;
extern MonAiFuncTable funcsLizardmanKing;
extern MonAiFuncTable funcsCaveWorm;
extern MonAiFuncTable funcsGigasLoad;
extern MonAiFuncTable funcsWifeLamia;
extern MonAiFuncTable funcsMeteoParasite;
extern MonAiFuncTable funcsMeteoParasiteC;
extern MonAiFuncTable funcsDuct;
extern MonAiFuncTable funcsDragonZombie;
extern MonAiFuncTable funcsAntrion;
extern MonAiFuncTable funcsTetsukyojin;
extern MonAiFuncTable funcsLich;
extern MonAiFuncTable funcsSaw;
extern MonAiFuncTable funcsRamoe;
extern MonAiFuncTable funcsLastBoss;
extern MonAiFuncTable funcsLKShooter;
}

#endif // _FFCC_MONOBJ_TABLE_H_

#include "ffcc/monobj_table.h"

typedef void (CGMonObj::*MonVoidFunc)();
typedef void (CGMonObj::*MonStateFunc)(int);
typedef int (CGMonObj::*MonCalcFunc)(int);

struct MonAiFuncTable {
    MonVoidFunc initFinished;
    MonVoidFunc moveFrame;
    MonVoidFunc moveCancel;
    MonStateFunc changeStat;
    MonVoidFunc cancelStat;
    MonVoidFunc frameStat;
    MonVoidFunc logic;
    MonStateFunc target;
    MonCalcFunc calcBranch;
    MonVoidFunc damaged;
    MonVoidFunc attacked;
    MonStateFunc attackCheck;
    MonVoidFunc always;
};

extern "C" MonAiFuncTable funcsDefault = {
    &CGMonObj::initFinishedFuncDefault,
    &CGMonObj::moveFrameFuncDefault,
    &CGMonObj::moveCancelFuncDefault,
    &CGMonObj::changeStatFuncDefault,
    &CGMonObj::cancelStatFuncDefault,
    &CGMonObj::frameStatFuncDefault,
    &CGMonObj::logicFuncDefault,
    0,
    &CGMonObj::calcBranchFuncDefault,
    0,
    0,
    0,
    &CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFuncTable funcsGiantCrab = {
    &CGMonObj::initFinishedFuncDefault,
    &CGMonObj::moveFrameFuncGiantCrab,
    &CGMonObj::moveCancelFuncGiantCrab,
    &CGMonObj::changeStatFuncGiantCrab,
    &CGMonObj::cancelStatFuncGiantCrab,
    &CGMonObj::frameStatFuncGiantCrab,
    &CGMonObj::logicFuncGiantCrab,
    0,
    &CGMonObj::calcBranchFuncGiantCrab,
    &CGMonObj::damagedFuncGiantCrab,
    0,
    0,
    &CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFuncTable funcsOrcKing = {
    &CGMonObj::initFinishedFuncDefault,
    &CGMonObj::moveFrameFuncOrcKing,
    &CGMonObj::moveCancelFuncOrcKing,
    &CGMonObj::changeStatFuncOrcKing,
    &CGMonObj::cancelStatFuncOrcKing,
    &CGMonObj::frameStatFuncOrcKing,
    &CGMonObj::logicFuncDefault,
    0,
    &CGMonObj::calcBranchFuncOrcKing,
    0,
    0,
    0,
    &CGMonObj::alwaysFuncOrcKing,
};

extern "C" MonAiFuncTable funcsGolem = {
    &CGMonObj::initFinishedFuncDefault,
    &CGMonObj::moveFrameFuncGolem,
    &CGMonObj::moveCancelFuncGolem,
    &CGMonObj::changeStatFuncGolem,
    &CGMonObj::cancelStatFuncGolem,
    &CGMonObj::frameStatFuncGolem,
    &CGMonObj::logicFuncDefault,
    0,
    &CGMonObj::calcBranchFuncGolem,
    &CGMonObj::damagedFuncGolem,
    0,
    0,
    &CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFuncTable funcsArmstrong = {
    &CGMonObj::initFinishedFuncDefault,
    &CGMonObj::moveFrameFuncArmstrong,
    &CGMonObj::moveCancelFuncArmstrong,
    &CGMonObj::changeStatFuncArmstrong,
    &CGMonObj::cancelStatFuncArmstrong,
    &CGMonObj::frameStatFuncArmstrong,
    &CGMonObj::logicFuncDefault,
    0,
    &CGMonObj::calcBranchFuncDefault,
    0,
    0,
    0,
    &CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFuncTable funcsGoblinKing = {
    &CGMonObj::initFinishedFuncDefault,
    &CGMonObj::moveFrameFuncGoblinKing,
    &CGMonObj::moveCancelFuncGoblinKing,
    &CGMonObj::changeStatFuncGoblinKing,
    &CGMonObj::cancelStatFuncGoblinKing,
    &CGMonObj::frameStatFuncGoblinKing,
    &CGMonObj::logicFuncDefault,
    0,
    &CGMonObj::calcBranchFuncGoblinKing,
    0,
    0,
    0,
    &CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFuncTable funcsMolbol = {
    &CGMonObj::initFinishedFuncDefault,
    &CGMonObj::moveFrameFuncMolbol,
    &CGMonObj::moveCancelFuncMolbol,
    &CGMonObj::changeStatFuncMolbol,
    &CGMonObj::cancelStatFuncMolbol,
    &CGMonObj::frameStatFuncMolbol,
    &CGMonObj::logicFuncDefault,
    0,
    &CGMonObj::calcBranchFuncDefault,
    0,
    0,
    0,
    &CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFuncTable funcsLizardmanKing = {
    &CGMonObj::initFinishedFuncDefault,
    &CGMonObj::moveFrameFuncLizardmanKing,
    &CGMonObj::moveCancelFuncLizardmanKing,
    &CGMonObj::changeStatFuncLizardmanKing,
    &CGMonObj::cancelStatFuncLizardmanKing,
    &CGMonObj::frameStatFuncLizardmanKing,
    &CGMonObj::logicFuncDefault,
    0,
    &CGMonObj::calcBranchFuncDefault,
    0,
    0,
    0,
    &CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFuncTable funcsCaveWorm = {
    &CGMonObj::initFinishedFuncDefault,
    &CGMonObj::moveFrameFuncCaveWorm,
    &CGMonObj::moveCancelFuncCaveWorm,
    &CGMonObj::changeStatFuncCaveWorm,
    &CGMonObj::cancelStatFuncCaveWorm,
    &CGMonObj::frameStatFuncCaveWorm,
    &CGMonObj::logicFuncDefault,
    0,
    &CGMonObj::calcBranchFuncDefault,
    0,
    0,
    0,
    &CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFuncTable funcsGigasLoad = {
    &CGMonObj::initFinishedFuncDefault,
    &CGMonObj::moveFrameFuncGigasLoad,
    &CGMonObj::moveCancelFuncGigasLoad,
    &CGMonObj::changeStatFuncGigasLoad,
    &CGMonObj::cancelStatFuncGigasLoad,
    &CGMonObj::frameStatFuncGigasLoad,
    &CGMonObj::logicFuncDefault,
    &CGMonObj::tgtFuncGigasLoad,
    &CGMonObj::calcBranchFuncGigasLoad,
    &CGMonObj::damagedFuncGigasLoad,
    0,
    0,
    &CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFuncTable funcsWifeLamia = {
    &CGMonObj::initFinishedFuncDefault,
    &CGMonObj::moveFrameFuncDefault,
    &CGMonObj::moveCancelFuncDefault,
    &CGMonObj::changeStatFuncDefault,
    &CGMonObj::cancelStatFuncDefault,
    &CGMonObj::frameStatFuncWifeLamia,
    &CGMonObj::logicFuncDefault,
    0,
    &CGMonObj::calcBranchFuncDefault,
    &CGMonObj::damagedFuncWifeLamia,
    0,
    0,
    &CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFuncTable funcsMeteoParasite = {
    &CGMonObj::initFinishedFuncMeteoParasite,
    &CGMonObj::moveFrameFuncMeteoParasite,
    &CGMonObj::moveCancelFuncMeteoParasite,
    &CGMonObj::changeStatFuncMeteoParasite,
    &CGMonObj::cancelStatFuncMeteoParasite,
    &CGMonObj::frameStatFuncMeteoParasite,
    &CGMonObj::logicFuncMeteoParasite,
    0,
    &CGMonObj::calcBranchFuncDefault,
    0,
    0,
    &CGMonObj::attackCheckFuncMeteoParasite,
    &CGMonObj::alwaysFuncMeteoParasite,
};

extern "C" MonAiFuncTable funcsMeteoParasiteC = {
    &CGMonObj::initFinishedFuncMeteoParasiteC,
    &CGMonObj::moveFrameFuncMeteoParasiteC,
    &CGMonObj::moveCancelFuncMeteoParasiteC,
    &CGMonObj::changeStatFuncMeteoParasiteC,
    &CGMonObj::cancelStatFuncMeteoParasiteC,
    &CGMonObj::frameStatFuncMeteoParasiteC,
    &CGMonObj::logicFuncMeteoParasiteC,
    0,
    &CGMonObj::calcBranchFuncMeteoParasiteC,
    &CGMonObj::damagedFuncMeteoParasiteC,
    0,
    &CGMonObj::attackCheckFuncMeteoParasiteC,
    &CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFuncTable funcsDuct = {
    &CGMonObj::initFinishedFuncDuct,
    &CGMonObj::moveFrameFuncDuct,
    &CGMonObj::moveCancelFuncDuct,
    &CGMonObj::changeStatFuncDuct,
    &CGMonObj::cancelStatFuncDuct,
    &CGMonObj::frameStatFuncDuct,
    &CGMonObj::logicFuncDefault,
    0,
    &CGMonObj::calcBranchFuncDefault,
    &CGMonObj::damagedFuncDuct,
    0,
    0,
    &CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFuncTable funcsDragonZombie = {
    &CGMonObj::initFinishedFuncDefault,
    &CGMonObj::moveFrameFuncDragonZombie,
    &CGMonObj::moveCancelFuncDragonZombie,
    &CGMonObj::changeStatFuncDragonZombie,
    &CGMonObj::cancelStatFuncDragonZombie,
    &CGMonObj::frameStatFuncDragonZombie,
    &CGMonObj::logicFuncDefault,
    0,
    &CGMonObj::calcBranchFuncDragonZombie,
    0,
    0,
    0,
    &CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFuncTable funcsAntrion = {
    &CGMonObj::initFinishedFuncDefault,
    &CGMonObj::moveFrameFuncAntrion,
    &CGMonObj::moveCancelFuncAntrion,
    &CGMonObj::changeStatFuncAntrion,
    &CGMonObj::cancelStatFuncAntrion,
    &CGMonObj::frameStatFuncAntrion,
    &CGMonObj::logicFuncDefault,
    0,
    &CGMonObj::calcBranchFuncDefault,
    0,
    0,
    0,
    &CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFuncTable funcsTetsukyojin = {
    &CGMonObj::initFinishedFuncDefault,
    &CGMonObj::moveFrameFuncTetsukyojin,
    &CGMonObj::moveCancelFuncTetsukyojin,
    &CGMonObj::changeStatFuncTetsukyojin,
    &CGMonObj::cancelStatFuncTetsukyojin,
    &CGMonObj::frameStatFuncTetsukyojin,
    &CGMonObj::logicFuncDefault,
    0,
    &CGMonObj::calcBranchFuncTetsukyojin,
    0,
    0,
    0,
    &CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFuncTable funcsLich = {
    &CGMonObj::initFinishedFuncDefault,
    &CGMonObj::moveFrameFuncLich,
    &CGMonObj::moveCancelFuncLich,
    &CGMonObj::changeStatFuncLich,
    &CGMonObj::cancelStatFuncLich,
    &CGMonObj::frameStatFuncLich,
    &CGMonObj::logicFuncDefault,
    0,
    &CGMonObj::calcBranchFuncLich,
    0,
    0,
    0,
    &CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFuncTable funcsSaw = {
    &CGMonObj::initFinishedFuncDefault,
    &CGMonObj::moveFrameFuncSaw,
    &CGMonObj::moveCancelFuncDefault,
    &CGMonObj::changeStatFuncDefault,
    &CGMonObj::cancelStatFuncSaw,
    &CGMonObj::frameStatFuncSaw,
    &CGMonObj::logicFuncSaw,
    0,
    &CGMonObj::calcBranchFuncDefault,
    0,
    &CGMonObj::attackedFuncSaw,
    0,
    &CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFuncTable funcsRamoe = {
    &CGMonObj::initFinishedFuncDefault,
    &CGMonObj::moveFrameFuncRamoe,
    &CGMonObj::moveCancelFuncRamoe,
    &CGMonObj::changeStatFuncRamoe,
    &CGMonObj::cancelStatFuncRamoe,
    &CGMonObj::frameStatFuncRamoe,
    &CGMonObj::logicFuncRamoe,
    0,
    &CGMonObj::calcBranchFuncDefault,
    0,
    0,
    0,
    &CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFuncTable funcsLastBoss = {
    &CGMonObj::initFinishedFuncLastBoss,
    &CGMonObj::moveFrameFuncLastBoss,
    &CGMonObj::moveCancelFuncLastBoss,
    &CGMonObj::changeStatFuncLastBoss,
    &CGMonObj::cancelStatFuncLastBoss,
    &CGMonObj::frameStatFuncLastBoss,
    &CGMonObj::logicFuncLastBoss,
    0,
    &CGMonObj::calcBranchFuncLastBoss,
    &CGMonObj::damagedFuncLastBoss,
    0,
    0,
    &CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFuncTable funcsLKShooter = {
    &CGMonObj::initFinishedFuncDefault,
    &CGMonObj::moveFrameFuncDefault,
    &CGMonObj::moveCancelFuncDefault,
    &CGMonObj::changeStatFuncDefault,
    &CGMonObj::cancelStatFuncDefault,
    &CGMonObj::frameStatFuncLKShooter,
    &CGMonObj::logicFuncDefault,
    0,
    &CGMonObj::calcBranchFuncDefault,
    0,
    0,
    &CGMonObj::attackCheckFuncLKShooter,
    &CGMonObj::alwaysFuncDefault,
};

/*
 * --INFO--
 * PAL Address: 0x801434a8
 * PAL Size: 8012b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_monobj_table_cpp(void);

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::alwaysFuncDefault()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::frameStatFuncDefault()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::cancelStatFuncDefault()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::changeStatFuncDefault(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveCancelFuncDefault()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveFrameFuncDefault()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::cancelStatFuncGiantCrab()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::changeStatFuncGiantCrab(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveCancelFuncGiantCrab()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveFrameFuncGiantCrab()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::changeStatFuncOrcKing(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::cancelStatFuncGolem()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveCancelFuncGolem()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveFrameFuncGolem()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveCancelFuncArmstrong()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveFrameFuncArmstrong()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::changeStatFuncGoblinKing(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveCancelFuncGoblinKing()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveFrameFuncGoblinKing()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveCancelFuncMolbol()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveFrameFuncMolbol()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::frameStatFuncLizardmanKing()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::cancelStatFuncLizardmanKing()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::changeStatFuncLizardmanKing(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveCancelFuncLizardmanKing()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveFrameFuncLizardmanKing()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveCancelFuncCaveWorm()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveFrameFuncCaveWorm()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::frameStatFuncGigasLoad()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::cancelStatFuncGigasLoad()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::changeStatFuncGigasLoad(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveCancelFuncGigasLoad()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveFrameFuncGigasLoad()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::cancelStatFuncMeteoParasite()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveCancelFuncMeteoParasite()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveFrameFuncMeteoParasite()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::cancelStatFuncMeteoParasiteC()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::changeStatFuncMeteoParasiteC(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveCancelFuncMeteoParasiteC()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveFrameFuncMeteoParasiteC()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::frameStatFuncDuct()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::cancelStatFuncDuct()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::changeStatFuncDuct(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveCancelFuncDuct()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveFrameFuncDuct()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveCancelFuncDragonZombie()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveFrameFuncDragonZombie()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::frameStatFuncAntrion()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::cancelStatFuncAntrion()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::changeStatFuncAntrion(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveCancelFuncAntrion()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveFrameFuncAntrion()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveCancelFuncTetsukyojin()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveFrameFuncTetsukyojin()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveCancelFuncLich()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveFrameFuncLich()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveCancelFuncRamoe()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveFrameFuncRamoe()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveCancelFuncLastBoss()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveFrameFuncLastBoss()
{
	// TODO
}

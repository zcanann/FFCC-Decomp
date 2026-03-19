#include "ffcc/monobj_table.h"

typedef void (CGMonObj::*MonAiFunc)();

extern "C" MonAiFunc DAT_80212a1c[13] = {
    &CGMonObj::initFinishedFuncDefault,
    &CGMonObj::moveFrameFuncDefault,
    &CGMonObj::moveCancelFuncDefault,
    (MonAiFunc)&CGMonObj::changeStatFuncDefault,
    &CGMonObj::cancelStatFuncDefault,
    &CGMonObj::frameStatFuncDefault,
    &CGMonObj::logicFuncDefault,
    0,
    (MonAiFunc)&CGMonObj::calcBranchFuncDefault,
    0,
    0,
    0,
    &CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFunc DAT_80212b30[13] = {
    (MonAiFunc)&CGMonObj::initFinishedFuncDefault,
    (MonAiFunc)&CGMonObj::moveFrameFuncGiantCrab,
    (MonAiFunc)&CGMonObj::moveCancelFuncGiantCrab,
    (MonAiFunc)&CGMonObj::changeStatFuncGiantCrab,
    (MonAiFunc)&CGMonObj::cancelStatFuncGiantCrab,
    (MonAiFunc)&CGMonObj::frameStatFuncGiantCrab,
    (MonAiFunc)&CGMonObj::logicFuncGiantCrab,
    0,
    (MonAiFunc)&CGMonObj::calcBranchFuncGiantCrab,
    (MonAiFunc)&CGMonObj::damagedFuncGiantCrab,
    0,
    0,
    (MonAiFunc)&CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFunc DAT_80212c38[13] = {
    (MonAiFunc)&CGMonObj::initFinishedFuncDefault,
    (MonAiFunc)&CGMonObj::moveFrameFuncOrcKing,
    (MonAiFunc)&CGMonObj::moveCancelFuncOrcKing,
    (MonAiFunc)&CGMonObj::changeStatFuncOrcKing,
    (MonAiFunc)&CGMonObj::cancelStatFuncOrcKing,
    (MonAiFunc)&CGMonObj::frameStatFuncOrcKing,
    (MonAiFunc)&CGMonObj::logicFuncDefault,
    0,
    (MonAiFunc)&CGMonObj::calcBranchFuncOrcKing,
    0,
    0,
    0,
    (MonAiFunc)&CGMonObj::alwaysFuncOrcKing,
};

extern "C" MonAiFunc DAT_80212d4c[13] = {
    (MonAiFunc)&CGMonObj::initFinishedFuncDefault,
    (MonAiFunc)&CGMonObj::moveFrameFuncGolem,
    (MonAiFunc)&CGMonObj::moveCancelFuncGolem,
    (MonAiFunc)&CGMonObj::changeStatFuncGolem,
    (MonAiFunc)&CGMonObj::cancelStatFuncGolem,
    (MonAiFunc)&CGMonObj::frameStatFuncGolem,
    (MonAiFunc)&CGMonObj::logicFuncDefault,
    0,
    (MonAiFunc)&CGMonObj::calcBranchFuncGolem,
    (MonAiFunc)&CGMonObj::damagedFuncGolem,
    0,
    0,
    (MonAiFunc)&CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFunc DAT_80212e54[13] = {
    (MonAiFunc)&CGMonObj::initFinishedFuncDefault,
    (MonAiFunc)&CGMonObj::moveFrameFuncArmstrong,
    (MonAiFunc)&CGMonObj::moveCancelFuncArmstrong,
    (MonAiFunc)&CGMonObj::changeStatFuncArmstrong,
    (MonAiFunc)&CGMonObj::cancelStatFuncArmstrong,
    (MonAiFunc)&CGMonObj::frameStatFuncArmstrong,
    (MonAiFunc)&CGMonObj::logicFuncDefault,
    0,
    (MonAiFunc)&CGMonObj::calcBranchFuncDefault,
    0,
    0,
    0,
    (MonAiFunc)&CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFunc DAT_80212f5c[13] = {
    (MonAiFunc)&CGMonObj::initFinishedFuncDefault,
    (MonAiFunc)&CGMonObj::moveFrameFuncGoblinKing,
    (MonAiFunc)&CGMonObj::moveCancelFuncGoblinKing,
    (MonAiFunc)&CGMonObj::changeStatFuncGoblinKing,
    (MonAiFunc)&CGMonObj::cancelStatFuncGoblinKing,
    (MonAiFunc)&CGMonObj::frameStatFuncGoblinKing,
    (MonAiFunc)&CGMonObj::logicFuncDefault,
    0,
    (MonAiFunc)&CGMonObj::calcBranchFuncGoblinKing,
    0,
    0,
    0,
    (MonAiFunc)&CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFunc DAT_80213064[13] = {
    (MonAiFunc)&CGMonObj::initFinishedFuncDefault,
    (MonAiFunc)&CGMonObj::moveFrameFuncMolbol,
    (MonAiFunc)&CGMonObj::moveCancelFuncMolbol,
    (MonAiFunc)&CGMonObj::changeStatFuncMolbol,
    (MonAiFunc)&CGMonObj::cancelStatFuncMolbol,
    (MonAiFunc)&CGMonObj::frameStatFuncMolbol,
    (MonAiFunc)&CGMonObj::logicFuncDefault,
    0,
    (MonAiFunc)&CGMonObj::calcBranchFuncDefault,
    0,
    0,
    0,
    (MonAiFunc)&CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFunc DAT_8021316c[13] = {
    (MonAiFunc)&CGMonObj::initFinishedFuncDefault,
    (MonAiFunc)&CGMonObj::moveFrameFuncLizardmanKing,
    (MonAiFunc)&CGMonObj::moveCancelFuncLizardmanKing,
    (MonAiFunc)&CGMonObj::changeStatFuncLizardmanKing,
    (MonAiFunc)&CGMonObj::cancelStatFuncLizardmanKing,
    (MonAiFunc)&CGMonObj::frameStatFuncLizardmanKing,
    (MonAiFunc)&CGMonObj::logicFuncDefault,
    0,
    (MonAiFunc)&CGMonObj::calcBranchFuncDefault,
    0,
    0,
    0,
    (MonAiFunc)&CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFunc DAT_80213274[13] = {
    (MonAiFunc)&CGMonObj::initFinishedFuncDefault,
    (MonAiFunc)&CGMonObj::moveFrameFuncCaveWorm,
    (MonAiFunc)&CGMonObj::moveCancelFuncCaveWorm,
    (MonAiFunc)&CGMonObj::changeStatFuncCaveWorm,
    (MonAiFunc)&CGMonObj::cancelStatFuncCaveWorm,
    (MonAiFunc)&CGMonObj::frameStatFuncCaveWorm,
    (MonAiFunc)&CGMonObj::logicFuncDefault,
    0,
    (MonAiFunc)&CGMonObj::calcBranchFuncDefault,
    0,
    0,
    0,
    (MonAiFunc)&CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFunc DAT_80213394[13] = {
    (MonAiFunc)&CGMonObj::initFinishedFuncDefault,
    (MonAiFunc)&CGMonObj::moveFrameFuncGigasLoad,
    (MonAiFunc)&CGMonObj::moveCancelFuncGigasLoad,
    (MonAiFunc)&CGMonObj::changeStatFuncGigasLoad,
    (MonAiFunc)&CGMonObj::cancelStatFuncGigasLoad,
    (MonAiFunc)&CGMonObj::frameStatFuncGigasLoad,
    (MonAiFunc)&CGMonObj::logicFuncDefault,
    (MonAiFunc)&CGMonObj::tgtFuncGigasLoad,
    (MonAiFunc)&CGMonObj::calcBranchFuncGigasLoad,
    (MonAiFunc)&CGMonObj::damagedFuncGigasLoad,
    0,
    0,
    (MonAiFunc)&CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFunc DAT_802134a8[13] = {
    (MonAiFunc)&CGMonObj::initFinishedFuncDefault,
    (MonAiFunc)&CGMonObj::moveFrameFuncDefault,
    (MonAiFunc)&CGMonObj::moveCancelFuncDefault,
    (MonAiFunc)&CGMonObj::changeStatFuncDefault,
    (MonAiFunc)&CGMonObj::cancelStatFuncDefault,
    (MonAiFunc)&CGMonObj::frameStatFuncWifeLamia,
    (MonAiFunc)&CGMonObj::logicFuncDefault,
    0,
    (MonAiFunc)&CGMonObj::calcBranchFuncDefault,
    (MonAiFunc)&CGMonObj::damagedFuncWifeLamia,
    0,
    0,
    (MonAiFunc)&CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFunc DAT_802135bc[13] = {
    (MonAiFunc)&CGMonObj::initFinishedFuncMeteoParasite,
    (MonAiFunc)&CGMonObj::moveFrameFuncMeteoParasite,
    (MonAiFunc)&CGMonObj::moveCancelFuncMeteoParasite,
    (MonAiFunc)&CGMonObj::changeStatFuncMeteoParasite,
    (MonAiFunc)&CGMonObj::cancelStatFuncMeteoParasite,
    (MonAiFunc)&CGMonObj::frameStatFuncMeteoParasite,
    (MonAiFunc)&CGMonObj::logicFuncMeteoParasite,
    0,
    (MonAiFunc)&CGMonObj::calcBranchFuncDefault,
    0,
    0,
    (MonAiFunc)&CGMonObj::attackCheckFuncMeteoParasite,
    (MonAiFunc)&CGMonObj::alwaysFuncMeteoParasite,
};

extern "C" MonAiFunc DAT_802136dc[13] = {
    (MonAiFunc)&CGMonObj::initFinishedFuncMeteoParasiteC,
    (MonAiFunc)&CGMonObj::moveFrameFuncMeteoParasiteC,
    (MonAiFunc)&CGMonObj::moveCancelFuncMeteoParasiteC,
    (MonAiFunc)&CGMonObj::changeStatFuncMeteoParasiteC,
    (MonAiFunc)&CGMonObj::cancelStatFuncMeteoParasiteC,
    (MonAiFunc)&CGMonObj::frameStatFuncMeteoParasiteC,
    (MonAiFunc)&CGMonObj::logicFuncMeteoParasiteC,
    0,
    (MonAiFunc)&CGMonObj::calcBranchFuncMeteoParasiteC,
    (MonAiFunc)&CGMonObj::damagedFuncMeteoParasiteC,
    0,
    (MonAiFunc)&CGMonObj::attackCheckFuncMeteoParasiteC,
    (MonAiFunc)&CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFunc DAT_802137f0[13] = {
    (MonAiFunc)&CGMonObj::initFinishedFuncDuct,
    (MonAiFunc)&CGMonObj::moveFrameFuncDuct,
    (MonAiFunc)&CGMonObj::moveCancelFuncDuct,
    (MonAiFunc)&CGMonObj::changeStatFuncDuct,
    (MonAiFunc)&CGMonObj::cancelStatFuncDuct,
    (MonAiFunc)&CGMonObj::frameStatFuncDuct,
    (MonAiFunc)&CGMonObj::logicFuncDefault,
    0,
    (MonAiFunc)&CGMonObj::calcBranchFuncDefault,
    (MonAiFunc)&CGMonObj::damagedFuncDuct,
    0,
    0,
    (MonAiFunc)&CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFunc DAT_802138f8[13] = {
    (MonAiFunc)&CGMonObj::initFinishedFuncDefault,
    (MonAiFunc)&CGMonObj::moveFrameFuncDragonZombie,
    (MonAiFunc)&CGMonObj::moveCancelFuncDragonZombie,
    (MonAiFunc)&CGMonObj::changeStatFuncDragonZombie,
    (MonAiFunc)&CGMonObj::cancelStatFuncDragonZombie,
    (MonAiFunc)&CGMonObj::frameStatFuncDragonZombie,
    (MonAiFunc)&CGMonObj::logicFuncDefault,
    0,
    (MonAiFunc)&CGMonObj::calcBranchFuncDragonZombie,
    0,
    0,
    0,
    (MonAiFunc)&CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFunc DAT_80213a00[13] = {
    (MonAiFunc)&CGMonObj::initFinishedFuncDefault,
    (MonAiFunc)&CGMonObj::moveFrameFuncAntrion,
    (MonAiFunc)&CGMonObj::moveCancelFuncAntrion,
    (MonAiFunc)&CGMonObj::changeStatFuncAntrion,
    (MonAiFunc)&CGMonObj::cancelStatFuncAntrion,
    (MonAiFunc)&CGMonObj::frameStatFuncAntrion,
    (MonAiFunc)&CGMonObj::logicFuncDefault,
    0,
    (MonAiFunc)&CGMonObj::calcBranchFuncDefault,
    0,
    0,
    0,
    (MonAiFunc)&CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFunc DAT_80213b08[13] = {
    (MonAiFunc)&CGMonObj::initFinishedFuncDefault,
    (MonAiFunc)&CGMonObj::moveFrameFuncTetsukyojin,
    (MonAiFunc)&CGMonObj::moveCancelFuncTetsukyojin,
    (MonAiFunc)&CGMonObj::changeStatFuncTetsukyojin,
    (MonAiFunc)&CGMonObj::cancelStatFuncTetsukyojin,
    (MonAiFunc)&CGMonObj::frameStatFuncTetsukyojin,
    (MonAiFunc)&CGMonObj::logicFuncDefault,
    0,
    (MonAiFunc)&CGMonObj::calcBranchFuncTetsukyojin,
    0,
    0,
    0,
    (MonAiFunc)&CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFunc DAT_80213c10[13] = {
    (MonAiFunc)&CGMonObj::initFinishedFuncDefault,
    (MonAiFunc)&CGMonObj::moveFrameFuncLich,
    (MonAiFunc)&CGMonObj::moveCancelFuncLich,
    (MonAiFunc)&CGMonObj::changeStatFuncLich,
    (MonAiFunc)&CGMonObj::cancelStatFuncLich,
    (MonAiFunc)&CGMonObj::frameStatFuncLich,
    (MonAiFunc)&CGMonObj::logicFuncDefault,
    0,
    (MonAiFunc)&CGMonObj::calcBranchFuncLich,
    0,
    0,
    0,
    (MonAiFunc)&CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFunc DAT_80213d24[13] = {
    (MonAiFunc)&CGMonObj::initFinishedFuncDefault,
    (MonAiFunc)&CGMonObj::moveFrameFuncSaw,
    (MonAiFunc)&CGMonObj::moveCancelFuncDefault,
    (MonAiFunc)&CGMonObj::changeStatFuncDefault,
    (MonAiFunc)&CGMonObj::cancelStatFuncSaw,
    (MonAiFunc)&CGMonObj::frameStatFuncSaw,
    (MonAiFunc)&CGMonObj::logicFuncSaw,
    0,
    (MonAiFunc)&CGMonObj::calcBranchFuncDefault,
    0,
    (MonAiFunc)&CGMonObj::attackedFuncSaw,
    0,
    (MonAiFunc)&CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFunc DAT_80213e2c[13] = {
    (MonAiFunc)&CGMonObj::initFinishedFuncDefault,
    (MonAiFunc)&CGMonObj::moveFrameFuncRamoe,
    (MonAiFunc)&CGMonObj::moveCancelFuncRamoe,
    (MonAiFunc)&CGMonObj::changeStatFuncRamoe,
    (MonAiFunc)&CGMonObj::cancelStatFuncRamoe,
    (MonAiFunc)&CGMonObj::frameStatFuncRamoe,
    (MonAiFunc)&CGMonObj::logicFuncRamoe,
    0,
    (MonAiFunc)&CGMonObj::calcBranchFuncDefault,
    0,
    0,
    0,
    (MonAiFunc)&CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFunc DAT_80213f40[13] = {
    (MonAiFunc)&CGMonObj::initFinishedFuncLastBoss,
    (MonAiFunc)&CGMonObj::moveFrameFuncLastBoss,
    (MonAiFunc)&CGMonObj::moveCancelFuncLastBoss,
    (MonAiFunc)&CGMonObj::changeStatFuncLastBoss,
    (MonAiFunc)&CGMonObj::cancelStatFuncLastBoss,
    (MonAiFunc)&CGMonObj::frameStatFuncLastBoss,
    (MonAiFunc)&CGMonObj::logicFuncLastBoss,
    0,
    (MonAiFunc)&CGMonObj::calcBranchFuncLastBoss,
    (MonAiFunc)&CGMonObj::damagedFuncLastBoss,
    0,
    0,
    (MonAiFunc)&CGMonObj::alwaysFuncDefault,
};

extern "C" MonAiFunc DAT_80214054[13] = {
    (MonAiFunc)&CGMonObj::initFinishedFuncDefault,
    (MonAiFunc)&CGMonObj::moveFrameFuncDefault,
    (MonAiFunc)&CGMonObj::moveCancelFuncDefault,
    (MonAiFunc)&CGMonObj::changeStatFuncDefault,
    (MonAiFunc)&CGMonObj::cancelStatFuncDefault,
    (MonAiFunc)&CGMonObj::frameStatFuncLKShooter,
    (MonAiFunc)&CGMonObj::logicFuncDefault,
    0,
    (MonAiFunc)&CGMonObj::calcBranchFuncDefault,
    0,
    0,
    (MonAiFunc)&CGMonObj::attackCheckFuncLKShooter,
    (MonAiFunc)&CGMonObj::alwaysFuncDefault,
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

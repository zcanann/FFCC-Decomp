#include "ffcc/monobj_table.h"

extern "C" {
MonAiFuncTable funcsDefault = {
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

MonAiFuncTable funcsGiantCrab = {
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

MonAiFuncTable funcsOrcKing = {
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

MonAiFuncTable funcsGolem = {
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

MonAiFuncTable funcsArmstrong = {
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

MonAiFuncTable funcsGoblinKing = {
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

MonAiFuncTable funcsMolbol = {
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

MonAiFuncTable funcsLizardmanKing = {
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

MonAiFuncTable funcsCaveWorm = {
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

MonAiFuncTable funcsGigasLoad = {
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

MonAiFuncTable funcsWifeLamia = {
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

MonAiFuncTable funcsMeteoParasite = {
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

MonAiFuncTable funcsMeteoParasiteC = {
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

MonAiFuncTable funcsDuct = {
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

MonAiFuncTable funcsDragonZombie = {
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

MonAiFuncTable funcsAntrion = {
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

MonAiFuncTable funcsTetsukyojin = {
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

MonAiFuncTable funcsLich = {
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

MonAiFuncTable funcsSaw = {
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

MonAiFuncTable funcsRamoe = {
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

MonAiFuncTable funcsLastBoss = {
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

MonAiFuncTable funcsLKShooter = {
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
}

/*
 * --INFO--
 * PAL Address: 0x8015B23C
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveCancelFuncLastBoss()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B240
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveFrameFuncLastBoss()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B244
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveCancelFuncRamoe()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B248
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveFrameFuncRamoe()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B24C
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveCancelFuncLich()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B250
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveFrameFuncLich()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B254
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveCancelFuncTetsukyojin()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B258
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveFrameFuncTetsukyojin()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B25C
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncAntrion()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B260
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncAntrion()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B264
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncAntrion(int)
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B268
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveCancelFuncAntrion()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B26C
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveFrameFuncAntrion()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B270
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveCancelFuncDragonZombie()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B274
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveFrameFuncDragonZombie()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B278
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncDuct()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B27C
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncDuct()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B280
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncDuct(int)
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B284
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveCancelFuncDuct()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B288
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveFrameFuncDuct()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B28C
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncMeteoParasiteC()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B290
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncMeteoParasiteC(int)
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B294
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveCancelFuncMeteoParasiteC()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B298
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveFrameFuncMeteoParasiteC()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B29C
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncMeteoParasite()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B2A0
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveCancelFuncMeteoParasite()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B2A4
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveFrameFuncMeteoParasite()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B2A8
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncGigasLoad()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B2AC
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncGigasLoad()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B2B0
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncGigasLoad(int)
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B2B4
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveCancelFuncGigasLoad()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B2B8
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveFrameFuncGigasLoad()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B2BC
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveCancelFuncCaveWorm()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B2C0
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveFrameFuncCaveWorm()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B2C4
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncLizardmanKing()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B2C8
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncLizardmanKing()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B2CC
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncLizardmanKing(int)
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B2D0
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveCancelFuncLizardmanKing()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B2D4
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveFrameFuncLizardmanKing()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B2D8
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveCancelFuncMolbol()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B2DC
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveFrameFuncMolbol()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B2E0
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncGoblinKing(int)
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B2E4
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveCancelFuncGoblinKing()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B2E8
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveFrameFuncGoblinKing()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B2EC
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveCancelFuncArmstrong()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B2F0
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveFrameFuncArmstrong()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B2F4
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncGolem()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B2F8
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveCancelFuncGolem()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B2FC
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveFrameFuncGolem()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B300
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncOrcKing(int)
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B304
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncGiantCrab()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B308
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncGiantCrab(int)
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B30C
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveCancelFuncGiantCrab()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B310
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveFrameFuncGiantCrab()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B314
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::alwaysFuncDefault()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B318
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::frameStatFuncDefault()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B31C
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::cancelStatFuncDefault()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B320
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::changeStatFuncDefault(int)
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B324
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveCancelFuncDefault()
{
}

/*
 * --INFO--
 * PAL Address: 0x8015B328
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveFrameFuncDefault()
{
}

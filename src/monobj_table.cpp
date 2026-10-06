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
 * PAL Address: 0x801433B8
 * PAL Size: 4b
 * EN Address: 0x80142528
 * EN Size: 4b
 * JP Address: 0x8013F154
 * JP Size: 4b
 */
void CGMonObj::moveCancelFuncLastBoss()
{
}

/*
 * --INFO--
 * PAL Address: 0x801433BC
 * PAL Size: 4b
 * EN Address: 0x8014252C
 * EN Size: 4b
 * JP Address: 0x8013F158
 * JP Size: 4b
 */
void CGMonObj::moveFrameFuncLastBoss()
{
}

/*
 * --INFO--
 * PAL Address: 0x801433C0
 * PAL Size: 4b
 * EN Address: 0x80142530
 * EN Size: 4b
 * JP Address: 0x8013F15C
 * JP Size: 4b
 */
void CGMonObj::moveCancelFuncRamoe()
{
}

/*
 * --INFO--
 * PAL Address: 0x801433C4
 * PAL Size: 4b
 * EN Address: 0x80142534
 * EN Size: 4b
 * JP Address: 0x8013F160
 * JP Size: 4b
 */
void CGMonObj::moveFrameFuncRamoe()
{
}

/*
 * --INFO--
 * PAL Address: 0x801433C8
 * PAL Size: 4b
 * EN Address: 0x80142538
 * EN Size: 4b
 * JP Address: 0x8013F164
 * JP Size: 4b
 */
void CGMonObj::moveCancelFuncLich()
{
}

/*
 * --INFO--
 * PAL Address: 0x801433CC
 * PAL Size: 4b
 * EN Address: 0x8014253C
 * EN Size: 4b
 * JP Address: 0x8013F168
 * JP Size: 4b
 */
void CGMonObj::moveFrameFuncLich()
{
}

/*
 * --INFO--
 * PAL Address: 0x801433D0
 * PAL Size: 4b
 * EN Address: 0x80142540
 * EN Size: 4b
 * JP Address: 0x8013F16C
 * JP Size: 4b
 */
void CGMonObj::moveCancelFuncTetsukyojin()
{
}

/*
 * --INFO--
 * PAL Address: 0x801433D4
 * PAL Size: 4b
 * EN Address: 0x80142544
 * EN Size: 4b
 * JP Address: 0x8013F170
 * JP Size: 4b
 */
void CGMonObj::moveFrameFuncTetsukyojin()
{
}

/*
 * --INFO--
 * PAL Address: 0x801433D8
 * PAL Size: 4b
 * EN Address: 0x80142548
 * EN Size: 4b
 * JP Address: 0x8013F174
 * JP Size: 4b
 */
void CGMonObj::frameStatFuncAntrion()
{
}

/*
 * --INFO--
 * PAL Address: 0x801433DC
 * PAL Size: 4b
 * EN Address: 0x8014254C
 * EN Size: 4b
 * JP Address: 0x8013F178
 * JP Size: 4b
 */
void CGMonObj::cancelStatFuncAntrion()
{
}

/*
 * --INFO--
 * PAL Address: 0x801433E0
 * PAL Size: 4b
 * EN Address: 0x80142550
 * EN Size: 4b
 * JP Address: 0x8013F17C
 * JP Size: 4b
 */
void CGMonObj::changeStatFuncAntrion(int)
{
}

/*
 * --INFO--
 * PAL Address: 0x801433E4
 * PAL Size: 4b
 * EN Address: 0x80142554
 * EN Size: 4b
 * JP Address: 0x8013F180
 * JP Size: 4b
 */
void CGMonObj::moveCancelFuncAntrion()
{
}

/*
 * --INFO--
 * PAL Address: 0x801433E8
 * PAL Size: 4b
 * EN Address: 0x80142558
 * EN Size: 4b
 * JP Address: 0x8013F184
 * JP Size: 4b
 */
void CGMonObj::moveFrameFuncAntrion()
{
}

/*
 * --INFO--
 * PAL Address: 0x801433EC
 * PAL Size: 4b
 * EN Address: 0x8014255C
 * EN Size: 4b
 * JP Address: 0x8013F188
 * JP Size: 4b
 */
void CGMonObj::moveCancelFuncDragonZombie()
{
}

/*
 * --INFO--
 * PAL Address: 0x801433F0
 * PAL Size: 4b
 * EN Address: 0x80142560
 * EN Size: 4b
 * JP Address: 0x8013F18C
 * JP Size: 4b
 */
void CGMonObj::moveFrameFuncDragonZombie()
{
}

/*
 * --INFO--
 * PAL Address: 0x801433F4
 * PAL Size: 4b
 * EN Address: 0x80142564
 * EN Size: 4b
 * JP Address: 0x8013F190
 * JP Size: 4b
 */
void CGMonObj::frameStatFuncDuct()
{
}

/*
 * --INFO--
 * PAL Address: 0x801433F8
 * PAL Size: 4b
 * EN Address: 0x80142568
 * EN Size: 4b
 * JP Address: 0x8013F194
 * JP Size: 4b
 */
void CGMonObj::cancelStatFuncDuct()
{
}

/*
 * --INFO--
 * PAL Address: 0x801433FC
 * PAL Size: 4b
 * EN Address: 0x8014256C
 * EN Size: 4b
 * JP Address: 0x8013F198
 * JP Size: 4b
 */
void CGMonObj::changeStatFuncDuct(int)
{
}

/*
 * --INFO--
 * PAL Address: 0x80143400
 * PAL Size: 4b
 * EN Address: 0x80142570
 * EN Size: 4b
 * JP Address: 0x8013F19C
 * JP Size: 4b
 */
void CGMonObj::moveCancelFuncDuct()
{
}

/*
 * --INFO--
 * PAL Address: 0x80143404
 * PAL Size: 4b
 * EN Address: 0x80142574
 * EN Size: 4b
 * JP Address: 0x8013F1A0
 * JP Size: 4b
 */
void CGMonObj::moveFrameFuncDuct()
{
}

/*
 * --INFO--
 * PAL Address: 0x80143408
 * PAL Size: 4b
 * EN Address: 0x80142578
 * EN Size: 4b
 * JP Address: 0x8013F1A4
 * JP Size: 4b
 */
void CGMonObj::cancelStatFuncMeteoParasiteC()
{
}

/*
 * --INFO--
 * PAL Address: 0x8014340C
 * PAL Size: 4b
 * EN Address: 0x8014257C
 * EN Size: 4b
 * JP Address: 0x8013F1A8
 * JP Size: 4b
 */
void CGMonObj::changeStatFuncMeteoParasiteC(int)
{
}

/*
 * --INFO--
 * PAL Address: 0x80143410
 * PAL Size: 4b
 * EN Address: 0x80142580
 * EN Size: 4b
 * JP Address: 0x8013F1AC
 * JP Size: 4b
 */
void CGMonObj::moveCancelFuncMeteoParasiteC()
{
}

/*
 * --INFO--
 * PAL Address: 0x80143414
 * PAL Size: 4b
 * EN Address: 0x80142584
 * EN Size: 4b
 * JP Address: 0x8013F1B0
 * JP Size: 4b
 */
void CGMonObj::moveFrameFuncMeteoParasiteC()
{
}

/*
 * --INFO--
 * PAL Address: 0x80143418
 * PAL Size: 4b
 * EN Address: 0x80142588
 * EN Size: 4b
 * JP Address: 0x8013F1B4
 * JP Size: 4b
 */
void CGMonObj::cancelStatFuncMeteoParasite()
{
}

/*
 * --INFO--
 * PAL Address: 0x8014341C
 * PAL Size: 4b
 * EN Address: 0x8014258C
 * EN Size: 4b
 * JP Address: 0x8013F1B8
 * JP Size: 4b
 */
void CGMonObj::moveCancelFuncMeteoParasite()
{
}

/*
 * --INFO--
 * PAL Address: 0x80143420
 * PAL Size: 4b
 * EN Address: 0x80142590
 * EN Size: 4b
 * JP Address: 0x8013F1BC
 * JP Size: 4b
 */
void CGMonObj::moveFrameFuncMeteoParasite()
{
}

/*
 * --INFO--
 * PAL Address: 0x80143424
 * PAL Size: 4b
 * EN Address: 0x80142594
 * EN Size: 4b
 * JP Address: 0x8013F1C0
 * JP Size: 4b
 */
void CGMonObj::frameStatFuncGigasLoad()
{
}

/*
 * --INFO--
 * PAL Address: 0x80143428
 * PAL Size: 4b
 * EN Address: 0x80142598
 * EN Size: 4b
 * JP Address: 0x8013F1C4
 * JP Size: 4b
 */
void CGMonObj::cancelStatFuncGigasLoad()
{
}

/*
 * --INFO--
 * PAL Address: 0x8014342C
 * PAL Size: 4b
 * EN Address: 0x8014259C
 * EN Size: 4b
 * JP Address: 0x8013F1C8
 * JP Size: 4b
 */
void CGMonObj::changeStatFuncGigasLoad(int)
{
}

/*
 * --INFO--
 * PAL Address: 0x80143430
 * PAL Size: 4b
 * EN Address: 0x801425A0
 * EN Size: 4b
 * JP Address: 0x8013F1CC
 * JP Size: 4b
 */
void CGMonObj::moveCancelFuncGigasLoad()
{
}

/*
 * --INFO--
 * PAL Address: 0x80143434
 * PAL Size: 4b
 * EN Address: 0x801425A4
 * EN Size: 4b
 * JP Address: 0x8013F1D0
 * JP Size: 4b
 */
void CGMonObj::moveFrameFuncGigasLoad()
{
}

/*
 * --INFO--
 * PAL Address: 0x80143438
 * PAL Size: 4b
 * EN Address: 0x801425A8
 * EN Size: 4b
 * JP Address: 0x8013F1D4
 * JP Size: 4b
 */
void CGMonObj::moveCancelFuncCaveWorm()
{
}

/*
 * --INFO--
 * PAL Address: 0x8014343C
 * PAL Size: 4b
 * EN Address: 0x801425AC
 * EN Size: 4b
 * JP Address: 0x8013F1D8
 * JP Size: 4b
 */
void CGMonObj::moveFrameFuncCaveWorm()
{
}

/*
 * --INFO--
 * PAL Address: 0x80143440
 * PAL Size: 4b
 * EN Address: 0x801425B0
 * EN Size: 4b
 * JP Address: 0x8013F1DC
 * JP Size: 4b
 */
void CGMonObj::frameStatFuncLizardmanKing()
{
}

/*
 * --INFO--
 * PAL Address: 0x80143444
 * PAL Size: 4b
 * EN Address: 0x801425B4
 * EN Size: 4b
 * JP Address: 0x8013F1E0
 * JP Size: 4b
 */
void CGMonObj::cancelStatFuncLizardmanKing()
{
}

/*
 * --INFO--
 * PAL Address: 0x80143448
 * PAL Size: 4b
 * EN Address: 0x801425B8
 * EN Size: 4b
 * JP Address: 0x8013F1E4
 * JP Size: 4b
 */
void CGMonObj::changeStatFuncLizardmanKing(int)
{
}

/*
 * --INFO--
 * PAL Address: 0x8014344C
 * PAL Size: 4b
 * EN Address: 0x801425BC
 * EN Size: 4b
 * JP Address: 0x8013F1E8
 * JP Size: 4b
 */
void CGMonObj::moveCancelFuncLizardmanKing()
{
}

/*
 * --INFO--
 * PAL Address: 0x80143450
 * PAL Size: 4b
 * EN Address: 0x801425C0
 * EN Size: 4b
 * JP Address: 0x8013F1EC
 * JP Size: 4b
 */
void CGMonObj::moveFrameFuncLizardmanKing()
{
}

/*
 * --INFO--
 * PAL Address: 0x80143454
 * PAL Size: 4b
 * EN Address: 0x801425C4
 * EN Size: 4b
 * JP Address: 0x8013F1F0
 * JP Size: 4b
 */
void CGMonObj::moveCancelFuncMolbol()
{
}

/*
 * --INFO--
 * PAL Address: 0x80143458
 * PAL Size: 4b
 * EN Address: 0x801425C8
 * EN Size: 4b
 * JP Address: 0x8013F1F4
 * JP Size: 4b
 */
void CGMonObj::moveFrameFuncMolbol()
{
}

/*
 * --INFO--
 * PAL Address: 0x8014345C
 * PAL Size: 4b
 * EN Address: 0x801425CC
 * EN Size: 4b
 * JP Address: 0x8013F1F8
 * JP Size: 4b
 */
void CGMonObj::changeStatFuncGoblinKing(int)
{
}

/*
 * --INFO--
 * PAL Address: 0x80143460
 * PAL Size: 4b
 * EN Address: 0x801425D0
 * EN Size: 4b
 * JP Address: 0x8013F1FC
 * JP Size: 4b
 */
void CGMonObj::moveCancelFuncGoblinKing()
{
}

/*
 * --INFO--
 * PAL Address: 0x80143464
 * PAL Size: 4b
 * EN Address: 0x801425D4
 * EN Size: 4b
 * JP Address: 0x8013F200
 * JP Size: 4b
 */
void CGMonObj::moveFrameFuncGoblinKing()
{
}

/*
 * --INFO--
 * PAL Address: 0x80143468
 * PAL Size: 4b
 * EN Address: 0x801425D8
 * EN Size: 4b
 * JP Address: 0x8013F204
 * JP Size: 4b
 */
void CGMonObj::moveCancelFuncArmstrong()
{
}

/*
 * --INFO--
 * PAL Address: 0x8014346C
 * PAL Size: 4b
 * EN Address: 0x801425DC
 * EN Size: 4b
 * JP Address: 0x8013F208
 * JP Size: 4b
 */
void CGMonObj::moveFrameFuncArmstrong()
{
}

/*
 * --INFO--
 * PAL Address: 0x80143470
 * PAL Size: 4b
 * EN Address: 0x801425E0
 * EN Size: 4b
 * JP Address: 0x8013F20C
 * JP Size: 4b
 */
void CGMonObj::cancelStatFuncGolem()
{
}

/*
 * --INFO--
 * PAL Address: 0x80143474
 * PAL Size: 4b
 * EN Address: 0x801425E4
 * EN Size: 4b
 * JP Address: 0x8013F210
 * JP Size: 4b
 */
void CGMonObj::moveCancelFuncGolem()
{
}

/*
 * --INFO--
 * PAL Address: 0x80143478
 * PAL Size: 4b
 * EN Address: 0x801425E8
 * EN Size: 4b
 * JP Address: 0x8013F214
 * JP Size: 4b
 */
void CGMonObj::moveFrameFuncGolem()
{
}

/*
 * --INFO--
 * PAL Address: 0x8014347C
 * PAL Size: 4b
 * EN Address: 0x801425EC
 * EN Size: 4b
 * JP Address: 0x8013F218
 * JP Size: 4b
 */
void CGMonObj::changeStatFuncOrcKing(int)
{
}

/*
 * --INFO--
 * PAL Address: 0x80143480
 * PAL Size: 4b
 * EN Address: 0x801425F0
 * EN Size: 4b
 * JP Address: 0x8013F21C
 * JP Size: 4b
 */
void CGMonObj::cancelStatFuncGiantCrab()
{
}

/*
 * --INFO--
 * PAL Address: 0x80143484
 * PAL Size: 4b
 * EN Address: 0x801425F4
 * EN Size: 4b
 * JP Address: 0x8013F220
 * JP Size: 4b
 */
void CGMonObj::changeStatFuncGiantCrab(int)
{
}

/*
 * --INFO--
 * PAL Address: 0x80143488
 * PAL Size: 4b
 * EN Address: 0x801425F8
 * EN Size: 4b
 * JP Address: 0x8013F224
 * JP Size: 4b
 */
void CGMonObj::moveCancelFuncGiantCrab()
{
}

/*
 * --INFO--
 * PAL Address: 0x8014348C
 * PAL Size: 4b
 * EN Address: 0x801425FC
 * EN Size: 4b
 * JP Address: 0x8013F228
 * JP Size: 4b
 */
void CGMonObj::moveFrameFuncGiantCrab()
{
}

/*
 * --INFO--
 * PAL Address: 0x80143490
 * PAL Size: 4b
 * EN Address: 0x80142600
 * EN Size: 4b
 * JP Address: 0x8013F22C
 * JP Size: 4b
 */
void CGMonObj::alwaysFuncDefault()
{
}

/*
 * --INFO--
 * PAL Address: 0x80143494
 * PAL Size: 4b
 * EN Address: 0x80142604
 * EN Size: 4b
 * JP Address: 0x8013F230
 * JP Size: 4b
 */
void CGMonObj::frameStatFuncDefault()
{
}

/*
 * --INFO--
 * PAL Address: 0x80143498
 * PAL Size: 4b
 * EN Address: 0x80142608
 * EN Size: 4b
 * JP Address: 0x8013F234
 * JP Size: 4b
 */
void CGMonObj::cancelStatFuncDefault()
{
}

/*
 * --INFO--
 * PAL Address: 0x8014349C
 * PAL Size: 4b
 * EN Address: 0x8014260C
 * EN Size: 4b
 * JP Address: 0x8013F238
 * JP Size: 4b
 */
void CGMonObj::changeStatFuncDefault(int)
{
}

/*
 * --INFO--
 * PAL Address: 0x801434A0
 * PAL Size: 4b
 * EN Address: 0x80142610
 * EN Size: 4b
 * JP Address: 0x8013F23C
 * JP Size: 4b
 */
void CGMonObj::moveCancelFuncDefault()
{
}

/*
 * --INFO--
 * PAL Address: 0x801434A4
 * PAL Size: 4b
 * EN Address: 0x80142614
 * EN Size: 4b
 * JP Address: 0x8013F240
 * JP Size: 4b
 */
void CGMonObj::moveFrameFuncDefault()
{
}

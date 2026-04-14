#ifndef _FFCC_MONOBJ_TABLE_H_
#define _FFCC_MONOBJ_TABLE_H_

class CGMonObj;

class CGMonObj
{
public:
    void initFinishedFuncDefault();
    void logicFuncDefault();
    int calcBranchFuncDefault(int);

    void alwaysFuncDefault();
    void alwaysFuncMeteoParasite();
    void alwaysFuncOrcKing();
    void attackCheckFuncLKShooter(int);
    void attackCheckFuncMeteoParasite(int);
    void attackCheckFuncMeteoParasiteC(int);
    void attackedFuncSaw();
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
    void frameStatFuncDefault();
    void cancelStatFuncDefault();
    void changeStatFuncDefault(int);
    void moveCancelFuncDefault();
    void moveFrameFuncDefault();

    void cancelStatFuncGiantCrab();
    void changeStatFuncGiantCrab(int);
    void damagedFuncGiantCrab();
    void frameStatFuncGiantCrab();
    void logicFuncGiantCrab();
    void moveCancelFuncGiantCrab();
    void moveFrameFuncGiantCrab();

    void changeStatFuncOrcKing(int);
    void cancelStatFuncOrcKing();
    void frameStatFuncOrcKing();
    void moveCancelFuncOrcKing();
    void moveFrameFuncOrcKing();

    void changeStatFuncGolem(int);
    void cancelStatFuncGolem();
    void damagedFuncGolem();
    void frameStatFuncGolem();
    void moveCancelFuncGolem();
    void moveFrameFuncGolem();

    void changeStatFuncArmstrong(int);
    void cancelStatFuncArmstrong();
    void frameStatFuncArmstrong();
    void moveCancelFuncArmstrong();
    void moveFrameFuncArmstrong();

    void changeStatFuncGoblinKing(int);
    void cancelStatFuncGoblinKing();
    void frameStatFuncGoblinKing();
    void moveCancelFuncGoblinKing();
    void moveFrameFuncGoblinKing();

    void changeStatFuncMolbol(int);
    void cancelStatFuncMolbol();
    void frameStatFuncMolbol();
    void moveCancelFuncMolbol();
    void moveFrameFuncMolbol();

    void frameStatFuncLizardmanKing();
    void cancelStatFuncLizardmanKing();
    void changeStatFuncLizardmanKing(int);
    void moveCancelFuncLizardmanKing();
    void moveFrameFuncLizardmanKing();

    void changeStatFuncCaveWorm(int);
    void cancelStatFuncCaveWorm();
    void frameStatFuncCaveWorm();
    void moveCancelFuncCaveWorm();
    void moveFrameFuncCaveWorm();

    void changeStatFuncGigasLoad(int);
    void frameStatFuncGigasLoad();
    void cancelStatFuncGigasLoad();
    void damagedFuncGigasLoad();
    void tgtFuncGigasLoad(int);
    void moveCancelFuncGigasLoad();
    void moveFrameFuncGigasLoad();

    void changeStatFuncMeteoParasite(int);
    void cancelStatFuncMeteoParasite();
    void frameStatFuncMeteoParasite();
    void initFinishedFuncMeteoParasite();
    void logicFuncMeteoParasite();
    void moveCancelFuncMeteoParasite();
    void moveFrameFuncMeteoParasite();

    void cancelStatFuncMeteoParasiteC();
    void changeStatFuncMeteoParasiteC(int);
    void damagedFuncMeteoParasiteC();
    void frameStatFuncMeteoParasiteC();
    void initFinishedFuncMeteoParasiteC();
    void logicFuncMeteoParasiteC();
    void moveCancelFuncMeteoParasiteC();
    void moveFrameFuncMeteoParasiteC();

    void changeStatFuncDuct(int);
    void frameStatFuncDuct();
    void cancelStatFuncDuct();
    void damagedFuncDuct();
    void initFinishedFuncDuct();
    void moveCancelFuncDuct();
    void moveFrameFuncDuct();

    void changeStatFuncDragonZombie(int);
    void cancelStatFuncDragonZombie();
    void frameStatFuncDragonZombie();
    void moveCancelFuncDragonZombie();
    void moveFrameFuncDragonZombie();

    void frameStatFuncAntrion();
    void cancelStatFuncAntrion();
    void changeStatFuncAntrion(int);
    void moveCancelFuncAntrion();
    void moveFrameFuncAntrion();

    void changeStatFuncTetsukyojin(int);
    void cancelStatFuncTetsukyojin();
    void frameStatFuncTetsukyojin();
    void moveCancelFuncTetsukyojin();
    void moveFrameFuncTetsukyojin();

    void changeStatFuncLich(int);
    void cancelStatFuncLich();
    void frameStatFuncLich();
    void moveCancelFuncLich();
    void moveFrameFuncLich();

    void cancelStatFuncSaw();
    void frameStatFuncSaw();
    void logicFuncSaw();
    void moveFrameFuncSaw();

    void changeStatFuncRamoe(int);
    void cancelStatFuncRamoe();
    void frameStatFuncRamoe();
    void logicFuncRamoe();
    void moveCancelFuncRamoe();
    void moveFrameFuncRamoe();

    void changeStatFuncLastBoss(int);
    void cancelStatFuncLastBoss();
    void damagedFuncLastBoss();
    void frameStatFuncLastBoss();
    void initFinishedFuncLastBoss();
    void logicFuncLastBoss();
    void moveCancelFuncLastBoss();
    void moveFrameFuncLastBoss();

    void damagedFuncWifeLamia();
    void frameStatFuncWifeLamia();
    void frameStatFuncLKShooter();
};

#endif // _FFCC_MONOBJ_TABLE_H_

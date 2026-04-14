#ifndef _FFCC_MONOBJ_BOSS_H_
#define _FFCC_MONOBJ_BOSS_H_

struct Vec;
class CGObject;

class CGMonObj
{
public:
    void damagedFuncGiantCrab();
    void logicFuncGiantCrab();
    int calcBranchFuncGiantCrab(int);
    void frameStatFuncGiantCrab();

    void damagedFuncGolem();
    void changeStatFuncGolem(int);
    int calcBranchFuncGolem(int);
    void frameStatFuncGolem();

    void changeStatFuncArmstrong(int);
    void cancelStatFuncArmstrong();
    void frameStatFuncArmstrong();

    void cancelStatFuncOrcKing();
    void frameStatFuncOrcKing();
    void alwaysFuncOrcKing();
    void moveFrameFuncOrcKing();
    void moveCancelFuncOrcKing();
    int calcBranchFuncOrcKing(int);

    void cancelStatFuncGoblinKing();
    void frameStatFuncGoblinKing();
    int calcBranchFuncGoblinKing(int);

    void cancelStatFuncSaw();
    void frameStatFuncSaw();
    void logicFuncSaw();
    void moveFrameFuncSaw();
    void attackedFuncSaw();

    void frameStatFuncLKShooter();
    void attackCheckFuncLKShooter(int);

    void changeStatFuncDragonZombie(int);
    void cancelStatFuncDragonZombie();
    void frameStatFuncDragonZombie();
    int calcBranchFuncDragonZombie(int);

    void changeStatFuncCaveWorm(int);
    void cancelStatFuncCaveWorm();
    void frameStatFuncCaveWorm();

    void changeStatFuncLich(int);
    void cancelStatFuncLich();
    void frameStatFuncLich();
    int calcBranchFuncLich(int);

    void changeStatFuncTetsukyojin(int);
    void cancelStatFuncTetsukyojin();
    void frameStatFuncTetsukyojin();
    int calcBranchFuncTetsukyojin(int);

    void damagedFuncGigasLoad();
    void tgtFuncGigasLoad(int);
    int calcBranchFuncGigasLoad(int);

    void frameStatFuncWifeLamia();
    void damagedFuncWifeLamia();

    void changeStatFuncMolbol(int);
    void cancelStatFuncMolbol();
    void frameStatFuncMolbol();

    void initFinishedFuncMeteoParasiteC();
    void damagedFuncMeteoParasiteC();
    void frameStatFuncMeteoParasiteC();
    int calcBranchFuncMeteoParasiteC(int);
    void logicFuncMeteoParasiteC();
    void attackCheckFuncMeteoParasiteC(int);

    void initFinishedFuncMeteoParasite();
    void changeStatFuncMeteoParasite(int);
    void alwaysFuncMeteoParasite();
    void frameStatFuncMeteoParasite();
    void logicFuncMeteoParasite();
    void attackCheckFuncMeteoParasite(int);

    void aiAddDuct(int&);
    void initFinishedFuncDuct();
    void damagedFuncDuct();

    void logicFuncRamoe();
    void changeStatFuncRamoe(int);
    void cancelStatFuncRamoe();
    void frameStatFuncRamoe();

    void initFinishedFuncLastBoss();
    void damagedFuncLastBoss();
    void changeStatFuncLastBoss(int);
    void cancelStatFuncLastBoss();
    void frameStatFuncLastBoss();
    int calcBranchFuncLastBoss(int);
    void logicFuncLastBoss();

    void teleport(int, int, int, int, int, int, int, int, int, Vec*, int&, Vec&);
    void suikomiSub(CGObject*, float);
    void suikomi(int, float);
};

#endif // _FFCC_MONOBJ_BOSS_H_

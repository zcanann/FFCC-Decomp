#ifndef _FFCC_MONOBJ_TABLE_H_
#define _FFCC_MONOBJ_TABLE_H_

class CGMonObj;

class CGMonObj
{
public:
    void alwaysFuncDefault();
    void frameStatFuncDefault();
    void cancelStatFuncDefault();
    void changeStatFuncDefault(int);
    void moveCancelFuncDefault();
    void moveFrameFuncDefault();

    void cancelStatFuncGiantCrab();
    void changeStatFuncGiantCrab(int);
    void moveCancelFuncGiantCrab();
    void moveFrameFuncGiantCrab();

    void changeStatFuncOrcKing(int);

    void cancelStatFuncGolem();
    void moveCancelFuncGolem();
    void moveFrameFuncGolem();

    void moveCancelFuncArmstrong();
    void moveFrameFuncArmstrong();

    void changeStatFuncGoblinKing(int);
    void moveCancelFuncGoblinKing();
    void moveFrameFuncGoblinKing();

    void moveCancelFuncMolbol();
    void moveFrameFuncMolbol();

    void frameStatFuncLizardmanKing();
    void cancelStatFuncLizardmanKing();
    void changeStatFuncLizardmanKing(int);
    void moveCancelFuncLizardmanKing();
    void moveFrameFuncLizardmanKing();

    void moveCancelFuncCaveWorm();
    void moveFrameFuncCaveWorm();

    void frameStatFuncGigasLoad();
    void cancelStatFuncGigasLoad();
    void changeStatFuncGigasLoad(int);
    void moveCancelFuncGigasLoad();
    void moveFrameFuncGigasLoad();

    void cancelStatFuncMeteoParasite();
    void moveCancelFuncMeteoParasite();
    void moveFrameFuncMeteoParasite();

    void cancelStatFuncMeteoParasiteC();
    void changeStatFuncMeteoParasiteC(int);
    void moveCancelFuncMeteoParasiteC();
    void moveFrameFuncMeteoParasiteC();

    void frameStatFuncDuct();
    void cancelStatFuncDuct();
    void changeStatFuncDuct(int);
    void moveCancelFuncDuct();
    void moveFrameFuncDuct();

    void moveCancelFuncDragonZombie();
    void moveFrameFuncDragonZombie();

    void frameStatFuncAntrion();
    void cancelStatFuncAntrion();
    void changeStatFuncAntrion(int);
    void moveCancelFuncAntrion();
    void moveFrameFuncAntrion();

    void moveCancelFuncTetsukyojin();
    void moveFrameFuncTetsukyojin();

    void moveCancelFuncLich();
    void moveFrameFuncLich();

    void moveCancelFuncRamoe();
    void moveFrameFuncRamoe();

    void moveCancelFuncLastBoss();
    void moveFrameFuncLastBoss();
};

#endif // _FFCC_MONOBJ_TABLE_H_

// Function: DrawSingLife__8CMenuPcsFv
// Entry: 80145738
// Size: 420 bytes

/* WARNING: Removing unreachable block (ram,0x801458c0) */
/* WARNING: Removing unreachable block (ram,0x801458b8) */
/* WARNING: Removing unreachable block (ram,0x80145750) */
/* WARNING: Removing unreachable block (ram,0x80145748) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawSingLife__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  uint32_t uVar2;
  uint uVar3;
  uint uVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  
  uVar2 = Game.game.m_scriptFoodBase[0];
  uVar4 = *(uint *)&menuPcs->field_0x874;
  dVar7 = (double)FLOAT_80332918;
  dVar6 = (double)FLOAT_8033291c;
  if (-1 < (int)uVar4) {
    if ((int)uVar4 < 10) {
      if ((int)uVar4 < 0) {
        uVar3 = 0;
      }
      else {
        uVar3 = 10;
        if ((int)uVar4 < 0xb) {
          uVar3 = uVar4;
        }
      }
      dVar5 = (double)sin((double)(FLOAT_80332920 *
                                  FLOAT_80332924 *
                                  (float)((double)CONCAT44(0x43300000,uVar3 ^ 0x80000000) -
                                         DOUBLE_80332938)));
      fVar1 = (float)((double)FLOAT_80332928 * (double)(float)dVar5 + dVar6);
    }
    else {
      fVar1 = FLOAT_8033292c;
      if (0x27 < (int)uVar4) {
        uVar4 = 10 - (uVar4 - 0x28);
        if ((int)uVar4 < 0) {
          uVar3 = 0;
        }
        else {
          uVar3 = 10;
          if ((int)uVar4 < 0xb) {
            uVar3 = uVar4;
          }
        }
        dVar5 = (double)sin((double)(FLOAT_80332920 *
                                    FLOAT_80332924 *
                                    (float)((double)CONCAT44(0x43300000,uVar3 ^ 0x80000000) -
                                           DOUBLE_80332938)));
        fVar1 = (float)((double)FLOAT_80332928 * (double)(float)dVar5 + dVar6);
      }
    }
    DrawHeart__8CMesMenuFffff
              ((double)(float)(dVar7 + (double)(float)((double)CONCAT44(0x43300000,
                                                                        (int)((8 - (uint)(*(ushort *
                                                  )(uVar2 + 0x1a) >> 1)) * 0x18) / 2 ^ 0x80000000) -
                                                  DOUBLE_80332938)),(double)(fVar1 - FLOAT_80332930)
               ,(double)FLOAT_80332934,(double)FLOAT_80332934,MenuPcs._268_4_);
  }
  return;
}


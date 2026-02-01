// Function: CalcListPos__8CMenuPcsFiii
// Entry: 8014744c
// Size: 164 bytes

double CalcListPos__8CMenuPcsFiii(CMenuPcs *menuPcs,uint param_2,int param_3,int param_4)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  if (param_4 == 0) {
    uVar3 = param_3 - 8;
  }
  else {
    uVar3 = param_3 - 1;
  }
  fVar1 = (float)((double)CONCAT44(0x43300000,uVar3 ^ 0x80000000) - DOUBLE_80332938);
  fVar2 = FLOAT_8033299c;
  if ((FLOAT_8033294c < fVar1) && (8 < param_3)) {
    fVar2 = FLOAT_803329a0 *
            ((float)((double)CONCAT44(0x43300000,param_2 ^ 0x80000000) - DOUBLE_80332938) / fVar1) +
            FLOAT_8033292c;
  }
  return (double)fVar2;
}


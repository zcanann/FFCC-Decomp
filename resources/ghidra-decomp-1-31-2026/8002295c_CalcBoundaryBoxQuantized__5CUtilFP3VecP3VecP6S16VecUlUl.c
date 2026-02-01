// Function: CalcBoundaryBoxQuantized__5CUtilFP3VecP3VecP6S16VecUlUl
// Entry: 8002295c
// Size: 548 bytes

void CalcBoundaryBoxQuantized__5CUtilFP3VecP3VecP6S16VecUlUl
               (CUtil *util,float *param_2,float *param_3,S16Vec *s16Vec,int param_5,int param_6)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  uint uVar8;
  short local_78;
  short sStack_76;
  short local_74;
  short local_70;
  short sStack_6e;
  short local_6c;
  
  dVar4 = DOUBLE_8032f890;
  local_6c = 0x7fff;
  sStack_6e = 0x7fff;
  sVar7 = sStack_6e;
  sStack_6e = 0x7fff;
  local_70 = 0x7fff;
  local_74 = -0x7fff;
  sStack_76 = -0x7fff;
  sVar5 = sStack_76;
  sStack_76 = -0x7fff;
  local_78 = -0x7fff;
  if (param_5 != 0) {
    do {
      sVar5 = s16Vec->x;
      if (local_70 < s16Vec->x) {
        sVar5 = local_70;
      }
      sVar7 = s16Vec->y;
      if (sStack_6e < s16Vec->y) {
        sVar7 = sStack_6e;
      }
      sVar6 = s16Vec->z;
      if (local_6c < s16Vec->z) {
        sVar6 = local_6c;
      }
      if (local_78 < s16Vec->x) {
        local_78 = s16Vec->x;
      }
      if (sStack_76 < s16Vec->y) {
        sStack_76 = s16Vec->y;
      }
      if (local_74 < s16Vec->z) {
        local_74 = s16Vec->z;
      }
      s16Vec = s16Vec + 1;
      param_5 = param_5 + -1;
      local_6c = sVar6;
      sStack_6e = sVar7;
      local_70 = sVar5;
      sVar5 = sStack_76;
    } while (param_5 != 0);
  }
  sStack_76 = sVar5;
  sStack_6e = sVar7;
  uVar8 = 1 << param_6 ^ 0x80000000;
  dVar1 = (double)CONCAT44(0x43300000,(int)sStack_6e ^ 0x80000000) - DOUBLE_8032f890;
  dVar2 = (double)CONCAT44(0x43300000,uVar8) - DOUBLE_8032f890;
  dVar3 = (double)CONCAT44(0x43300000,(int)local_6c ^ 0x80000000) - DOUBLE_8032f890;
  *param_2 = (float)((double)CONCAT44(0x43300000,(int)local_70 ^ 0x80000000) - DOUBLE_8032f890) /
             (float)((double)CONCAT44(0x43300000,uVar8) - DOUBLE_8032f890);
  param_2[1] = (float)dVar1 / (float)dVar2;
  param_2[2] = (float)dVar3 / (float)((double)CONCAT44(0x43300000,uVar8) - dVar4);
  *param_3 = (float)((double)CONCAT44(0x43300000,(int)local_78 ^ 0x80000000) - dVar4) /
             (float)((double)CONCAT44(0x43300000,uVar8) - dVar4);
  param_3[1] = (float)((double)CONCAT44(0x43300000,(int)sStack_76 ^ 0x80000000) - dVar4) /
               (float)((double)CONCAT44(0x43300000,uVar8) - dVar4);
  param_3[2] = (float)((double)CONCAT44(0x43300000,(int)local_74 ^ 0x80000000) - dVar4) /
               (float)((double)CONCAT44(0x43300000,uVar8) - dVar4);
  return;
}


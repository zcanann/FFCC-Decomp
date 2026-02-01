// Function: DrawRect3d__8CMenuPcsFUlfffffffff
// Entry: 800eab98
// Size: 508 bytes

/* WARNING: Removing unreachable block (ram,0x800ead7c) */
/* WARNING: Removing unreachable block (ram,0x800ead74) */
/* WARNING: Removing unreachable block (ram,0x800ead6c) */
/* WARNING: Removing unreachable block (ram,0x800ead64) */
/* WARNING: Removing unreachable block (ram,0x800eabc0) */
/* WARNING: Removing unreachable block (ram,0x800eabb8) */
/* WARNING: Removing unreachable block (ram,0x800eabb0) */
/* WARNING: Removing unreachable block (ram,0x800eaba8) */
/* WARNING: Removing unreachable block (ram,0x800eace4) */

void DrawRect3d__8CMenuPcsFUlfffffffff
               (double param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9_00,uint param_10)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  double in_f28;
  double dVar6;
  double in_f29;
  double dVar7;
  double in_f30;
  double dVar8;
  double in_f31;
  double dVar9;
  double in_ps28_1;
  double in_ps29_1;
  double in_ps30_1;
  double in_ps31_1;
  float param_9;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_38;
  float fStack_34;
  float local_28;
  float fStack_24;
  float local_18;
  float fStack_14;
  float local_8;
  float fStack_4;
  
  local_8 = (float)in_f31;
  fStack_4 = (float)in_ps31_1;
  local_18 = (float)in_f30;
  fStack_14 = (float)in_ps30_1;
  local_28 = (float)in_f29;
  fStack_24 = (float)in_ps29_1;
  local_38 = (float)in_f28;
  fStack_34 = (float)in_ps28_1;
  if (((double)FLOAT_803313dc < param_4) && ((double)FLOAT_803313dc < param_5)) {
    if ((param_10 & 8) == 0) {
      dVar7 = param_6 + (double)FLOAT_80331434;
      dVar6 = (double)(float)(param_6 + param_4) - (double)FLOAT_80331434;
    }
    else {
      dVar6 = (double)FLOAT_80331434 + param_6;
      dVar7 = (double)(float)(param_6 + param_4) - (double)FLOAT_80331434;
    }
    dVar9 = (double)(float)dVar6;
    dVar6 = (double)(float)dVar7;
    if ((param_10 & 4) == 0) {
      dVar7 = param_7 + (double)FLOAT_80331434;
      dVar8 = (double)(float)((double)(float)(param_7 + param_5) - (double)FLOAT_80331434);
    }
    else {
      dVar8 = (double)(float)((double)FLOAT_80331434 + param_7);
      dVar7 = (double)(float)(dVar8 + param_5) - (double)FLOAT_80331434;
    }
    dVar7 = (double)(float)dVar7;
    if ((param_10 & 1) != 0) {
      param_1 = -(double)(float)((double)FLOAT_80331434 * (double)(float)(param_4 * param_8) -
                                param_1);
    }
    if ((param_10 & 2) != 0) {
      param_2 = -(double)(float)((double)FLOAT_80331434 * (double)(float)(param_5 * (double)param_9)
                                - param_2);
    }
    local_6c = (float)(param_1 + (double)(float)(param_4 * param_8));
    local_78 = (float)param_1;
    local_5c = (float)(param_2 + (double)(float)(param_5 * (double)param_9));
    local_74 = (float)param_2;
    local_70 = (float)param_3;
    local_68 = (float)param_2;
    local_64 = (float)param_3;
    local_60 = (float)param_1;
    local_58 = (float)param_3;
    local_4c = (float)param_3;
    local_54 = local_6c;
    local_50 = local_5c;
    GXBegin(0x98,0,4);
    pfVar1 = &local_78;
    iVar2 = 0;
    iVar3 = 2;
    do {
      DAT_cc008000 = *pfVar1;
      DAT_cc008000 = pfVar1[1];
      DAT_cc008000 = pfVar1[2];
      dVar4 = dVar7;
      if (iVar2 < 2) {
        dVar4 = dVar8;
      }
      DAT_cc008000 = (float)dVar6;
      DAT_cc008000 = (float)dVar4;
      DAT_cc008000 = pfVar1[3];
      DAT_cc008000 = pfVar1[4];
      DAT_cc008000 = pfVar1[5];
      dVar4 = dVar6;
      if ((iVar2 + 1U & 1) != 0) {
        dVar4 = dVar9;
      }
      dVar5 = dVar7;
      if ((int)(iVar2 + 1U) < 2) {
        dVar5 = dVar8;
      }
      DAT_cc008000 = (float)dVar4;
      pfVar1 = pfVar1 + 6;
      iVar2 = iVar2 + 2;
      DAT_cc008000 = (float)dVar5;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  return;
}


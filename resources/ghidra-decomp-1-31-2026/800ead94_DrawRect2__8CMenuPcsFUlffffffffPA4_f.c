// Function: DrawRect2__8CMenuPcsFUlffffffffPA4_f
// Entry: 800ead94
// Size: 524 bytes

/* WARNING: Removing unreachable block (ram,0x800eaf88) */
/* WARNING: Removing unreachable block (ram,0x800eaf80) */
/* WARNING: Removing unreachable block (ram,0x800eaf78) */
/* WARNING: Removing unreachable block (ram,0x800eaf70) */
/* WARNING: Removing unreachable block (ram,0x800eadbc) */
/* WARNING: Removing unreachable block (ram,0x800eadb4) */
/* WARNING: Removing unreachable block (ram,0x800eadac) */
/* WARNING: Removing unreachable block (ram,0x800eada4) */
/* WARNING: Removing unreachable block (ram,0x800eaef4) */

void DrawRect2__8CMenuPcsFUlffffffffPA4_f
               (double param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,uint param_10,
               Mtx *param_11)

{
  undefined4 *puVar1;
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
  undefined4 local_a8 [12];
  Vec local_78;
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
  if (((double)FLOAT_803313dc < param_3) && ((double)FLOAT_803313dc < param_4)) {
    if ((param_10 & 8) == 0) {
      dVar8 = param_5 + (double)FLOAT_80331434;
      dVar7 = (double)(float)(param_5 + param_3) - (double)FLOAT_80331434;
    }
    else {
      dVar7 = (double)FLOAT_80331434 + param_5;
      dVar8 = (double)(float)(param_5 + param_3) - (double)FLOAT_80331434;
    }
    dVar9 = (double)(float)dVar7;
    dVar7 = (double)(float)dVar8;
    if ((param_10 & 4) == 0) {
      dVar8 = param_6 + (double)FLOAT_80331434;
      dVar6 = (double)(float)((double)(float)(param_6 + param_4) - (double)FLOAT_80331434);
    }
    else {
      dVar6 = (double)(float)((double)FLOAT_80331434 + param_6);
      dVar8 = (double)(float)(dVar6 + param_4) - (double)FLOAT_80331434;
    }
    dVar8 = (double)(float)dVar8;
    if ((param_10 & 1) != 0) {
      param_1 = -(double)(float)((double)FLOAT_80331434 * (double)(float)(param_3 * param_7) -
                                param_1);
    }
    if ((param_10 & 2) != 0) {
      param_2 = -(double)(float)((double)FLOAT_80331434 * (double)(float)(param_4 * param_8) -
                                param_2);
    }
    local_6c = (float)(param_1 + (double)(float)(param_3 * param_7));
    local_5c = (float)(param_2 + (double)(float)(param_4 * param_8));
    local_78.x = (float)param_1;
    local_78.y = (float)param_2;
    local_78.z = FLOAT_803313dc;
    local_68 = (float)param_2;
    local_64 = FLOAT_803313dc;
    local_60 = (float)param_1;
    local_58 = FLOAT_803313dc;
    local_4c = FLOAT_803313dc;
    local_54 = local_6c;
    local_50 = local_5c;
    PSMTXMultVecArray(param_11,&local_78,local_a8,4);
    GXBegin(0x98,0,4);
    puVar1 = local_a8;
    iVar2 = 0;
    iVar3 = 2;
    do {
      DAT_cc008000 = *puVar1;
      DAT_cc008000 = puVar1[1];
      DAT_cc008000 = FLOAT_803313dc;
      dVar4 = dVar6;
      if (iVar2 < 2) {
        dVar4 = dVar8;
      }
      DAT_cc008000 = (float)dVar7;
      DAT_cc008000 = (float)dVar4;
      DAT_cc008000 = puVar1[3];
      DAT_cc008000 = puVar1[4];
      DAT_cc008000 = FLOAT_803313dc;
      dVar4 = dVar7;
      if ((iVar2 + 1U & 1) != 0) {
        dVar4 = dVar9;
      }
      dVar5 = dVar6;
      if ((int)(iVar2 + 1U) < 2) {
        dVar5 = dVar8;
      }
      DAT_cc008000 = (float)dVar4;
      puVar1 = puVar1 + 6;
      iVar2 = iVar2 + 2;
      DAT_cc008000 = (float)dVar5;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  return;
}


// Function: ArtiBaseInfoInit__8CMenuPcsFPQ28CMenuPcs5Sprt2PQ28CMenuPcs5Sprt2
// Entry: 80133170
// Size: 924 bytes

/* WARNING: Removing unreachable block (ram,0x80133360) */
/* WARNING: Removing unreachable block (ram,0x801332d8) */
/* WARNING: Removing unreachable block (ram,0x8013328c) */
/* WARNING: Removing unreachable block (ram,0x801333ac) */

void ArtiBaseInfoInit__8CMenuPcsFPQ28CMenuPcs5Sprt2PQ28CMenuPcs5Sprt2
               (CMenuPcs *menuPcs,short *param_2,int param_3)

{
  float fVar1;
  double dVar2;
  float fVar3;
  double dVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  
  dVar2 = DOUBLE_80331e88;
  dVar7 = DOUBLE_80331e78;
  *DAT_8032eeb0 =
       (float)(((double)CONCAT44(0x43300000,(int)param_2[2] ^ 0x80000000) - DOUBLE_80331e88) *
               DOUBLE_80331e78 +
              ((double)CONCAT44(0x43300000,(int)*param_2 ^ 0x80000000) - DOUBLE_80331e88));
  DAT_8032eeb0[1] =
       (float)(((double)CONCAT44(0x43300000,(int)param_2[3] ^ 0x80000000) - dVar2) * dVar7 +
              ((double)CONCAT44(0x43300000,(int)param_2[1] ^ 0x80000000) - dVar2));
  dVar8 = (double)(float)((double)CONCAT44(0x43300000,(int)*(short *)(param_3 + 4) ^ 0x80000000) -
                         dVar2);
  dVar7 = dVar8 * dVar7;
  dVar9 = (double)(float)((double)CONCAT44(0x43300000,(int)*(short *)(param_3 + 6) ^ 0x80000000) -
                         dVar2);
  fVar3 = (float)((double)CONCAT44(0x43300000,(int)param_2[1] ^ 0x80000000) - dVar2);
  fVar1 = (float)((double)*DAT_8032eeb0 - dVar7);
  DAT_8032eeb0[0xe] = fVar1;
  DAT_8032eeb0[0xf] = fVar3;
  dVar2 = (double)CONCAT44(0x43300000,(int)param_2[3] ^ 0x80000000) - DOUBLE_80331e88;
  DAT_8032eeb0[6] = fVar1;
  DAT_8032eeb0[7] = fVar3 + (float)((double)(float)dVar2 - dVar9);
  dVar9 = dVar9 * DOUBLE_80331e78;
  fVar1 = (float)((double)DAT_8032eeb0[1] - dVar9);
  fVar3 = (float)((double)CONCAT44(0x43300000,(int)*param_2 ^ 0x80000000) - DOUBLE_80331e88);
  DAT_8032eeb0[10] = fVar3;
  DAT_8032eeb0[0xb] = fVar1;
  DAT_8032eeb0[2] =
       fVar3 + (float)((double)(float)((double)CONCAT44(0x43300000,(int)param_2[2] ^ 0x80000000) -
                                      DOUBLE_80331e88) - dVar8);
  DAT_8032eeb0[3] = fVar1;
  dVar4 = DOUBLE_80331e88;
  dVar8 = DOUBLE_80331e80;
  dVar2 = DOUBLE_80331e78;
  iVar5 = 0;
  iVar6 = 2;
  do {
    fVar1 = (float)((double)(float)(((double)CONCAT44(0x43300000,(int)param_2[2] ^ 0x80000000) -
                                    dVar4) * dVar8 +
                                   ((double)CONCAT44(0x43300000,(int)*param_2 ^ 0x80000000) - dVar4)
                                   ) - dVar7);
    fVar3 = (float)((double)(float)(((double)CONCAT44(0x43300000,(int)param_2[3] ^ 0x80000000U) -
                                    dVar4) * dVar8 +
                                   ((double)CONCAT44(0x43300000,(int)param_2[1] ^ 0x80000000) -
                                   dVar4)) - dVar9);
    dVar10 = (double)fVar3;
    if (iVar5 == 0) {
      DAT_8032eeb0[0xc] = fVar1;
      DAT_8032eeb0[0xd] = fVar3;
    }
    else {
      fVar3 = (float)(((double)CONCAT44(0x43300000,(int)param_2[3] ^ 0x80000000U) - dVar4) *
                      DOUBLE_80331e78 + dVar10);
      dVar10 = (double)fVar3;
      DAT_8032eeb0[8] = fVar1;
      DAT_8032eeb0[9] = fVar3;
    }
    fVar1 = (float)(((double)CONCAT44(0x43300000,(int)param_2[2] ^ 0x80000000) - dVar4) * dVar2 +
                   (double)fVar1);
    if (iVar5 == 0) {
      DAT_8032eeb0[0x10] = fVar1;
      DAT_8032eeb0[0x11] = (float)dVar10;
    }
    else {
      DAT_8032eeb0[4] = fVar1;
      DAT_8032eeb0[5] = (float)dVar10;
    }
    iVar5 = iVar5 + 1;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  return;
}


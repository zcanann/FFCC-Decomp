// Function: DrawSingWin__8CMenuPcsFs
// Entry: 80146adc
// Size: 1500 bytes

/* WARNING: Removing unreachable block (ram,0x80147090) */
/* WARNING: Removing unreachable block (ram,0x80147088) */
/* WARNING: Removing unreachable block (ram,0x80147080) */
/* WARNING: Removing unreachable block (ram,0x80147078) */
/* WARNING: Removing unreachable block (ram,0x80147070) */
/* WARNING: Removing unreachable block (ram,0x80147068) */
/* WARNING: Removing unreachable block (ram,0x80147060) */
/* WARNING: Removing unreachable block (ram,0x80147058) */
/* WARNING: Removing unreachable block (ram,0x80147050) */
/* WARNING: Removing unreachable block (ram,0x80147048) */
/* WARNING: Removing unreachable block (ram,0x80146b34) */
/* WARNING: Removing unreachable block (ram,0x80146b2c) */
/* WARNING: Removing unreachable block (ram,0x80146b24) */
/* WARNING: Removing unreachable block (ram,0x80146b1c) */
/* WARNING: Removing unreachable block (ram,0x80146b14) */
/* WARNING: Removing unreachable block (ram,0x80146b0c) */
/* WARNING: Removing unreachable block (ram,0x80146b04) */
/* WARNING: Removing unreachable block (ram,0x80146afc) */
/* WARNING: Removing unreachable block (ram,0x80146af4) */
/* WARNING: Removing unreachable block (ram,0x80146aec) */

void DrawSingWin__8CMenuPcsFs(CMenuPcs *menuPcs,short param_2)

{
  float fVar1;
  float fVar2;
  short sVar3;
  float fVar4;
  float fVar5;
  uint uVar6;
  uint uVar7;
  short *psVar8;
  undefined4 uVar9;
  int iVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  double dVar20;
  undefined4 local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  uint uStack_f4;
  undefined8 local_f0;
  undefined4 local_e8;
  uint uStack_e4;
  undefined8 local_e0;
  longlong local_d8;
  undefined4 local_d0;
  uint uStack_cc;
  longlong local_c8;
  undefined4 local_c0;
  uint uStack_bc;
  
  if ((-1 < param_2) && (*(short *)(*(int *)&menuPcs->field_0x848 + 10) != param_2)) {
    *(short *)(*(int *)&menuPcs->field_0x848 + 10) = param_2;
  }
  psVar8 = *(short **)&menuPcs->field_0x848;
  if (psVar8[5] != 3) {
    uVar7 = (int)*psVar8 ^ 0x80000000;
    local_f0 = (double)CONCAT44(0x43300000,(int)psVar8[2] ^ 0x80000000U);
    uVar6 = (int)psVar8[1] ^ 0x80000000;
    local_e0 = (double)CONCAT44(0x43300000,(int)psVar8[3] ^ 0x80000000U);
    fVar1 = (float)((double)CONCAT44(0x43300000,uVar7) - DOUBLE_80332938) +
            (float)((local_f0 - DOUBLE_80332938) * DOUBLE_80332968);
    fVar4 = (float)((double)CONCAT44(0x43300000,uVar6) - DOUBLE_80332938) +
            (float)((local_e0 - DOUBLE_80332938) * DOUBLE_80332968);
    if (psVar8[5] == 1) {
      local_e0 = (double)CONCAT44(0x43300000,uVar7);
      fVar1 = (float)(local_e0 - DOUBLE_80332938);
      fVar2 = (float)((double)CONCAT44(0x43300000,uVar6) - DOUBLE_80332938);
      local_f0 = (double)CONCAT44(0x43300000,(int)psVar8[2] ^ 0x80000000U);
      dVar12 = local_f0 - DOUBLE_80332938;
      dVar11 = (double)CONCAT44(0x43300000,(int)psVar8[3] ^ 0x80000000U) - DOUBLE_80332938;
    }
    else {
      local_e0 = (double)CONCAT44(0x43300000,uVar7);
      local_f0 = (double)CONCAT44(0x43300000,uVar6);
      fVar5 = (((fVar1 - (float)(local_e0 - DOUBLE_80332938)) - FLOAT_8033292c) / FLOAT_80332970) *
              (float)((double)CONCAT44(0x43300000,(int)psVar8[4] ^ 0x80000000U) - DOUBLE_80332938);
      fVar2 = (((fVar4 - (float)(local_f0 - DOUBLE_80332938)) - FLOAT_8033292c) / FLOAT_80332970) *
              (float)((double)CONCAT44(0x43300000,(int)psVar8[4] ^ 0x80000000U) - DOUBLE_80332938);
      fVar1 = (fVar1 - FLOAT_8033292c) - fVar5;
      dVar12 = DOUBLE_80332978 * (double)(FLOAT_8033292c + fVar5);
      dVar11 = DOUBLE_80332978 * (double)(FLOAT_8033292c + fVar2);
      fVar2 = (fVar4 - FLOAT_8033292c) - fVar2;
    }
    local_e8 = 0x43300000;
    local_d0 = 0x43300000;
    local_e0 = (double)(longlong)(int)((double)fVar1 - DOUBLE_80332968);
    local_f8 = 0x43300000;
    local_f0 = (double)(longlong)(int)((double)fVar2 - DOUBLE_80332968);
    local_c0 = 0x43300000;
    local_d8 = (longlong)(int)((double)(float)dVar12 - DOUBLE_80332980);
    local_c8 = (longlong)(int)((double)(float)dVar11 - DOUBLE_80332980);
    uStack_e4 = (int)((double)fVar1 - DOUBLE_80332968) ^ 0x80000000;
    uStack_f4 = (int)((double)fVar2 - DOUBLE_80332968) ^ 0x80000000;
    uStack_cc = (int)((double)(float)dVar12 - DOUBLE_80332980) ^ 0x80000000;
    uStack_bc = (int)((double)(float)dVar11 - DOUBLE_80332980) ^ 0x80000000;
    dVar11 = (double)(float)((double)CONCAT44(0x43300000,uStack_e4) - DOUBLE_80332938);
    dVar12 = (double)(float)((double)CONCAT44(0x43300000,uStack_f4) - DOUBLE_80332938);
    dVar19 = (double)(float)((double)CONCAT44(0x43300000,uStack_cc) - DOUBLE_80332938);
    dVar18 = (double)(float)((double)CONCAT44(0x43300000,uStack_bc) - DOUBLE_80332938);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    local_fc = 0xffffffff;
    local_100 = 0xffffffff;
    GXSetChanMatColor(4,&local_100);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x3f);
    dVar15 = (double)FLOAT_8033294c;
    dVar20 = (double)((float)(dVar11 + dVar19) - FLOAT_8033292c);
    uVar6 = 0;
    dVar14 = (double)((float)(dVar12 + dVar18) - FLOAT_8033292c);
    do {
      uVar7 = 0;
      dVar13 = dVar11;
      if ((uVar6 & 1) != 0) {
        uVar7 = 8;
        dVar13 = dVar20;
      }
      dVar16 = dVar12;
      if ((uVar6 & 2) != 0) {
        uVar7 = uVar7 | 4;
        dVar16 = dVar14;
      }
      DrawRect__8CMenuPcsFUlfffffffff
                (dVar13,dVar16,(double)FLOAT_8033292c,(double)FLOAT_8033292c,dVar15,dVar15,
                 (double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,uVar7);
      uVar6 = uVar6 + 1;
    } while ((int)uVar6 < 4);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x41);
    dVar19 = dVar19 - DOUBLE_80332988;
    dVar16 = (double)FLOAT_8033294c;
    dVar17 = (double)(float)((double)FLOAT_8033292c + dVar11);
    iVar10 = 0;
    dVar13 = (double)(float)dVar19;
    dVar15 = dVar12;
    do {
      uVar9 = 0;
      if (iVar10 != 0) {
        uVar9 = 4;
        dVar12 = dVar14;
      }
      DrawRect__8CMenuPcsFUlfffffffff
                (dVar17,dVar12,dVar13,(double)FLOAT_8033292c,dVar16,dVar16,(double)FLOAT_80332934,
                 (double)FLOAT_80332934,&MenuPcs,uVar9);
      iVar10 = iVar10 + 1;
    } while (iVar10 < 2);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x40);
    dVar18 = dVar18 - DOUBLE_80332988;
    iVar10 = 0;
    dVar14 = (double)(float)((double)FLOAT_8033292c + dVar15);
    dVar15 = (double)FLOAT_8033294c;
    dVar12 = (double)(float)dVar18;
    do {
      uVar9 = 0;
      if (iVar10 != 0) {
        uVar9 = 8;
        dVar11 = dVar20;
      }
      DrawRect__8CMenuPcsFUlfffffffff
                (dVar11,dVar14,(double)FLOAT_8033292c,dVar12,dVar15,dVar15,(double)FLOAT_80332934,
                 (double)FLOAT_80332934,&MenuPcs,uVar9);
      iVar10 = iVar10 + 1;
    } while (iVar10 < 2);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x42);
    DrawRect__8CMenuPcsFUlfffffffff
              (dVar17,dVar14,(double)(float)dVar19,(double)(float)dVar18,(double)FLOAT_8033294c,
               (double)FLOAT_8033294c,(double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,uVar9);
    iVar10 = *(int *)&menuPcs->field_0x848;
    sVar3 = *(short *)(iVar10 + 10);
    if (sVar3 == 0) {
      *(short *)(iVar10 + 8) = *(short *)(iVar10 + 8) + 1;
      if (5 < *(short *)(*(int *)&menuPcs->field_0x848 + 8)) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 8) = 6;
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 1;
      }
    }
    else if (sVar3 == 1) {
      if (*(short *)(iVar10 + 8) != 6) {
        *(undefined2 *)(iVar10 + 8) = 6;
      }
    }
    else if (sVar3 == 2) {
      *(short *)(iVar10 + 8) = *(short *)(iVar10 + 8) + -1;
      if (*(short *)(*(int *)&menuPcs->field_0x848 + 8) < 1) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 8) = 0;
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 3;
      }
    }
  }
  return;
}


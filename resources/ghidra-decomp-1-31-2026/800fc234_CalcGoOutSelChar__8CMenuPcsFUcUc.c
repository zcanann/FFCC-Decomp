// Function: CalcGoOutSelChar__8CMenuPcsFUcUc
// Entry: 800fc234
// Size: 648 bytes

/* WARNING: Removing unreachable block (ram,0x800fc49c) */
/* WARNING: Removing unreachable block (ram,0x800fc244) */

int CalcGoOutSelChar__8CMenuPcsFUcUc(CMenuPcs *menuPcs,char param_2,char param_3)

{
  short sVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  double dVar5;
  double dVar6;
  undefined8 local_38;
  double local_30;
  
  if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) < 5) {
    if (param_2 != '\0') {
      CalcGoOutCharaSelect__8CMenuPcsFUc(menuPcs,param_3);
    }
    dVar6 = DOUBLE_80331408;
    iVar2 = *(int *)&menuPcs->field_0x82c;
    sVar1 = *(short *)(iVar2 + 0x10);
    if (sVar1 == 0) {
      uVar4 = (int)*(short *)(iVar2 + 0x22) - 10;
    }
    else if ((sVar1 < 1) || (3 < sVar1)) {
      uVar4 = -(int)*(short *)(iVar2 + 0x22);
    }
    else {
      uVar4 = 0;
    }
    *(undefined2 *)(*(int *)&menuPcs->field_0x820 + 4) = 0x10;
    iVar2 = *(int *)&menuPcs->field_0x820;
    local_38 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar2 + 8) + (int)*(short *)(iVar2 + 4))
                       ^ 0x80000000);
    *(short *)(iVar2 + 0x20) = (short)(int)(FLOAT_803313e0 - (float)(local_38 - dVar6));
    if ((int)uVar4 < 0) {
      local_30 = (double)(CONCAT44(0x43300000,
                                   (int)*(short *)(*(int *)&menuPcs->field_0x820 + 8) +
                                   (int)*(short *)(*(int *)&menuPcs->field_0x820 + 4)) ^ 0x80000000)
      ;
      dVar5 = (double)(float)(local_30 - dVar6);
      if (-0xb < (int)uVar4) {
        uVar3 = (int)uVar4 >> 0x1f;
        local_30 = (double)(CONCAT44(0x43300000,(uVar3 ^ uVar4) - uVar3) ^ 0x80000000);
        uVar3 = (uVar3 ^ uVar4) - uVar3;
        dVar6 = (double)(float)(dVar5 * DOUBLE_803314e8 * (local_30 - dVar6));
        if ((int)uVar3 < 0) {
          uVar3 = 0;
        }
        if (10 < (int)uVar3) {
          uVar3 = 10;
        }
        local_38 = (double)CONCAT44(0x43300000,uVar3 ^ 0x80000000);
        dVar5 = (double)sin((double)(FLOAT_803314bc *
                                    (float)(local_38 - DOUBLE_80331408) * FLOAT_803316d4));
        dVar5 = (double)(float)(dVar6 * (double)(float)dVar5);
      }
      dVar6 = DOUBLE_80331408;
      local_30 = (double)(CONCAT44(0x43300000,(int)*(short *)(*(int *)&menuPcs->field_0x820 + 4)) ^
                         0x80000000);
      *(short *)(*(int *)&menuPcs->field_0x820 + 4) =
           (short)(int)((double)(float)(local_30 - DOUBLE_80331408) - dVar5);
      *(short *)(*(int *)&menuPcs->field_0x820 + 0x20) =
           (short)(int)((double)(float)((double)CONCAT44(0x43300000,
                                                         (int)*(short *)(*(int *)&menuPcs->
                                                  field_0x820 + 0x20) ^ 0x80000000) - dVar6) + dVar5
                       );
    }
    sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
    if ((0 < sVar1) && (sVar1 < 4)) {
      CalcChara__8CMenuPcsFv(menuPcs);
    }
    iVar2 = *(int *)&menuPcs->field_0x828;
    if (*(char *)(iVar2 + 0xe) == '\0') {
      if ((*(char *)(iVar2 + 10) == '\0') ||
         ((iVar2 = (int)*(short *)(iVar2 + 4),
          *(int *)(*(int *)&menuPcs->field_0x844 + iVar2 * 0x14) == 3 && (param_3 != '\0')))) {
        iVar2 = -1;
      }
    }
    else {
      iVar2 = -2;
    }
  }
  else {
    iVar2 = -1;
  }
  return iVar2;
}


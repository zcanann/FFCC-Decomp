// Function: CalcWMFrame0__8CMenuPcsFi
// Entry: 800f3500
// Size: 428 bytes

/* WARNING: Removing unreachable block (ram,0x800f3690) */
/* WARNING: Removing unreachable block (ram,0x800f3510) */

void CalcWMFrame0__8CMenuPcsFi(CMenuPcs *menuPcs,uint param_2)

{
  int iVar1;
  uint uVar2;
  double dVar3;
  double dVar4;
  undefined8 local_38;
  double local_30;
  
  dVar4 = DOUBLE_80331408;
  *(undefined2 *)(*(int *)&menuPcs->field_0x820 + 4) = 0x10;
  iVar1 = *(int *)&menuPcs->field_0x820;
  local_38 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar1 + 8) + (int)*(short *)(iVar1 + 4)) ^
                     0x80000000);
  *(short *)(iVar1 + 0x20) = (short)(int)(FLOAT_803313e0 - (float)(local_38 - dVar4));
  if ((int)param_2 < 0) {
    local_30 = (double)(CONCAT44(0x43300000,
                                 (int)*(short *)(*(int *)&menuPcs->field_0x820 + 8) +
                                 (int)*(short *)(*(int *)&menuPcs->field_0x820 + 4)) ^ 0x80000000);
    dVar3 = (double)(float)(local_30 - dVar4);
    if (-0xb < (int)param_2) {
      uVar2 = (int)param_2 >> 0x1f;
      local_30 = (double)(CONCAT44(0x43300000,(uVar2 ^ param_2) - uVar2) ^ 0x80000000);
      uVar2 = (uVar2 ^ param_2) - uVar2;
      dVar4 = (double)(float)(dVar3 * DOUBLE_803314e8 * (local_30 - dVar4));
      if ((int)uVar2 < 0) {
        uVar2 = 0;
      }
      if (10 < (int)uVar2) {
        uVar2 = 10;
      }
      local_38 = (double)CONCAT44(0x43300000,uVar2 ^ 0x80000000);
      dVar3 = (double)sin((double)(FLOAT_803314bc *
                                  (float)(local_38 - DOUBLE_80331408) * FLOAT_803316d4));
      dVar3 = (double)(float)(dVar4 * (double)(float)dVar3);
    }
    dVar4 = DOUBLE_80331408;
    local_30 = (double)(CONCAT44(0x43300000,(int)*(short *)(*(int *)&menuPcs->field_0x820 + 4)) ^
                       0x80000000);
    *(short *)(*(int *)&menuPcs->field_0x820 + 4) =
         (short)(int)((double)(float)(local_30 - DOUBLE_80331408) - dVar3);
    *(short *)(*(int *)&menuPcs->field_0x820 + 0x20) =
         (short)(int)((double)(float)((double)CONCAT44(0x43300000,
                                                       (int)*(short *)(*(int *)&menuPcs->field_0x820
                                                                      + 0x20) ^ 0x80000000) - dVar4)
                     + dVar3);
  }
  return;
}


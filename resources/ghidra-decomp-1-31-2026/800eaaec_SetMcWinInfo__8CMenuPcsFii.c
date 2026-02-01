// Function: SetMcWinInfo__8CMenuPcsFii
// Entry: 800eaaec
// Size: 172 bytes

void SetMcWinInfo__8CMenuPcsFii(CMenuPcs *menuPcs,int param_2,uint param_3)

{
  double dVar1;
  
  dVar1 = (double)(FLOAT_80331430 -
                  (float)((double)CONCAT44(0x43300000,param_3 ^ 0x80000000) - DOUBLE_80331408)) *
          DOUBLE_803313f8;
  **(undefined2 **)&menuPcs->field_0x848 =
       (short)(int)((double)(float)((double)CONCAT44(0x43300000,0x280U - param_2 ^ 0x80000000) -
                                   DOUBLE_80331408) * DOUBLE_803313f8);
  *(short *)(*(int *)&menuPcs->field_0x848 + 2) = (short)(int)dVar1;
  *(short *)(*(int *)&menuPcs->field_0x848 + 4) = (short)param_2;
  *(short *)(*(int *)&menuPcs->field_0x848 + 6) = (short)param_3;
  *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 8) = 0;
  *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 3;
  return;
}


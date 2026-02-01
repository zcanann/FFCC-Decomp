// Function: AddSphere__5CWindFPC3Vecffi
// Entry: 800d93bc
// Size: 380 bytes

undefined4
AddSphere__5CWindFPC3Vecffi
          (double param_1,double param_2,byte *param_3,undefined4 *param_4,undefined4 param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  byte *pbVar4;
  byte *pbVar5;
  int iVar6;
  
  iVar3 = 0;
  iVar6 = 4;
  pbVar4 = param_3;
  do {
    pbVar5 = pbVar4;
    if (((((-1 < (int)((uint)*pbVar4 << 0x18)) ||
          (pbVar5 = pbVar4 + 100, -1 < (int)((uint)*pbVar5 << 0x18))) ||
         (pbVar5 = pbVar4 + 200, -1 < (int)((uint)*pbVar5 << 0x18))) ||
        ((pbVar5 = pbVar4 + 300, -1 < (int)((uint)*pbVar5 << 0x18) ||
         (pbVar5 = pbVar4 + 400, -1 < (int)((uint)*pbVar5 << 0x18))))) ||
       ((pbVar5 = pbVar4 + 500, -1 < (int)((uint)*pbVar5 << 0x18) ||
        ((pbVar5 = pbVar4 + 600, -1 < (int)((uint)*pbVar5 << 0x18) ||
         (pbVar5 = pbVar4 + 700, -1 < (int)((uint)pbVar4[700] << 0x18))))))) goto LAB_800d94a8;
    iVar3 = iVar3 + 7;
    pbVar4 = pbVar4 + 800;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  pbVar5 = (byte *)0x0;
LAB_800d94a8:
  if (pbVar5 == (byte *)0x0) {
    Printf__7CSystemFPce(&System,&DAT_801db528,param_5,iVar3);
    uVar2 = 0xffffffff;
  }
  else {
    pbVar5[0x1c] = 0;
    pbVar5[0x1d] = 0;
    pbVar5[0x1e] = 0;
    pbVar5[0x1f] = 2;
    uVar2 = *param_4;
    uVar1 = param_4[2];
    *pbVar5 = *pbVar5 & 0x7f | 0x80;
    iVar3 = *(int *)(param_3 + 0xc80);
    *(int *)(param_3 + 0xc80) = iVar3 + 1;
    *(int *)(pbVar5 + 0x20) = iVar3;
    *(float *)(pbVar5 + 0x54) = (float)param_2;
    *(float *)(pbVar5 + 0x50) = (float)param_2;
    *(float *)(pbVar5 + 0x4c) = (float)param_2;
    *(float *)(pbVar5 + 0x2c) = (float)param_1;
    *(undefined4 *)(pbVar5 + 0x24) = param_5;
    pbVar5[0x28] = 0;
    pbVar5[0x29] = 0;
    pbVar5[0x2a] = 0;
    pbVar5[0x2b] = 0;
    *(undefined4 *)(pbVar5 + 4) = uVar2;
    *(undefined4 *)(pbVar5 + 8) = uVar1;
    uVar2 = *(undefined4 *)(pbVar5 + 0x20);
  }
  return uVar2;
}


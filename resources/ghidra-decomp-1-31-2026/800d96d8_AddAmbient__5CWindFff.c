// Function: AddAmbient__5CWindFff
// Entry: 800d96d8
// Size: 360 bytes

undefined4 AddAmbient__5CWindFff(double param_1,double param_2,byte *param_3)

{
  undefined4 uVar1;
  byte *pbVar2;
  byte *pbVar3;
  int iVar4;
  
  iVar4 = 4;
  pbVar2 = param_3;
  do {
    pbVar3 = pbVar2;
    if (((((-1 < (int)((uint)*pbVar2 << 0x18)) ||
          (pbVar3 = pbVar2 + 100, -1 < (int)((uint)*pbVar3 << 0x18))) ||
         (pbVar3 = pbVar2 + 200, -1 < (int)((uint)*pbVar3 << 0x18))) ||
        ((pbVar3 = pbVar2 + 300, -1 < (int)((uint)*pbVar3 << 0x18) ||
         (pbVar3 = pbVar2 + 400, -1 < (int)((uint)*pbVar3 << 0x18))))) ||
       ((pbVar3 = pbVar2 + 500, -1 < (int)((uint)*pbVar3 << 0x18) ||
        ((pbVar3 = pbVar2 + 600, -1 < (int)((uint)*pbVar3 << 0x18) ||
         (pbVar3 = pbVar2 + 700, -1 < (int)((uint)pbVar2[700] << 0x18))))))) goto LAB_800d97c4;
    pbVar2 = pbVar2 + 800;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  pbVar3 = (byte *)0x0;
LAB_800d97c4:
  if (pbVar3 == (byte *)0x0) {
    Printf__7CSystemFPce(&System,&DAT_801db568);
    uVar1 = 0xffffffff;
  }
  else {
    pbVar3[0x1c] = 0;
    pbVar3[0x1d] = 0;
    pbVar3[0x1e] = 0;
    pbVar3[0x1f] = 0;
    *pbVar3 = *pbVar3 & 0x7f | 0x80;
    iVar4 = *(int *)(param_3 + 0xc80);
    *(int *)(param_3 + 0xc80) = iVar4 + 1;
    *(int *)(pbVar3 + 0x20) = iVar4;
    *(float *)(pbVar3 + 0x48) = (float)param_1;
    *(float *)(pbVar3 + 0x44) = (float)param_1;
    *(float *)(pbVar3 + 0x40) = (float)param_1;
    *(float *)(pbVar3 + 0x54) = (float)param_2;
    *(float *)(pbVar3 + 0x50) = (float)param_2;
    *(float *)(pbVar3 + 0x4c) = (float)param_2;
    uVar1 = *(undefined4 *)(pbVar3 + 0x20);
  }
  return uVar1;
}


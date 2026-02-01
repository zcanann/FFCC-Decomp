// Function: AddDiffuse__5CWindFPC3Vecfff
// Entry: 800d9538
// Size: 416 bytes

undefined4
AddDiffuse__5CWindFPC3Vecfff
          (double param_1,double param_2,double param_3,byte *param_4,float *param_5)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  int iVar4;
  byte *pbVar5;
  byte *pbVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  
  iVar4 = 0;
  iVar7 = 4;
  pbVar5 = param_4;
  do {
    pbVar6 = pbVar5;
    if (((((-1 < (int)((uint)*pbVar5 << 0x18)) ||
          (pbVar6 = pbVar5 + 100, -1 < (int)((uint)*pbVar6 << 0x18))) ||
         (pbVar6 = pbVar5 + 200, -1 < (int)((uint)*pbVar6 << 0x18))) ||
        ((pbVar6 = pbVar5 + 300, -1 < (int)((uint)*pbVar6 << 0x18) ||
         (pbVar6 = pbVar5 + 400, -1 < (int)((uint)*pbVar6 << 0x18))))) ||
       ((pbVar6 = pbVar5 + 500, -1 < (int)((uint)*pbVar6 << 0x18) ||
        ((pbVar6 = pbVar5 + 600, -1 < (int)((uint)*pbVar6 << 0x18) ||
         (pbVar6 = pbVar5 + 700, -1 < (int)((uint)pbVar5[700] << 0x18))))))) goto LAB_800d9624;
    iVar4 = iVar4 + 7;
    pbVar5 = pbVar5 + 800;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  pbVar6 = (byte *)0x0;
LAB_800d9624:
  if (pbVar6 == (byte *)0x0) {
    Printf__7CSystemFPce(&System,&DAT_801db548,iVar4);
    uVar3 = 0xffffffff;
  }
  else {
    fVar1 = *param_5;
    dVar9 = (double)fVar1;
    pbVar6[0x1c] = 0;
    pbVar6[0x1d] = 0;
    pbVar6[0x1e] = 0;
    pbVar6[0x1f] = 1;
    fVar2 = param_5[2];
    dVar8 = (double)fVar2;
    *pbVar6 = *pbVar6 & 0x7f | 0x80;
    iVar4 = *(int *)(param_4 + 0xc80);
    *(int *)(param_4 + 0xc80) = iVar4 + 1;
    *(int *)(pbVar6 + 0x20) = iVar4;
    *(float *)(pbVar6 + 0x48) = (float)param_2;
    *(float *)(pbVar6 + 0x44) = (float)param_2;
    *(float *)(pbVar6 + 0x40) = (float)param_2;
    *(float *)(pbVar6 + 0x54) = (float)param_3;
    *(float *)(pbVar6 + 0x50) = (float)param_3;
    *(float *)(pbVar6 + 0x4c) = (float)param_3;
    *(float *)(pbVar6 + 0x30) = (float)param_1;
    *(float *)(pbVar6 + 0x34) = (float)(param_1 * param_1);
    *(float *)(pbVar6 + 4) = fVar1;
    *(float *)(pbVar6 + 8) = fVar2;
    *(float *)(pbVar6 + 0xc) = (float)(dVar9 - param_1);
    *(float *)(pbVar6 + 0x10) = (float)(dVar8 - param_1);
    *(float *)(pbVar6 + 0x14) = (float)(dVar9 + param_1);
    *(float *)(pbVar6 + 0x18) = (float)(dVar8 + param_1);
    uVar3 = *(undefined4 *)(pbVar6 + 0x20);
  }
  return uVar3;
}


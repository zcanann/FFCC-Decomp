// Function: AXFXDelayCallback
// Entry: 80196518
// Size: 464 bytes

void AXFXDelayCallback(int *param_1,uint *param_2)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  
  iVar10 = 0x50;
  piVar5 = (int *)*param_1;
  piVar6 = (int *)param_1[1];
  piVar7 = (int *)param_1[2];
  piVar2 = (int *)(param_2[0xc] + param_2[3] * 0x280);
  piVar3 = (int *)(param_2[0xd] + param_2[4] * 0x280);
  piVar4 = (int *)(param_2[0xe] + param_2[5] * 0x280);
  do {
    iVar8 = *piVar2;
    iVar9 = *piVar3;
    iVar1 = *piVar4;
    *piVar2 = *piVar5 + ((int)(iVar8 * param_2[6]) >> 7);
    *piVar3 = *piVar6 + ((int)(iVar9 * param_2[7]) >> 7);
    *piVar4 = *piVar7 + ((int)(iVar1 * param_2[8]) >> 7);
    *piVar5 = (int)(iVar8 * param_2[9]) >> 7;
    *piVar6 = (int)(iVar9 * param_2[10]) >> 7;
    *piVar7 = (int)(iVar1 * param_2[0xb]) >> 7;
    iVar8 = piVar2[1];
    iVar9 = piVar3[1];
    iVar1 = piVar4[1];
    piVar2[1] = piVar5[1] + ((int)(iVar8 * param_2[6]) >> 7);
    piVar2 = piVar2 + 2;
    piVar3[1] = piVar6[1] + ((int)(iVar9 * param_2[7]) >> 7);
    piVar3 = piVar3 + 2;
    piVar4[1] = piVar7[1] + ((int)(iVar1 * param_2[8]) >> 7);
    piVar4 = piVar4 + 2;
    piVar5[1] = (int)(iVar8 * param_2[9]) >> 7;
    piVar5 = piVar5 + 2;
    piVar6[1] = (int)(iVar9 * param_2[10]) >> 7;
    piVar6 = piVar6 + 2;
    piVar7[1] = (int)(iVar1 * param_2[0xb]) >> 7;
    piVar7 = piVar7 + 2;
    iVar10 = iVar10 + -1;
  } while (iVar10 != 0);
  param_2[3] = (param_2[3] + 1) - ((param_2[3] + 1) / *param_2) * *param_2;
  param_2[4] = (param_2[4] + 1) - ((param_2[4] + 1) / param_2[1]) * param_2[1];
  param_2[5] = (param_2[5] + 1) - ((param_2[5] + 1) / param_2[2]) * param_2[2];
  return;
}


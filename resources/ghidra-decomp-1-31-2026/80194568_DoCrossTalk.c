// Function: DoCrossTalk
// Entry: 80194568
// Size: 400 bytes

void DoCrossTalk(double param_1,double param_2,uint *param_3,uint *param_4)

{
  double dVar1;
  uint *puVar2;
  uint *puVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  
  dVar1 = DAT_80333780;
  iVar7 = 0x4f;
  dVar8 = param_1 * (double)DAT_80333788;
  dVar16 = param_2 * (double)DAT_80333788;
  dVar9 = (double)(float)((double)CONCAT44(0x43300000,*param_3 ^ 0x80000000) - DAT_80333780);
  dVar10 = (double)(float)((double)CONCAT44(0x43300000,*param_4 ^ 0x80000000) - DAT_80333780);
  dVar11 = (double)(float)((double)CONCAT44(0x43300000,param_3[1] ^ 0x80000000) - DAT_80333780);
  dVar12 = (double)(float)((double)CONCAT44(0x43300000,param_4[1] ^ 0x80000000) - DAT_80333780);
  do {
    puVar3 = param_4;
    puVar2 = param_3;
    uVar4 = puVar3[2];
    uVar5 = puVar2[3];
    dVar13 = dVar9 * param_2;
    dVar14 = dVar9 * dVar8;
    dVar17 = dVar10 * dVar16;
    uVar6 = puVar3[3];
    dVar15 = dVar11 * dVar8;
    dVar9 = (double)(float)((double)CONCAT44(0x43300000,puVar2[2] ^ 0x80000000) - dVar1);
    *puVar2 = (int)(dVar13 + dVar10 * param_1);
    dVar10 = (double)(float)((double)CONCAT44(0x43300000,uVar4 ^ 0x80000000) - dVar1);
    *puVar3 = (int)(dVar14 + dVar17);
    puVar2[1] = (int)(dVar11 * param_2 + dVar12 * param_1);
    dVar11 = (double)(float)((double)CONCAT44(0x43300000,uVar5 ^ 0x80000000) - dVar1);
    puVar3[1] = (int)(dVar15 + dVar12 * dVar16);
    dVar12 = (double)(float)((double)CONCAT44(0x43300000,uVar6 ^ 0x80000000) - dVar1);
    iVar7 = iVar7 + -1;
    param_3 = puVar2 + 2;
    param_4 = puVar3 + 2;
  } while (iVar7 != 0);
  puVar2[2] = (int)(dVar9 * param_2 + dVar10 * param_1);
  puVar3[2] = (int)(dVar9 * dVar8 + dVar10 * dVar16);
  puVar2[3] = (int)(dVar11 * param_2 + dVar12 * param_1);
  puVar3[3] = (int)(dVar11 * dVar8 + dVar12 * dVar16);
  return;
}


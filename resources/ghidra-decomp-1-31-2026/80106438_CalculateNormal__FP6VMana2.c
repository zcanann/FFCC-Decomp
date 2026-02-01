// Function: CalculateNormal__FP6VMana2
// Entry: 80106438
// Size: 604 bytes

void CalculateNormal__FP6VMana2(int param_1)

{
  ushort uVar1;
  float fVar2;
  float fVar3;
  Vec *pVVar4;
  int iVar5;
  uint uVar6;
  float *pfVar7;
  float *pfVar8;
  uint uVar9;
  float *pfVar10;
  int iVar11;
  Vec *pVVar12;
  int iVar13;
  int iVar14;
  Vec VStack_48;
  Vec local_3c;
  Vec local_30;
  
  fVar2 = FLOAT_80331898;
  iVar5 = 0;
  iVar13 = *(int *)(param_1 + 0x3c);
  pVVar12 = *(Vec **)(param_1 + 0x40);
  iVar11 = *(int *)(param_1 + 0x50);
  iVar14 = 0x12;
  pVVar4 = pVVar12;
  do {
    pVVar4->z = fVar2;
    iVar5 = iVar5 + 0x10;
    pVVar4->y = fVar2;
    pVVar4->x = fVar2;
    pVVar4[1].z = fVar2;
    pVVar4[1].y = fVar2;
    pVVar4[1].x = fVar2;
    pVVar4[2].z = fVar2;
    pVVar4[2].y = fVar2;
    pVVar4[2].x = fVar2;
    pVVar4[3].z = fVar2;
    pVVar4[3].y = fVar2;
    pVVar4[3].x = fVar2;
    pVVar4[4].z = fVar2;
    pVVar4[4].y = fVar2;
    pVVar4[4].x = fVar2;
    pVVar4[5].z = fVar2;
    pVVar4[5].y = fVar2;
    pVVar4[5].x = fVar2;
    pVVar4[6].z = fVar2;
    pVVar4[6].y = fVar2;
    pVVar4[6].x = fVar2;
    pVVar4[7].z = fVar2;
    pVVar4[7].y = fVar2;
    pVVar4[7].x = fVar2;
    pVVar4[8].z = fVar2;
    pVVar4[8].y = fVar2;
    pVVar4[8].x = fVar2;
    pVVar4[9].z = fVar2;
    pVVar4[9].y = fVar2;
    pVVar4[9].x = fVar2;
    pVVar4[10].z = fVar2;
    pVVar4[10].y = fVar2;
    pVVar4[10].x = fVar2;
    pVVar4[0xb].z = fVar2;
    pVVar4[0xb].y = fVar2;
    pVVar4[0xb].x = fVar2;
    pVVar4[0xc].z = fVar2;
    pVVar4[0xc].y = fVar2;
    pVVar4[0xc].x = fVar2;
    pVVar4[0xd].z = fVar2;
    pVVar4[0xd].y = fVar2;
    pVVar4[0xd].x = fVar2;
    pVVar4[0xe].z = fVar2;
    pVVar4[0xe].y = fVar2;
    pVVar4[0xe].x = fVar2;
    pVVar4[0xf].z = fVar2;
    pVVar4[0xf].y = fVar2;
    pVVar4[0xf].x = fVar2;
    fVar3 = FLOAT_80331898;
    pVVar4 = pVVar4 + 0x10;
    iVar14 = iVar14 + -1;
  } while (iVar14 != 0);
  iVar14 = 0x121 - iVar5;
  pVVar4 = pVVar12 + iVar5;
  if (iVar5 < 0x121) {
    do {
      pVVar4->z = fVar3;
      pVVar4->y = fVar3;
      pVVar4->x = fVar3;
      pVVar4 = pVVar4 + 1;
      iVar14 = iVar14 + -1;
    } while (iVar14 != 0);
  }
  iVar5 = 0;
  iVar14 = 0;
  do {
    uVar1 = *(ushort *)(iVar11 + iVar14);
    uVar6 = (uint)*(ushort *)(iVar11 + iVar14 + 2);
    uVar9 = (uint)*(ushort *)(iVar11 + iVar14 + 4);
    pfVar7 = (float *)(iVar13 + (uint)uVar1 * 0xc);
    iVar14 = iVar14 + 6;
    pfVar8 = (float *)(iVar13 + uVar6 * 0xc);
    local_30.x = *pfVar8 - *pfVar7;
    pfVar10 = (float *)(iVar13 + uVar9 * 0xc);
    local_30.y = pfVar8[1] - pfVar7[1];
    local_30.z = pfVar8[2] - pfVar7[2];
    local_3c.x = *pfVar10 - *pfVar7;
    local_3c.y = pfVar10[1] - pfVar7[1];
    local_3c.z = pfVar10[2] - pfVar7[2];
    PSVECCrossProduct(&local_30,&local_3c,&VStack_48);
    PSVECNormalize(&VStack_48,&VStack_48);
    PSVECAdd(pVVar12 + uVar1,&VStack_48,pVVar12 + uVar1);
    PSVECAdd(pVVar12 + uVar6,&VStack_48,pVVar12 + uVar6);
    PSVECAdd(pVVar12 + uVar9,&VStack_48,pVVar12 + uVar9);
    iVar5 = iVar5 + 1;
  } while (iVar5 < 0x200);
  iVar5 = 0;
  pVVar4 = pVVar12;
  do {
    PSVECNormalize(pVVar4,pVVar4);
    iVar5 = iVar5 + 1;
    pVVar4 = pVVar4 + 1;
  } while (iVar5 < 0x121);
  DCFlushRange(pVVar12,0xd8c);
  return;
}


// Function: InitAnmWork__11CFunnyShapeFv
// Entry: 80051b8c
// Size: 500 bytes

/* WARNING: Removing unreachable block (ram,0x80051d64) */
/* WARNING: Removing unreachable block (ram,0x80051d5c) */
/* WARNING: Removing unreachable block (ram,0x80051d54) */
/* WARNING: Removing unreachable block (ram,0x80051d4c) */
/* WARNING: Removing unreachable block (ram,0x80051bb4) */
/* WARNING: Removing unreachable block (ram,0x80051bac) */
/* WARNING: Removing unreachable block (ram,0x80051ba4) */
/* WARNING: Removing unreachable block (ram,0x80051b9c) */

void InitAnmWork__11CFunnyShapeFv(CFunnyShape *funnyShape)

{
  short sVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  CFunnyShape *pCVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  
  uVar3 = *(uint *)funnyShape->UnkBuff3;
  dVar9 = (double)FLOAT_8032fd6c;
  dVar10 = (double)FLOAT_8032fda4;
  dVar11 = (double)FLOAT_8032fda8;
  iVar7 = 0;
  pCVar8 = funnyShape;
  dVar12 = DOUBLE_8032fd88;
  do {
    *(int *)pCVar8->m_maybeTexture = iVar7;
    *(undefined4 *)(pCVar8->m_maybeTexture + 4) = *(undefined4 *)(funnyShape->UnkBuff2 + 0xc);
    iVar4 = rand();
    *(float *)(pCVar8->m_maybeTexture + 8) =
         (float)((double)CONCAT44(0x43300000,
                                  iVar4 - (iVar4 / (int)*(short *)(funnyShape->UnkBuff3 + 0x2a)) *
                                          (int)*(short *)(funnyShape->UnkBuff3 + 0x2a) ^ 0x80000000)
                - dVar12);
    iVar4 = rand();
    *(float *)(pCVar8->m_maybeTexture + 0xc) =
         (float)((double)CONCAT44(0x43300000,
                                  iVar4 - (iVar4 / (int)*(short *)(funnyShape->UnkBuff3 + 0x2a)) *
                                          (int)*(short *)(funnyShape->UnkBuff3 + 0x2a) ^ 0x80000000)
                - dVar12);
    *(float *)(pCVar8->m_maybeTexture + 0x10) = (float)dVar9;
    iVar4 = rand();
    sVar1 = *(short *)(*(int *)(funnyShape->UnkBuff2 + 0xc) + 6);
    *(short *)(pCVar8->m_maybeTexture + 0x14) = (short)iVar4 - (short)(iVar4 / (int)sVar1) * sVar1;
    pCVar8->m_maybeTexture[0x16] = '\x02';
    pCVar8->m_maybeTexture[0x17] = '\0';
    *(float *)(pCVar8->m_maybeTexture + 0x24) = (float)dVar9;
    *(float *)(pCVar8->m_maybeTexture + 0x20) = (float)dVar9;
    iVar5 = rand();
    iVar4 = iVar5 / 0x168 + (iVar5 >> 0x1f);
    *(float *)(pCVar8->m_maybeTexture + 0x28) =
         (float)((double)CONCAT44(0x43300000,iVar5 + (iVar4 - (iVar4 >> 0x1f)) * -0x168 ^ 0x80000000
                                 ) - dVar12);
    *(float *)(pCVar8->m_maybeTexture + 0x28) =
         (float)((double)(float)(dVar10 * (double)*(float *)(pCVar8->m_maybeTexture + 0x28)) /
                dVar11);
    uVar6 = rand();
    if ((uVar6 & 1 ^ uVar6 >> 0x1f) != uVar6 >> 0x1f) {
      *(float *)(pCVar8->m_maybeTexture + 8) =
           *(float *)(pCVar8->m_maybeTexture + 8) * FLOAT_8032fd80;
    }
    uVar6 = rand();
    if ((uVar6 & 1 ^ uVar6 >> 0x1f) != uVar6 >> 0x1f) {
      *(float *)(pCVar8->m_maybeTexture + 0xc) =
           *(float *)(pCVar8->m_maybeTexture + 0xc) * FLOAT_8032fd80;
    }
    fVar2 = FLOAT_8032fd6c;
    if ((uVar3 >> 7 & 1) != 1) {
      pCVar8->m_maybeTexture[0x14] = '\0';
      pCVar8->m_maybeTexture[0x15] = '\0';
      *(float *)(pCVar8->m_maybeTexture + 0xc) = fVar2;
      *(float *)(pCVar8->m_maybeTexture + 8) = fVar2;
    }
    iVar7 = iVar7 + 1;
    pCVar8 = (CFunnyShape *)(pCVar8->m_maybeTexture + 0x30);
  } while (iVar7 < 0x200);
  return;
}


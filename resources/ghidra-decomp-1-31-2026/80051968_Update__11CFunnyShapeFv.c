// Function: Update__11CFunnyShapeFv
// Entry: 80051968
// Size: 548 bytes

void Update__11CFunnyShapeFv(CFunnyShape *funnyShape)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  CFunnyShape *pCVar8;
  
  if ((funnyShape->field_0x60d4 != '\0') && (*(int *)(funnyShape->UnkBuff2 + 0xc) != 0)) {
    uVar7 = *(uint *)funnyShape->UnkBuff3 >> 7 & 1 ^ 1;
    pCVar8 = funnyShape;
    for (iVar6 = 0; iVar6 < *(short *)(funnyShape->UnkBuff3 + 0x28); iVar6 = iVar6 + 1) {
      *(short *)(pCVar8->m_maybeTexture + 0x16) = *(short *)(pCVar8->m_maybeTexture + 0x16) + -0x200
      ;
      if (*(short *)(pCVar8->m_maybeTexture + 0x16) < 1) {
        *(short *)(pCVar8->m_maybeTexture + 0x14) = *(short *)(pCVar8->m_maybeTexture + 0x14) + 1;
        if (*(short *)(*(int *)(funnyShape->UnkBuff2 + 0xc) + 6) <=
            *(short *)(pCVar8->m_maybeTexture + 0x14)) {
          pCVar8->m_maybeTexture[0x14] = '\0';
          pCVar8->m_maybeTexture[0x15] = '\0';
          iVar3 = rand();
          *(float *)(pCVar8->m_maybeTexture + 8) =
               (float)((double)CONCAT44(0x43300000,
                                        iVar3 - (iVar3 / (int)*(short *)(funnyShape->UnkBuff3 + 0x2a
                                                                        )) *
                                                (int)*(short *)(funnyShape->UnkBuff3 + 0x2a) ^
                                        0x80000000) - DOUBLE_8032fd88);
          iVar3 = rand();
          fVar1 = FLOAT_8032fd6c;
          *(float *)(pCVar8->m_maybeTexture + 0xc) =
               (float)((double)CONCAT44(0x43300000,
                                        iVar3 - (iVar3 / (int)*(short *)(funnyShape->UnkBuff3 + 0x2a
                                                                        )) *
                                                (int)*(short *)(funnyShape->UnkBuff3 + 0x2a) ^
                                        0x80000000) - DOUBLE_8032fd88);
          *(float *)(pCVar8->m_maybeTexture + 0x10) = fVar1;
          pCVar8->m_maybeTexture[0x16] = '\x02';
          pCVar8->m_maybeTexture[0x17] = '\0';
          *(float *)(pCVar8->m_maybeTexture + 0x24) = fVar1;
          *(float *)(pCVar8->m_maybeTexture + 0x20) = fVar1;
          iVar4 = rand();
          fVar2 = FLOAT_8032fda8;
          fVar1 = FLOAT_8032fda4;
          iVar3 = iVar4 / 0x168 + (iVar4 >> 0x1f);
          *(float *)(pCVar8->m_maybeTexture + 0x28) =
               (float)((double)CONCAT44(0x43300000,
                                        iVar4 + (iVar3 - (iVar3 >> 0x1f)) * -0x168 ^ 0x80000000) -
                      DOUBLE_8032fd88);
          *(float *)(pCVar8->m_maybeTexture + 0x28) =
               (fVar1 * *(float *)(pCVar8->m_maybeTexture + 0x28)) / fVar2;
          uVar5 = rand();
          if ((uVar5 & 1 ^ uVar5 >> 0x1f) != uVar5 >> 0x1f) {
            *(float *)(pCVar8->m_maybeTexture + 8) =
                 *(float *)(pCVar8->m_maybeTexture + 8) * FLOAT_8032fd80;
          }
          uVar5 = rand();
          if ((uVar5 & 1 ^ uVar5 >> 0x1f) != uVar5 >> 0x1f) {
            *(float *)(pCVar8->m_maybeTexture + 0xc) =
                 *(float *)(pCVar8->m_maybeTexture + 0xc) * FLOAT_8032fd80;
          }
          fVar1 = FLOAT_8032fd6c;
          if (uVar7 != 0) {
            pCVar8->m_maybeTexture[0x14] = '\0';
            pCVar8->m_maybeTexture[0x15] = '\0';
            *(float *)(pCVar8->m_maybeTexture + 0xc) = fVar1;
            *(float *)(pCVar8->m_maybeTexture + 8) = fVar1;
          }
        }
        *(undefined2 *)(pCVar8->m_maybeTexture + 0x16) =
             *(undefined2 *)
              (*(int *)(funnyShape->UnkBuff2 + 0xc) + *(short *)(pCVar8->m_maybeTexture + 0x14) * 8
              + 0x12);
      }
      if (uVar7 != 0) {
        return;
      }
      pCVar8 = (CFunnyShape *)(pCVar8->m_maybeTexture + 0x30);
    }
  }
  return;
}


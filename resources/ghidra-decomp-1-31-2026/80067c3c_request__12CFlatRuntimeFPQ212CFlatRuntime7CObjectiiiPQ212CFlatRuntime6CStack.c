// Function: request__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStack
// Entry: 80067c3c
// Size: 1144 bytes

undefined4
request__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStack
          (CFlatRuntime *flatRuntime,int param_2,int param_3,int param_4,int param_5,CStack *cstack)

{
  CStack *pCVar1;
  byte bVar2;
  short sVar3;
  uint32_t *puVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  CStack *pCVar8;
  uint uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  uint uVar20;
  
  iVar12 = *(int *)(param_2 + 0x18);
  if ((int)((uint)*(byte *)(iVar12 + 0x38) << 0x18) < 0) {
    return 1;
  }
  if ((*(short *)(iVar12 + 0x16) < 0) || (((param_3 != 2 && (param_3 != 3)) || (param_4 < 0)))) {
    iVar5 = flatRuntime->m_funcCount;
    puVar6 = (undefined4 *)flatRuntime->m_funcsPtr;
    if (0 < iVar5) {
      do {
        if ((puVar6[0x10] == param_3) && (puVar6[0x11] == param_4)) goto LAB_80067cf4;
        puVar6 = puVar6 + 0x14;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
  }
  else {
    iVar5 = *(int *)((int)flatRuntime->m_classesPtr +
                    *(short *)(iVar12 + 0x16) * 0x22c + 0x24 + param_4 * 4);
    if (-1 < iVar5) {
      puVar6 = (undefined4 *)((int)flatRuntime->m_funcsPtr + iVar5 * 0x50);
      goto LAB_80067cf4;
    }
  }
  puVar6 = (undefined4 *)0x0;
LAB_80067cf4:
  if (puVar6 == (undefined4 *)0x0) {
    return 0;
  }
  iVar5 = puVar6[0x12];
  if (-1 < iVar5) {
    uVar9 = (uint)*(ushort *)(iVar12 + 0x34);
    iVar7 = 0x1f;
    iVar19 = 4;
    do {
      iVar13 = iVar7;
      if ((((uVar9 & 0x80000000) != 0) || (iVar13 = iVar7 + -1, (uVar9 & 0x40000000) != 0)) ||
         ((iVar13 = iVar7 + -2, (uVar9 & 0x20000000) != 0 ||
          ((((iVar13 = iVar7 + -3, (uVar9 & 0x10000000) != 0 ||
             (iVar13 = iVar7 + -4, (uVar9 & 0x8000000) != 0)) ||
            (iVar13 = iVar7 + -5, (uVar9 & 0x4000000) != 0)) ||
           ((iVar13 = iVar7 + -6, (uVar9 & 0x2000000) != 0 ||
            (iVar13 = iVar7 + -7, (uVar9 & 0x1000000) != 0)))))))) goto LAB_80067dc8;
      uVar9 = uVar9 << 8;
      iVar7 = iVar7 + -8;
      iVar19 = iVar19 + -1;
    } while (iVar19 != 0);
    iVar13 = -1;
LAB_80067dc8:
    if (iVar5 <= iVar13) {
      return 0;
    }
    *(ushort *)(iVar12 + 0x34) = *(ushort *)(iVar12 + 0x34) | (ushort)(1 << iVar5);
  }
  iVar5 = 0;
  if (0 < param_5) {
    if (8 < param_5) {
      uVar9 = param_5 - 1U >> 3;
      iVar7 = 0;
      pCVar8 = cstack;
      if (0 < param_5 + -8) {
        do {
          iVar15 = iVar7 + 4;
          iVar16 = iVar7 + 8;
          iVar17 = iVar7 + 0xc;
          iVar18 = iVar7 + 0x10;
          *(uint32_t *)(*(int *)(iVar12 + 8) + iVar7) = pCVar8->m_arg;
          iVar14 = iVar7 + 0x14;
          iVar13 = iVar7 + 0x18;
          iVar19 = iVar7 + 0x1c;
          iVar7 = iVar7 + 0x20;
          iVar5 = iVar5 + 8;
          *(uint32_t *)(*(int *)(iVar12 + 8) + iVar15) = pCVar8[1].m_arg;
          *(uint32_t *)(*(int *)(iVar12 + 8) + iVar16) = pCVar8[2].m_arg;
          *(uint32_t *)(*(int *)(iVar12 + 8) + iVar17) = pCVar8[3].m_arg;
          *(uint32_t *)(*(int *)(iVar12 + 8) + iVar18) = pCVar8[4].m_arg;
          *(uint32_t *)(*(int *)(iVar12 + 8) + iVar14) = pCVar8[5].m_arg;
          *(uint32_t *)(*(int *)(iVar12 + 8) + iVar13) = pCVar8[6].m_arg;
          pCVar1 = pCVar8 + 7;
          pCVar8 = pCVar8 + 8;
          *(uint32_t *)(*(int *)(iVar12 + 8) + iVar19) = pCVar1->m_arg;
          uVar9 = uVar9 - 1;
        } while (uVar9 != 0);
      }
    }
    iVar7 = iVar5 * 4;
    iVar19 = param_5 - iVar5;
    pCVar8 = cstack + iVar5;
    if (iVar5 < param_5) {
      do {
        puVar4 = &pCVar8->m_arg;
        pCVar8 = pCVar8 + 1;
        iVar5 = iVar5 + 1;
        *(uint32_t *)(*(int *)(iVar12 + 8) + iVar7) = *puVar4;
        iVar7 = iVar7 + 4;
        iVar19 = iVar19 + -1;
      } while (iVar19 != 0);
    }
  }
  *(int *)(iVar12 + 8) = *(int *)(iVar12 + 8) + iVar5 * 4;
  uVar10 = *(undefined4 *)(iVar12 + 0x1c);
  bVar2 = *(byte *)(iVar12 + 0x38);
  uVar11 = *(undefined4 *)(iVar12 + 0xc);
  iVar7 = *(int *)(iVar12 + 0x28);
  iVar5 = *(int *)(iVar12 + 0x2c);
  sVar3 = *(short *)(iVar12 + 0x36);
  if (puVar6[0x13] == 0) {
    *(int *)(iVar12 + 0xc) = *(int *)(iVar12 + 8) + puVar6[9] * -4;
    *(int *)(iVar12 + 8) = *(int *)(iVar12 + 0xc) + puVar6[10] * 4;
  }
  else {
    *(int *)(iVar12 + 8) = *(int *)(iVar12 + 8) + -4;
    *(short *)(iVar12 + 0x36) = (short)**(undefined4 **)(iVar12 + 8);
    *(int *)(iVar12 + 0xc) = *(int *)(iVar12 + 8) + *(short *)(iVar12 + 0x36) * -4;
    *(int *)(iVar12 + 8) = *(int *)(iVar12 + 0xc) + *(short *)(iVar12 + 0x36) * 4;
  }
  *(ushort *)(iVar12 + 0x1c) = (ushort)((int)(short)*puVar6 << 4) | *(ushort *)(iVar12 + 0x1c) & 0xf
  ;
  *(uint *)(iVar12 + 0x1c) = *(uint *)(iVar12 + 0x1c) & 0xfff00000;
  *(byte *)(iVar12 + 0x38) = *(byte *)(iVar12 + 0x38) & 0xdf | 0x20;
  *(undefined4 *)(iVar12 + 0x28) = 0;
  *(undefined4 *)(iVar12 + 0x2c) = 0;
  **(undefined4 **)(iVar12 + 8) = uVar11;
  *(int *)(iVar12 + 8) = *(int *)(iVar12 + 8) + 4;
  **(undefined4 **)(iVar12 + 8) = uVar10;
  *(int *)(iVar12 + 8) = *(int *)(iVar12 + 8) + 4;
  **(int **)(iVar12 + 8) = (int)((uint)bVar2 << 0x1a | (uint)(bVar2 >> 6)) >> 0x1f;
  *(int *)(iVar12 + 8) = *(int *)(iVar12 + 8) + 4;
  **(uint **)(iVar12 + 8) = (int)sVar3 | iVar7 << 0x10 | iVar5 << 0xf;
  *(int *)(iVar12 + 8) = *(int *)(iVar12 + 8) + 4;
  uVar9 = puVar6[10] - puVar6[9];
  if ((uVar9 != 0) &&
     (puVar6 = (undefined4 *)(*(int *)(iVar12 + 0xc) + puVar6[9] * 4), 0 < (int)uVar9)) {
    uVar20 = uVar9 >> 3;
    if (uVar20 != 0) {
      do {
        *puVar6 = 0;
        puVar6[1] = 0;
        puVar6[2] = 0;
        puVar6[3] = 0;
        puVar6[4] = 0;
        puVar6[5] = 0;
        puVar6[6] = 0;
        puVar6[7] = 0;
        puVar6 = puVar6 + 8;
        uVar20 = uVar20 - 1;
      } while (uVar20 != 0);
      uVar9 = uVar9 & 7;
      if (uVar9 == 0) {
        return 1;
      }
    }
    do {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
      uVar9 = uVar9 - 1;
    } while (uVar9 != 0);
  }
  return 1;
}


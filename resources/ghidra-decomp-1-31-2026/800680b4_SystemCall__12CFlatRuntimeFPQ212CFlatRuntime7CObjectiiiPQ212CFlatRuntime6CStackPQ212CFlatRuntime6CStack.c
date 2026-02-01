// Function: SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
// Entry: 800680b4
// Size: 1044 bytes

undefined4
SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
          (CCFlat *cflat,int param_2,int param_3,int param_4,int param_5,undefined4 *param_6,
          CStack *cstack)

{
  undefined4 *puVar1;
  byte bVar2;
  short sVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int iVar8;
  uint32_t uVar9;
  int iVar10;
  int iVar11;
  uint32_t *puVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  CObject *object;
  uint uVar18;
  uint uVar19;
  
  if (param_2 == 0) {
    param_2 = (**(code **)(*(int *)cflat + 0x3c))(cflat,1);
  }
  object = *(CObject **)(param_2 + 0x18);
  if ((int)((uint)object->m_flags << 0x18) < 0) {
    return 1;
  }
  if ((*(short *)&object->field_0x16 < 0) || (((param_3 != 2 && (param_3 != 3)) || (param_4 < 0))))
  {
    iVar4 = *(int *)&cflat->field_0x1c;
    puVar6 = *(undefined4 **)&cflat->field_0x20;
    if (0 < iVar4) {
      do {
        if ((puVar6[0x10] == param_3) && (puVar6[0x11] == param_4)) goto LAB_800681ac;
        puVar6 = puVar6 + 0x14;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
LAB_800681a8:
    puVar6 = (undefined4 *)0x0;
  }
  else {
    iVar4 = *(int *)(*(int *)&cflat->field_0x18 +
                    *(short *)&object->field_0x16 * 0x22c + 0x24 + param_4 * 4);
    if (iVar4 < 0) goto LAB_800681a8;
    puVar6 = (undefined4 *)(*(int *)&cflat->field_0x20 + iVar4 * 0x50);
  }
LAB_800681ac:
  if ((puVar6 == (undefined4 *)0x0) || (puVar6[0xc] == 0)) {
    return 0;
  }
  iVar4 = 0;
  if (0 < param_5) {
    if (8 < param_5) {
      uVar18 = param_5 - 1U >> 3;
      iVar8 = 0;
      puVar7 = param_6;
      if (0 < param_5 + -8) {
        do {
          iVar17 = iVar8 + 4;
          iVar16 = iVar8 + 8;
          iVar15 = iVar8 + 0xc;
          iVar14 = iVar8 + 0x10;
          *(undefined4 *)((int)object->m_stackPointer + iVar8) = *puVar7;
          iVar13 = iVar8 + 0x14;
          iVar11 = iVar8 + 0x18;
          iVar10 = iVar8 + 0x1c;
          iVar8 = iVar8 + 0x20;
          iVar4 = iVar4 + 8;
          *(undefined4 *)((int)object->m_stackPointer + iVar17) = puVar7[1];
          *(undefined4 *)((int)object->m_stackPointer + iVar16) = puVar7[2];
          *(undefined4 *)((int)object->m_stackPointer + iVar15) = puVar7[3];
          *(undefined4 *)((int)object->m_stackPointer + iVar14) = puVar7[4];
          *(undefined4 *)((int)object->m_stackPointer + iVar13) = puVar7[5];
          *(undefined4 *)((int)object->m_stackPointer + iVar11) = puVar7[6];
          puVar1 = puVar7 + 7;
          puVar7 = puVar7 + 8;
          *(undefined4 *)((int)object->m_stackPointer + iVar10) = *puVar1;
          uVar18 = uVar18 - 1;
        } while (uVar18 != 0);
      }
    }
    iVar8 = iVar4 * 4;
    iVar10 = param_5 - iVar4;
    puVar7 = param_6 + iVar4;
    if (iVar4 < param_5) {
      do {
        uVar5 = *puVar7;
        puVar7 = puVar7 + 1;
        iVar4 = iVar4 + 1;
        *(undefined4 *)((int)object->m_stackPointer + iVar8) = uVar5;
        iVar8 = iVar8 + 4;
        iVar10 = iVar10 + -1;
      } while (iVar10 != 0);
    }
  }
  object->m_stackPointer = object->m_stackPointer + iVar4;
  uVar9 = object->m_codePos;
  bVar2 = object->m_flags;
  puVar12 = object->m_localBase;
  iVar8 = object->m_waitCounter;
  iVar4._0_1_ = object->m_reqFlag0;
  iVar4._1_1_ = object->m_reqFlag1;
  iVar4._2_1_ = object->m_reqFlag2;
  iVar4._3_1_ = object->m_reqFlag3;
  sVar3 = object->m_argCount;
  if (puVar6[0x13] == 0) {
    object->m_localBase = object->m_stackPointer + -puVar6[9];
    object->m_stackPointer = object->m_localBase + puVar6[10];
  }
  else {
    object->m_stackPointer = object->m_stackPointer + -1;
    object->m_argCount = (int16_t)*object->m_stackPointer;
    object->m_localBase = object->m_stackPointer + -(int)object->m_argCount;
    object->m_stackPointer = object->m_localBase + object->m_argCount;
  }
  *(ushort *)&object->m_codePos =
       (ushort)((int)(short)*puVar6 << 4) | *(ushort *)&object->m_codePos & 0xf;
  object->m_codePos = object->m_codePos & 0xfff00000;
  object->m_flags = object->m_flags & 0xdf | 0x20;
  object->m_waitCounter = 0;
  object->m_reqFlag0 = '\0';
  object->m_reqFlag1 = '\0';
  object->m_reqFlag2 = '\0';
  object->m_reqFlag3 = '\0';
  *object->m_stackPointer = (uint32_t)puVar12;
  object->m_stackPointer = object->m_stackPointer + 1;
  *object->m_stackPointer = uVar9;
  object->m_stackPointer = object->m_stackPointer + 1;
  *object->m_stackPointer = (int)((uint)bVar2 << 0x1a | (uint)(bVar2 >> 6)) >> 0x1f;
  object->m_stackPointer = object->m_stackPointer + 1;
  *object->m_stackPointer = (int)sVar3 | iVar8 << 0x10 | iVar4 << 0xf;
  object->m_stackPointer = object->m_stackPointer + 1;
  uVar18 = puVar6[10] - puVar6[9];
  if ((uVar18 != 0) && (puVar12 = object->m_localBase + puVar6[9], 0 < (int)uVar18)) {
    uVar19 = uVar18 >> 3;
    if (uVar19 != 0) {
      do {
        *puVar12 = 0;
        puVar12[1] = 0;
        puVar12[2] = 0;
        puVar12[3] = 0;
        puVar12[4] = 0;
        puVar12[5] = 0;
        puVar12[6] = 0;
        puVar12[7] = 0;
        puVar12 = puVar12 + 8;
        uVar19 = uVar19 - 1;
      } while (uVar19 != 0);
      uVar18 = uVar18 & 7;
      if (uVar18 == 0) goto LAB_80068480;
    }
    do {
      *puVar12 = 0;
      puVar12 = puVar12 + 1;
      uVar18 = uVar18 - 1;
    } while (uVar18 != 0);
  }
LAB_80068480:
  objectFrame__12CFlatRuntimeFPQ212CFlatRuntime7CObject(cflat,object);
  object->m_stackPointer = object->m_stackPointer + -1;
  if (cstack != (CStack *)0x0) {
    cstack->m_arg = *object->m_stackPointer;
  }
  return 1;
}


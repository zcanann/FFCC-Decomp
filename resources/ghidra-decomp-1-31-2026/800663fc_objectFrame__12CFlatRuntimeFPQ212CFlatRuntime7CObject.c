// Function: objectFrame__12CFlatRuntimeFPQ212CFlatRuntime7CObject
// Entry: 800663fc
// Size: 5600 bytes

undefined4
objectFrame__12CFlatRuntimeFPQ212CFlatRuntime7CObject(CFlatRuntime *flatRuntime,CObject *object)

{
  byte bVar1;
  short sVar2;
  undefined2 uVar3;
  int iVar4;
  CObject *object_00;
  undefined4 uVar5;
  void *pvVar6;
  uint uVar7;
  uint32_t *puVar8;
  float *pfVar9;
  int iVar10;
  int iVar11;
  uint32_t uVar12;
  uint32_t *puVar13;
  uint32_t uVar14;
  uint uVar15;
  uint32_t uVar16;
  undefined4 *puVar17;
  byte *pbVar18;
  double dVar19;
  int local_5c;
  undefined auStack_58 [48];
  undefined8 local_28;
  
  DumpMapFile__7CSystemFPv((CSystem *)auStack_58);
  Reset__10CStopWatchFv(auStack_58);
  Start__10CStopWatchFv(auStack_58);
  if (object->m_waitCounter != 0) goto LAB_80066e98;
  pbVar18 = (byte *)(*(int *)((int)flatRuntime->m_funcsPtr +
                             ((int)((int)*(short *)&object->m_codePos << 0x10 |
                                   (uint)(int)*(short *)&object->m_codePos >> 0x10) >> 0x14) * 0x50
                             + 0x34) +
                    ((int)(object->m_codePos << 0xc | object->m_codePos >> 0x14) >> 0xc));
LAB_80066478:
  flatRuntime->m_unk0x968 = flatRuntime->m_unk0x964;
  flatRuntime->m_unk0x96a = flatRuntime->m_unk0x966;
  uVar3 = *(undefined2 *)((int)&object->m_codePos + 2);
  flatRuntime->m_unk0x964 = *(undefined2 *)&object->m_codePos;
  flatRuntime->m_unk0x966 = uVar3;
  switch(*pbVar18) {
  case 0:
    uVar7 = *(uint *)(pbVar18 + 1);
    iVar10 = (int)uVar7 >> 8;
    if ((uVar7 & 1) == 0) {
      if ((uVar7 & 2) == 0) {
        if ((uVar7 & 4) != 0) {
          if (iVar10 < 0) {
            if ((uVar7 & 0x10) == 0) {
              puVar13 = (uint32_t *)
                        (**(code **)((int)flatRuntime->vtable + 0x28))(flatRuntime,object);
            }
            else {
              puVar13 = (uint32_t *)
                        (**(code **)((int)flatRuntime->vtable + 0x2c))(flatRuntime,object);
            }
          }
          else if ((uVar7 & 8) == 0) {
            puVar13 = object->m_localBase + iVar10;
          }
          else if ((uVar7 & 0x10) == 0) {
            puVar13 = (uint32_t *)((int)flatRuntime->m_variableValuesPtr + iVar10 * 4);
          }
          else {
            puVar13 = object->m_thisBase + iVar10;
          }
          object->m_stackPointer = object->m_stackPointer + -1;
          *object->m_stackPointer = *(uint32_t *)(*puVar13 + *object->m_stackPointer * 4);
          object->m_stackPointer = object->m_stackPointer + 1;
        }
      }
      else {
        if (iVar10 < 0) {
          object->m_stackPointer = object->m_stackPointer + -1;
          if ((uVar7 & 0x10) == 0) {
            puVar13 = (uint32_t *)
                      (**(code **)((int)flatRuntime->vtable + 0x28))
                                (flatRuntime,object,iVar10 + *object->m_stackPointer);
          }
          else {
            puVar13 = (uint32_t *)
                      (**(code **)((int)flatRuntime->vtable + 0x2c))
                                (flatRuntime,object,iVar10 + *object->m_stackPointer);
          }
        }
        else if ((uVar7 & 8) == 0) {
          object->m_stackPointer = object->m_stackPointer + -1;
          puVar13 = object->m_localBase + iVar10 + *object->m_stackPointer;
        }
        else if ((uVar7 & 0x10) == 0) {
          object->m_stackPointer = object->m_stackPointer + -1;
          puVar13 = (uint32_t *)
                    ((int)flatRuntime->m_variableValuesPtr + (iVar10 + *object->m_stackPointer) * 4)
          ;
        }
        else {
          object->m_stackPointer = object->m_stackPointer + -1;
          puVar13 = object->m_thisBase + iVar10 + *object->m_stackPointer;
        }
        *object->m_stackPointer = *puVar13;
        object->m_stackPointer = object->m_stackPointer + 1;
      }
    }
    else {
      if (iVar10 < 0) {
        if ((uVar7 & 0x10) == 0) {
          puVar13 = (uint32_t *)(**(code **)((int)flatRuntime->vtable + 0x28))(flatRuntime,object);
        }
        else {
          puVar13 = (uint32_t *)(**(code **)((int)flatRuntime->vtable + 0x2c))(flatRuntime,object);
        }
      }
      else if ((uVar7 & 8) == 0) {
        puVar13 = object->m_localBase + iVar10;
      }
      else if ((uVar7 & 0x10) == 0) {
        puVar13 = (uint32_t *)((int)flatRuntime->m_variableValuesPtr + iVar10 * 4);
      }
      else {
        puVar13 = object->m_thisBase + iVar10;
      }
      *object->m_stackPointer = *puVar13;
      object->m_stackPointer = object->m_stackPointer + 1;
    }
    break;
  case 1:
    uVar7 = *(uint *)(pbVar18 + 1);
    iVar10 = (int)uVar7 >> 8;
    if ((uVar7 & 1) == 0) {
      if ((uVar7 & 2) == 0) {
        if ((uVar7 & 4) != 0) {
          if (iVar10 < 0) {
            if ((uVar7 & 0x10) == 0) {
              puVar13 = (uint32_t *)
                        (**(code **)((int)flatRuntime->vtable + 0x28))(flatRuntime,object);
            }
            else {
              puVar13 = (uint32_t *)
                        (**(code **)((int)flatRuntime->vtable + 0x2c))(flatRuntime,object);
            }
          }
          else if ((uVar7 & 8) == 0) {
            puVar13 = object->m_localBase + iVar10;
          }
          else if ((uVar7 & 0x10) == 0) {
            puVar13 = (uint32_t *)((int)flatRuntime->m_variableValuesPtr + iVar10 * 4);
          }
          else {
            puVar13 = object->m_thisBase + iVar10;
          }
          object->m_stackPointer = object->m_stackPointer + -1;
          *object->m_stackPointer = *puVar13 + *object->m_stackPointer * 4;
          object->m_stackPointer = object->m_stackPointer + 1;
        }
      }
      else {
        if (iVar10 < 0) {
          object->m_stackPointer = object->m_stackPointer + -1;
          if ((uVar7 & 0x10) == 0) {
            puVar13 = (uint32_t *)
                      (**(code **)((int)flatRuntime->vtable + 0x28))
                                (flatRuntime,object,iVar10 + *object->m_stackPointer);
          }
          else {
            puVar13 = (uint32_t *)
                      (**(code **)((int)flatRuntime->vtable + 0x2c))
                                (flatRuntime,object,iVar10 + *object->m_stackPointer);
          }
        }
        else if ((uVar7 & 8) == 0) {
          object->m_stackPointer = object->m_stackPointer + -1;
          puVar13 = object->m_localBase + iVar10 + *object->m_stackPointer;
        }
        else if ((uVar7 & 0x10) == 0) {
          object->m_stackPointer = object->m_stackPointer + -1;
          puVar13 = (uint32_t *)
                    ((int)flatRuntime->m_variableValuesPtr + (iVar10 + *object->m_stackPointer) * 4)
          ;
        }
        else {
          object->m_stackPointer = object->m_stackPointer + -1;
          puVar13 = object->m_thisBase + iVar10 + *object->m_stackPointer;
        }
        *object->m_stackPointer = (uint32_t)puVar13;
        object->m_stackPointer = object->m_stackPointer + 1;
      }
    }
    else {
      if (iVar10 < 0) {
        if ((uVar7 & 0x10) == 0) {
          puVar13 = (uint32_t *)(**(code **)((int)flatRuntime->vtable + 0x28))(flatRuntime,object);
        }
        else {
          puVar13 = (uint32_t *)(**(code **)((int)flatRuntime->vtable + 0x2c))(flatRuntime,object);
        }
      }
      else if ((uVar7 & 8) == 0) {
        puVar13 = object->m_localBase + iVar10;
      }
      else if ((uVar7 & 0x10) == 0) {
        puVar13 = (uint32_t *)((int)flatRuntime->m_variableValuesPtr + iVar10 * 4);
      }
      else {
        puVar13 = object->m_thisBase + iVar10;
      }
      *object->m_stackPointer = (uint32_t)puVar13;
      object->m_stackPointer = object->m_stackPointer + 1;
    }
    break;
  case 2:
    uVar7 = *(uint *)(pbVar18 + 1);
    if (object->m_engineObject == (void *)0x0) {
      uVar15 = 1;
    }
    else {
      uVar15 = (uint)*(short *)((int)object->m_engineObject + 0x30);
    }
    if ((uVar7 & 1) == 0) {
      if ((uVar7 & 2) != 0) {
        object->m_stackPointer = object->m_stackPointer + -1;
        *object->m_stackPointer =
             -(uVar7 >> 4 & 1) & 0x1000 |
             uVar15 & 0xfff | (((int)uVar7 >> 8) + *object->m_stackPointer) * 0x2000;
        object->m_stackPointer = object->m_stackPointer + 1;
      }
    }
    else {
      *object->m_stackPointer =
           ((int)uVar7 >> 8) << 0xd | uVar15 & 0xfff | -(uVar7 >> 4 & 1) & 0x1000;
      object->m_stackPointer = object->m_stackPointer + 1;
    }
    break;
  case 3:
    *object->m_stackPointer = *(uint32_t *)(pbVar18 + 1);
    object->m_stackPointer = object->m_stackPointer + 1;
    break;
  case 4:
    *object->m_stackPointer = *(uint32_t *)(pbVar18 + 1);
    object->m_stackPointer = object->m_stackPointer + 1;
    break;
  case 5:
    *object->m_stackPointer = *(uint32_t *)(pbVar18 + 1);
    object->m_stackPointer = object->m_stackPointer + 1;
    break;
  case 6:
    if ((int)*(uint *)(pbVar18 + 1) >> 0x10 == 0) {
      object->m_stackPointer = object->m_stackPointer + 2;
    }
    else {
      puVar13 = object->m_stackPointer + (-3 - (*(uint *)(pbVar18 + 1) & 0xffff));
      puVar17 = (undefined4 *)(**(code **)((int)flatRuntime->vtable + 0x3c))(flatRuntime,*puVar13);
      puVar13[1] = (uint32_t)object->m_thisBase;
      uVar7 = 0xffff;
      if (-1 < object->m_classIndex) {
        uVar7 = (int)object->m_classIndex;
      }
      puVar13[2] = (int)*(short *)((int)object->m_engineObject + 0x30) << 0x10 | uVar7;
      object->m_thisBase = (uint32_t *)*puVar17;
      object->m_classIndex = *(int16_t *)(puVar17 + 5);
      object->m_engineObject = puVar17;
    }
    break;
  case 7:
    uVar7 = object->m_codePos;
    iVar10 = (int)(uVar7 << 0xc | uVar7 >> 0x14) >> 0xc;
    iVar11 = (*(uint *)(pbVar18 + 1) & 0xffffff) - iVar10;
    pbVar18 = pbVar18 + iVar11;
    object->m_codePos = iVar10 + iVar11 & 0xfffffU | uVar7 & 0xfff00000;
    goto LAB_80066478;
  case 8:
    object->m_stackPointer = object->m_stackPointer + -1;
    if (*object->m_stackPointer == 0) {
      uVar7 = *(uint *)(pbVar18 + 1);
      if ((int)uVar7 >> 0x18 != 0) {
        *object->m_stackPointer = 0;
        object->m_stackPointer = object->m_stackPointer + 1;
      }
      uVar15 = object->m_codePos;
      iVar10 = (int)(uVar15 << 0xc | uVar15 >> 0x14) >> 0xc;
      iVar11 = (uVar7 & 0xffffff) - iVar10;
      pbVar18 = pbVar18 + iVar11;
      object->m_codePos = iVar10 + iVar11 & 0xfffffU | uVar15 & 0xfff00000;
      goto LAB_80066478;
    }
    break;
  case 9:
    object->m_stackPointer = object->m_stackPointer + -1;
    if (*object->m_stackPointer != 0) {
      uVar7 = *(uint *)(pbVar18 + 1);
      if ((int)uVar7 >> 0x18 != 0) {
        *object->m_stackPointer = 1;
        object->m_stackPointer = object->m_stackPointer + 1;
      }
      uVar15 = object->m_codePos;
      iVar10 = (int)(uVar15 << 0xc | uVar15 >> 0x14) >> 0xc;
      iVar11 = (uVar7 & 0xffffff) - iVar10;
      pbVar18 = pbVar18 + iVar11;
      object->m_codePos = iVar10 + iVar11 & 0xfffffU | uVar15 & 0xfff00000;
      goto LAB_80066478;
    }
    break;
  case 10:
    puVar17 = (undefined4 *)
              ((int)flatRuntime->m_funcsPtr + (*(uint *)(pbVar18 + 1) & 0xffff) * 0x50);
    if (-1 < (int)*(uint *)(pbVar18 + 1) >> 0x10) goto code_r0x80066c9c;
    goto LAB_80066ccc;
  case 0xb:
    object_00 = (CObject *)createObject__12CFlatRuntimeFi(flatRuntime,*(undefined4 *)(pbVar18 + 1));
    iVar10 = 0;
    puVar17 = (undefined4 *)
              ((int)flatRuntime->m_funcsPtr +
              *(int *)((int)flatRuntime->m_classesPtr +
                      *(short *)&object_00->field_0x16 * 0x22c + 0x24) * 0x50);
    for (iVar11 = 0; iVar4 = puVar17[9], iVar11 < iVar4; iVar11 = iVar11 + 1) {
      *(uint32_t *)((int)object_00->m_stackPointer + iVar10) =
           object->m_stackPointer[iVar11 - iVar4];
      iVar10 = iVar10 + 4;
    }
    object_00->m_stackPointer = object_00->m_stackPointer + iVar4;
    uVar12 = object_00->m_codePos;
    bVar1 = object_00->m_flags;
    puVar13 = object_00->m_localBase;
    iVar11 = object_00->m_waitCounter;
    iVar10._0_1_ = object_00->m_reqFlag0;
    iVar10._1_1_ = object_00->m_reqFlag1;
    iVar10._2_1_ = object_00->m_reqFlag2;
    iVar10._3_1_ = object_00->m_reqFlag3;
    sVar2 = object_00->m_argCount;
    if (puVar17[0x13] == 0) {
      object_00->m_localBase = object_00->m_stackPointer + -puVar17[9];
      object_00->m_stackPointer = object_00->m_localBase + puVar17[10];
    }
    else {
      object_00->m_stackPointer = object_00->m_stackPointer + -1;
      object_00->m_argCount = (int16_t)*object_00->m_stackPointer;
      object_00->m_localBase = object_00->m_stackPointer + -(int)object_00->m_argCount;
      object_00->m_stackPointer = object_00->m_localBase + object_00->m_argCount;
    }
    *(ushort *)&object_00->m_codePos =
         (ushort)((int)(short)*puVar17 << 4) | *(ushort *)&object_00->m_codePos & 0xf;
    object_00->m_codePos = object_00->m_codePos & 0xfff00000;
    object_00->m_flags = object_00->m_flags & 0xdf | 0x20;
    object_00->m_waitCounter = 0;
    object_00->m_reqFlag0 = '\0';
    object_00->m_reqFlag1 = '\0';
    object_00->m_reqFlag2 = '\0';
    object_00->m_reqFlag3 = '\0';
    *object_00->m_stackPointer = (uint32_t)puVar13;
    object_00->m_stackPointer = object_00->m_stackPointer + 1;
    *object_00->m_stackPointer = uVar12;
    object_00->m_stackPointer = object_00->m_stackPointer + 1;
    *object_00->m_stackPointer = (int)((uint)bVar1 << 0x1a | (uint)(bVar1 >> 6)) >> 0x1f;
    object_00->m_stackPointer = object_00->m_stackPointer + 1;
    *object_00->m_stackPointer = (int)sVar2 | iVar11 << 0x10 | iVar10 << 0xf;
    object_00->m_stackPointer = object_00->m_stackPointer + 1;
    uVar7 = puVar17[10] - puVar17[9];
    if ((uVar7 != 0) && (puVar13 = object_00->m_localBase + puVar17[9], 0 < (int)uVar7)) {
      uVar15 = uVar7 >> 3;
      if (uVar15 != 0) {
        do {
          *puVar13 = 0;
          puVar13[1] = 0;
          puVar13[2] = 0;
          puVar13[3] = 0;
          puVar13[4] = 0;
          puVar13[5] = 0;
          puVar13[6] = 0;
          puVar13[7] = 0;
          puVar13 = puVar13 + 8;
          uVar15 = uVar15 - 1;
        } while (uVar15 != 0);
        uVar7 = uVar7 & 7;
        if (uVar7 == 0) goto LAB_80067160;
      }
      do {
        *puVar13 = 0;
        puVar13 = puVar13 + 1;
        uVar7 = uVar7 - 1;
      } while (uVar7 != 0);
    }
LAB_80067160:
    objectFrame__12CFlatRuntimeFPQ212CFlatRuntime7CObject(flatRuntime,object_00);
    object_00->m_stackPointer = object_00->m_stackPointer + -1;
    object->m_stackPointer = object->m_stackPointer + -puVar17[9];
    *object->m_stackPointer = (int)object_00->m_particleId;
    object->m_stackPointer = object->m_stackPointer + 1;
    request__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStack
              (flatRuntime,object_00,2,3,0,(CStack *)0x0);
    request__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStack
              (flatRuntime,object_00,2,2,0,(CStack *)0x0);
    (**(code **)((int)object_00->m_vtable + 8))(object_00);
    break;
  case 0xc:
    object->m_stackPointer = object->m_stackPointer + -1;
    break;
  case 0xd:
    puVar13 = object->m_stackPointer;
    object->m_stackPointer = puVar13 + -1;
    puVar8 = (uint32_t *)puVar13[-2];
    puVar13[-2] = *puVar8;
    *puVar8 = puVar13[-1];
    break;
  case 0xe:
    puVar13 = object->m_stackPointer;
    object->m_stackPointer = puVar13 + -1;
    puVar8 = (uint32_t *)puVar13[-2];
    puVar13[-2] = *puVar8;
    *puVar8 = *puVar8 + puVar13[-1];
    break;
  case 0xf:
    puVar13 = object->m_stackPointer;
    object->m_stackPointer = puVar13 + -1;
    puVar8 = (uint32_t *)puVar13[-2];
    puVar13[-2] = *puVar8;
    *puVar8 = *puVar8 - puVar13[-1];
    break;
  case 0x10:
    puVar13 = object->m_stackPointer;
    object->m_stackPointer = puVar13 + -1;
    puVar8 = (uint32_t *)puVar13[-2];
    puVar13[-2] = *puVar8;
    *puVar8 = puVar13[-1];
    break;
  case 0x11:
    puVar13 = object->m_stackPointer;
    object->m_stackPointer = puVar13 + -1;
    pfVar9 = (float *)puVar13[-2];
    puVar13[-2] = (uint32_t)*pfVar9;
    *pfVar9 = *pfVar9 + (float)puVar13[-1];
    break;
  case 0x12:
    puVar13 = object->m_stackPointer;
    object->m_stackPointer = puVar13 + -1;
    pfVar9 = (float *)puVar13[-2];
    puVar13[-2] = (uint32_t)*pfVar9;
    *pfVar9 = *pfVar9 - (float)puVar13[-1];
    break;
  case 0x13:
  case 0x16:
    puVar13 = object->m_stackPointer;
    puVar8 = puVar13 + -1;
    object->m_stackPointer = puVar8;
    uVar7 = puVar13[-2];
    if ((uVar7 >> 0xc & 1) == 0) {
      (**(code **)((int)flatRuntime->vtable + 0x30))(flatRuntime,(int)uVar7 >> 0xd,puVar8,0);
    }
    else {
      uVar5 = (**(code **)((int)flatRuntime->vtable + 0x3c))(flatRuntime,uVar7 & 0xfff);
      (**(code **)((int)flatRuntime->vtable + 0x34))(flatRuntime,(int)uVar7 >> 0xd,uVar5,puVar8,0);
    }
    break;
  case 0x14:
  case 0x17:
    puVar13 = object->m_stackPointer;
    puVar8 = puVar13 + -1;
    object->m_stackPointer = puVar8;
    uVar7 = puVar13[-2];
    if ((uVar7 >> 0xc & 1) == 0) {
      (**(code **)((int)flatRuntime->vtable + 0x30))(flatRuntime,(int)uVar7 >> 0xd,puVar8,1);
    }
    else {
      uVar5 = (**(code **)((int)flatRuntime->vtable + 0x3c))(flatRuntime,uVar7 & 0xfff);
      (**(code **)((int)flatRuntime->vtable + 0x34))(flatRuntime,(int)uVar7 >> 0xd,uVar5,puVar8,1);
    }
    break;
  case 0x15:
  case 0x18:
    puVar13 = object->m_stackPointer;
    puVar8 = puVar13 + -1;
    object->m_stackPointer = puVar8;
    uVar7 = puVar13[-2];
    if ((uVar7 >> 0xc & 1) == 0) {
      (**(code **)((int)flatRuntime->vtable + 0x30))
                (flatRuntime,(int)uVar7 >> 0xd,puVar8,0xffffffff);
    }
    else {
      uVar5 = (**(code **)((int)flatRuntime->vtable + 0x3c))(flatRuntime,uVar7 & 0xfff);
      (**(code **)((int)flatRuntime->vtable + 0x34))
                (flatRuntime,(int)uVar7 >> 0xd,uVar5,puVar8,0xffffffff);
    }
    break;
  case 0x19:
  case 0x1a:
  case 0x1b:
  case 0x1c:
  case 0x1d:
  case 0x1e:
  case 0x1f:
  case 0x20:
  case 0x21:
  case 0x22:
  case 0x23:
  case 0x24:
  case 0x25:
  case 0x26:
  case 0x27:
  case 0x28:
  case 0x29:
  case 0x2a:
  case 0x2b:
    _GetCodeInfo__12CFlatRuntimeFPc(flatRuntime,object);
    break;
  case 0x2c:
    puVar13 = object->m_stackPointer;
    object->m_stackPointer = puVar13 + -1;
    uVar7 = countLeadingZeros(puVar13[-1] - puVar13[-2]);
    puVar13[-2] = uVar7 >> 5 & 0xff;
    break;
  case 0x2d:
    puVar13 = object->m_stackPointer;
    object->m_stackPointer = puVar13 + -1;
    puVar13[-2] = (puVar13[-1] - puVar13[-2] | puVar13[-2] - puVar13[-1]) >> 0x1f;
    break;
  case 0x2e:
    puVar13 = object->m_stackPointer;
    object->m_stackPointer = puVar13 + -1;
    uVar7 = puVar13[-1] ^ puVar13[-2];
    puVar13[-2] = ((int)uVar7 >> 1) - (uVar7 & puVar13[-1]) >> 0x1f;
    break;
  case 0x2f:
    puVar13 = object->m_stackPointer;
    object->m_stackPointer = puVar13 + -1;
    puVar13[-2] = ((int)puVar13[-1] >> 0x1f) +
                  ((uint)(puVar13[-2] <= puVar13[-1]) - ((int)puVar13[-2] >> 0x1f)) & 0xff;
    break;
  case 0x30:
    puVar13 = object->m_stackPointer;
    object->m_stackPointer = puVar13 + -1;
    uVar7 = puVar13[-2] ^ puVar13[-1];
    puVar13[-2] = ((int)uVar7 >> 1) - (uVar7 & puVar13[-2]) >> 0x1f;
    break;
  case 0x31:
    puVar13 = object->m_stackPointer;
    object->m_stackPointer = puVar13 + -1;
    puVar13[-2] = ((int)puVar13[-2] >> 0x1f) +
                  ((uint)(puVar13[-1] <= puVar13[-2]) - ((int)puVar13[-1] >> 0x1f)) & 0xff;
    break;
  case 0x32:
    puVar13 = object->m_stackPointer;
    object->m_stackPointer = puVar13 + -1;
    local_28 = (double)CONCAT44(0x43300000,
                                ((uint)(byte)(((float)puVar13[-2] == (float)puVar13[-1]) << 1) <<
                                0x1c) >> 0x1d);
    puVar13[-2] = (uint32_t)(float)(local_28 - DOUBLE_80330128);
    break;
  case 0x33:
    puVar13 = object->m_stackPointer;
    object->m_stackPointer = puVar13 + -1;
    local_28 = (double)(CONCAT44(0x43300000,
                                 ((uint)(byte)(((float)puVar13[-2] == (float)puVar13[-1]) << 1) <<
                                 0x1c) >> 0x1d) ^ 1);
    puVar13[-2] = (uint32_t)(float)(local_28 - DOUBLE_80330128);
    break;
  case 0x34:
    puVar13 = object->m_stackPointer;
    object->m_stackPointer = puVar13 + -1;
    local_28 = (double)CONCAT44(0x43300000,
                                ((uint)(byte)(((float)puVar13[-2] < (float)puVar13[-1]) << 3) <<
                                0x1c) >> 0x1f);
    puVar13[-2] = (uint32_t)(float)(local_28 - DOUBLE_80330128);
    break;
  case 0x35:
    puVar13 = object->m_stackPointer;
    object->m_stackPointer = puVar13 + -1;
    local_28 = (double)CONCAT44(0x43300000,
                                ((uint)(byte)(((float)puVar13[-2] <= (float)puVar13[-1]) << 1) <<
                                0x1c) >> 0x1d);
    puVar13[-2] = (uint32_t)(float)(local_28 - DOUBLE_80330128);
    break;
  case 0x36:
    puVar13 = object->m_stackPointer;
    object->m_stackPointer = puVar13 + -1;
    local_28 = (double)CONCAT44(0x43300000,
                                ((uint)(byte)(((float)puVar13[-1] < (float)puVar13[-2]) << 2) <<
                                0x1c) >> 0x1e);
    puVar13[-2] = (uint32_t)(float)(local_28 - DOUBLE_80330128);
    break;
  case 0x37:
    puVar13 = object->m_stackPointer;
    object->m_stackPointer = puVar13 + -1;
    local_28 = (double)CONCAT44(0x43300000,
                                ((uint)(byte)(((float)puVar13[-1] <= (float)puVar13[-2]) << 1) <<
                                0x1c) >> 0x1d);
    puVar13[-2] = (uint32_t)(float)(local_28 - DOUBLE_80330128);
    break;
  case 0x39:
    object->m_stackPointer = object->m_stackPointer + -1;
    uVar12 = *object->m_stackPointer;
    object->m_stackPointer = object->m_stackPointer + -1;
    uVar7 = *object->m_stackPointer;
    pvVar6 = (void *)(**(code **)((int)flatRuntime->vtable + 0x3c))(flatRuntime,uVar7 >> 0x10);
    object->m_engineObject = pvVar6;
    object->m_classIndex = (int16_t)uVar7;
    object->m_stackPointer = object->m_stackPointer + -1;
    object->m_thisBase = (uint32_t *)*object->m_stackPointer;
    object->m_stackPointer = object->m_stackPointer + -1;
    *object->m_stackPointer = uVar12;
    object->m_stackPointer = object->m_stackPointer + 1;
    break;
  case 0x3a:
    *object->m_stackPointer = object->m_stackPointer[-1];
    object->m_stackPointer = object->m_stackPointer + 1;
    break;
  case 0x3c:
    goto switchD_800664a0_caseD_3c;
  case 0x3d:
    uVar12 = (uint32_t)(float)object->m_stackPointer[-1];
    local_28 = (double)(longlong)(int)uVar12;
    object->m_stackPointer[-1] = uVar12;
    break;
  case 0x3e:
    local_28 = (double)(CONCAT44(0x43300000,object->m_stackPointer[-1]) ^ 0x80000000);
    object->m_stackPointer[-1] = (uint32_t)(float)(local_28 - DOUBLE_80330130);
    break;
  case 0x3f:
    *object->m_stackPointer = 0;
    object->m_stackPointer = object->m_stackPointer + 1;
  }
  goto switchD_800664a0_caseD_38;
code_r0x80066c9c:
  iVar10 = *(int *)((int)flatRuntime->m_classesPtr +
                   object->m_classIndex * 0x22c + puVar17[0x11] * 4 + 0x24);
  if (iVar10 < 0) goto LAB_80066478;
  puVar17 = (undefined4 *)((int)flatRuntime->m_funcsPtr + iVar10 * 0x50);
LAB_80066ccc:
  uVar12 = object->m_codePos;
  bVar1 = object->m_flags;
  puVar13 = object->m_localBase;
  iVar10 = object->m_waitCounter;
  iVar11._0_1_ = object->m_reqFlag0;
  iVar11._1_1_ = object->m_reqFlag1;
  iVar11._2_1_ = object->m_reqFlag2;
  iVar11._3_1_ = object->m_reqFlag3;
  sVar2 = object->m_argCount;
  if (puVar17[0x13] == 0) {
    object->m_localBase = object->m_stackPointer + -puVar17[9];
    object->m_stackPointer = object->m_localBase + puVar17[10];
  }
  else {
    object->m_stackPointer = object->m_stackPointer + -1;
    object->m_argCount = (int16_t)*object->m_stackPointer;
    object->m_localBase = object->m_stackPointer + -(int)object->m_argCount;
    object->m_stackPointer = object->m_localBase + object->m_argCount;
  }
  *(ushort *)&object->m_codePos =
       (ushort)((int)(short)*puVar17 << 4) | *(ushort *)&object->m_codePos & 0xf;
  object->m_codePos = object->m_codePos & 0xfff00000;
  object->m_flags = object->m_flags & 0xdf;
  object->m_waitCounter = 0;
  object->m_reqFlag0 = '\0';
  object->m_reqFlag1 = '\0';
  object->m_reqFlag2 = '\0';
  object->m_reqFlag3 = '\0';
  *object->m_stackPointer = (uint32_t)puVar13;
  object->m_stackPointer = object->m_stackPointer + 1;
  *object->m_stackPointer = uVar12;
  object->m_stackPointer = object->m_stackPointer + 1;
  *object->m_stackPointer = (int)((uint)bVar1 << 0x1a | (uint)(bVar1 >> 6)) >> 0x1f;
  object->m_stackPointer = object->m_stackPointer + 1;
  *object->m_stackPointer = (int)sVar2 | iVar10 << 0x10 | iVar11 << 0xf;
  object->m_stackPointer = object->m_stackPointer + 1;
  uVar7 = puVar17[10] - puVar17[9];
  if ((uVar7 != 0) && (puVar13 = object->m_localBase + puVar17[9], 0 < (int)uVar7)) {
    uVar15 = uVar7 >> 3;
    if (uVar15 != 0) {
      do {
        *puVar13 = 0;
        puVar13[1] = 0;
        puVar13[2] = 0;
        puVar13[3] = 0;
        puVar13[4] = 0;
        puVar13[5] = 0;
        puVar13[6] = 0;
        puVar13[7] = 0;
        puVar13 = puVar13 + 8;
        uVar15 = uVar15 - 1;
      } while (uVar15 != 0);
      uVar7 = uVar7 & 7;
      if (uVar7 == 0) goto LAB_80066e78;
    }
    do {
      *puVar13 = 0;
      puVar13 = puVar13 + 1;
      uVar7 = uVar7 - 1;
    } while (uVar7 != 0);
  }
LAB_80066e78:
  if (((puVar17[0x10] != 1) && (puVar17[0x10] != 2)) || (-1 < (int)puVar17[0x11])) {
    pbVar18 = (byte *)(*(int *)((int)flatRuntime->m_funcsPtr +
                               ((int)((int)*(short *)&object->m_codePos << 0x10 |
                                     (uint)(int)*(short *)&object->m_codePos >> 0x10) >> 0x14) *
                               0x50 + 0x34) +
                      ((int)(object->m_codePos << 0xc | object->m_codePos >> 0x14) >> 0xc));
    goto LAB_80066478;
  }
LAB_80066e98:
  iVar10 = (int)((int)*(short *)&object->m_codePos << 0x10 |
                (uint)(int)*(short *)&object->m_codePos >> 0x10) >> 0x14;
  iVar10 = systemFunc__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiRi
                     (flatRuntime,object,
                      *(undefined4 *)((int)flatRuntime->m_funcsPtr + iVar10 * 0x50 + 0x40),
                      *(undefined4 *)((int)flatRuntime->m_funcsPtr + iVar10 * 0x50 + 0x44),&local_5c
                     );
  if (iVar10 == 0) {
    *object->m_stackPointer = 0;
    object->m_stackPointer = object->m_stackPointer + 1;
  }
  else if (local_5c != 0) {
    if ((local_5c != 2) && (object->m_waitCounter < 0x708)) {
      object->m_waitCounter = object->m_waitCounter + 1;
    }
    Stop__10CStopWatchFv(auStack_58);
    dVar19 = (double)Get__10CStopWatchFv(auStack_58);
    *(float *)flatRuntime->m_workArea = (float)((double)*(float *)flatRuntime->m_workArea + dVar19);
    __ct__10CStopWatchFPc(auStack_58,0xffffffff);
    return 0;
  }
switchD_800664a0_caseD_3c:
  bVar1 = object->m_flags;
  object->m_stackPointer = object->m_stackPointer + -1;
  uVar16 = *object->m_stackPointer;
  object->m_stackPointer = object->m_stackPointer + -1;
  uVar15 = *object->m_stackPointer;
  object->m_stackPointer = object->m_stackPointer + -1;
  uVar7 = uVar15 >> 0xf & 1;
  uVar12 = *object->m_stackPointer;
  object->m_stackPointer = object->m_stackPointer + -1;
  uVar14 = *object->m_stackPointer;
  object->m_stackPointer = object->m_stackPointer + -1;
  puVar13 = (uint32_t *)*object->m_stackPointer;
  object->m_stackPointer = object->m_localBase;
  *object->m_stackPointer = uVar16;
  object->m_stackPointer = object->m_stackPointer + 1;
  object->m_localBase = puVar13;
  object->m_codePos = uVar14;
  object->m_flags = (byte)((int)(char)uVar12 << 5) & 0x20 | object->m_flags & 0xdf;
  object->m_waitCounter = (int)uVar15 >> 0x10;
  object->m_reqFlag0 = (char)(uVar7 >> 0x18);
  object->m_reqFlag1 = (char)(uVar7 >> 0x10);
  object->m_reqFlag2 = (char)(uVar7 >> 8);
  object->m_reqFlag3 = (char)uVar7;
  object->m_argCount = (int16_t)uVar15;
  if ((int)((uint)object->m_flags << 0x18) < 0) {
    __ct__10CStopWatchFPc(auStack_58,0xffffffff);
    return 0;
  }
  if ((int)((uint)bVar1 << 0x1a | (uint)(bVar1 >> 6)) < 0) {
    __ct__10CStopWatchFPc(auStack_58,0xffffffff);
    return 1;
  }
  pbVar18 = (byte *)(*(int *)((int)flatRuntime->m_funcsPtr +
                             ((int)((int)*(short *)&object->m_codePos << 0x10 |
                                   (uint)(int)*(short *)&object->m_codePos >> 0x10) >> 0x14) * 0x50
                             + 0x34) +
                    ((int)(object->m_codePos << 0xc | object->m_codePos >> 0x14) >> 0xc));
switchD_800664a0_caseD_38:
  iVar10 = 1;
  if (*pbVar18 < 0xc) {
    iVar10 = 5;
  }
  uVar7 = object->m_codePos;
  pbVar18 = pbVar18 + iVar10;
  object->m_codePos =
       ((int)(uVar7 << 0xc | uVar7 >> 0x14) >> 0xc) + iVar10 & 0xfffffU | uVar7 & 0xfff00000;
  goto LAB_80066478;
}


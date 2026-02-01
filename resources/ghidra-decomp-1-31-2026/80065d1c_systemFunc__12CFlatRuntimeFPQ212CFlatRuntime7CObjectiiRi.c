// Function: systemFunc__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiRi
// Entry: 80065d1c
// Size: 1760 bytes

undefined4
systemFunc__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiRi
          (CFlatRuntime *param_1,CObject *object,int param_3,int param_4,undefined4 *param_5)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  uint32_t *puVar4;
  CObject *pCVar5;
  char *pcVar6;
  CObject *pCVar7;
  void *pvVar8;
  int iVar9;
  int iVar10;
  uint32_t uVar11;
  char *pcVar12;
  int iVar13;
  CObject *pCVar14;
  int iVar15;
  int iVar16;
  uint32_t uVar17;
  int iVar18;
  char *pcVar19;
  undefined4 uVar20;
  char *pcVar21;
  double dVar22;
  undefined auStack_388 [48];
  undefined auStack_358 [48];
  char local_328 [256];
  char local_228 [256];
  char local_128 [264];
  
  uVar20 = 1;
  *param_5 = 1;
  if (param_3 == 1) {
    if (param_4 == -1) {
      if ((int)*object->m_localBase <= object->m_waitCounter) {
        *object->m_stackPointer = 0;
        object->m_stackPointer = object->m_stackPointer + 1;
        *param_5 = 0;
      }
    }
    else if ((param_4 < -1) && (-3 < param_4)) {
      if (param_1->m_unk0x1298 != 0) {
        pcVar19 = param_1->m_strBlob + param_1->m_strOffs[*object->m_localBase];
        if (object->m_argCount == 1) {
          Printf__7CSystemFPce(&System,pcVar19);
          Printf__7CSystemFPce(&System,&DAT_80330118);
        }
        else {
          pcVar21 = local_228 + 1;
          local_128[0] = '\0';
          for (iVar18 = 0; iVar18 < object->m_argCount + -1; iVar18 = iVar18 + 1) {
            while( true ) {
              pcVar6 = local_228;
              iVar9 = 0;
              for (; (cVar1 = *pcVar19, cVar1 != '\0' &&
                     ((iVar9 == 0 || ((iVar9 != 0 && (cVar1 != '%')))))); pcVar19 = pcVar19 + 1) {
                *pcVar6 = cVar1;
                iVar9 = iVar9 + 1;
                pcVar6 = pcVar6 + 1;
              }
              local_228[iVar9] = '\0';
              if (local_228[0] == '%') break;
              strcat(local_128,local_228);
            }
            iVar9 = iVar18 + 1;
            puVar4 = object->m_localBase;
            pcVar6 = pcVar21;
            if (local_228[0] == '%') {
              iVar10 = 1;
              iVar15 = 0;
              uVar3 = countLeadingZeros(0x30 - local_228[1]);
              uVar3 = uVar3 >> 5 & 0xff;
              for (pcVar12 = pcVar21; (cVar1 = *pcVar12, '/' < cVar1 && (cVar1 < ':'));
                  pcVar12 = pcVar12 + 1) {
                iVar10 = iVar10 + 1;
                iVar15 = (int)cVar1 + iVar15 * 10 + -0x30;
              }
              if (local_228[iVar10] != 'b') goto LAB_80066000;
              pcVar6 = local_328;
              uVar11 = puVar4[iVar9];
              iVar13 = 0;
              iVar16 = 0;
              iVar9 = iVar15;
              if (0 < iVar15) {
                do {
                  uVar2 = (int)uVar11 >> ((iVar15 - iVar16) - 1U & 0x3f) & 1;
                  if ((uVar3 == 0) && (uVar2 != 0)) {
                    uVar3 = 1;
                  }
                  if (uVar3 != 0) {
                    iVar13 = iVar13 + 1;
                    *pcVar6 = (char)uVar2 + '0';
                    pcVar6 = pcVar6 + 1;
                  }
                  iVar16 = iVar16 + 1;
                  iVar9 = iVar9 + -1;
                } while (iVar9 != 0);
              }
              local_328[iVar13] = '\0';
              strcat(local_328,local_228 + iVar10 + 1);
            }
            else {
LAB_80066000:
              while (*pcVar6 != '\0') {
                switch(*pcVar6) {
                case 'd':
                case 'x':
                  sprintf(local_328,local_228,puVar4[iVar9]);
                  goto LAB_8006600c;
                default:
                  pcVar6 = pcVar6 + 1;
                  break;
                case 'f':
                  sprintf((double)(float)puVar4[iVar9],local_328,local_228);
                  goto LAB_8006600c;
                case 's':
                  sprintf(local_328,local_228,param_1->m_strBlob + param_1->m_strOffs[puVar4[iVar9]]
                         );
                  goto LAB_8006600c;
                }
              }
            }
LAB_8006600c:
            strcat(local_128,local_328);
          }
          Printf__7CSystemFPce(&System,local_128);
          Printf__7CSystemFPce(&System,&DAT_80330118);
        }
      }
      *object->m_stackPointer = 0;
      object->m_stackPointer = object->m_stackPointer + 1;
      *param_5 = 0;
    }
    else {
      DumpMapFile__7CSystemFPv((CSystem *)auStack_358);
      Reset__10CStopWatchFv(auStack_358);
      Start__10CStopWatchFv(auStack_358);
      uVar20 = (**(code **)((int)param_1->vtable + 0x20))(param_1,object,1,param_4,param_5);
      Stop__10CStopWatchFv(auStack_358);
      dVar22 = (double)Get__10CStopWatchFv(auStack_358);
      *(float *)((int)param_1 + param_4 * -4 + 0x4c) =
           (float)((double)*(float *)((int)param_1 + param_4 * -4 + 0x4c) + dVar22);
      *(int *)((int)param_1 + param_4 * -4 + 0x44c) =
           *(int *)((int)param_1 + param_4 * -4 + 0x44c) + 1;
      __ct__10CStopWatchFPc(auStack_358,0xffffffff);
    }
  }
  else if (param_4 == -2) {
    pCVar14 = (CObject *)object->m_engineObject;
    uVar11 = *object->m_localBase;
    pCVar14->m_next->m_previous = pCVar14->m_previous;
    pCVar14->m_previous->m_next = pCVar14->m_next;
    pCVar5 = (param_1->m_objRoot).m_next;
    pCVar7 = pCVar5;
    do {
      if ((int)uVar11 < (int)pCVar7->m_scriptGroup) break;
      pCVar7 = pCVar7->m_next;
    } while (pCVar7 != pCVar5);
    pCVar7 = pCVar7->m_previous;
    pCVar14->m_next = pCVar7;
    pCVar14->m_previous = pCVar7->m_previous;
    pCVar7->m_previous->m_next = pCVar14;
    pCVar7->m_previous = pCVar14;
    pCVar14->m_scriptGroup = (int16_t)uVar11;
    *object->m_stackPointer = 0;
    object->m_stackPointer = object->m_stackPointer + 1;
    *param_5 = 0;
  }
  else {
    if (param_4 < -2) {
      if (param_4 == -4) {
        SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                  ((CCFlat *)param_1,object,2,*object->m_localBase,object->m_argCount + -1,
                   object->m_localBase + 1,(CStack *)0x0);
        *object->m_stackPointer = 0;
        object->m_stackPointer = object->m_stackPointer + 1;
        *param_5 = 0;
        return 1;
      }
      if (-5 < param_4) {
        pvVar8 = object->m_engineObject;
        uVar3 = countLeadingZeros((int)pvVar8 - (int)object);
        if (uVar3 >> 5 == 0) {
          *(undefined4 *)(*(int *)((int)pvVar8 + 0x20) + 0x24) = *(undefined4 *)((int)pvVar8 + 0x24)
          ;
          *(undefined4 *)(*(int *)((int)pvVar8 + 0x24) + 0x20) = *(undefined4 *)((int)pvVar8 + 0x20)
          ;
          *(int *)(**(int **)((int)pvVar8 + 4) + 4) = (*(int **)((int)pvVar8 + 4))[1];
          *(undefined4 *)(*(undefined4 **)((int)pvVar8 + 4))[1] = **(undefined4 **)((int)pvVar8 + 4)
          ;
          *(void **)(*(int *)((int)pvVar8 + 4) + 4) = param_1->m_freeHead;
          param_1->m_freeHead = *(void **)((int)pvVar8 + 4);
          *(byte *)((int)pvVar8 + 0x38) = *(byte *)((int)pvVar8 + 0x38) & 0xef;
          (**(code **)((int)param_1->vtable + 0x1c))();
        }
        else {
          object->m_flags = object->m_flags & 0x7f | 0x80;
        }
        *object->m_stackPointer = 0;
        object->m_stackPointer = object->m_stackPointer + 1;
        *param_5 = 0;
        return 1;
      }
    }
    else if (param_4 < 0) {
      iVar18._0_1_ = object->m_reqFlag0;
      iVar18._1_1_ = object->m_reqFlag1;
      iVar18._2_1_ = object->m_reqFlag2;
      iVar18._3_1_ = object->m_reqFlag3;
      if (iVar18 != 0) {
        *object->m_stackPointer = 0;
        object->m_stackPointer = object->m_stackPointer + 1;
        *param_5 = 0;
        return 1;
      }
      uVar11 = *object->m_localBase;
      uVar17 = object->m_localBase[1];
      object->m_waitCounter = 1;
      object->m_reqFlag0 = '\0';
      object->m_reqFlag1 = '\0';
      object->m_reqFlag2 = '\0';
      object->m_reqFlag3 = '\x01';
      iVar18 = request__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStack
                         (param_1,object,2,uVar11,object->m_argCount + -2,
                          (CStack *)(object->m_localBase + 2));
      if (iVar18 != 0) {
        if (object == (CObject *)object->m_engineObject) {
          *param_5 = 2;
          return 1;
        }
        *object->m_stackPointer = 0;
        object->m_stackPointer = object->m_stackPointer + 1;
        *param_5 = 0;
        return 1;
      }
      object->m_reqFlag0 = '\0';
      object->m_reqFlag1 = '\0';
      object->m_reqFlag2 = '\0';
      object->m_reqFlag3 = '\0';
      if (uVar17 != 0) {
        return 1;
      }
      *object->m_stackPointer = 0;
      object->m_stackPointer = object->m_stackPointer + 1;
      *param_5 = 0;
      return 1;
    }
    DumpMapFile__7CSystemFPv((CSystem *)auStack_388);
    Reset__10CStopWatchFv(auStack_388);
    Start__10CStopWatchFv(auStack_388);
    uVar20 = (**(code **)((int)param_1->vtable + 0x24))(param_1,object,param_3,param_4,param_5);
    Stop__10CStopWatchFv(auStack_388);
    dVar22 = (double)Get__10CStopWatchFv(auStack_388);
    *(float *)((int)param_1 + param_4 * -4 + 0x24c) =
         (float)((double)*(float *)((int)param_1 + param_4 * -4 + 0x24c) + dVar22);
    *(int *)((int)param_1 + param_4 * -4 + 0x64c) =
         *(int *)((int)param_1 + param_4 * -4 + 0x64c) + 1;
    __ct__10CStopWatchFPc(auStack_388,0xffffffff);
  }
  return uVar20;
}


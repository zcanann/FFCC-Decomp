// Function: pppFrameChangeTex
// Entry: 8013eff8
// Size: 1292 bytes

/* WARNING: Removing unreachable block (ram,0x8013f4e8) */
/* WARNING: Removing unreachable block (ram,0x8013f008) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameChangeTex(pppChangeTex *pppChangeTex,UnkB *param_2,UnkC *param_3)

{
  short sVar2;
  uint uVar1;
  CCharaPcsCHandle *pCVar3;
  int iVar4;
  float fVar5;
  CCharaPcsCHandle *handle;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  undefined4 *puVar13;
  float *value;
  undefined4 *puVar14;
  int iVar15;
  int *piVar16;
  double dVar17;
  undefined8 local_50;
  
  if (DAT_8032ed70 == 0) {
    iVar9 = param_3->m_serializedDataOffsets[1];
    value = (float *)((int)(&pppChangeTex->field0_0x0 + 2) + param_3->m_serializedDataOffsets[2]);
    pCVar3 = (CCharaPcsCHandle *)
             GetCharaHandlePtr__FP8CGObjectl((CGObject *)(pppMngStPtr->m_velocity).x,0);
    iVar4 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(pCVar3);
    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf
              ((float)param_2->m_initWOrk,&pppChangeTex->field0_0x0,param_2->m_graphId,value,
               value + 1,value + 2,&param_2->m_stepValue,&param_2->m_arg3);
    value[6] = (pppMngStPtr->m_velocity).x;
    value[9] = (float)pppEnvStPtr;
    *(float **)(iVar4 + 0xe4) = value;
    *(UnkB **)(iVar4 + 0xe8) = param_2;
    *(code **)(iVar4 + 0xfc) = ChangeTex_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f;
    *(code **)(iVar4 + 0x104) = ChangeTex_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f;
    fVar5 = (float)GetTextureFromRSD__FiP9_pppEnvSt(param_2->m_dataValIndex,pppEnvStPtr);
    value[7] = fVar5;
    pCVar3 = (CCharaPcsCHandle *)GetCharaHandlePtr__FP8CGObjectl((CGObject *)value[6],1);
    handle = (CCharaPcsCHandle *)GetCharaHandlePtr__FP8CGObjectl((CGObject *)value[6],2);
    if ((pCVar3 != (CCharaPcsCHandle *)0x0) &&
       (iVar6 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(pCVar3), iVar6 != 0)) {
      *(float **)(iVar6 + 0xe4) = value;
      *(UnkB **)(iVar6 + 0xe8) = param_2;
      *(code **)(iVar6 + 0xfc) = ChangeTex_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f;
      *(code **)(iVar6 + 0x104) = ChangeTex_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f;
    }
    if ((handle != (CCharaPcsCHandle *)0x0) &&
       (iVar6 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle), iVar6 != 0)) {
      *(float **)(iVar6 + 0xe4) = value;
      *(UnkB **)(iVar6 + 0xe8) = param_2;
      *(code **)(iVar6 + 0xfc) = ChangeTex_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f;
      *(code **)(iVar6 + 0x104) = ChangeTex_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f;
    }
    if ((param_2->m_payload[0] != '\0') &&
       (fVar5 = (float)GetTextureFromRSD__FiP9_pppEnvSt(param_2->m_dataValIndex,pppEnvStPtr),
       fVar5 != 0.0)) {
      value[7] = fVar5;
      iVar6 = *(int *)(iVar4 + 0xac);
      if ((value[3] == 0.0) && (value[4] == 0.0)) {
        value[0x11] = FLOAT_80332020;
        fVar5 = (float)pppMemAlloc__FUlPQ27CMemory6CStagePci
                                 (*(int *)(*(int *)(iVar4 + 0xa4) + 0xc) << 2,
                                  pppEnvStPtr->m_stagePtr,s_pppChangeTex_cpp_801dd660,0x163);
        value[3] = fVar5;
        fVar5 = (float)pppMemAlloc__FUlPQ27CMemory6CStagePci
                                 (*(int *)(*(int *)(iVar4 + 0xa4) + 0xc) << 2,
                                  pppEnvStPtr->m_stagePtr,s_pppChangeTex_cpp_801dd660,0x166);
        value[4] = fVar5;
        puVar14 = (undefined4 *)value[3];
        iVar15 = 0;
        for (uVar12 = 0; uVar12 < *(uint *)(*(int *)(iVar4 + 0xa4) + 0xc); uVar12 = uVar12 + 1) {
          iVar10 = *(int *)(iVar6 + 8);
          iVar8 = strcmp(iVar10,&DAT_80332024);
          if (iVar8 == 0) {
            CalcBoundaryBoxQuantized__5CUtilFP3VecP3VecP6S16VecUlUl
                      ((CUtil *)&DAT_8032ec70,value + 10,value + 0xe,*(S16Vec **)(iVar6 + 0xc),
                       *(undefined4 *)(iVar10 + 0x14),*(undefined4 *)(*(int *)(iVar4 + 0xa4) + 0x34)
                      );
          }
          uVar7 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                            (*(int *)(*(int *)(iVar6 + 8) + 0x4c) << 2,pppEnvStPtr->m_stagePtr,
                             s_pppChangeTex_cpp_801dd660,0x181);
          *(undefined4 *)((int)value[4] + iVar15) = uVar7;
          iVar8 = *(int *)(*(int *)(iVar6 + 8) + 0x4c) + -1;
          puVar13 = *(undefined4 **)(*(int *)(iVar6 + 8) + 0x50);
          piVar16 = (int *)(*(int *)((int)value[4] + iVar15) + iVar8 * 4);
          for (; -1 < iVar8; iVar8 = iVar8 + -1) {
            iVar10 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                               (8,pppEnvStPtr->m_stagePtr,s_pppChangeTex_cpp_801dd660,0x18b);
            *piVar16 = iVar10;
            *(undefined4 *)(*piVar16 + 4) = *puVar13;
            uVar7 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                              (*puVar13,pppEnvStPtr->m_stagePtr,s_pppChangeTex_cpp_801dd660,0x18d);
            *(undefined4 *)*piVar16 = uVar7;
            memcpy(*(void **)*piVar16,puVar13[1],*puVar13);
            ReWriteDisplayList__5CUtilFPvUlUl
                      ((CUtil *)&DAT_8032ec70,*(undefined4 *)*piVar16,*puVar13,1);
            piVar16 = piVar16 + -1;
            puVar13 = puVar13 + 3;
          }
          uVar7 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                            (*(int *)(*(int *)(iVar6 + 8) + 0x14) << 2,pppEnvStPtr->m_stagePtr,
                             s_pppChangeTex_cpp_801dd660,0x196);
          *puVar14 = uVar7;
          memset(*puVar14,0,*(int *)(*(int *)(iVar6 + 8) + 0x14) << 2);
          iVar15 = iVar15 + 4;
          puVar14 = puVar14 + 1;
          iVar6 = iVar6 + 0x14;
        }
      }
      if (DAT_8032ed78 == '\0') {
        fVar5 = *value * (value[0xf] - value[0xb]) + value[0xb];
        sVar2 = (short)(int)(fVar5 * (float)((double)CONCAT44(0x43300000,
                                                              1 << *(int *)(*(int *)(iVar4 + 0xa4) +
                                                                           0x34) ^ 0x80000000) -
                                            DOUBLE_80332030));
        if (value[0x11] != fVar5) {
          value[0x11] = fVar5;
          iVar6 = 0;
          local_50 = (double)CONCAT44(0x43300000,(uint)(byte)(&pppChangeTex->field_0x8b)[iVar9]);
          iVar9 = *(int *)(iVar4 + 0xac);
          dVar17 = (double)(FLOAT_80332028 * ((float)(local_50 - DOUBLE_80332038) / FLOAT_80332028))
          ;
          for (uVar12 = 0; uVar12 < *(uint *)(*(int *)(iVar4 + 0xa4) + 0xc); uVar12 = uVar12 + 1) {
            iVar10 = 0;
            iVar8 = *(int *)((int)value[3] + iVar6);
            iVar15 = iVar8;
            for (uVar11 = 0; uVar1 = *(uint *)(*(int *)(iVar9 + 8) + 0x14), uVar11 < uVar1;
                uVar11 = uVar11 + 1) {
              if (param_2->m_payload[0] == '\x01') {
                if (*(short *)(*(int *)(iVar9 + 0xc) + iVar10 + 2) < sVar2) {
                  *(char *)(iVar15 + 3) = (char)(int)dVar17;
                }
                else {
                  *(undefined *)(iVar15 + 3) = 0;
                }
              }
              else if (param_2->m_payload[0] == '\x02') {
                if (sVar2 < *(short *)(*(int *)(iVar9 + 0xc) + iVar10 + 2)) {
                  *(char *)(iVar15 + 3) = (char)(int)dVar17;
                }
                else {
                  *(undefined *)(iVar15 + 3) = 0;
                }
              }
              iVar10 = iVar10 + 6;
              iVar15 = iVar15 + 4;
            }
            DCFlushRange(iVar8,uVar1 << 2);
            iVar6 = iVar6 + 4;
            iVar9 = iVar9 + 0x14;
          }
        }
      }
    }
  }
  return;
}


// Function: pppFrameLerpPos
// Entry: 8012b24c
// Size: 496 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameLerpPos(pppLerpPos *pppLerpPos,UnkB *param_2,UnkC *param_3)

{
  _pppMngSt *pppMngSt;
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  float *pfVar6;
  int iVar7;
  Vec local_38;
  Vec local_2c;
  undefined4 local_20;
  uint uStack_1c;
  
  pppMngSt = pppMngStPtr;
  if (DAT_8032ed70 == 0) {
    iVar2 = *param_3->m_serializedDataOffsets;
    if (*(int *)((int)(&pppLerpPos->field0_0x0 + 2) + iVar2) == 0) {
      uVar3 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                        ((uint)*(byte *)&param_2->m_dataValIndex * 0xc,pppEnvStPtr->m_stagePtr,
                         s_pppLerpPos_cpp_801dd418,0x37);
      *(undefined4 *)((int)(&pppLerpPos->field0_0x0 + 2) + iVar2) = uVar3;
      iVar5 = 0;
      for (iVar7 = 0; iVar7 < (int)(uint)*(byte *)&param_2->m_dataValIndex; iVar7 = iVar7 + 1) {
        iVar4 = iVar5 + 4;
        iVar1 = iVar5 + 8;
        *(float *)(*(int *)((int)(&pppLerpPos->field0_0x0 + 2) + iVar2) + iVar5) =
             (pppMngStPtr->m_matrix).value[0][3];
        iVar5 = iVar5 + 0xc;
        *(float *)(*(int *)((int)(&pppLerpPos->field0_0x0 + 2) + iVar2) + iVar4) =
             (pppMngStPtr->m_matrix).value[1][3];
        *(float *)(*(int *)((int)(&pppLerpPos->field0_0x0 + 2) + iVar2) + iVar1) =
             (pppMngStPtr->m_matrix).value[2][3];
      }
    }
    else {
      local_2c.z = FLOAT_80331bf8;
      local_2c.y = FLOAT_80331bf8;
      local_2c.x = FLOAT_80331bf8;
      iVar5 = *(byte *)&param_2->m_dataValIndex - 1;
      iVar7 = iVar5 * 0xc;
      for (; 0 < iVar5; iVar5 = iVar5 + -1) {
        pfVar6 = (float *)(*(int *)((int)(&pppLerpPos->field0_0x0 + 2) + iVar2) + iVar7 + -0xc);
        local_38.x = *pfVar6;
        local_38.y = pfVar6[1];
        local_38.z = pfVar6[2];
        pppCopyVector__FR3Vec3Vec
                  ((Vec *)(*(int *)((int)(&pppLerpPos->field0_0x0 + 2) + iVar2) + iVar7),&local_38);
        iVar7 = iVar7 + -0xc;
      }
      iVar7 = 0;
      **(float **)((int)(&pppLerpPos->field0_0x0 + 2) + iVar2) = (pppMngStPtr->m_matrix).value[0][3]
      ;
      *(float *)(*(int *)((int)(&pppLerpPos->field0_0x0 + 2) + iVar2) + 4) =
           (pppMngStPtr->m_matrix).value[1][3];
      *(float *)(*(int *)((int)(&pppLerpPos->field0_0x0 + 2) + iVar2) + 8) =
           (pppMngStPtr->m_matrix).value[2][3];
      for (iVar5 = 0; uStack_1c = (uint)*(byte *)&param_2->m_dataValIndex, iVar5 < (int)uStack_1c;
          iVar5 = iVar5 + 1) {
        PSVECAdd((Vec *)(*(int *)((int)(&pppLerpPos->field0_0x0 + 2) + iVar2) + iVar7),&local_2c,
                 &local_2c);
        iVar7 = iVar7 + 0xc;
      }
      local_20 = 0x43300000;
      PSVECScale(FLOAT_80331bfc / (float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_80331c00),
                 &local_2c,&local_2c);
      (pppMngStPtr->m_matrix).value[0][3] = local_2c.x;
      (pppMngStPtr->m_matrix).value[1][3] = local_2c.y;
      (pppMngStPtr->m_matrix).value[2][3] = local_2c.z;
      pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
    }
  }
  return;
}


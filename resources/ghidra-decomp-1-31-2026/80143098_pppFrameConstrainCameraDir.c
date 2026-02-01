// Function: pppFrameConstrainCameraDir
// Entry: 80143098
// Size: 508 bytes

/* WARNING: Removing unreachable block (ram,0x80143270) */
/* WARNING: Removing unreachable block (ram,0x80143268) */
/* WARNING: Removing unreachable block (ram,0x80143260) */
/* WARNING: Removing unreachable block (ram,0x80143258) */
/* WARNING: Removing unreachable block (ram,0x80143250) */
/* WARNING: Removing unreachable block (ram,0x80143248) */
/* WARNING: Removing unreachable block (ram,0x80143240) */
/* WARNING: Removing unreachable block (ram,0x801430d8) */
/* WARNING: Removing unreachable block (ram,0x801430d0) */
/* WARNING: Removing unreachable block (ram,0x801430c8) */
/* WARNING: Removing unreachable block (ram,0x801430c0) */
/* WARNING: Removing unreachable block (ram,0x801430b8) */
/* WARNING: Removing unreachable block (ram,0x801430b0) */
/* WARNING: Removing unreachable block (ram,0x801430a8) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameConstrainCameraDir
               (pppConstrainCameraDir *pppConstrainCameraDir,UnkB *param_2,UnkC *param_3)

{
  _pppMngSt *pppMngSt;
  float fVar1;
  float *value;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  Mtx MStack_e8;
  Mtx MStack_b8;
  
  pppMngSt = pppMngStPtr;
  if (DAT_8032ed70 == 0) {
    value = (float *)((int)(&pppConstrainCameraDir->field0_0x0 + 2) +
                     *param_3->m_serializedDataOffsets);
    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf
              ((float)param_2->m_dataValIndex,&pppConstrainCameraDir->field0_0x0,param_2->m_graphId,
               value,value + 1,value + 2,&param_2->m_initWOrk,&param_2->m_stepValue);
    if ((DAT_8032ed78 != '\x01') &&
       ((*(char *)((int)&param_2->m_arg3 + 1) != '\0' || (*(char *)&param_2->m_arg3 != '\0')))) {
      dVar8 = (double)(float)CameraPcs._236_4_;
      dVar7 = (double)(float)CameraPcs._240_4_;
      dVar6 = (double)(float)CameraPcs._244_4_;
      PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_b8);
      dVar5 = (double)(float)CameraPcs._224_4_;
      dVar4 = (double)(float)CameraPcs._228_4_;
      dVar3 = (double)(float)CameraPcs._232_4_;
      dVar2 = (double)(FLOAT_803320b8 + ((float)CameraPcs._252_4_ - FLOAT_803320bc) / FLOAT_803320bc
                      );
      PSMTXIdentity(&pppMngStPtr->m_matrix);
      fVar1 = FLOAT_803320b8;
      (pppMngSt->m_scale).x = (float)((double)FLOAT_803320c0 * dVar2);
      (pppMngSt->m_scale).y = (float)dVar2;
      (pppMngSt->m_scale).z = fVar1;
      PSMTXScale((pppMngSt->m_scale).x,(pppMngSt->m_scale).y,(pppMngSt->m_scale).z,&MStack_e8);
      if (*(char *)((int)&param_2->m_arg3 + 1) != '\0') {
        PSMTXInverse(&MStack_b8,&pppMngStPtr->m_matrix);
      }
      PSMTXConcat(&MStack_e8,&pppMngStPtr->m_matrix,&pppMngStPtr->m_matrix);
      if (*(char *)&param_2->m_arg3 != '\0') {
        dVar2 = (double)*value;
        (pppMngStPtr->m_matrix).value[0][3] = (float)(dVar8 * dVar2 + dVar5);
        (pppMngStPtr->m_matrix).value[1][3] = (float)(dVar7 * dVar2 + dVar4);
        (pppMngStPtr->m_matrix).value[2][3] = (float)(dVar6 * dVar2 + dVar3);
      }
      pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
    }
  }
  return;
}


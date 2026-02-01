// Function: pppFrameConstrainCameraDir2
// Entry: 8016ca80
// Size: 688 bytes

/* WARNING: Removing unreachable block (ram,0x8016cd08) */
/* WARNING: Removing unreachable block (ram,0x8016cd00) */
/* WARNING: Removing unreachable block (ram,0x8016ccf8) */
/* WARNING: Removing unreachable block (ram,0x8016ccf0) */
/* WARNING: Removing unreachable block (ram,0x8016caa8) */
/* WARNING: Removing unreachable block (ram,0x8016caa0) */
/* WARNING: Removing unreachable block (ram,0x8016ca98) */
/* WARNING: Removing unreachable block (ram,0x8016ca90) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameConstrainCameraDir2
               (pppConstrainCameraDir *pppConstrainCameraDir,UnkB *param_2,UnkC *param_3)

{
  _pppMngSt *pppMngSt;
  float fVar1;
  float *value;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  float local_108;
  float local_104;
  float local_100;
  Vec local_fc;
  Vec local_f0;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  Vec local_c0;
  Mtx MStack_b4;
  Mtx MStack_84;
  
  pppMngSt = pppMngStPtr;
  if (DAT_8032ed70 == 0) {
    value = (float *)((int)(&pppConstrainCameraDir->field0_0x0 + 2) +
                     *param_3->m_serializedDataOffsets);
    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf
              ((float)param_2->m_dataValIndex,&pppConstrainCameraDir->field0_0x0,param_2->m_graphId,
               value,value + 1,value + 2,&param_2->m_initWOrk,&param_2->m_stepValue);
    if ((DAT_8032ed78 != '\x01') &&
       ((*(char *)((int)&param_2->m_arg3 + 1) != '\0' || (*(char *)&param_2->m_arg3 != '\0')))) {
      local_cc = (float)CameraPcs._236_4_;
      local_c8 = (float)CameraPcs._240_4_;
      local_c4 = (float)CameraPcs._244_4_;
      PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_84);
      dVar5 = (double)(float)CameraPcs._224_4_;
      dVar4 = (double)(float)CameraPcs._228_4_;
      dVar3 = (double)(float)CameraPcs._232_4_;
      dVar2 = (double)(FLOAT_803331e0 + ((float)CameraPcs._252_4_ - FLOAT_803331e4) / FLOAT_803331e4
                      );
      PSMTXIdentity(&pppMngStPtr->m_matrix);
      fVar1 = FLOAT_803331e0;
      (pppMngSt->m_scale).x = (float)((double)FLOAT_803331e8 * dVar2);
      (pppMngSt->m_scale).y = (float)dVar2;
      (pppMngSt->m_scale).z = fVar1;
      PSMTXScale((pppMngSt->m_scale).x,(pppMngSt->m_scale).y,(pppMngSt->m_scale).z,&MStack_b4);
      if (*(char *)((int)&param_2->m_arg3 + 1) != '\0') {
        PSMTXInverse(&MStack_84,&pppMngStPtr->m_matrix);
      }
      PSMTXConcat(&MStack_b4,&pppMngStPtr->m_matrix,&pppMngStPtr->m_matrix);
      if (*(char *)&param_2->m_arg3 != '\0') {
        dVar2 = (double)*value;
        local_c0.x = (float)((double)local_cc * dVar2 + dVar5);
        local_c0.y = (float)((double)local_c8 * dVar2 + dVar4);
        local_c0.z = (float)((double)local_c4 * dVar2 + dVar3);
      }
      dVar2 = (double)(pppConstrainCameraDir->field0_0x0).m_localMatrix.value[0][3];
      dVar3 = (double)(pppConstrainCameraDir->field0_0x0).m_localMatrix.value[1][3];
      local_108 = local_cc;
      local_104 = local_c8;
      local_100 = local_c4;
      GetDirectVector__5CUtilFP3VecP3Vec3Vec((CUtil *)&DAT_8032ec70,&local_d8,&local_e4,&local_108);
      local_f0.x = (float)(dVar2 * (double)local_d8);
      local_f0.y = (float)(dVar2 * (double)local_d4);
      local_f0.z = (float)(dVar2 * (double)local_d0);
      local_fc.x = (float)(dVar3 * (double)local_e4);
      local_fc.y = (float)(dVar3 * (double)local_e0);
      local_fc.z = (float)(dVar3 * (double)local_dc);
      PSVECAdd(&local_c0,&local_f0,&local_c0);
      PSVECAdd(&local_c0,&local_fc,&local_c0);
      (pppMngStPtr->m_matrix).value[0][3] = local_c0.x;
      (pppMngStPtr->m_matrix).value[1][3] = local_c0.y;
      (pppMngStPtr->m_matrix).value[2][3] = local_c0.z;
      pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
    }
  }
  return;
}


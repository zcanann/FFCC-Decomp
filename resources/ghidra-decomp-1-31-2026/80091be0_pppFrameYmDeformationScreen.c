// Function: pppFrameYmDeformationScreen
// Entry: 80091be0
// Size: 516 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameYmDeformationScreen
               (pppYmDeformationScreen *pppYmDeformationScreen,UnkB *param_2,UnkC *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  Vec4d local_78;
  Vec4d VStack_68;
  Mat4x4 MStack_58;
  longlong local_18;
  
  if (DAT_8032ed70 == 0) {
    pfVar4 = (float *)((int)(&pppYmDeformationScreen->field0_0x0 + 2) +
                      param_3->m_serializedDataOffsets[2]);
    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf
              ((float)param_2->m_initWOrk,&pppYmDeformationScreen->field0_0x0,param_2->m_graphId,
               pfVar4 + 2,pfVar4 + 3,pfVar4 + 4,&param_2->m_stepValue,&param_2->m_arg3);
    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf
              (*(float *)param_2->m_payload,&pppYmDeformationScreen->field0_0x0,param_2->m_graphId,
               pfVar4 + 5,pfVar4 + 6,pfVar4 + 7,param_2->m_payload + 4,param_2->m_payload + 8);
    if (DAT_8032ed78 == '\0') {
      if (*(char *)((int)pfVar4 + 6) == '\0') {
        local_18 = (longlong)(int)pfVar4[5];
        *(short *)(pfVar4 + 1) = *(short *)(pfVar4 + 1) - (short)(int)pfVar4[5];
        if ((int)*(short *)(pfVar4 + 1) < -(int)*(short *)(param_2->m_payload + 0xc)) {
          *(undefined *)((int)pfVar4 + 6) = 1;
        }
      }
      else {
        local_18 = (longlong)(int)pfVar4[5];
        *(short *)(pfVar4 + 1) = *(short *)(pfVar4 + 1) + (short)(int)pfVar4[5];
        if (*(short *)(param_2->m_payload + 0xc) < *(short *)(pfVar4 + 1)) {
          *(undefined *)((int)pfVar4 + 6) = 0;
        }
      }
      if ((pppYmDeformationScreen->field0_0x0).m_graphId == 0) {
        PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_58);
        local_78.x = FLOAT_80330670;
        local_78.y = FLOAT_80330670;
        local_78.z = -*(float *)(param_2->m_payload + 0x10);
        local_78.w = FLOAT_8033067c;
        MTX44MultVec4__5CMathFPA4_fP5Vec4dP5Vec4d(&Math,&MStack_58,&local_78,&VStack_68);
        if (VStack_68.w != FLOAT_80330670) {
          VStack_68.z = VStack_68.z / VStack_68.w;
        }
        *pfVar4 = VStack_68.z;
      }
      fVar1 = (float)CameraPcs._212_4_;
      fVar2 = (float)CameraPcs._216_4_;
      fVar3 = (float)CameraPcs._220_4_;
      if (Game.game.m_currentSceneId == 7) {
        fVar1 = ppvCameraMatrix0.value[0][3];
        fVar2 = ppvCameraMatrix0.value[1][3];
        fVar3 = ppvCameraMatrix0.value[2][3];
      }
      (pppMngStPtr->m_matrix).value[0][3] = fVar1;
      (pppMngStPtr->m_matrix).value[1][3] = fVar2;
      (pppMngStPtr->m_matrix).value[2][3] = fVar3;
      pppSetFpMatrix__FP9_pppMngSt(pppMngStPtr);
    }
  }
  return;
}


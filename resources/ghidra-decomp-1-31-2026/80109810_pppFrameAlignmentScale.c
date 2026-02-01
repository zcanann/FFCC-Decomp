// Function: pppFrameAlignmentScale
// Entry: 80109810
// Size: 284 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

pppAlignmentScale * pppFrameAlignmentScale(pppAlignmentScale *pppAlignmentScale,UnkC *param_2)

{
  float fVar1;
  float xS;
  _pppMngSt *pppMngSt;
  double dVar2;
  Vec local_58;
  Vec local_4c;
  Mtx MStack_40;
  
  pppMngSt = pppMngStPtr;
  if (DAT_8032ed70 == 0) {
    local_4c.x = (float)CameraPcs._224_4_;
    local_4c.y = (float)CameraPcs._228_4_;
    local_4c.z = (float)CameraPcs._232_4_;
    local_58.x = (pppMngStPtr->m_matrix).value[0][3];
    local_58.y = (pppMngStPtr->m_matrix).value[1][3];
    local_58.z = (pppMngStPtr->m_matrix).value[2][3];
    dVar2 = (double)PSVECDistance(&local_4c,&local_58);
    fVar1 = (float)(dVar2 / (double)(float)param_2->m_unk0x4);
    xS = FLOAT_80331920;
    if (FLOAT_80331920 < fVar1) {
      xS = (fVar1 - FLOAT_80331920) * (float)param_2->m_unk0x8 + FLOAT_80331920;
    }
    PSMTXScale(xS,xS,xS,&MStack_40);
    fVar1 = FLOAT_80331924;
    (pppMngStPtr->m_matrix).value[0][3] = FLOAT_80331924;
    (pppMngStPtr->m_matrix).value[1][3] = fVar1;
    (pppMngStPtr->m_matrix).value[2][3] = fVar1;
    PSMTXConcat(&MStack_40,&pppMngStPtr->m_matrix,&pppMngStPtr->m_matrix);
    (pppMngStPtr->m_matrix).value[0][3] = local_58.x;
    (pppMngStPtr->m_matrix).value[1][3] = local_58.y;
    (pppMngStPtr->m_matrix).value[2][3] = local_58.z;
    pppAlignmentScale = (pppAlignmentScale *)pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
  }
  return pppAlignmentScale;
}


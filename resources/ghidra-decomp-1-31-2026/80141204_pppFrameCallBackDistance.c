// Function: pppFrameCallBackDistance
// Entry: 80141204
// Size: 272 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameCallBackDistance(pppCallBackDistance *pppCallBackDistance,UnkB *param_2,UnkC *param_3)

{
  _pppMngSt *p_Var1;
  uint uVar2;
  int iVar3;
  double dVar4;
  Vec local_28;
  Vec local_1c;
  
  local_1c.x = (pppMngStPtr->m_matrix).value[0][3];
  iVar3 = *param_3->m_serializedDataOffsets;
  local_1c.y = (pppMngStPtr->m_matrix).value[1][3];
  local_1c.z = (pppMngStPtr->m_matrix).value[2][3];
  dVar4 = (double)PSVECDistance(&local_1c,&pppMngStPtr->m_paramVec0);
  p_Var1 = pppMngStPtr;
  if ((dVar4 <= (double)(float)param_2->m_dataValIndex) ||
     ((double)*(float *)((int)(&pppCallBackDistance->field0_0x0 + 2) + iVar3) <= dVar4)) {
    local_28.x = (pppMngStPtr->m_matrix).value[0][3];
    local_28.y = (pppMngStPtr->m_matrix).value[1][3];
    local_28.z = (pppMngStPtr->m_matrix).value[2][3];
    PSMTXMultVec(&ppvWorldMatrix,&local_28,&local_28);
    uVar2 = (pppCallBackDistance->field0_0x0).m_graphId;
    iVar3 = (int)&p_Var1[0x5f2411].m_scale / 0x158 + ((int)&p_Var1[0x5f2411].m_scale >> 0x1f);
    ParticleFrameCallback__5CGameFiiiiiP3Vec
              (&Game.game,iVar3 - (iVar3 >> 0x1f),(int)p_Var1->m_kind,(int)p_Var1->m_nodeIndex,
               (int)*(short *)&param_2->m_initWOrk,
               ((int)uVar2 >> 0xc) + (uint)((int)uVar2 < 0 && (uVar2 & 0xfff) != 0));
  }
  return;
}


// Function: pppFrameYmCallBack
// Entry: 800a5fcc
// Size: 192 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameYmCallBack(pppYmCallBack *pppYmCallBack,int param_2)

{
  _pppMngSt *p_Var1;
  int iVar2;
  uint uVar3;
  Vec local_18;
  
  p_Var1 = pppMngStPtr;
  uVar3 = (pppYmCallBack->field0_0x0).m_graphId;
  if (((int)uVar3 >> 0xc) + (uint)((int)uVar3 < 0 && (uVar3 & 0xfff) != 0) ==
      (int)*(short *)(param_2 + 4)) {
    local_18.x = (pppMngStPtr->m_matrix).value[0][3];
    local_18.y = (pppMngStPtr->m_matrix).value[1][3];
    local_18.z = (pppMngStPtr->m_matrix).value[2][3];
    PSMTXMultVec(&ppvWorldMatrix,&local_18,&local_18);
    iVar2 = (int)&p_Var1[0x5f2411].m_scale / 0x158 + ((int)&p_Var1[0x5f2411].m_scale >> 0x1f);
    ParticleFrameCallback__5CGameFiiiiiP3Vec
              (&Game.game,iVar2 - (iVar2 >> 0x1f),(int)p_Var1->m_kind,(int)p_Var1->m_nodeIndex,
               (int)*(short *)(param_2 + 6),(int)*(short *)(param_2 + 4));
  }
  return;
}


// Function: pppParMoveMatrix
// Entry: 800d467c
// Size: 428 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppParMoveMatrix(void)

{
  _pppMngSt *pppMngSt;
  Vec local_68;
  Vec local_5c;
  Vec local_50;
  Vec local_44;
  Mtx MStack_38;
  
  pppMngSt = pppMngStPtr;
  PSVECSubtract(&pppMngStPtr->m_previousPosition,&pppMngStPtr->m_position,&local_44);
  if (((FLOAT_80330e38 != local_44.x) || (FLOAT_80330e38 != local_44.y)) ||
     (FLOAT_80330e38 != local_44.z)) {
    PSVECNormalize(&local_44,&local_68);
    local_50.z = -local_68.x;
    local_50.x = local_68.z;
    local_50.y = FLOAT_80330e38;
    if ((FLOAT_80330e38 == local_68.z) && (FLOAT_80330e38 == local_50.z)) {
      local_50.x = FLOAT_80330e3c;
      local_50.z = FLOAT_80330e38;
      local_5c.x = FLOAT_80330e38;
      local_5c.y = FLOAT_80330e38;
      local_5c.z = FLOAT_80330e3c;
    }
    else {
      PSVECNormalize(&local_50,&local_50);
      PSVECCrossProduct(&local_68,&local_50,&local_5c);
      PSVECNormalize(&local_5c,&local_5c);
    }
    (pppMngStPtr->m_matrix).value[0][0] = local_50.x;
    (pppMngStPtr->m_matrix).value[1][0] = local_50.y;
    (pppMngStPtr->m_matrix).value[2][0] = local_50.z;
    (pppMngStPtr->m_matrix).value[0][1] = local_5c.x;
    (pppMngStPtr->m_matrix).value[1][1] = local_5c.y;
    (pppMngStPtr->m_matrix).value[2][1] = local_5c.z;
    (pppMngStPtr->m_matrix).value[0][2] = local_68.x;
    (pppMngStPtr->m_matrix).value[1][2] = local_68.y;
    (pppMngStPtr->m_matrix).value[2][2] = local_68.z;
    PSMTXScale((pppMngStPtr->m_scale).x,(pppMngStPtr->m_scale).y,(pppMngStPtr->m_scale).z,&MStack_38
              );
    PSMTXConcat(&MStack_38,&pppMngStPtr->m_matrix,&pppMngStPtr->m_matrix);
    (pppMngStPtr->m_matrix).value[0][3] = (pppMngSt->m_position).x;
    (pppMngStPtr->m_matrix).value[1][3] = (pppMngSt->m_position).y;
    (pppMngStPtr->m_matrix).value[2][3] = (pppMngSt->m_position).z;
    pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
  }
  return;
}


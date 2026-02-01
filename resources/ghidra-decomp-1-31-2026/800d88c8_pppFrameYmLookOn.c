// Function: pppFrameYmLookOn
// Entry: 800d88c8
// Size: 476 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameYmLookOn(pppYmLookOn *pppYmLookOn,UnkB *param_2,UnkC *param_3)

{
  _pppMngSt *pppMngSt;
  int iVar1;
  float fVar2;
  Vec local_58;
  Vec local_4c;
  Vec local_40;
  Vec local_34;
  Vec local_28;
  Vec local_1c [2];
  
  pppMngSt = pppMngStPtr;
  if (DAT_8032ed70 == 0) {
    fVar2 = (pppMngStPtr->m_velocity).y;
    iVar1 = *param_3->m_serializedDataOffsets;
    if ((fVar2 != 0.0) || (*(int *)((int)(&pppYmLookOn->field0_0x0 + 2) + iVar1) != 0)) {
      *(float *)((int)(&pppYmLookOn->field0_0x0 + 2) + iVar1) = fVar2;
      if (fVar2 == 0.0) {
        fVar2 = *(float *)((int)(&pppYmLookOn->field0_0x0 + 2) + iVar1);
      }
      local_4c.x = *(float *)((int)fVar2 + 0x15c);
      local_4c.z = *(float *)((int)fVar2 + 0x164);
      local_4c.y = *(float *)((int)fVar2 + 0x160) + (float)param_2->m_dataValIndex;
      local_58.x = (pppMngStPtr->m_matrix).value[0][3];
      local_58.y = (pppMngStPtr->m_matrix).value[1][3];
      local_58.z = (pppMngStPtr->m_matrix).value[2][3];
      PSVECSubtract(&local_58,&local_4c,local_1c);
      if (((FLOAT_80330ec8 != local_1c[0].x) || (FLOAT_80330ec8 != local_1c[0].y)) ||
         (FLOAT_80330ec8 != local_1c[0].z)) {
        PSVECNormalize(local_1c,&local_40);
        local_28.z = -local_40.x;
        local_28.x = local_40.z;
        local_28.y = FLOAT_80330ec8;
        if ((FLOAT_80330ec8 == local_40.z) && (FLOAT_80330ec8 == local_28.z)) {
          local_28.x = FLOAT_80330ecc;
          local_28.z = FLOAT_80330ec8;
          local_34.x = FLOAT_80330ec8;
          local_34.y = FLOAT_80330ec8;
          local_34.z = FLOAT_80330ecc;
        }
        else {
          PSVECNormalize(&local_28,&local_28);
          PSVECCrossProduct(&local_40,&local_28,&local_34);
          PSVECNormalize(&local_34,&local_34);
        }
        (pppMngStPtr->m_matrix).value[0][0] = local_28.x;
        (pppMngStPtr->m_matrix).value[1][0] = local_28.y;
        (pppMngStPtr->m_matrix).value[2][0] = local_28.z;
        (pppMngStPtr->m_matrix).value[0][1] = local_34.x;
        (pppMngStPtr->m_matrix).value[1][1] = local_34.y;
        (pppMngStPtr->m_matrix).value[2][1] = local_34.z;
        (pppMngStPtr->m_matrix).value[0][2] = local_40.x;
        (pppMngStPtr->m_matrix).value[1][2] = local_40.y;
        (pppMngStPtr->m_matrix).value[2][2] = local_40.z;
        pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
      }
    }
  }
  return;
}


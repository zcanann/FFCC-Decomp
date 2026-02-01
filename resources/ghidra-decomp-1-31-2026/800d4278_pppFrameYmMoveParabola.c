// Function: pppFrameYmMoveParabola
// Entry: 800d4278
// Size: 736 bytes

/* WARNING: Removing unreachable block (ram,0x800d4530) */
/* WARNING: Removing unreachable block (ram,0x800d4288) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameYmMoveParabola(pppYmMoveParabola *pppYmMoveParabola,UnkB *param_2,UnkC *param_3)

{
  uint uVar1;
  _pppMngSt *pppMngSt;
  float *pfVar2;
  double dVar3;
  Vec local_98;
  Vec local_8c;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  Vec local_44;
  float local_38;
  float local_34;
  float local_30;
  undefined8 local_28;
  
  pppMngSt = pppMngStPtr;
  if (DAT_8032ed70 == 0) {
    pfVar2 = (float *)((int)(&pppYmMoveParabola->field0_0x0 + 2) + *param_3->m_serializedDataOffsets
                      );
    pfVar2[1] = pfVar2[1] + pfVar2[2];
    *pfVar2 = *pfVar2 + pfVar2[1];
    if (param_2->m_graphId == (pppYmMoveParabola->field0_0x0).m_graphId) {
      *pfVar2 = *pfVar2 + param_2->m_stepValue;
      pfVar2[1] = pfVar2[1] + (float)param_2->m_arg3;
      pfVar2[2] = pfVar2[2] + *(float *)param_2->m_payload;
    }
    local_28 = (double)CONCAT44(0x43300000,(uint)*(ushort *)(pfVar2 + 3));
    dVar3 = (double)(float)(local_28 - DOUBLE_80330e30);
    if (Game.game.m_currentSceneId == 7) {
      local_44.y = FLOAT_80330e1c;
      local_44.x = FLOAT_80330e18;
      local_44.z = FLOAT_80330e1c;
    }
    else {
      PSVECSubtract(&pppMngSt->m_paramVec0,&pppMngSt->m_savedPosition,&local_44);
    }
    local_50 = local_44.x;
    local_4c = local_44.y;
    local_48 = local_44.z;
    pppNormalize__FR3Vec3Vec(&local_44,&local_50);
    uVar1 = (uint)((FLOAT_80330e20 * (float)param_2->m_dataValIndex) / FLOAT_80330e24);
    local_28 = (double)(longlong)(int)uVar1;
    local_30 = (float)(dVar3 * (double)(*pfVar2 *
                                       *(float *)((int)ppvSinTbl + (uVar1 + 0x4000 & 0xfffc))));
    local_38 = local_44.x * local_30;
    local_30 = local_44.z * local_30;
    local_34 = (float)(dVar3 * (double)(*pfVar2 * *(float *)((int)ppvSinTbl + (uVar1 & 0xfffc))) -
                      (double)(float)(dVar3 * (double)(float)((double)(FLOAT_80330e28 *
                                                                      (float)param_2->m_initWOrk) *
                                                             dVar3)));
    if (Game.game.m_currentSceneId == 7) {
      local_68 = pfVar2[4];
      local_64 = pfVar2[5];
      local_60 = pfVar2[6];
      local_5c = local_38;
      local_58 = local_34;
      local_54 = local_30;
      pppAddVector__FR3Vec3Vec3Vec(&local_38,&local_5c,&local_68);
    }
    else {
      local_80 = (pppMngSt->m_savedPosition).x;
      local_7c = (pppMngSt->m_savedPosition).y;
      local_78 = (pppMngSt->m_savedPosition).z;
      local_74 = local_38;
      local_70 = local_34;
      local_6c = local_30;
      pppAddVector__FR3Vec3Vec3Vec(&local_38,&local_74,&local_80);
    }
    local_8c.x = (pppMngSt->m_position).x;
    local_8c.y = (pppMngSt->m_position).y;
    local_8c.z = (pppMngSt->m_position).z;
    pppCopyVector__FR3Vec3Vec(&pppMngSt->m_previousPosition,&local_8c);
    local_98.x = local_38;
    local_98.y = local_34;
    local_98.z = local_30;
    pppCopyVector__FR3Vec3Vec(&pppMngSt->m_position,&local_98);
    (pppMngStPtr->m_matrix).value[0][3] = local_38;
    (pppMngStPtr->m_matrix).value[1][3] = local_34;
    (pppMngStPtr->m_matrix).value[2][3] = local_30;
    pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
    *(short *)(pfVar2 + 3) = *(short *)(pfVar2 + 3) + 1;
  }
  return;
}


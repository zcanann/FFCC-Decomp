// Function: pppFrameYmTraceMove
// Entry: 800d4828
// Size: 936 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameYmTraceMove(pppYmTraceMove *pppYmTraceMove,UnkB *param_2,UnkC *param_3)

{
  _pppMngSt *p_Var1;
  float fVar2;
  Vec *dest;
  Vec local_128;
  Vec local_11c;
  float local_110;
  float local_10c;
  float local_108;
  float local_104;
  float local_100;
  float local_fc;
  float local_f8;
  float local_f4;
  float local_f0;
  Vec local_ec;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  Vec local_c8;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  Vec local_98;
  Vec local_8c;
  Quat local_80;
  Quat local_70;
  Quat local_60;
  Vec local_50;
  float local_44;
  float local_40;
  float local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  Vec local_2c;
  Vec local_20;
  
  p_Var1 = pppMngStPtr;
  if (DAT_8032ed70 == 0) {
    fVar2 = (pppMngStPtr->m_velocity).y;
    dest = (Vec *)((int)(&pppYmTraceMove->field0_0x0 + 2) + *param_3->m_serializedDataOffsets);
    dest[2].z = dest[2].z + dest[3].x;
    dest[2].y = dest[2].y + dest[2].z;
    if (param_2->m_graphId == (pppYmTraceMove->field0_0x0).m_graphId) {
      dest[2].y = dest[2].y + (float)param_2->m_initWOrk;
      dest[2].z = dest[2].z + param_2->m_stepValue;
      dest[3].x = dest[3].x + (float)param_2->m_arg3;
    }
    if (fVar2 == 0.0) {
      local_8c.x = dest->x;
      local_8c.y = dest->y;
      local_8c.z = dest->z;
      pppCopyVector__FR3Vec3Vec(&local_20,&local_8c);
      local_98.x = dest[1].y;
      local_98.y = dest[1].z;
      local_98.z = dest[2].x;
      pppCopyVector__FR3Vec3Vec(&local_2c,&local_98);
    }
    else {
      local_a4 = *(undefined4 *)((int)fVar2 + 0x15c);
      local_a0 = *(undefined4 *)((int)fVar2 + 0x160);
      local_9c = *(undefined4 *)((int)fVar2 + 0x164);
      local_b0 = (p_Var1->m_position).x;
      local_ac = (p_Var1->m_position).y;
      local_a8 = (p_Var1->m_position).z;
      local_38 = local_a4;
      local_34 = local_a0;
      local_30 = local_9c;
      pppSubVector__FR3Vec3Vec3Vec(&local_20,&local_a4,&local_b0);
      local_b8 = local_20.y + *(float *)param_2->m_payload;
      local_bc = local_20.x;
      local_b4 = local_20.z;
      local_20.y = local_b8;
      pppNormalize__FR3Vec3Vec(&local_20,&local_bc);
      local_c8.x = local_20.x;
      local_c8.y = local_20.y;
      local_c8.z = local_20.z;
      pppCopyVector__FR3Vec3Vec(dest,&local_c8);
      local_e0 = (p_Var1->m_previousPosition).x;
      local_dc = (p_Var1->m_previousPosition).y;
      local_d8 = (p_Var1->m_previousPosition).z;
      local_d4 = (p_Var1->m_position).x;
      local_d0 = (p_Var1->m_position).y;
      local_cc = (p_Var1->m_position).z;
      pppSubVector__FR3Vec3Vec3Vec(&local_2c,&local_d4,&local_e0);
      if (((local_2c.x == FLOAT_80330e40) && (local_2c.y == FLOAT_80330e40)) &&
         (local_2c.z == FLOAT_80330e40)) {
        local_ec.x = dest[1].y;
        local_ec.y = dest[1].z;
        local_ec.z = dest[2].x;
        pppCopyVector__FR3Vec3Vec(&local_2c,&local_ec);
      }
      local_f8 = local_2c.x;
      local_f4 = local_2c.y;
      local_f0 = local_2c.z;
      pppNormalize__FR3Vec3Vec(&local_2c,&local_f8);
    }
    local_60.x = local_20.x;
    local_60.y = local_20.y;
    local_60.z = local_20.z;
    local_60.w = FLOAT_80330e44;
    local_70.x = local_2c.x;
    local_70.y = local_2c.y;
    local_70.z = local_2c.z;
    local_70.w = FLOAT_80330e44;
    C_QUATLerp((double)(float)param_2->m_dataValIndex,&local_70,&local_60,&local_80);
    PSQUATNormalize(&local_80,&local_80);
    local_50.x = local_80.x;
    local_50.y = local_80.y;
    local_50.z = local_80.z;
    PSVECScale(dest[2].y * p_Var1->m_paramC,&local_50,&local_50);
    local_110 = (p_Var1->m_position).x;
    local_10c = (p_Var1->m_position).y;
    local_108 = (p_Var1->m_position).z;
    local_104 = local_50.x;
    local_100 = local_50.y;
    local_fc = local_50.z;
    pppAddVector__FR3Vec3Vec3Vec(&local_44,&local_104,&local_110);
    local_11c.x = (p_Var1->m_position).x;
    local_11c.y = (p_Var1->m_position).y;
    local_11c.z = (p_Var1->m_position).z;
    pppCopyVector__FR3Vec3Vec(&p_Var1->m_previousPosition,&local_11c);
    local_128.x = local_44;
    local_128.y = local_40;
    local_128.z = local_3c;
    pppCopyVector__FR3Vec3Vec(&p_Var1->m_position,&local_128);
    (pppMngStPtr->m_matrix).value[0][3] = local_44;
    (pppMngStPtr->m_matrix).value[1][3] = local_40;
    (pppMngStPtr->m_matrix).value[2][3] = local_3c;
  }
  return;
}


// Function: pppConstructYmTraceMove
// Entry: 800d4bd0
// Size: 172 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructYmTraceMove(pppYmTraceMove *pppYmTraceMove,UnkC *param_2)

{
  float fVar1;
  Vec *dest;
  Vec local_38;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  
  local_2c = (pppMngStPtr->m_savedPosition).x;
  local_28 = (pppMngStPtr->m_savedPosition).y;
  dest = (Vec *)((int)(&pppYmTraceMove->field0_0x0 + 2) + *param_2->m_serializedDataOffsets);
  local_24 = (pppMngStPtr->m_savedPosition).z;
  local_20 = (pppMngStPtr->m_paramVec0).x;
  local_1c = (pppMngStPtr->m_paramVec0).y;
  local_18 = (pppMngStPtr->m_paramVec0).z;
  pppSubVector__FR3Vec3Vec3Vec(&dest[1].y,&local_20,&local_2c);
  local_38.x = dest[1].y;
  local_38.y = dest[1].z;
  local_38.z = dest[2].x;
  pppCopyVector__FR3Vec3Vec(dest,&local_38);
  fVar1 = FLOAT_80330e40;
  dest[3].x = FLOAT_80330e40;
  dest[2].z = fVar1;
  dest[2].y = fVar1;
  return;
}


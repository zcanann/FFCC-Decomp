// Function: pppConstructCallBackDistance
// Entry: 80141318
// Size: 132 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructCallBackDistance(pppCallBackDistance *pppCallBackDistance,UnkC *param_2)

{
  int iVar1;
  float fVar2;
  double dVar3;
  Vec local_28;
  Vec local_1c;
  
  fVar2 = (pppMngStPtr->m_velocity).y;
  iVar1 = *param_2->m_serializedDataOffsets;
  local_28.x = *(float *)((int)fVar2 + 0x15c);
  local_28.y = *(float *)((int)fVar2 + 0x160);
  local_28.z = *(float *)((int)fVar2 + 0x164);
  local_1c.x = (pppMngStPtr->m_paramVec0).x;
  local_1c.y = (pppMngStPtr->m_paramVec0).y;
  local_1c.z = (pppMngStPtr->m_paramVec0).z;
  dVar3 = (double)PSVECDistance(&local_28,&local_1c);
  *(float *)((int)(&pppCallBackDistance->field0_0x0 + 2) + iVar1) = (float)dVar3;
  return;
}


// Function: dstTargetRot__8CGPrgObjFP8CGPrgObj
// Entry: 801271e0
// Size: 176 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void dstTargetRot__8CGPrgObjFP8CGPrgObj(CGPrgObj *gPrgObject,CGPrgObj *other)

{
  float fVar1;
  Vec *vecA;
  double dVar2;
  Vec local_38;
  CVector CStack_2c;
  CVector aCStack_20 [2];
  
  __ct__7CVectorFRC3Vec(aCStack_20,&(other->object).m_worldPosition);
  vecA = (Vec *)__ct__7CVectorFRC3Vec(&CStack_2c,&(gPrgObject->object).m_worldPosition);
  __ct__7CVectorFv(&local_38);
  PSVECSubtract(vecA,(Vec *)aCStack_20,&local_38);
  fVar1 = FLOAT_80331bd4;
  if (((double)FLOAT_80331bd4 != (double)local_38.x) &&
     ((double)FLOAT_80331bd4 != (double)local_38.z)) {
    dVar2 = (double)atan2(-(double)local_38.x,-(double)local_38.z);
    fVar1 = (float)dVar2;
  }
  DstRot__5CMathFff((double)(gPrgObject->object).m_rotBaseY,(double)(FLOAT_80331bd8 + fVar1),&Math);
  return;
}


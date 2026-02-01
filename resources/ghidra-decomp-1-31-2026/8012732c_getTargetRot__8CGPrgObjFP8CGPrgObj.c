// Function: getTargetRot__8CGPrgObjFP8CGPrgObj
// Entry: 8012732c
// Size: 144 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

double getTargetRot__8CGPrgObjFP8CGPrgObj(CGPrgObj *gPrgObj,int param_2)

{
  float fVar1;
  Vec *vecA;
  double dVar2;
  Vec local_38;
  CVector CStack_2c;
  CVector aCStack_20 [2];
  
  __ct__7CVectorFRC3Vec(&CStack_2c,(Vec *)(param_2 + 0x15c));
  vecA = (Vec *)__ct__7CVectorFRC3Vec(aCStack_20,&(gPrgObj->object).m_worldPosition);
  __ct__7CVectorFv(&local_38);
  PSVECSubtract(vecA,(Vec *)&CStack_2c,&local_38);
  fVar1 = FLOAT_80331bd4;
  if (((double)FLOAT_80331bd4 != (double)local_38.x) &&
     ((double)FLOAT_80331bd4 != (double)local_38.z)) {
    dVar2 = (double)atan2(-(double)local_38.x,-(double)local_38.z);
    fVar1 = (float)dVar2;
  }
  return (double)fVar1;
}


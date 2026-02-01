// Function: CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf
// Entry: 800e58c0
// Size: 92 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf
               (float addValue,_pppPObject *pppPObject,int graphId,float *value,float *velocity,
               float *acceleration,float *velocityAdd,float *accelerationAdd)

{
  *velocity = *velocity + *acceleration;
  *value = *value + *velocity;
  if (graphId != pppPObject->m_graphId) {
    return;
  }
  *value = *value + addValue;
  *velocity = *velocity + *velocityAdd;
  *acceleration = *acceleration + *accelerationAdd;
  return;
}


// Function: GetClassControl__8CGPrgObjFi
// Entry: 80127028
// Size: 92 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

uint32_t * GetClassControl__8CGPrgObjFi(CGPrgObj *gPrgObj,int param_2)

{
  uint32_t *puVar1;
  
  if (param_2 == 9) {
    puVar1 = (uint32_t *)isRideTarget__10CGPartyObjFv();
  }
  else {
    if (param_2 < 9) {
      if (7 < param_2) {
        puVar1 = (uint32_t *)isDispTarget__10CGPartyObjFv();
        return puVar1;
      }
    }
    else if (param_2 < 0xb) {
      return gPrgObj[1].object.base_object.object.m_thisBase;
    }
    puVar1 = (uint32_t *)0x0;
  }
  return puVar1;
}


// Function: EndParticleSlot__13CFlatRuntime2Fii
// Entry: 8006a148
// Size: 48 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

CFlatRuntime2 * EndParticleSlot__13CFlatRuntime2Fii(CFlatRuntime2 *flatRuntime2,int param_2)

{
  undefined4 in_r5;
  
  if (param_2 != 0) {
    flatRuntime2 = (CFlatRuntime2 *)pppEndSlot__8CPartMngFii(&PartMng,param_2,in_r5);
  }
  return flatRuntime2;
}


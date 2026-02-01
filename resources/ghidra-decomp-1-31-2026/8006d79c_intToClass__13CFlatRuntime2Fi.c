// Function: intToClass__13CFlatRuntime2Fi
// Entry: 8006d79c
// Size: 204 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

CFlatRuntime2 * intToClass__13CFlatRuntime2Fi(CFlatRuntime2 *flatRuntime2,uint param_2)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = (int)param_2 >> 8;
  uVar1 = param_2 & 0xff;
  if (iVar2 == 3) {
    return (CFlatRuntime2 *)((int)m_objParty + (uVar1 - 1) * 0x6f8);
  }
  if (2 < iVar2) {
    if (iVar2 == 5) {
      return (CFlatRuntime2 *)(m_objItem + (uVar1 - 1));
    }
    if (4 < iVar2) {
      return flatRuntime2;
    }
    return (CFlatRuntime2 *)((int)m_objParty + (uVar1 - 1) * 0x740 + 0x1be0);
  }
  if (iVar2 == 1) {
    return (CFlatRuntime2 *)(m_gObjQuadArr + (uVar1 - 1));
  }
  if (iVar2 < 1) {
    if (iVar2 < 0) {
      return flatRuntime2;
    }
    return (CFlatRuntime2 *)(m_gBaseObjArr + (uVar1 - 1));
  }
  return (CFlatRuntime2 *)(m_gObjArr + (uVar1 - 1));
}


// Function: canPlayerUseItem__10CGPartyObjFv
// Entry: 8011d170
// Size: 92 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 canPlayerUseItem__10CGPartyObjFv(CGPartyObj *gPartyObj)

{
  if ((int)((uint)*(byte *)&(gPartyObj->gCharaObj).gPrgObj.object.m_weaponNodeFlags << 0x18) < 0) {
    if ((((int)((uint)*(byte *)((int)&(gPartyObj->gCharaObj).gPrgObj.object.m_weaponNodeFlags + 1)
               << 0x18) < 0) && ((int)((uint)(byte)(gPartyObj->gCharaObj).field_0x63c << 0x18) < 0))
       && (*(short *)((gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle + 7) != 0)) {
      return 1;
    }
  }
  return 0;
}


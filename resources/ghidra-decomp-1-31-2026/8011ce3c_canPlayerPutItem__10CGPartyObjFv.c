// Function: canPlayerPutItem__10CGPartyObjFv
// Entry: 8011ce3c
// Size: 168 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 canPlayerPutItem__10CGPartyObjFv(CGPartyObj *gPartyObj)

{
  int iVar1;
  
  if (((((int)((uint)*(byte *)&(gPartyObj->gCharaObj).gPrgObj.object.m_weaponNodeFlags << 0x18) < 0)
       && ((int)((uint)*(byte *)((int)&(gPartyObj->gCharaObj).gPrgObj.object.m_weaponNodeFlags + 1)
                << 0x18) < 0)) &&
      ((int)((uint)(byte)(gPartyObj->gCharaObj).field_0x63c << 0x18) < 0)) &&
     ((*(short *)((gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle + 7) != 0 &&
      (*(int *)&gPartyObj->field_0x6f0 == 0)))) {
    if ((Game.game.m_gameWork.m_menuStageMode != '\0') &&
       (iVar1 = CanCreateFromScript__9CGItemObjFv(), iVar1 == 0)) {
      return 0;
    }
    return 1;
  }
  return 0;
}


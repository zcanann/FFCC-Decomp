// Function: onTalk__10CGPartyObjFP9CGBaseObji
// Entry: 8011e0ec
// Size: 168 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onTalk__10CGPartyObjFP9CGBaseObji(CGPartyObj *gPartyObj,CGBaseObj *gBaseObj,undefined4 param_3)

{
  uint uVar1;
  double dVar2;
  
  uVar1 = (**(code **)((int)(gBaseObj->object).m_vtable + 0xc))(gBaseObj);
  if ((uVar1 & 5) == 5) {
    if (gBaseObj[0x10].object.m_id == 0x23) {
      *(CGBaseObj **)&gPartyObj->field_0x6e8 = gBaseObj;
    }
    else {
      dVar2 = (double)PSVECDistance(&(gPartyObj->gCharaObj).gPrgObj.object.m_worldPosition,
                                    (Vec *)&gBaseObj[4].object.m_codePos);
      if (dVar2 < (double)*(float *)&gPartyObj->field_0x6ec) {
        *(CGBaseObj **)&gPartyObj->field_0x6e4 = gBaseObj;
        *(float *)&gPartyObj->field_0x6ec = (float)dVar2;
      }
    }
  }
  onTalk__9CGBaseObjFP9CGBaseObji((CGBaseObj *)gPartyObj,gBaseObj,param_3);
  return;
}


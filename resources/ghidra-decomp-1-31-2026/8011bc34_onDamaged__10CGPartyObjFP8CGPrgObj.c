// Function: onDamaged__10CGPartyObjFP8CGPrgObj
// Entry: 8011bc34
// Size: 172 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onDamaged__10CGPartyObjFP8CGPrgObj(CGPartyObj *gPartyObj,CGPrgObj *gPrgObj)

{
  uint uVar1;
  
  uVar1 = (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0xc))(gPrgObj);
  if (((uVar1 & 0xad) == 0xad) && (Game.game.m_gameWork.m_menuStageMode != '\0')) {
    m_ghostWork__10CGPartyObj._4_4_ = m_ghostWork__10CGPartyObj._4_4_ + 1;
    m_ghostWork__10CGPartyObj._8_4_ = m_ghostWork__10CGPartyObj._8_4_ + 1;
    m_ghostWork__10CGPartyObj._12_4_ = m_ghostWork__10CGPartyObj._12_4_ + 1;
    Printf__7CSystemFPce
              (&System,&DAT_801dcb1c,m_ghostWork__10CGPartyObj._4_4_,Chara._8264_4_,
               m_ghostWork__10CGPartyObj._8_4_,Chara._8268_4_,m_ghostWork__10CGPartyObj._12_4_,
               Chara._8272_4_);
  }
  return;
}


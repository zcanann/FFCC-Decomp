// Function: ChangeCommandMode__10CGPartyObjFi
// Entry: 8011c59c
// Size: 220 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void ChangeCommandMode__10CGPartyObjFi(CGPartyObj *gPartyObj,int param_2)

{
  if (*(short *)&gPartyObj->field_0x6f4 != param_2) {
    *(short *)&gPartyObj->field_0x6f4 = (short)param_2;
    if (*(CRingMenu **)
         (&MenuPcs.field_0x13c + (int)(gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle[0xed] * 4
         ) == (CRingMenu *)0x0) {
      if (1 < (uint)System.m_execParam) {
        Printf__7CSystemFPce(&System,&DAT_801dcb38);
      }
    }
    else {
      SetBattleCommand__9CRingMenuFiii
                (*(CRingMenu **)
                  (&MenuPcs.field_0x13c +
                  (int)(gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle[0xed] * 4),0,0xffffffff,
                 0xffffffff);
      SetBattleCommand__9CRingMenuFiii
                (*(CRingMenu **)
                  (&MenuPcs.field_0x13c +
                  (int)(gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle[0xed] * 4),1,0xffffffff,
                 0xffffffff);
      SetBattleCommand__9CRingMenuFiii
                (*(CRingMenu **)
                  (&MenuPcs.field_0x13c +
                  (int)(gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle[0xed] * 4),2,0xffffffff,
                 0xffffffff);
    }
  }
  return;
}


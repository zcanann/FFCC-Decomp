// Function: onFramePostCalc__10CGPartyObjFv
// Entry: 80122fdc
// Size: 196 bytes

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onFramePostCalc__10CGPartyObjFv(CGPartyObj *param_1)

{
  uint uVar1;
  
  if ((param_1->gCharaObj).gPrgObj.object.m_scriptHandle != (void **)0x0) {
    if ((((Game.game.m_gameWork.m_menuStageMode == '\0') ||
         (0xe < Game.game.m_gameWork.m_bossArtifactStageIndex)) ||
        (uVar1 = (**(code **)((int)(param_1->gCharaObj).gPrgObj.object.base_object.object.m_vtable +
                             0xc))(), (uVar1 & 0x6d) != 0x6d)) ||
       ((param_1->gCharaObj).gPrgObj.object.m_scriptHandle[0xed] == (void *)0x0)) {
      command__10CGPartyObjFv(param_1);
      shouki__10CGPartyObjFv(param_1);
    }
    else {
      ghostPartyMog__10CGPartyObjFv(param_1);
    }
    *(undefined4 *)&param_1->field_0x6e4 = 0;
    *(undefined4 *)&param_1->field_0x6e8 = 0;
    *(undefined4 *)&param_1->field_0x6ec = DAT_8032ec24;
    onFramePostCalc__10CGCharaObjFv(param_1);
  }
  return;
}


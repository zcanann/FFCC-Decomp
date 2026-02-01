// Function: enableDamageCol__10CGPartyObjFi
// Entry: 801209d4
// Size: 188 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void enableDamageCol__10CGPartyObjFi(int param_1,int param_2)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar2 = 4;
  if (*(short *)(*(int *)(param_1 + 0x58) + 0x1c) != 0) {
    uVar2 = 8;
  }
  if ((param_2 == 0) ||
     ((((Game.game.m_gameWork.m_menuStageMode != '\0' &&
        (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf)) &&
       (uVar1 = (**(code **)(*(int *)(param_1 + 0x48) + 0xc))(param_1), (uVar1 & 0x6d) == 0x6d)) &&
      (*(int *)(*(int *)(param_1 + 0x58) + 0x3b4) != 0)))) {
    *(undefined4 *)(param_1 + 900) = 0;
    *(undefined4 *)(param_1 + 0x3ac) = 0;
  }
  else {
    *(undefined4 *)(param_1 + 900) = uVar2;
    *(undefined4 *)(param_1 + 0x3ac) = uVar2;
  }
  return;
}


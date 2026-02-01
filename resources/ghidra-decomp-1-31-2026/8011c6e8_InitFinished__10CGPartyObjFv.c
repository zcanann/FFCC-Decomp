// Function: InitFinished__10CGPartyObjFv
// Entry: 8011c6e8
// Size: 248 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void InitFinished__10CGPartyObjFv(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  
  _GetCurrentWeaponItem__12CCaravanWorkFRiRi
            (*(CCaravanWork **)(param_1 + 0x58),param_1 + 0x6dc,param_1 + 0x6e0);
  (**(code **)(*(int *)(param_1 + 0x48) + 0x94))(param_1,1);
  *(undefined4 *)(*(int *)(param_1 + 0x58) + 0xbd0) = 0;
  if ((((Game.game.m_gameWork.m_menuStageMode != '\0') &&
       (Game.game.m_gameWork.m_menuStageMode != '\0')) &&
      (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf)) &&
     ((uVar4 = (**(code **)(*(int *)(param_1 + 0x48) + 0xc))(param_1), fVar2 = FLOAT_80331ab0,
      (uVar4 & 0x6d) == 0x6d && (*(int *)(*(int *)(param_1 + 0x58) + 0x3b4) != 0)))) {
    *(undefined *)(param_1 + 0xe6) = 0;
    fVar1 = FLOAT_80331a98;
    *(float *)(param_1 + 0x144) = fVar2;
    fVar3 = FLOAT_80331ab4;
    *(float *)(param_1 + 0x134) = fVar2;
    *(float *)(param_1 + 0x13c) = fVar1;
    *(float *)(param_1 + 0x4e8) = fVar3;
    uVar4 = countLeadingZeros(*(undefined4 *)(param_1 + 0x6f0));
    m_boss__8CGMonObj._108_1_ =
         (byte)((int)(char)(uVar4 >> 5) << 7) | m_boss__8CGMonObj._108_1_ & 0x7f;
  }
  return;
}


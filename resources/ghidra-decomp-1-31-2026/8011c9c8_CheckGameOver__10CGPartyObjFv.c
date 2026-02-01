// Function: CheckGameOver__10CGPartyObjFv
// Entry: 8011c9c8
// Size: 240 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CheckGameOver__10CGPartyObjFv(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = -0x7fde1140;
  iVar3 = 0;
  Game.game.m_gameWork.m_gameOverFlag = '\x01';
  while (((iVar2 = *(int *)(iVar4 + 0xc5b0), iVar2 == 0 ||
          ((((Game.game.m_gameWork.m_menuStageMode != '\0' &&
             (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf)) &&
            (uVar1 = (**(code **)(*(int *)(iVar2 + 0x48) + 0xc))(iVar2), (uVar1 & 0x6d) == 0x6d)) &&
           (*(int *)(*(int *)(iVar2 + 0x58) + 0x3b4) != 0)))) ||
         ((*(short *)(*(int *)(iVar2 + 0x58) + 0x1c) == 0 &&
          (-1 < (int)((uint)*(byte *)(iVar2 + 0x6b8) << 0x1d | (uint)(*(byte *)(iVar2 + 0x6b8) >> 3)
                     )))))) {
    iVar3 = iVar3 + 1;
    iVar4 = iVar4 + 4;
    if (3 < iVar3) {
      return;
    }
  }
  Game.game.m_gameWork.m_gameOverFlag = '\0';
  return;
}


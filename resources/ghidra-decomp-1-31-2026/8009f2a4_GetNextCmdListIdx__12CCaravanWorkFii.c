// Function: GetNextCmdListIdx__12CCaravanWorkFii
// Entry: 8009f2a4
// Size: 224 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int GetNextCmdListIdx__12CCaravanWorkFii(CCaravanWork *caravanWork,int param_2,int param_3)

{
  int iVar1;
  
LAB_8009f2d4:
  do {
    iVar1 = param_2;
    param_2 = iVar1 + param_3;
    if (param_2 < 0) {
      param_2 = param_2 + (short)caravanWork->m_numCmdListSlots;
    }
    else if ((short)caravanWork->m_numCmdListSlots + -1 < param_2) {
      param_2 = param_2 - (short)caravanWork->m_numCmdListSlots;
    }
    if (Game.game.m_gameWork.m_menuStageMode != '\0') {
      if (*(short *)(caravanWork->m_commandListExtra + param_2 * 2) == -1) goto LAB_8009f2d4;
      if ((param_3 == -1) && (*(short *)(caravanWork->m_commandListExtra + param_2 * 2) == -1)) {
        if (0 < *(short *)(caravanWork->m_commandListExtra + iVar1 * 2)) goto LAB_8009f2d4;
      }
    }
    iVar1 = _DelCmdListAndItem__12CCaravanWorkFii(caravanWork,param_2);
    if ((param_2 < 2) || (0 < iVar1)) {
      return param_2;
    }
  } while( true );
}


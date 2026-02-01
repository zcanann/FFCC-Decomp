// Function: LoadLogoWaitingData__5CGameFv
// Entry: 80015e8c
// Size: 136 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void LoadLogoWaitingData__5CGameFv(CGame *game)

{
  if (game->m_assetsLoadedFlag == '\0') {
    createLoad__9CSoundPcsFv(&SoundPcs);
    createLoad__9CCharaPcsFv(&CharaPcs);
    createLoad__8CPartPcsFv(&PartPcs);
    game->m_assetsLoadedFlag = '\x01';
    if (2 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,&DAT_801d61dc);
    }
  }
  return;
}


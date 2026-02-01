// Function: GbaThreadInitGbaContext__12CMiniGamePcsFP16MgGbaThreadParami
// Entry: 8012a5f4
// Size: 1236 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void GbaThreadInitGbaContext__12CMiniGamePcsFP16MgGbaThreadParami
               (int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  
  puVar4 = (undefined *)(param_1 + *(char *)(param_2 + 0xbc) * 0x60 + 0x16ac);
  memset(puVar4,0,0x60);
  if (param_3 == 0) {
    *puVar4 = 1;
  }
  puVar4[1] = *(undefined *)(param_2 + 0xbc);
  puVar4[3] = 1;
  *(undefined4 *)(puVar4 + 4) = *(undefined4 *)(param_1 + 0x1364);
  puVar4[0x10] = *(undefined *)(param_1 + 0x134a);
  puVar4[0x11] = *(undefined *)(param_1 + 0x134b);
  puVar4[0x14] = 0xff;
  puVar4[0x15] = 0xff;
  puVar4[0x16] = 0xff;
  puVar4[0x17] = 0xff;
  puVar4[0x18] = 0xff;
  puVar4[0x19] = 0xff;
  puVar4[0x1a] = 0xff;
  puVar4[0x1b] = 0xff;
  puVar4[0x1c] = 0xff;
  puVar4[0x1d] = 0xff;
  puVar4[0x1e] = 0xff;
  puVar4[0x1f] = 0xff;
  puVar4[0x20] = 0xff;
  puVar4[0x21] = 0xff;
  puVar4[0x22] = 0xff;
  puVar4[0x23] = 0xff;
  if (Game.game.m_partyObjArr[0] == (CGPartyObj *)0x0) {
    puVar4[0x14] = 5;
    puVar4[0x15] = 0x11;
    puVar4[0x16] = 0x1e;
    puVar4[0x17] = 0x2a;
    puVar4[0x18] = 0x37;
    puVar4[0x19] = 0x43;
    puVar4[0x1a] = 0x50;
    puVar4[0x1b] = 0x5c;
  }
  else {
    iVar3 = 0;
    do {
      if (Game.game.m_gameWork.m_menuStageMode == '\0') {
        iVar2 = GetFoodLevel__5CGameFii(&Game.game,0,iVar3);
      }
      else {
        iVar2 = GetFoodLevel__5CGameFii(&Game.game,0,iVar3);
      }
      if (iVar2 < 1) {
        iVar2 = 1;
      }
      else if (100 < iVar2) {
        iVar2 = 100;
      }
      iVar1 = iVar3 + 0x14;
      iVar3 = iVar3 + 1;
      puVar4[iVar1] = (char)iVar2;
    } while (iVar3 < 8);
  }
  puVar4[0x24] = 0xff;
  puVar4[0x25] = 0xff;
  puVar4[0x26] = 0xff;
  puVar4[0x27] = 0xff;
  puVar4[0x28] = 0xff;
  puVar4[0x29] = 0xff;
  puVar4[0x2a] = 0xff;
  puVar4[0x2b] = 0xff;
  puVar4[0x2c] = 0xff;
  puVar4[0x2d] = 0xff;
  puVar4[0x2e] = 0xff;
  puVar4[0x2f] = 0xff;
  puVar4[0x30] = 0xff;
  puVar4[0x31] = 0xff;
  puVar4[0x32] = 0xff;
  puVar4[0x33] = 0xff;
  if (Game.game.m_partyObjArr[1] == (CGPartyObj *)0x0) {
    puVar4[0x24] = 5;
    puVar4[0x25] = 0x11;
    puVar4[0x26] = 0x1e;
    puVar4[0x27] = 0x2a;
    puVar4[0x28] = 0x37;
    puVar4[0x29] = 0x43;
    puVar4[0x2a] = 0x50;
    puVar4[0x2b] = 0x5c;
  }
  else {
    iVar3 = 0;
    do {
      if (Game.game.m_gameWork.m_menuStageMode == '\0') {
        iVar2 = GetFoodLevel__5CGameFii(&Game.game,1,iVar3);
      }
      else {
        iVar2 = GetFoodLevel__5CGameFii(&Game.game,0,iVar3);
      }
      if (iVar2 < 1) {
        iVar2 = 1;
      }
      else if (100 < iVar2) {
        iVar2 = 100;
      }
      iVar1 = iVar3 + 0x24;
      iVar3 = iVar3 + 1;
      puVar4[iVar1] = (char)iVar2;
    } while (iVar3 < 8);
  }
  puVar4[0x34] = 0xff;
  puVar4[0x35] = 0xff;
  puVar4[0x36] = 0xff;
  puVar4[0x37] = 0xff;
  puVar4[0x38] = 0xff;
  puVar4[0x39] = 0xff;
  puVar4[0x3a] = 0xff;
  puVar4[0x3b] = 0xff;
  puVar4[0x3c] = 0xff;
  puVar4[0x3d] = 0xff;
  puVar4[0x3e] = 0xff;
  puVar4[0x3f] = 0xff;
  puVar4[0x40] = 0xff;
  puVar4[0x41] = 0xff;
  puVar4[0x42] = 0xff;
  puVar4[0x43] = 0xff;
  if (Game.game.m_partyObjArr[2] == (CGPartyObj *)0x0) {
    puVar4[0x34] = 5;
    puVar4[0x35] = 0x11;
    puVar4[0x36] = 0x1e;
    puVar4[0x37] = 0x2a;
    puVar4[0x38] = 0x37;
    puVar4[0x39] = 0x43;
    puVar4[0x3a] = 0x50;
    puVar4[0x3b] = 0x5c;
  }
  else {
    iVar3 = 0;
    do {
      if (Game.game.m_gameWork.m_menuStageMode == '\0') {
        iVar2 = GetFoodLevel__5CGameFii(&Game.game,2,iVar3);
      }
      else {
        iVar2 = GetFoodLevel__5CGameFii(&Game.game,0,iVar3);
      }
      if (iVar2 < 1) {
        iVar2 = 1;
      }
      else if (100 < iVar2) {
        iVar2 = 100;
      }
      iVar1 = iVar3 + 0x34;
      iVar3 = iVar3 + 1;
      puVar4[iVar1] = (char)iVar2;
    } while (iVar3 < 8);
  }
  puVar4[0x44] = 0xff;
  puVar4[0x45] = 0xff;
  puVar4[0x46] = 0xff;
  puVar4[0x47] = 0xff;
  puVar4[0x48] = 0xff;
  puVar4[0x49] = 0xff;
  puVar4[0x4a] = 0xff;
  puVar4[0x4b] = 0xff;
  puVar4[0x4c] = 0xff;
  puVar4[0x4d] = 0xff;
  puVar4[0x4e] = 0xff;
  puVar4[0x4f] = 0xff;
  puVar4[0x50] = 0xff;
  puVar4[0x51] = 0xff;
  puVar4[0x52] = 0xff;
  puVar4[0x53] = 0xff;
  if (Game.game.m_partyObjArr[3] == (CGPartyObj *)0x0) {
    puVar4[0x44] = 5;
    puVar4[0x45] = 0x11;
    puVar4[0x46] = 0x1e;
    puVar4[0x47] = 0x2a;
    puVar4[0x48] = 0x37;
    puVar4[0x49] = 0x43;
    puVar4[0x4a] = 0x50;
    puVar4[0x4b] = 0x5c;
  }
  else {
    iVar3 = 0;
    do {
      if (Game.game.m_gameWork.m_menuStageMode == '\0') {
        iVar2 = GetFoodLevel__5CGameFii(&Game.game,3,iVar3);
      }
      else {
        iVar2 = GetFoodLevel__5CGameFii(&Game.game,0,iVar3);
      }
      if (iVar2 < 1) {
        iVar2 = 1;
      }
      else if (100 < iVar2) {
        iVar2 = 100;
      }
      iVar1 = iVar3 + 0x44;
      iVar3 = iVar3 + 1;
      puVar4[iVar1] = (char)iVar2;
    } while (iVar3 < 8);
  }
  return;
}


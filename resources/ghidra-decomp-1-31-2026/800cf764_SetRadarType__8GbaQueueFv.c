// Function: SetRadarType__8GbaQueueFv
// Entry: 800cf764
// Size: 684 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SetRadarType__8GbaQueueFv(GbaQueue *gbaQueue)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  OSSemaphore *osSemaphore;
  int unaff_r27;
  uint uVar6;
  GbaQueue *osSemaphore_00;
  int iVar7;
  uint uVar8;
  
  if ((gbaQueue->radarTypeFlg == '\0') && (Game.game.m_gameWork.m_bossArtifactStageIndex != 0x19)) {
    uVar8 = (uint)(-1 < Game.game.m_gameWork.m_wmBackupParams[0]);
    if (-1 < Game.game.m_gameWork.m_wmBackupParams[1]) {
      uVar8 = uVar8 + 1;
    }
    if (-1 < Game.game.m_gameWork.m_wmBackupParams[2]) {
      uVar8 = uVar8 + 1;
    }
    if (-1 < Game.game.m_gameWork.m_wmBackupParams[3]) {
      uVar8 = uVar8 + 1;
    }
    gbaQueue->field_0x2d32 = 1;
    uVar6 = 0;
    if ((Game.game.m_scriptFoodBase[0] != 0) &&
       (*(int *)(Game.game.m_scriptFoodBase[0] + 0x3a4) != 0)) {
      uVar6 = 1;
    }
    gbaQueue->field_0x2d33 = 1;
    if ((Game.game.m_scriptFoodBase[1] != 0) &&
       (*(int *)(Game.game.m_scriptFoodBase[1] + 0x3a4) != 0)) {
      uVar6 = uVar6 | 2;
    }
    gbaQueue->field_0x2d34 = 1;
    if ((Game.game.m_scriptFoodBase[2] != 0) &&
       (*(int *)(Game.game.m_scriptFoodBase[2] + 0x3a4) != 0)) {
      uVar6 = uVar6 | 4;
    }
    gbaQueue->field_0x2d35 = 1;
    if ((Game.game.m_scriptFoodBase[3] != 0) &&
       (*(int *)(Game.game.m_scriptFoodBase[3] + 0x3a4) != 0)) {
      uVar6 = uVar6 | 8;
    }
    iVar7 = 0;
    while (iVar7 < (int)uVar8) {
      iVar3 = rand();
      iVar5 = iVar3 >> 0x1f;
      iVar5 = (iVar5 * 4 | (uint)(iVar3 * 0x40000000 + iVar5) >> 0x1e) - iVar5;
      if ((uVar6 & 1 << iVar5) != 0) {
        iVar3 = iVar7;
        if (1 < iVar7) {
          if (iVar7 == 2) {
            uVar4 = rand();
            iVar3 = (uVar4 & 1) + 2;
          }
          else {
            uVar4 = countLeadingZeros(2 - unaff_r27);
            iVar3 = (uVar4 >> 5) + 2;
          }
        }
        osSemaphore = (OSSemaphore *)((int)gbaQueue + iVar5 * 0xc);
        OSWaitSemaphore(osSemaphore);
        *(char *)((int)gbaQueue + iVar5 + 0x2d32) = (char)iVar3;
        OSSignalSemaphore(osSemaphore);
        uVar6 = uVar6 & ~(1 << iVar5);
        iVar7 = iVar7 + 1;
        unaff_r27 = iVar3;
      }
    }
    if (gbaQueue->field_0x2d56 != '\0') {
      gbaQueue->field_0x2d32 = Game.game.m_gameWork.m_mogScoreRadarType;
      gbaQueue->field_0x2d33 = Game.game.m_gameWork.m_mogScoreRadarType;
      gbaQueue->field_0x2d34 = Game.game.m_gameWork.m_mogScoreRadarType;
      gbaQueue->field_0x2d35 = Game.game.m_gameWork.m_mogScoreRadarType;
    }
    gbaQueue->radarTypeFlg = 1;
    if (0xe < Game.game.m_gameWork.m_bossArtifactStageIndex) {
      gbaQueue->field_0x2d32 = 0;
      gbaQueue->field_0x2d33 = 0;
      gbaQueue->field_0x2d34 = 0;
      gbaQueue->field_0x2d35 = 0;
    }
    iVar7 = 0;
    osSemaphore_00 = gbaQueue;
    do {
      OSWaitSemaphore(osSemaphore_00->accessSemaphores);
      bVar1 = gbaQueue->field_0x2d41;
      bVar2 = (byte)(1 << iVar7);
      gbaQueue->field_0x2d41 = bVar1 & ~bVar2 | bVar2;
      if (bVar1 != gbaQueue->field_0x2d41) {
        gbaQueue->chgRadarMode = gbaQueue->chgRadarMode | bVar2;
      }
      OSSignalSemaphore(osSemaphore_00->accessSemaphores);
      iVar7 = iVar7 + 1;
      osSemaphore_00 = (GbaQueue *)(osSemaphore_00->accessSemaphores + 1);
    } while (iVar7 < 4);
  }
  return;
}


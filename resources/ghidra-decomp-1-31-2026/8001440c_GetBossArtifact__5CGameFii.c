// Function: GetBossArtifact__5CGameFii
// Entry: 8001440c
// Size: 308 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int GetBossArtifact__5CGameFii(CGame *game,int param_2,uint param_3)

{
  short sVar1;
  uint32_t uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined auStack_38 [2];
  short local_36;
  short local_34;
  short local_32;
  undefined4 local_30;
  uint uStack_2c;
  longlong local_28;
  
  iVar5 = Game.game.m_gameWork.m_bossArtifactStageTable
          [Game.game.m_gameWork.m_bossArtifactStageIndex];
  if (2 < iVar5) {
    iVar5 = 2;
  }
  uStack_2c = param_3 ^ 0x80000000;
  local_30 = 0x43300000;
  sVar1 = *(short *)(&DAT_8032e3d0 + iVar5 * 2);
  iVar5 = (int)((float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_8032f680) *
               (float)(&PTR_s_dvd__scft_newbattle_cfd_801e8350)[param_2]);
  local_28 = (longlong)iVar5;
  memset(auStack_38,0,8);
  uVar2 = Game.game.m_bossArtifactBase;
  iVar3 = (int)Game.game.m_gameWork.m_bossArtifactStageIndex;
  iVar6 = 3;
  iVar4 = Game.game.m_bossArtifactBase + iVar3 * 0x168;
  local_36 = *(short *)(iVar4 + 0x162);
  local_34 = *(short *)(iVar4 + 0x164);
  local_32 = *(short *)(iVar4 + 0x166);
  if (((iVar5 < local_32) && (iVar6 = 2, iVar5 < local_34)) && (iVar6 = 1, iVar5 < local_36)) {
    iVar6 = 0;
  }
  iVar5 = rand();
  return uVar2 + iVar3 * 0x168 + 0x20 +
                 ((int)sVar1 + (iVar5 - (iVar5 / (iVar6 + 1)) * (iVar6 + 1))) * 8;
}


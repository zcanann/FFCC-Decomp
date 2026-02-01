// Function: sendCombiToScript__10CGCharaObjFP10CGCharaObjii
// Entry: 8010b8b8
// Size: 256 bytes

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void sendCombiToScript__10CGCharaObjFP10CGCharaObjii
               (CGame *game,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  uint uVar2;
  CGame *pCVar3;
  int iVar4;
  undefined4 local_28;
  undefined4 local_24;
  
  iVar4 = 0;
  pCVar3 = game;
  while ((iVar4 < *(int *)(game->m_gameWork).m_linkTable[3][0][0] &&
         (((iVar1 = *(int *)((pCVar3->m_gameWork).m_linkTable[3][0][0] + 4), iVar1 == 0 ||
           ((((Game.game.m_gameWork.m_menuStageMode != '\0' &&
              (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf)) &&
             (uVar2 = (**(code **)(*(int *)(iVar1 + 0x48) + 0xc))(), (uVar2 & 0x6d) == 0x6d)) &&
            (*(int *)(*(int *)(*(int *)((pCVar3->m_gameWork).m_linkTable[3][0][0] + 4) + 0x58) +
                     0x3b4) != 0)))) ||
          ((iVar1 = *(int *)(*(int *)((pCVar3->m_gameWork).m_linkTable[3][0][0] + 4) + 0x520),
           iVar1 == 6 || (iVar1 == 2))))))) {
    pCVar3 = (CGame *)&pCVar3->unk_0x4;
    iVar4 = iVar4 + 1;
  }
  if (iVar4 == *(int *)(game->m_gameWork).m_linkTable[3][0][0]) {
    local_28 = param_2;
    local_24 = param_3;
    SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
              (&CFlat,game,2,0x17,2,&local_28,(CStack *)0x0);
  }
  return;
}


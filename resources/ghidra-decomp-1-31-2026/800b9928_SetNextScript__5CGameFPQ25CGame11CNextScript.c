// Function: SetNextScript__5CGameFPQ25CGame11CNextScript
// Entry: 800b9928
// Size: 56 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SetNextScript__5CGameFPQ25CGame11CNextScript(CGame *game,CNextScript *nextScript)

{
  uint32_t *puVar1;
  uint32_t uVar2;
  char *pcVar3;
  CNextScript *pCVar4;
  int iVar5;
  
  pCVar4 = &game->m_nextScript;
  pcVar3 = nextScript[-1].m_name + 0xfc;
  iVar5 = 0x20;
  do {
    puVar1 = (uint32_t *)(pcVar3 + 4);
    pcVar3 = pcVar3 + 8;
    uVar2 = *(uint32_t *)pcVar3;
    *(uint32_t *)pCVar4->m_name = *puVar1;
    pCVar4 = (CNextScript *)(pCVar4->m_name + 4);
    pCVar4->m_flags = uVar2;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  game->m_newGameFlag = 1;
  return;
}


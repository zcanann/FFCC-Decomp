// Function: GetFoodRank__12CCaravanWorkFi
// Entry: 800a1ab0
// Size: 172 bytes

int GetFoodRank__12CCaravanWorkFi(CCaravanWork *caravanWork,int param_2)

{
  CCaravanWork *pCVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = 0;
  iVar3 = 0;
  iVar4 = 2;
  pCVar1 = caravanWork;
  do {
    if ((param_2 != iVar3) && (caravanWork->m_letterMeta[param_2] < pCVar1->m_letterMeta[0])) {
      iVar2 = iVar2 + 1;
    }
    if ((param_2 != iVar3 + 1) && (caravanWork->m_letterMeta[param_2] < pCVar1->m_letterMeta[1])) {
      iVar2 = iVar2 + 1;
    }
    if ((param_2 != iVar3 + 2) && (caravanWork->m_letterMeta[param_2] < pCVar1->m_letterMeta[2])) {
      iVar2 = iVar2 + 1;
    }
    if ((param_2 != iVar3 + 3) && (caravanWork->m_letterMeta[param_2] < pCVar1->m_letterMeta[3])) {
      iVar2 = iVar2 + 1;
    }
    pCVar1 = (CCaravanWork *)&(pCVar1->gObjWork).m_saveSlot;
    iVar3 = iVar3 + 4;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  return iVar2;
}


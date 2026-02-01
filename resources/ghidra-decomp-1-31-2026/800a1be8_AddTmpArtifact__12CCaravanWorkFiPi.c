// Function: AddTmpArtifact__12CCaravanWorkFiPi
// Entry: 800a1be8
// Size: 148 bytes

undefined4 AddTmpArtifact__12CCaravanWorkFiPi(CCaravanWork *caravanWork,int param_2,int *param_3)

{
  CCaravanWork *pCVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  iVar3 = 4;
  pCVar1 = caravanWork;
  do {
    if (pCVar1->m_treasures[0] == 0xffff) {
      caravanWork->m_treasures[iVar2] = (uint16_t)param_2;
      SetTmpArti__6JoyBusFiii(&Joybus,caravanWork->m_joybusCaravanId,iVar2,param_2);
      if (param_3 != (int *)0x0) {
        *param_3 = iVar2;
      }
      return 1;
    }
    pCVar1 = (CCaravanWork *)((int)&(pCVar1->gObjWork).vtable + 2);
    iVar2 = iVar2 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return 0;
}


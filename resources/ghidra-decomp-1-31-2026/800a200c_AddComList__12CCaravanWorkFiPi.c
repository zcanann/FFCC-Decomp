// Function: AddComList__12CCaravanWorkFiPi
// Entry: 800a200c
// Size: 164 bytes

undefined4 AddComList__12CCaravanWorkFiPi(CCaravanWork *caravanWork,uint16_t param_2,int *param_3)

{
  int iVar1;
  int32_t *piVar2;
  int iVar3;
  
  iVar3 = 2;
  piVar2 = &(caravanWork->gObjWork).m_objType;
  iVar1 = (short)caravanWork->m_numCmdListSlots + -2;
  if (2 < (short)caravanWork->m_numCmdListSlots) {
    do {
      if (*(short *)(piVar2 + 0x81) == -1) {
        caravanWork->m_commandListInventorySlotRef[iVar3] = param_2;
        SetCmdLst__6JoyBusFiis(&Joybus,caravanWork->m_joybusCaravanId,iVar3,param_2);
        if (param_3 != (int *)0x0) {
          *param_3 = iVar3;
        }
        return 1;
      }
      piVar2 = (int32_t *)((int)piVar2 + 2);
      iVar3 = iVar3 + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  return 0;
}


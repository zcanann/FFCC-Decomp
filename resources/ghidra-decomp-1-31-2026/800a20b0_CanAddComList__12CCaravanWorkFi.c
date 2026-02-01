// Function: CanAddComList__12CCaravanWorkFi
// Entry: 800a20b0
// Size: 64 bytes

uint CanAddComList__12CCaravanWorkFi(CCaravanWork *caravanWork,int param_2)

{
  int iVar1;
  uint uVar2;
  int32_t *piVar3;
  
  piVar3 = &(caravanWork->gObjWork).m_objType;
  iVar1 = (short)caravanWork->m_numCmdListSlots + -2;
  if (2 < (short)caravanWork->m_numCmdListSlots) {
    do {
      if ((*(short *)(piVar3 + 0x81) == -1) && (param_2 = param_2 + -1, param_2 == 0)) break;
      piVar3 = (int32_t *)((int)piVar3 + 2);
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  uVar2 = countLeadingZeros(param_2);
  return uVar2 >> 5 & 0xff;
}


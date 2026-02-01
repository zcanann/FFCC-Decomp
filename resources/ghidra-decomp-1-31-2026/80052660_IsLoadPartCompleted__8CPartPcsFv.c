// Function: IsLoadPartCompleted__8CPartPcsFv
// Entry: 80052660
// Size: 260 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

ulonglong IsLoadPartCompleted__8CPartPcsFv(void)

{
  uint uVar1;
  CPartMng *pCVar2;
  int iVar3;
  
  pCVar2 = &PartMng;
  uVar1 = 0;
  iVar3 = 2;
  while( true ) {
    if (pCVar2->m_partAsyncBusy[0] != 0) {
      return (ulonglong)uVar1;
    }
    if (pCVar2->m_partAsyncBusy[1] != 0) {
      return (ulonglong)uVar1;
    }
    if (pCVar2->m_partAsyncBusy[2] != 0) {
      return (ulonglong)uVar1;
    }
    if (pCVar2->m_partAsyncBusy[3] != 0) {
      return (ulonglong)uVar1;
    }
    if (pCVar2->m_partAsyncBusy[4] != 0) {
      return (ulonglong)uVar1;
    }
    if (pCVar2->m_partAsyncBusy[5] != 0) {
      return (ulonglong)uVar1;
    }
    if (pCVar2->m_partAsyncBusy[6] != 0) {
      return (ulonglong)uVar1;
    }
    if (pCVar2->m_partAsyncBusy[7] != 0) break;
    pCVar2 = (CPartMng *)((pCVar2->m_cursorPacket).m_cursorPacketRaw + 8);
    uVar1 = uVar1 + 7;
    iVar3 = iVar3 + -1;
    if (iVar3 == 0) {
      return CONCAT44(1,uVar1);
    }
  }
  return (ulonglong)uVar1;
}


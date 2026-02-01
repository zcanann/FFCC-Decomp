// Function: pppGetFreeDataMng__8CPartMngFv
// Entry: 8005880c
// Size: 212 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int pppGetFreeDataMng__8CPartMngFv(CPartMng *partMng)

{
  int iVar1;
  pppPdtSlot *ppVar2;
  void **ppvVar3;
  int iVar4;
  
  ppvVar3 = (void **)&partMng->m_charaVisToggle;
  iVar1 = 8;
  iVar4 = 0x18;
  do {
    if (((pppPdtSlot *)(ppvVar3 + 0x8b86))->m_pppDataHead == (_pppDataHead *)0x0) {
      ppVar2 = partMng->m_pdtSlots + iVar1;
      goto LAB_8005885c;
    }
    ppvVar3 = ppvVar3 + 0xe;
    iVar1 = iVar1 + 1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  ppVar2 = (pppPdtSlot *)0x0;
LAB_8005885c:
  if (ppVar2 == (pppPdtSlot *)0x0) {
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,s_pppGetFreePppDataMngSt_CAN_NOT_A_801d826c);
    }
    OSPanic(s_partMng_cpp_801d8230,0xd74,&DAT_8032fe1c);
    iVar1 = -1;
  }
  else {
    iVar1 = (int)ppVar2 - (int)partMng->m_pdtSlots;
    iVar1 = iVar1 / 0x38 + (iVar1 >> 0x1f);
    iVar1 = iVar1 - (iVar1 >> 0x1f);
  }
  return iVar1;
}


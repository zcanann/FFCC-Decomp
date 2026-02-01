// Function: AddMessageCallback__4CUSBFPFUlPv10MCCChannel_vPv
// Entry: 8002261c
// Size: 168 bytes

void AddMessageCallback__4CUSBFPFUlPv10MCCChannel_vPv(CUSB *usb,void *callback,void *callerContext)

{
  CUSBCallbackEntry *pCVar1;
  int iVar2;
  int iVar3;
  
  pCVar1 = usb->m_callbacks;
  iVar2 = 0;
  iVar3 = 8;
  while( true ) {
    if (pCVar1->m_inUse == 0) {
      pCVar1->m_inUse = 1;
      pCVar1->m_callback = callback;
      pCVar1->m_callerContext = callerContext;
      goto LAB_80022690;
    }
    if (pCVar1->m_callback == callback) break;
    iVar2 = iVar2 + 1;
    pCVar1 = pCVar1 + 1;
    iVar3 = iVar3 + -1;
    if (iVar3 == 0) {
LAB_80022690:
      if (iVar2 == 8) {
        Printf__7CSystemFPce(&System,s_CUSB_AddMessageCallback__C_x_g_B_801d7020);
      }
      return;
    }
  }
  Printf__7CSystemFPce(&System,s_CUSB_AddMessageCallback__C_x_g_o_801d6fdc);
  goto LAB_80022690;
}


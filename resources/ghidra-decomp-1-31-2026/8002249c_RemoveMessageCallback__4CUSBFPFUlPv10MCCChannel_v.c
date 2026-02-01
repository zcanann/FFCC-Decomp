// Function: RemoveMessageCallback__4CUSBFPFUlPv10MCCChannel_v
// Entry: 8002249c
// Size: 384 bytes

void RemoveMessageCallback__4CUSBFPFUlPv10MCCChannel_v(CUSB *usb,MCCChannel *mccChannel)

{
  int iVar1;
  
  iVar1 = 0;
  if ((usb->m_callbacks[0].m_inUse == 0) ||
     ((MCCChannel *)usb->m_callbacks[0].m_callback != mccChannel)) {
    iVar1 = 1;
    if ((usb->m_callbacks[1].m_inUse == 0) ||
       ((MCCChannel *)usb->m_callbacks[1].m_callback != mccChannel)) {
      iVar1 = 2;
      if ((usb->m_callbacks[2].m_inUse == 0) ||
         ((MCCChannel *)usb->m_callbacks[2].m_callback != mccChannel)) {
        iVar1 = 3;
        if ((usb->m_callbacks[3].m_inUse == 0) ||
           ((MCCChannel *)usb->m_callbacks[3].m_callback != mccChannel)) {
          iVar1 = 4;
          if ((usb->m_callbacks[4].m_inUse == 0) ||
             ((MCCChannel *)usb->m_callbacks[4].m_callback != mccChannel)) {
            iVar1 = 5;
            if ((usb->m_callbacks[5].m_inUse == 0) ||
               ((MCCChannel *)usb->m_callbacks[5].m_callback != mccChannel)) {
              iVar1 = 6;
              if ((usb->m_callbacks[6].m_inUse == 0) ||
                 ((MCCChannel *)usb->m_callbacks[6].m_callback != mccChannel)) {
                iVar1 = 7;
                if ((usb->m_callbacks[7].m_inUse == 0) ||
                   ((MCCChannel *)usb->m_callbacks[7].m_callback != mccChannel)) {
                  iVar1 = 8;
                }
                else {
                  usb->m_callbacks[7].m_inUse = 0;
                }
              }
              else {
                usb->m_callbacks[6].m_inUse = 0;
              }
            }
            else {
              usb->m_callbacks[5].m_inUse = 0;
            }
          }
          else {
            usb->m_callbacks[4].m_inUse = 0;
          }
        }
        else {
          usb->m_callbacks[3].m_inUse = 0;
        }
      }
      else {
        usb->m_callbacks[2].m_inUse = 0;
      }
    }
    else {
      usb->m_callbacks[1].m_inUse = 0;
    }
  }
  else {
    usb->m_callbacks[0].m_inUse = 0;
  }
  if (iVar1 == 8) {
    Printf__7CSystemFPce(&System,s_CUSB_AddMessageCallback__C_x_g_o_801d6f9c);
  }
  return;
}


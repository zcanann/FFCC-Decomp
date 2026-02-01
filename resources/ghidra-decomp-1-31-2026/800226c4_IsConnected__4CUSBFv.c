// Function: IsConnected__4CUSBFv
// Entry: 800226c4
// Size: 20 bytes

uint IsConnected__4CUSBFv(CUSB *usb)

{
  uint uVar1;
  
  uVar1 = countLeadingZeros(8 - usb->m_connectionState);
  return uVar1 >> 5 & 0xff;
}


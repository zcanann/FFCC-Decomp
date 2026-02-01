// Function: SendDataCode__7CUSBPcsFiPvii
// Entry: 8001ff6c
// Size: 532 bytes

undefined4
SendDataCode__7CUSBPcsFiPvii
          (CUSBPcs *usbPcs,uint param_2,undefined4 param_3,int param_4,uint param_5)

{
  uint *ptr;
  int iVar1;
  uint *dstBuffer;
  uint uVar2;
  CStage *pCVar3;
  undefined4 uVar4;
  uint count;
  
  count = param_4 * param_5;
  uVar2 = count + 0x5f & 0xffffffe0;
  pCVar3 = usbPcs->m_bigStage;
  if (pCVar3 == (CStage *)0x0) {
    pCVar3 = usbPcs->m_smallStage;
  }
  ptr = (uint *)__nwa__FUlPQ27CMemory6CStagePci(uVar2,pCVar3,s_p_usb_cpp_801d6d08,0x1ca);
  ptr[1] = uVar2;
  *ptr = 4;
  ptr[9] = param_2 << 0x18 | (param_2 >> 8 & 0xff) << 0x10 | (param_2 >> 0x10 & 0xff) << 8 |
           param_2 >> 0x18;
  ptr[10] = param_5 << 0x18 | (param_5 >> 8 & 0xff) << 0x10 | (param_5 >> 0x10 & 0xff) << 8 |
            param_5 >> 0x18;
  ptr[0xc] = count * 0x1000000 | (count >> 8 & 0xff) << 0x10 | (count >> 0x10 & 0xff) << 8 |
             count >> 0x18;
  ptr[0xb] = 0;
  ptr[8] = count * 0x1000000 | (count >> 8 & 0xff) << 0x10 | (count >> 0x10 & 0xff) << 8 |
           count >> 0x18;
  memcpy(ptr + 0x10,param_3,count);
  iVar1 = IsConnected__4CUSBFv(&USB);
  if (iVar1 == 0) {
    uVar4 = 0;
  }
  else {
    pCVar3 = usbPcs->m_bigStage;
    if (pCVar3 == (CStage *)0x0) {
      pCVar3 = usbPcs->m_smallStage;
    }
    dstBuffer = (uint *)__nwa__FUlPQ27CMemory6CStagePci
                                  (ptr[1] + 0x1f & 0xffffffe0,pCVar3,s_p_usb_cpp_801d6d08,0x19e);
    memcpy(dstBuffer,ptr,ptr[1] + 0x1f & 0xffffffe0);
    uVar2 = *ptr;
    *dstBuffer = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
                 uVar2 >> 0x18;
    uVar2 = ptr[1];
    dstBuffer[1] = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
                   uVar2 >> 0x18;
    DCFlushRange(dstBuffer,ptr[1] + 0x1f & 0xffffffe0);
    DCInvalidateRange(dstBuffer,ptr[1] + 0x1f & 0xffffffe0);
    iVar1 = Write__4CUSBFPvi(&USB,dstBuffer,ptr[1] + 0x1f & 0xffffffe0);
    if (iVar1 == 0) {
      __dla__FPv(dstBuffer);
      uVar4 = 0;
    }
    else {
      iVar1 = SendMessage__4CUSBFUl10MCCChannel(&USB,0,9);
      if (iVar1 == 0) {
        __dla__FPv(dstBuffer);
        uVar4 = 0;
      }
      else {
        __dla__FPv(dstBuffer);
        uVar4 = 1;
      }
    }
  }
  if (ptr != (uint *)0x0) {
    __dla__FPv(ptr);
  }
  return uVar4;
}


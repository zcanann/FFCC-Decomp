// Function: GXCPInterruptHandler
// Entry: 801a02c8
// Size: 308 bytes

void GXCPInterruptHandler(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined auStack_2d0 [716];
  
  iVar1 = DAT_80333828;
  *(uint *)(DAT_80333828 + 0xc) = (uint)*DAT_8032f2ec;
  if (((*(uint *)(iVar1 + 8) >> 3 & 1) != 0) && ((*(uint *)(iVar1 + 0xc) >> 1 & 1) != 0)) {
    OSResumeThread(DAT_8032f318);
    DAT_8032f320 = 0;
    __GXWriteFifoIntReset(1,1);
    __GXWriteFifoIntEnable(1,0);
  }
  if (((*(uint *)(DAT_80333828 + 8) >> 2 & 1) != 0) && ((*(uint *)(DAT_80333828 + 0xc) & 1) != 0)) {
    DAT_8032f328 = DAT_8032f328 + 1;
    __GXWriteFifoIntEnable(0,1);
    __GXWriteFifoIntReset(1,0);
    DAT_8032f320 = 1;
    OSSuspendThread(DAT_8032f318);
  }
  iVar1 = DAT_80333828;
  if (((*(uint *)(DAT_80333828 + 8) >> 5 & 1) != 0) &&
     ((*(uint *)(DAT_80333828 + 0xc) >> 4 & 1) != 0)) {
    *(uint *)(DAT_80333828 + 8) = *(uint *)(DAT_80333828 + 8) & 0xffffffdf;
    DAT_8032f2ec[1] = (ushort)*(undefined4 *)(iVar1 + 8);
    if (DAT_8032f324 != (code *)0x0) {
      OSClearContext(auStack_2d0);
      OSSetCurrentContext(auStack_2d0);
      (*DAT_8032f324)();
      OSClearContext(auStack_2d0);
      OSSetCurrentContext(param_2);
    }
  }
  return;
}


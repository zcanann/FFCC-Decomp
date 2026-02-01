// Function: _DMACheckProcess__Fv
// Entry: 801bdfac
// Size: 280 bytes

void _DMACheckProcess__Fv(void)

{
  undefined4 uVar1;
  int *piVar2;
  
  if (DAT_8032f408 != 0) {
    OSReport(s__s______DMA_CHECK_PROCESS______801e7788,&DAT_801e77a8);
    fflush(&DAT_8021d1a8);
    uVar1 = OSGetSemaphoreCount((OSSemaphore *)&DAT_8032ddd8);
    OSReport(s__s_Status____d__Semaphore____d__E_801e77ba,&DAT_801e77a8,DAT_8032f468,uVar1,
             DAT_8032f484,DAT_8032f488);
    fflush(&DAT_8021d1a8);
  }
  piVar2 = &DAT_8032b860;
  do {
    if ((*piVar2 != 0) && (DAT_8032f408 != 0)) {
      OSReport(s__s_ID____d__MMem____8_8X__AMem___801e77f8,&DAT_801e77a8,*piVar2,piVar2[2],piVar2[3]
               ,piVar2[4],piVar2[5]);
      fflush(&DAT_8021d1a8);
    }
    piVar2 = piVar2 + 7;
  } while (piVar2 < &DAT_8032d460);
  fflush(&DAT_8021d1a8);
  return;
}


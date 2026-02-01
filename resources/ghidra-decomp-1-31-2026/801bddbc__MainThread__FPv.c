// Function: _MainThread__FPv
// Entry: 801bddbc
// Size: 300 bytes

undefined4 _MainThread__FPv(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  DAT_8032f3c4 = DAT_8032f3c4 | 1;
  while (DAT_8032f3c0 != 0) {
    OSWaitSemaphore((OSSemaphore *)&DAT_8032d778);
    if (DAT_8032f3c0 != 0) {
      iVar2 = OSGetTick();
      iVar1 = DAT_8032f3f0;
      iVar3 = DAT_8032f3b8;
      uVar4 = DAT_8032f3b8 - DAT_8032f458;
      if (*(short *)(DAT_8032f3f0 + 0x48e) != 0) {
        *(uint *)(DAT_8032f3f0 + 0x478) = *(int *)(DAT_8032f3f0 + 0x478) + uVar4;
      }
      DAT_8032f458 = iVar3;
      if (4 < uVar4) {
        uVar4 = 4;
      }
      MainControl__Fi(uVar4);
      StreamControl__Fv();
      _ExecuteCommand__Fv();
      if ((-1 < *DAT_8032f428) && (*(int *)(iVar1 + 0x470) < 0)) {
        _MusicPlaySequence__FPi(DAT_8032f428);
        *DAT_8032f428 = -1;
        DAT_8032f424 = 0;
      }
      do {
        iVar3 = OSTryWaitSemaphore((OSSemaphore *)&DAT_8032d778);
      } while (0 < iVar3);
      memmove(DAT_8032f3cc + 1,DAT_8032f3cc,0x18c);
      iVar3 = OSGetTick();
      *DAT_8032f3cc = iVar3 - iVar2;
    }
  }
  DAT_8032f3c4 = DAT_8032f3c4 & 0xfffffffe;
  return 0;
}


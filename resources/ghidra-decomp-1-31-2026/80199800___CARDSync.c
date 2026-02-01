// Function: __CARDSync
// Entry: 80199800
// Size: 152 bytes

int __CARDSync(int chan)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = OSDisableInterrupts();
  while( true ) {
    if ((chan < 0) || (1 < chan)) {
      iVar1 = -0x80;
    }
    else {
      iVar1 = (&DAT_80327544)[chan * 0x44];
    }
    if (iVar1 != -1) break;
    OSSleepThread(&DAT_803275cc + chan * 0x110);
  }
  OSRestoreInterrupts(uVar2);
  return iVar1;
}


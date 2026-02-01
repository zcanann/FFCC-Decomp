// Function: PADReceiveCheckCallback
// Entry: 8018dc08
// Size: 308 bytes

void PADReceiveCheckCallback(int param_1,uint param_2)

{
  undefined4 uVar1;
  uint uVar2;
  
  uVar2 = 0x80000000 >> param_1;
  if ((DAT_8032f13c & uVar2) != 0) {
    DAT_8032f148 = DAT_8032f148 & ~uVar2;
    DAT_8032f14c = DAT_8032f14c & ~uVar2;
    if (((((param_2 & 0xf) == 0) && ((param_2 & 0x80000000) != 0)) && ((param_2 & 0x100000) != 0))
       && ((((param_2 & 0x40000000) != 0 && ((param_2 & 0x4000000) == 0)) &&
           (((param_2 & 0x80000) == 0 && ((param_2 & 0x40000) == 0)))))) {
      SITransfer(param_1,&DAT_8032eb30,1,&DAT_8030cca0 + param_1 * 0xc,10,PADOriginUpdateCallback,0,
                 0);
      return;
    }
    uVar1 = OSDisableInterrupts();
    SIDisablePolling(uVar2);
    uVar2 = ~uVar2;
    DAT_8032f13c = DAT_8032f13c & uVar2;
    DAT_8032f148 = DAT_8032f148 & uVar2;
    DAT_8032f14c = DAT_8032f14c & uVar2;
    DAT_8032f150 = DAT_8032f150 & uVar2;
    OSSetWirelessID(param_1,0);
    OSRestoreInterrupts(uVar1);
  }
  return;
}


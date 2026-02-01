// Function: PADOriginUpdateCallback
// Entry: 8018d744
// Size: 192 bytes

void PADOriginUpdateCallback(int param_1,uint param_2)

{
  undefined4 uVar1;
  uint uVar2;
  
  uVar2 = 0x80000000 >> param_1;
  if ((DAT_8032f13c & uVar2) != 0) {
    if ((param_2 & 0xf) == 0) {
      UpdateOrigin(param_1);
    }
    if ((param_2 & 8) != 0) {
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
  }
  return;
}


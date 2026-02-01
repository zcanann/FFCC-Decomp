// Function: TRKPostInterruptEvent
// Entry: 801ac618
// Size: 172 bytes

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void TRKPostInterruptEvent(void)

{
  uint uVar1;
  undefined4 uVar2;
  int local_18;
  undefined auStack_14 [20];
  
  if (_DAT_8032a1c0 == 0) {
    uVar1 = DAT_8032a4c0 & 0xffff;
    if ((uVar1 == 0xd00) || ((uVar1 < 0xd00 && (uVar1 == 0x700)))) {
      TRKTargetReadInstruction(&local_18,DAT_8032a248);
      if (local_18 == 0xfe00000) {
        uVar2 = 5;
      }
      else {
        uVar2 = 3;
      }
    }
    else {
      uVar2 = 4;
    }
    TRKConstructEvent(auStack_14,uVar2);
    TRKPostEvent(auStack_14);
  }
  else {
    _DAT_8032a1c0 = 0;
  }
  return;
}


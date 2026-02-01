// Function: TRKDoContinue
// Entry: 801aa568
// Size: 176 bytes

undefined4 TRKDoContinue(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_88;
  undefined local_84;
  undefined local_80;
  undefined4 local_48;
  undefined local_44;
  undefined local_40;
  
  MWTRACE(1,s_DoContinue_801e689c);
  iVar1 = TRKTargetStopped();
  if (iVar1 == 0) {
    memset(&local_48,0,0x40);
    local_44 = 0x80;
    local_48 = 0x40;
    local_40 = 0x16;
    TRKWriteUARTN(&local_48,0x40);
    uVar2 = 0;
  }
  else {
    memset(&local_88,0,0x40);
    local_84 = 0x80;
    local_88 = 0x40;
    local_80 = 0;
    TRKWriteUARTN(&local_88,0x40);
    uVar2 = TRKTargetContinue();
  }
  return uVar2;
}


// Function: TRKDoStop
// Entry: 801aa2a0
// Size: 168 bytes

undefined4 TRKDoStop(void)

{
  int iVar1;
  undefined uVar2;
  undefined4 local_48;
  undefined local_44;
  undefined local_40;
  
  iVar1 = TRKTargetStop();
  if (iVar1 == 0x704) {
    uVar2 = 0x21;
    goto LAB_801aa300;
  }
  if (iVar1 < 0x704) {
    if (iVar1 == 0) {
      uVar2 = 0;
      goto LAB_801aa300;
    }
  }
  else {
    if (iVar1 == 0x706) {
      uVar2 = 0x20;
      goto LAB_801aa300;
    }
    if (iVar1 < 0x706) {
      uVar2 = 0x22;
      goto LAB_801aa300;
    }
  }
  uVar2 = 1;
LAB_801aa300:
  memset(&local_48,0,0x40);
  local_44 = 0x80;
  local_48 = 0x40;
  local_40 = uVar2;
  TRKWriteUARTN(&local_48,0x40);
  return 0;
}


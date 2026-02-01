// Function: TRKDoSetOption
// Entry: 801aa1f8
// Size: 168 bytes

undefined4 TRKDoSetOption(int param_1)

{
  char cVar1;
  undefined4 local_48;
  undefined local_44;
  undefined local_40;
  
  cVar1 = *(char *)(param_1 + 0x1c);
  if (*(char *)(param_1 + 0x18) == '\x01') {
    usr_puts_serial(s_MetroTRK_Option___SerialIO___801e6868);
    if (cVar1 == '\0') {
      usr_puts_serial(s_Disable_801e6890);
    }
    else {
      usr_puts_serial(s_Enable_801e6888);
    }
    SetUseSerialIO(cVar1);
  }
  memset(&local_48,0,0x40);
  local_44 = 0x80;
  local_48 = 0x40;
  local_40 = 0;
  TRKWriteUARTN(&local_48,0x40);
  return 0;
}


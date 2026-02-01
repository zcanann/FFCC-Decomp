// Function: __close_console
// Entry: 801aeac0
// Size: 132 bytes

/* WARNING: Removing unreachable block (ram,0x801aeb0c) */

undefined4 __close_console(undefined4 param_1)

{
  int iVar1;
  byte bVar2;
  
  iVar1 = GetTRKConnected();
  if (iVar1 == 0) {
    return 1;
  }
  bVar2 = TRKCloseFile(0xd3,param_1);
  if (bVar2 != 1) {
    if (bVar2 == 0) {
      return 0;
    }
    if (bVar2 < 3) {
      return 2;
    }
  }
  return 1;
}


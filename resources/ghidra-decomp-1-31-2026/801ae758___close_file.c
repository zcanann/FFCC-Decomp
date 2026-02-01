// Function: __close_file
// Entry: 801ae758
// Size: 132 bytes

/* WARNING: Removing unreachable block (ram,0x801ae7a4) */

undefined4 __close_file(undefined4 param_1)

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


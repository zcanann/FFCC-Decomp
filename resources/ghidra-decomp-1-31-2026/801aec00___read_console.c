// Function: __read_console
// Entry: 801aec00
// Size: 188 bytes

/* WARNING: Removing unreachable block (ram,0x801aec80) */

undefined4 __read_console(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  char cVar2;
  int iVar1;
  byte bVar3;
  undefined4 local_18 [4];
  
  cVar2 = GetUseSerialIO();
  if ((cVar2 != '\0') && (iVar1 = GetTRKConnected(), iVar1 != 0)) {
    local_18[0] = *param_3;
    bVar3 = TRKAccessFile(0xd1,0,local_18,param_2);
    *param_3 = local_18[0];
    if (bVar3 != 1) {
      if (bVar3 == 0) {
        return 0;
      }
      if (bVar3 < 3) {
        return 2;
      }
    }
  }
  return 1;
}


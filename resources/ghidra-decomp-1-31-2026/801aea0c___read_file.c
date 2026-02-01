// Function: __read_file
// Entry: 801aea0c
// Size: 180 bytes

/* WARNING: Removing unreachable block (ram,0x801aea80) */

undefined4 __read_file(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  byte bVar2;
  undefined4 local_18 [3];
  
  iVar1 = GetTRKConnected();
  if (iVar1 == 0) {
    return 1;
  }
  local_18[0] = *param_3;
  bVar2 = TRKAccessFile(0xd1,param_1,local_18,param_2);
  *param_3 = local_18[0];
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


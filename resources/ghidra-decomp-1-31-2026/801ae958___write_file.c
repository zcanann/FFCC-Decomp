// Function: __write_file
// Entry: 801ae958
// Size: 180 bytes

/* WARNING: Removing unreachable block (ram,0x801ae9cc) */

undefined4 __write_file(uint32_t handle,byte *buffer,uint32_t *count)

{
  int iVar1;
  byte bVar2;
  uint32_t local_18 [3];
  
  iVar1 = GetTRKConnected();
  if (iVar1 == 0) {
    return 1;
  }
  local_18[0] = *count;
  bVar2 = TRKAccessFile(0xd0,handle,local_18,buffer);
  *count = local_18[0];
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


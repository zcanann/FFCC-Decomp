// Function: __open_file
// Entry: 801ae7dc
// Size: 380 bytes

/* WARNING: Removing unreachable block (ram,0x801ae840) */
/* WARNING: Removing unreachable block (ram,0x801ae918) */

undefined4 __open_file(uint32_t handle,byte *param_2,uint32_t *param_3)

{
  byte bVar1;
  int iVar2;
  byte bVar3;
  uint uVar4;
  
  iVar2 = GetTRKConnected();
  if (iVar2 == 0) {
    return 1;
  }
  uVar4 = 0;
  bVar3 = *param_2 >> 6;
  bVar1 = *param_2 >> 3 & 7;
  if (bVar3 == 1) {
    uVar4 = 4;
  }
  else if (bVar3 == 0) {
    uVar4 = 1;
  }
  else if (bVar3 < 3) {
    uVar4 = 2;
  }
  if (bVar1 == 3) {
    uVar4 = uVar4 | 0x12;
  }
  else if (bVar1 < 3) {
    if (bVar1 == 1) {
      uVar4 = uVar4 | 1;
    }
    else if (bVar1 != 0) {
      uVar4 = uVar4 | 2;
    }
  }
  else if (bVar1 == 7) {
    uVar4 = 7;
  }
  else if ((bVar1 < 7) && (5 < bVar1)) {
    uVar4 = uVar4 | 4;
  }
  if ((param_2[1] >> 3 & 1) == 1) {
    uVar4 = uVar4 | 8;
  }
  bVar3 = TRKOpenFile(0xd2,handle,uVar4,param_3);
  if (bVar3 != 1) {
    if (bVar3 == 0) {
      return 0;
    }
    if (bVar3 < 3) {
      return 2;
    }
  }
  return 1;
}


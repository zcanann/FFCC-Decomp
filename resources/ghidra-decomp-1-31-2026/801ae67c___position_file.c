// Function: __position_file
// Entry: 801ae67c
// Size: 220 bytes

/* WARNING: Removing unreachable block (ram,0x801ae714) */

undefined4 __position_file(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  byte bVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  iVar1 = GetTRKConnected();
  if (iVar1 == 0) {
    return 1;
  }
  if (param_3 == 0) {
    uVar3 = 0;
  }
  else if (param_3 == 1) {
    uVar3 = 1;
  }
  else if (param_3 == 2) {
    uVar3 = 2;
  }
  bVar2 = TRKPositionFile(0xd4,param_1,param_2,uVar3);
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


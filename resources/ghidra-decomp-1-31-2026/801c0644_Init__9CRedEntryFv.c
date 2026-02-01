// Function: Init__9CRedEntryFv
// Entry: 801c0644
// Size: 244 bytes

void Init__9CRedEntryFv(int *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = RedNew__Fi(0x400);
  *param_1 = iVar2;
  iVar2 = RedNew__Fi(0x1000);
  param_1[1] = iVar2;
  iVar2 = RedNew__Fi(0x40);
  param_1[2] = iVar2;
  memset(*param_1,0,0x400);
  iVar2 = 0;
  do {
    iVar1 = iVar2 * 0x10;
    iVar2 = iVar2 + 1;
    *(undefined4 *)(*param_1 + iVar1) = 0xffffffff;
  } while (iVar2 < 0x40);
  memset(param_1[1],0,0x1000);
  iVar2 = 0;
  do {
    iVar1 = iVar2 * 0x10;
    iVar2 = iVar2 + 1;
    *(undefined4 *)(param_1[1] + iVar1) = 0xffffffff;
  } while (iVar2 < 0x100);
  memset(param_1[2],0,0x40);
  iVar2 = 0;
  do {
    iVar1 = iVar2 * 0x10;
    iVar2 = iVar2 + 1;
    *(undefined4 *)(param_1[2] + iVar1) = 0xffffffff;
  } while (iVar2 < 4);
  param_1[3] = -1;
  return;
}


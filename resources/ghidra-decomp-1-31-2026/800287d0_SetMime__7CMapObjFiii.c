// Function: SetMime__7CMapObjFiii
// Entry: 800287d0
// Size: 48 bytes

void SetMime__7CMapObjFiii(CMapObj *mapObj,undefined4 param_2,int param_3,undefined param_4)

{
  int iVar1;
  
  iVar1 = *(int *)&mapObj->field_0xec;
  *(undefined4 *)(iVar1 + 0x20) = param_2;
  *(undefined4 *)(iVar1 + 0x1c) = param_2;
  if (*(int *)(iVar1 + 0x28) < param_3) {
    param_3 = *(int *)(iVar1 + 0x28);
  }
  *(int *)(iVar1 + 0x24) = param_3;
  *(undefined *)(iVar1 + 0x17) = param_4;
  *(undefined *)(iVar1 + 0x18) = 1;
  return;
}


// Function: destroySingleMenu__8CMenuPcsFv
// Entry: 8014a67c
// Size: 336 bytes

void destroySingleMenu__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  int *piVar1;
  int iVar2;
  undefined4 local_18 [5];
  
  if (DAT_8032eeb8 != (CFileCHandle *)0x0) {
    Close__5CFileFPQ25CFile7CHandle(&File,DAT_8032eeb8);
    DAT_8032eeb8 = (CFileCHandle *)0x0;
  }
  piVar1 = *(int **)&menuPcs->field_0x108;
  if (piVar1 != (int *)0x0) {
    iVar2 = piVar1[1];
    piVar1[1] = iVar2 + -1;
    if ((iVar2 + -1 == 0) && (piVar1 != (int *)0x0)) {
      (**(code **)(*piVar1 + 8))(piVar1,1);
    }
    *(undefined4 *)&menuPcs->field_0x108 = 0;
  }
  freeTexture__8CMenuPcsFiiii(menuPcs,4,1,0x20,0xd);
  freeTexture__8CMenuPcsFiiii(menuPcs,5,2,0x2d,0x33);
  *(undefined4 *)&menuPcs->field_0xf0 = 0;
  menuPcs->field_0x85a = 0;
  menuPcs->field_0x859 = 0;
  DAT_8032eec4 = 0xffffffff;
  if (*(void **)&menuPcs->field_0x814 != (void *)0x0) {
    __dla__FPv(*(void **)&menuPcs->field_0x814);
    *(undefined4 *)&menuPcs->field_0x814 = 0;
  }
  if (*(int *)&menuPcs->field_0x850 != 0) {
    __dl__FPv();
    *(undefined4 *)&menuPcs->field_0x850 = 0;
  }
  if (*(int *)&menuPcs->field_0x82c != 0) {
    __dl__FPv();
    *(undefined4 *)&menuPcs->field_0x82c = 0;
  }
  if (*(int *)&menuPcs->field_0x848 != 0) {
    __dl__FPv();
    *(undefined4 *)&menuPcs->field_0x848 = 0;
  }
  local_18[0] = DAT_802381a7;
  GXSetCopyClear(local_18,0xffffff);
  return;
}


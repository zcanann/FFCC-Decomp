// Function: destroyWorld__8CMenuPcsFv
// Entry: 80101150
// Size: 756 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void destroyWorld__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  bool bVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  undefined4 local_18 [2];
  
  puVar5 = &menuPcs->field_0x10;
  iVar4 = 4;
  do {
    piVar2 = *(int **)(puVar5 + 0x10c);
    if (piVar2 != (int *)0x0) {
      iVar3 = piVar2[1];
      piVar2[1] = iVar3 + -1;
      if ((iVar3 + -1 == 0) && (piVar2 != (int *)0x0)) {
        (**(code **)(*piVar2 + 8))(piVar2,1);
      }
      *(undefined4 *)(puVar5 + 0x10c) = 0;
    }
    iVar4 = iVar4 + 1;
    puVar5 = puVar5 + 4;
  } while (iVar4 < 6);
  piVar2 = *(int **)&menuPcs->field_0xfc;
  if (piVar2 != (int *)0x0) {
    iVar4 = piVar2[1];
    piVar2[1] = iVar4 + -1;
    if ((iVar4 + -1 == 0) && (piVar2 != (int *)0x0)) {
      (**(code **)(*piVar2 + 8))(piVar2,1);
    }
    *(undefined4 *)&menuPcs->field_0xfc = 0;
  }
  if (*(int *)&menuPcs->field_0x81c != 0) {
    __dl__FPv();
    *(undefined4 *)&menuPcs->field_0x81c = 0;
  }
  freeTexture__8CMenuPcsFiiii(menuPcs,2,3,0x16,0x2f);
  piVar2 = *(int **)&menuPcs->field_0xbc;
  if (piVar2 != (int *)0x0) {
    if (piVar2 != (int *)0x0) {
      (**(code **)(*piVar2 + 8))(piVar2,1);
    }
    *(undefined4 *)&menuPcs->field_0xbc = 0;
  }
  if (*(void **)&menuPcs->field_0x814 != (void *)0x0) {
    __dla__FPv(*(void **)&menuPcs->field_0x814);
    *(undefined4 *)&menuPcs->field_0x814 = 0;
  }
  if (*(int *)&menuPcs->field_0x818 != 0) {
    __dl__FPv();
    *(undefined4 *)&menuPcs->field_0x818 = 0;
  }
  if (*(int *)&menuPcs->field_0x81c != 0) {
    __dl__FPv();
    *(undefined4 *)&menuPcs->field_0x81c = 0;
  }
  if (*(int *)&menuPcs->field_0x820 != 0) {
    __dl__FPv();
    *(undefined4 *)&menuPcs->field_0x820 = 0;
  }
  if (*(void **)&menuPcs->field_0x824 != (void *)0x0) {
    __dla__FPv(*(void **)&menuPcs->field_0x824);
    *(undefined4 *)&menuPcs->field_0x824 = 0;
  }
  if (*(void **)&menuPcs->field_0x828 != (void *)0x0) {
    __dla__FPv(*(void **)&menuPcs->field_0x828);
    *(undefined4 *)&menuPcs->field_0x828 = 0;
  }
  if (*(void **)&menuPcs->field_0x844 != (void *)0x0) {
    __dla__FPv(*(void **)&menuPcs->field_0x844);
    *(undefined4 *)&menuPcs->field_0x844 = 0;
  }
  if (*(int *)&menuPcs->field_0x82c != 0) {
    __dl__FPv();
    *(undefined4 *)&menuPcs->field_0x82c = 0;
  }
  if (menuPcs->m_unk0x838 != (uint32_t *)0x0) {
    __dla__FPv(menuPcs->m_unk0x838);
    menuPcs->m_unk0x838 = (uint32_t *)0x0;
  }
  if (*(int *)&menuPcs->field_0x83c != 0) {
    __dl__FPv();
    *(undefined4 *)&menuPcs->field_0x83c = 0;
  }
  iVar4 = *(int *)&menuPcs->field_0x840;
  if (iVar4 != 0) {
    if (iVar4 != 0) {
      __dla__FPv((void *)(iVar4 + -0x10));
    }
    *(undefined4 *)&menuPcs->field_0x840 = 0;
  }
  if (*(int *)&menuPcs->field_0x848 != 0) {
    __dl__FPv();
    *(undefined4 *)&menuPcs->field_0x848 = 0;
  }
  if (menuPcs->field_0x858 != '\0') {
    THPSimpleAudioStop();
    THPSimpleLoadStop();
    THPSimpleClose();
    THPSimpleQuit();
    bVar1 = *(int *)&menuPcs->field_0x854 != 0;
    if (bVar1) {
      if (bVar1) {
        Free__7CMemoryFPv(&Memory);
        *(undefined4 *)&menuPcs->field_0x854 = 0;
      }
      *(undefined4 *)&menuPcs->field_0x854 = 0;
    }
    menuPcs->field_0x858 = 0;
  }
  pppDestroyAll__8CPartMngFv(&PartMng);
  McEnd__14CMemoryCardManFv(&MemoryCardMan);
  local_18[0] = DAT_802381a7;
  GXSetCopyClear(local_18,0xffffff);
  SetControllerMode__8GbaQueueFi(&GbaQue,0);
  return;
}


// Function: BindMcObj__8CMenuPcsFi
// Entry: 8017683c
// Size: 336 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void BindMcObj__8CMenuPcsFi(CMenuPcs *menuPcs,int param_2)

{
  uint32_t *puVar1;
  uint uVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar5 = 0;
  do {
    if (param_2 == iVar5) {
      puVar3 = (undefined4 *)(*(int *)&menuPcs->field_0x840 + (iVar5 + 0x11) * 0x524);
      if (-1 < (int)puVar3[1]) {
        pppDeletePart__8CPartMngFi(&PartMng,puVar3[1]);
        puVar3[1] = 0xffffffff;
        puVar3[2] = 0xffffffff;
        *puVar3 = 0xffffffff;
      }
      if (-1 < (int)puVar3[0x525]) {
        pppDeletePart__8CPartMngFi(&PartMng,puVar3[0x525]);
        puVar3[0x525] = 0xffffffff;
        puVar3[0x526] = 0xffffffff;
        puVar3[0x524] = 0xffffffff;
      }
    }
    iVar5 = iVar5 + 1;
  } while (iVar5 < 4);
  iVar5 = 0;
  iVar6 = 0;
  do {
    if (param_2 == iVar5) {
      puVar1 = menuPcs->m_unk0x838;
      iVar4 = *(int *)((int)puVar1 + iVar6 + 0xc);
      if (iVar4 != 0) {
        BindEffect__8CMenuPcsFiii(menuPcs,iVar5 + 0x11,iVar4 + 0x16,0xffffffff);
      }
      uVar2 = *(uint *)((int)puVar1 + iVar6 + 0x28);
      if ((uVar2 & 1) == 0) {
        if ((uVar2 & 2) == 0) {
          if ((uVar2 & 4) == 0) {
            if ((uVar2 & 8) == 0) {
              if ((uVar2 & 0x10) != 0) {
                iVar4 = 4;
              }
            }
            else {
              iVar4 = 3;
            }
          }
          else {
            iVar4 = 2;
          }
        }
        else {
          iVar4 = 1;
        }
      }
      else {
        iVar4 = 0;
      }
      BindEffect__8CMenuPcsFiii(menuPcs,iVar5 + 0x11,iVar4 + 0x1a,0xffffffff);
    }
    iVar5 = iVar5 + 1;
    iVar6 = iVar6 + 0x48;
  } while (iVar5 < 4);
  return;
}


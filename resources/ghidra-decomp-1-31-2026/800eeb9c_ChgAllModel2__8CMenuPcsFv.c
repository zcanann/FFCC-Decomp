// Function: ChgAllModel2__8CMenuPcsFv
// Entry: 800eeb9c
// Size: 232 bytes

void ChgAllModel2__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  CMenuPcs *pCVar8;
  int iVar9;
  int iVar10;
  
  iVar10 = 0;
  iVar7 = 0;
  iVar9 = 0;
  pCVar8 = menuPcs;
  do {
    iVar3 = *(int *)&menuPcs->field_0x88c + iVar9 + 0x14d0;
    if (*(int *)(iVar3 + 0x5b4) == 0) {
      uVar1 = 0xffffffff;
      *(undefined4 *)(*(int *)&menuPcs->field_0x824 + iVar10 + 8) = 0xffffffff;
      uVar6 = 0xffffffff;
      uVar4 = 0xffffffff;
    }
    else {
      uVar1 = (uint)*(ushort *)(iVar3 + 0x2e);
      uVar6 = (uint)*(ushort *)(iVar3 + 0x32);
      uVar4 = (uint)*(ushort *)(iVar3 + 0x30);
    }
    iVar3 = *(int *)&menuPcs->field_0x824 + iVar10;
    if ((int)uVar1 < 0) {
      uVar2 = 3;
      *(undefined *)(iVar3 + 0xc) = 0;
      iVar5 = 0x43;
    }
    else {
      uVar2 = 0;
      iVar5 = uVar1 * 200 + 100;
      if (uVar4 != 0) {
        iVar5 = uVar1 * 200 + 200;
      }
      iVar5 = iVar5 + uVar6;
      *(undefined *)(iVar3 + 0xc) = 1;
    }
    LoadModelASync__Q29CCharaPcs7CHandleFiUlUl
              (*(CCharaPcsCHandle **)&pCVar8->field_0x7f4,uVar2,iVar5,0);
    iVar7 = iVar7 + 1;
    iVar9 = iVar9 + 0x9c0;
    pCVar8 = (CMenuPcs *)&pCVar8->field_0x4;
    iVar10 = iVar10 + 0x34;
  } while (iVar7 < 8);
  return;
}


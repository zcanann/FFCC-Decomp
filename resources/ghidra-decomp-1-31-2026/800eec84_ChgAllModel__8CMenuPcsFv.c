// Function: ChgAllModel__8CMenuPcsFv
// Entry: 800eec84
// Size: 256 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void ChgAllModel__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  CMenuPcs *pCVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  
  iVar8 = -0x7fde1140;
  iVar10 = 0;
  iVar9 = 0;
  pCVar7 = menuPcs;
  do {
    iVar2 = *(int *)&menuPcs->field_0x824 + iVar9;
    if (*(int *)(iVar8 + 0x1794) == 0) {
      uVar4 = 0xffffffff;
      *(undefined4 *)(iVar2 + 8) = 0xffffffff;
      uVar5 = 0xffffffff;
      uVar6 = 0xffffffff;
    }
    else {
      uVar4 = (uint)*(ushort *)(iVar8 + 0x17d0);
      uVar6 = (uint)*(ushort *)(iVar8 + 0x17d2);
      uVar5 = (uint)*(ushort *)(iVar8 + 0x17d4);
      iVar1 = uVar4 * 200 + 100;
      if (uVar6 != 0) {
        iVar1 = uVar4 * 200 + 200;
      }
      *(uint *)(iVar2 + 8) = iVar1 + uVar5;
    }
    iVar2 = *(int *)&menuPcs->field_0x824 + iVar9;
    if ((int)uVar4 < 0) {
      uVar3 = 3;
      *(undefined *)(iVar2 + 0xc) = 0;
      iVar1 = 0x43;
    }
    else {
      uVar3 = 0;
      iVar1 = uVar4 * 200 + 100;
      if (uVar6 != 0) {
        iVar1 = uVar4 * 200 + 200;
      }
      iVar1 = iVar1 + uVar5;
      *(undefined *)(iVar2 + 0xc) = 1;
    }
    LoadModelASync__Q29CCharaPcs7CHandleFiUlUl
              (*(CCharaPcsCHandle **)&pCVar7->field_0x7f4,uVar3,iVar1,0);
    iVar10 = iVar10 + 1;
    iVar8 = iVar8 + 0xc30;
    pCVar7 = (CMenuPcs *)&pCVar7->field_0x4;
    iVar9 = iVar9 + 0x34;
  } while (iVar10 < 8);
  return;
}


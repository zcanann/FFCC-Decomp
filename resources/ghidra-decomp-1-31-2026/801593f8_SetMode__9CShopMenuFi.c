// Function: SetMode__9CShopMenuFi
// Entry: 801593f8
// Size: 604 bytes

void SetMode__9CShopMenuFi(CShopMenu *shopMenu,int param_2)

{
  int iVar1;
  int iVar2;
  
  (shopMenu->field0_0x0).ref.refCount = param_2;
  *(undefined4 *)&shopMenu->field_0xc = 0;
  switch((shopMenu->field0_0x0).ref.refCount) {
  case 0:
    *(float *)&shopMenu->field_0x1c = FLOAT_80332d9c;
    shopMenu->field_0x48 = 0xff;
    break;
  case 1:
    shopMenu->field_0x48 = 0;
    break;
  case 3:
    *(undefined4 *)&shopMenu->field_0x14 = 0;
    goto LAB_80159470;
  case 4:
  case 7:
    *(undefined4 *)&shopMenu->field_0x28 = 0;
    *(undefined4 *)&shopMenu->field_0x24 = 0;
    *(undefined4 *)&shopMenu->field_0x38 = 0;
    break;
  case 6:
    *(undefined4 *)&shopMenu->field_0x14 = 1;
LAB_80159470:
    *(undefined4 *)&shopMenu->field_0x10 = 0;
    *(undefined4 *)&shopMenu->field_0x28 = 0xffffffff;
    *(undefined4 *)&shopMenu->field_0x24 = 0;
    *(undefined4 *)&shopMenu->field_0x2c = 8;
    *(undefined4 *)&shopMenu->field_0x34 = 0;
    *(undefined4 *)&shopMenu->field_0x30 = 0;
    *(undefined4 *)&shopMenu->field_0x40 = 0;
    *(undefined4 *)&shopMenu->field_0x44 = 1;
    *(undefined4 *)&shopMenu->field_0x38 = 0;
    *(undefined4 *)&shopMenu->field_0x3c = 0;
    break;
  case 9:
    *(float *)&shopMenu->field_0x1c = FLOAT_80332d9c;
    shopMenu->field_0x48 = 0xff;
    iVar2 = 0;
    *(undefined4 *)&shopMenu->field_0x14 = 2;
    *(undefined4 *)&shopMenu->field_0x10 = 0;
    *(undefined4 *)&shopMenu->field_0x28 = 0;
    *(undefined4 *)&shopMenu->field_0x24 = 0;
    *(undefined4 *)&shopMenu->field_0x2c = 8;
    *(undefined4 *)&shopMenu->field_0x34 = 0;
    *(undefined4 *)&shopMenu->field_0x30 = 0;
    *(undefined4 *)&shopMenu->field_0x40 = 0;
    *(undefined4 *)&shopMenu->field_0x44 = 1;
    *(undefined4 *)&shopMenu->field_0x38 = 0;
    *(undefined4 *)&shopMenu->field_0x3c = 0;
    *(undefined4 *)&shopMenu->field_0x154 = 0xffffffff;
    *(undefined4 *)&shopMenu->field_0x4c = 0;
    do {
      iVar1 = GetItemType__8CMenuPcsFii(&MenuPcs,iVar2,0);
      if (iVar1 == 9) {
        iVar1 = *(int *)&shopMenu->field_0x4c;
        *(int *)&shopMenu->field_0x4c = iVar1 + 1;
        *(int *)(&shopMenu->field_0x50 + iVar1 * 4) = iVar2;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0x40);
    if (*(int *)&shopMenu->field_0x4c == 0) {
      *(undefined4 *)&shopMenu->field_0x4c = 1;
      *(undefined4 *)&shopMenu->field_0x50 = 0xffffffff;
      iVar2 = *(int *)&shopMenu->field_0x4c;
      *(int *)&shopMenu->field_0x4c = iVar2 + 1;
      *(undefined4 *)(&shopMenu->field_0x50 + iVar2 * 4) = 0xffffffff;
      iVar2 = *(int *)&shopMenu->field_0x4c;
      *(int *)&shopMenu->field_0x4c = iVar2 + 1;
      *(undefined4 *)(&shopMenu->field_0x50 + iVar2 * 4) = 0xffffffff;
      iVar2 = *(int *)&shopMenu->field_0x4c;
      *(int *)&shopMenu->field_0x4c = iVar2 + 1;
      *(undefined4 *)(&shopMenu->field_0x50 + iVar2 * 4) = 0xffffffff;
      iVar2 = *(int *)&shopMenu->field_0x4c;
      *(int *)&shopMenu->field_0x4c = iVar2 + 1;
      *(undefined4 *)(&shopMenu->field_0x50 + iVar2 * 4) = 0xffffffff;
      iVar2 = *(int *)&shopMenu->field_0x4c;
      *(int *)&shopMenu->field_0x4c = iVar2 + 1;
      *(undefined4 *)(&shopMenu->field_0x50 + iVar2 * 4) = 0xffffffff;
      iVar2 = *(int *)&shopMenu->field_0x4c;
      *(int *)&shopMenu->field_0x4c = iVar2 + 1;
      *(undefined4 *)(&shopMenu->field_0x50 + iVar2 * 4) = 0xffffffff;
      iVar2 = *(int *)&shopMenu->field_0x4c;
      *(int *)&shopMenu->field_0x4c = iVar2 + 1;
      *(undefined4 *)(&shopMenu->field_0x50 + iVar2 * 4) = 0xffffffff;
    }
    break;
  case 10:
    shopMenu->field_0x48 = 0;
    break;
  case 0xc:
    *(undefined4 *)&shopMenu->field_0x3c = 0;
  }
  return;
}


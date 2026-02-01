// Function: calcMenu__11CDbgMenuPcsFPQ211CDbgMenuPcs3CDM
// Entry: 8012cac0
// Size: 592 bytes

void calcMenu__11CDbgMenuPcsFPQ211CDbgMenuPcs3CDM(CMenuPcs *menuPcs,int param_2)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = param_2;
  do {
    *(int *)&menuPcs[4].field_0x7dc = iVar2;
    switch(*(undefined4 *)(iVar2 + 0x38)) {
    case 100:
      *(uint *)(iVar2 + 0x30) = (uint)(-CFlat._4772_4_ | CFlat._4772_4_) >> 0x1f;
      break;
    case 0x65:
      *(uint *)(iVar2 + 0x30) =
           (uint)(-(int)((char)CFlat._4836_1_ >> 7) | (int)((char)CFlat._4836_1_ >> 7)) >> 0x1f;
      break;
    case 0x66:
      uVar1 = (uint)(char)((int)((uint)(byte)CFlat._4836_1_ << 0x1c) >> 0x1f);
      *(uint *)(iVar2 + 0x30) = (-uVar1 | uVar1) >> 0x1f;
      break;
    case 0x67:
      *(uint *)(iVar2 + 0x30) = *(uint *)&menuPcs->field_0x4 & 1;
      break;
    case 0x68:
      *(uint *)(iVar2 + 0x30) = *(uint *)&menuPcs->field_0x4 >> 1 & 1;
      break;
    case 0x69:
      *(uint *)(iVar2 + 0x30) = *(uint *)&menuPcs->field_0x4 >> 2 & 1;
      break;
    case 0x6a:
      *(uint *)(iVar2 + 0x30) = *(uint *)&menuPcs->field_0x4 >> 3 & 1;
      break;
    case 0x6b:
      *(uint *)(iVar2 + 0x30) = *(uint *)&menuPcs->field_0x4 >> 4 & 1;
      break;
    case 0x6c:
      *(uint *)(iVar2 + 0x30) = *(uint *)&menuPcs->field_0x4 >> 5 & 1;
      break;
    case 0x6d:
      *(uint *)(iVar2 + 0x30) = *(uint *)&menuPcs->field_0x4 >> 6 & 1;
      break;
    case 0x6e:
      *(uint *)(iVar2 + 0x30) = *(uint *)&menuPcs->field_0x4 >> 7 & 1;
      break;
    case 0x6f:
      *(uint *)(iVar2 + 0x30) = *(uint *)&menuPcs->field_0x4 >> 8 & 1;
      break;
    case 0x70:
      *(uint *)(iVar2 + 0x30) = *(uint *)&menuPcs->field_0x4 >> 9 & 1;
      break;
    case 0x71:
      *(uint *)(iVar2 + 0x30) = *(uint *)&menuPcs->field_0x4 >> 10 & 1;
      break;
    case 0x72:
      *(uint *)(iVar2 + 0x30) = *(uint *)&menuPcs->field_0x4 >> 0xb & 1;
      break;
    case 0x73:
      *(uint *)(iVar2 + 0x30) = *(uint *)&menuPcs->field_0x4 >> 0xc & 1;
      break;
    case 0x75:
      *(uint *)(iVar2 + 0x30) = -(uint)DAT_8032ecd8 >> 0x1f;
      break;
    case 0x76:
      *(uint *)(iVar2 + 0x30) = -(uint)DAT_8032e698 >> 0x1f;
      break;
    case 0x78:
      *(uint *)(iVar2 + 0x30) = *(uint *)&menuPcs->field_0x4 >> 0xd & 1;
      break;
    case 0x79:
      *(uint *)(iVar2 + 0x30) = *(uint *)&menuPcs->field_0x4 >> 0xe & 1;
      break;
    case 0x7a:
      *(uint *)(iVar2 + 0x30) = *(uint *)&menuPcs->field_0x4 >> 0xf & 1;
    }
    *(int *)(iVar2 + 0x3c) = *(int *)(*(int *)(iVar2 + 0x4c) + 0x10) + *(int *)(iVar2 + 0x10);
    *(int *)(iVar2 + 0x40) = *(int *)(*(int *)(iVar2 + 0x4c) + 0x14) + *(int *)(iVar2 + 0x14);
    if (*(int *)(iVar2 + 0x50) != 0) {
      calcMenu__11CDbgMenuPcsFPQ211CDbgMenuPcs3CDM(menuPcs,*(int *)(iVar2 + 0x50));
    }
    iVar2 = *(int *)(iVar2 + 0x48);
  } while (iVar2 != param_2);
  return;
}


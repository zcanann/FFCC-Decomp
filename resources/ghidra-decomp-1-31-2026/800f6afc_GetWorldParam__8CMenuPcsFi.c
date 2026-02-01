// Function: GetWorldParam__8CMenuPcsFi
// Entry: 800f6afc
// Size: 628 bytes

uint GetWorldParam__8CMenuPcsFi(CMenuPcs *menuPcs,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = 0;
  switch(param_2) {
  case 0:
    uVar2 = (uint)(char)menuPcs->field_0x4;
    break;
  case 1:
    uVar2 = (uint)(char)menuPcs->field_0x6;
    break;
  case 2:
    uVar2 = (uint)*(short *)&menuPcs->field_0x1a;
    break;
  case 3:
    uVar2 = (uint)(char)menuPcs->field_0x7;
    break;
  case 4:
    uVar2 = (uint)(char)menuPcs->field_0x8;
    break;
  case 5:
    uVar2 = (uint)*(short *)&menuPcs->field_0x1c;
    break;
  case 6:
    uVar2 = (uint)*(short *)&menuPcs->field_0x1e;
    break;
  case 7:
    uVar2 = (uint)(char)menuPcs->field_0x9;
    break;
  case 8:
    uVar2 = (uint)(char)menuPcs->field_0xc;
    break;
  case 9:
    uVar2 = (uint)(char)menuPcs->field_0xd;
    break;
  case 10:
    uVar2 = -(uint)(byte)menuPcs->field_0x10 >> 0x1f;
    break;
  case 0xb:
    uVar2 = -(uint)(byte)menuPcs->field_0x11 >> 0x1f;
    break;
  case 0xc:
    uVar2 = (uint)(char)menuPcs->field_0xe;
    break;
  case 0xd:
    uVar2 = (uint)(char)menuPcs->field_0xf;
    break;
  case 0xe:
    uVar2 = -(uint)(byte)menuPcs->field_0x12 >> 0x1f;
    break;
  case 0xf:
    uVar2 = -(uint)(byte)menuPcs->field_0x13 >> 0x1f;
    break;
  case 0x10:
    uVar2 = (uint)(char)menuPcs->field_0x17;
    break;
  case 0x11:
    iVar3 = 0;
    do {
      iVar1 = McChkConnect__14CMemoryCardManFi(&MemoryCardMan,0);
      if (iVar1 != 1) break;
      iVar3 = iVar3 + 1;
    } while (iVar3 < 10);
    if (iVar1 == 0) {
      uVar2 = 1;
    }
    else if (iVar1 == 1) {
      uVar2 = 7;
    }
    else if (iVar1 != -1) {
      if (iVar1 == -2) {
        uVar2 = 2;
      }
      else if (iVar1 == -3) {
        uVar2 = 3;
      }
      else {
        uVar2 = 6;
      }
    }
    iVar3 = 0;
    do {
      iVar1 = McChkConnect__14CMemoryCardManFi(&MemoryCardMan,1);
      if (iVar1 != 1) break;
      iVar3 = iVar3 + 1;
    } while (iVar3 < 10);
    if (iVar1 == 0) {
      uVar2 = uVar2 | 0x10;
    }
    else if (iVar1 == 1) {
      uVar2 = uVar2 | 0x70;
    }
    else if (iVar1 != -1) {
      if (iVar1 == -2) {
        uVar2 = uVar2 | 0x20;
      }
      else if (iVar1 == -3) {
        uVar2 = uVar2 | 0x30;
      }
      else {
        uVar2 = uVar2 | 0x60;
      }
    }
    break;
  default:
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce
                (&System,s__s__d___Error_function_code_not_f_801dc3ec,s_wm_menu_cpp_801dc418,0x1521,
                 param_2);
    }
    break;
  case 0x15:
    uVar2 = 0x16;
  }
  return uVar2;
}


// Function: SetWorldParam__8CMenuPcsFii
// Entry: 800f6d70
// Size: 724 bytes

void SetWorldParam__8CMenuPcsFii(CMenuPcs *menuPcs,undefined4 param_2,uint param_3)

{
  byte bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  ushort uVar5;
  int iVar7;
  byte bVar6;
  
  uVar3 = DAT_8033175c;
  uVar2 = DAT_80331758;
  bVar6 = (byte)param_3;
  uVar5 = (ushort)param_3;
  bVar1 = (byte)(param_3 >> 0x18);
  switch(param_2) {
  case 0:
    menuPcs->field_0x5 = menuPcs->field_0x4;
    menuPcs->field_0x4 = bVar6;
    menuPcs->field_0xa = menuPcs->field_0xa | (byte)uVar2;
    break;
  case 1:
    menuPcs->field_0x6 = bVar6;
    break;
  case 2:
    *(ushort *)&menuPcs->field_0x1a = uVar5 & 0x3ff;
    break;
  case 3:
    menuPcs->field_0x7 = bVar6;
    break;
  case 4:
    menuPcs->field_0x8 = bVar6;
    break;
  case 5:
    *(ushort *)&menuPcs->field_0x1c = uVar5;
    break;
  case 6:
    *(ushort *)&menuPcs->field_0x1e = uVar5;
    break;
  case 7:
    menuPcs->field_0x9 = bVar6;
    break;
  case 8:
    menuPcs->field_0xb = menuPcs->field_0xc;
    menuPcs->field_0xc = bVar6;
    menuPcs->field_0xa = menuPcs->field_0xa | (byte)uVar3;
    break;
  case 9:
    if ((int)(char)menuPcs->field_0xd != param_3) {
      menuPcs->field_0xd = bVar6;
    }
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x20) = 2;
    break;
  case 10:
    menuPcs->field_0x10 = (byte)((byte)(-param_3 >> 0x18) | bVar1) >> 7;
    break;
  case 0xb:
    menuPcs->field_0x11 = (byte)((byte)(-param_3 >> 0x18) | bVar1) >> 7;
    break;
  case 0xc:
    menuPcs->field_0xe = bVar6;
    break;
  case 0xd:
    menuPcs->field_0xf = bVar6 & 3;
    break;
  case 0xe:
    menuPcs->field_0x12 = (byte)((byte)(-param_3 >> 0x18) | bVar1) >> 7;
    break;
  case 0xf:
    menuPcs->field_0x13 = (byte)((byte)(-param_3 >> 0x18) | bVar1) >> 7;
    break;
  case 0x10:
    menuPcs->field_0x17 = bVar6;
    break;
  default:
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce
                (&System,s__s__d___Error_function_code_not_f_801dc3ec,s_wm_menu_cpp_801dc418,0x1482,
                 param_2);
    }
    break;
  case 0x12:
    (menuPcs->m_mcCtrl).m_previousState = 0;
    (menuPcs->m_mcCtrl).m_state = 0;
    (menuPcs->m_mcCtrl).m_lastResult = 0;
    (menuPcs->m_mcCtrl).m_iteration = 0;
    (menuPcs->m_mcCtrl).m_userBuffer = (void *)0x0;
    (menuPcs->m_mcCtrl).m_createFlag = 0;
    (menuPcs->m_mcCtrl).m_cardChannel = (int)(char)menuPcs->field_0x17;
    menuPcs->field_0x18 = 0x12;
    break;
  case 0x13:
    (menuPcs->m_mcCtrl).m_previousState = 0;
    (menuPcs->m_mcCtrl).m_state = 0;
    (menuPcs->m_mcCtrl).m_lastResult = 0;
    (menuPcs->m_mcCtrl).m_iteration = 0;
    (menuPcs->m_mcCtrl).m_userBuffer = (void *)0x0;
    (menuPcs->m_mcCtrl).m_createFlag = 0;
    (menuPcs->m_mcCtrl).m_cardChannel = (int)(char)menuPcs->field_0x17;
    menuPcs->field_0x18 = 0x13;
    break;
  case 0x14:
    McEnd__14CMemoryCardManFv(&MemoryCardMan);
    menuPcs->field_0x14 = 1;
    break;
  case 0x16:
    menuPcs->field_0x15 = 1;
    changeMode__8CMenuPcsFQ28CMenuPcs8MENUMODE(menuPcs,2);
    menuPcs->field_0x15 = 1;
    break;
  case 0x17:
    uVar4 = countLeadingZeros(param_3);
    CameraPcs._1148_1_ = (byte)((int)(char)(uVar4 >> 5) << 7) | CameraPcs._1148_1_ & 0x7f;
    CameraPcs._1152_2_ = 0x4b;
    CameraPcs._1150_2_ = 0x4b;
    CameraPcs._1156_4_ = FLOAT_80331618;
    CameraPcs._1160_4_ = FLOAT_80331760;
    CameraPcs._1164_4_ = FLOAT_80331764;
    break;
  case 0x18:
    loadData__8CMenuPcsFv();
    break;
  case 0x19:
    menuPcs->field_0x16 = 1;
    break;
  case 0x1a:
    iVar7 = 0;
    do {
      SetRadarMode__8GbaQueueFii(&GbaQue,iVar7,0);
      iVar7 = iVar7 + 1;
    } while (iVar7 < 4);
    break;
  case 0x1b:
    SetControllerMode__8GbaQueueFi(&GbaQue,(-param_3 | param_3) >> 0x1f);
  }
  return;
}


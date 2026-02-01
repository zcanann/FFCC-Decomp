// Function: Init__8CMenuPcsFv
// Entry: 800974a8
// Size: 368 bytes

void Init__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  int iVar2;
  int32_t *piVar3;
  
  *(undefined4 *)&menuPcs->field_0xec = 0;
  *(undefined4 *)&menuPcs->field_0xf0 = 0;
  *(undefined4 *)&menuPcs->field_0xf4 = 0;
  memset(&menuPcs->field_0xf8,0,0x14);
  memset(&menuPcs->field_0x14c,0,0x40);
  memset(&menuPcs->field_0x18c,0,0x1a4);
  memset(&menuPcs->field_0x4,0,0x1c);
  menuPcs->field_0x859 = 0;
  *(undefined2 *)&menuPcs->field_0x86c = 0;
  *(undefined4 *)&menuPcs->field_0x830 = 0;
  *(undefined4 *)&menuPcs->field_0x850 = 0;
  *(undefined2 *)&menuPcs->field_0x864 = 0;
  WmInit__8CMenuPcsFv(menuPcs);
  BonusInit__8CMenuPcsFv(menuPcs);
  menuPcs->field_0x8e = 0;
  fVar1 = FLOAT_8033080c;
  menuPcs->field_0x8f = 0;
  iVar2 = 1;
  piVar3 = &(menuPcs->m_mcCtrl).m_cardChannel;
  menuPcs->field_0x90 = 0;
  menuPcs->field_0x91 = 6;
  menuPcs->field_0x92 = 6;
  menuPcs->field_0x93 = 0;
  menuPcs->field_0x94 = 0;
  menuPcs->field_0x9c = 0;
  *(float *)&menuPcs->field_0x98 = fVar1;
  menuPcs->field_0x9d = 0;
  menuPcs->field_0xa4 = 0;
  *(float *)&menuPcs->field_0xa0 = fVar1;
  *(float *)&menuPcs->field_0xa8 = fVar1;
  menuPcs->field_0xac = 0;
  menuPcs->field_0xb5 = 0;
  menuPcs->field_0xb6 = 0;
  menuPcs->field_0xb7 = 0;
  menuPcs->field_0xb8 = 0;
  *(undefined4 *)&menuPcs->field_0xbc = 0;
  *(undefined4 *)&menuPcs->field_0xc0 = 0;
  *(undefined4 *)&menuPcs->field_0xc4 = 0;
  *(undefined4 *)&menuPcs->field_0xc8 = 0;
  *(undefined4 *)&menuPcs->field_0xcc = 0;
  *(undefined4 *)&menuPcs->field_0xd0 = 0;
  *(undefined4 *)&menuPcs->field_0xd4 = 0;
  *(undefined4 *)&menuPcs->field_0xd8 = 0;
  *(undefined4 *)&menuPcs->field_0xdc = 0;
  *(undefined4 *)&menuPcs->field_0xe0 = 0;
  *(undefined4 *)&menuPcs->field_0xe4 = 0;
  do {
    piVar3[0x30] = 0;
    piVar3 = piVar3 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  menuPcs->m_shopMenuPtr = (CShopMenu *)0x0;
  menuPcs->field_0x87c = 1;
  menuPcs->field_0x888 = 0;
  menuPcs->field_0x889 = 0;
  menuPcs->field_0x88a = 0;
  *(undefined4 *)&menuPcs->field_0x884 = 0;
  *(undefined4 *)&menuPcs->field_0x880 = 0;
  *(undefined4 *)&menuPcs->field_0x88c = 0;
  return;
}


// Function: calc__6CMcPcsFv
// Entry: 80124998
// Size: 312 bytes

void calc__6CMcPcsFv(void)

{
  int iVar1;
  undefined4 uVar2;
  
  Rand__5CMathFUl(&Math,0x7fffffff);
  if (MenuPcs._20_1_ != '\x01') {
    if (MenuPcs._24_1_ == '\x13') {
      iVar1 = Format__6McCtrlFi(&MenuPcs.m_mcCtrl,1);
      if (iVar1 != 0) {
        if (iVar1 == 1) {
          uVar2 = 1;
        }
        else if (iVar1 == -1) {
          uVar2 = 4;
        }
        else {
          uVar2 = 6;
        }
        CallWorldParam__8CMenuPcsFiii(&MenuPcs,6,uVar2,0);
        MenuPcs._24_1_ = 0;
      }
    }
    else if ((MenuPcs._24_1_ == '\x12') &&
            (iVar1 = ChkEmpty__6McCtrlFi(&MenuPcs.m_mcCtrl,0), iVar1 != 0)) {
      if (iVar1 == 1) {
        uVar2 = 1;
      }
      else if (iVar1 == -1) {
        uVar2 = 4;
      }
      else if (iVar1 == -2) {
        uVar2 = 5;
      }
      else if ((iVar1 == -3) || (iVar1 == -4)) {
        uVar2 = 2;
      }
      else {
        uVar2 = 6;
      }
      CallWorldParam__8CMenuPcsFiii(&MenuPcs,5,uVar2,0);
      MenuPcs._24_1_ = 0;
    }
  }
  return;
}


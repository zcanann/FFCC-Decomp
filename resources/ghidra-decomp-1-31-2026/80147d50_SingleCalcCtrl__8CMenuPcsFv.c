// Function: SingleCalcCtrl__8CMenuPcsFv
// Entry: 80147d50
// Size: 1232 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SingleCalcCtrl__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float xS;
  short sVar1;
  bool bVar2;
  ushort uVar3;
  CModel *model;
  int iVar4;
  undefined2 uVar5;
  Mtx MStack_48;
  
  if (DAT_8032eebc != 0) {
    if ((menuPcs->field_0x872 != '\0') && (*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) != 0)) {
      menuPcs->field_0x872 = 0;
    }
    uVar5 = 0;
    model = *(CModel **)(*(int *)&menuPcs->field_0x774 + 0x168);
    if (model->m_animEnd <= model->m_time) {
      SetFrame__Q26CChara6CModelFf(FLOAT_8033294c,model);
    }
    else {
      AddFrame__Q26CChara6CModelFf((double)FLOAT_80332934,model);
    }
    iVar4 = (uint)*(ushort *)(Game.game.m_scriptFoodBase[0] + 0x3e0) * 4;
    xS = *(float *)(&DAT_801dd708 + iVar4);
    PSMTXScale(xS,xS,xS,&MStack_48);
    MStack_48.value[1][3] = *(float *)(&DAT_801dd6f8 + iVar4);
    MStack_48.value[0][3] = FLOAT_8033294c;
    MStack_48.value[2][3] = FLOAT_8033294c;
    iVar4 = *(int *)(*(int *)&menuPcs->field_0x774 + 0x168);
    *(byte *)(iVar4 + 0x10c) = *(byte *)(iVar4 + 0x10c) & 0x7f | 0x80;
    SetMatrix__Q26CChara6CModelFPA4_f
              (*(CModel **)(*(int *)&menuPcs->field_0x774 + 0x168),&MStack_48);
    CalcMatrix__Q26CChara6CModelFv(*(undefined4 *)(*(int *)&menuPcs->field_0x774 + 0x168));
    CalcSkin__Q26CChara6CModelFv(*(undefined4 *)(*(int *)&menuPcs->field_0x774 + 0x168));
    switch(*(undefined2 *)&menuPcs->field_0x864) {
    case 0:
      sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
      if (sVar1 == 0) {
        uVar5 = CmdOpen__8CMenuPcsFv(menuPcs);
      }
      else if (sVar1 == 1) {
        uVar5 = CmdCtrl__8CMenuPcsFv(menuPcs);
      }
      else {
        uVar5 = CmdClose__8CMenuPcsFv(menuPcs);
      }
      break;
    case 1:
      sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
      if (sVar1 == 0) {
        uVar5 = ItemOpen__8CMenuPcsFv(menuPcs);
      }
      else if (sVar1 == 1) {
        uVar5 = ItemCtrl__8CMenuPcsFv(menuPcs);
      }
      else {
        uVar5 = ItemClose__8CMenuPcsFv(menuPcs);
      }
      if ((-1 < *(int *)&menuPcs->field_0x874) &&
         (*(int *)&menuPcs->field_0x874 = *(int *)&menuPcs->field_0x874 + 1,
         0x31 < *(int *)&menuPcs->field_0x874)) {
        *(undefined4 *)&menuPcs->field_0x874 = 0xffffffff;
      }
      break;
    case 2:
      sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
      if (sVar1 == 0) {
        uVar5 = EquipOpen__8CMenuPcsFv(menuPcs);
      }
      else if (sVar1 == 1) {
        uVar5 = EquipCtrl__8CMenuPcsFv(menuPcs);
      }
      else {
        uVar5 = EquipClose__8CMenuPcsFv(menuPcs);
      }
      break;
    case 3:
      sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
      if (sVar1 == 0) {
        uVar5 = ArtiOpen__8CMenuPcsFv(menuPcs);
      }
      else if (sVar1 == 1) {
        uVar5 = ArtiCtrl__8CMenuPcsFv(menuPcs);
      }
      else {
        uVar5 = ArtiClose__8CMenuPcsFv(menuPcs);
      }
      break;
    case 4:
      sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
      if (sVar1 == 0) {
        uVar5 = TmpArtiOpen__8CMenuPcsFv(menuPcs);
      }
      else if (sVar1 == 1) {
        uVar5 = TmpArtiCtrl__8CMenuPcsFv(menuPcs);
      }
      else {
        uVar5 = TmpArtiClose__8CMenuPcsFv(menuPcs);
      }
      break;
    case 5:
      sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
      if (sVar1 == 0) {
        uVar5 = MoneyOpen__8CMenuPcsFv(menuPcs);
      }
      else if (sVar1 == 1) {
        uVar5 = MoneyCtrl__8CMenuPcsFv(menuPcs);
      }
      else {
        uVar5 = MoneyClose__8CMenuPcsFv(menuPcs);
      }
      break;
    case 6:
      sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
      if (sVar1 == 0) {
        uVar5 = FavoOpen__8CMenuPcsFv(menuPcs);
      }
      else if (sVar1 == 1) {
        uVar5 = FavoCtrl__8CMenuPcsFv(menuPcs);
      }
      else {
        uVar5 = FavoClose__8CMenuPcsFv(menuPcs);
      }
      break;
    case 7:
      sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
      if (sVar1 == 0) {
        uVar5 = CompaOpen__8CMenuPcsFv(menuPcs);
      }
      else if (sVar1 == 1) {
        uVar5 = CompaCtrl__8CMenuPcsFv(menuPcs);
      }
      else {
        uVar5 = CompaClose__8CMenuPcsFv(menuPcs);
      }
      break;
    case 8:
      sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
      if (sVar1 == 0) {
        uVar5 = LetterOpen__8CMenuPcsFv(menuPcs);
      }
      else if (sVar1 == 1) {
        uVar5 = LetterCtrl__8CMenuPcsFv(menuPcs);
      }
      else {
        uVar5 = LetterClose__8CMenuPcsFv(menuPcs);
      }
      break;
    case 9:
      sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
      if (sVar1 == 0) {
        uVar5 = MLstOpen__8CMenuPcsFv(menuPcs);
      }
      else if (sVar1 == 1) {
        uVar5 = MLstCtrl__8CMenuPcsFv(menuPcs);
      }
      else {
        uVar5 = MLstClose__8CMenuPcsFv(menuPcs);
      }
    }
    CalcHeart__8CMesMenuFv(MenuPcs._268_4_);
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2e) = uVar5;
    bVar2 = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
      bVar2 = true;
    }
    if (bVar2) {
      uVar3 = 0;
    }
    else {
      countLeadingZeros(Pad._448_4_);
      uVar3 = Pad._8_2_;
    }
    if ((uVar3 & 0x800) != 0) {
      *(undefined2 *)(*(int *)&menuPcs->field_0x850 + 6) = 1;
    }
  }
  return;
}


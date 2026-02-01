// Function: SetGoOutMode__10CGoOutMenuFUc
// Entry: 8016b8d4
// Size: 2256 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SetGoOutMode__10CGoOutMenuFUc(CGoOutMenu *goOutMenu,undefined param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  goOutMenu->field_0x18 = param_2;
  switch(goOutMenu->field_0x18) {
  case 1:
    goOutMenu->field_0x1c = 0;
    *(undefined2 *)(MenuPcs._2092_4_ + 0x1e) = 0xffff;
    *(undefined2 *)(MenuPcs._2092_4_ + 0x18) = 10;
    break;
  case 3:
    if (-1 < *(short *)&goOutMenu->field_0x36) {
      *(undefined2 *)(MenuPcs._2120_4_ + 10) = 2;
      *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
    }
    goOutMenu->field_0x45 = 0;
    *(undefined2 *)&goOutMenu->field_0x34 = 4;
    goOutMenu->field_0x48 = 0;
    *(undefined4 *)&goOutMenu->field_0x3c = 0;
    goOutMenu->field_0x46 = 1;
    break;
  case 4:
    if (-1 < *(short *)&goOutMenu->field_0x36) {
      *(undefined2 *)(MenuPcs._2120_4_ + 10) = 2;
      *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
    }
    goOutMenu->field_0x45 = 0;
    *(undefined2 *)&goOutMenu->field_0x34 = 5;
    goOutMenu->field_0x48 = 0;
    *(undefined4 *)&goOutMenu->field_0x3c = 0;
    goOutMenu->field_0x46 = 1;
    break;
  case 5:
    iVar1 = ChkConnect__6McCtrlFi(&MenuPcs.m_mcCtrl,(uint)(byte)goOutMenu->field_0x2);
    *(int *)&goOutMenu->field_0x4 = iVar1;
    if (*(int *)&goOutMenu->field_0x4 == 1) {
      MenuPcs.m_mcCtrl.m_saveIndex = (int32_t)(byte)goOutMenu->field_0x3;
      MenuPcs.m_mcCtrl.m_cardChannel = (int32_t)(byte)goOutMenu->field_0x2;
      MenuPcs.m_mcCtrl.m_previousState = 0;
      MenuPcs.m_mcCtrl.m_state = 0;
      MenuPcs.m_mcCtrl.m_lastResult = 0;
      MenuPcs.m_mcCtrl.m_iteration = 0;
      MenuPcs.m_mcCtrl.m_userBuffer = (void *)0x0;
      MenuPcs.m_mcCtrl.m_createFlag = 0;
      goOutMenu->field_0x1 = 3;
    }
    if (-1 < *(short *)&goOutMenu->field_0x36) {
      *(undefined2 *)(MenuPcs._2120_4_ + 10) = 2;
      *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
    }
    goOutMenu->field_0x45 = 0;
    *(undefined2 *)&goOutMenu->field_0x34 = 7;
    goOutMenu->field_0x48 = 0;
    *(undefined4 *)&goOutMenu->field_0x3c = 0;
    break;
  case 6:
    if (*(short *)(MenuPcs._2120_4_ + 10) == 1) {
      *(undefined2 *)(MenuPcs._2120_4_ + 10) = 3;
      *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
      *(undefined2 *)&goOutMenu->field_0x36 = 0xffff;
      *(undefined4 *)&goOutMenu->field_0x40 = 0;
      goOutMenu->field_0x44 = 1;
    }
    if (-1 < *(short *)&goOutMenu->field_0x36) {
      *(undefined2 *)(MenuPcs._2120_4_ + 10) = 2;
      *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
    }
    goOutMenu->field_0x45 = 0;
    *(undefined2 *)&goOutMenu->field_0x34 = 0xc;
    goOutMenu->field_0x48 = 0;
    *(undefined4 *)&goOutMenu->field_0x3c = 0;
    goOutMenu->field_0x46 = 1;
    break;
  case 7:
    MenuPcs._2184_1_ = 1;
    goOutMenu->field_0x14 = 0;
    goOutMenu->field_0x18 = 7;
    goOutMenu->field_0x1c = 0;
    goOutMenu->field_0x1d = 0;
    iVar1 = Game.game.m_gameWork.m_languageId - 1;
    _SetMenuStr__10CGoOutMenuFlie
              (goOutMenu,0,7,(&PTR_s_Please_insert_a_Memory_Card_with_80215018)[iVar1 * 0x6e],
               (&PTR_s_current_game_s_data_into_Slot_A__8021501c)[iVar1 * 0x6e],
               (&PTR_s_Insert_into_Slot_B_a_Memory_Card_80215020)[iVar1 * 0x6e],
               (&PTR_s_with_the_character_data_to_be_tr_80215024)[iVar1 * 0x6e],
               (&PTR_DAT_80215028)[iVar1 * 0x6e],
               (&PTR_s_Please_do_not_remove_either_Memo_8021502c)[iVar1 * 0x6e],
               (&PTR_s_until_the_transfer_is_complete__80215030)[iVar1 * 0x6e]);
    break;
  case 0xc:
    if (-1 < *(short *)&goOutMenu->field_0x36) {
      *(undefined2 *)(MenuPcs._2120_4_ + 10) = 2;
      *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
    }
    goOutMenu->field_0x45 = 0;
    *(undefined2 *)&goOutMenu->field_0x34 = 0x21;
    goOutMenu->field_0x48 = 0;
    *(undefined4 *)&goOutMenu->field_0x3c = 0;
    GetMcAccessPos__8CMenuPcsFPiPi(&MenuPcs,&goOutMenu->field_0xc,&goOutMenu->field_0x10);
    *(undefined4 *)&goOutMenu->field_0xc = 0;
    MenuPcs.m_mcCtrl.m_cardChannel = *(int32_t *)&goOutMenu->field_0xc;
    goOutMenu->field_0x2 = (char)MenuPcs.m_mcCtrl.m_cardChannel;
    goOutMenu->field_0x3 = (char)*(undefined4 *)&goOutMenu->field_0x10;
    iVar1 = ChkConnect__6McCtrlFi(&MenuPcs.m_mcCtrl,(uint)(byte)goOutMenu->field_0x2);
    *(int *)&goOutMenu->field_0x4 = iVar1;
    if (*(int *)&goOutMenu->field_0x4 == 1) {
      MenuPcs.m_mcCtrl.m_saveIndex = (int32_t)(byte)goOutMenu->field_0x3;
      MenuPcs.m_mcCtrl.m_cardChannel = (int32_t)(byte)goOutMenu->field_0x2;
      MenuPcs.m_mcCtrl.m_previousState = 0;
      MenuPcs.m_mcCtrl.m_state = 0;
      MenuPcs.m_mcCtrl.m_lastResult = 0;
      MenuPcs.m_mcCtrl.m_iteration = 0;
      MenuPcs.m_mcCtrl.m_userBuffer = (void *)0x0;
      MenuPcs.m_mcCtrl.m_createFlag = 0;
      goOutMenu->field_0x1 = 1;
    }
    break;
  case 0xe:
    InitSaveLoadMenu__8CMenuPcsFv(&MenuPcs);
    SetMenuCharaAnim__8CMenuPcsFii(&MenuPcs);
    CopyNowCaravanDat__8CMenuPcsFPQ22Mc7SaveDat(&MenuPcs,MenuPcs._2176_4_);
    MenuPcs._2185_1_ = 2;
    MenuPcs._2186_1_ = 1;
    MenuPcs._2188_4_ = MenuPcs._2180_4_;
    if (-1 < *(short *)&goOutMenu->field_0x36) {
      *(undefined2 *)(MenuPcs._2120_4_ + 10) = 2;
      *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
    }
    goOutMenu->field_0x45 = 0;
    *(undefined2 *)&goOutMenu->field_0x34 = 0xffff;
    goOutMenu->field_0x48 = 0;
    *(undefined4 *)&goOutMenu->field_0x3c = 0;
    break;
  case 0xf:
    ChgAllModel2__8CMenuPcsFv(&MenuPcs);
    if (goOutMenu->field_0x1d == '\0') {
      InitSaveLoadMenu__8CMenuPcsFv(&MenuPcs);
    }
    SetMenuCharaAnim__8CMenuPcsFii(&MenuPcs);
    goOutMenu->field_0x1d = 1;
    if (-1 < *(short *)&goOutMenu->field_0x36) {
      *(undefined2 *)(MenuPcs._2120_4_ + 10) = 2;
      *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
    }
    goOutMenu->field_0x45 = 0;
    *(undefined2 *)&goOutMenu->field_0x34 = 0xffff;
    goOutMenu->field_0x48 = 0;
    *(undefined4 *)&goOutMenu->field_0x3c = 0;
    MenuPcs._2185_1_ = 2;
    MenuPcs._2186_1_ = 1;
    MenuPcs._2188_4_ = MenuPcs._2180_4_;
    break;
  case 0x10:
    if (goOutMenu->field_0x1e == '\0') {
      iVar1 = Game.game.m_gameWork.m_languageId - 1;
      _SetMenuStr__10CGoOutMenuFlie
                (goOutMenu,0,5,(&PTR_s_Are_you_sure_you_wish_to_import_80215034)[iVar1 * 0x6e],
                 (&PTR_s_the_selected_character_into_the_80215038)[iVar1 * 0x6e],
                 (&PTR_s_current_game__The_character_will_8021503c)[iVar1 * 0x6e],
                 (&PTR_s_be_unavailable_until_returned__80215040)[iVar1 * 0x6e],
                 (&PTR_s__Yes_No_80215044)[iVar1 * 0x6e]);
    }
    else {
      iVar1 = Game.game.m_gameWork.m_languageId - 1;
      _SetMenuStr__10CGoOutMenuFlie
                (goOutMenu,0,5,(&PTR_s_Are_you_sure_you_wish_to_return_80215048)[iVar1 * 0x6e],
                 (&PTR_s_the_selected_character_to_the_8021504c)[iVar1 * 0x6e],
                 (&PTR_s_current_game__The_character_s_80215050)[iVar1 * 0x6e],
                 (&PTR_s_guest_data_will_be_deleted__80215054)[iVar1 * 0x6e],
                 (&PTR_s__Yes_No_80215058)[iVar1 * 0x6e]);
    }
    goOutMenu->field_0x46 = 1;
    break;
  case 0x11:
    if (-1 < *(short *)&goOutMenu->field_0x36) {
      *(undefined2 *)(MenuPcs._2120_4_ + 10) = 2;
      *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
    }
    goOutMenu->field_0x45 = 0;
    *(undefined2 *)&goOutMenu->field_0x34 = 0x1f;
    goOutMenu->field_0x48 = 0;
    *(undefined4 *)&goOutMenu->field_0x3c = 0;
    goOutMenu->field_0x46 = 1;
    break;
  case 0x12:
    goOutMenu->field_0x1c = 0;
    iVar1 = *(int *)&goOutMenu->field_0x20;
    if (*(char *)(MenuPcs._2180_4_ + iVar1 * 0x9c0 + 0x1d91) == '\0') {
      if (*(int *)(MenuPcs._2176_4_ + 0x1a84) == 0) {
        uVar2 = 0;
      }
      else if (*(int *)(MenuPcs._2176_4_ + 0x2444) == 0) {
        uVar2 = 1;
      }
      else if (*(int *)(MenuPcs._2176_4_ + 0x2e04) == 0) {
        uVar2 = 2;
      }
      else if (*(int *)(MenuPcs._2176_4_ + 0x37c4) == 0) {
        uVar2 = 3;
      }
      else if (*(int *)(MenuPcs._2176_4_ + 0x4184) == 0) {
        uVar2 = 4;
      }
      else if (*(int *)(MenuPcs._2176_4_ + 0x4b44) == 0) {
        uVar2 = 5;
      }
      else if (*(int *)(MenuPcs._2176_4_ + 0x5504) == 0) {
        uVar2 = 6;
      }
      else if (*(int *)(MenuPcs._2176_4_ + 0x5ec4) == 0) {
        uVar2 = 7;
      }
      else {
        uVar2 = 0xffffffff;
      }
      Odekake__14CMemoryCardManFiRQ22Mc7SaveDatiRQ22Mc7SaveDati
                (&MemoryCardMan,1,MenuPcs._2180_4_,iVar1,MenuPcs._2176_4_,uVar2);
    }
    else {
      uVar2 = GetSameCharaData__8CMenuPcsFPQ22Mc7SaveDatPQ22Mc7SaveDatii
                        (&MenuPcs,MenuPcs._2176_4_,MenuPcs._2180_4_,iVar1,0);
      Odekake__14CMemoryCardManFiRQ22Mc7SaveDatiRQ22Mc7SaveDati
                (&MemoryCardMan,0,MenuPcs._2180_4_,*(undefined4 *)&goOutMenu->field_0x20,
                 MenuPcs._2176_4_,uVar2);
    }
    MenuPcs.m_mcCtrl.m_cardChannel = *(int32_t *)&goOutMenu->field_0xc;
    goOutMenu->field_0x2 = (char)MenuPcs.m_mcCtrl.m_cardChannel;
    goOutMenu->field_0x3 = (char)*(undefined4 *)&goOutMenu->field_0x10;
    *(undefined4 *)&goOutMenu->field_0x8 = MenuPcs._2176_4_;
    iVar1 = ChkConnect__6McCtrlFi(&MenuPcs.m_mcCtrl,(uint)(byte)goOutMenu->field_0x2);
    *(int *)&goOutMenu->field_0x4 = iVar1;
    if (*(int *)&goOutMenu->field_0x4 == 1) {
      MenuPcs.m_mcCtrl.m_saveIndex = (int32_t)(byte)goOutMenu->field_0x3;
      MenuPcs.m_mcCtrl.m_cardChannel = (int32_t)(byte)goOutMenu->field_0x2;
      MenuPcs.m_mcCtrl.m_previousState = 0;
      MenuPcs.m_mcCtrl.m_state = 0;
      MenuPcs.m_mcCtrl.m_lastResult = 0;
      MenuPcs.m_mcCtrl.m_iteration = 0;
      MenuPcs.m_mcCtrl.m_userBuffer = (void *)0x0;
      MenuPcs.m_mcCtrl.m_createFlag = 0;
      goOutMenu->field_0x1 = 2;
    }
    iVar1 = Game.game.m_gameWork.m_languageId - 1;
    _SetMenuStr__10CGoOutMenuFlie
              (goOutMenu,0,4,(&PTR_s_Saving_data_to_the_Memory_8021505c)[iVar1 * 0x6e],
               (&PTR_s_Card_in_Slot_A__Please_do_80215060)[iVar1 * 0x6e],
               (&PTR_s_not_touch_the_Memory_Card_80215064)[iVar1 * 0x6e],
               (&PTR_s_or_the_POWER_Button__80215068)[iVar1 * 0x6e]);
    break;
  case 0x13:
    MenuPcs.m_mcCtrl.m_cardChannel = (int32_t)(byte)goOutMenu->field_0x1a;
    goOutMenu->field_0x2 = goOutMenu->field_0x1a;
    goOutMenu->field_0x3 = goOutMenu->field_0x1b;
    *(undefined4 *)&goOutMenu->field_0x8 = MenuPcs._2180_4_;
    iVar1 = ChkConnect__6McCtrlFi(&MenuPcs.m_mcCtrl,(uint)(byte)goOutMenu->field_0x2);
    *(int *)&goOutMenu->field_0x4 = iVar1;
    if (*(int *)&goOutMenu->field_0x4 == 1) {
      MenuPcs.m_mcCtrl.m_saveIndex = (int32_t)(byte)goOutMenu->field_0x3;
      MenuPcs.m_mcCtrl.m_cardChannel = (int32_t)(byte)goOutMenu->field_0x2;
      MenuPcs.m_mcCtrl.m_previousState = 0;
      MenuPcs.m_mcCtrl.m_state = 0;
      MenuPcs.m_mcCtrl.m_lastResult = 0;
      MenuPcs.m_mcCtrl.m_iteration = 0;
      MenuPcs.m_mcCtrl.m_userBuffer = (void *)0x0;
      MenuPcs.m_mcCtrl.m_createFlag = 0;
      goOutMenu->field_0x1 = 2;
    }
    iVar1 = Game.game.m_gameWork.m_languageId - 1;
    _SetMenuStr__10CGoOutMenuFlie
              (goOutMenu,0,4,(&PTR_s_Saving_data_to_the_Memory_8021506c)[iVar1 * 0x6e],
               (&PTR_s_Card_in_Slot_B__Please_do_80215070)[iVar1 * 0x6e],
               (&PTR_s_not_touch_the_Memory_Card_80215074)[iVar1 * 0x6e],
               (&PTR_s_or_the_POWER_Button__80215078)[iVar1 * 0x6e]);
    break;
  case 0x14:
    if (-1 < *(short *)&goOutMenu->field_0x36) {
      *(undefined2 *)(MenuPcs._2120_4_ + 10) = 2;
      *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
    }
    goOutMenu->field_0x45 = 0;
    *(undefined2 *)&goOutMenu->field_0x34 = 0x20;
    goOutMenu->field_0x48 = 0;
    *(undefined4 *)&goOutMenu->field_0x3c = 0;
  }
  return;
}


// Function: CalcGoOut__10CGoOutMenuFv
// Entry: 8016a06c
// Size: 6248 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CalcGoOut__10CGoOutMenuFv(CGoOutMenu *goOutMenu)

{
  bool bVar1;
  ushort uVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  char cVar7;
  undefined local_10 [3];
  undefined uStack_d;
  undefined local_c [3];
  undefined uStack_9;
  
  if (((goOutMenu->field_0x1c != '\0') && (uVar4 = *(uint *)&goOutMenu->field_0x30, 0x13 < uVar4))
     && ((uVar4 & 0xf) == 0)) {
    if ((uVar4 & 0x10) == 0) {
      iVar5 = ChkConnect__6McCtrlFi(&MenuPcs.m_mcCtrl,1);
    }
    else {
      iVar5 = ChkConnect__6McCtrlFi(&MenuPcs.m_mcCtrl,0);
    }
    if (iVar5 != 1) {
      goOutMenu->field_0x1c = 0;
      goOutMenu->field_0x19 = 0xff;
      goOutMenu->field_0x18 = 0;
      *(undefined2 *)(MenuPcs._2120_4_ + 10) = 3;
      *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
      *(undefined2 *)&goOutMenu->field_0x36 = 0xffff;
      *(undefined4 *)&goOutMenu->field_0x40 = 0;
      goOutMenu->field_0x44 = 1;
      iVar5 = Game.game.m_gameWork.m_languageId - 1;
      _SetMenuStr__10CGoOutMenuFlie
                (goOutMenu,0,5,(&PTR_s_A_Memory_Card_has_been_removed__8021507c)[iVar5 * 0x6e],
                 (&PTR_s_Cancelling_character_transfer__80215080)[iVar5 * 0x6e],
                 (&PTR_DAT_80215084)[iVar5 * 0x6e],
                 (&PTR_s_Please_do_not_remove_either_Memo_80215088)[iVar5 * 0x6e],
                 (&PTR_s_until_the_character_transfer_is_c_8021508c)[iVar5 * 0x6e]);
      return;
    }
  }
  uVar6 = 0xffffffff;
  if (goOutMenu->field_0x1d != '\0') {
    uVar4 = countLeadingZeros(0xf - (char)goOutMenu->field_0x18);
    uVar6 = CalcGoOutSelChar__8CMenuPcsFUcUc(&MenuPcs,uVar4 >> 5 & 0xff,1);
  }
  switch(goOutMenu->field_0x18) {
  case 0:
    if (goOutMenu->field_0x45 != '\0') {
      bVar1 = false;
      if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        bVar1 = true;
      }
      if (bVar1) {
        uVar2 = 0;
      }
      else {
        countLeadingZeros(Pad._448_4_);
        uVar2 = Pad._8_2_;
      }
      if ((uVar2 & 0x100) != 0) {
        PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
        if (goOutMenu->field_0x19 == -1) {
          SetMainMode__10CGoOutMenuFUc(goOutMenu,1);
        }
        else {
          SetGoOutMode__10CGoOutMenuFUc(goOutMenu,goOutMenu->field_0x19);
        }
      }
    }
    break;
  case 2:
    if (goOutMenu->field_0x45 != '\0') {
      bVar1 = false;
      if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        bVar1 = true;
      }
      if (bVar1) {
        uVar2 = 0;
      }
      else {
        countLeadingZeros(Pad._448_4_);
        uVar2 = Pad._8_2_;
      }
      if ((uVar2 & 0x100) != 0) {
        PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
        SetMainMode__10CGoOutMenuFUc(goOutMenu,1);
      }
    }
    break;
  case 3:
    if (goOutMenu->field_0x45 == '\0') break;
    goOutMenu->field_0x47 = 1;
    bVar3 = 0;
    goOutMenu->field74_0x4a = 0xcf;
    goOutMenu->field75_0x4c = 0xe7;
    goOutMenu->field_0x49 = 0;
    if (*(short *)(MenuPcs._2120_4_ + 10) == 1) {
      if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        bVar3 = 1;
      }
      if (bVar3 == 0) {
        countLeadingZeros(Pad._448_4_);
        uVar2 = Pad._8_2_;
      }
      else {
        uVar2 = 0;
      }
      if ((uVar2 & 3) == 0) {
        bVar1 = false;
        if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
          bVar1 = true;
        }
        if (bVar1) {
          uVar2 = 0;
        }
        else {
          countLeadingZeros(Pad._448_4_);
          uVar2 = Pad._8_2_;
        }
        if ((uVar2 & 0x100) != 0) {
          if (goOutMenu->field_0x46 == '\0') {
            PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
          }
          else if (goOutMenu->field_0x46 == '\x01') {
            PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
          }
          bVar3 = goOutMenu->field_0x46 + 1;
          goto LAB_8016b494;
        }
      }
      else {
        goOutMenu->field_0x46 = goOutMenu->field_0x46 ^ 1;
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
      bVar3 = 0;
    }
LAB_8016b494:
    if (bVar3 == 2) {
      SetMainMode__10CGoOutMenuFUc(goOutMenu,1);
    }
    else if ((bVar3 < 2) && (bVar3 != 0)) {
      SetGoOutMode__10CGoOutMenuFUc(goOutMenu,4);
    }
    break;
  case 4:
    if (goOutMenu->field_0x45 == '\0') break;
    goOutMenu->field_0x47 = 1;
    bVar3 = 0;
    goOutMenu->field74_0x4a = 0xce;
    goOutMenu->field75_0x4c = 0xde;
    goOutMenu->field_0x49 = 0;
    if (*(short *)(MenuPcs._2120_4_ + 10) == 1) {
      if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        bVar3 = 1;
      }
      if (bVar3 == 0) {
        countLeadingZeros(Pad._448_4_);
        uVar2 = Pad._8_2_;
      }
      else {
        uVar2 = 0;
      }
      if ((uVar2 & 3) == 0) {
        bVar1 = false;
        if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
          bVar1 = true;
        }
        if (bVar1) {
          uVar2 = 0;
        }
        else {
          countLeadingZeros(Pad._448_4_);
          uVar2 = Pad._8_2_;
        }
        if ((uVar2 & 0x100) != 0) {
          if (goOutMenu->field_0x46 == '\0') {
            PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
          }
          else if (goOutMenu->field_0x46 == '\x01') {
            PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
          }
          bVar3 = goOutMenu->field_0x46 + 1;
          goto LAB_8016b678;
        }
      }
      else {
        goOutMenu->field_0x46 = goOutMenu->field_0x46 ^ 1;
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
      bVar3 = 0;
    }
LAB_8016b678:
    if (bVar3 == 2) {
      SetMainMode__10CGoOutMenuFUc(goOutMenu,1);
    }
    else if ((bVar3 < 2) && (bVar3 != 0)) {
      SetGoOutMode__10CGoOutMenuFUc(goOutMenu,5);
    }
    break;
  case 5:
    if ((goOutMenu->field_0x45 != '\0') && (*(int *)&goOutMenu->field_0x4 != 0)) {
      cVar7 = SetMemCardError__10CGoOutMenuFv(goOutMenu);
      if (cVar7 != '\0') {
        return;
      }
      SetGoOutMode__10CGoOutMenuFUc(goOutMenu,6);
    }
    break;
  case 6:
    if (goOutMenu->field_0x45 != '\0') {
      bVar1 = false;
      if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        bVar1 = true;
      }
      if (bVar1) {
        uVar2 = 0;
      }
      else {
        countLeadingZeros(Pad._448_4_);
        uVar2 = Pad._8_2_;
      }
      if ((uVar2 & 0x100) != 0) {
        PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
        SetMainMode__10CGoOutMenuFUc(goOutMenu,1);
      }
    }
    break;
  case 7:
    if (goOutMenu->field_0x45 != '\0') {
      bVar1 = false;
      if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        bVar1 = true;
      }
      if (bVar1) {
        uVar2 = 0;
      }
      else {
        countLeadingZeros(Pad._448_4_);
        uVar2 = Pad._8_2_;
      }
      if ((uVar2 & 0x100) != 0) {
        PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
        SetGoOutMode__10CGoOutMenuFUc(goOutMenu,8);
      }
    }
    break;
  case 8:
    iVar5 = ChkConnect__6McCtrlFi(&MenuPcs.m_mcCtrl,0);
    if (iVar5 == -1) {
      return;
    }
    *(undefined4 *)&goOutMenu->field_0x30 = 0;
    SetGoOutMode__10CGoOutMenuFUc(goOutMenu,9);
    break;
  case 9:
    if (*(uint *)&goOutMenu->field_0x30 < 0x14) {
      return;
    }
    iVar5 = ChkConnect__6McCtrlFi(&MenuPcs.m_mcCtrl,0);
    if (iVar5 == -3) {
      _SetMenuStr__10CGoOutMenuFlie
                (goOutMenu,0,2,
                 (&PTR_s_No_Memory_Card_found_in_80215090)
                 [(Game.game.m_gameWork.m_languageId - 1) * 0x6e],
                 (&PTR_s_Slot_A__80215094)[(Game.game.m_gameWork.m_languageId - 1) * 0x6e]);
      goOutMenu->field_0x19 = 0xff;
      SetGoOutMode__10CGoOutMenuFUc(goOutMenu,0);
      return;
    }
    SetGoOutMode__10CGoOutMenuFUc(goOutMenu,0xc);
    break;
  case 10:
    iVar5 = ChkConnect__6McCtrlFi(&MenuPcs.m_mcCtrl,1);
    if (iVar5 == -1) {
      return;
    }
    *(undefined4 *)&goOutMenu->field_0x30 = 0;
    SetGoOutMode__10CGoOutMenuFUc(goOutMenu,0xb);
    break;
  case 0xb:
    if (*(uint *)&goOutMenu->field_0x30 < 0x14) {
      return;
    }
    iVar5 = ChkConnect__6McCtrlFi(&MenuPcs.m_mcCtrl,1);
    if (iVar5 == -3) {
      _SetMenuStr__10CGoOutMenuFlie
                (goOutMenu,0,2,
                 (&PTR_s_No_Memory_Card_found_in_80215098)
                 [(Game.game.m_gameWork.m_languageId - 1) * 0x6e],
                 (&PTR_s_Slot_B__8021509c)[(Game.game.m_gameWork.m_languageId - 1) * 0x6e]);
      goOutMenu->field_0x19 = 0xff;
      SetGoOutMode__10CGoOutMenuFUc(goOutMenu,0);
      return;
    }
    SetGoOutMode__10CGoOutMenuFUc(goOutMenu,0xe);
    break;
  case 0xc:
    if (*(int *)&goOutMenu->field_0x4 != 0) {
      cVar7 = SetMemCardError__10CGoOutMenuFv(goOutMenu);
      if (cVar7 != '\0') {
        return;
      }
      GetMcAccessPos__8CMenuPcsFPiPi(&MenuPcs,&goOutMenu->field_0xc,&goOutMenu->field_0x10);
      if (*(int *)&goOutMenu->field_0xc == -1) {
        iVar5 = Game.game.m_gameWork.m_languageId - 1;
        _SetMenuStr__10CGoOutMenuFlie
                  (goOutMenu,0,5,(&PTR_s_The_Memory_Card_in_Slot_A_contai_80214fe0)[iVar5 * 0x6e],
                   (&PTR_s_no_save_data_for_your_current_ga_80214fe4)[iVar5 * 0x6e],
                   (&PTR_s_or_contains_corrupt_data__Please_80214fe8)[iVar5 * 0x6e],
                   (&PTR_s_insert_a_Memory_Card_containing_80214fec)[iVar5 * 0x6e],
                   (&PTR_s_valid_save_data_into_Slot_A__80214ff0)[iVar5 * 0x6e]);
        goOutMenu->field_0x19 = 0xff;
        SetGoOutMode__10CGoOutMenuFUc(goOutMenu,0);
      }
      else {
        *(undefined4 *)&goOutMenu->field_0xc = 0;
        MenuPcs.m_mcCtrl.m_cardChannel = *(int32_t *)&goOutMenu->field_0xc;
        goOutMenu->field_0x2 = (char)MenuPcs.m_mcCtrl.m_cardChannel;
        goOutMenu->field_0x3 = (char)*(undefined4 *)&goOutMenu->field_0x10;
        SetGoOutMode__10CGoOutMenuFUc(goOutMenu,10);
      }
    }
    break;
  case 0xe:
    if (MenuPcs._2158_1_ != '\0') {
      if (MenuPcs._2160_2_ == 4) {
        *(undefined2 *)(MenuPcs._2092_4_ + 0x20) = 0;
        InitSaveLoadMenu__8CMenuPcsFv(&MenuPcs);
        SetMenuCharaAnim__8CMenuPcsFii(&MenuPcs);
        iVar5 = CheckSameMcFormatID__8CMenuPcsFPQ22Mc7SaveDatPQ22Mc7SaveDat
                          (&MenuPcs,MenuPcs._2176_4_,MenuPcs._2180_4_);
        if (iVar5 != 0) {
          _SetMenuStr__10CGoOutMenuFlie
                    (goOutMenu,0,2,
                     (&PTR_s_This_data_is_a_copy_of_the_curre_802150a0)
                     [(Game.game.m_gameWork.m_languageId - 1) * 0x6e],
                     (&PTR_s_game_s_data_and_cannot_be_used__802150a4)
                     [(Game.game.m_gameWork.m_languageId - 1) * 0x6e]);
          goOutMenu->field_0x19 = 0xff;
          SetGoOutMode__10CGoOutMenuFUc(goOutMenu,0);
          return;
        }
        GetMcOdekakePos__8CMenuPcsFPiPi(&MenuPcs,local_c,local_10);
        goOutMenu->field_0x1a = uStack_9;
        goOutMenu->field_0x1b = uStack_d;
        SetGoOutMode__10CGoOutMenuFUc(goOutMenu,0xf);
        goOutMenu->field_0x1c = 1;
      }
      else if (MenuPcs._2160_2_ == 1) {
        SetMainMode__10CGoOutMenuFUc(goOutMenu,1);
      }
      else {
        *(undefined2 *)(MenuPcs._2092_4_ + 0x20) = 0;
        InitSaveLoadMenu__8CMenuPcsFv(&MenuPcs);
        SetMenuCharaAnim__8CMenuPcsFii(&MenuPcs);
        iVar5 = Game.game.m_gameWork.m_languageId - 1;
        _SetMenuStr__10CGoOutMenuFlie
                  (goOutMenu,0,7,(&PTR_s_The_Memory_Card_in_Slot_B_contai_802150a8)[iVar5 * 0x6e],
                   (&PTR_s_no_save_data_for_FINAL_FANTASY_802150ac)[iVar5 * 0x6e],
                   (&PTR_s_Crystal_Chronicles__or_contains_802150b0)[iVar5 * 0x6e],
                   (&PTR_s_corrupt_data__802150b4)[iVar5 * 0x6e],(&PTR_DAT_802150b8)[iVar5 * 0x6e],
                   (&PTR_s_Please_insert_a_Memory_Card_cont_802150bc)[iVar5 * 0x6e],
                   (&PTR_s_valid_save_data_into_Slot_B__802150c0)[iVar5 * 0x6e]);
        goOutMenu->field_0x19 = 0xff;
        SetGoOutMode__10CGoOutMenuFUc(goOutMenu,0);
      }
    }
    if (*(short *)&goOutMenu->field_0x36 == -1) {
      CalcLoadMenu__8CMenuPcsFv(&MenuPcs);
    }
    break;
  case 0xf:
    *(undefined4 *)&goOutMenu->field_0x20 = uVar6;
    iVar5 = *(int *)&goOutMenu->field_0x20;
    if (iVar5 == -2) {
      SetGoOutMode__10CGoOutMenuFUc(goOutMenu,1);
      return;
    }
    if (iVar5 != -1) {
      if (*(char *)(MenuPcs._2180_4_ + iVar5 * 0x9c0 + 0x1d90) == '\0') {
        goOutMenu->field_0x1e = 0;
        iVar5 = *(int *)&goOutMenu->field_0x20;
        if (*(char *)(MenuPcs._2180_4_ + iVar5 * 0x9c0 + 0x1d91) == '\0') {
          iVar5 = GetSameCharaData__8CMenuPcsFPQ22Mc7SaveDatPQ22Mc7SaveDatii
                            (&MenuPcs,MenuPcs._2176_4_,MenuPcs._2180_4_,iVar5,1);
          if (iVar5 == -3) {
            goOutMenu->field_0x19 = 0xf;
            goOutMenu->field_0x18 = 0;
            iVar5 = Game.game.m_gameWork.m_languageId - 1;
            _SetMenuStr__10CGoOutMenuFlie
                      (goOutMenu,0,3,
                       (&PTR_s_The_current_game_data_already_co_802150cc)[iVar5 * 0x6e],
                       (&PTR_s_the_same_character__so_this_char_802150d0)[iVar5 * 0x6e],
                       (&PTR_s_cannot_be_transferred__802150d4)[iVar5 * 0x6e]);
            break;
          }
          if (*(int *)(MenuPcs._2176_4_ + 0x1a84) == 0) {
            DAT_8032ef0c = 0;
          }
          else if (*(int *)(MenuPcs._2176_4_ + 0x2444) == 0) {
            DAT_8032ef0c = 1;
          }
          else if (*(int *)(MenuPcs._2176_4_ + 0x2e04) == 0) {
            DAT_8032ef0c = 2;
          }
          else if (*(int *)(MenuPcs._2176_4_ + 0x37c4) == 0) {
            DAT_8032ef0c = 3;
          }
          else if (*(int *)(MenuPcs._2176_4_ + 0x4184) == 0) {
            DAT_8032ef0c = 4;
          }
          else if (*(int *)(MenuPcs._2176_4_ + 0x4b44) == 0) {
            DAT_8032ef0c = 5;
          }
          else if (*(int *)(MenuPcs._2176_4_ + 0x5504) == 0) {
            DAT_8032ef0c = 6;
          }
          else if (*(int *)(MenuPcs._2176_4_ + 0x5ec4) == 0) {
            DAT_8032ef0c = 7;
          }
          else {
            DAT_8032ef0c = -1;
          }
          if (DAT_8032ef0c < 0) {
            goOutMenu->field_0x19 = 0xf;
            goOutMenu->field_0x18 = 0;
            iVar5 = Game.game.m_gameWork.m_languageId - 1;
            _SetMenuStr__10CGoOutMenuFlie
                      (goOutMenu,0,6,(&PTR_s_The_current_game_data_already_802150d8)[iVar5 * 0x6e],
                       (&PTR_s_contains_8_characters__so_no_mor_802150dc)[iVar5 * 0x6e],
                       (&PTR_s_characters_can_be_transferred__802150e0)[iVar5 * 0x6e],
                       (&PTR_DAT_802150e4)[iVar5 * 0x6e],
                       (&PTR_s_You_must_delete_at_least_one_cha_802150e8)[iVar5 * 0x6e],
                       (&PTR_s_before_you_can_transfer_any_more_802150ec)[iVar5 * 0x6e]);
            break;
          }
        }
        else {
          DAT_8032ef0c = GetSameCharaData__8CMenuPcsFPQ22Mc7SaveDatPQ22Mc7SaveDatii
                                   (&MenuPcs,MenuPcs._2176_4_,MenuPcs._2180_4_,iVar5,0);
          if (DAT_8032ef0c < 0) {
            goOutMenu->field_0x19 = 0xf;
            goOutMenu->field_0x18 = 0;
            goOutMenu->field_0x19 = 0xf;
            goOutMenu->field_0x18 = 0;
            _SetMenuStr__10CGoOutMenuFlie
                      (goOutMenu,0,2,
                       (&PTR_s_Guest_characters_can_only_be_802150f0)
                       [(Game.game.m_gameWork.m_languageId - 1) * 0x6e],
                       (&PTR_s_returned_to_their_original_save_d_802150f4)
                       [(Game.game.m_gameWork.m_languageId - 1) * 0x6e]);
            break;
          }
          goOutMenu->field_0x1e = 1;
        }
        SetGoOutMode__10CGoOutMenuFUc(goOutMenu,0x10);
      }
      else {
        _SetMenuStr__10CGoOutMenuFlie
                  (goOutMenu,0,2,
                   (&PTR_s_You_cannot_import_characters_802150c4)
                   [(Game.game.m_gameWork.m_languageId - 1) * 0x6e],
                   (&PTR_s_that_are_currently_abroad__802150c8)
                   [(Game.game.m_gameWork.m_languageId - 1) * 0x6e]);
        goOutMenu->field_0x19 = 0xf;
        SetGoOutMode__10CGoOutMenuFUc(goOutMenu,0);
      }
    }
    break;
  case 0x10:
    if (goOutMenu->field_0x45 == '\0') break;
    bVar1 = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
      bVar1 = true;
    }
    if (bVar1) {
      uVar2 = 0;
    }
    else {
      countLeadingZeros(Pad._448_4_);
      uVar2 = Pad._8_2_;
    }
    if ((uVar2 & 0x200) != 0) {
      PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
      SetGoOutMode__10CGoOutMenuFUc(goOutMenu,0xf);
      break;
    }
    if (goOutMenu->field_0x1e == '\0') {
      goOutMenu->field_0x47 = 1;
      bVar3 = 0;
      goOutMenu->field74_0x4a = 0xb1;
      goOutMenu->field75_0x4c = 0xdc;
      goOutMenu->field_0x49 = 0;
      if (*(short *)(MenuPcs._2120_4_ + 10) == 1) {
        if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
          bVar3 = 1;
        }
        if (bVar3 == 0) {
          countLeadingZeros(Pad._448_4_);
          uVar2 = Pad._8_2_;
        }
        else {
          uVar2 = 0;
        }
        if ((uVar2 & 3) == 0) {
          bVar1 = false;
          if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
            bVar1 = true;
          }
          if (bVar1) {
            uVar2 = 0;
          }
          else {
            countLeadingZeros(Pad._448_4_);
            uVar2 = Pad._8_2_;
          }
          if ((uVar2 & 0x100) != 0) {
            if (goOutMenu->field_0x46 == '\0') {
              PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
            }
            else if (goOutMenu->field_0x46 == '\x01') {
              PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
            }
            bVar3 = goOutMenu->field_0x46 + 1;
            goto LAB_8016aedc;
          }
        }
        else {
          goOutMenu->field_0x46 = goOutMenu->field_0x46 ^ 1;
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
        bVar3 = 0;
      }
    }
    else {
      goOutMenu->field_0x47 = 1;
      bVar3 = 0;
      goOutMenu->field74_0x4a = 0x8b;
      goOutMenu->field75_0x4c = 0xdc;
      goOutMenu->field_0x49 = 0;
      if (*(short *)(MenuPcs._2120_4_ + 10) == 1) {
        if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
          bVar3 = 1;
        }
        if (bVar3 == 0) {
          countLeadingZeros(Pad._448_4_);
          uVar2 = Pad._8_2_;
        }
        else {
          uVar2 = 0;
        }
        if ((uVar2 & 3) == 0) {
          bVar1 = false;
          if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
            bVar1 = true;
          }
          if (bVar1) {
            uVar2 = 0;
          }
          else {
            countLeadingZeros(Pad._448_4_);
            uVar2 = Pad._8_2_;
          }
          if ((uVar2 & 0x100) != 0) {
            if (goOutMenu->field_0x46 == '\0') {
              PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
            }
            else if (goOutMenu->field_0x46 == '\x01') {
              PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
            }
            bVar3 = goOutMenu->field_0x46 + 1;
            goto LAB_8016aedc;
          }
        }
        else {
          goOutMenu->field_0x46 = goOutMenu->field_0x46 ^ 1;
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
        bVar3 = 0;
      }
    }
LAB_8016aedc:
    if (bVar3 == 2) {
      SetGoOutMode__10CGoOutMenuFUc(goOutMenu,0xf);
    }
    else if ((bVar3 < 2) && (bVar3 != 0)) {
      SetGoOutMode__10CGoOutMenuFUc(goOutMenu,0x11);
    }
    break;
  case 0x11:
    if (goOutMenu->field_0x45 == '\0') break;
    bVar1 = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
      bVar1 = true;
    }
    if (bVar1) {
      uVar2 = 0;
    }
    else {
      countLeadingZeros(Pad._448_4_);
      uVar2 = Pad._8_2_;
    }
    if ((uVar2 & 0x200) != 0) {
      PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
      SetGoOutMode__10CGoOutMenuFUc(goOutMenu,0xf);
      break;
    }
    goOutMenu->field_0x47 = 1;
    bVar3 = 0;
    goOutMenu->field74_0x4a = 0xd3;
    goOutMenu->field75_0x4c = 0xe9;
    goOutMenu->field_0x49 = 0;
    if (*(short *)(MenuPcs._2120_4_ + 10) == 1) {
      if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        bVar3 = 1;
      }
      if (bVar3 == 0) {
        countLeadingZeros(Pad._448_4_);
        uVar2 = Pad._8_2_;
      }
      else {
        uVar2 = 0;
      }
      if ((uVar2 & 3) == 0) {
        bVar1 = false;
        if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
          bVar1 = true;
        }
        if (bVar1) {
          uVar2 = 0;
        }
        else {
          countLeadingZeros(Pad._448_4_);
          uVar2 = Pad._8_2_;
        }
        if ((uVar2 & 0x100) != 0) {
          if (goOutMenu->field_0x46 == '\0') {
            PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
          }
          else if (goOutMenu->field_0x46 == '\x01') {
            PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
          }
          bVar3 = goOutMenu->field_0x46 + 1;
          goto LAB_8016b16c;
        }
      }
      else {
        goOutMenu->field_0x46 = goOutMenu->field_0x46 ^ 1;
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
      bVar3 = 0;
    }
LAB_8016b16c:
    if (bVar3 == 2) {
      SetGoOutMode__10CGoOutMenuFUc(goOutMenu,0xf);
    }
    else if ((bVar3 < 2) && (bVar3 != 0)) {
      SetGoOutMode__10CGoOutMenuFUc(goOutMenu,0x12);
    }
    break;
  case 0x12:
    if ((goOutMenu->field_0x45 != '\0') && (*(int *)&goOutMenu->field_0x4 != 0)) {
      cVar7 = SetMemCardError__10CGoOutMenuFv(goOutMenu);
      if (cVar7 != '\0') {
        return;
      }
      SetGoOutMode__10CGoOutMenuFUc(goOutMenu,0x13);
    }
    break;
  case 0x13:
    if ((goOutMenu->field_0x45 != '\0') && (*(int *)&goOutMenu->field_0x4 != 0)) {
      cVar7 = SetMemCardError__10CGoOutMenuFv(goOutMenu);
      if (cVar7 != '\0') {
        return;
      }
      SetGoOutMode__10CGoOutMenuFUc(goOutMenu,0x14);
    }
    break;
  case 0x14:
    if (goOutMenu->field_0x45 != '\0') {
      bVar1 = false;
      if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        bVar1 = true;
      }
      if (bVar1) {
        uVar2 = 0;
      }
      else {
        countLeadingZeros(Pad._448_4_);
        uVar2 = Pad._8_2_;
      }
      if ((uVar2 & 0x100) != 0) {
        PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
        SetCaravanWork__8CMenuPcsFPQ22Mc7SaveDat(&MenuPcs,MenuPcs._2176_4_);
        ChgAllModel__8CMenuPcsFv(&MenuPcs);
        SetGoOutMode__10CGoOutMenuFUc(goOutMenu,1);
      }
    }
  }
  bVar3 = goOutMenu->field_0x1;
  if (bVar3 == 2) {
    uVar6 = SaveDataBuffer__6McCtrlFPc(&MenuPcs.m_mcCtrl,*(undefined4 *)&goOutMenu->field_0x8);
    *(undefined4 *)&goOutMenu->field_0x4 = uVar6;
    if (*(int *)&goOutMenu->field_0x4 != 0) {
      *(undefined *)goOutMenu = goOutMenu->field_0x1;
      goOutMenu->field_0x1 = 0;
    }
  }
  else if (bVar3 < 2) {
    if (bVar3 != 0) {
      uVar6 = ChkNowData__6McCtrlFv(&MenuPcs.m_mcCtrl);
      *(undefined4 *)&goOutMenu->field_0x4 = uVar6;
      if (*(int *)&goOutMenu->field_0x4 != 0) {
        *(undefined *)goOutMenu = goOutMenu->field_0x1;
        goOutMenu->field_0x1 = 0;
      }
    }
  }
  else if (bVar3 < 4) {
    iVar5 = Format__6McCtrlFi(&MenuPcs.m_mcCtrl,1);
    if (iVar5 < 0) {
      MemoryCardMan.m_opDoneFlag = '\x01';
      MemoryCardMan.m_currentSlot = 0xff;
    }
    if (iVar5 == 0) {
      uVar6 = 0;
    }
    else if (iVar5 == 1) {
      uVar6 = 1;
    }
    else if (iVar5 == -2) {
      uVar6 = 0xfffffffb;
    }
    else {
      uVar6 = 0xfffffc19;
    }
    *(undefined4 *)&goOutMenu->field_0x4 = uVar6;
    if (*(int *)&goOutMenu->field_0x4 != 0) {
      *(undefined *)goOutMenu = goOutMenu->field_0x1;
      goOutMenu->field_0x1 = 0;
    }
  }
  return;
}


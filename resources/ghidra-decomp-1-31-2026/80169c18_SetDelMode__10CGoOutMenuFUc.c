// Function: SetDelMode__10CGoOutMenuFUc
// Entry: 80169c18
// Size: 1108 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SetDelMode__10CGoOutMenuFUc(CGoOutMenu *goOutMenu,undefined param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  goOutMenu->field_0x24 = param_2;
  switch(goOutMenu->field_0x24) {
  case 1:
    *(undefined2 *)(MenuPcs._2092_4_ + 0x1e) = 0xffff;
    *(undefined2 *)(MenuPcs._2092_4_ + 0x18) = 10;
    break;
  case 2:
    if (-1 < *(short *)&goOutMenu->field_0x36) {
      *(undefined2 *)(MenuPcs._2120_4_ + 10) = 2;
      *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
    }
    goOutMenu->field_0x45 = 0;
    *(undefined2 *)&goOutMenu->field_0x34 = 0xffff;
    goOutMenu->field_0x48 = 0;
    *(undefined4 *)&goOutMenu->field_0x3c = 0;
    if (goOutMenu->field_0x26 == '\0') {
      InitSaveLoadMenu__8CMenuPcsFv(&MenuPcs);
    }
    SetMenuCharaAnim__8CMenuPcsFii(&MenuPcs);
    goOutMenu->field_0x26 = 1;
    break;
  case 3:
    iVar2 = -0x7fde1140;
    if (Game.game.m_caravanWorkArr[*(int *)&goOutMenu->field_0x28].m_caravanLocalFlags == '\0') {
      iVar1 = 0;
      iVar3 = 2;
      do {
        if ((*(int *)(iVar2 + 0x1794) != 0) && (*(char *)(iVar2 + 0x1f96) == '\0')) {
          iVar1 = iVar1 + 1;
        }
        if ((*(int *)(iVar2 + 0x23c4) != 0) && (*(char *)(iVar2 + 0x2bc6) == '\0')) {
          iVar1 = iVar1 + 1;
        }
        if ((*(int *)(iVar2 + 0x2ff4) != 0) && (*(char *)(iVar2 + 0x37f6) == '\0')) {
          iVar1 = iVar1 + 1;
        }
        if ((*(int *)(iVar2 + 0x3c24) != 0) && (*(char *)(iVar2 + 0x4426) == '\0')) {
          iVar1 = iVar1 + 1;
        }
        iVar2 = iVar2 + 0x30c0;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      if (iVar1 < 2) {
        iVar2 = Game.game.m_gameWork.m_languageId - 1;
        _SetMenuStr__10CGoOutMenuFlie
                  (goOutMenu,0,4,(&PTR_s_This_character_cannot_be_deleted_802150f8)[iVar2 * 0x6e],
                   (&PTR_DAT_802150fc)[iVar2 * 0x6e],
                   (&PTR_s_At_least_one_non_guest_character_80215100)[iVar2 * 0x6e],
                   (&PTR_s_must_remain__80215104)[iVar2 * 0x6e]);
        goOutMenu->field_0x25 = 2;
        SetDelMode__10CGoOutMenuFUc(goOutMenu,0);
        return;
      }
    }
    _SetMenuStr__10CGoOutMenuFlie
              (goOutMenu,0,2,
               (&PTR_s_Delete_this_character__80215108)
               [(Game.game.m_gameWork.m_languageId - 1) * 0x6e],
               (&PTR_s__Yes_No_8021510c)[(Game.game.m_gameWork.m_languageId - 1) * 0x6e]);
    goOutMenu->field_0x46 = 1;
    break;
  case 4:
    iVar2 = Game.game.m_gameWork.m_languageId - 1;
    _SetMenuStr__10CGoOutMenuFlie
              (goOutMenu,0,4,(&PTR_s_Deleted_characters_80215110)[iVar2 * 0x6e],
               (&PTR_s_cannot_be_restored__80215114)[iVar2 * 0x6e],
               (&PTR_s_Are_you_sure__80215118)[iVar2 * 0x6e],(&PTR_s__Yes_No_8021511c)[iVar2 * 0x6e]
              );
    goOutMenu->field_0x46 = 1;
    break;
  case 5:
    if (Game.game.m_caravanWorkArr[*(int *)&goOutMenu->field_0x28].m_caravanLocalFlags == '\0') {
      _SetMenuStr__10CGoOutMenuFlie
                (goOutMenu,0,1,
                 (&PTR_s_The_character_has_been_deleted__80215140)
                 [(Game.game.m_gameWork.m_languageId - 1) * 0x6e]);
    }
    else {
      iVar2 = Game.game.m_gameWork.m_languageId - 1;
      _SetMenuStr__10CGoOutMenuFlie
                (goOutMenu,0,8,(&PTR_s_The_guest_character_has_been_del_80215120)[iVar2 * 0x6e],
                 (&PTR_DAT_80215124)[iVar2 * 0x6e],
                 (&PTR_s_Please_restore_the_character_s_80215128)[iVar2 * 0x6e],
                 (&PTR_s_original_save_data__8021512c)[iVar2 * 0x6e],
                 (&PTR_DAT_80215130)[iVar2 * 0x6e],
                 (&PTR_s_To_restore_a_character_who_is_ab_80215134)[iVar2 * 0x6e],
                 (&PTR_s_first_select__Delete_Character___80215138)[iVar2 * 0x6e],
                 (&PTR_s_select_the_character_you_wish_to_8021513c)[iVar2 * 0x6e]);
    }
    goOutMenu->field_0x46 = 1;
    SetMenuCharaAnim__8CMenuPcsFii(&MenuPcs,*(undefined4 *)&goOutMenu->field_0x28,5);
    break;
  case 6:
    iVar2 = Game.game.m_gameWork.m_languageId - 1;
    _SetMenuStr__10CGoOutMenuFlie
              (goOutMenu,0,6,(&PTR_s_This_character_is_currently_abro_80215144)[iVar2 * 0x6e],
               (&PTR_s_and_cannot_be_deleted_here__If_y_80215148)[iVar2 * 0x6e],
               (&PTR_s_wish_to_delete_the_character_s_8021514c)[iVar2 * 0x6e],
               (&PTR_s_original_data__you_must_first_80215150)[iVar2 * 0x6e],
               (&PTR_s_restore_it__Proceed__80215154)[iVar2 * 0x6e],
               (&PTR_s__Yes_No_80215158)[iVar2 * 0x6e]);
    goOutMenu->field_0x46 = 1;
    break;
  case 7:
    iVar2 = Game.game.m_gameWork.m_languageId - 1;
    _SetMenuStr__10CGoOutMenuFlie
              (goOutMenu,0,5,(&PTR_s_This_will_restore_the_character__8021515c)[iVar2 * 0x6e],
               (&PTR_s_to_the_state_it_was_in_before_tr_80215160)[iVar2 * 0x6e],
               (&PTR_s_It_will_also_prevent_the_transfe_80215164)[iVar2 * 0x6e],
               (&PTR_s_from_returning_to_this_save_loca_80215168)[iVar2 * 0x6e],
               (&PTR_s__Yes_No_8021516c)[iVar2 * 0x6e]);
    goOutMenu->field_0x46 = 1;
    break;
  case 8:
    SetMenuCharaAnim__8CMenuPcsFii(&MenuPcs,*(undefined4 *)&goOutMenu->field_0x28,3);
    _SetMenuStr__10CGoOutMenuFlie
              (goOutMenu,0,1,
               (&PTR_s_The_character_has_been_restored__80215170)
               [(Game.game.m_gameWork.m_languageId - 1) * 0x6e]);
  }
  return;
}


// Function: SetMainMode__10CGoOutMenuFUc
// Entry: 8016c1a4
// Size: 616 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SetMainMode__10CGoOutMenuFUc(CGoOutMenu *goOutMenu,byte param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  MenuPcs._2185_1_ = 0;
  MenuPcs._2186_1_ = 0;
  MenuPcs._2188_4_ = 0;
  if (goOutMenu->field_0x2c == '\x02') {
    McEnd__14CMemoryCardManFv(&MemoryCardMan);
  }
  cVar1 = goOutMenu->field_0x2c;
  goOutMenu->field_0x2c = param_2;
  *(undefined4 *)&goOutMenu->field_0x30 = 0;
  if (param_2 == 2) {
    if (Game.game.m_gameWork.m_mcHasSerial._0_1_ != '\x01') {
      iVar2 = Game.game.m_gameWork.m_languageId - 1;
      _SetMenuStr__10CGoOutMenuFlie
                (goOutMenu,0,4,(&PTR_s_This_game_has_not_been_saved__80214ff4)[iVar2 * 0x6e],
                 (&PTR_DAT_80214ff8)[iVar2 * 0x6e],
                 (&PTR_s_You_must_save_your_game_before_80214ffc)[iVar2 * 0x6e],
                 (&PTR_s_you_can_import_a_character__80215000)[iVar2 * 0x6e]);
      goOutMenu->field_0x19 = 0xff;
      goOutMenu->field_0x18 = 0;
    }
    iVar2 = 0;
    iVar4 = -0x7fde1140;
    do {
      if ((*(int *)(iVar4 + 0x1794) != 0) && (*(char *)(iVar4 + 0x200e) != '\x01')) {
        iVar3 = Game.game.m_gameWork.m_languageId - 1;
        _SetMenuStr__10CGoOutMenuFlie
                  (goOutMenu,0,5,(&PTR_s_This_game_contains_character_dat_80215004)[iVar3 * 0x6e],
                   (&PTR_s_that_has_not_yet_been_saved__80215008)[iVar3 * 0x6e],
                   (&PTR_DAT_8021500c)[iVar3 * 0x6e],
                   (&PTR_s_You_must_save_your_game_before_80215010)[iVar3 * 0x6e],
                   (&PTR_s_you_can_import_a_character__80215014)[iVar3 * 0x6e]);
        goOutMenu->field_0x19 = 0xff;
        goOutMenu->field_0x18 = 0;
      }
      iVar2 = iVar2 + 1;
      iVar4 = iVar4 + 0xc30;
    } while (iVar2 < 8);
    goOutMenu->field_0x1 = 0;
    *(undefined *)goOutMenu = 0;
    goOutMenu->field_0x2 = 0;
    goOutMenu->field_0x3 = 0;
    *(undefined4 *)&goOutMenu->field_0x4 = 0xffffffff;
    *(undefined4 *)&goOutMenu->field_0x8 = 0;
    SetGoOutMode__10CGoOutMenuFUc(goOutMenu,7);
  }
  else if (param_2 < 2) {
    if (param_2 != 0) {
      goOutMenu->field_0x46 = 1;
      if (cVar1 != '\x03') {
        goOutMenu->field_0x46 = 0;
      }
      ChgAllModel__8CMenuPcsFv(&MenuPcs);
      if (-1 < *(short *)&goOutMenu->field_0x36) {
        *(undefined2 *)(MenuPcs._2120_4_ + 10) = 2;
        *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
      }
      goOutMenu->field_0x45 = 0;
      *(undefined2 *)&goOutMenu->field_0x34 = 0x1e;
      goOutMenu->field_0x48 = 0;
      *(undefined4 *)&goOutMenu->field_0x3c = 0;
      goOutMenu->field_0x14 = 0;
    }
  }
  else if (param_2 < 4) {
    ChgAllModel__8CMenuPcsFv(&MenuPcs);
    MenuPcs._2184_1_ = 2;
    goOutMenu->field_0x14 = 0;
    goOutMenu->field_0x26 = 0;
    SetDelMode__10CGoOutMenuFUc(goOutMenu,2);
  }
  return;
}


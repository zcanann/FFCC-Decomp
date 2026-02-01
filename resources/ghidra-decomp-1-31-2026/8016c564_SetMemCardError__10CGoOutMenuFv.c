// Function: SetMemCardError__10CGoOutMenuFv
// Entry: 8016c564
// Size: 1156 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 SetMemCardError__10CGoOutMenuFv(CGoOutMenu *goOutMenu)

{
  char cVar1;
  int iVar2;
  
  iVar2 = *(int *)&goOutMenu->field_0x4;
  if (iVar2 == -5) {
    *(undefined2 *)(MenuPcs._2120_4_ + 10) = 3;
    *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
    *(undefined2 *)&goOutMenu->field_0x36 = 0xffff;
    *(undefined4 *)&goOutMenu->field_0x40 = 0;
    goOutMenu->field_0x44 = 1;
    if (-1 < *(short *)&goOutMenu->field_0x36) {
      *(undefined2 *)(MenuPcs._2120_4_ + 10) = 2;
      *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
    }
    goOutMenu->field_0x45 = 0;
    *(undefined2 *)&goOutMenu->field_0x34 = 3;
    goOutMenu->field_0x48 = 0;
    *(undefined4 *)&goOutMenu->field_0x3c = 0;
    goto LAB_8016c9c8;
  }
  if (iVar2 < -5) {
    if (iVar2 == -0xd) {
LAB_8016c92c:
      SetGoOutMode__10CGoOutMenuFUc(goOutMenu,3);
      return 1;
    }
    if (-0xe < iVar2) {
      if (iVar2 < -6) goto LAB_8016c9c8;
      goto LAB_8016c92c;
    }
    if (iVar2 != -999) {
      if (((-1000 < iVar2) || (iVar2 < -1000)) || (*(char *)goOutMenu != '\x01')) goto LAB_8016c9c8;
LAB_8016c94c:
      *(undefined2 *)(MenuPcs._2120_4_ + 10) = 3;
      *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
      *(undefined2 *)&goOutMenu->field_0x36 = 0xffff;
      *(undefined4 *)&goOutMenu->field_0x40 = 0;
      goOutMenu->field_0x44 = 1;
      iVar2 = Game.game.m_gameWork.m_languageId - 1;
      _SetMenuStr__10CGoOutMenuFlie
                (goOutMenu,0,5,(&PTR_s_The_Memory_Card_in_Slot_A_contai_80214fe0)[iVar2 * 0x6e],
                 (&PTR_s_no_save_data_for_your_current_ga_80214fe4)[iVar2 * 0x6e],
                 (&PTR_s_or_contains_corrupt_data__Please_80214fe8)[iVar2 * 0x6e],
                 (&PTR_s_insert_a_Memory_Card_containing_80214fec)[iVar2 * 0x6e],
                 (&PTR_s_valid_save_data_into_Slot_A__80214ff0)[iVar2 * 0x6e]);
      goto LAB_8016c9c8;
    }
    cVar1 = *(char *)goOutMenu;
    if (cVar1 == '\x01') {
      *(undefined2 *)(MenuPcs._2120_4_ + 10) = 3;
      *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
      *(undefined2 *)&goOutMenu->field_0x36 = 0xffff;
      *(undefined4 *)&goOutMenu->field_0x40 = 0;
      goOutMenu->field_0x44 = 1;
      iVar2 = Game.game.m_gameWork.m_languageId - 1;
      _SetMenuStr__10CGoOutMenuFlie
                (goOutMenu,0,5,(&PTR_s_The_Memory_Card_in_Slot_A_contai_80214fe0)[iVar2 * 0x6e],
                 (&PTR_s_no_save_data_for_your_current_ga_80214fe4)[iVar2 * 0x6e],
                 (&PTR_s_or_contains_corrupt_data__Please_80214fe8)[iVar2 * 0x6e],
                 (&PTR_s_insert_a_Memory_Card_containing_80214fec)[iVar2 * 0x6e],
                 (&PTR_s_valid_save_data_into_Slot_A__80214ff0)[iVar2 * 0x6e]);
      goto LAB_8016c9c8;
    }
    if (cVar1 == '\x03') {
      *(undefined2 *)(MenuPcs._2120_4_ + 10) = 3;
      *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
      *(undefined2 *)&goOutMenu->field_0x36 = 0xffff;
      *(undefined4 *)&goOutMenu->field_0x40 = 0;
      goOutMenu->field_0x44 = 1;
      if (-1 < *(short *)&goOutMenu->field_0x36) {
        *(undefined2 *)(MenuPcs._2120_4_ + 10) = 2;
        *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
      }
      goOutMenu->field_0x45 = 0;
      *(undefined2 *)&goOutMenu->field_0x34 = 0xd;
      goOutMenu->field_0x48 = 0;
      *(undefined4 *)&goOutMenu->field_0x3c = 0;
      goto LAB_8016c9c8;
    }
    if (cVar1 == '\x02') {
      *(undefined2 *)(MenuPcs._2120_4_ + 10) = 3;
      *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
      *(undefined2 *)&goOutMenu->field_0x36 = 0xffff;
      *(undefined4 *)&goOutMenu->field_0x40 = 0;
      goOutMenu->field_0x44 = 1;
      if (-1 < *(short *)&goOutMenu->field_0x36) {
        *(undefined2 *)(MenuPcs._2120_4_ + 10) = 2;
        *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
      }
      goOutMenu->field_0x45 = 0;
      *(undefined2 *)&goOutMenu->field_0x34 = 0xf;
      goOutMenu->field_0x48 = 0;
      *(undefined4 *)&goOutMenu->field_0x3c = 0;
      goto LAB_8016c9c8;
    }
  }
  else if (iVar2 != -1) {
    if (-2 < iVar2) {
      if (iVar2 == 1) {
        return 0;
      }
      goto LAB_8016c9c8;
    }
    if (iVar2 != -3) {
      if (-4 < iVar2) {
        *(undefined2 *)(MenuPcs._2120_4_ + 10) = 3;
        *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
        *(undefined2 *)&goOutMenu->field_0x36 = 0xffff;
        *(undefined4 *)&goOutMenu->field_0x40 = 0;
        goOutMenu->field_0x44 = 1;
        if (-1 < *(short *)&goOutMenu->field_0x36) {
          *(undefined2 *)(MenuPcs._2120_4_ + 10) = 2;
          *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
        }
        goOutMenu->field_0x45 = 0;
        *(undefined2 *)&goOutMenu->field_0x34 = 2;
        goOutMenu->field_0x48 = 0;
        *(undefined4 *)&goOutMenu->field_0x3c = 0;
        goto LAB_8016c9c8;
      }
      if (*(char *)goOutMenu != '\x01') {
        *(undefined2 *)(MenuPcs._2120_4_ + 10) = 3;
        *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
        *(undefined2 *)&goOutMenu->field_0x36 = 0xffff;
        *(undefined4 *)&goOutMenu->field_0x40 = 0;
        goOutMenu->field_0x44 = 1;
        if (-1 < *(short *)&goOutMenu->field_0x36) {
          *(undefined2 *)(MenuPcs._2120_4_ + 10) = 2;
          *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
        }
        goOutMenu->field_0x45 = 0;
        *(undefined2 *)&goOutMenu->field_0x34 = 0x13;
        goOutMenu->field_0x48 = 0;
        *(undefined4 *)&goOutMenu->field_0x3c = 0;
        goto LAB_8016c9c8;
      }
      goto LAB_8016c94c;
    }
  }
  *(undefined2 *)(MenuPcs._2120_4_ + 10) = 3;
  *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
  *(undefined2 *)&goOutMenu->field_0x36 = 0xffff;
  *(undefined4 *)&goOutMenu->field_0x40 = 0;
  goOutMenu->field_0x44 = 1;
  if (-1 < *(short *)&goOutMenu->field_0x36) {
    *(undefined2 *)(MenuPcs._2120_4_ + 10) = 2;
    *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
  }
  goOutMenu->field_0x45 = 0;
  *(undefined2 *)&goOutMenu->field_0x34 = 1;
  goOutMenu->field_0x48 = 0;
  *(undefined4 *)&goOutMenu->field_0x3c = 0;
LAB_8016c9c8:
  goOutMenu->field_0x18 = 2;
  return 1;
}


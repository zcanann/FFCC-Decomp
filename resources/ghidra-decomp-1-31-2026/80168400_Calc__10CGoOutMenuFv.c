// Function: Calc__10CGoOutMenuFv
// Entry: 80168400
// Size: 2620 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Calc__10CGoOutMenuFv(CGoOutMenu *goOutMenu)

{
  bool bVar1;
  ushort uVar3;
  byte bVar4;
  int iVar2;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  char cVar10;
  int iVar9;
  int iVar11;
  short local_20;
  short local_1e [9];
  
  goOutMenu->field_0x47 = 0;
  if (MenuPcs._2172_1_ != '\0') {
    MenuPcs._2172_1_ = 0;
    *(undefined2 *)(MenuPcs._2120_4_ + 10) = 3;
    *(undefined2 *)&goOutMenu->field_0x36 = 0xffff;
    *(undefined2 *)&goOutMenu->field_0x34 = 0xffff;
    *(undefined2 *)&goOutMenu->field_0x38 = 0;
    SetMainMode__10CGoOutMenuFUc(goOutMenu,1);
    MenuPcs._2176_4_ =
         __nw__FUlPQ27CMemory6CStagePci(0x8bd0,MenuPcs._236_4_,s_goout_cpp_801e2f24,0x32b);
    MenuPcs._2180_4_ =
         __nw__FUlPQ27CMemory6CStagePci(0x8bd0,MenuPcs._236_4_,s_goout_cpp_801e2f24,0x32d);
    MenuPcs._2188_4_ = 0;
    MenuPcs._2184_1_ = 0;
    MenuPcs._2185_1_ = 0;
    MenuPcs._2186_1_ = 0;
    puVar5 = (undefined4 *)GetWinMess__8CMenuPcsFi(&MenuPcs,0x22);
    *puVar5 = 0;
    *(undefined2 *)(puVar5 + 1) = 0;
    *(undefined2 *)((int)puVar5 + 6) = 1;
    *(undefined2 *)(puVar5 + 2) = 2;
    *(undefined2 *)((int)puVar5 + 10) = 3;
    *(undefined2 *)(puVar5 + 3) = 4;
    *(undefined2 *)((int)puVar5 + 0xe) = 5;
    *(undefined2 *)(puVar5 + 4) = 6;
    *(undefined2 *)((int)puVar5 + 0x12) = 7;
    puVar5 = (undefined4 *)GetWinMess__8CMenuPcsFi(&MenuPcs,0x23);
    *puVar5 = 0;
    *(undefined2 *)(puVar5 + 1) = 10;
    *(undefined2 *)((int)puVar5 + 6) = 0xb;
    *(undefined2 *)(puVar5 + 2) = 0xc;
    *(undefined2 *)((int)puVar5 + 10) = 0xd;
    *(undefined2 *)(puVar5 + 3) = 0xe;
    *(undefined2 *)((int)puVar5 + 0xe) = 0xf;
    *(undefined2 *)(puVar5 + 4) = 0x10;
    *(undefined2 *)((int)puVar5 + 0x12) = 0x11;
    *(undefined2 *)(MenuPcs._2120_4_ + 10) = 3;
    goOutMenu->field_0x44 = 1;
  }
  if (goOutMenu->field_0x48 != '\0') goto LAB_80168cf4;
  cVar10 = goOutMenu->field_0x2c;
  if (cVar10 == '\x02') {
    CalcGoOut__10CGoOutMenuFv(goOutMenu);
  }
  else if (cVar10 < '\x02') {
    if (cVar10 == '\0') {
      if (goOutMenu->field_0x45 != '\0') {
        bVar1 = false;
        if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
          bVar1 = true;
        }
        if (bVar1) {
          uVar3 = 0;
        }
        else {
          countLeadingZeros(Pad._448_4_);
          uVar3 = Pad._8_2_;
        }
        if ((uVar3 & 0x100) != 0) {
          PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
          SetMainMode__10CGoOutMenuFUc(goOutMenu,goOutMenu->field_0x2d);
        }
      }
    }
    else if ((-1 < cVar10) && (goOutMenu->field_0x45 != '\0')) {
      bVar1 = false;
      if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        bVar1 = true;
      }
      if (bVar1) {
        uVar3 = 0;
      }
      else {
        countLeadingZeros(Pad._448_4_);
        uVar3 = Pad._8_2_;
      }
      if ((uVar3 & 0x200) != 0) {
        PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
        InitSaveLoadMenu__8CMenuPcsFv(&MenuPcs);
        SetMenuCharaAnim__8CMenuPcsFii(&MenuPcs);
        *(undefined2 *)(MenuPcs._2092_4_ + 0x20) = 0xffff;
        if (MenuPcs._2176_4_ != 0) {
          __dl__FPv();
          MenuPcs._2176_4_ = 0;
        }
        if (MenuPcs._2180_4_ != 0) {
          __dl__FPv();
          MenuPcs._2180_4_ = 0;
        }
        MenuPcs._2188_4_ = 0;
        MenuPcs._2184_1_ = 0;
        MenuPcs._2185_1_ = 0;
        MenuPcs._2186_1_ = 0;
        MenuPcs._2172_1_ = 1;
        ChgAllModel__8CMenuPcsFv(&MenuPcs);
        return;
      }
      goOutMenu->field_0x47 = 1;
      goOutMenu->field74_0x4a = 200;
      goOutMenu->field75_0x4c = 0xb0;
      goOutMenu->field_0x49 = 1;
      if (*(short *)(MenuPcs._2120_4_ + 10) == 1) {
        bVar1 = false;
        if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
          bVar1 = true;
        }
        if (bVar1) {
          uVar3 = 0;
        }
        else {
          countLeadingZeros(Pad._448_4_);
          uVar3 = Pad._8_2_;
        }
        if ((uVar3 & 0xc) == 0) {
          bVar1 = false;
          if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
            bVar1 = true;
          }
          if (bVar1) {
            uVar3 = 0;
          }
          else {
            countLeadingZeros(Pad._448_4_);
            uVar3 = Pad._8_2_;
          }
          if ((uVar3 & 0x100) != 0) {
            PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
            bVar4 = goOutMenu->field_0x46 + 1;
            goto LAB_80168910;
          }
        }
        else {
          goOutMenu->field_0x46 = goOutMenu->field_0x46 ^ 1;
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
        bVar4 = 0;
      }
      else {
        bVar4 = 0;
      }
LAB_80168910:
      if (bVar4 == 2) {
        iVar6 = -0x7fde1140;
        iVar2 = 0;
        iVar9 = 0;
        iVar11 = 2;
        do {
          iVar7 = iVar2;
          if ((*(int *)(iVar6 + 0x1794) != 0) &&
             (iVar7 = iVar2 + 1, *(char *)(iVar6 + 0x1f95) != '\0')) {
            iVar7 = iVar2 + 2;
          }
          iVar2 = iVar7;
          if ((*(int *)(iVar6 + 0x23c4) != 0) &&
             (iVar2 = iVar7 + 1, *(char *)(iVar6 + 0x2bc5) != '\0')) {
            iVar2 = iVar7 + 2;
          }
          iVar7 = iVar2;
          if ((*(int *)(iVar6 + 0x2ff4) != 0) &&
             (iVar7 = iVar2 + 1, *(char *)(iVar6 + 0x37f5) != '\0')) {
            iVar7 = iVar2 + 2;
          }
          iVar2 = iVar7;
          if ((*(int *)(iVar6 + 0x3c24) != 0) &&
             (iVar2 = iVar7 + 1, *(char *)(iVar6 + 0x4425) != '\0')) {
            iVar2 = iVar7 + 2;
          }
          iVar6 = iVar6 + 0x30c0;
          iVar9 = iVar9 + 3;
          iVar11 = iVar11 + -1;
        } while (iVar11 != 0);
        if (iVar2 < 2) {
          _SetMenuStr__10CGoOutMenuFlie
                    (goOutMenu,0,2,
                     (&PTR_s_The_character_cannot_be_80215190)
                     [(Game.game.m_gameWork.m_languageId - 1) * 0x6e],
                     (&PTR_s_deleted_from_the_current_data__80215194)
                     [(Game.game.m_gameWork.m_languageId - 1) * 0x6e]);
          goOutMenu->field_0x2d = 1;
          SetMainMode__10CGoOutMenuFUc(goOutMenu,0);
        }
        else {
          SetMainMode__10CGoOutMenuFUc(goOutMenu,3,iVar9);
          if (-1 < *(short *)&goOutMenu->field_0x36) {
            *(undefined2 *)(MenuPcs._2120_4_ + 10) = 2;
            *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
          }
          goOutMenu->field_0x45 = 0;
          *(undefined2 *)&goOutMenu->field_0x34 = 0xffff;
          goOutMenu->field_0x48 = 0;
          *(undefined4 *)&goOutMenu->field_0x3c = 0;
        }
      }
      else if ((bVar4 < 2) && (bVar4 != 0)) {
        iVar2 = -0x7fde1140;
        cVar10 = Game.game.m_caravanWorkArr[0].m_shopState != 0;
        if (Game.game.m_caravanWorkArr[1].m_shopState != 0) {
          cVar10 = cVar10 + '\x01';
        }
        if (Game.game.m_caravanWorkArr[2].m_shopState != 0) {
          cVar10 = cVar10 + '\x01';
        }
        if (Game.game.m_caravanWorkArr[3].m_shopState != 0) {
          cVar10 = cVar10 + '\x01';
        }
        if (Game.game.m_caravanWorkArr[4].m_shopState != 0) {
          cVar10 = cVar10 + '\x01';
        }
        if (Game.game.m_caravanWorkArr[5].m_shopState != 0) {
          cVar10 = cVar10 + '\x01';
        }
        if (Game.game.m_caravanWorkArr[6].m_shopState != 0) {
          cVar10 = cVar10 + '\x01';
        }
        if (Game.game.m_caravanWorkArr[7].m_shopState != 0) {
          cVar10 = cVar10 + '\x01';
        }
        if (cVar10 == '\0') {
          iVar2 = Game.game.m_gameWork.m_languageId - 1;
          _SetMenuStr__10CGoOutMenuFlie
                    (goOutMenu,0,7,(&PTR_s_The_current_game_data_contains_n_80215174)[iVar2 * 0x6e],
                     (&PTR_s_characters__so_no_characters_can_80215178)[iVar2 * 0x6e],
                     (&PTR_s_be_imported__8021517c)[iVar2 * 0x6e],(&PTR_DAT_80215180)[iVar2 * 0x6e],
                     (&PTR_s_To_import_a_character__you_must_80215184)[iVar2 * 0x6e],
                     (&PTR_s_first_create_one_and_save_the_da_80215188)[iVar2 * 0x6e],
                     (&PTR_s_to_a_Memory_Card__8021518c)[iVar2 * 0x6e]);
          goOutMenu->field_0x2d = 1;
          SetMainMode__10CGoOutMenuFUc(goOutMenu,0);
        }
        else {
          iVar6 = 0;
          iVar9 = 0;
          iVar11 = 2;
          do {
            if ((*(int *)(iVar2 + 0x1794) != 0) && (*(char *)(iVar2 + 0x1f95) == '\0')) {
              iVar6 = iVar6 + 1;
            }
            if ((*(int *)(iVar2 + 0x23c4) != 0) && (*(char *)(iVar2 + 0x2bc5) == '\0')) {
              iVar6 = iVar6 + 1;
            }
            if ((*(int *)(iVar2 + 0x2ff4) != 0) && (*(char *)(iVar2 + 0x37f5) == '\0')) {
              iVar6 = iVar6 + 1;
            }
            if ((*(int *)(iVar2 + 0x3c24) != 0) && (*(char *)(iVar2 + 0x4425) == '\0')) {
              iVar6 = iVar6 + 1;
            }
            iVar2 = iVar2 + 0x30c0;
            iVar9 = iVar9 + 3;
            iVar11 = iVar11 + -1;
          } while (iVar11 != 0);
          if (iVar6 < 8) {
            SetMainMode__10CGoOutMenuFUc(goOutMenu,2,iVar9);
          }
          else {
            iVar2 = Game.game.m_gameWork.m_languageId - 1;
            _SetMenuStr__10CGoOutMenuFlie
                      (goOutMenu,0,6,(&PTR_s_The_current_game_data_already_802150d8)[iVar2 * 0x6e],
                       (&PTR_s_contains_8_characters__so_no_mor_802150dc)[iVar2 * 0x6e],
                       (&PTR_s_characters_can_be_transferred__802150e0)[iVar2 * 0x6e],
                       (&PTR_DAT_802150e4)[iVar2 * 0x6e],
                       (&PTR_s_You_must_delete_at_least_one_cha_802150e8)[iVar2 * 0x6e],
                       (&PTR_s_before_you_can_transfer_any_more_802150ec)[iVar2 * 0x6e]);
            goOutMenu->field_0x2d = 1;
            SetMainMode__10CGoOutMenuFUc(goOutMenu,0);
          }
        }
      }
    }
  }
  else if (cVar10 < '\x04') {
    CalcDel__10CGoOutMenuFv(goOutMenu);
  }
  *(int *)&goOutMenu->field_0x30 = *(int *)&goOutMenu->field_0x30 + 1;
  if (10000 < *(uint *)&goOutMenu->field_0x30) {
    *(undefined4 *)&goOutMenu->field_0x30 = 10000;
  }
LAB_80168cf4:
  if (*(short *)(MenuPcs._2120_4_ + 10) == 1) {
    goOutMenu->field_0x44 = 1;
    goOutMenu->field_0x45 = 1;
  }
  if ((goOutMenu->field_0x44 != '\0') && (*(short *)(MenuPcs._2120_4_ + 10) == 3)) {
    *(undefined2 *)&goOutMenu->field_0x36 = *(undefined2 *)&goOutMenu->field_0x34;
    if (*(short *)&goOutMenu->field_0x34 == -1) {
      goOutMenu->field_0x44 = 1;
    }
    else {
      uVar8 = (uint)*(short *)&goOutMenu->field_0x36;
      GetWinSize__8CMenuPcsFiPsPsi
                (&MenuPcs,uVar8,&local_20,local_1e,
                 ~-((uint)(uVar8 < 0x1e) - ((int)uVar8 >> 0x1f)) & 2);
      SetMcWinInfo__8CMenuPcsFii(&MenuPcs,(int)local_20,(int)local_1e[0]);
      *(undefined2 *)(MenuPcs._2120_4_ + 10) = 0;
      *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
      *(undefined4 *)&goOutMenu->field_0x40 = *(undefined4 *)&goOutMenu->field_0x3c;
      goOutMenu->field_0x44 = 0;
    }
  }
  if ((*(int *)&goOutMenu->field_0x40 != 0) &&
     (iVar2 = *(int *)&goOutMenu->field_0x40 + -1, *(int *)&goOutMenu->field_0x40 = iVar2,
     iVar2 == 0)) {
    if (-1 < *(short *)&goOutMenu->field_0x36) {
      *(undefined2 *)(MenuPcs._2120_4_ + 10) = 2;
      *(undefined2 *)(MenuPcs._2092_4_ + 0x22) = 0;
    }
    goOutMenu->field_0x45 = 0;
    *(undefined2 *)&goOutMenu->field_0x34 = 0xffff;
    goOutMenu->field_0x48 = 0;
    *(undefined4 *)&goOutMenu->field_0x3c = 0;
  }
  return;
}


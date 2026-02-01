// Function: LetterCtrlCur__8CMenuPcsFv
// Entry: 80163fdc
// Size: 3844 bytes

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 LetterCtrlCur__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  byte bVar1;
  short sVar2;
  bool bVar3;
  uint32_t caravanWork;
  float fVar4;
  ushort uVar5;
  ushort uVar6;
  short *psVar7;
  void *ptr;
  undefined *ptr_00;
  undefined *puVar8;
  int iVar9;
  uint uVar10;
  undefined4 uVar11;
  int iVar12;
  undefined *puVar13;
  int iVar14;
  uint uVar15;
  
  caravanWork = Game.game.m_scriptFoodBase[0];
  bVar3 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar3 = true;
  }
  if (bVar3) {
    uVar5 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar5 = Pad._8_2_;
  }
  bVar3 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar3 = true;
  }
  if (bVar3) {
    uVar6 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar6 = Pad._20_2_;
  }
  if (uVar6 == 0) {
    return 0;
  }
  iVar12 = *(int *)&menuPcs->field_0x82c;
  sVar2 = *(short *)(iVar12 + 0x30);
  if (sVar2 != 0) {
    if (sVar2 != 1) {
      if (sVar2 == 2) {
        if ((uVar6 & 0xc) != 0) {
          *(ushort *)(iVar12 + 0x28) = *(ushort *)(iVar12 + 0x28) ^ 1;
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
        if ((uVar6 & 0xc) != 0) {
          return 0;
        }
        if ((uVar5 & 0x100) == 0) {
          if ((uVar5 & 0x200) == 0) {
            return 0;
          }
          if (((CFlat._66568_4_ == 0) ||
              (bVar1 = *(byte *)(caravanWork + DAT_8032eee8 * 0xc + 0x3ec), (bVar1 >> 4 & 1) == 0))
             || ((bVar1 >> 5 & 1) != 0)) {
            *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 0xff;
          }
          else {
            *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 1;
          }
          *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
               *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
          *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
          PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
          return 0;
        }
        sVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x28);
        if (((int)*(char *)(*(int *)&menuPcs->field_0x82c + 9) & 1 << sVar2 + 1) != 0) {
          if (sVar2 == 0) {
            iVar12 = caravanWork + DAT_8032eee8 * 0xc;
            uVar10 = *(ushort *)(iVar12 + 0x3ee) & 0x1ff;
            if ((*(byte *)(iVar12 + 0x3ec) >> 3 & 1) == 0) {
              AddItem__12CCaravanWorkFiPi((CCaravanWork *)caravanWork,(short)uVar10,0);
            }
            else {
              AddGil__12CCaravanWorkFi((CCaravanWork *)caravanWork,uVar10 * 100);
            }
            iVar12 = DAT_8032eee8 * 0xc + 0x3ec;
            *(byte *)(caravanWork + iVar12) = *(byte *)(caravanWork + iVar12) & 0xbf | 0x40;
          }
          if (((CFlat._66568_4_ == 0) ||
              (bVar1 = *(byte *)(caravanWork + DAT_8032eee8 * 0xc + 0x3ec), (bVar1 >> 4 & 1) == 0))
             || ((bVar1 >> 5 & 1) != 0)) {
            *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 0xff;
          }
          else {
            *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 1;
          }
          *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
               *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
          *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
          PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
          return 0;
        }
        PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
        return 0;
      }
      if (sVar2 != 3) {
        if (sVar2 == 4) {
          if ((uVar6 & 8) == 0) {
            if ((uVar6 & 4) != 0) {
              if (*(short *)(iVar12 + 0x28) < 3) {
                *(short *)(iVar12 + 0x28) = *(short *)(iVar12 + 0x28) + 1;
              }
              else {
                *(undefined2 *)(iVar12 + 0x28) = 0;
              }
              PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
            }
          }
          else {
            if (*(short *)(iVar12 + 0x28) == 0) {
              *(undefined2 *)(iVar12 + 0x28) = 3;
            }
            else {
              *(short *)(iVar12 + 0x28) = *(short *)(iVar12 + 0x28) + -1;
            }
            PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
          }
          if ((uVar6 & 0xc) != 0) {
            return 0;
          }
          if ((uVar5 & 0x100) != 0) {
            sVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x28);
            if (sVar2 < 3) {
              DAT_8032eeed = (char)sVar2;
              *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 1;
            }
            else {
              DAT_8032eeed = 2;
              *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 0xff;
            }
            *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
                 *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
            DAT_8032eef4 = 0;
            DAT_8032eef0 = 0;
            *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
            PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
            return 0;
          }
          if ((uVar5 & 0x200) == 0) {
            return 0;
          }
          *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 0xff;
          *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
               *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
          *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
          PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
          return 0;
        }
        if (sVar2 != 5) {
          return 0;
        }
        if ((uVar6 & 0xc) != 0) {
          *(ushort *)(iVar12 + 0x28) = *(ushort *)(iVar12 + 0x28) ^ 1;
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
        if ((uVar6 & 0xc) != 0) {
          return 0;
        }
        if ((uVar5 & 0x100) != 0) {
          if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x28) == 0) {
            iVar14 = 0;
            iVar12 = DAT_8032eef0;
            if ((DAT_8032eeed != '\0') && (iVar12 = 0, DAT_8032eeed == '\x01')) {
              iVar14 = DAT_8032eef0;
            }
            FGLetterReply__12CCaravanWorkFiiii
                      ((CCaravanWork *)caravanWork,(int)DAT_8032eee8,(int)DAT_8032eeec,iVar12,iVar14
                      );
            if (DAT_8032eeed == '\0') {
              DeleteItemIdx__12CCaravanWorkFii((CCaravanWork *)caravanWork,(int)DAT_8032eeee,0);
            }
            else {
              AddGil__12CCaravanWorkFi((CCaravanWork *)caravanWork,-iVar14);
            }
            *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 1;
          }
          else {
            *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 0xff;
          }
          *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
               *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
          *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
          PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
          return 0;
        }
        if ((uVar5 & 0x200) == 0) {
          return 0;
        }
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 0xff;
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
             *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
        PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
        return 0;
      }
      iVar14 = (int)DAT_8032eeeb;
      if ((uVar6 & 8) == 0) {
        if ((uVar6 & 4) != 0) {
          if ((int)*(short *)(iVar12 + 0x28) < iVar14 + -1) {
            *(short *)(iVar12 + 0x28) = *(short *)(iVar12 + 0x28) + 1;
          }
          else {
            *(undefined2 *)(iVar12 + 0x28) = 0;
          }
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
      }
      else {
        if (*(short *)(iVar12 + 0x28) == 0) {
          *(short *)(iVar12 + 0x28) = DAT_8032eeeb + -1;
        }
        else {
          *(short *)(iVar12 + 0x28) = *(short *)(iVar12 + 0x28) + -1;
        }
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
      if ((uVar6 & 0xc) != 0) {
        return 0;
      }
      if ((uVar5 & 0x100) == 0) {
        if ((uVar5 & 0x200) == 0) {
          return 0;
        }
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 0xff;
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
             *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
        PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
        return 0;
      }
      sVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x28);
      if ((int)sVar2 < iVar14 + -1) {
        DAT_8032eeec = (char)sVar2;
        uVar11 = MenuPcs._236_4_;
        if (Game.game.m_gameWork.m_menuStageMode != '\0') {
          uVar11 = MenuPcs._244_4_;
        }
        ptr = (void *)__nwa__FUlPQ27CMemory6CStagePci(0x400,uVar11,s_menu_letter_cpp_801dedf8,0x65e)
        ;
        uVar11 = MenuPcs._236_4_;
        if (Game.game.m_gameWork.m_menuStageMode != '\0') {
          uVar11 = MenuPcs._244_4_;
        }
        ptr_00 = (undefined *)
                 __nwa__FUlPQ27CMemory6CStagePci(0x400,uVar11,s_menu_letter_cpp_801dedf8,0x660);
        memset(ptr,0,0x400);
        memset(ptr_00,0,0x400);
        strcpy(ptr,*(undefined4 *)
                    ((int)Game.game.m_cFlatDataArr[1].m_mesPtr +
                    (*(ushort *)(caravanWork + DAT_8032eee8 * 0xc + 0x3ec) & 0x7fc) * 2 + 0x44));
        MakeAgbString__4CMesFPcPcii(ptr_00,ptr,*(undefined2 *)(caravanWork + 0x3e2),0);
        iVar12 = 0;
        puVar13 = ptr_00;
        do {
          puVar8 = (undefined *)strchr(puVar13,10);
          if (puVar8 != (undefined *)0x0) {
            *puVar8 = 0;
          }
          if (iVar12 == DAT_8032eeec) {
            strcpy(s_ReplyStr,puVar13);
          }
          if (puVar8 == (undefined *)0x0) break;
          iVar12 = iVar12 + 1;
          puVar13 = puVar8 + 1;
        } while (iVar12 < 7);
        __dla__FPv(ptr);
        __dla__FPv(ptr_00);
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 1;
      }
      else {
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 0xff;
      }
      *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
           *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
      *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
      PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
      return 0;
    }
    if ((uVar5 & 0x100) != 0) {
      iVar14 = Game.game.m_scriptFoodBase[0] + DAT_8032eee8 * 0xc;
      if (((*(ushort *)(iVar14 + 0x3ee) & 0x1ff) != 0) &&
         ((*(byte *)(iVar14 + 0x3ec) >> 6 & 1) == 0)) {
        *(undefined *)(iVar12 + 8) = 1;
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 9) = 5;
        iVar12 = caravanWork + DAT_8032eee8 * 0xc;
        if ((*(byte *)(iVar12 + 0x3ec) >> 3 & 1) == 0) {
          if (*(ushort *)(caravanWork + 0xb4) + 1 < 0x41) {
            *(byte *)(*(int *)&menuPcs->field_0x82c + 9) =
                 *(byte *)(*(int *)&menuPcs->field_0x82c + 9) | 2;
          }
        }
        else {
          iVar12 = CanAddGil__12CCaravanWorkFi
                             ((CCaravanWork *)caravanWork,
                              (*(ushort *)(iVar12 + 0x3ee) & 0x1ff) * 100);
          if (iVar12 != 0) {
            *(byte *)(*(int *)&menuPcs->field_0x82c + 9) =
                 *(byte *)(*(int *)&menuPcs->field_0x82c + 9) | 2;
          }
        }
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
             *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
        PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
        return 0;
      }
      if ((CFlat._66568_4_ != 0) &&
         (((*(byte *)(iVar14 + 0x3ec) >> 4 & 1) != 0 && ((*(byte *)(iVar14 + 0x3ec) >> 5 & 1) == 0))
         )) {
        *(undefined *)(iVar12 + 8) = 2;
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
             *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
        PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
        return 0;
      }
      PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
      return 0;
    }
    if ((uVar5 & 0x200) == 0) {
      return 0;
    }
    *(undefined *)(iVar12 + 8) = 0xff;
    fVar4 = FLOAT_803330f8;
    *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
         *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
    iVar12 = *(int *)&menuPcs->field_0x850;
    *(undefined4 *)(iVar12 + 0x2c) = 0;
    *(undefined4 *)(iVar12 + 0x30) = 10;
    iVar12 = *(int *)&menuPcs->field_0x850;
    *(undefined4 *)(iVar12 + 0x6c) = 0;
    *(undefined4 *)(iVar12 + 0x70) = 10;
    uVar10 = (uint)**(short **)&menuPcs->field_0x850;
    psVar7 = *(short **)&menuPcs->field_0x850 + 4;
    if (0 < (int)uVar10) {
      uVar15 = uVar10 >> 3;
      if (uVar15 != 0) {
        do {
          psVar7[0x10] = 0;
          psVar7[0x11] = 0;
          *(float *)(psVar7 + 8) = fVar4;
          psVar7[0x30] = 0;
          psVar7[0x31] = 0;
          *(float *)(psVar7 + 0x28) = fVar4;
          psVar7[0x50] = 0;
          psVar7[0x51] = 0;
          *(float *)(psVar7 + 0x48) = fVar4;
          psVar7[0x70] = 0;
          psVar7[0x71] = 0;
          *(float *)(psVar7 + 0x68) = fVar4;
          psVar7[0x90] = 0;
          psVar7[0x91] = 0;
          *(float *)(psVar7 + 0x88) = fVar4;
          psVar7[0xb0] = 0;
          psVar7[0xb1] = 0;
          *(float *)(psVar7 + 0xa8) = fVar4;
          psVar7[0xd0] = 0;
          psVar7[0xd1] = 0;
          *(float *)(psVar7 + 200) = fVar4;
          psVar7[0xf0] = 0;
          psVar7[0xf1] = 0;
          *(float *)(psVar7 + 0xe8) = fVar4;
          psVar7 = psVar7 + 0x100;
          uVar15 = uVar15 - 1;
        } while (uVar15 != 0);
        uVar10 = uVar10 & 7;
        if (uVar10 == 0) goto LAB_801646dc;
      }
      do {
        psVar7[0x10] = 0;
        psVar7[0x11] = 0;
        *(float *)(psVar7 + 8) = fVar4;
        psVar7 = psVar7 + 0x20;
        uVar10 = uVar10 - 1;
      } while (uVar10 != 0);
    }
LAB_801646dc:
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
    PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
    return 0;
  }
  iVar14 = *(int *)(Game.game.m_scriptFoodBase[0] + 1000);
  if ((iVar14 == 0) && ((uVar6 & 0xc) != 0)) {
    PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
    return 0;
  }
  if ((uVar6 & 8) == 0) {
    if ((uVar6 & 4) != 0) {
      iVar9 = (int)*(short *)(iVar12 + 0x26);
      if ((iVar9 < 8) && (iVar9 < iVar14 + -1)) {
        *(short *)(iVar12 + 0x26) = *(short *)(iVar12 + 0x26) + 1;
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
      else if (*(short *)(iVar12 + 0x34) + iVar9 < iVar14 + -1) {
        *(short *)(iVar12 + 0x34) = *(short *)(iVar12 + 0x34) + 1;
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
      else {
        PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
      }
    }
  }
  else if (*(short *)(iVar12 + 0x26) == 0) {
    if (*(short *)(iVar12 + 0x34) == 0) {
      PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
    }
    else {
      *(short *)(iVar12 + 0x34) = *(short *)(iVar12 + 0x34) + -1;
      PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
    }
  }
  else {
    *(short *)(iVar12 + 0x26) = *(short *)(iVar12 + 0x26) + -1;
    PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
  }
  fVar4 = FLOAT_803330f8;
  if ((uVar6 & 0xc) != 0) {
    return 0;
  }
  if ((uVar5 & 0x20) != 0) {
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 1;
    PlaySe__6CSoundFiiii(&Sound,0x5a,0x40,0x7f,0);
    return 1;
  }
  if ((uVar5 & 0x40) != 0) {
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 0xffff;
    PlaySe__6CSoundFiiii(&Sound,0x5a,0x40,0x7f,0);
    return 1;
  }
  if ((uVar5 & 0x100) == 0) {
    if ((uVar5 & 0x200) == 0) {
      return 0;
    }
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xd) = 1;
    PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
    return 1;
  }
  if (iVar14 == 0) {
    PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
    return 0;
  }
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) =
       *(short *)(*(int *)&menuPcs->field_0x82c + 0x12) + 1;
  DAT_8032eee8 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x34) +
                 *(short *)(*(int *)&menuPcs->field_0x82c + 0x26);
  iVar12 = caravanWork + DAT_8032eee8 * 0xc;
  m_tempVar__4CMes._0_4_ = ZEXT24(*(ushort *)(iVar12 + 0x3f0));
  m_tempVar__4CMes._4_4_ = ZEXT24(*(ushort *)(iVar12 + 0x3f2));
  m_tempVar__4CMes._8_4_ = ZEXT24(*(ushort *)(iVar12 + 0x3f4));
  m_tempVar__4CMes._12_4_ = ZEXT24(*(ushort *)(iVar12 + 0x3f6));
  iVar12 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar12 + 0x24) = 0;
  *(undefined4 *)(iVar12 + 0x2c) = 10;
  *(undefined4 *)(iVar12 + 0x30) = 10;
  iVar12 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar12 + 100) = 0;
  *(undefined4 *)(iVar12 + 0x6c) = 0;
  *(undefined4 *)(iVar12 + 0x70) = 10;
  uVar10 = (uint)**(short **)&menuPcs->field_0x850;
  psVar7 = *(short **)&menuPcs->field_0x850 + 4;
  if (0 < (int)uVar10) {
    uVar15 = uVar10 >> 3;
    if (uVar15 != 0) {
      do {
        psVar7[0x10] = 0;
        psVar7[0x11] = 0;
        *(float *)(psVar7 + 8) = fVar4;
        psVar7[0x30] = 0;
        psVar7[0x31] = 0;
        *(float *)(psVar7 + 0x28) = fVar4;
        psVar7[0x50] = 0;
        psVar7[0x51] = 0;
        *(float *)(psVar7 + 0x48) = fVar4;
        psVar7[0x70] = 0;
        psVar7[0x71] = 0;
        *(float *)(psVar7 + 0x68) = fVar4;
        psVar7[0x90] = 0;
        psVar7[0x91] = 0;
        *(float *)(psVar7 + 0x88) = fVar4;
        psVar7[0xb0] = 0;
        psVar7[0xb1] = 0;
        *(float *)(psVar7 + 0xa8) = fVar4;
        psVar7[0xd0] = 0;
        psVar7[0xd1] = 0;
        *(float *)(psVar7 + 200) = fVar4;
        psVar7[0xf0] = 0;
        psVar7[0xf1] = 0;
        *(float *)(psVar7 + 0xe8) = fVar4;
        psVar7 = psVar7 + 0x100;
        uVar15 = uVar15 - 1;
      } while (uVar15 != 0);
      uVar10 = uVar10 & 7;
      if (uVar10 == 0) goto LAB_80164428;
    }
    do {
      psVar7[0x10] = 0;
      psVar7[0x11] = 0;
      *(float *)(psVar7 + 8) = fVar4;
      psVar7 = psVar7 + 0x20;
      uVar10 = uVar10 - 1;
    } while (uVar10 != 0);
  }
LAB_80164428:
  *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
  PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
  return 0;
}


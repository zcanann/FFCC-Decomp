// Function: CmakeNameCtrl__8CMenuPcsFv
// Entry: 80171fa0
// Size: 2332 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 CmakeNameCtrl__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  short sVar2;
  short sVar3;
  ushort uVar5;
  ushort uVar6;
  uint uVar4;
  uint uVar7;
  int iVar8;
  undefined4 uVar9;
  bool bVar12;
  int iVar10;
  CmakeInfo *pCVar11;
  int iVar13;
  undefined *puVar14;
  short local_28;
  short local_26;
  char local_24 [12];
  
  bVar12 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar12 = true;
  }
  if (bVar12) {
    uVar5 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar5 = Pad._8_2_;
  }
  bVar12 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar12 = true;
  }
  if (bVar12) {
    uVar6 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar6 = Pad._20_2_;
  }
  if (uVar6 != 0) {
    sVar1 = *(short *)(*(int *)&menuPcs->field_0x848 + 10);
    if (sVar1 == 3) {
      if ((uVar6 & 8) == 0) {
        if ((uVar6 & 4) != 0) {
          iVar10 = *(int *)&menuPcs->field_0x82c;
          if ((int)*(short *)(iVar10 + 0x28) <
              (int)(((int)*(short *)(iVar10 + 0x26) >> 0x1f) +
                    (uint)(9 < (uint)(int)*(short *)(iVar10 + 0x26)) + 4)) {
            *(short *)(iVar10 + 0x28) = *(short *)(iVar10 + 0x28) + 1;
          }
          else {
            *(undefined2 *)(iVar10 + 0x28) = 0;
          }
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
      }
      else {
        iVar10 = *(int *)&menuPcs->field_0x82c;
        if (*(short *)(iVar10 + 0x28) == 0) {
          if (*(short *)(iVar10 + 0x26) < 10) {
            *(undefined2 *)(iVar10 + 0x28) = 4;
          }
          else {
            *(undefined2 *)(iVar10 + 0x28) = 5;
          }
        }
        else {
          *(short *)(iVar10 + 0x28) = *(short *)(iVar10 + 0x28) + -1;
        }
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
      if ((uVar6 & 1) == 0) {
        if ((uVar6 & 2) != 0) {
          iVar10 = *(int *)&menuPcs->field_0x82c;
          if (*(short *)(iVar10 + 0x28) < 5) {
            if (*(short *)(iVar10 + 0x26) < 0xb) {
              *(short *)(iVar10 + 0x26) = *(short *)(iVar10 + 0x26) + 1;
            }
            else {
              *(undefined2 *)(iVar10 + 0x26) = 0;
            }
            PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
          }
          else {
            PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
          }
        }
      }
      else {
        iVar10 = *(int *)&menuPcs->field_0x82c;
        if (*(short *)(iVar10 + 0x28) < 5) {
          if (*(short *)(iVar10 + 0x26) == 0) {
            *(undefined2 *)(iVar10 + 0x26) = 0xb;
          }
          else {
            *(short *)(iVar10 + 0x26) = *(short *)(iVar10 + 0x26) + -1;
          }
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
        else {
          PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
        }
      }
      if ((uVar6 & 0xf) == 0) {
        if ((uVar5 & 0x40) == 0) {
          if ((uVar5 & 0x20) == 0) {
            if ((uVar5 & 0x1000) == 0) {
              if ((uVar5 & 0x100) == 0) {
                if ((uVar5 & 0x200) != 0) {
                  uVar7 = strlen(&s_CmakeInfo);
                  if ((uVar7 & (int)(-uVar7 | uVar7) >> 0x1f) == 0) {
                    PlaySe__6CSoundFiiii(&Sound,0x34,0x40,0x7f,0);
                    ChgModel__8CMenuPcsFiiii
                              (menuPcs,(int)*(short *)&menuPcs->field_0x86a,0xffffffff,0xffffffff,
                               0xffffffff);
                    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 0xffff;
                    return 0xffffffff;
                  }
                  uVar7 = strlen(&s_CmakeInfo);
                  if ((uVar7 & (int)(-uVar7 | uVar7) >> 0x1f) == 0) {
                    iVar10 = -1;
                  }
                  else {
                    iVar10 = strlen(&s_CmakeInfo);
                    uVar9 = strlen(&s_CmakeInfo);
                    uVar7 = countLeadingZeros(uVar9);
                    if ((uVar7 >> 5 & 1) == 0) {
                      (&g_GoOutMenu.field_0x4f)[iVar10] = 0;
                    }
                    else {
                      (&g_GoOutMenu.field_0x4e)[iVar10] = 0;
                    }
                    iVar10 = 0;
                  }
                  if (iVar10 == 0) {
                    PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
                  }
                  else {
                    PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
                  }
                }
              }
              else {
                iVar10 = *(int *)&menuPcs->field_0x82c;
                sVar1 = *(short *)(iVar10 + 0x28);
                if (sVar1 < 5) {
                  sVar2 = *(short *)(iVar10 + 0x2a);
                  sVar3 = *(short *)(iVar10 + 0x26);
                  memset(local_24,0,3);
                  local_24[0] = '\0';
                  puVar14 = (&PTR_s_ABCDEFGHIJKL_80215968)[(int)sVar1 + sVar2 * 5];
                  iVar10 = strlen(puVar14);
                  if (iVar10 != 0) {
                    iVar8 = 0;
                    iVar13 = 0;
                    if (0 < iVar10) {
                      do {
                        if (iVar8 == sVar3) {
                          local_24[0] = puVar14[iVar13];
                          local_24[1] = 0;
                          break;
                        }
                        iVar8 = iVar8 + 1;
                        iVar13 = iVar13 + 1;
                        iVar10 = iVar10 + -1;
                      } while (iVar10 != 0);
                    }
                  }
                  uVar7 = strlen(&s_CmakeInfo);
                  uVar7 = uVar7 & (int)(-uVar7 | uVar7) >> 0x1f;
                  if ((int)uVar7 < 7) {
                    local_24[0] = '\0';
                    iVar10 = strlen(puVar14);
                    if (iVar10 != 0) {
                      iVar8 = 0;
                      iVar13 = 0;
                      if (0 < iVar10) {
                        do {
                          if (iVar8 == sVar3) {
                            local_24[0] = puVar14[iVar13];
                            local_24[1] = 0;
                            break;
                          }
                          iVar8 = iVar8 + 1;
                          iVar13 = iVar13 + 1;
                          iVar10 = iVar10 + -1;
                        } while (iVar10 != 0);
                      }
                    }
                    if (uVar7 == 0) {
                      strcat((char *)&s_CmakeInfo,local_24);
                      iVar10 = 0;
                    }
                    else {
                      uVar9 = strlen(puVar14);
                      uVar4 = countLeadingZeros(uVar9);
                      if (((uVar4 >> 5 & 1) == 0) && (6 < (int)uVar7)) {
                        iVar10 = -1;
                      }
                      else {
                        strcat((char *)&s_CmakeInfo,local_24);
                        iVar10 = 0;
                      }
                    }
                  }
                  else {
                    iVar10 = -1;
                  }
                  if (iVar10 == 0) {
                    uVar7 = strlen(&s_CmakeInfo);
                    if (6 < (int)(uVar7 & (int)(-uVar7 | uVar7) >> 0x1f)) {
                      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26) = 0xb;
                      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x28) = 5;
                    }
                    PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
                  }
                  else {
                    PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
                  }
                }
                else {
                  uVar7 = strlen(&s_CmakeInfo);
                  if ((uVar7 & (int)(-uVar7 | uVar7) >> 0x1f) == 0) {
                    PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
                    return 0;
                  }
                  iVar8 = strlen(&s_CmakeInfo);
                  iVar13 = 0;
                  pCVar11 = &s_CmakeInfo;
                  iVar10 = iVar8;
                  if (0 < iVar8) {
                    do {
                      if (*(char *)pCVar11 != ' ') break;
                      pCVar11 = (CmakeInfo *)&pCVar11->field_0x1;
                      iVar13 = iVar13 + 1;
                      iVar10 = iVar10 + -1;
                    } while (iVar10 != 0);
                  }
                  if (iVar13 == iVar8) {
                    PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
                    return 0;
                  }
                  iVar8 = -0x7fde1140;
                  bVar12 = false;
                  iVar10 = 0;
                  do {
                    if ((((iVar10 != *(short *)&menuPcs->field_0x86a) &&
                         (*(int *)(iVar8 + 0x1794) != 0)) && (*(char *)(iVar8 + 0x1f96) != '\x01'))
                       && (iVar13 = strcmp(&s_CmakeInfo,iVar8 + 0x17ba), iVar13 == 0)) {
                      bVar12 = true;
                      break;
                    }
                    iVar10 = iVar10 + 1;
                    iVar8 = iVar8 + 0xc30;
                  } while (iVar10 < 8);
                  if (!bVar12) {
                    iVar10 = 0;
                    iVar8 = 0;
                    do {
                      iVar13 = strcmp(*(undefined4 *)
                                       ((int)Game.game.m_cFlatDataArr[1].m_table[2].index + iVar8),
                                      &s_CmakeInfo);
                      if (iVar13 == 0) {
                        bVar12 = true;
                        break;
                      }
                      iVar10 = iVar10 + 1;
                      iVar8 = iVar8 + 4;
                    } while (iVar10 < 0x100);
                  }
                  if (!bVar12) {
                    PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
                    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 1;
                    return 1;
                  }
                  PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
                  GetWinSize__8CMenuPcsFiPsPsi(menuPcs,0x14,&local_26,&local_28,0);
                  SetMcWinInfo__8CMenuPcsFii(menuPcs,(int)local_26,(int)local_28);
                  *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 0;
                }
              }
            }
            else {
              *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26) = 0xb;
              *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x28) = 5;
              PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
            }
          }
          else {
            *(short *)(*(int *)&menuPcs->field_0x82c + 0x2a) =
                 *(short *)(*(int *)&menuPcs->field_0x82c + 0x2a) + 1;
            if (2 < *(short *)(*(int *)&menuPcs->field_0x82c + 0x2a)) {
              *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2a) = 0;
            }
            PlaySe__6CSoundFiiii(&Sound,0x5a,0x40,0x7f,0);
          }
        }
        else {
          *(short *)(*(int *)&menuPcs->field_0x82c + 0x2a) =
               *(short *)(*(int *)&menuPcs->field_0x82c + 0x2a) + -1;
          if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x2a) < 0) {
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2a) = 2;
          }
          PlaySe__6CSoundFiiii(&Sound,0x5a,0x40,0x7f,0);
        }
      }
    }
    else if ((sVar1 == 1) && ((uVar5 & 0x300) != 0)) {
      PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
      *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
    }
  }
  return 0;
}


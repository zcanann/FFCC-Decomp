// Function: CmakeVillageCtrl__8CMenuPcsFv
// Entry: 8016d940
// Size: 1940 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 CmakeVillageCtrl__8CMenuPcsFv(CMenuPcs *menuPcs)

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
  bool bVar11;
  CmakeInfo *pCVar10;
  int iVar12;
  undefined *puVar13;
  int iVar14;
  int iVar15;
  char local_18 [8];
  
  iVar14 = *(int *)&menuPcs->field_0x830;
  bVar11 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar11 = true;
  }
  if (bVar11) {
    uVar5 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar5 = Pad._8_2_;
  }
  bVar11 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar11 = true;
  }
  if (bVar11) {
    uVar6 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar6 = Pad._20_2_;
  }
  if (uVar6 != 0) {
    if ((uVar6 & 8) == 0) {
      if ((uVar6 & 4) != 0) {
        if ((int)*(short *)(iVar14 + 0x28) <
            (int)(((int)*(short *)(iVar14 + 0x26) >> 0x1f) +
                  (uint)(9 < (uint)(int)*(short *)(iVar14 + 0x26)) + 4)) {
          *(short *)(iVar14 + 0x28) = *(short *)(iVar14 + 0x28) + 1;
        }
        else {
          *(undefined2 *)(iVar14 + 0x28) = 0;
        }
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
    }
    else {
      if (*(short *)(iVar14 + 0x28) == 0) {
        if (*(short *)(iVar14 + 0x26) < 10) {
          *(undefined2 *)(iVar14 + 0x28) = 4;
        }
        else {
          *(undefined2 *)(iVar14 + 0x28) = 5;
        }
      }
      else {
        *(short *)(iVar14 + 0x28) = *(short *)(iVar14 + 0x28) + -1;
      }
      PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
    }
    if ((uVar6 & 1) == 0) {
      if ((uVar6 & 2) != 0) {
        if (*(short *)(iVar14 + 0x28) < 5) {
          if (*(short *)(iVar14 + 0x26) < 0xb) {
            *(short *)(iVar14 + 0x26) = *(short *)(iVar14 + 0x26) + 1;
          }
          else {
            *(undefined2 *)(iVar14 + 0x26) = 0;
          }
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
        else {
          PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
        }
      }
    }
    else if (*(short *)(iVar14 + 0x28) < 5) {
      if (*(short *)(iVar14 + 0x26) == 0) {
        *(undefined2 *)(iVar14 + 0x26) = 0xb;
      }
      else {
        *(short *)(iVar14 + 0x26) = *(short *)(iVar14 + 0x26) + -1;
      }
      PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
    }
    else {
      PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
    }
    if ((uVar6 & 0xf) == 0) {
      if ((uVar5 & 0x40) == 0) {
        if ((uVar5 & 0x20) == 0) {
          if ((uVar5 & 0x1000) == 0) {
            if ((uVar5 & 0x100) == 0) {
              if ((uVar5 & 0x200) != 0) {
                uVar7 = strlen(&s_CmakeInfo);
                if ((uVar7 & (int)(-uVar7 | uVar7) >> 0x1f) == 0) {
                  PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
                }
                else {
                  uVar7 = strlen(&s_CmakeInfo);
                  if ((uVar7 & (int)(-uVar7 | uVar7) >> 0x1f) == 0) {
                    iVar14 = -1;
                  }
                  else {
                    iVar14 = strlen(&s_CmakeInfo);
                    uVar9 = strlen(&s_CmakeInfo);
                    uVar7 = countLeadingZeros(uVar9);
                    if ((uVar7 >> 5 & 1) == 0) {
                      (&g_GoOutMenu.field_0x4f)[iVar14] = 0;
                    }
                    else {
                      (&g_GoOutMenu.field_0x4e)[iVar14] = 0;
                    }
                    iVar14 = 0;
                  }
                  if (iVar14 == 0) {
                    PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
                  }
                  else {
                    PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
                  }
                }
              }
            }
            else {
              sVar1 = *(short *)(iVar14 + 0x28);
              if (4 < sVar1) {
                uVar7 = strlen(&s_CmakeInfo);
                if ((uVar7 & (int)(-uVar7 | uVar7) >> 0x1f) == 0) {
                  PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
                  return 0;
                }
                iVar8 = strlen(&s_CmakeInfo);
                iVar12 = 0;
                pCVar10 = &s_CmakeInfo;
                iVar15 = iVar8;
                if (0 < iVar8) {
                  do {
                    if (*(char *)pCVar10 != ' ') break;
                    pCVar10 = (CmakeInfo *)&pCVar10->field_0x1;
                    iVar12 = iVar12 + 1;
                    iVar15 = iVar15 + -1;
                  } while (iVar15 != 0);
                }
                if (iVar12 != iVar8) {
                  memset(0x8021ff68,0,0x11);
                  strcpy(0x8021ff68,&s_CmakeInfo);
                  PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
                  *(undefined2 *)(iVar14 + 0x1e) = 1;
                  return 1;
                }
                PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
                return 0;
              }
              sVar2 = *(short *)(iVar14 + 0x2a);
              sVar3 = *(short *)(iVar14 + 0x26);
              memset(local_18,0,3);
              local_18[0] = '\0';
              puVar13 = (&PTR_s_ABCDEFGHIJKL_80215968)[(int)sVar1 + sVar2 * 5];
              iVar15 = strlen(puVar13);
              if (iVar15 != 0) {
                iVar8 = 0;
                iVar12 = 0;
                if (0 < iVar15) {
                  do {
                    if (iVar8 == sVar3) {
                      local_18[0] = puVar13[iVar12];
                      local_18[1] = 0;
                      break;
                    }
                    iVar8 = iVar8 + 1;
                    iVar12 = iVar12 + 1;
                    iVar15 = iVar15 + -1;
                  } while (iVar15 != 0);
                }
              }
              uVar7 = strlen(&s_CmakeInfo);
              uVar7 = uVar7 & (int)(-uVar7 | uVar7) >> 0x1f;
              if ((int)uVar7 < 7) {
                local_18[0] = '\0';
                iVar15 = strlen(puVar13);
                if (iVar15 != 0) {
                  iVar8 = 0;
                  iVar12 = 0;
                  if (0 < iVar15) {
                    do {
                      if (iVar8 == sVar3) {
                        local_18[0] = puVar13[iVar12];
                        local_18[1] = 0;
                        break;
                      }
                      iVar8 = iVar8 + 1;
                      iVar12 = iVar12 + 1;
                      iVar15 = iVar15 + -1;
                    } while (iVar15 != 0);
                  }
                }
                if (uVar7 == 0) {
                  strcat((char *)&s_CmakeInfo,local_18);
                  iVar15 = 0;
                }
                else {
                  uVar9 = strlen(puVar13);
                  uVar4 = countLeadingZeros(uVar9);
                  if (((uVar4 >> 5 & 1) == 0) && (6 < (int)uVar7)) {
                    iVar15 = -1;
                  }
                  else {
                    strcat((char *)&s_CmakeInfo,local_18);
                    iVar15 = 0;
                  }
                }
              }
              else {
                iVar15 = -1;
              }
              if (iVar15 == 0) {
                uVar7 = strlen(&s_CmakeInfo);
                if (6 < (int)(uVar7 & (int)(-uVar7 | uVar7) >> 0x1f)) {
                  *(undefined2 *)(iVar14 + 0x26) = 0xb;
                  *(undefined2 *)(iVar14 + 0x28) = 5;
                }
                PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
              }
              else {
                PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
              }
            }
          }
          else {
            *(undefined2 *)(iVar14 + 0x26) = 0xb;
            *(undefined2 *)(iVar14 + 0x28) = 5;
            PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
          }
        }
        else {
          *(short *)(iVar14 + 0x2a) = *(short *)(iVar14 + 0x2a) + 1;
          if (2 < *(short *)(iVar14 + 0x2a)) {
            *(undefined2 *)(iVar14 + 0x2a) = 0;
          }
          PlaySe__6CSoundFiiii(&Sound,0x5a,0x40,0x7f,0);
        }
      }
      else {
        *(short *)(iVar14 + 0x2a) = *(short *)(iVar14 + 0x2a) + -1;
        if (*(short *)(iVar14 + 0x2a) < 0) {
          *(undefined2 *)(iVar14 + 0x2a) = 2;
        }
        PlaySe__6CSoundFiiii(&Sound,0x5a,0x40,0x7f,0);
      }
    }
  }
  return 0;
}


// Function: DrawHelpMessageUS__8CMenuPcsFiP5CFontii8_GXColoriff
// Entry: 80179fc4
// Size: 3188 bytes

/* WARNING: Removing unreachable block (ram,0x8017ac24) */
/* WARNING: Removing unreachable block (ram,0x8017ac1c) */
/* WARNING: Removing unreachable block (ram,0x80179fdc) */
/* WARNING: Removing unreachable block (ram,0x80179fd4) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawHelpMessageUS__8CMenuPcsFiP5CFontii8_GXColoriff
               (double param_1,CMenuPcs *menuPcs,int param_3,CFont *param_4,undefined4 param_5,
               undefined4 param_6,undefined4 *param_7,undefined4 param_8)

{
  ushort uVar1;
  uint32_t uVar2;
  int iVar3;
  void *pvVar4;
  int iVar5;
  undefined4 uVar6;
  char cVar8;
  int iVar7;
  uint uVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  int32_t iVar13;
  undefined *puVar14;
  int iVar15;
  int unaff_r24;
  int iVar16;
  int iVar17;
  double dVar18;
  double dVar19;
  undefined4 local_2a8;
  uint local_2a4 [4];
  char acStack_294 [256];
  char local_194 [260];
  undefined8 local_90;
  undefined8 local_88;
  undefined8 local_80;
  undefined8 local_78;
  
  uVar2 = Game.game.m_scriptFoodBase[0];
  local_2a4[0] = DAT_801e36d0;
  local_2a4[1] = DAT_801e36d4;
  dVar19 = (double)FLOAT_80333654;
  local_2a4[2] = DAT_801e36d8;
  iVar11 = Game.game.m_gameWork.m_languageId - 1;
  iVar15 = 1;
  local_2a4[3] = DAT_801e36dc;
  puVar14 = (undefined *)0x0;
  SetMargin__5CFontFf(FLOAT_803335a0,param_4);
  SetShadow__5CFontFi(param_4,1);
  SetScale__5CFontFf((float)param_1,param_4);
  DrawInit__5CFontFv(param_4);
  SetTlut__5CFontFi(param_4,param_8);
  local_2a8 = *param_7;
  SetColor__5CFontF8_GXColor(param_4,&local_2a8);
  SetScale__5CFontFf(FLOAT_80333548,param_4);
  iVar16 = 500;
  if ((-1 < param_3) && (param_3 < 0x269)) {
    unaff_r24 = 3;
    iVar16 = param_3 * 3 + 0x1f5;
  }
  uVar6 = MenuPcs._236_4_;
  if (Game.game.m_gameWork.m_menuStageMode != '\0') {
    uVar6 = MenuPcs._244_4_;
  }
  pvVar4 = (void *)__nwa__FUlPQ27CMemory6CStagePci(0x200,uVar6,s_MenuUtil_cpp_801e37fc,0x8c);
  if ((pvVar4 == (void *)0x0) && (System.m_execParam != 0)) {
    Printf__7CSystemFPce
              (&System,s__s__d___Error__memory_allocation_801e380c,s_MenuUtil_cpp_801e37fc,0x8e);
  }
  iVar3 = iVar16 << 2;
  iVar17 = -1;
  for (iVar12 = iVar16; iVar12 < iVar16 + 3; iVar12 = iVar12 + 1) {
    uVar6 = *(undefined4 *)((int)Game.game.m_cFlatDataArr[1].m_table[6].index + iVar3);
    memset(pvVar4,0,0x200);
    MakeAgbString__4CMesFPcPcii(pvVar4,uVar6,0,1);
    iVar5 = strlen(pvVar4);
    iVar7 = iVar17;
    if ((iVar5 != 0) &&
       (iVar7 = drawTagString__4CMesFP5CFontPciii(param_4,uVar6,0,0,0), iVar7 < iVar17)) {
      iVar7 = iVar17;
    }
    iVar3 = iVar3 + 4;
    iVar17 = iVar7;
  }
  __dla__FPv(pvVar4);
  if ((param_3 < 0x259) || (0x268 < param_3)) {
    if (param_3 == 0x209) {
      puVar14 = (undefined *)GetSkillStr__8CMenuPcsFi(menuPcs,0);
    }
    else if (param_3 == 0x20d) {
      puVar14 = (undefined *)GetSkillStr__8CMenuPcsFi(menuPcs,1);
    }
    else if (param_3 == 0x211) {
      puVar14 = (undefined *)GetSkillStr__8CMenuPcsFi(menuPcs,2);
    }
    else {
      puVar14 = &DAT_80333658;
    }
    if (((param_3 == 0x209) || (param_3 == 0x20d)) || (param_3 == 0x211)) {
      local_194[0] = '\0';
    }
    else {
      MakeArtItemName__5CGameFPcii(&Game.game,local_194,param_3,1);
      iVar3 = strlen(local_194);
      if ((iVar3 != 0) && (local_194[0] != '\0')) {
        local_194[0] = _toupperLatin1();
      }
    }
    dVar19 = (double)FLOAT_80333620;
  }
  else {
    iVar15 = 0;
  }
  if ((param_3 < 1) || (0x44 < param_3)) {
    if ((param_3 < 0x45) || (0x7e < param_3)) {
      if ((param_3 < 0x7f) || (0x9e < param_3)) {
        iVar3 = 0;
      }
      else {
        iVar3 = 0x7f;
      }
    }
    else {
      iVar3 = 0x45;
    }
  }
  else {
    iVar3 = 1;
  }
  if (iVar3 == 0) {
    iVar11 = 3;
    uVar6 = MenuPcs._236_4_;
    if (Game.game.m_gameWork.m_menuStageMode != '\0') {
      uVar6 = MenuPcs._244_4_;
    }
    pvVar4 = (void *)__nwa__FUlPQ27CMemory6CStagePci(0x200,uVar6,s_MenuUtil_cpp_801e37fc,0x23d);
    if ((pvVar4 == (void *)0x0) && (System.m_execParam != 0)) {
      Printf__7CSystemFPce
                (&System,s__s__d___Error__memory_allocation_801e380c,s_MenuUtil_cpp_801e37fc,0x23f);
    }
    iVar12 = 0;
    iVar3 = iVar16;
    do {
      iVar13 = Game.game.m_cFlatDataArr[1].m_table[6].index[iVar16 + iVar12];
      memset(pvVar4,0,0x200);
      MakeAgbString__4CMesFPcPcii(pvVar4,iVar13,0,1);
      iVar7 = strlen(pvVar4);
      if ((iVar7 == 0) && (iVar11 = iVar11 + -1, iVar3 == iVar16 + iVar12)) {
        iVar3 = iVar3 + 1;
      }
      iVar12 = iVar12 + 1;
    } while (iVar12 < unaff_r24);
    __dla__FPv(pvVar4);
    uVar9 = local_2a4[iVar11 + iVar15 + -1];
    if (iVar15 != 0) {
      SetPosX__5CFontFf(FLOAT_8033357c,param_4);
      local_78 = (double)CONCAT44(0x43300000,uVar9 ^ 0x80000000);
      SetPosY__5CFontFf((float)(local_78 - DOUBLE_80333640),param_4);
      Draw__5CFontFPc(param_4,local_194);
      Draw__5CFontFPc(param_4,puVar14);
      local_80 = (double)CONCAT44(0x43300000,uVar9 ^ 0x80000000);
      uVar9 = (uint)((double)(float)(local_80 - DOUBLE_80333640) + dVar19);
      local_88 = (double)(longlong)(int)uVar9;
    }
    dVar18 = DOUBLE_80333640;
    for (iVar15 = 0; iVar15 < iVar11; iVar15 = iVar15 + 1) {
      local_78 = (double)CONCAT44(0x43300000,0x140U - iVar17 / 2 ^ 0x80000000);
      iVar13 = Game.game.m_cFlatDataArr[1].m_table[6].index[iVar3 + iVar15];
      SetPosX__5CFontFf((float)(local_78 - dVar18),param_4);
      local_80 = (double)(CONCAT44(0x43300000,uVar9) ^ 0x80000000);
      SetPosY__5CFontFf((float)(local_80 - dVar18),param_4);
      drawTagString__4CMesFP5CFontPciii(param_4,iVar13,1,0,0);
      local_88 = (double)(CONCAT44(0x43300000,uVar9) ^ 0x80000000);
      uVar9 = (uint)((double)(float)(local_88 - dVar18) + dVar19);
      local_90 = (double)(longlong)(int)uVar9;
    }
  }
  else {
    uVar10 = local_2a4[iVar15 + 2];
    uVar9 = uVar10;
    if (iVar15 != 0) {
      SetPosX__5CFontFf(FLOAT_8033357c,param_4);
      local_90 = (double)CONCAT44(0x43300000,uVar10 ^ 0x80000000);
      SetPosY__5CFontFf((float)(local_90 - DOUBLE_80333640),param_4);
      Draw__5CFontFPc(param_4,local_194);
      Draw__5CFontFPc(param_4,puVar14);
      local_88 = (double)CONCAT44(0x43300000,uVar10 ^ 0x80000000);
      uVar9 = (uint)((double)(float)(local_88 - DOUBLE_80333640) + dVar19);
    }
    iVar15 = 0;
    dVar18 = DOUBLE_80333640;
    do {
      local_80 = (double)CONCAT44(0x43300000,0x140U - iVar17 / 2 ^ 0x80000000);
      iVar13 = Game.game.m_cFlatDataArr[1].m_table[6].index[iVar16 + iVar15];
      SetPosX__5CFontFf((float)(local_80 - dVar18),param_4);
      local_88 = (double)(CONCAT44(0x43300000,uVar9) ^ 0x80000000);
      SetPosY__5CFontFf((float)(local_88 - dVar18),param_4);
      drawTagString__4CMesFP5CFontPciii(param_4,iVar13,1,0,0);
      iVar15 = iVar15 + 1;
      local_90 = (double)CONCAT44(0x43300000,uVar9 ^ 0x80000000);
      uVar9 = (uint)((double)(float)(local_90 - dVar18) + dVar19);
      local_78 = (double)(longlong)(int)uVar9;
    } while (iVar15 < unaff_r24);
    iVar15 = Game.game.unkCFlatData0[2] + param_3 * 0x48;
    uVar1 = *(ushort *)(iVar15 + 4);
    if ((uVar1 & 0x100) == 0) {
      if ((uVar1 & 0x200) == 0) {
        if ((uVar1 & 0x400) == 0) {
          if ((uVar1 & 0x800) == 0) {
            if ((uVar1 & 0x1000) == 0) {
              if ((uVar1 & 0x2000) != 0) {
                strcpy(acStack_294,&DAT_80333658);
              }
            }
            else {
              strcpy(acStack_294,&DAT_80333658);
            }
          }
          else {
            strcpy(acStack_294,(&PTR_s_Defence__80215a4c)[iVar11 * 0x14]);
          }
        }
        else {
          strcpy(acStack_294,(&PTR_s_Defence__80215a4c)[iVar11 * 0x14]);
        }
      }
      else {
        strcpy(acStack_294,(&PTR_s_Defence__80215a4c)[iVar11 * 0x14]);
      }
    }
    else {
      strcpy(acStack_294,(&PTR_s_Strength__80215a48)[iVar11 * 0x14]);
    }
    SetPosX__5CFontFf(FLOAT_8033357c,param_4);
    local_78 = (double)CONCAT44(0x43300000,uVar10 ^ 0x80000000);
    iVar11 = (int)(dVar19 + (double)(float)(local_78 - DOUBLE_80333640));
    local_80 = (double)(longlong)iVar11;
    local_88 = (double)(CONCAT44(0x43300000,iVar11) ^ 0x80000000);
    SetPosY__5CFontFf((float)(local_88 - DOUBLE_80333640),param_4);
    if ((*(ushort *)(iVar15 + 4) & 0x1000) == 0) {
      strcat(acStack_294,&DAT_8033366c);
      Draw__5CFontFPc(param_4,acStack_294);
      dVar19 = (double)GetWidth__5CFontFPc(param_4,acStack_294);
      local_78 = 4.5036017748542e+15;
      uVar9 = (uint)((float)(4.5036017748542e+15 - DOUBLE_80333640) +
                    (float)((double)FLOAT_803335a0 + dVar19));
      local_80 = (double)(longlong)(int)uVar9;
      SetTlut__5CFontFi(param_4,1);
      local_88 = (double)CONCAT44(0x43300000,uVar9 ^ 0x80000000);
      SetPosX__5CFontFf((float)(local_88 - DOUBLE_80333640),param_4);
      sprintf(acStack_294,&DAT_80333670,*(undefined2 *)(iVar15 + 6));
      Draw__5CFontFPc(param_4,acStack_294);
      if ((*(short *)&menuPcs->field_0x864 == 2) &&
         (iVar11 = *(int *)&menuPcs->field_0x82c, *(short *)(iVar11 + 0x30) == 1)) {
        uVar1 = *(ushort *)(iVar15 + 4);
        if ((uVar1 & 0x1000) == 0) {
          iVar16 = -1;
          if ((uVar1 & 0x100) == 0) {
            if ((uVar1 & 0x400) == 0) {
              if ((uVar1 & 0x800) == 0) {
                if ((uVar1 & 0x200) == 0) {
                  if ((uVar1 & 0x1000) == 0) {
                    if ((uVar1 & 0x2000) != 0) {
                      iVar16 = 3;
                    }
                  }
                  else {
                    iVar16 = 3;
                  }
                }
                else {
                  iVar16 = 2;
                }
              }
              else {
                iVar16 = 2;
              }
            }
            else {
              iVar16 = 1;
            }
          }
          else {
            iVar16 = 0;
          }
          iVar16 = (int)*(short *)(uVar2 + *(short *)(uVar2 + iVar16 * 2 + 0xac) * 2 + 0xb6);
          cVar8 = ChkEquipActive__8CMenuPcsFi
                            (menuPcs,(int)*(short *)(iVar11 + 0x28) + (int)*(short *)(iVar11 + 0x34)
                            );
          if (cVar8 != '\0') {
            if (iVar16 == -1) {
              uVar10 = 0;
            }
            else {
              uVar10 = (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar16 * 0x48 + 6);
            }
            iVar16 = *(ushort *)(iVar15 + 6) - uVar10;
            dVar19 = (double)GetWidth__5CFontFPc(param_4,acStack_294);
            local_78 = (double)CONCAT44(0x43300000,uVar9 ^ 0x80000000);
            iVar11 = (int)((float)(local_78 - DOUBLE_80333640) +
                          (float)((double)FLOAT_803335a0 + dVar19));
            local_80 = (double)(longlong)iVar11;
            local_88 = (double)(CONCAT44(0x43300000,iVar11) ^ 0x80000000);
            SetPosX__5CFontFf((float)(local_88 - DOUBLE_80333640),param_4);
            if (iVar16 < 0) {
              SetTlut__5CFontFi(param_4,3);
            }
            else {
              SetTlut__5CFontFi(param_4,9);
            }
            sprintf(acStack_294,&DAT_80333674,iVar16);
            if (iVar16 != 0) {
              Draw__5CFontFPc(param_4,acStack_294);
            }
          }
        }
      }
      dVar18 = (double)param_4->posX;
      dVar19 = (double)GetWidth__5CFontFPc(param_4,&DAT_8033366c);
      local_78 = (double)(longlong)(int)(dVar18 + dVar19);
      local_80 = (double)(CONCAT44(0x43300000,(int)(dVar18 + dVar19)) ^ 0x80000000);
      SetPosX__5CFontFf((float)(local_80 - DOUBLE_80333640),param_4);
      if ((((*(ushort *)(iVar15 + 4) & 0x1000) == 0) && (*(ushort *)(iVar15 + 8) != 0)) &&
         (*(ushort *)(iVar15 + 8) < 0x14)) {
        SetTlut__5CFontFi(param_4,4);
        uVar6 = GetAttrStr__8CMenuPcsFi(menuPcs,(uint)*(ushort *)(iVar15 + 8));
        strcpy(acStack_294,uVar6);
        Draw__5CFontFPc(param_4,acStack_294);
        SetTlut__5CFontFi(param_4,9);
        if ((*(ushort *)(iVar15 + 8) != 0) && (*(ushort *)(iVar15 + 8) < 9)) {
          sprintf(acStack_294,&DAT_8033367c,&DAT_80333660);
          Draw__5CFontFPc(param_4,acStack_294);
        }
      }
    }
    else {
      uVar9 = (uint)*(ushort *)(iVar15 + 8);
      if ((uVar9 != 0) && (uVar9 < 0x14)) {
        uVar6 = GetAttrStr__8CMenuPcsFi(menuPcs,uVar9);
        strcpy(acStack_294,uVar6);
        SetTlut__5CFontFi(param_4,4);
        Draw__5CFontFPc(param_4,acStack_294);
        dVar19 = (double)GetWidth__5CFontFPc(param_4,acStack_294);
        local_78 = 4.5036017748542e+15;
        iVar11 = (int)((float)(4.5036017748542e+15 - DOUBLE_80333640) +
                      (float)((double)FLOAT_803335a0 + dVar19));
        local_80 = (double)(longlong)iVar11;
        local_88 = (double)(CONCAT44(0x43300000,iVar11) ^ 0x80000000);
        SetPosX__5CFontFf((float)(local_88 - DOUBLE_80333640),param_4);
        SetTlut__5CFontFi(param_4,9);
        uVar1 = *(ushort *)(iVar15 + 8);
        if ((uVar1 == 0) || (8 < uVar1)) {
          if (((uVar1 == 0xb) || (uVar1 == 0x11)) || (uVar1 == 0x12)) {
            sprintf(acStack_294,&DAT_80333664,0x2b,*(undefined2 *)(iVar15 + 6));
          }
          else {
            if ((1 < (ushort)(uVar1 - 9)) && (uVar1 != 0xc)) {
              return;
            }
            sprintf(acStack_294,&DAT_80333664,0x2d,*(undefined2 *)(iVar15 + 6));
            SetTlut__5CFontFi(param_4,3);
          }
        }
        else {
          sprintf(acStack_294,&DAT_8033365c,&DAT_80333660);
        }
        Draw__5CFontFPc(param_4,acStack_294);
      }
    }
  }
  return;
}


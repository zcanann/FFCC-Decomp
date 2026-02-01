// Function: DrawSelectOpenAnim__8CMenuPcsFv
// Entry: 80135258
// Size: 2824 bytes

/* WARNING: Removing unreachable block (ram,0x80135d44) */
/* WARNING: Removing unreachable block (ram,0x80135d3c) */
/* WARNING: Removing unreachable block (ram,0x80135d34) */
/* WARNING: Removing unreachable block (ram,0x80135d2c) */
/* WARNING: Removing unreachable block (ram,0x80135d24) */
/* WARNING: Removing unreachable block (ram,0x80135288) */
/* WARNING: Removing unreachable block (ram,0x80135280) */
/* WARNING: Removing unreachable block (ram,0x80135278) */
/* WARNING: Removing unreachable block (ram,0x80135270) */
/* WARNING: Removing unreachable block (ram,0x80135268) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawSelectOpenAnim__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  void *ptr;
  void *ptr_00;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  short *psVar7;
  uint uVar8;
  int32_t iVar9;
  int iVar10;
  int iVar11;
  CFont *pCVar12;
  short *unaff_r28;
  int iVar13;
  int unaff_r30;
  int iVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  double dVar20;
  undefined4 local_1d0;
  undefined4 local_1cc;
  undefined auStack_1c8 [4];
  undefined4 local_1c4;
  undefined auStack_1c0 [4];
  undefined4 local_1bc;
  undefined4 local_1b8;
  undefined4 local_1b4;
  undefined auStack_1a4 [260];
  undefined8 local_a0;
  undefined8 local_98;
  undefined4 local_90;
  uint uStack_8c;
  undefined8 local_88;
  
  if (*(char *)(*(int *)&menuPcs->field_0x82c + 0xb) != '\0') {
    iVar13 = *DAT_8032eea8;
    DrawInit__8CMenuPcsFv(menuPcs);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    iVar11 = 0;
    iVar1 = 0;
    iVar4 = 0;
    psVar7 = (short *)0x0;
    for (iVar10 = 0; iVar10 < **(short **)&menuPcs->field_0x84c; iVar10 = iVar10 + 1) {
      unaff_r28 = (short *)((int)*(short **)&menuPcs->field_0x84c + iVar1 + 8);
      iVar14 = *(int *)(unaff_r28 + 0xe);
      if ((-1 < iVar14) || (iVar14 != -1)) {
        if (iVar14 == -3) {
          uStack_8c = (int)unaff_r28[2] ^ 0x80000000;
          local_a0 = (double)CONCAT44(0x43300000,(int)*unaff_r28 ^ 0x80000000);
          local_98 = (double)CONCAT44(0x43300000,(int)unaff_r28[1] ^ 0x80000000);
          local_90 = 0x43300000;
          local_88 = (double)CONCAT44(0x43300000,(int)unaff_r28[3] ^ 0x80000000);
          DrawBonusFrame__8CMenuPcsFfffff
                    ((double)(float)(local_a0 - DOUBLE_80331e88),
                     (double)(float)(local_98 - DOUBLE_80331e88),
                     (double)(float)((double)CONCAT44(0x43300000,uStack_8c) - DOUBLE_80331e88),
                     (double)(float)(local_88 - DOUBLE_80331e88),(double)*(float *)(unaff_r28 + 8),
                     menuPcs);
          iVar4 = *(int *)(unaff_r28 + 0xe);
        }
        else if (iVar14 == -4) {
          if (psVar7 == (short *)0x0) {
            psVar7 = unaff_r28;
          }
          DrawArtiBase__8CMenuPcsFPQ28CMenuPcs5Sprt2f
                    ((double)*(float *)(unaff_r28 + 8),menuPcs,unaff_r28);
          iVar4 = *(int *)(unaff_r28 + 0xe);
        }
        else if (iVar14 == -2) {
          if (iVar11 < iVar13) {
            iVar5 = 0;
            piVar2 = DAT_8032eea8;
            iVar14 = unaff_r30;
            iVar4 = iVar13;
            if (0 < iVar13) {
              do {
                iVar14 = iVar5;
                if (iVar11 == piVar2[0xd]) break;
                piVar2 = piVar2 + 0xb;
                iVar5 = iVar5 + 1;
                iVar4 = iVar4 + -1;
                iVar14 = unaff_r30;
              } while (iVar4 != 0);
            }
            iVar4 = DAT_8032eea8[iVar14 * 0xb + 8];
            SetProjection__8CMenuPcsFi(menuPcs,iVar11);
          }
          else {
            iVar14 = iVar11 + iVar13;
            iVar4 = *(int *)((int)(&menuPcs->m_cameraMatrix + 1) + iVar14 * 4);
            if (iVar4 == 0) {
              iVar11 = iVar11 + 1;
              iVar4 = -2;
              unaff_r30 = iVar14;
              goto LAB_801355f8;
            }
            SetProjection__8CMenuPcsFi(menuPcs,iVar14);
          }
          SetLight__8CMenuPcsFi(menuPcs,1);
          uVar6 = *(undefined4 *)(iVar4 + 8);
          *(undefined4 *)(iVar4 + 8) = 0x300543;
          Draw__Q29CCharaPcs7CHandleFi(iVar4,5);
          *(undefined4 *)(iVar4 + 8) = uVar6;
          if (iVar13 <= iVar11) {
            DrawMenuIdx__8CPartPcsFi
                      (&PartPcs,*(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar14 * 0x524 + 4))
            ;
          }
          RestoreProjection__8CMenuPcsFv(menuPcs);
          iVar4 = *(int *)(unaff_r28 + 0xe);
          iVar11 = iVar11 + 1;
          unaff_r30 = iVar14;
        }
        else {
          if (iVar4 < 0) {
            DrawInit__8CMenuPcsFv(menuPcs);
            SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
          }
          local_88 = (double)(longlong)(int)(FLOAT_80331e98 * *(float *)(unaff_r28 + 8));
          local_1b4 = CONCAT31(0xffffff,(char)(int)(FLOAT_80331e98 * *(float *)(unaff_r28 + 8)));
          local_1b8 = local_1b4;
          GXSetChanMatColor(4,&local_1b8);
          SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,*(undefined4 *)(unaff_r28 + 0xe));
          if (*(int *)(unaff_r28 + 0xe) == 0x20) {
            _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,1,5);
          }
          uStack_8c = (int)unaff_r28[1] ^ 0x80000000;
          local_88 = (double)(CONCAT44(0x43300000,(int)*unaff_r28) ^ 0x80000000);
          local_90 = 0x43300000;
          local_98 = (double)CONCAT44(0x43300000,(int)unaff_r28[2] ^ 0x80000000);
          local_a0 = (double)CONCAT44(0x43300000,(int)unaff_r28[3] ^ 0x80000000);
          DrawRect__8CMenuPcsFUlfffffffff
                    ((double)((float)(local_88 - DOUBLE_80331e88) + *(float *)(unaff_r28 + 0x18)),
                     (double)((float)((double)CONCAT44(0x43300000,uStack_8c) - DOUBLE_80331e88) +
                             *(float *)(unaff_r28 + 0x1a)),
                     (double)(float)(local_98 - DOUBLE_80331e88),
                     (double)(float)(local_a0 - DOUBLE_80331e88),(double)*(float *)(unaff_r28 + 4),
                     (double)*(float *)(unaff_r28 + 6),(double)*(float *)(unaff_r28 + 10),
                     (double)*(float *)(unaff_r28 + 10),&MenuPcs,0);
          if (*(int *)(unaff_r28 + 0xe) == 0x20) {
            _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
          }
          iVar4 = *(int *)(unaff_r28 + 0xe);
        }
      }
LAB_801355f8:
      iVar1 = iVar1 + 0x40;
    }
    dVar18 = (double)*(float *)(psVar7 + 8);
    if (DOUBLE_80331e90 < dVar18) {
      _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
      local_88 = (double)(longlong)(int)((double)FLOAT_80331e98 * dVar18);
      local_1d0 = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80331e98 * dVar18));
      local_1cc = local_1d0;
      GXSetChanMatColor(4,&local_1cc);
      SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
      SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x23);
      uVar8 = 0;
      iVar1 = *DAT_8032eea8;
      piVar2 = DAT_8032eea8;
      if (0 < iVar1) {
        do {
          if (-1 < piVar2[0x10]) {
            uVar8 = uVar8 | 1 << piVar2[0x10];
          }
          piVar2 = piVar2 + 0xb;
          iVar1 = iVar1 + -1;
        } while (iVar1 != 0);
      }
      iVar4 = 0;
      iVar1 = 0;
      do {
        if ((uVar8 & 1 << iVar4) != 0) {
          DrawRect__8CMenuPcsFUlfffffffff
                    ((double)(*(float *)(DAT_8032eeb0 + iVar1 + 8) + FLOAT_80331e9c),
                     (double)(*(float *)(DAT_8032eeb0 + iVar1 + 0xc) + FLOAT_80331ea0),
                     (double)FLOAT_80331ea4,(double)FLOAT_80331ea8,(double)FLOAT_80331eac,
                     (double)FLOAT_80331eac,(double)FLOAT_80331eb0,(double)FLOAT_80331eb0,&MenuPcs,0
                    );
        }
        iVar4 = iVar4 + 1;
        iVar1 = iVar1 + 8;
      } while (iVar4 < 8);
    }
    DrawInit__8CMenuPcsFv(menuPcs);
    pCVar12 = *(CFont **)&menuPcs->field_0xf8;
    SetMargin__5CFontFf(FLOAT_80331eb0,pCVar12);
    SetShadow__5CFontFi(pCVar12,1);
    SetScale__5CFontFf(FLOAT_80331f38,pCVar12);
    SetTlut__5CFontFi(pCVar12,7);
    DrawInit__5CFontFv(pCVar12);
    iVar10 = 0;
    iVar4 = 0;
    iVar1 = 0;
    while( true ) {
      psVar7 = *(short **)&menuPcs->field_0x84c;
      iVar11 = (int)*psVar7;
      if ((iVar11 <= iVar4) || (iVar13 <= iVar10)) break;
      unaff_r28 = (short *)((int)psVar7 + iVar1 + 8);
      iVar11 = unaff_r30;
      if (*(int *)(unaff_r28 + 0xe) == -1) {
        local_88 = (double)(longlong)(int)(FLOAT_80331e98 * *(float *)(unaff_r28 + 8));
        puVar3 = (undefined4 *)
                 __ct__6CColorFUcUcUcUc
                           (auStack_1c0,0xff,0xff,0xff,
                            (int)(FLOAT_80331e98 * *(float *)(unaff_r28 + 8)));
        local_1bc = *puVar3;
        SetColor__5CFontF8_GXColor(pCVar12,&local_1bc);
        iVar5 = 0;
        piVar2 = DAT_8032eea8;
        iVar14 = iVar13;
        if (0 < iVar13) {
          do {
            iVar11 = iVar5;
            if (iVar10 == piVar2[0xd]) break;
            piVar2 = piVar2 + 0xb;
            iVar5 = iVar5 + 1;
            iVar14 = iVar14 + -1;
            iVar11 = unaff_r30;
          } while (iVar14 != 0);
        }
        if (iVar10 < iVar13) {
          strcpy(auStack_1a4,Game.game.m_scriptFoodBase[DAT_8032eea8[iVar11 * 0xb + 7]] + 0x3ca);
        }
        uStack_8c = (int)unaff_r28[1] ^ 0x80000000;
        local_88 = (double)(CONCAT44(0x43300000,(int)*unaff_r28) ^ 0x80000000);
        local_90 = 0x43300000;
        dVar18 = (double)((float)((double)CONCAT44(0x43300000,uStack_8c) - DOUBLE_80331e88) +
                         *(float *)(unaff_r28 + 0x1a));
        if (iVar10 < iVar13) {
          dVar18 = (double)(float)(dVar18 - (double)FLOAT_80331f3c);
        }
        SetPosX__5CFontFf((float)(local_88 - DOUBLE_80331e88) + *(float *)(unaff_r28 + 0x18),pCVar12
                         );
        SetPosY__5CFontFf((float)(dVar18 - (double)FLOAT_80331f3c),pCVar12);
        Draw__5CFontFPc(pCVar12,auStack_1a4);
        iVar10 = iVar10 + 1;
      }
      iVar1 = iVar1 + 0x40;
      iVar4 = iVar4 + 1;
      unaff_r30 = iVar11;
    }
    if ((*(short *)(*(int *)&menuPcs->field_0x82c + 0x1c) == 4) &&
       (0 < *(short *)((int)DAT_8032eea8 + *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) * 2 + 10
                      ))) {
      iVar1 = 0;
      if (0 < iVar11) {
        do {
          unaff_r28 = (short *)((int)psVar7 + iVar1 + 8);
          if (*(int *)(unaff_r28 + 0xe) == -3) break;
          iVar1 = iVar1 + 0x40;
          iVar11 = iVar11 + -1;
        } while (iVar11 != 0);
      }
      pCVar12 = *(CFont **)&menuPcs->field_0xfc;
      SetMargin__5CFontFf(FLOAT_80331eb0,pCVar12);
      SetShadow__5CFontFi(pCVar12,0);
      SetScaleX__5CFontFf(FLOAT_80331f40,pCVar12);
      SetScaleY__5CFontFf(FLOAT_80331f44,pCVar12);
      DrawInit__5CFontFv(pCVar12);
      puVar3 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_1c8,0xff,0xff,0xff,0xff);
      local_1c4 = *puVar3;
      SetColor__5CFontF8_GXColor(pCVar12,&local_1c4);
      uStack_8c = (int)*unaff_r28 ^ 0x80000000;
      local_88 = (double)CONCAT44(0x43300000,(int)unaff_r28[2] ^ 0x80000000);
      local_90 = 0x43300000;
      iVar1 = (int)*(short *)((int)DAT_8032eea8 +
                             *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) * 2 + 10);
      local_98 = (double)CONCAT44(0x43300000,(int)unaff_r28[3] ^ 0x80000000);
      iVar9 = Game.game.m_cFlatDataArr[1].m_table[0].index[iVar1 * 5 + 4];
      local_a0 = (double)CONCAT44(0x43300000,(int)unaff_r28[1] ^ 0x80000000);
      dVar16 = (double)(float)((local_88 - DOUBLE_80331e88) * DOUBLE_80331e78 +
                              ((double)CONCAT44(0x43300000,uStack_8c) - DOUBLE_80331e88));
      dVar17 = (double)(float)((local_98 - DOUBLE_80331e88) * DOUBLE_80331e78 +
                              (local_a0 - DOUBLE_80331e88));
      dVar18 = (double)GetWidth__5CFontFPc(pCVar12,iVar9);
      SetPosX__5CFontFf((float)-(dVar18 * DOUBLE_80331e78 - dVar16),pCVar12);
      SetPosY__5CFontFf((float)(dVar17 - (double)FLOAT_80331f48) - FLOAT_80331f3c,pCVar12);
      Draw__5CFontFPc(pCVar12,iVar9);
      ptr = (void *)__nwa__FUlPQ27CMemory6CStagePci
                              (0x200,MenuPcs._236_4_,s_33bonus_menu_cpp_801dd586 + 2,0xa9c);
      if ((ptr == (void *)0x0) && (System.m_execParam != 0)) {
        Printf__7CSystemFPce
                  (&System,s__s__d___Error__memory_allocation_801dd598,
                   s_33bonus_menu_cpp_801dd586 + 2,0xa9f);
      }
      memset(ptr,0,0x200);
      ptr_00 = (void *)__nwa__FUlPQ27CMemory6CStagePci
                                 (0x200,MenuPcs._236_4_,s_33bonus_menu_cpp_801dd586 + 2,0xaa5);
      if ((ptr_00 == (void *)0x0) && (System.m_execParam != 0)) {
        Printf__7CSystemFPce
                  (&System,s__s__d___Error__memory_allocation_801dd598,
                   s_33bonus_menu_cpp_801dd586 + 2,0xaa8);
      }
      memset(ptr_00,0,0x200);
      strcpy(ptr,Game.game.m_cFlatDataArr[1].m_table[6].index[iVar1]);
      MakeAgbString__4CMesFPcPcii(ptr_00,ptr,0,0);
      strlen(ptr_00);
      iVar1 = 0;
      dVar19 = (double)FLOAT_80331f3c;
      dVar20 = (double)FLOAT_80331f58;
      dVar18 = (double)(float)(dVar17 - (double)FLOAT_80331f4c) - (double)FLOAT_80331f50;
      dVar17 = DOUBLE_80331e78;
      while( true ) {
        dVar18 = (double)(float)dVar18;
        if (iVar1 == 0) {
          iVar4 = strtok(ptr_00,&DAT_80331f54);
        }
        else {
          iVar4 = strtok(0,&DAT_80331f54);
        }
        if (iVar4 == 0) break;
        dVar15 = (double)GetWidth__5CFontFPc(pCVar12,iVar4);
        SetPosX__5CFontFf((float)-(dVar15 * dVar17 - dVar16),pCVar12);
        SetPosY__5CFontFf((float)(dVar18 - dVar19),pCVar12);
        Draw__5CFontFPc(pCVar12,iVar4);
        dVar18 = dVar18 + dVar20;
        iVar1 = iVar1 + 1;
      }
      __dla__FPv(ptr);
      __dla__FPv(ptr_00);
    }
    DrawInit__8CMenuPcsFv(menuPcs);
    if ((*(short *)(*(int *)&menuPcs->field_0x848 + 10) != 3) &&
       (DrawMcWin__8CMenuPcsFss(menuPcs,0xffff,1),
       *(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1)) {
      DrawMcWinMess__8CMenuPcsFii(menuPcs,0x18,1);
      DrawInit__8CMenuPcsFv(menuPcs);
      local_88 = (double)(CONCAT44(0x43300000,
                                   (int)*(short *)(*(int *)&menuPcs->field_0x848 + 2) +
                                   *(short *)(*(int *)&menuPcs->field_0x848 + 6) + -0x3e) ^
                         0x80000000);
      dVar18 = (double)(float)(local_88 - DOUBLE_80331e88);
      uStack_8c = GetYesNoXPos__8CMenuPcsFi
                            (menuPcs,(int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x28));
      uStack_8c = uStack_8c ^ 0x80000000;
      local_a0 = (double)(longlong)(int)dVar18;
      local_90 = 0x43300000;
      iVar1 = (int)((double)CONCAT44(0x43300000,uStack_8c) - DOUBLE_80331e88);
      local_98 = (double)(longlong)iVar1;
      DrawCursor__8CMenuPcsFiif((double)FLOAT_80331eb0,menuPcs,iVar1,(int)dVar18);
    }
  }
  return;
}


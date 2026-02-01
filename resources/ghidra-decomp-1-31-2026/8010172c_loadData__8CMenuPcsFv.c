// Function: loadData__8CMenuPcsFv
// Entry: 8010172c
// Size: 6000 bytes

/* WARNING: Removing unreachable block (ram,0x80102e80) */
/* WARNING: Removing unreachable block (ram,0x8010173c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void loadData__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  undefined4 *puVar1;
  float fVar2;
  undefined4 uVar3;
  short sVar4;
  float fVar5;
  float fVar6;
  byte bVar7;
  CCharaPcsCHandle *pCVar8;
  undefined4 *puVar9;
  uint32_t *puVar10;
  uint uVar11;
  char *pcVar12;
  CFileCHandle *fileHandle;
  CTextureSet *textureSet;
  undefined4 uVar13;
  undefined4 *puVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  uint uVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  CGBaseObj *pCVar25;
  undefined *puVar26;
  CMenuPcs *pCVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  int iVar31;
  int iVar32;
  float *pfVar33;
  int iVar34;
  int iVar35;
  int iVar36;
  int iVar37;
  int iVar38;
  int iVar39;
  short *psVar40;
  int iVar41;
  uint *puVar42;
  int iVar43;
  double dVar44;
  undefined4 local_408 [10];
  undefined4 local_3e0;
  undefined4 local_3dc;
  undefined4 local_3d8;
  undefined4 local_3d4;
  undefined4 local_3d0;
  CGBaseObj *local_3cc;
  CGBaseObj *local_3c8;
  undefined4 local_3c4;
  undefined4 local_3c0;
  float local_3bc;
  float local_3b8;
  undefined local_3b4;
  undefined4 local_3b0;
  undefined local_3ac;
  undefined local_3ab;
  undefined local_3aa;
  undefined4 local_3a8;
  undefined4 local_3a4;
  undefined4 local_3a0;
  undefined4 local_39c;
  undefined2 local_398;
  undefined local_396;
  undefined local_395;
  undefined4 local_374;
  undefined4 local_370;
  undefined4 local_36c;
  undefined4 local_368;
  undefined4 local_364;
  CGBaseObj *local_360;
  CGBaseObj *local_35c;
  undefined4 local_358;
  undefined4 local_354;
  float local_350;
  float local_34c;
  undefined local_348;
  undefined4 local_344;
  undefined local_340;
  undefined local_33f;
  undefined local_33e;
  undefined4 local_33c;
  undefined4 local_338;
  undefined4 local_334;
  undefined4 local_330;
  undefined2 local_32c;
  undefined local_32a;
  undefined local_329;
  undefined4 local_308;
  undefined4 local_304;
  undefined4 local_300;
  undefined4 local_2fc;
  undefined4 local_2f8;
  CGBaseObj *local_2f4;
  CGBaseObj *local_2f0;
  undefined4 local_2ec;
  undefined4 local_2e8;
  float local_2e4;
  float local_2e0;
  undefined local_2dc;
  undefined4 local_2d8;
  undefined local_2d4;
  undefined local_2d3;
  undefined local_2d2;
  undefined4 local_2d0;
  undefined4 local_2cc;
  undefined4 local_2c8;
  undefined4 local_2c4;
  undefined2 local_2c0;
  undefined local_2be;
  undefined local_2bd;
  undefined4 local_29c;
  undefined4 local_298;
  undefined4 local_294;
  undefined4 local_290;
  undefined4 local_28c;
  CGBaseObj *local_288;
  CGBaseObj *local_284;
  undefined4 local_280;
  undefined4 local_27c;
  float local_278;
  float local_274;
  undefined local_270;
  undefined4 local_26c;
  undefined local_268;
  undefined local_267;
  undefined local_266;
  undefined4 local_264;
  undefined4 local_260;
  undefined4 local_25c;
  undefined4 local_258;
  undefined2 local_254;
  undefined local_252;
  undefined local_251;
  undefined4 uStack_234;
  undefined4 local_230 [20];
  undefined auStack_1e0 [128];
  undefined auStack_160 [256];
  undefined4 local_60;
  uint uStack_5c;
  
  *(undefined2 *)&menuPcs->field_0x86c = 0;
  SetControllerMode__8GbaQueueFi(&GbaQue,1);
  loadTexture__8CMenuPcsFPPciiPQ28CMenuPcs4CTmpiii
            (menuPcs,&PTR_s_world_80210b74,2,3,&DAT_80210b98,0x16,0x2f,0);
  iVar36 = 0;
  psVar40 = &DAT_801dc168;
  *(undefined4 *)&menuPcs->field_0x774 = 0;
  *(undefined4 *)&menuPcs->field_0x778 = 0;
  *(undefined4 *)&menuPcs->field_0x77c = 0;
  *(undefined4 *)&menuPcs->field_0x780 = 0;
  *(undefined4 *)&menuPcs->field_0x784 = 0;
  *(undefined4 *)&menuPcs->field_0x788 = 0;
  *(undefined4 *)&menuPcs->field_0x78c = 0;
  *(undefined4 *)&menuPcs->field_0x790 = 0;
  *(undefined4 *)&menuPcs->field_0x794 = 0;
  *(undefined4 *)&menuPcs->field_0x798 = 0;
  *(undefined4 *)&menuPcs->field_0x79c = 0;
  *(undefined4 *)&menuPcs->field_0x7a0 = 0;
  *(undefined4 *)&menuPcs->field_0x7a4 = 0;
  *(undefined4 *)&menuPcs->field_0x7a8 = 0;
  *(undefined4 *)&menuPcs->field_0x7ac = 0;
  *(undefined4 *)&menuPcs->field_0x7b0 = 0;
  *(undefined4 *)&menuPcs->field_0x7b4 = 0;
  *(undefined4 *)&menuPcs->field_0x7b8 = 0;
  *(undefined4 *)&menuPcs->field_0x7bc = 0;
  *(undefined4 *)&menuPcs->field_0x7c0 = 0;
  *(undefined4 *)&menuPcs->field_0x7c4 = 0;
  *(undefined4 *)&menuPcs->field_0x7c8 = 0;
  *(undefined4 *)&menuPcs->field_0x7cc = 0;
  *(undefined4 *)&menuPcs->field_0x7d0 = 0;
  *(undefined4 *)&menuPcs->field_0x7d4 = 0;
  *(undefined4 *)&menuPcs->field_0x7d8 = 0;
  *(undefined4 *)&menuPcs->field_0x7dc = 0;
  *(undefined4 *)&menuPcs->field_0x7e0 = 0;
  *(undefined4 *)&menuPcs->field_0x7e4 = 0;
  *(undefined4 *)&menuPcs->field_0x7e8 = 0;
  *(undefined4 *)&menuPcs->field_0x7ec = 0;
  *(undefined4 *)&menuPcs->field_0x7f0 = 0;
  *(undefined4 *)&menuPcs->field_0x7f4 = 0;
  *(undefined4 *)&menuPcs->field_0x7f8 = 0;
  *(undefined4 *)&menuPcs->field_0x7fc = 0;
  *(undefined4 *)&menuPcs->field_0x800 = 0;
  *(undefined4 *)&menuPcs->field_0x804 = 0;
  *(undefined4 *)&menuPcs->field_0x808 = 0;
  *(undefined4 *)&menuPcs->field_0x80c = 0;
  *(undefined4 *)&menuPcs->field_0x810 = 0;
  pCVar27 = menuPcs;
  do {
    pCVar8 = (CCharaPcsCHandle *)
             __nw__Q29CCharaPcs7CHandleFUlPQ27CMemory6CStagePci
                       (0x194,(CCharaPcsCHandle *)MenuPcs._236_4_,s_wm_menu_cpp_801dc418,500);
    if (pCVar8 != (CCharaPcsCHandle *)0x0) {
      pCVar8 = (CCharaPcsCHandle *)__ct__Q29CCharaPcs7CHandleFv(pCVar8);
    }
    *(CCharaPcsCHandle **)&pCVar27->field_0x774 = pCVar8;
    Add__Q29CCharaPcs7CHandleFv(*(CCharaPcsCHandle **)&pCVar27->field_0x774);
    if (iVar36 < 0x20) {
      iVar15 = (int)*psVar40;
      CharaPcs._228_4_ = 1;
      uVar13 = 3;
    }
    else {
      iVar43 = (iVar36 + -0x20) * 0xc30;
      CharaPcs._228_4_ = 0;
      if (*(int *)((int)&Game + iVar43 + 0x17a4) == 0) {
        uVar13 = 3;
        iVar15 = (int)DAT_801dc192;
      }
      else {
        uVar13 = 0;
        iVar16 = (uint)*(ushort *)((int)&Game + iVar43 + 0x17e0) * 200;
        iVar15 = iVar16 + 100;
        if (*(short *)((int)&Game + iVar43 + 0x17e2) != 0) {
          iVar15 = iVar16 + 200;
        }
        iVar15 = iVar15 + (uint)*(ushort *)((int)&Game + iVar43 + 0x17e4);
      }
    }
    LoadModel__Q29CCharaPcs7CHandleFiUlUlUliii
              (*(undefined4 *)&pCVar27->field_0x774,uVar13,iVar15,0,0,0xffffffff,0,0);
    puVar26 = &pCVar27->field_0x774;
    iVar36 = iVar36 + 1;
    pCVar27 = (CMenuPcs *)&pCVar27->field_0x4;
    psVar40 = psVar40 + 1;
    *(uint *)(*(int *)puVar26 + 8) = *(uint *)(*(int *)puVar26 + 8) | 0x141;
  } while (iVar36 < 0x28);
  CharaPcs._228_4_ = 0;
  *(float *)(*(int *)(*(int *)&menuPcs->field_0x78c + 0x168) + 0x9c) = FLOAT_803314b0;
  uVar13 = __nwa__FUlPQ27CMemory6CStagePci(0xc80,MenuPcs._236_4_,s_wm_menu_cpp_801dc418,0x214);
  *(undefined4 *)&menuPcs->field_0x814 = uVar13;
  fVar6 = FLOAT_80331598;
  fVar5 = FLOAT_803313e8;
  fVar2 = FLOAT_803313dc;
  iVar36 = 0;
  iVar43 = 0x28;
  do {
    iVar31 = iVar36 + 4;
    pfVar33 = (float *)(*(int *)&menuPcs->field_0x814 + iVar36 + 0x1c);
    iVar29 = iVar36 + 8;
    pfVar33[2] = fVar2;
    iVar28 = iVar36 + 10;
    iVar24 = iVar36 + 0xc;
    pfVar33[1] = fVar2;
    iVar23 = iVar36 + 0xe;
    iVar22 = iVar36 + 0x10;
    *pfVar33 = fVar2;
    iVar21 = iVar36 + 0x14;
    iVar20 = iVar36 + 0x18;
    iVar18 = iVar36 + 0x40;
    pfVar33[5] = fVar2;
    iVar17 = iVar36 + 0x44;
    iVar16 = iVar36 + 0x48;
    iVar15 = iVar36 + 0x4c;
    pfVar33[4] = fVar2;
    pfVar33[3] = fVar2;
    pfVar33[8] = fVar5;
    pfVar33[7] = fVar5;
    pfVar33[6] = fVar5;
    *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar36) = 0;
    iVar36 = iVar36 + 0x50;
    *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar31) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x814 + iVar29) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x814 + iVar28) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x814 + iVar24) = 0x280;
    *(undefined2 *)(*(int *)&menuPcs->field_0x814 + iVar23) = 0x1c0;
    *(float *)(*(int *)&menuPcs->field_0x814 + iVar22) = fVar2;
    *(float *)(*(int *)&menuPcs->field_0x814 + iVar21) = fVar2;
    *(float *)(*(int *)&menuPcs->field_0x814 + iVar20) = fVar6;
    *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar18) = 0;
    *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar17) = 0;
    *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar16) = 0x280;
    *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar15) = 0x1c0;
    iVar43 = iVar43 + -1;
  } while (iVar43 != 0);
  uVar13 = __nw__FUlPQ27CMemory6CStagePci(0x8c,MenuPcs._236_4_,s_wm_menu_cpp_801dc418,0x227);
  *(undefined4 *)&menuPcs->field_0x818 = uVar13;
  memset(*(undefined4 *)&menuPcs->field_0x818,0,0x8c);
  uVar13 = __nw__FUlPQ27CMemory6CStagePci(0xec,MenuPcs._236_4_,s_wm_menu_cpp_801dc418,0x22b);
  *(undefined4 *)&menuPcs->field_0x81c = uVar13;
  memset(*(undefined4 *)&menuPcs->field_0x81c,0,0xec);
  fVar2 = FLOAT_803313e8;
  puVar9 = &uStack_234;
  puVar14 = (undefined4 *)0x801dc1b4;
  iVar36 = 10;
  do {
    puVar1 = puVar14 + 1;
    puVar14 = puVar14 + 2;
    uVar13 = *puVar14;
    puVar9[1] = *puVar1;
    puVar9 = puVar9 + 2;
    *puVar9 = uVar13;
    iVar36 = iVar36 + -1;
  } while (iVar36 != 0);
  puVar9 = local_230;
  iVar36 = 0;
  iVar43 = 5;
  puVar14 = (undefined4 *)&stack0xfffffbf0;
  do {
    iVar22 = iVar36 + 0x10;
    iVar21 = iVar36 + 0x12;
    *(short *)(*(int *)&menuPcs->field_0x81c + iVar36 + 0xc) = (short)*puVar9;
    iVar20 = iVar36 + 0x14;
    uVar13 = puVar14[2];
    iVar18 = iVar36 + 0x18;
    iVar17 = iVar36 + 0x1c;
    iVar16 = iVar36 + 0x20;
    uVar3 = puVar14[3];
    iVar15 = iVar36 + 0x24;
    *(short *)(*(int *)&menuPcs->field_0x81c + iVar36 + 0xe) = (short)puVar9[1];
    iVar36 = iVar36 + 0x1c;
    *(short *)(*(int *)&menuPcs->field_0x81c + iVar22) = (short)puVar9[2];
    puVar1 = puVar9 + 3;
    puVar9 = puVar9 + 4;
    *(short *)(*(int *)&menuPcs->field_0x81c + iVar21) = (short)*puVar1;
    *(undefined4 *)(*(int *)&menuPcs->field_0x81c + iVar20) = uVar13;
    *(undefined4 *)(*(int *)&menuPcs->field_0x81c + iVar18) = uVar3;
    *(float *)(*(int *)&menuPcs->field_0x81c + iVar17) = fVar2;
    *(float *)(*(int *)&menuPcs->field_0x81c + iVar16) = fVar2;
    *(undefined4 *)(*(int *)&menuPcs->field_0x81c + iVar15) = 0;
    iVar43 = iVar43 + -1;
    puVar14 = puVar14 + 2;
  } while (iVar43 != 0);
  uVar13 = __nw__FUlPQ27CMemory6CStagePci(0x3c,MenuPcs._236_4_,s_wm_menu_cpp_801dc418,0x231);
  *(undefined4 *)&menuPcs->field_0x820 = uVar13;
  memset(*(undefined4 *)&menuPcs->field_0x820,0,0x3c);
  *(undefined2 *)(*(int *)&menuPcs->field_0x820 + 4) = 0x10;
  fVar5 = FLOAT_803313e8;
  fVar2 = FLOAT_803313dc;
  *(undefined2 *)(*(int *)&menuPcs->field_0x820 + 6) = 0x10;
  *(undefined2 *)(*(int *)&menuPcs->field_0x820 + 8) = 0xe8;
  *(undefined2 *)(*(int *)&menuPcs->field_0x820 + 10) = 0x168;
  *(float *)(*(int *)&menuPcs->field_0x820 + 0xc) = fVar2;
  *(float *)(*(int *)&menuPcs->field_0x820 + 0x10) = fVar2;
  *(float *)(*(int *)&menuPcs->field_0x820 + 0x14) = fVar5;
  *(float *)(*(int *)&menuPcs->field_0x820 + 0x18) = fVar5;
  *(undefined4 *)(*(int *)&menuPcs->field_0x820 + 0x1c) = 0;
  iVar36 = *(int *)&menuPcs->field_0x820;
  *(undefined2 *)(iVar36 + 0x20) = *(undefined2 *)(iVar36 + 4);
  *(undefined2 *)(iVar36 + 0x22) = *(undefined2 *)(iVar36 + 6);
  *(undefined2 *)(iVar36 + 0x24) = *(undefined2 *)(iVar36 + 8);
  *(undefined2 *)(iVar36 + 0x26) = *(undefined2 *)(iVar36 + 10);
  *(undefined4 *)(iVar36 + 0x28) = *(undefined4 *)(iVar36 + 0xc);
  *(undefined4 *)(iVar36 + 0x2c) = *(undefined4 *)(iVar36 + 0x10);
  *(undefined4 *)(iVar36 + 0x30) = *(undefined4 *)(iVar36 + 0x14);
  *(undefined4 *)(iVar36 + 0x34) = *(undefined4 *)(iVar36 + 0x18);
  *(undefined4 *)(iVar36 + 0x38) = *(undefined4 *)(iVar36 + 0x1c);
  iVar36 = *(int *)&menuPcs->field_0x820;
  *(short *)(iVar36 + 0x20) = 0x280 - (*(short *)(iVar36 + 8) + *(short *)(iVar36 + 4));
  *(undefined4 *)(*(int *)&menuPcs->field_0x820 + 0x38) = 8;
  uVar13 = __nwa__FUlPQ27CMemory6CStagePci(0x1a0,MenuPcs._236_4_,s_wm_menu_cpp_801dc418,0x237);
  *(undefined4 *)&menuPcs->field_0x824 = uVar13;
  fVar5 = FLOAT_803313e8;
  fVar2 = FLOAT_803313dc;
  iVar36 = 0;
  iVar43 = 4;
  do {
    *(undefined4 *)(*(int *)&menuPcs->field_0x824 + iVar36) = 0;
    *(undefined4 *)(*(int *)&menuPcs->field_0x824 + iVar36 + 4) = 0;
    iVar17 = iVar36 + 0x38;
    *(undefined4 *)(*(int *)&menuPcs->field_0x824 + iVar36 + 8) = 0;
    iVar16 = iVar36 + 0x3c;
    *(undefined *)(*(int *)&menuPcs->field_0x824 + iVar36 + 0xc) = 0;
    iVar15 = iVar36 + 0x40;
    pfVar33 = (float *)(*(int *)&menuPcs->field_0x824 + iVar36 + 0x10);
    pfVar33[2] = fVar2;
    pfVar33[1] = fVar2;
    *pfVar33 = fVar2;
    pfVar33[5] = fVar2;
    pfVar33[4] = fVar2;
    pfVar33[3] = fVar2;
    pfVar33[8] = fVar5;
    pfVar33[7] = fVar5;
    pfVar33[6] = fVar5;
    iVar18 = iVar36 + 0x44;
    *(undefined4 *)(*(int *)&menuPcs->field_0x824 + iVar36 + 0x34) = 0;
    iVar36 = iVar36 + 0x68;
    *(undefined4 *)(*(int *)&menuPcs->field_0x824 + iVar17) = 0;
    *(undefined4 *)(*(int *)&menuPcs->field_0x824 + iVar16) = 0;
    *(undefined *)(*(int *)&menuPcs->field_0x824 + iVar15) = 0;
    pfVar33 = (float *)(*(int *)&menuPcs->field_0x824 + iVar18);
    pfVar33[2] = fVar2;
    pfVar33[1] = fVar2;
    *pfVar33 = fVar2;
    pfVar33[5] = fVar2;
    pfVar33[4] = fVar2;
    pfVar33[3] = fVar2;
    pfVar33[8] = fVar5;
    pfVar33[7] = fVar5;
    pfVar33[6] = fVar5;
    iVar43 = iVar43 + -1;
  } while (iVar43 != 0);
  InitCharaInfo__8CMenuPcsFv(menuPcs);
  uVar13 = __nwa__FUlPQ27CMemory6CStagePci(0x80,MenuPcs._236_4_,s_wm_menu_cpp_801dc418,0x243);
  *(undefined4 *)&menuPcs->field_0x828 = uVar13;
  uVar13 = __nw__FUlPQ27CMemory6CStagePci(0x48,MenuPcs._236_4_,s_wm_menu_cpp_801dc418,0x246);
  *(undefined4 *)&menuPcs->field_0x82c = uVar13;
  memset(*(undefined4 *)&menuPcs->field_0x82c,0,0x48);
  puVar10 = (uint32_t *)
            __nwa__FUlPQ27CMemory6CStagePci(0x120,MenuPcs._236_4_,s_wm_menu_cpp_801dc418,0x24a);
  menuPcs->m_unk0x838 = puVar10;
  memset(menuPcs->m_unk0x838,0,0x120);
  uVar13 = __nw__FUlPQ27CMemory6CStagePci(0x10,MenuPcs._236_4_,s_wm_menu_cpp_801dc418,0x24e);
  *(undefined4 *)&menuPcs->field_0x83c = uVar13;
  memset(*(undefined4 *)&menuPcs->field_0x83c,0,0x10);
  uVar13 = __nwa__FUlPQ27CMemory6CStagePci(0xcdb0,MenuPcs._236_4_,s_wm_menu_cpp_801dc418,0x252);
  uVar13 = __construct_new_array(uVar13,__ct__Q28CMenuPcs10EffectInfoFv,0,0x524,0x28);
  *(undefined4 *)&menuPcs->field_0x840 = uVar13;
  iVar36 = 0;
  iVar43 = 5;
  do {
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar36) = 0xffffffff;
    iVar41 = iVar36 + 0x528;
    iVar39 = iVar36 + 0x52c;
    iVar38 = iVar36 + 0xa48;
    iVar37 = iVar36 + 0xa4c;
    iVar35 = iVar36 + 0xa50;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar36 + 4) = 0xffffffff;
    iVar34 = iVar36 + 0xf6c;
    iVar32 = iVar36 + 0xf70;
    iVar30 = iVar36 + 0xf74;
    iVar31 = iVar36 + 0x1490;
    iVar29 = iVar36 + 0x1494;
    iVar28 = iVar36 + 0x1498;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar36 + 8) = 0xffffffff;
    iVar24 = iVar36 + 0x19b4;
    iVar23 = iVar36 + 0x19b8;
    iVar22 = iVar36 + 0x19bc;
    iVar21 = iVar36 + 0x1ed8;
    iVar20 = iVar36 + 0x1edc;
    iVar18 = iVar36 + 0x1ee0;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar36 + 0x524) = 0xffffffff;
    iVar17 = iVar36 + 0x23fc;
    iVar16 = iVar36 + 0x2400;
    iVar15 = iVar36 + 0x2404;
    iVar36 = iVar36 + 0x2920;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar41) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar39) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar38) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar37) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar35) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar34) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar32) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar30) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar31) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar29) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar28) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar24) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar23) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar22) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar21) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar20) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar18) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar17) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar16) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar15) = 0xffffffff;
    iVar43 = iVar43 + -1;
  } while (iVar43 != 0);
  uVar13 = __nwa__FUlPQ27CMemory6CStagePci(0xa0,MenuPcs._236_4_,s_wm_menu_cpp_801dc418,0x25a);
  *(undefined4 *)&menuPcs->field_0x844 = uVar13;
  memset(*(undefined4 *)&menuPcs->field_0x844,0,0xa0);
  uVar13 = __nw__FUlPQ27CMemory6CStagePci(0xc,MenuPcs._236_4_,s_wm_menu_cpp_801dc418,0x25e);
  *(undefined4 *)&menuPcs->field_0x848 = uVar13;
  memset(*(undefined4 *)&menuPcs->field_0x848,0,0xc);
  iVar36 = 0;
  iVar43 = 5;
  do {
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar36 + 4) = 0xffffffff;
    iVar28 = iVar36 + 0x52c;
    iVar29 = iVar36 + 0x524;
    iVar31 = iVar36 + 0xa4c;
    iVar30 = iVar36 + 0xa50;
    iVar32 = iVar36 + 0xa48;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar36 + 8) = 0xffffffff;
    iVar34 = iVar36 + 0xf70;
    iVar41 = iVar36 + 0xf74;
    iVar39 = iVar36 + 0xf6c;
    iVar38 = iVar36 + 0x1494;
    iVar37 = iVar36 + 0x1498;
    iVar35 = iVar36 + 0x1490;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar36) = 0xffffffff;
    iVar24 = iVar36 + 0x19b8;
    iVar23 = iVar36 + 0x19bc;
    iVar22 = iVar36 + 0x19b4;
    iVar21 = iVar36 + 0x1edc;
    iVar20 = iVar36 + 0x1ee0;
    iVar18 = iVar36 + 0x1ed8;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar36 + 0x528) = 0xffffffff;
    iVar17 = iVar36 + 0x2400;
    iVar16 = iVar36 + 0x2404;
    iVar15 = iVar36 + 0x23fc;
    iVar36 = iVar36 + 0x2920;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar28) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar29) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar31) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar30) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar32) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar34) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar41) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar39) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar38) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar37) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar35) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar24) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar23) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar22) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar21) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar20) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar18) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar17) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar16) = 0xffffffff;
    *(undefined4 *)(*(int *)&menuPcs->field_0x840 + iVar15) = 0xffffffff;
    iVar43 = iVar43 + -1;
  } while (iVar43 != 0);
  menuPcs->field_0x86e = 0;
  menuPcs->field_0x858 = 0;
  *(undefined4 *)&menuPcs->field_0x854 = 0;
  memset(*(undefined4 *)&menuPcs->field_0x828,0,0x80);
  bVar7 = 0;
  iVar36 = 0;
  iVar43 = 0;
  iVar15 = 2;
  do {
    *(undefined *)(*(int *)&menuPcs->field_0x828 + iVar36 + 0xc) = 0;
    *(undefined *)(*(int *)&menuPcs->field_0x828 + iVar36 + 0xb) = 0;
    *(undefined *)(*(int *)&menuPcs->field_0x828 + iVar36 + 10) = 0;
    sVar4 = *(short *)(*(int *)&menuPcs->field_0x82c + iVar43 + 0x3e);
    if (sVar4 < 0) {
      *(undefined2 *)(*(int *)&menuPcs->field_0x828 + iVar36 + 4) = 0xffff;
    }
    else {
      *(short *)(*(int *)&menuPcs->field_0x828 + iVar36 + 4) = sVar4;
      bVar7 = bVar7 | (byte)(1 << (int)sVar4);
    }
    *(undefined *)(*(int *)&menuPcs->field_0x828 + iVar36 + 0x1c) = 0;
    *(undefined *)(*(int *)&menuPcs->field_0x828 + iVar36 + 0x1b) = 0;
    *(undefined *)(*(int *)&menuPcs->field_0x828 + iVar36 + 0x1a) = 0;
    sVar4 = *(short *)(*(int *)&menuPcs->field_0x82c + iVar43 + 0x40);
    if (sVar4 < 0) {
      *(undefined2 *)(*(int *)&menuPcs->field_0x828 + iVar36 + 0x14) = 0xffff;
    }
    else {
      *(short *)(*(int *)&menuPcs->field_0x828 + iVar36 + 0x14) = sVar4;
      bVar7 = bVar7 | (byte)(1 << (int)sVar4);
    }
    iVar36 = iVar36 + 0x20;
    iVar43 = iVar43 + 4;
    iVar15 = iVar15 + -1;
  } while (iVar15 != 0);
  iVar36 = 0;
  iVar43 = 4;
  do {
    if (*(short *)(*(int *)&menuPcs->field_0x828 + iVar36 + 4) < 0) {
      iVar15 = 0;
      uVar19 = (uint)(char)bVar7;
      if ((((((uVar19 & 1) != 0) && (iVar15 = 1, (uVar19 & 2) != 0)) &&
           (iVar15 = 2, (uVar19 & 4) != 0)) &&
          ((iVar15 = 3, (uVar19 & 8) != 0 && (iVar15 = 4, (uVar19 & 0x10) != 0)))) &&
         ((iVar15 = 5, (uVar19 & 0x20) != 0 &&
          ((iVar15 = 6, (uVar19 & 0x40) != 0 && (iVar15 = 7, (uVar19 & 0x80) != 0)))))) {
        iVar15 = 8;
      }
      *(short *)(*(int *)&menuPcs->field_0x828 + iVar36 + 4) = (short)iVar15;
      bVar7 = bVar7 | (byte)(1 << iVar15);
    }
    iVar15 = *(int *)&menuPcs->field_0x828 + iVar36;
    iVar36 = iVar36 + 0x10;
    *(undefined2 *)(iVar15 + 6) = *(undefined2 *)(iVar15 + 4);
    iVar43 = iVar43 + -1;
  } while (iVar43 != 0);
  SetManaWaterEffect__8CMenuPcsFv(menuPcs);
  *(undefined2 *)&menuPcs->field_0x88 = 0xffff;
  *(undefined2 *)&menuPcs->field_0x8a = 0xffff;
  SetCrystalCageAttr__8CMenuPcsFv(menuPcs);
  local_25c = 0xffffffff;
  local_26c = 0xffffffff;
  local_268 = 0;
  local_267 = 1;
  local_264 = 0;
  local_266 = 0;
  local_260 = 0x1e;
  local_258 = 0;
  local_254 = 0;
  local_252 = 0;
  local_251 = 0;
  local_29c = 0;
  local_298 = 0;
  local_294 = 0;
  local_290 = 0;
  local_28c = 0;
  local_288 = (CGBaseObj *)0x0;
  local_284 = (CGBaseObj *)0x0;
  local_280 = 0;
  local_27c = 0;
  local_278 = FLOAT_803313e8;
  local_274 = FLOAT_803313e8;
  local_270 = 0;
  iVar36 = *(int *)&menuPcs->field_0x840;
  *(undefined4 *)(iVar36 + 0x23fc) = 9;
  pCVar25 = (CGBaseObj *)(iVar36 + 0x2408);
  *(undefined4 *)(iVar36 + 0x2404) = 7;
  Create__9CGBaseObjFv(pCVar25);
  *(undefined4 *)(iVar36 + 0x2500) = *(undefined4 *)&menuPcs->field_0x790;
  local_288 = pCVar25;
  local_284 = pCVar25;
  uVar13 = pppCreate__8CPartMngFiiP14PPPCREATEPARAMi(&PartMng,0,9,&local_29c,1);
  *(undefined4 *)(iVar36 + 0x2400) = uVar13;
  dVar44 = (double)FLOAT_803313e8;
  iVar36 = 0;
  do {
    local_2c8 = 0xffffffff;
    local_2d8 = 0xffffffff;
    local_2d4 = 0;
    local_2d3 = 1;
    local_2d0 = 0;
    local_2d2 = 0;
    local_2cc = 0x1e;
    local_2c4 = 0;
    local_2c0 = 0;
    local_2be = 0;
    local_2bd = 0;
    local_308 = 0;
    local_304 = 0;
    local_300 = 0;
    local_2fc = 0;
    local_2f8 = 0;
    local_2f4 = (CGBaseObj *)0x0;
    local_2f0 = (CGBaseObj *)0x0;
    local_2ec = 0;
    local_2e8 = 0;
    local_2e4 = (float)dVar44;
    local_2e0 = (float)dVar44;
    local_2dc = 0;
    puVar42 = (uint *)(*(int *)&menuPcs->field_0x840 + (iVar36 + 8) * 0x524);
    if ((iVar36 + 8 == 5) && (iVar36 + 5 < 0x13)) {
      puVar42 = puVar42 + 0x149;
    }
    else if ((0x10 < iVar36 + 8) && ((iVar36 + 8 < 0x15 && (0x19 < iVar36 + 5)))) {
      puVar42 = puVar42 + 0x524;
    }
    uVar19 = iVar36 + 5;
    *puVar42 = uVar19;
    pCVar25 = (CGBaseObj *)(puVar42 + 3);
    puVar42[2] = iVar36 + 8;
    Create__9CGBaseObjFv(pCVar25);
    puVar42[0x41] = *(uint *)((int)(&menuPcs->m_cameraMatrix + 1) + iVar36 * 4 + 0x20);
    local_2f4 = pCVar25;
    local_2f0 = pCVar25;
    uVar19 = pppCreate__8CPartMngFiiP14PPPCREATEPARAMi
                       (&PartMng,((int)(uVar19 ^ 100) >> 1) - ((uVar19 ^ 100) & uVar19) >> 0x1f,
                        iVar36 + 5,&local_308,1);
    iVar36 = iVar36 + 1;
    puVar42[1] = uVar19;
  } while (iVar36 < 4);
  dVar44 = (double)FLOAT_803313e8;
  uVar19 = 0;
  do {
    local_334 = 0xffffffff;
    local_344 = 0xffffffff;
    local_340 = 0;
    local_33f = 1;
    local_33c = 0;
    local_33e = 0;
    local_338 = 0x1e;
    local_330 = 0;
    local_32c = 0;
    local_32a = 0;
    local_329 = 0;
    local_374 = 0;
    local_370 = 0;
    local_36c = 0;
    local_368 = 0;
    local_364 = 0;
    local_360 = (CGBaseObj *)0x0;
    local_35c = (CGBaseObj *)0x0;
    local_358 = 0;
    local_354 = 0;
    local_350 = (float)dVar44;
    local_34c = (float)dVar44;
    local_348 = 0;
    puVar42 = (uint *)(*(int *)&menuPcs->field_0x840 + (uVar19 + 0xc) * 0x524);
    if ((uVar19 + 0xc == 5) && ((int)uVar19 < 0x13)) {
      puVar42 = puVar42 + 0x149;
    }
    else if ((0x10 < (int)(uVar19 + 0xc)) && (((int)(uVar19 + 0xc) < 0x15 && (0x19 < (int)uVar19))))
    {
      puVar42 = puVar42 + 0x524;
    }
    pCVar25 = (CGBaseObj *)(puVar42 + 3);
    *puVar42 = uVar19;
    puVar42[2] = uVar19 + 0xc;
    Create__9CGBaseObjFv(pCVar25);
    puVar42[0x41] = *(uint *)((int)(&menuPcs->m_cameraMatrix + 2) + uVar19 * 4);
    local_360 = pCVar25;
    local_35c = pCVar25;
    uVar11 = pppCreate__8CPartMngFiiP14PPPCREATEPARAMi
                       (&PartMng,((int)(uVar19 ^ 100) >> 1) - ((uVar19 ^ 100) & uVar19) >> 0x1f,
                        uVar19,&local_374,1);
    uVar19 = uVar19 + 1;
    puVar42[1] = uVar11;
  } while ((int)uVar19 < 5);
  dVar44 = (double)FLOAT_803313e8;
  iVar36 = 0;
  do {
    local_3a0 = 0xffffffff;
    local_3b0 = 0xffffffff;
    local_3ac = 0;
    local_3ab = 1;
    local_3a8 = 0;
    local_3aa = 0;
    local_3a4 = 0x1e;
    local_39c = 0;
    local_398 = 0;
    local_396 = 0;
    local_395 = 0;
    local_3e0 = 0;
    local_3dc = 0;
    local_3d8 = 0;
    local_3d4 = 0;
    local_3d0 = 0;
    local_3cc = (CGBaseObj *)0x0;
    local_3c8 = (CGBaseObj *)0x0;
    local_3c4 = 0;
    local_3c0 = 0;
    local_3bc = (float)dVar44;
    local_3b8 = (float)dVar44;
    local_3b4 = 0;
    puVar42 = (uint *)(*(int *)&menuPcs->field_0x840 + (iVar36 + 0x20) * 0x524);
    if ((iVar36 + 0x20 == 5) && (iVar36 + 10 < 0x13)) {
      puVar42 = puVar42 + 0x149;
    }
    else if ((0x10 < iVar36 + 0x20) && ((iVar36 + 0x20 < 0x15 && (0x19 < iVar36 + 10)))) {
      puVar42 = puVar42 + 0x524;
    }
    uVar19 = iVar36 + 10;
    *puVar42 = uVar19;
    pCVar25 = (CGBaseObj *)(puVar42 + 3);
    puVar42[2] = iVar36 + 0x20;
    Create__9CGBaseObjFv(pCVar25);
    puVar42[0x41] = *(uint *)(&menuPcs->field_0x7f4 + iVar36 * 4);
    local_3cc = pCVar25;
    local_3c8 = pCVar25;
    uVar19 = pppCreate__8CPartMngFiiP14PPPCREATEPARAMi
                       (&PartMng,((int)(uVar19 ^ 100) >> 1) - ((uVar19 ^ 100) & uVar19) >> 0x1f,
                        iVar36 + 10,&local_3e0,1);
    puVar42[1] = uVar19;
    if (iVar36 == 0) {
      GetParLocIdx__8CPartPcsFiR3Vec(&PartPcs,puVar42[1],&s_RingOrgPos);
    }
    iVar36 = iVar36 + 1;
  } while (iVar36 < 4);
  iVar36 = 0;
  FLOAT_8032ee18 = FLOAT_803317fc;
  do {
    iVar43 = (iVar36 + 1) * 100;
    LoadAnim__9CCharaPcsFiiPciii(&CharaPcs,0,iVar43,s_stand_80331638,1,0,0);
    LoadAnim__9CCharaPcsFiiPciii(&CharaPcs,0,iVar43,&DAT_80331640,1,0,0);
    LoadAnim__9CCharaPcsFiiPciii(&CharaPcs,0,iVar43,&DAT_80331648,1,0,0);
    LoadAnim__9CCharaPcsFiiPciii(&CharaPcs,0,iVar43,&DAT_8033164c,3,0,0);
    LoadAnim__9CCharaPcsFiiPciii(&CharaPcs,0,iVar43,&DAT_80331654,1,0,0);
    iVar36 = iVar36 + 1;
  } while (iVar36 < 8);
  iVar43 = 0;
  iVar36 = 0;
  do {
    iVar15 = iVar43 * 4;
    pCVar8 = *(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + iVar15);
    if (pCVar8->m_charaKind != 3) {
      uVar19 = (uint)pCVar8->m_charaNo / 100;
      iVar16 = uVar19 * 100;
      iVar18 = (uVar19 - 1) * 6;
      LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
                (pCVar8,s_stand_80331638,iVar18,1,0,iVar16,0xffffffff,0);
      LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
                (*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + iVar15),&DAT_80331640,iVar18 + 1,1,0
                 ,iVar16,0xffffffff,0);
      LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
                (*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + iVar15),&DAT_80331648,iVar18 + 2,1,0
                 ,iVar16,0xffffffff,0);
      LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
                (*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + iVar15),&DAT_8033164c,iVar18 + 3,3,0
                 ,iVar16,0xffffffff,0);
      LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
                (*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + iVar15),&DAT_80331654,iVar18 + 4,1,0
                 ,iVar16,0xffffffff,0);
      LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
                (*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + iVar15),&DAT_8033165c,iVar18 + 5,1,0
                 ,iVar16,0xffffffff,0);
      *(undefined4 *)(*(int *)&menuPcs->field_0x844 + iVar36) = 0;
      *(undefined4 *)(*(int *)&menuPcs->field_0x844 + iVar36 + 4) = 0xffffffff;
      iVar16 = rand();
      iVar17 = iVar16 / 0xfa + (iVar16 >> 0x1f);
      *(int *)(*(int *)&menuPcs->field_0x844 + iVar36 + 8) =
           iVar16 + (iVar17 - (iVar17 >> 0x1f)) * -0xfa;
      SetAnim__Q29CCharaPcs7CHandleFiiiii
                (*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + iVar15),iVar18,0xffffffff,0xffffffff
                 ,0,0);
      dVar44 = DOUBLE_803313f0;
      local_60 = 0x43300000;
      *(undefined4 *)(*(int *)&menuPcs->field_0x844 + iVar36 + 0xc) =
           *(undefined4 *)(*(int *)(*(int *)(&menuPcs->field_0x7f4 + iVar15) + 0x168) + 0xb4);
      *(undefined4 *)(*(int *)&menuPcs->field_0x844 + iVar36 + 0x10) =
           *(undefined4 *)(*(int *)(*(int *)(&menuPcs->field_0x7f4 + iVar15) + 0x168) + 0xc0);
      uStack_5c = (uint)*(ushort *)
                         (*(int *)(*(int *)(*(int *)(&menuPcs->field_0x7f4 + iVar15) +
                                           (iVar18 + 6) * 4 + 0xc) + 0x28) + 0x10);
      fVar2 = (float)((double)CONCAT44(0x43300000,uStack_5c) - dVar44);
      if (FLOAT_8032ee18 < fVar2) {
        FLOAT_8032ee18 = fVar2;
      }
    }
    iVar43 = iVar43 + 1;
    iVar36 = iVar36 + 0x14;
  } while (iVar43 < 8);
  LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
            (*(CCharaPcsCHandle **)&menuPcs->field_0x778,s_w_open_80331800,0,2,0xffffffff,0xffffffff
             ,0xffffffff,0);
  LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
            (*(CCharaPcsCHandle **)&menuPcs->field_0x778,&DAT_80331808,1,0,0xffffffff,0xffffffff,
             0xffffffff,0);
  LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
            (*(CCharaPcsCHandle **)&menuPcs->field_0x778,&DAT_80331810,2,2,0xffffffff,0xffffffff,
             0xffffffff,0);
  LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
            (*(CCharaPcsCHandle **)&menuPcs->field_0x778,&DAT_80331818,3,2,0xffffffff,0xffffffff,
             0xffffffff,0);
  LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
            (*(CCharaPcsCHandle **)&menuPcs->field_0x778,s_last_l_80331820,4,2,0xffffffff,0xffffffff
             ,0xffffffff,0);
  LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
            (*(CCharaPcsCHandle **)&menuPcs->field_0x778,s_last_r_80331828,5,2,0xffffffff,0xffffffff
             ,0xffffffff,0);
  LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
            (*(CCharaPcsCHandle **)&menuPcs->field_0x778,s_w_close_80331830,6,2,0xffffffff,
             0xffffffff,0xffffffff,0);
  LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
            (*(CCharaPcsCHandle **)&menuPcs->field_0x778,&DAT_80331838,7,0,0xffffffff,0xffffffff,
             0xffffffff,0);
  SetAnim__Q29CCharaPcs7CHandleFiiiii
            (*(CCharaPcsCHandle **)&menuPcs->field_0x778,0,0xffffffff,0xffffffff,0xffffffff,0);
  *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1c) = 0;
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x36) = (short)Game.game.m_gameWork.m_wmBackupParams[0]
  ;
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x3e) = (short)Game.game.m_gameWork.m_wmBackupParams[0]
  ;
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x38) = (short)Game.game.m_gameWork.m_wmBackupParams[1]
  ;
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x40) = (short)Game.game.m_gameWork.m_wmBackupParams[1]
  ;
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x3a) = (short)Game.game.m_gameWork.m_wmBackupParams[2]
  ;
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x42) = (short)Game.game.m_gameWork.m_wmBackupParams[2]
  ;
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x3c) = (short)Game.game.m_gameWork.m_wmBackupParams[3]
  ;
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x44) = (short)Game.game.m_gameWork.m_wmBackupParams[3]
  ;
  pcVar12 = GetLangString__5CGameFv(&Game.game);
  sprintf(auStack_1e0,s_dvd__smenu_subfont_fnt_801dc46c,pcVar12);
  loadFont__8CMenuPcsFiPcii(menuPcs,0,auStack_1e0,1,0xffffffff);
  menuPcs->field_0xd = 0;
  puVar26 = &menuPcs->field_0x10;
  iVar36 = 4;
  menuPcs->field_0x10 = 0;
  menuPcs->field_0x12 = 0;
  menuPcs->field_0x13 = 0;
  *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x20) = 0;
  *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 0;
  *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x18) = 0;
  DAT_8032ee1c = 1;
  DAT_8032e8ac = 1;
  do {
    iVar43 = __nw__FUlPQ27CMemory6CStagePci(0x3dfc,MenuPcs._236_4_,s_wm_menu_cpp_801dc418,0x2ea);
    if (iVar43 != 0) {
      iVar43 = __ct__8CMesMenuFv();
    }
    *(int *)(puVar26 + 0x10c) = iVar43;
    iVar43 = *(int *)(puVar26 + 0x10c);
    *(int *)(iVar43 + 0x18) = iVar36;
    *(int *)(iVar43 + 0x1c) = iVar36;
    (**(code **)(**(int **)(puVar26 + 0x10c) + 0xc))();
    iVar36 = iVar36 + 1;
    puVar26 = puVar26 + 4;
  } while (iVar36 < 6);
  pcVar12 = GetLangString__5CGameFv(&Game.game);
  sprintf(auStack_160,s_dvd__smenu_option_tex_801dc484,pcVar12);
  fileHandle = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,auStack_160,0,0);
  if (fileHandle != (CFileCHandle *)0x0) {
    Read__5CFileFPQ25CFile7CHandle(&File,fileHandle);
    SyncCompleted__5CFileFPQ25CFile7CHandle(&File,fileHandle);
    textureSet = (CTextureSet *)
                 __nw__11CTextureSetFUlPQ27CMemory6CStagePci
                           ((CTextureSet *)0x24,MenuPcs._236_4_,s_wm_menu_cpp_801dc418,0x300);
    if (textureSet != (CTextureSet *)0x0) {
      textureSet = (CTextureSet *)__ct__11CTextureSetFv(textureSet);
    }
    *(CTextureSet **)&menuPcs->field_0xbc = textureSet;
    Create__11CTextureSetFPvPQ27CMemory6CStageiP13CAmemCacheSetii
              (*(CTextureSet **)&menuPcs->field_0xbc,File.m_readBuffer,
               *(undefined4 *)&menuPcs->field_0xec,0,0,0,0);
    Close__5CFileFPQ25CFile7CHandle(&File,fileHandle);
  }
  pCVar27 = menuPcs;
  for (uVar19 = 0;
      uVar11 = GetSize__21CPtrArray<P8CTexture>Fv((CPtrArray *)(*(int *)&menuPcs->field_0xbc + 8)),
      uVar19 < uVar11; uVar19 = uVar19 + 1) {
    uVar13 = __vc__21CPtrArray<P8CTexture>FUl(*(int *)&menuPcs->field_0xbc + 8,uVar19);
    *(undefined4 *)&pCVar27->field_0xc0 = uVar13;
    pCVar27 = (CMenuPcs *)&pCVar27->field_0x4;
  }
  GetOptionData__8CMenuPcsFv(menuPcs);
  menuPcs->field_0x80 = 0;
  fVar2 = FLOAT_803313dc;
  *(float *)&menuPcs->field_0x7c = FLOAT_803313dc;
  *(float *)&menuPcs->field_0x78 = fVar2;
  *(undefined2 *)&menuPcs->field_0x74 = 0;
  DAT_8032ef08 = &g_GoOutMenu;
  return;
}


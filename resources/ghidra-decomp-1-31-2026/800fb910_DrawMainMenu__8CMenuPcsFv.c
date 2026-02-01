// Function: DrawMainMenu__8CMenuPcsFv
// Entry: 800fb910
// Size: 1952 bytes

/* WARNING: Removing unreachable block (ram,0x800fc08c) */
/* WARNING: Removing unreachable block (ram,0x800fc084) */
/* WARNING: Removing unreachable block (ram,0x800fb928) */
/* WARNING: Removing unreachable block (ram,0x800fb920) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawMainMenu__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  bool bVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  short *psVar6;
  undefined *puVar7;
  int iVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined auStack_b4 [4];
  undefined4 local_b0;
  undefined *local_ac [4];
  undefined *local_9c;
  Mat4x4 MStack_98;
  double local_58;
  undefined8 local_50;
  undefined8 local_48;
  undefined8 local_40;
  
  iVar4 = *(int *)&menuPcs->field_0x82c;
  sVar2 = *(short *)(iVar4 + 0x10);
  if (sVar2 == 0) {
    local_58 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar4 + 0x22)) ^ 0x80000000);
    dVar9 = (double)(float)(DOUBLE_803314e8 * (local_58 - DOUBLE_80331408));
  }
  else if ((sVar2 < 1) || (3 < sVar2)) {
    local_58 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar4 + 0x22)) ^ 0x80000000);
    dVar9 = (double)(float)-(DOUBLE_803314e8 * (local_58 - DOUBLE_80331408) - DOUBLE_80331420);
  }
  else {
    dVar9 = (double)FLOAT_803313e8;
  }
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_58 = (double)(longlong)(int)(DOUBLE_80331508 * dVar9);
  local_bc = CONCAT31(0xffffff,(char)(int)(DOUBLE_80331508 * dVar9));
  local_b8 = local_bc;
  GXSetChanMatColor(4,&local_b8);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x1e);
  iVar8 = 0;
  iVar4 = 0;
  do {
    if ((1 << iVar8 & 1U) != 0) {
      psVar6 = (short *)(*(int *)&menuPcs->field_0x820 + iVar4 + 4);
      local_58 = (double)(CONCAT44(0x43300000,(int)*psVar6) ^ 0x80000000);
      local_50 = (double)CONCAT44(0x43300000,(int)psVar6[1] ^ 0x80000000);
      local_48 = (double)CONCAT44(0x43300000,(int)psVar6[2] ^ 0x80000000);
      local_40 = (double)CONCAT44(0x43300000,(int)psVar6[3] ^ 0x80000000);
      DrawRect__8CMenuPcsFUlfffffffff
                ((double)(float)(local_58 - DOUBLE_80331408),
                 (double)(float)(local_50 - DOUBLE_80331408),
                 (double)(float)(local_48 - DOUBLE_80331408),
                 (double)(float)(local_40 - DOUBLE_80331408),(double)*(float *)(psVar6 + 4),
                 (double)*(float *)(psVar6 + 6),(double)FLOAT_803313e8,(double)FLOAT_803313e8,
                 &MenuPcs,*(undefined4 *)(psVar6 + 0xc));
    }
    iVar8 = iVar8 + 1;
    iVar4 = iVar4 + 0x1c;
  } while (iVar8 < 2);
  iVar4 = *(int *)&menuPcs->field_0x82c;
  sVar2 = *(short *)(iVar4 + 0x10);
  if ((0 < sVar2) && (sVar2 < 4)) {
    if (sVar2 == 1) {
      local_40 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar4 + 0x22)) ^ 0x80000000);
      dVar9 = (double)(float)(DOUBLE_803314e8 * (local_40 - DOUBLE_80331408));
    }
    else if (sVar2 == 2) {
      dVar9 = (double)FLOAT_803313e8;
    }
    else {
      local_40 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar4 + 0x22)) ^ 0x80000000);
      dVar9 = (double)(float)-(DOUBLE_803314e8 * (local_40 - DOUBLE_80331408) - DOUBLE_80331420);
    }
    dVar9 = (double)(float)(dVar9 * DOUBLE_803313f8);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    local_40 = (double)(longlong)(int)(DOUBLE_80331508 * dVar9);
    local_c4 = CONCAT31(0xffffff,(char)(int)(DOUBLE_80331508 * dVar9));
    local_c0 = local_c4;
    GXSetChanMatColor(4,&local_c0);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x33);
    dVar11 = (double)FLOAT_80331410;
    dVar9 = (double)(float)((double)FLOAT_80331440 - dVar11);
    DrawRect__8CMenuPcsFUlfffffffff
              (dVar11,dVar9,(double)FLOAT_803316d0,(double)FLOAT_80331500,(double)FLOAT_803313dc,
               (double)FLOAT_803313dc,(double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,0);
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)(float)(dVar11 + (double)FLOAT_803316d0),dVar9,(double)FLOAT_803316d0,
               (double)FLOAT_80331500,(double)FLOAT_803313dc,(double)FLOAT_803313dc,
               (double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,8);
    dVar9 = (double)(float)(dVar9 + (double)FLOAT_80331500);
    dVar11 = (double)FLOAT_80331410;
    DrawRect__8CMenuPcsFUlfffffffff
              (dVar11,dVar9,(double)FLOAT_803316d0,(double)FLOAT_80331500,(double)FLOAT_803313dc,
               (double)FLOAT_803313dc,(double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,4);
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)(float)(dVar11 + (double)FLOAT_803316d0),dVar9,(double)FLOAT_803316d0,
               (double)FLOAT_80331500,(double)FLOAT_803313dc,(double)FLOAT_803313dc,
               (double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,0xc);
  }
  DrawMainMenuSub__8CMenuPcsFv(menuPcs);
  PSMTXCopy(&menuPcs->m_cameraMatrix,&CameraPcs.m_cameraMatrix);
  local_c8 = DAT_802381a7;
  GXSetCopyClear(&local_c8,0xffffff);
  PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_98);
  GXSetProjection(&MStack_98,0);
  SetViewport__8CGraphicFv(&Graphic);
  GXSetScissor(0,0,0x280,0x1c0);
  DrawInit__8CMenuPcsFv(menuPcs);
  iVar4 = *(int *)&menuPcs->field_0x82c;
  sVar2 = *(short *)(iVar4 + 0x10);
  if ((0 < sVar2) && (sVar2 < 4)) {
    if (sVar2 == 1) {
      local_40 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar4 + 0x22)) ^ 0x80000000);
      dVar9 = (double)(float)(DOUBLE_803314e8 * (local_40 - DOUBLE_80331408));
    }
    else if (sVar2 == 2) {
      dVar9 = (double)FLOAT_803313e8;
    }
    else {
      local_40 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar4 + 0x22)) ^ 0x80000000);
      dVar9 = (double)(float)-(DOUBLE_803314e8 * (local_40 - DOUBLE_80331408) - DOUBLE_80331420);
    }
    if (DOUBLE_803314f0 < dVar9) {
      SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
      dVar10 = (double)(float)((double)FLOAT_80331458 * dVar9);
      iVar4 = (int)((double)FLOAT_80331458 * dVar9);
      local_40 = (double)(longlong)iVar4;
      local_d0 = CONCAT31(0xffffff,(char)iVar4);
      local_cc = local_d0;
      GXSetChanMatColor(4,&local_cc);
      SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x1f);
      dVar11 = (double)FLOAT_803313dc;
      DrawRect__8CMenuPcsFUlfffffffff
                (dVar11,(double)(float)(DOUBLE_803314d0 - (double)FLOAT_80331440),
                 (double)FLOAT_803313e0,(double)FLOAT_80331440,dVar11,dVar11,(double)FLOAT_803313e8,
                 (double)FLOAT_803313e8,&MenuPcs,0);
      iVar4 = Game.game.m_gameWork.m_languageId - 1;
      local_ac[0] = (&PTR_s_Select_party_members_and_create_n_80210750)[iVar4 * 0xb];
      local_ac[1] = (&PTR_s_View_diary_entries__80210754)[iVar4 * 0xb];
      local_ac[2] = (&PTR_s_Import_character_from_another_Me_80210758)[iVar4 * 0xb];
      local_ac[3] = (&PTR_s_Configure_game_settings__8021075c)[iVar4 * 0xb];
      local_9c = (&PTR_s_Save_game_data_to_a_Memory_Card__80210760)[iVar4 * 0xb];
      if (dVar9 <= (double)FLOAT_803313e8) {
        uVar3 = (uint)dVar10;
        local_48 = (double)(longlong)(int)uVar3;
      }
      else {
        uVar3 = 0xff;
      }
      puVar5 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_b4,0xff,0xff,0xff,uVar3 & 0xff);
      local_b0 = *puVar5;
      puVar7 = local_ac[*(short *)(*(int *)&menuPcs->field_0x82c + 0x26)];
      dVar9 = (double)CalcCenteringPos2__8CMenuPcsFPcff
                                ((double)FLOAT_80331594,(double)FLOAT_803313e8,menuPcs,puVar7);
      local_50 = (double)(longlong)(int)dVar9;
      local_58 = (double)(longlong)(int)FLOAT_803317d0;
      DrawFont2__8CMenuPcsFii8_GXColoriPcfff
                ((double)FLOAT_80331594,(double)FLOAT_803313e8,(double)FLOAT_803313e8,menuPcs,
                 (int)dVar9,(int)FLOAT_803317d0,&local_b0,7,puVar7);
    }
  }
  iVar4 = *(int *)&menuPcs->field_0x82c;
  bVar1 = *(short *)(iVar4 + 0x10) == 2;
  if (bVar1) {
    if ((bVar1) && (*(short *)(iVar4 + 0x18) != 0)) {
      *(short *)(iVar4 + 0x18) = *(short *)(iVar4 + 0x18) + -1;
      iVar4 = *(int *)&menuPcs->field_0x82c;
      if (*(short *)(iVar4 + 0x18) < 1) {
        *(short *)(iVar4 + 0x10) = *(short *)(iVar4 + 0x10) + 1;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
        PlaySe__6CSoundFiiii(&Sound,0x31,0x40,0x7f,0);
      }
    }
  }
  else {
    *(short *)(iVar4 + 0x22) = *(short *)(iVar4 + 0x22) + 1;
    iVar4 = *(int *)&menuPcs->field_0x82c;
    if (9 < *(short *)(iVar4 + 0x22)) {
      *(short *)(iVar4 + 0x10) = *(short *)(iVar4 + 0x10) + 1;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
      iVar4 = *(int *)&menuPcs->field_0x82c;
      if (4 < *(short *)(iVar4 + 0x10)) {
        *(undefined2 *)(iVar4 + 0x20) = *(undefined2 *)(iVar4 + 0x1e);
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1e) = 0;
      }
    }
  }
  return;
}


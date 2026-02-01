// Function: DrawCMakeMenu__8CMenuPcsFv
// Entry: 800f98bc
// Size: 2320 bytes

/* WARNING: Removing unreachable block (ram,0x800fa1a8) */
/* WARNING: Removing unreachable block (ram,0x800f98cc) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawCMakeMenu__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  bool bVar1;
  char cVar2;
  short sVar3;
  int iVar4;
  undefined4 *puVar5;
  short *psVar6;
  uint uVar7;
  undefined *puVar8;
  int iVar9;
  double dVar10;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined auStack_ac [4];
  undefined4 local_a8;
  undefined auStack_a4 [4];
  undefined4 local_a0;
  undefined auStack_9c [4];
  undefined4 local_98;
  undefined auStack_94 [4];
  undefined4 local_90;
  undefined *local_8c [3];
  Mat4x4 MStack_80;
  double local_40;
  undefined4 local_38;
  uint uStack_34;
  undefined8 local_30;
  undefined8 local_28;
  
  iVar4 = *(int *)&menuPcs->field_0x82c;
  sVar3 = *(short *)(iVar4 + 0x10);
  if (sVar3 == 0) {
    local_40 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar4 + 0x22)) ^ 0x80000000);
    dVar10 = (double)(float)(DOUBLE_803314e8 * (local_40 - DOUBLE_80331408));
  }
  else if (sVar3 == 1) {
    local_40 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar4 + 0x22)) ^ 0x80000000);
    dVar10 = (double)(float)-(DOUBLE_80331460 * (local_40 - DOUBLE_80331408) - DOUBLE_80331420);
  }
  else if (sVar3 == 2) {
    dVar10 = (double)FLOAT_80331434;
  }
  else if (sVar3 == 3) {
    local_40 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar4 + 0x22)) ^ 0x80000000);
    dVar10 = (double)(float)(DOUBLE_80331460 * (local_40 - DOUBLE_80331408) + DOUBLE_803313f8);
  }
  else {
    local_40 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar4 + 0x22)) ^ 0x80000000);
    dVar10 = (double)(float)-(DOUBLE_803314e8 * (local_40 - DOUBLE_80331408) - DOUBLE_80331420);
  }
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_40 = (double)(longlong)(int)(DOUBLE_80331508 * dVar10);
  local_b4 = CONCAT31(0xffffff,(char)(int)(DOUBLE_80331508 * dVar10));
  local_b0 = local_b4;
  GXSetChanMatColor(4,&local_b0);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x1e);
  iVar9 = 0;
  iVar4 = 0;
  do {
    if ((1 << iVar9 & 3U) != 0) {
      psVar6 = (short *)(*(int *)&menuPcs->field_0x820 + iVar4 + 4);
      uStack_34 = (int)psVar6[1] ^ 0x80000000;
      local_40 = (double)(CONCAT44(0x43300000,(int)*psVar6) ^ 0x80000000);
      local_38 = 0x43300000;
      local_30 = (double)CONCAT44(0x43300000,(int)psVar6[2] ^ 0x80000000);
      local_28 = (double)CONCAT44(0x43300000,(int)psVar6[3] ^ 0x80000000);
      DrawRect__8CMenuPcsFUlfffffffff
                ((double)(float)(local_40 - DOUBLE_80331408),
                 (double)(float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_80331408),
                 (double)(float)(local_30 - DOUBLE_80331408),
                 (double)(float)(local_28 - DOUBLE_80331408),(double)*(float *)(psVar6 + 4),
                 (double)*(float *)(psVar6 + 6),(double)FLOAT_803313e8,(double)FLOAT_803313e8,
                 &MenuPcs,*(undefined4 *)(psVar6 + 0xc));
    }
    iVar9 = iVar9 + 1;
    iVar4 = iVar4 + 0x1c;
  } while (iVar9 < 2);
  iVar4 = *(int *)&menuPcs->field_0x82c;
  sVar3 = *(short *)(iVar4 + 0x10);
  if ((0 < sVar3) && (sVar3 < 4)) {
    if (sVar3 == 1) {
      local_28 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar4 + 0x22)) ^ 0x80000000);
      dVar10 = (double)(float)(DOUBLE_803314e8 * (local_28 - DOUBLE_80331408));
    }
    else if (sVar3 == 2) {
      dVar10 = (double)FLOAT_803313e8;
    }
    else {
      local_28 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar4 + 0x22)) ^ 0x80000000);
      dVar10 = (double)(float)-(DOUBLE_803314e8 * (local_28 - DOUBLE_80331408) - DOUBLE_80331420);
    }
    DrawCharaBase__8CMenuPcsFv(menuPcs);
    DrawChara__8CMenuPcsFv(menuPcs);
    PSMTXCopy(&menuPcs->m_cameraMatrix,&CameraPcs.m_cameraMatrix);
    local_b8 = DAT_802381a7;
    GXSetCopyClear(&local_b8,0xffffff);
    PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_80);
    GXSetProjection(&MStack_80,0);
    SetViewport__8CGraphicFv(&Graphic);
    GXSetScissor(0,0,0x280,0x1c0);
    DrawInit__8CMenuPcsFv(menuPcs);
    DrawCharaName__8CMenuPcsFv(menuPcs);
    DrawCMLife__8CMenuPcsFv(menuPcs);
    if ((*(short *)(*(int *)&menuPcs->field_0x82c + 0x1c) == 3) &&
       (sVar3 = *(short *)(*(int *)&menuPcs->field_0x848 + 10), sVar3 != 3)) {
      DrawMcWin__8CMenuPcsFss(menuPcs,0xffff,0);
      if ((sVar3 == 0) && (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1)) {
        PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
      }
      if (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1) {
        DrawMcWinMess__8CMenuPcsFii(menuPcs,0x17,1);
      }
    }
    if (dVar10 <= (double)FLOAT_803313e8) {
      uVar7 = (uint)((double)FLOAT_80331458 * dVar10);
      local_28 = (double)(longlong)(int)uVar7;
    }
    else {
      uVar7 = 0xff;
    }
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    local_30 = (double)(longlong)(int)((double)FLOAT_80331458 * dVar10);
    local_c0 = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80331458 * dVar10));
    local_bc = local_c0;
    GXSetChanMatColor(4,&local_bc);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x1f);
    dVar10 = (double)FLOAT_803313dc;
    DrawRect__8CMenuPcsFUlfffffffff
              (dVar10,(double)(float)(DOUBLE_803314d0 - (double)FLOAT_80331440),
               (double)FLOAT_803313e0,(double)FLOAT_80331440,dVar10,dVar10,(double)FLOAT_803313e8,
               (double)FLOAT_803313e8,&MenuPcs,0);
    sVar3 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x1c);
    if (sVar3 != 3) {
      if (sVar3 == 8) {
        cVar2 = *(char *)(DAT_8032ef08 + 0x2c);
        if (cVar2 == '\x03') {
          if (*(char *)(DAT_8032ef08 + 0x24) == '\x02') {
            puVar8 = (&PTR_s_Select_character_to_delete__80210778)
                     [(Game.game.m_gameWork.m_languageId - 1) * 0xb];
            puVar5 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_ac,0xff,0xff,0xff,uVar7 & 0xff);
            local_a8 = *puVar5;
            dVar10 = (double)CalcCenteringPos2__8CMenuPcsFPcff
                                       ((double)FLOAT_80331594,(double)FLOAT_803313e8,&MenuPcs,
                                        puVar8);
            local_28 = (double)(longlong)(int)dVar10;
            local_30 = (double)(longlong)(int)FLOAT_803317d0;
            DrawFont2__8CMenuPcsFii8_GXColoriPcfff
                      ((double)FLOAT_80331594,(double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs
                       ,(int)dVar10,(int)FLOAT_803317d0,&local_a8,7,puVar8);
          }
        }
        else if ((cVar2 < '\x03') && ('\x01' < cVar2)) {
          cVar2 = *(char *)(DAT_8032ef08 + 0x18);
          if (cVar2 == '\x0f') {
            puVar8 = (&PTR_s_Select_character_to_import__80210774)
                     [(Game.game.m_gameWork.m_languageId - 1) * 0xb];
            puVar5 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_a4,0xff,0xff,0xff,uVar7 & 0xff);
            local_a0 = *puVar5;
            dVar10 = (double)CalcCenteringPos2__8CMenuPcsFPcff
                                       ((double)FLOAT_80331594,(double)FLOAT_803313e8,&MenuPcs,
                                        puVar8);
            local_28 = (double)(longlong)(int)dVar10;
            local_30 = (double)(longlong)(int)FLOAT_803317d0;
            DrawFont2__8CMenuPcsFii8_GXColoriPcfff
                      ((double)FLOAT_80331594,(double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs
                       ,(int)dVar10,(int)FLOAT_803317d0,&local_a0,7,puVar8);
          }
          else if ((cVar2 < '\x0f') && ('\r' < cVar2)) {
            puVar8 = (&PTR_s_Select_game_data_to_load__80210770)
                     [(Game.game.m_gameWork.m_languageId - 1) * 0xb];
            puVar5 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_9c,0xff,0xff,0xff,uVar7 & 0xff);
            local_98 = *puVar5;
            dVar10 = (double)CalcCenteringPos2__8CMenuPcsFPcff
                                       ((double)FLOAT_80331594,(double)FLOAT_803313e8,&MenuPcs,
                                        puVar8);
            local_28 = (double)(longlong)(int)dVar10;
            local_30 = (double)(longlong)(int)FLOAT_803317d0;
            DrawFont2__8CMenuPcsFii8_GXColoriPcfff
                      ((double)FLOAT_80331594,(double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs
                       ,(int)dVar10,(int)FLOAT_803317d0,&local_98,7,puVar8);
          }
        }
      }
    }
    else if (sVar3 == 3) {
      iVar9 = Game.game.m_gameWork.m_languageId - 1;
      iVar4 = (int)*(short *)&menuPcs->field_0x74 / 0x4b +
              ((int)*(short *)&menuPcs->field_0x74 >> 0x1f);
      local_8c[0] = (&PTR_s_Select_party_members__80210764)[iVar9 * 0xb];
      local_8c[1] = (&PTR_s_Select__Empty__to_create_a_new_c_80210768)[iVar9 * 0xb];
      local_8c[2] = (&PTR_s_Press_START_when_finished__8021076c)[iVar9 * 0xb];
      puVar5 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_94,0xff,0xff,0xff,uVar7 & 0xff);
      local_90 = *puVar5;
      puVar8 = local_8c[iVar4 - (iVar4 >> 0x1f)];
      dVar10 = (double)CalcCenteringPos2__8CMenuPcsFPcff
                                 ((double)FLOAT_80331594,(double)FLOAT_803313e8,menuPcs,puVar8);
      local_28 = (double)(longlong)(int)dVar10;
      local_30 = (double)(longlong)(int)FLOAT_803317d0;
      DrawFont2__8CMenuPcsFii8_GXColoriPcfff
                ((double)FLOAT_80331594,(double)FLOAT_803313e8,(double)FLOAT_803313e8,menuPcs,
                 (int)dVar10,(int)FLOAT_803317d0,&local_90,7,puVar8);
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
        PlaySe__6CSoundFiiii
                  (&Sound,0x31 - ((int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x1e) >> 0x1f),
                   0x40,0x7f,0);
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


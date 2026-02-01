// Function: DrawWMFrame__8CMenuPcsFv
// Entry: 800f36ac
// Size: 2228 bytes

/* WARNING: Removing unreachable block (ram,0x800f3f44) */
/* WARNING: Removing unreachable block (ram,0x800f3f3c) */
/* WARNING: Removing unreachable block (ram,0x800f3f34) */
/* WARNING: Removing unreachable block (ram,0x800f3f2c) */
/* WARNING: Removing unreachable block (ram,0x800f36d4) */
/* WARNING: Removing unreachable block (ram,0x800f36cc) */
/* WARNING: Removing unreachable block (ram,0x800f36c4) */
/* WARNING: Removing unreachable block (ram,0x800f36bc) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawWMFrame__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  char cVar1;
  float fVar2;
  short sVar3;
  float *pfVar4;
  uint uVar5;
  short *psVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined auStack_c4 [12];
  float local_b8;
  float local_a8;
  float local_98;
  undefined8 local_90;
  undefined4 local_88;
  uint uStack_84;
  undefined8 local_80;
  undefined4 local_78;
  uint uStack_74;
  undefined4 local_70;
  uint uStack_6c;
  undefined8 local_68;
  
  dVar13 = DOUBLE_803316e0;
  dVar12 = DOUBLE_803314f0;
  pfVar4 = *(float **)&menuPcs->field_0x82c;
  if (*(short *)(pfVar4 + 4) == 0) {
    *pfVar4 = *pfVar4 - FLOAT_80331550;
    if ((double)**(float **)&menuPcs->field_0x82c <= dVar12) {
      **(float **)&menuPcs->field_0x82c = FLOAT_803313dc;
    }
    local_90 = (double)(CONCAT44(0x43300000,(int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22)) ^
                       0x80000000);
    dVar12 = (double)(float)(DOUBLE_803316d8 * (local_90 - DOUBLE_80331408));
  }
  else if (*(short *)(pfVar4 + 4) == 3) {
    *pfVar4 = *pfVar4 + FLOAT_80331550;
    if (dVar13 <= (double)**(float **)&menuPcs->field_0x82c) {
      **(float **)&menuPcs->field_0x82c = FLOAT_80331440;
    }
    local_90 = (double)(CONCAT44(0x43300000,(int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22)) ^
                       0x80000000);
    dVar12 = (double)(float)-(DOUBLE_803316d8 * (local_90 - DOUBLE_80331408) - DOUBLE_80331508);
  }
  else {
    dVar12 = (double)FLOAT_80331458;
  }
  PSMTXRotRad(FLOAT_803314bc * **(float **)&menuPcs->field_0x82c,auStack_c4,0x7a);
  local_b8 = FLOAT_803315b0;
  local_a8 = FLOAT_803315b4;
  local_98 = FLOAT_803313dc;
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_90 = (double)(longlong)(int)dVar12;
  local_c8 = CONCAT31(0xffffff,(char)(int)dVar12);
  local_cc = local_c8;
  GXSetChanMatColor(4,&local_cc);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x16);
  dVar14 = (double)FLOAT_803315b0;
  dVar13 = (double)FLOAT_803315b4;
  iVar9 = 0;
  iVar8 = 0;
  dVar12 = DOUBLE_80331408;
  do {
    psVar6 = (short *)(*(int *)&menuPcs->field_0x81c + iVar8 + 0xc);
    uStack_84 = (int)psVar6[1] ^ 0x80000000;
    local_90 = (double)(CONCAT44(0x43300000,(int)*psVar6) ^ 0x80000000);
    uStack_74 = (int)psVar6[3] ^ 0x80000000;
    local_88 = 0x43300000;
    local_80 = (double)CONCAT44(0x43300000,(int)psVar6[2] ^ 0x80000000);
    local_78 = 0x43300000;
    DrawRect2__8CMenuPcsFUlffffffffPA4_f
              ((double)(float)((double)(float)(local_90 - dVar12) - dVar14),
               (double)(float)((double)(float)((double)CONCAT44(0x43300000,uStack_84) - dVar12) -
                              dVar13),(double)(float)(local_80 - dVar12),
               (double)(float)((double)CONCAT44(0x43300000,uStack_74) - dVar12),
               (double)*(float *)(psVar6 + 4),(double)*(float *)(psVar6 + 6),(double)FLOAT_803313e8,
               (double)FLOAT_803313e8,&MenuPcs,0,auStack_c4);
    iVar9 = iVar9 + 1;
    iVar8 = iVar8 + 0x1c;
  } while (iVar9 < 5);
  sVar3 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
  if ((sVar3 != 0) && (sVar3 < 4)) {
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x17);
    local_78 = 0x43300000;
    uStack_74 = *(uint *)(*(int *)&menuPcs->field_0x81c + 4) ^ 0x80000000;
    iVar8 = (int)(DOUBLE_80331508 *
                 ((double)(float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80331408) /
                 DOUBLE_803316e8));
    local_80 = (double)(longlong)iVar8;
    local_c8 = CONCAT31(0xffffff,(char)iVar8);
    local_d0 = local_c8;
    GXSetChanMatColor(4,&local_d0);
    iVar8 = *(int *)&menuPcs->field_0x81c;
    uStack_84 = (int)*(short *)(iVar8 + 0x98) ^ 0x80000000;
    local_88 = 0x43300000;
    uStack_6c = (int)*(short *)(iVar8 + 0x9c) ^ 0x80000000;
    local_90 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar8 + 0x9a) ^ 0x80000000);
    local_70 = 0x43300000;
    local_68 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar8 + 0x9e) ^ 0x80000000);
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)(float)((double)CONCAT44(0x43300000,uStack_84) - DOUBLE_80331408),
               (double)(float)(local_90 - DOUBLE_80331408),
               (double)(float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_80331408),
               (double)(float)(local_68 - DOUBLE_80331408),(double)*(float *)(iVar8 + 0xa0),
               (double)*(float *)(iVar8 + 0xa4),(double)FLOAT_803313e8,(double)FLOAT_803313e8,
               &MenuPcs,0);
    if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) < 3) {
      uVar10 = (uint)Game.game.m_gameWork.m_languageId;
      SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
      local_c8 = 0xffffffff;
      local_d4 = 0xffffffff;
      GXSetChanMatColor(4,&local_d4);
      SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x21);
      fVar2 = FLOAT_803316f8;
      if (uVar10 != 5) {
        fVar2 = FLOAT_803316f4;
      }
      DrawRect__8CMenuPcsFUlfffffffff
                ((double)FLOAT_803316f0,(double)fVar2,(double)FLOAT_80331440,(double)FLOAT_80331558,
                 (double)FLOAT_803313dc,(double)FLOAT_803313dc,(double)FLOAT_803313e8,
                 (double)FLOAT_803313e8,&MenuPcs,0);
      SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
      SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x17);
      if ((menuPcs->field_0xa & 2) == 0) {
        cVar1 = menuPcs->field_0xc;
      }
      else {
        cVar1 = menuPcs->field_0xb;
      }
      uVar5 = Game.game.m_gameWork._8_4_ + (int)cVar1;
      iVar8 = 1 - ((int)(((int)(uVar5 ^ 9) >> 1) - ((uVar5 ^ 9) & uVar5)) >> 0x1f);
      if (99 < (int)uVar5) {
        iVar8 = 3;
      }
      uVar5 = ~((int)(uVar10 - 5 | 5 - uVar10) >> 0x1f) & 0xe;
      if (iVar8 == 3) {
        iVar9 = (int)(DOUBLE_80331508 * (double)*(float *)(*(int *)&menuPcs->field_0x81c + 0xc4));
        local_68 = (double)(longlong)iVar9;
        local_c8 = CONCAT31(0xffffff,(char)iVar9);
        local_d8 = local_c8;
        GXSetChanMatColor(4,&local_d8);
        iVar9 = *(int *)&menuPcs->field_0x81c;
        local_70 = 0x43300000;
        uStack_6c = (int)*(short *)(iVar9 + 0xb4) ^ 0x80000000;
        uStack_74 = (int)*(short *)(iVar9 + 0xb6) + uVar5 ^ 0x80000000;
        uStack_84 = (int)*(short *)(iVar9 + 0xba) ^ 0x80000000;
        local_78 = 0x43300000;
        local_80 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar9 + 0xb8) ^ 0x80000000);
        local_88 = 0x43300000;
        DrawRect__8CMenuPcsFUlfffffffff
                  ((double)(float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_80331408),
                   (double)(float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80331408),
                   (double)(float)(local_80 - DOUBLE_80331408),
                   (double)(float)((double)CONCAT44(0x43300000,uStack_84) - DOUBLE_80331408),
                   (double)*(float *)(iVar9 + 0xbc),(double)*(float *)(iVar9 + 0xc0),
                   (double)*(float *)(iVar9 + 200),(double)*(float *)(iVar9 + 200),&MenuPcs,0);
      }
      else {
        iVar11 = 0;
        dVar12 = DOUBLE_80331508;
        dVar13 = DOUBLE_80331408;
        for (iVar9 = 0; iVar9 < iVar8; iVar9 = iVar9 + 1) {
          iVar7 = (int)(dVar12 * (double)*(float *)(*(int *)&menuPcs->field_0x81c + iVar11 + 0xc4));
          local_68 = (double)(longlong)iVar7;
          local_c8 = CONCAT31(0xffffff,(char)iVar7);
          local_dc = local_c8;
          GXSetChanMatColor(4,&local_dc);
          local_78 = 0x43300000;
          iVar7 = *(int *)&menuPcs->field_0x81c + iVar11;
          uStack_74 = (int)*(short *)(iVar7 + 0xb6) + uVar5 ^ 0x80000000;
          uStack_6c = (int)*(short *)(iVar7 + 0xb4) ^ 0x80000000;
          uStack_84 = (int)*(short *)(iVar7 + 0xba) ^ 0x80000000;
          local_80 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar7 + 0xb8)) ^ 0x80000000);
          local_70 = 0x43300000;
          local_88 = 0x43300000;
          DrawRect__8CMenuPcsFUlfffffffff
                    ((double)(float)((double)CONCAT44(0x43300000,uStack_6c) - dVar13),
                     (double)(float)((double)CONCAT44(0x43300000,uStack_74) - dVar13),
                     (double)(float)(local_80 - dVar13),
                     (double)(float)((double)CONCAT44(0x43300000,uStack_84) - dVar13),
                     (double)*(float *)(iVar7 + 0xbc),(double)*(float *)(iVar7 + 0xc0),
                     (double)*(float *)(iVar7 + 200),(double)*(float *)(iVar7 + 200),&MenuPcs,0);
          iVar11 = iVar11 + 0x1c;
        }
      }
      if ((iVar8 != 3) && (uVar10 != 5)) {
        iVar8 = *(int *)&menuPcs->field_0x81c;
        uStack_6c = (int)*(short *)(iVar8 + 0xb4) ^ 0x80000000;
        local_68 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar8 + 0xb8)) ^ 0x80000000);
        uStack_74 = (int)*(short *)(iVar8 + 0xb6) ^ 0x80000000;
        dVar12 = (double)*(float *)(iVar8 + 200);
        local_70 = 0x43300000;
        dVar15 = (double)FLOAT_803313dc;
        local_78 = 0x43300000;
        dVar14 = (double)(float)((double)(float)(local_68 - DOUBLE_80331408) * dVar12 +
                                (double)(float)((double)CONCAT44(0x43300000,uStack_6c) -
                                               DOUBLE_80331408));
        dVar13 = (double)(float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80331408);
        if (uVar10 == 1) {
          if (DAT_8032ee30 / 10 == 1) {
            dVar15 = (double)FLOAT_8033151c;
          }
          else {
            uVar10 = (uint)DAT_8032ee30 % 10;
            if ((uVar10 == 0) || (3 < uVar10)) {
              dVar15 = (double)FLOAT_8033151c;
            }
            else {
              local_68 = (double)(CONCAT44(0x43300000,uVar10 - 1) ^ 0x80000000);
              dVar15 = (double)(FLOAT_803314d8 * (float)(local_68 - DOUBLE_80331408));
            }
          }
        }
        else if (uVar10 == 4) {
          if (DAT_8032ee30 != 1) {
            dVar15 = (double)FLOAT_803314d8;
          }
        }
        else if (uVar10 == 2) {
          dVar13 = (double)(float)(dVar13 + (double)FLOAT_80331550);
        }
        iVar8 = (int)(DOUBLE_80331508 * (double)*(float *)(iVar8 + 0xc4));
        local_68 = (double)(longlong)iVar8;
        SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
        local_c8 = CONCAT22(0xffff,CONCAT11(0xff,(char)iVar8));
        local_e0 = local_c8;
        GXSetChanMatColor(4,&local_e0);
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x34);
        DrawRect__8CMenuPcsFUlfffffffff
                  (dVar14,dVar13,(double)FLOAT_80331410,(double)FLOAT_803314d8,
                   (double)FLOAT_803313dc,dVar15,dVar12,dVar12,&MenuPcs,0);
      }
    }
  }
  return;
}


// Function: CalcChara__8CMenuPcsFv
// Entry: 800f2b00
// Size: 1720 bytes

/* WARNING: Removing unreachable block (ram,0x800f319c) */
/* WARNING: Removing unreachable block (ram,0x800f2b10) */

void CalcChara__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  int iVar8;
  CCharaPcsCHandle *handle;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  undefined4 *puVar14;
  int iVar15;
  uint uVar16;
  undefined *puVar17;
  int iVar18;
  double dVar19;
  Vec local_e8;
  Mtx MStack_dc;
  Mtx MStack_ac;
  Mtx MStack_7c;
  undefined4 local_48;
  uint uStack_44;
  
  uVar13 = 0;
  puVar14 = (undefined4 *)(*(int *)&menuPcs->field_0x814 + 0xa00);
  if (*(char *)(*(int *)&menuPcs->field_0x828 + 0xd) == '\x01') {
    uVar13 = 1 << (int)*(short *)(*(int *)&menuPcs->field_0x828 + 4);
  }
  if (*(char *)(*(int *)&menuPcs->field_0x828 + 0x1d) == '\x01') {
    uVar13 = uVar13 | 1 << (int)*(short *)(*(int *)&menuPcs->field_0x828 + 0x14);
  }
  if (*(char *)(*(int *)&menuPcs->field_0x828 + 0x2d) == '\x01') {
    uVar13 = uVar13 | 1 << (int)*(short *)(*(int *)&menuPcs->field_0x828 + 0x24);
  }
  if (*(char *)(*(int *)&menuPcs->field_0x828 + 0x3d) == '\x01') {
    uVar13 = uVar13 | 1 << (int)*(short *)(*(int *)&menuPcs->field_0x828 + 0x34);
  }
  iVar15 = 0;
  do {
    uVar16 = 0;
    iVar10 = 0;
    iVar9 = (int)*(short *)(*(int *)&menuPcs->field_0x828 + 4);
    if (((*(char *)(*(int *)&menuPcs->field_0x828 + 0xd) == '\x01') && (-1 < iVar9)) &&
       (iVar15 == iVar9)) {
      uVar16 = 1;
      iVar10 = 1;
    }
    iVar9 = (int)*(short *)(*(int *)&menuPcs->field_0x828 + 0x14);
    if (((*(char *)(*(int *)&menuPcs->field_0x828 + 0x1d) == '\x01') && (-1 < iVar9)) &&
       (iVar15 == iVar9)) {
      iVar10 = iVar10 + 1;
      uVar16 = uVar16 | 2;
    }
    iVar9 = (int)*(short *)(*(int *)&menuPcs->field_0x828 + 0x24);
    if (((*(char *)(*(int *)&menuPcs->field_0x828 + 0x2d) == '\x01') && (-1 < iVar9)) &&
       (iVar15 == iVar9)) {
      iVar10 = iVar10 + 1;
      uVar16 = uVar16 | 4;
    }
    iVar9 = (int)*(short *)(*(int *)&menuPcs->field_0x828 + 0x34);
    if (((*(char *)(*(int *)&menuPcs->field_0x828 + 0x3d) == '\x01') && (-1 < iVar9)) &&
       (iVar15 == iVar9)) {
      iVar10 = iVar10 + 1;
      uVar16 = uVar16 | 8;
    }
    if (iVar10 != 0) {
      if (iVar10 == 1) {
        dVar19 = (double)FLOAT_803313dc;
      }
      else if (iVar10 == 2) {
        dVar19 = (double)FLOAT_80331588;
      }
      else if (iVar10 == 3) {
        dVar19 = (double)FLOAT_8033169c;
      }
      else {
        dVar19 = (double)FLOAT_803316a0;
      }
      iVar9 = 0;
      iVar10 = 0;
      do {
        if ((uVar16 & 1 << iVar9) != 0) {
          local_e8.y = (float)((double)s_RingOrgPos.y + DOUBLE_80331420 + dVar19);
          local_e8.x = s_RingOrgPos.x;
          local_e8.z = s_RingOrgPos.z;
          SetParLocIdx__8CPartPcsFiR3Vec
                    (&PartPcs,*(int *)(*(int *)&menuPcs->field_0x840 + iVar10 + 0xa484),&local_e8);
          dVar19 = (double)(float)(dVar19 - (double)FLOAT_8033169c);
        }
        iVar9 = iVar9 + 1;
        iVar10 = iVar10 + 0x524;
      } while (iVar9 < 4);
    }
    iVar15 = iVar15 + 1;
  } while (iVar15 < 8);
  iVar15 = 0;
  puVar17 = &menuPcs->field_0x80;
  iVar10 = 0;
  iVar9 = 0;
  do {
    iVar8 = IsModelLoaded__Q29CCharaPcs7CHandleFi(*(CCharaPcsCHandle **)(puVar17 + 0x774),1);
    if (iVar8 == 0) {
      *puVar14 = 0;
    }
    else {
      iVar8 = *(int *)&menuPcs->field_0x824 + iVar10;
      if (*(char *)(iVar8 + 0xc) == '\x01') {
        iVar2 = iVar15 * 4;
        puVar14[0xb] = FLOAT_80331664;
        handle = *(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + iVar2);
        if (handle->m_charaKind != 3) {
          uVar16 = (uint)handle->m_charaNo / 100;
          iVar12 = uVar16 * 100;
          iVar18 = (uVar16 - 1) * 6;
          LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
                    (handle,s_stand_80331638,iVar18,1,0,iVar12,0xffffffff,0);
          LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
                    (*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + iVar2),&DAT_80331640,iVar18 + 1,
                     1,0,iVar12,0xffffffff,0);
          LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
                    (*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + iVar2),&DAT_80331648,iVar18 + 2,
                     1,0,iVar12,0xffffffff,0);
          LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
                    (*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + iVar2),&DAT_8033164c,iVar18 + 3,
                     3,0,iVar12,0xffffffff,0);
          LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
                    (*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + iVar2),&DAT_80331654,iVar18 + 4,
                     1,0,iVar12,0xffffffff,0);
          LoadAnim__Q29CCharaPcs7CHandleFPciiiiii
                    (*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + iVar2),&DAT_8033165c,iVar18 + 5,
                     1,0,iVar12,0xffffffff,0);
          *(undefined4 *)(*(int *)&menuPcs->field_0x844 + iVar9) = 0;
          *(undefined4 *)(*(int *)&menuPcs->field_0x844 + iVar9 + 4) = 0xffffffff;
          iVar12 = rand();
          iVar11 = iVar12 / 0xfa + (iVar12 >> 0x1f);
          *(int *)(*(int *)&menuPcs->field_0x844 + iVar9 + 8) =
               iVar12 + (iVar11 - (iVar11 >> 0x1f)) * -0xfa;
          SetAnim__Q29CCharaPcs7CHandleFiiiii
                    (*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + iVar2),iVar18,0xffffffff,
                     0xffffffff,
                     -1 - ((*(CCharaPcsCHandle **)(&menuPcs->field_0x7f4 + iVar2))->
                           m_currentAnimIndex >> 0x1f),1);
          *(undefined4 *)(*(int *)&menuPcs->field_0x844 + iVar9 + 0xc) =
               *(undefined4 *)(*(int *)(*(int *)(&menuPcs->field_0x7f4 + iVar2) + 0x168) + 0xb4);
          *(undefined4 *)(*(int *)&menuPcs->field_0x844 + iVar9 + 0x10) =
               *(undefined4 *)(*(int *)(*(int *)(&menuPcs->field_0x7f4 + iVar2) + 0x168) + 0xc0);
        }
        *(undefined *)(iVar8 + 0xc) = 0;
      }
      *puVar14 = 1;
      fVar7 = FLOAT_803316bc;
      fVar6 = FLOAT_803316b0;
      fVar5 = FLOAT_803316a4;
      fVar4 = FLOAT_803313e8;
      fVar3 = FLOAT_803313dc;
      if (**(int **)(puVar17 + 0x774) == 3) {
        if ((uVar13 & 1 << iVar15) == 0) {
          puVar14[7] = FLOAT_803313dc;
          puVar14[8] = fVar3;
          puVar14[9] = fVar3;
          puVar14[0xd] = fVar4;
          puVar14[0xe] = fVar4;
          puVar14[0xf] = fVar4;
          puVar14[10] = fVar3;
          puVar14[0xb] = fVar3;
        }
        else {
          puVar14[7] = FLOAT_803313dc;
          fVar4 = FLOAT_803316a8;
          puVar14[8] = fVar5;
          fVar5 = FLOAT_803316ac;
          puVar14[9] = fVar3;
          puVar14[0xd] = fVar4;
          puVar14[0xe] = fVar4;
          puVar14[0xf] = fVar4;
          puVar14[10] = fVar5;
          puVar14[0xb] = fVar3;
        }
      }
      else if ((uVar13 & 1 << iVar15) == 0) {
        puVar14[7] = FLOAT_803313dc;
        fVar4 = FLOAT_80331434;
        puVar14[8] = fVar7;
        fVar5 = FLOAT_803315d0;
        puVar14[9] = fVar3;
        puVar14[0xd] = fVar4;
        puVar14[0xe] = fVar4;
        puVar14[0xf] = fVar4;
        puVar14[10] = fVar5;
      }
      else {
        puVar14[7] = FLOAT_803313dc;
        fVar4 = FLOAT_803316b4;
        puVar14[8] = fVar6;
        fVar5 = FLOAT_803316b8;
        puVar14[9] = fVar3;
        puVar14[0xd] = fVar4;
        puVar14[0xe] = fVar4;
        puVar14[0xf] = fVar4;
        puVar14[10] = fVar5;
      }
      local_48 = 0x43300000;
      uStack_44 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22) ^ 0x80000000;
      dVar19 = (double)(float)(DOUBLE_803314e8 *
                              ((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80331408));
      if (DOUBLE_80331420 < dVar19) {
        dVar19 = (double)FLOAT_803313e8;
      }
      sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
      if (sVar1 == 1) {
        *(float *)(*(int *)(*(int *)(puVar17 + 0x774) + 0x168) + 0x9c) = (float)dVar19;
      }
      else if (sVar1 == 2) {
        *(float *)(*(int *)(*(int *)(puVar17 + 0x774) + 0x168) + 0x9c) = FLOAT_803313e8;
      }
      else {
        *(float *)(*(int *)(*(int *)(puVar17 + 0x774) + 0x168) + 0x9c) =
             (float)(DOUBLE_80331420 - dVar19);
      }
      PSMTXScale((float)puVar14[0xd],(float)puVar14[0xe],(float)puVar14[0xf],&MStack_7c);
      PSMTXRotRad((float)puVar14[10],&MStack_ac,0x78);
      PSMTXRotRad((float)puVar14[0xb],&MStack_dc,0x79);
      PSMTXConcat(&MStack_ac,&MStack_dc,&MStack_ac);
      MStack_ac.value[0][3] = (float)puVar14[7];
      MStack_ac.value[1][3] = (float)puVar14[8];
      MStack_ac.value[2][3] = (float)puVar14[9];
      PSMTXConcat(&MStack_ac,&MStack_7c,&MStack_7c);
      SetMatrix__Q26CChara6CModelFPA4_f(*(CModel **)(*(int *)(puVar17 + 0x774) + 0x168),&MStack_7c);
      CalcMatrix__Q26CChara6CModelFv(*(undefined4 *)(*(int *)(puVar17 + 0x774) + 0x168));
      CalcSkin__Q26CChara6CModelFv(*(undefined4 *)(*(int *)(puVar17 + 0x774) + 0x168));
    }
    iVar15 = iVar15 + 1;
    iVar9 = iVar9 + 0x14;
    puVar14 = puVar14 + 0x14;
    puVar17 = puVar17 + 4;
    iVar10 = iVar10 + 0x34;
  } while (iVar15 < 8);
  PCAnimCtrl__8CMenuPcsFv(menuPcs);
  return;
}


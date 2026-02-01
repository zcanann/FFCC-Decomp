// Function: DrawCMLife__8CMenuPcsFv
// Entry: 800efc38
// Size: 1596 bytes

/* WARNING: Removing unreachable block (ram,0x800f0258) */
/* WARNING: Removing unreachable block (ram,0x800f0250) */
/* WARNING: Removing unreachable block (ram,0x800f0248) */
/* WARNING: Removing unreachable block (ram,0x800f0240) */
/* WARNING: Removing unreachable block (ram,0x800f0238) */
/* WARNING: Removing unreachable block (ram,0x800f0230) */
/* WARNING: Removing unreachable block (ram,0x800f0228) */
/* WARNING: Removing unreachable block (ram,0x800f0220) */
/* WARNING: Removing unreachable block (ram,0x800f0218) */
/* WARNING: Removing unreachable block (ram,0x800f0210) */
/* WARNING: Removing unreachable block (ram,0x800efc90) */
/* WARNING: Removing unreachable block (ram,0x800efc88) */
/* WARNING: Removing unreachable block (ram,0x800efc80) */
/* WARNING: Removing unreachable block (ram,0x800efc78) */
/* WARNING: Removing unreachable block (ram,0x800efc70) */
/* WARNING: Removing unreachable block (ram,0x800efc68) */
/* WARNING: Removing unreachable block (ram,0x800efc60) */
/* WARNING: Removing unreachable block (ram,0x800efc58) */
/* WARNING: Removing unreachable block (ram,0x800efc50) */
/* WARNING: Removing unreachable block (ram,0x800efc48) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawCMLife__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  char cVar2;
  char cVar3;
  ushort uVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  float *pfVar11;
  float *pfVar12;
  uint uVar13;
  int iVar14;
  uint uVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  double dVar19;
  double dVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  double dVar24;
  double dVar25;
  double dVar26;
  double dVar27;
  double dVar28;
  double dVar29;
  undefined4 local_120;
  undefined4 local_11c;
  int local_118;
  float *local_114;
  double local_110;
  longlong local_108;
  longlong local_100;
  longlong local_f8;
  undefined4 local_f0;
  uint uStack_ec;
  undefined4 local_e8;
  uint uStack_e4;
  undefined4 local_e0;
  uint uStack_dc;
  undefined4 local_d8;
  uint uStack_d4;
  
  iVar8 = *(int *)&menuPcs->field_0x82c;
  if (*(short *)(iVar8 + 0x10) == 1) {
    local_110 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar8 + 0x22)) ^ 0x80000000);
    fVar1 = (float)(DOUBLE_803314e8 * (local_110 - DOUBLE_80331408));
  }
  else {
    fVar1 = FLOAT_803313e8;
    if (*(short *)(iVar8 + 0x10) != 2) {
      local_110 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar8 + 0x22)) ^ 0x80000000);
      fVar1 = (float)-(DOUBLE_803314e8 * (local_110 - DOUBLE_80331408) - DOUBLE_80331420);
    }
  }
  iVar8 = *(int *)&menuPcs->field_0x828;
  uVar13 = 0;
  if (((*(char *)(iVar8 + 0xd) != '\0') && (*(char *)(iVar8 + 0xb) == '\0')) &&
     (*(char *)(iVar8 + 0xc) == '\0')) {
    uVar13 = 1 << (int)*(short *)(iVar8 + 4);
  }
  iVar8 = *(int *)&menuPcs->field_0x828;
  if (((*(char *)(iVar8 + 0x1d) != '\0') && (*(char *)(iVar8 + 0x1b) == '\0')) &&
     (*(char *)(iVar8 + 0x1c) == '\0')) {
    uVar13 = uVar13 | 1 << (int)*(short *)(iVar8 + 0x14);
  }
  iVar8 = *(int *)&menuPcs->field_0x828;
  if (((*(char *)(iVar8 + 0x2d) != '\0') && (*(char *)(iVar8 + 0x2b) == '\0')) &&
     (*(char *)(iVar8 + 0x2c) == '\0')) {
    uVar13 = uVar13 | 1 << (int)*(short *)(iVar8 + 0x24);
  }
  iVar8 = *(int *)&menuPcs->field_0x828;
  if (((*(char *)(iVar8 + 0x3d) != '\0') && (*(char *)(iVar8 + 0x3b) == '\0')) &&
     (*(char *)(iVar8 + 0x3c) == '\0')) {
    uVar13 = uVar13 | 1 << (int)*(short *)(iVar8 + 0x34);
  }
  iVar8 = -0x7fde1140;
  uVar15 = 0;
  dVar28 = (double)(FLOAT_80331458 * fVar1);
  iVar17 = 0;
  do {
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x27);
    if (((*(short *)(*(int *)&menuPcs->field_0x82c + 0x1c) == 8) && (menuPcs->field_0x888 == '\x01')
        ) && (*(int *)&menuPcs->field_0x88c != 0)) {
      iVar9 = *(int *)&menuPcs->field_0x88c + iVar17;
      if (*(int *)(iVar9 + 0x1a84) != 0) {
        uVar4 = *(ushort *)(iVar9 + 0x14d6);
LAB_800efe7c:
        iVar9 = (int)(uint)uVar4 >> 1;
        fVar1 = FLOAT_80331434;
        fVar5 = FLOAT_80331668;
        if ((uVar13 & 1 << uVar15) != 0) {
          fVar1 = FLOAT_803313e8;
          fVar5 = FLOAT_803313e8;
        }
        local_f8 = (longlong)(int)dVar28;
        local_110 = (double)(longlong)(int)(FLOAT_80331458 * fVar1);
        local_108 = (longlong)(int)(FLOAT_80331458 * fVar5);
        local_100 = (longlong)(int)(FLOAT_80331458 * fVar5);
        local_120 = CONCAT22(CONCAT11((char)(int)(FLOAT_80331458 * fVar1),
                                      (char)(int)(FLOAT_80331458 * fVar5)),
                             CONCAT11((char)(int)(FLOAT_80331458 * fVar5),(char)(int)dVar28));
        local_11c = local_120;
        GXSetChanMatColor(4,&local_120);
        iVar16 = ((int)uVar15 >> 2) + (uint)((int)uVar15 < 0 && (uVar15 & 3) != 0);
        iVar14 = (int)uVar15 >> 0x1f;
        local_e8 = 0x43300000;
        local_f0 = 0x43300000;
        uStack_e4 = iVar16 * 0xb8 ^ 0x80000000;
        uStack_ec = ((iVar14 * 4 | uVar15 * 0x40000000 + iVar14 >> 0x1e) - iVar14) * 0x90 ^
                    0x80000000;
        dVar26 = (double)(FLOAT_80331478 +
                         (float)((double)CONCAT44(0x43300000,uStack_e4) - DOUBLE_80331408));
        dVar27 = (double)(FLOAT_80331410 +
                         (float)((double)CONCAT44(0x43300000,uStack_ec) - DOUBLE_80331408));
        dVar24 = dVar26;
        if (iVar16 != 0) {
          dVar24 = (double)(float)(dVar26 + (double)FLOAT_80331548);
        }
        uStack_dc = iVar9 * -0x10 + 0x90U ^ 0x80000000;
        local_e0 = 0x43300000;
        uStack_d4 = 8U - iVar9 ^ 0x80000000;
        dVar25 = (double)(float)(dVar24 + (double)FLOAT_8033166c);
        iVar14 = 0;
        dVar29 = (double)FLOAT_803314c0;
        local_d8 = 0x43300000;
        dVar20 = (double)FLOAT_803313dc;
        dVar24 = ((double)CONCAT44(0x43300000,uStack_dc) - DOUBLE_80331408) * DOUBLE_803313f8 +
                 dVar27;
        dVar21 = (double)FLOAT_80331558;
        dVar23 = ((double)CONCAT44(0x43300000,uStack_d4) - DOUBLE_80331408) * DOUBLE_803313f8;
        dVar22 = DOUBLE_80331420;
        while( true ) {
          dVar24 = (double)(float)dVar24;
          dVar23 = (double)(float)dVar23;
          if (iVar9 <= iVar14) break;
          fVar1 = (float)(dVar23 / dVar29);
          local_118 = DAT_8032e918;
          local_114 = DAT_8032e91c;
          dVar19 = (double)FLOAT_803313dc;
          if (fVar1 < DAT_8032e91c[DAT_8032e918 * 4 + -4]) {
            iVar10 = 0;
            pfVar12 = DAT_8032e91c;
            iVar18 = DAT_8032e918;
            if (0 < DAT_8032e918) {
              do {
                if (fVar1 <= *pfVar12) {
                  if (iVar10 == 0) {
                    dVar19 = (double)DAT_8032e91c[1];
                  }
                  else {
                    pfVar11 = DAT_8032e91c + iVar10 * 4;
                    pfVar12 = DAT_8032e91c + (iVar10 + -1) * 4;
                    fVar5 = *pfVar11 - *pfVar12;
                    fVar7 = (fVar1 - *pfVar12) / fVar5;
                    fVar6 = fVar7 * fVar7;
                    fVar1 = fVar6 * fVar7;
                    dVar19 = (double)(fVar5 * (pfVar12[3] *
                                               (fVar7 + -(FLOAT_803314c8 * fVar6 - fVar1)) +
                                              pfVar11[2] * (fVar1 - fVar6)) +
                                     pfVar12[1] *
                                     (FLOAT_803313e8 +
                                     (FLOAT_803314c8 * fVar1 - FLOAT_803314c4 * fVar6)) +
                                     pfVar11[1] * (FLOAT_803314cc * fVar1 + FLOAT_803314c4 * fVar6))
                    ;
                  }
                  break;
                }
                pfVar12 = pfVar12 + 4;
                iVar10 = iVar10 + 1;
                iVar18 = iVar18 + -1;
              } while (iVar18 != 0);
            }
          }
          else {
            dVar19 = (double)DAT_8032e91c[DAT_8032e918 * 4 + -3];
          }
          DrawRect__8CMenuPcsFUlfffffffff
                    (dVar24,(double)(float)(dVar25 + dVar19),(double)FLOAT_80331558,
                     (double)FLOAT_80331558,dVar20,dVar20,(double)FLOAT_803313e8,
                     (double)FLOAT_803313e8,&MenuPcs,0);
          dVar23 = dVar23 + dVar22;
          iVar14 = iVar14 + 1;
          dVar24 = dVar24 + dVar21;
        }
        if ((menuPcs->field_0x888 == '\x01') && (*(int *)&menuPcs->field_0x88c != 0)) {
          iVar9 = *(int *)&menuPcs->field_0x88c + iVar17;
          cVar2 = *(char *)(iVar9 + 0x1d90);
          cVar3 = *(char *)(iVar9 + 0x1d91);
        }
        else {
          cVar2 = *(char *)(iVar8 + 0x1f95);
          cVar3 = *(char *)(iVar8 + 0x1f96);
        }
        if ((cVar2 != '\0') || (cVar3 != '\0')) {
          SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x38);
          fVar1 = FLOAT_80331440;
          if (cVar2 != '\0') {
            fVar1 = FLOAT_803313dc;
          }
          if (iVar16 != 0) {
            dVar26 = (double)(float)(dVar26 + (double)FLOAT_80331548);
          }
          DrawRect__8CMenuPcsFUlfffffffff
                    ((double)(float)(dVar27 + DOUBLE_80331670),
                     (double)(float)(dVar26 + DOUBLE_803315c0),(double)FLOAT_80331524,
                     (double)FLOAT_80331440,(double)FLOAT_803313dc,(double)fVar1,
                     (double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,0);
        }
      }
    }
    else if (*(int *)(iVar8 + 0x1794) != 0) {
      uVar4 = *(ushort *)(iVar8 + 0x140a);
      goto LAB_800efe7c;
    }
    uVar15 = uVar15 + 1;
    iVar8 = iVar8 + 0xc30;
    iVar17 = iVar17 + 0x9c0;
    if (7 < (int)uVar15) {
      return;
    }
  } while( true );
}


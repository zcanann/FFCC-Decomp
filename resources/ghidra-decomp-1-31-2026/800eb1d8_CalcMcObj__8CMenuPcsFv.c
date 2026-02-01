// Function: CalcMcObj__8CMenuPcsFv
// Entry: 800eb1d8
// Size: 1312 bytes

/* WARNING: Removing unreachable block (ram,0x800eb6dc) */
/* WARNING: Removing unreachable block (ram,0x800eb6d4) */
/* WARNING: Removing unreachable block (ram,0x800eb6cc) */
/* WARNING: Removing unreachable block (ram,0x800eb6c4) */
/* WARNING: Removing unreachable block (ram,0x800eb6bc) */
/* WARNING: Removing unreachable block (ram,0x800eb6b4) */
/* WARNING: Removing unreachable block (ram,0x800eb6ac) */
/* WARNING: Removing unreachable block (ram,0x800eb6a4) */
/* WARNING: Removing unreachable block (ram,0x800eb69c) */
/* WARNING: Removing unreachable block (ram,0x800eb228) */
/* WARNING: Removing unreachable block (ram,0x800eb220) */
/* WARNING: Removing unreachable block (ram,0x800eb218) */
/* WARNING: Removing unreachable block (ram,0x800eb210) */
/* WARNING: Removing unreachable block (ram,0x800eb208) */
/* WARNING: Removing unreachable block (ram,0x800eb200) */
/* WARNING: Removing unreachable block (ram,0x800eb1f8) */
/* WARNING: Removing unreachable block (ram,0x800eb1f0) */
/* WARNING: Removing unreachable block (ram,0x800eb1e8) */

void CalcMcObj__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  double dVar7;
  double dVar8;
  uint32_t *puVar9;
  float *pfVar10;
  int iVar11;
  float *pfVar12;
  undefined4 *puVar13;
  uint uVar14;
  uint32_t *puVar15;
  int iVar16;
  int iVar17;
  longlong lVar18;
  double dVar19;
  double dVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  double dVar24;
  double dVar25;
  double dVar26;
  Mtx MStack_168;
  Mtx MStack_138;
  Mtx MStack_108;
  longlong local_d8;
  undefined4 local_d0;
  uint uStack_cc;
  longlong local_c8;
  undefined4 local_c0;
  uint uStack_bc;
  
  puVar15 = &(menuPcs->m_mcCtrl).m_serialHi;
  lVar18 = (longlong)(int)FLOAT_80331480;
  puVar13 = (undefined4 *)(*(int *)&menuPcs->field_0x814 + 0x550);
  uVar14 = 0;
  iVar16 = 0;
  dVar23 = (double)FLOAT_803314a0;
  dVar24 = (double)FLOAT_803313dc;
  dVar25 = (double)FLOAT_803314a4;
  dVar19 = DOUBLE_80331488;
  dVar20 = DOUBLE_80331498;
  dVar21 = DOUBLE_80331408;
  dVar22 = DOUBLE_80331490;
  dVar26 = DOUBLE_803314a8;
  do {
    uStack_cc = uVar14 ^ 0x80000000;
    local_d0 = 0x43300000;
    *(short *)(puVar13 + 2) = (short)lVar18;
    iVar17 = (int)((double)(float)(dVar19 + dVar20 * ((double)CONCAT44(0x43300000,uStack_cc) -
                                                     dVar21) + dVar22) - dVar23);
    local_c8 = (longlong)iVar17;
    *(short *)((int)puVar13 + 10) = (short)iVar17;
    *(undefined2 *)(puVar13 + 3) = 0x140;
    *(undefined2 *)((int)puVar13 + 0xe) = 0xe0;
    puVar13[4] = (float)dVar24;
    puVar13[5] = (float)dVar24;
    puVar13[6] = (float)dVar25;
    puVar9 = menuPcs->m_unk0x838;
    puVar13[1] = puVar13[1] + 1;
    if (dVar26 * (double)DAT_8032e8b4[DAT_8032e8b0 * 4 + -4] <=
        (double)(float)((double)CONCAT44(0x43300000,puVar13[1] ^ 0x80000000) - dVar21)) {
      puVar13[1] = 0;
    }
    fVar1 = FLOAT_803314b0;
    if (*(int *)((int)puVar9 + iVar16 + 8) < 1) {
      *puVar13 = 0;
    }
    else {
      *puVar13 = 1;
      fVar2 = FLOAT_803314b4;
      puVar13[7] = fVar1;
      fVar1 = FLOAT_803313dc;
      puVar13[8] = fVar2;
      fVar2 = FLOAT_80331434;
      puVar13[9] = fVar1;
      fVar6 = FLOAT_803314b8;
      puVar13[0xd] = fVar2;
      fVar4 = FLOAT_803314bc;
      puVar13[0xe] = fVar2;
      dVar7 = DOUBLE_80331408;
      puVar13[0xf] = fVar2;
      fVar3 = FLOAT_803314c0;
      puVar13[10] = fVar6;
      puVar13[0xb] = (float)puVar13[0xb] + fVar4;
      fVar6 = FLOAT_803314c0;
      dVar8 = DOUBLE_80331408;
      fVar2 = FLOAT_803313dc;
      fVar3 = (float)((double)CONCAT44(0x43300000,puVar13[1] ^ 0x80000000) - dVar7) / fVar3;
      if (fVar3 < DAT_8032e8b4[DAT_8032e8b0 * 4 + -4]) {
        iVar11 = 0;
        pfVar12 = DAT_8032e8b4;
        iVar17 = DAT_8032e8b0;
        if (0 < DAT_8032e8b0) {
          do {
            if (fVar3 <= *pfVar12) {
              if (iVar11 == 0) {
                fVar1 = DAT_8032e8b4[1];
              }
              else {
                pfVar10 = DAT_8032e8b4 + iVar11 * 4;
                pfVar12 = DAT_8032e8b4 + (iVar11 + -1) * 4;
                fVar1 = *pfVar10 - *pfVar12;
                fVar5 = (fVar3 - *pfVar12) / fVar1;
                fVar4 = fVar5 * fVar5;
                fVar3 = fVar4 * fVar5;
                fVar1 = fVar1 * (pfVar12[3] * (fVar5 + -(FLOAT_803314c8 * fVar4 - fVar3)) +
                                pfVar10[2] * (fVar3 - fVar4)) +
                        pfVar12[1] *
                        (FLOAT_803313e8 + (FLOAT_803314c8 * fVar3 - FLOAT_803314c4 * fVar4)) +
                        pfVar10[1] * (FLOAT_803314cc * fVar3 + FLOAT_803314c4 * fVar4);
              }
              break;
            }
            pfVar12 = pfVar12 + 4;
            iVar11 = iVar11 + 1;
            iVar17 = iVar17 + -1;
          } while (iVar17 != 0);
        }
      }
      else {
        fVar1 = DAT_8032e8b4[DAT_8032e8b0 * 4 + -3];
      }
      local_c0 = 0x43300000;
      puVar13[8] = (float)puVar13[8] + fVar1;
      uStack_bc = puVar13[1] ^ 0x80000000;
      fVar6 = (float)((double)CONCAT44(0x43300000,uStack_bc) - dVar8) / fVar6;
      if (fVar6 < DAT_8032e8bc[DAT_8032e8b8 * 4 + -4]) {
        iVar11 = 0;
        pfVar12 = DAT_8032e8bc;
        iVar17 = DAT_8032e8b8;
        if (0 < DAT_8032e8b8) {
          do {
            if (fVar6 <= *pfVar12) {
              if (iVar11 == 0) {
                fVar2 = DAT_8032e8bc[1];
              }
              else {
                pfVar10 = DAT_8032e8bc + iVar11 * 4;
                pfVar12 = DAT_8032e8bc + (iVar11 + -1) * 4;
                fVar1 = *pfVar10 - *pfVar12;
                fVar6 = (fVar6 - *pfVar12) / fVar1;
                fVar3 = fVar6 * fVar6;
                fVar2 = fVar3 * fVar6;
                fVar2 = fVar1 * (pfVar12[3] * (fVar6 + -(FLOAT_803314c8 * fVar3 - fVar2)) +
                                pfVar10[2] * (fVar2 - fVar3)) +
                        pfVar12[1] *
                        (FLOAT_803313e8 + (FLOAT_803314c8 * fVar2 - FLOAT_803314c4 * fVar3)) +
                        pfVar10[1] * (FLOAT_803314cc * fVar2 + FLOAT_803314c4 * fVar3);
              }
              break;
            }
            pfVar12 = pfVar12 + 4;
            iVar11 = iVar11 + 1;
            iVar17 = iVar17 + -1;
          } while (iVar17 != 0);
        }
      }
      else {
        fVar2 = DAT_8032e8bc[DAT_8032e8b8 * 4 + -3];
      }
      puVar13[0xb] = FLOAT_803314bc * fVar2;
      local_d8 = lVar18;
      PSMTXScale((float)puVar13[0xd],(float)puVar13[0xe],(float)puVar13[0xf],&MStack_108);
      PSMTXRotRad((float)puVar13[10],&MStack_138,0x78);
      PSMTXRotRad((float)puVar13[0xb],&MStack_168,0x79);
      PSMTXConcat(&MStack_138,&MStack_168,&MStack_138);
      MStack_138.value[0][3] = (float)puVar13[7];
      MStack_138.value[1][3] = (float)puVar13[8];
      MStack_138.value[2][3] = (float)puVar13[9];
      PSMTXConcat(&MStack_138,&MStack_108,&MStack_108);
      SetMatrix__Q26CChara6CModelFPA4_f(*(CModel **)(puVar15[0x1dd] + 0x168),&MStack_108);
      CalcMatrix__Q26CChara6CModelFv(*(undefined4 *)(puVar15[0x1dd] + 0x168));
      CalcSkin__Q26CChara6CModelFv(*(undefined4 *)(puVar15[0x1dd] + 0x168));
    }
    uVar14 = uVar14 + 1;
    puVar13 = puVar13 + 0x14;
    puVar15 = puVar15 + 1;
    iVar16 = iVar16 + 0x48;
    if (3 < (int)uVar14) {
      return;
    }
  } while( true );
}


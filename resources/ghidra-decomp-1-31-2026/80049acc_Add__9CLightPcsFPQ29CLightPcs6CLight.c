// Function: Add__9CLightPcsFPQ29CLightPcs6CLight
// Entry: 80049acc
// Size: 1032 bytes

void Add__9CLightPcsFPQ29CLightPcs6CLight(int param_1,undefined4 *param_2)

{
  undefined uVar1;
  undefined uVar2;
  undefined uVar3;
  undefined uVar4;
  float fVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  float fVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 *puVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  int iVar15;
  undefined4 uVar16;
  int iVar17;
  int iVar18;
  undefined4 uVar19;
  int iVar20;
  undefined4 uVar21;
  undefined4 uVar22;
  undefined4 uVar23;
  undefined4 uVar24;
  undefined4 uVar25;
  undefined4 uVar26;
  undefined4 uVar27;
  undefined4 uVar28;
  undefined4 uVar29;
  undefined4 uVar30;
  undefined4 uVar31;
  undefined4 uVar32;
  undefined4 uVar33;
  undefined4 uVar34;
  undefined4 uVar35;
  undefined4 uVar36;
  undefined4 uVar37;
  undefined4 uVar38;
  undefined4 uVar39;
  undefined4 uVar40;
  undefined4 uVar41;
  undefined4 uVar42;
  undefined4 uVar43;
  undefined4 uVar44;
  undefined4 uVar45;
  float local_c8;
  float local_c4;
  undefined4 local_88;
  
  uVar26 = *param_2;
  uVar27 = param_2[1];
  uVar44 = param_2[2];
  uVar42 = param_2[3];
  uVar40 = param_2[4];
  uVar38 = param_2[5];
  uVar36 = param_2[6];
  fVar5 = (float)param_2[7];
  uVar32 = param_2[0xe];
  uVar30 = param_2[0xf];
  uVar28 = param_2[0x10];
  uVar6 = param_2[0x11];
  uVar7 = param_2[0x12];
  fVar8 = (float)param_2[10];
  uVar9 = param_2[0xc];
  uVar10 = param_2[0xb];
  uVar1 = *(undefined *)((int)param_2 + 0x4d);
  uVar34 = param_2[0xd];
  uVar2 = *(undefined *)((int)param_2 + 0x4e);
  uVar3 = *(undefined *)(param_2 + 0x13);
  uVar4 = *(undefined *)((int)param_2 + 0x4f);
  iVar20 = param_2[0x14];
  iVar18 = param_2[0x15];
  iVar15 = param_2[0x16];
  uVar13 = param_2[0x17];
  uVar29 = param_2[0x19];
  uVar31 = param_2[0x1a];
  uVar33 = param_2[0x1b];
  uVar35 = param_2[0x1c];
  uVar37 = param_2[0x1d];
  uVar39 = param_2[0x1e];
  uVar41 = param_2[0x1f];
  uVar43 = param_2[0x20];
  uVar45 = param_2[0x21];
  uVar25 = param_2[0x22];
  uVar24 = param_2[0x23];
  uVar23 = param_2[0x24];
  uVar22 = param_2[0x25];
  uVar21 = param_2[0x26];
  uVar19 = param_2[0x27];
  uVar16 = param_2[0x28];
  uVar14 = param_2[0x29];
  uVar11 = param_2[0x2a];
  local_c8 = (float)param_2[8];
  if (FLOAT_8032fc10 <= (float)param_2[8]) {
    local_c8 = fVar5;
  }
  local_c4 = fVar5;
  if (fVar5 < FLOAT_8032fc14) {
    local_c4 = -fVar5;
  }
  local_c4 = local_c4 * FLOAT_8032fc18;
  local_88 = 0x1010101;
  if (iVar20 == 0) {
    local_88 = 0x10101;
  }
  if (iVar18 == 0) {
    local_88._1_3_ = (uint3)local_88._2_2_;
  }
  if (iVar15 == 0) {
    local_88._2_2_ = (ushort)(byte)local_88;
  }
  iVar17 = *(int *)(param_1 + 0xb8);
  *(int *)(param_1 + 0xb8) = iVar17 + 1;
  puVar12 = (undefined4 *)(param_1 + iVar17 * 0xb0 + 0x63c);
  *puVar12 = uVar26;
  puVar12[1] = uVar27;
  puVar12[2] = uVar44;
  puVar12[3] = uVar42;
  puVar12[4] = uVar40;
  puVar12[5] = uVar38;
  puVar12[6] = uVar36;
  puVar12[7] = fVar5;
  puVar12[8] = local_c8;
  puVar12[9] = local_c4 * fVar8;
  puVar12[10] = fVar8;
  puVar12[0xb] = uVar10;
  puVar12[0xc] = uVar9;
  puVar12[0xd] = uVar34;
  puVar12[0xe] = uVar32;
  puVar12[0xf] = uVar30;
  puVar12[0x10] = uVar28;
  puVar12[0x11] = uVar6;
  puVar12[0x12] = uVar7;
  *(undefined *)(puVar12 + 0x13) = uVar3;
  *(undefined *)((int)puVar12 + 0x4d) = uVar1;
  *(undefined *)((int)puVar12 + 0x4e) = uVar2;
  *(undefined *)((int)puVar12 + 0x4f) = uVar4;
  puVar12[0x14] = iVar20;
  puVar12[0x15] = iVar18;
  puVar12[0x16] = iVar15;
  puVar12[0x17] = uVar13;
  puVar12[0x18] = local_88;
  puVar12[0x19] = uVar29;
  puVar12[0x1a] = uVar31;
  puVar12[0x1b] = uVar33;
  puVar12[0x1c] = uVar35;
  puVar12[0x1d] = uVar37;
  puVar12[0x1e] = uVar39;
  puVar12[0x1f] = uVar41;
  puVar12[0x20] = uVar43;
  puVar12[0x21] = uVar45;
  puVar12[0x22] = uVar25;
  puVar12[0x23] = uVar24;
  puVar12[0x24] = uVar23;
  puVar12[0x25] = uVar22;
  puVar12[0x26] = uVar21;
  puVar12[0x27] = uVar19;
  puVar12[0x28] = uVar16;
  puVar12[0x29] = uVar14;
  puVar12[0x2a] = uVar11;
  puVar12[0x2b] = fVar5 * fVar5;
  return;
}


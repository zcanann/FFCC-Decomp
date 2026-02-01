// Function: Frame__4CPadFv
// Entry: 80020494
// Size: 2844 bytes

void Frame__4CPadFv(int param_1)

{
  ushort uVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  double dVar5;
  int iVar6;
  ushort uVar8;
  ushort *puVar7;
  char cVar9;
  ushort *puVar10;
  int iVar11;
  ushort *puVar12;
  ushort *puVar13;
  int iVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  ushort *puVar18;
  int iVar19;
  ushort local_98 [8];
  ushort local_88 [24];
  undefined4 local_58;
  uint uStack_54;
  undefined4 local_50;
  uint uStack_4c;
  undefined4 local_48;
  uint uStack_44;
  undefined4 local_40;
  uint uStack_3c;
  undefined4 local_38;
  uint uStack_34;
  undefined4 local_30;
  uint uStack_2c;
  
  PADRead(local_88);
  PADClamp(local_88);
  memcpy(BYTE_ARRAY_8024430c,local_88,0x30);
  puVar18 = local_98;
  *(undefined4 *)(param_1 + 0x1c4) = 0;
  uVar17 = 0;
  puVar7 = puVar18;
  do {
    iVar6 = SIProbe(uVar17);
    iVar6 = countLeadingZeros(0x40000 - iVar6);
    *(byte *)puVar7 = (byte)(iVar6 << 2) & 0x80 | *(byte *)puVar7 & 0x7f;
    uVar8 = GetCtrlMode__6JoyBusFi(&Joybus,uVar17);
    iVar6 = 0;
    *puVar7 = uVar8 & 0x3fff | *puVar7 & 0xc000;
    if (((char)*(byte *)puVar7 < '\0') && ((*puVar7 & 0x3fff) == 0)) {
      iVar6 = 1;
    }
    *(byte *)puVar7 = (byte)(iVar6 << 6) | *(byte *)puVar7 & 0xbf;
    puVar7[1] = 0;
    if ((char)*(byte *)puVar7 < '\0') {
      uVar8 = GetPadData__6JoyBusFi(&Joybus,uVar17);
      puVar7[1] = uVar8;
    }
    uVar17 = uVar17 + 1;
    puVar7 = puVar7 + 2;
  } while (uVar17 < 4);
  iVar6 = *(int *)(param_1 + 0x1b0);
  if ((iVar6 != 0) && (iVar14 = *(int *)(param_1 + 0x1bc), -1 < iVar14)) {
    if (*(int *)(iVar6 + 4) == 0) {
      if (iVar14 < 0x1a5e0) {
        iVar6 = 0;
        iVar19 = 0;
        puVar7 = local_88;
        puVar13 = local_98;
        iVar11 = 4;
        do {
          uVar8 = *puVar7;
          puVar10 = (ushort *)(*(int *)(param_1 + 0x1b0) + iVar14 * 0x40 + iVar6 + 0xc);
          *puVar7 = *puVar10;
          *(undefined *)(puVar7 + 1) = *(undefined *)(puVar10 + 1);
          *(undefined *)((int)puVar7 + 3) = *(undefined *)((int)puVar10 + 3);
          *(undefined *)(puVar7 + 2) = *(undefined *)(puVar10 + 2);
          *(undefined *)((int)puVar7 + 5) = *(undefined *)((int)puVar10 + 5);
          *(undefined *)(puVar7 + 3) = *(undefined *)(puVar10 + 3);
          *(undefined *)((int)puVar7 + 7) = *(undefined *)((int)puVar10 + 7);
          *(undefined *)(puVar7 + 4) = *(undefined *)(puVar10 + 4);
          *(undefined *)((int)puVar7 + 9) = *(undefined *)((int)puVar10 + 9);
          *(undefined *)(puVar7 + 5) = *(undefined *)(puVar10 + 5);
          puVar10 = (ushort *)(*(int *)(param_1 + 0x1b0) + iVar14 * 0x40 + iVar19 + 0x3c);
          uVar1 = puVar10[1];
          *puVar13 = *puVar10;
          puVar13[1] = uVar1;
          if ((uVar8 & 0x10) != 0) {
            *puVar7 = *puVar7 | uVar8;
          }
          puVar7 = puVar7 + 6;
          iVar6 = iVar6 + 0xc;
          iVar19 = iVar19 + 4;
          puVar13 = puVar13 + 2;
          iVar11 = iVar11 + -1;
        } while (iVar11 != 0);
      }
    }
    else if (*(int *)(iVar6 + 8) < 0x1a5e0) {
      iVar6 = 0;
      iVar14 = 0;
      puVar7 = local_88;
      puVar13 = local_98;
      iVar19 = 4;
      do {
        uVar8 = *puVar13;
        uVar1 = puVar13[1];
        iVar11 = *(int *)(*(int *)(param_1 + 0x1b0) + 8) * 0x40 + iVar6;
        iVar6 = iVar6 + 0xc;
        puVar13 = puVar13 + 2;
        puVar12 = (ushort *)(*(int *)(param_1 + 0x1b0) + iVar11 + 0xc);
        *puVar12 = *puVar7;
        *(undefined *)(puVar12 + 1) = *(undefined *)(puVar7 + 1);
        *(undefined *)((int)puVar12 + 3) = *(undefined *)((int)puVar7 + 3);
        *(undefined *)(puVar12 + 2) = *(undefined *)(puVar7 + 2);
        *(undefined *)((int)puVar12 + 5) = *(undefined *)((int)puVar7 + 5);
        *(undefined *)(puVar12 + 3) = *(undefined *)(puVar7 + 3);
        *(undefined *)((int)puVar12 + 7) = *(undefined *)((int)puVar7 + 7);
        *(undefined *)(puVar12 + 4) = *(undefined *)(puVar7 + 4);
        *(undefined *)((int)puVar12 + 9) = *(undefined *)((int)puVar7 + 9);
        puVar10 = puVar7 + 5;
        puVar7 = puVar7 + 6;
        *(undefined *)(puVar12 + 5) = *(undefined *)puVar10;
        iVar11 = *(int *)(*(int *)(param_1 + 0x1b0) + 8) * 0x40 + iVar14;
        iVar14 = iVar14 + 4;
        puVar10 = (ushort *)(*(int *)(param_1 + 0x1b0) + iVar11 + 0x3c);
        *puVar10 = uVar8;
        puVar10[1] = uVar1;
        iVar19 = iVar19 + -1;
      } while (iVar19 != 0);
      *(int *)(*(int *)(param_1 + 0x1b0) + 8) = *(int *)(*(int *)(param_1 + 0x1b0) + 8) + 1;
      **(int **)(param_1 + 0x1b0) = **(int **)(param_1 + 0x1b0) + 0x40;
    }
  }
  puVar13 = local_88;
  puVar10 = (ushort *)(param_1 + 0x154);
  uVar16 = 0;
  uVar17 = 0;
  puVar7 = puVar13;
  do {
    cVar9 = *(char *)(puVar7 + 5);
    uVar15 = 0x80000000 >> uVar17;
    if (cVar9 == -1) {
      cVar9 = GBAReady__6JoyBusFi(&Joybus,uVar17);
      if (cVar9 == '\0') {
        uVar16 = uVar16 | uVar15;
      }
      *(uint *)(param_1 + 0x1a8) = *(uint *)(param_1 + 0x1a8) & ~uVar15;
    }
    else if (cVar9 < -1) {
      if (cVar9 == -3) {
        *(uint *)(param_1 + 0x1a8) = *(uint *)(param_1 + 0x1a8) | uVar15;
      }
      else if (-4 < cVar9) {
        *(uint *)(param_1 + 0x1a8) = *(uint *)(param_1 + 0x1a8) & ~uVar15;
      }
    }
    else if (cVar9 < '\x01') {
      *(uint *)(param_1 + 0x1a8) = *(uint *)(param_1 + 0x1a8) | uVar15;
    }
    uVar17 = uVar17 + 1;
    puVar7 = puVar7 + 6;
  } while (uVar17 < 4);
  if ((uVar16 & 0xf0000000) != 0) {
    PADReset();
  }
  fVar2 = FLOAT_8032f820;
  *(ushort *)(param_1 + 0x1a0) = *puVar10;
  uVar17 = 0;
  *(undefined2 *)(param_1 + 0x158) = 0;
  *puVar10 = 0;
  *(undefined2 *)(param_1 + 0x1a2) = *(undefined2 *)(param_1 + 0x156);
  *(undefined2 *)(param_1 + 0x15a) = 0;
  *(undefined2 *)(param_1 + 0x156) = 0;
  *(undefined2 *)(param_1 + 0x15c) = *(undefined2 *)(param_1 + 0x15e);
  *(undefined4 *)(param_1 + 0x18c) = 0;
  *(undefined4 *)(param_1 + 400) = 0;
  *(undefined2 *)(param_1 + 0x15e) = 0;
  *(undefined2 *)(param_1 + 0x160) = 0;
  *(undefined2 *)(param_1 + 0x164) = 0;
  *(undefined2 *)(param_1 + 0x162) = 0;
  *(undefined *)(param_1 + 0x16b) = 0;
  *(undefined *)(param_1 + 0x16a) = 0;
  *(undefined *)(param_1 + 0x169) = 0;
  *(undefined *)(param_1 + 0x168) = 0;
  *(undefined *)(param_1 + 0x167) = 0;
  *(undefined *)(param_1 + 0x166) = 0;
  *(float *)(param_1 + 0x180) = fVar2;
  *(float *)(param_1 + 0x17c) = fVar2;
  *(float *)(param_1 + 0x178) = fVar2;
  *(float *)(param_1 + 0x174) = fVar2;
  *(float *)(param_1 + 0x170) = fVar2;
  *(float *)(param_1 + 0x16c) = fVar2;
  *(undefined2 *)(param_1 + 0x188) = 0;
  *(undefined2 *)(param_1 + 0x186) = 0;
  *(undefined2 *)(param_1 + 0x184) = 0;
  *(undefined4 *)(param_1 + 0x198) = 0;
  iVar6 = param_1;
  do {
    puVar12 = (ushort *)(iVar6 + 4);
    iVar14 = 0;
    iVar19 = 2;
    puVar7 = puVar10;
    do {
      if ((iVar14 != 0) || (*(char *)(puVar13 + 5) != -3)) {
        puVar12[0x26] = *(ushort *)(iVar6 + 0x34) | *puVar12;
        if (iVar14 == 0) {
          uVar8 = *puVar18;
          *(undefined2 *)(iVar6 + 0xc) = *(undefined2 *)(iVar6 + 0xe);
          uVar16 = countLeadingZeros(1 - (uVar8 & 0x3fff));
          *(undefined *)(iVar6 + 0x44) = *(undefined *)(puVar13 + 5);
          *(uint *)(iVar6 + 0x54) = uVar16 >> 5 & 0xff;
          *(undefined4 *)(iVar6 + 0x48) = 0;
          *(undefined4 *)(iVar6 + 0x3c) = 0;
          *(undefined4 *)(iVar6 + 0x40) = 0;
          if ((*(char *)(iVar6 + 0x44) == '\0') || ((*(byte *)puVar18 >> 6 & 1) != 0)) {
            if ((*(byte *)puVar18 >> 6 & 1) == 0) {
              *puVar12 = *puVar13;
            }
            else {
              *puVar12 = puVar18[1];
            }
            if (99 < *(byte *)(puVar13 + 3)) {
              *puVar12 = *puVar12 | 0x40;
            }
            if (99 < *(byte *)((int)puVar13 + 7)) {
              *puVar12 = *puVar12 | 0x20;
            }
            if (((MiniGamePcs._25732_4_ & 0x100) != 0) &&
               ((uVar16 = (int)*(char *)(iVar6 + 0x18) >> 0x1f,
                *(int *)(param_1 + 0x1c8) <= (int)((uVar16 ^ (int)*(char *)(iVar6 + 0x18)) - uVar16)
                || (uVar16 = (int)*(char *)(iVar6 + 0x19) >> 0x1f,
                   *(int *)(param_1 + 0x1c8) <=
                   (int)((uVar16 ^ (int)*(char *)(iVar6 + 0x19)) - uVar16))))) {
              *puVar12 = *puVar12 & 0xfff0;
              *(undefined4 *)(iVar6 + 0x40) = 1;
              if (*(int *)(param_1 + 0x1c8) <= (int)*(char *)(iVar6 + 0x18)) {
                *puVar12 = *puVar12 | 2;
              }
              if ((int)*(char *)(iVar6 + 0x18) <= -*(int *)(param_1 + 0x1c8)) {
                *puVar12 = *puVar12 | 1;
              }
              if (*(int *)(param_1 + 0x1c8) <= (int)*(char *)(iVar6 + 0x19)) {
                *puVar12 = *puVar12 | 8;
              }
              if ((int)*(char *)(iVar6 + 0x19) <= -*(int *)(param_1 + 0x1c8)) {
                *puVar12 = *puVar12 | 4;
              }
            }
            *(uint *)(iVar6 + 0x48) = *(uint *)(iVar6 + 0x48) | 1;
            *(undefined *)(iVar6 + 0x18) = *(undefined *)(puVar13 + 1);
            *(undefined2 *)(iVar6 + 0xe) = 0;
            if (*(char *)(iVar6 + 0x18) < '\0') {
              *(ushort *)(iVar6 + 0xe) = *(ushort *)(iVar6 + 0xe) | 1;
            }
            if ('\0' < *(char *)(iVar6 + 0x18)) {
              *(ushort *)(iVar6 + 0xe) = *(ushort *)(iVar6 + 0xe) | 2;
            }
            *(undefined *)(iVar6 + 0x19) = *(undefined *)((int)puVar13 + 3);
            if (*(char *)(iVar6 + 0x19) < '\0') {
              *(ushort *)(iVar6 + 0xe) = *(ushort *)(iVar6 + 0xe) | 4;
            }
            if ('\0' < *(char *)(iVar6 + 0x19)) {
              *(ushort *)(iVar6 + 0xe) = *(ushort *)(iVar6 + 0xe) | 8;
            }
            dVar4 = DOUBLE_8032f830;
            local_58 = 0x43300000;
            *(undefined *)(iVar6 + 0x1a) = *(undefined *)(puVar13 + 2);
            dVar5 = DOUBLE_8032f838;
            fVar2 = FLOAT_8032f824;
            local_50 = 0x43300000;
            *(undefined *)(iVar6 + 0x1b) = *(undefined *)((int)puVar13 + 5);
            fVar3 = FLOAT_8032f828;
            local_48 = 0x43300000;
            *(undefined *)(iVar6 + 0x16) = *(undefined *)(puVar13 + 3);
            local_40 = 0x43300000;
            *(undefined *)(iVar6 + 0x17) = *(undefined *)((int)puVar13 + 7);
            local_38 = 0x43300000;
            uStack_54 = (int)*(char *)(iVar6 + 0x18) ^ 0x80000000;
            local_30 = 0x43300000;
            *(float *)(iVar6 + 0x24) =
                 (float)((double)CONCAT44(0x43300000,uStack_54) - dVar4) * fVar2;
            uStack_4c = (int)*(char *)(iVar6 + 0x19) ^ 0x80000000;
            *(float *)(iVar6 + 0x28) =
                 (float)((double)CONCAT44(0x43300000,uStack_4c) - dVar4) * fVar2;
            uStack_44 = (int)*(char *)(iVar6 + 0x1a) ^ 0x80000000;
            *(float *)(iVar6 + 0x2c) =
                 (float)((double)CONCAT44(0x43300000,uStack_44) - dVar4) * fVar2;
            uStack_3c = (int)*(char *)(iVar6 + 0x1b) ^ 0x80000000;
            *(float *)(iVar6 + 0x30) =
                 (float)((double)CONCAT44(0x43300000,uStack_3c) - dVar4) * fVar2;
            uStack_34 = (uint)*(byte *)(iVar6 + 0x16);
            *(float *)(iVar6 + 0x1c) =
                 (float)((double)CONCAT44(0x43300000,(uint)*(byte *)(iVar6 + 0x16)) - dVar5) / fVar3
            ;
            uStack_2c = (uint)*(byte *)(iVar6 + 0x17);
            *(float *)(iVar6 + 0x20) =
                 (float)((double)CONCAT44(0x43300000,(uint)*(byte *)(iVar6 + 0x17)) - dVar5) / fVar3
            ;
          }
          else {
            *puVar12 = 0;
            fVar2 = FLOAT_8032f820;
            *(undefined *)(iVar6 + 0x18) = 0;
            *(undefined *)(iVar6 + 0x19) = 0;
            *(undefined *)(iVar6 + 0x1a) = 0;
            *(undefined *)(iVar6 + 0x1b) = 0;
            *(undefined *)(iVar6 + 0x16) = 0;
            *(undefined *)(iVar6 + 0x17) = 0;
            *(float *)(iVar6 + 0x24) = fVar2;
            *(float *)(iVar6 + 0x28) = fVar2;
            *(float *)(iVar6 + 0x2c) = fVar2;
            *(float *)(iVar6 + 0x30) = fVar2;
            *(float *)(iVar6 + 0x1c) = fVar2;
            *(float *)(iVar6 + 0x20) = fVar2;
          }
        }
        else if ((char)*(byte *)puVar18 < '\0') {
          uVar8 = puVar18[1];
          *(uint *)(iVar6 + 0x48) = *(uint *)(iVar6 + 0x48) | 1;
          *puVar12 = uVar8;
        }
        puVar12[2] = *puVar12 & (puVar12[0x26] ^ *puVar12);
        if (iVar14 == 0) {
          *(ushort *)(iVar6 + 0x12) = puVar12[0x26] & (puVar12[0x26] ^ *puVar12);
          *(ushort *)(iVar6 + 0x10) =
               *(ushort *)(iVar6 + 0xe) & (*(ushort *)(iVar6 + 0xc) ^ *(ushort *)(iVar6 + 0xe));
          *(ushort *)(iVar6 + 0x14) = puVar12[0x26] & *puVar12 & 0x1f7f;
          if (*(short *)(iVar6 + 0x14) == 0) {
            *(undefined4 *)(iVar6 + 0x4c) = 0;
          }
          else {
            *(int *)(iVar6 + 0x4c) = *(int *)(iVar6 + 0x4c) + 1;
            if (*(uint *)(iVar6 + 0x4c) < 0x10) {
              *(undefined2 *)(iVar6 + 0x14) = 0;
            }
            else if ((*(uint *)(iVar6 + 0x4c) & 1) != 0) {
              *(undefined2 *)(iVar6 + 0x14) = 0;
            }
          }
          *(ushort *)(iVar6 + 0x14) = *(ushort *)(iVar6 + 0x14) | puVar12[2];
          if (*(int *)(iVar6 + 0x3c) == 0) {
            *(undefined2 *)(iVar6 + 0x38) = 0;
            *(undefined2 *)(iVar6 + 0x36) = 0;
            *(undefined2 *)(iVar6 + 0x34) = 0;
          }
          else {
            *(ushort *)(iVar6 + 0x34) = *puVar12;
            *(ushort *)(iVar6 + 0x36) = puVar12[2];
            *(undefined2 *)(iVar6 + 0x38) = *(undefined2 *)(iVar6 + 0x14);
            *(undefined2 *)(iVar6 + 0xe) = 0;
            *(undefined2 *)(iVar6 + 0x10) = 0;
            *(undefined2 *)(iVar6 + 0x14) = 0;
            puVar12[2] = 0;
            *(undefined2 *)(iVar6 + 0x12) = 0;
            *puVar12 = 0;
          }
        }
        puVar7[2] = puVar7[2] | puVar12[2];
        *puVar7 = *puVar7 | *puVar12;
        if (iVar14 == 0) {
          *(uint *)(param_1 + 0x18c) = *(uint *)(param_1 + 0x18c) | *(uint *)(iVar6 + 0x3c);
          *(uint *)(param_1 + 400) = *(uint *)(param_1 + 400) | *(uint *)(iVar6 + 0x40);
          *(ushort *)(param_1 + 0x162) = *(ushort *)(param_1 + 0x162) | *(ushort *)(iVar6 + 0x12);
          *(ushort *)(param_1 + 0x15e) = *(ushort *)(param_1 + 0x15e) | *(ushort *)(iVar6 + 0xe);
          *(ushort *)(param_1 + 0x160) = *(ushort *)(param_1 + 0x160) | *(ushort *)(iVar6 + 0x10);
          *(ushort *)(param_1 + 0x164) = *(ushort *)(param_1 + 0x164) | *(ushort *)(iVar6 + 0x14);
          *(ushort *)(param_1 + 0x186) = *(ushort *)(param_1 + 0x186) | *(ushort *)(iVar6 + 0x36);
          *(ushort *)(param_1 + 0x184) = *(ushort *)(param_1 + 0x184) | *(ushort *)(iVar6 + 0x34);
          *(ushort *)(param_1 + 0x188) = *(ushort *)(param_1 + 0x188) | *(ushort *)(iVar6 + 0x38);
          cVar9 = *(char *)(iVar6 + 0x18);
          uVar15 = (int)*(char *)(param_1 + 0x168) >> 0x1f;
          uVar16 = (int)cVar9 >> 0x1f;
          if ((int)((uVar15 ^ (int)*(char *)(param_1 + 0x168)) - uVar15) <
              (int)((uVar16 ^ (int)cVar9) - uVar16)) {
            *(char *)(param_1 + 0x168) = cVar9;
            *(undefined4 *)(param_1 + 0x174) = *(undefined4 *)(iVar6 + 0x24);
          }
          cVar9 = *(char *)(iVar6 + 0x19);
          uVar15 = (int)*(char *)(param_1 + 0x169) >> 0x1f;
          uVar16 = (int)cVar9 >> 0x1f;
          if ((int)((uVar15 ^ (int)*(char *)(param_1 + 0x169)) - uVar15) <
              (int)((uVar16 ^ (int)cVar9) - uVar16)) {
            *(char *)(param_1 + 0x169) = cVar9;
            *(undefined4 *)(param_1 + 0x178) = *(undefined4 *)(iVar6 + 0x28);
          }
          cVar9 = *(char *)(iVar6 + 0x1a);
          uVar15 = (int)*(char *)(param_1 + 0x16a) >> 0x1f;
          uVar16 = (int)cVar9 >> 0x1f;
          if ((int)((uVar15 ^ (int)*(char *)(param_1 + 0x16a)) - uVar15) <
              (int)((uVar16 ^ (int)cVar9) - uVar16)) {
            *(char *)(param_1 + 0x16a) = cVar9;
            *(undefined4 *)(param_1 + 0x17c) = *(undefined4 *)(iVar6 + 0x2c);
          }
          cVar9 = *(char *)(iVar6 + 0x1b);
          uVar15 = (int)*(char *)(param_1 + 0x16b) >> 0x1f;
          uVar16 = (int)cVar9 >> 0x1f;
          if ((int)((uVar15 ^ (int)*(char *)(param_1 + 0x16b)) - uVar15) <
              (int)((uVar16 ^ (int)cVar9) - uVar16)) {
            *(char *)(param_1 + 0x16b) = cVar9;
            *(undefined4 *)(param_1 + 0x180) = *(undefined4 *)(iVar6 + 0x30);
          }
          if (*(byte *)(param_1 + 0x166) < *(byte *)(iVar6 + 0x16)) {
            *(byte *)(param_1 + 0x166) = *(byte *)(iVar6 + 0x16);
            *(undefined4 *)(param_1 + 0x16c) = *(undefined4 *)(iVar6 + 0x1c);
          }
          if (*(byte *)(param_1 + 0x167) < *(byte *)(iVar6 + 0x17)) {
            *(byte *)(param_1 + 0x167) = *(byte *)(iVar6 + 0x17);
            *(undefined4 *)(param_1 + 0x170) = *(undefined4 *)(iVar6 + 0x20);
          }
        }
      }
      puVar12 = puVar12 + 1;
      puVar7 = puVar7 + 1;
      iVar14 = iVar14 + 1;
      iVar19 = iVar19 + -1;
    } while (iVar19 != 0);
    uVar17 = uVar17 + 1;
    puVar13 = puVar13 + 6;
    puVar18 = puVar18 + 2;
    iVar6 = iVar6 + 0x54;
  } while (uVar17 < 4);
  if (-1 < *(int *)(param_1 + 0x1bc)) {
    *(int *)(param_1 + 0x1bc) = *(int *)(param_1 + 0x1bc) + 1;
  }
  return;
}


// Function: __AXServiceVPB
// Entry: 80193270
// Size: 1800 bytes

void __AXServiceVPB(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  uint uVar8;
  uint uVar9;
  
  DAT_8032f298 = DAT_8032f298 + 1;
  iVar5 = *(int *)(param_1 + 0x18);
  uVar4 = *(uint *)(param_1 + 0x1c);
  iVar6 = iVar5 * 0xec;
  if (uVar4 == 0) {
    *(undefined2 *)(param_1 + 0x146) = *(undefined2 *)((int)&DAT_8031494c + iVar6 + 2);
    *(undefined2 *)(param_1 + 0x19c) = *(undefined2 *)(&DAT_803149a4 + iVar6);
    *(undefined2 *)(param_1 + 0x1b2) = *(undefined2 *)(&DAT_803149ba + iVar6);
    *(undefined2 *)(param_1 + 0x1b4) = *(undefined2 *)(&DAT_803149bc + iVar6);
    return;
  }
  if ((uVar4 & 0x80000000) != 0) {
    *(undefined4 *)(&DAT_80314940 + iVar5 * 0x76) = *(undefined4 *)(param_1 + 0x138);
    *(undefined4 *)(&DAT_80314944 + iVar5 * 0x76) = *(undefined4 *)(param_1 + 0x13c);
    (&DAT_80314948)[iVar5 * 0x3b] = *(undefined4 *)(param_1 + 0x140);
    (&DAT_8031494c)[iVar5 * 0x3b] = *(undefined4 *)(param_1 + 0x144);
    (&DAT_80314950)[iVar5 * 0x3b] = *(undefined4 *)(param_1 + 0x148);
    (&DAT_80314954)[iVar5 * 0x3b] = *(undefined4 *)(param_1 + 0x14c);
    (&DAT_80314958)[iVar5 * 0x3b] = *(undefined4 *)(param_1 + 0x150);
    (&DAT_8031495c)[iVar5 * 0x3b] = *(undefined4 *)(param_1 + 0x154);
    (&DAT_80314960)[iVar5 * 0x3b] = *(undefined4 *)(param_1 + 0x158);
    (&DAT_80314964)[iVar5 * 0x3b] = *(undefined4 *)(param_1 + 0x15c);
    (&DAT_80314968)[iVar5 * 0x3b] = *(undefined4 *)(param_1 + 0x160);
    (&DAT_8031496c)[iVar5 * 0x3b] = *(undefined4 *)(param_1 + 0x164);
    (&DAT_80314970)[iVar5 * 0x3b] = *(undefined4 *)(param_1 + 0x168);
    (&DAT_80314974)[iVar5 * 0x3b] = *(undefined4 *)(param_1 + 0x16c);
    (&DAT_80314978)[iVar5 * 0x3b] = *(undefined4 *)(param_1 + 0x170);
    (&DAT_8031497c)[iVar5 * 0x3b] = *(undefined4 *)(param_1 + 0x174);
    *(undefined4 *)(&DAT_80314980 + iVar6) = *(undefined4 *)(param_1 + 0x178);
    *(undefined4 *)(&DAT_80314984 + iVar6) = *(undefined4 *)(param_1 + 0x17c);
    *(undefined4 *)(&DAT_80314988 + iVar6) = *(undefined4 *)(param_1 + 0x180);
    *(undefined4 *)(&DAT_8031498c + iVar6) = *(undefined4 *)(param_1 + 0x184);
    *(undefined4 *)(&DAT_80314990 + iVar5 * 0x76) = *(undefined4 *)(param_1 + 0x188);
    *(undefined4 *)(&DAT_80314994 + iVar6) = *(undefined4 *)(param_1 + 0x18c);
    *(undefined4 *)(&DAT_80314998 + iVar6) = *(undefined4 *)(param_1 + 400);
    *(undefined4 *)(&DAT_8031499c + iVar6) = *(undefined4 *)(param_1 + 0x194);
    *(undefined4 *)(&DAT_803149a0 + iVar6) = *(undefined4 *)(param_1 + 0x198);
    *(undefined4 *)(&DAT_803149a4 + iVar6) = *(undefined4 *)(param_1 + 0x19c);
    *(undefined4 *)(&DAT_803149a8 + iVar6) = *(undefined4 *)(param_1 + 0x1a0);
    *(undefined4 *)(&DAT_803149ac + iVar6) = *(undefined4 *)(param_1 + 0x1a4);
    *(undefined4 *)(&DAT_803149b0 + iVar6) = *(undefined4 *)(param_1 + 0x1a8);
    *(undefined4 *)(&DAT_803149b4 + iVar6) = *(undefined4 *)(param_1 + 0x1ac);
    *(undefined4 *)(&DAT_803149b8 + iVar6) = *(undefined4 *)(param_1 + 0x1b0);
    *(undefined4 *)(&DAT_803149bc + iVar6) = *(undefined4 *)(param_1 + 0x1b4);
    *(undefined4 *)(&DAT_803149c0 + iVar6) = *(undefined4 *)(param_1 + 0x1b8);
    *(undefined4 *)(&DAT_803149c4 + iVar6) = *(undefined4 *)(param_1 + 0x1bc);
    *(undefined4 *)(&DAT_803149c8 + iVar6) = *(undefined4 *)(param_1 + 0x1c0);
    *(undefined4 *)(&DAT_803149cc + iVar6) = *(undefined4 *)(param_1 + 0x1c4);
    *(undefined4 *)(&DAT_803149d0 + iVar6) = *(undefined4 *)(param_1 + 0x1c8);
    *(undefined4 *)(&DAT_803149d4 + iVar6) = *(undefined4 *)(param_1 + 0x1cc);
    *(undefined4 *)(&DAT_803149d8 + iVar6) = *(undefined4 *)(param_1 + 0x1d0);
    *(undefined4 *)(&DAT_803149dc + iVar6) = *(undefined4 *)(param_1 + 0x1d4);
    *(undefined4 *)(&DAT_803149e0 + iVar6) = *(undefined4 *)(param_1 + 0x1d8);
    *(undefined4 *)(&DAT_803149e4 + iVar6) = *(undefined4 *)(param_1 + 0x1dc);
    *(undefined4 *)(&DAT_803149e8 + iVar6) = *(undefined4 *)(param_1 + 0x1e0);
    *(undefined4 *)(&DAT_803149ec + iVar6) = *(undefined4 *)(param_1 + 0x1e4);
    *(undefined4 *)(&DAT_803149f0 + iVar6) = *(undefined4 *)(param_1 + 0x1e8);
    *(undefined4 *)(&DAT_803149f4 + iVar6) = *(undefined4 *)(param_1 + 0x1ec);
    *(undefined4 *)(&DAT_803149f8 + iVar6) = *(undefined4 *)(param_1 + 0x1f0);
    *(undefined4 *)(&DAT_803149fc + iVar6) = *(undefined4 *)(param_1 + 500);
    *(undefined4 *)(&DAT_80314a00 + iVar6) = *(undefined4 *)(param_1 + 0x1f8);
    *(undefined4 *)(&DAT_80314a04 + iVar6) = *(undefined4 *)(param_1 + 0x1fc);
    *(undefined4 *)(&DAT_80314a08 + iVar6) = *(undefined4 *)(param_1 + 0x200);
    *(undefined4 *)(&DAT_80314a0c + iVar6) = *(undefined4 *)(param_1 + 0x204);
    uVar4 = *(uint *)(param_1 + 0x28);
    if (uVar4 == 0) {
      return;
    }
    puVar3 = (undefined4 *)(param_1 + 0x34);
    puVar7 = (undefined4 *)(&DAT_80319440 + *(int *)(param_1 + 0x18) * 0x100);
    if (uVar4 != 0) {
      uVar8 = uVar4 >> 3;
      if (uVar8 != 0) {
        do {
          *puVar3 = *puVar7;
          puVar3[1] = puVar7[1];
          puVar3[2] = puVar7[2];
          puVar3[3] = puVar7[3];
          puVar3[4] = puVar7[4];
          puVar3[5] = puVar7[5];
          puVar3[6] = puVar7[6];
          puVar1 = puVar7 + 7;
          puVar7 = puVar7 + 8;
          puVar3[7] = *puVar1;
          puVar3 = puVar3 + 8;
          uVar8 = uVar8 - 1;
        } while (uVar8 != 0);
        uVar4 = uVar4 & 7;
        if (uVar4 == 0) {
          return;
        }
      }
      do {
        uVar2 = *puVar7;
        puVar7 = puVar7 + 1;
        *puVar3 = uVar2;
        puVar3 = puVar3 + 1;
        uVar4 = uVar4 - 1;
      } while (uVar4 != 0);
      return;
    }
    return;
  }
  if ((uVar4 & 1) != 0) {
    *(undefined2 *)(&DAT_80314948 + iVar5 * 0x3b) = *(undefined2 *)(param_1 + 0x140);
    *(undefined2 *)((int)&DAT_80314948 + iVar6 + 2) = *(undefined2 *)(param_1 + 0x142);
  }
  if ((uVar4 & 2) != 0) {
    *(undefined2 *)(&DAT_8031494c + iVar5 * 0x3b) = *(undefined2 *)(param_1 + 0x144);
  }
  if ((uVar4 & 4) == 0) {
    *(undefined2 *)(param_1 + 0x146) = *(undefined2 *)((int)&DAT_8031494c + iVar6 + 2);
  }
  else {
    *(undefined2 *)((int)&DAT_8031494c + iVar6 + 2) = *(undefined2 *)(param_1 + 0x146);
  }
  if ((uVar4 & 8) != 0) {
    *(undefined2 *)(&DAT_80314950 + iVar5 * 0x3b) = *(undefined2 *)(param_1 + 0x148);
  }
  if ((uVar4 & 0x10) != 0) {
    *(undefined2 *)((int)&DAT_80314950 + iVar6 + 2) = *(undefined2 *)(param_1 + 0x14a);
    *(undefined2 *)(&DAT_80314954 + iVar5 * 0x3b) = *(undefined2 *)(param_1 + 0x14c);
    *(undefined2 *)((int)&DAT_80314954 + iVar6 + 2) = *(undefined2 *)(param_1 + 0x14e);
    *(undefined2 *)(&DAT_80314958 + iVar5 * 0x3b) = *(undefined2 *)(param_1 + 0x150);
    *(undefined2 *)((int)&DAT_80314958 + iVar6 + 2) = *(undefined2 *)(param_1 + 0x152);
    *(undefined2 *)(&DAT_8031495c + iVar5 * 0x3b) = *(undefined2 *)(param_1 + 0x154);
    *(undefined2 *)((int)&DAT_8031495c + iVar6 + 2) = *(undefined2 *)(param_1 + 0x156);
    *(undefined2 *)(&DAT_80314960 + iVar5 * 0x3b) = *(undefined2 *)(param_1 + 0x158);
    *(undefined2 *)((int)&DAT_80314960 + iVar6 + 2) = *(undefined2 *)(param_1 + 0x15a);
    *(undefined2 *)(&DAT_80314964 + iVar5 * 0x3b) = *(undefined2 *)(param_1 + 0x15c);
    *(undefined2 *)((int)&DAT_80314964 + iVar6 + 2) = *(undefined2 *)(param_1 + 0x15e);
    *(undefined2 *)(&DAT_80314968 + iVar5 * 0x3b) = *(undefined2 *)(param_1 + 0x160);
    *(undefined2 *)((int)&DAT_80314968 + iVar6 + 2) = *(undefined2 *)(param_1 + 0x162);
    *(undefined2 *)(&DAT_8031496c + iVar5 * 0x3b) = *(undefined2 *)(param_1 + 0x164);
    *(undefined2 *)((int)&DAT_8031496c + iVar6 + 2) = *(undefined2 *)(param_1 + 0x166);
    *(undefined2 *)(&DAT_80314970 + iVar5 * 0x3b) = *(undefined2 *)(param_1 + 0x168);
    *(undefined2 *)((int)&DAT_80314970 + iVar6 + 2) = *(undefined2 *)(param_1 + 0x16a);
    *(undefined2 *)(&DAT_80314974 + iVar5 * 0x3b) = *(undefined2 *)(param_1 + 0x16c);
  }
  if ((uVar4 & 0x40) == 0) {
    if ((uVar4 & 0x20) != 0) {
      *(undefined2 *)((int)&DAT_80314974 + iVar6 + 2) = *(undefined2 *)(param_1 + 0x16e);
      *(undefined2 *)(&DAT_80314978 + iVar5 * 0x3b) = *(undefined2 *)(param_1 + 0x170);
      *(undefined2 *)((int)&DAT_80314978 + iVar6 + 2) = *(undefined2 *)(param_1 + 0x172);
      *(undefined2 *)(&DAT_8031497c + iVar5 * 0x3b) = *(undefined2 *)(param_1 + 0x174);
      *(undefined2 *)((int)&DAT_8031497c + iVar6 + 2) = *(undefined2 *)(param_1 + 0x176);
      *(undefined2 *)(&DAT_80314980 + iVar6) = *(undefined2 *)(param_1 + 0x178);
      *(undefined2 *)(&DAT_80314982 + iVar6) = *(undefined2 *)(param_1 + 0x17a);
      puVar3 = *(undefined4 **)(param_1 + 0x134);
      *puVar3 = 0;
      puVar3[1] = 0;
      puVar3[2] = 0;
      puVar3[3] = 0;
      puVar3[4] = 0;
      puVar3[5] = 0;
      puVar3[6] = 0;
      puVar3[7] = 0;
      puVar3[8] = 0;
      puVar3[9] = 0;
      puVar3[10] = 0;
      puVar3[0xb] = 0;
      puVar3[0xc] = 0;
      puVar3[0xd] = 0;
      puVar3[0xe] = 0;
      puVar3[0xf] = 0;
    }
  }
  else {
    *(undefined2 *)(&DAT_80314980 + iVar6) = *(undefined2 *)(param_1 + 0x178);
    *(undefined2 *)(&DAT_80314982 + iVar6) = *(undefined2 *)(param_1 + 0x17a);
  }
  if ((uVar4 & 0x80) != 0) {
    *(undefined2 *)(&DAT_80314984 + iVar6) = *(undefined2 *)(param_1 + 0x17c);
    *(undefined2 *)(&DAT_80314986 + iVar6) = *(undefined2 *)(param_1 + 0x17e);
    *(undefined2 *)(&DAT_80314988 + iVar6) = *(undefined2 *)(param_1 + 0x180);
    *(undefined2 *)(&DAT_8031498a + iVar6) = *(undefined2 *)(param_1 + 0x182);
    *(undefined2 *)(&DAT_8031498c + iVar6) = *(undefined2 *)(param_1 + 0x184);
    uVar8 = *(uint *)(param_1 + 0x28);
    if (uVar8 != 0) {
      puVar3 = (undefined4 *)(param_1 + 0x34);
      puVar7 = (undefined4 *)(&DAT_80319440 + *(int *)(param_1 + 0x18) * 0x100);
      if (uVar8 != 0) {
        uVar9 = uVar8 >> 3;
        if (uVar9 != 0) {
          do {
            *puVar7 = *puVar3;
            puVar7[1] = puVar3[1];
            puVar7[2] = puVar3[2];
            puVar7[3] = puVar3[3];
            puVar7[4] = puVar3[4];
            puVar7[5] = puVar3[5];
            puVar7[6] = puVar3[6];
            puVar1 = puVar3 + 7;
            puVar3 = puVar3 + 8;
            puVar7[7] = *puVar1;
            puVar7 = puVar7 + 8;
            uVar9 = uVar9 - 1;
          } while (uVar9 != 0);
          uVar8 = uVar8 & 7;
          if (uVar8 == 0) goto LAB_80193768;
        }
        do {
          uVar2 = *puVar3;
          puVar3 = puVar3 + 1;
          *puVar7 = uVar2;
          puVar7 = puVar7 + 1;
          uVar8 = uVar8 - 1;
        } while (uVar8 != 0);
      }
    }
  }
LAB_80193768:
  if ((uVar4 & 0x100) != 0) {
    *(undefined2 *)(&DAT_80314992 + iVar6) = *(undefined2 *)(param_1 + 0x18a);
    *(undefined2 *)(&DAT_80314994 + iVar6) = *(undefined2 *)(param_1 + 0x18c);
    *(undefined2 *)(&DAT_80314996 + iVar6) = *(undefined2 *)(param_1 + 0x18e);
    *(undefined2 *)(&DAT_80314998 + iVar6) = *(undefined2 *)(param_1 + 400);
    *(undefined2 *)(&DAT_8031499a + iVar6) = *(undefined2 *)(param_1 + 0x192);
    *(undefined2 *)(&DAT_8031499c + iVar6) = *(undefined2 *)(param_1 + 0x194);
    *(undefined2 *)(&DAT_8031499e + iVar6) = *(undefined2 *)(param_1 + 0x196);
    *(undefined2 *)(&DAT_803149a0 + iVar6) = *(undefined2 *)(param_1 + 0x198);
    *(undefined2 *)(&DAT_803149a2 + iVar6) = *(undefined2 *)(param_1 + 0x19a);
  }
  if ((uVar4 & 0x400) == 0) {
    if ((uVar4 & 0x200) != 0) {
      *(undefined2 *)(&DAT_803149a4 + iVar6) = *(undefined2 *)(param_1 + 0x19c);
      *(undefined2 *)(&DAT_803149a6 + iVar6) = *(undefined2 *)(param_1 + 0x19e);
    }
  }
  else {
    *(undefined2 *)(param_1 + 0x19c) = *(undefined2 *)(&DAT_803149a4 + iVar6);
    *(undefined2 *)(&DAT_803149a6 + iVar6) = *(undefined2 *)(param_1 + 0x19e);
  }
  if ((uVar4 & 0x800) != 0) {
    *(undefined2 *)(&DAT_803149a8 + iVar6) = *(undefined2 *)(param_1 + 0x1a0);
    *(undefined2 *)(&DAT_803149aa + iVar6) = *(undefined2 *)(param_1 + 0x1a2);
    *(undefined2 *)(&DAT_803149ac + iVar6) = *(undefined2 *)(param_1 + 0x1a4);
  }
  if ((uVar4 & 0x1e000) == 0) {
    if ((uVar4 & 0x1000) == 0) {
      *(undefined2 *)(param_1 + 0x1b2) = *(undefined2 *)(&DAT_803149ba + iVar6);
      *(undefined2 *)(param_1 + 0x1b4) = *(undefined2 *)(&DAT_803149bc + iVar6);
    }
    else {
      *(undefined4 *)(&DAT_803149ae + iVar6) = *(undefined4 *)(param_1 + 0x1a6);
      *(undefined4 *)(&DAT_803149b2 + iVar6) = *(undefined4 *)(param_1 + 0x1aa);
      *(undefined4 *)(&DAT_803149b6 + iVar6) = *(undefined4 *)(param_1 + 0x1ae);
      *(undefined4 *)(&DAT_803149ba + iVar6) = *(undefined4 *)(param_1 + 0x1b2);
    }
  }
  else {
    if ((uVar4 & 0x2000) != 0) {
      *(undefined2 *)(&DAT_803149ae + iVar6) = *(undefined2 *)(param_1 + 0x1a6);
    }
    if ((uVar4 & 0x4000) != 0) {
      *(undefined4 *)(&DAT_803149b2 + iVar6) = *(undefined4 *)(param_1 + 0x1aa);
    }
    if ((uVar4 & 0x8000) != 0) {
      *(undefined4 *)(&DAT_803149b6 + iVar6) = *(undefined4 *)(param_1 + 0x1ae);
    }
    if ((uVar4 & 0x10000) == 0) {
      *(undefined4 *)(param_1 + 0x1b2) = *(undefined4 *)(&DAT_803149ba + iVar6);
    }
    else {
      *(undefined4 *)(&DAT_803149ba + iVar6) = *(undefined4 *)(param_1 + 0x1b2);
    }
  }
  if ((uVar4 & 0x20000) != 0) {
    *(undefined4 *)(&DAT_803149be + iVar6) = *(undefined4 *)(param_1 + 0x1b6);
    *(undefined4 *)(&DAT_803149c2 + iVar6) = *(undefined4 *)(param_1 + 0x1ba);
    *(undefined4 *)(&DAT_803149c6 + iVar6) = *(undefined4 *)(param_1 + 0x1be);
    *(undefined4 *)(&DAT_803149ca + iVar6) = *(undefined4 *)(param_1 + 0x1c2);
    *(undefined4 *)(&DAT_803149ce + iVar6) = *(undefined4 *)(param_1 + 0x1c6);
    *(undefined4 *)(&DAT_803149d2 + iVar6) = *(undefined4 *)(param_1 + 0x1ca);
    *(undefined4 *)(&DAT_803149d6 + iVar6) = *(undefined4 *)(param_1 + 0x1ce);
    *(undefined4 *)(&DAT_803149da + iVar6) = *(undefined4 *)(param_1 + 0x1d2);
    *(undefined4 *)(&DAT_803149de + iVar6) = *(undefined4 *)(param_1 + 0x1d6);
    *(undefined4 *)(&DAT_803149e2 + iVar6) = *(undefined4 *)(param_1 + 0x1da);
  }
  if ((uVar4 & 0x80000) == 0) {
    if ((uVar4 & 0x40000) != 0) {
      *(undefined2 *)(&DAT_803149e6 + iVar6) = *(undefined2 *)(param_1 + 0x1de);
      *(undefined2 *)(&DAT_803149e8 + iVar6) = *(undefined2 *)(param_1 + 0x1e0);
      *(undefined2 *)(&DAT_803149ea + iVar6) = *(undefined2 *)(param_1 + 0x1e2);
      *(undefined2 *)(&DAT_803149ec + iVar6) = *(undefined2 *)(param_1 + 0x1e4);
      *(undefined2 *)(&DAT_803149ee + iVar6) = *(undefined2 *)(param_1 + 0x1e6);
      *(undefined2 *)(&DAT_803149f0 + iVar6) = *(undefined2 *)(param_1 + 0x1e8);
      *(undefined2 *)(&DAT_803149f2 + iVar6) = *(undefined2 *)(param_1 + 0x1ea);
    }
  }
  else {
    *(undefined2 *)(&DAT_803149e6 + iVar6) = *(undefined2 *)(param_1 + 0x1de);
    *(undefined2 *)(&DAT_803149e8 + iVar6) = *(undefined2 *)(param_1 + 0x1e0);
  }
  if ((uVar4 & 0x100000) != 0) {
    *(undefined2 *)(&DAT_803149f4 + iVar6) = *(undefined2 *)(param_1 + 0x1ec);
    *(undefined2 *)(&DAT_803149f6 + iVar6) = *(undefined2 *)(param_1 + 0x1ee);
    *(undefined2 *)(&DAT_803149f8 + iVar6) = *(undefined2 *)(param_1 + 0x1f0);
    return;
  }
  return;
}


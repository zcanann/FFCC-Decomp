// Function: LetterLstBaseDraw__8CMenuPcsFf
// Entry: 8016398c
// Size: 1616 bytes

/* WARNING: Removing unreachable block (ram,0x80163fb8) */
/* WARNING: Removing unreachable block (ram,0x80163fb0) */
/* WARNING: Removing unreachable block (ram,0x80163fa8) */
/* WARNING: Removing unreachable block (ram,0x80163fa0) */
/* WARNING: Removing unreachable block (ram,0x80163f98) */
/* WARNING: Removing unreachable block (ram,0x80163f90) */
/* WARNING: Removing unreachable block (ram,0x80163f88) */
/* WARNING: Removing unreachable block (ram,0x80163f80) */
/* WARNING: Removing unreachable block (ram,0x80163f78) */
/* WARNING: Removing unreachable block (ram,0x80163f70) */
/* WARNING: Removing unreachable block (ram,0x80163f68) */
/* WARNING: Removing unreachable block (ram,0x80163f60) */
/* WARNING: Removing unreachable block (ram,0x80163f58) */
/* WARNING: Removing unreachable block (ram,0x80163f50) */
/* WARNING: Removing unreachable block (ram,0x80163a04) */
/* WARNING: Removing unreachable block (ram,0x801639fc) */
/* WARNING: Removing unreachable block (ram,0x801639f4) */
/* WARNING: Removing unreachable block (ram,0x801639ec) */
/* WARNING: Removing unreachable block (ram,0x801639e4) */
/* WARNING: Removing unreachable block (ram,0x801639dc) */
/* WARNING: Removing unreachable block (ram,0x801639d4) */
/* WARNING: Removing unreachable block (ram,0x801639cc) */
/* WARNING: Removing unreachable block (ram,0x801639c4) */
/* WARNING: Removing unreachable block (ram,0x801639bc) */
/* WARNING: Removing unreachable block (ram,0x801639b4) */
/* WARNING: Removing unreachable block (ram,0x801639ac) */
/* WARNING: Removing unreachable block (ram,0x801639a4) */
/* WARNING: Removing unreachable block (ram,0x8016399c) */

void LetterLstBaseDraw__8CMenuPcsFf(double param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  undefined4 local_140;
  undefined4 local_13c;
  longlong local_138;
  undefined4 local_130;
  uint uStack_12c;
  longlong local_128;
  undefined4 local_120;
  uint uStack_11c;
  longlong local_118;
  undefined4 local_110;
  uint uStack_10c;
  longlong local_108;
  undefined4 local_100;
  uint uStack_fc;
  
  if ((double)FLOAT_803330bc < param_1) {
    local_130 = 0x43300000;
    local_120 = 0x43300000;
    local_108 = (longlong)(int)((double)FLOAT_803330f0 - DOUBLE_803330e8);
    local_110 = 0x43300000;
    local_100 = 0x43300000;
    local_128 = (longlong)(int)((double)FLOAT_803330e0 - DOUBLE_803330a8);
    uStack_10c = (uint)((double)(float)(DOUBLE_803330d8 +
                                       (double)(float)((double)FLOAT_803330d0 * param_1)) -
                       DOUBLE_803330e8);
    local_118 = (longlong)(int)uStack_10c;
    uStack_12c = (uint)((double)(FLOAT_803330d4 -
                                (float)((double)(float)((double)FLOAT_803330d0 * param_1) *
                                       DOUBLE_803330a8)) - DOUBLE_803330a8);
    local_138 = (longlong)(int)uStack_12c;
    uStack_11c = (int)((double)FLOAT_803330e0 - DOUBLE_803330a8) ^ 0x80000000;
    uStack_12c = uStack_12c ^ 0x80000000;
    uStack_10c = uStack_10c ^ 0x80000000;
    uStack_fc = (int)((double)FLOAT_803330f0 - DOUBLE_803330e8) ^ 0x80000000;
    dVar15 = (double)(float)((double)CONCAT44(0x43300000,uStack_12c) - DOUBLE_803330c8);
    dVar14 = (double)(float)((double)CONCAT44(0x43300000,uStack_11c) - DOUBLE_803330c8);
    dVar11 = (double)(float)((double)CONCAT44(0x43300000,uStack_10c) - DOUBLE_803330c8);
    dVar13 = (double)(float)((double)CONCAT44(0x43300000,uStack_fc) - DOUBLE_803330c8);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    local_13c = 0xffffffff;
    local_140 = 0xffffffff;
    GXSetChanMatColor(4,&local_140);
    dVar17 = (double)(float)(dVar15 + dVar11);
    dVar16 = (double)(float)(dVar14 + dVar13);
    dVar7 = (double)FLOAT_803330bc;
    dVar12 = (double)(float)(dVar17 - (double)FLOAT_803330f4);
    uVar3 = 0;
    dVar6 = (double)(float)(dVar16 - (double)FLOAT_803330f4);
    do {
      uVar2 = 0;
      if (uVar3 == 0) {
        uVar1 = 0x3c;
      }
      else if (uVar3 == 1) {
        uVar1 = 0x3c;
      }
      else if (uVar3 == 2) {
        uVar1 = 0x4b;
      }
      else {
        uVar1 = 0x4d;
      }
      dVar5 = dVar15;
      if (((uVar3 & 1) != 0) && (dVar5 = dVar12, uVar3 == 1)) {
        uVar2 = 8;
      }
      dVar8 = dVar14;
      if ((uVar3 & 2) != 0) {
        dVar8 = dVar6;
      }
      SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar1);
      DrawRect__8CMenuPcsFUlfffffffff
                (dVar5,dVar8,(double)FLOAT_803330f4,(double)FLOAT_803330f4,dVar7,dVar7,
                 (double)FLOAT_803330f8,(double)FLOAT_803330f8,&MenuPcs,uVar2);
      uVar3 = uVar3 + 1;
    } while ((int)uVar3 < 4);
    dVar11 = dVar11 - DOUBLE_803330d8;
    dVar8 = (double)FLOAT_803330bc;
    dVar10 = (double)(float)((double)FLOAT_803330f4 + dVar15);
    iVar4 = 0;
    dVar5 = (double)(float)dVar11;
    dVar7 = dVar14;
    do {
      uVar2 = 0x49;
      if (iVar4 != 0) {
        uVar2 = 0x4c;
        dVar14 = dVar6;
      }
      SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar2);
      DrawRect__8CMenuPcsFUlfffffffff
                (dVar10,dVar14,dVar5,(double)FLOAT_803330f4,dVar8,dVar8,(double)FLOAT_803330f8,
                 (double)FLOAT_803330f8,&MenuPcs,0);
      iVar4 = iVar4 + 1;
    } while (iVar4 < 2);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x4a);
    dVar8 = dVar13 - DOUBLE_803330d8;
    dVar9 = (double)FLOAT_803330bc;
    dVar5 = (double)(float)((double)FLOAT_803330f4 + dVar7);
    iVar4 = 0;
    dVar6 = (double)(float)dVar8;
    dVar14 = dVar15;
    do {
      uVar2 = 0;
      if (iVar4 != 0) {
        uVar2 = 8;
        dVar15 = dVar12;
      }
      DrawRect__8CMenuPcsFUlfffffffff
                (dVar15,dVar5,(double)FLOAT_803330f4,dVar6,dVar9,dVar9,(double)FLOAT_803330f8,
                 (double)FLOAT_803330f8,&MenuPcs,uVar2);
      iVar4 = iVar4 + 1;
    } while (iVar4 < 2);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x4e);
    DrawRect__8CMenuPcsFUlfffffffff
              (dVar10,dVar5,(double)(float)dVar11,(double)(float)dVar8,(double)FLOAT_803330bc,
               (double)FLOAT_803330bc,(double)FLOAT_803330f8,(double)FLOAT_803330f8,&MenuPcs,uVar2);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x4f);
    dVar12 = (double)(float)(dVar17 - (double)FLOAT_80333108);
    dVar6 = (double)FLOAT_803330bc;
    dVar15 = dVar7 - DOUBLE_80333100;
    uVar3 = 0;
    dVar11 = DOUBLE_80333100 + dVar12;
    dVar5 = DOUBLE_80333100 + (double)(float)(dVar16 - (double)FLOAT_8033310c);
    do {
      uVar2 = 0;
      dVar8 = dVar11;
      if ((uVar3 & 1) == 0) {
        dVar8 = dVar14 - (double)FLOAT_80333110;
      }
      dVar10 = dVar15;
      if ((uVar3 & 2) != 0) {
        uVar2 = 4;
        dVar10 = dVar5;
      }
      DrawRect__8CMenuPcsFUlfffffffff
                ((double)(float)dVar8,(double)(float)dVar10,(double)FLOAT_80333108,
                 (double)FLOAT_8033310c,dVar6,dVar6,(double)FLOAT_803330f8,(double)FLOAT_803330f8,
                 &MenuPcs,uVar2);
      uVar3 = uVar3 + 1;
    } while ((int)uVar3 < 4);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x50);
    dVar11 = (double)(float)(dVar14 - (double)FLOAT_80333110);
    dVar12 = (double)(float)((double)FLOAT_80333110 + dVar12);
    dVar5 = (double)FLOAT_803330bc;
    iVar4 = 0;
    dVar15 = (double)(float)((DOUBLE_80333118 + dVar7) - DOUBLE_80333100);
    dVar13 = (double)(float)(dVar15 + (double)(float)(dVar13 - DOUBLE_80333120));
    dVar6 = DOUBLE_80333118;
    do {
      dVar8 = dVar15;
      if (iVar4 != 0) {
        dVar11 = dVar12;
      }
      for (; dVar15 < dVar13; dVar15 = (double)(float)(dVar15 + dVar10)) {
        dVar10 = (double)(float)(dVar13 - dVar15);
        if (dVar6 <= dVar10) {
          dVar10 = (double)FLOAT_8033310c;
        }
        DrawRect__8CMenuPcsFUlfffffffff
                  (dVar11,dVar15,(double)FLOAT_80333108,dVar10,dVar5,dVar5,(double)FLOAT_803330f8,
                   (double)FLOAT_803330f8,&MenuPcs,0);
      }
      iVar4 = iVar4 + 1;
      dVar15 = dVar8;
    } while (iVar4 < 2);
    if (DOUBLE_803330e8 <= param_1) {
      SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x3d);
      DrawRect__8CMenuPcsFUlfffffffff
                ((double)(float)(dVar14 - (double)FLOAT_803330f4),
                 (double)(float)(dVar7 - (double)FLOAT_80333108),(double)FLOAT_80333128,
                 (double)FLOAT_8033312c,(double)FLOAT_80333130,(double)FLOAT_803330bc,
                 (double)FLOAT_803330f8,(double)FLOAT_803330f8,&MenuPcs,0);
      DrawRect__8CMenuPcsFUlfffffffff
                ((double)(float)(dVar17 - (double)FLOAT_80333134),
                 (double)(float)(dVar16 - (double)FLOAT_803330c0),(double)FLOAT_80333130,
                 (double)FLOAT_80333138,(double)FLOAT_803330bc,(double)FLOAT_803330bc,
                 (double)FLOAT_803330f8,(double)FLOAT_803330f8,&MenuPcs,0);
    }
  }
  return;
}


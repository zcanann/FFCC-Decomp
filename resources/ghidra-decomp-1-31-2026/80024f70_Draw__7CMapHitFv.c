// Function: Draw__7CMapHitFv
// Entry: 80024f70
// Size: 1376 bytes

void Draw__7CMapHitFv(CMapHit *mapHit)

{
  ushort *puVar1;
  byte bVar2;
  CMapHitFace *pCVar3;
  undefined4 uVar4;
  uint uVar5;
  float *pfVar6;
  undefined4 uVar7;
  CMapHitFace *pCVar8;
  int iVar9;
  int iVar10;
  CMapHitFace *pCVar11;
  uint uVar12;
  undefined local_18;
  undefined uStack_17;
  undefined uStack_16;
  undefined uStack_15;
  undefined local_14;
  undefined uStack_13;
  undefined uStack_12;
  undefined uStack_11;
  
  GXSetVtxAttrFmt(7,9,1,4,0);
  GXSetVtxAttrFmt(7,10,0,4,0);
  GXSetVtxAttrFmt(7,0xb,1,5,0);
  GXClearVtxDesc();
  GXSetVtxDesc(9,1);
  GXSetVtxDesc(10,1);
  GXSetVtxDesc(0xb,1);
  pCVar11 = mapHit->m_faces;
  for (iVar10 = 0; iVar10 < (int)(uint)mapHit->m_faceCount; iVar10 = iVar10 + 1) {
    if ((*(byte *)((int)&pCVar11[1].field17_0x1c.z + 3) & 1) == 0) {
      bVar2 = *(byte *)((int)&pCVar11[1].field17_0x1c.x + 3);
      uVar7 = *(undefined4 *)&MapMng.mapIdGrpArr[bVar2].field_0x4;
      uVar4 = *(undefined4 *)&MapMng.mapIdGrpArr[bVar2].field_0x8;
      GXBegin(0x90,7,3);
      local_14 = (undefined)((uint)uVar7 >> 0x18);
      uStack_13 = (undefined)((uint)uVar7 >> 0x10);
      iVar9 = 0;
      uStack_12 = (undefined)((uint)uVar7 >> 8);
      uStack_11 = (undefined)uVar7;
      pCVar8 = pCVar11;
      while (iVar9 < (int)(uint)*(byte *)((int)&pCVar11[1].field17_0x1c.x + 2)) {
        pCVar3 = pCVar8 + 1;
        iVar9 = iVar9 + 1;
        pCVar8 = (CMapHitFace *)&pCVar8->field_0x2;
        pfVar6 = mapHit->m_vertices + (uint)*(ushort *)&(pCVar3->field17_0x1c).y * 3;
        DAT_cc008000 = *pfVar6;
        DAT_cc008000 = pfVar6[1];
        DAT_cc008000 = pfVar6[2];
        DAT_cc008000 = *(undefined4 *)pCVar11;
        DAT_cc008000 = *(undefined4 *)&pCVar11->field_0x4;
        DAT_cc008000 = *(undefined4 *)&pCVar11->field_0x8;
        DAT_cc008000._0_1_ = local_14;
        DAT_cc008000._0_1_ = uStack_13;
        DAT_cc008000._0_1_ = uStack_12;
        DAT_cc008000._0_1_ = uStack_11;
      }
      GXBegin(0x90,7,3);
      bVar2 = *(byte *)((int)&pCVar11[1].field17_0x1c.x + 2);
      uVar5 = (uint)bVar2;
      local_18 = (undefined)((uint)uVar4 >> 0x18);
      uStack_17 = (undefined)((uint)uVar4 >> 0x10);
      uStack_16 = (undefined)((uint)uVar4 >> 8);
      uStack_15 = (undefined)uVar4;
      iVar9 = (int)pCVar11 + (uVar5 - 1) * 2;
      if (-1 < (int)(uVar5 - 1)) {
        uVar12 = (uint)(bVar2 >> 1);
        if (bVar2 >> 1 != 0) {
          do {
            pfVar6 = mapHit->m_vertices + (uint)*(ushort *)(iVar9 + 0x48) * 3;
            DAT_cc008000 = *pfVar6;
            DAT_cc008000 = pfVar6[1];
            DAT_cc008000 = pfVar6[2];
            DAT_cc008000 = *(undefined4 *)pCVar11;
            DAT_cc008000 = *(undefined4 *)&pCVar11->field_0x4;
            DAT_cc008000 = *(undefined4 *)&pCVar11->field_0x8;
            DAT_cc008000._0_1_ = local_18;
            DAT_cc008000._0_1_ = uStack_17;
            DAT_cc008000._0_1_ = uStack_16;
            DAT_cc008000._0_1_ = uStack_15;
            puVar1 = (ushort *)(iVar9 + 0x46);
            iVar9 = iVar9 + -4;
            pfVar6 = mapHit->m_vertices + (uint)*puVar1 * 3;
            DAT_cc008000 = *pfVar6;
            DAT_cc008000 = pfVar6[1];
            DAT_cc008000 = pfVar6[2];
            DAT_cc008000 = *(undefined4 *)pCVar11;
            DAT_cc008000 = *(undefined4 *)&pCVar11->field_0x4;
            DAT_cc008000 = *(undefined4 *)&pCVar11->field_0x8;
            DAT_cc008000._0_1_ = local_18;
            DAT_cc008000._0_1_ = uStack_17;
            DAT_cc008000._0_1_ = uStack_16;
            DAT_cc008000._0_1_ = uStack_15;
            uVar12 = uVar12 - 1;
          } while (uVar12 != 0);
          uVar5 = uVar5 & 1;
          if ((bVar2 & 1) == 0) goto LAB_80025224;
        }
        do {
          puVar1 = (ushort *)(iVar9 + 0x48);
          iVar9 = iVar9 + -2;
          pfVar6 = mapHit->m_vertices + (uint)*puVar1 * 3;
          DAT_cc008000 = *pfVar6;
          DAT_cc008000 = pfVar6[1];
          DAT_cc008000 = pfVar6[2];
          DAT_cc008000 = *(undefined4 *)pCVar11;
          DAT_cc008000 = *(undefined4 *)&pCVar11->field_0x4;
          DAT_cc008000 = *(undefined4 *)&pCVar11->field_0x8;
          DAT_cc008000._0_1_ = local_18;
          DAT_cc008000._0_1_ = uStack_17;
          DAT_cc008000._0_1_ = uStack_16;
          DAT_cc008000._0_1_ = uStack_15;
          uVar5 = uVar5 - 1;
        } while (uVar5 != 0);
      }
    }
LAB_80025224:
    pCVar11 = pCVar11 + 2;
  }
  GXClearVtxDesc();
  GXSetVtxAttrFmt(7,9,1,4,0);
  GXSetVtxAttrFmt(7,0xb,1,5,0);
  GXSetVtxDesc(9,1);
  GXSetVtxDesc(0xb,1);
  pCVar11 = mapHit->m_faces;
  iVar10 = 0;
  do {
    if ((int)(uint)mapHit->m_faceCount <= iVar10) {
      return;
    }
    if ((*(byte *)((int)&pCVar11[1].field17_0x1c.z + 3) & 1) == 0) {
      *(undefined *)((int)&pCVar11[1].field17_0x1c.z + 3) = 0;
    }
    else {
      *(undefined *)((int)&pCVar11[1].field17_0x1c.z + 3) = 0;
      *(undefined *)((int)&pCVar11[1].field17_0x1c.z + 3) = 0;
      GXBegin(0x90,7,3);
      iVar9 = 0;
      pCVar8 = pCVar11;
      while (iVar9 < (int)(uint)*(byte *)((int)&pCVar11[1].field17_0x1c.x + 2)) {
        pCVar3 = pCVar8 + 1;
        pCVar8 = (CMapHitFace *)&pCVar8->field_0x2;
        iVar9 = iVar9 + 1;
        pfVar6 = mapHit->m_vertices + (uint)*(ushort *)&(pCVar3->field17_0x1c).y * 3;
        DAT_cc008000 = *pfVar6;
        DAT_cc008000 = pfVar6[1];
        DAT_cc008000 = pfVar6[2];
        DAT_cc008000._0_1_ = 0x40;
        DAT_cc008000._0_1_ = 0xff;
        DAT_cc008000._0_1_ = 0x40;
        DAT_cc008000._0_1_ = 0xff;
      }
      GXBegin(0x90,7,3);
      bVar2 = *(byte *)((int)&pCVar11[1].field17_0x1c.x + 2);
      uVar5 = (uint)bVar2;
      iVar9 = (int)pCVar11 + (uVar5 - 1) * 2;
      if (-1 < (int)(uVar5 - 1)) {
        uVar12 = (uint)(bVar2 >> 2);
        if (bVar2 >> 2 != 0) {
          do {
            pfVar6 = mapHit->m_vertices + (uint)*(ushort *)(iVar9 + 0x48) * 3;
            DAT_cc008000 = *pfVar6;
            DAT_cc008000 = pfVar6[1];
            DAT_cc008000 = pfVar6[2];
            DAT_cc008000._0_1_ = 0x40;
            DAT_cc008000._0_1_ = 0xff;
            DAT_cc008000._0_1_ = 0x40;
            DAT_cc008000._0_1_ = 0xff;
            pfVar6 = mapHit->m_vertices + (uint)*(ushort *)(iVar9 + 0x46) * 3;
            DAT_cc008000 = *pfVar6;
            DAT_cc008000 = pfVar6[1];
            DAT_cc008000 = pfVar6[2];
            DAT_cc008000._0_1_ = 0x40;
            DAT_cc008000._0_1_ = 0xff;
            DAT_cc008000._0_1_ = 0x40;
            DAT_cc008000._0_1_ = 0xff;
            pfVar6 = mapHit->m_vertices + (uint)*(ushort *)(iVar9 + 0x44) * 3;
            DAT_cc008000 = *pfVar6;
            DAT_cc008000 = pfVar6[1];
            DAT_cc008000 = pfVar6[2];
            DAT_cc008000._0_1_ = 0x40;
            DAT_cc008000._0_1_ = 0xff;
            DAT_cc008000._0_1_ = 0x40;
            DAT_cc008000._0_1_ = 0xff;
            puVar1 = (ushort *)(iVar9 + 0x42);
            iVar9 = iVar9 + -8;
            pfVar6 = mapHit->m_vertices + (uint)*puVar1 * 3;
            DAT_cc008000 = *pfVar6;
            DAT_cc008000 = pfVar6[1];
            DAT_cc008000 = pfVar6[2];
            DAT_cc008000._0_1_ = 0x40;
            DAT_cc008000._0_1_ = 0xff;
            DAT_cc008000._0_1_ = 0x40;
            DAT_cc008000._0_1_ = 0xff;
            uVar12 = uVar12 - 1;
          } while (uVar12 != 0);
          uVar5 = uVar5 & 3;
          if ((bVar2 & 3) == 0) goto LAB_800254a0;
        }
        do {
          puVar1 = (ushort *)(iVar9 + 0x48);
          iVar9 = iVar9 + -2;
          pfVar6 = mapHit->m_vertices + (uint)*puVar1 * 3;
          DAT_cc008000 = *pfVar6;
          DAT_cc008000 = pfVar6[1];
          DAT_cc008000 = pfVar6[2];
          DAT_cc008000._0_1_ = 0x40;
          DAT_cc008000._0_1_ = 0xff;
          DAT_cc008000._0_1_ = 0x40;
          DAT_cc008000._0_1_ = 0xff;
          uVar5 = uVar5 - 1;
        } while (uVar5 != 0);
      }
    }
LAB_800254a0:
    iVar10 = iVar10 + 1;
    pCVar11 = pCVar11 + 2;
  } while( true );
}


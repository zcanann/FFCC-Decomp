// Function: DrawWire__7CMapHitFv
// Entry: 80024e64
// Size: 268 bytes

void DrawWire__7CMapHitFv(CMapHit *mapHit)

{
  CMapHitFace *pCVar1;
  float *pfVar2;
  CMapHitFace *pCVar3;
  int iVar4;
  int iVar5;
  CMapHitFace *pCVar6;
  
  GXSetVtxAttrFmt(7,9,1,4,0);
  GXClearVtxDesc();
  GXSetVtxDesc(9,1);
  pCVar6 = mapHit->m_faces;
  iVar5 = 0;
  while (iVar5 < (int)(uint)mapHit->m_faceCount) {
    GXBegin(0xb0,7,4);
    iVar4 = 0;
    pCVar3 = pCVar6;
    while (iVar4 < (int)(uint)*(byte *)((int)&pCVar6[1].field17_0x1c.x + 2)) {
      pCVar1 = pCVar3 + 1;
      iVar4 = iVar4 + 1;
      pCVar3 = (CMapHitFace *)&pCVar3->field_0x2;
      pfVar2 = mapHit->m_vertices + (uint)*(ushort *)&(pCVar1->field17_0x1c).y * 3;
      DAT_cc008000 = *pfVar2;
      DAT_cc008000 = pfVar2[1];
      DAT_cc008000 = pfVar2[2];
    }
    pCVar3 = pCVar6 + 1;
    pCVar6 = pCVar6 + 2;
    iVar5 = iVar5 + 1;
    pfVar2 = mapHit->m_vertices + (uint)*(ushort *)&(pCVar3->field17_0x1c).y * 3;
    DAT_cc008000 = *pfVar2;
    DAT_cc008000 = pfVar2[1];
    DAT_cc008000 = pfVar2[2];
  }
  return;
}


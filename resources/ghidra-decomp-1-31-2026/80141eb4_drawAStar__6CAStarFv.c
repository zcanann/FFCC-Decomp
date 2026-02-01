// Function: drawAStar__6CAStarFv
// Entry: 80141eb4
// Size: 700 bytes

void drawAStar__6CAStarFv(CAStar *aStar)

{
  uint8_t uVar1;
  uint8_t uVar2;
  bool bVar3;
  int iVar4;
  undefined uVar7;
  undefined uVar8;
  undefined uVar9;
  undefined4 *puVar5;
  undefined4 uVar6;
  int iVar10;
  int iVar11;
  CAStar *pCVar12;
  CAStar *pCVar13;
  CAStar *pCVar14;
  undefined auStack_38 [4];
  undefined auStack_34 [4];
  undefined auStack_30 [4];
  undefined4 local_2c [2];
  
  if ((MiniGamePcs._25732_4_ & 0x400) != 0) {
    iVar4 = (int)System.m_frameCounter / 0x1e + ((int)System.m_frameCounter >> 0x1f);
    if (System.m_frameCounter == (iVar4 - (iVar4 >> 0x1f)) * 0x1e) {
      iVar4 = 0;
      do {
        uVar7 = Rand__5CMathFUl(&Math,0xff);
        uVar8 = Rand__5CMathFUl(&Math,0xff);
        uVar9 = Rand__5CMathFUl(&Math,0xff);
        puVar5 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_30,uVar9,uVar8,uVar7,0xff);
        local_2c[0] = *puVar5;
        SetIdGrpColor__7CMapMngFii8_GXColor(&MapMng,iVar4,0,local_2c);
        iVar4 = iVar4 + 1;
      } while (iVar4 < 0x40);
    }
    bVar3 = false;
    if ((aStar->m_currentGroup != '\0') && (aStar->m_prevGroup != '\0')) {
      bVar3 = true;
    }
    if (bVar3) {
      uVar6 = __ct__6CColorFUcUcUcUc(auStack_34,0xff,0xff,0xff,0xff);
      DrawSphere__8CGraphicFPA4_fP3VecfP8_GXColor
                ((double)FLOAT_803320a8,&Graphic,0x802687ac,&aStar->m_lastGroupPos,uVar6);
    }
    iVar4 = 0;
    pCVar14 = aStar;
    do {
      bVar3 = false;
      if ((pCVar14->m_portals[0].m_groupA != '\0') && (pCVar14->m_portals[0].m_groupB != '\0')) {
        bVar3 = true;
      }
      if (bVar3) {
        uVar6 = __ct__6CColorFUcUcUcUc(auStack_38,0xff,0xff,0,0xff);
        DrawSphere__8CGraphicFPA4_fP3VecfP8_GXColor
                  ((double)FLOAT_803320a8,&Graphic,0x802687ac,pCVar14->m_portals,uVar6);
        iVar11 = 0;
        pCVar13 = pCVar14;
        do {
          uVar1 = pCVar13->m_portals[0].m_groupA;
          if (uVar1 != '\0') {
            iVar10 = 0;
            pCVar12 = aStar;
            do {
              if (iVar4 != iVar10) {
                uVar2 = pCVar12->m_portals[0].m_groupA;
                bVar3 = false;
                if ((uVar2 != '\0') && (pCVar12->m_portals[0].m_groupB != '\0')) {
                  bVar3 = true;
                }
                if (bVar3) {
                  bVar3 = false;
                  if (uVar2 == uVar1) {
LAB_801420c4:
                    bVar3 = true;
                  }
                  else if (pCVar12->m_portals[0].m_groupB == uVar1) goto LAB_801420c4;
                  if (bVar3) {
                    GXLoadPosMtxImm(0x802687ac,0);
                    GXBegin(0xa8,0,2);
                    DAT_cc008000 = pCVar14->m_portals[0].m_position.x;
                    DAT_cc008000 = FLOAT_80332090 + pCVar14->m_portals[0].m_position.y;
                    DAT_cc008000 = pCVar14->m_portals[0].m_position.z;
                    DAT_cc008000 = pCVar12->m_portals[0].m_position.x;
                    DAT_cc008000 = FLOAT_80332090 + pCVar12->m_portals[0].m_position.y;
                    DAT_cc008000 = pCVar12->m_portals[0].m_position.z;
                  }
                }
              }
              iVar10 = iVar10 + 1;
              pCVar12 = (CAStar *)&pCVar12->m_portals[0].m_position.y;
            } while (iVar10 < 0x40);
          }
          iVar11 = iVar11 + 1;
          pCVar13 = (CAStar *)&pCVar13->field_0x1;
        } while (iVar11 < 2);
      }
      iVar4 = iVar4 + 1;
      pCVar14 = (CAStar *)&pCVar14->m_portals[0].m_position.y;
    } while (iVar4 < 0x40);
  }
  return;
}


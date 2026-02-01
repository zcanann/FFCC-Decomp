// Function: Calc__5CGameFv
// Entry: 80014994
// Size: 508 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Calc__5CGameFv(CGame *game)

{
  float fVar1;
  float fVar2;
  CGame *pCVar3;
  CGPartyObj *pCVar4;
  int iVar5;
  undefined auStack_38 [52];
  
  if (game->m_frameCounterEnable != 0) {
    (game->m_gameWork).m_frameCounter = (game->m_gameWork).m_frameCounter + 1;
  }
  fVar2 = FLOAT_8032f68c;
  fVar1 = FLOAT_8032f688;
  game->m_partyMinZ = FLOAT_8032f688;
  game->m_partyMinY = fVar1;
  game->m_partyMinX = fVar1;
  game->m_partyMaxZ = fVar2;
  game->m_partyMaxY = fVar2;
  game->m_partyMaxX = fVar2;
  iVar5 = 4;
  pCVar3 = game;
  do {
    pCVar4 = pCVar3->m_partyObjArr[0];
    if (pCVar4 != (CGPartyObj *)0x0) {
      fVar1 = (pCVar4->gCharaObj).gPrgObj.object.m_worldPosition.x;
      if (game->m_partyMinX < fVar1) {
        fVar1 = game->m_partyMinX;
      }
      game->m_partyMinX = fVar1;
      fVar1 = (pCVar4->gCharaObj).gPrgObj.object.m_worldPosition.y;
      if (game->m_partyMinY < fVar1) {
        fVar1 = game->m_partyMinY;
      }
      game->m_partyMinY = fVar1;
      fVar1 = (pCVar4->gCharaObj).gPrgObj.object.m_worldPosition.z;
      if (game->m_partyMinZ < fVar1) {
        fVar1 = game->m_partyMinZ;
      }
      game->m_partyMinZ = fVar1;
      fVar1 = (pCVar4->gCharaObj).gPrgObj.object.m_worldPosition.x;
      if (fVar1 < game->m_partyMaxX) {
        fVar1 = game->m_partyMaxX;
      }
      game->m_partyMaxX = fVar1;
      fVar1 = (pCVar4->gCharaObj).gPrgObj.object.m_worldPosition.y;
      if (fVar1 < game->m_partyMaxY) {
        fVar1 = game->m_partyMaxY;
      }
      game->m_partyMaxY = fVar1;
      fVar1 = (pCVar4->gCharaObj).gPrgObj.object.m_worldPosition.z;
      if (fVar1 < game->m_partyMaxZ) {
        fVar1 = game->m_partyMaxZ;
      }
      game->m_partyMaxZ = fVar1;
    }
    pCVar3 = (CGame *)&pCVar3->unk_0x4;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  Frame__5CWindFv(&Wind);
  Calc__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
  ResetPerformance__12CFlatRuntimeFv(&CFlat);
  Frame__13CFlatRuntime2Fii(&CFlat,1,0);
  if ((game->m_currentMapId == 0x21) && (iVar5 = GetMapObjIdx__7CMapMngFUs(&MapMng,0), -1 < iVar5))
  {
    if (BOOL_8032ec44 == false) {
      BOOL_8032ec44 = true;
      FLOAT_8032ec40 = FLOAT_8032f690;
    }
    FLOAT_8032ec40 = FLOAT_8032ec40 + FLOAT_8032f694;
    PSMTXRotRad(FLOAT_8032ec40,auStack_38,0x79);
    SetMapObjLMtx__7CMapMngFiPA4_f(&MapMng,iVar5,auStack_38);
  }
  return;
}


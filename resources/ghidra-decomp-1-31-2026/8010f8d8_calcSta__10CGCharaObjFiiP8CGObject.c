// Function: calcSta__10CGCharaObjFiiP8CGObject
// Entry: 8010f8d8
// Size: 1148 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

uint calcSta__10CGCharaObjFiiP8CGObject
               (CGCharaObj *gCharaObj,int param_2,int param_3,CGPrgObj *gPrgObj)

{
  ushort uVar1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  CGPrgObj *pCVar7;
  bool bVar9;
  int iVar8;
  uint uVar10;
  uint uVar11;
  short sVar12;
  
  if (((param_2 == 0) || (param_2 == 4)) &&
     (*(short *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle + param_2 * 2 + 0x3e) != 0)) {
    Printf__7CSystemFPce(&System,&DAT_801dc8d8);
    uVar5 = (uint)*(ushort *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle + param_2 * 2 + 0x3e);
  }
  else {
    uVar11 = 0;
    if (param_2 == 7) {
      uVar11 = (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x18);
    }
    else if (param_2 < 7) {
      if (param_2 == 3) {
        uVar11 = (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x22);
      }
      else if (param_2 < 3) {
        if (param_2 == 1) {
          uVar11 = (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0xe);
        }
        else if (param_2 < 1) {
          if (-1 < param_2) {
            uVar11 = (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x10);
          }
        }
        else {
          uVar11 = (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x1e);
        }
      }
      else if (param_2 != 5) {
        if (param_2 < 5) {
          uVar11 = (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x12);
        }
        else {
          uVar11 = (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x20);
        }
      }
    }
    else if (param_2 == 0x1c) {
      uVar11 = (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x1c);
    }
    else if (param_2 < 0x1c) {
      if (param_2 == 10) {
        uVar11 = (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x1a);
      }
      else if (param_2 < 10) {
        if (param_2 < 9) {
          uVar11 = (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x14);
        }
        else {
          uVar11 = (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x16);
        }
      }
    }
    else if (param_2 == 0x6a) {
      uVar11 = (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x24);
    }
    if (param_3 < 0x1f5) {
      sVar12 = 1;
    }
    else {
      sVar12 = *(short *)(Game.game.unkCFlatData0[2] + param_3 * 0x48 + 2);
    }
    uVar6 = (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0xc))(gPrgObj);
    uVar6 = countLeadingZeros(0x2d - (uVar6 & 0x2d));
    if ((uVar6 >> 5 & 0xff) == 0) {
      uVar1 = *(ushort *)(Game.game.unkCFlatData0[2] + param_3 * 0x48 + 0x2e);
    }
    else {
      bVar3 = false;
      bVar2 = false;
      bVar9 = false;
      if ((Game.game.m_gameWork.m_menuStageMode != '\0') &&
         (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf)) {
        bVar9 = true;
      }
      if (bVar9) {
        uVar6 = (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0xc))(gPrgObj);
        uVar6 = countLeadingZeros(0x6d - (uVar6 & 0x6d));
        if ((uVar6 >> 5 & 0xff) != 0) {
          bVar2 = true;
        }
      }
      if ((bVar2) && ((gPrgObj->object).m_scriptHandle[0xed] != (void *)0x0)) {
        bVar3 = true;
      }
      pCVar7 = gPrgObj;
      if (bVar3) {
        pCVar7 = (CGPrgObj *)Game.game.m_partyObjArr[0];
      }
      uVar1 = *(ushort *)
               ((int)(((CGCharaObj *)&pCVar7->object)->gPrgObj).object.m_scriptHandle[9] + 0x198);
    }
    uVar6 = (uint)uVar1;
    uVar5 = (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0xc))(gPrgObj);
    if ((uVar5 & 0xad) == 0xad) {
      if (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf) {
        iVar4 = Game.game.m_gameWork.m_bossArtifactStageTable
                [Game.game.m_gameWork.m_bossArtifactStageIndex];
        iVar8 = 2;
        if (iVar4 < 2) {
          iVar8 = iVar4;
        }
      }
      else {
        iVar8 = 0;
      }
      if (0 < iVar8) {
        uVar6 = uVar6 + *(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + iVar8 * 2 + 0x5c);
      }
    }
    uVar10 = 0;
    uVar5 = (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0xc))(gPrgObj);
    if (((uVar5 & 0x6d) == 0x6d) && ((sVar12 == 1 || (sVar12 == 9)))) {
      uVar10 = (uint)*(byte *)((int)(gPrgObj->object).m_scriptHandle + 0xbda);
    }
    uVar5 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0xc))
                      (gCharaObj);
    if (((uVar5 & 0x6d) == 0x6d) && ((sVar12 == 8 || (sVar12 == 9)))) {
      uVar10 = uVar10 - *(byte *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle + 0xbdb);
    }
    uVar5 = uVar10 + uVar11 * uVar6;
    uVar5 = uVar5 & ~((int)uVar5 >> 0x1f);
    Printf__7CSystemFPce(&System,&DAT_801dc8ec,uVar11,uVar6,uVar10,uVar5);
  }
  return uVar5;
}


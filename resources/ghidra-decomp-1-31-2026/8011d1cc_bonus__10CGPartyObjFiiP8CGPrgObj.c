// Function: bonus__10CGPartyObjFiiP8CGPrgObj
// Entry: 8011d1cc
// Size: 1348 bytes

/* WARNING: Removing unreachable block (ram,0x8011d66c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void bonus__10CGPartyObjFiiP8CGPrgObj
               (CGPartyObj *gPartyObj,int param_2,int param_3,CGPrgObj *gPrgObj)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  short sVar4;
  uint uVar5;
  int iVar6;
  void **ppvVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  
  if ((gPrgObj != (CGPrgObj *)0x0) &&
     (uVar5 = (**(code **)((int)(gPrgObj->object).base_object.object.m_vtable + 0xc))(gPrgObj),
     (uVar5 & 0x2d) != 0x2d)) {
    return;
  }
  ppvVar7 = (gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle;
  uVar9 = (uint)*(byte *)(ppvVar7 + 0x2e9);
  uVar5 = 0;
  uVar1 = *(ushort *)((int)ppvVar7 + 0xbca);
  uVar2 = *(ushort *)(ppvVar7 + 0x2f3);
  uVar10 = 0;
  iVar6 = Game.game.m_bossArtifactBase + Game.game.m_gameWork.m_bossArtifactStageIndex * 0x168 +
          uVar9 * 8;
  uVar12 = (uint)*(ushort *)(iVar6 + 0x66);
  uVar11 = (uint)*(ushort *)(iVar6 + 0x68);
  if (param_2 == 0) {
    uVar3 = *(ushort *)(ppvVar7 + 0x2f2);
    Printf__7CSystemFPce(&System,&DAT_801dcc08,uVar3 + 1);
    *(ushort *)((gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle + 0x2f2) = uVar3 + 1;
  }
  if (param_2 == 1) {
    uVar3 = *(ushort *)((gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle + 0x2f1);
    Printf__7CSystemFPce(&System,&DAT_801dcc24,uVar3 + 1);
    *(ushort *)((gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle + 0x2f1) = uVar3 + 1;
  }
  if (param_2 == 4) {
    uVar3 = *(ushort *)((int)(gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle + 0xbc6);
    Printf__7CSystemFPce(&System,&DAT_801dcc40,uVar3 + 1);
    *(ushort *)((int)(gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle + 0xbc6) = uVar3 + 1;
  }
  uVar13 = uVar10;
  switch(uVar9) {
  case 0:
    if ((param_2 == 2) &&
       (iVar6 = (int)System.m_frameCounter / 0x1e + ((int)System.m_frameCounter >> 0x1f),
       System.m_frameCounter == (iVar6 - (iVar6 >> 0x1f)) * 0x1e)) {
      uVar13 = uVar12;
    }
    break;
  case 1:
    if (param_2 == 3) {
      uVar13 = uVar12;
    }
    break;
  case 2:
  case 4:
  case 6:
    if (((param_2 == 4) &&
        ((uVar3 = *(ushort *)(Game.game.unkCFlatData0[2] + param_3 * 0x48), uVar9 != 4 ||
         (uVar13 = uVar12, uVar3 != 0x100)))) &&
       (((uVar9 != 6 || (uVar13 = uVar12, uVar3 != 400)) && (uVar13 = uVar10, uVar9 == 2)))) {
      if (uVar3 != 0x100) {
        if (uVar3 < 0x100) {
          if (uVar3 != 0xdb) {
            if (uVar3 < 0xdb) {
              if (uVar3 != 0xb6) {
                if (uVar3 < 0xb6) {
                  if (uVar3 != 0x9f) break;
                }
                else if (uVar3 != 0xcc) break;
              }
            }
            else if ((uVar3 != 0xe4) && ((0xe3 < uVar3 || (uVar3 != 0xdf)))) break;
          }
        }
        else if (uVar3 != 0x17d) {
          if (uVar3 < 0x17d) {
            if ((uVar3 != 0x12a) && (((0x129 < uVar3 || (0x126 < uVar3)) || (uVar3 < 0x125))))
            break;
          }
          else if ((uVar3 != 0x191) && ((400 < uVar3 || (uVar3 != 0x186)))) break;
        }
      }
      uVar13 = uVar12;
    }
    break;
  case 3:
  case 0xe:
    if ((param_2 == 5) &&
       (((sVar4 = *(short *)(Game.game.unkCFlatData0[2] + param_3 * 0x48), uVar9 == 0xe &&
         ((sVar4 == 0x17d || (sVar4 == 0x186)))) ||
        ((uVar9 == 3 && ((sVar4 != 0x17d && (sVar4 != 0x186)))))))) {
      uVar13 = uVar12;
    }
    break;
  case 7:
    if (param_2 == 10) {
      uVar13 = uVar12;
    }
    break;
  case 8:
    if (param_2 == 0xb) {
      uVar13 = uVar12;
    }
    break;
  case 9:
    if (param_2 == 0xc) {
      uVar13 = uVar12;
    }
    break;
  case 10:
    if ((param_2 - 0x12U < 3) || (param_2 == 0x15)) {
      uVar5 = uVar11;
    }
    if (param_2 == 0x17) {
      uVar13 = uVar12;
    }
    break;
  case 0xb:
    if ((param_2 - 0xeU < 3) || (param_2 == 0x11)) {
      uVar13 = uVar12;
    }
    break;
  case 0xc:
    if ((param_2 - 0x12U < 3) || (param_2 == 0x15)) {
      uVar5 = uVar11;
    }
    break;
  case 0xd:
    if (param_2 == 0x12) {
      uVar3 = *(ushort *)(Game.game.unkCFlatData0[2] + param_3 * 0x48 + 8);
      if (uVar3 < 0x69) {
        if ((0x25 < uVar3) || (uVar3 < 0x24)) break;
      }
      else if (0x6a < uVar3) break;
      uVar13 = uVar12;
    }
    break;
  case 0xf:
    if (param_2 == 9) {
      uVar5 = uVar11;
    }
    break;
  case 0x10:
    if (param_2 == 0x18) {
      uVar5 = uVar11;
    }
    break;
  case 0x11:
    if (param_2 == 0x19) {
      uVar5 = uVar11;
    }
    break;
  case 0x12:
  case 0x13:
    if ((param_2 == 0x16) &&
       (((uVar9 == 0x12 && (gPrgObj == (CGPrgObj *)gPartyObj)) ||
        ((uVar9 == 0x13 && (gPrgObj != (CGPrgObj *)gPartyObj)))))) {
      uVar5 = uVar11;
    }
    break;
  case 0x14:
    if (param_2 == 4) {
      uVar5 = uVar11;
    }
    break;
  case 0x15:
    Printf__7CSystemFPce(&System,&DAT_801dcc60);
    break;
  case 0x16:
    if (param_2 == 0x14) {
      uVar13 = uVar12;
    }
    break;
  case 0x17:
    if ((param_2 == 1) && ((*(ushort *)((int)(gPrgObj->object).m_scriptHandle[9] + 0xfe) & 4) != 0))
    {
      uVar13 = uVar12;
    }
    break;
  case 0x18:
    if (param_2 == 1) {
      uVar5 = uVar11;
    }
  }
  if (uVar13 != 0) {
    uVar13 = uVar1 + uVar13;
    uVar10 = 100;
    if (uVar13 < 0x65) {
      uVar10 = uVar13;
    }
    if (uVar9 != 0) {
      Printf__7CSystemFPce(&System,&DAT_801dcc78,uVar9,uVar10);
    }
    *(short *)((int)(gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle + 0xbca) = (short)uVar10;
  }
  if (uVar5 != 0) {
    iVar6 = uVar2 - uVar5;
    if (iVar6 < 0) {
      iVar8 = 0;
    }
    else {
      iVar8 = 100;
      if (iVar6 < 0x65) {
        iVar8 = iVar6;
      }
    }
    Printf__7CSystemFPce(&System,&DAT_801dcc94,uVar9,iVar8);
    *(short *)((gPartyObj->gCharaObj).gPrgObj.object.m_scriptHandle + 0x2f3) = (short)iVar8;
  }
  return;
}


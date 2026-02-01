// Function: onStatMagic__8CGMonObjFv
// Entry: 80117d5c
// Size: 756 bytes

/* WARNING: Removing unreachable block (ram,0x80118030) */
/* WARNING: Removing unreachable block (ram,0x80117d6c) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onStatMagic__8CGMonObjFv(CGMonObj *gMonObj)

{
  int iVar1;
  int iVar2;
  CGPartyObj *pCVar3;
  uint uVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  
  iVar1 = *(int *)&gMonObj->field_0x52c;
  if (iVar1 == 1) {
    if (*(int *)&gMonObj->field_0x68c < *(int *)&gMonObj->field_0x530) {
      changeSubStat__8CGPrgObjFi((CGPrgObj *)gMonObj,2);
    }
  }
  else if (iVar1 < 1) {
    if ((-1 < iVar1) && (*(int *)&gMonObj->field_0x530 == 0)) {
      if (-1 < *(int *)&gMonObj->field_0x6c4) {
        pCVar3 = Game.game.m_partyObjArr[*(int *)&gMonObj->field_0x6c4];
        *(float *)&gMonObj->field_0x66c = (pCVar3->gCharaObj).gPrgObj.object.m_worldPosition.x;
        *(float *)&gMonObj->field_0x670 =
             *(float *)((int)&(pCVar3->gCharaObj).gPrgObj.object.m_worldPosition + 4);
        *(float *)&gMonObj->field_0x674 =
             *(float *)((int)&(pCVar3->gCharaObj).gPrgObj.object.m_worldPosition + 8);
        if ((*(ushort *)(Game.game.unkCFlatData0[2] + *(int *)&gMonObj->field_0x560 * 0x48 + 0x32) &
            2) == 0) {
          dVar7 = (double)(FLOAT_80331a20 *
                          (float)((double)CONCAT44(0x43300000,
                                                   (uint)*(ushort *)
                                                          ((int)(gMonObj->gObject).m_scriptHandle[9]
                                                          + 0x19c)) - DOUBLE_803319e0));
          if (-1 < *(int *)&gMonObj->field_0x6c4) {
            dVar5 = (double)getTargetRot__8CGPrgObjFP8CGPrgObj
                                      ((CGPrgObj *)gMonObj,
                                       Game.game.m_partyObjArr[*(int *)&gMonObj->field_0x6c4]);
            if (dVar7 <= (double)FLOAT_80331a48) {
              dVar6 = (double)DstRot__5CMathFff(dVar5,(double)(float)(gMonObj->gObject).m_bgFlags,
                                                &Math);
              dVar5 = -dVar7;
              if ((dVar5 <= dVar6) && (dVar5 = dVar6, dVar7 < dVar6)) {
                dVar5 = dVar7;
              }
              (gMonObj->gObject).m_rotTargetY =
                   (float)((double)(float)(gMonObj->gObject).m_bgFlags + dVar5);
            }
            else {
              (gMonObj->gObject).m_rotTargetY = (float)dVar5;
            }
          }
        }
        pCVar3 = Game.game.m_partyObjArr[*(int *)&gMonObj->field_0x6c4];
        (**(code **)((int)*(void **)((int)&(pCVar3->gCharaObj).gPrgObj.object.base_object + 0x48) +
                    0x4c))(pCVar3,0x17,*(undefined4 *)&gMonObj->field_0x560,pCVar3);
      }
      putParticleFromItem__10CGCharaObjFiiiP3Vec
                (gMonObj,*(undefined4 *)&gMonObj->field_0x560,0,*(undefined4 *)&gMonObj->field_0x570
                 ,0);
      putParticleFromItem__10CGCharaObjFiiiP3Vec
                (gMonObj,*(undefined4 *)&gMonObj->field_0x560,1,*(undefined4 *)&gMonObj->field_0x570
                 ,0);
    }
  }
  else if ((iVar1 < 3) && (iVar1 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj), iVar1 != 0)) {
    uVar4 = (uint)*(ushort *)
                   (Game.game.unkCFlatData0[2] + *(int *)&gMonObj->field_0x560 * 0x48 + 10);
    if (uVar4 == 0xffff) {
      uVar4 = 0;
    }
    if (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf) {
      iVar2 = Game.game.m_gameWork.m_bossArtifactStageTable
              [Game.game.m_gameWork.m_bossArtifactStageIndex];
      iVar1 = 2;
      if (iVar2 < 2) {
        iVar1 = iVar2;
      }
    }
    else {
      iVar1 = 0;
    }
    if (0 < iVar1) {
      uVar4 = uVar4 - *(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + iVar1 * 2 + 0x58);
      uVar4 = uVar4 & ~((int)uVar4 >> 0x1f);
    }
    if (uVar4 == 0) {
      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
    }
    else {
      iVar2 = (int)uVar4 / 5 + ((int)uVar4 >> 0x1f);
      iVar2 = iVar2 - (iVar2 >> 0x1f);
      iVar1 = 1;
      if (0 < iVar2) {
        iVar1 = iVar2;
      }
      iVar1 = Rand__5CMathFUl(&Math,iVar1);
      *(uint *)&gMonObj->field_0x6f0 = uVar4 + iVar1;
      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0x11,0,0);
    }
  }
  return;
}


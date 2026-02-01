// Function: onStatAttack__8CGMonObjFi
// Entry: 80119a64
// Size: 1116 bytes

/* WARNING: Removing unreachable block (ram,0x80119ea0) */
/* WARNING: Removing unreachable block (ram,0x80119a74) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onStatAttack__8CGMonObjFi(CGMonObj *gMonObj,int param_2)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  CGPartyObj *pCVar4;
  uint uVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  
  iVar3 = Game.game.unkCFlatData0[2] + *(int *)&gMonObj->field_0x560 * 0x48;
  uVar1 = *(ushort *)(iVar3 + 0x32);
  if (param_2 == 0) {
    if ((*(int *)&gMonObj->field_0x528 == 0) && (-1 < *(int *)&gMonObj->field_0x6c4)) {
      pCVar4 = Game.game.m_partyObjArr[*(int *)&gMonObj->field_0x6c4];
      *(float *)&gMonObj->field_0x66c = (pCVar4->gCharaObj).gPrgObj.object.m_worldPosition.x;
      *(float *)&gMonObj->field_0x670 =
           *(float *)((int)&(pCVar4->gCharaObj).gPrgObj.object.m_worldPosition + 4);
      *(float *)&gMonObj->field_0x674 =
           *(float *)((int)&(pCVar4->gCharaObj).gPrgObj.object.m_worldPosition + 8);
      if ((uVar1 & 2) == 0) {
        dVar8 = (double)(FLOAT_80331a20 *
                        (float)((double)CONCAT44(0x43300000,
                                                 (uint)*(ushort *)
                                                        ((int)(gMonObj->gObject).m_scriptHandle[9] +
                                                        0x19c)) - DOUBLE_803319e0));
        if (-1 < *(int *)&gMonObj->field_0x6c4) {
          dVar6 = (double)getTargetRot__8CGPrgObjFP8CGPrgObj
                                    ((CGPrgObj *)gMonObj,
                                     Game.game.m_partyObjArr[*(int *)&gMonObj->field_0x6c4]);
          if (dVar8 <= (double)FLOAT_80331a48) {
            dVar7 = (double)DstRot__5CMathFff(dVar6,(double)(float)(gMonObj->gObject).m_bgFlags,
                                              &Math);
            dVar6 = -dVar8;
            if ((dVar6 <= dVar7) && (dVar6 = dVar7, dVar8 < dVar7)) {
              dVar6 = dVar8;
            }
            (gMonObj->gObject).m_rotTargetY =
                 (float)((double)(float)(gMonObj->gObject).m_bgFlags + dVar6);
          }
          else {
            (gMonObj->gObject).m_rotTargetY = (float)dVar6;
          }
        }
      }
      pCVar4 = Game.game.m_partyObjArr[*(int *)&gMonObj->field_0x6c4];
      (**(code **)((int)*(void **)((int)&(pCVar4->gCharaObj).gPrgObj.object.base_object + 0x48) +
                  0x4c))(pCVar4,0x17,*(undefined4 *)&gMonObj->field_0x560,pCVar4);
    }
  }
  else if (*(short *)(iVar3 + 0xe) == 3) {
    iVar3 = *(int *)&gMonObj->field_0x52c;
    if (iVar3 == 1) {
      if (*(int *)&gMonObj->field_0x530 == 0) {
        reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,*(undefined4 *)&gMonObj->field_0x554,1,0);
      }
      if (*(uint *)&gMonObj->field_0x530 ==
          (uint)*(ushort *)
                 (Game.game.unkCFlatData0[2] + *(int *)&gMonObj->field_0x560 * 0x48 + 0x2e)) {
        addSubStat__8CGPrgObjFv((CGPrgObj *)gMonObj);
      }
    }
    else if (iVar3 < 1) {
      if ((-1 < iVar3) && (iVar3 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj), iVar3 != 0)) {
        addSubStat__8CGPrgObjFv((CGPrgObj *)gMonObj);
      }
    }
    else if (iVar3 < 3) {
      if (*(int *)&gMonObj->field_0x530 == 0) {
        reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,*(undefined4 *)&gMonObj->field_0x558,0,0);
        endPSlotBit__10CGCharaObjFi(gMonObj,1);
      }
      iVar3 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
      if (iVar3 != 0) {
        uVar5 = (uint)*(ushort *)
                       (Game.game.unkCFlatData0[2] + *(int *)&gMonObj->field_0x560 * 0x48 + 10);
        if (uVar5 == 0xffff) {
          uVar5 = 0;
        }
        if (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf) {
          iVar2 = Game.game.m_gameWork.m_bossArtifactStageTable
                  [Game.game.m_gameWork.m_bossArtifactStageIndex];
          iVar3 = 2;
          if (iVar2 < 2) {
            iVar3 = iVar2;
          }
        }
        else {
          iVar3 = 0;
        }
        if (0 < iVar3) {
          uVar5 = uVar5 - *(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + iVar3 * 2 + 0x58);
          uVar5 = uVar5 & ~((int)uVar5 >> 0x1f);
        }
        if (uVar5 == 0) {
          changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
        }
        else {
          iVar2 = (int)uVar5 / 5 + ((int)uVar5 >> 0x1f);
          iVar2 = iVar2 - (iVar2 >> 0x1f);
          iVar3 = 1;
          if (0 < iVar2) {
            iVar3 = iVar2;
          }
          iVar3 = Rand__5CMathFUl(&Math,iVar3);
          *(uint *)&gMonObj->field_0x6f0 = uVar5 + iVar3;
          changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0x11,0,0);
        }
      }
    }
  }
  else {
    uVar5 = countLeadingZeros(*(undefined4 *)&gMonObj->field_0x524);
    if (((uVar5 >> 5 & 1) != 0) &&
       (iVar3 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj), iVar3 != 0)) {
      uVar5 = (uint)*(ushort *)
                     (Game.game.unkCFlatData0[2] + *(int *)&gMonObj->field_0x560 * 0x48 + 10);
      if (uVar5 == 0xffff) {
        uVar5 = 0;
      }
      if (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf) {
        iVar2 = Game.game.m_gameWork.m_bossArtifactStageTable
                [Game.game.m_gameWork.m_bossArtifactStageIndex];
        iVar3 = 2;
        if (iVar2 < 2) {
          iVar3 = iVar2;
        }
      }
      else {
        iVar3 = 0;
      }
      if (0 < iVar3) {
        uVar5 = uVar5 - *(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + iVar3 * 2 + 0x58);
        uVar5 = uVar5 & ~((int)uVar5 >> 0x1f);
      }
      if (uVar5 == 0) {
        changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
      }
      else {
        iVar2 = (int)uVar5 / 5 + ((int)uVar5 >> 0x1f);
        iVar2 = iVar2 - (iVar2 >> 0x1f);
        iVar3 = 1;
        if (0 < iVar2) {
          iVar3 = iVar2;
        }
        iVar3 = Rand__5CMathFUl(&Math,iVar3);
        *(uint *)&gMonObj->field_0x6f0 = uVar5 + iVar3;
        changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0x11,0,0);
      }
    }
  }
  return;
}


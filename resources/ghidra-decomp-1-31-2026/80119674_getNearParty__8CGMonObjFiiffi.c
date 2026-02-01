// Function: getNearParty__8CGMonObjFiiffi
// Entry: 80119674
// Size: 700 bytes

/* WARNING: Removing unreachable block (ram,0x80119914) */
/* WARNING: Removing unreachable block (ram,0x8011990c) */
/* WARNING: Removing unreachable block (ram,0x8011968c) */
/* WARNING: Removing unreachable block (ram,0x80119684) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int getNearParty__8CGMonObjFiiffi
              (double param_1,double param_2,CGMonObj *gMonObj,int param_4,uint param_5,
              void *param_6)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  CGMonObj *pCVar5;
  CGPartyObj *pCVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  double dVar10;
  Vec local_88;
  Vec VStack_7c;
  
  iVar9 = 0;
  iVar4 = -1;
  iVar8 = 0;
  pCVar5 = gMonObj;
  do {
    iVar7 = *(int *)&pCVar5->field_0x620;
    iVar1 = iVar7 * 4;
    pCVar6 = Game.game.m_partyObjArr[iVar7];
    if ((((((pCVar6 != (CGPartyObj *)0x0) &&
           ((((Game.game.m_gameWork.m_menuStageMode == '\0' ||
              (0xe < Game.game.m_gameWork.m_bossArtifactStageIndex)) ||
             (uVar3 = (**(code **)((int)*(void **)((int)&(pCVar6->gCharaObj).gPrgObj.object.
                                                         base_object + 0x48) + 0xc))(pCVar6),
             (uVar3 & 0x6d) != 0x6d)) ||
            ((pCVar6->gCharaObj).gPrgObj.object.m_scriptHandle[0xed] == (void *)0x0)))) &&
          (((param_5 & 1) == 0 ||
           ((((*(short *)((pCVar6->gCharaObj).gPrgObj.object.m_scriptHandle + 7) != 0 &&
              (iVar2 = (pCVar6->gCharaObj).gPrgObj.m_lastStateId, iVar2 != 9)) && (iVar2 != 0x22))
            && (((Game.game.m_gameWork.m_menuStageMode == '\0' ||
                 (0xe < Game.game.m_gameWork.m_bossArtifactStageIndex)) ||
                ((uVar3 = (**(code **)((int)*(void **)((int)&(pCVar6->gCharaObj).gPrgObj.object.
                                                             base_object + 0x48) + 0xc))(pCVar6),
                 (uVar3 & 0x6d) != 0x6d ||
                 ((pCVar6->gCharaObj).gPrgObj.object.m_scriptHandle[0xed] == (void *)0x0))))))))))
         && ((((param_5 & 0x10) == 0 ||
              (*(short *)((int)(pCVar6->gCharaObj).gPrgObj.object.m_scriptHandle + 0x4e) != 0)) &&
             ((((param_5 & 0x20) == 0 ||
               (((iVar2 = (pCVar6->gCharaObj).gPrgObj.m_lastStateId, iVar2 == 6 || (iVar2 == 2)) &&
                ((pCVar6->gCharaObj).gPrgObj.m_subState == 1)))) &&
              (((param_5 & 0x40) == 0 ||
               ((-1 < *(int *)&(pCVar6->gCharaObj).field_0x6c0 &&
                ((pCVar6->gCharaObj).gPrgObj.object.m_scriptHandle[4] == param_6)))))))))) &&
        (((param_5 & 2) != 0 || (param_1 <= (double)*(float *)(&gMonObj->field_0x5d0 + iVar1))))) &&
       (((param_5 & 4) != 0 || ((double)*(float *)(&gMonObj->field_0x5d0 + iVar1) <= param_2)))) {
      if (((param_5 & 8) != 0) && (FLOAT_803319d8 < *(float *)(&gMonObj->field_0x5d0 + iVar1))) {
        PSVECSubtract(&(pCVar6->gCharaObj).gPrgObj.object.m_worldPosition,
                      &(gMonObj->gObject).m_worldPosition,&VStack_7c);
        PSVECScale(FLOAT_803319c0 / *(float *)(&gMonObj->field_0x5d0 + iVar1),&VStack_7c,&VStack_7c)
        ;
        dVar10 = (double)sin((double)(gMonObj->gObject).m_rotTargetY);
        local_88.x = (float)dVar10;
        local_88.y = FLOAT_803319d8;
        dVar10 = (double)cos((double)(gMonObj->gObject).m_rotTargetY);
        local_88.z = (float)dVar10;
        dVar10 = (double)PSVECDotProduct(&VStack_7c,&local_88);
        if (dVar10 <= (double)FLOAT_803319d8) goto LAB_801198f8;
      }
      if (((param_4 == -1) || (param_4 == iVar9)) && (iVar4 = iVar7, param_4 == iVar9)) {
        return iVar7;
      }
      iVar9 = iVar9 + 1;
    }
LAB_801198f8:
    iVar8 = iVar8 + 1;
    pCVar5 = (CGMonObj *)&(pCVar5->gObject).base_object.object.m_freeListNode;
    if (3 < iVar8) {
      return iVar4;
    }
  } while( true );
}


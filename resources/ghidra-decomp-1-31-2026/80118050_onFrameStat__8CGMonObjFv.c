// Function: onFrameStat__8CGMonObjFv
// Entry: 80118050
// Size: 4648 bytes

/* WARNING: Removing unreachable block (ram,0x80119250) */
/* WARNING: Removing unreachable block (ram,0x80118060) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onFrameStat__8CGMonObjFv(CGMonObj *gMonObj)

{
  float fVar1;
  byte bVar2;
  short sVar3;
  bool bVar4;
  float fVar5;
  int iVar6;
  void *pvVar7;
  Vec *pVVar8;
  CRef *pCVar9;
  void *pvVar10;
  undefined4 uVar11;
  void **ppvVar12;
  uint uVar13;
  CGPartyObj *pCVar14;
  double dVar15;
  double dVar16;
  Vec local_b8;
  float local_ac;
  float local_a8;
  float local_a4;
  CVector CStack_a0;
  CVector CStack_94;
  Vec local_88;
  CVector CStack_7c;
  CVector CStack_70;
  float local_64;
  float local_60;
  float local_5c;
  Vec VStack_58;
  Vec VStack_4c;
  Vec local_40;
  undefined4 local_30;
  uint uStack_2c;
  undefined4 local_28;
  uint uStack_24;
  
  iVar6 = *(int *)&gMonObj->field_0x520;
  if (iVar6 == 0x11) {
LAB_801180a0:
    if (*(short *)((gMonObj->gObject).m_scriptHandle + 7) != 0) {
      iVar6 = *(int *)&gMonObj->field_0x6c4;
      if ((iVar6 < 0) ||
         ((iVar6 >= 0 &&
          (*(short *)((Game.game.m_partyObjArr[iVar6]->gCharaObj).gPrgObj.object.m_scriptHandle + 7)
           == 0)))) {
        bVar4 = false;
      }
      else {
        bVar4 = true;
      }
      if (!bVar4) {
        *(undefined4 *)&gMonObj->field_0x6c4 = 0xffffffff;
        changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
      }
    }
  }
  else if (iVar6 < 0x11) {
    if (iVar6 == 3) goto LAB_801180a0;
  }
  else if (iVar6 == 0x1e) goto LAB_801180a0;
  __ptmf_scall(gMonObj,*(undefined4 *)&gMonObj->field_0x708);
  dVar16 = DOUBLE_803319e0;
  fVar1 = FLOAT_803319d8;
  switch(*(undefined4 *)&gMonObj->field_0x520) {
  case 0:
    if (0x2c < *(int *)&gMonObj->field_0x6f4) {
      gMonObj->field_0x63c = gMonObj->field_0x63c & 0x7f | 0x80;
    }
    if (*(int *)&gMonObj->field_0x528 == 0) {
      reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0xffffffff,0,0);
    }
    break;
  case 3:
    gMonObj->field_0x63c = gMonObj->field_0x63c & 0x7f | 0x80;
    if ((*(int *)&gMonObj->field_0x528 == 0) &&
       (CancelAnim__8CGObjectFi(&gMonObj->gObject,1), gMonObj->field_0x6b8 == '\0')) {
      ppvVar12 = (gMonObj->gObject).m_scriptHandle;
      iVar6 = Rand__5CMathFUl(&Math,3);
      pvVar7 = ppvVar12[9];
      playSe3D__8CGPrgObjFiiiiP3Vec
                ((CGPrgObj *)gMonObj,
                 (uint)*(ushort *)((int)pvVar7 + 0x192) +
                 (uint)*(ushort *)((int)pvVar7 + 400) * 1000 + iVar6,0x32,0x96,0,0);
      gMonObj->field_0x6b8 = 1;
    }
    iVar6 = *(int *)&gMonObj->field_0x6c4;
    if ((iVar6 < 0) || (3 < iVar6)) {
      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
    }
    else {
      pCVar14 = Game.game.m_partyObjArr[iVar6];
      local_40.x = (pCVar14->gCharaObj).gPrgObj.object.m_worldPosition.x;
      local_40.y = *(float *)((int)&(pCVar14->gCharaObj).gPrgObj.object.m_worldPosition + 4);
      local_40.z = *(float *)((int)&(pCVar14->gCharaObj).gPrgObj.object.m_worldPosition + 8);
      PSVECSubtract(&local_40,&(gMonObj->gObject).m_worldPosition,&VStack_4c);
      local_30 = 0x43300000;
      uStack_2c = (uint)*(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0xd4);
      MoveVector__8CGObjectFP3Vecfiiii
                ((double)(*(float *)&gMonObj->field_0x690 *
                         (FLOAT_803319cc *
                          (float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_803319e0) +
                         FLOAT_803319c8)),&gMonObj->gObject,&VStack_4c,1,1,0,1);
    }
    break;
  case 0x10:
    gMonObj->field_0x63c = gMonObj->field_0x63c & 0x7f | 0x80;
    if (*(int *)&gMonObj->field_0x528 == 0) {
      reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0xffffffff,0,0);
    }
    iVar6 = Rand__5CMathFUl(&Math,0x32);
    if (iVar6 == 0) {
      iVar6 = Rand__5CMathFUl(&Math,2);
      if (iVar6 == 0) {
        (gMonObj->gObject).m_rotTargetY = (gMonObj->gObject).m_rotTargetY + FLOAT_80331a04;
      }
      else {
        (gMonObj->gObject).m_rotTargetY = (gMonObj->gObject).m_rotTargetY - FLOAT_80331a04;
      }
    }
    break;
  case 0x11:
    if (*(int *)&gMonObj->field_0x528 == 0) {
      reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0xffffffff,0,0);
    }
    sVar3 = *(short *)&gMonObj->field_0x6e4;
    if (sVar3 == 0) {
      pvVar7 = (gMonObj->gObject).m_scriptHandle[9];
    }
    else {
      pvVar7 = (void *)(Game.game.unkCFlatData0[1] +
                       ((int)sVar3 +
                       (uint)*(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0x100)) * 0x1d0
                       + 0x10);
    }
    pvVar10 = (gMonObj->gObject).m_scriptHandle[9];
    local_30 = 0x43300000;
    uStack_2c = (uint)*(ushort *)((int)pvVar10 + 0xce);
    fVar1 = (float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_803319e0);
    if (*(short *)((int)pvVar7 + 0x10a) == 2) {
      if (*(short *)((int)pvVar10 + 0x10c) == 1) {
        if (*(int *)&gMonObj->field_0x52c == 0) {
          uVar13 = 0;
          if (sVar3 != 0) {
            pvVar10 = (void *)(Game.game.unkCFlatData0[1] +
                              ((int)sVar3 + (uint)*(ushort *)((int)pvVar10 + 0x100)) * 0x1d0 + 0x10)
            ;
          }
          if ((*(ushort *)((int)pvVar10 + 0x102) & 0x10) != 0) {
            uVar13 = 0x8000;
          }
          pCVar14 = Game.game.m_partyObjArr[*(int *)&gMonObj->field_0x6c4];
          if (*(int *)&gMonObj->field_0x734 != 4) {
            memset(&gMonObj->field_0x70c,0,0x34);
            *(undefined4 *)&gMonObj->field_0x70c = 0x855;
            if ((*(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0xfe) & 4) != 0) {
              *(uint *)&gMonObj->field_0x70c = *(uint *)&gMonObj->field_0x70c | 0x400;
            }
            if (*(short *)&gMonObj->field_0x6e4 == 0) {
              pvVar7 = (gMonObj->gObject).m_scriptHandle[9];
            }
            else {
              pvVar7 = (void *)(Game.game.unkCFlatData0[1] +
                               ((int)*(short *)&gMonObj->field_0x6e4 +
                               (uint)*(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0x100))
                               * 0x1d0 + 0x10);
            }
            if ((*(ushort *)((int)pvVar7 + 0x102) & 0x80) != 0) {
              *(uint *)&gMonObj->field_0x70c = *(uint *)&gMonObj->field_0x70c | 0x20000;
            }
            dVar16 = DOUBLE_803319e0;
            *(uint *)&gMonObj->field_0x70c = *(uint *)&gMonObj->field_0x70c | uVar13;
            *(undefined4 *)&gMonObj->field_0x70c = *(undefined4 *)&gMonObj->field_0x70c;
            *(undefined4 *)&gMonObj->field_0x734 = 4;
            uStack_2c = (uint)*(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0xce);
            *(float *)&gMonObj->field_0x728 =
                 (float)((double)CONCAT44(0x43300000,uStack_2c) - dVar16);
            *(uint *)&gMonObj->field_0x72c =
                 (uint)*(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0x1b6);
          }
          local_30 = 0x43300000;
          *(CGPartyObj **)&gMonObj->field_0x714 = pCVar14;
          moveFrame__8CGMonObjFv(gMonObj);
          if (((*(uint *)&gMonObj->field_0x710 & 1) != 0) ||
             (bVar2 = (gMonObj->gObject).m_stateFlags0,
             (int)((uint)bVar2 << 0x19 | (uint)(bVar2 >> 7)) < 0)) {
            reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0xffffffff,0,0);
            if (-1 < *(int *)&gMonObj->field_0x6c4) {
              dVar16 = (double)getTargetRot__8CGPrgObjFP8CGPrgObj
                                         ((CGPrgObj *)gMonObj,
                                          Game.game.m_partyObjArr[*(int *)&gMonObj->field_0x6c4]);
              (gMonObj->gObject).m_rotTargetY = (float)dVar16;
            }
            *(undefined4 *)&gMonObj->field_0x52c = 1;
          }
        }
      }
      else {
        if ((*(int *)&gMonObj->field_0x528 == 0) &&
           (*(float *)(&gMonObj->field_0x5d0 + *(int *)&gMonObj->field_0x6c4 * 4) < fVar1)) {
          *(undefined4 *)&gMonObj->field_0x52c = 1;
        }
        if (*(int *)&gMonObj->field_0x52c == 1) {
          pvVar7 = (gMonObj->gObject).m_scriptHandle[9];
          uVar13 = (uint)*(ushort *)((int)pvVar7 + 0x1b6);
          if ((int)*(uint *)&gMonObj->field_0x528 <= (int)uVar13) {
            bVar2 = (gMonObj->gObject).m_stateFlags0;
            if ((((int)((uint)bVar2 << 0x19 | (uint)(bVar2 >> 7)) < 0) ||
                (*(uint *)&gMonObj->field_0x528 == uVar13)) ||
               (fVar1 <= *(float *)(&gMonObj->field_0x5d0 + *(int *)&gMonObj->field_0x6c4 * 4))) {
              *(undefined4 *)&gMonObj->field_0x52c = 0;
              dVar16 = (double)getTargetRot__8CGPrgObjFP8CGPrgObj
                                         ((CGPrgObj *)gMonObj,
                                          Game.game.m_partyObjArr[*(int *)&gMonObj->field_0x6c4]);
              (gMonObj->gObject).m_rotTargetY = (float)dVar16;
            }
            else {
              uStack_2c = (uint)*(ushort *)((int)pvVar7 + 0xd4);
              local_30 = 0x43300000;
              dVar16 = (double)(*(float *)&gMonObj->field_0x690 *
                               (FLOAT_803319cc *
                                (float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_803319e0) +
                               FLOAT_803319c8));
              __ct__7CVectorFRC3Vec
                        (&CStack_7c,
                         &(Game.game.m_partyObjArr[*(int *)&gMonObj->field_0x6c4]->gCharaObj).
                          gPrgObj.object.m_worldPosition);
              pVVar8 = (Vec *)__ct__7CVectorFRC3Vec(&CStack_70,&(gMonObj->gObject).m_worldPosition);
              __ct__7CVectorFv(&local_88);
              PSVECSubtract(pVVar8,(Vec *)&CStack_7c,&local_88);
              local_64 = local_88.x;
              local_60 = local_88.y;
              local_5c = local_88.z;
              moveVector__8CGObjectFP3Vecfi(dVar16,&gMonObj->gObject,&local_64,1);
            }
          }
        }
      }
    }
    if (*(int *)&gMonObj->field_0x6f0 <= *(int *)&gMonObj->field_0x528) {
      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
    }
    break;
  case 0x16:
    if (*(int *)&gMonObj->field_0x528 == 0) {
      reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0x2c,0,0);
    }
    else {
      iVar6 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
      if (iVar6 != 0) {
        gMonObj->field_0x6b9 = 0;
        changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
      }
    }
    break;
  case 0x17:
    if (*(int *)&gMonObj->field_0x528 == 0) {
      reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0x2d,0,0);
    }
    else {
      iVar6 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
      if (iVar6 != 0) {
        gMonObj->field_0x6b9 = 1;
        changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
      }
    }
    break;
  case 0x18:
    if (*(int *)&gMonObj->field_0x528 == 0) {
      gMonObj->_bossBranchRelated = 1;
      reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0x10,0,0);
      SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0,0);
      SetAnimSlot__8CGObjectFii(&gMonObj->gObject,4,4);
      (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask | 0x50000;
      (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask & 0xfffffff7;
      (gMonObj->gObject).m_objectFlags = (gMonObj->gObject).m_objectFlags & 0xffffffef;
    }
    iVar6 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
    if (iVar6 != 0) {
      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
    }
    break;
  case 0x1c:
    gMonObj->field_0x63c = gMonObj->field_0x63c & 0x7f | 0x80;
    if (*(int *)&gMonObj->field_0x528 == 0) {
      CancelAnim__8CGObjectFi(&gMonObj->gObject,1);
    }
    PSVECSubtract((Vec *)&gMonObj->field_0x6f8,&(gMonObj->gObject).m_worldPosition,&VStack_58);
    local_30 = 0x43300000;
    uStack_2c = (uint)*(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0xd4);
    MoveVector__8CGObjectFP3Vecfiiii
              ((double)(*(float *)&gMonObj->field_0x690 *
                       (FLOAT_803319cc *
                        (float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_803319e0) +
                       FLOAT_803319c8)),&gMonObj->gObject,&VStack_58,1,1,0,1);
    break;
  case 0x1d:
    gMonObj->field_0x63c = gMonObj->field_0x63c & 0x7f | 0x80;
    iVar6 = *(int *)&gMonObj->field_0x52c;
    if (iVar6 == 1) {
      iVar6 = Rand__5CMathFUl(&Math,100);
      if (iVar6 == 0) {
        changeSubStat__8CGPrgObjFi((CGPrgObj *)gMonObj,0);
      }
    }
    else if ((iVar6 < 1) && (-1 < iVar6)) {
      if (*(int *)&gMonObj->field_0x530 == 0) {
        ppvVar12 = (gMonObj->gObject).m_scriptHandle;
        iVar6 = Rand__5CMathFUl(&Math,0x50);
        dVar16 = (double)RandF__5CMathFv(&Math);
        uStack_2c = (uint)*(ushort *)((int)ppvVar12[9] + 0xd4);
        local_30 = 0x43300000;
        moveVectorRot__8CGObjectFfffi
                  ((double)(FLOAT_803319fc * (float)((double)FLOAT_803319c4 * dVar16)),
                   (double)FLOAT_803319d8,
                   (double)(FLOAT_80331a00 *
                           *(float *)&gMonObj->field_0x690 *
                           (FLOAT_803319cc *
                            (float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_803319e0) +
                           FLOAT_803319c8)),&gMonObj->gObject,iVar6 + 10);
      }
      else {
        bVar2 = *(byte *)((int)&(gMonObj->gObject).m_weaponNodeFlags + 1);
        if ((-1 < (int)((uint)bVar2 << 0x1a | (uint)(bVar2 >> 6))) ||
           (bVar2 = (gMonObj->gObject).m_stateFlags0,
           (int)((uint)bVar2 << 0x19 | (uint)(bVar2 >> 7)) < 0)) {
          CancelMove__8CGObjectFi(&gMonObj->gObject,1);
          changeSubStat__8CGPrgObjFi((CGPrgObj *)gMonObj,1);
        }
      }
    }
    break;
  case 0x1e:
    uStack_2c = (uint)*(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0xd4);
    local_30 = 0x43300000;
    dVar16 = (double)(*(float *)&gMonObj->field_0x690 *
                     (FLOAT_803319cc *
                      (float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_803319e0) +
                     FLOAT_803319c8));
    __ct__7CVectorFRC3Vec
              (&CStack_94,
               &(Game.game.m_partyObjArr[*(int *)&gMonObj->field_0x6c4]->gCharaObj).gPrgObj.object.
                m_worldPosition);
    pVVar8 = (Vec *)__ct__7CVectorFRC3Vec(&CStack_a0,&(gMonObj->gObject).m_worldPosition);
    __ct__7CVectorFv(&local_b8);
    PSVECSubtract(pVVar8,(Vec *)&CStack_94,&local_b8);
    local_ac = local_b8.x;
    local_a8 = local_b8.y;
    local_a4 = local_b8.z;
    moveVector__8CGObjectFP3Vecfi(dVar16,&gMonObj->gObject,&local_ac,1);
    local_28 = 0x43300000;
    pvVar7 = (gMonObj->gObject).m_scriptHandle[9];
    uStack_24 = (uint)*(ushort *)((int)pvVar7 + 0xce);
    if (((*(uint *)&gMonObj->field_0x528 == (uint)*(ushort *)((int)pvVar7 + 0x1b6)) ||
        ((float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_803319e0) <=
         *(float *)(&gMonObj->field_0x5d0 + *(int *)&gMonObj->field_0x6c4 * 4))) ||
       (bVar2 = (gMonObj->gObject).m_stateFlags0,
       (int)((uint)bVar2 << 0x19 | (uint)(bVar2 >> 7)) < 0)) {
      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
      if (-1 < *(int *)&gMonObj->field_0x6c4) {
        dVar16 = (double)getTargetRot__8CGPrgObjFP8CGPrgObj
                                   ((CGPrgObj *)gMonObj,
                                    Game.game.m_partyObjArr[*(int *)&gMonObj->field_0x6c4]);
        (gMonObj->gObject).m_rotTargetY = (float)dVar16;
      }
    }
    break;
  case 0x21:
    gMonObj->field_0x63c = gMonObj->field_0x63c & 0x7f | 0x80;
    moveFrame__8CGMonObjFv(gMonObj);
    break;
  case 0x32:
    if (*(int *)&gMonObj->field_0x528 == 0) {
      pvVar7 = (gMonObj->gObject).m_scriptHandle[4];
      if (((int)pvVar7 - 0x10U < 3) || (pvVar7 == (void *)0x5e)) {
        iVar6 = 0xf;
        uVar11 = 0x2ef1;
      }
      else {
        iVar6 = 0xd;
        uVar11 = 0xcb37;
      }
      *(float *)&gMonObj->field_0x694 = FLOAT_803319c0;
      *(byte *)&(gMonObj->gObject).m_weaponNodeFlags =
           *(byte *)&(gMonObj->gObject).m_weaponNodeFlags & 0xef | 0x10;
      (gMonObj->gObject).m_groundHitOffset.z = fVar1;
      (gMonObj->gObject).m_groundHitOffset.y = fVar1;
      (gMonObj->gObject).m_groundHitOffset.x = fVar1;
      (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask | 0x11;
      (gMonObj->gObject).m_displayFlags = (gMonObj->gObject).m_displayFlags | 1;
      *(float *)&gMonObj->field_0x6f8 = (gMonObj->gObject).unk_0x168;
      *(float *)&gMonObj->field_0x6fc = (gMonObj->gObject).unk_0x16C;
      *(float *)&gMonObj->field_0x700 = (gMonObj->gObject).unk_0x170;
      (gMonObj->gObject).m_worldPosition.x = *(float *)&gMonObj->field_0x6f8;
      (gMonObj->gObject).m_worldPosition.y = *(float *)&gMonObj->field_0x6fc;
      (gMonObj->gObject).m_worldPosition.z = *(float *)&gMonObj->field_0x700;
      reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,iVar6,0,0);
      playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,uVar11,0x32,0x96,0,0);
      if (iVar6 == 0xf) {
        if (pvVar7 == (void *)0x5e) {
          pCVar9 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
          if (pCVar9 == (CRef *)0x0) {
            iVar6 = -1;
          }
          else {
            iVar6 = pCVar9[2].refCount;
          }
          putParticle__8CGPrgObjFiiP8CGObjectfi
                    ((double)FLOAT_803319c0,(CGPrgObj *)gMonObj,iVar6 << 8 | 8,0,&gMonObj->gObject,0
                    );
        }
        else {
          pCVar9 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
          if (pCVar9 == (CRef *)0x0) {
            iVar6 = -1;
          }
          else {
            iVar6 = pCVar9[2].refCount;
          }
          putParticle__8CGPrgObjFiiP8CGObjectfi
                    ((double)FLOAT_803319c0,(CGPrgObj *)gMonObj,iVar6 << 8 | 7,0,&gMonObj->gObject,0
                    );
        }
      }
      else {
        pCVar9 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
        if (pCVar9 == (CRef *)0x0) {
          iVar6 = -1;
        }
        else {
          iVar6 = pCVar9[2].refCount;
        }
        putParticle__8CGPrgObjFiiP8CGObjectfi
                  ((double)FLOAT_803319c0,(CGPrgObj *)gMonObj,iVar6 << 8 | 2,2,&gMonObj->gObject,0);
      }
    }
    iVar6 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
    if (iVar6 != 0) {
      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
      (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask | 0xd0002;
      (**(code **)((int)(gMonObj->gObject).base_object.object.m_vtable + 0x94))(gMonObj,1);
      gMonObj->_bossBranchRelated = 1;
    }
    break;
  case 0x33:
    if (*(int *)&gMonObj->field_0x528 == 0) {
      pvVar7 = (gMonObj->gObject).m_scriptHandle[4];
      *(float *)&gMonObj->field_0x694 = FLOAT_803319c0;
      uVar13 = countLeadingZeros(0x3c - (int)pvVar7);
      *(byte *)&(gMonObj->gObject).m_weaponNodeFlags =
           *(byte *)&(gMonObj->gObject).m_weaponNodeFlags & 0xef | 0x10;
      (gMonObj->gObject).m_groundHitOffset.z = fVar1;
      (gMonObj->gObject).m_groundHitOffset.y = fVar1;
      (gMonObj->gObject).m_groundHitOffset.x = fVar1;
      (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask | 0x11;
      (gMonObj->gObject).m_displayFlags = (gMonObj->gObject).m_displayFlags | 1;
      reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0xd,0,0);
      playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,(uVar13 >> 5) + 0x7936,0x32,0x96,0,0);
      pCVar9 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
      if (pCVar9 == (CRef *)0x0) {
        iVar6 = -1;
      }
      else {
        iVar6 = pCVar9[2].refCount;
      }
      putParticle__8CGPrgObjFiiP8CGObjectfi
                ((double)FLOAT_803319c0,(CGPrgObj *)gMonObj,iVar6 << 8 | 4,0,&gMonObj->gObject,0);
    }
    iVar6 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
    if (iVar6 != 0) {
      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
      (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask | 0xd0002;
      (**(code **)((int)(gMonObj->gObject).base_object.object.m_vtable + 0x94))(gMonObj,1);
      gMonObj->_bossBranchRelated = 1;
    }
    break;
  case 0x34:
    if (*(int *)&gMonObj->field_0x528 == 0) {
      if ((gMonObj->gObject).m_scriptHandle[4] == (void *)0x39) {
        uVar13 = 4;
        uVar11 = 0xc36e;
      }
      else {
        uVar13 = 5;
        uVar11 = 0xb3d1;
      }
      *(byte *)&(gMonObj->gObject).m_weaponNodeFlags =
           *(byte *)&(gMonObj->gObject).m_weaponNodeFlags & 0xef | 0x10;
      (gMonObj->gObject).m_groundHitOffset.z = fVar1;
      (gMonObj->gObject).m_groundHitOffset.y = fVar1;
      (gMonObj->gObject).m_groundHitOffset.x = fVar1;
      (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask | 0x11;
      (gMonObj->gObject).m_displayFlags = (gMonObj->gObject).m_displayFlags | 1;
      reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0xb,0,0);
      playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,uVar11,0x32,0x96,0,0);
      pCVar9 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
      if (pCVar9 == (CRef *)0x0) {
        iVar6 = -1;
      }
      else {
        iVar6 = pCVar9[2].refCount;
      }
      putParticle__8CGPrgObjFiiP8CGObjectfi
                ((double)FLOAT_803319c0,(CGPrgObj *)gMonObj,uVar13 | iVar6 << 8,0,&gMonObj->gObject,
                 0);
    }
    iVar6 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
    if (iVar6 != 0) {
      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
      (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask | 0xd0002;
      (**(code **)((int)(gMonObj->gObject).base_object.object.m_vtable + 0x94))(gMonObj,1);
      (gMonObj->gObject).m_displayFlags = (gMonObj->gObject).m_displayFlags | 1;
      gMonObj->_bossBranchRelated = 1;
      SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0,0);
      if ((gMonObj->gObject).m_scriptHandle[4] == (void *)0x39) {
        SetAnimSlot__8CGObjectFii(&gMonObj->gObject,1,1);
        SetAnimSlot__8CGObjectFii(&gMonObj->gObject,4,4);
        SetAnimSlot__8CGObjectFii(&gMonObj->gObject,6,6);
      }
    }
    break;
  case 0x35:
    if (*(int *)&gMonObj->field_0x528 == 0) {
      local_28 = 0x43300000;
      *(float *)&gMonObj->field_0x694 = FLOAT_803319c0;
      fVar5 = FLOAT_803319cc;
      fVar1 = FLOAT_803319c8;
      dVar15 = (double)FLOAT_803319d8;
      (gMonObj->gObject).m_displayFlags = (gMonObj->gObject).m_displayFlags | 1;
      uStack_24 = (uint)*(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0xd4);
      moveVectorRot__8CGObjectFfffi
                ((double)(gMonObj->gObject).m_rotBaseY,dVar15,
                 (double)(fVar5 * (float)((double)CONCAT44(0x43300000,uStack_24) - dVar16) + fVar1),
                 &gMonObj->gObject,0x14);
    }
    if (*(int *)&gMonObj->field_0x528 == 0x10) {
      (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask | 0xd0002;
      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
    }
    break;
  case 0x36:
    if (*(int *)&gMonObj->field_0x52c != 0) {
      if (*(int *)&gMonObj->field_0x52c == 1) {
        if (*(int *)&gMonObj->field_0x530 == 0) {
          reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0x10,0,0);
        }
        else {
          iVar6 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
          if (iVar6 != 0) {
            changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
          }
        }
      }
      break;
    }
    if (*(int *)&gMonObj->field_0x530 == 0) {
      pCVar9 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
      if (pCVar9 == (CRef *)0x0) {
        iVar6 = -1;
      }
      else {
        iVar6 = pCVar9[2].refCount;
      }
      putParticle__8CGPrgObjFiiP8CGObjectfi
                ((double)FLOAT_803319c0,(CGPrgObj *)gMonObj,iVar6 << 8 | 4,0,&gMonObj->gObject,0);
      reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0xf,1,0);
      uVar11 = 0;
      pvVar7 = (gMonObj->gObject).m_scriptHandle[4];
      if (pvVar7 == (void *)0xa7) {
LAB_80119100:
        uVar11 = 0x12130;
      }
      else if ((int)pvVar7 < 0xa7) {
        if (pvVar7 == (void *)0x9c) goto LAB_80119100;
      }
      else if (pvVar7 == (void *)0xa9) {
        uVar11 = 0x1213a;
      }
      else if ((int)pvVar7 < 0xa9) {
        uVar11 = 0x12126;
      }
      playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,uVar11,0x32,0x96,0,0);
    }
    if (*(int *)&gMonObj->field_0x530 == 0x32) {
      changeSubStat__8CGPrgObjFi((CGPrgObj *)gMonObj,1);
    }
  }
  onFrameStat__10CGCharaObjFv((CGCharaObj *)gMonObj);
  return;
}


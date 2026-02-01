// Function: ?MonObjRelated
// Entry: 8011467c
// Size: 1272 bytes

/* WARNING: Removing unreachable block (ram,0x80114b4c) */
/* WARNING: Removing unreachable block (ram,0x80114880) */
/* WARNING: Removing unreachable block (ram,0x8011468c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void _MonObjRelated(CGMonObj *gMonObj)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  void *pvVar4;
  void **ppvVar5;
  CGPartyObj *pCVar6;
  double dVar7;
  double dVar8;
  undefined auStack_38 [4];
  int local_34 [5];
  
  iVar3 = *(int *)&gMonObj->field_0x6d8;
  if (iVar3 == 3) {
    FUN_801162f0();
    goto LAB_80114b28;
  }
  if (2 < iVar3) {
    if (iVar3 == 5) {
      if (*(int *)&gMonObj->field_0x6c4 < 0) {
        SoundBuffer._1252_4_ = 0;
        memset(&gMonObj->field_0x70c,0,0x34);
        *(undefined4 *)&gMonObj->field_0x6d8 = 0;
        *(undefined4 *)&gMonObj->field_0x6dc = 0;
        gMonObj->field_0x6bb = 1;
      }
      else {
        SoundBuffer._1252_4_ = 0x21;
        pCVar6 = Game.game.m_partyObjArr[*(int *)&gMonObj->field_0x6c4];
        if (*(int *)&gMonObj->field_0x734 != 4) {
          memset(&gMonObj->field_0x70c,0,0x34);
          *(undefined4 *)&gMonObj->field_0x70c = 0x855;
          if ((*(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0xfe) & 4) != 0) {
            *(uint *)&gMonObj->field_0x70c = *(uint *)&gMonObj->field_0x70c | 0x400;
          }
          if (*(short *)&gMonObj->field_0x6e4 == 0) {
            pvVar4 = (gMonObj->gObject).m_scriptHandle[9];
          }
          else {
            pvVar4 = (void *)(Game.game.unkCFlatData0[1] +
                             ((int)*(short *)&gMonObj->field_0x6e4 +
                             (uint)*(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0x100)) *
                             0x1d0 + 0x10);
          }
          if ((*(ushort *)((int)pvVar4 + 0x102) & 0x80) != 0) {
            *(uint *)&gMonObj->field_0x70c = *(uint *)&gMonObj->field_0x70c | 0x20000;
          }
          dVar7 = DOUBLE_803319e0;
          local_34[1] = 0x43300000;
          *(undefined4 *)&gMonObj->field_0x70c = *(undefined4 *)&gMonObj->field_0x70c;
          *(undefined4 *)&gMonObj->field_0x734 = 4;
          local_34[2] = (int)*(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0xce);
          *(float *)&gMonObj->field_0x728 =
               (float)((double)CONCAT44(0x43300000,local_34[2]) - dVar7);
          *(uint *)&gMonObj->field_0x72c =
               (uint)*(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0x1b6);
        }
        *(CGPartyObj **)&gMonObj->field_0x714 = pCVar6;
        if (((*(uint *)&gMonObj->field_0x710 & 1) != 0) ||
           (bVar1 = (gMonObj->gObject).m_stateFlags0,
           (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)) < 0)) {
          SoundBuffer._1252_4_ = 0;
          memset(&gMonObj->field_0x70c,0,0x34);
          if (-1 < *(int *)&gMonObj->field_0x6c4) {
            dVar7 = (double)getTargetRot__8CGPrgObjFP8CGPrgObj
                                      ((CGPrgObj *)gMonObj,
                                       Game.game.m_partyObjArr[*(int *)&gMonObj->field_0x6c4]);
            (gMonObj->gObject).m_rotTargetY = (float)dVar7;
          }
          *(undefined4 *)&gMonObj->field_0x6d8 = 1;
          *(undefined4 *)&gMonObj->field_0x6dc = 0;
          gMonObj->field_0x6bb = 1;
        }
      }
    }
    else if (iVar3 < 5) {
      FUN_80116654();
    }
    goto LAB_80114b28;
  }
  if (iVar3 == 1) {
    FUN_80114b74();
    goto LAB_80114b28;
  }
  if (0 < iVar3) {
    FUN_80115c00();
    goto LAB_80114b28;
  }
  if (iVar3 < 0) goto LAB_80114b28;
  if (*(short *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0x10c) == 1) {
    SoundBuffer._1252_4_ = 0;
    memset(&gMonObj->field_0x70c,0,0x34);
  }
  if (*(int *)&gMonObj->field_0x6dc == 0) {
    (gMonObj->gObject).m_rotTargetY = (float)(gMonObj->gObject).m_bgFlags;
  }
  dVar7 = DOUBLE_80331a18;
  if (Game.game.m_gameWork.m_soundOptionFlag != '\0') {
    dVar7 = DOUBLE_80331a10;
  }
  if (dVar7 <= (double)*(float *)&gMonObj->field_0x5bc) {
LAB_801147a0:
    local_34[0] = -1;
  }
  else {
    local_34[1] = 0x43300000;
    local_34[2] = (int)*(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 200);
    FUN_80116870((double)(gMonObj->gObject).m_rotBaseY,
                 (double)(float)((double)CONCAT44(0x43300000,local_34[2]) - DOUBLE_803319e0),gMonObj
                 ,6,auStack_38,local_34);
    if (local_34[0] < 0) goto LAB_801147a0;
  }
  if (local_34[0] < 0) {
    if (*(short *)&gMonObj->field_0x6e4 == 0) {
      pvVar4 = (gMonObj->gObject).m_scriptHandle[9];
    }
    else {
      pvVar4 = (void *)(Game.game.unkCFlatData0[1] +
                       ((int)*(short *)&gMonObj->field_0x6e4 +
                       (uint)*(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0x100)) * 0x1d0
                       + 0x10);
    }
    uVar2 = *(ushort *)((int)pvVar4 + 0x104);
    if (uVar2 == 1) {
      SoundBuffer._1252_4_ = 0x10;
    }
    else if (uVar2 == 0) {
      SoundBuffer._1252_4_ = 0;
    }
    else if (uVar2 < 3) {
      dVar7 = DOUBLE_80331a18;
      if (Game.game.m_gameWork.m_soundOptionFlag != '\0') {
        dVar7 = DOUBLE_80331a10;
      }
      if (dVar7 <= (double)*(float *)&gMonObj->field_0x5bc) {
        SoundBuffer._1252_4_ = 0;
      }
      else {
        SoundBuffer._1252_4_ = 0x1d;
        local_34[1] = 0x43300000;
        local_34[2] = (int)*(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0xcc);
        dVar8 = (double)(float)((double)CONCAT44(0x43300000,local_34[2]) - DOUBLE_803319e0);
        dVar7 = (double)PSVECDistance((Vec *)&gMonObj->field_0x6f8,
                                      &(gMonObj->gObject).m_worldPosition);
        if (dVar8 <= dVar7) {
          FUN_801162f0(gMonObj);
        }
      }
    }
  }
  else {
    *(int *)&gMonObj->field_0x6c4 = local_34[0];
    *(undefined4 *)&gMonObj->field_0x6d8 = 2;
    *(undefined4 *)&gMonObj->field_0x6dc = 0;
    gMonObj->field_0x6bb = 1;
    if (gMonObj->field_0x6b8 == '\0') {
      ppvVar5 = (gMonObj->gObject).m_scriptHandle;
      iVar3 = Rand__5CMathFUl(&Math,3);
      pvVar4 = ppvVar5[9];
      playSe3D__8CGPrgObjFiiiiP3Vec
                ((CGPrgObj *)gMonObj,
                 (uint)*(ushort *)((int)pvVar4 + 0x192) +
                 (uint)*(ushort *)((int)pvVar4 + 400) * 1000 + iVar3,0x32,0x96,0,0);
      gMonObj->field_0x6b8 = 1;
    }
  }
LAB_80114b28:
  if (gMonObj->field_0x6bb == '\0') {
    *(int *)&gMonObj->field_0x6dc = *(int *)&gMonObj->field_0x6dc + 1;
  }
  else {
    gMonObj->field_0x6bb = 0;
  }
  return;
}


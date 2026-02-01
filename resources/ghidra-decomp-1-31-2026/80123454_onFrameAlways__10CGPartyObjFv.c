// Function: onFrameAlways__10CGPartyObjFv
// Entry: 80123454
// Size: 1140 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onFrameAlways__10CGPartyObjFv(CGPrgObj *param_1)

{
  int *piVar1;
  short sVar2;
  ushort uVar3;
  float fVar4;
  void **ppvVar5;
  short *psVar6;
  uint uVar7;
  CCharaPcsCHandle *pCVar8;
  bool bVar9;
  int iVar10;
  CGObject *pCVar11;
  void *pvVar12;
  
  if ((param_1->object).m_scriptHandle != (void **)0x0) {
    fVar4 = param_1[1].object.m_attachLocal.x;
    if ((fVar4 != 0.0) && ((int)((uint)*(byte *)((int)fVar4 + 0x38) << 0x18) < 0)) {
      param_1[1].object.m_attachLocal.x = 0.0;
    }
    if ((*(short *)((param_1->object).m_scriptHandle + 7) == 0) ||
       (sVar2._0_1_ = (param_1->object).m_lastMapIdHit,
       sVar2._1_1_ = (param_1->object).m_lastMapIdExtra, sVar2 != 1)) {
      LoadWeapon__8CGObjectFii(&param_1->object,0xffffffff,0);
      LoadShield__8CGObjectFi(&param_1->object,0xffffffff);
    }
    else {
      if ((param_1->object).m_weaponModelHandle == (CCharaPcsCHandle *)0x0) {
        iVar10 = param_1[1].object.m_attachNode;
        pCVar11 = param_1[1].object.m_attachOwner;
        if (iVar10 < 1) {
          LoadWeapon__8CGObjectFii(&param_1->object,0xffffffff,0);
        }
        else {
          uVar3 = *(ushort *)(Game.game.unkCFlatData0[2] + iVar10 * 0x48 + 2);
          LoadWeapon__8CGObjectFii(&param_1->object,uVar3 & 0xfff,(int)(uint)uVar3 >> 0xc);
        }
        param_1[1].object.m_attachOwner = pCVar11;
        param_1[1].object.m_attachNode = iVar10;
        SetCurrentWeaponIdx__12CCaravanWorkFi
                  ((CCaravanWork *)(param_1->object).m_scriptHandle,
                   (int)param_1[1].object.m_attachOwner);
        *(byte *)&param_1[1].object.m_rotationX = *(byte *)&param_1[1].object.m_rotationX & 0xdf;
      }
      ppvVar5 = (param_1->object).m_scriptHandle;
      iVar10 = (int)*(short *)(ppvVar5 + 0x2c);
      if (iVar10 < 0) {
        iVar10 = 0;
      }
      else {
        iVar10 = (int)*(short *)((int)ppvVar5 + iVar10 * 2 + 0xb6);
      }
      if (iVar10 < 1) {
        LoadShield__8CGObjectFi(&param_1->object,0xffffffff);
      }
      else {
        pCVar8 = (param_1->object).m_shieldModelHandle;
        uVar7 = *(ushort *)(Game.game.unkCFlatData0[2] + iVar10 * 0x48 + 2) & 0xfff;
        if ((pCVar8 == (CCharaPcsCHandle *)0x0) || (pCVar8->m_charaNo != uVar7)) {
          LoadShield__8CGObjectFi(&param_1->object,uVar7);
        }
      }
    }
    CalcStatus__12CCaravanWorkFv((param_1->object).m_scriptHandle);
    pvVar12 = (param_1->object).m_scriptHandle[0xed];
    if ((((Game.game.m_gameWork.m_gameInitFlag == '\0') ||
         (-1 < (int)((uint)(byte)CFlat._4836_1_ << 0x1c | (uint)((byte)CFlat._4836_1_ >> 4)))) ||
        (-1 < (int)((uint)(byte)CFlat._4836_1_ << 0x1d | (uint)((byte)CFlat._4836_1_ >> 3)))) ||
       (((-1 < (int)((uint)*(byte *)&(param_1->object).m_weaponNodeFlags << 0x18) ||
         (-1 < (int)((uint)*(byte *)((int)&(param_1->object).m_weaponNodeFlags + 1) << 0x18))) ||
        ((param_1->m_lastStateId == 6 || (param_1->m_lastStateId == 2)))))) {
      bVar9 = false;
    }
    else if (((Game.game.m_gameWork.m_menuStageMode == '\0') ||
             (Game.game.m_gameWork.m_menuStageMode == '\0')) ||
            ((0xe < Game.game.m_gameWork.m_bossArtifactStageIndex ||
             ((uVar7 = (**(code **)((int)(param_1->object).base_object.object.m_vtable + 0xc))
                                 (param_1), (uVar7 & 0x6d) != 0x6d ||
              ((param_1->object).m_scriptHandle[0xed] == (void *)0x0)))))) {
      bVar9 = true;
    }
    else {
      bVar9 = false;
    }
    if ((bVar9) && (piVar1 = (int *)(&CFlat.field_0x1041c + (int)pvVar12 * 4), *piVar1 == 0)) {
      iVar10 = GetFreeParticleSlot__13CFlatRuntime2Fv();
      *piVar1 = iVar10;
      putParticleTrace__8CGPrgObjFiiP8CGObjectfi
                (SUB84((double)FLOAT_80331a54,0),param_1,(int)pvVar12 + 0x42U | 0x100,*piVar1,
                 &param_1->object,0);
    }
    else if (!bVar9) {
      iVar10 = *(int *)(&CFlat.field_0x1041c + (int)pvVar12 * 4);
      if (iVar10 != 0) {
        EndParticleSlot__13CFlatRuntime2Fii((CFlatRuntime2 *)&CFlat,iVar10);
        *(int *)(&CFlat.field_0x1041c + (int)pvVar12 * 4) = 0;
      }
    }
    if (((param_1->object).m_scriptHandle[0xed] == (void *)0x0) &&
       ((MiniGamePcs._25732_4_ & 0x400) != 0)) {
      addRealTime__6CAStarFP10CGPartyObj((CAStar *)&DbgMenuPcs.field_0x2a5c,(CGPartyObj *)param_1);
    }
    if ((MiniGamePcs._25732_4_ & 0x2000) != 0) {
      do {
        do {
          iVar10 = Rand__5CMathFUl(&Math,0x155);
          iVar10 = iVar10 + 0x9f;
          psVar6 = (short *)(Game.game.unkCFlatData0[2] + iVar10 * 0x48);
        } while (*psVar6 == 0);
        uVar3 = psVar6[1];
      } while ((((uVar3 & 0xfff) == 0) || ((uVar3 & 0xfff) == 0xffff)) || (iVar10 == 400));
      if ((param_1->object).m_scriptHandle[0xed] == (void *)0x0) {
        CreateFromScript__9CGItemObjFiiiP8CGObjectfPQ29CGItemObj4CCFS
                  ((double)FLOAT_80331a78,0,4,iVar10,param_1,0);
        iVar10 = Rand__5CMathFUl(&Math,10);
        if (iVar10 == 0) {
          CreateFromScript__9CGItemObjFiiiP8CGObjectfPQ29CGItemObj4CCFS
                    ((double)FLOAT_80331a78,2,4,0x3039,param_1,0);
        }
      }
      iVar10 = Rand__5CMathFUl(&Math,0x1a);
      iVar10 = iVar10 + 1;
      if (iVar10 == 0xf) {
        iVar10 = 1;
      }
      LoadWeapon__8CGObjectFii(&param_1->object,iVar10,0);
      iVar10 = Rand__5CMathFUl(&Math,0x1a);
      iVar10 = iVar10 + 1;
      if (iVar10 == 0xf) {
        iVar10 = 1;
      }
      LoadShield__8CGObjectFi(&param_1->object,iVar10);
    }
  }
  return;
}


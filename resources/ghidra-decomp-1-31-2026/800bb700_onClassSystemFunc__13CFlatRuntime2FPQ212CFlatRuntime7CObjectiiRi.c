// Function: onClassSystemFunc__13CFlatRuntime2FPQ212CFlatRuntime7CObjectiiRi
// Entry: 800bb700
// Size: 8520 bytes

/* WARNING: Removing unreachable block (ram,0x800bd82c) */
/* WARNING: Removing unreachable block (ram,0x800bd824) */
/* WARNING: Removing unreachable block (ram,0x800bd81c) */
/* WARNING: Removing unreachable block (ram,0x800bd814) */
/* WARNING: Removing unreachable block (ram,0x800bb728) */
/* WARNING: Removing unreachable block (ram,0x800bb720) */
/* WARNING: Removing unreachable block (ram,0x800bb718) */
/* WARNING: Removing unreachable block (ram,0x800bb710) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4
onClassSystemFunc__13CFlatRuntime2FPQ212CFlatRuntime7CObjectiiRi
          (CFlatRuntime2 *flatRuntime2,CObject *object,undefined4 param_3,undefined4 param_4,
          undefined4 *param_5)

{
  uint8_t uVar1;
  byte bVar2;
  bool bVar3;
  uint32_t uVar4;
  CCharaPcsCHandle *handle;
  float fVar5;
  undefined4 uVar6;
  int iVar7;
  uint uVar8;
  Vec *pVVar9;
  CCaravanWork *pCVar10;
  CGObject *pCVar11;
  float *pfVar12;
  float fVar13;
  undefined2 uVar16;
  void **ppvVar14;
  uint32_t uVar15;
  int iVar17;
  uint32_t *puVar18;
  CModel *pCVar19;
  void *pvVar20;
  CGCharaObj *gCharaObj;
  double dVar21;
  double dVar22;
  double dVar23;
  double dVar24;
  double dVar25;
  undefined4 local_19c;
  undefined local_198 [8];
  CVector CStack_190;
  CVector CStack_184;
  CVector CStack_178;
  CVector CStack_16c;
  CVector CStack_160;
  CVector CStack_154;
  uint32_t local_148;
  uint32_t local_144;
  uint32_t local_140;
  uint32_t local_13c;
  uint32_t local_138;
  uint32_t local_134;
  undefined4 local_130;
  undefined4 local_12c;
  undefined4 local_128;
  float local_124;
  float local_120;
  float local_11c;
  Vec local_118;
  undefined4 local_10c;
  undefined4 local_108;
  undefined4 local_104;
  uint32_t local_100;
  uint32_t local_fc;
  uint32_t local_f8;
  uint32_t local_f4;
  uint32_t local_f0;
  uint32_t local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  Vec local_d0;
  uint32_t local_c4;
  uint32_t local_c0;
  uint32_t local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  Vec VStack_a0;
  Vec local_94;
  Vec local_88;
  uint32_t local_7c;
  uint32_t local_78;
  uint32_t local_74;
  uint32_t local_70;
  uint32_t local_6c;
  uint32_t local_68;
  undefined4 local_60;
  uint uStack_5c;
  
  fVar13 = FLOAT_80330bc8;
  gCharaObj = (CGCharaObj *)object->m_engineObject;
  switch(param_4) {
  case 0xffffff61:
    uVar6 = IsAnimFinished__8CGObjectFi((CGObject *)gCharaObj,0);
    uVar8 = countLeadingZeros(uVar6);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar8 >> 5 & 0xff);
    *param_5 = 0;
    break;
  case 0xffffff62:
    (gCharaObj->gPrgObj).object.m_groundHitOffset.x =
         (gCharaObj->gPrgObj).object.m_groundHitOffset.x + (float)*object->m_localBase;
    (gCharaObj->gPrgObj).object.m_groundHitOffset.y =
         (gCharaObj->gPrgObj).object.m_groundHitOffset.y + (float)object->m_localBase[1];
    (gCharaObj->gPrgObj).object.m_groundHitOffset.z =
         (gCharaObj->gPrgObj).object.m_groundHitOffset.z + (float)object->m_localBase[2];
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff63:
    uVar6 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0x48))
                      (gCharaObj,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar6);
    *param_5 = 0;
    break;
  case 0xffffff64:
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti
              (flatRuntime2,object,(gCharaObj->gPrgObj).object.m_bgColMask);
    *param_5 = 0;
    break;
  case 0xffffff65:
    ((gCharaObj->gPrgObj).object.m_charaModelHandle)->m_model->m_attachMode =
         (uint8_t)*object->m_localBase;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff66:
    puVar18 = object->m_localBase;
    PlayAnim__8CGObjectFiiiiiPSc
              ((CGObject *)gCharaObj,*puVar18,1,1,(short)puVar18[1],(short)puVar18[2],0);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff67:
    puVar18 = object->m_localBase;
    PlayAnim__8CGObjectFiiiiiPSc
              ((CGObject *)gCharaObj,*puVar18,0,1,(short)puVar18[1],(short)puVar18[2],0);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  default:
    return 0;
  case 0xffffff69:
    OpenMenu__8GbaQueueFiii
              (&GbaQue,(gCharaObj->gPrgObj).object.m_scriptHandle[0xed],*object->m_localBase,1);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff6a:
    addHp__10CGCharaObjFiP8CGPrgObj(gCharaObj,*object->m_localBase,(CGPrgObj *)0x0);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff6b:
    puVar18 = object->m_localBase;
    PutMemoryCapsule__10CGPartyObjFiiiiPc
              (gCharaObj,*puVar18,puVar18[1],puVar18[2],puVar18[3],
               (flatRuntime2->flatRuntimeBase).m_strBlob +
               (flatRuntime2->flatRuntimeBase).m_strOffs[puVar18[4]]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff6c:
    SetArtifact__12CCaravanWorkFii
              ((CCaravanWork *)(gCharaObj->gPrgObj).object.m_scriptHandle,*object->m_localBase,
               object->m_localBase[1]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff6d:
    puVar18 = object->m_localBase;
    local_148 = *puVar18;
    local_144 = puVar18[1];
    local_140 = puVar18[2];
    Move__8CGObjectFP3Vecfiiiii
              ((double)(float)puVar18[3],(CGObject *)gCharaObj,&local_148,puVar18[4],1,0,1,0);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff6e:
    PutDropItem__8CGObjectFv((CGObject *)gCharaObj);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff6f:
    fVar5 = (float)object->m_localBase[1];
    fVar13 = (float)*object->m_localBase;
    pCVar19 = ((gCharaObj->gPrgObj).object.m_charaModelHandle)->m_model;
    pCVar19->m_furTarget = fVar13;
    if (fVar5 != 0.0) {
      pCVar19->m_furCur = fVar13;
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff70:
    (gCharaObj->gPrgObj).object.m_lookAtAccumYaw = (float)*object->m_localBase;
    (gCharaObj->gPrgObj).object.m_lookAtAccumPitch = (float)object->m_localBase[1];
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff71:
    (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0x44))
              (gCharaObj,*object->m_localBase,object->m_localBase[1]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff72:
    uVar4 = *object->m_localBase;
    pCVar11 = (CGObject *)
              (**(code **)((int)(flatRuntime2->flatRuntimeBase).vtable + 0x3c))
                        (flatRuntime2,object->m_localBase[1]);
    carry__10CGPartyObjFiP8CGObjecti((CGPartyObj *)gCharaObj,uVar4,pCVar11,object->m_localBase[2]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff73:
    commandFinished__10CGPartyObjFv(gCharaObj);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff74:
    uVar6 = 0;
    if (*object->m_localBase != 0) {
      uVar6 = (**(code **)((int)(flatRuntime2->flatRuntimeBase).vtable + 0x3c))();
    }
    LookAt__8CGObjectFP8CGObjectPc
              ((CGObject *)gCharaObj,uVar6,
               (flatRuntime2->flatRuntimeBase).m_strBlob +
               (flatRuntime2->flatRuntimeBase).m_strOffs[object->m_localBase[1]]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff75:
    (gCharaObj->gPrgObj).object.m_moveModePrevious = (uint8_t)*object->m_localBase;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff77:
    puVar18 = object->m_localBase;
    local_13c = *puVar18;
    local_138 = puVar18[1];
    local_134 = puVar18[2];
    Move__8CGObjectFP3Vecfiiiii
              ((double)(float)puVar18[3],(CGObject *)gCharaObj,&local_13c,puVar18[4],1,1,1,1);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff78:
    CalcSphereNearPos__8CGObjectFffR3Vec
              ((double)(float)*object->m_localBase,(double)(float)object->m_localBase[1],
               (CGObject *)gCharaObj,&local_130);
    *(undefined4 *)object->m_localBase[2] = local_130;
    *(undefined4 *)object->m_localBase[3] = local_12c;
    *(undefined4 *)object->m_localBase[4] = local_128;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff79:
    fVar13 = (float)object->m_localBase[1];
    pCVar19 = ((gCharaObj->gPrgObj).object.m_charaModelHandle)->m_model;
    pCVar19->m_furLenScale = (float)*object->m_localBase;
    pCVar19->m_furStep = fVar13;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff7a:
    pCVar19 = ((gCharaObj->gPrgObj).object.m_charaModelHandle)->m_model;
    pCVar19->m_flags0x10C =
         (byte)((int)(char)*object->m_localBase << 6) & 0x40 | pCVar19->m_flags0x10C & 0xbf;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff7b:
    puVar18 = object->m_localBase;
    uVar6 = ShopRequest__12CCaravanWorkFiiiiiii
                      ((CCaravanWork *)(gCharaObj->gPrgObj).object.m_scriptHandle,*puVar18,
                       puVar18[1],puVar18[2],puVar18[3],puVar18[4],(char)puVar18[5]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar6);
    *param_5 = 0;
    break;
  case 0xffffff7d:
    PlayAnim__8CGObjectFiiiiiPSc((CGObject *)gCharaObj,*object->m_localBase,1,1,0xffff,0xffff,0);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff7e:
    PlayAnim__8CGObjectFiiiiiPSc((CGObject *)gCharaObj,*object->m_localBase,0,1,0xffff,0xffff,0);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff81:
    pvVar20 = (void *)flatRuntime2->field61765_0x10410;
    flatRuntime2->field61765_0x10410 = (int)pvVar20 + 1;
    if (-1 < Game.game.m_gameWork.m_wmBackupParams[(int)pvVar20]) {
      SetClassWork__8CGObjectFii((CGObject *)gCharaObj,0,pvVar20);
      (gCharaObj->gPrgObj).object.m_scriptHandle[0xed] = pvVar20;
      Game.game.m_partyObjArr[(int)pvVar20] = (CGPartyObj *)gCharaObj;
      SendAllStat__6JoyBusFi(&Joybus,(int)pvVar20);
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff82:
    iVar7 = flatRuntime2->field61764_0x1040c;
    uVar4 = *object->m_localBase;
    flatRuntime2->field61764_0x1040c = iVar7 + 1;
    SetClassWork__8CGObjectFii((CGObject *)gCharaObj,1,iVar7);
    InitWork__8CGObjectFi((CGObject *)gCharaObj,uVar4);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff83:
    if (*object->m_localBase == 1) {
      (gCharaObj->gPrgObj).object.m_bodyEllipsoidAspect = (float)object->m_localBase[1];
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff84:
    uVar6 = GetFoodRank__12CCaravanWorkFi
                      ((CCaravanWork *)(gCharaObj->gPrgObj).object.m_scriptHandle,
                       *object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar6);
    *param_5 = 0;
    break;
  case 0xffffff86:
    puVar18 = object->m_localBase;
    PlayAnim__8CGObjectFiiiiiPSc
              ((CGObject *)gCharaObj,*puVar18,1,0,(short)puVar18[1],(short)puVar18[2],0);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff87:
    iVar17 = 0;
    iVar7 = (gCharaObj->gPrgObj).object.base_object.object.m_argCount + -1;
    if (0 < iVar7) {
      puVar18 = object->m_localBase;
      iVar17 = 1;
      local_198[0] = (undefined)puVar18[1];
      if (1 < iVar7) {
        iVar17 = 2;
        local_198[1] = (undefined)puVar18[2];
        if (2 < iVar7) {
          iVar17 = 3;
          local_198[2] = (undefined)puVar18[3];
          if (3 < iVar7) {
            iVar17 = 4;
            local_198[3] = (undefined)puVar18[4];
          }
        }
      }
    }
    local_198[iVar17] = 0xff;
    PlayAnim__8CGObjectFiiiiiPSc
              ((CGObject *)gCharaObj,*object->m_localBase,0,0,0xffff,0xffff,local_198);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff88:
    puVar18 = object->m_localBase;
    PlayAnim__8CGObjectFiiiiiPSc
              ((CGObject *)gCharaObj,*puVar18,0,0,(short)puVar18[1],(short)puVar18[2],0);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff89:
    pCVar10 = (CCaravanWork *)(gCharaObj->gPrgObj).object.m_scriptHandle;
    uVar4 = *object->m_localBase;
    uVar15 = object->m_localBase[1];
    if (uVar4 != 2) {
      if ((int)uVar4 < 2) {
        if (0 < (int)uVar4) {
          DeleteItemIdx__12CCaravanWorkFii(pCVar10,uVar15,1);
        }
      }
      else if ((int)uVar4 < 4) {
        DeleteCmdList__12CCaravanWorkFii(pCVar10,uVar15,1);
      }
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff8a:
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti
              (flatRuntime2,object,(gCharaObj->gPrgObj).object.m_scriptHandle[0x228]);
    *param_5 = 0;
    break;
  case 0xffffff8b:
    ppvVar14 = (gCharaObj->gPrgObj).object.m_scriptHandle;
    if (ppvVar14[0x227] != (void *)*object->m_localBase) {
      ppvVar14[0x227] = (void *)*object->m_localBase;
      ppvVar14[0x228] = (void *)0x0;
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff8c:
    pfVar12 = (float *)object->m_localBase;
    local_118.x = *pfVar12;
    local_118.y = pfVar12[1];
    local_118.z = pfVar12[2];
    dVar23 = (double)PSVECMag(&local_118);
    if ((double)FLOAT_80330bc8 == dVar23) {
      local_118.x = FLOAT_80330bc8;
      local_118.y = FLOAT_80330bc8;
      local_118.z = FLOAT_80330bc8;
    }
    else {
      PSVECScale((float)((double)FLOAT_80330bd8 / dVar23),&local_118,&local_118);
    }
    MoveVector__8CGObjectFP3Vecfiiii
              ((double)(float)object->m_localBase[3],(CGObject *)gCharaObj,&local_118,
               object->m_localBase[4],1,1,1);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff8d:
    bVar3 = false;
    pvVar20 = (gCharaObj->gPrgObj).object.m_scriptHandle[0xed];
    if ((Pad._452_4_ != 0) || ((pvVar20 == (void *)0x0 && (Pad._448_4_ != -1)))) {
      bVar3 = true;
    }
    if (bVar3) {
      uVar6 = 0;
    }
    else {
      uVar6 = *(undefined4 *)
               (&Pad.field_0x54 +
               ((uint)pvVar20 &
               ~(~(Pad._448_4_ - (int)pvVar20 | (int)pvVar20 - Pad._448_4_) >> 0x1f)) * 0x54);
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar6);
    *param_5 = 0;
    break;
  case 0xffffff8e:
    SetDispItemName__8CGObjectFi((CGObject *)gCharaObj,(char)*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff8f:
    (gCharaObj->gPrgObj).object.m_jumpLandingDampening = (float)*object->m_localBase;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff90:
    (gCharaObj->gPrgObj).object.m_stateFlags0 =
         (byte)((int)(char)*object->m_localBase << 4) & 0x10 |
         (gCharaObj->gPrgObj).object.m_stateFlags0 & 0xef;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff91:
    fVar13 = (float)*object->m_localBase;
    (gCharaObj->gPrgObj).object.m_moveOffset.z = fVar13;
    (gCharaObj->gPrgObj).object.m_moveOffset.x = fVar13;
    (gCharaObj->gPrgObj).object.m_moveOffset.y = (float)object->m_localBase[1];
    (gCharaObj->gPrgObj).object.m_bounceFactor = (float)object->m_localBase[2];
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff92:
    *(uint32_t *)(gCharaObj->gPrgObj).object.m_lastBgAttr = *object->m_localBase;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff93:
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff94:
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff96:
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff97:
    SetBattleCommand__9CRingMenuFiii
              (*(CRingMenu **)
                (&MenuPcs.field_0x13c + (int)(gCharaObj->gPrgObj).object.m_scriptHandle[0xed] * 4),
               *object->m_localBase,object->m_localBase[1],0xffffffff);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff98:
    SetBattleButton__9CRingMenuFii
              (*(CRingMenu **)
                (&MenuPcs.field_0x13c + (int)(gCharaObj->gPrgObj).object.m_scriptHandle[0xed] * 4),
               *object->m_localBase,object->m_localBase[1]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff9c:
    *(short *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle + 0x3e6) =
         (short)*object->m_localBase;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff9d:
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffff9e:
    uVar6 = ChgCtrlMode__6JoyBusFi(&Joybus,(gCharaObj->gPrgObj).object.m_scriptHandle[0xed]);
    uVar8 = countLeadingZeros(uVar6);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar8 >> 5 & 0xff);
    *param_5 = 0;
    break;
  case 0xffffff9f:
    puVar18 = object->m_localBase;
    AddLetter__12CCaravanWorkFiiiiiiiii
              ((CCaravanWork *)(gCharaObj->gPrgObj).object.m_scriptHandle,*puVar18,puVar18[1],
               puVar18[2],puVar18[3],puVar18[4],(short)puVar18[5],(short)puVar18[6],
               (short)puVar18[7],(short)puVar18[8]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffa0:
    pCVar11 = (CGObject *)
              (**(code **)((int)(flatRuntime2->flatRuntimeBase).vtable + 0x3c))
                        (flatRuntime2,object->m_localBase[1]);
    dVar23 = (double)CalcSafePos__8CGObjectFiP8CGObjectP3Vec
                               ((CGObject *)gCharaObj,*object->m_localBase,pCVar11,&local_10c);
    *(undefined4 *)object->m_localBase[2] = local_10c;
    *(undefined4 *)object->m_localBase[3] = local_108;
    *(undefined4 *)object->m_localBase[4] = local_104;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,(float)dVar23);
    *param_5 = 0;
    break;
  case 0xffffffa1:
    handle = (gCharaObj->gPrgObj).object.m_charaModelHandle;
    if (handle == (CCharaPcsCHandle *)0x0) {
      push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
      *param_5 = 0;
    }
    else {
      iVar7 = pppIsDeadCHandle__8CPartMngFPQ29CCharaPcs7CHandle(&PartMng,handle);
      if (iVar7 != 0) {
        push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
        *param_5 = 0;
      }
    }
    break;
  case 0xffffffa3:
    *(short *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle + *object->m_localBase * 2 + 0xf0) =
         (short)object->m_localBase[1];
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffa4:
    *(short *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle + *object->m_localBase * 2 + 0xd0) =
         (short)object->m_localBase[1];
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffa6:
    *(short *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle + *object->m_localBase * 2 + 0x8c) =
         (short)object->m_localBase[1];
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffaa:
    *(short *)((int)(gCharaObj->gPrgObj).object.m_scriptHandle + 0x1a) =
         (short)object->m_localBase[1];
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffab:
    *(short *)((gCharaObj->gPrgObj).object.m_scriptHandle + 7) = (short)object->m_localBase[1];
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffac:
    dVar22 = (double)(float)object->m_localBase[1];
    dVar21 = (double)(float)*object->m_localBase;
    dVar23 = (double)cos(dVar22);
    dVar24 = (double)(float)dVar23;
    dVar23 = (double)sin(dVar21);
    local_124 = (float)((double)(float)dVar23 * dVar24);
    dVar23 = (double)sin(dVar22);
    local_120 = (float)dVar23;
    dVar23 = (double)cos(dVar22);
    dVar22 = (double)(float)dVar23;
    dVar23 = (double)cos(dVar21);
    local_11c = (float)((double)(float)dVar23 * dVar22);
    MoveVector__8CGObjectFP3Vecfiiii
              ((double)(float)object->m_localBase[2],(CGObject *)gCharaObj,&local_124,
               object->m_localBase[3],0,0,1);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffad:
    (gCharaObj->gPrgObj).object.m_scriptHandle[0x80] = (void *)*object->m_localBase;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffae:
    uVar8 = 0;
    if ((*object->m_localBase & 2) != 0) {
      iVar7 = FindItem__12CCaravanWorkFi
                        ((CCaravanWork *)(gCharaObj->gPrgObj).object.m_scriptHandle,
                         object->m_localBase[1]);
      uVar8 = 0xffffffffU - (iVar7 >> 0x1f) & 2;
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar8);
    *param_5 = 0;
    break;
  case 0xffffffb1:
    pCVar10 = (CCaravanWork *)(gCharaObj->gPrgObj).object.m_scriptHandle;
    uVar4 = *object->m_localBase;
    local_19c = 0xffffffff;
    if (uVar4 != 2) {
      uVar16 = (undefined2)object->m_localBase[1];
      if ((int)uVar4 < 2) {
        if (0 < (int)uVar4) {
          AddItem__12CCaravanWorkFiPi(pCVar10,uVar16,&local_19c);
        }
      }
      else if ((int)uVar4 < 4) {
        AddComList__12CCaravanWorkFiPi(pCVar10,uVar16,&local_19c);
      }
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,local_19c);
    *param_5 = 0;
    break;
  case 0xffffffb5:
    ResetDynamics__8CGObjectFv((CGObject *)gCharaObj);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffb6:
    (gCharaObj->gPrgObj).object.m_hitNormal.x = (float)*object->m_localBase;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffb8:
    (gCharaObj->gPrgObj).object.m_stepSlopeLimit = (float)object->m_localBase[1];
    if (*object->m_localBase != 0) {
      (gCharaObj->gPrgObj).object.m_lookAtTimer = (gCharaObj->gPrgObj).object.m_stepSlopeLimit;
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffba:
    uVar6 = 0;
    if (*object->m_localBase != 0) {
      uVar6 = (**(code **)((int)(flatRuntime2->flatRuntimeBase).vtable + 0x3c))();
    }
    LookAt__8CGObjectFP8CGObjectPc((CGObject *)gCharaObj,uVar6,0);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffbb:
    SetTexAnim__8CGObjectFPc
              ((CGObject *)gCharaObj,
               (flatRuntime2->flatRuntimeBase).m_strBlob +
               (flatRuntime2->flatRuntimeBase).m_strOffs[*object->m_localBase]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffbc:
    pfVar12 = (float *)object->m_localBase;
    moveVectorHRot__8CGObjectFfffi
              ((double)*pfVar12,(double)pfVar12[1],(double)pfVar12[2],(CGObject *)gCharaObj,
               pfVar12[3]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffbd:
    pfVar12 = (float *)object->m_localBase;
    moveVectorRot__8CGObjectFfffi
              ((double)*pfVar12,(double)pfVar12[1],(double)pfVar12[2],(CGObject *)gCharaObj,
               pfVar12[3]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffbf:
    local_60 = 0x43300000;
    uStack_5c = *object->m_localBase ^ 0x80000000;
    (gCharaObj->gPrgObj).object.m_bgDownDist =
         FLOAT_80330bd8 / (float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80330bd0);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffc4:
    (gCharaObj->gPrgObj).object.m_frontHitAngle = (float)*object->m_localBase;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffc5:
    puVar18 = object->m_localBase;
    GraphicsPcs._108_4_ = *puVar18;
    GraphicsPcs._112_4_ = 1;
    GraphicsPcs._120_4_ = puVar18[1];
    GraphicsPcs._100_1_ = (undefined)puVar18[2];
    GraphicsPcs._101_1_ = (undefined)puVar18[3];
    GraphicsPcs._102_1_ = (undefined)puVar18[4];
    GraphicsPcs._103_1_ = 0xff;
    GraphicsPcs._92_4_ = puVar18[5];
    GraphicsPcs._96_4_ = GraphicsPcs._92_4_;
    GraphicsPcs._116_4_ = gCharaObj;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffc6:
    FreeAnim__8CGObjectFi((CGObject *)gCharaObj);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffc7:
    (gCharaObj->gPrgObj).object.m_pushParamA = (uint8_t)*object->m_localBase;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffc8:
    PlayAnim__8CGObjectFiiiiiPSc((CGObject *)gCharaObj,*object->m_localBase,1,0,0xffff,0xffff,0);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffc9:
    puVar18 = object->m_localBase;
    local_100 = *puVar18;
    local_fc = puVar18[1];
    local_f8 = puVar18[2];
    Move__8CGObjectFP3Vecfiiiii
              ((double)(float)puVar18[3],(CGObject *)gCharaObj,&local_100,puVar18[4],1,0,0,0);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffca:
    pfVar12 = (float *)object->m_localBase;
    uVar6 = __ct__7CVectorFfff(*pfVar12,pfVar12[1],pfVar12[2],&CStack_190);
    moveVectorH__8CGObjectFP3Vecfi
              ((double)(float)object->m_localBase[3],(CGObject *)gCharaObj,uVar6,
               object->m_localBase[4]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffcb:
    puVar18 = object->m_localBase;
    local_f4 = *puVar18;
    local_f0 = puVar18[1];
    local_ec = puVar18[2];
    Move__8CGObjectFP3Vecfiiiii
              ((double)(float)puVar18[3],(CGObject *)gCharaObj,&local_f4,puVar18[4],0,0,0,0);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffcc:
    if (*object->m_localBase != 0) {
      ResetAnimPoint__8CGObjectFi((CGObject *)gCharaObj,object->m_localBase[1]);
    }
    puVar18 = object->m_localBase;
    AddAnimPoint__8CGObjectFiii
              ((CGObject *)gCharaObj,puVar18[1],(short)puVar18[3],(short)puVar18[2]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffcd:
    fVar13 = (float)*object->m_localBase;
    (gCharaObj->gPrgObj).object.m_rotTargetY = fVar13;
    (gCharaObj->gPrgObj).object.m_rotBaseY = fVar13;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffcf:
    (gCharaObj->gPrgObj).object.m_moveVec.x = (float)*object->m_localBase;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffd0:
    uVar4 = *object->m_localBase;
    fVar13 = (float)object->m_localBase[1];
    if (uVar4 == 0xffffffff) {
      (gCharaObj->gPrgObj).object.m_damageColliders[1].m_localPosition.x = fVar13;
      (gCharaObj->gPrgObj).object.m_damageColliders[2].m_localPosition.x = fVar13;
      (gCharaObj->gPrgObj).object.m_damageColliders[3].m_localPosition.x = fVar13;
      (gCharaObj->gPrgObj).object.m_damageColliders[4].m_localPosition.x = fVar13;
      (gCharaObj->gPrgObj).object.m_damageColliders[5].m_localPosition.x = fVar13;
      (gCharaObj->gPrgObj).object.m_damageColliders[6].m_localPosition.x = fVar13;
      (gCharaObj->gPrgObj).object.m_damageColliders[7].m_localPosition.x = fVar13;
      (gCharaObj->gPrgObj).object.m_animPhase = fVar13;
    }
    else {
      (gCharaObj->gPrgObj).object.m_damageColliders[uVar4 + 1].m_localPosition.x = fVar13;
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffd1:
    puVar18 = object->m_localBase;
    pVVar9 = (Vec *)__ct__7CVectorFfff((float)puVar18[4],(float)puVar18[5],(float)puVar18[6],
                                       &CStack_184);
    puVar18 = object->m_localBase;
    SetDamageCol__8CGObjectFiPcffP3Vec
              ((double)(float)puVar18[2],(double)(float)puVar18[3],(CGObject *)gCharaObj,*puVar18,
               (flatRuntime2->flatRuntimeBase).m_strBlob +
               (flatRuntime2->flatRuntimeBase).m_strOffs[puVar18[1]],pVVar9);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffd2:
    uVar4 = *object->m_localBase;
    fVar13 = (float)object->m_localBase[1];
    if (uVar4 == 0xffffffff) {
      (gCharaObj->gPrgObj).object.m_attackColliders[1].m_localStart.x = fVar13;
      (gCharaObj->gPrgObj).object.m_attackColliders[2].m_localStart.x = fVar13;
      (gCharaObj->gPrgObj).object.m_attackColliders[3].m_localStart.x = fVar13;
      (gCharaObj->gPrgObj).object.m_attackColliders[4].m_localStart.x = fVar13;
      (gCharaObj->gPrgObj).object.m_attackColliders[5].m_localStart.x = fVar13;
      (gCharaObj->gPrgObj).object.m_attackColliders[6].m_localStart.x = fVar13;
      (gCharaObj->gPrgObj).object.m_attackColliders[7].m_localStart.x = fVar13;
      (gCharaObj->gPrgObj).object.m_damageColliders[0].m_localPosition.x = fVar13;
    }
    else {
      (gCharaObj->gPrgObj).object.m_attackColliders[uVar4 + 1].m_localStart.x = fVar13;
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffd3:
    puVar18 = object->m_localBase;
    pVVar9 = (Vec *)__ct__7CVectorFfff((float)puVar18[3],(float)puVar18[4],(float)puVar18[5],
                                       &CStack_178);
    puVar18 = object->m_localBase;
    SetAttackCol__8CGObjectFiPcfP3Vec
              ((double)(float)puVar18[2],(CGObject *)gCharaObj,*puVar18,
               (flatRuntime2->flatRuntimeBase).m_strBlob +
               (flatRuntime2->flatRuntimeBase).m_strOffs[puVar18[1]],pVVar9);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffd4:
    puVar18 = object->m_localBase;
    dVar22 = (double)(float)puVar18[2];
    dVar24 = (double)(float)puVar18[4];
    dVar25 = (double)(float)puVar18[3];
    dVar21 = (double)(float)puVar18[5];
    dVar23 = (double)sin(dVar22);
    local_dc = (float)(dVar25 * (double)(float)dVar23 +
                      (double)(gCharaObj->gPrgObj).object.m_worldPosition.x);
    local_d8 = (gCharaObj->gPrgObj).object.m_worldPosition.y + (float)object->m_localBase[1];
    dVar23 = (double)cos(dVar22);
    local_d4 = (float)(dVar25 * (double)(float)dVar23 +
                      (double)(gCharaObj->gPrgObj).object.m_worldPosition.z);
    local_e8 = FLOAT_80330bc8;
    local_e4 = (float)-dVar24;
    local_e0 = FLOAT_80330bc8;
    iVar7 = CheckHitCylinderNear__7CMapPcsFP3VecP3VecfUl
                      (dVar21,&MapPcs,&local_dc,&local_e8,*object->m_localBase);
    AddDebugDrawCC__13CFlatRuntime2FP3VecP3Vecfii(dVar21,flatRuntime2,&local_dc,&local_e8,1,0);
    if (iVar7 != 0) {
      *(undefined4 *)object->m_localBase[6] = 0;
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,iVar7);
    *param_5 = 0;
    break;
  case 0xffffffd5:
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffd6:
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffd7:
    DispCharaParts__8CGObjectFi((CGObject *)gCharaObj,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffd8:
    Detach__8CGObjectFv((CGObject *)gCharaObj);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffd9:
    iVar7 = (**(code **)((int)(flatRuntime2->flatRuntimeBase).vtable + 0x3c))
                      (flatRuntime2,*object->m_localBase);
    if (iVar7 != 0) {
      puVar18 = object->m_localBase;
      local_d0.x = (float)puVar18[2];
      local_d0.y = (float)puVar18[3];
      local_d0.z = (float)puVar18[4];
      Attach__8CGObjectFP8CGObjectPcP3Vec
                ((CGObject *)gCharaObj,iVar7,
                 (flatRuntime2->flatRuntimeBase).m_strBlob +
                 (flatRuntime2->flatRuntimeBase).m_strOffs[puVar18[1]],&local_d0);
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffda:
    puVar18 = object->m_localBase;
    local_c4 = *puVar18;
    local_c0 = puVar18[1];
    local_bc = puVar18[2];
    Move__8CGObjectFP3Vecfiiiii
              ((double)(float)puVar18[3],(CGObject *)gCharaObj,&local_c4,puVar18[4],1,1,0,1);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffdb:
    pfVar12 = (float *)object->m_localBase;
    uVar6 = __ct__7CVectorFfff(*pfVar12,pfVar12[1],pfVar12[2],&CStack_16c);
    SetPosBG__8CGObjectFP3Veci((CGObject *)gCharaObj,uVar6,0);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffdc:
    puVar18 = object->m_localBase;
    local_ac = (gCharaObj->gPrgObj).object.m_worldPosition.x;
    dVar24 = (double)(float)puVar18[2];
    dVar22 = (double)(float)puVar18[3];
    dVar21 = (double)(float)puVar18[4];
    local_a8 = (gCharaObj->gPrgObj).object.m_worldPosition.y + (float)puVar18[1];
    local_a4 = (gCharaObj->gPrgObj).object.m_worldPosition.z;
    dVar23 = (double)sin(dVar24);
    local_b4 = FLOAT_80330bc8;
    local_b8 = (float)(dVar22 * (double)(float)dVar23);
    dVar23 = (double)cos(dVar24);
    local_b0 = (float)(dVar22 * (double)(float)dVar23);
    iVar7 = CheckHitCylinderNear__7CMapPcsFP3VecP3VecfUl
                      (dVar21,&MapPcs,&local_ac,&local_b8,*object->m_localBase);
    AddDebugDrawCC__13CFlatRuntime2FP3VecP3Vecfii(dVar21,flatRuntime2,&local_ac,&local_b8,1,0);
    if (iVar7 != 0) {
      *(undefined4 *)object->m_localBase[5] = 0;
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,iVar7);
    *param_5 = 0;
    break;
  case 0xffffffdd:
    puVar18 = object->m_localBase;
    uVar8 = CCClassRot__8CGObjectFiiffff
                      ((double)(float)puVar18[2],(double)(float)puVar18[3],(double)(float)puVar18[4]
                       ,(double)(float)puVar18[5],(CGObject *)gCharaObj,*puVar18,puVar18[1]);
    if (uVar8 != 0) {
      *(int *)object->m_localBase[6] = (int)*(short *)(uVar8 + 0x30);
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,(-uVar8 | uVar8) >> 0x1f);
    *param_5 = 0;
    break;
  case 0xffffffde:
    (gCharaObj->gPrgObj).object.unk_0x184 = (float)*object->m_localBase;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffdf:
    puVar18 = object->m_localBase;
    local_88.x = (gCharaObj->gPrgObj).object.m_worldPosition.x;
    dVar23 = (double)(float)puVar18[5];
    local_88.y = (gCharaObj->gPrgObj).object.m_worldPosition.y + (float)puVar18[1];
    local_88.z = (gCharaObj->gPrgObj).object.m_worldPosition.z;
    local_94.x = (float)puVar18[2];
    local_94.y = (float)puVar18[3];
    local_94.z = (float)puVar18[4];
    PSVECSubtract(&local_94,&local_88,&VStack_a0);
    iVar7 = CheckHitCylinderNear__7CMapPcsFP3VecP3VecfUl
                      (dVar23,&MapPcs,&local_88,&VStack_a0,*object->m_localBase);
    AddDebugDrawCC__13CFlatRuntime2FP3VecP3Vecfii(dVar23,flatRuntime2,&local_88,&VStack_a0,1,0);
    if (iVar7 != 0) {
      *(undefined4 *)object->m_localBase[6] = 0;
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,iVar7);
    *param_5 = 0;
    break;
  case 0xffffffe0:
    puVar18 = object->m_localBase;
    local_7c = puVar18[3];
    local_78 = puVar18[4];
    local_74 = puVar18[5];
    uVar8 = CCClass__8CGObjectFiifP3Vecf
                      ((double)(float)puVar18[2],(double)(float)puVar18[6],gCharaObj,*puVar18,
                       puVar18[1],&local_7c);
    if (uVar8 != 0) {
      *(int *)object->m_localBase[7] = (int)*(short *)(uVar8 + 0x30);
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,(-uVar8 | uVar8) >> 0x1f);
    *param_5 = 0;
    break;
  case 0xffffffe1:
    (gCharaObj->gPrgObj).object.m_attrFlags = *object->m_localBase;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffe3:
    pfVar12 = (float *)object->m_localBase;
    uVar6 = __ct__7CVectorFfff(*pfVar12,pfVar12[1],pfVar12[2],&CStack_160);
    moveVector__8CGObjectFP3Vecfi
              ((double)(float)object->m_localBase[3],(CGObject *)gCharaObj,uVar6,
               object->m_localBase[4]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffe4:
    CancelMove__8CGObjectFi((CGObject *)gCharaObj,1);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffe5:
    bVar2 = *(byte *)((int)&(gCharaObj->gPrgObj).object.m_weaponNodeFlags + 1);
    if (-1 < (int)((uint)bVar2 << 0x1a | (uint)(bVar2 >> 6))) {
      push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
      *param_5 = 0;
    }
    break;
  case 0xffffffe6:
    Turn__8CGObjectFfi((float)*object->m_localBase,(CGObject *)gCharaObj,object->m_localBase[1]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffe7:
    puVar18 = object->m_localBase;
    if (*puVar18 == 1) {
      Reset__9CGQuadObjFff((float)puVar18[1],(float)puVar18[2],(CGQuadObj *)gCharaObj);
    }
    Add__9CGQuadObjFff((float)object->m_localBase[3],(float)object->m_localBase[4],
                       (CGQuadObj *)gCharaObj);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffe8:
    (gCharaObj->gPrgObj).object.m_rotationX = (float)*object->m_localBase;
    (gCharaObj->gPrgObj).object.m_rotationY = (float)object->m_localBase[1];
    (gCharaObj->gPrgObj).object.m_rotationZ = (float)object->m_localBase[2];
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffe9:
    (gCharaObj->gPrgObj).object.m_displayFlags = *object->m_localBase;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffea:
    (gCharaObj->gPrgObj).object.m_objectFlags = *object->m_localBase;
    if (((gCharaObj->gPrgObj).object.m_objectFlags & 0x10) != 0) {
      Game.game.unk_flat3_0xc7d0 = (uint32_t)gCharaObj;
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffeb:
    *(byte *)&(gCharaObj->gPrgObj).object.m_weaponNodeFlags =
         (byte)((int)(char)*object->m_localBase << 4) & 0x10 |
         *(byte *)&(gCharaObj->gPrgObj).object.m_weaponNodeFlags & 0xef;
    (gCharaObj->gPrgObj).object.m_groundHitOffset.z = fVar13;
    (gCharaObj->gPrgObj).object.m_groundHitOffset.y = fVar13;
    (gCharaObj->gPrgObj).object.m_groundHitOffset.x = fVar13;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffec:
    puVar18 = object->m_localBase;
    local_70 = *puVar18;
    local_6c = puVar18[1];
    local_68 = puVar18[2];
    Move__8CGObjectFP3Vecfiiiii
              ((double)(float)puVar18[3],(CGObject *)gCharaObj,&local_70,puVar18[4],0,1,0,1);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffed:
    (gCharaObj->gPrgObj).object.m_bgColMask = *object->m_localBase;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffee:
    CancelAnim__8CGObjectFi((CGObject *)gCharaObj,1);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xffffffef:
    iVar7 = IsAnimFinished__8CGObjectFi((CGObject *)gCharaObj,0);
    if (iVar7 != 0) {
      push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
      *param_5 = 0;
    }
    break;
  case 0xfffffff0:
    PlayAnim__8CGObjectFiiiiiPSc((CGObject *)gCharaObj,*object->m_localBase,0,0,0xffff,0xffff,0);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xfffffff1:
    SetAnimSlot__8CGObjectFii((CGObject *)gCharaObj,*object->m_localBase,object->m_localBase[1]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xfffffff2:
    LoadAnim__8CGObjectFPciiiUl((CGObject *)gCharaObj);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xfffffff3:
    puVar18 = object->m_localBase;
    uVar4 = *puVar18;
    fVar13 = (float)puVar18[1];
    fVar5 = (float)puVar18[4];
    if (uVar4 == 2) {
      (gCharaObj->gPrgObj).object.m_bodyColRadius = fVar13;
    }
    else if ((int)uVar4 < 2) {
      if (uVar4 == 0) {
        (gCharaObj->gPrgObj).object.m_capsuleHalfHeight = fVar13;
      }
      else if (-1 < (int)uVar4) {
        (gCharaObj->gPrgObj).object.m_bodyEllipsoidRadius = fVar13;
        (gCharaObj->gPrgObj).object.m_bodyEllipsoidOffset = fVar5;
      }
    }
    else if (uVar4 == 4) {
      (gCharaObj->gPrgObj).object.m_nearColRadius = fVar13;
    }
    else if ((int)uVar4 < 4) {
      (gCharaObj->gPrgObj).object.m_attackColRadius = fVar13;
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xfffffff6:
    (gCharaObj->gPrgObj).object.m_rotTargetY = (float)*object->m_localBase;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xfffffff7:
    (gCharaObj->gPrgObj).object.m_moveBaseSpeed = (float)*object->m_localBase;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xfffffff8:
    *(byte *)((int)&(gCharaObj->gPrgObj).object.m_weaponNodeFlags + 1) =
         (byte)((int)(char)*object->m_localBase << 7) |
         *(byte *)((int)&(gCharaObj->gPrgObj).object.m_weaponNodeFlags + 1) & 0x7f;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xfffffff9:
    (gCharaObj->gPrgObj).object.m_animStateMisc = (uint8_t)*object->m_localBase;
    uVar1 = (gCharaObj->gPrgObj).object.m_animStateMisc;
    if ((((char)uVar1 < '\0') || ('\x03' < (char)uVar1)) && (1 < (uint)System.m_execParam)) {
      Printf__7CSystemFPce(&System,&DAT_801da7cc);
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xfffffffa:
    pfVar12 = (float *)object->m_localBase;
    uVar6 = __ct__7CVectorFfff(*pfVar12,pfVar12[1],pfVar12[2],&CStack_154);
    SetPosBG__8CGObjectFP3Veci((CGObject *)gCharaObj,uVar6,1);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case 0xfffffffb:
    puVar18 = object->m_localBase;
    LoadModel__8CGObjectFiUlUli((CGObject *)gCharaObj,*puVar18,puVar18[1],puVar18[2],0);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
  }
  return 1;
}


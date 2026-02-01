// Function: pppHitCylinderSendSystem__FP9_pppMngStP3VecP3Vecff
// Entry: 80053d04
// Size: 876 bytes

/* WARNING: Removing unreachable block (ram,0x80054054) */
/* WARNING: Removing unreachable block (ram,0x80053d14) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4
pppHitCylinderSendSystem__FP9_pppMngStP3VecP3Vecff
          (undefined8 param_1,double param_2,_pppMngSt *pppMngSt,undefined4 *param_4,
          undefined4 *param_5)

{
  int iVar1;
  CGObject *gObject;
  int iVar2;
  _pppMngSt *p_Var3;
  uint uVar4;
  int colliderIndex;
  uint uVar5;
  CGObject *pCVar6;
  undefined4 uVar7;
  uint uVar8;
  double dVar9;
  Vec VStack_98;
  Vec VStack_8c;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  
  uVar7 = 0;
  if ((double)FLOAT_8032fddc != param_2) {
    local_50 = FLOAT_8032fde0;
    local_54 = FLOAT_8032fde0;
    local_58 = FLOAT_8032fde0;
    local_44 = FLOAT_8032fde4;
    local_48 = FLOAT_8032fde4;
    local_4c = FLOAT_8032fde4;
    local_80 = *param_4;
    local_7c = param_4[1];
    local_78 = param_4[2];
    local_68 = *param_5;
    local_64 = param_5[1];
    local_60 = param_5[2];
    local_5c = (float)param_2;
    iVar1 = CheckHitCylinder__7CMapMngFP12CMapCylinderP3VecUl
                      (&MapMng,&local_80,param_5,pppMngSt->m_cylinderAttribute);
    if (iVar1 != 0) {
      if (Game.game.m_currentSceneId == 7) {
        pppMngSt->m_endRequested = '\x01';
        if ((-1 < (pppMngSt->m_soundEffectData).m_soundEffectSlot) &&
           (iVar1 = (pppMngSt->m_soundEffectData).m_soundEffectHandle, -1 < iVar1)) {
          FadeOutSe3D__6CSoundFii
                    (&Sound,iVar1,(pppMngSt->m_soundEffectData).m_soundEffectFadeFrames);
          (pppMngSt->m_soundEffectData).m_soundEffectHandle = -1;
        }
      }
      else {
        CalcHitPosition__7CMapObjFP3Vec(MapMng._141944_4_,&VStack_8c);
        iVar1 = (int)&pppMngSt[0x5f2411].m_scale / 0x158 +
                ((int)&pppMngSt[0x5f2411].m_scale >> 0x1f);
        HitParticleBG__5CGameFiiiP3VecP10PPPIFPARAM
                  (&Game.game,iVar1 - (iVar1 >> 0x1f),(int)pppMngSt->m_kind,
                   (int)pppMngSt->m_nodeIndex,&VStack_8c,&pppMngSt->m_hitParams);
      }
      uVar7 = 1;
    }
  }
  if ((Game.game.m_currentSceneId != 7) && ((pppMngSt->m_hitParams).m_hitObjectCount < 0x10)) {
    gObject = (CGObject *)FindGObjFirst__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
    iVar1 = (int)&pppMngSt[0x5f2411].m_scale / 0x158 + ((int)&pppMngSt[0x5f2411].m_scale >> 0x1f);
    for (; gObject != (CGObject *)0x0;
        gObject = (CGObject *)
                  FindGObjNext__13CFlatRuntime2FP8CGObject((CFlatRuntime2 *)&CFlat,gObject)) {
      uVar5 = (uint)(pppMngSt->m_hitParams).m_hitObjectCount;
      uVar4 = 0;
      uVar8 = uVar5;
      for (p_Var3 = pppMngSt;
          (uVar8 != 0 && (p_Var3->m_hitObjectIds[0] != (gObject->base_object).object.m_particleId));
          p_Var3 = (_pppMngSt *)((int)&p_Var3->m_pppResSet + 2)) {
        uVar4 = uVar4 + 1;
        uVar8 = uVar8 - 1;
      }
      if (uVar4 == uVar5) {
        colliderIndex = 0;
        pCVar6 = gObject;
        do {
          if (((gObject->m_bgColMask & 0x80000) != 0) &&
             (((uint)pCVar6->m_damageColliders[1].m_localPosition.x & pppMngSt->m_objHitMask) != 0))
          {
            dVar9 = (double)(float)pCVar6->m_damageColliders[0].m_hitMask;
            if ((((double)FLOAT_8032fddc != dVar9) ||
                ((double)FLOAT_8032fddc != (double)(float)pCVar6->m_damageColliders[0].m_active)) &&
               (iVar2 = CrossCheckSphereVector__5CMathFP3VecPfP3VecP3VecP3Vecf
                                  (param_1,dVar9,
                                   (double)(float)pCVar6->m_damageColliders[0].m_active,&Math,
                                   &VStack_98,0,param_4,param_5,
                                   &pCVar6->m_damageColliders[0].m_worldPosition.y), iVar2 != 0)) {
              uVar7 = 1;
              if (Game.game.m_currentSceneId == 7) {
                _WaitDrawDone__8CGraphicFPci(&Graphic,s_pppPart_cpp_801d81f8,0xadb);
                _pppAllFreePObject__FP9_pppMngSt(pppMngSt);
                _WaitDrawDone__8CGraphicFPci(&Graphic,s_pppPart_cpp_801d81f8,0xadd);
              }
              else {
                HitParticle__8CGObjectFiiiiP3VecP10PPPIFPARAM
                          (gObject,iVar1 - (iVar1 >> 0x1f),(int)pppMngSt->m_kind,
                           (int)pppMngSt->m_nodeIndex,colliderIndex,&VStack_98,
                           &pppMngSt->m_hitParams);
                uVar8 = (uint)(pppMngSt->m_hitParams).m_hitObjectCount;
                if (uVar5 != uVar8) {
                  iVar2 = 0;
                  uVar4 = uVar8;
                  for (p_Var3 = pppMngSt;
                      (uVar4 != 0 &&
                      (p_Var3->m_hitObjectIds[0] != (gObject->base_object).object.m_particleId));
                      p_Var3 = (_pppMngSt *)((int)&p_Var3->m_pppResSet + 2)) {
                    iVar2 = iVar2 + 1;
                    uVar4 = uVar4 - 1;
                  }
                  uVar5 = uVar8;
                  if (iVar2 < (int)uVar8) break;
                }
              }
            }
          }
          colliderIndex = colliderIndex + 1;
          pCVar6 = (CGObject *)&(pCVar6->base_object).object.m_waitCounter;
        } while (colliderIndex < 8);
      }
    }
  }
  return uVar7;
}


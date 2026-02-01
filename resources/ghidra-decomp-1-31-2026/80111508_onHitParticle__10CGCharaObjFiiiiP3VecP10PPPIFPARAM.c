// Function: onHitParticle__10CGCharaObjFiiiiP3VecP10PPPIFPARAM
// Entry: 80111508
// Size: 368 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onHitParticle__10CGCharaObjFiiiiP3VecP10PPPIFPARAM
               (CGCharaObj *gCharaObj,int effectIndex,int kind,int nodeIndex,int colliderIndex,
               Vec *vec,PPPIFPARAM *pppIFParam)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  uVar1 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0xc))();
  if (((((uVar1 & 0x6d) != 0x6d) || (Game.game.m_gameWork.m_menuStageMode == '\0')) ||
      (0xe < Game.game.m_gameWork.m_bossArtifactStageIndex)) ||
     ((uVar1 = (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0xc))
                         (gCharaObj), (uVar1 & 0x6d) != 0x6d ||
      ((gCharaObj->gPrgObj).object.m_scriptHandle[0xed] == (void *)0x0)))) {
    iVar3 = pppIFParam->m_particleIndex;
    if (pppIFParam->m_classId == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = (**(code **)(CFlat._0_4_ + 0x3c))();
    }
    uVar1 = (**(code **)(*(int *)(iVar2 + 0x48) + 0xc))(iVar2);
    if ((uVar1 & 0xd) == 0xd) {
      (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0x80))
                (gCharaObj,iVar2,iVar3,0xffffffff,colliderIndex,vec);
    }
    IgnoreParticle__13CFlatRuntime2FiPQ212CFlatRuntime7CObject
              ((CFlatRuntime2 *)&CFlat,(short)effectIndex,(CObject *)gCharaObj);
    if ((*(ushort *)(Game.game.unkCFlatData0[2] + iVar3 * 0x48 + 0xc) & 0x100) != 0) {
      pppEndPart__8CPartMngFi(&PartMng,effectIndex);
    }
  }
  return;
}


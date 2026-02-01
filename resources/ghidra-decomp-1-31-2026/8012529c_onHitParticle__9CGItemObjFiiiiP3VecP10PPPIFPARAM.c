// Function: onHitParticle__9CGItemObjFiiiiP3VecP10PPPIFPARAM
// Entry: 8012529c
// Size: 556 bytes

/* WARNING: Removing unreachable block (ram,0x80125330) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onHitParticle__9CGItemObjFiiiiP3VecP10PPPIFPARAM
               (CGItemObj *gItemObj,int effectIndex,int kind,int nodeIndex,int colliderIndex,
               Vec *vec,PPPIFPARAM *pppIFParam)

{
  uint uVar1;
  int iVar2;
  float fVar3;
  uint unaff_r28;
  undefined4 unaff_r31;
  
  fVar3 = (gItemObj->prgObj).object.m_worldParamA;
  uVar1 = (uint)*(ushort *)(Game.game.unkCFlatData0[2] + pppIFParam->m_particleIndex * 0x48 + 8);
  if ((fVar3 == 1.82169e-44) || (fVar3 == 1.96182e-44)) {
    if ((((uVar1 == 0) || (uVar1 == 4)) && (fVar3 == 1.82169e-44)) ||
       ((uVar1 == 1 && (fVar3 == 1.96182e-44)))) {
      if (uVar1 == 1) {
        unaff_r28 = 0x20;
        unaff_r31 = 0x491;
      }
      else if (uVar1 == 0) {
        unaff_r28 = 0x1f;
        unaff_r31 = 0x492;
      }
      else if (uVar1 == 4) {
        unaff_r28 = 0x2f;
        unaff_r31 = 0x493;
      }
      EndParticleSlot__13CFlatRuntime2Fii
                ((CFlatRuntime2 *)&CFlat,*(undefined4 *)&gItemObj->field_0x55c);
      ResetParticleWork__13CFlatRuntime2Fii
                ((CFlatRuntime2 *)&CFlat,unaff_r28 | 0x100,*(undefined4 *)&gItemObj->field_0x55c);
      SetParticleWorkPos__13CFlatRuntime2FR3Vecf
                ((double)FLOAT_80331b20,(CFlatRuntime2 *)&CFlat,
                 &(gItemObj->prgObj).object.m_worldPosition);
      SetParticleWorkCol__13CFlatRuntime2Fiif((double)FLOAT_80331b18,(CFlatRuntime2 *)&CFlat,9,0);
      SetParticleWorkParam__13CFlatRuntime2FiPQ212CFlatRuntime7CObject
                ((CFlatRuntime2 *)&CFlat,unaff_r31,gItemObj);
      PutParticleWork__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
      (gItemObj->prgObj).object.m_bgColMask = (gItemObj->prgObj).object.m_bgColMask & 0xfff7ffff;
      addSubStat__8CGPrgObjFv(&gItemObj->prgObj);
    }
  }
  else {
    if (((fVar3 != 2.84464e-43) || ((gItemObj->prgObj).m_lastStateId != 0x24)) &&
       ((gItemObj->prgObj).m_lastStateId != 0x25)) {
      return;
    }
    if ((uVar1 - 0x66 < 2) || (uVar1 == 0x65)) {
      if (pppIFParam->m_classId == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = (**(code **)(CFlat._0_4_ + 0x3c))();
      }
      uVar1 = (**(code **)(*(int *)(iVar2 + 0x48) + 0xc))(iVar2);
      if (((uVar1 & 0x6d) == 0x6d) && (*(int *)&gItemObj->field_0x550 == iVar2)) {
        changeStat__8CGPrgObjFiii(&gItemObj->prgObj,0x26,0,0);
      }
    }
  }
  IgnoreParticle__13CFlatRuntime2FiPQ212CFlatRuntime7CObject
            ((CFlatRuntime2 *)&CFlat,(short)effectIndex,(CObject *)gItemObj);
  return;
}


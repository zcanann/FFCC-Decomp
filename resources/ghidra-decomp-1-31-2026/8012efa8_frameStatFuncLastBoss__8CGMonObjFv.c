// Function: frameStatFuncLastBoss__8CGMonObjFv
// Entry: 8012efa8
// Size: 1088 bytes

/* WARNING: Removing unreachable block (ram,0x8012f3c4) */
/* WARNING: Removing unreachable block (ram,0x8012efb8) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void frameStatFuncLastBoss__8CGMonObjFv(CGMonObj *gMonObj)

{
  bool bVar1;
  int iVar2;
  CRef *pCVar3;
  CGPrgObj *gPrgObj;
  int iVar4;
  int iVar5;
  CModel *pCVar6;
  double dVar7;
  double dVar8;
  Mtx MStack_58;
  
  pCVar6 = ((gMonObj->gObject).m_charaModelHandle)->m_model;
  PSMTXCopy((Mtx *)(SoundBuffer._1264_4_ + 0x6c),&MStack_58);
  iVar5 = -0x7fcffeb4;
  MStack_58.value[0][3] = MStack_58.value[0][3] + (pCVar6->m_drawMtx).value[0][3];
  MStack_58.value[1][3] = MStack_58.value[1][3] + (pCVar6->m_drawMtx).value[1][3];
  MStack_58.value[2][3] = MStack_58.value[2][3] + (pCVar6->m_drawMtx).value[2][3];
  iVar2 = *(int *)&gMonObj->field_0x520;
  m_aiWork__8CGMonObj._4_4_ = MStack_58.value[0][3];
  m_aiWork__8CGMonObj._8_4_ = MStack_58.value[1][3];
  m_boss__8CGMonObj._0_4_ = MStack_58.value[2][3];
  if (iVar2 == 0x65) {
    if (*(int *)&gMonObj->field_0x528 == 0) {
      (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask & 0xfff7ffff;
      reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0x19,0,0);
      pCVar3 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
      if (pCVar3 == (CRef *)0x0) {
        iVar2 = -1;
      }
      else {
        iVar2 = pCVar3[2].refCount;
      }
      putParticle__8CGPrgObjFiiP8CGObjectfi
                ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,iVar2 << 8 | 0x11,0,&gMonObj->gObject,0)
      ;
      pCVar3 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
      if (pCVar3 == (CRef *)0x0) {
        iVar2 = -1;
      }
      else {
        iVar2 = pCVar3[2].refCount;
      }
      putParticle__8CGPrgObjFiiP8CGObjectfi
                ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,iVar2 << 8 | 0x12,0,&gMonObj->gObject,0)
      ;
      playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0x12913,0x32,0x96,0,0);
    }
    else if (*(int *)&gMonObj->field_0x528 == 0x29) {
      (gMonObj->gObject).m_bodyEllipsoidRadius = FLOAT_80331d44;
    }
    else {
      iVar2 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
      if (iVar2 != 0) {
        (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask | 0x80000;
        changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
        SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0x13,0);
        SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0x15,1);
        SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0x17,4);
        gMonObj->_bossBranchRelated = 0;
      }
    }
  }
  else if (iVar2 < 0x65) {
    if (99 < iVar2) {
      if (*(int *)&gMonObj->field_0x528 == 0) {
        damageDelete__10CGCharaObjFv(gMonObj);
        (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask & 0xfff7ffff;
        reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0x18,0,0);
        pCVar3 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
        if (pCVar3 == (CRef *)0x0) {
          iVar2 = -1;
        }
        else {
          iVar2 = pCVar3[2].refCount;
        }
        putParticle__8CGPrgObjFiiP8CGObjectfi
                  ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,iVar2 << 8 | 0x10,0,&gMonObj->gObject,
                   0);
        playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0x12912,0x32,0x96,0,0);
      }
      else if (*(int *)&gMonObj->field_0x528 == 0x7d) {
        (gMonObj->gObject).m_bodyEllipsoidRadius = FLOAT_80331d40;
      }
      else {
        iVar2 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)gMonObj);
        if (iVar2 != 0) {
          (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask | 0x80000;
          SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0x12,0);
          SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0x14,1);
          SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0x16,4);
          changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0,0,0);
          gMonObj->_bossBranchRelated = 2;
        }
      }
    }
  }
  else if (iVar2 < 0x67) {
    iVar2 = *(int *)&gMonObj->field_0x528;
    if (iVar2 == 0) {
      pCVar3 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
      if (pCVar3 == (CRef *)0x0) {
        iVar2 = -1;
      }
      else {
        iVar2 = pCVar3[2].refCount;
      }
      putParticle__8CGPrgObjFiiP8CGObjectfi
                ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,iVar2 << 8 | 5,
                 *(int *)&gMonObj->field_0x58c,&gMonObj->gObject,0x12902);
    }
    else if (iVar2 == 0x4b) {
      iVar2 = 0;
      dVar8 = DOUBLE_80331d48;
      do {
        iVar4 = *(int *)(iVar5 + 8);
        if (((iVar4 != 0) && (*(int *)(iVar4 + 0x520) == 0x24)) &&
           (dVar7 = (double)getTargetRot__8CGPrgObjFP8CGPrgObj((CGPrgObj *)gMonObj,iVar4),
           ABS(dVar7) < dVar8)) {
          changeStat__8CGPrgObjFiii(*(CGPrgObj **)(iVar5 + 8),0x25,0,0);
        }
        iVar2 = iVar2 + 1;
        iVar5 = iVar5 + 4;
      } while (iVar2 < 4);
    }
    else if (iVar2 == 200) {
      iVar2 = 0;
      do {
        gPrgObj = *(CGPrgObj **)(iVar5 + 8);
        if (((gPrgObj != (CGPrgObj *)0x0) && (bVar1 = gPrgObj->m_lastStateId == 0x25, bVar1)) &&
           (bVar1)) {
          changeStat__8CGPrgObjFiii(gPrgObj,0x24,0,0);
        }
        iVar2 = iVar2 + 1;
        iVar5 = iVar5 + 4;
      } while (iVar2 < 4);
      endPSlotBit__10CGCharaObjFi(gMonObj,0x400);
    }
    _statAttack__10CGCharaObjFv((CGCharaObj *)gMonObj);
  }
  return;
}


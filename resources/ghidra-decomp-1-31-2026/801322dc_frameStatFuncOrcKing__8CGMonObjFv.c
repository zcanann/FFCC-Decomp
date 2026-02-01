// Function: frameStatFuncOrcKing__8CGMonObjFv
// Entry: 801322dc
// Size: 604 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void frameStatFuncOrcKing__8CGMonObjFv(CGMonObj *gMonObj)

{
  int iVar1;
  CRef *pCVar2;
  CGMonObj *monObj;
  
  if (*(int *)&gMonObj->field_0x520 == 100) {
    iVar1 = gMonObj->_bossBranchRelated;
    if (iVar1 == 0) {
      pCVar2 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
      if (pCVar2 == (CRef *)0x0) {
        iVar1 = -1;
      }
      else {
        iVar1 = pCVar2[2].refCount;
      }
      putParticle__8CGPrgObjFiiP8CGObjectfi
                ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,iVar1 << 8 | 0x18,
                 *(int *)&gMonObj->field_0x58c,&gMonObj->gObject,0x8cc0);
      reqAnim__8CGPrgObjFiii((CGPrgObj *)gMonObj,0xf,0,0);
      SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0x10,0);
      SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0x15,4);
    }
    else if (iVar1 == 0x96) {
      pCVar2 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
      if (pCVar2 == (CRef *)0x0) {
        iVar1 = -1;
      }
      else {
        iVar1 = pCVar2[2].refCount;
      }
      putParticle__8CGPrgObjFiiP8CGObjectfi
                ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,iVar1 << 8 | 0x19,
                 *(int *)&gMonObj->field_0x590,&gMonObj->gObject,0x8cc1);
    }
    else if (iVar1 == 300) {
      pCVar2 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
      if (pCVar2 == (CRef *)0x0) {
        iVar1 = -1;
      }
      else {
        iVar1 = pCVar2[2].refCount;
      }
      putParticle__8CGPrgObjFiiP8CGObjectfi
                ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,iVar1 << 8 | 0x1a,
                 *(int *)&gMonObj->field_0x590,&gMonObj->gObject,0x8cc2);
    }
    else if (iVar1 == 0x1c2) {
      pCVar2 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
      if (pCVar2 == (CRef *)0x0) {
        iVar1 = -1;
      }
      else {
        iVar1 = pCVar2[2].refCount;
      }
      putParticle__8CGPrgObjFiiP8CGObjectfi
                ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,iVar1 << 8 | 0x1b,
                 *(int *)&gMonObj->field_0x590,&gMonObj->gObject,0x8cc3);
    }
    else if (iVar1 == 600) {
      endPSlotBit__10CGCharaObjFi(gMonObj,0xc00);
      (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask & 0xfff7ffff;
      changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,0xfffffff7,0,0);
      SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0,0);
      for (monObj = (CGMonObj *)FindGMonObjFirst__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
          monObj != (CGMonObj *)0x0;
          monObj = (CGMonObj *)
                   FindGMonObjNext__13CFlatRuntime2FP8CGMonObj((CFlatRuntime2 *)&CFlat,monObj)) {
        if (monObj != gMonObj) {
          addHp__10CGCharaObjFiP8CGPrgObj
                    ((CGCharaObj *)monObj,
                     -(uint)*(ushort *)((int)(monObj->gObject).m_scriptHandle + 0x1a),
                     (CGPrgObj *)0x0);
        }
      }
      SoundBuffer._1260_4_ = 1;
    }
    gMonObj->_bossBranchRelated = gMonObj->_bossBranchRelated + 1;
  }
  return;
}


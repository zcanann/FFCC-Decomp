// Function: damagedFuncDuct__8CGMonObjFv
// Entry: 8012f7ac
// Size: 196 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void damagedFuncDuct__8CGMonObjFv(CGMonObj *gMonObj)

{
  int iVar1;
  void *pvVar2;
  CRef *pCVar3;
  CModel *model;
  
  pCVar3 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
  pvVar2 = (gMonObj->gObject).m_scriptHandle[4];
  if (pCVar3 == (CRef *)0x0) {
    iVar1 = -1;
  }
  else {
    iVar1 = pCVar3[2].refCount;
  }
  putParticle__8CGPrgObjFiiP8CGObjectfi
            ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,iVar1 << 8 | 2,0,&gMonObj->gObject,0);
  if (*(short *)((gMonObj->gObject).m_scriptHandle + 7) == 0) {
    model = *(CModel **)(*(int *)(m_boss__8CGMonObj._72_4_ + 0xf8) + 0x168);
    iVar1 = GetDispIndex__Q26CChara6CModelFPQ26CChara5CNode
                      (model,*(CNode **)(SoundBuffer + ((int)pvVar2 + -0x8e) * 4 + 0x4f4));
    model->m_meshVisibleMask = model->m_meshVisibleMask & ~(1 << iVar1);
  }
  return;
}


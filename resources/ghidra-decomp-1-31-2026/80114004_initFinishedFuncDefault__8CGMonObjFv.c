// Function: initFinishedFuncDefault__8CGMonObjFv
// Entry: 80114004
// Size: 516 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void initFinishedFuncDefault__8CGMonObjFv(CGMonObj *gMonObj)

{
  short sVar1;
  CCharaPcsCHandle *pCVar2;
  CModel *model;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  (gMonObj->gObject).m_hitNormal.x =
       FLOAT_803319cc *
       (float)((double)CONCAT44(0x43300000,
                                (uint)*(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0x1b0)
                               ) - DOUBLE_803319e0);
  pCVar2 = (gMonObj->gObject).m_charaModelHandle;
  if (((pCVar2 != (CCharaPcsCHandle *)0x0) && (model = pCVar2->m_model, model != (CModel *)0x0)) &&
     (iVar3 = SearchNode__Q26CChara6CModelFPc(model,&DAT_803319f0), -1 < iVar3)) {
    *(CNode **)&gMonObj->field_0x6e0 =
         ((gMonObj->gObject).m_charaModelHandle)->m_model->m_nodes + iVar3;
  }
  sVar1 = *(short *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0x1a0);
  if (sVar1 != -1) {
    AddAnimPoint__8CGObjectFiii(&gMonObj->gObject,1,sVar1,0xb);
  }
  sVar1 = *(short *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0x1a2);
  if (sVar1 != -1) {
    AddAnimPoint__8CGObjectFiii(&gMonObj->gObject,1,sVar1,10);
  }
  *(undefined4 *)&gMonObj->field_0x6e8 = 0xffffffff;
  iVar5 = 0;
  iVar3 = 0;
  iVar6 = 2;
  do {
    uVar4 = (uint)*(ushort *)((int)(gMonObj->gObject).m_scriptHandle + iVar3 + 0xd0);
    if ((uVar4 != 0xffff) && (*(short *)(Game.game.unkCFlatData0[2] + uVar4 * 0x48 + 0xe) == 4)) {
      *(int *)&gMonObj->field_0x6e8 = iVar5;
      break;
    }
    uVar4 = (uint)*(ushort *)((int)(gMonObj->gObject).m_scriptHandle + iVar3 + 0xd2);
    if ((uVar4 != 0xffff) && (*(short *)(Game.game.unkCFlatData0[2] + uVar4 * 0x48 + 0xe) == 4)) {
      *(int *)&gMonObj->field_0x6e8 = iVar5 + 1;
      break;
    }
    uVar4 = (uint)*(ushort *)((int)(gMonObj->gObject).m_scriptHandle + iVar3 + 0xd4);
    if ((uVar4 != 0xffff) && (*(short *)(Game.game.unkCFlatData0[2] + uVar4 * 0x48 + 0xe) == 4)) {
      *(int *)&gMonObj->field_0x6e8 = iVar5 + 2;
      break;
    }
    uVar4 = (uint)*(ushort *)((int)(gMonObj->gObject).m_scriptHandle + iVar3 + 0xd6);
    if ((uVar4 != 0xffff) && (*(short *)(Game.game.unkCFlatData0[2] + uVar4 * 0x48 + 0xe) == 4)) {
      *(int *)&gMonObj->field_0x6e8 = iVar5 + 3;
      break;
    }
    iVar3 = iVar3 + 8;
    iVar5 = iVar5 + 4;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  setRepop__8CGMonObjFi(gMonObj,1);
  return;
}


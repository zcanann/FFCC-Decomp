// Function: onHit__10CGCharaObjFiP8CGObjectiP3Vec
// Entry: 80111678
// Size: 480 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4
onHit__10CGCharaObjFiP8CGObjectiP3Vec
          (CGCharaObj *gCharaObj,undefined4 param_2,CGObject *gObject,undefined4 param_4,
          undefined4 param_5)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  CGCharaObj *pCVar4;
  int iVar5;
  
  uVar1 = (**(code **)((int)(gObject->base_object).object.m_vtable + 0xc))(gObject);
  if (((((uVar1 & 0x6d) == 0x6d) && (Game.game.m_gameWork.m_menuStageMode != '\0')) &&
      (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf)) &&
     ((uVar1 = (**(code **)((int)(gObject->base_object).object.m_vtable + 0xc))(gObject),
      (uVar1 & 0x6d) == 0x6d && (gObject->m_scriptHandle[0xed] != (void *)0x0)))) {
    return 0;
  }
  iVar2 = 0;
  iVar5 = 4;
  pCVar4 = gCharaObj;
  do {
    if (-1 < (char)pCVar4->field_0x640) {
      iVar5 = iVar2 * 8;
      (&gCharaObj->field_0x640)[iVar5] = (&gCharaObj->field_0x640)[iVar5] & 0x7f | 0x80;
      *(CGObject **)(&gCharaObj->field_0x644 + iVar5) = gObject;
      uVar1 = (uint)*(ushort *)
                     (Game.game.unkCFlatData0[2] + *(int *)&gCharaObj->field_0x560 * 0x48 + 0xe);
      *(ushort *)(&gCharaObj->field_0x642 + iVar5) =
           (short)~((ushort)(uVar1 - 3 >> 0x10) | (ushort)(3 - uVar1 >> 0x10)) >> 0xf & 0x1e;
      break;
    }
    if (*(CGObject **)&pCVar4->field_0x644 == gObject) {
      return 2;
    }
    pCVar4 = (CGCharaObj *)&(pCVar4->gPrgObj).object.base_object.object.m_stackPointer;
    iVar2 = iVar2 + 1;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  if (iVar2 == 4) {
    uVar3 = 2;
  }
  else {
    if ((gObject->m_objectFlags & 0x100) != 0) {
      (**(code **)((int)(gCharaObj->gPrgObj).object.base_object.object.m_vtable + 0x4c))
                (gCharaObj,3,0,0);
    }
    uVar1 = (**(code **)((int)(gObject->base_object).object.m_vtable + 0xc))(gObject);
    if ((uVar1 & 0x2d) == 0x2d) {
      (**(code **)((int)(gObject->base_object).object.m_vtable + 0x80))
                (gObject,gCharaObj,*(undefined4 *)&gCharaObj->field_0x560,param_2,param_4,param_5);
    }
    uVar3 = 1;
  }
  return uVar3;
}


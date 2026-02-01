// Function: logicFuncGiantCrab__8CGMonObjFv
// Entry: 80132e80
// Size: 232 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void logicFuncGiantCrab__8CGMonObjFv(CGMonObj *gMonObj)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = -1;
  if ((SoundBuffer._1260_4_ != 0) &&
     ((((SoundBuffer._1260_4_ = 0, gMonObj->_bossBranchRelated == 0 &&
        (iVar1 = Rand__5CMathFUl(&Math,10), iVar1 == 0)) ||
       ((gMonObj->_bossBranchRelated == 1 && (uVar2 = Rand__5CMathFUl(&Math,10), uVar2 < 2)))) ||
      ((gMonObj->_bossBranchRelated == 2 && (uVar2 = Rand__5CMathFUl(&Math,10), uVar2 < 3)))))) {
    iVar3 = 100;
  }
  if (iVar3 == -1) {
    logicFuncDefault__8CGMonObjFv(gMonObj);
  }
  else {
    changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,iVar3,0,0);
  }
  return;
}


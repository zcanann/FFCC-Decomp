// Function: aiAddDuct__8CGMonObjFRi
// Entry: 8012f8bc
// Size: 200 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void aiAddDuct__8CGMonObjFRi(CGMonObj *gMonObj,int param_2)

{
  int iVar1;
  
  iVar1 = Rand__5CMathFUl(&Math,300);
  if (iVar1 == 0) {
    aiTarget__8CGMonObjFv(gMonObj);
    _aiSeq__8CGMonObjFiiiiii(gMonObj,0xfffffff2,*(undefined4 *)param_2,0,1,100,0xffffffff);
    _aiSeq__8CGMonObjFiiiiii(gMonObj,0xfffffff3,*(undefined4 *)param_2,1,0,100,0xffffffff);
    iVar1 = Rand__5CMathFUl(&Math,3);
    playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,iVar1 + 0x11d40,0x32,0x96,0,0);
  }
  return;
}


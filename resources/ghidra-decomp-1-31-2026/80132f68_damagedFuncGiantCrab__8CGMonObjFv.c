// Function: damagedFuncGiantCrab__8CGMonObjFv
// Entry: 80132f68
// Size: 404 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void damagedFuncGiantCrab__8CGMonObjFv(CGMonObj *gMonObj)

{
  int iVar1;
  CRef *pCVar2;
  void **ppvVar3;
  
  SoundBuffer._1260_4_ = 1;
  iVar1 = gMonObj->_bossBranchRelated;
  if (iVar1 == 1) {
    ppvVar3 = (gMonObj->gObject).m_scriptHandle;
    if (*(ushort *)((int)ppvVar3 + 0x1a) / 3 <= (uint)*(ushort *)(ppvVar3 + 7)) {
      SoundBuffer._1260_4_ = 1;
      return;
    }
    DispCharaParts__8CGObjectFi(&gMonObj->gObject,1);
    pCVar2 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
    if (pCVar2 == (CRef *)0x0) {
      iVar1 = -1;
    }
    else {
      iVar1 = pCVar2[2].refCount;
    }
    putParticle__8CGPrgObjFiiP8CGObjectfi
              ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,iVar1 << 8 | 0xd,0,&gMonObj->gObject,0);
    playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0x4e37,0x32,500,0,0);
  }
  else {
    if (0 < iVar1) {
      SoundBuffer._1260_4_ = 1;
      return;
    }
    if (iVar1 < 0) {
      SoundBuffer._1260_4_ = 1;
      return;
    }
    ppvVar3 = (gMonObj->gObject).m_scriptHandle;
    if (((uint)*(ushort *)((int)ppvVar3 + 0x1a) << 1) / 3 <= (uint)*(ushort *)(ppvVar3 + 7)) {
      SoundBuffer._1260_4_ = 1;
      return;
    }
    DispCharaParts__8CGObjectFi(&gMonObj->gObject,3);
    pCVar2 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
    if (pCVar2 == (CRef *)0x0) {
      iVar1 = -1;
    }
    else {
      iVar1 = pCVar2[2].refCount;
    }
    putParticle__8CGPrgObjFiiP8CGObjectfi
              ((double)FLOAT_80331d18,(CGPrgObj *)gMonObj,iVar1 << 8 | 0xc,0,&gMonObj->gObject,0);
    playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0x4e36,0x32,500,0,0);
  }
  changeStat__8CGPrgObjFiii((CGPrgObj *)gMonObj,4,0,0);
  gMonObj->_bossBranchRelated = gMonObj->_bossBranchRelated + 1;
  *(undefined4 *)&gMonObj->field_0x6c8 = 0;
  return;
}


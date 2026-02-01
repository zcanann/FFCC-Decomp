// Function: onAnimPoint__8CGMonObjFii
// Entry: 80117c30
// Size: 300 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onAnimPoint__8CGMonObjFii(CGMonObj *gMonObj,undefined4 param_2,int param_3)

{
  int iVar1;
  CRef *pCVar2;
  void **ppvVar3;
  uint uVar4;
  uint uVar5;
  
  uVar4 = 0xffff;
  uVar5 = uVar4;
  if ((param_3 < 0xc) && (uVar5 = 0xffff, 9 < param_3)) {
    ppvVar3 = (gMonObj->gObject).m_scriptHandle;
    uVar4 = (uint)*(ushort *)((int)ppvVar3[9] + 0x1a4);
    if ((uVar4 != 0xffff) && (param_3 == 10)) {
      uVar4 = uVar4 + 1;
    }
    uVar5 = (uint)*(ushort *)((int)ppvVar3[9] + 0x1a6);
  }
  if (uVar4 != 0xffff) {
    pCVar2 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
    if (pCVar2 == (CRef *)0x0) {
      iVar1 = -1;
    }
    else {
      iVar1 = pCVar2[2].refCount;
    }
    putParticle__8CGPrgObjFiiP8CGObjectfi
              ((double)FLOAT_803319c0,(CGPrgObj *)gMonObj,uVar4 | iVar1 << 8,0,&gMonObj->gObject,0);
  }
  if (uVar5 != 0xffff) {
    if (uVar5 != 0xffff) {
      iVar1 = (uVar5 & 0xff) + ((int)uVar5 >> 8) * 1000;
    }
    else {
      iVar1 = 0;
    }
    playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,iVar1,0x32,0x96,0,0);
  }
  onAnimPoint__10CGCharaObjFii(gMonObj,param_2,param_3);
  return;
}


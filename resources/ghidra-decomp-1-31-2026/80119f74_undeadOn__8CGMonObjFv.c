// Function: undeadOn__8CGMonObjFv
// Entry: 80119f74
// Size: 384 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void undeadOn__8CGMonObjFv(CGMonObj *gMonObj)

{
  ushort uVar1;
  int iVar2;
  CRef *pCVar3;
  void **ppvVar4;
  int iVar5;
  int iVar6;
  void *pvVar7;
  
  *(float *)&gMonObj->field_0x694 = FLOAT_803319e8;
  ppvVar4 = (gMonObj->gObject).m_scriptHandle;
  pvVar7 = ppvVar4[4];
  iVar5 = (int)((uint)*(byte *)&(gMonObj->gObject).m_weaponNodeFlags << 0x18) >> 0x1f;
  if (*(short *)((int)ppvVar4[9] + 0xfc) != 0xb) {
    iVar5 = 1;
  }
  endPSlotBit__10CGCharaObjFi(gMonObj,0x1000);
  if (iVar5 == 0) {
    uVar1 = *(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0x1ae);
  }
  else {
    uVar1 = *(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0x1ac);
  }
  iVar6 = 0x3c;
  if (iVar5 != 0) {
    iVar6 = 0x46;
  }
  for (iVar5 = 0; iVar5 < (int)(uint)uVar1; iVar5 = iVar5 + 1) {
    pCVar3 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
    if (pCVar3 == (CRef *)0x0) {
      iVar2 = -1;
    }
    else {
      iVar2 = pCVar3[2].refCount;
    }
    putParticleBindTrace__8CGPrgObjFiiP8CGObjectfi
              ((double)FLOAT_803319c0,(CGPrgObj *)gMonObj,iVar6 + iVar5 | iVar2 << 8,
               *(int *)&gMonObj->field_0x594,&gMonObj->gObject,0);
  }
  if (*(short *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0xfc) == 0xb) {
    SetTexAnim__8CGObjectFPc(&gMonObj->gObject,&DAT_803319ec);
  }
  if ((int)((uint)*(byte *)&(gMonObj->gObject).m_weaponNodeFlags << 0x18) < 0) {
    if (pvVar7 == (void *)0x83) {
      playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0x987a,0x32,0x96,0,0);
    }
    else if (pvVar7 == (void *)0x7f) {
      playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)gMonObj,0x11585,0x32,0x96,0,0);
    }
  }
  gMonObj->field_0x6ba = 0;
  return;
}


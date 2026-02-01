// Function: undeadOff__8CGMonObjFv
// Entry: 8011a0f4
// Size: 296 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void undeadOff__8CGMonObjFv(CGMonObj *gMonObj)

{
  short sVar1;
  uint uVar2;
  CRef *pCVar3;
  int iVar4;
  int iVar5;
  
  *(float *)&gMonObj->field_0x694 = FLOAT_803319c0;
  iVar5 = (int)((uint)*(byte *)&(gMonObj->gObject).m_weaponNodeFlags << 0x18) >> 0x1f;
  uVar2 = countLeadingZeros(0xb - (uint)*(ushort *)
                                         ((int)(gMonObj->gObject).m_scriptHandle[9] + 0xfc));
  uVar2 = uVar2 >> 5 & 0xff;
  if (uVar2 == 0) {
    iVar5 = 1;
  }
  endPSlotBit__10CGCharaObjFi(gMonObj,0x1000);
  if (iVar5 == 0) {
    sVar1 = *(short *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0x1ae);
  }
  else {
    sVar1 = *(short *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0x1ac);
  }
  iVar4 = 0x3c;
  if (iVar5 != 0) {
    iVar4 = 0x46;
  }
  if ((uVar2 != 0) && (sVar1 != 0)) {
    pCVar3 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
    if (pCVar3 == (CRef *)0x0) {
      iVar5 = -1;
    }
    else {
      iVar5 = pCVar3[2].refCount;
    }
    putParticleBindTrace__8CGPrgObjFiiP8CGObjectfi
              ((double)FLOAT_803319c0,(CGPrgObj *)gMonObj,iVar4 + 9U | iVar5 << 8,
               *(int *)&gMonObj->field_0x594,&gMonObj->gObject,0);
  }
  if (*(short *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0xfc) == 0xb) {
    SetTexAnim__8CGObjectFPc(&gMonObj->gObject,&DAT_80331a4c);
  }
  gMonObj->field_0x6ba = 1;
  return;
}


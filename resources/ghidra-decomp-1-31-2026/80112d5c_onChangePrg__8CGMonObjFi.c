// Function: onChangePrg__8CGMonObjFi
// Entry: 80112d5c
// Size: 376 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onChangePrg__8CGMonObjFi(CGMonObj *gMonObj,int param_2)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  CRef *pCVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  
  if (((int)((uint)*(byte *)&(gMonObj->gObject).m_weaponNodeFlags << 0x18) >> 0x1f != param_2) &&
     (*(short *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0xfc) == 0xb)) {
    uVar2 = countLeadingZeros(0);
    uVar6 = uVar2 >> 5 & 0xff;
    uVar2 = countLeadingZeros((uint)(byte)gMonObj->field_0x6ba);
    iVar5 = param_2;
    if (uVar6 == 0) {
      iVar5 = 1;
    }
    endPSlotBit__10CGCharaObjFi(gMonObj,0x1000);
    if (iVar5 == 0) {
      uVar1 = *(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0x1ae);
    }
    else {
      uVar1 = *(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0x1ac);
    }
    iVar7 = 0x3c;
    if (iVar5 != 0) {
      iVar7 = 0x46;
    }
    if ((uVar2 >> 5 & 0xff) == 0) {
      if ((uVar6 != 0) && (uVar1 != 0)) {
        pCVar4 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
        if (pCVar4 == (CRef *)0x0) {
          iVar5 = -1;
        }
        else {
          iVar5 = pCVar4[2].refCount;
        }
        putParticleBindTrace__8CGPrgObjFiiP8CGObjectfi
                  ((double)FLOAT_803319c0,(CGPrgObj *)gMonObj,iVar7 + 9U | iVar5 << 8,
                   *(int *)&gMonObj->field_0x594,&gMonObj->gObject,0);
      }
    }
    else {
      for (iVar5 = 0; iVar5 < (int)(uint)uVar1; iVar5 = iVar5 + 1) {
        pCVar4 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
        if (pCVar4 == (CRef *)0x0) {
          iVar3 = -1;
        }
        else {
          iVar3 = pCVar4[2].refCount;
        }
        putParticleBindTrace__8CGPrgObjFiiP8CGObjectfi
                  ((double)FLOAT_803319c0,(CGPrgObj *)gMonObj,iVar7 + iVar5 | iVar3 << 8,
                   *(int *)&gMonObj->field_0x594,&gMonObj->gObject,0);
      }
    }
  }
  onChangePrg__10CGCharaObjFi(gMonObj,param_2);
  return;
}


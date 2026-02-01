// Function: setIceJEffect__8CGMonObjFi
// Entry: 80113f58
// Size: 172 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void setIceJEffect__8CGMonObjFi(CGMonObj *gMonObj,int param_2)

{
  ushort uVar1;
  int iVar2;
  CRef *pCVar3;
  int iVar4;
  
  endPSlotBit__10CGCharaObjFi(gMonObj,0x20000);
  if (param_2 != 0) {
    uVar1 = *(ushort *)((int)(gMonObj->gObject).m_scriptHandle[9] + 0x1aa);
    for (iVar4 = 0; iVar4 < (int)(uint)uVar1; iVar4 = iVar4 + 1) {
      pCVar3 = ((gMonObj->gObject).m_charaModelHandle)->m_pdtLoadRef;
      if (pCVar3 == (CRef *)0x0) {
        iVar2 = -1;
      }
      else {
        iVar2 = pCVar3[2].refCount;
      }
      putParticleBindTrace__8CGPrgObjFiiP8CGObjectfi
                ((double)FLOAT_803319c0,(CGPrgObj *)gMonObj,iVar4 + 0x5aU | iVar2 << 8,
                 *(int *)&gMonObj->field_0x5a8,&gMonObj->gObject,0);
    }
  }
  return;
}


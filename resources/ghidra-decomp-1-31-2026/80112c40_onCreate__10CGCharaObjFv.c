// Function: onCreate__10CGCharaObjFv
// Entry: 80112c40
// Size: 276 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onCreate__10CGCharaObjFv(CGCharaObj *gCharaObj)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  
  onCreate__8CGPrgObjFv(&gCharaObj->gPrgObj);
  fVar1 = FLOAT_80331964;
  if (DAT_8032ee6c == '\0') {
    DAT_8032ee68 = 0;
    DAT_8032ee6c = '\x01';
  }
  iVar3 = DAT_8032ee68 + 1;
  *(int *)&(gCharaObj->gPrgObj).m_flags = DAT_8032ee68;
  DAT_8032ee68 = iVar3;
  gCharaObj->field_0x63c = gCharaObj->field_0x63c & 0x7f;
  gCharaObj->field_0x640 = gCharaObj->field_0x640 & 0x7f;
  gCharaObj->field_0x648 = gCharaObj->field_0x648 & 0x7f;
  gCharaObj->field_0x650 = gCharaObj->field_0x650 & 0x7f;
  gCharaObj->field_0x658 = gCharaObj->field_0x658 & 0x7f;
  *(undefined4 *)&gCharaObj->field_0x660 = 0;
  *(undefined4 *)&gCharaObj->field_0x664 = 0;
  *(undefined4 *)&gCharaObj->field_0x668 = 0;
  *(undefined4 *)&gCharaObj->field_0x684 = 0xffffffff;
  *(undefined4 *)&gCharaObj->field_0x688 = 0;
  *(float *)&gCharaObj->field_0x690 = fVar1;
  *(float *)&gCharaObj->field_0x694 = fVar1;
  gCharaObj->m_aStarGroupId = 0;
  *(undefined4 *)&gCharaObj->field_0x6a0 = 0;
  *(undefined4 *)&gCharaObj->field_0x6a8 = 0;
  memset(&gCharaObj->field_0x6ac,0,0xc);
  iVar3 = 0;
  do {
    uVar2 = GetFreeParticleSlot__13CFlatRuntime2Fv(&CFlat);
    iVar3 = iVar3 + 1;
    *(undefined4 *)&gCharaObj->field_0x564 = uVar2;
    gCharaObj = (CGCharaObj *)&(gCharaObj->gPrgObj).object.base_object.object.m_freeListNode;
  } while (iVar3 < 0x16);
  return;
}


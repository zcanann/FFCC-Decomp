// Function: onCancelStat__8CGMonObjFi
// Entry: 80119278
// Size: 432 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onCancelStat__8CGMonObjFi(CGMonObj *gMonObj,undefined4 param_2)

{
  __ptmf_scall(gMonObj,*(undefined4 *)&gMonObj->field_0x708);
  switch(*(undefined4 *)&gMonObj->field_0x520) {
  case 0x16:
    gMonObj->field_0x6b9 = 0;
    SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0,0);
    SetAnimSlot__8CGObjectFii(&gMonObj->gObject,1,1);
    SetAnimSlot__8CGObjectFii(&gMonObj->gObject,4,4);
    SetAnimSlot__8CGObjectFii(&gMonObj->gObject,6,6);
    break;
  case 0x17:
    gMonObj->field_0x6b9 = 1;
    SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0x28,0);
    SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0x29,1);
    SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0x2a,4);
    SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0x2b,6);
    break;
  case 0x18:
    gMonObj->_bossBranchRelated = 1;
    SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0,0);
    SetAnimSlot__8CGObjectFii(&gMonObj->gObject,4,4);
    (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask | 0x50000;
    (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask & 0xfffffff7;
    (gMonObj->gObject).m_objectFlags = (gMonObj->gObject).m_objectFlags & 0xffffffef;
    break;
  case 0x1d:
    CancelMove__8CGObjectFi(&gMonObj->gObject,1);
    break;
  case 0x21:
    SoundBuffer._1252_4_ = 0;
    memset(&gMonObj->field_0x70c,0,0x34);
    if ((*(uint *)&gMonObj->field_0x710 & 2) == 0) {
      __ptmf_scall(gMonObj,*(undefined4 *)&gMonObj->field_0x708);
    }
  }
  onCancelStat__10CGCharaObjFi(gMonObj,param_2);
  return;
}


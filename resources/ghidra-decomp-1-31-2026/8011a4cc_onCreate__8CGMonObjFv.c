// Function: onCreate__8CGMonObjFv
// Entry: 8011a4cc
// Size: 168 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onCreate__8CGMonObjFv(CGMonObj *gMonObj)

{
  onCreate__10CGCharaObjFv((CGCharaObj *)gMonObj);
  *(undefined4 *)&gMonObj->field_0x6c4 = 0xffffffff;
  *(undefined2 *)&gMonObj->field_0x6e4 = 0;
  *(undefined2 *)&gMonObj->field_0x6e6 = 0;
  *(undefined4 *)&gMonObj->field_0x6c8 = 0;
  *(undefined4 *)&gMonObj->field_0x6cc = 0;
  gMonObj->_bossBranchRelated = 0;
  gMonObj->field_0x6b8 = 0;
  gMonObj->field_0x6b9 = 0;
  gMonObj->field_0x6ba = 0;
  gMonObj->field_0x6bc = 0;
  gMonObj->field_0x6bd = 0;
  gMonObj->field_0x6be = 0;
  *(undefined4 *)&gMonObj->field_0x6f0 = 0;
  *(undefined4 *)&gMonObj->field_0x6f4 = 0;
  gMonObj->field_0x6bf = 0;
  gMonObj->field_0x6c0 = 0;
  gMonObj->field_0x6c2 = 0;
  gMonObj->field_0x6c3 = 0;
  *(undefined4 *)&gMonObj->field_0x6d8 = 0;
  *(undefined4 *)&gMonObj->field_0x6dc = 0;
  gMonObj->field_0x6bb = 0;
  *(undefined4 *)&gMonObj->field_0x704 = 0;
  memset(&gMonObj->field_0x70c,0,0x34);
  *(undefined4 *)&gMonObj->field_0x6e0 = 0;
  gMonObj->field_0x6c1 = 0;
  return;
}


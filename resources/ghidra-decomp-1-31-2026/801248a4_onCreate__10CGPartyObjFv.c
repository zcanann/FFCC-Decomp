// Function: onCreate__10CGPartyObjFv
// Entry: 801248a4
// Size: 244 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onCreate__10CGPartyObjFv(CGCharaObj *param_1)

{
  float fVar1;
  
  onCreate__10CGCharaObjFv(param_1);
  *(undefined4 *)&param_1->field_0x6d0 = 0;
  fVar1 = FLOAT_80331a78;
  *(undefined4 *)&param_1->field_0x6c8 = 0;
  *(undefined4 *)&param_1->field_0x6cc = 0;
  *(undefined4 *)&param_1->field_0x6bc = 0;
  param_1[1].gPrgObj.object.base_object.object.m_thisBase = (uint32_t *)0x0;
  *(undefined4 *)&param_1[1].gPrgObj.object.base_object.object.m_classIndex = 0;
  param_1[1].gPrgObj.object.base_object.object.m_engineObject = DAT_8032ec24;
  param_1[1].gPrgObj.object.base_object.object.m_codePos = 0;
  param_1->field_0x6b8 = param_1->field_0x6b8 & 0x7f;
  param_1->field_0x6b8 = param_1->field_0x6b8 & 0xf7;
  param_1[1].gPrgObj.object.base_object.object.m_stackPointer = (uint32_t *)0x0;
  param_1[1].gPrgObj.object.base_object.object.m_localBase = (uint32_t *)0x0;
  param_1->field_0x6b8 = param_1->field_0x6b8 & 0xbf;
  param_1->field_0x6b8 = param_1->field_0x6b8 & 0xdf;
  param_1->field_0x6b8 = param_1->field_0x6b8 & 0xef;
  param_1->field_0x6b8 = param_1->field_0x6b8 & 0xfb;
  param_1->field_0x6b8 = param_1->field_0x6b8 & 0xfd;
  *(float *)&param_1->field_0x5bc = fVar1;
  *(undefined4 *)&param_1->field_0x6c0 = 0xffffffff;
  *(undefined2 *)&param_1[1].gPrgObj.object.base_object.object.m_previous = 0;
  if (DAT_8032ee74 == '\0') {
    DAT_8032ee70 = 0;
    DAT_8032ee74 = '\x01';
  }
  if (DAT_8032ee70 == 0) {
    DAT_8032ee70 = 1;
  }
  return;
}

